#pragma once
//#include "ChurchTask.h"
#include "TaskProt.h"
#include "TaskConf.h"
#include "RoleInfoDefine.h"

using namespace NTaskProt;
using namespace NRoleInfoDefine; 
class CPack;


const UINT16 wCircleIcon = 73;
class CTaskPkg
{
    public:
        CTaskPkg(CUser& rUser);
        ~CTaskPkg();

        CUser& GetUser();
        CPlayerPtr GetPlayer();
        CPack& GetUserPack();
        void FinishAllMainTask(UINT16 wTaskId);
#if 0
        STaskRecordStream* GetTaskRecord(UINT16 wTaskID, bool bInit = false);

        bool FromStream(const TVecTaskStream& vecStream);
        bool ToStream(TVecTaskStream& vecStream) const;
        bool FromStream(const TVecTaskRecStream& vecStream);
        bool ToStream(TVecTaskRecStream& vecStream) const;
        bool FromStream(const SChurchInfo& rChurch);
        bool ToStream(SChurchInfo& rChurch) const;
#endif
        //	bool HasTaskChange() const { return _bHasTaskChange; }
        //	void SetHasTaskChange(bool bHasChange) { _bHasTaskChange = bHasChange; }
        //	bool HasRecChange() const { return _bHasRecChange; }
        //	void SetHasRecChange(bool bHasChange) { _bHasRecChange = bHasChange; }
        //bool HasChurchChange() const { return _bHasChurchChange; }
        //void SetHasChurchChange(bool bHasChange) { _bHasChurchChange = bHasChange; }

        ENpcTaskState GetNpcTaskState(UINT16 wNpcID);
        void UpdateSurroundNpcTaskState(); //NPC任务才需要更新
        bool IsTaskFinished(UINT16 wTaskID);

        bool IsTaskPass(UINT16 wTaskID);
        ETaskResult CheckAcceptTask(UINT16 wTaskID);

        ETaskResult GiveUpTask(UINT16 wTaskID,bool bForbit = false);
        ETaskResult FinishTask(UINT16 wTaskID, UINT8 byIndex,UINT8 byCost,bool bGM = false);

        CTaskPtr FindTask(UINT16 wTaskID);
        CTaskPtr CreateTask(UINT16 wTaskID);

        void CreateTask(const RoleTaskInfo& rTaskInfo);
        RoleTaskInfo * GetRoleTaskInfo(UINT16 wTaskID);
        void UpdateRoleTaskInfo(RoleTaskInfo& rTaskInfo);

        void DestroyTask(CTask& rTask, bool bNotify = true);
        ETaskResult AcceptTask(UINT16 wTaskID,UINT8 byCost);
        void OnCollectItem(UINT16 wItemID);
        void OnGather(UINT16 wGatherID);
        bool OnNpcTalk(UINT16 wNpcID, UINT16 wTaskID);
        void OnKillMonster(UINT16 wMonsterID);
        void OnProbe(UINT16 wTaskID, SMapArea& rMapArea);
        void OnGrow(CPlayer& rPlayer, EProcessRoleProperty eProperty); //成长类型
        void OnAction(CPlayer& rPlayer, EProcessAction eProcessAction, UINT32 dwValue = 1,UINT32 dwEventTimer = 0); //dwValue表示行为次数
        void OnBuild(UINT16 wBuildID, UINT16 wLevel); //建筑升级(已取消)
        void OnTechnics(UINT16 wTechnicsID, UINT16 wLevel); //科技升级

        void DelTask(UINT16 wTaskID);
        void DelTask(const string& strName);
        void SetFinishTask(UINT16 wTaskID);
        void SetFinishTask(const string& strName);
        void SetTaskFail(UINT16 wTaskID);
        void GMAddTask(UINT16 wTaskID); //GM用
        void AllTaskNotify();
        //	void CChurchTaskNotify(UINT8 byVersion = 0, UINT8 byRefresh = 0);
        void CTaskRecordNotify();

        void TimerCheck(time_t tNow);

        //remove:bool CanBuyFresh() { return _oChurch.wCount > 0; }
        //remove:void RefreshChurchTask(bool bFree = true);
        void ResetState();
        void InitTaskFromDB(const TVecRoleTaskInfo& rvecTaskInfo);
        //UINT16 GetChurchTaskDoneTimes();

        bool HasKillMonsterTask(UINT16 wMonsterID, TVecUINT16& vecTaskID);

        void ForEachTask(function<void (CTask&)> func);
        //	bool AcceptItemTask();
        //UINT16 GetChurchTaskNum();
        void DoCaseForDgn(UINT16 wDgnType);
        //得到某任务类型的任务数
        UINT32 GetTaskNumByType(ETaskConfType eType); 
        //放弃某种类型的任务
        void   GiveUpTaskByType(ETaskConfType eType);
        //同步环任务
        void   SendCircleInfo();
        //尝试刷下一个环任务
        void    AcceptCircleTask(bool bSendCircleInfo = true);
        //完成所有的环任务
        ETaskResult FinishAllCircleTaskOneKey();
        //提升星级
        ETaskResult   UpdateCircleTaskStar();
        //尝试接取每日任务
        void AcceptEveryDayTask();
        void AcceptTaskFromSystem();
        void AcceptTaskForZero();
    protected:
        ETaskResult InternalAcceptTask(UINT16 wTaskID,UINT8 byCost,  bool bNotify = true);
        ETaskResult AcceptCommonTask(UINT16 wTaskID,UINT8 byCost, bool bNotify = true);
        //ETaskResult AcceptChurchTask(SChurch& rChurch);
        //bool AcceptChurchTask(UINT16 wTaskID, UINT8 byStar);
        void CheckDailyReset(bool bNotify = true);

        CUser& _rUser;
        map<UINT16, CTaskPtr> _mapID2Task;//活跃的任务
        map<UINT16,RoleTaskInfo> _mapID2Record;//任务记录

#if 0
        map<UINT16, STaskRecordStream> _mapID2Record;
#endif
        //	bool _bHasTaskChange;
        //  	bool _bHasRecChange;
#if 0
        bool _bHasChurchChange;

        //银焰教会
        SChurchInfo _oChurch;
        UINT8 _byVersion;
#endif
};
