#include "Protocols.h"
#include "TripodSlots.h"
#include "TripodMgr.h"
#include "TripodManager.h"
#include "ExpMgr.h"
#include "Parameter.h"
#include "VarDefine.h"
#include "User.h"
#include "TaskConf.h"
#include "UserMgr.h"
#include "RTime.h"
#include "SysMsgDefine.h"

class TripodEnumerate4List : public Enumerator<typename CVecSlots<int, CTripodPtr>::value_type>
{
public:
    typedef CVecSlots<int, CTripodPtr>::value_type value_type;

public:
    TripodEnumerate4List(STripodData& oTripodData) : oTripodData(oTripodData) {}

    bool operator()(value_type* obj)
    {
        if (obj && std::get<1>(*obj) && std::get<2>(*obj))
        {
            //std::get<2>(*obj)->SettleCurrentSoul();
            STripodInfo oTripodInfo;
            std::get<2>(*obj)->ToProt(oTripodInfo);
            oTripodData.vecTripods.push_back(oTripodInfo);
        }
        return true;
    }

public:
    STripodData& oTripodData;
};

CTripodSlots::CTripodSlots(UINT64 qwRoleID)
    : CVecSlots(3), _qwOwnerID(qwRoleID), _dwSettleTime(Time::Now()), _bAppearInited(false), _byAppearLoadCount(0)
{
}

bool CTripodSlots::TimerCheck(time_t tNow)
{
    //UINT32 dwSoul = GetAllHelpSoul(tNow, dwSettleTime);
    //return AddSoulToAllTripod(dwSoul);
    return UpdateTripodSoul(tNow);
}

void CTripodSlots::ResetTripodTimerCheck(CTripodPtr pTripod)
{
    if (!pTripod)
        return;
    UINT32 dwEndTime = 0;
    bool bIsDel = false;
    if (!pTripod->HasFire())
        bIsDel = true;
    else
    {
        if (pTripod->CanGetAward())
            bIsDel = true;
        else
        {
            TVecFloat vecRate;
            TVecUINT32 vecTime;
            UINT32 dwNow = time(NULL);
            GetAllHelpRate(dwNow, vecRate, vecTime);
            float fRate = pTripod->GetTripodRate();
            for (size_t i = 0; i < vecRate.size(); ++ i)
                fRate += vecRate[i];
            UINT32 dwMaxSoul = pTripod->GetConfigMaxSoul();
            UINT32 dwCurSoul = pTripod->GetSoul();
            dwEndTime = (dwMaxSoul - dwCurSoul) / (fRate*SParamConfig::wStoveSoulGain) + pTripod->GetStartTime();
            bIsDel = false;
        }
    }
    TripodManager.ResetTripodTimerCheck(GetOwnerID(), pTripod->GetID(), dwEndTime, bIsDel);
}

bool CTripodSlots::AddSoulToAllTripod(UINT32 dwSoul)
{
    bool bRes = false;
    if (dwSoul == 0)
        return bRes;
    for (size_t iSlot = 0; iSlot < static_cast<size_t>(GetSlots()); ++ iSlot)
    {
        CTripodPtr pTripod = Get(iSlot);
        if (!pTripod)
            continue;
        if (!pTripod->HasFire() || pTripod->CanGetAward())
            continue;
        pTripod->AddSoul(dwSoul);
        pTripod->Update2DB();
        bRes = true;
    }
    return bRes;
}

bool CTripodSlots::AddSoulToAllTripod(UINT32 dwTime, const TVecFloat& vecRate, const TVecUINT32& vecTime)
{
    bool bRes = false;
    if (dwTime == 0)
        return bRes;
    for (size_t iSlot = 0; iSlot < static_cast<size_t>(GetSlots()); ++ iSlot)
    {
        CTripodPtr pTripod = Get(iSlot);
        if (!pTripod)
            continue;
        if (!pTripod->HasFire() || pTripod->CanGetAward())
            continue;
        pTripod->AddSoul(dwTime, vecRate, vecTime);
        pTripod->Update2DB();
        bRes = true;
    }
    return bRes;
}

bool CTripodSlots::LoadTripodFromDB(const STripodData& oTripodData)
{
    const TVecTripodInfo& vecTripodInfo = oTripodData.vecTripods;
    size_t szTripods = vecTripodInfo.size();
    for (size_t i = 0; i < szTripods; ++i)
    {
        UINT8 byTripodID = vecTripodInfo[i].byTripodID;

        CTripodPtr pTripod = GetTripod(byTripodID);
        if (pTripod)
            continue;
        pTripod.reset(new CTripod(GetOwnerID(), byTripodID));
        pTripod->SetLevel(vecTripodInfo[i].byLevel);
        pTripod->SetExp(vecTripodInfo[i].dwExp);

        TripodData& sd = pTripod->GetTripodData();
        sd._wFireID         = vecTripodInfo[i].wFireID;
        sd._byFireLvl       = vecTripodInfo[i].byFireLvl;
        sd._dwStartTime     = vecTripodInfo[i].dwStartTime;
        sd._dwShanfengTime  = vecTripodInfo[i].dwShanfengTime;
        sd._dwCurSoul       = vecTripodInfo[i].dwSoul;
        sd._dwLine          = vecTripodInfo[i].dwLine;

        pTripod->SetConfigMaxSoul();

        Set(byTripodID - 1, pTripod);
    }
    _stPlayerAppear = oTripodData.stPlayer; // FIXME: 这里数据库压根就没有
    return true;
}

bool CTripodSlots::LoadTripodHelpFromDB(const STripodHelp& oTripodHelp)
{
    _vecFighterHelp = oTripodHelp.vecFighterHelp;
    _vecPlayerHelp  = oTripodHelp.vecPlayerHelp;
    for (auto& rInfo : _vecPlayerHelp)
    {
        rInfo.vecPlatforms = CUserMgr::GetPlatformParam(rInfo.qwRoleID);
    }
    return true;
}

bool CTripodSlots::LoadTripodLogFromDB(const STripodLog& oTripodLog)
{
    CTripodLogPtr pLog;
    switch(oTripodLog.wMsgID)
    {
        case eMsgStoveOtherBellow:
        case eMsgStoveOtherHelpBegin:
        case eMsgStoveOtherHelpEnd:
            {
                CTripodHelpLogPtr pHelpLog(new CTripodHelpLog(GetOwnerID()));
                if (pHelpLog)
                    pHelpLog->FormatParam(oTripodLog.wMsgID, oTripodLog.vecParam, oTripodLog.vecString, oTripodLog.dwTime);
                pLog = dynamic_pointer_cast<CTripodLog>(pHelpLog);
                break;
            }
            break;
    }
    if (pLog)
        AddLog(pLog, true);
    return true;
}

bool CTripodSlots::SettleTripodFireSoul()
{
    return UpdateTripodSoul(Time::Now());
    /*
    bool bRes = false;
    for (size_t iSlot = 0; iSlot < GetSlots(); ++ iSlot)
    {
        CTripodPtr pTripod = Get(iSlot);
        if (!pTripod)
            continue;
        bool bTmp = pTripod->SettleCurrentSoul();
        if (bTmp)
            bRes = bTmp;
    }
    return bRes;
    */
}

void CTripodSlots::UpdateTripodAttr(CUserPtr pUser)
{
    if (!pUser)
        return;
    TVecUINT32 vecValue;
    for (size_t iSlot = 0; iSlot < static_cast<size_t>(GetSlots()); ++ iSlot)
    {
        CTripodPtr pTripod = Get(iSlot);
        if (!pTripod)
            continue;
        UINT32 dwValue = pTripod->GetID() << 8 | pTripod->GetLevel();
        vecValue.push_back(dwValue);
    }
    UINT32 dwSeverID = pUser->GetGameSvrID();
    if (dwSeverID && !vecValue.empty())
        g_Game2CenterCommS.SendSvr_TripodAttrUpdate(&dwSeverID, 1, GetOwnerID(), vecValue);
}

// 获取散仙/玩家协助后的熔炼值
UINT32 CTripodSlots::GetAllHelpSoul(UINT32 dwNow, UINT32 dwSettleTime)
{
    FLOAT fSoul = 0.0f;
    bool bUpdate = false;
    fSoul += GetAllPlayerHelpSoul(dwNow, dwSettleTime, bUpdate);
    fSoul += GetAllFighterHelpSoul(dwNow, dwSettleTime, bUpdate);
    if (bUpdate)
        UpdateTripodHelp2DB();
    return fSoul;
}

// 获取散仙/玩家协助后的熔炼值
UINT32 CTripodSlots::GetAllHelpRate(UINT32 dwNow, TVecFloat& vecRate, TVecUINT32& vecTime)
{
    UINT32 dwTime = dwNow - _dwSettleTime;
    bool bUpdate = false;
    GetAllPlayerHelpRate(dwNow, vecRate, vecTime, bUpdate);
    GetAllFighterHelpRate(dwNow, vecRate, vecTime, bUpdate);
    if (bUpdate)
        UpdateTripodHelp2DB();
    return dwTime;
}

bool CTripodSlots::CanPlayerHelp(UINT64 qwRoleID, UINT8 byPos)
{
    if (!qwRoleID || GetSlots() <= 0 || byPos > 2)
        return false;
    auto it = _mapKickUserMap.find(qwRoleID);
    if (it != _mapKickUserMap.end())
    {
        if (it->second > Time::Now())
        {
            TVecUINT64 vecUserID;
            vecUserID.push_back(qwRoleID);
            g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgStoveHelpLeftCD);
            return false;
        }
    }
    for (size_t i = 0; i < _vecPlayerHelp.size(); ++ i)
    {
        if (_vecPlayerHelp[i].qwRoleID == qwRoleID
            && (_vecPlayerHelp[i].dwStartTime + SParamConfig::dwStoveHelpLastTimes > Time::Now()))
        {
            TVecUINT64 vecUserID;
            vecUserID.push_back(qwRoleID);
            g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgStoveAlreadyHelping);
            return false;
        }
    }
    for (size_t i = 0; i < _vecPlayerHelp.size(); ++ i)
    {
        if (byPos == _vecPlayerHelp[i].byPos)
        {
            if (_vecPlayerHelp[i].dwStartTime + SParamConfig::dwStoveHelpLastTimes <= Time::Now())
                return true;
            else
            {
                TVecUINT64 vecUserID;
                vecUserID.push_back(qwRoleID);
                g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgStoveBeBooked);
                return false;
            }
        }
    }
    if (_vecPlayerHelp.size() >= 3)
        return false;
    return true;
}

bool CTripodSlots::CanFighterHelp(UINT64 qwRoleID, UINT16 wFighterID, UINT8 byPos)
{
    if (!wFighterID || GetSlots() <= 0 || byPos > 1)
        return false;
    for (size_t i = 0; i < _vecFighterHelp.size(); ++ i)
    {
        if (byPos == _vecFighterHelp[i].byPos)
        {
            if (_vecFighterHelp[i].dwStartTime + SParamConfig::dwStoveHelpLastTimes > Time::Now())
            {
                TVecUINT64 vecUserID;
                vecUserID.push_back(qwRoleID);
                g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgStoveBeBooked);
                return false;
            }
            else
                return true;
        }
        if (_vecFighterHelp[i].wFighterID == wFighterID)
            return false;
    }
    if (_vecFighterHelp.size() >= 2)
        return false;
    return true;
}

bool CTripodSlots::CanPlayerOrFighterHelp()
{
    if (GetSlots() <= 0)
        return false;
    if (_vecPlayerHelp.size() >= 3 && _vecFighterHelp.size() >= 2)
    {
        for (size_t i = 0; i < _vecPlayerHelp.size(); ++ i)
        {
            if (_vecPlayerHelp[i].dwStartTime + SParamConfig::dwStoveHelpLastTimes <= Time::Now())
                return true;
        }
        for (size_t i = 0; i < _vecFighterHelp.size(); ++ i)
        {
            if (_vecFighterHelp[i].dwStartTime + SParamConfig::dwStoveHelpLastTimes <= Time::Now())
                return true;
        }
        return false;
    }
    return true;
}

bool CTripodSlots::CanPlayerHelp()
{
    if (GetSlots() <= 0)
        return false;
    if (_vecPlayerHelp.size() >= 3)
    {
        for (size_t i = 0; i < _vecPlayerHelp.size(); ++ i)
        {
            if (_vecPlayerHelp[i].dwStartTime + SParamConfig::dwStoveHelpLastTimes <= Time::Now())
                return true;
        }
        return false;
    }
    return true;
}

void CTripodSlots::InsertPlayerHelp(SPlayerHelpInfo& oPlayerHelp)
{
    for (size_t i = 0; i < _vecPlayerHelp.size(); ++ i)
    {
        if (oPlayerHelp.byPos == _vecPlayerHelp[i].byPos)
        {
            _vecPlayerHelp[i] = oPlayerHelp;
            return;
        }
    }
    _vecPlayerHelp.push_back(oPlayerHelp);
}

void CTripodSlots::InsertFighterHelp(SFighterHelpInfo& oFighterHelp)
{
    for (size_t i = 0; i < _vecFighterHelp.size(); ++ i)
    {
        if (oFighterHelp.byPos == _vecFighterHelp[i].byPos)
        {
            _vecFighterHelp[i] = oFighterHelp;
            return;
        }
    }
    _vecFighterHelp.push_back(oFighterHelp);
}

void CTripodSlots::GetAllTripods(STripodData& oTripodData)
{
    UpdateTripodSoul(Time::Now());
    TripodEnumerate4List en(oTripodData);
    enumerate(en);

    STripodHelp tripodHelpData(GetOwnerID(), _vecFighterHelp, _vecPlayerHelp);
    oTripodData.qwRoleID = GetOwnerID();
    oTripodData.stPlayer = _stPlayerAppear;
    oTripodData.tripodHelpData = tripodHelpData;
    for (auto & pLog: _deqLogPtr)
    {
        STripodLog sLogInfo;
        if (pLog)
        {
            pLog->GetAllInfo(sLogInfo);
            oTripodData.vecTripodLog.push_back(sLogInfo);
        }
    }
}

CTripodPtr CTripodSlots::ActiveTripod(CUserPtr pUser, UINT8 byTripodID)
{
    SStovePropCFGEx* pStovePropCfg = CTripodMgr::GetStovePropCfg(byTripodID);
    if (!pUser || !pStovePropCfg)
        return NULL;
    CTripodPtr pTripod = GetTripod(byTripodID);
    if (!pTripod)
    {
        pTripod.reset(new CTripod(GetOwnerID(), byTripodID));
        if (!Set(byTripodID-1, pTripod))
            return NULL;
        //激活九疑鼎火种
        for (size_t i = 0; i < pStovePropCfg->_vecFireID.size(); ++ i)
        {
            pUser->GetFireSlots().ActiveFire(pStovePropCfg->_vecFireID[i]);
        }
        UpdateTripodAttr(pUser);
    }
    return pTripod;
}

// 激活丹炉
ETripodType CTripodSlots::ActiveTripod(CUserPtr pUser, UINT8 byTripodID, shared_func<CTripodProtSvr::SActiveTripodAck> fnAck)
{
    if (!pUser || !byTripodID)
        return eTripodFailed;
    if(!pUser->GetOpLock().AddLock(eLock_Tripod))
        return eTripodFailed;

    CTripodPtr pTripod = GetTripod(byTripodID);
    if (pTripod)
        return eTripodFailed;

    SStovePropCFGEx* pStovePropCfg = CTripodMgr::GetStovePropCfg(byTripodID);
    if (!pStovePropCfg)
        return eTripodFailed;
    UINT16 wCondID = pStovePropCfg->_GetCondId;
    if (wCondID > 0)
    {
        UINT64 qwRoleID = pUser->GetUserID();
        UINT32 dwServerID = pUser->GetGameSvrID();
        if (!qwRoleID || !dwServerID)
            return eTripodFailed;
        g_Game2CenterCommS.SendSvr_ProcessCond(&dwServerID,1,qwRoleID,wCondID,NLogDataDefine::ItemTo_TripodActive,
                [this,fnAck,pUser,byTripodID](UINT8 byRet_, UINT8 byError) mutable
                {
                    if(!fnAck || !pUser || byRet_ || byError)
                    {
                        fnAck->eResult = eTripodCondIDErr;
                        TVecUINT64 vecUserID;
                        vecUserID.push_back(pUser->GetRoleID());
                        g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgStoveUnlockFailure);
                        fnAck(true);
                        TripodManager.Send_UpdateTripod(pUser);
                        return;
                    }
                    CTripodPtr pTripod = ActiveTripod(pUser, byTripodID);
                    if (!pTripod)
                    {
                        fnAck->eResult = eTripodFailed;
                        fnAck(true);
                        TripodManager.Send_UpdateTripod(pUser);
                        return;
                    }
                    pUser->GetOpLock().UnLock(eLock_Tripod);
                    pTripod->Update2DB();

                    fnAck->eResult = eTripodSucc;
                    fnAck(true);
                    TripodManager.Send_UpdateTripod(pUser);
                });
    }
    else
    {
        CTripodPtr pTripod = ActiveTripod(pUser, byTripodID);
        if (!pTripod)
            return eTripodFailed;
        pTripod->Update2DB();
    }
    return eTripodSucc;
}

ETripodType CTripodSlots::UpgradeTripod(CUserPtr pUser, UINT8 byTripodID, UINT8 byOneKey, shared_func<CTripodProtSvr::SUpgradeTripodAck> fnAck)
{
    if (!pUser || !byTripodID)
        return eTripodFailed;
    if(!pUser->GetOpLock().AddLock(eLock_Tripod))
        return eTripodFailed;

    CTripodPtr pTripod = GetTripod(byTripodID);
    if (!pTripod)
        return eTripodFailed;
    if (CTripodMgr::IsMaxLevel(byTripodID, pTripod->GetLevel(), 1))
        return eTripodFailed;
    UINT64 qwRoleID = pUser->GetUserID();
    UINT32 dwServerID = pUser->GetGameSvrID();
    if (!qwRoleID || !dwServerID)
        return eTripodFailed;

    g_Game2CenterCommS.SendSvr_UpgradeTripod(&dwServerID,1,qwRoleID,byTripodID,pTripod->GetLevel(),pTripod->GetExp(),byOneKey,
            [this,fnAck,pUser,pTripod](UINT8 byRet_,UINT8 byError,UINT8 byLevel, UINT32 dwExp) mutable
            {
                if(!fnAck || !pUser || !pTripod || byRet_ || byError)
                {
                    fnAck->eResult = eTripodItemErr;
                    fnAck(true);
                    TripodManager.Send_UpdateTripod(pUser);
                    TVecUINT64 vecUserID;
                    vecUserID.push_back(pUser->GetRoleID());
                    g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgStoveUpgradeMaterialLacking);
                    return;
                }
                pUser->GetOpLock().UnLock(eLock_Tripod);
                UpdateTripodSoul(Time::Now());
                if (pTripod->GetLevel() != byLevel)
                {
                    //pTripod->SettleCurrentSoul();  //XXX 必须在SetLevel之前
                    pTripod->SetLevel(byLevel);
                    UpdateTripodAttr(pUser);
                    ResetTripodTimerCheck(pTripod);
                }
                pTripod->SetExp(dwExp);
                pTripod->Update2DB();

                TVecINT32 vecParam;
                vecParam.push_back(pTripod->GetID());
                for (size_t iSlot = 0; iSlot < static_cast<size_t>(GetSlots()); ++ iSlot)
                {
                    CTripodPtr pTripod = Get(iSlot);
                    if (pTripod)
                        vecParam.push_back(pTripod->GetLevel());
                }
                pUser->OnEvent(eEventType_StoveUpgrade, vecParam);

                STripodInfo oTripodInfo;
                pTripod->ToProt(oTripodInfo);
                fnAck->vecTripods.push_back(oTripodInfo);
                fnAck->eResult = eTripodSucc;
                fnAck(true);
                TripodManager.Send_UpdateTripod(pUser);
            });

    return eTripodSucc;
}

ETripodType CTripodSlots::MakeFireTripod(CUserPtr pUser, UINT8 byTripodID, UINT16 wFireID, shared_func<CTripodProtSvr::SMakeFireTripodAck> fnAck)
{
    CTripodPtr pTripod = GetTripod(byTripodID);
    if (!pUser || !pTripod)
        return eTripodFailed;
    if(!pUser->GetOpLock().AddLock(eLock_Tripod))
        return eTripodFailed;

    TripodData& stoveData = pTripod->GetTripodData();
    if (stoveData._wFireID)
        return eTripodFailed;
    SStoveFireCFGEx* pStoveFireCfg = CTripodMgr::GetStoveFireCfg(wFireID);
    if (!pStoveFireCfg)
        return eTripodFailed;
    if (!pUser->GetFireSlots().HasRemainCnt(wFireID))
        return eTripodNoEnoughCnt;

    TVecUserItem vecUserItem;
    for (size_t i = 0; i < pStoveFireCfg->_vecItemCost.size(); ++ i)
    {
        SUserItem oItem(pStoveFireCfg->_vecItemCost[i].wItemID,pStoveFireCfg->_vecItemCost[i].wCount);
        vecUserItem.push_back(oItem);
    }

    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_UserSubItem(&dwServerID,1,pUser->GetUserID(),NLogDataDefine::ItemTo_TripodMakeFire,vecUserItem,
            [this,fnAck,pUser,pTripod,wFireID](UINT8 byRet_, UINT8 byError) mutable
            {
                if(!fnAck || !pUser || !pTripod || byRet_ || byError)
                {
                    LOG_CRI << "Sub item Error!!";
                    fnAck->eResult = eTripodItemErr;
                    fnAck(true);
                    TripodManager.Send_UpdateTripod(pUser);
                    TVecUINT64 vecUserID;
                    vecUserID.push_back(pUser->GetRoleID());
                    g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgStoveMaterialLacking);
                    return;
                }
                pUser->GetOpLock().UnLock(eLock_Tripod);
                TripodData& stoveData = pTripod->GetTripodData();
                stoveData._wFireID = wFireID;
                stoveData._dwStartTime = Time::Now();
                stoveData._byFireLvl = CTripodMgr::GetFireLevelRandom();
                SStoveFireLevelCFGEx* pFireLevelCfg = CTripodMgr::GetStoveFireLevelCfg(stoveData._byFireLvl);
                if (pFireLevelCfg)
                    stoveData._dwLine = CRandom::RandInt(pFireLevelCfg->_LowLine, pFireLevelCfg->_MaxLine);
                pTripod->SetConfigMaxSoul();
                pTripod->Update2DB();

                CFirePtr pFire = pUser->GetFireSlots().GetFire(wFireID);
                if (pFire)
                {
                    pFire->SubRemainCnt(1);
                    pUser->GetFireSlots().Update2DB(pFire, eOpUpdate);
                }

                STripodInfo oTripodInfo;
                pTripod->ToProt(oTripodInfo);
                fnAck->vecTripods.push_back(oTripodInfo);
                fnAck->eResult = eTripodSucc;
                UINT32 dwServerID = pUser->GetGameSvrID();
                g_Game2CenterCommS.SendSvr_ActionNotify(&dwServerID,1,pUser->GetUserID(),eProcessAction_MakeFire);

                TVecINT32 vecParam;
                vecParam.push_back(wFireID);
                vecParam.push_back(stoveData._byFireLvl);
                vecParam.push_back(pFire->GetRemainCnt());
                pUser->OnEvent(eEventType_StoveFireStarting,vecParam);
                fnAck(true);
                TripodManager.Send_UpdateTripod(pUser);
                ResetTripodTimerCheck(pTripod);
            });

    return eTripodSucc;
}

ETripodType CTripodSlots::ClearFireTripod(CUserPtr pUser, UINT8 byTripodID)
{
    CTripodPtr pTripod = GetTripod(byTripodID);
    if (!pTripod)
        return eTripodFailed;

    UpdateTripodSoul(Time::Now());
    //pTripod->SettleCurrentSoul();
    if (pTripod->CanGetAward())
        return eTripodYuanqiFull;

    pTripod->Reset();
    pTripod->Update2DB();
    ResetTripodTimerCheck(pTripod);
    return eTripodSucc;
}

ETripodType CTripodSlots::GetTripodAward(CUserPtr pUser, UINT8 byTripodID, shared_func<CTripodProtSvr::SGetTripodAwardAck> fnAck)
{
    CTripodPtr pTripod = GetTripod(byTripodID);
    if (!pTripod || !pUser)
        return eTripodFailed;
    if(!pUser->GetOpLock().AddLock(eLock_Tripod))
        return eTripodFailed;

    UpdateTripodSoul(Time::Now());
    //pTripod->SettleCurrentSoul();
    if (!pTripod->CanGetAward())
    {
        TVecUINT64 vecUserID;
        vecUserID.push_back(pUser->GetRoleID());
        g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgStoveEnergyNotFull);
        return eTripodYuanqiNotFull;
    }
    TripodData& stoveData = pTripod->GetTripodData();
    if (!stoveData._wFireID)
        return eTripodNotFire;
    SStoveFireCFGEx* pStoveFireCfg = CTripodMgr::GetStoveFireCfg(stoveData._wFireID);
    if (!pStoveFireCfg)
        return eTripodFailed;
    SStoveFireLevelCFGEx* pFireLevelCfg = CTripodMgr::GetStoveFireLevelCfg(stoveData._byFireLvl);
    if (!pFireLevelCfg)
        return eTripodFailed;
    if (pTripod->GetIsGeting())
        return eTripodFailed;

    FLOAT fFactor = FLOAT(stoveData._dwLine) / 10000;
    if (pStoveFireCfg->_LevelC > 0)
        fFactor += CExpMgr::GetStoveAwardRate(pUser->GetLevel());
    UINT32 dwCount = pStoveFireCfg->_oItemGenInfo.dwCount * (1.0f + fFactor);
    TVecUserItem vecUserItem;
    SUserItem oItem(pStoveFireCfg->_oItemGenInfo.wItemID, dwCount);
    vecUserItem.push_back(oItem);

    UINT32 dwStoveExp = pStoveFireCfg->_StoveExp;
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_UserAddItem(&dwServerID,1,pUser->GetUserID(),NLogDataDefine::ItemFrom_TripodAward,vecUserItem,
            [this,fnAck,pUser,pTripod,dwStoveExp](UINT8 byRet_, UINT8 byError) mutable
            {
                pTripod->SetIsGeting(false);
                if(!fnAck || !pUser || !pTripod || byRet_ || byError)
                {
                    LOG_CRI << "Add item Error!!";
                    fnAck->eResult = eTripodFailed;
                    fnAck(true);
                    TripodManager.Send_UpdateTripod(pUser);
                    return;
                }
                pUser->GetOpLock().UnLock(eLock_Tripod);
                CFirePtr pFire = pUser->GetFireSlots().GetFire(pTripod->GetTripodData()._wFireID);
                if (pFire)
                {
                    pFire->AddSucceedCnt(1);
                    pUser->GetFireSlots().Update2DB(pFire, eOpUpdate);

                    TVecINT32 vecParam;
                    vecParam.push_back(pFire->GetID());
                    vecParam.push_back(pFire->GetSucceedCnt());
                    vecParam.push_back(pFire->GetRemainCnt());
                    pUser->OnEvent(eEventType_StoveFireFinish, vecParam);
                }

                UpdateTripodSoul(Time::Now());
                UINT8 byOldLvl = pTripod->GetLevel();
                pTripod->AddExp(dwStoveExp);
                pTripod->Reset();
                pTripod->Update2DB();
                ResetTripodTimerCheck(pTripod);
                if (pTripod->GetLevel() != byOldLvl)
                {
                    UpdateTripodAttr(pUser);
                }

                STripodInfo oTripodInfo;
                pTripod->ToProt(oTripodInfo);
                fnAck->vecTripods.push_back(oTripodInfo);
                fnAck->eResult = eTripodSucc;
                fnAck(true);
                TripodManager.Send_UpdateTripod(pUser);
            });

    return eTripodSucc;
}

//加速九疑鼎炼丹(道具入鼎)
ETripodType CTripodSlots::SpeedTripod(CUserPtr pUser, UINT8 byTripodID, const NItemProt::TVecItemCount& vecItems, shared_func<CTripodProtSvr::SSpeedTripodAck> fnAck)
{
    CTripodPtr pTripod = GetTripod(byTripodID);
    if (!pUser || !pTripod)
        return eTripodFailed;
    if(!pUser->GetOpLock().AddLock(eLock_Tripod))
        return eTripodFailed;

    TripodData& stoveData = pTripod->GetTripodData();
    if (!stoveData._wFireID)
        return eTripodNotFire;

    UpdateTripodSoul(Time::Now());
    //pTripod->SettleCurrentSoul();
    if (pTripod->CanGetAward())
        return eTripodYuanqiFull;

    UINT32 dwMaxSoul  = pTripod->GetConfigMaxSoul();
    UINT32 dwCurSoul  = stoveData.GetSoul();
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_SpeedTripod(&dwServerID,1,pUser->GetUserID(),dwCurSoul,dwMaxSoul,vecItems,
            [this, fnAck, pTripod, pUser](UINT8 byRet_, UINT8 byError, UINT32 dwSoul) mutable
            {
                if(!fnAck || !pTripod || byRet_ || byError)
                {
                    LOG_CRI << "Sub item Error!!";
                    fnAck->eResult = eTripodItemErr;
                    fnAck(true);
                    TripodManager.Send_UpdateTripod(pUser);
                    TVecUINT64 vecUserID;
                    vecUserID.push_back(pUser->GetRoleID());
                    //g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgStoveXXX);
                    return;
                }
                pUser->GetOpLock().UnLock(eLock_Tripod);

                pTripod->AddSoul(dwSoul);
                STripodInfo oTripodInfo;
                pTripod->ToProt(oTripodInfo);
                fnAck->vecTripods.push_back(oTripodInfo);

                pTripod->Update2DB();
                fnAck->eResult = eTripodSucc;
                fnAck(true);
                TripodManager.Send_UpdateTripod(pUser);
                ResetTripodTimerCheck(pTripod);
            });

    return eTripodSucc;
}

//九疑鼎扇火
ETripodType CTripodSlots::AddTripodExtraSoul(CUserPtr pUser, UINT8 byTripodID, TVecTripodInfo& vecTripods)
{
    CTripodPtr pTripod = GetTripod(byTripodID);
    if (!pTripod)
        return eTripodFailed;
    if (!pTripod->HasFire())
        return eTripodNotFire;
    if (pUser->GetCenterVar().GetVar(NVarDefine::ePlayerVarTripodShanfeng) >= SParamConfig::byStoveBellowTimes)
    {
        TVecUINT64 vecUserID;
        vecUserID.push_back(pUser->GetRoleID());
        g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgStoveBellowTimesLacking);
        return eTripodShanfengFull;
    }
    if (!pTripod->CanShanfeng())
        return eTripodNotTime;

    UpdateTripodSoul(Time::Now());
    //pTripod->SettleCurrentSoul();
    if (pTripod->CanGetAward())
        return eTripodYuanqiFull;

    pTripod->AddSoul(SParamConfig::dwStoveBellowAddSoul);
    pTripod->SetShanfengTime(Time::Now());
    pTripod->Update2DB();
    pUser->GetCenterVar().AddVar(NVarDefine::ePlayerVarTripodShanfeng, 1);
    ResetTripodTimerCheck(pTripod);

    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_PushLoot(&dwServerID,1,pUser->GetUserID(),eOpTripodAward,NLogDataDefine::ItemFrom_TripodAward,SParamConfig::wStoveBellowReward);
    TVecUINT64 vecUserID;
    vecUserID.push_back(pUser->GetRoleID());
    g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgStoveBellowReward);

    STripodInfo oTripodInfo;
    pTripod->ToProt(oTripodInfo);
    vecTripods.push_back(oTripodInfo);

    // Event事件
    TVecINT32 vecParam;
    vecParam.push_back(1);
    pUser->OnEvent(eEventType_StoveBellow, vecParam);

    // Message弹框通知
    vecUserID.clear();
    vecUserID.push_back(_qwOwnerID);
    TVecString vecString;
    vecString.push_back(pUser->GetUserName());
    string strName;
    g_PHPProtS.GetNameByID(_qwOwnerID, strName);
    vecString.push_back(pTripod->GetName());
    g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgStoveOtherBellow, vecString);

    // 仙府动态日志
    TVecINT64 vecParam2;
    AddLog(eMsgStoveOtherBellow, vecParam2, vecString);
    return eTripodSucc;
}

ETripodType CTripodSlots::FighterHelpTripod(CUserPtr pUser, UINT16 wFighterID, UINT8 byPos, shared_func<CTripodProtSvr::SFighterHelpTripodAck> fnAck)
{
    if(!pUser || !pUser->GetOpLock().AddLock(eLock_Tripod))
        return eTripodFailed;

    if (!CanFighterHelp(pUser->GetRoleID(), wFighterID, byPos))
        return eTripodNotHelp;
    UINT64 qwRoleID = pUser->GetUserID();
    UINT32 dwServerID = pUser->GetGameSvrID();
    if (!qwRoleID || !dwServerID)
        return eTripodFailed;

    g_Game2CenterCommS.SendSvr_CheckHasFighter(&dwServerID,1,qwRoleID,wFighterID,[this,fnAck,pUser,wFighterID,byPos](UINT8 byRet_,UINT8 byError, UINT8 byColor) mutable
            {
                if(!pUser || byRet_ || byError)
                {
                    fnAck->eResult = eTripodNotHelp;
                    fnAck(true);
                    TripodManager.Send_UpdateTripod(pUser);
                    return;
                }
                pUser->GetOpLock().UnLock(eLock_Tripod);
                SFighterHelpInfo oFighterHelp(wFighterID, byPos, byColor, Time::Now());
                InsertFighterHelp(oFighterHelp);
                UpdateTripodHelp2DB();

                TVecINT32 vecParam;
                vecParam.push_back(1);
                pUser->OnEvent(eEventType_StoveFighterHelp, vecParam);

                fnAck->oFighterHelp = oFighterHelp;
                fnAck->eResult = eTripodSucc;
                fnAck(true);
                TripodManager.Send_UpdateTripod(pUser);
                for (size_t iSlot = 0; iSlot < static_cast<size_t>(GetSlots()); ++ iSlot)
                {
                    CTripodPtr pTripod = Get(iSlot);
                    if (!pTripod || !pTripod->HasFire())
                        continue;
                    ResetTripodTimerCheck(pTripod);
                }
            });
    return eTripodSucc;
}

ETripodType CTripodSlots::UserHelpTripod(CUserPtr pHelper, UINT8 byPos, function<void(ETripodType eResult, SPlayerHelpInfo oPlayerHelp)> func)
{
    if (!pHelper || pHelper->GetCenterVar().GetVar(NVarDefine::ePlayerVarTripodHelp) >= SParamConfig::byStoveHelpTimes)
    {
        TVecUINT64 vecUserID;
        vecUserID.push_back(pHelper->GetRoleID());
        g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgStoveHelpTimesLacking);
        return eTripodHelpTimesFull;
    }
    if(!pHelper->GetOpLock().AddLock(eLock_Tripod))
        return eTripodFailed;

    UINT64 qwHelpID = pHelper->GetUserID();
    if (!CanPlayerHelp(qwHelpID, byPos))
        return eTripodNotHelp;

    UINT32 dwServerID = 0;
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwHelpID);
    if(!pUser)
        dwServerID = CCenterConfig::Instance().GetSvrID();
    else
        dwServerID = pUser->GetGameSvrID();
    if (dwServerID)
    {
        // 获取外观信息
        g_Game2CenterRankS.SendSvr_GetFeature(&dwServerID, 1, qwHelpID, 
                [this, qwHelpID, byPos, pHelper, func, dwServerID](UINT8 byRet, UINT8 byError, const string& strName, UINT16 wLevel, const NBattleGS::SFeatureBasePtr& pFeature)
                {
                    if (pHelper)
                        pHelper->GetOpLock().UnLock(eLock_Tripod);
                    SPlayerHelpInfo oPlayerHelp;
                    if (pHelper && !byRet && !byError)
                    {
                        oPlayerHelp.qwRoleID = qwHelpID;
                        oPlayerHelp.dwStartTime = Time::Now();
                        oPlayerHelp.byPos = byPos;
                        oPlayerHelp.byLevel = pHelper->GetLevel();
                        oPlayerHelp.stPlayer.wLevel = wLevel;
                        oPlayerHelp.stPlayer.strName = strName;
                        oPlayerHelp.stPlayer.stAppear = *(dynamic_pointer_cast<NBattleGS::SPlayerFeature>(pFeature));
                        oPlayerHelp.vecPlatforms = CUserMgr::GetPlatformParam(qwHelpID);
                        InsertPlayerHelp(oPlayerHelp);
                        UpdateTripodHelp2DB();
                        for (size_t iSlot = 0; iSlot < static_cast<size_t>(GetSlots()); ++ iSlot)
                        {
                            CTripodPtr pTripod = Get(iSlot);
                            if (!pTripod || !pTripod->HasFire())
                                continue;
                            ResetTripodTimerCheck(pTripod);
                        }

                        TVecINT32 vecParam;
                        vecParam.push_back(1);
                        pHelper->OnEvent(eEventType_StovePlayerHelp, vecParam);
                        g_Game2CenterCommS.SendSvr_PushLoot(&dwServerID, 1, qwHelpID, eOpTripodAward,NLogDataDefine::ItemFrom_TripodAward, SParamConfig::wStoveHelpReward);
                        pHelper->GetCenterVar().AddVar(NVarDefine::ePlayerVarTripodHelp, 1);
                        TVecUINT64 vecUserID;
                        vecUserID.push_back(pHelper->GetRoleID());
                        g_GlobalChatProtS.SendClt_SystemMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgStoveHelpReward);
                        vecUserID.clear();
                        vecUserID.push_back(_qwOwnerID);
                        TVecString vecString;
                        vecString.push_back(pHelper->GetUserName());
                        g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(vecUserID.data(), vecUserID.size(), eMsgStoveOtherHelpBegin, vecString);
                        TVecINT64 vecParam2;
                        AddLog(eMsgStoveOtherHelpBegin, vecParam2, vecString);
                        func (eTripodSucc, oPlayerHelp);
                    }
                    else
                    {
                        func (eTripodFailed, oPlayerHelp);
                    }
                });
    }
    return eTripodFailed;
}

bool CTripodSlots::UpdateTripodHelp2DB()
{
    STripodHelp oTripodHelp;
    oTripodHelp.qwRoleID = GetOwnerID();
    oTripodHelp.vecFighterHelp = _vecFighterHelp;
    oTripodHelp.vecPlayerHelp = _vecPlayerHelp;
    size_t size = _vecFighterHelp.size() + _vecPlayerHelp.size();

    g_Center2DBCommC.Send_UpateTripodHelp(size > 0 ? eOpUpdate : eOpDel, oTripodHelp);
    return true;
}

void CTripodSlots::SyncAppear(function<void()> func)
{
    if (_bAppearInited)
        func();
    else
    {
        _byAppearLoadCount = _vecPlayerHelp.size();
        TVecUINT64 vecRoleID;
        for(auto& rInfo : _vecPlayerHelp)
        {
            vecRoleID.push_back(rInfo.qwRoleID);
        }
        if (vecRoleID.empty())
        {
            _bAppearInited = true;
            func();
        }
        else
        {
            for (auto qwID : vecRoleID)
            {
                CUserPtr pUser = CUserMgr::GetUserByUserID(qwID);
                UINT32 dwServerID = 0;
                if(!pUser)
                    dwServerID = CCenterConfig::Instance().GetSvrID();
                else
                    dwServerID = pUser->GetGameSvrID();
                if (dwServerID)
                {
                    g_Game2CenterRankS.SendSvr_GetFeature(&dwServerID, 1, qwID, 
                            [this, qwID, func](UINT8 byRet, UINT8 byError, const string& strName, UINT16 wLevel, const NBattleGS::SFeatureBasePtr& pFeature)
                            {
                                if (byRet || byError)
                                {
                                    --_byAppearLoadCount;
                                    func();
                                    return;
                                }
                                for (auto& rInfo : _vecPlayerHelp)
                                {
                                    if (rInfo.qwRoleID == qwID)
                                        rInfo.stPlayer.stAppear = *(dynamic_pointer_cast<NBattleGS::SPlayerFeature>(pFeature));

                                }
                                --_byAppearLoadCount;
                                if (!_byAppearLoadCount)
                                {
                                    _bAppearInited = true;
                                    func();
                                }
                            });
                }
                else 
                {
                    if (_byAppearLoadCount)
                        --_byAppearLoadCount;
                    if (!_byAppearLoadCount)
                    {
                        _bAppearInited = true;
                        func();
                    }
                }
            }
        }
    }
}

bool CTripodSlots::AddLog(ESystemMsgID eMsgID, const TVecINT64& rvecParam, const TVecString& rvecString, UINT32 dwTime /* = 0 */)
{
    return AddLog(static_cast<UINT16>(eMsgID), rvecParam, rvecString, dwTime);
}

bool CTripodSlots::AddLog(UINT16 wMsgID, const TVecINT64& rvecParam, const TVecString& rvecString, UINT32 dwTime /* = 0 */)
{
    CTripodLogPtr pLog;
    switch(wMsgID)
    {
        case eMsgStoveOtherBellow:
        case eMsgStoveOtherHelpBegin:
        case eMsgStoveOtherHelpEnd:
            {
                CTripodHelpLogPtr pHelpLog(new CTripodHelpLog(GetOwnerID()));
                if (pHelpLog)
                    pHelpLog->FormatParam(wMsgID, rvecParam, rvecString, dwTime);
                pLog = dynamic_pointer_cast<CTripodLog>(pHelpLog);
                break;
            }
            break;
    }
    return AddLog(pLog);
}

bool CTripodSlots::AddLog(CTripodLogPtr pLog, bool bInit /* = false */)
{
    if (!pLog)
        return false;
    _deqLogPtr.push_front(pLog);
    if (_deqLogPtr.size() > SParamConfig::byStoveHelpMessageNum)
    {
        auto it = _deqLogPtr.begin();
        advance(it, SParamConfig::byStoveHelpMessageNum);
        _deqLogPtr.erase(it, _deqLogPtr.end());
    }
    if (!bInit)
        CTripodLog::Update2DB(pLog);
    return true;
}

ETripodType CTripodSlots::ShotOffHelpTripod(UINT8 byPos, UINT8 byType)
{
    ETripodType eResult = eTripodFailed;
    UINT32 dwNow = Time::Now();
    UpdateTripodSoul(dwNow);
    switch (byType)
    {
        case 1: // 1玩家协助
            if (byPos > 2) // 最多三名玩家
            {
                eResult = eTripodFailed;
                break;
            }
            for (auto iter = _vecPlayerHelp.begin(); iter != _vecPlayerHelp.end(); ++ iter)
            {
                if (byPos != iter->byPos)
                    continue;
                _vecPlayerHelp.erase(iter);
                UpdateTripodHelp2DB();
                eResult = eTripodSucc;
                _mapKickUserMap[iter->qwRoleID] = Time::Now() + SParamConfig::wStoveHelperLeftCD;
                break;
            }
            break;
        case 0: // 0散仙协助 
            if (byPos > 1) // 最多两名玩家
            {
                eResult = eTripodFailed;
                break;
            }
            for (auto iter = _vecFighterHelp.begin(); iter != _vecFighterHelp.end(); ++ iter)
            {
                if (byPos != iter->byPos)
                    continue;
                _vecFighterHelp.erase(iter);
                UpdateTripodHelp2DB();
                eResult = eTripodSucc;
                break;
            }
            break;
    }
    for (size_t iSlot = 0; iSlot < static_cast<size_t>(GetSlots()); ++ iSlot)
    {
        CTripodPtr pTripod = Get(iSlot);
        if (!pTripod || !pTripod->HasFire())
            continue;
        ResetTripodTimerCheck(pTripod);
    }
    return eResult;
}

// 其他玩家协助加成，根据等级增加对应的元气值
FLOAT CTripodSlots::GetAllPlayerHelpSoul(UINT32 dwNow, UINT32 dwSettleTime, bool& bUpdate)
{
    FLOAT fSoul = 0;
    size_t iSize = 0;
    while (iSize < _vecPlayerHelp.size())
    {
        const SPlayerHelpInfo& oPlayerHelp = _vecPlayerHelp[iSize];
        bool bKick = false;
        UINT32 dwTime = GetCalcTime(dwNow, oPlayerHelp.dwStartTime, bKick);
        if (dwTime)
            fSoul += CExpMgr::GetStoveHelpRate(oPlayerHelp.byLevel) * dwTime;
        if (bKick) // 已经协助满8小时
        {
            _vecPlayerHelp.erase(_vecPlayerHelp.begin() + iSize);
            bUpdate = true;
        }
        else
            ++ iSize;
    }
    return fSoul;
}

// 散仙协助加成，根据品质增加对应的元气值
FLOAT CTripodSlots::GetAllFighterHelpSoul(UINT32 dwNow, UINT32 dwSettleTime, bool& bUpdate)
{
    FLOAT fSoul = 0;
    size_t iSize = 0;
    while (iSize < _vecFighterHelp.size())
    {
        const SFighterHelpInfo& oFighterHelp = _vecFighterHelp[iSize];
        bool bKick = false;
        UINT32 dwTime = GetCalcTime(dwNow, oFighterHelp.dwStartTime, bKick);
        if (dwTime)
        {
            switch (oFighterHelp.byColor)
            {
                case 2: //白
                    fSoul += FLOAT(SParamConfig::dwStoveFighterHelpCGreen) / 10000;
                    break;
                case 3: //绿
                    fSoul += FLOAT(SParamConfig::dwStoveFighterHelpCBlue) / 10000;
                    break;
                case 4: //蓝
                    fSoul += FLOAT(SParamConfig::dwStoveFighterHelpCPurple) / 10000;
                    break;
                case 5: //橙
                    fSoul += FLOAT(SParamConfig::dwStoveFighterHelpCOrange) / 10000;
                    break;
            }
        }
        if (bKick) // 已经协助满8小时
        {
            _vecFighterHelp.erase(_vecFighterHelp.begin() + iSize);
            bUpdate = true;
        }
        else
            ++ iSize;
    }
    return fSoul;
}

// 其他玩家协助加成，根据等级增加对应的元气值
UINT32 CTripodSlots::GetAllPlayerHelpRate(UINT32 dwNow, TVecFloat& vecRate, TVecUINT32& vecTime, bool& bUpdate)
{
    UINT32 dwCount = 0;
    size_t iSize = 0;
    while (iSize < _vecPlayerHelp.size())
    {
        const SPlayerHelpInfo& oPlayerHelp = _vecPlayerHelp[iSize];
        bool bKick = false;
        UINT32 dwTime = GetCalcTime(dwNow, oPlayerHelp.dwStartTime, bKick);
        if (dwTime)
        {
            vecRate.push_back(CExpMgr::GetStoveHelpRate(oPlayerHelp.byLevel));
            vecTime.push_back(dwTime);
            ++dwCount;
        }
        if (bKick) // 已经协助满8小时
        {
            KickPlayer(iSize);
            //_vecPlayerHelp.erase(_vecPlayerHelp.begin() + iSize);
            bUpdate = true;
        }
        else
            ++ iSize;
    }
    return dwCount;
}

// 散仙协助加成，根据品质增加对应的元气值
UINT32 CTripodSlots::GetAllFighterHelpRate(UINT32 dwNow, TVecFloat& vecRate, TVecUINT32& vecTime, bool& bUpdate)
{
    UINT32 dwCount = 0;
    size_t iSize = 0;
    while (iSize < _vecFighterHelp.size())
    {
        const SFighterHelpInfo& oFighterHelp = _vecFighterHelp[iSize];
        bool bKick = false;
        UINT32 dwTime = GetCalcTime(dwNow, oFighterHelp.dwStartTime, bKick);
        if (dwTime)
        {
            FLOAT fRate = 0.0f;
            switch (oFighterHelp.byColor)
            {
                case 2: //白
                    fRate = FLOAT(SParamConfig::dwStoveFighterHelpCGreen) / 10000;
                    break;
                case 3: //绿
                    fRate = FLOAT(SParamConfig::dwStoveFighterHelpCBlue) / 10000;
                    break;
                case 4: //蓝
                    fRate = FLOAT(SParamConfig::dwStoveFighterHelpCPurple) / 10000;
                    break;
                case 5: //橙
                    fRate = FLOAT(SParamConfig::dwStoveFighterHelpCOrange) / 10000;
                    break;
            }
            vecRate.push_back(fRate);
            vecTime.push_back(dwTime);
            ++ dwCount;
        }
        if (bKick) // 已经协助满8小时
        {
            _vecFighterHelp.erase(_vecFighterHelp.begin() + iSize);
            bUpdate = true;
        }
        else
            ++ iSize;
    }
    return dwCount;
}

UINT32 CTripodSlots::GetCalcTime(UINT32 dwNow, UINT32 dwStartTime, bool& bKick) const
{
    UINT32 dwTime = 0;
    if (dwNow > _dwSettleTime)
    {
        UINT32 dwEndTime = dwStartTime + SParamConfig::dwStoveHelpLastTimes;
        if (dwEndTime < dwNow) // 已经协助满8小时，需要自动踢掉
        {
            bKick = true;
            if (dwEndTime > _dwSettleTime)
                dwTime = dwEndTime - _dwSettleTime;
        }
        else if (_dwSettleTime > dwStartTime)
            dwTime = dwNow - _dwSettleTime;
        else if (dwNow > dwStartTime)
            dwTime = dwNow - dwStartTime;
    }
    dwTime = dwTime > 3600 ? 3600 : dwTime;
    return dwTime;
}

bool CTripodSlots::UpdateTripodSoul(time_t tNow)
{
    TVecFloat vecRate;
    TVecUINT32 vecTime;
    UINT32 dwTime = GetAllHelpRate(tNow, vecRate, vecTime);
    bool bRet =  AddSoulToAllTripod(dwTime, vecRate, vecTime);
    _dwSettleTime = tNow;
    return bRet;
}

bool CTripodSlots::KickPlayer(UINT8 byIndex)
{
    if (_vecPlayerHelp.size() < static_cast<size_t>(byIndex + 1))
        return false;
    SPlayerHelpInfo& rInfo = _vecPlayerHelp[byIndex];
    UINT32 dwTime = Time::Now();
    if ( rInfo.dwStartTime + SParamConfig::dwStoveHelpLastTimes < dwTime)
        dwTime = rInfo.dwStartTime + SParamConfig::dwStoveHelpLastTimes;
    TVecINT64 vecParam;
    TVecString vecString;
    vecString.push_back(rInfo.stPlayer.strName);
    AddLog(eMsgStoveOtherHelpEnd, vecParam, vecString, dwTime);
    _vecPlayerHelp.erase(_vecPlayerHelp.begin() + byIndex);
    return true;
}
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

