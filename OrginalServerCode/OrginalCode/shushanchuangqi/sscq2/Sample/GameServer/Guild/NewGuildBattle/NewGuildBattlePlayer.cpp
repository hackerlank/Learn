// =====================================================================================
//
//       Filename:  NewGuildBattlePlayer.cpp
//
//    Description:  新帮派战玩家数据
//
//        Version:  1.0
//        Created:  03/21/2015 05:25:44 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "NewGuildBattlePlayer.h"

#include "NewGuildBattlePuppet.h"

#include "Player.h"
#include "HeroFighter.h"
#include "RTime.h"
#include "User.h"

#include "Parameter.h"

namespace NNewGuildBattle
{

static TVecPuppetPtr s_vecNullPuppet;

// ===  FUNCTION  ======================================================================
//         Name:  CPlayer
//  Description:  构造函数
// =====================================================================================
CPlayer::CPlayer (::CPlayerPtr pPlayer, UINT64 qwGuildID, 
        const string& strGuildName, UINT16 wGuildLevel, const string& strGuildOwnerName):
    _pPlayer(pPlayer),
    _qwRoleID(0), 
    _qwGuildID(qwGuildID), _strGuildName(strGuildName), _wGuildLevel(wGuildLevel), _strGuildOwnerName(strGuildOwnerName),
    _dwScore(0), _dwDeadTime(0), _eMountainType(eNGBMNone), _eSide(eNGBSideInvalid)
{
    if (pPlayer)
    {
        _qwRoleID   = pPlayer->GetRoleID();
        _strName    = pPlayer->GetName();
    }
}		// -----  end of function CPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CPlayer
//  Description:  析构函数
// =====================================================================================
CPlayer::~CPlayer ()
{
}		// -----  end of function ~CPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPlayer
//  Description:  获取玩家的Player对象
// =====================================================================================
::CPlayerPtr CPlayer::GetPlayer () const
{
    return _pPlayer.lock();
}		// -----  end of function GetPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetRoleID
//  Description:  获取玩家ID
// =====================================================================================
UINT64 CPlayer::GetRoleID () const
{
    return _qwRoleID;
}		// -----  end of function GetRoleID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetName
//  Description:  获取玩家姓名
// =====================================================================================
const string& CPlayer::GetName () const
{
    return _strName;
}		// -----  end of function GetName  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildID
//  Description:  获取帮派ID
// =====================================================================================
UINT64 CPlayer::GetGuildID () const
{
    return _qwGuildID;
}		// -----  end of function GetGuildID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildName
//  Description:  获取帮派姓名
// =====================================================================================
const string& CPlayer::GetGuildName () const
{
    return _strGuildName;
}		// -----  end of function GetGuildName  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildLevel
//  Description:  获取帮派姓名
// =====================================================================================
UINT16 CPlayer::GetGuildLevel () const
{
    return _wGuildLevel;
}		// -----  end of function GetGuildLevel  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetGuildOwnerName
//  Description:  获取帮派姓名
// =====================================================================================
const string& CPlayer::GetGuildOwnerName () const
{
    return _strGuildOwnerName;
}		// -----  end of function GetGuildName  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetScore
//  Description:  获取战功
// =====================================================================================
UINT32 CPlayer::GetScore (ENGBMountain eMountainType) const
{
    auto it = _mapScore.find(eMountainType);
    if (it == _mapScore.end())
        return 0;
    else
        return it->second;
}		// -----  end of function GetScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetScore
//  Description:  获取战功
// =====================================================================================
UINT32 CPlayer::GetScore () const
{
    return _dwScore;
}		// -----  end of function GetScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetDeadTime
//  Description:  获取死亡需要复活的时间
// =====================================================================================
UINT32 CPlayer::GetDeadTime () const
{
    time_t tNow = Time::Now();
    if (tNow < _dwDeadTime)
        return _dwDeadTime - tNow;
    else
        return 0;
}		// -----  end of function GetDeadTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetMountain
//  Description:  获取自己参战的灵山类型
// =====================================================================================
ENGBMountain CPlayer::GetMountain () const
{
    return _eMountainType;
}		// -----  end of function GetMountain  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSide
//  Description:  获取自己所在的方向
// =====================================================================================
ENGBSide    CPlayer::GetSide() const
{
    return _eSide;
}		// -----  end of function GetSide  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllPuppet
//  Description:  获取所有购买的傀儡
// =====================================================================================
TVecPuppetPtr& CPlayer::GetAllPuppet (ENGBMountain eMountainType)
{
    auto it = _mapPuppet.find(eMountainType);
    if (it == _mapPuppet.end())
        return s_vecNullPuppet;
    return it->second;
}		// -----  end of function GetAllPuppet  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllInfo
//  Description:  获取所有信息
// =====================================================================================
bool CPlayer::GetAllInfo (NNewGuildBattleProt::SPlayerInfo& rInfo) const
{
    rInfo.qwRoleID  = GetRoleID();
    rInfo.strName   = GetName();

    ::CPlayerPtr pPlayer   = GetPlayer();
    if (pPlayer)
    {
        rInfo.eJob = pPlayer->GetMainFighter()->GetJob();
        rInfo.eSex = pPlayer->GetMainFighter()->GetSex();
        rInfo.byQuality = pPlayer->GetColor(); //品质
        rInfo.dwMaxHP   = pPlayer->GetMaxHP2(); //最大血量
        rInfo.dwHP      = pPlayer->GetCurrHP(); //当前血量
    }
    rInfo.qwGuildID = GetGuildID();
    rInfo.eSide     = GetSide();
	rInfo.dwDeadTime = GetDeadTime(); //死亡时间（复活所需时间）
    return true;
}		// -----  end of function GetAllInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllPanelInfo
//  Description:  获取所有信息
// =====================================================================================
bool CPlayer::GetAllPanelInfo (NNewGuildBattleProt::SPlayerPanelInfo& rInfo) const
{
    bool bRet = false;
    rInfo.qwRoleID      = GetRoleID();
    rInfo.strName       = GetName();
    rInfo.qwGuildID     = GetGuildID();
    rInfo.strGuildName  = GetGuildName();
    rInfo.eSide         = GetSide();

    ::CPlayerPtr pPlayer   = GetPlayer();
    if (pPlayer)
    {
        rInfo.byLevel   = pPlayer->GetLevel();
        if (GetDeadTime())
        {
            rInfo.byHPP = 0;
            bRet = false;
        }
        else
        {
            rInfo.byHPP     = pPlayer->GetCurrHP() * 100 / pPlayer->GetMaxHP2();
            bRet = true;
        }
        rInfo.byQuality = pPlayer->GetColor();
        rInfo.dwMaxHP   = pPlayer->GetMaxHP2(); //最大血量
        rInfo.dwHP      = pPlayer->GetCurrHP(); //当前血量
    }
    return bRet;
}		// -----  end of function GetAllPanelInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetPuppetInfo
//  Description:  获取傀儡信息
// =====================================================================================
bool CPlayer::GetPuppetInfo (TVecPuppetInfo& rvecInfo, ENGBMountain eMountainType /* = eNGBMNone */ ) const
{
    if (eMountainType == eNGBMNone)
        eMountainType = GetMountain();
    auto it = _mapPuppet.find(eMountainType);
    if (it == _mapPuppet.end())
        return false;

    const TVecPuppetPtr& rvecPuppet = it->second;
    UINT8 byIndex = 0;
    for (auto & pInfo : rvecPuppet)
    {
        if (!pInfo)
            continue;
        SPuppetInfo sInfo;
        sInfo.byIndex   = ++ byIndex;
        sInfo.qwOwnerID = GetRoleID();
        sInfo.dwNextAttackTime  = pInfo->GetNextAttackTime();
        rvecInfo.push_back(sInfo);
    }
    return true;
}		// -----  end of function GetPuppetInfo  ----- //

// ===  FUNCTION  ====================================================================== 
//         Name:  SetScore
//  Description:  设置战功
// =====================================================================================
void CPlayer::SetScore (ENGBMountain eMountainType, UINT32 dwScore)
{
    _mapScore[eMountainType] = dwScore;
}		// -----  end of function SetScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddScore
//  Description:  增加战功
// =====================================================================================
void CPlayer::AddScore (ENGBMountain eMountainType, UINT32 dwScore)
{
    _mapScore[eMountainType] += dwScore;
}		// -----  end of function AddScore  ----- //

// ===  FUNCTION  ====================================================================== 
//         Name:  SetScore
//  Description:  设置战功
// =====================================================================================
void CPlayer::SetScore (UINT32 dwScore)
{
    _dwScore = dwScore;
}		// -----  end of function SetScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddScore
//  Description:  增加战功
// =====================================================================================
void CPlayer::AddScore (UINT32 dwScore)
{
    _dwScore += dwScore;
}		// -----  end of function AddScore  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetDeadTime
//  Description:  设置死亡时间
// =====================================================================================
void CPlayer::SetDeadTime (UINT32 dwTime)
{
    time_t tNow = Time::Now();
    _dwDeadTime = tNow + dwTime;
}		// -----  end of function SetDeadTime  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetMountain
//  Description:  设置自己参战的灵山类型
// =====================================================================================
void CPlayer::SetMountain (ENGBMountain eMountainType, ENGBSide eSide)
{
    _eMountainType = eMountainType;
    _eSide = eSide;
}		// -----  end of function SetMountain  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetPlayer
//  Description:  设置玩家指针
// =====================================================================================
void CPlayer::SetPlayer (::CPlayerPtr pPlayer)
{
    _pPlayer = pPlayer;
}		// -----  end of function SetPlayer  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  BuyPuppet
//  Description:  购买攻城傀儡
// =====================================================================================
ENGBBuyPuppetResult CPlayer::BuyPuppet (ENGBMountain eMountainType, UINT32 dwStartTime)
{
    TVecPuppetPtr& rvecPuppetPtr = _mapPuppet[eMountainType];
    //if (rvecPuppetPtr.size() >= SParamConfig::wLingMountainRobotNumLimit)
    if (rvecPuppetPtr.size() >= 2)
        return eNGBBPRCountLimit;
    ::CPlayerPtr pPlayer = GetPlayer();
    if (!pPlayer)
        return eNGBBPRFailed;
    CUserPtr pUser = pPlayer->GetUserPtr();
    if (!pUser)
        return eNGBBPRFailed;

    if (!pUser->CanSubMoney(EMONEY_GOLD, SParamConfig::wLingMountainRobotPrice))
        return eNGBBPRLackOfMoney;
    pUser->SubMoney(EMONEY_GOLD, SParamConfig::wLingMountainRobotPrice, NLogDataDefine::ItemTo_NewGuildBattleBuyPuppet);

    CPuppetPtr pPuppet (new CPuppet);
    if (pPuppet)
    {
        pPuppet->SetNextAttackTime(dwStartTime);
        pPuppet->CalcNextAttackTime();
        rvecPuppetPtr.push_back(pPuppet);
        return eNGBBPRSuccess;
    }
    else
        return eNGBBPRFailed;
}		// -----  end of function BuyPuppet  ----- //
// ===  FUNCTION  ======================================================================
//         Name:  StopPuppet
//  Description:  停止指定灵山的攻城傀儡
// =====================================================================================
void CPlayer::StopPuppet (ENGBMountain eMountainType)
{
    auto it = _mapPuppet.find(eMountainType);
    if (it == _mapPuppet.end())
        return;
    for (auto& pPuppet : it->second)
    {
        if (!pPuppet)
            continue;
        pPuppet->Stop();
    }
    it->second.clear();
}		// -----  end of function StopPuppet  ----- //

} // namespace NNewGuildBattle
