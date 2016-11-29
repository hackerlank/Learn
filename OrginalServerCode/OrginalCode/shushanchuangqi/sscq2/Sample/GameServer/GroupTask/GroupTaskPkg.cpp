#include  "GroupTaskPkg.h"
#include  "Protocols.h"
#include  "Player.h"
#include "GroupTaskManager.h"
#include "TaskConf.h"
#include "TaskConfMgr.h"
#include "User.h"
#include "VarDefine.h"
#include "Parameter.h"
#include "VIPMgr.h"
using namespace NVarDefine;
CGroupTaskPkg::CGroupTaskPkg(CPlayer &rPlayer):_rPlayer(rPlayer)
{
    _eStudyState =   NGroupTaskProt::eCanStudy;
}
void CGroupTaskPkg::FlushMapToInfo()
{
    //clear
#define CLEARFLUSH(N) \
    _TaskInfo.dwFlushTask##N = 0; \
    _TaskInfo.eState##N = NGroupTaskProt::eNone;
    CLEARFLUSH(1);
    CLEARFLUSH(2);
    CLEARFLUSH(3);
    CLEARFLUSH(4);
    CLEARFLUSH(5);
    UINT8 byNum =0;
    for(auto it = _mapFlushTask.begin();it != _mapFlushTask.end();it++)
    {
        byNum++;
#define SETFLUSH(N) \
        _TaskInfo.dwFlushTask##N = it->first;\
        _TaskInfo.eState##N = it->second;
        switch (byNum)
        {
            case 1:
                {
                    SETFLUSH(1);
                }
                break;
            case 2:
                {
                    SETFLUSH(2);
                }
                break;

            case 3:
                {
                    SETFLUSH(3);
                }
                break;

            case 4:
                {
                    SETFLUSH(4);
                }
                break;
            case 5:
                {
                    SETFLUSH(5);
                }
                break;
        }
    }
}

void  CGroupTaskPkg::FlushInfoToMap()
{
    _mapFlushTask.clear();
#define INSERTMAP(N) \
    if(_TaskInfo.dwFlushTask##N != 0) \
    _mapFlushTask[_TaskInfo.dwFlushTask##N] = _TaskInfo.eState##N;
    INSERTMAP(1);
    INSERTMAP(2);
    INSERTMAP(3);
    INSERTMAP(4);
    INSERTMAP(5);
}
void CGroupTaskPkg::Init(const SGroupTaskInfo &rInfo)
{
    CheckStudyState(false);
    _TaskInfo = rInfo;
    FlushInfoToMap();
}

void CGroupTaskPkg::Update2DB()
{
    string strData;
    COutArchive iar(strData);
    FlushMapToInfo();
    iar << _TaskInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(), eTypeGroupTask, eOpUpdate, strData);
}

void CGroupTaskPkg::AcceptTask(UINT32 dwTaskId)
{
    STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(dwTaskId);
    if(pTaskConfig == NULL)
    {
        return ;
    }
    if(pTaskConfig->eTaskType != eTaskForGroup && pTaskConfig->eTaskType != eTaskForGroupLevel)
    {
        return;
    }
    if(pTaskConfig->eTaskType == eTaskForGroup)
    {
        auto it = _mapFlushTask.find(dwTaskId);
        if(it == _mapFlushTask.end())
        {
            return;
        }
        it->second = NGroupTaskProt::eAccept;
        SGroupTask stTask;
        stTask.dwTaskId = dwTaskId;
        stTask.eGroupTaskState = it->second;
        _rPlayer.SendPkg(g_GroupTaskProtS.BuildPkg_UpdateGroupTask(stTask));
        UINT8 byTimes = GetAcceptTask();
        if(byTimes > SParamConfig::byShiMenTaskMax)
        {
            if(_TaskInfo.byBuyTimes > 0)
            {
                _TaskInfo.byBuyTimes--;
            }
            else
            {
                LOG_CRI << "DATA ERR";
            }
        }
        SynTaskToClient();
        Update2DB();
    }
    else 
    {
        CheckStudyState();
    }

}

ETaskResult CGroupTaskPkg::CanAcceptGroupTask(UINT32 dwTaskId)
{
    LOG_CRI<< "_mapFlushTask is " << _mapFlushTask.size();
    STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(dwTaskId);
    if(pTaskConfig == NULL)
    {
        return eTaskNotExist;
    }
    if(pTaskConfig->eTaskType != eTaskForGroup )
    {
        return eTaskSucceed;
    }

    //是否为推的任务列表里的任务
    EGroupTaskState eState;
    if(!GetFlushState(dwTaskId,eState)|| eState != NGroupTaskProt::eNone)
    {
        return  eTaskNotExist;
    }
    if(_rPlayer.GetUser().GetTaskPkg().GetTaskNumByType(eTaskForGroup) > 0)
    {
        return eTaskGroupFull;
    }
    //vip购买师门任务数
    if(GetCanAccepTask() == 0)
    {
        return eTaskErrFull;
    }
    return eTaskSucceed; 
}
UINT8 CGroupTaskPkg::GetAcceptTask()
{
    //察看今日已完成的师门任务
    UINT8 byNum =  _rPlayer.GetUser().GetVars().GetVar(ePlayerFinishGroupTask);
    //察看已接未完成的师门任务
    byNum += _rPlayer.GetUser().GetTaskPkg().GetTaskNumByType(eTaskForGroup);
    return byNum;
}
UINT8 CGroupTaskPkg::GetCanAccepTask()
{
    UINT8 byNum = GetAcceptTask();
    if(byNum <= SParamConfig::byShiMenTaskMax)
    {
        return  SParamConfig::byShiMenTaskMax +_TaskInfo.byBuyTimes- byNum;
    }
    return _TaskInfo.byBuyTimes; 
}

void CGroupTaskPkg::SynTaskToClient()
{
    _rPlayer.SendPkg(g_GroupTaskProtS.BuildPkg_UpdateFinishTask(_rPlayer.GetUser().GetVars().GetVar(ePlayerFinishGroupTask),GetCanAccepTask(),_TaskInfo.byBuyTimes,_rPlayer.GetUser().GetVars().GetVar(ePlayerBuyGroupTask)));

}
bool CGroupTaskPkg::GetFlushState(UINT32 dwTaskId,EGroupTaskState &eState)
{
    auto it = _mapFlushTask.find( dwTaskId);
    if(it == _mapFlushTask.end())
    {
        return false;
    }
    eState = it ->second;
    return true;
}

void CGroupTaskPkg::FinishTask(UINT32 dwTaskId,UINT8 byNum)
{
    STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(dwTaskId);
    if(pTaskConfig == NULL )
    {
        return ;
    }
    if(pTaskConfig->eTaskType != eTaskForGroup && pTaskConfig->eTaskType != eTaskForGroupLevel)
    {
        return;
    }
    if(pTaskConfig->eTaskType == eTaskForGroup)
    {
        auto it = _mapFlushTask.find( dwTaskId);
        if(it != _mapFlushTask.end() && it->second == NGroupTaskProt::eAccept)
        {
            it->second = NGroupTaskProt::eFinish;
            SGroupTask stTask;
            stTask.dwTaskId = dwTaskId;
            stTask.eGroupTaskState = it->second;
            _rPlayer.SendPkg(g_GroupTaskProtS.BuildPkg_UpdateGroupTask(stTask));

        }
        _rPlayer.GetUser().GetVars().AddVar(ePlayerFinishGroupTask,byNum);
        TVecINT32 vecParam;
        vecParam.push_back(byNum);
        const SDaily_shimentaskColorCFG * pCFg = g_CGroupTaskManager.GetConfigByTaskID(dwTaskId);
        if(pCFg)
            vecParam.push_back(pCFg->_Color);
        else
            LOG_CRI << "Err Task";
        for(auto i = 0;i != byNum ;i++)
            _rPlayer.OnEvent(eEventType_DivisionFinish,vecParam);;

        SynTaskToClient();
        //增加声望
        _TaskInfo.dwRepute += byNum;
        _rPlayer.SendPkg(g_GroupTaskProtS.BuildPkg_UpdateGroupRepute(_TaskInfo.dwRepute));

    }
    else
    {
        //升级
        UINT16 wLevel =  g_CGroupTaskManager.GetReputeLvByTaskId(dwTaskId,_TaskInfo.dwRepute);
        if(wLevel <= _TaskInfo.byReputeLevel)
        {
            LOG_CRI << "TO lowLevel:";
        }
        else
        {
            _TaskInfo.byReputeLevel = wLevel;
            _rPlayer.SendPkg(g_GroupTaskProtS.BuildPkg_UpdateGroupReputeLevel(_TaskInfo.byReputeLevel));
            TVecINT32 vecParam;
            vecParam.push_back(wLevel);
            _rPlayer.OnEvent(eEventType_DivisionLevelUp,vecParam);


        }
    }
    Update2DB();
    CheckStudyState(true);
}

void CGroupTaskPkg::GiveUpTask(UINT32 dwTaskId)
{
    STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(dwTaskId);
    if(pTaskConfig == NULL)
    {
        return ;
    }
    if(pTaskConfig->eTaskType != eTaskForGroup && pTaskConfig->eTaskType != eTaskForGroupLevel)
    {
        return;
    }
    if(pTaskConfig->eTaskType == eTaskForGroup)
    {
        auto it = _mapFlushTask.find( dwTaskId);
        if(it != _mapFlushTask.end())
        {
            it->second = NGroupTaskProt::eNone;
            SGroupTask stTask;
            stTask.dwTaskId = dwTaskId;
            stTask.eGroupTaskState = it->second;
            _rPlayer.SendPkg(g_GroupTaskProtS.BuildPkg_UpdateGroupTask(stTask));
            SynTaskToClient();
            Update2DB();
        }
    }
    else  
    {
        CheckStudyState();
    }

}

EGroupTaskResult CGroupTaskPkg::DoGroupTaskOp(EGroupStudyState &eState)
{
    CheckStudyState(false);
    if(_eStudyState ==  NGroupTaskProt::eCanStudy)
    {
        //清修
        const SDaily_shimenCFG *  pCfg = g_CGroupTaskManager.GetLevelCFGbyLevel(_TaskInfo.byReputeLevel);
        if(pCfg== NULL)
        {
            return eGroupTaskErrOther;
        }

        _rPlayer.GetUser().AddMoney(EMONEY_PEXP,pCfg->_Retrun,NLogDataDefine::ItemFrom_GroupTask);
        _rPlayer.GetUser().GetVars().AddVar(ePlayerGetGroupPExp,1);     
        UINT8 byTimes = _rPlayer.GetUser().GetVars().GetVar(ePlayerGetGroupPExp);
        _rPlayer.SendPkg(g_GroupTaskProtS.BuildPkg_UpdateStudyAward(byTimes));
        if(GetStudyTimes() <= byTimes)
            _eStudyState = NGroupTaskProt::eStudied;
        TVecINT32 vecParam;
        vecParam.push_back(1);
        _rPlayer.OnEvent(eEventType_DivisionPrizeGet,vecParam);;

    }
    else if(NGroupTaskProt::eCanChallenge == _eStudyState)
    {
        //挑战
        //先将原来挑战的任务放弃
        _rPlayer.GetUser().GetTaskPkg().GiveUpTaskByType(eTaskForGroupLevel);
        //接受新挑战
        UINT8 byNewLv =  g_CGroupTaskManager.GetReputeLvByRepute(_TaskInfo.dwRepute);
        const SDaily_shimenCFG *pCfg = g_CGroupTaskManager.GetLevelCFGbyLevel(byNewLv);
        if(pCfg ==NULL)
        {
            LOG_CRI << "Config ERR";
            return eGroupTaskErrOther;
        }
        UINT16 wNewTask =  pCfg->_Task;

        ETaskResult  eResult = _rPlayer.GetUser().GetTaskPkg().AcceptTask(wNewTask,0);
        if(eTaskSucceed != eResult)
        {
            LOG_CRI << "AcceptTask ERR";
            g_TaskProtS.SendSysMsgIDNotify(eResult,_rPlayer.GetUser());
            return eGroupTaskErrOther;

        }
        _eStudyState =  NGroupTaskProt::eChallenging;

    }
    eState = _eStudyState; 
    return eGroupTaskSucceed;
}

void  CGroupTaskPkg::CheckStudyState(bool bNotice)
{
    EGroupStudyState OldState = _eStudyState;
    do{
        UINT8 byCurLv =  _TaskInfo.byReputeLevel;
        UINT8 byNewLv =  g_CGroupTaskManager.GetReputeLvByRepute(_TaskInfo.dwRepute);
        if(byCurLv < byNewLv)
        { 
            const SDaily_shimenCFG *pCfg = g_CGroupTaskManager.GetLevelCFGbyLevel(byNewLv);
            if(pCfg ==NULL)
            {
                LOG_CRI << "Config ERR";
                return ;
            }
            UINT16 wNewTask =  pCfg->_Task;
            if(_rPlayer.GetUser().GetTaskPkg().FindTask(wNewTask) == NULL)
            {
                _eStudyState = NGroupTaskProt::eCanChallenge;
                break;

            }
            else
            {
                //已接：报错
                _eStudyState = NGroupTaskProt::eChallenging;
                break;
            }
        }
        //没有到达：
        //是否当日清修
        UINT8 byNum =  _rPlayer.GetUser().GetVars().GetVar(ePlayerGetGroupPExp);

        if(byNum >= GetStudyTimes())
        {
            _eStudyState = NGroupTaskProt::eStudied;
            break;
        }
        else
        {
            _eStudyState = NGroupTaskProt::eCanStudy;
            break;

        }
    }while(0);

    if(bNotice && _eStudyState != OldState)
    {
        _rPlayer.SendPkg(g_GroupTaskProtS.BuildPkg_UpdateStudyState(_eStudyState));
    }

}

UINT8 CGroupTaskPkg::GetStudyTimes()
{
    UINT8 byNum =  _rPlayer.GetUser().GetVars().GetVar(ePlayerFinishGroupTask);
    UINT8 byTasks = SParamConfig::byDailyShimenGet ;
    if(byTasks == 0)
    {
        return 0;
    }
    return byNum / byTasks;
}
EGroupTaskResult CGroupTaskPkg::DoFlushTask(TVecGroupTask &vecTask,UINT8 &byFlushTimes)
{
    //看次数
    UINT8 byNum = _rPlayer.GetUser().GetVars().GetVar(ePlayerFlushGroupTask);
    bool bCost = false;
    if(byNum >= SParamConfig::byFreeFlushShiMenTask)
    {
        bCost = true;
        //察钱
        if(!_rPlayer.GetUser().SubMoney(EMONEY_GOLD,SParamConfig::dwFlushShiMenTaskCost,NLogDataDefine::ItemTo_FlushTask))
        {
            return eGroupTaskLowMoney;
        }
    }

    //开始刷
    _rPlayer.GetUser().GetVars().AddVar(ePlayerFlushGroupTask,1);
    byFlushTimes = ++byNum;
    TVecINT32 vecParam;
    vecParam.push_back(byFlushTimes);
    _rPlayer.OnEvent(eEventType_DivisionRefresh,vecParam);

    DoFlushTaskCase(false,bCost); 
    Update2DB();
    for(auto it = _mapFlushTask.begin();it != _mapFlushTask.end();it++)
    {
        SGroupTask sTask;
        sTask.dwTaskId = it->first;
        sTask.eGroupTaskState = it->second;
        vecTask.push_back(sTask);
    }
    return eGroupTaskSucceed;
}

void CGroupTaskPkg::DoFlushTaskCase(bool bFirst,bool bCost)
{
    TVecUINT16 vecSelect;
    g_CGroupTaskManager.GetTasksByLevel(_rPlayer,SParamConfig::byFlushShiMenTaskMax,vecSelect,bFirst,bCost);
    _mapFlushTask.clear();
    for(auto it = vecSelect.begin();it != vecSelect.end();it++)
    {
        _mapFlushTask[*it] =  NGroupTaskProt::eNone;
        TVecINT32 vecParam;
        const SDaily_shimentaskColorCFG * pCfg = g_CGroupTaskManager.GetConfigByTaskID(*it);
        if(pCfg)
            vecParam.push_back(pCfg->_Color);
        else
            LOG_CRI << "err Task";
        _rPlayer.OnEvent(eEventType_DivisionRefreshGet,vecParam);

    }
    LOG_CRI<< "_mapFlushTask is " << _mapFlushTask.size();
}
void CGroupTaskPkg::SendAllInfoTask()
{
    CheckStudyState(false);
    SGroupTaskInfoForClient sClient;
    sClient.eStudyState = _eStudyState;
    sClient.dwGroupRepute = _TaskInfo.dwRepute;
    sClient.dwGroupLevel = _TaskInfo.byReputeLevel;
    sClient.byFinishTask = _rPlayer.GetUser().GetVars().GetVar(ePlayerFinishGroupTask);
    sClient.byVIPTaskTimes = _TaskInfo.byBuyTimes;
    sClient.byAcceptTaskTimes = GetCanAccepTask();
    sClient.byFlushTask = _rPlayer.GetUser().GetVars().GetVar(ePlayerFlushGroupTask);
    sClient.byStudyAward = _rPlayer.GetUser().GetVars().GetVar(ePlayerGetGroupPExp);
    sClient.byBuyTimesToday = _rPlayer.GetUser().GetVars().GetVar(ePlayerBuyGroupTask);
    if(_mapFlushTask.empty())//初始免费刷一次
    {
        DoFlushTaskCase(true,false);
        Update2DB();
    }
    for(auto it = _mapFlushTask.begin();it != _mapFlushTask.end();it++)
    {
        SGroupTask sTask;
        sTask.dwTaskId = it->first;
        sTask.eGroupTaskState = it->second;
        sClient.vecTask.push_back(sTask);
    }
    _rPlayer.SendPkg(g_GroupTaskProtS.BuildPkg_ReturnAllInfoTask(sClient));
}

EGroupTaskResult CGroupTaskPkg::DoBuyTask()
{
    //查当前次数
    SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(_rPlayer.GetUser().GetVIPLevel());
    if(pCfgVip == NULL)
    {
        return NGroupTaskProt::eBuyTimesUpLimit;
    }
    if(_rPlayer.GetUser().GetVars().GetVar(ePlayerBuyGroupTask) >= pCfgVip->_ShimenTimes)
    {
        return NGroupTaskProt::eBuyTimesUpLimit;
    }

    if(_TaskInfo.byBuyTimes >= SParamConfig::byDailyShimenSave)
    {
        return NGroupTaskProt::eGroupSaveTimesUpLimit;
    }
    //查钱
    UINT32 dwCost = SParamConfig::byDailyShimenBuy;//配置
    if(!_rPlayer.GetUser().SubMoney(EMONEY_GOLD,dwCost,NLogDataDefine::ItemTo_BuyTask))
    {
        return eGroupTaskLowMoney;
    }
    //购买
    _TaskInfo.byBuyTimes++;
    _rPlayer.GetUser().GetVars().AddVar(ePlayerBuyGroupTask,1);
    TVecINT32 vecParam;
    vecParam.push_back(_rPlayer.GetUser().GetVars().GetVar(ePlayerBuyGroupTask));
    _rPlayer.OnEvent(eEventType_DivisionBuying,vecParam);
    //同步消息
    SynTaskToClient();
    //存数据库
    Update2DB();
    return NGroupTaskProt::eGroupTaskSucceed;
}

void  CGroupTaskPkg::GMaddTimes(UINT8 byTimes)
{
    _TaskInfo.byBuyTimes += byTimes;
    //同步消息
    if(_rPlayer.GetUser().GetUserState() == eUserInGame)
    {
        SynTaskToClient();
    }
    //存数据库
    Update2DB();

}
