// =====================================================================================
//
//       Filename:  GuildBattle.cpp
//
//    Description:  帮派战战斗
//
//        Version:  1.0
//        Created:  07/25/2014 10:54:00 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#include "GuildBattle.h"

#include "GuildBattleConfig.h"
#include "GuildBattleField.h"
#include "GuildBattleSpot.h"
#include "GuildBattleMgr.h"
#include "GuildBattleInfo.h"

#include "MapMgr.h"
#include "Player.h"

#include "Battle.h"

#include "Protocols.h"
#include "SysMsgDefine.h"
#include "EventMgr.h"
#include "HeroFighter.h"
#include "GUIDMgr.h"

CGuildBattle::CGuildBattle():
    _eState(eGBStateReady), 
    _dwPrepareTime(0), _dwStartTime(0), _dwNextBattleTime(0),
    _eWinnerSide(eGBSideInvalid), _bEnded(false)
{
    _dwScore[0] = 0;
    _dwScore[1] = 0;

    CGuildBattleFieldPtr pField (new CGuildBattleField());
    _pField = pField;

}

CGuildBattle::~CGuildBattle()
{
}

// ===  FUNCTION  ======================================================================
//         Name:  IsInBattle
//  Description:  根据玩家ID检索是否在该帮派战中
// =====================================================================================
bool CGuildBattle::IsInBattle (UINT64 qwRoleID) const
{
    if (!_pField)
        return false;
    EGBSpot eSpotType = _pField->GetPlayerSpot(qwRoleID);
    if (eSpotType == eGBSpotNone)
        return false;
    else
        return true;
}		// -----  end of function IsInBattle  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetState
//  Description:  获得当前战斗状态
// =====================================================================================
EGBState CGuildBattle::GetState () const
{
    return  _eState;
}		// -----  end of function GetState  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetField
//  Description:  获取帮派战场地
// =====================================================================================
CGuildBattleFieldPtr CGuildBattle::GetField ()
{
    return _pField;
}		// -----  end of function GetField  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSpotInfo
//  Description:  获取战斗中某据点的详细信息
// =====================================================================================
bool CGuildBattle::GetSpotInfo(CPlayerPtr pPlayer, EGBSpot eType, TVecSpotInfo& rvecSpotInfo, EGBResult& eResult)
{
    if (!_pField)
    {
        eResult = eGBResultFailed;
        return false;
    }
    if (eType == eGBSpotNone)
    {
        eResult = eGBResultFailed;
        return false;
    }

    auto it = _mapPlayerOBSpot.find(pPlayer->GetRoleID());
    if ((it != _mapPlayerOBSpot.end()) && (it->second != eType))
        _pField->RemoveOB(pPlayer->GetRoleID(), it->second);

    _mapPlayerOBSpot[pPlayer->GetRoleID()] = eType;
    _pField->AddOB(pPlayer->GetRoleID(), eType);
    return _pField->GetSpotInfo(pPlayer, eType, rvecSpotInfo, eResult);
}		// -----  end of function GetSpotInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllOB
//  Description:  获取参战的所有观战人员
// =====================================================================================
void CGuildBattle::GetAllOB (TVecUINT64& rvecRoleID) const
{
    for (auto it = _mapPlayerOBSpot.begin(); it != _mapPlayerOBSpot.end(); ++it)
    {
        rvecRoleID.push_back(it->first);
    }
}		// -----  end of function GetAllOB  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBattleInfo
//  Description:  获取战报信息 
// =====================================================================================
bool CGuildBattle::GetBattleInfo(EGBSpot eSpotType, EGBBattleResult& eResult, TVecBattleData& rvecBattleData) const
{
    if (!_pField)
    {
        eResult = eGBBattleFailed;
        return false;
    }
    return _pField->GetBattleInfo(eSpotType, eResult, rvecBattleData);
}		// -----  end of function GetBattleInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetCurrentScore
//  Description:  获取当前取得的积分
// =====================================================================================
UINT32 CGuildBattle::GetCurrentScore (EGBSide eSide) const
{
    UpdateScore(false);
    return _dwScore[eSide];
}		// -----  end of function GetCurrentScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitField
//  Description:  初始化帮派战场地信息
// =====================================================================================
bool CGuildBattle::InitField (CGuildBattleFieldPtr pField, EGBSide eSide , EGBSide eSide2)
{
    return _pField->InitInfo(pField, eSide, eSide2);
}		// -----  end of function InitField  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitTime
//  Description:  初始化帮派战时间
// =====================================================================================
void CGuildBattle::InitTime (UINT32 dwTodayTime)
{
    _dwPrepareTime = dwTodayTime;
    //_dwStartTime = dwTodayTime + CGuildBattleConfigMgr::Instance().GetPrepareTime();
    _dwStartTime = dwTodayTime;
    _dwNextBattleTime = _dwStartTime;
    return;
}		// -----  end of function InitTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetState
//  Description:  设置状态 
// =====================================================================================
void CGuildBattle::SetState (EGBState eState )
{
    _eState = eState;
}		// -----  end of function SetState  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitMap
//  Description:  初始化帮派战相关据点地图
// =====================================================================================
void CGuildBattle::InitMap ()
{
    _pField->InitMap();
}		// -----  end of function InitMap  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitPlayer
//  Description:  将玩家初始化至该地图上
// =====================================================================================
void CGuildBattle::InitPlayer ()
{
    _pField->InitPlayer();
    _pField->ResetOBSpot(_mapPlayerOBSpot);
}		// -----  end of function InitPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerQuit
//  Description:  玩家退出
// =====================================================================================
void CGuildBattle::PlayerQuit (CPlayerPtr pPlayer)
{
    if (!pPlayer || !_pField)
        return;
    auto it = _mapPlayerOBSpot.find(pPlayer->GetRoleID());
    if (it != _mapPlayerOBSpot.end())
    {
        _pField->RemoveOB(pPlayer->GetRoleID(), it->second);
        _mapPlayerOBSpot.erase(it);
    }
    _pField->RemovePlayer(pPlayer);
}		// -----  end of function PlayerQuit  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Adjust
//  Description:  调整
// =====================================================================================
void CGuildBattle::Adjust(UINT64 qwRoleID, EGBSpot eSpotType, UINT8 byIndex, EGBAdjustResult& eResult)
{
    _pField->Adjust(qwRoleID, eSpotType, byIndex, eResult);
}		// -----  end of function Adjust  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UserOnline
//  Description:  玩家上线
// =====================================================================================
void CGuildBattle::UserOnline (UINT64 qwRoleID)
{
    if (!_pField)
        return;
    auto it = _mapPlayerOBSpot.find(qwRoleID);
    if (it != _mapPlayerOBSpot.end())
        _pField->RemoveOB(qwRoleID, it->second);
    if (_pField)
    {
        EGBSpot eSpotType = _pField->GetPlayerSpot(qwRoleID);
        if (eSpotType != eGBSpotNone)
        {
            _mapPlayerOBSpot[qwRoleID] = eSpotType;
            _pField->AddOB(qwRoleID, eSpotType);
        }
    }
}		// -----  end of function UserOnline  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Process
//  Description:  帮派战具体流程
// =====================================================================================
void CGuildBattle::Process (UINT32 dwTodayTime)
{
    switch(_eState)
    {
        case eGBStateReady:
            break;
        case eGBStatePrepare:
            break;
        case eGBStateBattle:    
            if (dwTodayTime >= _dwNextBattleTime) //  新一轮战斗
            {
                RefreshSpotInfo();
                _dwNextBattleTime += CGuildBattleConfigMgr::Instance().GetBattleMaxTime();
                StartOneRound();
                NotifyFieldInfo();
                NotifyBattleInfo();
                NotifyAllOBSpotInfo();
            }
            break;
        default:
            break;
    }
    return ;
}		// -----  end of function Process  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  RefreshSpotInfo
//  Description:  更新据点信息
// =====================================================================================
void CGuildBattle::RefreshSpotInfo ()
{
    if (_pField)
    {
        _pField->RefreshState(false);
        _pField->UpdateSpotCache();
    }
}		// -----  end of function RefreshSpotInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  RefreshState
//  Description:  
// =====================================================================================
void CGuildBattle::RefreshState (bool bBattle)
{
    if (_pField)
        _pField->RefreshState(bBattle);
}		// -----  end of function RefreshState  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  StartOneRound
//  Description:  进行一轮战斗
// =====================================================================================
void CGuildBattle::StartOneRound ()
{
    TVecGBPlayerPtr vecPlayerA;
    TVecGBPlayerPtr vecPlayerB;
    _pField->PopBattlePlayerPairs(vecPlayerA, vecPlayerB);
    auto itA = vecPlayerA.begin();
    auto itB = vecPlayerB.begin();
    UINT8 byIndex = 1;
    while(itA != vecPlayerA.end() && itB != vecPlayerB.end())
    {
        if ((*itA) && (*itB)) // 双方都有人，需要战斗
        {
            CPlayerPtr pPlayerA = (*itA)->pPlayer.lock();
            CPlayerPtr pPlayerB = (*itB)->pPlayer.lock();

            if (pPlayerA && pPlayerB)
            {
                _pField->UpdateSpotCache(pPlayerA->GetRoleID(), eGBUserStateBattle);
                _pField->UpdateSpotCache(pPlayerB->GetRoleID(), eGBUserStateBattle);

                IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
                TVecBattleFighterPtr vecBattleFighter;
                TVecBattleFighterPtr vecBattleFighter2;
                pPlayerA->GetBattleFighterList(vecBattleFighter);
                pPlayerB->GetBattleFighterList(vecBattleFighter2);
                pBS->PutFighters(0, pPlayerA->GetMainFighter()->GetInstID(), pPlayerA->GetLevel(), vecBattleFighter, pPlayerA->GetRoleID(), false);
                pBS->PutFighters(1, pPlayerB->GetMainFighter()->GetInstID(), pPlayerB->GetLevel(), vecBattleFighter2, pPlayerB->GetRoleID(), false);
                pBS->PutScene(pPlayerA->GetSceneFighter());

                pBS->Start(EBTPlayer);

                std::string strReport;
                pBS->GetReport(strReport);

                SGuildBattleSpotPlayerPtr pWinner;
                SGuildBattleSpotPlayerPtr pLoser;
                SBattleUserAllInfo sUserAllInfoA;
                SBattleUserAllInfo sUserAllInfoB;
                (*itA)->GetAllInfo(sUserAllInfoA);
                (*itB)->GetAllInfo(sUserAllInfoB);
                EGBSide eSide = eGBSideInvalid;
                CPlayerPtr pWinnerPlayer;
                CPlayerPtr pLoserPlayer;
                switch(pBS->GetFinalWinner())
                {
                    case EBResultTie:
                    case EBResultAttackWin:
                        pWinner = *itA;
                        pLoser = *itB;
                        pWinnerPlayer = pPlayerA;
                        pLoserPlayer = pPlayerB;
                        eSide = eGBSideA;
                        break;
                    case EBResultDefenseWin:
                        pWinner = *itB;
                        pLoser = *itA;
                        pWinnerPlayer = pPlayerB;
                        pLoserPlayer = pPlayerA;
                        eSide = eGBSideB;
                        break;
                    default:
                        break;
                }

                std::string strData = g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayerA->GetRoleID(), pPlayerA->GetMainFighter()->GetID());
                pPlayerA->SendPkg(strData);
                strData = g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayerB->GetRoleID(), pPlayerB->GetMainFighter()->GetID());
                pPlayerB->SendPkg(strData);


                if (pWinner)
                {
                    ++(pWinner->byWinCount);
                    if (pWinner->byWinCount >= CGuildBattleConfigMgr::Instance().GetBattleMaxWin())
                        pWinner->eState = eGBUserStateWinTooMuch;
                    else
                        pWinner->eState = eGBUserStateWin;

                    pBS->GetFighterList(eSide, vecBattleFighter);
                    pWinnerPlayer->RecoverFighters(vecBattleFighter);
                    CGuildBattleMgr::Instance().AddPlayerBattleCount(pWinnerPlayer->GetRoleID(), true);
                }
                if (pLoser)
                {
                    pLoser->eState = eGBUserStateDead;
                    pLoserPlayer->RegenAllHP();
                    CGuildBattleMgr::Instance().AddPlayerBattleCount(pLoserPlayer->GetRoleID(), false);
                }
                CGuildBattleInfoPtr pInfo (new CGuildBattleInfo(pBS->GetBattleID(), byIndex, sUserAllInfoA, sUserAllInfoB, pPlayerA->GetRoleID(), pPlayerB->GetRoleID(), pPlayerA->GetName(), pPlayerB->GetName(), eSide, strReport));
                (*itA)->pSpot.lock()->PushBattleInfo(pInfo);
            }
        }
        ++itA;
        ++itB;
        byIndex = (byIndex % 3) + 1;
    }
    _pField->RefreshState(true);
    UpdateScore(false);
    return;
}		// -----  end of function StartOneRound  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UpdateScore
//  Description:  更新帮派战分数信息
// =====================================================================================
void CGuildBattle::UpdateScore (bool bForceEnd) const
{
    if (!_pField)
        return;
    _dwScore[eGBSideA] = 0;
    _dwScore[eGBSideB] = 0;
    EGBSide eBiggerSide = eGBSideInvalid;
    _bEnded = _pField->UpdateScore(_dwScore, eBiggerSide);
    if (bForceEnd)
        _bEnded = bForceEnd;
    if (_bEnded || bForceEnd)
    {
        if (_dwScore[eGBSideA] > _dwScore[eGBSideB])
        {
            _dwScore[eGBSideA] += 20;
            _eWinnerSide = eGBSideA;
        }
        else if (_dwScore[eGBSideB] > _dwScore[eGBSideA])
        {
            _dwScore[eGBSideB] += 20;
            _eWinnerSide = eGBSideB;
        }
        else if (eBiggerSide != eGBSideInvalid)
        {
            _dwScore[eBiggerSide] += 20;
            _eWinnerSide = eBiggerSide;
        }
    }
}		// -----  end of function UpdateScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  EndBattle
//  Description:  帮派战结束
// =====================================================================================
void CGuildBattle::EndBattle ()
{
    if (!_bEnded)
    {
        _pField->End();
        UpdateScore(true);
    }
    for (UINT8 byIndex = eGBSideA; byIndex < eGBSideInvalid; ++byIndex)
    {
        UINT64 qwGuildIDA = 0;
        UINT64 qwGuildIDB = 0;
        if (byIndex == eGBSideA)
        {
            qwGuildIDA = _pField->GetGuildID(eGBSideA);
            qwGuildIDB = _pField->GetGuildID(eGBSideB);
        }
        else
        {
            qwGuildIDB = _pField->GetGuildID(eGBSideA);
            qwGuildIDA = _pField->GetGuildID(eGBSideB);
        }

        TVecUINT64 vecRoleID;
        _pField->GetRoleID(static_cast<EGBSide>(byIndex), vecRoleID);
        bool bWin = _eWinnerSide == byIndex ? true:false;
        UINT32 dwExtraScore = bWin?200:50;
        for (auto& rRoleID : vecRoleID)
        {
            CGuildBattleMgr::Instance().AddPlayerScore(rRoleID, _dwScore[byIndex] + dwExtraScore);
            SGuildBattleSpotPlayerPtr pSpotPlayer = CGuildBattleMgr::Instance().GetSpotPlayer(rRoleID);
            if (pSpotPlayer)
            {
                CPlayerPtr pPlayer = pSpotPlayer->pPlayer.lock();
                if (pPlayer)
                {
                    //帮派id，积分，对战帮派id，对战帮派积分，我的获胜场次
                    TVecINT32 vecParam;
                    ostringstream strInfo;
                    UINT32 byOtherIndex;
                    if (byIndex == eGBSideA)
                        byOtherIndex = eGBSideB;
                    else
                        byOtherIndex = eGBSideA;
                    vecParam.push_back(_dwScore[byIndex]);
                    vecParam.push_back(_dwScore[byOtherIndex]);
                    vecParam.push_back(pSpotPlayer->byWinCount);
                    strInfo << qwGuildIDA  << "," << qwGuildIDB;
                    pPlayer->OnEvent(eEventType_GuildBattleOneRoundEnd, vecParam, strInfo.str());
                    {
                        TVecINT32 vecParam;
                        if(bWin)
                        {
                            pPlayer->OnEvent(eEventType_GuildBattleWin, vecParam);
                        }
                    }
                }
            }
        }
        CGuildBattleMgr::Instance().AddGuildScore(_pField->GetGuildID(static_cast<EGBSide>(byIndex)), _dwScore[byIndex]);
    }
}		// -----  end of function EndBattle  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CleanMap
//  Description:  清除玩家到其他地图
// =====================================================================================
void CGuildBattle::CleanMap (bool bFinal)
{
    if (_pField)
        _pField->CleanMap(bFinal);
}		// -----  end of function CleanMap  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CleanToPrepare
//  Description:  重置到准备状态
// =====================================================================================
void CGuildBattle::CleanToPrepare ()
{
    CGuildBattleFieldPtr pFieldOldA = CGuildBattleMgr::Instance().GetSignUpField(_pField->GetGuildID(eGBSideA));
    if (pFieldOldA)
    {
        pFieldOldA->CatFieldInfo(_pField, eGBSideA, eGBSideA, true);
        pFieldOldA->ClearSkill();
    }
    else
        LOG_CRI << "pFieldOleA == NULL.";
    CGuildBattleFieldPtr pFieldOldB = CGuildBattleMgr::Instance().GetSignUpField(_pField->GetGuildID(eGBSideB));
    if (pFieldOldB)
    {
        pFieldOldB->CatFieldInfo(_pField, eGBSideA, eGBSideB, true);
        pFieldOldB->ClearSkill();
    }
    else
        LOG_CRI << "pFieldOleB == NULL.";
}		// -----  end of function CleanToPrepare  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SaveSpotInfo
//  Description:  保存当前据点信息供其他切换进来的人看
// =====================================================================================
void CGuildBattle::SaveSpotInfo ()
{
}		// -----  end of function SaveSpotInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UserOffline
//  Description:  玩家下线
// =====================================================================================
void CGuildBattle::UserOffline (UINT64 qwRoleID)
{
    auto it = _mapPlayerOBSpot.find(qwRoleID);
    if (it != _mapPlayerOBSpot.end())
    {
        _pField->RemoveOB(qwRoleID, it->second);
        _mapPlayerOBSpot.erase(it);
    }
}		// -----  end of function UserOffline  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyBattleStartInfo
//  Description:  通知双方对阵信息
// =====================================================================================
void CGuildBattle::NotifyBattleStartInfo () const
{
    if (_pField)
    {
        if (_pField->GetGuildID(eGBSideA) && _pField->GetGuildID(eGBSideB))
        {
            g_Game2CenterGuildBattleC.Send_InfoNotify(_pField->GetGuildID(eGBSideA), eMsgGuildWarNextEnemy, BuildStrVec(_pField->GetGuildName(eGBSideB)));
            g_Game2CenterGuildBattleC.Send_InfoNotify(_pField->GetGuildID(eGBSideB), eMsgGuildWarNextEnemy, BuildStrVec(_pField->GetGuildName(eGBSideA)));
        }
        NotifyFieldInfo(eGBStatePrepare);
    }
}		// -----  end of function NotifyBattleStartInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyFieldInfo
//  Description:  通知玩家所有据点信息
// =====================================================================================
void CGuildBattle::NotifyFieldInfo () const
{
    EGBState eState = GetState();
    NotifyFieldInfo(eState);
}

// ===  FUNCTION  ======================================================================
//         Name:  NotifyFieldInfo
//  Description:  通知玩家所有据点信息
// =====================================================================================
void CGuildBattle::NotifyFieldInfo (EGBState eState) const
{
    SFieldInfo sFieldInfo;
    if (_pField->GetAllInfo(sFieldInfo, eState))
    {
        TVecUINT64 vecRoleID;
        if (eState == eGBStateBattle)
        {
            for (auto it = _mapPlayerOBSpot.begin(); it != _mapPlayerOBSpot.end(); ++it)
            {
                vecRoleID.push_back(it->first);
            }
        }
        else
        {
            CGuildBattleMgr::Instance().GetAllMapPlayers(_pField->GetGuildID(eGBSideA), vecRoleID);
            CGuildBattleMgr::Instance().GetAllMapPlayers(_pField->GetGuildID(eGBSideB), vecRoleID);
        }
        if (!vecRoleID.empty())
            g_GuildBattleProtS.SendClt_FieldInfoNotify(vecRoleID.data(), vecRoleID.size(), sFieldInfo);
    }
}		// -----  end of function NotifyFieldInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyAllOBSpotInfo
//  Description:  通知所有观战者据点信息 
// =====================================================================================
void CGuildBattle::NotifyAllOBSpotInfo () const
{
    if (_pField)
    {
        SFieldInfo sFieldInfo;
        if (_pField->GetAllInfo(sFieldInfo, GetState()))
        {
            TVecUINT64 vecRoleID;
            GetAllOB(vecRoleID);
            if (!vecRoleID.empty())
                g_GuildBattleProtS.SendClt_FieldInfoNotify(vecRoleID.data(), vecRoleID.size(), sFieldInfo);
        }
        _pField->NotifyAllOBSpotInfo();
    }
}		// -----  end of function NotifyAllOBSpotInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyBattleInfo
//  Description:  通知所有观战者战报信息
// =====================================================================================
void CGuildBattle::NotifyBattleInfo() const
{
    if (_pField)
        _pField->NotifyBattleInfo();
}		// -----  end of function NotifyBattleInfo  ----- //

