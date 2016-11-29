#ifndef GROUPTASK_H__
#define GROUPTASK_H__
#include "stdafx.h"
#include "RoleInfoDefine.h"
#include "GroupTaskProt.h"
#include "TaskProt.h"
class CPlayer;
using namespace NRoleInfoDefine;
using namespace  NTaskProt;
using namespace NGroupTaskProt;
class CGroupTaskPkg
{
    public:
        void Init(const SGroupTaskInfo &rInfo);
        void Update2DB();
        void AcceptTask(UINT32 dwTaskId);//接受一个任务
        void FinishTask(UINT32 dwTaskId,UINT8 byNum);
        void GiveUpTask(UINT32 dwTaskId);
        ETaskResult CanAcceptGroupTask(UINT32 dwTaskId);
        EGroupTaskResult DoGroupTaskOp(EGroupStudyState &eState);
        EGroupTaskResult DoFlushTask(TVecGroupTask &vecTask,UINT8 &byFlushTimes);
        void SendAllInfoTask();
        CGroupTaskPkg(CPlayer &rPlayer);
        void DoFlushTaskCase(bool bFirst,bool bCost );
        bool GetFlushState(UINT32 dwTaskId,EGroupTaskState &eState);
        void CheckStudyState(bool bNotice =true);
        EGroupTaskResult DoBuyTask();
        UINT8 GetCanAccepTask();
        void  GMaddTimes(UINT8 byTimes);
    private:
        void FlushMapToInfo();
        void FlushInfoToMap();
        UINT8 GetAcceptTask();
        void SynTaskToClient();
        UINT8 GetStudyTimes();
    private:
        SGroupTaskInfo _TaskInfo;
        EGroupStudyState _eStudyState;
        map<UINT32,EGroupTaskState> _mapFlushTask;
        CPlayer& _rPlayer;
};
#endif

