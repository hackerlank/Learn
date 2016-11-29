#include  "YaMenTaskPkg.h"
#include  "Protocols.h"
#include  "Player.h"
#include "YaMenTaskManager.h"
#include "TaskConf.h"
#include "TaskConfMgr.h"
#include "User.h"
#include "VarDefine.h"
#include "Parameter.h"
#include "VIPMgr.h"
using namespace NVarDefine;
CYaMenTaskPkg::CYaMenTaskPkg(CPlayer &rPlayer):_rPlayer(rPlayer)
{
    _eStudyState =   NYaMenTaskProt::eCanStudy;
}
void CYaMenTaskPkg::FlushMapToInfo()
{
    //clear
#define CLEARFLUSH(N) \
    _TaskInfo.dwFlushTask##N = 0; \
    _TaskInfo.eState##N = NYaMenTaskProt::eNone;
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

void  CYaMenTaskPkg::FlushInfoToMap()
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
void CYaMenTaskPkg::Init(const SYaMenTaskInfo &rInfo)
{
    CheckStudyState(false);
    _TaskInfo = rInfo;
    FlushInfoToMap();
}

void CYaMenTaskPkg::Update2DB()
{
    string strData;
    COutArchive iar(strData);
    FlushMapToInfo();
    iar << _TaskInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(), eTypeYaMenTask, eOpUpdate, strData);
}

void CYaMenTaskPkg::AcceptTask(UINT32 dwTaskId)
{
    STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(dwTaskId);
    if(pTaskConfig == NULL)
    {
        return ;
    }
    if(pTaskConfig->eTaskType != eTaskForYaMen && pTaskConfig->eTaskType != eTaskForYaMenLevel)
    {
        return;
    }
    if(pTaskConfig->eTaskType == eTaskForYaMen)
    {
        auto it = _mapFlushTask.find(dwTaskId);
        if(it == _mapFlushTask.end())
        {
            return;
        }
        it->second = NYaMenTaskProt::eAccept;
        SYaMenTask stTask;
        stTask.dwTaskId = dwTaskId;
        stTask.eYaMenTaskState = it->second;
        _rPlayer.SendPkg(g_YaMenTaskProtS.BuildPkg_UpdateYaMenTask(stTask));
        UINT8 byTimes = GetAcceptTask();
        if(byTimes > SParamConfig::byYaMenTaskMax)
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

ETaskResult CYaMenTaskPkg::CanAcceptYaMenTask(UINT32 dwTaskId)
{
    LOG_CRI<< "_mapFlushTask is " << _mapFlushTask.size();
    STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(dwTaskId);
    if(pTaskConfig == NULL)
    {
        return eTaskNotExist;
    }
    if(pTaskConfig->eTaskType != eTaskForYaMen )
    {
        return eTaskSucceed;
    }

    //是否为推的任务列表里的任务
    EYaMenTaskState eState;
    if(!GetFlushState(dwTaskId,eState)|| eState != NYaMenTaskProt::eNone)
    {
        return  eTaskNotExist;
    }
    if(_rPlayer.GetUser().GetTaskPkg().GetTaskNumByType(eTaskForYaMen) > 0)
    {
        return eTaskYaMenFull;
    }
    //vip购买衙门任务数
    if(GetCanAccepTask() == 0)
    {
        return eTaskErrFull;
    }
    return eTaskSucceed; 
}
UINT8 CYaMenTaskPkg::GetAcceptTask()
{
    //察看今日已完成的衙门任务
    UINT8 byNum =  _rPlayer.GetUser().GetVars().GetVar(ePlayerFinishYaMenTask);
    //察看已接未完成的衙门任务
    byNum += _rPlayer.GetUser().GetTaskPkg().GetTaskNumByType(eTaskForYaMen);
    return byNum;
}
UINT8 CYaMenTaskPkg::GetCanAccepTask()
{
    UINT8 byNum = GetAcceptTask();
    if(byNum <= SParamConfig::byYaMenTaskMax)
    {
        return  SParamConfig::byYaMenTaskMax +_TaskInfo.byBuyTimes- byNum;
    }
    return _TaskInfo.byBuyTimes; 
}

void CYaMenTaskPkg::SynTaskToClient()
{
    _rPlayer.SendPkg(g_YaMenTaskProtS.BuildPkg_UpdateFinishTask(_rPlayer.GetUser().GetVars().GetVar(ePlayerFinishYaMenTask),GetCanAccepTask(),_TaskInfo.byBuyTimes,_rPlayer.GetUser().GetVars().GetVar(ePlayerBuyYaMenTask)));

}
bool CYaMenTaskPkg::GetFlushState(UINT32 dwTaskId,EYaMenTaskState &eState)
{
    auto it = _mapFlushTask.find( dwTaskId);
    if(it == _mapFlushTask.end())
    {
        return false;
    }
    eState = it ->second;
    return true;
}

void CYaMenTaskPkg::FinishTask(UINT32 dwTaskId,UINT8 byNum)
{
    STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(dwTaskId);
    if(pTaskConfig == NULL )
    {
        return ;
    }
    if(pTaskConfig->eTaskType != eTaskForYaMen && pTaskConfig->eTaskType != eTaskForYaMenLevel)
    {
        return;
    }
    if(pTaskConfig->eTaskType == eTaskForYaMen)
    {
        auto it = _mapFlushTask.find( dwTaskId);
        if(it != _mapFlushTask.end() && it->second == NYaMenTaskProt::eAccept)
        {
            it->second = NYaMenTaskProt::eFinish;
            SYaMenTask stTask;
            stTask.dwTaskId = dwTaskId;
            stTask.eYaMenTaskState = it->second;
            _rPlayer.SendPkg(g_YaMenTaskProtS.BuildPkg_UpdateYaMenTask(stTask));

        }
        _rPlayer.GetUser().GetVars().AddVar(ePlayerFinishYaMenTask,byNum);
        TVecINT32 vecParam;
        vecParam.push_back(byNum);
        const SDaily_yamentaskColorCFG * pCFg = g_CYaMenTaskManager.GetConfigByTaskID(dwTaskId);
        if(pCFg)
            vecParam.push_back(pCFg->_Color);
        else
            LOG_CRI <<"Err Task";
        for(auto i = 0; i != byNum;i++)
            _rPlayer.OnEvent(eEventType_GovernmentTaskFinish,vecParam);

        SynTaskToClient();
        //增加声望
        _TaskInfo.dwHoly += byNum;
        _rPlayer.SendPkg(g_YaMenTaskProtS.BuildPkg_UpdateYaMenRepute(_TaskInfo.dwHoly));

    }
    else
    {
        //升级
        UINT16 wLevel =  g_CYaMenTaskManager.GetReputeLvByTaskId(dwTaskId,_TaskInfo.dwHoly);
        if(wLevel <= _TaskInfo.byHolyLevel)
        {
            LOG_CRI << "TO lowLevel:";
        }
        else
        {
            _TaskInfo.byHolyLevel = wLevel;
            _rPlayer.SendPkg(g_YaMenTaskProtS.BuildPkg_UpdateYaMenReputeLevel(_TaskInfo.byHolyLevel));
            TVecINT32 vecParam;
            vecParam.push_back(wLevel);
            _rPlayer.OnEvent(eEventType_GovernmentTaskLevelUp,vecParam);

        }
    }
    Update2DB();
    CheckStudyState(true);
}

void CYaMenTaskPkg::GiveUpTask(UINT32 dwTaskId)
{
    STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(dwTaskId);
    if(pTaskConfig == NULL)
    {
        return ;
    }
    if(pTaskConfig->eTaskType != eTaskForYaMen && pTaskConfig->eTaskType != eTaskForYaMenLevel)
    {
        return;
    }
    if(pTaskConfig->eTaskType == eTaskForYaMen)
    {
        auto it = _mapFlushTask.find( dwTaskId);
        if(it != _mapFlushTask.end())
        {
            it->second = NYaMenTaskProt::eNone;
            SYaMenTask stTask;
            stTask.dwTaskId = dwTaskId;
            stTask.eYaMenTaskState = it->second;
            _rPlayer.SendPkg(g_YaMenTaskProtS.BuildPkg_UpdateYaMenTask(stTask));
            SynTaskToClient();
            Update2DB();
        }
    }
    else  
    {
        CheckStudyState();
    }

}

EYaMenTaskResult CYaMenTaskPkg::DoYaMenTaskOp(EYaMenStudyState &eState)
{
    CheckStudyState(false);
    if(_eStudyState ==  NYaMenTaskProt::eCanStudy)
    {
        //清修
        const SDaily_yamenCFG *  pCfg = g_CYaMenTaskManager.GetLevelCFGbyLevel(_TaskInfo.byHolyLevel);
        if(pCfg== NULL)
        {
            return eYaMenTaskErrOther;
        }
        UINT32 dwItem = pCfg->_Retrun;
        CPack& oPack = _rPlayer.GetUser().GetPack();
        if(!oPack.CanAddItemWithID(dwItem,1,eBindGet,0))
        {
            return eYaMenAwardPackFull;
        }
        oPack.AddItemWithID(dwItem,1,eBindGet,0,NLogDataDefine::ItemFrom_YaMenAward);
        _rPlayer.GetUser().GetVars().AddVar(ePlayerGetYaMenPExp,1);
        UINT8 byTimes = _rPlayer.GetUser().GetVars().GetVar(ePlayerGetYaMenPExp);
        _rPlayer.SendPkg(g_YaMenTaskProtS.BuildPkg_UpdateStudyAward(byTimes));
        if(GetStudyTimes() <= byTimes)
            _eStudyState = NYaMenTaskProt::eStudied;
        TVecINT32 vecParam;
        vecParam.push_back(1);
        _rPlayer.OnEvent(eEventType_GovernmentTaskPrizeGet,vecParam);;

    }
    else if(NYaMenTaskProt::eCanChallenge == _eStudyState)
    {
        //挑战
        //先将原来挑战的任务放弃
        _rPlayer.GetUser().GetTaskPkg().GiveUpTaskByType(eTaskForYaMenLevel);
        //接受新挑战
        UINT8 byNewLv =  g_CYaMenTaskManager.GetReputeLvByRepute(_TaskInfo.dwHoly);
        const SDaily_yamenCFG *pCfg = g_CYaMenTaskManager.GetLevelCFGbyLevel(byNewLv);
        if(pCfg ==NULL)
        {
            LOG_CRI << "Config ERR";
            return eYaMenTaskErrOther;
        }
        UINT16 wNewTask =  pCfg->_Task;

        ETaskResult  eResult = _rPlayer.GetUser().GetTaskPkg().AcceptTask(wNewTask,0);
        if(eTaskSucceed != eResult)
        {
            LOG_CRI << "AcceptTask ERR";
            g_TaskProtS.SendSysMsgIDNotify(eResult,_rPlayer.GetUser());
            return eYaMenTaskErrOther;

        }
        _eStudyState =  NYaMenTaskProt::eChallenging;

    }
    eState = _eStudyState; 
    return eYaMenTaskSucceed;
}

void  CYaMenTaskPkg::CheckStudyState(bool bNotice)
{
    EYaMenStudyState OldState = _eStudyState;
    do{
        UINT8 byCurLv =  _TaskInfo.byHolyLevel;
        UINT8 byNewLv =  g_CYaMenTaskManager.GetReputeLvByRepute(_TaskInfo.dwHoly);
        if(byCurLv < byNewLv)
        { 
            const SDaily_yamenCFG *pCfg = g_CYaMenTaskManager.GetLevelCFGbyLevel(byNewLv);
            if(pCfg ==NULL)
            {
                LOG_CRI << "Config ERR";
                return ;
            }
            UINT16 wNewTask =  pCfg->_Task;
            if(_rPlayer.GetUser().GetTaskPkg().FindTask(wNewTask) == NULL)
            {
                _eStudyState = NYaMenTaskProt::eCanChallenge;
                break;

            }
            else
            {
                //已接：报错
                _eStudyState = NYaMenTaskProt::eChallenging;
                break;
            }
        }
        //没有到达：
        //是否当日清修
        UINT8 byNum =  _rPlayer.GetUser().GetVars().GetVar(ePlayerGetYaMenPExp);
        if(byNum >= GetStudyTimes())
        {
            _eStudyState = NYaMenTaskProt::eStudied;
            break;
        }
        else
        {
            _eStudyState = NYaMenTaskProt::eCanStudy;
            break;

        }
    }while(0);

    if(bNotice && _eStudyState != OldState)
    {
        _rPlayer.SendPkg(g_YaMenTaskProtS.BuildPkg_UpdateStudyState(_eStudyState));
    }

}

UINT8 CYaMenTaskPkg::GetStudyTimes()
{
    UINT8 byNum =  _rPlayer.GetUser().GetVars().GetVar(ePlayerFinishYaMenTask);
    UINT8 byTasks = SParamConfig::byFinishYaMenTaskHoly;
    if(byTasks == 0)
    {
        return 0;
    }
    return byNum / byTasks;
}
EYaMenTaskResult CYaMenTaskPkg::DoFlushTask(TVecYaMenTask &vecTask,UINT8 &byFlushTimes)
{
    //看次数
    UINT8 byNum = _rPlayer.GetUser().GetVars().GetVar(ePlayerFlushYaMenTask);
    bool bCost =false;
    if(byNum >= SParamConfig::byFreeFlushYaMenTask)
    {
        bCost = true;
        //察钱  
        if(!_rPlayer.GetUser().SubMoney(EMONEY_GOLD,SParamConfig::dwFlushYaMenTaskCost,NLogDataDefine::ItemTo_YaMenFlushTask))
        {
            return eYaMenTaskLowMoney;
        }
    }

    //开始刷
    _rPlayer.GetUser().GetVars().AddVar(ePlayerFlushYaMenTask,1);
    byFlushTimes = ++byNum;
    TVecINT32 vecParam;
    vecParam.push_back(byFlushTimes);
    _rPlayer.OnEvent(eEventType_GovernmentTaskRefresh,vecParam);

    DoFlushTaskCase(false,bCost); 
    Update2DB();
    for(auto it = _mapFlushTask.begin();it != _mapFlushTask.end();it++)
    {
        SYaMenTask sTask;
        sTask.dwTaskId = it->first;
        sTask.eYaMenTaskState = it->second;
        vecTask.push_back(sTask);  

    }
    return eYaMenTaskSucceed;
}

void CYaMenTaskPkg::DoFlushTaskCase(bool bFirst,bool bCost)
{
    TVecUINT16 vecSelect;
    g_CYaMenTaskManager.GetTasksByLevel(_rPlayer,SParamConfig::byFlushYaMenTaskMax,vecSelect,bFirst,bCost);
    _mapFlushTask.clear();
    for(auto it = vecSelect.begin();it != vecSelect.end();it++)
    {
        _mapFlushTask[*it] =  NYaMenTaskProt::eNone;
        TVecINT32 vecParam;
        const SDaily_yamentaskColorCFG * pCfg = g_CYaMenTaskManager.GetConfigByTaskID(*it);
        if(pCfg)
            vecParam.push_back(pCfg->_Color);
        else
            LOG_CRI << "err Task";
        _rPlayer.OnEvent(eEventType_GovernmentTaskRefreshGet,vecParam);

    }
    LOG_CRI<< "_mapFlushTask is " << _mapFlushTask.size();
}
void CYaMenTaskPkg::SendAllInfoTask()
{
    CheckStudyState(false);
    SYaMenTaskInfoForClient sClient;
    sClient.eStudyState = _eStudyState;
    sClient.dwYaMenRepute = _TaskInfo.dwHoly;
    sClient.dwYaMenLevel = _TaskInfo.byHolyLevel;
    sClient.byFinishTask = _rPlayer.GetUser().GetVars().GetVar(ePlayerFinishYaMenTask);
    sClient.byVIPTaskTimes = _TaskInfo.byBuyTimes;
    sClient.byAcceptTaskTimes = GetCanAccepTask();
    sClient.byFlushTask = _rPlayer.GetUser().GetVars().GetVar(ePlayerFlushYaMenTask);
    sClient.byStudyAward = _rPlayer.GetUser().GetVars().GetVar(ePlayerGetYaMenPExp);
    sClient.byBuyTimesToday = _rPlayer.GetUser().GetVars().GetVar(ePlayerBuyYaMenTask);
    if(_mapFlushTask.empty())//初始免费刷一次
    {
        DoFlushTaskCase(true,false);
        Update2DB();
    }
    for(auto it = _mapFlushTask.begin();it != _mapFlushTask.end();it++)
    {
        SYaMenTask sTask;
        sTask.dwTaskId = it->first;
        sTask.eYaMenTaskState = it->second;
        sClient.vecTask.push_back(sTask);
    }
    _rPlayer.SendPkg(g_YaMenTaskProtS.BuildPkg_ReturnAllInfoTask(sClient));
}

EYaMenTaskResult CYaMenTaskPkg::DoBuyTask()
{
    //查当前次数
    SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(_rPlayer.GetUser().GetVIPLevel());
    if(pCfgVip == NULL)
    {
        return NYaMenTaskProt::eBuyTimesUpLimit;
    }
    if(_TaskInfo.byBuyTimes >= SParamConfig::byDailyYamenSave)
    {
        return NYaMenTaskProt::eYaMenSaveTimesUpLimit;
    }
    if(_rPlayer.GetUser().GetVars().GetVar(ePlayerBuyYaMenTask) >= pCfgVip->_YamenTimes)
    {
        return NYaMenTaskProt::eBuyTimesUpLimit;
    }
    //查钱
    UINT32 dwCost = SParamConfig::byDailyYamenBuy;//配置
    if(!_rPlayer.GetUser().SubMoney(EMONEY_GOLD,dwCost,NLogDataDefine::ItemTo_YaMenBuyTask))
    {
        return eYaMenTaskLowMoney;
    }
    //购买
    _TaskInfo.byBuyTimes++;
    _rPlayer.GetUser().GetVars().AddVar(ePlayerBuyYaMenTask,1);
    TVecINT32 vecParam;
    vecParam.push_back(_rPlayer.GetUser().GetVars().GetVar(ePlayerBuyYaMenTask));
    _rPlayer.OnEvent(eEventType_GovernmentTaskBuying,vecParam);

    //同步消息
    SynTaskToClient();
    //存数据库
    Update2DB();
    return NYaMenTaskProt::eYaMenTaskSucceed;
}
void  CYaMenTaskPkg::GMaddTimes(UINT8 byTimes)
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
