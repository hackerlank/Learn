#ifndef YAMENTASK_H__
#define YAMENTASK_H__
#include "stdafx.h"
#include "RoleInfoDefine.h"
#include "YaMenTaskProt.h"
#include "TaskProt.h"
class CPlayer;
using namespace NRoleInfoDefine;
using namespace  NTaskProt;
using namespace NYaMenTaskProt;
class CYaMenTaskPkg
{
    public:
        void Init(const SYaMenTaskInfo &rInfo);
        void Update2DB();
        void AcceptTask(UINT32 dwTaskId);//接受一个任务
        void FinishTask(UINT32 dwTaskId,UINT8 byNum);
        void GiveUpTask(UINT32 dwTaskId);
        ETaskResult CanAcceptYaMenTask(UINT32 dwTaskId);
        EYaMenTaskResult DoYaMenTaskOp(EYaMenStudyState &eState);
        EYaMenTaskResult DoFlushTask(TVecYaMenTask &vecTask,UINT8 &byFlushTimes);
        void SendAllInfoTask();
        CYaMenTaskPkg(CPlayer &rPlayer);
        void DoFlushTaskCase(bool bFirst,bool bCost );
        bool GetFlushState(UINT32 dwTaskId,EYaMenTaskState &eState);
        void CheckStudyState(bool bNotice =true);
        EYaMenTaskResult DoBuyTask();
        UINT8 GetCanAccepTask();
        void  GMaddTimes(UINT8 byTimes);
    private:
        void FlushMapToInfo();
        void FlushInfoToMap();
        UINT8 GetAcceptTask();
        void SynTaskToClient();
        UINT8 GetStudyTimes();
    private:
        SYaMenTaskInfo _TaskInfo;
        EYaMenStudyState _eStudyState;
        map<UINT32,EYaMenTaskState> _mapFlushTask;
        CPlayer& _rPlayer;
};
#endif

