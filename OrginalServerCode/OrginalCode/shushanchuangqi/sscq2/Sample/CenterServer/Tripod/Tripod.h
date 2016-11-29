#ifndef TRIPOD_H_
#define TRIPOD_H_

#include "TripodProt.h"

using namespace NTripodProt;

struct TripodData
{
    TripodData()
    {
        Reset();
    }

    void Reset()
    {
        memset(this, 0, sizeof(*this));
    }
    bool IsRightStatus()
    {
        if (!_wFireID)
            return false;
        UINT32 dwCurtime = time(NULL);
        if (_dwStartTime == 0 || _dwStartTime > dwCurtime)
            return false;
        return true;
    }
    UINT32 GetSoul()
    {
        return _dwCurSoul;
    }
    void SetMaxSoul(UINT32 dwSoul) { _dwMaxSoul = dwSoul; }

    UINT16 _wFireID;
    UINT32 _dwStartTime;
    UINT32 _dwShanfengTime;
    UINT32 _dwCurSoul;
    UINT32 _dwMaxSoul;
    UINT8 _byFireLvl;
    UINT32 _dwLine;
};

class CTripod: public CPoolObj<CTripod>
{
public:
    CTripod(UINT64 qwRoleID, UINT8 byTripodID);
    ~CTripod();

    void Reset()
    {
        _stTD.Reset();
    }
    void SetOwnerID(UINT64 qwRoleID) { _qwOwnerID = qwRoleID; }
    UINT64 GetOwnerID() const { return _qwOwnerID; }
    UINT8 GetID() const { return _byTripodID; }
    UINT8 GetLevel() const { return _byLevel; }
    UINT32 GetExp() const { return _dwExp; }
    void SetLevel(UINT8 byLvl) { _byLevel = byLvl; }
    void SetExp(UINT32 dwExp) { _dwExp = dwExp; }
    void SetIsGeting(bool bIs) { _bIsGeting = bIs; }
    bool GetIsGeting() { return _bIsGeting; }
    TripodData& GetTripodData() { return _stTD; }
    void SetShanfengTime(UINT32 dwTime) { _stTD._dwShanfengTime = dwTime; }
    UINT32 GetShanfengTime() { return _stTD._dwShanfengTime; }
    void SetStartTime(UINT32 dwTime) { _stTD._dwStartTime = dwTime; }
    UINT32 GetStartTime() { return _stTD._dwStartTime; }
    const string& GetName() const;
    void AddSoul(UINT32 dwSoul);
    void AddSoul(UINT32 dwTime, const TVecFloat& vecRate, const TVecUINT32& vecTime);
    void SetSoul(UINT32 dwSoul);
    UINT32 GetSoul() { return _stTD._dwCurSoul; }
    void SetConfigMaxSoul();
    UINT32 GetConfigMaxSoul();
    void AddExp(UINT32 dwExp);
    FLOAT GetTripodRate();
    bool SettleCurrentSoul();

    void Update2DB();
    bool CanGetAward();
    bool CanShanfeng();
    bool HasFire();
    void ToProt(STripodInfo& oTripodInfo);
private:
    UINT64 _qwOwnerID;
    UINT8 _byTripodID;
    UINT8 _byLevel;
    UINT32 _dwExp;  //当前等级下多余的经验
    bool _bIsGeting;  //是否正在领取炼丹果实
    TripodData _stTD;
};

#endif // TRIPOD_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

