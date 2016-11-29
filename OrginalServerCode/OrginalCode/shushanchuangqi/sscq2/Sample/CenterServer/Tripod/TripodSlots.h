
#ifndef TRIPODSLOTS_H_
#define TRIPODSLOTS_H_

#include "stdafx.h"
#include "VecSlots.h"
#include "TripodProt.h"
#include "Tripod.h"
#include "ArenaGS.h"
#include "TripodLog.h"
#include "SysMsgDefine.h"

using namespace NArenaGS;
using namespace NTripodProt;
using namespace NProtoCommon;

class CUser;

class CTripodSlots: public CVecSlots<int, CTripodPtr>, public CPoolObj<CTripodSlots>
{
public:
    CTripodSlots(UINT64 qwRoleID);
    ~CTripodSlots() {}

    CTripodPtr GetTripod(UINT8 byTripodID, int* pIdx = NULL) const
    {
        VecSlotsEnumerateByID<UINT8, int, CTripodPtr> en(byTripodID);
        enumerate(en);
        if (en._sSlot == INVALID_SLOT)
            return NULL;
        if (pIdx)
            *pIdx = en._sSlot;
        return en._pObj;
    }
    SArenaFighter& GetUserAppear() { return _stPlayerAppear; }
    UINT64 GetOwnerID() const { return _qwOwnerID; }
    bool CanPlayerHelp(UINT64 qwRoleID, UINT8 byPos);
    bool CanFighterHelp(UINT64 qwRoleID, UINT16 wFighterID, UINT8 byPos);
    bool CanPlayerOrFighterHelp();
    bool CanPlayerHelp();
    void InsertPlayerHelp(SPlayerHelpInfo& oPlayerHelp);
    void InsertFighterHelp(SFighterHelpInfo& oFighterHelp);

    bool TimerCheck(time_t tNow);
    void ResetTripodTimerCheck(CTripodPtr pTripod);
    bool LoadTripodFromDB(const STripodData& oTripodData);
    bool LoadTripodHelpFromDB(const STripodHelp& oTripodHelp);
    bool LoadTripodLogFromDB(const STripodLog& oTripodLog);
    bool SettleTripodFireSoul();
    void UpdateTripodAttr(CUserPtr pUser);
    UINT32 GetAllHelpSoul(UINT32 dwNow, UINT32 dwSettleTime);
    bool AddSoulToAllTripod(UINT32 dwSoul);
    bool AddSoulToAllTripod(UINT32 dwTime, const TVecFloat& vecRate, const TVecUINT32& vecTime);
    void GetAllTripods(STripodData& oTripodDatas);
    CTripodPtr ActiveTripod(CUserPtr pUser, UINT8 byTripodID);
    ETripodType ActiveTripod(CUserPtr pUser, UINT8 byTripodID, shared_func<CTripodProtSvr::SActiveTripodAck> fnAck);
    ETripodType UpgradeTripod(CUserPtr pUser, UINT8 byTripodID, UINT8 byOneKey, shared_func<CTripodProtSvr::SUpgradeTripodAck> fnAck);
    ETripodType MakeFireTripod(CUserPtr pUser, UINT8 byTripodID, UINT16 wFireID, shared_func<CTripodProtSvr::SMakeFireTripodAck> fnAck);
    ETripodType ClearFireTripod(CUserPtr pUser, UINT8 byTripodID);
    ETripodType GetTripodAward(CUserPtr pUser, UINT8 byTripodID, shared_func<CTripodProtSvr::SGetTripodAwardAck> fnAck);
    ETripodType SpeedTripod(CUserPtr pUser, UINT8 byTripodID, const NItemProt::TVecItemCount& vecItems, shared_func<CTripodProtSvr::SSpeedTripodAck> fnAck);
    ETripodType AddTripodExtraSoul(CUserPtr pUser, UINT8 byTripodID, TVecTripodInfo& vecTripods);
    ETripodType FighterHelpTripod(CUserPtr pUser, UINT16 wFighterID, UINT8 byPos, shared_func<CTripodProtSvr::SFighterHelpTripodAck> fnAck);
    ETripodType UserHelpTripod(CUserPtr pHelper, UINT8 byPos, function<void(ETripodType eResult, SPlayerHelpInfo oPlayerHelp)> func);
    ETripodType ShotOffHelpTripod(UINT8 byPos, UINT8 byType);

    bool UpdateTripodHelp2DB();

    void SyncAppear(function<void()> func);

    bool AddLog(ESystemMsgID eMsgID, const TVecINT64& rvecParam, const TVecString& rvecString, UINT32 dwTime = 0);
    bool AddLog(UINT16 wMsgID, const TVecINT64& rvecParam, const TVecString& rvecString, UINT32 dwTime = 0);
    bool AddLog(CTripodLogPtr pLog, bool bInit = false);

private:
    UINT32 GetAllHelpRate(UINT32 dwNow, TVecFloat& vecRate, TVecUINT32& vecTime);

    FLOAT GetAllPlayerHelpSoul(UINT32 dwNow, UINT32 dwSettleTime, bool& bUpdate);
    FLOAT GetAllFighterHelpSoul(UINT32 dwNow, UINT32 dwSettleTime, bool& bUpdate);
    UINT32 GetAllPlayerHelpRate(UINT32 dwNow, TVecFloat& vecRate, TVecUINT32& vecTime, bool& bUpdate);
    UINT32 GetAllFighterHelpRate(UINT32 dwNow, TVecFloat& vecRate, TVecUINT32& vecTime, bool& bUpdate);
    UINT32 GetCalcTime(UINT32 dwNow, UINT32 dwStartTime, bool& bKick) const;

    bool UpdateTripodSoul(time_t tNow);

    bool KickPlayer(UINT8 byIndex);

private:
    UINT64 _qwOwnerID;
    SArenaFighter _stPlayerAppear;
    TVecFighterHelpInfo _vecFighterHelp;
    TVecPlayerHelpInfo _vecPlayerHelp;
    UINT32 _dwSettleTime; // 上次处理时间
    bool   _bAppearInited; // 是否更新协助者外观信息（因为不是从数据库加载，所以需要的话还是一个个从GameServer拉新的把）
    UINT8  _byAppearLoadCount; // 加载计数器
    map<UINT64, UINT32> _mapKickUserMap;
    TDequeTripodLogPtr _deqLogPtr;
};

#endif // TRIPODSLOTS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

