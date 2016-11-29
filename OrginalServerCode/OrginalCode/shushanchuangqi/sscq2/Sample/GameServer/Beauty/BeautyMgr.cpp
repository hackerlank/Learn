#include "stdafx.h"
#include "BeautyMgr.h"
#include "Player.h"
#include "User.h"
#include "Game2DBCommC.h"
#include "Tokenizer.h"
#include "GetCondMgr.h"
#include "BeautyS.h"
#include "AutoStoreMgr.h"
#include "Item.h"
#include "ItemMgr.h"
#include "SysMsgDefine.h"
//#include "Loot.h"
#include "Random.h"
#include "SkillAttr.h"
#include "FighterManager.h"
#include "FighterMgr.h"
#include "Battle.h"
#include "Map.h"
#include "BeautyLogGS.h"
#include "Game2CenterCommC.h"
#include "GameServerSysMail.h"
#include "HeroFighter.h"
#include "Game2CenterTeamC.h"

extern CGame2CenterCommC g_Game2CenterCommC;
extern CGame2DBCommC g_Game2DBCommC;
TMapBeautyCFGExPtr CBeautyMgr::_mapBeautyCFGExPtr;
TMapBeautyLevelCFGExPtr CBeautyMgr::_mapBeautyLevelCFGExPtr;
TMapBeautyLotteryCFGExPtr CBeautyMgr::_mapBeautyLotteryCFGExPtr;
TDMapRareLotteryLoot      CBeautyMgr::_dmapRareLotteryLoot;
TSetRareItem              CBeautyMgr::_setRareItem;

void GetItemTypeFromString(TVecUINT16& _vecItemType, const string strItem)
{
    Tokenizer tk(strItem, "|"); // XXX: itemType|itemType
    for (size_t i = 0; i < tk.size(); ++i)
    {
        UINT16 wItemType = atoi(tk[i].c_str());
        if (wItemType)
        {
            _vecItemType.push_back(wItemType);
        }
    }
}

void GetDropIDFromString(TVecUINT32& vecDropID, const string strItem)
{
    Tokenizer tk(strItem, "|"); // XXX: itemType|itemType
    for (size_t i = 0; i < tk.size(); ++i)
    {
        UINT32 dwDropID = atoi(tk[i].c_str());
        if (dwDropID)
        {
            vecDropID.push_back(dwDropID);
        }
    }
}

bool CBeautyMgr::BeautyInit()
{
    string strBeautyPath = Config._strConfigDir + "Conf/Table/Beauty.xml";
    CBeautyLoader oBeautyLoader;
    if(!oBeautyLoader.LoadData(strBeautyPath))
    {
        LOG_CRI << "CBeautyLoaderLoader fails! Path: " << strBeautyPath;
        return false;
    }

    for(size_t i  = 0; i < oBeautyLoader._vecData.size(); ++i)
    {
        SBeautyCFGExPtr pBeautyCFG(new SBeautyCFGEx);
        pBeautyCFG->CopyFrom(*oBeautyLoader._vecData[i]);
        //GetItemFromString(pBeautyCFG->vecPassPrize,pBeautyCFG->_PassPrize);
        _mapBeautyCFGExPtr[pBeautyCFG->_ID] = pBeautyCFG;
    }

    string strBeautyLevelPath = Config._strConfigDir + "Conf/Table/BeautyLevel.xml";
    CBeautyLevelLoader oBeautyLevelLoader;
    if(!oBeautyLevelLoader.LoadData(strBeautyLevelPath))
    {
        LOG_CRI << "CBeautyLevelLoaderLoader fails! Path: " << strBeautyLevelPath;
        return false;
    }

    for(size_t i  = 0; i < oBeautyLevelLoader._vecData.size(); ++i)
    {
        SBeautyLevelCFGExPtr pBeautyLevelCFG(new SBeautyLevelCFGEx);
        pBeautyLevelCFG->CopyFrom(*oBeautyLevelLoader._vecData[i]);
        GetItemTypeFromString(pBeautyLevelCFG->_vecItemType,pBeautyLevelCFG->_ItemType);
        _mapBeautyLevelCFGExPtr[pBeautyLevelCFG->_LevelID] = pBeautyLevelCFG;
    }

    string strBeautyLotteryPath = Config._strConfigDir + "Conf/Table/BeautyLottery.xml";
    CBeautyLotteryLoader oBeautyLotteryLoader;
    if(!oBeautyLotteryLoader.LoadData(strBeautyLotteryPath))
    {
        LOG_CRI << "CBeautyLotteryLoaderLoader fails! Path: " << strBeautyLotteryPath;
        return false;
    }

    for(size_t i  = 0; i < oBeautyLotteryLoader._vecData.size(); ++i)
    {
        SBeautyLotteryCFGExPtr pBeautyLotteryCFG(new SBeautyLotteryCFGEx);
        pBeautyLotteryCFG->CopyFrom(*oBeautyLotteryLoader._vecData[i]);
        //GetItemFromString(pBeautyLotteryCFG->vecPassPrize,pBeautyLotteryCFG->_PassPrize);
        //pBeautyLotteryCFG->_vecDropID.push_back(pBeautyLotteryCFG->_DropID);
        //GetDropIDFromString(pBeautyLotteryCFG->_vecDropID,pBeautyLotteryCFG->_DropID);
        _mapBeautyLotteryCFGExPtr[pBeautyLotteryCFG->_PrizeType] = pBeautyLotteryCFG;
    }


    string strBeautyRareLotteryPath = Config._strConfigDir + "Conf/Table/BeautyRareLottery.xml";
    CBeautyRareLotteryLoader oBeautyRareLotteryLoader;
    if(!oBeautyRareLotteryLoader.LoadData(strBeautyRareLotteryPath))
    {
        LOG_CRI << "CBeautyRareLotteryLoaderLoader fails! Path: " << strBeautyRareLotteryPath;
        return false;
    }

    for(size_t i  = 0; i < oBeautyRareLotteryLoader._vecData.size(); ++i)
    {
        SBeautyRareLotteryCFGExPtr pBeautyRareLotteryCFG(new SBeautyRareLotteryCFGEx);
        pBeautyRareLotteryCFG->CopyFrom(*oBeautyRareLotteryLoader._vecData[i]);
        pBeautyRareLotteryCFG->oItemGenInfo.wItemID = pBeautyRareLotteryCFG->_ItemID;
        pBeautyRareLotteryCFG->oItemGenInfo.dwCount = pBeautyRareLotteryCFG->_ItemCount;
        _dmapRareLotteryLoot[pBeautyRareLotteryCFG->_Loots].push_back(pBeautyRareLotteryCFG);
        _setRareItem.insert(pBeautyRareLotteryCFG->_ItemID);
    }

    return true;
}

CBeautyMgr::CBeautyMgr(CPlayer& rPlayer):
    _rPlayer(rPlayer)
{
    _wBeautyID    = 0;
    _wBeautyLevel= 0;
    _bInitLotter = false;
}

bool CBeautyMgr::LoadFromDB(const RoleDataInfo& rRoleDataInfo)
{
    UINT16 wBeautyFightBeautyID = GetFightBeautyID();

    for(size_t i=0;i < rRoleDataInfo.vecBeauty.size(); i++)
    {
        SBeautyPtr pBeauty(new SBeauty);
        *pBeauty = rRoleDataInfo.vecBeauty[i];
        if(wBeautyFightBeautyID == pBeauty->wBeautyID)
        {
            _wBeautyID = wBeautyFightBeautyID;
            _wBeautyLevel = pBeauty->wBeautyLevel;
            pBeauty->bFight = true;
        }
        _mapBeautyPtr.insert(make_pair(pBeauty->wBeautyID,pBeauty));
    }

    ReBuildAttr();

    return true;
}

void CBeautyMgr::Update2DB(const SBeauty& rInfo, EDataChange eDataChange/* = eOpUpdate*/)
{
    string strData;
    COutArchive iar(strData);
    iar << rInfo;

    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(),eTypeBeauty, eDataChange, strData);
}

//接收：获取美女信息
EBeautyRet CBeautyMgr::OnGetBeatyInfo(shared_func<CBeautySvr::SGetBeatyInfoAck>& fnAck)
{
    for(auto itr = _mapBeautyPtr.begin(); itr != _mapBeautyPtr.end(); itr++)
        fnAck->vecBeauty.push_back(*(itr->second));
    fnAck->dwLoveCnt = GetLoveHearts();
    fnAck->dwNextChatTime = GetNexChatTime();
    fnAck->dwNextGoldLotteryTime = GetNextFreeGoldTime();
    fnAck->dwNextSilverLotterTime = GetNextFreeSilverTime();
    fnAck->wBeautyID = GetFightBeautyID();
    LOG_INF<<"qwRoleID:"<<_rPlayer.GetRoleID()<<"dwLoveCnt:"<<GetLoveHearts()<<" dwNextChatTime:"<<GetNexChatTime()<<" dwNextGoldLotteryTime:"<<GetNextFreeGoldTime()<<" dwNextSilverLotterTime"<<GetNextFreeSilverTime()<<" wBeautyID:"<<GetFightBeautyID();
    return eBeautyRet_Sucess;
}

//接收：结识美女
EBeautyRet CBeautyMgr::OnMeetBeauty( UINT16 wBeautyID)
{
    LOG_INF<<"OnMeetBeauty:"<<wBeautyID;

    SBeautyCFGExPtr pBeautyCFGExPtr = GetBeautyCFG(wBeautyID);
    if(NULL == pBeautyCFGExPtr)
    {
        _rPlayer.SendSysMsg(eMsgBeautyErrorCFG);
        LOG_INF<<"eMsgBeautyErrorCFG";
        return eBeautyRet_ErrorCFG;
    }


    SBeautyPtr pBeauty1 = GetBeauty(wBeautyID);
    if(pBeauty1)
    {
        _rPlayer.SendSysMsg(eMsgBeautyExistBeauty);
        LOG_INF<<"eMsgBeautyExistBeauty";
        return eBeautyRet_ExistBeauty;
    }

    CUser& rUser = _rPlayer.GetUser();

    UINT16 wCondID = pBeautyCFGExPtr->_CondID;
    if (!wCondID || !CGetCondMgr::Instance().TestCond(rUser, wCondID))
    {
        _rPlayer.SendSysMsg(eMsgBeautyGondError);
        LOG_INF<<"eMsgBeautyGondError";
        return eBeautyRet_GondError;
    }

    if (!CGetCondMgr::Instance().ProcessCond(rUser, wCondID, NLogDataDefine::ItemTo_Beauty))
    {
        _rPlayer.SendSysMsg(eMsgBeautyGondError);
        LOG_INF<<"eMsgBeautyGondError ProcessCond";
        return eBeautyRet_GondError;
    }

    SBeautyLevelCFGExPtr pLevelCFG = GetBeautyLevelCFG(wBeautyID,1); 
    if(NULL == pLevelCFG)
    {
        _rPlayer.SendSysMsg(eMsgBeautyErrorCFG);

        LOG_INF<<"NULL == pLevelCFG";
        return eBeautyRet_ErrorCFG;
    }

    SBeautyPtr pBeauty(new SBeauty);
    pBeauty->qwRoleID=_rPlayer.GetRoleID();
    pBeauty->wBeautyID = wBeautyID;
    pBeauty->wBeautyLevel = 1;
    pBeauty->dwBeautyExp = 0;
    pBeauty->wDayLoveType = pLevelCFG->GetRandomItemType();
    pBeauty->dwChatTime = 0;

    _mapBeautyPtr[wBeautyID] = pBeauty;

    Update2DB(*pBeauty);

    _rPlayer.SendPkg(g_BeautyS.BuildPkg_BeautyNotify(*pBeauty));

    ReBuildAttr();

    LOG_INF<<"qwRoldID:"<<_rPlayer.GetRoleID()<<" MeetBuauty sucess wBeautyID:"<<wBeautyID;

    
    TVecINT32 vecParam;
    vecParam.push_back(wBeautyID);
    _rPlayer.OnEvent(eEventType_BeautyUnlock,vecParam);
    
    {
        TVecINT32 vecParam;
        vecParam.push_back(_mapBeautyPtr.size());
        _rPlayer.OnEvent(eEventType_BeautyUnlockNum,vecParam);
       
        //美女收集活动
        g_Game2CenterCommC.Send_SendWonderType(NGame2CenterComm::eActBeauty,_rPlayer.GetRoleID(),wBeautyID);

        //存Log
        WriteBeautyLogToDB(wBeautyID);
    }

    return eBeautyRet_Sucess; 
}

//接收：和美女聊天
EBeautyRet CBeautyMgr::OnChatBeauty( UINT16 wBeautyID)
{
    LOG_DBG<<"OnChatBeauty";
    SBeautyPtr pBeauty = GetBeauty(wBeautyID);
    if(NULL == pBeauty)
    {
        _rPlayer.SendSysMsg(eMsgBeautyErrorID);
        LOG_INF<<"eMsgBeautyErrorID:"<<wBeautyID;
        return eBeautyRet_ErrorID;
    }

    UINT32 dwNextChatTime = GetNexChatTime();

    if(dwNextChatTime>time(NULL))
    {
        if((dwNextChatTime-time(NULL))>SParamConfig::wBeautyTotalChatCd)
        {
            _rPlayer.SendSysMsg(eMsgBeautyChatCd);
            LOG_INF<<"eMsgBeautyChatCd:"<<dwNextChatTime<<"|"<<time(NULL);
            return eBeautyRet_ChatCd;
        }
    }
    else
    {
        dwNextChatTime = time(NULL);
    }

    //cd
    dwNextChatTime += SParamConfig::wBeautySingleChatCd;
    _rPlayer.SendPkg(g_BeautyS.BuildPkg_ChatCdNotify(dwNextChatTime));
    SetNextChatTime(dwNextChatTime);

    //亲密度增加
    pBeauty->dwBeautyExp += SParamConfig::wBeautyChatAddExp;

    LOG_INF<<"qwRoleID"<<_rPlayer.GetRoleID()<<"dwBeautyExp:"<<pBeauty->dwBeautyExp<<" AddExp:"<<SParamConfig::wBeautyChatAddExp;

    OnExpChange(pBeauty);

    TVecINT32 vecParam;
    vecParam.push_back(1);
    _rPlayer.OnEvent(eEventType_BeautyHug,vecParam);
 
    return eBeautyRet_Sucess; 
}

//亲密度改变
void CBeautyMgr::OnExpChange(SBeautyPtr pBeauty)
{
    //屏蔽爱心功能爱心计算
    if(0)
    {
        UINT32 dwMaxExp = pBeauty->dwBeautyExp;
        if(dwMaxExp > SParamConfig::dwBeautyMoodExpMax)
        {
            //dwMaxExp = SParamConfig::dwBeautyMoodExpMax;
        }

        UINT32 dwHeartAddExp = dwMaxExp - pBeauty->dwPrizeExp;

        UINT32 dwCount = dwHeartAddExp/SParamConfig::dwBeautyMoodExpOneHeart;
        if(dwCount)
        {
            pBeauty->dwPrizeExp += dwCount*SParamConfig::dwBeautyMoodExpOneHeart;
            UINT32 dwHearts = GetLoveHearts() + dwCount;
            AddLoveHearts(dwCount);
            _rPlayer.SendPkg(g_BeautyS.BuildPkg_LoveHeartCntNotify(dwHearts));
            LOG_INF<<"add hearts count:"<<dwCount;
        }
    }

    //等级计算
    UINT16 wNowLevel = pBeauty->wBeautyLevel; 
    UINT16 wBeautyID = pBeauty->wBeautyID;

    UINT16 wOldLevel = wNowLevel;

    for(UINT32 i=0; i <200; i++)
    {
        SBeautyLevelCFGExPtr pLevelCFG = GetBeautyLevelCFG(wBeautyID,wNowLevel); 
        if(NULL == pLevelCFG)
        {
            break;
        }

        //等级升满
        SBeautyLevelCFGExPtr pNextLevelCFG = GetBeautyLevelCFG(wBeautyID,wNowLevel+1);
        if(NULL == pNextLevelCFG)
        {
            break;
        }

        if(pLevelCFG->_Exp <= pBeauty->dwBeautyExp)
        {
            wNowLevel++;
            pBeauty->wDayLoveType=pLevelCFG->GetRandomItemType();
        }
        else
        {
            break;
        }
    }

    //新等级
    pBeauty->wBeautyLevel = wNowLevel;

    Update2DB(*pBeauty);
    _rPlayer.SendPkg(g_BeautyS.BuildPkg_BeautyNotify(*pBeauty));
    
    //写LOGServer
    WriteBeautyLogToDB(wBeautyID);

    //有升级
    if(wOldLevel != wNowLevel)
    {
        LOG_INF<<"qwRoleID:"<<_rPlayer.GetRoleID()<<" wBeautyLevel:"<<wOldLevel<<"->"<<wNowLevel;
        ReBuildAttr();
        if(wBeautyID == _wBeautyID)
        {
            _wBeautyLevel = wNowLevel;
            //视野广播处理
            CGameMapPtr pMap = _rPlayer.GetMap();
            if(NULL != pMap)
            {
                pMap->AppearToSurround(_rPlayer);
            }
        }

        TVecINT32 vecParam;
        vecParam.push_back(wBeautyID);
        vecParam.push_back(wNowLevel);
        _rPlayer.OnEvent(eEventType_BeautyLevelUp,vecParam);

    }
    _rPlayer.GetUser().GetTaskPkg().OnAction(_rPlayer,eProcessAction_SpecialBeautyPoint);
}

void PushItem(NItemProt::TVecItemCount& vecItemCountPack,const SItemCount& oItemCount)
{
    for(size_t i=0; i < vecItemCountPack.size(); i++)
    {
        if(oItemCount.wItemID == vecItemCountPack[i].wItemID )
        {
            vecItemCountPack[i].wCount += oItemCount.wCount;
            return;
        }
    }

    vecItemCountPack.push_back(oItemCount);

}

void PackItemCount(const NItemProt::TVecItemCount& vecItemCount,NItemProt::TVecItemCount& vecItemCountPack)
{
    for(size_t i=0; i < vecItemCount.size(); i++)
    {
        PushItem(vecItemCountPack,vecItemCount[i]);
    }
}

//接收：送美女礼品
EBeautyRet CBeautyMgr::OnSendPrizeBeauty(UINT16 wBeautyID,const NItemProt::TVecItemCount& vecItemCount)
{
    LOG_INF<<"OnSendPrizeBeauty";
    SBeautyPtr pBeauty = GetBeauty(wBeautyID);
    if(NULL == pBeauty)
    {
        _rPlayer.SendSysMsg(eMsgBeautyErrorID);
        LOG_INF<<"eMsgBeautyErrorID:"<<wBeautyID;
        return eBeautyRet_ErrorID;
    }

    SBeautyLevelCFGExPtr pLevelCFG = GetBeautyLevelCFG(wBeautyID,pBeauty->wBeautyLevel);
    if(NULL == pLevelCFG)
    {
        _rPlayer.SendSysMsg(eMsgBeautyErrorCFG);
        LOG_INF<<"NULL == pLevelCFG";
        return eBeautyRet_ErrorCFG;
    }

    NItemProt::TVecItemCount vecItemCountPack;
    PackItemCount(vecItemCount,vecItemCountPack);


    CUser& rUser = _rPlayer.GetUser();
    CPack& rPack = rUser.GetPack();

    if(!rPack.CanSubItem(vecItemCountPack))
    {
        //_rPlayer.SendSysMsg(eMsgBattleArrayPackError);
        _rPlayer.SendSysMsg(eMsgBeautyLackItem);
        LOG_INF<<"eMsgBeautyLackItem";
        return eBeautyRet_LackItem;
    }

    double fRate = SParamConfig::dwBeautyLoveTypeRate/10000.0;

    //获取喜欢的
    UINT16 wLoveType = pBeauty->wDayLoveType;

    UINT32 dwAddExp = 0;

    UINT32 dwLoveAddValue = 0;
    UINT32 dwNormalAddValue = 0;
    for(UINT32 i=0;i < vecItemCount.size(); i++)
    {
        UINT16 wItemID = vecItemCount[i].wItemID;
        UINT32 wCount  = vecItemCount[i].wCount;
        SItemInfo* pItemInfo = CItemMgr::GetItemConfig(wItemID);
        if(NULL == pItemInfo)
        {
            _rPlayer.SendSysMsg(eMsgBeautyErrorCFG);
            return eBeautyRet_ErrorCFG;
        }

        const SItemCFG& rItemCFG = pItemInfo->oItemCfg; 

        //物品类型检查
        //if(!pLevelCFG->IsItemType(rItemCFG._Type))
        if(rItemCFG._Type<166 || rItemCFG._Type>180)
        {
            _rPlayer.SendSysMsg(eMsgBeautyErrorCFG); 
            LOG_CRI<<"ItemType Error!!!";
            return eBeautyRet_ErrorCFG;
        }

        if (rItemCFG._Type == wLoveType)
        {
            dwAddExp += rItemCFG._Goodwill * fRate*wCount;
            dwLoveAddValue += rItemCFG._Goodwill * fRate*wCount;
        }
        else
        {
            dwAddExp += rItemCFG._Goodwill*wCount;

            dwNormalAddValue += rItemCFG._Goodwill*wCount;
        }
    }

    rPack.SubItem(vecItemCountPack,NLogDataDefine::ItemTo_Beauty);


    pBeauty->dwBeautyExp += dwAddExp;

    LOG_INF<<"qwRoleID:"<<_rPlayer.GetRoleID()<<"dwBeautyExp:"<<pBeauty->dwBeautyExp<<" AddExp:"<<dwAddExp;
    OnExpChange(pBeauty);
    
    TVecINT32 vecParam;
    vecParam.push_back(1);
    _rPlayer.OnEvent(eEventType_BeautySend,vecParam);

    {
        TVecINT32 vecParam;
        vecParam.push_back(dwLoveAddValue);
        vecParam.push_back(dwNormalAddValue);
        _rPlayer.OnEvent(eEventType_BeautySendAppreciate,vecParam);
    }
 
    return eBeautyRet_Sucess; 
}

extern void PushItemFromRes(TVecItemGenInfo& oVecToItemGenInfo,TVecResource& vecFromRes);

//接收：抽奖
EBeautyRet CBeautyMgr::OnLotteryBeauty(const ELotteryBeautyType eLotteryBeautyType,NItemProt::TVecItemGenInfo& vecItemGenInfo)
{
    if(!_bInitLotter)
    {
        InitDropLoot();
        _bInitLotter = true;
    }

    CUser& rUser = _rPlayer.GetUser();
    CPack& rPack = rUser.GetPack();
    if(rPack.GetEmptyCount() < 3)
    {
        _rPlayer.SendSysMsg(eMsgBattleArrayPackError);
        LOG_INF<<"eMsgBattleArrayPackError";
        return eBeautyRet_PackError;
    }

    SBeautyLotteryCFGExPtr pLotteryCFG = GetBeautyLotteryCFG(eLotteryBeautyType);
    if(NULL == pLotteryCFG)
    {
        _rPlayer.SendSysMsg(eMsgBeautyLotterTypeError);
        return eBeautyRet_LotterTypeError;
    }

    UINT32 dwCost = pLotteryCFG->_Cost;

    UINT32 dwTakeCount = 1;

    bool bGold = false;
    switch(eLotteryBeautyType)
    {

        case eLotteryBeautyType_OneSilver: //= 1001, //单次银币抽奖
            {
                UINT32 dwNexTime = GetNextFreeSilverTime();

                //SParamConfig::byBeautySliveFreeCount;

                //UINT32 dwMaxFreeCnt = 16;
                              //非免费
                if(dwNexTime > time(NULL) || GetFreeCnt() >= SParamConfig::byBeautySliveFreeCount)
                {
                    if(!rUser.CanSubMoney(EMONEY_SILVER,dwCost))
                    {
                        _rPlayer.SendSysMsg(eMsgSilverErr);
                        LOG_INF<<eLotteryBeautyType<<" eMsgSilverErr";
                        return eBeautyRet_MoneyError;
                    }

                    rUser.SubMoney(EMONEY_SILVER,dwCost,NLogDataDefine::ItemTo_Beauty);
                }
                else
                {
                    UINT32 dwCDTime = time(NULL)+SParamConfig::dwBeautySliveLotteryCd;

                    //test code
                    //dwCDTime = time(NULL) + 30;

                    SetNextFreeSilverTime(dwCDTime);

                    _rPlayer.SendPkg(g_BeautyS.BuildPkg_FreeMoneyCdNotify(eLotteryBeautyType_OneSilver,dwCDTime));
                    UINT32 dwCnt = GetFreeCnt() + 1;
                    SetFreeCnt(dwCnt);
                    _rPlayer.SendPkg(g_BeautyS.BuildPkg_LotteryFreeCntNotify(GetFreeCnt()));
                }
            }
            break;
        case eLotteryBeautyType_OneGold:  //= 1002, //单次仙石抽奖
            {
                bGold = true;
                if(!rUser.CanSubMoney(EMONEY_GOLD,dwCost))
                {
                    _rPlayer.SendSysMsg(eMsgGoldErr);
                    LOG_INF<<eLotteryBeautyType<<" eMsgGoldErr";
                    return eBeautyRet_MoneyError;
                }

                rUser.SubMoney(EMONEY_GOLD,dwCost,NLogDataDefine::ItemTo_Beauty);

                //UINT32 dwNexTime = GetNextFreeGoldTime();

            }
            break;
        case eLotteryBeautyType_OneLoveHeart: //= 1003, //单次爱心抽奖
            {
                UINT32 dwLoveHearts = GetLoveHearts();
                if(dwLoveHearts < dwCost)
                {
                    _rPlayer.SendSysMsg(eMsgBeautyHeartError);
                    LOG_INF<<eLotteryBeautyType<<" eMsgBeautyHeartError";
                    return eBeautyRet_MoneyError;
                }

                //dwLoveHearts -= dwCost;
                SubLoveHearts(dwCost);
            }
            break;
        case eLotteryBeautyType_OneFreeGold:
            {
                UINT32 dwNexTime = GetNextFreeGoldTime();

                //非免费
                if(dwNexTime > time(NULL))
                {
                    return eBeautyRet_LotterTypeError;

                }
                else
                {
                    UINT32 dwCDTime = time(NULL)+SParamConfig::dwBeautyGoldLotteryCd;
                    SetNextFreeGoldTime(dwCDTime);
                    _rPlayer.SendPkg(g_BeautyS.BuildPkg_FreeMoneyCdNotify(eLotteryBeautyType_OneGold,dwCDTime));
                }

            }
            break;
        case eLotteryBeautyType_TenSilver:  //= 2001, //10次银币抽奖
            {
                if(!rUser.CanSubMoney(EMONEY_SILVER,dwCost))
                {
                    _rPlayer.SendSysMsg(eMsgSilverErr);
                    LOG_INF<<eLotteryBeautyType<<" eMsgSilverErr";
                    return eBeautyRet_MoneyError;
                }

                rUser.SubMoney(EMONEY_SILVER,dwCost,NLogDataDefine::ItemTo_Beauty);

                dwTakeCount = 10;

            }
            break;
        case eLotteryBeautyType_TenGold:   //= 2002, //10次仙石抽奖
            {
                if(!rUser.CanSubMoney(EMONEY_GOLD,dwCost))
                {
                    _rPlayer.SendSysMsg(eMsgGoldErr);
                    LOG_INF<<eLotteryBeautyType<<" eMsgGoldErr";
                    return eBeautyRet_MoneyError;
                }

                rUser.SubMoney(EMONEY_GOLD,dwCost,NLogDataDefine::ItemTo_Beauty);

    
                dwTakeCount = 10;
            }
            break;
        case eLotteryBeautyType_TenLoveHeart: //= 2003 //10次爱心抽奖
            {
                UINT32 dwLoveHearts = GetLoveHearts();
                if(dwLoveHearts < dwCost)
                {
                    _rPlayer.SendSysMsg(eMsgBeautyHeartError);
                    LOG_INF<<eLotteryBeautyType<<" eMsgBeautyHeartError";
                    return eBeautyRet_MoneyError;
                }

                //dwLoveHearts -= dwCost;
                SubLoveHearts(dwCost);

                dwTakeCount = 10;
            }
            break;
        default:
            {
                return eBeautyRet_Sucess;
            }
            break;
    }

    //no do
    if(bGold) {};

    TVecItemGenInfo vecItems;
    TVecResource vecRes;
    
    if( (eLotteryBeautyType == eLotteryBeautyType_TenGold) && (0 == GetFirstGoldLotter()))
    {
         SetFirstGoldLotter(1);
         //SendFirstGoldLotterPrize();
         //谢林信物
         //rPack.AddItemWithID(360,1,eBindGet,0,NLogDataDefine::ItemFrom_Beauty);

         //第一次十连抽
         Loot(1, vecItems);
         if(vecItems.empty())
         {
            if(pLotteryCFG->_DropID)
            {
              Loot(pLotteryCFG->_DropID, vecItems);
            }
         }
    }
    else
    {
          if(pLotteryCFG->_DropID)
          {
              Loot(pLotteryCFG->_DropID, vecItems);
          }
         
     }

     {
          for(UINT32 i =0; i < pLotteryCFG->_Count; i++)
          {
              Loot(pLotteryCFG->_RandomDropID,vecItems);
          }
     }
 
    
    rPack.AddItem(vecItems,NLogDataDefine::ItemFrom_Beauty,true,false);

   
    //发送客户端物品信息
    vecItemGenInfo = vecItems;

    for(UINT32 i=0; i < vecItems.size(); i++)
    {
        SItemInfo* pItemInfo = CItemMgr::GetItemConfig(vecItems[i].wItemID);
        if(NULL == pItemInfo)
        {
            LOG_CRI<<" Error wItemID:"<<vecItems[i].wItemID;
            continue;
        }

        //全局log
        if(pItemInfo->oItemCfg._Quality >= 4 )
        {
            NBeautyLogGS::SBeautyLog oBeautyLog;
            oBeautyLog.qwUserID = _rPlayer.GetUserID();
            oBeautyLog.strRoleName = _rPlayer.GetName();
            oBeautyLog.byColor = _rPlayer.GetColor();
            oBeautyLog.wItemID = vecItems[i].wItemID;
            oBeautyLog.dwCount = vecItems[i].dwCount;
            _rPlayer.SendCenterSvrPkg(g_Game2CenterCommC.BuildPkg_BeautyLotteryLog(oBeautyLog));
        }
        LOG_INF<<"qwRoleID:"<<_rPlayer.GetRoleID()<<" LotteryPrize "<<"wItemID:"<<vecItems[i].wItemID<<" dwCount:"<<vecItems[i].dwCount;
    }

    TVecINT32 vecParam;
    vecParam.push_back(dwTakeCount);
    _rPlayer.OnEvent(eEventType_TravelFinish,vecParam);

    return eBeautyRet_Sucess; 
}

//接收：美女出战
EBeautyRet CBeautyMgr::OnBeautyFight(UINT16 wBeautyID)
{
    bool bDel = false;
    //卸下当前美女
    if(_wBeautyID)
    {
        SBeautyPtr pBeauty = GetBeauty(_wBeautyID);
        if(pBeauty)
        {
            pBeauty->bFight = false;
            _rPlayer.SendPkg(g_BeautyS.BuildPkg_BeautyNotify(*pBeauty));
        }
        if (!wBeautyID)
            bDel = true;
    }

    if(wBeautyID)
    {
        SBeautyPtr pBeauty = GetBeauty(wBeautyID);
        if(NULL == pBeauty)
        {
            _rPlayer.SendSysMsg(eMsgBeautyErrorID);
            LOG_INF<<"eMsgBeautyErrorID:"<<wBeautyID;
            return eBeautyRet_ErrorID;
        }

        _wBeautyID = wBeautyID;
        _wBeautyLevel = pBeauty->wBeautyLevel;
        pBeauty->bFight = true;
        _rPlayer.SendPkg(g_BeautyS.BuildPkg_BeautyNotify(*pBeauty));
    }
    else
    {
        //卸下美女
        _wBeautyID = 0;
        _wBeautyLevel = 0;
    }

    SetFightBeautyID(wBeautyID);

    //视野广播处理
    CGameMapPtr pMap = _rPlayer.GetMap();
    if(NULL != pMap)
        pMap->AppearToSurround(_rPlayer);

    if (bDel)
        g_Game2CenterTeamC.Send_SynTeamDelBeauty(_rPlayer.GetRoleID());
    else
        g_Game2CenterTeamC.SyncBeautyInfo(_rPlayer.GetRoleID());
    _rPlayer.GetUser().GetTaskPkg().OnAction(_rPlayer, eProcessAction_GetBeauty);

    return eBeautyRet_Sucess;
}

bool CBeautyMgr::GetBattleFighters(std::vector<IBattleFighterPtr>& vecBattleFighter)
{

    CHeroFighterPtr pMainFighter = _rPlayer.GetMainFighter();
    if (NULL == pMainFighter)
        return false;

    TVecFloat vecAddAttr = pMainFighter->GetAttrVec();
    IBattleFighterPtr pBattleFighter = ToBattleFighter(vecAddAttr);
    if (pBattleFighter)
    {
        vecBattleFighter.push_back(pBattleFighter);
        return true;
    }
    return false;
}


IBattleFighterPtr CBeautyMgr::ToBattleFighter(const TVecFloat& allPetAttr)
{
    UINT16 wBeautyID = GetFightBeautyID();
    if(0 == wBeautyID)
    {
        return NULL;
    }

    const SBeautyPtr pBeauty = GetBeauty(wBeautyID);
    if(NULL == pBeauty)
    {
        LOG_CRI<<"qwRoleID:"<<_rPlayer.GetRoleID()<<" wBeautyID:"<<wBeautyID;
        return NULL;
    }

    const SBeautyLevelCFGExPtr pLevelCFG = GetBeautyLevelCFG(wBeautyID,pBeauty->wBeautyLevel); 
    if(NULL == pLevelCFG)
    {
        LOG_CRI<<"qwRoleID:"<<_rPlayer.GetRoleID()<<" wBeautyID:"<<wBeautyID<<" wBeautyLevelID:"<<pBeauty->wBeautyLevel;
        return NULL;
    }

    SBeautyCFGExPtr pBeautyCFG =  GetBeautyCFG(wBeautyID);
    if(NULL == pBeautyCFG)
    {
        return NULL;
    }

    UINT32 dwSkillID  = CSkillMgr::Instance().GetSkillIDQualityLevel(pLevelCFG->_SkillID, pBeauty->wBeautyLevel);

    UINT16 wFighterID = pBeautyCFG->_NPCID;

    SFighterPropCFGEx* pFighterCFG = CFighterMgr::GetFighterPropCfg(wFighterID);
    if (!pFighterCFG)
        return NULL;

    IBattleFighterPtr pBattleFighter = CreateBattleFighter();
    if (!pBattleFighter)
        return NULL;

    SBFInfo sBFInfo;
    sBFInfo.qwInstID    = 0;                                            //将唯一ID
    sBFInfo.wFighterID  = wFighterID;                                   //将类型ID
    sBFInfo.dwPos       = IBattleFighter::GetBeautyPos();               //阵型中的位置(BattleSimulator加载的时候会重新设置)
    sBFInfo.byLevel     = 1;                                            //等级
    sBFInfo.eJob        = static_cast<ECareerType>(pFighterCFG->_Job);  //职业
    sBFInfo.strName     = pFighterCFG->_Name;                           //姓名
    sBFInfo.eSex        = ESEX_FEMALE;                                  //性别


    SBeautyFeaturePtr pSBeautyFeature(new SBeautyFeature);
    pSBeautyFeature->wBeautyID = wFighterID;

    sBFInfo.pFeature = dynamic_pointer_cast<SFeatureBase>(pSBeautyFeature);
    if (!pBattleFighter->InitFighter(sBFInfo))
        return NULL;

    pBattleFighter->InitFighterAttr(allPetAttr);
    pBattleFighter->InitFighterBattleInfo(100, 100, pFighterCFG->_EFIGHTATTR_INITAURA, pFighterCFG->_EFIGHTATTR_MAXAURA);
    pBattleFighter->SetMaxHP(100);
    pBattleFighter->SetHP(100);

    UINT32      dwNormalAttack = 0;
    
    TVecUINT32 vecAllSkill;
    vecAllSkill.push_back(dwSkillID);
    pBattleFighter->InitFighterSkills(vecAllSkill, dwNormalAttack);

    return pBattleFighter;
}

//零点事件
void CBeautyMgr::OnMidNight()
{
    for(auto itr = _mapBeautyPtr.begin(); itr != _mapBeautyPtr.end(); itr++)
    {
        SBeautyLevelCFGExPtr pLevelCFG = GetBeautyLevelCFG(itr->second->wBeautyID,itr->second->wBeautyLevel);
        if(pLevelCFG)
        {
            itr->second->wDayLoveType = pLevelCFG->GetRandomItemType();
            Update2DB(*(itr->second));
            _rPlayer.SendPkg(g_BeautyS.BuildPkg_BeautyNotify(*(itr->second)));
        }

    }

    //计数清零
    SetFreeCnt(0);
    _rPlayer.SendPkg(g_BeautyS.BuildPkg_LotteryFreeCntNotify(GetFreeCnt()));
}

SBeautyCFGExPtr CBeautyMgr::GetBeautyCFG(UINT16 wBeautyID)
{
    auto itr = CBeautyMgr::_mapBeautyCFGExPtr.find(wBeautyID);
    if(itr != CBeautyMgr::_mapBeautyCFGExPtr.end())
    {
        return itr->second;
    }

    return NULL;
}

SBeautyLevelCFGExPtr CBeautyMgr::GetBeautyLevelCFG(UINT32 dwLevelID)
{
    auto itr = CBeautyMgr::_mapBeautyLevelCFGExPtr.find(dwLevelID);
    if(itr != CBeautyMgr::_mapBeautyLevelCFGExPtr.end())
    {
        return itr->second;
    }
    return NULL;
}

SBeautyLevelCFGExPtr CBeautyMgr::GetBeautyLevelCFG(UINT16 wBeautyID,UINT16 wLevel)
{
    UINT32 dwLevelID = wBeautyID*PERID + wLevel;
    return GetBeautyLevelCFG(dwLevelID);
}

SBeautyLotteryCFGExPtr CBeautyMgr::GetBeautyLotteryCFG(UINT16 wPrizeType)
{
    auto itr = CBeautyMgr::_mapBeautyLotteryCFGExPtr.find(wPrizeType);
    if(itr != CBeautyMgr::_mapBeautyLotteryCFGExPtr.end())
    {
        return itr->second;
    }

    return NULL;
}


SBeautyPtr CBeautyMgr::GetBeauty(UINT16 wBeautyID)
{
    auto itr = _mapBeautyPtr.find(wBeautyID);
    if(itr != _mapBeautyPtr.end())
    {
        return itr->second;
    }
    return NULL;
}
void CBeautyMgr::AddLoveHearts(UINT32 dwCount)
{
    CUser& rUser = _rPlayer.GetUser();
    rUser.AddMoney(EMONEY_LOVEHEART,dwCount,NLogDataDefine::ItemFrom_Beauty);

}

void CBeautyMgr::SubLoveHearts(UINT32 dwCount)
{
    CUser& rUser = _rPlayer.GetUser();
    rUser.SubMoney(EMONEY_LOVEHEART,dwCount,NLogDataDefine::ItemTo_Beauty);
}

UINT32 CBeautyMgr::GetLoveHearts()
{
    CUser& rUser = _rPlayer.GetUser();
    return rUser.GetMoney(EMONEY_LOVEHEART);
}

void CBeautyMgr::SetNextChatTime(UINT32 dwTime)
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        pAutoStoreMgr->SetValue(eAutoStore_Beauty,eBeautyAttr_NextChatTime,dwTime);
    }
}

UINT32 CBeautyMgr::GetNexChatTime()
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        return pAutoStoreMgr->GetValue(eAutoStore_Beauty,eBeautyAttr_NextChatTime);
    }

    LOG_CRI<<"Unkown error!!! qwRoleID:"<<_rPlayer.GetRoleID();
    return 0;
}

void CBeautyMgr::SetNextFreeGoldTime(UINT32 dwTime)
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        pAutoStoreMgr->SetValue(eAutoStore_Beauty,eBeautyAttr_NextFreeGoldTime,dwTime);
    }

}

UINT32 CBeautyMgr::GetNextFreeGoldTime()
{

    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        return pAutoStoreMgr->GetValue(eAutoStore_Beauty,eBeautyAttr_NextFreeGoldTime);
    }

    LOG_CRI<<"Unkown error!!! qwRoleID:"<<_rPlayer.GetRoleID();
    return 0;
}

void CBeautyMgr::SetNextFreeSilverTime(UINT32 dwTime)
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        pAutoStoreMgr->SetValue(eAutoStore_Beauty,eBeautyAttr_NextFreeSilverTime,dwTime);
    }


}

UINT32 CBeautyMgr::GetNextFreeSilverTime()
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        return pAutoStoreMgr->GetValue(eAutoStore_Beauty,eBeautyAttr_NextFreeSilverTime);
    }

    LOG_CRI<<"Unkown error!!! qwRoleID:"<<_rPlayer.GetRoleID();
    return 0;
}

void CBeautyMgr::SetFightBeautyID(UINT16 wBeautyID)
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        pAutoStoreMgr->SetValue(eAutoStore_Beauty,eBeautyAttr_FightBeautyID,wBeautyID);
    }


}

//第一次仙石抽奖
void CBeautyMgr::SetFirstGoldLotter(UINT32 dwTag)
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        pAutoStoreMgr->SetValue(eAutoStore_Beauty,eBeautyAttr_FirstLotter,dwTag);
    }
}

UINT32 CBeautyMgr::GetFirstGoldLotter()
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        return pAutoStoreMgr->GetValue(eAutoStore_Beauty,eBeautyAttr_FirstLotter);
    }

    LOG_CRI<<"Unkown error!!! qwRoleID:"<<_rPlayer.GetRoleID();
    return 0;

}

UINT32 CBeautyMgr::GetRareItemID(UINT32 dwItemID)
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        return pAutoStoreMgr->GetValue(eAutoStore_Beauty_RareItem,dwItemID);
    }

    LOG_CRI<<"Unkown error!!! qwRoleID:"<<_rPlayer.GetRoleID();
    return 0;
}

void   CBeautyMgr::SetRareItemID(UINT32 dwItemID)
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        pAutoStoreMgr->SetValue(eAutoStore_Beauty_RareItem,dwItemID,1);
    }
}

//免费次数抽奖
UINT32 CBeautyMgr::GetFreeCnt()
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        return pAutoStoreMgr->GetValue(eAutoStore_Beauty,eBeautyAttr_FreeCnt);
    }

    LOG_CRI<<"Unkown error!!! qwRoleID:"<<_rPlayer.GetRoleID();
    return 0;

}

void CBeautyMgr::SetFreeCnt(UINT32 dwFreeCnt)
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        pAutoStoreMgr->SetValue(eAutoStore_Beauty,eBeautyAttr_FreeCnt,dwFreeCnt);
    }
}


void CBeautyMgr::GetTakedRareItem(TVecUINT16& vecItemID)
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        TVecAutoStoreDBInfo vecAutoStoreDBInfo;
        pAutoStoreMgr->GetListByType(eAutoStore_Beauty_RareItem,vecAutoStoreDBInfo);
        for(size_t i = 0; i < vecAutoStoreDBInfo.size(); i++)
        {
            vecItemID.push_back(vecAutoStoreDBInfo[i].dwClassID);
        }
    }
}

UINT16 CBeautyMgr::GetFightBeautyID() const
{
    CAutoStoreMgrPtr pAutoStoreMgr = _rPlayer.GetAutoStoreMgr();
    if(pAutoStoreMgr)
    {
        return pAutoStoreMgr->GetValue(eAutoStore_Beauty,eBeautyAttr_FightBeautyID);
    }

    LOG_CRI<<"Unkown error!!! qwRoleID:"<<_rPlayer.GetRoleID();
    return 0;
}



void CBeautyMgr::ReBuildAttr()
{
    _vecAttr.clear();

    for(auto itr = _mapBeautyPtr.begin(); itr != _mapBeautyPtr.end(); itr++)
    {
        SBeautyLevelCFGExPtr pLevelCFG = GetBeautyLevelCFG(itr->second->wBeautyID,itr->second->wBeautyLevel);
        if(pLevelCFG)
        {
            SSkillAttrPtr pSkillAttr = g_SkillAttrMgr.GetSkillAttrByID(pLevelCFG->_SkillAttrID);
            if(NULL == pSkillAttr)
            {
                LOG_CRI<<"Error SkillAttr: "<<pLevelCFG->_SkillAttrID;
                continue;
            }
            _vecAttr += pSkillAttr->_vecAttr; 
        }

    }

    SetDirty();

}

void CBeautyMgr::SendFirstGoldLotterPrize()
{
   TVecUINT64 vecUserID;
   vecUserID.push_back(_rPlayer.GetUserID());

   TVecItemGenInfo vecItems;
   SItemGenInfo oItemGenInfo;
   oItemGenInfo.wItemID   = 360; //谢林信物
   oItemGenInfo.dwCount   = 1;
   oItemGenInfo.eBindType = eBindGet;
   vecItems.push_back(oItemGenInfo);
   
   NMailProt::SysMailSendTxt stBody;
   stBody.dwstrMsgID = BODY_FIRST_GOLD_LOTTERY;
   //stBody.vecParam.push_back(NumberToString(pPlayer->dwNo));
   GameServerSysMail::SendSysMail(SEND_FIRST_GOLD_LOTTERY, TITLE_FIRST_GOLD_LOTTERY, stBody, vecUserID, &vecItems);

}
void CBeautyMgr::SetDirty()
{
    {
        CFighterManagerPtr& pFighterManager =_rPlayer.GetFighterManager();
        if(pFighterManager)
        {
            pFighterManager->SetDirty(eAttrBeauty);
        }
    }
}

void CBeautyMgr::Loot(UINT32 dwDropID,TVecItemGenInfo& vecItems)
{
    LOG_INF<<"dwDropID:"<<dwDropID;

    if(0 == dwDropID)
        return;

    SLootProb& rLootProb = _mapLootProb[dwDropID];
    if(rLootProb.vecProbLottery.empty())
    {
        LOG_CRI<<"Error Loot dwDropID:"<<dwDropID;
        return;
    }

    if(rLootProb.dwTotleProb < 1)
    {
        return;
    }

    UINT32 dwProb = CRandom::RandInt(0,rLootProb.dwTotleProb-1);
    TVecProbLottery& rVecProbLottery  = rLootProb.vecProbLottery;

    UINT16 wRareItemID = 0;

    for(size_t i=0; i < rVecProbLottery.size(); i++)
    {
        SProbLottery& rProbLottery = rVecProbLottery[i];  
        if(rProbLottery.dwMinProb>= dwProb)
        {
            //掉落物品

            if(NULL == rProbLottery.pBeautyRareLotteryCFGExPtr)
            {
                LOG_CRI<<"Unkown Error!!!";
                continue;
            }
            vecItems.push_back(rProbLottery.pBeautyRareLotteryCFGExPtr->oItemGenInfo);

            //删除稀有掉i落
           
            if(rProbLottery.pBeautyRareLotteryCFGExPtr->_Rare)
            {
                SetRareItemID(rProbLottery.pBeautyRareLotteryCFGExPtr->_ItemID);
                wRareItemID = rProbLottery.pBeautyRareLotteryCFGExPtr->_ItemID;

                rVecProbLottery.erase(rVecProbLottery.begin()+i);

            }

            break;
        }
    }

    if(wRareItemID)
    {
        DeleteDropItem(wRareItemID);
    }

    
}

//删掉掉落
void CBeautyMgr::DeleteDropItem(UINT16 wItemID)
{
    for(auto itr = _mapLootProb.begin(); itr != _mapLootProb.end(); itr++)
    {
        RemoveDropItem(wItemID,itr->second);
    }

    SetRareItemID(wItemID);

}

//删掉物品
void CBeautyMgr::RemoveDropItem(UINT16 wItemID,SLootProb& rLootProb )
{
    if(rLootProb.vecProbLottery.empty())
    {
        return;
    }

    TVecProbLottery& rVecProbLottery  = rLootProb.vecProbLottery;

     UINT32 dwReset = -1;
    for(size_t i=0; i < rVecProbLottery.size(); i++)
    {
        SProbLottery& rProbLottery = rVecProbLottery[i];  
        {
            //掉落物品

            if(NULL == rProbLottery.pBeautyRareLotteryCFGExPtr)
            {
                LOG_CRI<<"Unkown Error!!!";
                continue;
            }

            //删除稀有掉i落
           
            if(wItemID == rProbLottery.pBeautyRareLotteryCFGExPtr->_ItemID)
            {
                LOG_INF<<"remove:loot:"<<rProbLottery.pBeautyRareLotteryCFGExPtr->_Loots<<" ItemID:"<<wItemID;
                rVecProbLottery.erase(rVecProbLottery.begin()+i);
                dwReset = i;
                break;
            }
        }
    }

    if(dwReset < 0 || dwReset >= rVecProbLottery.size())
        return;

    //reset drop
    if(dwReset)
    {
        SProbLottery& rProbLottery = rVecProbLottery[dwReset-1];
        rLootProb.dwTotleProb = rProbLottery.dwMinProb;
    }
    else
    {
        rLootProb.dwTotleProb = 0;
    }

    for(size_t i=dwReset; i < rVecProbLottery.size(); i++) 
    {
        SProbLottery& rProbLottery = rVecProbLottery[i]; 

        rLootProb.dwTotleProb += rProbLottery.pBeautyRareLotteryCFGExPtr->_Probablity;

        rProbLottery.dwMinProb = rLootProb.dwTotleProb;
    }
   
}

//设置掉落库
void CBeautyMgr::SetDropLoot(UINT32 dwDropID,TVecBeautyRareLotteryCFGExPtr& rVecBeautyRareLotteryCFGExPtr)
{
    SLootProb& rLootProb = _mapLootProb[dwDropID];
    rLootProb.dwTotleProb = 0;
    TVecProbLottery& rVecProbLottery  = rLootProb.vecProbLottery;

    for(auto itr = rVecBeautyRareLotteryCFGExPtr.begin(); itr != rVecBeautyRareLotteryCFGExPtr.end(); itr++)
    {
        SBeautyRareLotteryCFGExPtr pBeautyRareLotteryCFGEx = *itr;
        if(pBeautyRareLotteryCFGEx)
        {
            if(pBeautyRareLotteryCFGEx->_Rare && GetRareItemID(pBeautyRareLotteryCFGEx->_ItemID))
                continue;

            rLootProb.dwTotleProb += pBeautyRareLotteryCFGEx->_Probablity;
            SProbLottery oProbLottery;
            oProbLottery.dwMinProb = rLootProb.dwTotleProb;
            oProbLottery.pBeautyRareLotteryCFGExPtr = pBeautyRareLotteryCFGEx;
            rVecProbLottery.push_back(oProbLottery);
        }
    }

}


//初始化掉落库
void CBeautyMgr::InitDropLoot()
{
    for(auto itr = CBeautyMgr::_dmapRareLotteryLoot.begin(); itr != CBeautyMgr::_dmapRareLotteryLoot.end(); itr++)
    {
        SetDropLoot(itr->first,itr->second);
    }

    _bInitLotter = true;
}

void CBeautyMgr::OnGetLotteryFreeCnt()
{
    _rPlayer.SendPkg(g_BeautyS.BuildPkg_LotteryFreeCntNotify(GetFreeCnt()));
}

void CBeautyMgr::WriteBeautyLogToDB(UINT16 wBeautyID)
{
    SBeautyCFGExPtr pConfig = GetBeautyCFG(wBeautyID);
    if(!pConfig)
        return;
    SBeautyPtr pBeauty = GetBeauty(wBeautyID);
    if(!pBeauty)
        return;
    NLogDataDefine::SBeautyLogPtr ptrLog(new NLogDataDefine::SBeautyLog());
    if(NULL == ptrLog)
        return;
    NLogDataDefine::SBeautyLog& rLog = *ptrLog;
    rLog.dwServerId  = Config._wGroup;
    rLog.qwUserId    = pBeauty->qwRoleID;
    rLog.sName       = pConfig->_Name;
    rLog.wID         = wBeautyID;
    rLog.wLevel      = pBeauty->wBeautyLevel;
    rLog.dwExp       = pBeauty->dwBeautyExp;
    rLog.happenedTime = time(NULL);
    CGameServerLog::LogToDB(ptrLog);
}

//登陆事件
void CBeautyMgr::OnLogin()
{
    if(_rPlayer.GetFighterManager())
    {
        TVecFighterPtr rvecFighters;
        _rPlayer.GetFighterManager()->GetAllFighters(rvecFighters);
        for(size_t i=0; i < rvecFighters.size(); i++)
        {
            if(rvecFighters[i])
            {
                SFighterPropCFG* pFighterPropCFG = rvecFighters[i]->GetFighterPropConfig();
                if(pFighterPropCFG)
                {
                    if(pFighterPropCFG->_RecruitItem)
                    {
                        if(CBeautyMgr::_setRareItem.find(pFighterPropCFG->_RecruitItem) != CBeautyMgr::_setRareItem.end())
                        {
                            DeleteDropItem(pFighterPropCFG->_RecruitItem);
                        }
                    }
                }
            }

        }
    }
}


