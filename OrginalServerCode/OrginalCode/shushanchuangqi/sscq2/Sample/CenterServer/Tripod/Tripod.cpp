#include "Protocols.h"
#include "TripodMgr.h"
#include "TripodManager.h"
#include "Tripod.h"
#include "Parameter.h"
#include "UserMgr.h"
#include "User.h"
#include "VIPMgr.h"
#include "RTime.h"

static string s_strInvalidName = "无名鼎";

CTripod::CTripod(UINT64 qwRoleID, UINT8 byTripodID)
    : _qwOwnerID(qwRoleID), _byTripodID(byTripodID), _byLevel(1), _dwExp(0), _bIsGeting(false)
{
}

CTripod::~CTripod()
{}

void CTripod::ToProt(STripodInfo& oTripodInfo)
{
    oTripodInfo.byTripodID     = GetID();
    oTripodInfo.byLevel        = GetLevel();
    oTripodInfo.dwExp          = GetExp();
    oTripodInfo.wFireID        = GetTripodData()._wFireID;
    oTripodInfo.byFireLvl      = GetTripodData()._byFireLvl;
    oTripodInfo.dwStartTime    = GetTripodData()._dwStartTime;
    oTripodInfo.dwShanfengTime = GetTripodData()._dwShanfengTime;
    oTripodInfo.dwSoul         = GetTripodData()._dwCurSoul;
    oTripodInfo.dwLine         = GetTripodData()._dwLine;
#ifdef AEIOU
    LOG_WRN << "ID: " << (UINT32)GetID() << ", StartTime: " << GetTripodData()._dwStartTime << ", dwSoul = " << GetTripodData()._dwCurSoul << ".";
#endif
}

const string& CTripod::GetName() const
{
    SStovePropCFGEx* pStovePropCfg = CTripodMgr::GetStovePropCfg(_byTripodID);
    if (pStovePropCfg)
        return pStovePropCfg->_Name;
    else
        return s_strInvalidName;
}

void CTripod::AddSoul(UINT32 dwSoul)
{
    _stTD._dwCurSoul += dwSoul;
    UINT32 dwMaxSoul = GetConfigMaxSoul();
    if (_stTD._dwCurSoul > dwMaxSoul)
        _stTD._dwCurSoul = dwMaxSoul;
}

void CTripod::AddSoul(UINT32 dwTime, const TVecFloat& vecRate, const TVecUINT32& vecTime)
{
    UINT32 dwMaxTime = Time::Now() - GetTripodData()._dwStartTime;
    if (dwMaxTime < dwTime)
        dwTime = dwMaxTime;
    FLOAT fSoul  = SParamConfig::wStoveSoulGain * GetTripodRate() * dwTime;
    auto it = vecRate.begin();
    auto it2 = vecTime.begin();
    for (; it != vecRate.end() && it2 != vecTime.end(); ++it, ++it2)
    {
        UINT32 dwTime2 = *it2;
        if (dwTime2 > dwTime)
            dwTime2 = dwTime;
        fSoul += SParamConfig::wStoveSoulGain * (*it) * (dwTime2);
    }
    _stTD._dwCurSoul += static_cast<UINT32>(fSoul);
    UINT32 dwMaxSoul = GetConfigMaxSoul();
    if (_stTD._dwCurSoul > dwMaxSoul)
        _stTD._dwCurSoul = dwMaxSoul;
}

void CTripod::SetSoul(UINT32 dwSoul)
{
    _stTD._dwCurSoul = dwSoul;
    UINT32 dwMaxSoul = GetConfigMaxSoul();
    if (_stTD._dwCurSoul > dwMaxSoul)
        _stTD._dwCurSoul = dwMaxSoul;
}

void CTripod::SetConfigMaxSoul()
{
    SStoveFireCFGEx* pStoveFireCfg = CTripodMgr::GetStoveFireCfg(GetTripodData()._wFireID);
    if (pStoveFireCfg)
        GetTripodData().SetMaxSoul(pStoveFireCfg->_VigorMax);
}

UINT32 CTripod::GetConfigMaxSoul()
{
    if (GetTripodData()._dwMaxSoul == 0)
    {
        SStoveFireCFGEx* pStoveFireCfg = CTripodMgr::GetStoveFireCfg(GetTripodData()._wFireID);
        if (!pStoveFireCfg)
            return 0;
        GetTripodData().SetMaxSoul(pStoveFireCfg->_VigorMax);
    }
    return GetTripodData()._dwMaxSoul;
}

FLOAT CTripod::GetTripodRate()
{
    float fRate = 1.0f;
    SStoveAttrCFGEx* pStoveAttrCfg = CTripodMgr::GetStoveAttrCfg(GetID(), GetLevel(), 1);
    if (pStoveAttrCfg)
        fRate += float(pStoveAttrCfg->_SpeedAddition) / 10000;
	CUserPtr pUser = CUserMgr::GetUserByUserID(_qwOwnerID);
	if(pUser)
    {
        SVIPLevelCFGEx* pVIPCfg = CVIPMgr::GetVIPLevelCfg(pUser->GetVIPLevel());
        if (pVIPCfg)
            fRate += float(pVIPCfg->_StoveSpeeding) / 10000;
    }
#ifdef AEIOU
    LOG_WRN << "UserID:" << GetOwnerID() << ", GetTripodRate():fRate:" << fRate;
#endif
    return fRate;
}

bool CTripod::SettleCurrentSoul()
{
    SStoveFireCFGEx* pStoveFireCfg = CTripodMgr::GetStoveFireCfg(GetTripodData()._wFireID);
    if (!pStoveFireCfg)
        return false;
    UINT32 dwCurtime = Time::Now();
    UINT32& dwStartTime = GetTripodData()._dwStartTime;
    if(dwStartTime >= dwCurtime)
        return false;
    if (GetTripodData().GetSoul() >= GetConfigMaxSoul())
        return true;

    if (dwStartTime == 0)
        dwStartTime = Time::Now();
    UINT32 dwSoul = (dwCurtime - dwStartTime) * SParamConfig::wStoveSoulGain * GetTripodRate() + GetTripodData().GetSoul();
    SetSoul(dwSoul);
    dwStartTime = Time::Now();
    Update2DB();
    return true;
}

bool CTripod::HasFire()
{
    return GetTripodData()._wFireID > 0;
}

bool CTripod::CanGetAward()
{
    /*
    SStoveFireCFGEx* pStoveFireCfg = CTripodMgr::GetStoveFireCfg(GetTripodData()._wFireID);
    if (!pStoveFireCfg)
        return false;
    UINT32 dwCurtime = Time::Now();
    UINT32 dwStartTime = GetTripodData()._dwStartTime;
    if(dwStartTime > dwCurtime || dwStartTime == 0)
        return false;

    UINT32 dwSoul = (dwCurtime - dwStartTime) * SParamConfig::wStoveSoulGain * GetTripodRate() + GetTripodData().GetSoul();
    */
    return GetTripodData().GetSoul() >= GetConfigMaxSoul();
}

bool CTripod::CanShanfeng()
{
    if (!HasFire())
        return false;
    return GetTripodData()._dwShanfengTime + SParamConfig::wStoveBellowColdTime <= Time::Now();
}

void CTripod::AddExp(UINT32 dwExp)
{
    _dwExp += dwExp;
    UINT8 byLvl = GetLevel();
    CTripodMgr::TestTripodLevelUp(GetID(), byLvl, _dwExp);
    if (GetLevel() != byLvl)
    {
        //SettleCurrentSoul();  //XXX 必须在SetLevel之前
        SetLevel(byLvl);
    }
}

void CTripod::Update2DB()
{
    STripodInfo oTripodInfo;
    ToProt(oTripodInfo);
    g_Center2DBCommC.Send_UpdateTripod(GetOwnerID(), oTripodInfo);
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

