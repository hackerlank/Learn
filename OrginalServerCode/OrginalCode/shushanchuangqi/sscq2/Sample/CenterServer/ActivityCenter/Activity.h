#ifndef ACTIVITY_H__ 
#define ACTIVITY_H__
#include "stdafx.h"
#include "ProtoCommon.h"
using namespace NProtoCommon;
namespace NActivity
{
struct SKey
{
    UINT32 dwActID;
    UINT8 byIndex; 
    SKey(UINT32 ActID,UINT8 Index)
    {
        dwActID = ActID; 
        byIndex = Index;
    }
    bool operator < (const SKey& oKey) const
    {
        if(dwActID != oKey.dwActID)
            return dwActID < oKey.dwActID;
        return byIndex < oKey.byIndex;
    }
};

enum EState
{
   eNone,
   eSync,
   eAlarm,
   eReady,
   eBegin,
   eEnd,
   eMax
};
enum EServerType
{
    eServerNone,
    eGameServer,
    eCenerServer,
    eServerMax
};

class CActivity
{
    public:
        CActivity(UINT32 dwActID,UINT8 byIndex);
        virtual ~CActivity(){};
        
        void OnAlarm();
        void OnReady();
        void OnBegin();
        void OnEnd();
        void OnSync();
        void OnReBegin();
        void UpdateState();
        bool IsRun();
        void Update2DB(EDataChange eType);
    public:
        UINT32 GetID() { return _dwActID; }
        UINT32 GetActID() { return _dwActID; }
        UINT32 GetBeginTime() { return _dwBegin; }
        UINT32 GetEndTime() { return _dwEnd; }
        string GetName() { return _strName; }
        EState GetState() { return _eState; }
        UINT8  GetIndex() { return _byIndex; }
        
        void   SetBeginTime(UINT32 dwTmp) { _dwBegin = dwTmp; }
        void   SetEndTime(UINT32 dwTmp) { _dwEnd = dwTmp; }
        void   SetName(string strTmp) { _strName = strTmp; }
        void   SetIndex(UINT8 byTmp) { _byIndex = byTmp; }
        void   SetState(EState eTmp) { _eState = eTmp; }
        void   SetSyncTime(UINT32 dwTmp) { _dwSync = dwTmp; }
        void   SetAlarmTime(UINT32 dwTmp) { _dwAlarm = dwTmp; }
        void   SetReadyTime(UINT32 dwTmp) { _dwReady = dwTmp; }
        void   SetIsSync(bool bTmp) { _bSync = bTmp; }
        
        void   ModifyAlarm(UINT32 dwTmp);// 修改活动的公告时间
        void   ModifyLonger(UINT32 dwTmp);//修改活动的持续时间
    private:
        UINT32 _dwActID;
        UINT8  _byIndex;
        UINT32 _dwAlarm;
        UINT32 _dwReady;
        UINT32 _dwBegin;
        UINT32 _dwEnd;
        EState _eState;
        string _strName;
        bool   _bSync;//是否需要同步到GameServer
        bool   _dwSync; //什么时间同步(默认活动公告前2分钟)
};

typedef shared_ptr<CActivity> ActivityPtr;
typedef std::map<SKey,ActivityPtr> TMapID2Activity;
} //namespace end;
#endif
 
