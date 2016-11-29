
#include "stdafx.h"
#include "Protocols.h"
#include "FormationProtS.h"
#include "UserMgr.h"
#include "FighterManager.h"
#include "Player.h"
#include "FormationPet.h"
#include "SysMsgDefine.h"
#include "GameNetMgr.h"

void SystemMsg(EFormPetType& eResult);

//接收：上阵/下阵
bool CFormationProtS::OnRecv_FormationUp(
        UINT64 qwInstID, //散仙唯一ID
        INT32 iPos, //目标位置: [0-8]为上阵 <0时为下阵
        shared_func<SFormationUpAck>& fnAck //返回回调函数
        )
{
    //XXX 暂时取消了，注意！！
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eFormPetFalied;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eFormPetFalied;
        return false;
    }

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eFormPetFalied;
        return false;
    }

    CFighterPtr pFighter = pFighterManager->GetFighterByInstID(qwInstID);
    if (!pFighter)
    {
        fnAck->eResult = eFormPetFalied;
        return false;
    }

    if (pFighterManager->GetFormation().PutInto(iPos,pFighter))
    {
        pFighter->SetDirty(true);
        pFighterManager->ResetCombinationSkill();
        fnAck->eResult = eFormPetSucc;
    }
    else
        fnAck->eResult = eFormPetFalied;
    return true;
}

//接收：设置阵形
bool CFormationProtS::OnRecv_SetFormation(
        const TVecSLineup& vecSLineup, //阵形列表
        shared_func<SSetFormationAck>& fnAck //返回回调函数
        )
{

    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        return false;
    }

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        return false;
    }

    if (!vecSLineup.size())
    {
        fnAck->bRet = false;
        return false;
    }


    TVecINT32 vecParamFormation;
    TVecLineup vecLineup;
    for (size_t i = 0;i < vecSLineup.size(); ++i)
    {
        CFighterPtr pFighter = pFighterManager->GetFighterByInstID(vecSLineup[i].qwInstID);
        if (!pFighter)
        {
            fnAck->bRet = false;
            return false;
        }
        pFighter->SetDirty(true);
        vecLineup.push_back(Lineup(pFighter, vecSLineup[i].iPos));

        vecParamFormation.push_back(pFighter->GetID());
        vecParamFormation.push_back(vecSLineup[i].iPos);
    }


    fnAck->bRet = pFighterManager->GetFormation().SetFomation(vecLineup);
    if(fnAck->bRet && vecLineup.size() > 0)
    {
        pUser->GetTaskPkg().OnAction(*pPlayer,eProcessAction_FighterWork);
        pUser->GetTaskPkg().OnAction(*pPlayer,eProcessAction_SpecialFighterWork);

        TVecINT32 vecParam;
        vecParam.push_back(vecLineup.size());
        pPlayer->OnEvent(eEventType_FighterInBattle,vecParam);

        pPlayer->OnEvent(eEventType_FormationChangeMore,vecParamFormation);
    }

    pFighterManager->ResetCombinationSkill();

    return true;
}

//接收：取得所有阵灵信息
bool CFormationProtS::OnRecv_PetsGet(
        shared_func<SPetsGetAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;

    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
        return false;

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
        return false;

    //pFighterManager->GetFormationPet().GetPetSlots().GetRolePet(fnAck->sRolePetInfo);
    pFighterManager->GetFormationPet().GetPetSlots().GetAllPets(fnAck->vecPets);
    return true;
}

//接收：激活阵灵
bool CFormationProtS::OnRecv_PetsActive(
        UINT16 wPetID, //阵灵ID
        shared_func<SPetsActiveAck>& fnAck //返回回调函数
        )
{
    fnAck->eResult = eFormPetFalied;
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;

    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
        return false;

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
        return false;

    CPetPtr pPet = pFighterManager->GetFormationPet().GetPetSlots().AdoptPet(wPetID);
    if (pPet)
        fnAck->eResult = eFormPetSucc;
    return true;
}

//接收：设置阵灵状态
bool CFormationProtS::OnRecv_PetsStatus(
        UINT16 wPetID, //阵灵ID
        UINT8 byType, //状态: 1-出战且显示 2-出战隐藏
        shared_func<SPetsStatusAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;

    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
        return false;

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
        return false;

    bool bRet = pFighterManager->GetFormationPet().GetPetSlots().ActivePet(wPetID, byType);
    if (bRet)
        fnAck->eResult = eFormPetSucc;
    else
        fnAck->eResult = eFormPetFalied;
    return bRet;
}

//接收：阵灵幻化
bool CFormationProtS::OnRecv_PetsUpgrade(
        UINT16 wPetID, //阵灵ID
        shared_func<SPetsUpgradeAck>& fnAck //返回回调函数
        )
{
    return true;
}

//接收：阵灵升级
bool CFormationProtS::OnRecv_PetsLevelUp(
        UINT16 wPetID, //阵灵ID
        UINT8 byType, //状态: 1-出战且显示 2-出战隐藏
        shared_func<SPetsLevelUpAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eFormPetFalied;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eFormPetFalied;
        return false;
    }

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eFormPetFalied;
        return false;
    }

    fnAck->eResult = pFighterManager->GetFormationPet().GetPetSlots().PetLevelUp(wPetID);
    SystemMsg(fnAck->eResult);
    return true;
}

//接收：阵灵一键升级
bool CFormationProtS::OnRecv_QuickPetsLevelUp(
        UINT16 wPetID, //阵灵ID
        shared_func<SQuickPetsLevelUpAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eFormPetFalied;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eFormPetFalied;
        return false;
    }

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eFormPetFalied;
        return false;
    }

    fnAck->eResult = pFighterManager->GetFormationPet().GetPetSlots().QuickPetLevelUp(wPetID);
    SystemMsg(fnAck->eResult);
    return true;
}

//接收：获取兽魂信息
bool CFormationProtS::OnRecv_GetBeastSoul(
        shared_func<SGetBeastSoulAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eBeastSoulFailed;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eBeastSoulFailed;
        return false;
    }

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eBeastSoulFailed;
        return false;
    }

    fnAck->eResult = pFighterManager->GetFormationPet().GetBeastSoul().GetAllInfo(fnAck->vecBeastSoul);
    return true;
}

//接收：升级兽魂
bool CFormationProtS::OnRecv_UpgradeBeastSoul(
        NRoleInfoDefine::EBeastSoulType eType, //兽魂种类
        shared_func<SUpgradeBeastSoulAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eBeastSoulFailed;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        fnAck->eResult = eBeastSoulFailed;
        return false;
    }
    if (pPlayer->GetLevel() < SParamConfig::wShouHunOpenLevel)
    {
        fnAck->eResult = eBeastSoulLevelLimit;
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgShouHunNotOpen);
        pPlayer->SendPkg(strPkg);
        return false;
    }

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eBeastSoulFailed;
        return false;
    }
    fnAck->eResult = pFighterManager->GetFormationPet().GetBeastSoul().UpgradeBeastSoul(eType, fnAck->vecItem);
    if (fnAck->eResult == eBeastSoulSucces)
        pFighterManager->GetFormationPet().GetBeastSoul().GetAllInfo(fnAck->vecBeastSoul);
    return true;
}

void SystemMsg(EFormPetType& eResult)
{
    ESystemMsgID eMsgID = eMsgOtherErr;
    switch (eResult)
    {
        case eFormPetItemErr:
            eMsgID = eMsgFormPetItemErr;
            break;
        case eFormPetPetLevelItemErr:
            break;
        default:
            return;
    }
    g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

