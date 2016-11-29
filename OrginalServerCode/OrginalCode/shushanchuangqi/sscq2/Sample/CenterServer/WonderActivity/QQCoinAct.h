
#ifndef QQCOINMGR_H_
#define QQCOINMGR_H_

#include "Singleton.h"
#include "WonderActivity.h"
#include "UserMgr.h"

class CQQCoinAct  : public CWonderActivity
{
public:
    CQQCoinAct(UINT16 wType); 
    virtual ~CQQCoinAct() { } 
    void    OnRetain();
    void    OnBegin();
    void    OpenIcon(bool bNotify);
public:
    EWActResult OnExChange(CUser &rUser,UINT8 byType);
    bool OnSyncInfo(CUser &rUser);
    void ResetPoolValue(UINT32 dwValue);
    void ResetCurValue(UINT32 dwValue);
    void OnSuc(CUser& rUser,UINT32 dwNeed,UINT8 byLevel);
    void TimerCheck();
    void SpecialProcess() override;
    bool IsRun(UINT32& dwTime);
    bool IsRetain();
    void SendUDPLog(UINT64 qwRoleID,UINT32 dwCount,UINT32 dwValue);
private:
    void InitParam();
private:
    UINT32 _dwInstTime;
    UINT8  _byQQLv;
    UINT8  _byGoldLv;
    float  _fRate;
    UINT16 _wLv2Coupon;
    UINT16 _wCoupon2QQ;
    UINT16 _wCoupon2Gold;
    bool   _bStart;
    UINT8  _byInterval;
    UINT8  _byMinLv;
};

#endif // VIPMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

