#ifndef DAYACTIVITY_H__
#define DAYACTIVITY_H__
#include "stdafx.h"
//#include "Player.h"
#include "DayActProt.h"
#include "DayActCFG.h"

using namespace NDayActProt;

struct STimerInfo
{
    UINT8 byHour;
    UINT8 byMinute;
    STimerInfo():
        byHour(0), byMinute(0)
    { }
};


struct SDayActEx:public SDayActCFG
{
    STimerInfo oAlarmTime;
    STimerInfo oReadyTime;
    STimerInfo oBeginTime;
    STimerInfo oEndTime;
    void CopyFrom(SDayActCFG& rDayActCFG)
    {
        *((SDayActCFG*)this) = rDayActCFG;
    }
    
};

typedef shared_ptr<SDayActEx> SDayActExPtr;

struct SActEvent
{
    UINT32 dwEventID;
    UINT32 dwNextEventTime; //事件下次触发时间
    UINT32 dwCount;         //执行次数
    UINT32 dwPeriodTime;    //执行周期
    UINT32 dwParam;         //参数1
    string strParam;        //参数2
    SActEvent()
    {
        dwEventID = 0;
        dwNextEventTime = 0;
        dwCount = 1;
        dwPeriodTime = 0;
        dwParam = 0;
        strParam = "";
    }
};

typedef std::map<UINT32,SActEvent> TMapActEvent;

class CDayActivity
{
    public:
        CDayActivity(NDayActProt::EActType eType);
        virtual ~CDayActivity(){};

        //void Init();
        UINT32 GetActID() const{ return _dwActID; };
        void SetActID(UINT32 dwActID) {_dwActID=dwActID; }

        NDayActProt::EActType GetActType() const { return _eType; }

        void SetStatus(EDayActivityStatus eStatus);
        UINT32 GetStatus() const { return _dwState; }

        UINT32 GetParam() const;
        
        virtual bool GMOpen(){return false;};        // GM指令直接开启活动

        virtual bool OnAlarm();                     // 程序开始准备
        virtual void OnReady();                     // 开始通知
        virtual void OnBegin();                     // 正式开始
        virtual void OnEnd();                       // 活动结束
        
        virtual void OnReBegin(){};                 // 服务器重启,处于活动期间的处理

        virtual void UpdateState(time_t tNow);      // 更新状态
        
        virtual void ResetState();                  // 重置原始状态
        virtual void OnEvent(SActEvent& oSActEvent) = 0;    // 注册事件触发

        //void SetCFG(SDayActExPtr pDayActEx);
        //const SDayActEx* GetCFG();
        SDayActExPtr GetCFG() const;
        
        //注册单次触发事件
        void AddEvent(UINT32 dwEventID,UINT32 dwNextEventTime,UINT32 dwParam=0,string strParam="");

        //注册周期触发事件
        void AddPeriodEvent(UINT32 dwEventID,UINT32 dwNextEventTime,UINT32 dwCount,UINT32 dwPeriodTime,UINT32 dwParam=0,string strParam="");

        void UpdateEvent(time_t tNow);
        
        // 0表示清除全部事件
        void ClearEvent(UINT32 dwEventID = 0);

        //UINT32 GetDayTimePoint(const STimerInfo& oTimerInfo);
    protected:
        NDayActProt::EActType _eType;
        UINT32   _dwActID;
        UINT32   _dwState;
        UINT32   _dwAlarmTime;
        UINT32   _dwReadyTime;
        UINT32   _dwBeginTime;
        UINT32   _dwEndTime;
        UINT32   _dwAlarmTimeSpan;
        UINT32   _dwReadyTimeSpan;
        UINT32   _dwProcessTimeSpan;

        //参数
        UINT32 _dwParam;

        TMapActEvent _mapActEventData;
};

typedef shared_ptr<CDayActivity> CDayActivityPtr;

//活动开启动作操作
class CDayActEvent
{
 public:
    CDayActEvent(UINT32 dwActID,UINT32 dwActType):
        _dwActID(dwActID), _dwActType(dwActType)
    {}

    virtual ~CDayActEvent(){};
    void OnAlarm();
    bool IsOpenDay();
    bool IsAlarmTime(time_t tNow);
    void CheckStatus();
    void GMOpen();
    SDayActExPtr GetCFG();
    UINT32 GetActID(){ return _dwActID; }

 public:
    UINT32 _dwActID;
    UINT32 _dwActType;
};
typedef shared_ptr<CDayActEvent> CDayActEventPtr;

#endif
 
