
#ifndef GODCHEST_H_
#define GODCHEST_H_

#include "Singleton.h"
#include "MapMgr.h"
#include "DayActivity.h"
#include "MiscProtS.h"
#include "ProtoCommon.h"
#include "PHPProt.h"
using namespace NMiscProt;
enum EChestType
{
    eChestType_None,
    eChestType_Big = 3001,
    eChestType_Mid = 3002,
    eChestType_Small = 3003
};
struct SChestInfo
{
    UINT16 wIndex;
    EChestType eType;
    float fX;
    float fY;
    SChestInfo()
    {
        memset(this,0,sizeof *this);
    }
};
typedef vector<SChestInfo> TVecChestInfo;

enum EChestEventType
{
    eEventType_None,
    eEventType_PreNotice,
    eEventType_PreCountDown,
    eEventType_Notice,
    eEventType_CountDown,
    eEventType_Reflush,
    eEventType_ClearChest,
    eEventType_ChangeMap,
    eEventType_Max
};

class CGodChest : public CDayActivity,public CPoolObj<CGodChest>
{
public:
    CGodChest();
    virtual ~CGodChest() {}
    
    void OnEnter(CPlayer &rPlayer);
    void GetRount(CPlayer &rPlayer);

    bool RandChest(SMapInfoPtr pMapInfo,TVecChestInfo& vecInfo);
    bool GetPoint(SMapInfoPtr pMapInfo,UINT32 dwID,float& rX,float &rY);
    void Reflush();
    void SendCountDown();
    void SendNotice();
    void ClearChest();
    bool InitEvent();
    void SetTime(const NProtoCommon::SActivityTime& sActTime);
    void OnSync(UINT32);
    void ModifyParam(const NPHPProt::SChestInfo& sInfo);
public:
    virtual bool GMOpen();
    virtual bool OnAlarm();
    virtual void OnReady();
    virtual void OnBegin();
    virtual void OnReBegin();
    virtual void OnEnd();
    virtual void OnEvent(SActEventData&);

    virtual void UpdateState(time_t tNow);
    virtual void ResetState();
    void CheckChest(CPlayer &rPlayer);

    bool SetBig(UINT8 byTmp); 
    bool SetMid(UINT8 byTmp) ;
    bool SetSmall(UINT8 byTmp) ;
    bool SetInterval(UINT8 byTmp);
    bool SetLonger(UINT8 byTmp);
    bool SetMap(UINT16 wMapID);
    bool IsRun();
private:
    void InitParam();
private:
    UINT16 _wMapID;
    UINT8  _byBig;
    UINT8  _byMid;
    UINT8  _bySmall;
    UINT8  _byInterval; //刷新间隔(秒
    UINT8  _byLonger; //持续时间 (分钟
    UINT8  _byRount;
    UINT8  _byRemain;
    UINT8  _byCountDown;
    UINT8  _byNotice;
};

extern CGodChest g_GodChest;
#endif // VIPMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

