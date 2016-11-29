#include "Game2CenterCommC.h"
#include "stdafx.h"
#include "Protocols.h"
#include "MoneyParam.h"
#include "UserForbidMgr.h"
#include "MapMgr.h"
#include "UserMgr.h"
#include "GM.h"
#include "ItemMgr.h"
#include "Monster.h"
#include "Loot.h"
#include "GameServerSysMail.h"
#include "SysMsgDefine.h"
#include "Trump.h"
#include "Bubble.h"
#include "FighterManager.h"
#include "Battle.h"
#include "GetCondMgr.h"
#include "Parameter.h"
#include "TripodMgr.h"
#include "Mall.h"
#include "TaskMarket.h"
#include "HeroFighter.h"
#include "GodChest.h"
#include "DayActProtS.h"
#include "GUIDMgr.h"
#include "AllTimers.h"
#include "GameNetMgr.h"

//接收：替换帐号
bool CGame2CenterCommC::OnRecv_ReplaceUser(
        UINT64 qwUsrID, //帐号ID
        shared_func<SReplaceUserAck>& fnAck //返回回调函数
        )
{
    NetMgr.GetGateHandler()->OnUserLogout(qwUsrID);
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return false;
    }
    pUser->OnReplace();
    return true;
}

bool CGame2CenterCommC::OnRecv_GMCmd(
        UINT64 qwUsrID, //帐号ID
        const std::string& strInfo, //GM指令信息
        shared_func<SGMCmdAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return false;
    }
#ifdef _DEBUG
    GM::GM(strInfo.c_str(), 0xFFFF, (void*)&pUser);
#else
    //GM::GM(strInfo.c_str(), pUser->GetGMLvl(), (void*)&pUser);
    GM::GM(strInfo.c_str(), 0xFFFF, (void*)&pUser);
#endif
    return true;
}

//接收：充值接口
bool CGame2CenterCommC::OnRecv_AddTotalRecharge(
        const NRoleInfoDefine::SRecharge& oRecharge, //充值仙石的数据
        const std::string& strUdp1, //udpLog参数1(平台传来的)
        const std::string& strUdp2, //udpLog参数2(平台传来的)
        shared_func<SAddTotalRechargeAck>& fnAck //返回回调函数
        )
{
    if (!oRecharge.qwRoleID)
    {
        LOG_CRI << "UserID is 0 !";
        return false;
    }
    if (!oRecharge.dwCount || !oRecharge.dwGold)
    {
        LOG_CRI << "Recharge Gold is 0 !";
        return false;
    }
    LOG_INF << "Rev Recharge Requst Player:"<< oRecharge.qwRoleID <<"---Gold :" << oRecharge.dwGold;
    CUserPtr pUser = CUserMgr::GetUserByUserID(oRecharge.qwRoleID);
    if (pUser)
    {
        bool bRes = pUser->AddTotalRecharge(oRecharge.dwGold);
        if (bRes)
        {
            g_Game2DBCommC.Send_UpdateRecharge(oRecharge);
            string strData = g_Game2CenterLog.BuildPkg_LogRecharge(pUser->GetUserID(), strUdp1, strUdp2, oRecharge.dwGold);
            pUser->SendCenterSvrPkg(strData);
            CMall::Instance().OnChongZhiAward(oRecharge.wGoldID, oRecharge.dwCount, pUser);
        }
        return bRes;
    }
    //XXX 玩家不在线
    CUserMgr::LoadUser(oRecharge.qwRoleID,[oRecharge,strUdp1,strUdp2](CUserPtr pUser){
            if (!pUser)
                return;
            bool bRes = pUser->AddTotalRecharge(oRecharge.dwGold);
            if (bRes)
            {
                g_Game2DBCommC.Send_UpdateRecharge(oRecharge);
                string strData = g_Game2CenterLog.BuildPkg_LogRecharge(pUser->GetUserID(), strUdp1, strUdp2, oRecharge.dwGold);
                pUser->SendCenterSvrPkg(strData);
                CMall::Instance().OnChongZhiAward(oRecharge.wGoldID, oRecharge.dwCount, pUser);
            }
            });
    return true;
}

//接收：充值接口(改版:加仙石礼包到邮件)
bool CGame2CenterCommC::OnRecv_AddRechargeMailItem(
    const NRoleInfoDefine::SRecharge& oRecharge, //充值仙石的数据
    const std::string& strUdp1, //udpLog参数1(平台传来的)
    const std::string& strUdp2, //udpLog参数2(平台传来的)
    shared_func<SAddRechargeMailItemAck>& fnAck //返回回调函数
)
{
    if (!oRecharge.qwRoleID)
    {
        LOG_CRI << "UserID is 0 !";
        return false;
    }
    if (!oRecharge.dwCount || !oRecharge.dwGold)
    {
        LOG_CRI << "Recharge Gold is 0 !";
        return false;
    }

    //发送邮件
    NMailProt::SysMailSendTxt stBody;
    stBody.dwstrMsgID = BODY_RECHARGE_MAIL;
    SItemInfo* pItemInfo = CItemMgr::GetItemConfig(oRecharge.wGoldID);
    if (pItemInfo)
        stBody.vecParam.push_back(pItemInfo->oItemCfg._Name);
    else
        stBody.vecParam.push_back(NumberToString(oRecharge.wGoldID));
    stBody.vecParam.push_back(NumberToString(oRecharge.dwCount));
    TVecItemGenInfo vecItems;
    SItemGenInfo stItemGen;
    stItemGen.wItemID = oRecharge.wGoldID;
    stItemGen.dwCount = oRecharge.dwCount;
    stItemGen.eBindType = eBindGet;
    vecItems.push_back(stItemGen);
    TVecUINT64 vecTargets;
    vecTargets.push_back(oRecharge.qwRoleID);
    GameServerSysMail::SendSysMail(SEND_RECHARGE_MAIL, TITLE_RECHARGE_MAIL, stBody, vecTargets, &vecItems);

    CUserPtr pUser = CUserMgr::GetUserByUserID(oRecharge.qwRoleID);
    if (pUser)
    {
        pUser->AddTotalRecharge(oRecharge.dwGold, false);
        g_Game2DBCommC.Send_UpdateRecharge(oRecharge);
        string strData = g_Game2CenterLog.BuildPkg_LogRecharge(pUser->GetUserID(), strUdp1, strUdp2, oRecharge.dwGold);
        pUser->SendCenterSvrPkg(strData);
        return true;
    }
    //XXX 玩家不在线
    CUserMgr::LoadUser(oRecharge.qwRoleID,[oRecharge,strUdp1,strUdp2](CUserPtr pUser){
            if (!pUser)
                return;
            pUser->AddTotalRecharge(oRecharge.dwGold, false);
            g_Game2DBCommC.Send_UpdateRecharge(oRecharge);
            string strData = g_Game2CenterLog.BuildPkg_LogRecharge(pUser->GetUserID(), strUdp1, strUdp2, oRecharge.dwGold);
            pUser->SendCenterSvrPkg(strData);
            });
    return true;
}

//接收：补偿玩家未创建预先充值的仙石
bool CGame2CenterCommC::OnRecv_AddTotalPrepaid(
        UINT64 qwUsrID, //帐号ID
        UINT32 dwGold, //仙石数量
        shared_func<SAddTotalPrepaidAck>& fnAck //返回回调函数
        )
{
    if (!qwUsrID || !dwGold)
    {
        LOG_CRI << "UserID or dwGold is 0 ! UserID:" << qwUsrID << ",dwGold:" << dwGold;
        return false;
    }
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (pUser)
    {
        if (!pUser->AddTotalRecharge(dwGold))
            LOG_CRI << "Add Prepaid Error! Prepaid dwGold is " << dwGold;
    }
    return true;
}

//接收：Q点直购道具
bool CGame2CenterCommC::OnRecv_AddQQCoinBuyItem(
    UINT64 qwUsrID, //帐号ID
    const TVecUserItem& vecUserItem, //物品列表
    shared_func<SAddQQCoinBuyItemAck>& fnAck //返回回调函数
)
{
    if (!qwUsrID || vecUserItem.empty())
    {
        LOG_CRI << "UserID or vecUserItem's size is 0 ! UserID:" << qwUsrID << ",vecUserItem size:" << vecUserItem.size();
        return false;
    }
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (pUser)
    {
        for(auto & rInfo : vecUserItem)
        {
            for(UINT32 dwIndex = 0; dwIndex < rInfo.dwCount; ++ dwIndex)
            {
                if (rInfo.dwTypeID == 302) //月卡
                    pUser->OpenSelfMonthCard();
            }
        }
        return true;
    }
    //XXX 玩家不在线
    CUserMgr::LoadUser(qwUsrID,[vecUserItem](CUserPtr pUser){
            if (!pUser)
                return;
            for(auto & rInfo : vecUserItem)
            {
                for(UINT32 dwIndex = 0; dwIndex < rInfo.dwCount; ++ dwIndex)
                {
                    if (rInfo.dwTypeID == 302) //月卡
                        pUser->OpenSelfMonthCard();
                }
            }
            });
    return true;
}

//接收：询问可否提取附件
bool CGame2CenterCommC::OnRecv_CheckMailAttch(
        UINT64 qwUsrID, //帐号ID
        UINT64 qwMailID, //邮件ID
        const NMailProt::TVecMailAttachment& vecItemInfo, //附件
        shared_func<SCheckMailAttchAck>& fnAck //返回回调函数
        ) 
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return false;
    }
    vector<CItemPtr> vecItem;
    TVecResource vecRes;
    TransMailAttachToItem(vecItemInfo,vecItem,vecRes);
    if(!pUser->GetPack().CanAddItem(vecItem))
    {
        fnAck->byCan = 1;
    }
    return true;

}

//接收：发送附件
void CGame2CenterCommC::OnRecv_SendMailAttch(
        UINT64 qwUsrID, //帐号ID
        UINT64 qwMailID, //邮件ID
        const NMailProt::TVecMailAttachment& vecItemInfo //附件
        ) 
{
    /* pUser->GetPack().PushMailAttach(vecItemInfo);*/
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        //发送补偿邮件
        return ;
    }

    vector<CItemPtr> vecItem;
    TVecResource vecRes;
    TransMailAttachToItem(vecItemInfo,vecItem,vecRes);
    TVecAddItemMsg vecItemMsg;  
    for (auto iter = vecItem.begin();iter != vecItem.end();iter++)
    {
        CItem& rItem = *(*iter);
        if(6 == rItem.GetItemCfg()._Type)
        {
            UINT32 wFighterID = rItem.GetItemCfg()._AttrIdx_3;
            CPlayerPtr pPlayer = pUser->GetPlayer();
            if(pPlayer&&pPlayer->GetFighterManager())
            {
                pPlayer->GetFighterManager()->GetFighterForce(wFighterID);
            }
            continue;
         }
        if(pUser->GetPack().CanAddItem(rItem))
        {
            pUser->GetPack().AddItem(rItem,-1,true,false,true,NLogDataDefine::ItemFrom_Mail);
            SAddItemMsg rAddItemMsg;
            rAddItemMsg.wItemID = rItem.GetItemID();
            rAddItemMsg.wCount = rItem.GetCount();
            rAddItemMsg.byQuality = rItem.GetQuality();
            vecItemMsg.push_back(rAddItemMsg);
        }
        else
        {
            LOG_CRI<< "Cam Not Recieve Mail";
            //发送补偿邮件
        }

    }
    if(!vecItemMsg.empty())
    {
        pUser->SendPkg(g_ItemProtS.BuildPkg_AddItemSystemMsg(vecItemMsg)); 
    }
    //加钱
    CStore::AddResource(*pUser,vecRes,NLogDataDefine::ItemFrom_Mail);
}


void CGame2CenterCommC::TransMailAttachToItem(const NMailProt::TVecMailAttachment& vecItemInfo,vector<CItemPtr>& rVecCItem,TVecResource& vecRes)
{
    for (auto iter = vecItemInfo.begin();iter != vecItemInfo.end();iter++)
    {
        SMailBaseAttachmentPtr itemPtr = *(iter);
        switch (itemPtr->GetClassType())
        {
            case eType_SItemAttachment:
                {
                    SItemAttachmentPtr pAttach = dynamic_pointer_cast<SItemAttachment>(itemPtr);
                    if(pAttach == NULL)
                    {
                        break;
                    }
                    const TVecMailItemInfo& rvecItemInfo = pAttach->vecItemInfo;
                    for (auto it = rvecItemInfo.begin();it != rvecItemInfo.end();it++)
                    {
                        const SMailItemInfo& rMailInfo = *it;
                        if ((rMailInfo.wItemID > EMONEY_NONE) && (rMailInfo.wItemID < EMONEY_END))
                        {
                            SResource stSResource;
                            stSResource._eRes = static_cast<EMoneyType>(rMailInfo.wItemID);
                            stSResource._dwValue = rMailInfo.wCount;
                            vecRes.push_back(stSResource);
                        }
                        else
                        {
                            TransMailAttachToItem(rVecCItem,rMailInfo);

                        }
                    }

                }
                break;
            case eType_SItemBaseCT:
                {
                    SItemBaseCTPtr pAttach = dynamic_pointer_cast<SItemBaseCT>(itemPtr);
                    if(pAttach == NULL)
                    {
                        break;
                    }
                    for (auto iter = pAttach->vecItems.begin();iter != pAttach->vecItems.end();iter++)
                    {
                        SItemPtr ptr = *iter;
                        TransMailStance(rVecCItem,ptr);
                    };
                }
                break;
            default:
                break;

        }

    }
}

//接收：修改签名
void CGame2CenterCommC::OnRecv_SetSign(
        UINT64 qwUsrID, //帐号ID
        const std::string& strSign //签名
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return;
    }
    pUser->SetSign(strSign);
}

//接收：修改表情
void CGame2CenterCommC::OnRecv_SetMood(
        UINT64 qwUsrID, //帐号ID
        UINT16 wMood //表情
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return;
    }
    pUser->SetMood(wMood);
}

//////////////////////////////////////////////////////////////////////
void CGame2CenterCommC::TransMailAttachToItem(vector<CItemPtr>& rVecCItem,const SMailItemInfo& rMailInfo)
{
    SItemInfo* pCfg = CItemMgr::GetItemConfig(rMailInfo.wItemID);
    if(NULL == pCfg)
        return; 
    CreateMailItem(rVecCItem,rMailInfo,pCfg->oItemCfg);
    /*
       SItemCFG& rItemCfg = pCfg->oItemCfg;
       switch((CItem::GetItemType(rItemCfg))
       {
       case eItemEquip:
       {
       CreateMailEquip(rVecCItem,rMailInfo);

       }
       break;
       case eItemFashion:
       {
       CreateMailFashion(rVecCItem,rMailInfo);
       }
       break;
       case eItemCitta :
       {
       CreateMailCitta(rVecCItem,rMailInfo);
       }
       break;
       default:
       CreateMailItem(rVecCItem,rMailInfo,rItemCfg);
       break;
       }
       */
}

void CGame2CenterCommC::AddMailItemProp(CItemPtr pItem,const SMailItemInfo& rMailInfo)
{  
    if(!pItem->IsBind() && rMailInfo.eBindType == NItemProt::eBindGet)
    {
        pItem->SetBind(true);
    }
    if(rMailInfo.byExpired >0 && rMailInfo.dwExpireTime > 0 )
    {
        UINT32 dwExpiredTime= time(NULL)+rMailInfo.dwExpireTime;
        pItem->SetExpiration(dwExpiredTime,true);
    }
}

void CGame2CenterCommC::CreateMailItem(vector<CItemPtr>& rVecCItem,const SMailItemInfo& rMailInfo,SItemCFG& rItemCfg)
{
    if(CItem::IsStackItem(rItemCfg))
    { 
        UINT16 MaxCount = CItem::GetMaxNum(rItemCfg);

        if(MaxCount == 0)
        {
            LOG_CRI <<"STACK ITEM MAX NUM IS 0:ID:" << rMailInfo.wItemID;
        }
        UINT16 Fullsize = rMailInfo.wCount/MaxCount;
        CreateMailItemWithNum(rVecCItem,rMailInfo,Fullsize,MaxCount);
        UINT16 resSize = rMailInfo.wCount - Fullsize*MaxCount;
        if(resSize > 0 )
        {
            CreateMailItemWithNum(rVecCItem,rMailInfo,1,resSize);
        }
    }
    else
    {
        CreateMailItemWithNum(rVecCItem,rMailInfo,rMailInfo.wCount,1);
    }
}

void CGame2CenterCommC::CreateMailItemWithNum(vector<CItemPtr>& rVecCItem,const SMailItemInfo& rMailInfo,UINT16 wCount,UINT16 wEachCount)
{
    for(auto i = 0; i < wCount;i++)
    {
        CItemPtr pItem = CItemMgr::CreateAllTypeItem(rMailInfo.wItemID,wEachCount);
        if(NULL != pItem)
        {
            AddMailItemProp(pItem,rMailInfo);
            rVecCItem.push_back(pItem);
        }
    }
}

void CGame2CenterCommC::TransMailStance(vector<CItemPtr>& rVecCItem, SItemPtr ItemPtr)
{
    CItemPtr pItem = CItemMgr::CreateItem(*ItemPtr);
    if(pItem != NULL)
    {
        rVecCItem.push_back(pItem);
    }
}

void  CGame2CenterCommC::FighterToOther(UINT64 qwUsrID,UINT64 qwOtherID,bool bDrop,
        NBattleGS::EBattleType eBattleType, //战斗类型 
        UINT32 dwBufferID, //临时增加的buffer
        UINT32 dwSkillAttrID, //增加的属性
        UINT32 dwCount, //buffer叠加层数
        BattleResult fun
        )

{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        fun(false,false,0); 
        return ;
    }
    //如果是机器人
    CPlayerPtr pPlayer = pUser->GetPlayer();
    IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
    TVecBattleFighterPtr vecBattleFighter;
    pPlayer->GetBattleFighterList(vecBattleFighter);
    vector<TVecBattleFighterPtr> vecvecBattleFighter2;
    IBattleFighterPtr pScene;
    if(qwOtherID <= 65535)
    {
        UINT64 qwDefenseID = GET_GUID(GUID_MONSTER);
        UINT64 qwMainMonster = CMonster::GetBattleFighterListByGroupID(vecvecBattleFighter2, qwOtherID,qwDefenseID, vecBattleFighter);
        if(!qwMainMonster)
        {
            LOG_CRI << "Can't find Monster! GroupID: " << qwOtherID;
            fun(false,false,0);
            return ;
        }
        pScene = CMonster::GetSceneFighter(qwOtherID);
        if (!pScene)
            pScene = pPlayer->GetSceneFighter();
        pBS->PutFighters(0, pPlayer->GetMainFighter()->GetInstID(), pPlayer->GetLevel(), vecBattleFighter, pPlayer->GetRoleID());
        pBS->PutFighters(1, qwMainMonster, CMonster::GetMonsterLevelByGroupID(qwOtherID), vecvecBattleFighter2[0], qwDefenseID);
        pBS->PutScene(pScene);
        pBS->Start(EBTPlayer);
        std::string strReport;
        pBS->GetReport(strReport);
        if(bDrop && pBS->GetFinalWinner() == EBResultAttackWin)
            CMonster::OnDrop(*pPlayer,qwOtherID,strReport);
        pPlayer->SendPkg(g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayer->GetRoleID(), pPlayer->GetMainFighter()->GetID()));

        if(pBS->GetFinalWinner() == EBResultAttackWin)
            fun(true,true,pBS->GetBattleID());
        else
            fun(true,false,pBS->GetBattleID());
        return ;
    }
    else //到数据库查询
    {
        CUserMgr::LoadUser(qwOtherID,
                [fun,qwUsrID,qwOtherID,eBattleType,dwBufferID,dwSkillAttrID,dwCount](CUserPtr pOtherUser)
                {
                if(pOtherUser == NULL)
                {
                fun(false,false,0);
                return ;
                }
                CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
                if (!pUser)
                {
                fun(false,false,0); 
                return ;
                }
                IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));

                CPlayerPtr pPlayer = pUser->GetPlayer();
                TVecBattleFighterPtr vecBattleFighter;
                IBattleFighterPtr pScene = NULL;
                UINT16 wMapID = 0;
                switch (eBattleType)
                { 
                    case NBattleGS::EBArena: //竞技场
                        wMapID = SParamConfig::byFightMapDoujian; 
                        break;
                    case NBattleGS::EBDemonTower: //锁妖塔
                        wMapID = SParamConfig::byFightMapSuoyaota;
                        break;
                    case NBattleGS::EBShip://元江金船
                        wMapID =  SParamConfig::wFightMapShip;
                    default:
                        break;

                }
                LOG_CRI << "battle start";
                if(wMapID != 0)
                    pScene = CMapMgr::ToBattleFighterWithFighterMapID(wMapID);
                if (!pScene)
                    pScene = pPlayer->GetSceneFighter();
                pPlayer->GetBattleFighterList(vecBattleFighter);
                pBS->PutFighters(0, pPlayer->GetMainFighter()->GetInstID(), pPlayer->GetLevel(), vecBattleFighter, pPlayer->GetRoleID());

                CPlayerPtr pOtherPlayer = pOtherUser->GetPlayer();

                //临时添加buffer
                if(dwBufferID)
                {

                    TVecUINT32 vecParam;
                    vecParam.push_back(dwSkillAttrID);
                    vecParam.push_back(dwCount);
                    pOtherPlayer->AddBuff(dwBufferID,vecParam,100);
                }
                TVecBattleFighterPtr vecBattleFighter2;
                pOtherPlayer->GetBattleFighterList(vecBattleFighter2);
                pBS->PutFighters(1, pOtherPlayer->GetMainFighter()->GetInstID(), pOtherPlayer->GetLevel(), vecBattleFighter2, pOtherPlayer->GetRoleID());
                pBS->PutScene(pScene);
                LOG_CRI << "battle begin";
                pBS->Start(EBTPlayer);
                std::string strReport;
                LOG_CRI << "battle end0";
                pBS->GetReport(strReport);
                LOG_CRI << "battle end";

                if(dwBufferID)
                {
                    pOtherPlayer->RemoveBuff(dwBufferID);
                }
                pPlayer->SendPkg(g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayer->GetRoleID(), pPlayer->GetMainFighter()->GetID()));
                if(pBS->GetFinalWinner() == EBResultAttackWin)
                    fun(true,true,pBS->GetBattleID());
                else
                    fun(true,false,pBS->GetBattleID());
                return ;
                });

    }


}
//请求和他人发起战斗
bool CGame2CenterCommC::OnRecv_FigtherToOther(
        UINT64 qwUsrID, //帐号ID
        UINT64 qwOtherID, //他人的ID
        UINT32 dwCost, //花费的游戏币
        NBattleGS::EBattleType eBattleType, //战斗类型
        UINT32 dwBufferID, //临时增加的buffer
        UINT32 dwSkillAttrID, //增加的属性
        UINT32 dwCount, //buffer叠加层数
        shared_func<SFigtherToOtherAck>& fnAck //返回回调函数
        )
{
    FighterToOther(qwUsrID,qwOtherID,false,eBattleType,dwBufferID,dwSkillAttrID,dwCount,[qwUsrID,qwOtherID,dwCost,fnAck](bool bFindOther,bool bIsWinner,UINT64 qwBattleID){
            if(!bFindOther)
            {
            fnAck->byRet = 1;
            fnAck(false);
            return;
            }
            CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
            if (!pUser)
            {
            fnAck->byRet = 1;
            fnAck(false);
            return;

            }
            if(dwCost > 0)
            {
            pUser->SubMoney(EMONEY_GOLD,dwCost,NLogDataDefine::ItemTo_FigtherToOther);
            }
            if(bIsWinner)
            {
                fnAck->bySuc = 1;
            }
            fnAck->byRet = 0;
            fnAck->qwBattleID = qwBattleID;
            if(pUser)
            {
                fnAck->dwSelfFighterPower = pUser->GetPlayer()->GetBattlePoint();
                fnAck->bySelfQuality = pUser->GetPlayer()->GetMainFighter()->GetColor();
            }
            if(qwOtherID > 65535)
            {
                CUserPtr pOtherUser = CUserMgr::GetUserByUserID(qwOtherID);
                if(pOtherUser)
                {
                    fnAck->dwOtherFighterPower = pOtherUser->GetPlayer()->GetBattlePoint();
                    fnAck->byOtherQuality = pOtherUser->GetPlayer()->GetMainFighter()->GetColor();
                }
            }

            fnAck(true);  
    });
    return true;
}

//接收：询问可否放下掉落
bool CGame2CenterCommC::OnRecv_CanPushLoot(
        UINT64 qwUsrID, //帐号ID
        UINT32 dwLootId, //掉落的ID
        shared_func<SCanPushLootAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        fnAck->byRet = 1;
        return false;
    }
    CPack& oPack = pUser->GetPack(); 
    TVecResource vecRes;
    std::vector<SItemGenInfo> vecItems;
    LOOT.Roll(dwLootId, vecItems,vecRes);
    if(!vecItems.empty())     
    {
        if(!oPack.CanAddItem(vecItems)) 
        {
            fnAck->byRet = 1;
        }
    }
    return true;
}
//接收：掉落到玩家包裹
void CGame2CenterCommC::OnRecv_PushLoot(
        UINT64 qwUsrID, //帐号ID
        EOpSource eSource, //原因
        NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
        UINT32 dwLootId //掉落的ID
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return ;
    }
    CPack& oPack = pUser->GetPack(); 
    std::vector<SItemGenInfo> vecMailInfo;
    TVecResource vecRes;
    std::vector<SItemGenInfo> vecItems;
    LOOT.Roll(dwLootId, vecItems,vecRes);
    if(!vecItems.empty())
    {
        if(!oPack.CanAddItem(vecItems))
        {
            for(size_t i = 0; i !=  vecItems.size();i++)
            {
                vecMailInfo.push_back(vecItems[i]);
            }
        }
        else
        {
            oPack.AddItem(vecItems, eItemFrom);

        }
    }
    if(!vecRes.empty() )
    {
        CStore::AddResource(*pUser,vecRes,eItemFrom);
    }
    if(!vecMailInfo.empty())
    {
        UINT16 wSystemMsgID  = 0 ;
        UINT32 dwMailID = 0;
        UINT32 dwSendID = 0;
        UINT32 dwTitleID = 0;
        switch(eSource)
        {
            case eOpAreaAward:
                {
                    wSystemMsgID = eMsgArenaAwardPackFull;
                    dwMailID = BODY_ARENAAWARD;
                    dwSendID = SEND_ARENAAWARD;
                    dwTitleID = TITLE_ARENAAWARD;
                }
                break;
            case eOpArenaWirship:
                {
                    wSystemMsgID = eMsgArenaWirshipPackFull;
                    dwMailID = BODY_ARENAWIRSHIP;
                    dwSendID = SEND_ARENAWIRSHIP;
                    dwTitleID = TITLE_ARENAWIRSHIP;
                }
                break;
            default:
                break;
        }
        if (wSystemMsgID  > 0 && dwMailID > 0 && dwSendID > 0 && dwTitleID > 0)
        {
            pUser->GetPlayer()->SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(wSystemMsgID));
            //发送邮件
            NMailProt::SysMailSendTxt stBody;
            stBody.dwstrMsgID = dwMailID;
            TVecUINT64 vecTargets;
            vecTargets.push_back(qwUsrID);
            GameServerSysMail::SendSysMail(dwSendID,dwTitleID,stBody,vecTargets,&vecMailInfo);
        }
    }
    return ;
}

//接收：扣钱或物品
bool CGame2CenterCommC::OnRecv_ReduceItem(
        UINT64 qwUsrID, //帐号ID
        NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
        UINT32 dwID, //钱或物品ID
        UINT32 dwCount, //数量
        shared_func<SReduceItemAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        fnAck->byRet = 2;
        return false;
    }
    if(dwID > EMONEY_NONE && dwID < EMONEY_END)
    {
        TVecResource vecRes;
        SResource sRes;
        sRes._eRes = static_cast<EMoneyType>(dwID);
        sRes._dwValue = dwCount;
        vecRes.push_back(sRes);
        if (CStore::SubResource(*pUser,vecRes,eItemTo))
        {
            fnAck->byRet = 0;
            return true;
        }
        else
        {
            fnAck->byRet = 1;
            return false;
        }
    }
    else
    {
        CPack& oPack = pUser->GetPack();
        if (oPack.DelItemByItemID(static_cast<UINT16>(dwID),static_cast<UINT16>(dwCount), true, eItemTo))
        {
            fnAck->byRet = 0;
            return true;
        }
        else
        {
            fnAck->byRet = 2;
            return false;
        }
    }
}

//接收：物品数量是否够
bool CGame2CenterCommC::OnRecv_CanReduceItem(
        UINT64 qwUsrID, //帐号ID
        UINT32 dwID, //物品ID
        UINT32 dwCount, //数量
        shared_func<SCanReduceItemAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        fnAck->byRet = 2;
        return false;
    }
    if(dwID > EMONEY_NONE && dwID < EMONEY_END)
    {
        TVecResource vecRes;
        SResource sRes;
        sRes._eRes = static_cast<EMoneyType>(dwID);
        sRes._dwValue = dwCount;
        vecRes.push_back(sRes);
        if(!CStore::CanSubResource(*pUser,vecRes))
        {
            fnAck->byRet = 1;
        }
    }
    else
    {
        CPack& oPack = pUser->GetPack();
        if(oPack.GetItemCount(dwID) < dwCount)
        {
            fnAck->byRet = 1;
        }
    }
    return true;
}

void CGame2CenterCommC::OnRecv_SendSysMsg(
        UINT64 qwUsrID, //帐号ID
        UINT16 wMsgID //消息ID
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return ;
    }
    pUser->GetPlayer()->SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(wMsgID));

}
//接收：任务事件通知
void CGame2CenterCommC::OnRecv_ActionNotify(
        UINT64 qwUsrID, //帐号ID
        UINT16 wAction //通知类型
        ) 
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return ;
    }
    if( wAction >= eProcessAction_Max)
    {
        return ;
    }
    EProcessAction eAction = static_cast<EProcessAction>(wAction);
    pUser->GetTaskPkg().OnAction(*(pUser->GetPlayer()),eAction);
}

//接收：查询玩家属性
bool CGame2CenterCommC:: OnRecv_GetUserUINTProp(
        UINT64 qwUsrID, //帐号ID
        EPlayerUINTProp eUINTPropType, //属性类型
        shared_func<SGetUserUINTPropAck>& fnAck //返回回调函数
        )
{

    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);                        
    if (!pUser)                                                                 
    {                                                                           
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;                       
        fnAck->byError = 1;
        return false;                                                                
    }                                                                           

    CPlayerPtr pPlayer= pUser->GetPlayer();
    if(NULL == pPlayer)
    {
        LOG_CRI << "pPlayer NULL";
        fnAck->byError = 2;
        return false;
    }

    switch(eUINTPropType)
    {
        case ePropTopDemonFloorID:
            {
                fnAck->dwValue = pPlayer->GetTopDemonFloorID();
            }
            break;
        case ePropPrizeDemonFloorID:
            {
                fnAck->dwValue = pPlayer->GetPrizeDemonFloorID();
            }
            break;
    }

    fnAck->byError = 0;

    return true;
}

//接收：设置玩家属性
bool CGame2CenterCommC::OnRecv_SetUserUINTProp(
        UINT64 qwUsrID, //帐号ID
        EPlayerUINTProp eUINTPropType, //属性类型
        UINT32 dwValue, //属性值
        shared_func<SSetUserUINTPropAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);                        
    if (!pUser)                                                                 
    {                                                                           
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;                       
        fnAck->byError = 1;
        return false;                                                                
    }                                                                           

    CPlayerPtr pPlayer= pUser->GetPlayer();
    if(NULL == pPlayer)
    {
        LOG_CRI << "pPlayer NULL";
        fnAck->byError = 2;
        return false;
    }

    switch(eUINTPropType)
    {
        case ePropTopDemonFloorID:
            {
                pPlayer->SetTopDemonFloorID(dwValue);
            }
            break;
        case ePropPrizeDemonFloorID:
            {
                pPlayer->SetPrizeDemonFloorID(dwValue);
            }
            break;
    }

    fnAck->byError = 0;


    return true;
}

//接收：扣除物品/钱币
bool CGame2CenterCommC::OnRecv_UserSubItem(
        UINT64 qwUsrID, //帐号ID
        NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
        const TVecUserItem& vecUserItem, //物品列表
        shared_func<SUserSubItemAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        fnAck->byError = eUpdateErrorNoUser;
        return false;
    }

    CPlayerPtr pPlayer= pUser->GetPlayer();
    if(NULL == pPlayer)
    {
        LOG_CRI << "pPlayer NULL";
        fnAck->byError = eUpdateErrorNoUser;
        return false;
    }

    for(auto itr = vecUserItem.begin(); itr != vecUserItem.end(); ++itr)
    {
        //钱币
        if(itr->dwTypeID < 100)
        {
            if(!pUser->CanSubMoney((EMoneyType)itr->dwTypeID,itr->dwCount))
            {
                fnAck->byError = eUpdateErrorMoneyCount;
                return true;
            }
        }
        else
        {
            CStore* pStore = pUser->GetStoreByType(eStorePack);
            if(!pStore)
            {
                fnAck->byError = eUpdateErrorUnKown;
                return true;
            }

            if(pStore->GetItemCount(itr->dwTypeID) < itr->dwCount)
            {
                fnAck->byError = eUpdateErrorItemCount;
                return true;
            }
        }
    }

    fnAck->byError = 0;

    for(auto itr = vecUserItem.begin(); itr != vecUserItem.end(); ++itr)
    {
        //钱币
        if(itr->dwTypeID < 100)
        {
            if(!pUser->SubMoney((EMoneyType)itr->dwTypeID,itr->dwCount,eItemTo))
            {
                fnAck->byError = eUpdateErrorMoneyCount;
                LOG_CRI << "OnRecv_UserSubItem UnKown Error";
                return true;
            }
        }
        else
        {
            CStore* pStore = pUser->GetStoreByType(eStorePack);
            if(!pStore)
            {
                fnAck->byError = eUpdateErrorUnKown;
                LOG_CRI << "OnRecv_UserSubItem UnKown Error";
                return true;
            }

            if(!pStore->DelItemByItemID((UINT16)itr->dwTypeID, (UINT16)itr->dwCount, true, eItemTo))
            {
                fnAck->byError = eUpdateErrorItemCount;
                LOG_CRI << "OnRecv_UserSubItem UnKown Error";
                return true;
            }
        }
    }

    return true;
}

//接收：添加物品/钱币
bool CGame2CenterCommC::OnRecv_UserAddItem(
        UINT64 qwUsrID, //帐号ID
        NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
        const TVecUserItem& vecUserItem, //物品列表
        shared_func<SUserAddItemAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        fnAck->byError = eUpdateErrorNoUser;
        return false;
    }

    CPlayerPtr pPlayer= pUser->GetPlayer();
    if(NULL == pPlayer)
    {
        LOG_CRI << "pPlayer NULL";
        fnAck->byError = eUpdateErrorNoUser;
        return false;
    }

    TVecItemGenInfo oVecItemGenInfo;
    TVecResource vecRes;
    for(auto itr = vecUserItem.begin(); itr != vecUserItem.end(); ++itr)
    {
        //钱币
        SResource res;
        if(itr->dwTypeID < 100)
        {

            SResource res; 
            res._eRes = (EMoneyType)itr->dwTypeID;
            res._dwValue = itr->dwCount;
            vecRes.push_back(res);
            if(!pUser->CanAddMoney((EMoneyType)itr->dwTypeID,itr->dwCount))
            {
                fnAck->byError = eUpdateErrorMoneyCount;
                return true;
            }
        }
        else
        {
            SItemGenInfo oItemGenInfo;
            oItemGenInfo.wItemID  = itr->dwTypeID;
            oItemGenInfo.dwCount  = itr->dwCount;
            oItemGenInfo.eBindType = eBindGet;
            oVecItemGenInfo.push_back(oItemGenInfo);
        }
    }

    fnAck->byError = 0;

    CStore* pStore = pUser->GetStoreByType(eStorePack);
    if(!pStore)
    {
        fnAck->byError = eUpdateErrorUnKown;
        return true;
    }
    if (!pStore->CanAddItem(oVecItemGenInfo, true))
    {
        fnAck->byError = eUpdateErrorUnKown;
        return true;
    }
    if(eItemFrom != NLogDataDefine::ItemFrom_ArenaBattle && eItemFrom != NLogDataDefine::ItemFrom_LadderBattle)
    {

        pStore->AddItem(oVecItemGenInfo, eItemFrom);
        CStore::AddResource(*pUser,vecRes,eItemFrom);
    }
    else
    {
        pStore->AddItem(oVecItemGenInfo, eItemFrom,true,false);
        pUser->GetPlayer()->PendDrop(oVecItemGenInfo,vecRes,PendBattle);

    }
    return true;
}

//接收：气泡事件通知
void CGame2CenterCommC::OnRecv_BubbleNotify(
        UINT64 qwUsrID, //帐号ID
        NProtoCommon::EDataChange eType, //修改类型
        UINT16 wMsgID, //通知类型
        const TVecINT64& vecParam, //整型变量
        const TVecString& vecString //字符串型变量
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);                        
    if (!pUser)                                                                 
    {                                                                           
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;                       
        return;                                                                
    }                                                                           
    CBubbleOwnerPtr pBubbleOwner = pUser->GetBubbleOwner();
    if (!pBubbleOwner)
        return;
    switch(eType)
    {
        case eOpAdd:
            pBubbleOwner->CreateBubble(wMsgID, vecParam, vecString);
            break;
        default:
            break;
    }
}

//接收：玩家帮派等级更新
void CGame2CenterCommC::OnRecv_GuildLevelUpdated(
        UINT64 qwRoleID, //玩家ID
        UINT16 wLevel //帮派等级
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (!pUser)
        return;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    pPlayer->SetGuildLevel(wLevel);
}

//接收：玩家帮派名有更新
void CGame2CenterCommC::OnRecv_GuildNameUpdated(
        UINT64 qwRoleID, //玩家ID
        const std::string& strGuildName //帮派名称
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (!pUser)
        return;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    pPlayer->SetGuildName(strGuildName);
}

//接收：帮派技能属性更新
void CGame2CenterCommC::OnRecv_GuildTechUpdate(
        UINT64 qwRoleID, //玩家唯一ID
        const NProtoCommon::TVecFtAttrMod& vecFtAttr, //玩家的帮派技能属性
        const NGuildProt::TVecGuildTechInfo& vecGuildTech //玩家的帮派技能信息
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (!pUser)
        return;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    VECATTR_DEC(vecAttr);
    size_t size = vecFtAttr.size();
    for (size_t i = 0; i < size; ++i)
    {
        if ((UINT32)vecFtAttr[i]._eAttr >= vecAttr.size())
            continue;
        vecAttr[vecFtAttr[i]._eAttr] += vecFtAttr[i]._fValue;
    }
    CFighterManagerPtr& pFighterManager = pPlayer->GetFighterManager();
    pFighterManager->SetDirty(eAttrGpGuildTech, vecAttr);

    pPlayer->SetGuildTechInfo(vecGuildTech);
}
//接收：重新加载表格
void CGame2CenterCommC::OnRecv_ReloadTable(
        const TVecString& vecTableName //表格名字
        )
{
}

//接收：玩家九疑鼎属性更新
void CGame2CenterCommC::OnRecv_TripodAttrUpdate(
        UINT64 qwRoleID, //玩家唯一ID
        const TVecUINT32& vecValue //九疑鼎ID、等级
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (!pUser)
        return;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    VECATTR_DEC(vecAttr);
    size_t size = vecValue.size();
    for (size_t i = 0; i < size; ++i)
    {
        //高8为ID 低8位level
        CTripodMgr::AddTripodAttr(vecValue[i]>>8, UINT8(vecValue[i]), 1, vecAttr);
    }
    CFighterManagerPtr& pFighterManager = pPlayer->GetFighterManager();
    pFighterManager->SetDirty(eAttrGpTripod, vecAttr);
}

//接收：完成GetCond条件
bool CGame2CenterCommC::OnRecv_ProcessCond(
        UINT64 qwUsrID, //玩家ID
        UINT16 wCondID, //条件ID
        NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
        shared_func<SProcessCondAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        fnAck->byError = 1;
        return false;
    }
    if (!CGetCondMgr::Instance().TestCond(*pUser, wCondID))
    {
        fnAck->byError = 1;
        return false;
    }
    if (!CGetCondMgr::Instance().ProcessCond(*pUser, wCondID, eItemTo))
    {
        fnAck->byError = 1;
        return false;
    }
    fnAck->byError = 0;
    return true;
}

//接收：玩家升级九疑鼎
bool CGame2CenterCommC::OnRecv_UpgradeTripod(
        UINT64 qwUsrID, //玩家ID
        UINT8 byTripodID, //九疑鼎ID
        UINT8 byLevel, //九疑鼎当前等级
        UINT32 dwExp, //九疑鼎当前经验值
        UINT8 byOneKey, //是否一键
        shared_func<SUpgradeTripodAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        fnAck->byError = 1;
        return false;
    }
    bool bRes = CTripodMgr::UpgradeTripod(byTripodID, byLevel, 1, dwExp, byOneKey > 0, pUser);
    fnAck->byError = bRes ? 0 : 1;
    fnAck->byLevel = byLevel;
    fnAck->dwExp   = dwExp;
    return true;
}

//接收：加速九疑鼎炼丹(道具入鼎)
bool CGame2CenterCommC::OnRecv_SpeedTripod(
        UINT64 qwUsrID, //玩家ID
        UINT32 dwCurSoul, //当前九疑鼎的火种元气值
        UINT32 dwMaxSoul, //当前九疑鼎的火种最大元气值(配置)
        const NItemProt::TVecItemCount& vecItems, //入鼎道具列表
        shared_func<SSpeedTripodAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        fnAck->byError = 1;
        return false;
    }
    CStore* pStore = pUser->GetStoreByType(eStorePack);
    if(!pStore)
    {
        fnAck->byError = 1;
        return true;
    }

    UINT32 dwTmpSoul = dwCurSoul;
    TVecItemCount vecItemTmp;
    map<UINT64, UINT32> mapEnergy;
    for(auto itr = vecItems.begin(); itr != vecItems.end(); ++itr)
    {
        if (!itr->wCount)
            continue;
        if (pStore->GetItemCount(itr->wItemID) < itr->wCount)
            continue;
        SItemInfo* pItemInfo = CItemMgr::GetItemConfig(itr->wItemID);
        if (!pItemInfo || !pItemInfo->oItemCfg._Energy)
            continue;
        mapEnergy.insert(std::make_pair(itr->wItemID, pItemInfo->oItemCfg._Energy));
        bool bDelAll = true;
        for (UINT32 j = 0; j < itr->wCount; ++ j)
        {
            if (dwTmpSoul >= dwMaxSoul)
            {
                if (j > 0)
                {
                    SItemCount oItem(itr->wItemID, j);
                    vecItemTmp.push_back(oItem);
                    bDelAll = false;
                }
                break;
            }
            dwTmpSoul += pItemInfo->oItemCfg._Energy;
        }
        if (bDelAll)
            vecItemTmp.push_back(*itr);
    }
    if (vecItemTmp.empty())
    {
        fnAck->byError = 1;
        return true;
    }

    TVecINT32 vecParam;
    fnAck->dwSoul = 0;
    fnAck->byError = 0;
    for(auto itr = vecItemTmp.begin(); itr != vecItemTmp.end(); ++itr)
    {
        if(pStore->DelItemByItemID(itr->wItemID, itr->wCount, true, NLogDataDefine::ItemTo_TripodSpeed))
        {
            auto it = mapEnergy.find(itr->wItemID);
            if (it != mapEnergy.end())
            {
                if (fnAck->dwSoul+dwCurSoul >= dwMaxSoul)
                    break;
                fnAck->dwSoul += it->second * itr->wCount;
            }
            vecParam.push_back(itr->wItemID);
            vecParam.push_back(itr->wCount);
        }
    }
    if (pUser->GetPlayer())
        pUser->GetPlayer()->OnEvent(eEventType_StoveComingIn, vecParam);
    return true;
}

//接收：判断玩家是否拥有散仙
bool CGame2CenterCommC::OnRecv_CheckHasFighter(
        UINT64 qwUsrID, //玩家ID
        UINT16 wFighterID, //散仙ID
        shared_func<SCheckHasFighterAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        fnAck->byError = 1;
        return false;
    }
    CPlayerPtr pPlayer= pUser->GetPlayer();
    if(NULL == pPlayer)
    {
        LOG_CRI << "pPlayer NULL";
        fnAck->byError = 1;
        return false;
    }
    CFighterPtr pFighter = pPlayer->GetFighterByID(wFighterID);
    if (pFighter)
    {
        fnAck->byError = 0;
        fnAck->byColor = pFighter->GetColor();
    }
    else
    {
        fnAck->byError = 1;
        fnAck->byColor = 0;
    }
    return true;
}

//接收：获取战斗力
bool CGame2CenterCommC::OnRecv_GetBattlePoint(
        UINT64 qwUsrID, //玩家ID
        shared_func<SGetBattlePointAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        fnAck->byError = 1;
        return false;
    }

    CPlayerPtr pPlayer= pUser->GetPlayer();
    if(NULL == pPlayer)
    {
        LOG_CRI << "pPlayer NULL";
        fnAck->byError = 2;
        return false;
    }
    fnAck->dwBattlePoint = pPlayer->GetBattlePoint();
    return true;
}

//接收：玩家发事件中心消息
void CGame2CenterCommC::OnRecv_OnPlayerEvent(
        UINT64 qwUsrID, //玩家ID
        NEventCenter::EventType eEventType, //事件类型
        const TVecINT32& vecParam, //事件参数
        const std::string& strParam, //事件参数
        bool bLog //事件参数

        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
    {
        LOG_CRI << "Can't find User! UsrID: " << qwUsrID;
        return;
    }

    CPlayerPtr pPlayer= pUser->GetPlayer();
    if(NULL == pPlayer)
    {
        LOG_CRI << "pPlayer NULL";
        return;
    }

    CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
    if(pEventMgr)
    {
        pEventMgr->OnEvent(eEventType,vecParam,strParam,bLog);
    }
}

//接收：增加或者设置玩家GameVar数值
void CGame2CenterCommC::OnRecv_AddORSetGameVar(
        UINT64 qwUsrID, //玩家ID
        UINT8 byType, //0增加 >0设置
        const TVecUINT16& vecVars, //varID列表
        const TVecUINT64& vecValues //var数值列表(必须与vecVars对应)
        )
{
    if (!qwUsrID || vecVars.empty() || vecValues.empty())
        return;
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (pUser)
    {
        for (size_t i = 0; i < vecVars.size() && i < vecValues.size(); ++ i)
        {
            if (byType > 0)
                pUser->GetVars().SetVar(vecVars[i], vecValues[i]);
            else
                pUser->GetVars().AddVar(vecVars[i], vecValues[i]);
        }
        return;
    }
    //XXX 玩家不在线
    CUserMgr::LoadUser(qwUsrID,[byType,vecVars,vecValues](CUserPtr pUser){
            if (!pUser)
            return;
            for (size_t i = 0; i < vecVars.size() && i < vecValues.size(); ++ i)
            {
            if (byType > 0)
            pUser->GetVars().SetVar(vecVars[i], vecValues[i]);
            else
            pUser->GetVars().AddVar(vecVars[i], vecValues[i]);
            }
            });
}

//接收：清除玩家GameVar
void CGame2CenterCommC::OnRecv_DeleteGameVar(
        UINT64 qwUsrID, //玩家ID
        const TVecUINT16& vecVars //varID列表
        )
{
    if (!qwUsrID || vecVars.empty())
        return;
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (pUser)
    {
        for (size_t i = 0; i < vecVars.size(); ++ i)
            pUser->GetVars().DelVar(vecVars[i]);
        return;
    }
    //XXX 玩家不在线
    CUserMgr::LoadUser(qwUsrID,[vecVars](CUserPtr pUser){
            if (!pUser)
            return;
            for (size_t i = 0; i < vecVars.size(); ++ i)
            pUser->GetVars().DelVar(vecVars[i]);
            });
}

//接收：清除商城限购活动
void CGame2CenterCommC::OnRecv_ClearMallDiscount(
    UINT8 byPos //限购道具栏位
)
{
    CMall::Instance().ClearMallDiscount(byPos);
    CMall::Instance().UpdateDiscountToDB();
}

//接收：增加商城限购活动
void CGame2CenterCommC::OnRecv_AddMallDiscount(
        const NMallProt::SDiscount& oDiscount//限购道具列表
        )
{
    CMall::Instance().ClearMallDiscount(oDiscount.byPos);
    CMall::Instance().AddDiscountFromBS(oDiscount);
    CMall::Instance().UpdateDiscountToDB();
    CMall::Instance().SendMallDiscountInfo(oDiscount);
}

//接收：扣除玩家钱币/物品
bool CGame2CenterCommC::OnRecv_SubPlayerMoney(
        const TVecUINT64& vecUserID, //玩家ID
        const TVecUserItem& vecUserItem, //物品列表
        shared_func<SSubPlayerMoneyAck>& fnAck //返回回调函数
        )
{
    bool mark = false;
    for (size_t i=0; i<vecUserID.size(); ++i)
    {
        const UINT64 qwUserID = vecUserID[i];
        if (SubPlayerMoney(qwUserID, vecUserItem))
            mark = true;
    }

    // 对于同时操作多个玩家，只要有一个成功，则返回true
    if (mark)
        return true;
    else
        return false;
}

//接收：扣除玩家钱币
bool CGame2CenterCommC::SubPlayerMoney(const UINT64 qwUserID, const TVecUserItem& vecUserItem)
{
    CUserMgr::LoadUser(qwUserID, 
            [vecUserItem](CUserPtr pUser)
            {
            if (!pUser)
            return false;

            for(auto itr = vecUserItem.begin(); itr != vecUserItem.end(); ++itr)
            {
            if(itr->dwTypeID >= 100)
            return false;

            if(!pUser->CanSubMoney((EMoneyType)itr->dwTypeID,itr->dwCount))
            return false;
            }

            for(auto itr = vecUserItem.begin(); itr != vecUserItem.end(); ++itr)
            {
            if(!pUser->SubMoney((EMoneyType)itr->dwTypeID,itr->dwCount,NLogDataDefine::ItemTo_PHP))
            continue;
            }
            return true;
            });
    return true;
}

//接收：设置玩家等级
bool CGame2CenterCommC::OnRecv_SetPlayerLevel(
        UINT64 qwUserID, //玩家ID
        UINT16 wLevel, //玩家等级
        shared_func<SSetPlayerLevelAck>& fnAck //返回回调函数
        )
{
    CUserMgr::LoadUser(qwUserID, [wLevel, fnAck](CUserPtr pUser) 
            {
            if (!pUser)
            {
            fnAck(false);
            return;
            }

            CPlayerPtr pPlayer= pUser->GetPlayer();
            if(!pPlayer)
            {
            fnAck(false);
            return;
            }

            pPlayer->PHPSetLevel(wLevel);
            fnAck(true);
            return;
            });
    return true;
}

//接收：设置玩家VIP等级
bool CGame2CenterCommC::OnRecv_SetPlayerVIPLevel(
        UINT64 qwUserID, //玩家ID
        NPHPProt::EOptType eOptType, //后台台操作类型(eOptSetPlayerVIPLevel/eOptAddGrowthValue)
        UINT32 dwLevelOrGrowthValue, //等级or成长值
        shared_func<SSetPlayerVIPLevelAck>& fnAck //返回回调函数
        )
{
    if (0 == dwLevelOrGrowthValue)
        return false;

    if (NPHPProt::eOptSetPlayerVIPLevel!=eOptType && NPHPProt::eOptAddGrowthValue!=eOptType)
        return false;

    CUserMgr::LoadUser(qwUserID, 
            [eOptType, dwLevelOrGrowthValue, fnAck](CUserPtr pUser) 
            {
            if (!pUser)
            {
            fnAck(false);
            return false;
            }

            if (NPHPProt::eOptSetPlayerVIPLevel == eOptType)
                pUser->PHPSetVIPLevel(dwLevelOrGrowthValue);
            else
            {
                pUser->AddTotalRecharge(dwLevelOrGrowthValue, false);
                //pUser->AddVIPGrowthValue(dwLevelOrGrowthValue);
            }

            fnAck(true);
            return true;
            });
    return true;
}

//接收：设置日常任务
bool CGame2CenterCommC::OnRecv_SetDayTask(
        const TVecUINT64& vecUserID, //UserID
        NPHPProt::EPHPTaskType eTaskType, //日常任务类型
        shared_func<SSetDayTaskAck>& fnAck //返回回调函数
        )
{
    if (NPHPProt::ePHPShiMenTask!=eTaskType && NPHPProt::ePHPYaMenTask!=eTaskType)
        return false;

    bool mark = false;
    for (size_t i=0; i<vecUserID.size(); ++i)
    {
        const UINT64 qwUserID = vecUserID[i];
        if (SetDayTask(qwUserID, eTaskType))
            mark = true;
    }

    // 对于同时操作多个玩家，只要有一个成功，则返回true
    if (mark)
        return true;
    else
        return false;
}

bool CGame2CenterCommC::SetDayTask(const UINT64 qwUserID, NPHPProt::EPHPTaskType eTaskType)
{
    CUserMgr::LoadUser(qwUserID, 
            [eTaskType](CUserPtr pUser)
            {
            if (!pUser)
            return false;

            CPlayerPtr pPlayer= pUser->GetPlayer();
            if(!pPlayer)
            return false;

            if (NPHPProt::ePHPShiMenTask == eTaskType)
            pPlayer->GetGroupPkg().GMaddTimes(SParamConfig::byShiMenTaskMax);
            else
            pPlayer->GetYaMenPkg().GMaddTimes(SParamConfig::byYaMenTaskMax);
            return true;
            });
    return true;
}

//接收：获取玩家信息
bool CGame2CenterCommC::OnRecv_GetPlayerInfo(
        UINT64 qwUserID, //玩家ID
        shared_func<SGetPlayerInfoAck>& fnAck //返回回调函数
        )
{
    CUserMgr::LoadUser(qwUserID, [this, qwUserID, fnAck](CUserPtr pUser)
            {
            if (!pUser)
            {
            fnAck(false);
            return;
            }

            NPHPProt::SPlayerInfo sPlayerInfo;
            if (!this->GetPlayerInfo(qwUserID, sPlayerInfo))
            {
            fnAck(false);
            return;
            }

            fnAck->sPlayerInfo = sPlayerInfo;
            fnAck(true);
            return;
            });
    return true;
}

bool CGame2CenterCommC::GetPlayerInfo(
        UINT64 qwUserID,
        NPHPProt::SPlayerInfo& sPlayerInfo //玩家信息 
        )
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if (NULL == pUser)
        return false;

    CPlayerPtr pPlayer = pUser->GetPlayer();
    if (NULL == pPlayer)
        return false;

    CHeroFighterPtr pMainFighter = pPlayer->GetMainFighter();
    if (NULL == pMainFighter)
        return false;

    //基本信息
    sPlayerInfo.qwUserID = qwUserID;
    sPlayerInfo.strName = pPlayer->GetName();
    sPlayerInfo.wLevel = pPlayer->GetLevel();
    sPlayerInfo.byJob = pMainFighter->GetJob();
    sPlayerInfo.bySex = pPlayer->GetSex();
    sPlayerInfo.dwSilver = pUser->GetMoney(EMONEY_SILVER);
    sPlayerInfo.dwGold = pUser->GetMoney(EMONEY_GOLD);
    sPlayerInfo.dwCoupon = pUser->GetMoney(EMONEY_COUPON);
    sPlayerInfo.byVIPLevel = pUser->GetVIPLevel();
    sPlayerInfo.dwPrestige = pUser->GetMoney(EMONEY_PRESTIGE);
    sPlayerInfo.dwHonor = pUser->GetMoney(EMONEY_HONOR);
    sPlayerInfo.wShiMenTask = pPlayer->GetGroupPkg().GetCanAccepTask();
    sPlayerInfo.wYaMenTaTask = pPlayer->GetYaMenPkg().GetCanAccepTask();
    sPlayerInfo.byForbExpire = pPlayer->GetBaseInfo().dwForbExpireTime;
    sPlayerInfo.byLockExpire = pPlayer->GetBaseInfo().dwLockExpireTime;
    sPlayerInfo.dwCreateTime = pPlayer->GetBaseInfo().dwCreateTime;

    return true;
}

//接收：获取玩家背包信息
bool CGame2CenterCommC::OnRecv_GetPlayerBagInfo(
        UINT64 qwUserID, //玩家ID
        shared_func<SGetPlayerBagInfoAck>& fnAck //返回回调函数
        )
{
    CUserMgr::LoadUser(qwUserID, [this, qwUserID, fnAck](CUserPtr pUser)
            {
            if (!pUser)
            {
            fnAck(false);
            return;
            }

            CStore* pStorePack = pUser->GetStoreByType(eStorePack);
            if (!pStorePack)
            {
            fnAck(false);
            return;
            }

            CStore* pStoreDepot = pUser->GetStoreByType(eStoreDepot);
            if (!pStoreDepot)
            {
            fnAck(false);
            return;
            }

            vector<CItemPtr> vecItemPack;
            pStorePack->GetAllItemList(vecItemPack);
            for(auto it=vecItemPack.begin(); it!=vecItemPack.end(); ++it)
            {
                NPHPProt::SPlayerBagInfo sPlayerBagInfo;
                sPlayerBagInfo.qwInstID = (*it)->GetInstID();
                sPlayerBagInfo.wItemID = (*it)->GetItemID();
                sPlayerBagInfo.byType = pStorePack->GetStoreType();
                sPlayerBagInfo.wCount = (*it)->GetCount();
                sPlayerBagInfo.byBind = (*it)->GetBindType();

                fnAck->vecPlayerBagInfo.push_back(sPlayerBagInfo);
            }

            vector<CItemPtr> vecItemDepot;
            pStoreDepot->GetAllItemList(vecItemDepot);
            for(auto it=vecItemDepot.begin(); it!=vecItemDepot.end(); ++it)
            {
                NPHPProt::SPlayerBagInfo sPlayerBagInfo;
                sPlayerBagInfo.qwInstID = (*it)->GetInstID();
                sPlayerBagInfo.wItemID = (*it)->GetItemID();
                sPlayerBagInfo.byType = pStoreDepot->GetStoreType();
                sPlayerBagInfo.wCount = (*it)->GetCount();
                sPlayerBagInfo.byBind = (*it)->GetBindType();

                fnAck->vecPlayerBagInfo.push_back(sPlayerBagInfo);
            }

            fnAck(true);
            return;
            });
    return true;
}

//接收：删除玩家物品
bool CGame2CenterCommC::OnRecv_DelPlayerItem(
        UINT64 qwUserID, //用户ID
        UINT8 byType, //1；背包，2：仓库
        UINT64 qwInstID, //物品唯一ID
        UINT16 wCount, //堆叠数
        shared_func<SDelPlayerItemAck>& fnAck //返回回调函数
        )
{
    if (0 == qwUserID)
        return false;

    if (1!=byType && 2!=byType)
        return false;

    if (0==qwInstID || 0==wCount)
        return false;

    CUserMgr::LoadUser(qwUserID, 
            [qwUserID, byType, qwInstID, wCount, fnAck](CUserPtr pUser)
            {
            if (!pUser)
            {
            fnAck(false);
            return false;
            }

            CStore* pStore = NULL;
            if (1 == byType)
            pStore = pUser->GetStoreByType(eStorePack);
            else
            pStore = pUser->GetStoreByType(eStoreDepot);

            if (!pStore)
            {
            fnAck(false);
            return false;
            }

            if (!pStore->DelItemByInstID(qwInstID, wCount, true, true, NLogDataDefine::ItemTo_PHP))
            {
                fnAck(false);
                return false;
            }

            fnAck(true);
            return true;
            });
    return true;
}
//接收：给玩家用掉落包发系统邮件
void CGame2CenterCommC::OnRecv_SendSysMailByLootId(
        UINT64 qwUserID, //用户ID
        UINT16 wTitle, //邮件标题
        UINT16 wText, //邮件正文
        const TVecString& vecParam, //邮件参数
        UINT32 dwLootId, //掉落包
        UINT32 dwRate //倍率
        )
{
    if(dwRate < 10000)
    {
        dwRate = 10000;
    }
    TVecResource vecRes;
    std::vector<SItemGenInfo> vecItems;
    LOOT.Roll(dwLootId, vecItems,vecRes);
    for(auto it = vecItems.begin(); it != vecItems.end();it++)
    {
        SItemGenInfo &sItem = *(it);
        sItem.dwCount = sItem.dwCount * float(dwRate)/10000;
    }
    for(auto it = vecRes.begin(); it != vecRes.end();it++)
    {
        SItemGenInfo sItem;
        SResource& sRes = *it;
        sItem.wItemID =sRes._eRes;
        sItem.dwCount = sRes._dwValue * float(dwRate)/10000;
        vecItems.push_back(sItem);
    }
    
    NMailProt::SysMailSendTxt stBody;
    stBody.dwstrMsgID = wText;
    stBody.vecParam = vecParam;
    TVecUINT64 vecRole;
    vecRole.push_back(qwUserID);
    GameServerSysMail::SendSysMail(0,wTitle,stBody,vecRole,&vecItems);



}

//接收：任务集市查询
bool CGame2CenterCommC::OnRecv_GetTaskStateForPlatfrom(
		UINT64 qwUserID, //玩家ID
		UINT32 dwTaskID, //任务ID
		UINT8 byStep, //步骤ID
		UINT8 byOpt, //操作类型
		shared_func<SGetTaskStateForPlatfromAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(pUser)
    {
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if(!pPlayer)
        {
            LOG_INF <<"pPlayer null.";
            return false;
        }
        fnAck->eRet = TaskMarketMgr.CheckTask(*pPlayer,dwTaskID,byStep,byOpt);
    }
    else 
    {
        CUserMgr::LoadUser(qwUserID, 
                [qwUserID, dwTaskID, byStep, byOpt, fnAck](CUserPtr pUser)
                {
                if (!pUser)
                {
                fnAck(false);
                return ;
                }
                CPlayerPtr pPlayer = pUser->GetPlayer();
                if(!pPlayer)
                {
                    LOG_INF <<"pPlayer null.";
                    return ;
                }
                fnAck->eRet = TaskMarketMgr.CheckTask(*pPlayer,dwTaskID,byStep,byOpt);
                });
    }
    return true;
}

//接收：同步微信微博人数
void CGame2CenterCommC::OnRecv_SynWeiweiPersonNum(
		UINT64 qwUserID, //玩家ID
		UINT8 byType, //类型
		UINT32 dwCount //人数
	)
{
    
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(pUser)
    {
        if(byType == 0)
            pUser->GetVars().SetVar(ePlayerWeiboNum, dwCount);
        if(byType == 1)
            pUser->GetVars().SetVar(ePlayerWeixinNum, dwCount);
    }
    else 
    {
        CUserMgr::LoadUser(qwUserID, 
                [byType,dwCount](CUserPtr pUser)
                {
                if (!pUser)
                {
                    return ;
                }
                if(byType == 0)
                    pUser->GetVars().SetVar(ePlayerWeiboNum, dwCount);
                if(byType == 1)
                    pUser->GetVars().SetVar(ePlayerWeixinNum, dwCount);
                });
    }

}

//接收：检测CDK
void CGame2CenterCommC::OnRecv_CheckCDK(
		UINT64 qwUserID, //玩家ID
		const std::string& strCDK //CDK码
	) 
{
     
    CShushanweiweiPtr pShushanweiwei = NULL;
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(pUser)
    {
        CPlayerPtr pPlayer = pUser->GetPlayer();
        if(pPlayer)
        {
            pShushanweiwei = pPlayer->GetShushanweiwei();
        }
        if(pShushanweiwei)
        {
            pShushanweiwei->CheckCDK(strCDK);
        }
    }
}
//接收：QQAlarm安装
void CGame2CenterCommC::OnRecv_SynQQAlarm(
		UINT64 qwUserID //玩家ID
	)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(pUser)
    {
        pUser->FixQQAlarmSuc();
    }
    else
    {
        //XXX 玩家不在线
        CUserMgr::LoadUser(qwUserID,[qwUserID](CUserPtr pUser){
            if (!pUser)
            return;
                pUser->FixQQAlarmSuc();
            });
    }
}
//接收：运营修改宝箱信息
void CGame2CenterCommC::OnRecv_ModifyChest(
		const NPHPProt::SChestInfo& sChestInfo //信息
	)
{
    LOG_INF<<"Recv ModifyChestInfo.";
    g_GodChest.ModifyParam(sChestInfo);
}

//接收：Center2Game活动时间同步
void CGame2CenterCommC::OnRecv_SyncActivityTime(
		const NProtoCommon::SActivityTime& sActTime //信息
	)
{

}

//接收：请求累计登入天数
bool CGame2CenterCommC::OnRecv_GetLoginDays(
		UINT64 qwUserID, //玩家ID
		shared_func<SGetLoginDaysAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    CPlayerPtr pPlayer = NULL;
    if(!pUser || !(pPlayer = pUser->GetPlayer(),pPlayer))
    {
        //XXX 玩家不在线
        CUserMgr::LoadUser(qwUserID,[fnAck](CUserPtr pUser){
            if (!pUser)
                return;
            CPlayerPtr pPlayer = pUser->GetPlayer();
            if(!pPlayer)
                return;
            CLoginPkgMgrPtr pLoginMgr = pPlayer->GetLoginPkgMgr();
            if(pLoginMgr)
                fnAck->dwDays = pLoginMgr->GetLoginDays();
            });
    }else 
    {
        CLoginPkgMgrPtr pLoginMgr = pPlayer->GetLoginPkgMgr();
        if(pLoginMgr)
            fnAck->dwDays = pLoginMgr->GetLoginDays();
    }
    return true;
}

//接收：同步活动状态
void CGame2CenterCommC::OnRecv_SyncActState(
		const SActivityState& oInfo, //数据
        bool bNotify
	)
{
    LOG_INF<<" Center to GameServer IconOpen. ID="<<oInfo.dwActID;
    CUserMgr::AddIcon(oInfo.dwActID,oInfo.bOpen,bNotify);
}
//接收：添加Title
void CGame2CenterCommC::OnRecv_SyncTitle(
		UINT64 qwUserID, //玩家ID
		UINT16 wTitleID //添加Title
	)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    CPlayerPtr pPlayer = NULL;
    if(!pUser || !(pPlayer = pUser->GetPlayer(),pPlayer))
    {
        //XXX 玩家不在线
        CUserMgr::LoadUser(qwUserID,[wTitleID](CUserPtr pUser){
            if (!pUser)
                return;
            CPlayerPtr pPlayer = pUser->GetPlayer();
            if(!pPlayer)
                return;
            CTitlePkg& rTitlePkg =  pPlayer->GetTitlePkg(); 
            rTitlePkg.AddTitle(wTitleID);
            LOG_INF<<"roleID:"<<pPlayer->GetRoleID()<<" AddTitle TitleID: "<<wTitleID;
            });
    }else 
    {
        CTitlePkg& rTitlePkg =  pPlayer->GetTitlePkg(); 
        rTitlePkg.AddTitle(wTitleID);
        LOG_INF<<"roleID:"<<pPlayer->GetRoleID()<<" AddTitle TitleID: "<<wTitleID;
    }
}

void CGame2CenterCommC::TimerCheck()
{
    if(Config._bIsCrossServer)
    {
        _bCenterInited = true;
        _bTimerClosed = true;
        if(!NetInterface::CloseTimer(CTimerMgr::Instance().GetInitTimerForCenter()))
            LOG_CRI << "CloseTimer fails!";
    }
    if(!_bCenterInited)
        Send_GetCenterState([this](UINT8 byRet_ //0为成功，1为失败，2为超时
                    )
                {
                if(byRet_ == 0)
                {
                if(!_bCenterInited)
                {
                _bCenterInited = true;
                Config.OnCenterInited();
                }

                if(!_bTimerClosed)
                {
                _bTimerClosed = true;
                if(!NetInterface::CloseTimer(CTimerMgr::Instance().GetInitTimerForCenter()))
                LOG_CRI << "CloseTimer fails!";
                }
                }
                });
}
//接收：扣除礼卷钻石
bool CGame2CenterCommC::OnRecv_SubGoldOrCoupon(
	UINT64 qwUsrID, //帐号ID
	NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
	UINT32 dwCount, //扣款数量
	shared_func<SSubGoldOrCouponAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(NULL == pUser)
    {
        fnAck->byError = 1;
        return true;
    }

    if(!pUser->SubGoldOrCoupon(dwCount,eCouponCoin,eItemTo))
    {
        fnAck->byError = 2;
        return true;
    }

    fnAck->byError = 0;

    return true;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

