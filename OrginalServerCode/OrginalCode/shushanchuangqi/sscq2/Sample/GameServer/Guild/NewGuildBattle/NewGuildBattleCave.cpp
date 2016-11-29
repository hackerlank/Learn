// =====================================================================================
//
//       Filename:  NewGuildBattleCave.cpp
//
//    Description:  新帮派战洞府
//
//        Version:  1.0
//        Created:  03/20/2015 10:11:42 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "NewGuildBattleCave.h"

#include "NewGuildBattleCaveCore.h"
#include "NewGuildBattleConfig.h"
#include "NewGuildBattleMgr.h"
#include "NewGuildBattlePlayer.h"
#include "NewGuildBattleMountain.h"
#include "NewGuildBattleRank.h"

#include "NewGuildBattleProtS.h"

#include "Battle.h"
#include "GUIDMgr.h"
#include "Player.h"
#include "HeroFighter.h"
#include "Parameter.h"
#include "RTime.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "Skill.h"
#include "MapMgr.h"
#include "GameNetMgr.h"

namespace NNewGuildBattle
{

// ===  FUNCTION  ======================================================================
//         Name:  CCave
//  Description:  构造函数
// =====================================================================================
CCave::CCave (CMountainPtr pMountain):
    _pMountain(pMountain),
    _qwDefenderID(0), _dwNextResCalcTime(0), _qwWinnerID(0)
{
}		// -----  end of function CCave  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CCave
//  Description:  析构函数
// =====================================================================================
CCave::~CCave ()
{
}		// -----  end of function ~CCave  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetMountain
//  Description:  获取灵山
// =====================================================================================
CMountainPtr CCave::GetMountain () const
{
    return _pMountain.lock();
}		// -----  end of function GetMountain  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRemainTime
//  Description:  获取开始前倒计时
// =====================================================================================
UINT32 CCave::GetRemainTime () const
{
    time_t tNow = Time::Now();
    if (tNow < _dwStartRemainTime)
        return _dwStartRemainTime - tNow;
    else
        return 0;
}		// -----  end of function GetRemainTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetDefenderID
//  Description:  获取防守帮派ID
// =====================================================================================
UINT64 CCave::GetDefenderID () const
{
    return _qwDefenderID;
}		// -----  end of function GetDefenderID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllAttackGuildID
//  Description:  获取攻击帮派ID
// =====================================================================================
void CCave::GetAllAttackGuildID (TVecUINT64& rvecGuildID) const
{
    rvecGuildID.insert(rvecGuildID.end(), _vecAttackGuildID.begin(), _vecAttackGuildID.end());
}		// -----  end of function GetAllAttackGuildID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetWinnerID
//  Description:  获取占领者帮派ID
// =====================================================================================
UINT64 CCave::GetWinnerID () const
{
    return _qwWinnerID;
}		// -----  end of function GetWinnerID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayer
//  Description:  获取玩家
// =====================================================================================
CPlayerPtr CCave::GetPlayer (UINT64 qwRoleID) const
{
    auto it = _mapAllPlayer.find(qwRoleID);
    if (it == _mapAllPlayer.end())
        return NULL;
    return it->second;
}		// -----  end of function GetPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllPlayerID
//  Description:  获取所有玩家的ID
// =====================================================================================
void CCave::GetAllPlayerID (TVecUINT64& rvecRoleID) const
{
    for (auto & rPair : _mapAllPlayer)
    {
        if (rPair.second && rPair.second->GetMountain() == GetMountain()->GetType())
            rvecRoleID.push_back(rPair.first);
    }
}		// -----  end of function GetAllPlayerID  ----- //
// ===  FUNCTION  ======================================================================
//         Name:  PlayerNotify
//  Description:  通知玩家信息
// =====================================================================================
void CCave::PlayerNotify (UINT64 qwRoleID) const
{
    SCaveInfo sInfo;
    if (GetAllInfo(sInfo, qwRoleID))
    {
        string strPkg = g_NewGuildBattleProtS.BuildPkg_CaveInfoNotify(sInfo);
        if (qwRoleID)
            NetMgr.GetGateHandler()->SendClt(&qwRoleID, 1, &strPkg[0], (UINT32)strPkg.size());
        else
            NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());
    }
}		// -----  end of function PlayerNotify  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllInfo
//  Description:  获取所有信息
// =====================================================================================
bool  CCave::GetAllInfo (SCaveInfo& rInfo, UINT64 qwRoleID /* = 0 */) const
{
	rInfo.dwRemainTime = GetRemainTime(); //开始倒计时

    for (auto & rPair : _mapCorePtr)
    {
        if (!rPair.second)
            continue;
        SCaveCoreInfo sInfo;
        rPair.second->GetAllInfo(sInfo);
        rInfo.vecCaveCoreInfo.push_back(sInfo);
    }

    auto it = _vecAttackGuildID.begin();
    auto it2 = _vecAttackGuildName.begin();
    while(it != _vecAttackGuildID.end() && it2 != _vecAttackGuildName.end())
    {

        SCaveAttackGuildInfo sInfo;
        sInfo.qwGuildID     = *it;
        sInfo.strName       = *it2;
        sInfo.dwMaxEnergy   = CConfigMgr::Instance().GetCaveCoreMaxRes();
        auto it3 = _mapGuildRes.find(*it);
        if (it3 != _mapGuildRes.end())
            sInfo.dwEnergy = it3->second;

        rInfo.vecCaveAttackGuildInfo.push_back(sInfo); //洞府攻击帮派信息
        ++it;
        ++it2;
    }


    UINT64 qwGuildID = 0;
    CPlayerPtr pPlayer = GetPlayer(qwRoleID);
    if (pPlayer)
    {
        GetPlayerInfo(rInfo, pPlayer);
        qwGuildID = pPlayer->GetGuildID();
    }

    GetOthersInfo(rInfo.vecPlayerInfo, qwGuildID);
    return true;
}		// -----  end of function GetAllInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  StartBattle
//  Description:  开始洞府战
// =====================================================================================
bool CCave::StartBattle (UINT64 qwGuildID, 
        const TVecUINT64& rvecAttackGuildID, const TVecString& rvecAttackGuildName,
        const TVecUINT64& rvecRoleID)
{
    for (UINT8 byIndex = eNGBCCNone + 1; byIndex < eNGBCCMax; ++ byIndex)
    {
        ENGBCaveCore eCaveCoreType = static_cast<ENGBCaveCore>(byIndex);
        CCaveCorePtr pCaveCore (new CCaveCore(eCaveCoreType));
        if (!pCaveCore)
            LOG_CRI << "Error when new CCaveCore.";
        _mapCorePtr[eCaveCoreType] = pCaveCore;
    }
    _qwDefenderID = qwGuildID;
    _vecAttackGuildID = rvecAttackGuildID;
    _vecAttackGuildName = rvecAttackGuildName;
    _dwStartRemainTime = Time::Now() + SParamConfig::wLingMountainWarReadyTime;
    _dwNextResCalcTime = _dwStartRemainTime + CConfigMgr::Instance().GetResCalcTime();

    for (auto & rID : rvecRoleID)
    {
        CPlayerPtr pPlayer = CBattleMgr::Instance().GetPlayer(rID);
        if (!pPlayer)
            continue;
        if (pPlayer->GetMountain() != GetMountain()->GetType())
            continue;
        _mapAllPlayer[rID] = pPlayer;
    }
    return true;
}		// -----  end of function StartBattle  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  EndBattle
//  Description:  结束洞府战
// =====================================================================================
void CCave::EndBattle (bool bTimeOver, UINT64 qwWinnerID)
{
    CalcFinalWinner(bTimeOver, qwWinnerID);
    NotifyWinner();
    KickAllPlayer();
}		// -----  end of function EndBattle  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  BattleProcess
//  Description:  战斗进行
// =====================================================================================
void CCave::BattleProcess (time_t tNow)
{
    if (tNow < _dwStartRemainTime)
        return;

    if (tNow >= _dwNextResCalcTime)
    {
        // 增加资源
        for (auto & rPair : _mapCorePtr)
        {
            if (!rPair.second)
            {
                LOG_CRI << "No CaveCore :" << static_cast<UINT32>(rPair.first) << ".";
                continue;
            }
            if (!rPair.second->GetOwner())
                continue;
            UINT32 dwRes = 0;
            UINT32 dwScore = 0;
            switch (rPair.second->GetType())
            {
                case eNGBCCDragon: //青龙
                    dwRes = SParamConfig::wLingMountainDragonHonorPerSec;
                    dwScore = SParamConfig::wLingMountainDragonContrPerSec;
                    break;
                case eNGBCCTiger: //白虎
                    dwRes = SParamConfig::wLingMountainTigerHonorPerSec;
                    dwScore = SParamConfig::wLingMountainTigerContrPerSec;
                    break;
                case eNGBCCPhenix: //朱雀
                    dwRes = SParamConfig::wLingMountainBirdHonorPerSec;
                    dwScore = SParamConfig::wLingMountainBirdContrPerSec;
                    break;
                case eNGBCCTurtle: //玄武
                    dwRes = SParamConfig::wLingMountainTortoiseHonorPerSec;
                    dwScore = SParamConfig::wLingMountainTortoiseContrPerSec;
                    break;
                default:
                    break;
            }
            if (rPair.second->GetOwner()->GetGuildID() != _qwDefenderID)
                _mapGuildRes[rPair.second->GetOwner()->GetGuildID()] += dwRes;
            AddPlayerScore(rPair.second->GetOwner(), dwScore);
        }
        NotifyCaveInfo();
        NotifyRankInfo();
        _dwNextResCalcTime += CConfigMgr::Instance().GetResCalcTime();
    }

    NotifyRankInfo();
    CalcFinalWinner(false, 0);
}		// -----  end of function BattleProcess  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerEnter
//  Description:  玩家进入帮派战
// =====================================================================================
ENGBEnterResult CCave::PlayerEnter (CPlayerPtr pPlayer)
{
    ENGBEnterResult eResult = eNGBERFailed;
    if (!pPlayer)
        return eResult;
    bool bGuildValid = false;
    for (auto & rID : _vecAttackGuildID)
    {
        if (rID == pPlayer->GetGuildID())
        {
            bGuildValid = true;
            break;
        }
    }
    if (!bGuildValid)
    {
        if (_qwDefenderID != pPlayer->GetGuildID())
        {
            eResult = eNGBERGuildWrong;
            return eResult;
        }
    }

    if (pPlayer->GetMountain() != eNGBMNone)
    {
        eResult = eNGBERRepeat;
        return eResult;
    }
    _mapAllPlayer[pPlayer->GetRoleID()] = pPlayer;

    pPlayer->SetMountain(GetMountain()->GetType(), 
            pPlayer->GetGuildID() == _qwDefenderID ? eNGBSideDefencer : eNGBSideAttacker);

    return eNGBERSuccess;
}		// -----  end of function PlayerEnter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerQuit
//  Description:  玩家退出
// =====================================================================================
ENGBQuitResult CCave::PlayerQuit (CPlayerPtr pPlayer)
{
    ENGBQuitResult eResult = eNGBQuitFailed;
    if (!pPlayer)
        return eResult;
    UINT64 qwRoleID = pPlayer->GetRoleID();
    auto it = _mapAllPlayer.find(qwRoleID);
    if (it == _mapAllPlayer.end())
        return eResult;
    _mapAllPlayer.erase(it);
    pPlayer->SetMountain(eNGBMNone, eNGBSideInvalid);
    for (auto & rPair : _mapCorePtr)
    {
        if (rPair.second && rPair.second->GetOwner() 
                && rPair.second->GetOwner()->GetRoleID() == qwRoleID)
            rPair.second->SetOwner(NULL);
    }
    eResult = eNGBQuitSuccess;
    if (pPlayer->GetPlayer())
        pPlayer->GetPlayer()->AddBuff(23);
    return eResult;
}		// -----  end of function PlayerQuit  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerAttack
//  Description:  玩家攻击
// =====================================================================================
ENGBCaveAttackResult CCave::PlayerAttack (CPlayerPtr pPlayer, UINT64 qwRoleID)
{
    if (!pPlayer && !qwRoleID)
        return eNGBCARFailed;
    if (GetRemainTime())
    {
        ::CPlayerPtr pPlayer0 = pPlayer->GetPlayer();
        if (pPlayer0)
        {
            string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgLingMountainBattleIsReady);
            pPlayer0->SendPkg(strPkg);
        }
        return eNGBCARWrongTime;
    }
    if (pPlayer->GetDeadTime())
        return eNGBCARSelfIsDead;


    UINT64 qwAttackerID = pPlayer->GetRoleID();
    auto it = _mapAllPlayer.find(qwAttackerID);
    if (it != _mapAllPlayer.end() && it->second)
        pPlayer = it->second;

    CPlayerPtr pTarget;
    it = _mapAllPlayer.find(qwRoleID);
    if (it != _mapAllPlayer.end() && it->second)
    {
        pTarget = it->second;
        if (pTarget && pTarget->GetDeadTime())
            return eNGBCARTargetDead;
    }
    if (!pTarget)
        return eNGBCARFailed;
    if (pTarget->GetGuildID() == pPlayer->GetGuildID())
        return eNGBCARSelfSide;

    ::CPlayerPtr pPlayerA = pPlayer->GetPlayer();
    ::CPlayerPtr pPlayerB = pTarget->GetPlayer();
    if (!pPlayerA || !pPlayerB)
        return eNGBCARFailed;

    ENGBCaveCore eCoreType = eNGBCCNone;
    for (auto& rPair : _mapCorePtr)
    {
        if (!rPair.second)
            continue;
        CPlayerPtr pPlayerOwner = rPair.second->GetOwner();
        if (pPlayerOwner && pPlayerOwner->GetRoleID() == qwRoleID)
        {
            eCoreType = rPair.first;
            break;
        }
    }

    for (auto& rPair : _mapCorePtr)
    {
        if (!rPair.second)
            continue;
        CPlayerPtr pPlayerOwner = rPair.second->GetOwner();
        if (pPlayerOwner && pPlayerOwner->GetRoleID() == pPlayer->GetRoleID())
            return eNGBCARInCore;
    }


    IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
    if (!pBS)
        return eNGBCARFailed;

    TVecBattleFighterPtr vecBattleFighter;
    TVecBattleFighterPtr vecBattleFighter2;
    pPlayerA->GetBattleFighterList(vecBattleFighter);
    pPlayerB->GetBattleFighterList(vecBattleFighter2);
    TVecUINT32 vecSkill;
    UINT32 dwSkillID = SkillMgr.GetSkillIDQualityLevel(SParamConfig::wLingMountainAllDownSkill);
    vecSkill.push_back(dwSkillID);
    for (auto& pFighter : vecBattleFighter)
    {
        pFighter->PushMoreSkills(vecSkill);
    }
    for (auto& pFighter : vecBattleFighter2)
    {
        pFighter->PushMoreSkills(vecSkill);
    }
    pBS->PutFighters(0, pPlayerA->GetMainFighter()->GetInstID(), pPlayerA->GetLevel(), vecBattleFighter, pPlayerA->GetRoleID(), false);
    pBS->PutFighters(1, pPlayerB->GetMainFighter()->GetInstID(), pPlayerB->GetLevel(), vecBattleFighter2, pPlayerB->GetRoleID(), false);
    IBattleFighterPtr   pScene;
    if (!pScene)
        pScene = CMapMgr::ToBattleFighterWithFighterMapID(SParamConfig::wLingMountainBattleField2);
    if (!pScene)
        pScene = pPlayerA->GetSceneFighter();
    pBS->PutScene(pScene);

    pBS->Start(EBTPlayer);
    
    CPlayerPtr pWinner;
    CPlayerPtr pLoser;

    bool bWin = false;
    switch (pBS->GetFinalWinner())
    {
        case EBResultAttackWin: //攻击方胜利
            {
                if (eCoreType != eNGBCCNone)
                    _mapCorePtr[eCoreType]->SetOwner(pPlayer);

                pTarget->SetDeadTime(SParamConfig::wLingMountainReliveTime);
                AddPlayerScore(pTarget, SParamConfig::wLingMountainFightDefeatHonor);
                AddPlayerScore(pPlayer, SParamConfig::wLingMountainFightWinHonor);
                CBattleMgr::Instance().AddPlayerBattleCount(pPlayer->GetRoleID(), true);
                CBattleMgr::Instance().AddPlayerBattleCount(pTarget->GetRoleID(), false);
                pWinner = pPlayer;
                pLoser = pTarget;
                TVecBattleFighterPtr vecFighters;
                pBS->GetFighterList(0, vecFighters);
                pPlayerA->RecoverFighters(vecFighters);
            }
            bWin = true;
            break;
        case EBResultDefenseWin: //防守方胜利
        default:
            {
                AddPlayerScore(pTarget, SParamConfig::wLingMountainFightWinHonor);
                AddPlayerScore(pPlayer, SParamConfig::wLingMountainFightDefeatHonor);
                pPlayer->SetDeadTime(SParamConfig::wLingMountainReliveTime);
                CBattleMgr::Instance().AddPlayerBattleCount(pTarget->GetRoleID(), true);
                CBattleMgr::Instance().AddPlayerBattleCount(pPlayer->GetRoleID(), false);
                pWinner = pTarget;
                pLoser = pPlayer;
                TVecBattleFighterPtr vecFighters;
                pBS->GetFighterList(1, vecFighters);
                pPlayerB->RecoverFighters(vecFighters);
            }
            bWin = false;
    }

    std::string strReport;
    pBS->GetReport(strReport);

    std::string strData = g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayerA->GetRoleID(), pPlayerA->GetMainFighter()->GetID());
    pPlayerA->SendPkg(strData);

    strData = g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayerB->GetRoleID(), pPlayerB->GetMainFighter()->GetID());
    pPlayerB->SendPkg(strData);

    NotifyRankInfo();

    pLoser->GetPlayer()->RegenAllHP();

    TVecUINT64 vecRoleID;
    vecRoleID.push_back(pWinner->GetRoleID());
    vecRoleID.push_back(pLoser->GetRoleID());

    // 攻击阵眼
    if (eCoreType != eNGBCCNone)
    {
        TVecString vecString;
        ostringstream strTmp;

        strTmp.str("");
        strTmp << static_cast<UINT32>(pPlayer->GetPlayer()->GetColor());
        vecString.push_back(strTmp.str());
        vecString.push_back(pPlayer->GetName());

        vecString.push_back(_mapCorePtr[eCoreType]->GetName());

        if (!vecRoleID.empty())
        {
            if (bWin)
                g_NewGuildBattleProtS.SendClt_BattleLogNotify((UINT64*)&vecRoleID[0], (UINT16)vecRoleID.size(), eMsgLingMountainCenterAttackWin, vecString);
            else
                g_NewGuildBattleProtS.SendClt_BattleLogNotify((UINT64*)&vecRoleID[0], (UINT16)vecRoleID.size(), eMsgLingMountainCenterAttackLost, vecString);
        }
    }
    //  攻击不在阵眼的玩家
    else 
    {
        TVecString vecString;
        ostringstream strTmp;
        strTmp.str("");
        strTmp << static_cast<UINT32>(pPlayer->GetPlayer()->GetColor());
        vecString.push_back(strTmp.str());
        vecString.push_back(pPlayer->GetName());

        strTmp.str("");
        strTmp << static_cast<UINT32>(pTarget->GetPlayer()->GetColor());
        vecString.push_back(strTmp.str());
        vecString.push_back(pTarget->GetName());

        if (!vecRoleID.empty())
        {
            if (bWin)
                g_NewGuildBattleProtS.SendClt_BattleLogNotify((UINT64*)&vecRoleID[0], (UINT16)vecRoleID.size(), eMsgLingMountainNotCenterAttackWin, vecString);
            else
                g_NewGuildBattleProtS.SendClt_BattleLogNotify((UINT64*)&vecRoleID[0], (UINT16)vecRoleID.size(), eMsgLingMountainNotCenterAttackLost, vecString);
        }
    }

    NotifyCaveInfo();

    return eNGBCARSuccess;
}		// -----  end of function PlayerAttack  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerCapture
//  Description:  玩家占领阵眼
// =====================================================================================
ENGBCaveAttackResult CCave::PlayerCapture (CPlayerPtr pPlayer, ENGBCaveCore eCaveType)
{
    if (!pPlayer)
        return eNGBCARFailed;
    if (GetRemainTime())
        return eNGBCARWrongTime;
    if (pPlayer->GetDeadTime())
        return eNGBCARSelfIsDead;

    UINT64 qwRoleID = pPlayer->GetRoleID();
    auto it = _mapAllPlayer.find(qwRoleID);
    if (it != _mapAllPlayer.end() && it->second)
        pPlayer = it->second;

    auto it2 = _mapCorePtr.find(eCaveType);
    if (it2 == _mapCorePtr.end() || !it2->second)
        return eNGBCARFailed;
    if (it2->second->GetOwner())
        return eNGBCARBeCaptured;

    // 看看自己有占领的阵眼
    ENGBCaveCore eCoreType = eNGBCCNone;
    for (auto& rPair : _mapCorePtr)
    {
        if (!rPair.second)
            continue;
        CPlayerPtr pPlayerOwner = rPair.second->GetOwner();
        if (pPlayerOwner && pPlayerOwner->GetRoleID() == qwRoleID)
        {
            eCoreType = rPair.first;
            break;
        }
    }
    if (eCoreType != eNGBCCNone)
        _mapCorePtr[eCoreType]->SetOwner(NULL);
    _mapCorePtr[eCaveType]->SetOwner(pPlayer);
    {
        TVecString vecString;
        TVecUINT64 vecRoleID;
        for (auto& rPair : _mapAllPlayer)
        {
            if (rPair.second && rPair.second->GetMountain() == GetMountain()->GetType())
                vecRoleID.push_back(rPair.second->GetRoleID());
        }
        ostringstream strTmp;
        strTmp.str("");
        strTmp << static_cast<UINT32>(pPlayer->GetPlayer()->GetColor());
        vecString.push_back(strTmp.str());
        vecString.push_back(pPlayer->GetName());

        vecString.push_back(_mapCorePtr[eCaveType]->GetName());
        if (!vecRoleID.empty())
            g_NewGuildBattleProtS.SendClt_BattleLogNotify((UINT64*)&vecRoleID[0], (UINT16)vecRoleID.size(), eMsgLingMountainCenterAttackWin, vecString);
    }
    return eNGBCARSuccess;

}		// -----  end of function PlayerCapture  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerRest
//  Description:  玩家下阵眼
// =====================================================================================
ENGBCaveAttackResult CCave::PlayerRest (CPlayerPtr pPlayer)
{
    if (!pPlayer)
        return eNGBCARFailed;

    UINT64 qwRoleID = pPlayer->GetRoleID();
    auto it = _mapAllPlayer.find(qwRoleID);
    if (it != _mapAllPlayer.end() && it->second)
        pPlayer = it->second;

    ENGBCaveCore eCoreType = eNGBCCNone;
    for (auto& rPair : _mapCorePtr)
    {
        if (!rPair.second)
            continue;
        CPlayerPtr pPlayerOwner = rPair.second->GetOwner();
        if (pPlayerOwner && pPlayerOwner->GetRoleID() == qwRoleID)
        {
            eCoreType = rPair.first;
            break;
        }
    }
    if (eCoreType != eNGBCCNone)
    {
        _mapCorePtr[eCoreType]->SetOwner(NULL);
        return eNGBCARSuccess;
    }
    else
        return eNGBCARNotInCore;

}		// -----  end of function PlayerRest  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CalcFinalWinner
//  Description:  计算最后获胜的人
// =====================================================================================
void CCave::CalcFinalWinner (bool bTimeOver, UINT64 qwWinnerID)
{
    if (_qwWinnerID)
        return;

    if (bTimeOver && qwWinnerID)
    {
        _qwWinnerID = qwWinnerID;
        return;
    }

    // 检查是否有人占领
    TVecUINT64 vecWinnerGuildID;
    for (auto & rPair : _mapGuildRes)
    {
        if (rPair.second >= CConfigMgr::Instance().GetCaveCoreMaxRes())
            vecWinnerGuildID.push_back(rPair.first);
    }

    if (bTimeOver && !qwWinnerID && vecWinnerGuildID.empty())
    {
        UINT32 dwMaxRes = 0;
        for (auto & rPair : _mapGuildRes)
        {
            if (rPair.second > dwMaxRes)
            {
                dwMaxRes = rPair.second;
                vecWinnerGuildID.clear();
                vecWinnerGuildID.push_back(rPair.first);
            }
            else if (rPair.second == dwMaxRes)
                vecWinnerGuildID.push_back(rPair.first);
        }
        LOG_WRN << "Force calc Winner: ";
        for (auto& rID : vecWinnerGuildID)
        {
            LOG_WRN << rID << ".";
        }
    }

    // 有帮派资源达标，可以占领该据点
    if (!vecWinnerGuildID.empty())
    {
        // 过滤分数不是最高的帮派
        TVecUINT64 vecWinnerGuildID2;
        UINT32 dwMaxScore = 0;
        for (auto & rID : vecWinnerGuildID)
        {
            UINT32 dwScore = CBattleMgr::Instance().GetGuildScore(rID, GetMountain()->GetType());
            if (dwMaxScore < dwScore)
            {
                vecWinnerGuildID2.clear();
                dwMaxScore = dwScore;
                vecWinnerGuildID2.push_back(rID);
            }
            else if (dwMaxScore == dwScore)
                vecWinnerGuildID2.push_back(rID);
        }
        vecWinnerGuildID = vecWinnerGuildID2;

        LOG_WRN << "Force calc Winner2: ";
        for (auto& rID : vecWinnerGuildID)
        {
            LOG_WRN << rID << ".";
        }
    }

    UINT64 qwRoleID = 0;

    // FIXME: 这里默认是从高到低排序的阵眼
    if (!vecWinnerGuildID.empty())
    {
        for (auto & rPair : _mapCorePtr)
        {
            if (!rPair.second)
            {
                LOG_CRI << "_mapCorePtr[" << static_cast<UINT32>(rPair.first) << "] == NULL.";
                continue;
            }
            CPlayerPtr pPlayer = rPair.second->GetOwner();
            if (!pPlayer)
                continue;
            UINT64 qwGuildID = pPlayer->GetGuildID();

            for (auto rID : vecWinnerGuildID)
            {
                if (rID == qwGuildID)
                {
                    _qwWinnerID = qwGuildID;
                    break;
                }
            }

            //保存胜利者

            qwRoleID = pPlayer->GetRoleID();

            if (_qwWinnerID)
                break;
        }
        if (!_qwWinnerID)
            _qwWinnerID = vecWinnerGuildID[0];
        LOG_WRN << "Final Winner: " << _qwWinnerID << ".";
    }

    if(qwRoleID && GetMountain())
    {
        TVecINT32 vecParam;
        vecParam.push_back(GetMountain()->GetType());
        vecParam.push_back(time(NULL));
    {
        ::CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if(pUser)
        {
            ::CPlayerPtr pPlayer =  pUser->GetPlayer();
            if(pPlayer)
            {
                pPlayer->OnEvent(eEventType_LingMountainWin,vecParam);
            }
        }
        else
        {
            ::CPlayer::AddOffLineEvent(qwRoleID,eEventType_LingMountainWin,vecParam);
        }
    }

    }

}		// -----  end of function CalcFinalWinner  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyCaveInfo
//  Description:  广播洞府战信息
// =====================================================================================
void CCave::NotifyCaveInfo () const
{
    SCaveInfo sInfo;
    if (!GetAllInfo(sInfo))
        return;
    for (auto& rPair : _mapAllPlayer)
    {
        if (!rPair.second)
            continue;
        ::CPlayerPtr pPlayer = rPair.second->GetPlayer();
        if (!pPlayer)
            continue;
        GetPlayerInfo(sInfo, rPair.second);
        GetOthersInfo(sInfo.vecPlayerInfo, rPair.second->GetGuildID());
        string strPkg = g_NewGuildBattleProtS.BuildPkg_CaveInfoNotify(sInfo);
        pPlayer->SendPkg(strPkg);
    }
}		// -----  end of function NotifyCaveInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyCaveCoreInfo
//  Description:  广播阵眼信息
// =====================================================================================
void CCave::NotifyCaveCoreInfo () const
{
    TVecCaveCoreInfo vecCoreInfo;
    for (auto & rPair : _mapCorePtr)
    {
        if (!rPair.second)
            continue;
        SCaveCoreInfo sInfo;
        if (rPair.second->GetAllInfo(sInfo))
            vecCoreInfo.push_back(sInfo);
    }
    TVecUINT64 vecRoleID;
    for (auto& rPair : _mapAllPlayer)
    {
        if (rPair.second && rPair.second->GetMountain() == GetMountain()->GetType())
            vecRoleID.push_back(rPair.second->GetRoleID());
    }
    if (!vecRoleID.empty())
        g_NewGuildBattleProtS.SendClt_CaveCoreNotify((UINT64*)&vecRoleID[0], (UINT16)vecRoleID.size(), vecCoreInfo);
}		// -----  end of function NotifyCaveCoreInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyRankInfo
//  Description:  广播排行榜有关数据
// =====================================================================================
void CCave::NotifyRankInfo () const
{
    TVecUINT64 vecRoleID;
    map<UINT64, TVecUINT64> mapVecGuileRoleID;
    for (auto& rPair : _mapAllPlayer)
    {
        if (rPair.second && rPair.second->GetMountain() == GetMountain()->GetType())
        {
            vecRoleID.push_back(rPair.second->GetRoleID());
            mapVecGuileRoleID[rPair.second->GetGuildID()].push_back(rPair.second->GetRoleID());
        }
    }
    if (vecRoleID.empty())
        return;

    CPlayerRankMgrPtr pPlayerRank = CBattleMgr::Instance().GetPlayerRankMgr();
    if (pPlayerRank)
    {
        TVecPlayerRankInfo vecInfo;
        UINT32 dwCurIndex = 0;
        UINT32 dwMaxCount = 0;
        pPlayerRank->GetRankInfo(GetMountain()->GetType(), 1, 7, dwCurIndex, dwMaxCount, vecInfo);
        g_NewGuildBattleProtS.SendClt_PlayerRankInfoNotify((UINT64*)&vecRoleID[0], (UINT16)vecRoleID.size(), dwCurIndex, dwMaxCount, vecInfo);

    }

    CGuildMemberRankMgrPtr pGuildMemberRank = CBattleMgr::Instance().GetGuildMemberRankMgr();
    if (pGuildMemberRank)
    {
        for (auto & rPair : mapVecGuileRoleID)
        {
            if (rPair.second.empty())
                continue;
            NNewGuildBattleProt::TVecGuildMemberRankInfo vecInfo;
            UINT32 dwCurIndex = 0;
            UINT32 dwMaxCount = 0;
            pGuildMemberRank->GetRankInfo(GetMountain()->GetType(), rPair.first, 1, 7, dwCurIndex, dwMaxCount, vecInfo);
            g_NewGuildBattleProtS.SendClt_GuildMemberRankInfoNotify((UINT64*)&rPair.second[0], (UINT16)rPair.second.size(), dwCurIndex, dwMaxCount, vecInfo);
        }
    }

    CGuildRankMgrPtr pGuildRank = CBattleMgr::Instance().GetGuildRankMgr();
    if (pGuildRank)
    {
        NNewGuildBattleProt::TVecGuildRankInfo vecInfo;
        UINT32 dwCurIndex = 0;
        UINT32 dwMaxCount = 0;
        pGuildRank->GetRankInfo(GetMountain()->GetType(), 1, 7, dwCurIndex, dwMaxCount, vecInfo);
        g_NewGuildBattleProtS.SendClt_GuildRankInfoNotify((UINT64*)&vecRoleID[0], (UINT16)vecRoleID.size(), dwCurIndex, dwMaxCount, vecInfo);

    }
}		// -----  end of function NotifyRankInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyWinner
//  Description:  广播占领消息
// =====================================================================================
void CCave::NotifyWinner () const
{
    // 已经占领
    if (_qwWinnerID)
    {
        string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgLingMountainEnd);
        NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());

        TVecUINT64 vecRoleID;
        for (auto& rPair : _mapAllPlayer)
        {
            if (rPair.second && rPair.second->GetMountain() == GetMountain()->GetType())
                vecRoleID.push_back(rPair.second->GetRoleID());
        }
        // if (!vecRoleID.empty())
        // {
        //     TVecString vecString;
        //     vecString.push_back(GetMountain()->GetName());
        //     vecString.push_back(CBattleMgr::Instance().GetGuildName(_qwWinnerID));
        //     g_ChatProtS.SendClt_SystemFormatMsgIDNotify((UINT64*)&vecRoleID[0], (UINT16)vecRoleID.size(), eMsgLingMountainSeize, vecString);
        // }
    }
}		// -----  end of function NotifyWinner  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayerInfo
//  Description:  获取玩家信息
// =====================================================================================
void CCave::GetPlayerInfo (SCaveInfo& rInfo, CPlayerPtr pPlayer) const
{
    if (!pPlayer)
        return;
    pPlayer->GetAllInfo(rInfo.sSelfInfo);

    rInfo.eSelfSide = pPlayer->GetSide();
}		// -----  end of function GetPlayerInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetOthersInfo
//  Description:  获取其他人呢的面板信息
// =====================================================================================
void CCave::GetOthersInfo (TVecPlayerPanelInfo& rvecInfo, UINT64 qwGuildID) const
{
    rvecInfo.clear();
    for (auto & rPair : _mapAllPlayer)
    {
        if (rPair.second && rPair.second->GetGuildID() != qwGuildID)
        {
            SPlayerPanelInfo sInfo;
            if( rPair.second->GetAllPanelInfo(sInfo))
                rvecInfo.push_back(sInfo);
        }
    }
}		// -----  end of function GetOthersInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddPlayerScore
//  Description:  增加玩家的战功
// =====================================================================================
void CCave::AddPlayerScore (CPlayerPtr pPlayer, UINT32 dwScore)
{
    if (!pPlayer)
        return;
    pPlayer->AddScore(GetMountain()->GetType(), dwScore);

    CPlayerRankMgrPtr pPlayerRank = CBattleMgr::Instance().GetPlayerRankMgr();
    if (pPlayerRank)
        pPlayerRank->AddPlayerScore(GetMountain()->GetType(), pPlayer->GetRoleID(), pPlayer->GetName(), dwScore);

    CGuildMemberRankMgrPtr pGuildMemberRank = CBattleMgr::Instance().GetGuildMemberRankMgr();
    if (pGuildMemberRank)
        pGuildMemberRank->AddGuildMemberScore(GetMountain()->GetType(), pPlayer->GetGuildID(), pPlayer->GetRoleID(), pPlayer->GetName(), dwScore);

    CGuildRankMgrPtr pGuildRank = CBattleMgr::Instance().GetGuildRankMgr();
    if (pGuildRank)
        pGuildRank->AddGuildScore(GetMountain()->GetType(), pPlayer->GetGuildID(), pPlayer->GetGuildName(), dwScore);

}		// -----  end of function SyncPlayerScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  KickAllPlayer
//  Description:  踢出所有参战玩家
// =====================================================================================
void CCave::KickAllPlayer ()
{
    for (auto& rPair : _mapAllPlayer)
    {
        if (!rPair.second)
            continue;
        rPair.second->SetMountain(eNGBMNone, eNGBSideInvalid);
    }
}		// -----  end of function KickAllPlayer  ----- //
} // namespace NNewGuildBattle
