#ifndef _EVENTMGR_H
#define _EVENTMGR_H
#include <map>
#include <memory>
#include "EventCenterCFG.h"
#include "DataUploadCFG.h"
#include "RoleInfoDefine.h"
#include "CommonDef.h"
#include "ProtoCommon.h"
#include "EventCenter.h"
using namespace NProtoCommon;
using namespace NRoleInfoDefine;
using namespace NProtoCommon;
using namespace NEventCenter;

/*
enum EventType
{
    eEventType_Invalid,
    eEventType_Trump = 10000,       //1收藏法宝  法宝id
    eEventType_Hero,        //2收藏散仙  散仙id
    eEventType_Formation,   //3收藏阵型  阵型id
    eEventType_PetData,     //4收藏阵灵  阵灵id
    eEventType_GetFashion,  //5收藏时装  时装id
    eEventType_GetHorse,    //6收藏坐骑  坐骑id
    //new evemt上面的事件暂时不用
    eEventType_Login = 1,    //登陆事件
    eEventType_PackExpand = 100, //扩展背包格子
    eEventType_SellItem   = 101, //出售物品
    eEventType_SortPack   = 102, //整理背包
    eEventType_AchiementLevel = 201, //成就等级
    eEventType_GetAchiement   = 202, //成就达成
    eEventType_RoleLevel      = 301, //玩家等级

    eEventType_Max,
};
*/
enum EActClass  //活动分类
{
    eActClass_Invalid,
    eActClass_Achieve,//成就
    eActClass_Collect, //收藏
    eActClass_LevelPrize, //条件礼包活动
    eActClass_Activity, //活跃度
    eActClass_LoginPkg, //累计登录礼包
    eActClass_SevenDayTarget,//七日目标活动
    eActClass_UDPLOG,        //log监测事件
    eActclass_End,
};

enum EEventStatus
{
    eEventStatus_Init,    //初始化
    eEventStatus_Process, //进行中(仅对持续事件)
    eEventStatus_Finish,  //完成
};

enum EEventCondition
{
    eEventCondition_Common, //普通触发事件
    eEventCondition_Add =1, //持续触发事件
};

enum EEventOp
{
    eEventOp_Invalid,               //无效
    eEventOp_Equal            =1,   //等于
    eEventOp_GreaterOrEqual   =2,   //大于等于
    eEventOp_Sum              =3,   //累计
    eEventOp_TotalLogin       =4,   //累计登陆
    eEventOp_ContinueLogin    =5,   //连续登陆
    eEventOp_LessOrEqual      =6,   //小于等于
    eEventOp_MinCount         =7,   //统计大于等于VecParamLimit[0]的数据VecParamLimit[1]次 
};


struct SEventCFGEx:SEventCenterCFG
{
    TVecINT32 _vecParam;
    void CopyFrom(SEventCenterCFG& rEventCFG)
    {
        *((SEventCenterCFG*)this) = rEventCFG;
    }
};

class CPlayer;
class CRegiserterEvent;

typedef shared_ptr<SEventCFGEx> SEventCFGExPtr;
typedef std::map<UINT32,SEventCFGExPtr> TMapEventCFGExPtr;
typedef std::vector<SEventCFGExPtr>     TVecEventCFGExPtr;

typedef shared_ptr<SDataUploadCFG> SDataUploadCFGPtr;
typedef std::map<UINT32,SDataUploadCFGPtr> TMapDataUploadPtr;

typedef shared_ptr<SEventInfo> SEventInfoPtr;


//typedef std::map<UINT16,TListEventInfoPtr> TMapEventInfoListPtr;

struct SEventKey
{
    SEventKey(UINT8 byActClassID,UINT32 dwEventInstID,UINT32 dwApplyID):
        _byActClassID(byActClassID),
        _dwEventInstID(dwEventInstID),
        _dwApplyID(dwApplyID) 
    {}

    UINT8   _byActClassID;
    UINT32  _dwEventInstID;
    UINT32  _dwApplyID;
    

    bool operator < (const SEventKey& sk) const
    {
        if(_byActClassID != sk._byActClassID)
        {
            return _byActClassID < sk._byActClassID;
        }

        if(_dwEventInstID != sk._dwEventInstID)
        {
           return _dwEventInstID < sk._dwEventInstID;
        }
        
        return _dwApplyID < sk._dwApplyID;
    }

};

struct SApplyKey
{
    SApplyKey(UINT8 byActClassID,UINT32 dwApplyID):
        _byActClassID(byActClassID),
        _dwApplyID(dwApplyID) 
    {}

    UINT8   _byActClassID;
    UINT32  _dwApplyID;
    
    bool operator < (const SApplyKey& sk) const
    {
        if(_byActClassID != sk._byActClassID)
        {
            return _byActClassID < sk._byActClassID;
        }
       
        return _dwApplyID < sk._dwApplyID;
    }

};

typedef std::map<SApplyKey,TVecUINT32> TMapApply;
typedef std::vector<SApplyKey> TVecApplyKey;

typedef std::map<SEventKey,SEventInfoPtr> TMapEventInfoPtr;
typedef std::list<SEventInfoPtr> TListEventInfoPtr;

typedef std::map<UINT16,TMapEventInfoPtr> TMapMapEventInfoPtr; 

typedef std::map<UINT16,TVecUINT32> TMapMapEventInst;

//事件活动继承的基类
//使用前要做RegisterEventInit()
class CRegiserterEvent
{
 public:
     CRegiserterEvent(EActClass eActClassID,CPlayer& rPlayer);
     ~CRegiserterEvent();

     //继承虚
     virtual void OnEvent(SEventInfoPtr pEventInfo)=0;

     //添加关注的事件
     bool AddEvent(UINT32 dwEventInstID,UINT32 dwApplyID,UINT32 dwStartTime=0);

     //删除某个事件
     void RemoveEvent(UINT32 dwEventInstID,UINT32 dwApplyID);

     //删除所有关注事件
     void ClearEvent();

     //获取事件信息
     SEventInfoPtr GetEventInfo(UINT32 dwEventInstID,UINT32 dwApplyID);

     //该事件是否完成
     bool IsFinish(UINT32 dwEventInstID,UINT32 dwApplyID);
    
    EActClass GetActClassID()
    {
        return _eActClassID;
    }

    //初始化，主要功能是注册活动
    void RegisterEventInit();

public:
    EActClass _eActClassID;
    bool _bInit;
protected:
    CPlayer& _rRegisterPlayer;
};

typedef std::list<CRegiserterEvent*>  TListRegiserterEventPtr;
typedef std::vector<CRegiserterEvent*> TVecRegiserterEventPtr;

class CGlobalEvent
{
public:
    CGlobalEvent(EActClass eActClassID):_eActClassID(eActClassID){};
    //@in vecEventInst
    //@out vecNeedEventInst
    virtual UINT32 IsListen(TVecUINT32& vecEventInst,TVecUINT32& vecNeedEventInst)=0;
    virtual bool OnEventFinish(CPlayer& rPlayer,UINT32 dwEventInstID);
    virtual void OnEventProcess(CPlayer& rPlayer,const SEventInfoPtr pEventInfoPtr);
    EActClass GetActClassID() { return _eActClassID; }
public:
    EActClass _eActClassID;
};

typedef std::map<UINT16,CGlobalEvent*> TMapGlobalEvent;



class CEventMgr:public CPoolObj<CEventMgr>
{
 public:
     ~CEventMgr(){};
     CEventMgr(CPlayer& rPlayer);
     
     static bool EventInit();

    bool LoadFromDB(const RoleDataInfo& rRoleDataInfo);

    void Update2DB(SEventInfo& rInfo, EDataChange eDataChange = eOpUpdate);

    void RegisterClass(CRegiserterEvent* pRegiserterEvent);

    void UnRegisterClass(CRegiserterEvent* pRegiserterEvent);


     SEventCFGExPtr GetEventByID(UINT32 dwEventID);


     //@vecParam参数1参数2，参数3。。。。参数3后面的特殊处理
     //@bLog 是否需要打log，非瞬时的填false
     void OnEvent(const EventType eEvent,const TVecINT32& vecParam,const string& strParam="",bool bLog=true,UINT32 dwEventTime=0);


     bool CheckIsSaveDB(SEventInfoPtr pEventInfoPtr);

     bool OnProcess(SEventInfoPtr pEventInfoPtr,const TVecINT32& vecParam);

     void OnUDPLog(SEventInfoPtr pEventInfoPtr, const TVecINT32& vecParam,const string& strParam,bool bLog);


     bool AddEvent(EActClass eActClassID,UINT32 dwEventInstID,UINT32 dwApplyID,UINT32 dwStartTime);
     
     void RemoveEvent(EActClass eActClassID,UINT32 dwEventInstID,UINT32 dwApplyID);

     void ClearEventByActClassID(EActClass eActClassID);

     void ClearApply(EActClass eActClassID,UINT32 dwApplyID);

     void ClearApply(EActClass eActClassID);

     bool CheckIsSaveDB(SEventCFGExPtr pEventCFGEx);   
     //是否所有事件实例都完成
     bool IsAllFinish(SEventInfoPtr pEventInfoPtr);

     CRegiserterEvent* GetActByClassID(EActClass eActClassID);

     SEventInfoPtr GetEventInfo(EActClass eActClassID,UINT32 dwEventInstID,UINT32 dwApplyID);

     SEventInfoPtr FindEventInfoInMap(TMapEventInfoPtr& mapEventInfoPtr,EActClass eActClassID,UINT32 dwEventInstID,UINT32 dwApplyID);

     bool InsertEventInfo(TMapEventInfoPtr& mapEventInfoPtr,SEventInfoPtr pEventInfoPtr);

     void RemoveEventByClassID(TMapEventInfoPtr& mapEventInfoPtr,EActClass eActClassID);

     void RemoveEventInfo(TMapEventInfoPtr& mapEventInfoPtr,EActClass eActClassID,UINT32 dwEventInstID,UINT32 dwApplyID); 

     void ClearEventInfo(TMapEventInfoPtr& mapEventInfoPtr);

     //获取事件下面的列表
     TMapEventInfoPtr* GetMapEventInfo(EventType eEventType);

     //获取udplog配置
     SDataUploadCFGPtr GetUDPLogCFG(UINT32 dwEventInstID);

     

     static void RegGlobalClass(CGlobalEvent* pGlobalEvent); 

     void PrintEventSize();
 private:
     void DoEventForTask(EventType eEvent,const TVecINT32& vecParam,UINT32 dwEventTimer);

 private:
     //注册表
     TVecRegiserterEventPtr _vecRegiserterEventPtr;

     //全局的注册表
     static TMapGlobalEvent _mapGlobalEvent;

     //活动事件列表
     //TMapActClassInfo _mapActClassInfo;

     TMapMapEventInfoPtr _mapMapEventInfoPtr;

     static TMapEventCFGExPtr _mapEventCFGExPtr;
     
     static TMapMapEventInst  _mapMapEventInst;

     static TMapDataUploadPtr _mapDataUploadPtr;

     //TVecEventCFGExPtr _arEventType[eEventType_Max];
     //
     

     //记录应用id对应多少个事件
     TMapApply _mapApply;

     bool _bLog;

     CPlayer& _rPlayer;

};

//extern CEventMgr g_EventMgr;

#endif

