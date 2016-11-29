// =====================================================================================
//
//       Filename:  GuildBattleField.cpp
//
//    Description:  帮派战场地/据点
//
//        Version:  1.0
//        Created:  07/24/2014 05:42:39 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#include "GuildBattleField.h"
#include "GuildBattleSpot.h"
#include "GuildBattleConfig.h"
#include "GuildBattleMgr.h"
#include "GuildBattle.h"

#include "Protocols.h"

#include "Player.h"
#include "User.h"
#include "EventMgr.h"

CGuildBattleField::CGuildBattleField()
{
    _qwGuildID[0] = 0;
    _qwGuildID[1] = 0;

    for (UINT8 byIndex = eGBSpotNone + 1; byIndex < eGBSpotMax; ++byIndex)
    {
        EGBSpot eSpotType = static_cast<EGBSpot>(byIndex);
        CGuildBattleSpotPtr pSpot(new CGuildBattleSpot(eSpotType));
        _mapSpot.insert(make_pair(eSpotType, pSpot));
    }
}

CGuildBattleField::~CGuildBattleField()
{
}

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildID
//  Description:  获取帮派ID
// =====================================================================================
UINT64 CGuildBattleField::GetGuildID (EGBSide eSide) const
{
    if (eSide >= eGBSideInvalid)
        return 0;
    return _qwGuildID[eSide];
}		// -----  end of function GetGuildID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildName
//  Description:  获得参战双方帮派名称
// =====================================================================================
const string&  CGuildBattleField::GetGuildName (EGBSide eSide ) const
{
    return _strGuildName[eSide];
}		// -----  end of function GetGuildName  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildSide
//  Description:  根据帮派名称获取帮派所在方向
// =====================================================================================
EGBSide CGuildBattleField::GetGuildSide(UINT64 qwGuildID) const
{
    if (_qwGuildID[eGBSideA] == qwGuildID)
        return eGBSideA;
    if (_qwGuildID[eGBSideB] == qwGuildID)
        return eGBSideB;
    return eGBSideInvalid;
}		// -----  end of function GetGuildSide  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllInfo
//  Description:  获取该战场的所有数据
// =====================================================================================
bool CGuildBattleField::GetAllInfo (SFieldInfo& rFieldInfo, EGBState eState, UINT64 qwGuildID /* = 0 */) const
{
    rFieldInfo.strGuildNameA =  _strGuildName[eGBSideA];
    rFieldInfo.strGuildNameB =  _strGuildName[eGBSideB];
    for (auto it = _mapSpot.begin(); it != _mapSpot.end(); ++it)
    {
        switch(eState)
        {
            case eGBStateBattle:
                {
                    SSpotBriefInfoPtr pSpotInfo (new SSpotBriefInfo);
                    if (it->second->GetAllInfo(*pSpotInfo))
                        rFieldInfo.vecSpotInfo.push_back(pSpotInfo);
                    else
                        return false;
                }
                break;
            case eGBStatePrepare:
                {
                    SSpotAllInfoPtr pSpotInfo (new SSpotAllInfo);
                    if (it->second->GetAllInfo(*pSpotInfo))
                        rFieldInfo.vecSpotInfo.push_back(pSpotInfo);
                    else
                        return false;
                }
                break;
            case eGBStateReady:
                {
                    SSpotReadyInfoPtr pSpotInfo (new SSpotReadyInfo);
                    if (it->second->GetAllInfo(*pSpotInfo))
                        rFieldInfo.vecSpotInfo.push_back(pSpotInfo);
                    else
                        return false;
                }
                break;
            default:
                break;
        }
    }
    return true;
}		// -----  end of function GetAllInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSpotInfo
//  Description:  获取某一个据点的信息
// =====================================================================================
bool CGuildBattleField::GetSpotInfo(CPlayerPtr pPlayer, EGBSpot eSpotType, TVecSpotInfo& rvecSpotInfo, EGBResult& eResult) const
{
    // 直接发送缓存的据点信息
    auto it2 = _mapSpotInfoCache.find(eSpotType);
    if (it2 != _mapSpotInfoCache.end())
    {
        rvecSpotInfo.insert(rvecSpotInfo.end(), (it2->second).begin(), (it2->second).end());
        eResult = eGBResultSuccess;
        return true;
    }

    // 没有缓存信息，直接发送最新信息
    auto it = _mapSpot.find(eSpotType);
    if (it == _mapSpot.end())
    {
        eResult = eGBResultFailed;
        return false;
    }
    SSpotAllInfoPtr pSpotInfo (new SSpotAllInfo);
    if (it->second->GetAllInfo(*pSpotInfo))
    {
        rvecSpotInfo.push_back(pSpotInfo);
        eResult = eGBResultSuccess;
        return true;
    }
    eResult = eGBResultFailed;
    return false;
}		// -----  end of function GetSpotInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayerCount
//  Description:  获得某一方的参战成员数量
// =====================================================================================
UINT32 CGuildBattleField::GetPlayerCount (EGBSide eSide) const
{
    if (eSide >= eGBSideInvalid)
        return 0;
    UINT32 dwCount = 0;
    for (auto it = _mapSpot.begin(); it != _mapSpot.end(); ++it)
    {
        dwCount += it->second->GetPlayerCount(eSide);
    }
    return dwCount;
}		// -----  end of function GetPlayerCount  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSpotPlayerCount
//  Description:  获得某一方的参战成员数量
// =====================================================================================
UINT32 CGuildBattleField::GetSpotPlayerCount (UINT64 qwGuildID, EGBSpot eType) const
{
    EGBSide eSide = eGBSideInvalid;
    if (_qwGuildID[0] == qwGuildID)
        eSide = eGBSideA;
    if (_qwGuildID[1] == qwGuildID)
        eSide = eGBSideB;
    auto it = _mapSpot.find(eType);
    if (it == _mapSpot.end())
        return 0;
    return it->second->GetPlayerCount(eSide);
}

// ===  FUNCTION  ======================================================================
//         Name:  InitMap
//  Description:  初始化地图
// =====================================================================================
void CGuildBattleField::InitMap ()
{
    CGuildBattleFieldPtr pFiledA = CGuildBattleMgr::Instance().GetSignUpField(_qwGuildID[eGBSideA]);
    CGuildBattleFieldPtr pFiledB = CGuildBattleMgr::Instance().GetSignUpField(_qwGuildID[eGBSideB]);
    CatFieldInfo(pFiledA, eGBSideA, eGBSideA, true);
    CatFieldInfo(pFiledB, eGBSideB, eGBSideA, true);
    for (auto it = _mapSpot.begin(); it != _mapSpot.end(); ++it)
    {
        it->second->InitMap(_qwGuildID[eGBSideA], _qwGuildID[eGBSideB]);
    }
}		// -----  end of function InitMap  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitPlayer
//  Description:  将玩家初始化至该地图上
// =====================================================================================
void CGuildBattleField::InitPlayer ()
{
    for (auto & rPair : _mapSpot)
    {
        rPair.second->InitPlayer(_setSkillBuff);
    }
}		// -----  end of function InitPlayer  ----- //

void CGuildBattleField::SetBattle(CGuildBattlePtr pBattle)
{
    _pBattle = pBattle;
}

// ===  FUNCTION  ======================================================================
//         Name:  SetGuildID
//  Description:  设置帮派ID
// =====================================================================================
void CGuildBattleField::SetGuildID (UINT64 qwGuildID, EGBSide eGBSide)
{
    if (eGBSide < eGBSideInvalid)
        _qwGuildID[eGBSide] = qwGuildID;
}		// -----  end of function SetGuildID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetGuildName
//  Description:  设置帮派名称
// =====================================================================================
void CGuildBattleField::SetGuildName (const string& strGuildName, EGBSide eGBSide)
{
    if (eGBSide < eGBSideInvalid)
        _strGuildName[eGBSide] = strGuildName;
}		// -----  end of function SetGuildName  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  InitInfo
//  Description:  初始化基本战场参数
// =====================================================================================
bool CGuildBattleField::InitInfo (CGuildBattleFieldPtr pField, EGBSide eSide , EGBSide eSide2)
{
    if (!pField)
        return false;
    _qwGuildID[eSide] = pField->GetGuildID(eSide2);
    _strGuildName[eSide] = pField->GetGuildName(eSide2);
    return true;
}		// -----  end of function InitInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CatFieldInfo
//  Description:  从另一个场地初始化该场地信息
// =====================================================================================
bool CGuildBattleField::CatFieldInfo (CGuildBattleFieldPtr pField, EGBSide eSide , EGBSide eSide2, bool bCleanSrc /*  = false */)
{
    if (!pField)
        return false;
    for (auto it = pField->_mapSpot.begin(); it != pField->_mapSpot.end(); ++it)
    {
        auto it2 = _mapSpot.find(it->first);
        if (it2 == _mapSpot.end())
        {
            CGuildBattleSpotPtr pSpot(new CGuildBattleSpot(it->first));
            auto pairRet = _mapSpot.insert(make_pair(it->first, pSpot));
            it2 = pairRet.first;
        }
        TVecUINT64 vecRoleID;
        it2->second->CatSpotInfo(it->second, eSide, eSide2, bCleanSrc, vecRoleID);
        for (auto it3 = vecRoleID.begin(); it3 != vecRoleID.end(); ++it3)
        {
            _mapPlayerID2Spot[*it3] = it2->first;
            if (bCleanSrc)
                pField->_mapPlayerID2Spot.erase(*it3);
        }
    }
    /*
    for (auto it = pField->_mapPlayerID2Spot.begin(); it != pField->_mapPlayerID2Spot.end(); ++it)
    {
        _mapPlayerID2Spot[it->first] = it->second;
    }
    if (bCleanSrc)
        pField->_mapPlayerID2Spot.clear();
    */
    _setSkillBuff[eSide].clear();
    _setSkillBuff[eSide].swap(pField->_setSkillBuff[eSide2]);
    return true;
}		// -----  end of function CatFieldInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddPlayer
//  Description:  玩家加入帮派战据点
//                报名
//                布阵调整
// =====================================================================================
SGuildBattleSpotPlayerPtr CGuildBattleField::AddPlayer ( CPlayerPtr pPlayer, EGBSide eSide, EGBSpot eSpotType, 
        EGBSignUpResult& eResult, UINT8 byIndex /* = 0 */, UINT32 dwPreCount /* = 0 */)
{
    if (!pPlayer || eSpotType >= eGBSpotMax)
    {
        eResult = eGBSignUpFailed;
        return NULL;
    }
    auto it = _mapPlayerID2Spot.find(pPlayer->GetRoleID());
    if (it != _mapPlayerID2Spot.end())
    {
        eResult = eGBSignUpRepeat;
        return _mapSpot[it->second]->GetSpotPlayer(pPlayer->GetRoleID());
    }
    if (GetState() == eGBStateBattle)  // 战斗时间无法加入战斗
    {
        eResult = eGBSignUpWrongTime;
        return NULL;
    }
    SGuildBattleSpotPlayerPtr pSpotPlayer = _mapSpot[eSpotType]->AddPlayer(pPlayer, eSide, eResult, byIndex, dwPreCount);
    if (eResult == eGBSignUpSuccess)
    {
        _mapPlayerID2Spot.insert(make_pair(pPlayer->GetRoleID(), eSpotType));
        _mapSpot[eSpotType]->NotifySpotInfo(GetState(), GetGuildID(eSide));
    }
    return pSpotPlayer;
}		// -----  end of function AddPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ForceAddPlayer
//  Description:  玩家加入帮派战据点
//                报名
//                布阵调整
// =====================================================================================
SGuildBattleSpotPlayerPtr CGuildBattleField::ForceAddPlayer ( CPlayerPtr pPlayer, EGBSide eSide, EGBSpot eSpotType, 
        EGBSignUpResult& eResult, UINT8 byIndex)
{
    if (!pPlayer)
    {
        eResult = eGBSignUpFailed;
        LOG_CRI << "eGBSignUpFailed";
        return NULL;
    }
    if (GetState() == eGBStateBattle)  // 战斗时间无法加入战斗
    {
        eResult = eGBSignUpWrongTime;
        LOG_CRI << "eGBSignUpWrongTime";
        return NULL;
    }
    SGuildBattleSpotPlayerPtr pSpotPlayer = _mapSpot[eSpotType]->AddPlayer(pPlayer, eSide, eResult, byIndex, 0);
    if (eResult == eGBSignUpSuccess)
    {
        _mapPlayerID2Spot[pPlayer->GetRoleID()] = eSpotType;
    }
    return pSpotPlayer;
}		// -----  end of function ForceAddPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  RemovePlayer
//  Description:  玩家退出帮派战据点
// =====================================================================================
EGBQuitResult CGuildBattleField::RemovePlayer (CPlayerPtr pPlayer)
{
    if (!pPlayer)
        return eGBQuitFailed;

    auto it = _mapPlayerID2Spot.find(pPlayer->GetRoleID());
    if (it == _mapPlayerID2Spot.end())
        return eGBQuitFailed;

    EGBSide eSide = _mapSpot[it->second]->RemovePlayer(pPlayer);
    _mapPlayerID2Spot.erase(pPlayer->GetRoleID());
    if (eSide == eGBSideA || eSide == eGBSideB)
    {
        TVecUINT64 vecRoleID;
        vecRoleID.push_back(pPlayer->GetRoleID());
        _mapSpot[it->second]->NotifySpotInfo(GetState(), GetGuildID(eSide));
        return eGBQuitSuccess;
    }
    else
        return eGBQuitFailed;
}		// -----  end of function RemovePlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CleanMap
//  Description:  清除帮派战地图数据
// =====================================================================================
void CGuildBattleField::CleanMap (bool bFinal)
{
    for (auto it = _mapSpot.begin(); it != _mapSpot.end(); ++it)
    {
        it->second->CleanMap(bFinal);
    }
}		// -----  end of function CleanMap  ----- //


// ===  FUNCTION  ======================================================================
//         Name:  GetPlayerNotInPrepareMap
//  Description:  清除不在准备地图上的玩家
// =====================================================================================
void CGuildBattleField::GetPlayerNotInPrepareMap (TVecUINT64& rvecRoleID)
{
    for (auto it = _mapSpot.begin(); it != _mapSpot.end(); ++it)
    {
        it->second->GetPlayerNotInPrepareMap(rvecRoleID);
    }
}		// -----  end of function GetPlayerNotInPrepareMap  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Adjust
//  Description:  玩家据点位置调整
// =====================================================================================
void CGuildBattleField::Adjust (UINT64 qwRoleID, EGBSpot eSpotType, UINT8 byIndex, EGBAdjustResult& eResult)
{
    auto it = _mapPlayerID2Spot.find(qwRoleID);
    if (it == _mapPlayerID2Spot.end() || eSpotType >= eGBSpotMax)
    {
        LOG_CRI << "_mapPlayerID2Spot.end().";
        eResult = eGBAdjustFailed;
        return;
    }
    EGBSpot eOldSpot = it->second;
    EGBSide eSide = _mapSpot[it->second]->GetPlayerSide(qwRoleID);
    SGuildBattleSpotPlayerPtr pSpotPlayer = _mapSpot[it->second]->GetSpotPlayer(qwRoleID);
    if (!pSpotPlayer)
    {
        LOG_CRI << "Can't find Role(" << qwRoleID << ");";
        eResult = eGBAdjustFailed;
        return;
    }
    CPlayerPtr pPlayer = pSpotPlayer->pPlayer.lock();

    EGBSignUpResult eResult2;
    pSpotPlayer = ForceAddPlayer(pPlayer, eSide, eSpotType, eResult2, byIndex);
    if (eResult2 == eGBSignUpSuccess)
    {
        if (eOldSpot != eSpotType)
        {
            _mapSpot[eOldSpot]->RemovePlayer(pPlayer, false, pSpotPlayer);
            _mapSpot[eOldSpot]->NotifySpotInfo(eGBStatePrepare, eSide);
        }
        _mapSpot[eSpotType]->NotifySpotInfo(eGBStatePrepare, eSide);
        NotifyFieldInfo(eGBStateReady, eSide);
        NotifyFieldInfo(eGBStatePrepare, eSide);
        eResult = eGBAdjustSuccess;
        string strPkg = g_GuildBattleProtS.BuildPkg_StateNotify(eGBStatePrepare, CGuildBattleMgr::Instance().GetBattleCount(), CGuildBattleMgr::Instance().GetRemainTime(), eSpotType, eSide);
        if (pPlayer)
            pPlayer->SendPkg(strPkg);
        CGuildBattleMgr::Instance().ResetPlayerMap(pSpotPlayer);
    }
    else if (eResult2 == eGBSignUpSpotFull)
        eResult = eGBAdjustSpotFull;
    else
    {
        LOG_CRI << "eResult = " << static_cast<UINT32>(eResult2) << ".";
        eResult = eGBAdjustFailed;
    }
}		// -----  end of function Adjust  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddOB
//  Description:  增加观战人员
// =====================================================================================
void CGuildBattleField::AddOB (UINT64 qwRoleID, EGBSpot eSpotType)
{
    auto it = _mapSpot.find(eSpotType);
    if (it == _mapSpot.end())
        return;
    it->second->AddOB(qwRoleID);
}		// -----  end of function AddOB  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  RemoveOB
//  Description:  移除观察人员
// =====================================================================================
void CGuildBattleField::RemoveOB (UINT64 qwRoleID, EGBSpot eSpotType)
{
    auto it = _mapSpot.find(eSpotType);
    if (it == _mapSpot.end())
        return;
    it->second->RemoveOB(qwRoleID);
}		// -----  end of function RemoveOB  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PopBattlePlayerPairs
//  Description:  获取可以战斗的成员
// =====================================================================================
void CGuildBattleField::PopBattlePlayerPairs(TVecGBPlayerPtr& rvecPlayerA, TVecGBPlayerPtr& rvecPlayerB, UINT8 byCount /* = 3 */)
{
    for (auto it = _mapSpot.begin(); it != _mapSpot.end(); ++it)
    {
        it->second->PopBattlePlayerPairs(rvecPlayerA, rvecPlayerB, byCount);
    }
}

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayerSpot
//  Description:  获取玩家所在的据点
// =====================================================================================
EGBSpot CGuildBattleField::GetPlayerSpot (UINT64 qwRoleID) const
{
    auto it = _mapPlayerID2Spot.find(qwRoleID);
    if (it == _mapPlayerID2Spot.end())
        return eGBSpotNone;
    else
        return it->second;
}		// -----  end of function GetPlayerSpot  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetState
//  Description:  获取当前帮派战状态
// =====================================================================================
EGBState CGuildBattleField::GetState () const
{
    if (_pBattle.lock())
        return _pBattle.lock()->GetState();
    else
        return eGBStateNone;
}		// -----  end of function GetState  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetBattleInfo
//  Description:  获取战报信息 
// =====================================================================================
bool CGuildBattleField::GetBattleInfo(EGBSpot eSpotType, EGBBattleResult& eResult, TVecBattleData& rvecBattleData) const
{
    auto it = _mapSpot.find(eSpotType);
    if (it == _mapSpot.end())
    {
        eResult = eGBBattleFailed;
        return false;
    }
    if(it->second->GetAllBattleInfo(rvecBattleData))
    {
        eResult = eGBBattleSuccess;
        return true;
    }
    else
    {
        eResult = eGBBattleFailed;
        return false;
    }
}		// -----  end of function GetBattleInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ResetOBSpot
//  Description:  重新更新观察者列表
// =====================================================================================
void CGuildBattleField::ResetOBSpot (map<UINT64, EGBSpot>& rmapOBSpot) const
{
    rmapOBSpot.clear();
    for (auto it = _mapSpot.begin(); it != _mapSpot.end(); ++it)
    {
        it->second->AppendOBSpot(rmapOBSpot);
    }
}		// -----  end of function ResetOBSpot  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UpdateScore
//  Description:  更新场地分数信息
// =====================================================================================
bool CGuildBattleField::UpdateScore(UINT32 dwScore[2], EGBSide& eBiggerSide) const
{
    bool bFinal = true;
    UINT32 dwMaxWinnerScore = 0;
    for (auto it = _mapSpot.begin(); it != _mapSpot.end(); ++it)
    {
        UINT32 dwWinnerScore = 0;
        EGBSide eWinnerSide = eGBSideInvalid;
        bool bTmp = it->second->GetScore(dwWinnerScore, eWinnerSide);
        if (!bTmp)
            bFinal = false;
        else
            dwScore[eWinnerSide] += dwWinnerScore;
        if (dwMaxWinnerScore < dwWinnerScore)
        {
            eBiggerSide = eWinnerSide;
            dwMaxWinnerScore = dwWinnerScore;
        }
    }
    return bFinal;
}		// -----  end of function UpdateScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSkillInfo
//  Description:  获取帮派技能信息
// =====================================================================================
bool CGuildBattleField::GetSkillInfo(TVecSkillInfo& rvecSkillInfo, UINT64 qwGuildID, EGBSkillResult& eResult) const
{
    if (_qwGuildID[0] == qwGuildID)
    {
        for (auto it = _setSkillBuff[0].begin(); it != _setSkillBuff[0].end(); ++it)
        {
            rvecSkillInfo.push_back(SSkillInfo(*it));
        }
    }
    if (_qwGuildID[1] == qwGuildID)
    {
        for (auto it = _setSkillBuff[1].begin(); it != _setSkillBuff[1].end(); ++it)
        {
            rvecSkillInfo.push_back(SSkillInfo(*it));
        }
    }
    return true;
}		// -----  end of function GetSkillInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRoleID
//  Description:  获取某方所有成员ID
// =====================================================================================
void CGuildBattleField::GetRoleID(EGBSide eSide, TVecUINT64& rvecRoleID) const
{
    if (eSide >= eGBSideInvalid)
        return;
    for (auto it = _mapSpot.begin(); it != _mapSpot.end(); ++it)
    {
        it->second->GetRoleID(eSide, rvecRoleID);
    }
}		// -----  end of function GetRoleID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSkill
//  Description:  获取某方的所有技能
// =====================================================================================
const set<EGBSkill>& CGuildBattleField::GetSkill (EGBSide eSide) const
{
    return _setSkillBuff[eSide];
}		// -----  end of function GetSkill  ----- //
// ===  FUNCTION  ======================================================================
//         Name:  GetDumpInfo
//  Description:  获取调试输出信息 
// =====================================================================================
string CGuildBattleField::GetDumpInfo () const
{
#ifndef _DEBUG
    return "";
#else
    ostringstream strInfo;
    for (auto it = _mapSpot.begin(); it != _mapSpot.end(); ++it)
    {
#ifdef PROT_USE_XML
        strInfo << "据点: " << EnumValToStr(it->first) << "\n";
#else
        strInfo << "据点: " << static_cast<UINT32>(it->first) << "\n";
#endif
        strInfo << it->second->GetDumpInfo() << "\n";
    }
    return strInfo.str();
#endif // #ifndef _DEBUG
}		// -----  end of function GetDumpInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  RefreshState
//  Description:  更新当前战斗场地状态
// =====================================================================================
void CGuildBattleField::RefreshState (bool bBattle)
{
    for (auto it = _mapSpot.begin(); it != _mapSpot.end(); ++it)
    {
        it->second->RefreshState(bBattle);
    }
    return ;
}		// -----  end of function RefreshState  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  End
//  Description:  结束据点上所有战斗
// =====================================================================================
void CGuildBattleField::End ()
{
    for (auto it = _mapSpot.begin(); it != _mapSpot.end(); ++it)
    {
        it->second->End();
    }
}		// -----  end of function End  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyAllOBSpotInfo
//  Description:  通知所有观战者战场信息
// =====================================================================================
void CGuildBattleField::NotifyAllOBSpotInfo () const
{
    for (auto& rPair : _mapSpot)
    {
        auto it = _mapSpotInfoCache.find(rPair.first);
        if (it != _mapSpotInfoCache.end())
        {
            TVecSpotInfo vecSpotInfoInner;
            TVecSpotInfo vecSpotInfoAll;

            vecSpotInfoAll.insert(vecSpotInfoAll.end(), (it->second).begin(), (it->second).end());


            TVecUINT64 vecMapRoleID = rPair.second->GetAllOB();   // 在据点内的人员

            SSpotBriefInfoPtr pSpotInfoBrief (new SSpotBriefInfo);
            if (rPair.second->GetAllInfo(*pSpotInfoBrief))
                vecSpotInfoInner.push_back(pSpotInfoBrief);

            string strData;
            strData = g_GuildBattleProtS.BuildPkg_SpotInfoNotify(vecSpotInfoInner);
            g_Game2CenterCommC.Send_NotifyGuildInfo(0, vecMapRoleID, strData);

            if (!vecMapRoleID.empty())
                g_GuildBattleProtS.SendClt_SpotInfoNotify(vecMapRoleID.data(), vecMapRoleID.size(), vecSpotInfoAll);

        }
        else
            rPair.second->NotifySpotInfo(GetState());
    }
}		// -----  end of function NotifyAllOBSpotInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyBattleInfo
//  Description:  通知战斗情况
// =====================================================================================
void CGuildBattleField::NotifyBattleInfo () const
{
    for (auto it = _mapSpot.begin(); it != _mapSpot.end(); ++it)
    {
        it->second->NotifyBattleInfo();
    }
}		// -----  end of function NotifyBattleInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyFieldInfo
//  Description:  通知所有人战场情况
// =====================================================================================
void CGuildBattleField::NotifyFieldInfo (EGBState eState, EGBSide eSide /* = eGBSideInvalid */) const
{
    SFieldInfo sFieldInfo;
    if (GetAllInfo(sFieldInfo, eState))
    {
        TVecUINT64 vecRoleID;
        if (eGBSideA == eSide || eSide == eGBSideInvalid)
            CGuildBattleMgr::Instance().GetAllMapPlayers(GetGuildID(eGBSideA), vecRoleID);
        if (eGBSideB == eSide || eSide == eGBSideInvalid)
            CGuildBattleMgr::Instance().GetAllMapPlayers(GetGuildID(eGBSideB), vecRoleID);
        if (!vecRoleID.empty())
            g_GuildBattleProtS.SendClt_FieldInfoNotify(vecRoleID.data(), vecRoleID.size(), sFieldInfo);
    }
}		// -----  end of function NotifyFieldInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifySkillInfo
//  Description:  广播技能信息
// =====================================================================================
void CGuildBattleField::NotifySkillInfo (EGBSide eSide) const
{
    TVecSkillInfo vecSkillInfo;
    for (auto it = _setSkillBuff[eSide].begin(); it != _setSkillBuff[eSide].end(); ++it)
    {
        vecSkillInfo.push_back(SSkillInfo(*it));
        TVecUINT64 vecRoleID;
        CGuildBattleMgr::Instance().GetAllMapPlayers(GetGuildID(eSide), vecRoleID);
        if (!vecRoleID.empty())
            g_GuildBattleProtS.SendClt_SkillInfoNotify(vecRoleID.data(), vecRoleID.size(), vecSkillInfo);
    }
}		// -----  end of function NotifySkillInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UpdateSpotCache
//  Description:  更新据点信息的缓存
// =====================================================================================
void CGuildBattleField::UpdateSpotCache ()
{
    _mapSpotInfoCache.clear();
    for (auto it = _mapSpot.begin(); it != _mapSpot.end(); ++it)
    {
        TVecSpotInfo vecSpotInfoAll;
        SSpotAllInfoPtr pSpotInfoAll (new SSpotAllInfo);
        if (it->second->GetAllInfo(*pSpotInfoAll))
            vecSpotInfoAll.push_back(pSpotInfoAll);
        _mapSpotInfoCache.insert(make_pair(it->first, vecSpotInfoAll));
        it->second->ClearBattleInfo();
    }
}		// -----  end of function UpdateSpotCache  ----- //


// ===  FUNCTION  ======================================================================
//         Name:  UpdateSpotCache
//  Description:  
// =====================================================================================
void CGuildBattleField::UpdateSpotCache (UINT64 qwRoleID, EGBUserState eState)
{
    for (auto & rPair : _mapSpotInfoCache)
    {
        for (auto & rInfo : rPair.second)
        {
            switch (rInfo->GetClassType())
            {

                case eType_SSpotAllInfo:
                    {
                        SSpotAllInfoPtr pAllInfo = dynamic_pointer_cast<SSpotAllInfo>(rInfo);
                        for (auto& rMemberInfo : pAllInfo->vecMemberInfoA)
                        {
                            if (rMemberInfo->qwRoleID == qwRoleID)
                                rMemberInfo->eState = eState;
                        }
                        for (auto& rMemberInfo : pAllInfo->vecMemberInfoB)
                        {
                            if (rMemberInfo->qwRoleID == qwRoleID)
                                rMemberInfo->eState = eState;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
}		// -----  end of function UpdateSpotCache  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  BuySkill
//  Description:  购买技能
// =====================================================================================
bool CGuildBattleField::BuySkill(CPlayerPtr pPlayer, UINT64 qwGuildID, EGBSkill eSkillType, EGBSkillResult& eResult)
{
    if (!pPlayer)
    {
        eResult = eGBSkillFailed;
        return false;
    }

    SGuildBattleSpotPlayerPtr pGuildBattleSpotPlayerPtr = NULL;
    auto it = _mapPlayerID2Spot.find(pPlayer->GetRoleID());
    if (it != _mapPlayerID2Spot.end())
    {
        pGuildBattleSpotPlayerPtr = _mapSpot[it->second]->GetSpotPlayer(pPlayer->GetRoleID());
        if (!pGuildBattleSpotPlayerPtr)
        {
            eResult = eGBSkillFailed;
            return false;
        }
    }

    auto it2 = pGuildBattleSpotPlayerPtr->setSkillBuff.find(eSkillType);
    if (it2 != pGuildBattleSpotPlayerPtr->setSkillBuff.end())
    {
        eResult = eGBSkillAlreadyHave;
        return false;
    }
 
    UINT32 dwPrice =  CGuildBattleConfigMgr::Instance().GetSkillPrice(eSkillType);
    bool bUseGold = false;
    CUser& rUser = pPlayer->GetUser();
    if(!rUser.CanSubMoney(EMONEY_COUPON, dwPrice))
    {
        bUseGold = true;
        if(!rUser.CanSubMoney(EMONEY_GOLD, dwPrice))
        {
            eResult = eGBSkillNoGold;
            return false;
        }
    }

    if(bUseGold)
        rUser.SubMoney(EMONEY_GOLD,dwPrice,NLogDataDefine::ItemTo_BuyAction);
    else
        rUser.SubMoney(EMONEY_COUPON,dwPrice,NLogDataDefine::ItemTo_BuyAction);
   
    pGuildBattleSpotPlayerPtr->setSkillBuff.insert(eSkillType);

    TVecINT32 vecParam;
    vecParam.push_back(eSkillType);
    ostringstream strInfo;
    strInfo << qwGuildID;
    pPlayer->OnEvent(eEventType_GuildBattleInspire, vecParam, strInfo.str());
    
    eResult = eGBSkillSuccess;
    return true;

    /*eResult = eGBSkillSuccess;
    if (_qwGuildID[0] == qwGuildID)
    {
        auto it = _setSkillBuff[0].find(eSkillType);
        if (it != _setSkillBuff[0].end())
        {
            eResult = eGBSkillAlreadyHave;
            return false;
        }
        CUser& rUser = pPlayer->GetUser();
        if (rUser.GetMoney(EMONEY_GOLD) < CGuildBattleConfigMgr::Instance().GetSkillPrice(eSkillType))
        {
            eResult = eGBSkillNoGold;
            return false;
        }
        if (rUser.SubMoney(EMONEY_GOLD,CGuildBattleConfigMgr::Instance().GetSkillPrice(eSkillType),NLogDataDefine::ItemTo_BuyGuildSkill))
        {
            _setSkillBuff[0].insert(eSkillType);
            eResult = eGBSkillSuccess;

            TVecINT32 vecParam;
            vecParam.push_back(eSkillType);
            ostringstream strInfo;
            strInfo << qwGuildID;
            pPlayer->OnEvent(eEventType_GuildBattleInspire, vecParam, strInfo.str());
            return true;
        }
    }
    if (_qwGuildID[1] == qwGuildID)
    {
        auto it = _setSkillBuff[1].find(eSkillType);
        if (it != _setSkillBuff[1].end())
        {
            eResult = eGBSkillAlreadyHave;
            return false;
        }
        CUser& rUser = pPlayer->GetUser();
        if (rUser.GetMoney(EMONEY_GOLD) < CGuildBattleConfigMgr::Instance().GetSkillPrice(eSkillType))
        {
            eResult = eGBSkillNoGold;
            return false;
        }
        if (rUser.SubMoney(EMONEY_GOLD,CGuildBattleConfigMgr::Instance().GetSkillPrice(eSkillType),NLogDataDefine::ItemTo_BuyGuildSkill))
        {
            _setSkillBuff[1].insert(eSkillType);
            eResult = eGBSkillSuccess;

            TVecINT32 vecParam;
            vecParam.push_back(eSkillType);
            ostringstream strInfo;
            strInfo << qwGuildID;
            pPlayer->OnEvent(eEventType_GuildBattleInspire, vecParam, strInfo.str());
            return true;
        }
    }
    eResult = eGBSkillFailed;
    return false;*/
}		// -----  end of function BuySkill  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ClearSkill
//  Description:  清除帮派技能
// =====================================================================================
void CGuildBattleField::ClearSkill ()
{
    _setSkillBuff[0].clear();
    _setSkillBuff[1].clear();
}		// -----  end of function ClearSkill  ----- //
