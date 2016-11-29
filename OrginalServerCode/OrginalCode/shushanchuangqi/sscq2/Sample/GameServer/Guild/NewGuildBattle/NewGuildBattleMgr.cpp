// =====================================================================================
//
//       Filename:  NewGuildBattleMgr.cpp
//
//    Description:  新帮派战管理类
//
//        Version:  1.0
//        Created:  03/19/2015 10:48:44 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "NewGuildBattleMgr.h"

#include "NewGuildBattleConfig.h"
#include "NewGuildBattleMountain.h"
#include "NewGuildBattlePlayer.h"
#include "NewGuildBattleRank.h"

#include "NewGuildBattleProtS.h"

#include "RTime.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "Game2DBComm.h"
#include "GuildBattleConfig.h"
#include "UserMgr.h"
#include "Player.h"
#include "GameNetMgr.h"

namespace NNewGuildBattle
{

static string s_strInvalidGuildName = "非法";

// ===  FUNCTION  ======================================================================
//         Name:  CBattleMgr
//  Description:  构造函数
// =====================================================================================
CBattleMgr::CBattleMgr ():
    CDayActivity(eActTypeNewGuildBattle),
    _bLoaded(false), _eState(eNGBSNone),
    _dwLastExpCheckTime(0),
    _dwGateHP(0), _dwGateAttack(0)
{
    for (UINT8 byIndex = eNGBMNone + 1; byIndex < eNGBMMax; ++ byIndex)
    {
        ENGBMountain eMountainType = static_cast<ENGBMountain>(byIndex);
        CMountainPtr pMoutain (new CMountain(eMountainType));
        if (!pMoutain)
            LOG_CRI << "Error when new CMountain.";
        _mapMountainPtr[eMountainType] = pMoutain;
    }
}		// -----  end of function CBattleMgr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CBattleMgr
//  Description:  析构函数
// =====================================================================================
CBattleMgr::~CBattleMgr ()
{
}		// -----  end of function ~CBattleMgr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  IsLoaded
//  Description:  是否已经加载相关数据完成
// =====================================================================================
bool CBattleMgr::IsLoaded () const
{
    return _bLoaded;
}		// -----  end of function IsLoaded  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetState
//  Description:  获取当前新帮派战状态
// =====================================================================================
ENGBState CBattleMgr::GetState () const
{
    return _eState;
}		// -----  end of function GetState  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllMountainsPanelInfo
//  Description:  获取所有灵山的面板信息
// =====================================================================================
bool CBattleMgr::GetAllMountainsPanelInfo (TVecMountainPanelInfo& rvecInfo) const
{
    for (auto & rPair : _mapMountainPtr)
    {
        if (!rPair.second)
        {
            LOG_CRI << "_mapMountainPtr second = NULL, "
                "first = " << static_cast<UINT32>(rPair.first) << ".";
            continue;
        }
        SMountainPanelInfo sInfo;
        if (rPair.second->GetPanelInfo(sInfo))
            rvecInfo.push_back(sInfo);
    }
    return true;
}		// -----  end of function GetAllMountainsPanelInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRemainTime
//  Description:  获取新帮派战剩余时间
// =====================================================================================
UINT32 CBattleMgr::GetRemainTime () const
{
    time_t tNow = Time::Now();
    switch (GetState())
    {
        case eNGBSBattle: //帮派战进行中
            if (tNow <= _dwEndTime)
                return _dwEndTime - tNow;
            else
                return 0;
            break;
        case eNGBSNone: //没有开启帮派战
            {
                UINT32 dwTime = CConfigMgr::Instance().GetNextBeginTime(tNow);
                if (dwTime > tNow)
                    return dwTime - tNow;
            }
        case eNGBSReady: //帮派战即将开启，倒计时通知阶段
            if (tNow <= _dwBeginTime)
                return _dwBeginTime - tNow;
            else
                return 0;
            break;
        case eNGBSBattleEnd: //帮派战战役结束
        default:
            break;
    }
    return 0;
}		// -----  end of function GetRemainTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayerMountain
//  Description:  获取参战玩家所处的灵山类型
// =====================================================================================
ENGBMountain CBattleMgr::GetPlayerMountain (UINT64 qwRoleID) const
{
    ENGBMountain eMountain = eNGBMNone;
    auto it = _mapAllPlayer.find(qwRoleID);
    if (it != _mapAllPlayer.end() && it->second)
        eMountain = it->second->GetMountain();
    return eMountain;
}		// -----  end of function GetPlayerMountain  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  IsPlayerInBattle
//  Description:  该玩家是否在参战中
// =====================================================================================
bool CBattleMgr::IsPlayerInBattle (UINT64 qwRoleID) const
{
    ENGBMountain eMountain = eNGBMNone;
    auto it = _mapAllPlayer.find(qwRoleID);
    if (it != _mapAllPlayer.end() && it->second)
        eMountain = it->second->GetMountain();
    return eMountain == eNGBMNone ? false : true;
}		// -----  end of function IsPlayerInBattle  ----- //
// ===  FUNCTION  ======================================================================
//         Name:  GetGuildName
//  Description:  获取帮派姓名
// =====================================================================================
const string& CBattleMgr::GetGuildName (UINT64 qwGuildID) const
{
    auto it = _mapGuildName.find(qwGuildID);
    if (it == _mapGuildName.end())
        return s_strInvalidGuildName;
    else
        return it->second;

}		// -----  end of function GetGuildName  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildLevel
//  Description:  获取帮派姓名
// =====================================================================================
UINT16 CBattleMgr::GetGuildLevel (UINT64 qwGuildID) const
{
    auto it = _mapGuildLevel.find(qwGuildID);
    if (it == _mapGuildLevel.end())
        return 0;
    else
        return it->second;

}		// -----  end of function GetGuildLevel  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildOwnerName
//  Description:  获取帮派姓名
// =====================================================================================
const string& CBattleMgr::GetGuildOwnerName (UINT64 qwGuildID) const
{
    auto it = _mapGuildOwnerName.find(qwGuildID);
    if (it == _mapGuildOwnerName.end())
        return s_strInvalidGuildName;
    else
        return it->second;

}		// -----  end of function GetGuildOwnerName  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildScore
//  Description:  获取帮派战功
// =====================================================================================
UINT32 CBattleMgr::GetGuildScore (UINT64 qwGuildID, ENGBMountain eMountainType) const
{
    if (!_pGuildRankMgr)
        return 0;
    return _pGuildRankMgr->GetGuildScore(qwGuildID, eMountainType);
}		// -----  end of function GetGuildScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayerScore
//  Description:  获取玩家战功
// =====================================================================================
UINT32 CBattleMgr::GetPlayerScore (UINT64 qwRoleID) const
{
    auto it = _mapAllPlayer.find(qwRoleID);
    if (it == _mapAllPlayer.end() || !it->second)
        return 0;
    else
        return it->second->GetScore();
}		// -----  end of function GetPlayerScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayer
//  Description:  获取指定参战人员
// =====================================================================================
CPlayerPtr CBattleMgr::GetPlayer (UINT64 qwRoleID) const
{
    auto it = _mapAllPlayer.find(qwRoleID);
    if (it == _mapAllPlayer.end())
        return NULL;
    else
        return it->second;
}		// -----  end of function GetPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerNotify
//  Description:  玩家通知
// =====================================================================================
void CBattleMgr::PlayerNotify (UINT64 qwRoleID) const
{
    if (GetState() != eNGBSBattle)
        return;
    auto it = _mapAllPlayer.find(qwRoleID);
    if (it == _mapAllPlayer.end() || !it->second)
        return;
    CPlayerPtr pPlayer = it->second;

    ENGBMountain eMountain = pPlayer->GetMountain();
    if (eMountain  == eNGBMNone)
        return;
    auto it2 = _mapMountainPtr.find(eMountain);
    if (it2 == _mapMountainPtr.end() || !it2->second)
        return;
    it2->second->PlayerNotify(qwRoleID);
}		// -----  end of function PlayerNotify  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildRankMgr
//  Description:  获取帮派排行榜管理类
// =====================================================================================
CGuildRankMgrPtr CBattleMgr::GetGuildRankMgr () const
{
    return _pGuildRankMgr;
}		// -----  end of function GetGuildRankMgr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildMemberRankMgr
//  Description:  获取帮派成员排行榜管理类
// =====================================================================================
CGuildMemberRankMgrPtr CBattleMgr::GetGuildMemberRankMgr () const
{
    return _pGuildMemberRankMgr;
}		// -----  end of function GetGuildMemberRankMgr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayerRankMgr
//  Description:  获取帮派排行榜管理类
// =====================================================================================
CPlayerRankMgrPtr CBattleMgr::GetPlayerRankMgr () const
{
    return _pPlayerRankMgr;
}		// -----  end of function GetGuildRankMgr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetMountain
//  Description:  获取灵山
// =====================================================================================
CMountainPtr CBattleMgr::GetMountain (ENGBMountain eMountainType) const
{
    auto it = _mapMountainPtr.find(eMountainType);
    if (it == _mapMountainPtr.end())
        return NULL;
    else
        return it->second;
}		// -----  end of function GetMountain  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGateHP
//  Description:  获取某灵山城门HP（调试用）
// =====================================================================================
UINT32 CBattleMgr::GetGateHP (ENGBMountain eMountainType) const
{
    auto it = _mapMountainPtr.find(eMountainType);
    if (it == _mapMountainPtr.end())
        return 0;
    else
        return it->second->GetGateHP();

}		// -----  end of function GetGateHP  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGateMaxHP
//  Description:  获取某灵山城门MaxHP（调试用）
// =====================================================================================
UINT32 CBattleMgr::GetGateMaxHP (ENGBMountain eMountainType) const
{
    auto it = _mapMountainPtr.find(eMountainType);
    if (it == _mapMountainPtr.end())
        return 0;
    else
        return it->second->GetGateMaxHP();

}		// -----  end of function GetGateMaxHP  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllGuildPlayer
//  Description:  获取某一个帮派所有参战成员
// =====================================================================================
void CBattleMgr::GetAllGuildPlayer (UINT64 qwGuildID, TVecUINT64& rvecRoleID) const
{
    if (GetState() != eNGBSBattle)
        return;

    for (auto& rPair: _mapAllPlayer)
    {
        if (rPair.second 
                && rPair.second->GetGuildID() == qwGuildID
                && rPair.second->GetMountain() != eNGBMNone)
            rvecRoleID.push_back(rPair.first);
    }
}		// -----  end of function GetAllGuildPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGateInitHP
//  Description:  获取山门战初始血量
// =====================================================================================
UINT32 CBattleMgr::GetGateInitHP () const
{
    return _dwGateHP;
}		// -----  end of function GetGateInitHP  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGateInitAttack
//  Description:  获取山门战初始攻击力
// =====================================================================================
UINT32 CBattleMgr::GetGateInitAttack () const
{
    return _dwGateAttack;
}		// -----  end of function GetGateInitAttack  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetLoaded
//  Description:  设置是否加载完成
// =====================================================================================
void CBattleMgr::SetLoaded (bool bLoaded)
{
    _bLoaded = bLoaded;
}		// -----  end of function SetLoaded  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerEnter
//  Description:  玩家进入帮派战
// =====================================================================================
ENGBEnterResult CBattleMgr::PlayerEnter (CPlayerPtr pPlayer, 
        ENGBMountain eMountainType, ENGBMountainState& eState)
{
    ENGBEnterResult eResult = eNGBERFailed;
    if (!pPlayer)
        return eResult;

    if (GetState() != eNGBSBattle)
    {
        eResult = eNGBERWrongTime;
        return eResult;
    }

    UINT64 qwRoleID = pPlayer->GetRoleID();
    auto it = _mapAllPlayer.find(qwRoleID);
    if (it != _mapAllPlayer.end())
    {
        if (it->second && it->second->GetMountain() != eNGBMNone)
        {
            eResult = eNGBERRepeat;
            return eResult;
        }
    }
    else  //
    {
        //event
        TVecINT32 vecParam;
        vecParam.push_back(eMountainType);
        vecParam.push_back(1); //1次
        ::CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if(pUser)
        {
            ::CPlayerPtr pPlayer =  pUser->GetPlayer();
            if(pPlayer)
            {
                pPlayer->OnEvent(eEventType_LingMountainJoin,vecParam);
            }
        }
        else
        {
            ::CPlayer::AddOffLineEvent(qwRoleID,eEventType_LingMountainJoin,vecParam);
        }
    }

    _mapAllPlayer[qwRoleID] = pPlayer;
    auto it2 = _mapMountainPtr.find(eMountainType);
    if (it2 == _mapMountainPtr.end() || !it2->second)
    {
        eResult = eNGBERFailed;
        return eResult;
    }
    eState = it2->second->GetState();
    eResult =  it2->second->PlayerEnter(pPlayer);
    if (eResult == eNGBERSuccess)
    {
        _mapAllPlayer[qwRoleID] = pPlayer;
        _mapGuildName[pPlayer->GetGuildID()]        = pPlayer->GetGuildName();
        _mapGuildLevel[pPlayer->GetGuildID()]       = pPlayer->GetGuildLevel();
        _mapGuildOwnerName[pPlayer->GetGuildID()]   = pPlayer->GetGuildOwnerName();
    }

    return eResult;
}		// -----  end of function PlayerEnter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerQuit
//  Description:  玩家退出
// =====================================================================================
ENGBQuitResult CBattleMgr::PlayerQuit (CPlayerPtr pPlayer)
{
    if (GetState() != eNGBSBattle)
        return eNGBQuitFailed;

    UINT64 qwRoleID = pPlayer->GetRoleID();
    auto it = _mapAllPlayer.find(qwRoleID);
    if (it == _mapAllPlayer.end() || !it->second)
        return eNGBQuitFailed;

    pPlayer = it->second;

    auto it2 = _mapMountainPtr.find(pPlayer->GetMountain());
    if (it2 == _mapMountainPtr.end() || !it2->second)
        return eNGBQuitFailed;
    return it2->second->PlayerQuit(pPlayer);

}		// -----  end of function PlayerQuit  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetState
//  Description:  帮派战状态更改
// =====================================================================================
void CBattleMgr::SetState(ENGBState eState, bool bNotify /* = true */)
{
    _eState = eState;
    g_Game2CenterGuildBattleC.Send_NewSetState(eState);
    if (bNotify)
    {
        TVecMountainPanelInfo vecInfo;
        GetAllMountainsPanelInfo(vecInfo);
        string strPkg = g_NewGuildBattleProtS.BuildPkg_StateNotify(_eState, GetRemainTime(), vecInfo);
        NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());
    }
}		// -----  end of function SetState  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GMCapture
//  Description:  GM命令占领某一个山 
// =====================================================================================
bool CBattleMgr::GMCapture (ENGBMountain eMountainType, 
        UINT64 qwGuildID, const string& strName, UINT16 wLevel)
{
    auto it = _mapMountainPtr.find(eMountainType);
    if (it == _mapMountainPtr.end() || !it->second)
        return false;
    return it->second->GMCapture(qwGuildID, strName, wLevel);
}		// -----  end of function GMCapture  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetGateHP
//  Description:  设置某灵山的城门HP
// =====================================================================================
void CBattleMgr::SetGateHP (ENGBMountain eMountainType, UINT32 dwHP)
{
    auto it = _mapMountainPtr.find(eMountainType);
    if (it == _mapMountainPtr.end() || !it->second)
        return;
    return it->second->SetGateHP(dwHP);
}		// -----  end of function SetGateHP  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetGateMaxHP
//  Description:  设置某灵山的城门MaxHP
// =====================================================================================
void CBattleMgr::SetGateMaxHP (ENGBMountain eMountainType, UINT32 dwMaxHP)
{
    auto it = _mapMountainPtr.find(eMountainType);
    if (it == _mapMountainPtr.end() || !it->second)
        return;
    return it->second->SetGateMaxHP(dwMaxHP);
}		// -----  end of function SetGateMaxHP  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddPlayerBattleCount
//  Description:  更新玩家获胜场数
// =====================================================================================
void CBattleMgr::AddPlayerBattleCount (UINT64 qwRoleID, bool bWin)
{
    if (bWin)
    {
        ++_mapPlayerWinCombo[qwRoleID];
        LOG_DBG << "qwRoleID = " << qwRoleID << ", bWin = " << (bWin?"true":"false") << "(" << _mapPlayerWinCombo[qwRoleID] << ").";
    }
    else
    {
        _mapPlayerWinCombo[qwRoleID] = 0;
        LOG_DBG << "qwRoleID = " << qwRoleID << ", bWin = " << (bWin?"true":"false") << ".";
    }

    TVecINT32 vecParam;
    vecParam.push_back(_mapPlayerWinCombo[qwRoleID]);

    ::CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(pUser)
    {
        ::CPlayerPtr pPlayer =  pUser->GetPlayer();
        if(pPlayer)
        {
            pPlayer->OnEvent(eEventType_GuildBattleComboKill,vecParam);
        }
    }
    else
    {
        ::CPlayer::AddOffLineEvent(qwRoleID,eEventType_GuildBattleComboKill,vecParam);
    }

}		// -----  end of function AddPlayerBattleCount  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PushGuildName
//  Description:  增加帮派名字缓存
// =====================================================================================
void CBattleMgr::PushGuildName(UINT64 qwGuildID, const string& strGuildName, 
        UINT16 wGuildLevel, const string& strGuildOwnerName)
{
    _mapGuildName[qwGuildID] = strGuildName;
    _mapGuildLevel[qwGuildID] = wGuildLevel;
    _mapGuildOwnerName[qwGuildID] = strGuildOwnerName;
}		// -----  end of function PushGuildName  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ChangeGuildLevel
//  Description:  改变帮派等级
// =====================================================================================
void CBattleMgr::ChangeGuildLevel (UINT64 qwGuildID, UINT16 wLevel)
{
    _mapGuildLevel[qwGuildID] = wLevel;
    for (auto & rPair : _mapMountainPtr)
    {
        if (rPair.second)
            rPair.second->ChangeGuildLevel(qwGuildID, wLevel);
    }
}		// -----  end of function ChangeGuildLevel  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ChangeGuildOwnerName
//  Description:  改变帮派等级
// =====================================================================================
void CBattleMgr::ChangeGuildOwnerName (UINT64 qwGuildID, const string& strName)
{
    _mapGuildOwnerName[qwGuildID] = strName;
    for (auto & rPair : _mapMountainPtr)
    {
        if (rPair.second)
            rPair.second->ChangeGuildOwnerName(qwGuildID, strName);
    }
}		// -----  end of function ChangeGuildOwnerName  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ClearGuild
//  Description:  帮派解散，清除存在的占领帮派
// =====================================================================================
void CBattleMgr::ClearGuild (UINT64 qwGuildID)
{
    for (auto & rPair : _mapMountainPtr)
    {
        if (rPair.second)
            rPair.second->ClearGuild(qwGuildID);
    }
}		// -----  end of function ClearGuild  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetGateInitHP
//  Description:  设置城门初始血量
// =====================================================================================
void CBattleMgr::SetGateInitHP (UINT32 dwHP)
{
    _dwGateHP = dwHP;
}		// -----  end of function SetGateInitHP  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetGateInitAttack
//  Description:  设置城门初始攻击力
// =====================================================================================
void CBattleMgr::SetGateInitAttack (UINT32 dwAttack)
{
    _dwGateAttack = dwAttack;
}		// -----  end of function SetGateInitAttack  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  StartLoadData
//  Description:  开始向DB要数据
// =====================================================================================
void CBattleMgr::StartLoadData ()
{
    g_Game2DBCommC.Send_GetNewGuildBattleHistory();
}		// -----  end of function StartLoadData  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadFromDB
//  Description:  从数据库加载数据
// =====================================================================================
bool CBattleMgr::LoadFromDB (const string& strData)
{
    NGame2DBComm::TVecDBGuildNewBattleHistoryInfo vecInfo;
    CInArchive ar(strData);
    ar >> vecInfo;
    for (auto & rInfo : vecInfo)
    {
        if (rInfo.byMountainType >= eNGBMMax)
        {
            LOG_CRI << "Invalid Mountain Type : " << static_cast<UINT32>(rInfo.byMountainType);
            continue;
        }
        ENGBMountain eMountainType = static_cast<ENGBMountain>(rInfo.byMountainType);
        auto it = _mapMountainPtr.find(eMountainType);
        if (it == _mapMountainPtr.end() || !it->second)
        {
            LOG_CRI << "Invalid Mountain Type : " << static_cast<UINT32>(rInfo.byMountainType);
            continue;
        }
        CMountainHistoryPtr pHistory(new CMountainHistory(eMountainType, rInfo.qwGuildID, rInfo.strGuildName, rInfo.strGuildOwnerName, rInfo.dwTime));
        it->second->PushHistory(pHistory);
    }
    return true;
}		// -----  end of function LoadFromDB  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  TimerCheck
//  Description:  定时器检查
// =====================================================================================
void CBattleMgr::TimerCheck (time_t tNow)
{
    switch (GetState())
    {
        case eNGBSBattle: //帮派战进行中
            ExpProcess(tNow);
            // 时间到了，结束帮派战
            if (tNow >= _dwEndTime)
                EndBattle();
            else
            {
                for (auto& rPair : _mapMountainPtr)
                {
                    if (!rPair.second)
                    {
                        LOG_CRI << "No Mountain(" << static_cast<UINT32>(rPair.first) << ").";
                        continue;
                    }
                    rPair.second->BattleProcess(tNow);
                }
            }
            break;
        case eNGBSNone: //没有开启帮派战
        case eNGBSReady: //帮派战即将开启，倒计时通知阶段
        case eNGBSBattleEnd: //帮派战战役结束
        default:
            break;
    }
}		// -----  end of function TimerCheck  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ExpProcess
//  Description:  经验值结算定时处理
// =====================================================================================
void CBattleMgr::ExpProcess (UINT32 dwTime)
{
    if (dwTime >= _dwLastExpCheckTime)
    {
        for (auto & rPair : _mapAllPlayer)
        {
            if (rPair.second && rPair.second->GetMountain() != eNGBMNone)
            {
                ::CPlayerPtr pPlayer = rPair.second->GetPlayer();
                if (pPlayer)
                {
                    UINT8 byLevel = pPlayer->GetLevel();
                    pPlayer->AddExp(CGuildBattleConfigMgr::Instance().GetExp(byLevel));
                }
            }
        }
        _dwLastExpCheckTime += CGuildBattleConfigMgr::Instance().GetExpTime();
    }
}		// -----  end of function ExpProcess  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GMOpen
//  Description:  GM开启活动
// =====================================================================================
bool CBattleMgr::GMOpen()
{
    ForceEndBattle();
    ClearEvent();

    time_t tNow = Time::Now();

    _dwAlarmTime = tNow - 60;
    _dwReadyTime = tNow + 5;
    _dwBeginTime = _dwReadyTime + CConfigMgr::Instance().GetDebugStartTime();

    _dwEndTime = _dwBeginTime + CConfigMgr::Instance().GetCampaignTime();

    _dwAlarmTimeSpan   = _dwReadyTime - _dwAlarmTime;
    _dwReadyTimeSpan   = _dwBeginTime - _dwReadyTime;
    _dwProcessTimeSpan = _dwEndTime   - _dwBeginTime;
    
    CDayActivity::SetStatus(eDayActivityStatusAlarm);
    LOG_WRN << "CBattleMgr::GMOpen()";
    return true;
}		// -----  end of function GMOpen  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnAlarm
//  Description:  程序开始准备
// =====================================================================================
bool CBattleMgr::OnAlarm()
{
    CDayActivity::OnAlarm();
    return true;
}		// -----  end of function OnAlarm  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnReady
//  Description:  开始通知
// =====================================================================================
void CBattleMgr::OnReady()
{
    CDayActivity::OnReady();
    string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgLingMountainReady);
    NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());
    SetState(eNGBSReady);
}		// -----  end of function OnReady  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnBegin
//  Description:  正式开始
// =====================================================================================
void CBattleMgr::OnBegin()
{
    CDayActivity::OnBegin();
    LOG_WRN << "CBattleMgr::OnBegin()";
    StartBattle();
}		// -----  end of function OnBegin  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnEnd
//  Description:  活动结束
// =====================================================================================
void CBattleMgr::OnEnd()
{
    CDayActivity::OnEnd();
    EndBattle();
}		// -----  end of function OnEnd  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  OnEvent
//  Description:  注册时间触发
// =====================================================================================
void CBattleMgr::OnEvent(SActEventData& oSActEventData)
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
void CBattleMgr::OnReBegin()
{
    ForceEndBattle();
    //CGuildBattleConfigMgr::Instance().ForceStart();
}		// -----  end of function OnReBegin  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UpdateState
//  Description:  更新状态
// =====================================================================================
void CBattleMgr::UpdateState(time_t tNow)
{
    CDayActivity::UpdateState(tNow);
}		// -----  end of function UpdateState  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ResetState
//  Description:  重置原始状态
// =====================================================================================
void CBattleMgr::ResetState()
{
}		// -----  end of function ResetState  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  StartBattle
//  Description:  开始帮派战
// =====================================================================================
bool CBattleMgr::StartBattle ()
{
    bool bRet = false;
    switch (GetState())
    {
        case eNGBSNone: //没有开启帮派战
        case eNGBSReady: //帮派战即将开启，倒计时通知阶段
            bRet = true;
            {
                // 灵山商店开启通知
                TVecLingShanShopData vecInfo;
                g_Game2CenterCommC.Send_NotifyGuildExchangedItemBegin(vecInfo);
            }
            for(auto& rPair : _mapMountainPtr)
            {
                if (!rPair.second)
                {
                    bRet = false;
                    break;
                }
                bRet = rPair.second->StartBattle();
                if (!bRet)
                {
                    LOG_CRI << "Mount Start Battle false.";
                    break;
                }
            }
            if (!bRet)
                break;
            if (!_pGuildRankMgr)
                _pGuildRankMgr.reset(new CGuildRankMgr);
            if (!_pGuildMemberRankMgr)
                _pGuildMemberRankMgr.reset(new CGuildMemberRankMgr);
            if (!_pPlayerRankMgr)
                _pPlayerRankMgr.reset(new CPlayerRankMgr);
            SetState(eNGBSBattle);
        case eNGBSBattle: //帮派战进行中
        case eNGBSBattleEnd: //帮派战战役结束
        default:
            break;
    }
    if (bRet)
    {
        _dwLastExpCheckTime = Time::Now();
        string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgLingMountainSignIn);
        NetMgr.GetGateHandler()->SendClt(NULL, 0, &strPkg[0], (UINT32)strPkg.size());
    }
    else
        LOG_CRI << "StartBattle error.";

    return bRet;
}		// -----  end of function StartBattle  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  EndBattle
//  Description:  结束新帮派战
// =====================================================================================
void CBattleMgr::EndBattle ()
{
    switch(GetState())
    {
        case eNGBSBattle: //帮派战进行中
            for (auto& rPair : _mapMountainPtr)
            {
                if (!rPair.second)
                    continue;
                rPair.second->EndBattle(true);
            }
            SetState(eNGBSBattleEnd);

            for (auto & rPair : _mapAllPlayer)
            {
                for (auto rPair2 : _mapMountainPtr)
                {
                    if (!rPair2.second)
                        continue;
                    rPair2.second->Reward(rPair.first);
                }
            }
            SetState(eNGBSNone);
            break;
        case eNGBSNone: //没有开启帮派战
        case eNGBSReady: //帮派战即将开启，倒计时通知阶段
        case eNGBSBattleEnd: //帮派战战役结束
        default:
            break;
    }

    // 灵山商店开启通知
    TVecLingShanShopData vecInfo;
    for (auto& rPair : _mapMountainPtr)
    {
        if (!rPair.second)
            continue;
        bool bFound = false;
        for (auto& rInfo : vecInfo)
        {
            if (rInfo.qwGuildID == rPair.second->GetGuildID())
            {
                rInfo.vecLingShanType.push_back(static_cast<UINT8>(rPair.first));
                bFound = true;
                break;
            }
        }
        if (!bFound)
        {
            TVecUINT8 vecTmp;
            vecTmp.push_back(static_cast<UINT8>(rPair.first));
            SLingShanShopData sInfo(rPair.second->GetGuildID(), vecTmp);
            vecInfo.push_back(sInfo);
        }
    }
    g_Game2CenterCommC.Send_NotifyGuildExchangedItemBegin(vecInfo);
    Reset();

}		// -----  end of function EndBattle  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ForceEndBattle
//  Description:  强制结束战斗
// =====================================================================================
void CBattleMgr::ForceEndBattle ()
{
    EndBattle();
    Reset();
}		// -----  end of function ForceEndBattle  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Reset
//  Description:  重置所有成员
// =====================================================================================
void CBattleMgr::Reset ()
{
    _eState = eNGBSNone;
    _pGuildRankMgr = NULL;
    _pGuildMemberRankMgr = NULL;
    _pPlayerRankMgr = NULL;


    for (auto & rPair : _mapMountainPtr)
    {
        if (rPair.second)
            rPair.second->Reset();
    }
    _mapGuildScore.clear();
    _mapAllPlayer.clear();
    _mapPlayerWinCombo.clear();

}		// -----  end of function Reset  ----- //

} // namespace NNewGuildBattle
