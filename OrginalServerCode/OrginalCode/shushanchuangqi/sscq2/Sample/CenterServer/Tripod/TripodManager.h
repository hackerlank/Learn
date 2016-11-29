
#ifndef TRIPODMANAGER_H_
#define TRIPODMANAGER_H_


#include "stdafx.h"
#include "TripodSlots.h"
#include "TripodProt.h"

using namespace NTripodProt;

class CUser;
class CTripodSlots;

struct STripodTimerKey
{
    STripodTimerKey(UINT64 qwRoleID, UINT8 byID) : qwUserID(qwRoleID), byTripodID(byID) {}

    UINT64 qwUserID;
    UINT8  byTripodID;

    bool operator < (const STripodTimerKey& sk) const
    {
        if (qwUserID !=  sk.qwUserID)
            return qwUserID < sk.qwUserID;
        return byTripodID < sk.byTripodID;
    }
};

class CTripodManager : public Singleton<CTripodManager>
{
public:
    CTripodManager()  {}
    ~CTripodManager() {}


    void TimerCheck(time_t tNow);
    void OnUserLogin(CUserPtr pUser);
    bool SettleTripodFireSoul(UINT64 qwRoleID);
    void Send_UpdateTripod(CUserPtr pUser);
    CTripodSlots& GetTripodSlots(UINT64 qwRoleID);
    bool LoadTripodFromDB();
    bool LoadTripodHelpFromDB();
    bool LoadTripodLogFromDB();
    void RecieveDBData(UINT32 dwCurPage, UINT32 dwTotalPage, const NTripodProt::TVecTripodData& vecSendData);
    void RecieveDBData(UINT32 dwCurPage, UINT32 dwTotalPage, const NTripodProt::TVecTripodHelp& vecSendData);
    void RecieveDBData(UINT32 dwCurPage, UINT32 dwTotalPage, const NTripodProt::TVecTripodLog& vecSendData);
    void GetAllTripods(CUserPtr pUser, STripodData& oTripodData);
    ETripodType ActiveTripod(CUserPtr pUser, UINT8 byTripodID, shared_func<CTripodProtSvr::SActiveTripodAck> fnAck);
    ETripodType UpgradeTripod(CUserPtr pUser, UINT8 byTripodID, UINT8 byOneKey, shared_func<CTripodProtSvr::SUpgradeTripodAck> fnAck);
    ETripodType MakeFireTripod(CUserPtr pUser, UINT8 byTripodID, UINT16 wFireID, shared_func<CTripodProtSvr::SMakeFireTripodAck> fnAck);
    ETripodType ClearFireTripod(CUserPtr pUser, UINT8 byTripodID);
    ETripodType GetTripodAward(CUserPtr pUser, UINT8 byTripodID, shared_func<CTripodProtSvr::SGetTripodAwardAck> fnAck);
    ETripodType SpeedTripod(CUserPtr pUser, UINT8 byTripodID, const NItemProt::TVecItemCount& vecItems, shared_func<CTripodProtSvr::SSpeedTripodAck> fnAck);
    ETripodType AddTripodExtraSoul(CUserPtr pUser, UINT64 qwRoleID, UINT8 byTripodID, TVecTripodInfo& vecTripods);
    ETripodType FighterHelpTripod(CUserPtr pUser, UINT16 wFighterID, UINT8 byPos, shared_func<CTripodProtSvr::SFighterHelpTripodAck> fnAck);
    //ETripodType UserHelpTripod(CUserPtr pUser, UINT64 qwRoleID, UINT8 byPos, SPlayerHelpInfo& oPlayerHelp);
    ETripodType UserHelpTripod(CUserPtr pUser, UINT64 qwRoleID, UINT8 byPos, function<void(ETripodType eResult, SPlayerHelpInfo oPlayerHelp)> func);
    void GetTripodStatus(CUserPtr pUser, const TVecUINT64& vecRoleID, TVecTripodStatus& vecStatus);
    ETripodType ShotOffHelpTripod(CUserPtr pUser, UINT8 byPos, UINT8 byType);

    void SyncAppear(UINT64 qwRoleID, function<void()> func);
    void ResetTripodTimerCheck(UINT64 qwRoleID, UINT8 byTripodID, UINT32 dwEndTime, bool bIsDel);

private:
    unordered_map<UINT64, CTripodSlots> _mapAllTripod;
    multimap<UINT32, STripodTimerKey> _mapTimerTripodOpposite;  //九疑鼎定时器反向记录
    map<STripodTimerKey, UINT32>      _mapTimerTripodForward;   //九疑鼎定时器正向记录
    static bool _bLoadFromDB;
    static bool _bLoadHelpFromDB;
    static bool _bLoadLogFromDB;
    static UINT32 _dwSettleTime; // 上次处理时间
};

#define TripodManager CTripodManager::Instance()

#endif // TRIPODMANAGER_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

