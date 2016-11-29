#include "stdafx.h"
#include "TaskPkg.h"
#include "TaskConfMgr.h"
#include "Protocols.h"
#include "User.h"
#include "Player.h"
#include "TaskMgr.h"
#include "Script.h"
//#include "ScriptLib.h"
#include "Map.h"
#include "NPC.h"
#include "Visitor.h"
#include "Parameter.h"
//#include "LogMgr.h"
//#include "RecordUtil.h"
#include "Task.h"
#include "TaskMgr.h"
#include "Version.h"
#include "VIPMgr.h"
CTaskPkg::CTaskPkg(CUser& rUser) : _rUser(rUser)/*, _bHasTaskChange(false), _bHasRecChange(false), _byVersion(0)*/
{
    //_oChurch.wCount = _oChurch.wTotalCount = 10;//TODO: SParamConfig::wTaskChurchCount;
}

CTaskPkg::~CTaskPkg()
{
    _mapID2Task.clear();
}

CUser& CTaskPkg::GetUser()
{
    return _rUser;
}

CPlayerPtr CTaskPkg::GetPlayer()
{
    return _rUser.GetPlayer();
}

CPack& CTaskPkg::GetUserPack()
{
    return _rUser.GetPack();
}
#if 0
STaskRecordStream* CTaskPkg::GetTaskRecord(UINT16 wTaskID, bool bInit /*= false*/)
{
    auto it = _mapID2Record.find(wTaskID);
    if(it != _mapID2Record.end())
        return &it->second;

    if(bInit)
    {
        STaskRecordStream& rRecord = _mapID2Record[wTaskID];
        rRecord.wTaskID = wTaskID;
        SetHasRecChange(true);
        return &rRecord;
    }
    return NULL;
}

bool CTaskPkg::FromStream(const TVecTaskStream& vecStream)
{
    for(size_t i = 0; i < vecStream.size(); ++i)
        CreateTask(*vecStream[i]);

    return true;
}

bool CTaskPkg::ToStream(TVecTaskStream& vecStream) const
{
    for(auto it = _mapID2Task.begin(); it != _mapID2Task.end(); ++it)
    {
        CTaskPtr pTask = it->second;
        STaskStreamPtr pStream = pTask->ToDBProt();
        vecStream.push_back(pStream);
    }
    return true;
}

bool CTaskPkg::FromStream(const TVecTaskRecStream& vecStream)
{
    for(size_t i = 0; i < vecStream.size(); ++i)
    {
        const STaskRecordStream& rRecord = vecStream[i];
        _mapID2Record[rRecord.wTaskID] = rRecord;
    }
    return true;
}

bool CTaskPkg::ToStream(TVecTaskRecStream& vecStream) const
{
    vecStream.reserve(_mapID2Record.size());
    for(auto it = _mapID2Record.begin(); it != _mapID2Record.end(); ++it)
    {
        const STaskRecordStream& rRecord = it->second;
        vecStream.push_back(rRecord);
    }
    return true;
}

bool CTaskPkg::FromStream(const SChurchInfo& rChurch)
{
    _oChurch = rChurch;
    return true;
}

bool CTaskPkg::ToStream(SChurchInfo& rChurch) const
{
    rChurch = _oChurch;
    return true;
}
#endif
void CTaskPkg::InitTaskFromDB(const TVecRoleTaskInfo& rvecTaskInfo)
{
    for (auto iter = rvecTaskInfo.begin() ;iter != rvecTaskInfo.end();iter++)
    {
        const RoleTaskInfo* pInfo = &(*iter);
        STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(pInfo->dwTaskId);
        if(pTaskConfig == NULL)
            continue;
        _mapID2Record[pInfo->dwTaskId] = *pInfo;
        switch (pInfo->eTaskState)
        {
            case eTaskFinish:
            case eTaskAccept:
            case eTaskFail:
                {
                    CTaskPtr pTask(new CTask(*pTaskConfig, *this,CTaskMgr::GetVersion()));
                    if(NULL == pTask)
                        return;
                    pTask->FromRoleTaskInfo(*pInfo);
                    _mapID2Task.insert(make_pair(pInfo->dwTaskId, pTask));

                }
                break;
            default:
                break;
        }
    }
}

ENpcTaskState CTaskPkg::GetNpcTaskState(UINT16 wNpcID)
{
    SNpcTask* pNpcTask = CTaskConfMgr::Instance().GetNpcTask(wNpcID);
    if(pNpcTask == NULL)
        return eNpcTaskNone;
    ENpcTaskState eNpcTaskState = eNpcTaskNone;
    for(size_t i = 0, size = pNpcTask->vecFinishTask.size(); i < size; ++i)
    {
        UINT16 wTaskID = pNpcTask->vecFinishTask[i];
        CTaskPtr pTask = FindTask(wTaskID);
        if(pTask != NULL)
        {
            switch(pTask->GetTaskState())
            {
                case eTaskFinish:
                    return eNpcTaskSubmit;
                case eTaskFail:
                    eNpcTaskState = eNpcTaskUnfinish;
                    break;
                default:
                    break;
            }
        }
    }
    for(size_t i = 0, size = pNpcTask->vecAcceptTask.size(); i < size; ++i)
    {
        UINT16 wTaskID = pNpcTask->vecAcceptTask[i];
        if(CheckAcceptTask(wTaskID) == eTaskSucceed)
            return eNpcTaskAccept;
    }
    return eNpcTaskState;
}

void CTaskPkg::UpdateSurroundNpcTaskState()
{
    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(pPlayer == NULL)
        return;
    CGameMapPtr pMap = pPlayer->GetMap();
    if(pMap == NULL)
        return;
    vector<CNpcPtr> vecNpc;
    TVecNpcTask vecNpcTask;
    pMap->GetSurroundObject(eVisitAllNpc, *pPlayer, vecNpc);
    for(size_t i = 0; i < vecNpc.size(); ++i)
    {
        CNpcPtr pNpc = vecNpc[i];
        if(pNpc == NULL)
            continue;
        ENpcTaskState eNpcTaskState = GetNpcTaskState(pNpc->GetNpcID());
        SNpcTaskState oSNpcTaskState(pNpc->GetNpcID(), eNpcTaskState);
        vecNpcTask.push_back(oSNpcTaskState);
    }
    UINT64 qwUsrID = _rUser.GetUserID();
    g_NpcProtS.SendClt_NpcTaskStateNtf(&qwUsrID, 1, vecNpcTask);
}

bool CTaskPkg::IsTaskFinished(UINT16 wTaskID)
{
    RoleTaskInfo* pTaskRecord  = GetRoleTaskInfo(wTaskID);
    if (!pTaskRecord)
        return false;
    return pTaskRecord->eTaskState == eTaskFinish;
}

bool CTaskPkg::IsTaskPass(UINT16 wTaskID)
{
    RoleTaskInfo * pTaskRecord  = GetRoleTaskInfo(wTaskID);
    if(NULL == pTaskRecord)
    {
        return false;
    }
    return pTaskRecord->dwFinishTimes > 0;
}
ETaskResult CTaskPkg::CheckAcceptTask(UINT16 wTaskID)
{
    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(pPlayer == NULL)
        return eTaskErrOther;

    STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(wTaskID);
    if(pTaskConfig == NULL || !pTaskConfig->bOpen)
        return eTaskNotExist;
    if(pTaskConfig->eTaskType == eTaskForGroup)
    {
        ETaskResult eResult = GetUser().GetPlayer()->GetGroupPkg().CanAcceptGroupTask(wTaskID);
        if(eResult != eTaskSucceed)
        {
            return eResult;
        }

    }
    else if(pTaskConfig->eTaskType == eTaskForYaMen)
    {
        ETaskResult eResult = GetUser().GetPlayer()->GetYaMenPkg().CanAcceptYaMenTask(wTaskID);
        if(eResult != eTaskSucceed)
        {
            return eResult;
        }
    }
    else if(pTaskConfig->eTaskType == eTaskCircle)
    {

        if(GetTaskNumByType(eTaskCircle) > 0)
        {
            return eTaskCircleFull;
        }
    }
    if(!Config.CheckTaskCanRepeat(pTaskConfig->eTaskType))
    {
        CTaskPtr pTask = FindTask(wTaskID);
        if(pTask != NULL)
            return eTaskAlreadyAccept;
    }
    STaskScript* pTaskScript = CTaskMgr::GetTaskScript(wTaskID);
    if(pTaskScript && pTaskScript->_bHasCanAcceptTask)
    {
        if(!Config.GetScript().CanAcceptTask(wTaskID,GetUser()))
        {
            return eTaskErrOther;
        }
    }
    //系统自动任务,悬赏任务无限制
    if(eTaskTypeExtent_reward != pTaskConfig->eTaskTypeExtent && pTaskConfig->oTriggerTarget.eType != eTargetScene)
    {
        if((UINT16)_mapID2Task.size() > SParamConfig::wMaxTaskCount)
            return eTaskErrFull;
    }

    time_t oCurTime = time(NULL);
    if(pTaskConfig->qwLimitDateFrom != 0 || pTaskConfig->qwLimitDateTo != 0)
    {
        if(oCurTime < (time_t)pTaskConfig->qwLimitDateFrom || oCurTime > (time_t)pTaskConfig->qwLimitDateTo)
            return eTaskNotExist;
    }

    if(pTaskConfig->wLimitDayTimeFrom != 0 || pTaskConfig->wLimitDayTimeTo != 0)
    {
        tm oTm;
        localtime_s(&oTm, &oCurTime);
        if(oTm.tm_hour < pTaskConfig->wLimitDayTimeFrom || oTm.tm_hour > pTaskConfig->wLimitDayTimeTo)
            return eTaskNotExist;
    }

    if(eTaskTypeExtent_reward != pTaskConfig->eTaskTypeExtent)
    {
        //悬赏任务无需判断次数
        RoleTaskInfo * pTaskRecord  = GetRoleTaskInfo(wTaskID);
        if(NULL != pTaskRecord)
        {
            if(pTaskConfig->eTaskType == eTaskConfDay)
            {
                //如果最近完成任务是今天
                if(Time::sameDay(pTaskRecord->dwLastFinishTimer,time(NULL)))
                {
                    return eTaskNotExist;
                }

            }
            else
            {
                if(pTaskRecord->dwFinishTimes > pTaskConfig->dwRepeat)
                    return eTaskNotExist;
            }
        }
    }

    //种族限制
#if 0
    if(pTaskConfig->byRace > 0 && pPlayer->GetRace() != pTaskConfig->byRace)
        return eTaskNoRace;
#endif 
    //职业限制
    size_t i = 0;
    for(;i < pTaskConfig->vecLimitCareers.size();i++)
    {
        UINT8 byJob = (UINT8)pTaskConfig->vecLimitCareers[i];
        if(pPlayer->GetJob() == byJob)
            break;
    }

    if(i > 0 && i == pTaskConfig->vecLimitCareers.size())
        return eTaskNoJob;
#if 0
    //家族公会限制
    switch(pTaskConfig->eLimitFamily)
    {
        case eLimitFamily_family:
            if(0 == _rUser.GetFamilyID())
                return eTaskNoFamily;
            break;
        case eLimitFamily_faction:
            if(0 == _rUser.GetGuildID())
                return eTaskNoGuild;
            break;
        default:
            break;
    }

    //camplimit
    if(pTaskConfig->eLimitCamp > eLimitCamp_none)
    {
        if(pPlayer->GetCamp() != (UINT8)pTaskConfig->eLimitCamp)
            return eTaskErrCamp;
    }
#endif
    UINT8 byPreCount = 0;
    UINT8 byLimitCount = (UINT8)pTaskConfig->vecLimitPreTasks.size();
    for(UINT16 wLimitPreTask : pTaskConfig->vecLimitPreTasks)
    {
        RoleTaskInfo * pTaskRecord  = GetRoleTaskInfo(wLimitPreTask);
        if(NULL == pTaskRecord||pTaskRecord->dwFinishTimes == 0)
            continue;
        byPreCount++;
    }
    if((pTaskConfig->byLimitPreTaskFlag == 0 && byPreCount < byLimitCount)
            || byPreCount < pTaskConfig->byLimitPreTaskFlag)
        return eTaskErrPrepTask;

    for(auto it_pro = pTaskConfig->vecLimitProp.begin();it_pro != pTaskConfig->vecLimitProp.end();it_pro++)
    {
        switch(it_pro->eLimitType)
        {
            case eLimtPropLevel:	//等级判断
                if(pPlayer->GetLevel() < (UINT8)it_pro->wValue)
                    return eTaskErrLevel;
                break;
            case eLimtPropRepute:	//声望判断
                //todo
                return eTaskNoRepution;
                break;
            default:
                break;
        }
    }

    TVecItemGenInfo vecItemGenInfo;
    for(auto it = pTaskConfig->vecItemGive.begin();it != pTaskConfig->vecItemGive.end();it++)
    {
        SItemGenInfo oItemGenInfo;
        oItemGenInfo.dwCount = it->wCount;
        oItemGenInfo.wItemID = (UINT16)it->dwIdx;
        vecItemGenInfo.push_back(oItemGenInfo);
    }
    if(!vecItemGenInfo.empty())
    {
        if(!_rUser.GetPack().CanAddItem(vecItemGenInfo))
            return eTaskErrPackFull;
    }
    return eTaskSucceed;
}

ETaskResult CTaskPkg::InternalAcceptTask(UINT16 wTaskID, UINT8 byCost, bool bNotify/* = true*/)
{
    STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(wTaskID);
    if(pTaskConfig == NULL )
    {
        return eTaskNotExist;
    }
    bool bMulAccept = Config.CheckTaskCanRepeat(pTaskConfig->eTaskType);
    CTaskPtr pTask ;
    bool bHasOld =false;
    if(bMulAccept)
    {
        pTask = FindTask(wTaskID);
        bHasOld = (pTask != NULL);
    }
    if(!bHasOld)
    {
        pTask = CreateTask(wTaskID);
    }
    if(pTask == NULL)
        return eTaskNotExist;
    if(!bHasOld)
    {
        if(_mapID2Task.find(wTaskID) != _mapID2Task.end())
        {
            return eTaskAlreadyAccept;
        }
    }
    if(!pTask->OnAccept(false))
        return eTaskErrPackFull;
    STaskScript* pTaskScript = CTaskMgr::GetTaskScript(wTaskID);
    if(pTaskScript && pTaskScript->_bHasAcceptTask/* && pTaskScript->_pScript*/)
    {
        Config.GetScript().OnAcceptTask(wTaskID,GetUser());
    }
    if(!bHasOld)
    {
        _mapID2Task.insert(make_pair(wTaskID, pTask));
    }
    if(bNotify)
    {
        GetUser().SendPkg(g_TaskProtS.BuildPkg_AddTaskAck(byCost,pTask->ToStask()));
    }
    RoleTaskInfo * pTaskRecord  = GetRoleTaskInfo(wTaskID);
    if(pTaskRecord !=NULL)
    {
        pTaskRecord->dwAcceptTimes++;
        if(bHasOld)
        {
            pTask->AddAcceptTimes(); 
        }
        pTask->SynData(*pTaskRecord);
    }
    else
    {
        RoleTaskInfo sTask;
        sTask.dwTaskId = wTaskID;
        sTask.dwAcceptTimes = 1;
        pTask->SynData(sTask);
        _mapID2Record[wTaskID]= sTask;
    }


#if 0
    if(eTaskConfMain == pTask->GetTaskConfig().eTaskType)
    {
        std::string strStep = "accept" + NumberToString(wTaskID);
        _rUser.SendCenterSvrPkg(g_Game2CenterLog.BuildPkg_LogGuideChange(_rUser.GetUserID(), "guide", strStep));
    }
#endif
    if(pTaskScript && pTaskScript->_bHasDoCaseForDgn/* && pTaskScript->_pScript*/)
    {
        Config.GetScript().DoCaseForDgn(wTaskID,GetUser().GetPlayer()->GetDgnID(),GetUser());
    }

#if 0
    CPlayerPtr pPlayer = GetPlayer();
    if(NULL != pPlayer)
        TaskLog.LogTask(*pPlayer, eTaskLog_Accept, (UINT8)pTask->GetTaskType(), wTaskID);
#endif
    GetUser().GetPlayer()->GetGroupPkg().AcceptTask(wTaskID);
    GetUser().GetPlayer()->GetYaMenPkg().AcceptTask(wTaskID);
    return eTaskSucceed;
}

ETaskResult CTaskPkg::AcceptTask(UINT16 wTaskID,UINT8 byCost)
{
    STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(wTaskID);
    if(pTaskConfig == NULL || !pTaskConfig->bOpen)
        return eTaskNotExist;

#if 0
    if(eTaskTypeExtent_reward == pTaskConfig->eTaskTypeExtent)
    {
        if(SSysConf<eSysMasterTask>::IsSystemOpened(_rUser))
        {
            //次数还够不够
            if(GetChurchTaskNum() >= SParamConfig::wAcceptChurchNum)
                return eTaskErrFull;
            if(0 == _oChurch.wCount)
                return eTaskNotExist;
            for(auto it = _oChurch.vecChurch.begin();it != _oChurch.vecChurch.end();it++)
            {
                if(it->wTaskID == wTaskID && it->eState == eChurchCanAccept)
                {
                    UINT8 byStar = it->byStar;
                    ETaskResult eResult = AcceptChurchTask(*it);
                    if (eResult == eTaskSucceed)
                    {
                        // check event act
                        _rUser.GetEventActPkg().OnEvent(SEventInfo(0, byStar, 0, eEventActType_Church, "GoldQuest"));
                        _rUser.GetEventActPkg().OnEvent(SEventInfo(0, byStar, 0, eEventActType_Angel, "GoldQuest"));
                    }

                    return eResult;
                }
            }
        }
    }
    else
    {
        return AcceptCommonTask(wTaskID);
    }
    return eTaskErrOther;
#endif
    return AcceptCommonTask(wTaskID,byCost);

}

ETaskResult CTaskPkg::AcceptCommonTask(UINT16 wTaskID,UINT8 byCost, bool bNotify/* = true*/)
{
    ETaskResult eResult = CheckAcceptTask(wTaskID);
    if(eResult != eTaskSucceed)
        return eResult;
    return InternalAcceptTask(wTaskID,byCost, bNotify);
}
#if 0
ETaskResult CTaskPkg::AcceptChurchTask(SChurch& rChurch)
{
    if (AcceptChurchTask(rChurch.wTaskID, rChurch.byStar))
    {
        rChurch.eState = eChurchAccept;
        _oChurch.wCount--;
        if(0 == _oChurch.wCount)
        {
            for(auto it = _oChurch.vecChurch.begin();it != _oChurch.vecChurch.end();it++)
            {
                if(eChurchCanAccept == it->eState)
                    it->eState = eChurchUnAccept;
            }
        }
        CChurchTaskNotify();
        CPlayerPtr pPlayer = _rUser.GetPlayer();
        if(NULL != pPlayer)
            _rUser.GetTaskPkg().OnAction(*pPlayer, eProcessAction_ChurchTask);
        SetHasChurchChange(true);

        return eTaskSucceed;
    }

    return eTaskErrFull;
}

bool CTaskPkg::AcceptChurchTask(UINT16 wTaskID, UINT8 byStar)
{
    do 
    {
        if(GetChurchTaskNum() < SParamConfig::wAcceptChurchNum)
        {
            ETaskResult eResult = CheckAcceptTask(wTaskID);
            if(eResult != eTaskSucceed)
                break;

            eResult = InternalAcceptTask(wTaskID, byStar);
            if(eTaskSucceed == eResult)
                return true;
        }

    } while (0);
    return false;
}
#endif
ETaskResult CTaskPkg::GiveUpTask(UINT16 wTaskID,bool bForbit)
{
    CTaskPtr pTask = FindTask(wTaskID);
    if(NULL == pTask)
        return eTaskNotExist;
    if(!bForbit)
    {
        if(!pTask->GetTaskConfig().bCanGiveUp)//系统任务不能删除
            return eTaskErrGiveUp;
        if(pTask->GetTaskConfig().eTaskType == eTaskCircle)
        {
            return eTaskErrGiveUp;  
        }
    }
    pTask->OnGiveUp();
    STaskScript* pTaskScript = CTaskMgr::GetTaskScript(wTaskID);
    if(NULL != pTaskScript && pTaskScript->_bHasGiveUpTask /*&& NULL != pTaskScript->_pScript*/)
    {
        Config.GetScript().OnGiveUpTask(wTaskID,GetUser());

#if 0
        INT32 iRet = 0;
        if(pTaskScript->_pScript->ExecuteFunc("OnGiveUpTask", iRet, SLuaUInt64(_rUser.GetUserID()), wTaskID))
        {
            if(0 != iRet)
                LOG_CRI << "GiveUpTask fails! taskid: " << wTaskID;
        }
        else
            LOG_CRI << "ExecuteFunc fails! taskid: " << wTaskID;
#endif
    }
    if(pTask->SubAcceptTimes())
    {
        DestroyTask(*pTask);
    }
    UpdateSurroundNpcTaskState();
    GetUser().GetPlayer()->GetGroupPkg().GiveUpTask(wTaskID);
    GetUser().GetPlayer()->GetYaMenPkg().GiveUpTask(wTaskID);

    return eTaskSucceed;
}

void CTaskPkg::DoCaseForDgn(UINT16 wDgnType)
{
    for( auto it = _mapID2Task.begin();it != _mapID2Task.end();it++)
    {   
        CTaskPtr pTask  = it->second;
        if(pTask->GetTaskState() == eTaskAccept)
        {
            STaskScript *pTaskScript = CTaskMgr::GetTaskScript(it->first);
            if(pTaskScript != NULL && pTaskScript->_bHasDoCaseForDgn)
            {
                Config.GetScript().DoCaseForDgn(it->first,wDgnType,GetUser());
            }
        }

    }
}
ETaskResult CTaskPkg::FinishTask(UINT16 wTaskID, UINT8 byIndex,UINT8 byCost,bool bGM)
{
    STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(wTaskID);
    if(pTaskConfig == NULL )
    {
        return eTaskNotExist;
    }
    bool bCanForce = (pTaskConfig->eTaskType == eTaskForGroup || pTaskConfig->eTaskType == eTaskForYaMen || pTaskConfig->eTaskType == eTaskCircle);
    bool bForce = false;
    CTaskPtr pTask = FindTask(wTaskID);
    if(NULL == pTask)
        return eTaskNotExist;
    bool bFinish = (pTask->GetTaskState() == eTaskFinish );
    if(bGM)
    {
        bFinish = true;
    }
    if(byCost == 0)//不付费
    {
        if(!bFinish)
        {
            return eTaskErrFinish;
        }
    }
    else
    {
        if(bFinish)
        {
            return eTaskErrFinish; 
        }
        if(!bCanForce)
        {
            return eTaskErrFinish;
        }
        if(pTaskConfig->eTaskType == eTaskForYaMen || pTaskConfig->eTaskType == eTaskForGroup)
        {
            //检查vip
            SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(_rUser.GetVIPLevel());
            if(pCfgVip == NULL)
            {
                return eTaskErrFinish;
            }
            if(pCfgVip->_ShiyaLiKe == 0)
            {
                return eTaskErrFinish;
            }
        }
        bForce = true;
    }
    UINT8 byAcceptTimes = 0;
    ETaskResult eResult = pTask->OnFinish(byIndex,byAcceptTimes,bForce);
    if(eResult != eTaskSucceed)
        return eResult;
    STaskScript *pTaskScript = CTaskMgr::GetTaskScript(wTaskID);
    if(pTaskScript != NULL && pTaskScript->_bHasFinishTask/* && pTaskScript->_pScript != NULL*/)
    {
        Config.GetScript().OnFinishTask(wTaskID,GetUser());
#if 0
        bool bRet = false;
        if(pTaskScript->_pScript->ExecuteFunc("OnFinishTask", bRet, SLuaUInt64(_rUser.GetUserID()), wTaskID))
        {
            if(!bRet)
                LOG_CRI << "FinishTask fails! taskid: " << wTaskID;
        }
        else
        {
            LOG_CRI << "ExecuteFunc fails! taskid: " << wTaskID;
        }
#endif
    }
#if 0   
    CPlayerPtr pPlayer = GetPlayer();
    if(eTaskChurch == pTask->GetTaskType())
    {
        _rUser.GetAchievePkg().OnAchieve(eAT_ChurchTask, 1);
        _rUser.GetDailyGuide().OnDailyGuide(eGuideChurchTask);
    }
    if(eTaskConfMain == pTask->GetTaskConfig().eTaskType)
    {
        std::string strStep = "finish" + NumberToString(wTaskID);
        _rUser.SendCenterSvrPkg(g_Game2CenterLog.BuildPkg_LogGuideChange(_rUser.GetUserID(),"guide",strStep));
    }

    //_rUser.GetAchievePkg().OnAchieve(eAT_TaskTotal, 1);
    if(NULL != pPlayer)
        TaskLog.LogTask(*pPlayer, eTaskLog_Award, (UINT8)pTask->GetTaskType(), wTaskID);
#endif
    const STaskConfig& rConfig = pTask->GetTaskConfig();
    if(pTask->GetCurAcceptTimes() == 0)
    {
        DestroyTask(*pTask);
    }
    GetUser().GetPlayer()->GetGroupPkg().FinishTask(wTaskID,byAcceptTimes);
    GetUser().GetPlayer()->GetYaMenPkg().FinishTask(wTaskID,byAcceptTimes);

    if(rConfig.dwRepeat > 0 && eTargetScene == rConfig.oTriggerTarget.eType)
        AcceptCommonTask(wTaskID,0);

    //onevent

    TVecINT32  vecParam;
    vecParam.push_back(wTaskID);
    GetUser().GetPlayer()->OnEvent(eEventType_NewPlayerTask,vecParam);

    //后续任务
    TTaskList* pTaskList = CTaskConfMgr::Instance().GetTaskPreTask(wTaskID);
    if(NULL != pTaskList)
    {
        auto it = pTaskList->begin();
        for(;it != pTaskList->end();it++)
        {
            AcceptTask(*it,0);
        }
    }
    //如果是环任务
    if(rConfig.eTaskType == eTaskCircle)
    {
        GetUser().GetVars().AddVar(ePlayerCircleTaskNum,1);
        if(GetUser().GetVars().GetVar(ePlayerCircleTaskNum) < SParamConfig::byCircleTaskMaxNum)
        {
            //尝试刷下一个环任务
            AcceptCircleTask(false);
        }
        else
        {
            GetUser().GetVars().SetVar(ePlayerCircleTaskStar,0);
        }
        //同步客户端
        SendCircleInfo();

        if(GetUser().GetVars().GetVar(ePlayerCircleTaskNum) >= SParamConfig::byCircleTaskMaxNum)
        {
            TVecINT32 vecParam;
            vecParam.push_back(1);
            GetUser().GetPlayer()->OnEvent(eEventType_CircleTaskFinish,vecParam);
        }
    }
    UpdateSurroundNpcTaskState();
    return eTaskSucceed;
}

CTaskPtr CTaskPkg::FindTask(UINT16 wTaskID)
{
    auto it = _mapID2Task.find(wTaskID);
    if(it != _mapID2Task.end())
        return it->second;
    return NULL;
}
RoleTaskInfo * CTaskPkg::GetRoleTaskInfo(UINT16 wTaskID)
{
    auto iter = _mapID2Record.find(wTaskID);
    if(iter != _mapID2Record.end())
    {
        return &(iter->second);
    }
    return NULL;
}
void CTaskPkg::UpdateRoleTaskInfo(RoleTaskInfo& rTaskInfo)
{
    RoleTaskInfo * pInfo = GetRoleTaskInfo(rTaskInfo.dwTaskId);
    if( NULL == pInfo)
    {
        _mapID2Record[rTaskInfo.dwTaskId] = rTaskInfo; 
        string strData;
        COutArchive iar(strData); 
        iar << rTaskInfo;
        g_Game2DBCommC.Send_RoleDataUpdate(GetUser().GetUserID(), eTypeTaskInfo, eOpAdd, strData);
    }
    else 
    {
        *pInfo = rTaskInfo;
        string strData;
        COutArchive iar(strData); 
        iar << rTaskInfo;
        g_Game2DBCommC.Send_RoleDataUpdate(GetUser().GetUserID(), eTypeTaskInfo, eOpUpdate, strData);

    }
}
CTaskPtr CTaskPkg::CreateTask(UINT16 wTaskID)
{
    STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(wTaskID);
    if(pTaskConfig == NULL)
        return NULL;

    CTaskPtr pTask = NULL;

    pTask.reset(new CTask(*pTaskConfig, *this, CTaskMgr::GetVersion()));

    if(pTask == NULL)
        return NULL;
    if(!pTask->Init())
        return NULL;
    return pTask;
}
void CTaskPkg::CreateTask(const RoleTaskInfo& rTaskInfo)
{
    STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(rTaskInfo.dwTaskId);
    if(pTaskConfig == NULL)
        return;
    CTaskPtr pTask(new CTask(*pTaskConfig, *this, CTaskMgr::GetVersion()));
    if(NULL == pTask)
        return;
    pTask->FromRoleTaskInfo(rTaskInfo);


    _mapID2Task.insert(make_pair(rTaskInfo.dwTaskId, pTask));
}
void CTaskPkg::DestroyTask(CTask& rTask, bool bNotify/* = true*/)
{
    if(bNotify)
        GetUser().SendPkg(g_TaskProtS.BuildPkg_DelTaskAck(rTask.GetTaskID()));
    _mapID2Task.erase(rTask.GetTaskID());
}

void CTaskPkg::OnCollectItem(UINT16 wItemID)
{
    TTaskList* pTaskList = CTaskConfMgr::Instance().GetCollectTask(wItemID);
    if(pTaskList != NULL)
    {
        for(size_t i = 0; i < pTaskList->size(); ++i)
        {
            CTaskPtr pTask = FindTask((*pTaskList)[i]);
            if(pTask != NULL && pTask->GetTaskState() == eTaskAccept)
                pTask->OnCollectItem(wItemID);
        }
    }
}

void CTaskPkg::OnGather(UINT16 wGatherID)
{
    TTaskList* pTaskList = CTaskConfMgr::Instance().GetGatherTask(wGatherID);
    if(pTaskList != NULL)
    {
        for(auto it_list = pTaskList->begin();it_list != pTaskList->end();it_list++)
        {
            CTaskPtr pTask = FindTask(*it_list);
            if(pTask != NULL && pTask->GetTaskState() == eTaskAccept)
                pTask->OnGather(wGatherID);
        }
    }
}

bool CTaskPkg::OnNpcTalk(UINT16 wNpcID, UINT16 wTaskID)
{
    CTaskPtr pTask = FindTask(wTaskID);
    if(pTask == NULL || pTask->GetTaskState() != eTaskAccept)
        return false;
    if(pTask->OnNpcTalk(wNpcID))
        return true;
    return false;
}

void CTaskPkg::OnKillMonster(UINT16 wMonsterID)
{
    TTaskList* pTaskList = CTaskConfMgr::Instance().GetMonsterTask(wMonsterID);
    if(pTaskList != NULL)
    {
        for(size_t i = 0, size = pTaskList->size(); i < size; ++i)
        {
            CTaskPtr pTask = FindTask((*pTaskList)[i]);
            if(pTask != NULL && pTask->GetTaskState() == eTaskAccept)
                pTask->OnKillMonster(wMonsterID);
        }
    }
}

void CTaskPkg::OnProbe(UINT16 wTaskID, SMapArea& rMapArea)
{
    CTaskPtr pTask = FindTask(wTaskID);
    if(pTask == NULL || pTask->GetTaskState() != eTaskAccept)
        return;
    pTask->OnProbe(rMapArea);
}

void CTaskPkg::OnGrow(CPlayer& rPlayer, EProcessRoleProperty eProperty)
{
    //已有任务
    for(auto it = _mapID2Task.begin(); it != _mapID2Task.end(); ++it)
    {
        CTaskPtr pTask = it->second;
        if(NULL != pTask && pTask->GetTaskState() == eTaskAccept)
            pTask->OnGrow(rPlayer, eProperty);
    }
    switch(eProperty)
    {
        case eProcessRoleProperty_level: 	//等级
            {
                //可接任务
                TTaskList* pTaskList = CTaskConfMgr::Instance().GetLevelTask((UINT16)rPlayer.GetLevel());
                if(NULL != pTaskList)
                {
                    auto it_list = pTaskList->begin();
                    for(;it_list != pTaskList->end();it_list++)
                    {
                        AcceptTask(*it_list,0);
                    }
                }
            }
            break;
        default:
            break;
    }
}

void CTaskPkg::OnAction(CPlayer& rPlayer, EProcessAction eProcessAction, UINT32 dwValue,UINT32 dwEventTimer)
{
    UINT16 index = (UINT16)eProcessAction;
    if(index > eProcessAction_none && index < eProcessAction_Max)
    {
        UINT64 status = _rUser.GetVars().GetVar(NVarDefine::ePlayerVarTaskMark);
        if(0 == GET_BIT(status, (index - 1)))
        {
            status = SET_BIT(status, (index - 1));
            _rUser.GetVars().SetVar(NVarDefine::ePlayerVarTaskMark, status);
        }
    }

    //已有任务
    auto it = _mapID2Task.begin();
    for(; it != _mapID2Task.end(); ++it)
    {
        CTaskPtr pTask = it->second;
        if(NULL != pTask && pTask->GetTaskState() == eTaskAccept)
        {
            if(dwEventTimer == 0)
            {
            pTask->OnAction(eProcessAction, dwValue);
            }
            else 
            {
                RoleTaskInfo * pTaskRecord  = GetRoleTaskInfo(it->first);
                if(pTaskRecord && pTaskRecord->dwLastAcceptTimer<= dwEventTimer)
                {
                    pTask->OnAction(eProcessAction, dwValue); 
                }

            }
        }
    }
}

void CTaskPkg::OnBuild(UINT16 wBuildID, UINT16 wLevel)
{
    //已有任务
    /*auto it = _mapID2Task.begin();
      for(; it != _mapID2Task.end(); ++it)
      {
      CTaskPtr pTask = it->second;
      if(NULL != pTask && pTask->GetTaskState() == eTaskAccept)
      pTask->OnBuild(wBuildID, wLevel);
      }*/
}

void CTaskPkg::OnTechnics(UINT16 wTechnicsID, UINT16 wLevel)
{
    //已有任务
    auto it = _mapID2Task.begin();
    for(; it != _mapID2Task.end(); ++it)
    {
        CTaskPtr pTask = it->second;
        if(NULL != pTask && pTask->GetTaskState() == eTaskAccept)
            pTask->OnTechnics(wTechnicsID, wLevel);
    }
}

void CTaskPkg::DelTask(UINT16 wTaskID)
{
    CTaskPtr pTask = FindTask(wTaskID);
    if(NULL != pTask)
    {
        pTask->OnGiveUp();
        DestroyTask(*pTask);
        UpdateSurroundNpcTaskState();
    }
}

void CTaskPkg::DelTask(const string& strName)
{
    for(auto it = _mapID2Task.begin(); it != _mapID2Task.end(); it++)
    {
        CTaskPtr pTask = it->second;
        if(pTask->GetConfig().strName == strName)
        {
            pTask->OnGiveUp();
            DestroyTask(*pTask);
            UpdateSurroundNpcTaskState();
            break;
        }
    }
}

void CTaskPkg::SetFinishTask(UINT16 wTaskID)
{
    CTaskPtr pTask = FindTask(wTaskID);
    if(NULL != pTask)
        pTask->SetFinishTask();
}

void CTaskPkg::SetFinishTask(const string& strName)
{
    for(auto it = _mapID2Task.begin(); it != _mapID2Task.end(); it++)
    {
        CTaskPtr pTask = it->second;
        if(pTask->GetConfig().strName == strName)
        {
            pTask->SetFinishTask();
            break;
        }
    }
}

void CTaskPkg::SetTaskFail(UINT16 wTaskID)
{
    CTaskPtr pTask = FindTask(wTaskID);
    if(NULL != pTask)
        pTask->OnStateUpdate(eTaskFail);
}

void CTaskPkg::GMAddTask(UINT16 wTaskID)
{
    STaskConfig* pCfg = CTaskConfMgr::Instance().GetTaskConfig(wTaskID);
    if(NULL != pCfg)
    {
        if(NULL == FindTask(wTaskID))
            InternalAcceptTask(wTaskID,0);
    }
}
void CTaskPkg::AcceptTaskFromSystem()
{
    TTaskList* pTaskList = CTaskConfMgr::Instance().GetBeginTask();
    if(NULL != pTaskList)
    {
        for(auto it = pTaskList->begin(); it != pTaskList->end(); ++it)
            AcceptCommonTask(*it,0, false);
    }
    AcceptTaskForZero();

}
void CTaskPkg::AcceptTaskForZero()
{
    AcceptCircleTask(false);
    AcceptEveryDayTask();

}

//同步任务
void CTaskPkg::AllTaskNotify()
{
    //TODO:为了测试，先这样，新手任务需要重新设计
    //if(_mapID2Record.empty() && _mapID2Task.empty())
    //{
    //遍历系统任务(新手任务)
    TVecTask vecTask;
    for(auto it = _mapID2Task.begin(); it != _mapID2Task.end(); ++it)
    {
        UINT16 wTaskID = it->first;
        CTaskPtr pTask = it->second;
        if(pTask != NULL)
        {
            if(eTaskAccept == pTask->GetTaskState() && pTask->GetTaskConfig().dwLimitTime > 0)
            {
                if(time(NULL) - pTask->GetAcceptTime() > pTask->GetTaskConfig().dwLimitTime)
                    pTask->SetTaskState(eTaskFail);
                RoleTaskInfo * pTaskRecord = GetRoleTaskInfo(wTaskID);
                if(NULL != pTaskRecord)
                {
                    pTask->SynData(*pTaskRecord);
                }
            }
            vecTask.push_back(pTask->ToStask());
        }
    }

    _rUser.SendPkg(g_TaskProtS.BuildPkg_TaskListNtf(vecTask));

    CTaskRecordNotify();
}
#if 0
void CTaskPkg::CChurchTaskNotify(UINT8 byVersion/* = 0*/, UINT8 byRefresh/* = 0*/)
{
    ResetState();
    if(1 == byRefresh)
        RefreshChurchTask(false);
    else if(_oChurch.vecChurch.empty() || _oChurch.dwTime < (UINT32)time(NULL))
        RefreshChurchTask();
    if(0 == _byVersion)
        _byVersion++;
    //if(0 == byVersion || byVersion != _byVersion)
    _rUser.SendPkg(g_TaskProtS.BuildPkg_NotifyChurchInfoAck(_byVersion, _oChurch));
}
#endif
void CTaskPkg::CTaskRecordNotify()
{
    TVecUINT16 vecTaskID;
    for(auto it = _mapID2Record.begin();it != _mapID2Record.end();it++)
    {
        RoleTaskInfo * pTaskRecord = &(it->second);
        if (pTaskRecord->dwFinishTimes > 0)
        {
            vecTaskID.push_back(it->first);
        }
    }
    _rUser.SendPkg(g_TaskProtS.BuildPkg_NotifyTaskRecordAck(vecTaskID));
#if 0
    UINT32 dwCenterSvrID = _rUser.GetCenterSvrID();
    g_Game2CenterCommC.SendSvr_TaskFinishNtf(&dwCenterSvrID, 1, _rUser.GetUserID(), vecTaskID);
#endif
}

void CTaskPkg::TimerCheck(time_t tNow)
{
    auto it = _mapID2Task.begin();
    for(; it != _mapID2Task.end(); ++it)
    {
        CTaskPtr pTask = it->second;
        if(NULL != pTask && pTask->GetTaskState() == eTaskAccept && pTask->GetLimitTime() > 0)
        {
            if(pTask->GetAcceptTime() + pTask->GetLimitTime() < tNow)
                pTask->OnStateUpdate(eTaskFail);
            RoleTaskInfo * pTaskRecord = GetRoleTaskInfo(it->first);
            if(NULL != pTaskRecord)
            {
                pTask->SynData(*pTaskRecord);
            }
        }
    }
}

#if 0
void CTaskPkg::RefreshChurchTask(bool bFree/* = true*/) 
{
    if(0 == _oChurch.wCount)
        return;

    if (bFree)
    {
        UINT32 dwDiff = 0;
        UINT32 dwCurTime = (UINT32)time(NULL);
        if (_oChurch.dwTime > 0 && dwCurTime > _oChurch.dwTime)
            dwDiff = (dwCurTime - _oChurch.dwTime) % SParamConfig::wTaskChurchInterval;

        _oChurch.dwTime = dwCurTime + SParamConfig::wTaskChurchInterval - dwDiff;
    }
    bool bGuide = _oChurch.vecChurch.empty();

    _oChurch.vecChurch.clear();
    SetHasChurchChange(true);
    CPlayerPtr pPlayer = GetPlayer();
    if(NULL == pPlayer)
        return;
    TTaskList* pTaskList = CTaskConfMgr::Instance().GetChurchTask(pPlayer->Level());
    if(NULL != pTaskList)
    {
        std::vector<UINT16> vecRan = *pTaskList;

        if(vecRan.size() > SParamConfig::wTaskChurchRannum)
            std::random_shuffle(vecRan.begin(),vecRan.end());

        for(size_t i = 0;i < vecRan.size() && _oChurch.vecChurch.size() < SParamConfig::wTaskChurchRannum;i++)
        {
            if(eTaskSucceed != CheckAcceptTask(vecRan[i]))
                continue;
            SChurch oChurch;
            oChurch.wTaskID = vecRan[i];
            if (bGuide && i > 0)
                oChurch.byStar = SParamConfig::byTaskChurchStar;
            else
                oChurch.byStar = CTaskMgr::RandomTaskStar(bFree);
            _oChurch.vecChurch.emplace_back(std::move(oChurch));
        }
    }
    _byVersion++;
}
#endif

void CTaskPkg::ResetState()
{
#if 0
    CRecord& rRecord = _rUser.GetRecordCollection().GetRecord(eRecord5amVarValue);
    if(!HasRecordFlag(rRecord, eRecord5amChurchTask))
    {
        _oChurch.wCount = _oChurch.wTotalCount;
        SetRecordFlag(rRecord, eRecord5amChurchTask);
        //免费刷新次
        RefreshChurchTask();
    }
#endif
}
#if 0
UINT16 CTaskPkg::GetChurchTaskDoneTimes()
{
    return _oChurch.wTotalCount - _oChurch.wCount;
}
#endif
void CTaskPkg::CheckDailyReset(bool bNotify /*= true*/)
{
#if 0
    CRecord& rRecord = _rUser.GetRecordCollection().GetRecord(eRecord5amVarValue);
    if(!HasRecordFlag(rRecord, eRecord5amDailyTask))
    {
        for(auto it = _mapID2Record.begin();it != _mapID2Record.end();it++)
        {
            STaskConfig* pCfg = CTaskConfMgr::Instance().GetTaskConfig(it->second.wTaskID);
            if(NULL == pCfg)
                continue;
            if(eTaskConfDay == pCfg->eTaskType && eTargetScene == pCfg->oTriggerTarget.eType)
            {
                it->second.wTodayFinishCount = 0;
                AcceptCommonTask(pCfg->wID, bNotify);
            }
        }

        SetRecordFlag(rRecord, eRecord5amDailyTask);
        SetHasRecChange(true);
        SetHasTaskChange(true);
    }
#endif
}

bool CTaskPkg::HasKillMonsterTask(UINT16 wMonsterID, TVecUINT16& vecTaskID)
{
    TTaskList* pTaskList = CTaskConfMgr::Instance().GetMonsterTask(wMonsterID);
    if(pTaskList != NULL && !pTaskList->empty())
    {
        vecTaskID = *pTaskList;
        return true;
    }
    return false;
}

void CTaskPkg::ForEachTask(function<void (CTask&)> func)
{
    for(auto it = _mapID2Task.begin(); it != _mapID2Task.end();)
    {
        CTaskPtr& pTask = it->second;
        ++it;
        if(func)
            func(*pTask);
    }
}
#if 0
UINT16 CTaskPkg::GetChurchTaskNum()
{
    UINT16 wChurchTaskNum = 0;
    for (auto it = _mapID2Task.begin();it != _mapID2Task.end();it++)
    {
        if (eTaskChurch == it->second->GetTaskType())
            wChurchTaskNum++;
    }

    return wChurchTaskNum;
}
bool CTaskPkg::AcceptItemTask(UINT8 byStar)
{
    CPlayerPtr pPlayer = GetPlayer();
    if(NULL == pPlayer)
        return false;
    TTaskList* pTaskList = CTaskConfMgr::Instance().GetChurchTask(pPlayer->Level());
    if(NULL != pTaskList)
    {
        std::vector<UINT16> vecRan = *pTaskList;

        if(vecRan.empty())
        {
            LOG_CRI << "ChurchTask Random Err Level:" << pPlayer->Level();
            return false;
        }
        std::random_shuffle(vecRan.begin(),vecRan.end());

        for (UINT16 wChurchTask : vecRan)
        {
            if (AcceptChurchTask(wChurchTask, byStar))
                return true;
        }
    }
    return false;
}
#endif

UINT32 CTaskPkg::GetTaskNumByType(ETaskConfType eType)
{
    UINT32 dwNum = 0;
    for(auto it = _mapID2Task.begin();it != _mapID2Task.end();it++)
    {
        CTaskPtr pTask = it->second;
        if(pTask == NULL )
        {
            continue;
        }
        const STaskConfig& rConf =  pTask->GetTaskConfig();
        if(rConf.eTaskType == eType)
        {
            dwNum += pTask->GetCurAcceptTimes();
        }
    }
    return dwNum;
}

void   CTaskPkg::GiveUpTaskByType(ETaskConfType eType)
{
    map<UINT16,UINT8> mapDrop;
    for(auto it = _mapID2Task.begin();it != _mapID2Task.end();it++)
    {
        CTaskPtr pTask = it->second;
        if(pTask == NULL )
        {
            continue;
        }
        const STaskConfig& rConf =  pTask->GetTaskConfig();
        if(rConf.eTaskType == eType)
        {
            mapDrop[it->first] = pTask->GetCurAcceptTimes();
        }
    }
    for(auto it =  mapDrop.begin();it != mapDrop.end();it++)
    {
        for(auto i = 0;i < it->second;i++)
        {
            GiveUpTask(it->first,true);
        }
    }
}

//同步环任务
void   CTaskPkg::SendCircleInfo()
{
    UINT8 byNum =  _rUser.GetVars().GetVar(ePlayerCircleTaskNum) + 1;
    UINT8 byStar =  _rUser.GetVars().GetVar(ePlayerCircleTaskStar);
    _rUser.SendPkg(g_TaskProtS.BuildPkg_SendCircleTaskInfo(byStar,byNum));
}
//尝试刷下一个环任务
void  CTaskPkg::AcceptCircleTask(bool bSendCircleInfo )
{
    CPlayerPtr  pPlayer = GetPlayer();
    if(pPlayer ==NULL)
    {
        return ;
    }
    if(!pPlayer->CheckIconIsOpen(wCircleIcon))
    {
        return ;
    }
    if(_rUser.GetVars().GetVar(ePlayerCircleTaskNum) >= SParamConfig::byCircleTaskMaxNum)
    {
        return ;
    }
    //已有环任务

    if(GetTaskNumByType(eTaskCircle) > 0)
    {
        return;
    }

    UINT16 wTaskId = 0;
    UINT8 byStar = 0;

    if(!CTaskMgr::GetCircleTask(_rUser, wTaskId,byStar))
    {
        return ;
    }
    ETaskResult  eResult = AcceptTask(wTaskId,0);
    if(eTaskSucceed !=  eResult)
    {

        LOG_CRI << "CircleTask Err : " << wTaskId << " err is " << eResult;
        return;
    }
    GetUser().GetVars().SetVar(ePlayerCircleTaskStar,byStar);
    if(bSendCircleInfo)
    {
        SendCircleInfo();
    }
}

//完成所有的环任务
ETaskResult CTaskPkg::FinishAllCircleTaskOneKey()
{

    //环功能开启
    CPlayerPtr  pPlayer = GetPlayer();
    if(pPlayer ==NULL)
    {
        return eTaskErrOther;
    }
    if(!pPlayer->CheckIconIsOpen(wCircleIcon))
    {
        return eTaskErrOther;
    }
    //环任务是否全部完成
    if(_rUser.GetVars().GetVar(ePlayerCircleTaskNum) >= SParamConfig::byCircleTaskMaxNum)
    {
        return eTaskErrOther;
    }
    //最终奖励能否放入包裹
    TVecItemGenInfo rvec ;
    if(!CTaskMgr::GetCircleFinishAward(_rUser,rvec))
    {
        return eTaskErrOther; 
    }
    if(!GetUserPack().CanAddItem(rvec))
    {
        return eTaskErrPackFull;
    }
    //计算需要仙石
    UINT8 byTimes = SParamConfig::byCircleTaskMaxNum - _rUser.GetVars().GetVar(ePlayerCircleTaskNum);
    UINT32 dwCost = SParamConfig::wCircleTaskFinishAll * byTimes;
    if(!_rUser.CanSubMoney(EMONEY_GOLD,dwCost))
    {
        return eTaskNoGold;
    }
    _rUser.SubMoney(EMONEY_GOLD,dwCost,NLogDataDefine::ItemTo_CircleOneKeyAll);
    //计算每环奖励
    TVecItemGenInfo rTaskvec ;
    for(UINT8 it = _rUser.GetVars().GetVar(ePlayerCircleTaskNum);it != SParamConfig::byCircleTaskMaxNum;it++)
    {
        TVecItemGenInfo rtempvec;
        if(CTaskMgr::GetCircleTaskAward(_rUser,5,it+1,rtempvec))
        {
            for(auto pos = rtempvec.begin();pos != rtempvec.end();pos++)
            {
                SItemGenInfo & rItem = *pos;
                bool bfind = false;
                for(auto iter = rTaskvec.begin();iter != rTaskvec.end();iter++)
                {
                    SItemGenInfo &rAllUtem = *iter;
                    if(rAllUtem.wItemID == rItem.wItemID)
                    {
                        bfind = true;
                        rAllUtem.dwCount += rItem.dwCount;
                        break;
                    }
                }
                if(!bfind)
                {
                    rTaskvec.push_back(rItem);
                }

            }
        }

    }
    _rUser.GetPack().AddItem(rTaskvec,NLogDataDefine::ItemFrom_CircleTask);
    //计算最终奖励
    _rUser.GetPack().AddItem(rvec,NLogDataDefine::ItemFrom_CircleTaskFinish);
    //同步消息
    _rUser.GetVars().SetVar(ePlayerCircleTaskNum,SParamConfig::byCircleTaskMaxNum);
    _rUser.GetVars().SetVar(ePlayerCircleTaskStar,0);
    SendCircleInfo();
    //放弃当前环任务
    GiveUpTaskByType(eTaskCircle);

    TVecINT32 vecParam;
    vecParam.push_back(1);
    pPlayer->OnEvent(eEventType_CircleTaskFinish,vecParam);
    return eTaskSucceed;
}

ETaskResult   CTaskPkg::UpdateCircleTaskStar()
{
    //环功能开启
    CPlayerPtr  pPlayer = GetPlayer();
    if(pPlayer ==NULL)
    {
        return eTaskErrOther;
    }
    if(!pPlayer->CheckIconIsOpen(wCircleIcon))
    {
        return eTaskErrOther;
    }
    //环任务是否全部完成
    if(_rUser.GetVars().GetVar(ePlayerCircleTaskNum) >= SParamConfig::byCircleTaskMaxNum)
    {
        return eTaskErrOther;
    }
    UINT8 byStar =  _rUser.GetVars().GetVar(ePlayerCircleTaskStar);
    if(byStar == 5)
    {
        return eTaskErrOther;
    }
    UINT32 dwCost = SParamConfig::wCircleTaskStarUpPrice;
    if(!_rUser.CanSubMoney(EMONEY_SILVER,dwCost))
    {
        return eTaskNoSliver;
    }
    GetUser().GetVars().SetVar(ePlayerCircleTaskStar,5);
    _rUser.SubMoney(EMONEY_SILVER,dwCost,NLogDataDefine::ItemTo_CircleUpStar);
    SendCircleInfo();

    TVecINT32 vecParam;
    vecParam.push_back(byStar);
    vecParam.push_back(1);
    pPlayer->OnEvent(eEventType_CircleTaskStarUp,vecParam);

    return eTaskSucceed;
}

void CTaskPkg::FinishAllMainTask(UINT16 wTaskId)
{
    if(wTaskId == 0)
    {
        return ;
    }
    do{
        UINT32 wCurId = 0;
        for(auto it = _mapID2Task.begin();it != _mapID2Task.end();it++)
        {
            CTaskPtr pTask = it->second;
            if(pTask == NULL )
            {
                continue;
            }
            const STaskConfig& rConf =  pTask->GetTaskConfig();
            if(rConf.eTaskType == eTaskConfMain)
            {
                wCurId = it->first;
                break;
            }
        }
        if(wCurId == 0 || wCurId == wTaskId)
        {
            break ;
        }
        SetFinishTask(wCurId);
        ETaskResult eResult = FinishTask(wCurId,0,0);
        if(eTaskSucceed != eResult)
        {
            g_TaskProtS.SendSysMsgIDNotify(eResult,_rUser);
            break;
        }
    }while(1);


}
void CTaskPkg::AcceptEveryDayTask()
{
    const TTaskList& pTaskList = CTaskConfMgr::Instance().GetEveryDayTask();
    for (auto it = pTaskList.begin();it != pTaskList.end();it++)
    {
        AcceptTask(*it,0);
    }
}

