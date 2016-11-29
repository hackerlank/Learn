
#ifndef ACTIVITYMGR_H_
#define ACTIVITYMGR_H_

#include "Singleton.h"
#include "Activity.h"
#include "ProtoCommon.h"
#include "ActivityCenterCFG.h"
using namespace NActivity;
using namespace NProtoCommon;
enum EActivityProcess
{
    eProcessNone,
    eProcessDBInited,
    eProcessConfigInited,
    eProcessInited
};

class CActivityMgr
{
public:
    CActivityMgr()
        : _bInit(true)
        , _byProcess(0)
    { }
    virtual ~CActivityMgr() { }
    bool Init();
    bool LoadConfig();
    void TimerCheck();
    void LoadFromDB();
    void Load(const TVecActivityOpt& vecInfo);
    ActivityPtr GetAct(UINT32 dwActID,UINT8 byIndex);
    void  DelAct(UINT32 dwActID,UINT8 byIndex);
    bool SetTime(UINT32 dwActID,UINT8 byIndex,UINT32 dwAlarm,UINT32 dwLonger,bool bSync = false , UINT32 dwSync=120);
    void SetTime(UINT32 dwActID,UINT32 dwBegin,UINT32 dwEnd);
    //bool ModifyChestParam(const NProtoCommon::SChestInfo& sChestOpt,UINT32 dwActID,UINT8 byIndex);

private:
    bool InitActivity();
    void DelActByKey(NActivity::SKey oKey);
    SActivityOpt* GetActByKey(NActivity::SKey oKey);
private:
    bool _bInit;
    UINT8 _byProcess;
    TMapID2Activity _mapID2Activity;
    map<NActivity::SKey,SActivityOpt> _mapTmp; //缓存数据库数据
};

extern CActivityMgr g_ActivityMgr;

#endif // ActivityMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

