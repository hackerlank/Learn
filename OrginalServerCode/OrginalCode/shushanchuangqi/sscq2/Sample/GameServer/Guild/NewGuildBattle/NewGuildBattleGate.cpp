// =====================================================================================
//
//       Filename:  NewGuildBattleGate.cpp
//
//    Description:  新帮派战城门
//
//        Version:  1.0
//        Created:  03/20/2015 10:10:38 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "NewGuildBattleGate.h"

#include "NewGuildBattlePuppet.h"
#include "NewGuildBattlePlayer.h"
#include "NewGuildBattleRank.h"
#include "NewGuildBattleMgr.h"
#include "NewGuildBattleMountain.h"

#include "NewGuildBattleProtS.h"

#include "RTime.h"
#include "Player.h"
#include "HeroFighter.h"
#include "Monster.h"
#include "MonsterMgr.h"
#include "Protocols.h"
#include "Parameter.h"
#include "SysMsgDefine.h"
#include "MapMgr.h"
#include "GUIDMgr.h"
#include "GameNetMgr.h"

namespace NNewGuildBattle
{
// ===  FUNCTION  ======================================================================
//         Name:  CGate
//  Description:  构造函数
// =====================================================================================
CGate::CGate (CMountainPtr pMountain):
    _pMountain(pMountain),
    _qwDefenderID(0), _dwGateMaxHP(0), _dwGateHP(0), _dwGateAttack(0)
{
    if (pMountain)
        _qwDefenderID = pMountain->GetGuildID();

    UINT32 dwEnemyID = 20050;
    TVecBattleFighterPtr vecBattleFighter;
    vector<TVecBattleFighterPtr> vecvecBattleFighter2;
    UINT64 qwTmpInstID =  1;
    qwTmpInstID = CMonster::GetBattleFighterListByGroupID(vecvecBattleFighter2, dwEnemyID, qwTmpInstID, vecBattleFighter);
    if (!vecvecBattleFighter2.empty())
    {
        for (auto & pFighter : vecvecBattleFighter2[0])
        {
            _dwGateMaxHP += pFighter->GetMaxHP();
        }
    }
    _dwGateAttack = 50000;

    if (_pMountain.lock())
    {
        UINT16 wHPID = 0;
        UINT16 wAttackID = 0;
        switch(_pMountain.lock()->GetType())
        {
            case eNGBMEMei: //峨眉
                wHPID = NVarDefine::eSystemVar_NewGuildBattleGate1HP;
                wAttackID = NVarDefine::eSystemVar_NewGuildBattleGate1Attack;
                break;
            case eNGBMKunLun: //昆仑
                wHPID = NVarDefine::eSystemVar_NewGuildBattleGate2HP;
                wAttackID = NVarDefine::eSystemVar_NewGuildBattleGate2Attack;
                break;
            case eNGBMHuangShan: //黄山
                wHPID = NVarDefine::eSystemVar_NewGuildBattleGate3HP;
                wAttackID = NVarDefine::eSystemVar_NewGuildBattleGate3Attack;
                break;
            default:
                break;
        }
        if (wHPID && wAttackID)
        {
            TVecUINT16 vecID;
            vecID.push_back(wHPID);
            vecID.push_back(wAttackID);
            g_Game2CenterCommC.Send_GetSystemVar(vecID,
                    [this, wHPID, wAttackID]
                    (
                     UINT8 byRet_, //0为成功，1为失败，2为超时
                     const TVecUINT16& vecVars, //(返回值)varID列表
                     const TVecUINT64& vecValues //(返回值)var数值列表(必须与vecVars对应)
                    )
            {
                if (!byRet_)
                {
                    size_t szCount = vecVars.size();
                    if (vecVars.size() > vecValues.size())
                    {
                        LOG_CRI << "vecVars.size() = " << vecVars.size() << ", vecValues.size() = " << vecValues.size() << ".";
                        szCount = vecValues.size();
                    }
                    for (size_t szIndex = 0; szIndex < szCount; ++szIndex)
                    {
                        if (vecVars[szIndex] == wHPID && vecValues[szIndex] > _dwGateMaxHP)
                        {
                            _dwGateMaxHP = vecValues[szIndex];
                            _dwGateHP = _dwGateMaxHP;
                        }
                        if (vecVars[szIndex] == wAttackID && vecValues[szIndex] > _dwGateAttack)
                            _dwGateAttack = vecValues[szIndex];
                    }
                }
#ifdef _DEBUG
                LOG_INF << GetMountain()->GetName() << " HP: " << _dwGateHP << ", Attack " << _dwGateAttack << ".";
#endif
            });
        }
    }
    _dwGateHP = _dwGateMaxHP;
#ifdef _DEBUG
    LOG_INF << GetMountain()->GetName() << " HP: " << _dwGateHP << ", Attack " << _dwGateAttack << ".";
#endif
}		// -----  end of function CGate  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CGate
//  Description:  析构函数
// =====================================================================================
CGate::~CGate ()
{
}		// -----  end of function ~CGate  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetMountain
//  Description:  获取灵山
// =====================================================================================
CMountainPtr CGate::GetMountain () const
{
    return _pMountain.lock();
}		// -----  end of function GetMountain  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetStartRemainTime
//  Description:  获取
// =====================================================================================
UINT32 CGate::GetStartRemainTime () const
{
    time_t tNow = Time::Now();
    if (tNow < _dwStartRemainTime)
        return _dwStartRemainTime - tNow;
    else
        return 0;
}		// -----  end of function GetStartRemainTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetDefenderID
//  Description:  获取防守帮派ID
// =====================================================================================
UINT64 CGate::GetDefenderID () const
{
    return _qwDefenderID;
}		// -----  end of function GetDefenderID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGateMaxHP
//  Description:  获取城门血量最大值
// =====================================================================================
UINT32 CGate::GetGateMaxHP () const
{
    return _dwGateMaxHP;
}		// -----  end of function GetGateMaxHP  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGateHP
//  Description:  获取城门血量
// =====================================================================================
UINT32 CGate::GetGateHP () const
{
    return _dwGateHP;
}		// -----  end of function GetGateHP  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  IsBroken
//  Description:  城门是否已经攻破
// =====================================================================================
bool  CGate::IsBroken () const
{
    return _dwGateHP ? false : true;
}		// -----  end of function IsBroken  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildAndPlayer
//  Description:  获取攻击帮派ID
// =====================================================================================
void CGate::GetGuildAndPlayer (TVecUINT64& rvecGuildID, TVecString& rvecGuildName,
        TVecUINT64& rvecRoleID) const
{
    rvecGuildID.insert(rvecGuildID.end(), _vecWinnerGuildID.begin(), _vecWinnerGuildID.end());
    rvecGuildName.insert(rvecGuildName.end(), _vecWinnerGuildName.begin(), _vecWinnerGuildName.end());

    for (auto & rPair : _mapAllAttackPlayer)
    {
        if (rPair.second && rPair.second->GetMountain() == GetMountain()->GetType())
            rvecRoleID.push_back(rPair.first);
    }

    for (auto & rPair : _mapAllDefendPlayer)
    {
        if (rPair.second && rPair.second->GetMountain() == GetMountain()->GetType())
            rvecRoleID.push_back(rPair.first);
    }
}		// -----  end of function GetGuildAndPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayer
//  Description:  获取参战人员
// =====================================================================================
CPlayerPtr CGate::GetPlayer (UINT64 qwRoleID, ENGBSide& eSide) const
{
    auto it = _mapAllAttackPlayer.find(qwRoleID);
    if (it != _mapAllAttackPlayer.end())
    {
        eSide = eNGBSideAttacker;
        return it->second;
    }

    it = _mapAllDefendPlayer.find(qwRoleID);
    if (it != _mapAllDefendPlayer.end())
    {
        eSide = eNGBSideDefencer;
        return it->second;
    }
    eSide = eNGBSideInvalid;
    return NULL;
}		// -----  end of function GetPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerNotify
//  Description:  玩家消息通知
// =====================================================================================
void CGate::PlayerNotify (UINT64 qwRoleID) const
{
    SMountainGateInfo sInfo;
    if (GetAllInfo(sInfo, qwRoleID))
    {
        string strPkg = g_NewGuildBattleProtS.BuildPkg_GateInfoNotify(sInfo);
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
bool CGate::GetAllInfo (SMountainGateInfo& rInfo, UINT64 qwRoleID /* = 0 */) const
{
	rInfo.dwRemainTime      = GetStartRemainTime(); //开始倒计时
	rInfo.dwGateMaxHP       = GetGateMaxHP();       //城门总血量
	rInfo.dwGateHP          = GetGateHP();          //城门剩余血量

    GetPuppetInfo(rInfo.vecPuppetInfo);

    GetPlayerInfo(rInfo, qwRoleID);
    return true;
}		// -----  end of function GetAllInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetGateHP
//  Description:  设置城门血量
// =====================================================================================
void CGate::SetGateHP (UINT32 dwHP)
{
    _dwGateHP = dwHP;
    if (_dwGateMaxHP < _dwGateHP)
        _dwGateMaxHP = _dwGateHP;
}		// -----  end of function SetGateHP  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetGateMaxHP
//  Description:  设置城门血量
// =====================================================================================
void CGate::SetGateMaxHP (UINT32 dwMaxHP)
{
    _dwGateMaxHP = dwMaxHP;
    if (_dwGateHP > _dwGateMaxHP)
        _dwGateHP = _dwGateMaxHP;
}		// -----  end of function SetGateMaxHP  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  StartBattle
//  Description:  开始城门战
// =====================================================================================
bool  CGate::StartBattle (UINT64 qwGuildID)
{
    time_t tNow = Time::Now();
    _dwStartRemainTime = tNow + SParamConfig::wLingMountainWarReadyTime;
    _qwDefenderID = qwGuildID;
    _pPuppet = NULL;
    _pPuppet.reset(new CPuppet);
    _pPuppet->SetNextAttackTime(_dwStartRemainTime);
    _pPuppet->CalcNextAttackTime();
    return true;
}		// -----  end of function StartBattle  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  EndBattle
//  Description:  结束城门战
// =====================================================================================
void CGate::EndBattle (bool bTimeOver)
{
    StopAllPuppets();
    if (!bTimeOver)
    {
        ReliveAllPlayers();
        CalcFinalWinner();
        NotifyBroken();
        ClearInvalidPlayers();
    }
}		// -----  end of function EndBattle  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CalcFinalWinner
//  Description:  计算最后获胜者
// =====================================================================================
UINT8 CGate::CalcFinalWinner ()
{
    set<SGuildScore>        setGuildScore;

    time_t tNow = Time::Now();
    for (auto & rPair : _mapGuildScore)
    {
        if (rPair.first == _qwDefenderID)
            continue;
        UINT32 dwTime = tNow;
        auto it = _mapGuildScoreTime.find(rPair.first);
        if (it != _mapGuildScoreTime.end())
            dwTime = it->second;
        string strGuildName = CBattleMgr::Instance().GetGuildName(rPair.first);
        SGuildScore sInfo(rPair.first, strGuildName, rPair.second, dwTime);
        setGuildScore.insert(sInfo);
    }

    UINT32 dwCount = 0;
    for (auto& rInfo : setGuildScore)
    {
        _vecWinnerGuildID.push_back(rInfo._qwGuildID);
        _vecWinnerGuildName.push_back(rInfo._strName);
        if (++dwCount >= 4)
            break;
    }
    return dwCount;

}		// -----  end of function CalcFinalWinner  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ClearInvalidPlayers
//  Description:  清除无效的玩家
// =====================================================================================
void CGate::ClearInvalidPlayers ()
{
    TSetUINT64 setGuildID;
    for (auto & rID : _vecWinnerGuildID)
    {
        setGuildID.insert(rID);
    }

    TVecUINT64 vecRoleWinner;
    TVecUINT64 vecRoleLoser;
    TVecUINT64 vecRoleDefencer;
    for (auto it = _mapAllAttackPlayer.begin(); it != _mapAllAttackPlayer.end();)
    {
        if (it->second)
        {
            auto it0 = setGuildID.find(it->second->GetGuildID());
            if (it0 != setGuildID.end())
            {
                ++it;
                vecRoleWinner.push_back(it->first);
                continue;
            }
            it->second->SetMountain(eNGBMNone, eNGBSideInvalid);
        }
        vecRoleLoser.push_back(it->first);
        _mapAllAttackPlayer.erase(it++);
    }
    if (!vecRoleWinner.empty())
    {
        string strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgLingMountainDoorEndJoin, BuildStrVec(GetMountain()->GetName()));
        NetMgr.GetGateHandler()->SendClt(vecRoleWinner.data(), vecRoleWinner.size(), &strPkg[0], (UINT32)strPkg.size());
    }

    if (!vecRoleLoser.empty())
    {
        string strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgLingMountainDoorEndNotJoin, BuildStrVec(GetMountain()->GetName()));
        NetMgr.GetGateHandler()->SendClt(vecRoleLoser.data(), vecRoleLoser.size(), &strPkg[0], (UINT32)strPkg.size());
    }

    for (auto & rPair : _mapAllDefendPlayer)
    {
        vecRoleDefencer.push_back(rPair.first);
    }
    if (!vecRoleDefencer.empty())
    {
        string strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgLingMountainDoorDefence, BuildStrVec(GetMountain()->GetName()));
        NetMgr.GetGateHandler()->SendClt(vecRoleDefencer.data(), vecRoleDefencer.size(), &strPkg[0], (UINT32)strPkg.size());
    }
}		// -----  end of function ClearInvalidPlayers  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  StopAllPuppets
//  Description:  停止所有战争傀儡
// =====================================================================================
void CGate::StopAllPuppets ()
{
    _pPuppet->Stop();
    _pPuppet = NULL;
    for (auto & rPair : _mapAllDefendPlayer)
    {
        if (rPair.second)
            rPair.second->StopPuppet(GetMountain()->GetType());
    }
}		// -----  end of function StopAllPuppets  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  BattleProcess
//  Description:  战斗进行
// =====================================================================================
void CGate::BattleProcess (time_t tNow)
{
    if (tNow < _dwStartRemainTime)
        return;
    if (CheckGate())
    {
        if (TryPuppetAttack(tNow))
            NotifyGateInfo();
    }
}		// -----  end of function BattleProcess  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerEnter
//  Description:  玩家进入帮派战
// =====================================================================================
ENGBEnterResult CGate::PlayerEnter (CPlayerPtr pPlayer)
{
    ENGBEnterResult eResult = eNGBERFailed;
    if (!pPlayer)
        return eResult;
    if (pPlayer->GetMountain() != eNGBMNone)
    {
        eResult = eNGBERRepeat;
        return eResult;
    }
    ENGBSide eSide = eNGBSideInvalid;
    UINT64 qwGuildID = pPlayer->GetGuildID();
    if (qwGuildID == _qwDefenderID)
    {
        _mapAllDefendPlayer[pPlayer->GetRoleID()] = pPlayer;
        eSide = eNGBSideDefencer;
    }
    else
    {
        _mapAllAttackPlayer[pPlayer->GetRoleID()] = pPlayer;
        eSide = eNGBSideAttacker;
    }
    pPlayer->SetMountain(GetMountain()->GetType(), eSide);

    return eNGBERSuccess;
}		// -----  end of function PlayerEnter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerQuit
//  Description:  玩家退出
// =====================================================================================
ENGBQuitResult CGate::PlayerQuit (CPlayerPtr pPlayer)
{
    ENGBQuitResult eResult = eNGBQuitFailed;
    if (!pPlayer)
        return eResult;
    UINT64 qwRoleID = pPlayer->GetRoleID();

    auto it = _mapAllDefendPlayer.find(qwRoleID);
    if (it != _mapAllDefendPlayer.end())
        _mapAllDefendPlayer.erase(it);

    auto it2 = _mapAllAttackPlayer.find(qwRoleID);
    if (it2 != _mapAllAttackPlayer.end())
        _mapAllAttackPlayer.erase(it2);

    pPlayer->SetMountain(eNGBMNone,eNGBSideInvalid);
    eResult = eNGBQuitSuccess;
    if (pPlayer->GetPlayer())
        pPlayer->GetPlayer()->AddBuff(22);
    return eResult;
}		// -----  end of function PlayerQuit  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerAttack
//  Description:  玩家攻击
// =====================================================================================
ENGBGateAttackResult CGate::PlayerAttack (CPlayerPtr pPlayer, UINT64 qwRoleID)
{
    if (!pPlayer)
        return eNGBGARFailed;
    if (GetStartRemainTime())
    {
        ::CPlayerPtr pPlayer0 = pPlayer->GetPlayer();
        if (pPlayer0)
        {
            string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgLingMountainBattleIsReady);
            pPlayer0->SendPkg(strPkg);
        }
        return eNGBGARWrongTime;
    }

    bool bAttackSide = false;

    UINT64 qwAttackerID = pPlayer->GetRoleID();
    auto it = _mapAllAttackPlayer.find(qwAttackerID);
    if (it != _mapAllAttackPlayer.end() && it->second)
    {
        pPlayer = it->second;
        bAttackSide = true;
    }

    if (!bAttackSide)
    {
        auto it = _mapAllDefendPlayer.find(qwAttackerID);
        if (it != _mapAllDefendPlayer.end() && it->second)
        {
            pPlayer = it->second;
            if (!qwRoleID)
                return eNGBGARDefencer;
        }
    }

    if (pPlayer->GetDeadTime())
        return eNGBGARSelfIsDead;

    CPlayerPtr pTarget;

    if (bAttackSide)
    {
        if (qwRoleID)
        {
            it = _mapAllDefendPlayer.find(qwRoleID);
            if (it != _mapAllDefendPlayer.end() && it->second)
            {
                pTarget = it->second;
                if (pTarget->GetDeadTime())
                    return eNGBGARTargetIsDead;
            }
        }
        else
        {
            for (auto& rPair : _mapAllDefendPlayer)
            {
                if (rPair.second && !rPair.second->GetDeadTime())
                    return eNGBGARDefencerAlive;
            }
        }
    }
    else
    {
        it = _mapAllAttackPlayer.find(qwRoleID);
        if (it != _mapAllAttackPlayer.end() && it->second)
        {
            pTarget = it->second;
            if (pTarget->GetDeadTime())
                return eNGBGARTargetIsDead;
        }
        else
            return eNGBGARFailed;
    }

    ::CPlayerPtr pPlayerA = pPlayer->GetPlayer();
    if (!pPlayerA)
        return eNGBGARFailed;

    ::CPlayerPtr pPlayerB;
    if (pTarget)
    {
        pPlayerB = pTarget->GetPlayer();
        if (!pPlayerB)
            return eNGBGARFailed;
    }

    IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
    if (!pBS)
        return eNGBGARFailed;

    TVecBattleFighterPtr vecBattleFighter;
    TVecBattleFighterPtr vecBattleFighter2;
    IBattleFighterPtr   pScene;

    pPlayerA->GetBattleFighterList(vecBattleFighter);

    if (pTarget) // 和玩家打
    {
        pPlayerB->GetBattleFighterList(vecBattleFighter2);
        pBS->PutFighters(1, pPlayerB->GetMainFighter()->GetInstID(), pPlayerB->GetLevel(), vecBattleFighter2, pPlayerB->GetRoleID(), false);
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
    }
    else    // 和城门打
    {
        UINT32 dwEnemyID = 20050;
        vector<TVecBattleFighterPtr> vecvecBattleFighter2;
        UINT64 qwTmpInstID =  1;
        qwTmpInstID = CMonster::GetBattleFighterListByGroupID(vecvecBattleFighter2, dwEnemyID, qwTmpInstID, vecBattleFighter);
        if (!qwTmpInstID || vecvecBattleFighter2.empty() || vecvecBattleFighter2[0].empty())
            return eNGBGARFailed;

        IBattleFighterPtr& pFighter = vecvecBattleFighter2[0][0]; // XXX: 第一个肯定是BOSS

        pFighter->SetHP(_dwGateHP);
        pFighter->SetFighterAttr(EFIGHTATTR_PHYATK, _dwGateAttack);
        pFighter->SetFighterAttr(EFIGHTATTR_MGCATK, _dwGateAttack);

        pBS->PutFighters(1, qwTmpInstID, CMonsterMgr::GetMonsterLevel(dwEnemyID), vecvecBattleFighter2[0], 1, false);
        pScene = CMonster::GetSceneFighter(dwEnemyID);
    }
    pBS->PutFighters(0, pPlayerA->GetMainFighter()->GetInstID(), pPlayerA->GetLevel(), vecBattleFighter, pPlayerA->GetRoleID(), false);


    if (!pScene)
        pScene = CMapMgr::ToBattleFighterWithFighterMapID(SParamConfig::wLingMountainBattleField1);
    if (!pScene)
        pScene = pPlayerA->GetSceneFighter();
    pBS->PutScene(pScene);

    pBS->Start(EBTPlayer);

    UINT32 dwLostHP = 0;
    CPlayerPtr pWinner;
    CPlayerPtr pLoser;
    bool bWin = false;
    switch (pBS->GetFinalWinner())
    {
        case EBResultAttackWin: //攻击方胜利
            {
                pWinner = pPlayer;
                if (pTarget) // 攻打玩家
                    pLoser  = pTarget;
                else // 城门被攻破
                {
                    dwLostHP = _dwGateHP;
                    _dwGateHP = 0;
                    RejustGateAttr();
                }

                TVecBattleFighterPtr vecFighters;
                pBS->GetFighterList(0, vecFighters);
                pPlayerA->RecoverFighters(vecFighters);
                bWin = true;
            }

            break;
        case EBResultDefenseWin: //防守方胜利
        default:
            pLoser = pPlayer;
            if (pTarget) // 攻打玩家
            {
                pWinner = pTarget;
                TVecBattleFighterPtr vecFighters;
                pBS->GetFighterList(1, vecFighters);
                pPlayerB->RecoverFighters(vecFighters);
            }
            else // 城门把自己打败了
            {
                UINT32 dwRemainHP = 0;
                TVecBattleFighterPtr vecFighters;
                pBS->GetFighterList(1, vecFighters);
                for (auto& pFighter : vecFighters)
                {
                    dwRemainHP += pFighter ? pFighter->GetHP() : 0;
                }

                if (dwRemainHP < _dwGateHP)
                    dwLostHP = _dwGateHP - dwRemainHP;
                else
                    dwLostHP = 0;
                _dwGateHP = dwRemainHP;
            }
            bWin = false;
    }

    std::string strReport;
    pBS->GetReport(strReport);

    std::string strData = g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayerA->GetRoleID(), pPlayerA->GetMainFighter()->GetID());
    pPlayerA->SendPkg(strData);

    if (pPlayerB)
    {
        strData = g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayerB->GetRoleID(), pPlayerB->GetMainFighter()->GetID());
        pPlayerB->SendPkg(strData);
    }

    // 分数
    if (pWinner)
    {
        AddPlayerScore(pWinner, SParamConfig::wLingMountainFightWinHonor);
        CBattleMgr::Instance().AddPlayerBattleCount(pWinner->GetRoleID(), true);
    }
    if (pLoser)
    {
        pLoser->SetDeadTime(SParamConfig::wLingMountainReliveTime);
        pLoser->GetPlayer()->RegenAllHP();
        if (pTarget)
            AddPlayerScore(pLoser, SParamConfig::wLingMountainFightDefeatHonor);
        else
            AddPlayerScore(pLoser, SParamConfig::wLingMountainAttackDoorHonor);
        CBattleMgr::Instance().AddPlayerBattleCount(pLoser->GetRoleID(), false);
    }
    NotifyRankInfo();

    // 广播
    if (!pTarget) // 攻打城门
    {
        if (pWinner)  // 城门被攻破
        {
            TVecString vecString;
            UINT64 qwRoleID = pWinner->GetRoleID();
            vecString.push_back(GetMountain()->GetName());
            ostringstream strTmp;
            strTmp.str("");
            strTmp << static_cast<UINT32>(pWinner->GetPlayer()->GetColor());
            vecString.push_back(strTmp.str());
            vecString.push_back(pWinner->GetName());
            g_NewGuildBattleProtS.SendClt_BattleLogNotify(&qwRoleID, 1, eMsgLingMountainDoorBreak, vecString);
        }
        else if (pLoser)// 城门没被攻破
        {
            TVecString vecString;
            UINT64 qwRoleID = pLoser->GetRoleID();
            ostringstream strTmp;
            strTmp.str("");
            strTmp << static_cast<UINT32>(pLoser->GetPlayer()->GetColor());
            vecString.push_back(strTmp.str());
            vecString.push_back(pLoser->GetName());
            strTmp.str("");
            strTmp << dwLostHP;
            vecString.push_back(strTmp.str());
            g_NewGuildBattleProtS.SendClt_BattleLogNotify(&qwRoleID, 1, eMsgLingMountainAttackDoor, vecString);

        }
    }
    else // 攻击玩家
    {
        TVecString vecString;
        TVecUINT64 vecRoleID;
        ostringstream strTmp;
        vecRoleID.push_back(pPlayer->GetRoleID());
        vecRoleID.push_back(pTarget->GetRoleID());
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

    NotifyGateInfo();

    return eNGBGARSuccess;
}		// -----  end of function PlayerAttack  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerBuyPuppet
//  Description:  玩家购买战争傀儡
// =====================================================================================
ENGBBuyPuppetResult CGate::PlayerBuyPuppet (CPlayerPtr pPlayer)
{
    if (!pPlayer)
        return eNGBBPRFailed;

    UINT64 qwRoleID = pPlayer->GetRoleID();
    auto it = _mapAllAttackPlayer.find(qwRoleID);
    if (it != _mapAllAttackPlayer.end() && it->second)
        pPlayer = it->second;
    else
    {
        auto it2 = _mapAllDefendPlayer.find(qwRoleID);
        if (it2 != _mapAllDefendPlayer.end() && it2->second)
            return eNGBBPRDefencer;
    }

    time_t tStartTime = Time::Now();
    tStartTime = tStartTime >= _dwStartRemainTime ? tStartTime : _dwStartRemainTime;
    return pPlayer->BuyPuppet(GetMountain()->GetType(), tStartTime);
}		// -----  end of function PlayerBuyPuppet  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyGateInfo
//  Description:  广播城门信息
// =====================================================================================
void CGate::NotifyGateInfo () const
{
    SMountainGateInfo sInfo;
    if (!GetAllInfo(sInfo))
        return;
    for (auto& rPair : _mapAllAttackPlayer)
    {
        if (!rPair.second)
            continue;
        ::CPlayerPtr pPlayer = rPair.second->GetPlayer();
        if (!pPlayer)
            continue;
        GetPlayerInfo(sInfo, rPair.second->GetRoleID());
        string strPkg = g_NewGuildBattleProtS.BuildPkg_GateInfoNotify(sInfo);
        pPlayer->SendPkg(strPkg);
    }

    for (auto& rPair : _mapAllDefendPlayer)
    {
        if (!rPair.second)
            continue;
        ::CPlayerPtr pPlayer = rPair.second->GetPlayer();
        if (!pPlayer)
            continue;
        GetPlayerInfo(sInfo, rPair.second->GetRoleID());
        string strPkg = g_NewGuildBattleProtS.BuildPkg_GateInfoNotify(sInfo);
        pPlayer->SendPkg(strPkg);
    }
}		// -----  end of function NotifyGateInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyBroken
//  Description:  广播被攻破
// =====================================================================================
void CGate::NotifyBroken () const
{
    UINT64 qwRoleID = 0;

    TVecUINT64 vecRoleID;
    for (auto & rPair : _mapAllAttackPlayer)
    {
        vecRoleID.push_back(rPair.first);
        qwRoleID = rPair.first;
    }
    for (auto & rPair : _mapAllDefendPlayer)
    {
        vecRoleID.push_back(rPair.first);
    }
    g_NewGuildBattleProtS.SendClt_GateBrokenNotify((UINT64*)&vecRoleID[0], (UINT16)vecRoleID.size(), GetMountain()->GetType(), _vecWinnerGuildID);

    TVecINT32 vecParam;
    vecParam.push_back(GetMountain()->GetType());
    vecParam.push_back(time(NULL));
    if(qwRoleID)
    {
        ::CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if(pUser)
        {
            ::CPlayerPtr pPlayer =  pUser->GetPlayer();
            if(pPlayer)
            {
                pPlayer->OnEvent(eEventType_LingMountainConquer,vecParam);
            }
        }
        else
        {
            ::CPlayer::AddOffLineEvent(qwRoleID,eEventType_LingMountainConquer,vecParam);
        }
    }

}		// -----  end of function NotifyBroken  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyRankInfo
//  Description:  广播排行榜信息
// =====================================================================================
void CGate::NotifyRankInfo () const
{
    TVecUINT64 vecRoleID;
    map<UINT64, TVecUINT64> mapVecGuileRoleID;
    for (auto & rPair : _mapAllAttackPlayer)
    {
        if (rPair.second && rPair.second->GetMountain() == GetMountain()->GetType())
        {
            vecRoleID.push_back(rPair.first);
            mapVecGuileRoleID[rPair.second->GetGuildID()].push_back(rPair.second->GetRoleID());
        }
    }
    for (auto & rPair : _mapAllDefendPlayer)
    {
        if (rPair.second && rPair.second->GetMountain() == GetMountain()->GetType())
        {
            vecRoleID.push_back(rPair.first);
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
//         Name:  CheckGate
//  Description:  检查城门是否被存在
//                true 还存在
//                false 已经被攻破
// =====================================================================================
bool CGate::CheckGate ()
{
    if (_dwGateHP <= 0)
        return false;
    else
        return true;
}		// -----  end of function CheckGate  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  TryPuppetAttack
//  Description:  傀儡攻击城门
// =====================================================================================
bool CGate::TryPuppetAttack (time_t tNow)
{
    if (!_dwGateHP)
        return false;

    TVecUINT64 vecRoleID;
    for (auto & rPair : _mapAllAttackPlayer)
    {
        if (rPair.second && rPair.second->GetMountain() == GetMountain()->GetType())
            vecRoleID.push_back(rPair.first);
    }

    for (auto & rPair : _mapAllDefendPlayer)
    {
        if (rPair.second && rPair.second->GetMountain() == GetMountain()->GetType())
            vecRoleID.push_back(rPair.first);
    }
    ostringstream strTmp;

    bool bRet = false;
    TVecString vecString;
    if (_pPuppet)
    {
        while(tNow >= _pPuppet->GetNextAttackTime())
        {
            UINT32 dwLostHP = _pPuppet->GetAttack();
            if (dwLostHP > _dwGateHP)
                _dwGateHP = 0;
            else
                _dwGateHP -= dwLostHP;
            _pPuppet->CalcNextAttackTime();
            bRet = true;
            vecString.clear();
            strTmp.str("");
            strTmp << 5 ;
            vecString.push_back(strTmp.str());
            vecString.push_back("傀儡");
            strTmp.str("");
            strTmp << dwLostHP ;
            vecString.push_back(strTmp.str());
            if (!vecRoleID.empty())
            {
                g_NewGuildBattleProtS.SendClt_BattleLogNotify((UINT64*)&vecRoleID[0], (UINT16)vecRoleID.size(), eMsgLingMountainAttackDoor, vecString);
                g_NewGuildBattleProtS.SendClt_PuppetAttackNotify((UINT64*)&vecRoleID[0], (UINT16)vecRoleID.size(), 0);
            }
        }
    }
    bool bChanged = false;
    for (auto& rPair : _mapAllAttackPlayer)
    {
        if (!rPair.second)
            continue;
        UINT64 qwRoleID = rPair.second->GetRoleID();
        TVecPuppetPtr& vecPuppet = rPair.second->GetAllPuppet(GetMountain()->GetType());
        UINT8 byIndex = 1;
        for (auto & pPuppet : vecPuppet)
        {
            if (!pPuppet)
                continue;
            while(tNow >= pPuppet->GetNextAttackTime())
            {
                UINT32 dwLostHP = pPuppet->GetAttack();
                if (dwLostHP > _dwGateHP)
                    _dwGateHP = 0;
                else
                    _dwGateHP -= dwLostHP;
                pPuppet->CalcNextAttackTime();
                bRet = true;
                vecString.clear();
                strTmp.str("");
                strTmp << 5 ;
                vecString.push_back(strTmp.str());
                vecString.push_back("傀儡");
                strTmp.str("");
                strTmp << dwLostHP ;
                vecString.push_back(strTmp.str());
                g_NewGuildBattleProtS.SendClt_BattleLogNotify(&qwRoleID, 1, eMsgLingMountainAttackDoor, vecString);
                AddPlayerScore(rPair.second, SParamConfig::wLingMountainAttackDoorHonor);
                bChanged = true;

                g_NewGuildBattleProtS.SendClt_PuppetAttackNotify(&qwRoleID, 1, byIndex);
            }
            ++ byIndex;
        }
    }
    if (bChanged)
        NotifyRankInfo();
    return bRet;
}		// -----  end of function TryPuppetAttack  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPuppetInfo
//  Description:  获取傀儡信息
// =====================================================================================
void CGate::GetPuppetInfo (TVecPuppetInfo& rvecInfo) const
{
    if (_pPuppet)
    {
        SPuppetInfo sInfo;
        sInfo.byIndex           = 0;
        sInfo.qwOwnerID         = 0;
        sInfo.dwNextAttackTime  = _pPuppet->GetNextAttackTime();
        rvecInfo.push_back(sInfo);
    }

}		// -----  end of function GetPuppetInfo  ----- //
// ===  FUNCTION  ======================================================================
//         Name:  GetPlayerInfo
//  Description:  获取玩家的信息
// =====================================================================================
void CGate::GetPlayerInfo (SMountainGateInfo& rInfo, UINT64 qwRoleID) const
{
    CPlayerPtr pPlayer = GetPlayer(qwRoleID, rInfo.eSelfSide);
    if (pPlayer)
    {
        pPlayer->GetAllInfo(rInfo.sSelfInfo); //自己的信息
        rInfo.vecPuppetInfo.clear();
        GetPuppetInfo(rInfo.vecPuppetInfo);
        pPlayer->GetPuppetInfo(rInfo.vecPuppetInfo);
    }

    rInfo.vecPlayerInfo.clear();
    switch (rInfo.eSelfSide)
    {
        case eNGBSideAttacker:
            for (auto & rPair : _mapAllDefendPlayer)
            {
                if (rPair.second)
                {
                    SPlayerPanelInfo sInfo;
                    if (rPair.second->GetAllPanelInfo(sInfo))
                        rInfo.vecPlayerInfo.push_back(sInfo);
                }
            }
            break;
        case eNGBSideDefencer:
            for (auto & rPair : _mapAllAttackPlayer)
            {
                if (rPair.second)
                {
                    SPlayerPanelInfo sInfo;
                    if (rPair.second->GetAllPanelInfo(sInfo))
                        rInfo.vecPlayerInfo.push_back(sInfo);
                }
            }
            break;
        default:
            break;
    }
}		// -----  end of function GetPlayerInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddPlayerScore
//  Description:  增加玩家的战功
// =====================================================================================
void CGate::AddPlayerScore (CPlayerPtr pPlayer, UINT32 dwScore)
{
    if (!pPlayer)
        return;
    time_t tNow = Time::Now();
    pPlayer->AddScore(GetMountain()->GetType(), dwScore);
    _mapGuildScore[pPlayer->GetGuildID()] += dwScore;
    _mapGuildScoreTime[pPlayer->GetGuildID()] = tNow;

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
//         Name:  ReliveAllPlayers
//  Description:  复活所有玩家
// =====================================================================================
void CGate::ReliveAllPlayers ()
{
    for (auto& rPair : _mapAllAttackPlayer)
    {
        if (!rPair.second)
            continue;
        ::CPlayerPtr pPlayer = rPair.second->GetPlayer();
        if (!pPlayer)
            continue;
        if (!rPair.second->GetDeadTime())
            continue;
        rPair.second->SetDeadTime(0);
        PlayerNotify(pPlayer->GetRoleID());
    }

    for (auto& rPair : _mapAllDefendPlayer)
    {
        if (!rPair.second)
            continue;
        ::CPlayerPtr pPlayer = rPair.second->GetPlayer();
        if (!pPlayer)
            continue;
        if (!rPair.second->GetDeadTime())
            continue;
        rPair.second->SetDeadTime(0);
        PlayerNotify(pPlayer->GetRoleID());
    }
}		// -----  end of function ReliveAllPlayers  ----- //

//基准时间10分钟
const UINT32 GATE_BOSS_BASE_TIME = 10 * 60;

const FLOAT GATE_BOSS_HP_FACTOR = 1.0f;//hp系数

const FLOAT GATE_BOSS_ATK_FACTOR = 0.5f;//atkhp系数

const FLOAT GATE_BOSS_MAX_ASC_HP_FACTOR = 0.40f;
const FLOAT GATE_BOSS_MAX_ASC_ATK_FACTOR = 0.40f;

// ===  FUNCTION  ======================================================================
//         Name:  RejustGateAttr
//  Description:  更新城门相关属性
// =====================================================================================
void CGate::RejustGateAttr ()
{
    time_t tNow = Time::Now();
    UINT32 dwLast = 0;
    if (tNow < _dwStartRemainTime)
        dwLast = _dwStartRemainTime - tNow;
    else
        dwLast = tNow - _dwStartRemainTime;

    DOUBLE fRate = GATE_BOSS_BASE_TIME / dwLast - 1;
    if(fRate > GATE_BOSS_MAX_ASC_HP_FACTOR)
        fRate = GATE_BOSS_MAX_ASC_HP_FACTOR;

    _dwGateMaxHP  += fRate * GATE_BOSS_HP_FACTOR * _dwGateMaxHP;
    _dwGateAttack += fRate * GATE_BOSS_ATK_FACTOR * _dwGateAttack;

    UINT16 wHPID = 0;
    UINT16 wAttackID = 0;
    switch(_pMountain.lock()->GetType())
    {
        case eNGBMEMei: //峨眉
            wHPID = NVarDefine::eSystemVar_NewGuildBattleGate1HP;
            wAttackID = NVarDefine::eSystemVar_NewGuildBattleGate1Attack;
            break;
        case eNGBMKunLun: //昆仑
            wHPID = NVarDefine::eSystemVar_NewGuildBattleGate2HP;
            wAttackID = NVarDefine::eSystemVar_NewGuildBattleGate2Attack;
            break;
        case eNGBMHuangShan: //黄山
            wHPID = NVarDefine::eSystemVar_NewGuildBattleGate3HP;
            wAttackID = NVarDefine::eSystemVar_NewGuildBattleGate3Attack;
            break;
        default:
            break;
    }
    if (wHPID && wAttackID)
    {
        TVecUINT16 vecID;
        TVecUINT64 vecValue;
        vecID.push_back(wHPID);
        vecValue.push_back(_dwGateMaxHP);
        vecID.push_back(wAttackID);
        vecValue.push_back(_dwGateAttack);
        g_Game2CenterCommC.Send_SetSystemVar(vecID, vecValue,
                [] ( UINT8 byRet_, const TVecUINT16& vecVarID ) { });
    }
}		// -----  end of function RejustGateAttr  ----- //
} // namespace NNewGuildBattle

