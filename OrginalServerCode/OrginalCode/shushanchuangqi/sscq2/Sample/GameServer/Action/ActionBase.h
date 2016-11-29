#ifndef ACTIONBASE_H__
#define ACTIONBASE_H__
#include "stdafx.h"
#include "SittingProt.h"
#include "ItemProt.h"
using namespace NItemProt;
using namespace std;
enum EACTION
{
    eACTION_NONE,
    eACTION_SWEEPING ,//扫荡
    eACTION_SIT,//打坐
    eACTION_DGN,//副本
    eACTION_WORLDBOSS,//世界Boss
    eACTION_TOWER,//索妖塔
    eACTION_GUIDBATTLE,//帮派战
    eACTION_CAMPBATTLE,//阵营战
    eACTION_GATHER,//采集
    eACTION_MAX
};
enum EACTION_RELATION
{
    E_MUTEX, //互斥
    E_TOGATHER,//共存
    E_BREAK, //中断
};
enum EACTION_OTHER
{
    E_TimerEndLess = 1 << 30, //无尽次数
    E_Sitting_Timer = 6,//打坐6秒
};
typedef std::set<EACTION> setAction;
class CActionManager;
class CPlayer;
class CActionBase
{
    public:
        CActionBase(EACTION eAction,time_t ContinueTimer,UINT32 dwTimes,CActionManager *pManager):_eAction(eAction),_ContinueTimer(ContinueTimer),_dwTimes(dwTimes),_pManager(pManager),_bIsWork(true)
    {
        _dwSpeedTime = 0;
        _LastEndTimer = time(NULL) + ContinueTimer;
    }
        CActionBase():_eAction(eACTION_NONE),_ContinueTimer(0),_dwTimes(0),_LastEndTimer(0),_pManager(NULL),_bIsWork(false)
    {
    }

        virtual ~CActionBase();
        virtual void End();//这个动作结束时作的事情
        virtual void Break();//这个动作被终止时作的事情
        virtual void TimeOut();//一个计数到达时做的事情
        virtual bool CheckSpeedUp(UINT8 byOptions){return false;};//加速,扣除资源
        virtual bool IsTimeOut(time_t tNow);
        bool IsWork(){return _bIsWork ;}
        bool IsOver(){return _dwTimes== 0;}
        time_t ReserverTime();
        time_t GetLastEndTime(){return _LastEndTimer ;}
        UINT32 GetTimes(){return _dwTimes;}
        void AddSpeedTime(UINT32 dwSpeedTime) { _dwSpeedTime += dwSpeedTime; }
        void SetEndTime(UINT32 dwEndTime) { _LastEndTimer = dwEndTime; }
        EACTION GetAction() { return _eAction;}
    protected:
        EACTION _eAction;
        time_t _ContinueTimer;
        UINT32 _dwTimes;
        time_t _LastEndTimer;
        //加速时间
        UINT32 _dwSpeedTime;
        CActionManager* _pManager;
    private:
        bool _bIsWork;
};
namespace NRoleInfoDefine
{
    struct RoleDataInfo;
};
namespace NDungeonProt
{
    struct SGetSweepInfo;
};
class CActionManager
{
    public:
        CActionManager(CPlayer& rPlayer):_rPlayer(rPlayer),_bLoaded(false),_bInitSweep(false)
    {}
        ~CActionManager();
        void TimerCheck(time_t now);
        CPlayer& GetPlayer(){return _rPlayer;} 

    public://Create
        void  AddAction(EACTION eAction);//登记一个动作
        void  ClearAction(EACTION eAction);//清除一个动作
        bool  HasAction(EACTION eAction);
        EACTION CanAddAction(EACTION eAction,bool bNeedNotice=true);//判定可否加入一个动作
        void BreakAction(const setAction &setBreak);
        static bool Init();
        void NoticeActionErrMsg(EACTION eAction);
        ///以下是扫荡的代码
        bool  AddSweePing(UINT16 wDgnID,UINT16 wCount,UINT32& dwSweepEndTime);
        UINT8  SpeedUpAction(EACTION eAction,UINT8 byOptions);//0,成功，1，不允许加速，2，加速道具不足
        UINT32 GetReserverTimerByType(EACTION eAction);
        void  GetSweePingInfo(NDungeonProt::SGetSweepInfo& oGetSweepInfo);
        bool CancelAction( EACTION eAction);
        void OnVIPChange();

        bool LoadFromDB(const NRoleInfoDefine::RoleDataInfo& rRoleDataInfo);

        NSittingProt::ESittingResult DoSitting(UINT64 qwRoleId);
        void CalSittingAward(TVecResource& vecRes,UINT32 dwTimer,bool bDouble);
        void SetLoadedOk() { _bLoaded= true; }
        void SetInitSweep(bool bInit ) { _bInitSweep = bInit ; }
        bool IsInitSweep() { return _bInitSweep; }
    private:
        static map<EACTION,map<EACTION,EACTION_RELATION> > _mapActionConfig; 
        setAction _setAction;
        //以下是扫荡的代码
        CActionBase *  CreateAction(EACTION eAction,time_t ContinueTimer = 0,UINT32 dwTimes = 0);
        CActionBase * GetActionByType(EACTION eAction);
        CPlayer& _rPlayer;
        map<EACTION,CActionBase*> _mapAction;
        bool _bLoaded;
        bool _bInitSweep;

};
#endif//ACTIONBASE_H__
