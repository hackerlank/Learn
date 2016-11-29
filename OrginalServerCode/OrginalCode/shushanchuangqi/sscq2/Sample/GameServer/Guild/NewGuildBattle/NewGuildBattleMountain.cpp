// =====================================================================================
//
//       Filename:  NewGuildBattleMountain.cpp
//
//    Description:  新帮派战灵山类
//
//        Version:  1.0
//        Created:  03/19/2015 01:58:23 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "NewGuildBattleMountain.h"

#include "NewGuildBattleGate.h"
#include "NewGuildBattleCave.h"
#include "NewGuildBattlePlayer.h"
#include "NewGuildBattleMgr.h"
#include "NewGuildBattleRank.h"

#include "NewGuildBattleProtS.h"

#include "RTime.h"
#include "Protocols.h"
#include "GameServerSysMail.h"

namespace NNewGuildBattle
{

// ===  FUNCTION  ======================================================================
//         Name:  CMountain
//  Description:  
// =====================================================================================
CMountain::CMountain (ENGBMountain eType):
    _eType(eType), _eState(eNGBMSNone),
    _qwGuildID(0), _wGuildLevel(0), _dwGuildOwnCount(0), _dwCaptureTime(0),
    _qwGuildLostID(0)
{
}		// -----  end of function CMountain  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CMountain
//  Description:  析构函数
// =====================================================================================
CMountain::~CMountain ()
{
}		// -----  end of function ~CMountain  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetType
//  Description:  获取灵山类型
// =====================================================================================
ENGBMountain CMountain::GetType () const
{
    return _eType;
}		// -----  end of function GetType  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetName
//  Description:  获取灵山名字
// =====================================================================================
string CMountain::GetName () const
{
    string strName = "???";
    switch (GetType())
    {
        case eNGBMEMei: //峨眉
            strName = "峨眉";
            break;
        case eNGBMKunLun: //昆仑
            strName = "昆仑";
            break;
        case eNGBMHuangShan: //黄山
            strName = "黄山";
            break;
        default:
            break;
    }
    return strName;
}		// -----  end of function GetName  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetState
//  Description:  获取当前灵山状态
// =====================================================================================
ENGBMountainState CMountain::GetState () const
{
    return _eState;
}		// -----  end of function GetState  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildID
//  Description:  获取占领帮派ID
// =====================================================================================
UINT64 CMountain::GetGuildID () const
{
    return _qwGuildID;
}		// -----  end of function GetGuildID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPanelInfo
//  Description:  面板数据协议参数序列化
// =====================================================================================
bool CMountain::GetPanelInfo (SMountainPanelInfo& rInfo) const
{
    rInfo.eMountainType     = _eType;
    rInfo.eState            = _eState;
    rInfo.qwGuildID         = _qwGuildID;
    rInfo.strGuildName      = _strGuildName;
    rInfo.wGuildLevel       = _wGuildLevel;
    rInfo.strGuildOwnerName = _strGuildOwnerName;
    rInfo.dwGuildOwnCount   = _dwGuildOwnCount;

    if (GetState() == eNGBMSCave && _pCave)
        _pCave->GetAllAttackGuildID(rInfo.vecAttackGuildID);

    return true;
}		// -----  end of function GetPanelInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetHistoryInfo
//  Description:  获取占领的历史信息
// =====================================================================================
bool CMountain::GetHistoryInfo (TVecOwnerHistoryInfo& rvecInfo) const
{
    for (auto & pInfo : _listHistoryPtr)
    {
        if (!pInfo)
            continue;
        SOwnerHistoryInfo sInfo;
        if (pInfo->GetAllInfo(sInfo))
            rvecInfo.push_back(sInfo);
    }
    return true;
}		// -----  end of function GetHistoryInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerNotify
//  Description:  玩家通知
// =====================================================================================
void CMountain::PlayerNotify (UINT64 qwRoleID) const
{
    switch (GetState())
    {
        case eNGBMSGate: //城门战
            if (_pGate)
                _pGate->PlayerNotify(qwRoleID);
            break;
        case eNGBMSCave: //洞府战
            if (_pCave)
                _pCave->PlayerNotify(qwRoleID);
            break;
        default:
            break;
    }
}		// -----  end of function PlayerNotify  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGate
//  Description:  获取城门类
// =====================================================================================
CGatePtr CMountain::GetGate () const
{
    return _pGate;
}		// -----  end of function GetGate  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetCave
//  Description:  获取洞府类
// =====================================================================================
CCavePtr CMountain::GetCave () const
{
    return _pCave;
}		// -----  end of function GetCave  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGateHP
//  Description:  获取城门的血量
// =====================================================================================
UINT32 CMountain::GetGateHP () const
{
    if (_pGate)
        return _pGate->GetGateHP();
    else
        return 0;
}		// -----  end of function GetGateHP  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGateMaxHP
//  Description:  获取城门的血量
// =====================================================================================
UINT32 CMountain::GetGateMaxHP () const
{
    if (_pGate)
        return _pGate->GetGateMaxHP();
    else
        return 0;
}		// -----  end of function GetGateMaxHP  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  StartBattle
//  Description:  开始战斗
// =====================================================================================
bool CMountain::StartBattle ()
{
    switch (GetState())
    {
        case eNGBMSNone: //无效状态
            return StartGate();
        case eNGBMSGate: //城门战
        case eNGBMSCave: //洞府战
        case eNGBMSEnd: //战斗结束
        default:
            return false;
    }
    return true;
}		// -----  end of function StartBattle  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  EndBattle
//  Description:  战斗结束
// =====================================================================================
void CMountain::EndBattle (bool bTimeOver)
{

    if (_pGate)
    {
        _pGate->EndBattle(bTimeOver);
        _pGate = NULL;
    }

    // 洞府战战斗阶段结束
    if (_pCave)
    {
        TVecUINT64 vecRoleID;
        _pCave->GetAllPlayerID(vecRoleID);

        _pCave->EndBattle(bTimeOver, _qwGuildID);
        _pCave->GetAllAttackGuildID(_vecCaveAttackGuildID);

        UINT64 qwGuildID = _pCave->GetWinnerID();

        if (qwGuildID)
        {

            if (_qwGuildID != qwGuildID)
                _qwGuildLostID      = _qwGuildID;
            else
                _qwGuildLostID = 0;

            _qwGuildID          = qwGuildID;
            _strGuildName       = CBattleMgr::Instance().GetGuildName(qwGuildID);
            _wGuildLevel        = CBattleMgr::Instance().GetGuildLevel(qwGuildID);
            _strGuildOwnerName  = CBattleMgr::Instance().GetGuildOwnerName(qwGuildID);
            _dwGuildOwnCount    = ++_mapGuildCaptureCount[qwGuildID];

            if (!vecRoleID.empty())
                g_NewGuildBattleProtS.SendClt_CaveCapture((UINT64*)&vecRoleID[0], (UINT16)vecRoleID.size(), GetType(), _strGuildName);
        }
        else
        {
            _qwGuildLostID = 0;

            // 无人占领，也通知其他人
            if (bTimeOver && !vecRoleID.empty())
                g_NewGuildBattleProtS.SendClt_CaveCapture((UINT64*)&vecRoleID[0], (UINT16)vecRoleID.size(), GetType(), "");
        }
        _pCave = NULL;
    }

    // 有帮派占领，记录占领历史
    if (_qwGuildID)
    {
        time_t tNow = Time::Now();
        CMountainHistoryPtr pHistory(new CMountainHistory(GetType(), _qwGuildID, _strGuildName, _strGuildOwnerName, tNow));
        if (pHistory)
        {
            _listHistoryPtr.push_front(pHistory);
            NGame2DBComm::TVecDBGuildNewBattleHistoryInfo vecInfo;
            NGame2DBComm::SDBGuildNewBattleHistoryInfo sInfo;
            if (pHistory->GetAllInfo(sInfo))
                vecInfo.push_back(sInfo);
            g_Game2DBCommC.Send_AddNewGuildBattleHistory(vecInfo);
        }
    }

    if (bTimeOver)
        _eState = eNGBMSNone;
    else
        _eState = eNGBMSEnd;
}		// -----  end of function EndBattle  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Reset
//  Description:  内部成员重置
// =====================================================================================
void CMountain::Reset ()
{
    _pGate = NULL;
    _pCave = NULL;
    _eState = eNGBMSNone;
    _vecCaveAttackGuildID.clear();
}		// -----  end of function Reset  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetGateHP
//  Description:  设置城门血量
// =====================================================================================
void CMountain::SetGateHP (UINT32 dwHP)
{
    if (_pGate)
        _pGate->SetGateHP(dwHP);
}		// -----  end of function SetGateHP  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetGateMaxHP
//  Description:  设置城门血量
// =====================================================================================
void CMountain::SetGateMaxHP (UINT32 dwMaxHP)
{
    if (_pGate)
        _pGate->SetGateMaxHP(dwMaxHP);
}		// -----  end of function SetGateMaxHP  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PushHistory
//  Description:  塞入一个历史日志
// =====================================================================================
bool CMountain::PushHistory (CMountainHistoryPtr pHistory)
{
    if (!pHistory)
        return false;
    _listHistoryPtr.push_back(pHistory);
    _dwGuildOwnCount    = ++_mapGuildCaptureCount[_qwGuildID];
    if (pHistory->_dwTime >= _dwCaptureTime)
    {
        _qwGuildID          = pHistory->_qwGuildID;
        _dwCaptureTime      = pHistory->_dwTime;
        g_Game2CenterCommC.Send_GetGuildName(_qwGuildID,
                [this, pHistory] (UINT8 byRet, bool bValid, UINT64 qwGuildID, const std::string& strGuildName, UINT8 byGuildLvl, const std::string& strGuildOwnerName)
                {
                    if (qwGuildID == _qwGuildID)
                    {
                        if (byRet != 0 || !bValid)
                        {
                            LOG_DBG << "No guild: " << qwGuildID << ".";
                            ClearGuild(qwGuildID);
                        }
                        else
                        {
                            _wGuildLevel        = byGuildLvl;
                            _strGuildName       = strGuildName;
                            _strGuildOwnerName  = strGuildOwnerName;
                            _dwCaptureTime      = pHistory->_dwTime;
                            CBattleMgr::Instance().PushGuildName(qwGuildID, strGuildName, byGuildLvl, strGuildOwnerName);
                        }
                    }
                });
    }
    return true;
}		// -----  end of function PushHistory  ----- //


// ===  FUNCTION  ======================================================================
//         Name:  ChangeGuildLevel
//  Description:  改变帮派等级
// =====================================================================================
void CMountain::ChangeGuildLevel (UINT64 qwGuildID, UINT16 wLevel)
{
    if (_qwGuildID == qwGuildID)
        _wGuildLevel = wLevel;
}		// -----  end of function ChangeGuildLevel  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ChangeGuildOwnerName
//  Description:  改变帮派等级
// =====================================================================================
void CMountain::ChangeGuildOwnerName (UINT64 qwGuildID, const string& strName)
{
    if (_qwGuildID == qwGuildID)
        _strGuildOwnerName = strName;
}		// -----  end of function ChangeGuildOwnerName  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ClearGuild
//  Description:  帮派解散，清除存在的占领帮派
// =====================================================================================
void CMountain::ClearGuild (UINT64 qwGuildID)
{
    if (_qwGuildID == qwGuildID)
    {
        _qwGuildID = 0;
        _wGuildLevel = 0;
        _strGuildName = "";
        _strGuildOwnerName = "";
        _dwGuildOwnCount = 0;
        _dwCaptureTime = 0;
    }
}		// -----  end of function ClearGuild  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  BattleProcess
//  Description:  战斗进程
// =====================================================================================
void CMountain::BattleProcess (time_t tNow)
{
    switch (GetState())
    {
        case eNGBMSGate: //城门战
            if (_pGate)
            {
                _pGate->BattleProcess(tNow);

                // 城门攻破，进入洞府战
                if (_pGate->IsBroken())
                    StartCave();
            }
            else
                LOG_CRI << "Wrong gate: " << static_cast<UINT32>(GetState()) << ".";
            break;
        case eNGBMSCave: //洞府战
            if (_pCave)
            {
                _pCave->BattleProcess(tNow);
                if (_pCave->GetWinnerID())
                    EndBattle(false);
            }
            else
                LOG_CRI << "Wrong cave: " << static_cast<UINT32>(GetState()) << ".";
            break;
        case eNGBMSEnd: //战斗结束
            break;
        case eNGBMSNone: //无效状态
        default:
            LOG_CRI << "Wrong state: " << static_cast<UINT32>(GetState()) << ".";
    }
}		// -----  end of function BattleProcess  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerEnter
//  Description:  玩家进入
// =====================================================================================
ENGBEnterResult CMountain::PlayerEnter (CPlayerPtr pPlayer)
{
    ENGBEnterResult eResult = eNGBERFailed;
    if (!pPlayer)
        return eResult;
    if (pPlayer->GetMountain() != eNGBMNone)
    {
        eResult = eNGBERRepeat;
        return eResult;
    }

    switch (GetState())
    {
        case eNGBMSGate: //城门战
            if (_pGate)
                eResult = _pGate->PlayerEnter(pPlayer);
            else
                LOG_CRI << "Wrong gate: " << static_cast<UINT32>(GetState()) << ".";
            break;
        case eNGBMSCave: //洞府战
            if (_pCave)
                eResult = _pCave->PlayerEnter(pPlayer);
            else
                LOG_CRI << "Wrong cave: " << static_cast<UINT32>(GetState()) << ".";
            break;
        case eNGBMSEnd: //战斗结束
        case eNGBMSNone: //无效状态
        default:
            LOG_CRI << "Wrong state: " << static_cast<UINT32>(GetState()) << ".";
    }
    return eResult;
}		// -----  end of function PlayerEnter  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  PlayerQuit
//  Description:  玩家退出
// =====================================================================================
ENGBQuitResult  CMountain::PlayerQuit (CPlayerPtr pPlayer)
{
    ENGBQuitResult eResult = eNGBQuitFailed;
    switch (GetState())
    {
        case eNGBMSGate: //城门战
            if (_pGate)
                eResult = _pGate->PlayerQuit(pPlayer);
            else
                LOG_CRI << "Wrong gate: " << static_cast<UINT32>(GetState()) << ".";
            break;
        case eNGBMSCave: //洞府战
            if (_pCave)
                eResult = _pCave->PlayerQuit(pPlayer);
            else
                LOG_CRI << "Wrong cave: " << static_cast<UINT32>(GetState()) << ".";
            break;
        case eNGBMSEnd: //战斗结束
        case eNGBMSNone: //无效状态
        default:
            LOG_CRI << "Wrong state: " << static_cast<UINT32>(GetState()) << ".";
    }

    // 不管怎样，全部退出
    eResult = eNGBQuitSuccess;
    pPlayer->SetMountain(eNGBMNone, eNGBSideInvalid);
    return eResult;
}		// -----  end of function PlayerQuit  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Reward
//  Description:  奖励结算
// =====================================================================================
void CMountain::Reward (UINT64 qwRoleID) const
{
    TVecUINT64 vecTargets;
    vecTargets.push_back(qwRoleID);

    CPlayerPtr pPlayer = CBattleMgr::Instance().GetPlayer(qwRoleID);
    if (!pPlayer)
        return;
    UINT64 qwGuildID = pPlayer->GetGuildID();
    UINT16 wLevel = CBattleMgr::Instance().GetGuildLevel(qwGuildID);
    if (!wLevel)
        wLevel = 1;

    UINT32 dwScore = CBattleMgr::Instance().GetPlayerRankMgr()->GetPlayerScore(qwRoleID, GetType());
    if (dwScore)
    {
        // 灵山战个人奖励
        // 您在本次$s灵山争夺战中功勋卓著，根据战功点数给予你应得的奖励，点击附件领取！
        TVecItemGenInfo vecItems;
        vecItems.push_back(SItemGenInfo(29, dwScore, 0,  eBindGet, 0));
        NMailProt::SysMailSendTxt stBody;
        stBody.dwstrMsgID = BODY_NEW_GUILD_BATTLE_SELF_MAIL;
        stBody.vecParam.push_back(GetName());
        GameServerSysMail::SendSysMail(SEND_NEW_GUILD_BATTLE_SELF_MAIL, TITLE_NEW_GUILD_BATTLE_SELF_MAIL, stBody, vecTargets, &vecItems);

        // 灵山占领奖励
        // 由于您的卓越表现，贵帮派在$s洞府争夺中取得了胜利，占领了该灵山，根据您的表现获得丰厚奖励，点击附件领取！
        if (qwGuildID == _qwGuildID)
        {
            TVecItemGenInfo vecItems2;
            vecItems2.push_back(SItemGenInfo(29, wLevel * SParamConfig::wLingMountainSucceedAward, 0, eBindGet, 0));
            NMailProt::SysMailSendTxt stBody2;
            stBody2.dwstrMsgID = BODY_NEW_GUILD_BATTLE_CAPTURE_MAIL;
            stBody2.vecParam.push_back(GetName());
            GameServerSysMail::SendSysMail(SEND_NEW_GUILD_BATTLE_CAPTURE_MAIL, TITLE_NEW_GUILD_BATTLE_CAPTURE_MAIL, stBody2, vecTargets, &vecItems2);
        }
        else
        {
            // 灵山洞府战奖励
            // 贵帮派在$s洞府争夺中遗憾落败，占领了该灵山，但根据您的优异表现获得丰厚奖励，点击附件领取！
            for(auto & rID : _vecCaveAttackGuildID)
            {
                if (rID == qwGuildID)
                {
                    TVecItemGenInfo vecItems3;
                    vecItems3.push_back(SItemGenInfo(29, wLevel * SParamConfig::wLingMountainFailAward, 0, eBindGet, 0));
                    NMailProt::SysMailSendTxt stBody3;
                    stBody3.dwstrMsgID = BODY_NEW_GUILD_BATTLE_LOST_MAIL;
                    stBody3.vecParam.push_back(GetName());
                    GameServerSysMail::SendSysMail(SEND_NEW_GUILD_BATTLE_LOST_MAIL, TITLE_NEW_GUILD_BATTLE_LOST_MAIL, stBody3, vecTargets, &vecItems3);
                }
            }
        }
    }
}		// -----  end of function Reward  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GMCapture
//  Description:  GM命令占领该山
// =====================================================================================
bool CMountain::GMCapture (UINT64 qwGuildID, const string& strName, UINT16 wLevel)
{
    switch (GetState())
    {
        case eNGBMSGate:
        case eNGBMSCave:
            return false;
        default:
            break;
    }
    time_t tNow = Time::Now();

    _qwGuildID          = qwGuildID;
    _strGuildName       = strName;
    _wGuildLevel        = wLevel;
    _strGuildOwnerName  = "GM干的";
    _dwGuildOwnCount    = 9527;

    CMountainHistoryPtr pHistory(new CMountainHistory(GetType(), qwGuildID, strName, _strGuildOwnerName, tNow));
    _listHistoryPtr.push_front(pHistory);
    return true;
}		// -----  end of function GMCapture  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  StartGate
//  Description:  开始城门战
// =====================================================================================
bool CMountain::StartGate ()
{
    _pGate = NULL;
    _eState = eNGBMSGate;
    _pGate.reset(new CGate(ToThisPtr(this)));
    return _pGate->StartBattle(_qwGuildID);
}		// -----  end of function StartGate  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  StartCave
//  Description:  开始洞府战
// =====================================================================================
bool CMountain::StartCave ()
{
    _pCave = NULL;
    _eState = eNGBMSCave;
    _pCave.reset(new CCave(ToThisPtr(this)));

    _vecCaveAttackGuildID.clear();

    TVecUINT64 vecGuildID;
    TVecString vecGuildName;
    TVecUINT64 vecRoleID;
    if (_pGate)
    {
        _pGate->EndBattle(false);
        _pGate->GetGuildAndPlayer(vecGuildID, vecGuildName, vecRoleID);
        _pGate = NULL;
    }
    return _pCave->StartBattle(_qwGuildID, vecGuildID, vecGuildName, vecRoleID);
}		// -----  end of function StartCave  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  CMountainHistory
//  Description:  构造函数
// =====================================================================================
CMountainHistory::CMountainHistory (ENGBMountain eMountainType, 
                UINT64 qwGuildID, const string& strName, const string& strOwnerName, 
                UINT32 dwTime):
    _eMountainType(eMountainType),
    _qwGuildID(qwGuildID), _strGuildName(strName), _strGuildOwnerName(strOwnerName),
    _dwTime(dwTime)
{
}		// -----  end of function CMountainHistory  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CMountainHistory
//  Description:  析构函数
// =====================================================================================
CMountainHistory::~CMountainHistory ()
{
}		// -----  end of function ~CMountainHistory  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllInfo
//  Description:  协议参数序列化
// =====================================================================================
bool CMountainHistory::GetAllInfo (SOwnerHistoryInfo& rInfo) const
{
    rInfo.eMountainType      = _eMountainType;
    rInfo.qwGuildID          = _qwGuildID;
    rInfo.strGuildName       = _strGuildName;
    rInfo.strGuildOwnerName  = _strGuildOwnerName;
    rInfo.dwTime             = _dwTime;

    return true;
}		// -----  end of function GetAllInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllInfo
//  Description:  协议参数序列化
// =====================================================================================
bool CMountainHistory::GetAllInfo (NGame2DBComm::SDBGuildNewBattleHistoryInfo& rInfo) const
{
    rInfo.byMountainType    = static_cast<UINT8>(_eMountainType);
    rInfo.qwGuildID          = _qwGuildID;
    rInfo.strGuildName       = _strGuildName;
    rInfo.strGuildOwnerName  = _strGuildOwnerName;
    rInfo.dwTime             = _dwTime;

    return true;
}		// -----  end of function GetAllInfo  ----- //

} // namespace NNewGuildBattle
