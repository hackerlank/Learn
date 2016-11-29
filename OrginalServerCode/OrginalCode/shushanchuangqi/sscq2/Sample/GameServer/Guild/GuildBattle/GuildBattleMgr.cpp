// =====================================================================================
//
//       Filename:  GuildBattleMgr.cpp
//
//    Description: 帮派战管理类 
//
//        Version:  1.0
//        Created:  07/24/2014 03:09:23 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#include "GuildBattleMgr.h"

#include "GuildBattleConfig.h"
#include "GuildBattle.h"
#include "Protocols.h"
#include "RTime.h"
#include "SysMsgDefine.h"
#include "GuildBattleField.h"
#include "GuildBattleSpot.h"

#include "Player.h"
#include "MapMgr.h"
#include "UserMgr.h"
#include "EventMgr.h"
#include "Random.h"
#include "GameNetMgr.h"

using namespace NGuildBattleProt;

CGuildBattleMgr::CGuildBattleMgr():
    CDayActivity(eActTypeGuildBattle),
    _eState(eGBStateNone), _dwNextTime(0), _qwEmptyBattleGuildID(0), 
    _dwLastExpCheckTime(0), _byBattleCount(0),
    _bNeedSignNotify(false), _dwReadyNotifyTime(0)
{
}

CGuildBattleMgr::~CGuildBattleMgr()
{
}

// ===  FUNCTION  ======================================================================
//         Name:  GetBattleViaRoleID
//  Description:  根据玩家ID检索到对应的帮派战
// =====================================================================================
CGuildBattlePtr CGuildBattleMgr::GetBattleViaRoleID (UINT64 qwRoleID)
{
    for (auto it = _vecGuildBattle.begin(); it != _vecGuildBattle.end(); ++it)
    {
        if ((*it)->IsInBattle(qwRoleID))
            return *it;
    }
    return NULL;
}		// -----  end of function GetBattleViaRoleID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBattleViaGuildID
//  Description:  根据帮派ID检索到对应的帮派战
// =====================================================================================
CGuildBattlePtr CGuildBattleMgr::GetBattleViaGuildID (UINT64 qwGuildID)
{
    auto it = _mapGuildBattleIndex.find(qwGuildID);
    if (it == _mapGuildBattleIndex.end())
        return NULL;
    else
        return it->second;
}		// -----  end of function GetBattleViaRoleID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPrepareMap
//  Description:  获取对应帮派的准备地图
// =====================================================================================
CGameMapPtr CGuildBattleMgr::GetPrepareMap (UINT64 qwGuildID )
{
    auto it = _mapPrepareMap.find(qwGuildID);
    if (it == _mapPrepareMap.end())
        return NULL;
    else
        return it->second;
}		// -----  end of function GetPrepareMap  ----- //

#if 0
// ===  FUNCTION  ======================================================================
//         Name:  TimerCheck
//  Description:  定时器检查
//        Input:
// =====================================================================================
void CGuildBattleMgr::TimerCheck(time_t tNow, bool bForce /* = false */)
{
    UINT32 dwTodayTime = tNow - Time::TheDay();
    if (dwTodayTime < CGuildBattleConfigMgr::Instance().GetSignUpNotifyTime()) // 还没开始
    {
        if (_eState != eGBStateNone)
        {
            EndBattle(true);
            SetStatus(eGBStateNone);
            _dwNextTime = CGuildBattleConfigMgr::Instance().GetSignUpTime();
        }
    }
#if 0   // 不需要准备时间了
    else if (dwTodayTime < CGuildBattleConfigMgr::Instance().GetSignUpTime()) // 还没开始报名通知
    {
        if (_eState < eGBStatePreReady)
        {
            SetStatus(eGBStatePreReady);
            _dwNextTime = CGuildBattleConfigMgr::Instance().GetSignUpTime();
        }

    }
#endif
    else if (dwTodayTime < CGuildBattleConfigMgr::Instance().GetStartTime()) // 报名阶段时间
    {
        if (_eState < eGBStateReady)
            StartSignUp();
        if (_bNeedSignNotify && dwTodayTime > CGuildBattleConfigMgr::Instance().GetEnterNotifyTime())
        {
            EnterNotify();
            _bNeedSignNotify = false;
        }
    }
    else if (dwTodayTime < CGuildBattleConfigMgr::Instance().GetEndTime()) // 战斗阶段时间
    {
        if (_eState < eGBStatePrepare)
        {
            LOG_DBG << "Start Battle.";
            SetStatus(eGBStatePrepare);
            StartBattle(dwTodayTime);
        }
        if (bForce)
            UpdateNextTime();
        BattleProcess(dwTodayTime);
    }
    else    // 结束时间
    {
        if (_eState != eGBStateNone)
        {
            LOG_DBG << "End Battle";
            SetStatus(eGBStateNone);
            EndBattle(true);
        }
    }
}		// -----  end of function TimerCheck  ----- //
#endif

// ===  FUNCTION  ======================================================================
//         Name:  TimerCheck
//  Description:  定时器检查
//        Input:
// =====================================================================================
void CGuildBattleMgr::TimerCheck(time_t tNow)
{
    switch (_eState)
    {
        case eGBStateNone: //没有开启或即将开启的帮派战
        case eGBStatePreReady: //帮派战报名即将开启
            break;
        case eGBStateReady: //帮派战即将开启，报名阶段
            if (_bNeedSignNotify && tNow > _dwReadyNotifyTime)
            {
                EnterNotify();
                _bNeedSignNotify = false;
            }
            break;
        case eGBStatePrepare: //帮派战准备中
        case eGBStateBattle: //帮派战进行中
            BattleProcess(tNow);
            break;
        case eGBStateBattleEnd: //帮派战战役结束
            break;
        default:
            break;
    }
}		// -----  end of function TimerCheck  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBattleCount
//  Description:  获取当前已经战斗的场数
// =====================================================================================
UINT8 CGuildBattleMgr::GetBattleCount () const
{
    return _byBattleCount;
}		// -----  end of function GetBattleCount  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRemainTime
//  Description:  获取当前状态剩余时间
// =====================================================================================
UINT32 CGuildBattleMgr::GetRemainTime () const
{
    time_t tNow = Time::Now();

    if (tNow > _dwNextTime)
        return 0;

    UINT32 dwRemainTime = 0;
    switch(_eState)
    {
        case eGBStateNone:
        case eGBStateReady:
        case eGBStatePrepare:
        case eGBStateBattle:
        default:
            dwRemainTime = _dwNextTime - tNow;
            break;
    }
    return dwRemainTime;
}		// -----  end of function GetRemainTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetState
//  Description:  获取当前状态
// =====================================================================================
EGBState CGuildBattleMgr::GetState () const
{
    return _eState;
}		// -----  end of function GetState  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetFieldInfo
//  Description:  获取战场信息
// =====================================================================================
bool CGuildBattleMgr::GetFieldInfo(CPlayerPtr pPlayer, UINT64 qwGuildID, const string& strGuildName,
        EGBResult& eResult, TVecFieldInfo& vecFieldInfo)
{
    if (!pPlayer)
    {
        eResult = eGBResultFailed;
        LOG_DBG << "eGBResultFailed";
        return false;
    }
    if (!qwGuildID)
    {
        eResult = eGBResultNoGuild;
        LOG_DBG << "eGBResultNoGuild";
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgGuildKick, BuildStrVec("没有定Message      "));
        pPlayer->SendPkg(strPkg);
        return false;
    }

    EGBState eState = _eState;
    // 如果是在准备地图发送详细战场
    // 如果实在战斗地图则发送简略信息
    CGuildBattleFieldPtr pField;
    switch (_eState)
    {
        case eGBStateReady: // 报名阶段
        case eGBStatePrepare: // 布阵阶段
            {
                if (_mapSignUpField.find(qwGuildID) == _mapSignUpField.end())
                {
                    CGuildBattleFieldPtr pField (new CGuildBattleField());
                    if (!pField)
                    {
                        eResult = eGBResultFailed;
                        LOG_DBG << "eGBResultFailed";
                        return false;
                    }
                    pField->SetGuildID(qwGuildID, eGBSideA);
                    pField->SetGuildName(strGuildName, eGBSideA);
                    _mapSignUpField.insert(make_pair(qwGuildID, pField));
                }


                auto it = _mapSignUpField.find(qwGuildID);
                if (it == _mapSignUpField.end())
                {
                    eResult = eGBResultNotInBattle;
                    LOG_DBG << "eGBResultNotInBattle";
                    return false;
                }
                pField = it->second;
                CGameMapPtr pMap = pPlayer->GetMap();
                if (pMap && pMap->GetMapID() == CGuildBattleConfigMgr::Instance().GetPrepareMapID())
                    eState = eGBStatePrepare;
                else
                    eState = eGBStateReady;
            }
            break;

        case eGBStateBattle:
            {
                if (_qwEmptyBattleGuildID == qwGuildID && _pEmptyBattle)
                {
                    pField = _pEmptyBattle->GetField();
                    CGameMapPtr pMap = pPlayer->GetMap();
                    if (pMap && pMap->GetMapID() == CGuildBattleConfigMgr::Instance().GetPrepareMapID())
                        eState = eGBStatePrepare;
                    else
                        eState = eGBStateReady;
                }
                else 
                {
                    auto it = _mapGuildBattleIndex.find(qwGuildID);

                    if (it == _mapGuildBattleIndex.end())
                    {
                        eResult = eGBResultNotInBattle;
                        return false;
                    }
                    else
                    {
                        pField = it->second->GetField();
                        CGameMapPtr pMap = pPlayer->GetMap();
                        if (pMap && pMap->GetMapID() == CGuildBattleConfigMgr::Instance().GetPrepareMapID())
                            eState = eGBStatePrepare;
                        else if (pMap && CGuildBattleConfigMgr::Instance().IsBattleMap(pMap->GetMapID()))
                            eState = eGBStateBattle;
                        else
                            eState = eGBStateReady;
                    }
                }
            }
            break;
        default:
            eResult = eGBResultWrongTime;
            LOG_DBG << "eGBResultWrongTime";
            return false;
    }


    bool bRet = false;
    if (!pField)
    {
        eResult = eGBResultFailed;
        return false;
    }
    SFieldInfo sFieldInfo;
    bRet = pField->GetAllInfo(sFieldInfo, eState, qwGuildID);

    if (bRet)
    {
        eResult = eGBResultSuccess;
        vecFieldInfo.push_back(sFieldInfo);
    }
    else
        eResult = eGBResultFailed;
    return bRet;
}		// -----  end of function GetFieldInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  IsGuildJoined
//  Description:  帮派是否参加了帮派战
// =====================================================================================
bool CGuildBattleMgr::IsGuildJoined (UINT64 qwGuildID) const
{
    return _mapSignUpField.find(qwGuildID) != _mapSignUpField.end();
}		// -----  end of function IsGuildJoined  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  IsPlayerInGuildBattleField
//  Description:  玩家是否在帮派战地图
// =====================================================================================
bool CGuildBattleMgr::IsPlayerInGuildBattleField(UINT64 qwGuildID) const
{
    if (_eState == eGBStateNone)
        return false;
    return _mapAllPlayer.find(qwGuildID) == _mapAllPlayer.end()?false:true;
}		// -----  end of function IsPlayerInGuildBattleField  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSpotType
//  Description:  获取玩家所在据点
// =====================================================================================
EGBSpot CGuildBattleMgr::GetSpotType (CPlayerPtr pPlayer) const
{
    if (!pPlayer)
        return eGBSpotNone;
    auto it = _mapAllPlayer.find(pPlayer->GetRoleID());
    if (it != _mapAllPlayer.end() && it->second->pSpot.lock())
        return it->second->pSpot.lock()->GetType();
    else
        return eGBSpotNone;
}		// -----  end of function GetSpotType  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSpotSide
//  Description:  获取玩家所在的方向
// =====================================================================================
EGBSide CGuildBattleMgr::GetSpotSide (CPlayerPtr pPlayer) const
{
    if (!pPlayer)
        return eGBSideInvalid;
    auto it = _mapUserID2GuildID.find(pPlayer->GetRoleID());
    if (it != _mapUserID2GuildID.end())
    {
        auto it2 = _mapGuildBattleIndex.find(it->second);
        if (it2 != _mapGuildBattleIndex.end())
        {
            if (_eState == eGBStatePrepare)
                return eGBSideA;
            CGuildBattleFieldPtr pField = it2->second->GetField();
            if (pField)
                return pField->GetGuildSide(it->second);
            else
                return eGBSideA;
        }
        else
            return eGBSideA;
    }
    else
        return eGBSideInvalid;
}		// -----  end of function GetSpotSide  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildID
//  Description:  获取玩家对应的帮派ID
// =====================================================================================
UINT64 CGuildBattleMgr::GetGuildID (CPlayerPtr pPlayer) const
{
    if (!pPlayer)
        return 0;
    auto it = _mapUserID2GuildID.find(pPlayer->GetRoleID());
    if (it == _mapUserID2GuildID.end())
        return 0;
    else
        return it->second;
}		// -----  end of function GetGuildID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSignUpField
//  Description:  获得帮派对应的报名场地
// =====================================================================================
CGuildBattleFieldPtr CGuildBattleMgr::GetSignUpField (UINT64 qwGuildID)
{
    auto it = _mapSignUpField.find(qwGuildID);
    if (it == _mapSignUpField.end())
        return NULL;
    else
        return it->second;
}		// -----  end of function GetSignUpField  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBattleField
//  Description:  获得战斗场地
// =====================================================================================
CGuildBattleFieldPtr  CGuildBattleMgr::GetBattleField (UINT64 qwGuildID)
{
    auto it = _mapGuildBattleIndex.find(qwGuildID);
    if (it == _mapGuildBattleIndex.end())
        return NULL;
    return it->second->GetField();
}		// -----  end of function GetBattleField  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSpotPlayer
//  Description:  获取据点玩家
// =====================================================================================
SGuildBattleSpotPlayerPtr CGuildBattleMgr::GetSpotPlayer (UINT64 qwRoleID)
{
    auto it = _mapAllPlayer.find(qwRoleID);
    if (it == _mapAllPlayer.end())
        return NULL;
    else
        return it->second;
}		// -----  end of function GetSpotPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSpotInfo
//  Description:  获取据点详细信息
// =====================================================================================
bool CGuildBattleMgr::GetSpotInfo(CPlayerPtr pPlayer, EGBSpot eType, TVecSpotInfo& rvecSpotInfo, EGBResult& eResult)
{
    if (!pPlayer || eType >= eGBSpotMax)
    {
        eResult = eGBResultFailed;
        return false;
    }
    auto it = _mapAllPlayer.find(pPlayer->GetRoleID());
    if (it == _mapAllPlayer.end())
    {
        eResult = eGBResultNotInBattle;
        return false;
    }

    CGuildBattlePtr pBattle;
    UINT64 qwGuildID = _mapUserID2GuildID[pPlayer->GetRoleID()];
    if (_qwEmptyBattleGuildID == qwGuildID && _pEmptyBattle)
        pBattle = _pEmptyBattle;
    else
    {
        auto it2 = _mapGuildBattleIndex.find(qwGuildID);
        if (it2 == _mapGuildBattleIndex.end())
        {
            if (qwGuildID == _qwEmptyBattleGuildID && _pEmptyBattle)
                eResult = eGBResultFailed;
            else
                eResult = eGBResultNotInBattle;
            return false;
        }
        pBattle = it2->second;
    }

    switch(_eState)
    {
        case eGBStateBattle:
        case eGBStatePrepare:
            break;
        default:
            eResult = eGBResultWrongTime;
            return false;
    }
    return pBattle->GetSpotInfo(pPlayer, eType, rvecSpotInfo, eResult);
}		// -----  end of function GetSpotInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllMapPlayers
//  Description:  获取准备地图所有玩家
// =====================================================================================
bool CGuildBattleMgr::GetAllMapPlayers(UINT64 qwGuildID, TVecUINT64& vecRoleID) const
{
    auto it = _mapPrepareMap.find(qwGuildID);
    if (it == _mapPrepareMap.end())
        return false;
    TMapID2Player mapPlayers = it->second->GetPlayerMap();
    for (auto it2 = mapPlayers.begin(); it2 != mapPlayers.end(); ++it2)
    {
        CPlayerPtr pPlayer = it2->second.lock();
        if (pPlayer)
        {
            vecRoleID.push_back(pPlayer->GetRoleID());
            LOG_DBG << pPlayer->GetName() << ".";
        }
    }
    return true;
}		// -----  end of function GetAllMapPlayers  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllOB
//  Description:  获取某一帮派战所有观战者 // =====================================================================================
bool CGuildBattleMgr::GetAllOB(UINT64 qwGuildID, TVecUINT64& vecRoleID) const
{
    auto it = _mapGuildBattleIndex.find(qwGuildID);
    if (it == _mapGuildBattleIndex.end())
        return false;
    it->second->GetAllOB(vecRoleID);
    return true;

}		// -----  end of function GetAllOB  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBattleInfo
//  Description:  获取战报信息
// =====================================================================================
bool CGuildBattleMgr::GetBattleInfo (CPlayerPtr pPlayer, EGBSpot eSpotType, EGBBattleResult& eResult, TVecBattleData& rvecBattleData)
{
    if (!pPlayer || eSpotType >= eGBSpotMax)
    {
        eResult = eGBBattleFailed;
        return false;
    }

    auto it = _mapUserID2GuildID.find(pPlayer->GetRoleID());
    if (it == _mapUserID2GuildID.end())
    {
        eResult = eGBBattleFailed;
        return false;
    }

    UINT64 qwGuildID = it->second;
    auto it2 = _mapGuildBattleIndex.find(qwGuildID);
    if (it2 == _mapGuildBattleIndex.end())
    {
        eResult = eGBBattleNotInGuild;
        return false;
    }
    return it2->second->GetBattleInfo(eSpotType, eResult, rvecBattleData);
}		// -----  end of function GetBattleInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSkillInfo
//  Description:  获取帮派战技能信息
// =====================================================================================
bool CGuildBattleMgr::GetSkillInfo(CPlayerPtr pPlayer, UINT64 qwGuildID, EGBSkillResult& eResult, TVecSkillInfo& rvecSkillInfo)
{
    if (!pPlayer)
    {
        eResult = eGBSkillFailed;
        return false;
    }
    CGuildBattleFieldPtr pField;
    switch(_eState)
    {
        case eGBStatePrepare:
            pField = GetSignUpField(qwGuildID);
            break;
        case eGBStateBattle:
            pField = GetBattleField(qwGuildID);
            break;
        default:
            eResult = eGBSkillWrongTime;
            return false;
    }
    
    /*if (!pField)
    {
        eResult = eGBSkillFailed;
        return false;
    }
    
    pField->GetSkillInfo(rvecSkillInfo, qwGuildID, eResult);*/
    
    SGuildBattleSpotPlayerPtr pGuildBattleSpotPlayerPtr = GetSpotPlayer(pPlayer->GetRoleID());
    if (!pGuildBattleSpotPlayerPtr)
    {
        eResult = eGBSkillFailed;
        return false;
    }

    for (auto it=pGuildBattleSpotPlayerPtr->setSkillBuff.begin(); it!=pGuildBattleSpotPlayerPtr->setSkillBuff.end(); ++it)
    {
        rvecSkillInfo.push_back(SSkillInfo(*it));
    }

    eResult = eGBSkillSuccess;
    return true;
}		// -----  end of function GetSkillInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildScore
//  Description:  
// =====================================================================================
UINT32 CGuildBattleMgr::GetGuildScore (UINT64 qwGuildID) const
{
    auto it = _mapBattleScore.find(qwGuildID);
    if (it == _mapBattleScore.end())
        return 0;
    else
        return it->second;
}		// -----  end of function GetGuildScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildRank
//  Description:  
// =====================================================================================
UINT32 CGuildBattleMgr::GetGuildRank (UINT64 qwGuildID) const
{
    auto it = _mapGuildRank.find(qwGuildID);
    if (it == _mapGuildRank.end())
        return _mapGuildRank.size() + 1;
    else
        return it->second;
}		// -----  end of function GetGuildRank  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayerScore
//  Description:  
// =====================================================================================
UINT32 CGuildBattleMgr::GetPlayerScore (UINT64 qwRoleID) const
{
    auto it = _mapPlayerScore.find(qwRoleID);
    if (it == _mapPlayerScore.end())
        return 0;
    else
        return it->second;
}		// -----  end of function GetPlayerScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetDumpInfo
//  Description:  获得调试信息
// =====================================================================================
string CGuildBattleMgr::GetDumpInfo (CPlayerPtr pPlayer) const
{
    ostringstream strInfo;
#ifdef PROT_USE_XML
    strInfo << "State: " << EnumValToStr(_eState) << "\n";
#else
    strInfo << "State: " << static_cast<UINT32>(_eState) << "\n";
#endif
    strInfo << "Remain Time: " << GetRemainTime() << "\n";
    strInfo << "byBattleCount = " << static_cast<UINT32>(_byBattleCount) << ".\n";
    if (pPlayer)
    {
        auto it = _mapAllPlayer.find(pPlayer->GetRoleID());
        if (it != _mapAllPlayer.end())
            strInfo << it->second->pSpot.lock()->GetDumpInfo() << "\n";
        auto it2 = _mapUserID2GuildID.find(pPlayer->GetRoleID());
        if (it2 != _mapUserID2GuildID.end())
        {
            auto it3 = _mapGuildBattleIndex.find(it2->second);
            if (it3 != _mapGuildBattleIndex.end())
            {
                CGuildBattleFieldPtr pField = it3->second->GetField();
                if (!pField)
                    strInfo << pField->GetDumpInfo() << "\n";
            }
        }
    }
    return strInfo.str();
}		// -----  end of function GetDumpInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UserSignUp
//  Description:  玩家报名帮派战
// =====================================================================================
bool CGuildBattleMgr::UserSignUp(CPlayerPtr pPlayer, UINT64 qwGuildID, UINT16 wLevel, const string& strGuildName, UINT32 dwScore, EGBSpot eType, EGBSignUpResult& eResult)
{
    if (!pPlayer || !qwGuildID || eType >= eGBSpotMax)
        return false;
    switch(_eState)
    {
        case eGBStateReady:     // 报名阶段报名
            {
                if (_mapAllPlayer.find(pPlayer->GetRoleID()) != _mapAllPlayer.end())
                {
                    eResult = eGBSignUpRepeat;
                    return false;
                }

                auto it = _mapSignUpField.find(qwGuildID);
                if (it == _mapSignUpField.end())
                {
                    CGuildBattleFieldPtr pField (new CGuildBattleField());
                    if (!pField)
                    {
                        eResult = eGBSignUpFailed;
                        return false;
                    }
                    pField->SetGuildID(qwGuildID, eGBSideA);
                    pField->SetGuildName(strGuildName, eGBSideA);
                    _mapSignUpField.insert(make_pair(qwGuildID, pField));
                }

                auto it2 = _mapPrepareMap.find(qwGuildID);
                if (it2 == _mapPrepareMap.end())
                {
                    CGameMapPtr pMap = CMapMgr::CreateMap(CGuildBattleConfigMgr::Instance().GetPrepareMapID());
                    if (!pMap)
                    {
                        LOG_CRI << "Can't create Prepare map.";
                        eResult = eGBSignUpFailed;
                        return false;
                    }
                    LOG_DBG << "Create PrepareMap(" << qwGuildID << ").";
                    _mapPrepareMap.insert(make_pair(qwGuildID, pMap));
                }

                SGuildBattleSpotPlayerPtr pSpotPlayer = _mapSignUpField[qwGuildID]->AddPlayer(pPlayer,eGBSideA, eType, eResult);
                if (pSpotPlayer)
                {
                    _mapAllPlayer.insert(make_pair(pPlayer->GetRoleID(), pSpotPlayer));
                    _mapGuildScore[dwScore].insert(qwGuildID);
                    _mapUserID2GuildID.insert(make_pair(pPlayer->GetRoleID(), qwGuildID));
                    string strPkg = g_GuildBattleProtS.BuildPkg_StateNotify(_eState, GetBattleCount(), GetRemainTime(), pSpotPlayer->pSpot.lock()->GetType(), eGBSideA);
                    pPlayer->SendPkg(strPkg);
                    pSpotPlayer->pSpot.lock()->NotifySpotInfo(_eState, qwGuildID);
                    _mapGuildLevel[qwGuildID] = wLevel;

                    TVecINT32 vecParam;
                    ostringstream strInfo;
                    strInfo << qwGuildID;
                    pPlayer->OnEvent(eEventType_GuildBattleSignUp, vecParam, strInfo.str());

                    return true;
                }
                else
                    return false;
            }
            break;
        case eGBStateBattle:    // 战斗阶段，只能进入准备场中，不能进入据点中
        case eGBStatePrepare:   // 对战前布阵阶段，进入实际据点中
            {
                if (_mapAllPlayer.find(pPlayer->GetRoleID()) != _mapAllPlayer.end())
                {
                    eResult = eGBSignUpRepeat;
                    return false;
                }
                auto it = _mapSignUpField.find(qwGuildID);
                if (it == _mapSignUpField.end())
                {
                    eResult = eGBSignUpWrongTime;
                    return false;
                }

                auto it2 = _mapGuildBattleIndex.find(qwGuildID);
                if (it2 == _mapGuildBattleIndex.end())
                {
                    eResult = eGBSignUpFailed;
                    return false;
                }

                if (pPlayer->HasBuff(13))
                {
                    eResult = eGBSignUpEscape;
                    return false;
                }

                CGuildBattleFieldPtr pField2 = it2->second->GetField();
                UINT32 dwPreCount = pField2->GetSpotPlayerCount(qwGuildID, eType);
                SGuildBattleSpotPlayerPtr pSpotPlayer = _mapSignUpField[qwGuildID]->AddPlayer(pPlayer,eGBSideA, eType, eResult, 0, dwPreCount);
                if (pSpotPlayer)
                {
                    _mapAllPlayer.insert(make_pair(pPlayer->GetRoleID(), pSpotPlayer));
                    _mapGuildScore[dwScore].insert(qwGuildID);
                    _mapUserID2GuildID.insert(make_pair(pPlayer->GetRoleID(), qwGuildID));
                    string strPkg = g_GuildBattleProtS.BuildPkg_StateNotify(_eState, GetBattleCount(), GetRemainTime(), pSpotPlayer->pSpot.lock()->GetType(), eGBSideA);
                    pPlayer->SendPkg(strPkg);
                    _mapGuildLevel[qwGuildID] = wLevel;

                    TVecINT32 vecParam;
                    ostringstream strInfo;
                    strInfo << qwGuildID;
                    pPlayer->OnEvent(eEventType_GuildBattleSignUp, vecParam, strInfo.str());
                    return true;
                }
                else
                    return false;
            }
            break;
        default:
            eResult = eGBSignUpWrongTime;
            return false;
    }

    eResult = eGBSignUpFailed;
    return false;
}		// -----  end of function UserSignUp  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UserEnter
//  Description:  玩家进入帮派战
// =====================================================================================
bool CGuildBattleMgr::UserEnter (CPlayerPtr pPlayer, EGBEnterResult& eResult)
{
    if (!pPlayer)
    {
        eResult = eGBEnterFailed;
        LOG_CRI << "pPlayer == NULL.";
        return false;
    }

    auto it = _mapUserID2GuildID.find(pPlayer->GetRoleID());
    if (it == _mapUserID2GuildID.end())
    {
        eResult = eGBEnterNotInGuild;
        return false;
    }

    UINT64 qwGuildID = it->second;
    auto it2 = _mapPrepareMap.find(qwGuildID);
    if (it2 == _mapPrepareMap.end())
    {
        eResult = eGBEnterFailed;
        LOG_CRI << "Find PrepareMap(" << qwGuildID << ") error.";
        return false;
    }
    switch(_eState)
    {
        case eGBStateReady:
        case eGBStatePrepare:
        case eGBStateBattle:
            {
                SPoint oPoint;
                it2->second->GetRandPoint(oPoint);
                if(!pPlayer->JumpMap(it2->second, oPoint))
                {
                    LOG_CRI << "Error when Enter(" << pPlayer->GetRoleID() << ").";
                    eResult = eGBEnterFailed;
                    return false;
                }
                eResult = eGBEnterSuccess;
            }
            break;
        default:
            eResult = eGBEnterWrongTime;
            return false;
    }
    return true;
}		// -----  end of function UserEnter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UserQuit
//  Description:  玩家退出帮派战
// =====================================================================================
bool CGuildBattleMgr::UserQuit ( CPlayerPtr pPlayer, EGBQuitResult& eResult )
{
    if (!pPlayer)
    {
        eResult = eGBQuitFailed;
        return false;
    }
    auto it = _mapUserID2GuildID.find(pPlayer->GetRoleID());
    if (it == _mapUserID2GuildID.end())
    {
        eResult = eGBQuitNotInBattle;
        return false;
    }
    UINT64 qwGuildID = it->second;
    switch(_eState)
    {
        case eGBStateReady:
            {
                UINT16 wMapID = pPlayer->GetBaseInfo().wMapID;
                SPoint oPoint(pPlayer->GetBaseInfo().fX, pPlayer->GetBaseInfo().fY);
                if(wMapID == 0)
                {
                    LOG_CRI << "NO MAP";
                    wMapID = 1;
                }
                pPlayer->JumpMap(wMapID, oPoint);
                pPlayer->SetCurMapID(wMapID);
                pPlayer->SetPoint(oPoint);
                eResult = eGBQuitSuccess;
                return true;
            }
            break;
        case eGBStatePrepare:
            {
                UINT16 wMapID = pPlayer->GetBaseInfo().wMapID;
                SPoint oPoint(pPlayer->GetBaseInfo().fX, pPlayer->GetBaseInfo().fY);
                if(wMapID == 0)
                {
                    LOG_CRI << "NO MAP";
                    wMapID = 1;
                }
                pPlayer->JumpMap(wMapID, oPoint);
                pPlayer->SetCurMapID(wMapID);
                pPlayer->SetPoint(oPoint);
                eResult = eGBQuitSuccess;
            }
        case eGBStateBattle:
            {
                auto it2 = _mapGuildBattleIndex.find(qwGuildID);
                if (it2 != _mapGuildBattleIndex.end())
                    it2->second->PlayerQuit(pPlayer);
            }
            break;
        default:
            eResult = eGBQuitWrongTime;
            return false;
    }
    _mapUserID2GuildID.erase(it);
    auto it2 = _mapSignUpField.find(qwGuildID);
    if (it2 == _mapSignUpField.end())
        eResult = eGBQuitNotInBattle;
    else
        eResult = it2->second->RemovePlayer(pPlayer);

    _mapAllPlayer.erase(pPlayer->GetRoleID());

    string strPkg = g_GuildBattleProtS.BuildPkg_StateNotify(_eState, GetBattleCount(), GetRemainTime(), eGBSpotNone, eGBSideInvalid);

    pPlayer->SendPkg(strPkg);
    UINT16 wMapID = pPlayer->GetBaseInfo().wMapID;
    SPoint oPoint(pPlayer->GetBaseInfo().fX, pPlayer->GetBaseInfo().fY);
    if(wMapID == 0)
    {
        LOG_CRI << "NO MAP";
        wMapID = 1;
    }
    pPlayer->JumpMap(wMapID, oPoint);
    pPlayer->SetCurMapID(wMapID);
    pPlayer->SetPoint(oPoint);
    pPlayer->RegenAllHP();
    eResult = eGBQuitSuccess; // XXX: 退出到这里就是成功退出了
    pPlayer->AddBuff(13);
    if (eResult == eGBQuitSuccess)
        return true;
    else
        return false;
}		// -----  end of function UserQuit  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UserOnline
//  Description:  玩家上线
// =====================================================================================
bool CGuildBattleMgr::UserOnline (CPlayerPtr pPlayer)
{
    if (!pPlayer)
        return true;
    auto it = _mapUserID2GuildID.find(pPlayer->GetRoleID());
    if (it == _mapUserID2GuildID.end())
        return true;
    UINT64 qwGuildID = it->second;
    auto it2 = _mapGuildBattleIndex.find(qwGuildID);
    if (it2 == _mapGuildBattleIndex.end())
        return true;
    it2->second->UserOnline(pPlayer->GetRoleID());
    return it2->second->IsInBattle(pPlayer->GetRoleID())?false:true;

}		// -----  end of function UserOnline  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UserOffline
//  Description:  TODO: 玩家下线
// =====================================================================================
void CGuildBattleMgr::UserOffline (CPlayerPtr pPlayer)
{
    if (!pPlayer)
        return;
    auto it = _mapAllPlayer.find(pPlayer->GetRoleID());
    if (it == _mapAllPlayer.end())
        return;
}		// -----  end of function UserOffline  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UserAdjust
//  Description:  玩家调整作战位置
// =====================================================================================
void CGuildBattleMgr::UserAdjust(CPlayerPtr pPlayer, UINT64 qwRoleID, EGBSpot eSpotType, UINT8 byIndex, EGBAdjustResult& eResult)
{
    if (!pPlayer || eSpotType >= eGBSpotMax)
    {
        eResult = eGBAdjustFailed;
        return;
    }
    switch(_eState)
    {
        case eGBStatePrepare:
            break;
        default:
            {
                eResult = eGBAdjustWrongTime;
                string strPkg;
                strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgGuildNotBattleTime);
                pPlayer->SendPkg(strPkg);
            }
            return;
    }
    auto it2 = _mapUserID2GuildID.find(qwRoleID);
    if (it2 == _mapUserID2GuildID.end())
    {
        LOG_DBG << "Can't find _mapUserID2GuildID[" << qwRoleID << "].";
        eResult = eGBAdjustFailed;
        return;
    }
    auto it3 = _mapSignUpField.find(it2->second);
    if (it3 == _mapSignUpField.end())
    {
        LOG_DBG << "Can't find _mapSignUpField[" << it2->second << "].";
        eResult = eGBAdjustFailed;
        return;
    }
    it3->second->Adjust(qwRoleID, eSpotType, byIndex, eResult);
}		// -----  end of function UserAdjust  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetStatus
//  Description:  设置帮派战状态
// =====================================================================================
void CGuildBattleMgr::SetStatus(EGBState eState)
{ 
    _eState = eState;
    g_Game2CenterGuildBattleC.Send_SetState(eState);
}		// -----  end of function SetStatus  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UpdateNextTime
//  Description:  更新下一个状态的时间
// =====================================================================================
void CGuildBattleMgr::UpdateNextTime ()
{
}		// -----  end of function UpdateNextTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  StartSignUp
//  Description:  帮派战开始报名
// =====================================================================================
void CGuildBattleMgr::StartSignUp()
{
    SetStatus(eGBStateReady);
    _byBattleCount = 0;
    _dwNextTime = _dwBeginTime;
    _bNeedSignNotify = true;

    //  广播通知
    string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgGuildWarCheckIn);
    NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());
    strPkg = g_GuildBattleProtS.BuildPkg_StateNotify(_eState, GetBattleCount(), GetRemainTime(), eGBSpotNone, eGBSideInvalid);
    NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());

}		// -----  end of function StartSignUp  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  EnterNotify
//  Description:  催人进入
// =====================================================================================
void CGuildBattleMgr::EnterNotify ()
{
    TSetUINT64 setGuildID;
    for (auto& rPair :_mapSignUpField)
    {
        if ((rPair.second)->GetPlayerCount(eGBSideA) >= CGuildBattleConfigMgr::Instance().GetMinUserCount()) // 报名人数满足上限
        {
            TVecUINT64 vecRoleID;
            rPair.second->GetPlayerNotInPrepareMap(vecRoleID);
            for (auto & rID : vecRoleID)
            {
                CUserPtr pUser = CUserMgr::GetUserByUserID(rID);
                if (pUser)
                {
                    CPlayerPtr pPlayer = pUser->GetPlayer();
                    if (pPlayer)
                    {
                        string strPkg = g_GuildBattleProtS.BuildPkg_SignupEnterNotify();
                        pPlayer->SendPkg(strPkg);
                    }
                }
            }
        }
    }
}		// -----  end of function EnterNotify  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  StartBattle
//  Description:  帮派战开始
// =====================================================================================
void CGuildBattleMgr::StartBattle(UINT32 dwTodayTime)
{
    SetStatus(eGBStatePrepare);
    _dwNextTime = _dwBeginTime + CGuildBattleConfigMgr::Instance().GetPrepareTime();

    // 剔除报名人数以及参战人数不足的帮派
    CleanupInvalidGuild();
    _dwLastExpCheckTime = dwTodayTime;
    StartNewRound();
}		// -----  end of function StartBattle  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  StartNewRound
//  Description:  开启一轮新的战役
// =====================================================================================
void CGuildBattleMgr::StartNewRound ()
{
    // 将满足要求的帮派放入帮派战地图

    // 按分数排序
    TVecUINT64 vecGuildID;
    for (auto it = _mapGuildScore.begin(); it != _mapGuildScore.end(); ++it)
    {
        TSetUINT64 setGuildID = it->second;
        while(!(setGuildID.empty()))
        {
            UINT32 dwIndex = CRandom::RandInt(0, setGuildID.size() - 1);
            auto it2 = setGuildID.begin();
            advance(it2, dwIndex);
            if (_mapSignUpField.find(*it2) != _mapSignUpField.end())
                vecGuildID.push_back(*it2);
            setGuildID.erase(it2);
        }
    }

    // 每四个随机匹配进入战场
    size_t szCount = vecGuildID.size();
    size_t szIndex = 0;
    while(szIndex < szCount)
    {
        if (szIndex + 4 <= szCount)
            std::random_shuffle(vecGuildID.begin() + szIndex, vecGuildID.begin() + szIndex + 4);       
        else
            std::random_shuffle(vecGuildID.begin() + szIndex, vecGuildID.end());       
        szIndex += 4;
    }

    CGuildBattlePtr pBattle;
    for (auto it = vecGuildID.begin(); it != vecGuildID.end(); ++it)
    {
        if (!pBattle)
        {
            pBattle = CGuildBattlePtr(new CGuildBattle);
            pBattle->InitField(_mapSignUpField[*it], eGBSideA, eGBSideA);
            pBattle->GetField()->SetBattle(pBattle);
            _mapGuildBattleIndex.insert(make_pair(_mapSignUpField[*it]->GetGuildID(eGBSideA), pBattle));
        }
        else
        {
            pBattle->InitField(_mapSignUpField[*it], eGBSideB, eGBSideA);
            _vecGuildBattle.push_back(pBattle);
            _mapGuildBattleIndex.insert(make_pair(_mapSignUpField[*it]->GetGuildID(eGBSideA), pBattle));
            pBattle = NULL;
        }
    }
    if (pBattle)
    {
        _pEmptyBattle = pBattle;
        CGuildBattleFieldPtr pField = _pEmptyBattle->GetField();
        if (pField)
            _qwEmptyBattleGuildID = pField->GetGuildID(eGBSideA);
        _vecGuildBattle.push_back(pBattle);
        pBattle = NULL;
    }

    SyncGuildName();

    // 初始化相关战斗的地图
    for (auto it = _vecGuildBattle.begin(); it != _vecGuildBattle.end(); ++it)
    {
        (*it)->SetState(eGBStatePrepare);
        (*it)->NotifyBattleStartInfo();
    }
}		// -----  end of function StartNewRound  ----- //

struct SGuildRank
{
    SGuildRank(UINT32 dwScore, UINT64 qwGuildID, UINT16 wLevel):
        dwScore(dwScore), qwGuildID(qwGuildID), wLevel(wLevel)
    { }

    UINT32 dwScore;
    UINT64 qwGuildID;
    UINT16 wLevel;
    bool operator < (const SGuildRank& rRank) const
    {
        if (qwGuildID == rRank.qwGuildID)
            return false;
        if (dwScore == rRank.dwScore)
        {
            if (wLevel == rRank.wLevel)
                return qwGuildID > rRank.qwGuildID;
            else
                return wLevel > rRank.wLevel;
        }
        else
            return dwScore > rRank.dwScore;
    }
};

// ===  FUNCTION  ======================================================================
//         Name:  EndBattle
//  Description:  结束帮派战
// =====================================================================================
void CGuildBattleMgr::EndBattle(bool bFinal, bool bForce /* = false */)
{
    for (auto& rPair:_mapPrepareMap)
    {
        TMapID2Player mapPlayers = rPair.second->GetPlayerMap();
        for (auto it2 = mapPlayers.begin(); it2 != mapPlayers.end(); ++it2)
        {
            CPlayerPtr pPlayer = it2->second.lock();
            SPoint oPoint;
            pPlayer->JumpMap(rPair.second, oPoint, 0, true);
        }

    }
    for (auto & pBattle : _vecGuildBattle)
    {
        pBattle->EndBattle();
        if (pBattle != _pEmptyBattle)
            pBattle->CleanMap(bFinal);
        pBattle->CleanToPrepare();
    }

    // 重新结算分数排名
    map<UINT64, UINT64> mapGuildScore;
    for (auto& rPair:_mapGuildScore)
    {
        for (auto& rGuildID : rPair.second)
        {
            mapGuildScore[rGuildID]  = rPair.first + _mapBattleScoreOnce[rGuildID];
            g_Game2CenterGuildBattleC.Send_AddGuildScore(rGuildID, _mapBattleScoreOnce[rGuildID]);
        }
    }
    _mapGuildScore.clear();
    for (auto& rPair : mapGuildScore)
    {
        _mapGuildScore[rPair.second].insert(rPair.first);
    }

    set<SGuildRank> setRank;
    for (auto& rPair : _mapBattleScore)
    {
        SGuildRank sRank(rPair.second, rPair.first, _mapGuildLevel[rPair.first]);
        setRank.insert(sRank);
    }

    _mapGuildRank.clear();
    UINT32 dwRank = 1;
    for (auto it = setRank.begin(); it != setRank.end(); ++it, ++dwRank)
    {
        _mapGuildRank[(*it).qwGuildID] = dwRank;
    }

    g_Game2CenterGuildBattleC.Send_SyncGuildRank();
    _mapBattleScoreOnce.clear();

    _vecGuildBattle.clear();
    _mapGuildBattleIndex.clear();
    _qwEmptyBattleGuildID = 0;
    _pEmptyBattle = NULL;
    if (bFinal)
    {
        ResultSum();
        Reset();
        if (!bForce)
        {
            string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgGuildWarEnd);
            NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());
        }
        _byBattleCount = 0;
    }
    else
    {
        for(auto& rPair : _mapAllPlayer)
        {
            UINT64 qwRoleID = rPair.first;
            if (rPair.second)
            {
                CPlayerPtr pPlayer = (rPair.second)->pPlayer.lock();
                if (pPlayer)
                {
                    g_Game2CenterGuildBattleC.Send_GetPanelInfo(qwRoleID,
                            [qwRoleID, pPlayer, this](UINT8 byRet, UINT32 dwSelfScore, UINT32 dwGuildScore, UINT32 dwGuildRank)
                            {
                                string strPkg = g_GuildBattleProtS.BuildPkg_PanelInfoNotify(GetPlayerScore(qwRoleID), dwGuildScore, dwGuildRank);
                                pPlayer->SendPkg(strPkg);
                            });
                }
            }
        }
        ++ _byBattleCount;
    }
}		// -----  end of function EndBattle  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ResultSum
//  Description:  结算
// =====================================================================================
void CGuildBattleMgr::ResultSum ()
{
    // 结算帮贡和经验值
    map <UINT64, TVecMemberScore> mapGuildMemberScore;
    for (auto it = _mapPlayerScore.begin(); it != _mapPlayerScore.end(); ++it)
    {
        g_Game2CenterCommC.Send_AddGuildContribution(it->first, it->second);
        auto it2 = _mapUserID2GuildID.find(it->first);
        if (it2 == _mapUserID2GuildID.end())
            continue;
        mapGuildMemberScore[it2->second].push_back(SMemberScore(it->first, it->second));
    }

    // 结算个人帮派积分
    for (auto it = _mapBattleScore.begin(); it != _mapBattleScore.end(); ++it)
    {
        g_Game2CenterGuildBattleC.Send_AddMemberScore(it->first, mapGuildMemberScore[it->first]);
        //帮派id，参与时间，我的帮派排名
        SGuildBattleSpotPlayerPtr pSpotPlayer = _mapAllPlayer[it->first];
        if (pSpotPlayer)
        {
            CPlayerPtr pPlayer = pSpotPlayer->pPlayer.lock();
            if (pPlayer)
            {
                TVecINT32 vecParam;
                vecParam.push_back(_mapUserJoinTime[it->first]);
                vecParam.push_back(999); // FIXME: 这里结算不合适
                ostringstream strInfo;
                strInfo << _mapUserID2GuildID[it->first];
                pPlayer->OnEvent(eEventType_GuildBattleEnd, vecParam, strInfo.str());
            }
        }
    }
}		// -----  end of function ResultSum  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Reset
//  Description:  重置帮派战情况
// =====================================================================================
void CGuildBattleMgr::Reset ( )
{
    _mapSignUpField.clear();      // 帮派战报名情况
    _mapGuildScore.clear();       // 帮派战历史积分
    _mapUserID2GuildID.clear();   // 玩家ID检索帮派ID

    // 玩家踢回自己的地方
    for  (auto it = _mapPrepareMap.begin(); it != _mapPrepareMap.end(); ++it)
    {
        TMapID2Player mapPlayers = it->second->GetPlayerMap();
        for (auto it2 = mapPlayers.begin(); it2 != mapPlayers.end(); ++it2)
        {
            CPlayerPtr pPlayer = it2->second.lock();
            UINT16 wMapID = pPlayer->GetBaseInfo().wMapID;
            SPoint oPoint(pPlayer->GetBaseInfo().fX, pPlayer->GetBaseInfo().fY);
            if(wMapID == 0)
            {
                LOG_CRI << "NO MAP";
                wMapID = 1;
            }
            pPlayer->JumpMap(wMapID, oPoint);
            pPlayer->SetCurMapID(wMapID);
            pPlayer->SetPoint(oPoint);
        }
    }
    _mapPrepareMap.clear();       // 帮派战准备地图

    _mapAllPlayer.clear();        // 所有玩家的索引
    SetStatus(eGBStateNone);
    _mapBattleScoreOnce.clear();
    _mapBattleScore.clear();
    _mapPlayerScore.clear();
    _mapPlayerWinCombo.clear();
    _mapUserJoinTime.clear();
}		// -----  end of function Reset  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ForceEndBattle
//  Description:  强制结束所有帮派战
// =====================================================================================
void CGuildBattleMgr::ForceEndBattle ()
{
    EndBattle(true, true);
}		// -----  end of function ForceEndBattle  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SyncGuildName
//  Description:  同步对手帮派名称至自己的报名场地信息
// =====================================================================================
void CGuildBattleMgr::SyncGuildName ()
{
    for (auto it = _mapSignUpField.begin(); it != _mapSignUpField.end(); ++it)
    {
        it->second->SetGuildID(0, eGBSideB);
        it->second->SetGuildName("", eGBSideB);
    }

    for (auto it = _vecGuildBattle.begin(); it != _vecGuildBattle.end(); ++it)
    {
        if (!*it)
            continue;
        CGuildBattleFieldPtr pField = (*it)->GetField();
        if (!pField)
            continue;
        UINT64 qwGuildIDA = pField->GetGuildID(eGBSideA);
        UINT64 qwGuildIDB = pField->GetGuildID(eGBSideB);
        if (qwGuildIDA && qwGuildIDB)
        {
            string strGuildNameA = pField->GetGuildName(eGBSideA);
            string strGuildNameB = pField->GetGuildName(eGBSideB);

            auto it  = _mapSignUpField.find(qwGuildIDA);
            auto it2 = _mapSignUpField.find(qwGuildIDB);
            if (it != _mapSignUpField.end())
            {
                it->second->SetGuildID(qwGuildIDB, eGBSideB);
                it->second->SetGuildName(strGuildNameB, eGBSideB);
            }

            if (it2 != _mapSignUpField.end())
            {
                it2->second->SetGuildID(qwGuildIDA, eGBSideB);
                it2->second->SetGuildName(strGuildNameA, eGBSideB);
            }
        }
        else if (!qwGuildIDA)
        {
            auto it  = _mapSignUpField.find(qwGuildIDA);
            if (it != _mapSignUpField.end())
            {
                it->second->SetGuildID(0, eGBSideB);
                it->second->SetGuildName("", eGBSideB);
            }
        }
        else if (!qwGuildIDB)
        {
            auto it  = _mapSignUpField.find(qwGuildIDB);
            if (it != _mapSignUpField.end())
            {
                it->second->SetGuildID(0, eGBSideB);
                it->second->SetGuildName("", eGBSideB);
            }
        }
    }
}		// -----  end of function SyncGuildName  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  BuySkill
//  Description:  购买帮派技能
// =====================================================================================
bool CGuildBattleMgr::BuySkill(CPlayerPtr pPlayer, UINT64 qwGuildID, EGBSkill eSkillType, EGBSkillResult& eResult)
{
    if (!pPlayer)
    {
        eResult = eGBSkillFailed;
        return false;
    }
    CGuildBattleFieldPtr pField;
    switch(_eState)
    {
        case eGBStatePrepare:
            pField = GetSignUpField(qwGuildID);
            break;
        //case eGBStateBattle:
            //pField = GetBattleField(qwGuildID);
            //break;
        default:
            eResult = eGBSkillWrongTime;
            return false;
    }
    if (!pField)
    {
        eResult = eGBSkillFailed;
        return false;
    }
    return pField->BuySkill(pPlayer, qwGuildID, eSkillType, eResult);
}		// -----  end of function BuySkill  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyPreparePlayerInfo
//  Description:  通知准备地图上所有人信息 
// =====================================================================================
void CGuildBattleMgr::NotifyPreparePlayerInfo (UINT64 qwGuildID, const string& strData) const
{
    auto it = _mapPrepareMap.find(qwGuildID);
    if (it == _mapPrepareMap.end())
        return;
    TMapID2Player mapPlayers = it->second->GetPlayerMap();
    for (auto it2 = mapPlayers.begin(); it2 != mapPlayers.end(); ++it2)
    {
        CPlayerPtr pPlayer = it2->second.lock();
        if (pPlayer)
            pPlayer->SendPkg(strData);
    }
}		// -----  end of function NotifyPreparePlayerInfo  ----- //


// ===  FUNCTION  ======================================================================
//         Name:  GMOpen
//  Description:  GM开启活动
// =====================================================================================
bool CGuildBattleMgr::GMOpen()
{
    ForceEndBattle();
    CGuildBattleConfigMgr::Instance().ForceStart();

    time_t tNow = Time::Now();

    _dwAlarmTime        = tNow - 300;
    _dwReadyTime        = tNow + 10;
    _dwReadyNotifyTime  = tNow + 15;
    _dwBeginTime        = tNow + 45;
    _dwEndTime          = _dwBeginTime + CGuildBattleConfigMgr::Instance().GetDebugLastTime();
    ClearEvent();
    CDayActivity::SetStatus(eDayActivityStatusAlarm);
    return true;
}		// -----  end of function GMOpen  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnAlarm
//  Description:  程序开始准备
// =====================================================================================
bool CGuildBattleMgr::OnAlarm()
{
    CDayActivity::OnAlarm();
    //LOG_DBG << "CGuildBattleMgr::OnAlarm()";
    return true;
}		// -----  end of function OnAlarm  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnReady
//  Description:  开始通知
// =====================================================================================
void CGuildBattleMgr::OnReady()
{
    //LOG_DBG << "CGuildBattleMgr::OnReady()";
    CDayActivity::OnReady();
    StartSignUp();
}		// -----  end of function OnReady  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnBegin
//  Description:  正式开始
// =====================================================================================
void CGuildBattleMgr::OnBegin()
{
    CDayActivity::OnBegin();
    //LOG_DBG << "CGuildBattleMgr::OnBegin()";
    UINT32 dwTodayTime = Time::Now() - Time::TheDay();
    StartBattle(dwTodayTime);
}		// -----  end of function OnBegin  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnEnd
//  Description:  活动结束
// =====================================================================================
void CGuildBattleMgr::OnEnd()
{
    CDayActivity::OnEnd();
    SetStatus(eGBStateNone);
    EndBattle(true);
}		// -----  end of function OnEnd  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnEvent
//  Description:  注册时间触发
// =====================================================================================
void CGuildBattleMgr::OnEvent(SActEventData& oSActEventData)
{
    switch(oSActEventData.dwEventID)
    {
        default:
            break;
    }
}		// -----  end of function OnEvent  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnReBegin
//  Description:  服务器重启,处于活动期间的处理
// =====================================================================================
void CGuildBattleMgr::OnReBegin()
{
    ForceEndBattle();
    CGuildBattleConfigMgr::Instance().ForceStart();
}		// -----  end of function OnReBegin  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UpdateState
//  Description:  更新状态
// =====================================================================================
void CGuildBattleMgr::UpdateState(time_t tNow)
{
    CDayActivity::UpdateState(tNow);
}		// -----  end of function UpdateState  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ResetState
//  Description:  重置原始状态
// =====================================================================================
void CGuildBattleMgr::ResetState()
{
}		// -----  end of function ResetState  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddPlayerMap
//  Description:  增加全局索引
// =====================================================================================
void CGuildBattleMgr::AddPlayerMap (SGuildBattleSpotPlayerPtr pSpotPlayer)
{
    if (!pSpotPlayer)
        return;
    CPlayerPtr pPlayer = pSpotPlayer->pPlayer.lock();
    if (pPlayer)
        _mapAllPlayer[pPlayer->GetRoleID()] = pSpotPlayer;
}		// -----  end of function AddPlayerMap  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  RemovePlayerMap
//  Description:  CGuildBattleSpot移除玩家时清除全局的索引
// =====================================================================================
void CGuildBattleMgr::RemovePlayerMap (UINT64 qwRoleID)
{
    _mapUserID2GuildID.erase(qwRoleID);
    _mapAllPlayer.erase(qwRoleID);
}		// -----  end of function RemovePlayerMap  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ResetPlayerMap
//  Description:  重新更新玩家信息
// =====================================================================================
void CGuildBattleMgr::ResetPlayerMap (SGuildBattleSpotPlayerPtr pSpotPlayer)
{
    if (!pSpotPlayer)
        return;
    CPlayerPtr pPlayer = pSpotPlayer->pPlayer.lock();
    if (pPlayer)
        _mapAllPlayer[pPlayer->GetRoleID()] = pSpotPlayer;
}		// -----  end of function ResetPlayerMap  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddGuildScore
//  Description:  增加帮派积分
// =====================================================================================
bool CGuildBattleMgr::AddGuildScore (UINT64 qwGuildID, UINT32 dwScore)
{
    LOG_DBG << "qwGuildID = " << qwGuildID << ", dwScore = " << dwScore << ".";
    if (qwGuildID)
    {
        _mapBattleScoreOnce[qwGuildID] += dwScore;
        _mapBattleScore[qwGuildID] += dwScore;
        return true;
    }
    return false;
}		// -----  end of function AddGuildScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddPlayerScore
//  Description:  增加玩家积分
// =====================================================================================
bool CGuildBattleMgr::AddPlayerScore(UINT64 qwRoleID, UINT32 dwScore)
{
    LOG_DBG << "qwRoleID = " << qwRoleID << ", dwScore = " << dwScore << ".";
    _mapPlayerScore[qwRoleID] += dwScore;
    return true;
}		// -----  end of function AddPlayerScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddPlayerBattleCount
//  Description:  更新玩家获胜场数
// =====================================================================================
void CGuildBattleMgr::AddPlayerBattleCount (UINT64 qwRoleID, bool bWin)
{
    if (bWin)
    {
        ++_mapPlayerWinCombo[qwRoleID];
        LOG_DBG << "qwRoleID = " << qwRoleID << ", bWin = " << (bWin?"true":"false") << "(" << _mapPlayerWinCombo[qwRoleID] << "), "
            << "Add score = " << CGuildBattleConfigMgr::Instance().GetWinComboScore(_mapPlayerWinCombo[qwRoleID]) << ".";
        _mapPlayerScore[qwRoleID] += CGuildBattleConfigMgr::Instance().GetWinComboScore(_mapPlayerWinCombo[qwRoleID]);
    }
    else
        LOG_DBG << "qwRoleID = " << qwRoleID << ", bWin = " << (bWin?"true":"false") << ".";
        _mapPlayerWinCombo[qwRoleID] = 0;
}		// -----  end of function AddPlayerBattleCount  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  BattleProcess
//  Description:  帮派战具体流程
// =====================================================================================
void CGuildBattleMgr::BattleProcess(time_t tNow)
{
    UINT32 dwTodayTime = tNow - Time::TheDay();
    switch(_eState)
    {
        case eGBStatePrepare:
            if (tNow >= _dwNextTime) // 准备状态-》战斗状态
            {
                SetStatus(eGBStateBattle);
                string strPkg = g_GuildBattleProtS.BuildPkg_StateNotify(_eState, GetBattleCount(), GetRemainTime(), eGBSpotNone, eGBSideInvalid);
                NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());
                _dwNextTime += CGuildBattleConfigMgr::Instance().GetBattleTime();
                for (auto& pBattle : _vecGuildBattle)
                {
                    pBattle->InitMap(); // 将准备地图中的报名情况同步至Battle中
                    pBattle->SetState(eGBStateBattle);
                    pBattle->InitTime(dwTodayTime);
                    if (pBattle != _pEmptyBattle)
                    {
                        pBattle->InitPlayer(); //所有玩家拉入战斗据点地图
                        pBattle->NotifyAllOBSpotInfo();
                    }
                    else // 轮空帮派通知不需要战斗
                    {
                        _pEmptyBattle->RefreshState(false);
                        string strPkg;
                        strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgGuildWarWinNoEnemy, BuildStrVec(_pEmptyBattle->GetCurrentScore(eGBSideA)));
                        TVecUINT64 vecRoleID;
                        g_Game2CenterCommC.Send_NotifyGuildInfo(pBattle->GetField()->GetGuildID(eGBSideA), vecRoleID, strPkg);
                        _pEmptyBattle->NotifyFieldInfo();
                    }
                    CGuildBattleFieldPtr pField = pBattle->GetField();
                }
            }
            break;
        case eGBStateBattle:
            if (tNow >= _dwNextTime) // 战斗状态-》准备状态
            {
                SetStatus(eGBStatePrepare);
                string strPkg = g_GuildBattleProtS.BuildPkg_StateNotify(_eState, GetBattleCount(), GetRemainTime(), eGBSpotNone, eGBSideInvalid);
                NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());
                _dwNextTime += CGuildBattleConfigMgr::Instance().GetPrepareTime();
                EndBattle(false);
                StartNewRound();
            }
            break;
        default:
            break;
    }
    for (auto& pBattle : _vecGuildBattle)
    {
        if (pBattle != _pEmptyBattle)
            pBattle->Process(dwTodayTime);
    }
    ExpProcess(dwTodayTime);
}		// -----  end of function BattleProcess  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ExpProcess
//  Description:  经验值结算定时处理
// =====================================================================================
void CGuildBattleMgr::ExpProcess (UINT32 dwTodayTime)
{
    if (dwTodayTime >= _dwLastExpCheckTime)
    {
        for (auto it = _mapAllPlayer.begin(); it != _mapAllPlayer.end(); ++it)
        {
            CPlayerPtr pPlayer = (it->second->pPlayer).lock();
            if (pPlayer)
            {
                CGameMapPtr pMap = pPlayer->GetMap();
                if (pMap)
                {
                    UINT16 wMapID = pMap->GetMapID();
                    if(wMapID == CGuildBattleConfigMgr::Instance().GetPrepareMapID()
                            || CGuildBattleConfigMgr::Instance().IsBattleMap(wMapID))
                    {
                        UINT8 byLevel = pPlayer->GetLevel();
                        pPlayer->AddExp(CGuildBattleConfigMgr::Instance().GetExp(byLevel));
                    }
                }
                _mapUserJoinTime[pPlayer->GetRoleID()] += CGuildBattleConfigMgr::Instance().GetExpTime();
            }
        }
        _dwLastExpCheckTime += CGuildBattleConfigMgr::Instance().GetExpTime();
    }
}		// -----  end of function ExpProcess  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CleanupInvalidGuild
//  Description:  清除不符合参战要求的帮派
// =====================================================================================
void CGuildBattleMgr::CleanupInvalidGuild ()
{
    TSetUINT64 setGuildID;
    for (auto it = _mapSignUpField.begin(); it != _mapSignUpField.end();)
    {
        if ((it->second)->GetPlayerCount(eGBSideA) >= CGuildBattleConfigMgr::Instance().GetMinUserCount()) // 报名人数满足上限
        {
            TVecUINT64 vecRoleID;
            it->second->GetPlayerNotInPrepareMap(vecRoleID);
            for (auto & rID : vecRoleID)
            {
                CUserPtr pUser = CUserMgr::GetUserByUserID(rID);
                if (pUser)
                {
                    CPlayerPtr pPlayer = pUser->GetPlayer();
                    if (pPlayer)
                    {
                        _mapUserID2GuildID.erase(rID);
                        it->second->RemovePlayer(pPlayer);

                        _mapAllPlayer.erase(rID);

                        string strPkg = g_GuildBattleProtS.BuildPkg_StateNotify(_eState, GetBattleCount(), GetRemainTime(), eGBSpotNone, eGBSideInvalid);
                        pPlayer->SendPkg(strPkg);
                    }
                }

            }
            ++it;
        }
        else // 报名人数不足
        {
            TVecString vecString;
            g_Game2CenterGuildBattleC.Send_InfoNotify(it->first, eMsgGuildWarGuildSignInFaild, vecString);
            setGuildID.insert(it->first);
            _mapSignUpField.erase(it++);
        }
    }

    for (auto & rID : setGuildID)
    {
        // 人数不足，玩家踢回世界地图
        auto it2 = _mapPrepareMap.find(rID);
        if (it2 == _mapPrepareMap.end())
            continue;

        TMapID2Player mapPlayers = it2->second->GetPlayerMap();
        for (auto it3 = mapPlayers.begin(); it3 != mapPlayers.end(); ++it3)
        {
            CPlayerPtr pPlayer = it3->second.lock();
            UINT16 wMapID = pPlayer->GetBaseInfo().wMapID;
            SPoint oPoint(pPlayer->GetBaseInfo().fX, pPlayer->GetBaseInfo().fY);
            if(wMapID == 0)
            {
                LOG_CRI << "NO MAP";
                wMapID = 1;
            }
            pPlayer->JumpMap(wMapID, oPoint);
            pPlayer->SetCurMapID(wMapID);
            pPlayer->SetPoint(oPoint);
            _mapAllPlayer.erase(pPlayer->GetRoleID());
            _mapUserID2GuildID.erase(pPlayer->GetRoleID());
        }
        _mapPrepareMap.erase(it2);
    }
}		// -----  end of function CleanupInvalidGuild  ----- //


