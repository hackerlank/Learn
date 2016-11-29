#include "stdafx.h"
#include "Protocols.h"
#include "FighterProtS.h"
#include "UserMgr.h"
#include "ItemMgr.h"
#include "Player.h"
#include "Parameter.h"
#include "MoneyParam.h"
#include "Map.h"
#include "MapInfo.h"
#include "SysMsgDefine.h"
#include "HeroFighter.h"
#include "FighterManager.h"
#include "VIPMgr.h"
#include "DrawMgr.h"
#include "Random.h"
#include "GameNetMgr.h"

void SystemMsg(ESkillResult& eResult);
void SystemMsg(ERecruitResult& eResult);
void SystemMsg(ECuiTiResult& eResult);
void SystemMsg(EShiftResult& eResult);
void SystemMsg(ESyncLevelResult& eResult);
void SystemMsg(ECombinationResult& eResult);
void SystemMsg(EDujieResult& eResult);
void SystemMsg(const EDismissResult& eResult);

//接收：散仙装备技能
bool CFighterProtS::OnRecv_FighterSkillEquipTo(
        UINT64 qwInstID, //散仙唯一ID
        UINT32 dwSkillID, //技能ID
        INT32 iSlot, //技能槽 -1表示卸下技能
        shared_func<SFighterSkillEquipToAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eSkillFailed;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eSkillFailed;
        return false;
    }

    CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(pPlayer->GetFighterByInstID(qwInstID));
    if (!pFighter)
    {
        fnAck->eResult = eSkillFailed;
        return false;
    }

    if (iSlot < 0)
    {
        fnAck->eResult = eSkillFailed;
        return false;
    }

    fnAck->eResult = pFighter->GetSkills().UpSkill(dwSkillID, iSlot);
    if (fnAck->eResult == eSkillSucc)
    {
        TVecUINT32 oActiveSkills;
        pFighter->GetSkills().GetActiveSkills(oActiveSkills);
        for (size_t i = 0; i < oActiveSkills.size(); ++i)
        {
            fnAck->vActiveSkill.push_back(SFightSkillInfo(i, oActiveSkills[i]));
        }
    }
    SystemMsg(fnAck->eResult);
    return true;
}

//接收：散仙技能升级
bool CFighterProtS::OnRecv_FighterSkillLevelUp(
        UINT64 qwInstID, //散仙唯一ID
        UINT32 dwSkillID, //技能ID
        shared_func<SFighterSkillLevelUpAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eSkillFailed;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eSkillFailed;
        return false;
    }

    CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(pPlayer->GetFighterByInstID(qwInstID));
    if (!pFighter)
    {
        fnAck->eResult = eSkillFailed;
        return false;
    }

    fnAck->eResult = pFighter->GetSkills().UpgradeActiveSkill(dwSkillID);
    SystemMsg(fnAck->eResult);
    return true;
}

//接收：散仙被动技能升级
bool CFighterProtS::OnRecv_FighterPassiveSkillLevelUp(
		UINT64 qwInstID, //散仙唯一ID
		UINT32 dwSkillID, //技能ID
		shared_func<SFighterPassiveSkillLevelUpAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eSkillFailed;
        return false;
    }
    if(!pUser || !pPlayer)
    {
        fnAck->eResult = eSkillFailed;
        return false;
    }

    CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(pPlayer->GetFighterByInstID(qwInstID));
    if (!pFighter)
    {
        fnAck->eResult = eSkillFailed;
        return false;
    }

    fnAck->eResult = pFighter->GetSkills().UpgradePassiveSkill(dwSkillID);
    SystemMsg(fnAck->eResult);
    return true;
}


//接收：获取客栈信息
bool CFighterProtS::OnRecv_GetTavernInfo(
        shared_func<SGetTavernInfoAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    SVIPLevelCFGEx* pCFG = CVIPMgr::Instance().GetVIPLevelCfg(pUser->GetVIPLevel());
    if (!pCFG)
        return false;
    UINT32 dwDrawCount = pUser->GetVars().GetVar(NVarDefine::ePlayerDrawCount);
    if (dwDrawCount > pCFG->_FreeDrawTimes)
        dwDrawCount = 0;
    fnAck->dwDrawCount = pCFG->_FreeDrawTimes - dwDrawCount;
    // TODO: 暂时不弄客栈信息，客户端可以获取
    return true;
}

//接收：求签
bool CFighterProtS::OnRecv_Draw(
        EDrawType eType, //求签类型
        shared_func<SDrawAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eDrawResultFailed;
        return false;
    }

    bool bFree = false;
    UINT32 dwSilver = 0;
    UINT32 dwGold = 0;
    CDrawDataPtr pData = CDrawMgr::Instance().GetDrawData(eType, pUser->GetLevel());
    if (!pData)
    {
        fnAck->eResult = eDrawResultFailed;
        return false;
    }

    switch (eType)
    {
        case eDrawTypeNormal: //普通求签(银币)
            {
                SVIPLevelCFGEx* pCFG = CVIPMgr::Instance().GetVIPLevelCfg(pUser->GetVIPLevel());
                if (pCFG && pUser->GetVars().GetVar(NVarDefine::ePlayerDrawCount) < pCFG->_FreeDrawTimes)
                        bFree = true;

                if (!bFree)
                {
                    dwSilver = pData->GetSilver();
                    dwGold = pData->GetGold();
                }
            }
            break;
        case eDrawTypeAdvance: //高级求签(仙石)
            dwSilver = pData->GetSilver();
            dwGold = pData->GetGold();
            break;
        default:
            return false;
    }
    if (!bFree)
    {
        if (dwSilver)
        {
            if (!pUser->CanSubMoney(EMONEY_SILVER, dwSilver))
            {
                fnAck->eResult = eDrawResultLackOfMoney;
                string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDrawSilverLack);
                pUser->SendPkg(strPkg);
                return false;
            }
        }
        if (dwGold)
        {
            if (!pUser->CanSubMoney(EMONEY_GOLD, dwGold))
            {
                fnAck->eResult = eDrawResultLackOfMoney;
                string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDrawGoldLack);
                pUser->SendPkg(strPkg);
                return false;
            }
        }
        if (dwSilver)
            pUser->SubMoney(EMONEY_SILVER, dwSilver, ItemTo_Draw);
        if (dwGold)
            pUser->SubMoney(EMONEY_GOLD, dwGold, ItemTo_Draw);
    }
    else
    {
        pUser->GetVars().AddVar(NVarDefine::ePlayerDrawCount, 1);
    }
    UINT16 wRand = CRandom::RandInt(0, 10000);
    EDrawRewardType eRewardType = eDrawRewardTypeNone;
    UINT32 dwRewardCount = 0;
    if (wRand < pData->GetBaseProb())
    {
        eRewardType = pData->GetBaseRewardType();
        dwRewardCount = CRandom::RandInt(pData->GetBaseMinCount(), pData->GetBaseMaxCount());
    }
    else
    {
        eRewardType = pData->GetUnexpectedRewardType();
        dwRewardCount = CRandom::RandInt(pData->GetUnexpectedMinCount(), pData->GetUnexpectedMaxCount());
    }

    EMoneyType eMoneyType = EMONEY_NONE;
    switch (eRewardType)
    {
        case eDrawRewardTypeBlue: //蓝色仙缘
            eMoneyType = EMONEY_BLUEFAIRYFATE;
            break;
        case eDrawRewardTypePurple: //紫色仙缘
            eMoneyType = EMONEY_PURPLEFAIRYFATE;
            break;
        case eDrawRewardTypeOrange: //橙色仙缘
            eMoneyType = EMONEY_ORANGEFAIRYFATE;
            break;
        default:
            LOG_CRI << "Invalid RewardType: " << static_cast<UINT32>(eRewardType) << ".";
            break;
    }
    if (eMoneyType != EMONEY_NONE)
        pUser->AddMoney(eMoneyType, dwRewardCount, ItemFrom_Draw);
    fnAck->vecItemGet.push_back(SItemCount(static_cast<UINT8>(eMoneyType), dwRewardCount));
    LOG_CRI << "eMoneyType = " << static_cast<UINT32>(eMoneyType) << ". size = " << fnAck->vecItemGet.size() << ".";

    //event
    {
        TVecINT32 vecParam;
        vecParam.push_back(eType);
        pPlayer->OnEvent(eEventType_PlayerDraw,vecParam);
    }

    return true;
}

//接收：招募
bool CFighterProtS::OnRecv_FighterRecruit(
        UINT16 wFighterID, //将ID
        shared_func<SFighterRecruitAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eRecruitFailed;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eRecruitFailed;
        return false;
    }

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
        return false;

    fnAck->eResult = pFighterManager->Recruit(wFighterID);
    SystemMsg(fnAck->eResult);
    return true;
}

//接收：淬体升级
bool CFighterProtS::OnRecv_CuiTiUpgrade(
        UINT64 qwInstID, //将唯一ID
        ECuiTiType eCuiTiType, //淬体类型
        UINT8 byTimes, //次数
        shared_func<SCuiTiUpgradeAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eCuiTiResultFailed;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eCuiTiResultFailed;
        return false;
    }

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eCuiTiResultFailed;
        return false;
    }

    CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(pFighterManager->GetFighterByInstID(qwInstID));
    if (!pFighter || byTimes == 0)
    {
        fnAck->eResult = eCuiTiResultFailed;
        return false;
    }

    UINT8 byLvl = pFighter->GetCuiTiLevel(eCuiTiType); //old CuiTi Level
    for(UINT8 i=0; i< byTimes; i++)
    {
        fnAck->eResult = pFighter->CuiTiUpgrade(eCuiTiType, fnAck->byLevel);
        if( fnAck->eResult != eCuiTiResultSucc)
        {
            //使用10次淬体的时候，完成未满10次时，返回成功
            if(fnAck->byLevel > byLvl)
                fnAck->eResult = eCuiTiResultSucc;
            break;
        }
    }
    SystemMsg(fnAck->eResult);
    return true;
}

//接收：散仙淬体全体(六种)升级一次
bool CFighterProtS::OnRecv_CuiTiAllUpgrade(
    UINT64 qwInstID, //将唯一ID
    shared_func<SCuiTiAllUpgradeAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eCuiTiResultFailed;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eCuiTiResultFailed;
        return false;
    }

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eCuiTiResultFailed;
        return false;
    }

    CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(pFighterManager->GetFighterByInstID(qwInstID));
    if (!pFighter)
    {
        fnAck->eResult = eCuiTiResultFailed;
        return false;
    }

    fnAck->vecLevel.resize(eCuiTiMax);
    bool bSucc = false;
    ECuiTiResult eResult = eCuiTiResultSucc;
    for(size_t i = 0; i < eCuiTiMax; ++ i)
    {
        fnAck->vecLevel[i] = pFighter->GetCuiTiLevel(ECuiTiType(i));
        fnAck->eResult = pFighter->CuiTiUpgrade(ECuiTiType(i), fnAck->vecLevel[i]);
        if (eResult == eCuiTiResultSucc)
            eResult = fnAck->eResult;
        if ((fnAck->eResult == eCuiTiResultSucc || fnAck->eResult == eCuiTiResultUnlock) && !bSucc)
            bSucc = true;
    }
    if (bSucc)
        fnAck->eResult = eCuiTiResultSucc;
    else
        fnAck->eResult = eResult;
    SystemMsg(fnAck->eResult);
    return true;
}

//接收：淬体转移
bool CFighterProtS::OnRecv_FighterShift(
        UINT64 qwInstIDSrc, //将唯一ID
        UINT64 qwInstIDDst, //将唯一ID
        shared_func<SFighterShiftAck>& fnAck //返回回调函数
        )
{
    if (qwInstIDSrc == qwInstIDDst)
    {
        fnAck->eResult = eShiftFailed;
        return false;
    }

    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eShiftFailed;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eShiftFailed;
        return false;
    }

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eShiftFailed;
        return false;
    }

    CHeroFighterPtr pFighterSrc = dynamic_pointer_cast<CHeroFighter>(pFighterManager->GetFighterByInstID(qwInstIDSrc));
    if (!pFighterSrc)
    {
        fnAck->eResult = eShiftFailed;
        return false;
    }

    CFighterPtr pFighterDst = pFighterManager->GetFighterByInstID(qwInstIDDst);
    if (!pFighterDst)
    {
        fnAck->eResult = eShiftFailed;
        return false;
    }

    fnAck->eResult = pFighterSrc->Shift(pFighterDst);
    SystemMsg(fnAck->eResult);
    return true;
}

//接收：同步等级
bool CFighterProtS::OnRecv_FighterSyncLevel(
        UINT64 qwInstID, //将唯一ID
		UINT8 byGoalLvl, //同步的目标等级
        shared_func<SFighterSyncLevelAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eSyncLevelFailed;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eSyncLevelFailed;
        return false;
    }

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eSyncLevelFailed;
        return false;
    }

    CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(pFighterManager->GetFighterByInstID(qwInstID));
    if (!pFighter)
    {
        fnAck->eResult = eSyncLevelFailed;
        return false;
    }

    fnAck->eResult = eSyncLevelFailed;
    SystemMsg(fnAck->eResult);
    return true;
}

//接收：渡劫升级
bool CFighterProtS::OnRecv_UpgradeDujie(
    UINT64 qwInstID, //将唯一ID
    UINT8 byOneKey, //是否一键(是>0 否=0)
    shared_func<SUpgradeDujieAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(pPlayer->GetFighterByInstID(qwInstID));
    if (!pFighter)
    {
        fnAck->eResult = eDujieFailed;
        return false;
    }

    fnAck->eResult = pFighter->DujieUpgrade(byOneKey > 0);
    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if(pFighterManager)
    {
        pFighterManager->OnFighterColorChange(pFighter->GetColor());
    }
    SystemMsg(fnAck->eResult);
    return true;
}

//接收：请求散仙心法
bool CFighterProtS::OnRecv_ReqFighterXinFaInfo(
        UINT64 qwInstID, //散仙唯一ID
        shared_func<SReqFighterXinFaInfoAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;

    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
        return false;

    CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(pPlayer->GetFighterByInstID(qwInstID));
    if (!pFighter)
        return false;

    if (pFighter->GetLevel() < 40)
        return false;

    pFighter->GetXinFas().HeroFighterXFInfo(fnAck->vecFighterXinFa);

    return true;
}

//接收：散仙学习心法
bool CFighterProtS::OnRecv_FighterActiveXinFa(
        UINT64 qwInstID, //散仙唯一ID
        UINT32 dwXinFaID, //心法ID
        shared_func<SFighterActiveXinFaAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eXinFaFailed;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eXinFaFailed;
        return false;
    }

    CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(pPlayer->GetFighterByInstID(qwInstID));
    if (!pFighter)
    {
        fnAck->eResult = eXinFaFailed;
        return false;
    }

    if (pFighter->GetLevel() < 40)
        return false;

    fnAck->eResult = pFighter->GetXinFas().LearnXinFa(dwXinFaID);

    return true;
}

//接收：散仙心法升级
bool CFighterProtS::OnRecv_FighterXinFaLevelUp(
        UINT64 qwInstID, //散仙唯一ID
        UINT32 dwXinFaID, //心法ID
        shared_func<SFighterXinFaLevelUpAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eXinFaFailed;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eXinFaFailed;
        return false;
    }

    CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(pPlayer->GetFighterByInstID(qwInstID));
    if (!pFighter)
    {
        fnAck->eResult = eXinFaFailed;
        return false;
    }

    if (pFighter->GetLevel() < 40)
        return false;

    fnAck->eResult = pFighter->GetXinFas().XinFaUpgrade(dwXinFaID);

    return true;
}

//接收：散仙心法散功
bool CFighterProtS::OnRecv_FighterXinFaDisperse(
        UINT64 qwInstID, //散仙唯一ID
        UINT32 dwXinFaID, //心法ID
        shared_func<SFighterXinFaDisperseAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eXinFaFailed;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eXinFaFailed;
        return false;
    }

    CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(pPlayer->GetFighterByInstID(qwInstID));
    if (!pFighter)
    {
        fnAck->eResult = eXinFaFailed;
        return false;
    }

    if (pFighter->GetLevel() < 40)
        return false;

    fnAck->eResult = pFighter->GetXinFas().XinFaDisperse(dwXinFaID);

    return true;
}

//接收：获取玩家的所有散仙组合
bool CFighterProtS::OnRecv_GetAllFighterCombination(
    shared_func<SGetAllFighterCombinationAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        LOG_CRI<<"pFighterManager null.";
        return false;
    }
    pFighterManager->GetHeroFighterCombinationSlots().GetAllFighterCombination(fnAck->vecCombinationInfo);
    return true;
}

//接收：激活散仙组合
bool CFighterProtS::OnRecv_ActiveCombination(
    UINT8 byGroupID, //散仙组合ID
    shared_func<SActiveCombinationAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eCombinationFailed;
        return false;
    }
    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eCombinationFailed;
        return false;
    }
    fnAck->eResult = pFighterManager->ActiveCombination(byGroupID);
    SystemMsg(fnAck->eResult);

    return true;
}

//接收：升级散仙组合
bool CFighterProtS::OnRecv_UpgradeCombination(
    UINT8 byGroupID, //散仙组合ID
    UINT8 byOneKey, //是否一键(是>0 否=0)
    shared_func<SUpgradeCombinationAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eCombinationFailed;
        return false;
    }
    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eCombinationFailed;
        return false;
    }
    fnAck->eResult = pFighterManager->UpgradeCombination(byGroupID, byOneKey > 0, fnAck->oCombinationInfo);
    SystemMsg(fnAck->eResult);

    return true;
}

//接收：装备散仙组合技能(连携技)
bool CFighterProtS::OnRecv_EquipToCombinationSkill(
    UINT8 byGroupID, //散仙组合ID
    UINT8 byType, //1出战在阵型 2出战在守卫峨眉
    shared_func<SEquipToCombinationSkillAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eCombinationFailed;
        return false;
    }
    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eCombinationFailed;
        return false;
    }
    TVecUINT16 rvecFighterID;
    if (ECombEquipToType(byType) == eCombEquipToLineUp)
    {
        CFormation& rFormation = pFighterManager->GetFormation();
        TVecLineup vecLineup;
        rFormation.GetLineup(vecLineup);

        for (size_t j = 0; j < vecLineup.size(); ++ j)
        {
            if (!vecLineup[j].pFighter)
                continue;
            rvecFighterID.push_back(vecLineup[j].pFighter->GetID());
        }
    }
    else if (ECombEquipToType(byType) == eCombEquipToEMei)
    {
        pPlayer->GetGuardEMeiFighterID(rvecFighterID);
    }
    else
    {
        fnAck->eResult = eCombinationFailed;
        return false;
    }
    fnAck->eResult = pFighterManager->EquipToCombinationSkill(byGroupID, byType, rvecFighterID);

    SystemMsg(fnAck->eResult);

    return true;
}

//接收：散仙散功
bool CFighterProtS::OnRecv_FighterDismiss(
    UINT64 qwInstID, //散仙唯一ID
    shared_func<SFighterDismissAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eDismissFailed;
        return false;
    }

    CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(pPlayer->GetFighterByInstID(qwInstID));
    if (!pFighter)
    {
        fnAck->eResult = eDismissFailed;
        return false;
    }

    fnAck->eResult = pFighter->FighterDismiss();
    SystemMsg(fnAck->eResult);
    return true;
}

void SystemMsg(EDujieResult& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {
        case eDujieSucc:
            //eMsgID = eMsgSuccess;
            return;
            break;
        case eDujieItemErr:
            eMsgID = eMsgStuffNotEnoughErr;
            break;
        case eDujieLevelMaxErr:
            eMsgID = eMsgSkillLevelMax;
            break;
        default:
            return;
            break;
    }
    g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}

void SystemMsg(ESyncLevelResult& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {
        case eSyncLevelSucc:
            eMsgID = eMsgSuccess;
            break;
        case eSyncLevelAlready:
            eMsgID = eMsgFighterLevelMaxErr;
            break;
        case eSyncLevelMoney:
            eMsgID = eMsgSilverErr;
            break;
        case eSyncLevelMoneyMore:
            //eMsgID = eMsgSilverErr;
            break;
        default:
            return;
            break;
    }
    g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}

void SystemMsg(EShiftResult& eResult)
{
    // TODO:
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {
        case eShiftGoldErr:
            eMsgID = eMsgGoldErr;
            break;
        default:
            return;
            break;
    }
    g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}

void SystemMsg(ECuiTiResult& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {
        case eCuiTiResultFailed:
            eMsgID = eMsgCfgErr;
            break;
        case eCuiTiResultSilverErr:
            eMsgID = eMsgSilverErr;
            break;
        case eCuiTiResultLvlMaxErr:
            eMsgID = eMsgCuiTiResultLvlMaxErr;
            break;
        case eCuiTiResultPlayerLvlErr:
            eMsgID = eMsgEquipIntenLevelErr;
            break;
        case eCuiTiResultUnlock:
            eMsgID = eMsgEquipIntenLevelErr;
            break;
        default:
            return;
            break;
    }
    g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}

void SystemMsg(EDrawResult& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {
        case eDrawResultSuccess: //求签成功
            eMsgID = eMsgFateConvertSuccess;
            break;
        case eDrawResultFailed: //求签失败
        case eDrawResultLackOfCount: //次数不足
        case eDrawResultLackOfMoney: //金钱不足
            eMsgID = eMsgFateConvertSuccess;
            break;
        default:
            break;
    }
    if (eMsgID != eMsgOtherErr)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);

}

void SystemMsg(ERecruitResult& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {
        case eRecruitFailed:
            eMsgID = eMsgCfgErr;
            break;
        case eRecruitAlready:
            eMsgID = eMsgInviteFateMax;
            break;
        default:
            break;
    }
    if (eMsgID != eMsgOtherErr)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}

void SystemMsg(ESkillResult& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {
        case eSkillNotExist:
            eMsgID = eMsgSkillNotExist;
            break;
        case eSkillLevelMax:
            eMsgID = eMsgSkillLevelMax;
            break;
        case eSkillLevelErr:
            eMsgID = eMsgRoleLevelErr;
            break;
        case eSkillNotUp:
            eMsgID = eMsgSkillNotUp;
            break;
        case eSkillPExpErr:
            eMsgID = eMsgPExpErr;
            break;
        case eRuneNotExist:
            eMsgID = eMsgRuneNotExist;
            break;
        case eRuneLevelMax:
            eMsgID = eMsgRuneLevelMax;
            break;
        case eRuneLevelErr:
            eMsgID = eMsgRoleLevelErr;
            break;
        case eAdvNotExist:
            eMsgID = eMsgAdvNotExist;
            break;
        case eAdvLevelGTSkillLevelErr:
            eMsgID = eMsgAdvLevelGTSkillLevelErr;
            break;
        case eSkillSopErr:
            eMsgID = eMsgSopErr;
            break;
        case eSkillPotenErr:
            eMsgID = eMsgPotenErr;
            break;
        default:
            return;
            break;
    }
    g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}

void SystemMsg(ECombinationResult& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {
        case eCombinationSucc:
            return;
        case eCombinationItemErr:
            eMsgID = eMsgHorseNotFullItem;
            break;
        case eCombinationMaxLevel:
            eMsgID = eMsgGuildLevelMax;
            break;
        case eCombinationMainLevelErr:
            eMsgID = eMsgRoleLevelErr;
            break;
        default:
            return;
            break;
    }
    g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}

void SystemMsg(const EDismissResult &eResult)
{
    ESystemMsgID eMsgID = eMsgSuccess; 
    switch (eResult)
    {
        case eNeedTakeOffStone:
            {
                eMsgID = eMsgGemstoneHeroReset;
            }
            break;
         default:
            break;

    }
    if(eMsgID != eMsgSuccess)
    {
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
    }
}

//接收：获取购买散仙信息
bool CFighterProtS::OnRecv_GetFighterBuyInfo(
    shared_func<SGetFighterBuyInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;

    CGameVar& rCGameVar = pUser->GetVars();
    UINT64 FighterBuyStatus = rCGameVar.GetVar(NVarDefine::ePlayerFighterBuyMark);
    TVecFighterBuyInfo vecFighterBuyInfo;
    SFighterBuyInfo sFighterBuyInfoA;
    SFighterBuyInfo sFighterBuyInfoB;
    sFighterBuyInfoA.wFighterID = (SParamConfig::wInviteFighterID1);
    sFighterBuyInfoA.byFighterBuyStatus = GET_BIT(FighterBuyStatus, 0);
    sFighterBuyInfoB.wFighterID = (SParamConfig::wInviteFighterID2);
    sFighterBuyInfoB.byFighterBuyStatus = GET_BIT(FighterBuyStatus, 1);
    vecFighterBuyInfo.push_back(sFighterBuyInfoA); 
    vecFighterBuyInfo.push_back(sFighterBuyInfoB);

    fnAck->vecFighterBuyInfo = vecFighterBuyInfo;

    return true;
}

//接收：散仙购买
bool CFighterProtS::OnRecv_FighterBuy(
    UINT16 wFighterID, //将ID
    shared_func<SFighterBuyAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eFighterBuyFailed;
        return false;
    }

    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eFighterBuyFailed;
        return false;
    }

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
        return false;

    fnAck->eResult = pFighterManager->FighterBuy(wFighterID);
    return true;
}

