#include "Protocols.h"
#include "TripodMgr.h"
#include "TripodManager.h"
#include "TripodSlots.h"
#include "TripodProtS.h"
#include "VarDefine.h"
#include "User.h"
#include "UserMgr.h"
#include "Friend.h"

bool CTripodManager::_bLoadFromDB = false;
bool CTripodManager::_bLoadHelpFromDB = false;
bool CTripodManager::_bLoadLogFromDB = false;

void CTripodManager::TimerCheck(time_t tNow)
{
    /*
    for (auto iter = _mapAllTripod.begin(); iter != _mapAllTripod.end(); ++ iter)
    {
        bool bRes = iter->second.TimerCheck(tNow);
        if (bRes)
        {
            CUserPtr pUser = CUserMgr::GetUserByUserID(iter->first);
            if (pUser)
                Send_UpdateTripod(pUser);
        }
    }
    */
    vector<STripodTimerKey> vecTimerKey;
    auto itLast = _mapTimerTripodOpposite.end();
    for(auto it = _mapTimerTripodOpposite.begin(); it != _mapTimerTripodOpposite.end(); ++ it)
    {
        if(it->first <= tNow)
        {
            vecTimerKey.push_back(it->second);
        }
        else
        {
            itLast = it;
            break;
        }
    }
    if(vecTimerKey.empty())
        return;
    //XXX delete time
    _mapTimerTripodOpposite.erase(_mapTimerTripodOpposite.begin(), itLast);

    for(auto iter = vecTimerKey.begin(); iter != vecTimerKey.end(); ++ iter)
    {
        _mapTimerTripodForward.erase(*iter);
        auto it = _mapAllTripod.find(iter->qwUserID);
        if (it == _mapAllTripod.end())
            continue;
        bool bRes = it->second.TimerCheck(tNow);
        if (bRes)
        {
            CUserPtr pUser = CUserMgr::GetUserByUserID(it->first);
            if (pUser)
                Send_UpdateTripod(pUser);
        }
    }
}

void CTripodManager::OnUserLogin(CUserPtr pUser)
{
    if (!pUser)
        return;
    CTripodSlots& tripodSlots = GetTripodSlots(pUser->GetUserID());
    tripodSlots.UpdateTripodAttr(pUser);
}

bool CTripodManager::SettleTripodFireSoul(UINT64 qwRoleID)
{
    CTripodSlots& tripodSlots = GetTripodSlots(qwRoleID);
    return tripodSlots.SettleTripodFireSoul();
}

void CTripodManager::Send_UpdateTripod(CUserPtr pUser)
{
    if (!pUser)
        return;
    if (!pUser->IsOnline())
        return;
    CTripodSlots& tripodSlots = GetTripodSlots(pUser->GetUserID());
    STripodData oTripodData;
    tripodSlots.GetAllTripods(oTripodData);
    UINT8 byValue = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarTripodShanfeng);
    UINT8 byHelpTimes = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarTripodHelp);
    pUser->SendPkg(g_TripodProtS.BuildPkg_UpdateTripod(oTripodData, byValue, byHelpTimes));
}

bool CTripodManager::LoadTripodFromDB()
{
    if (_bLoadFromDB)
        return false;

    UINT32 dwsize = TAKE_ARRAY_LENGTH(STripodData);
    g_Center2DBCommC.Send_GetAllTripod(dwsize);
    _bLoadFromDB = true;
    return true;
}

bool CTripodManager::LoadTripodHelpFromDB()
{
    if (_bLoadHelpFromDB)
        return false;

    UINT32 dwsize = TAKE_ARRAY_LENGTH(STripodHelp);
    g_Center2DBCommC.Send_GetAllTripodHelper(dwsize);
    _bLoadHelpFromDB = true;
    return true;
}

bool CTripodManager::LoadTripodLogFromDB()
{
    if (_bLoadLogFromDB)
        return false;

    UINT32 dwsize = TAKE_ARRAY_LENGTH(STripodHelp);
    g_Center2DBCommC.Send_GetAllTripodLog(dwsize);
    _bLoadLogFromDB = true;
    return true;
}

void CTripodManager::RecieveDBData(UINT32 dwCurPage, UINT32 dwTotalPage, const NTripodProt::TVecTripodData& vecSendData)
{
    for (size_t i = 0; i < vecSendData.size(); ++ i)
    {
        UINT64 qwRoleID = vecSendData[i].qwRoleID;
        if (!qwRoleID)
            continue;
        CTripodSlots& tripodSlots = GetTripodSlots(qwRoleID);
        tripodSlots.LoadTripodFromDB(vecSendData[i]);
    }
    if (dwCurPage == dwTotalPage)
    {
        LoadTripodHelpFromDB();
        LoadTripodLogFromDB();
    }
}

void CTripodManager::RecieveDBData(UINT32 dwCurPage, UINT32 dwTotalPage, const NTripodProt::TVecTripodHelp& vecSendData)
{
    for (size_t i = 0; i < vecSendData.size(); ++ i)
    {
        UINT64 qwRoleID = vecSendData[i].qwRoleID;
        if (!qwRoleID)
            continue;
        CTripodSlots& tripodSlots = GetTripodSlots(qwRoleID);
        tripodSlots.LoadTripodHelpFromDB(vecSendData[i]);
    }
    //XXX handle timer
    for (auto iter = _mapAllTripod.begin(); iter != _mapAllTripod.end(); ++ iter)
    {
        for (size_t iSlot = 0; iSlot < static_cast<size_t>(iter->second.GetSlots()); ++ iSlot)
        {
            CTripodPtr pTripod = iter->second.Get(iSlot);
            if (!pTripod || !pTripod->HasFire())
                continue;
            iter->second.ResetTripodTimerCheck(pTripod);
        }
    }
}

void CTripodManager::RecieveDBData(UINT32 dwCurPage, UINT32 dwTotalPage, const NTripodProt::TVecTripodLog& vecSendData)
{
    for (auto it = vecSendData.rbegin(); it != vecSendData.rend(); ++it)
    {
        UINT64 qwRoleID = (*it).qwRoleID;
        if (!qwRoleID)
            continue;
        CTripodSlots& tripodSlots = GetTripodSlots(qwRoleID);
        tripodSlots.LoadTripodLogFromDB(*it);
    }
}

CTripodSlots& CTripodManager::GetTripodSlots(UINT64 qwRoleID)
{
    auto iter = _mapAllTripod.find(qwRoleID);
    if (iter == _mapAllTripod.end())
    {
        CTripodSlots tripodSlots(qwRoleID);
        auto pairRet = _mapAllTripod.insert(make_pair(qwRoleID, tripodSlots));
        if (!pairRet.second)
            LOG_CRI  << "TripodSlots insert Error!qwRoleID: " << qwRoleID;
        iter = pairRet.first;
    }
    return iter->second;
}

void CTripodManager::GetAllTripods(CUserPtr pUser, STripodData& oTripodData)
{
    if (!pUser)
        return;
    UINT64 qwRoleID = pUser->GetUserID();
    if (!qwRoleID)
        return;
    CTripodSlots& tripodSlots = GetTripodSlots(qwRoleID);
    if (!tripodSlots.GetTripod(1) && pUser->HasIcon(17))
    {
        // XXX 默认给第一个九疑鼎
        CTripodPtr pTripod = tripodSlots.ActiveTripod(pUser, 1);
        if (pTripod)
            pTripod->Update2DB();
    }
    tripodSlots.GetAllTripods(oTripodData);
}

// 激活丹炉
ETripodType CTripodManager::ActiveTripod(CUserPtr pUser, UINT8 byTripodID, shared_func<CTripodProtSvr::SActiveTripodAck> fnAck)
{
    if (!pUser || !byTripodID || !pUser->GetUserID())
        return eTripodFailed;

    CTripodSlots& tripodSlots = GetTripodSlots(pUser->GetUserID());
    return tripodSlots.ActiveTripod(pUser, byTripodID, fnAck);
}

ETripodType CTripodManager::UpgradeTripod(CUserPtr pUser, UINT8 byTripodID, UINT8 byOneKey, shared_func<CTripodProtSvr::SUpgradeTripodAck> fnAck)
{
    if (!pUser || !byTripodID || !pUser->GetUserID())
        return eTripodFailed;

    CTripodSlots& tripodSlots = GetTripodSlots(pUser->GetUserID());
    return tripodSlots.UpgradeTripod(pUser, byTripodID, byOneKey, fnAck);
}

ETripodType CTripodManager::MakeFireTripod(CUserPtr pUser, UINT8 byTripodID, UINT16 wFireID, shared_func<CTripodProtSvr::SMakeFireTripodAck> fnAck)
{
    if (!pUser || !byTripodID || !wFireID)
        return eTripodFailed;

    CTripodSlots& tripodSlots = GetTripodSlots(pUser->GetUserID());
    return tripodSlots.MakeFireTripod(pUser, byTripodID, wFireID, fnAck);
}

ETripodType CTripodManager::ClearFireTripod(CUserPtr pUser, UINT8 byTripodID)
{
    if (!pUser || !byTripodID || !pUser->GetUserID())
        return eTripodFailed;

    CTripodSlots& tripodSlots = GetTripodSlots(pUser->GetUserID());
    return tripodSlots.ClearFireTripod(pUser, byTripodID);
}

ETripodType CTripodManager::GetTripodAward(CUserPtr pUser, UINT8 byTripodID, shared_func<CTripodProtSvr::SGetTripodAwardAck> fnAck)
{
    if (!pUser || !byTripodID || !pUser->GetUserID())
        return eTripodFailed;

    CTripodSlots& tripodSlots = GetTripodSlots(pUser->GetUserID());
    return tripodSlots.GetTripodAward(pUser, byTripodID, fnAck);
}

ETripodType CTripodManager::SpeedTripod(CUserPtr pUser, UINT8 byTripodID, const NItemProt::TVecItemCount& vecItems, shared_func<CTripodProtSvr::SSpeedTripodAck> fnAck)
{
    if (!pUser || !byTripodID || !pUser->GetUserID())
        return eTripodFailed;

    CTripodSlots& tripodSlots = GetTripodSlots(pUser->GetUserID());
    return tripodSlots.SpeedTripod(pUser, byTripodID, vecItems, fnAck);
}

ETripodType CTripodManager::AddTripodExtraSoul(CUserPtr pUser, UINT64 qwRoleID, UINT8 byTripodID, TVecTripodInfo& vecTripods)
{
    if (!pUser || !byTripodID || !qwRoleID)
        return eTripodFailed;

    CTripodSlots& tripodSlots = GetTripodSlots(qwRoleID);
    return tripodSlots.AddTripodExtraSoul(pUser, byTripodID, vecTripods);
}

ETripodType CTripodManager::FighterHelpTripod(CUserPtr pUser, UINT16 wFighterID, UINT8 byPos, shared_func<CTripodProtSvr::SFighterHelpTripodAck> fnAck)
{
    if (!pUser || !wFighterID)
        return eTripodFailed;

    CTripodSlots& tripodSlots = GetTripodSlots(pUser->GetUserID());
    return tripodSlots.FighterHelpTripod(pUser, wFighterID, byPos, fnAck);
}

ETripodType CTripodManager::UserHelpTripod(CUserPtr pUser, UINT64 qwRoleID, UINT8 byPos, function<void(ETripodType eResult, SPlayerHelpInfo oPlayerHelp )> func)
{
    if (!pUser || !qwRoleID)
        return eTripodFailed;

    CTripodSlots& tripodSlots = GetTripodSlots(qwRoleID);
    ETripodType eResult = tripodSlots.UserHelpTripod(pUser, byPos, func);
    return eResult;
}

void CTripodManager::GetTripodStatus(CUserPtr pUser, const TVecUINT64& vecRoleID, TVecTripodStatus& vecStatus)
{
    if (vecRoleID.empty() || !pUser)
        return;
	CFriend& rFriend = pUser->GetFriend();
    for (size_t i = 0; i < vecRoleID.size(); ++ i)
    {
        if (!rFriend.IsFriend(vecRoleID[i]))
            continue;
        STripodStatus oTripodStatus;
        CTripodSlots& tripodSlots = GetTripodSlots(vecRoleID[i]);
        for (size_t iSlot = 0; iSlot < static_cast<size_t>(tripodSlots.GetSlots()); ++ iSlot)
        {
            CTripodPtr pTripod = tripodSlots.Get(iSlot);
            if (!pTripod || pTripod->CanGetAward())
                continue;
            if (pTripod->CanShanfeng())
            {
                oTripodStatus.byShanfengst = 1;
                break;
            }
        }
        oTripodStatus.qwRoleID = vecRoleID[i];
        oTripodStatus.byHelpst = tripodSlots.CanPlayerHelp() ? 1 : 0;
        vecStatus.push_back(oTripodStatus);
    }
}

ETripodType CTripodManager::ShotOffHelpTripod(CUserPtr pUser, UINT8 byPos, UINT8 byType)
{
    if (!pUser || !pUser->GetUserID())
        return eTripodFailed;

    CTripodSlots& tripodSlots = GetTripodSlots(pUser->GetUserID());
    ETripodType eResult = tripodSlots.ShotOffHelpTripod(byPos, byType);
    return eResult;
}

void CTripodManager::SyncAppear(UINT64 qwRoleID, function<void()> func)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (!pUser)
        return;
    CTripodSlots& tripodSlots = GetTripodSlots(qwRoleID);
    if (!tripodSlots.GetTripod(1) && pUser->HasIcon(17))
    {
        // XXX 默认给第一个九疑鼎
        CTripodPtr pTripod = tripodSlots.ActiveTripod(pUser, 1);
        if (pTripod)
            pTripod->Update2DB();
    }
    tripodSlots.SyncAppear(func);
}

void CTripodManager::ResetTripodTimerCheck(UINT64 qwRoleID, UINT8 byTripodID, UINT32 dwEndTime, bool bIsDel)
{
    if (!qwRoleID || !byTripodID)
        return;
    STripodTimerKey stTimerKey(qwRoleID, byTripodID);
    auto iter = _mapTimerTripodForward.find(stTimerKey);
    if (iter != _mapTimerTripodForward.end())
    {
        auto range = _mapTimerTripodOpposite.equal_range(iter->second);
        for (auto it = range.first; it != range.second; ++ it)
        {
            if(it->second.byTripodID == byTripodID && it->second.qwUserID == qwRoleID)
            {
                _mapTimerTripodOpposite.erase(it);
                break;
            }
        }
        _mapTimerTripodForward.erase(iter);
    }
    if (!bIsDel)
    {
        if(!dwEndTime)
            return;
        _mapTimerTripodForward.insert(make_pair(stTimerKey, dwEndTime));
        _mapTimerTripodOpposite.insert(make_pair(dwEndTime, stTimerKey));
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

