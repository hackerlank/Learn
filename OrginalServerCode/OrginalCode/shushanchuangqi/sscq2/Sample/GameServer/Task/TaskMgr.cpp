#include "stdafx.h"
#include "TaskMgr.h"
#include "TaskConfMgr.h"
//#include "ScriptMgr.h"
#include "NPC.h"
#include "User.h"
#include "Parameter.h"
#include "Random.h"
#include "CircleTaskCFG.h"
#include "CircleTaskNumCFG.h"
#include "Tokenizer.h"
#include "VIPMgr.h"
//UINT32 CTaskMgr::_dwStarWeight = 0;
//UINT32 CTaskMgr::_dwStarGoldWeight = 0;
map<UINT16, STaskScript> CTaskMgr::_mapID2TaskScript;
//map<UINT8, SStartaskCFG> CTaskMgr::_mapStarTaskCfg;
UINT64 CTaskMgr::_qwVersion = VERSION_INIT;
map<UINT8,TVecUINT16> CTaskMgr::_mapCircleStar;
map<UINT8,TVecUINT16> CTaskMgr::_mapCircleTask;
map<UINT8,TVecItemGenInfo> CTaskMgr::_mapCircleTaskAward;
map<UINT8,TVecItemGenInfo> CTaskMgr::_mapCircleFinishAward;
map<UINT8,UINT8> CTaskMgr::_mapCircleLevelID;
map<UINT8,UINT16> CTaskMgr::_mapCircleAddNum;



bool CTaskMgr::Init()
{
    return LoadConfig();
}

bool CTaskMgr::LoadConfig(bool bReload /* =  false */)
{
    string strPath = Config._strConfigDir + "Conf/Task";
    if(!CTaskConfMgr::Instance().LoadTaskDirectory(strPath))
    {
        LOG_RAW << CTaskConfMgr::Instance().GetLogStream().str();
        return false;
    }

    if(bReload)
        ++ _qwVersion;
    if(bReload)
    {
        _mapCircleStar.clear();
        _mapCircleTask.clear();
        _mapCircleTaskAward.clear();
        _mapCircleFinishAward.clear();
        _mapCircleLevelID.clear();
        _mapCircleAddNum.clear();
    }
    string strCirclePath = Config._strConfigDir +"Conf/Table/CircleTask.xml";
    CCircleTaskLoader oCircleLoader;
    if(!oCircleLoader.LoadData(strCirclePath))
    {
        LOG_CRI << "CanNotfind " <<strCirclePath;
        return false;
    }
    for(size_t it = 0 ; it != oCircleLoader._vecData.size();it++)
    {
        SCircleTaskCFG* pConfig = oCircleLoader._vecData[it];
        buf::Tokenizer tkRateStar(pConfig->_Chance_Award,'|');
        TVecUINT16 vecStar;
        for(size_t i = 0; i < tkRateStar.size() ;i++)
        {
            UINT16 wRate = atoi(tkRateStar[i].c_str());
            vecStar.push_back(wRate);
        }

        if(!_mapCircleStar.insert(make_pair(static_cast<UINT8>(pConfig->_Level),vecStar)).second)
        {
            LOG_CRI << "Repeat Level :" << strCirclePath;
            return false;
        }
        TVecUINT16 vecTask;
        buf::Tokenizer tkRateTask(pConfig->_Task_ID,';'); 
        for(size_t i = 0; i < tkRateTask.size() ;i++)
        {
            UINT16 wTask = atoi(tkRateTask[i].c_str());
            vecTask.push_back(wTask);
        }

        if(!_mapCircleTask.insert(make_pair(static_cast<UINT8>(pConfig->_Level),vecTask)).second)
        {
            LOG_CRI << "Repeat Level :" << strCirclePath;
            return false;
        }
        TVecItemGenInfo rvecTaskAward;
        buf::Tokenizer tkTaskAward(pConfig->_Award,'|'); 
        for(size_t i = 0; i != tkTaskAward.size();i++)
        {
            buf::Tokenizer tkSubTaskAward(tkTaskAward[i].c_str(),','); 
            if(tkSubTaskAward.size() < 2)
            {
                LOG_CRI << "Task Award size < 2 :" << strCirclePath; 
            }
            SItemGenInfo sInfo;
            sInfo.wItemID = atoi(tkSubTaskAward[0].c_str()); 
            sInfo.dwCount = atoi(tkSubTaskAward[1].c_str());
            rvecTaskAward.push_back(sInfo);
        }
        if(!_mapCircleTaskAward.insert(make_pair(static_cast<UINT8>(pConfig->_Level),rvecTaskAward)).second)
        {
            LOG_CRI << "Repeat Level :" << strCirclePath;
            return false;
        }
        TVecItemGenInfo rvecFinishAward;
        buf::Tokenizer tkFinishAward(pConfig->_FinishAward,'|'); 
        for(size_t i = 0; i != tkFinishAward.size();i++)
        {
            buf::Tokenizer tkSubFinishAward(tkFinishAward[i].c_str(),','); 
            if(tkSubFinishAward.size() < 2)
            {
                LOG_CRI << "Finish Award size < 2 :" << strCirclePath; 
            }
            SItemGenInfo sInfo;
            sInfo.wItemID = atoi(tkSubFinishAward[0].c_str()); 
            sInfo.dwCount = atoi(tkSubFinishAward[1].c_str());
            rvecFinishAward.push_back(sInfo);
        }
        if(!_mapCircleFinishAward.insert(make_pair(static_cast<UINT8>(pConfig->_Level),rvecFinishAward)).second)
        {
            LOG_CRI << "Repeat Level :" << strCirclePath;
            return false;
        }
        if(! _mapCircleLevelID.insert(make_pair(static_cast<UINT8>(pConfig->_Level_max),static_cast<UINT8>(pConfig->_Level))).second)
        {
            LOG_CRI << "Repeat Max Level :" << strCirclePath;
            return false;
        }
    }

    string strCircleNumPath = Config._strConfigDir +"Conf/Table/CircleTaskNum.xml";
    CCircleTaskNumLoader oCircleNumLoader;
    if(!oCircleNumLoader.LoadData(strCircleNumPath))
    {
        LOG_CRI << "CanNotfind " <<strCircleNumPath;
        return false;
    }
    for(size_t it = 0 ; it != oCircleNumLoader._vecData.size();it++)
    {
        SCircleTaskNumCFG* pConfig = oCircleNumLoader._vecData[it];

        if(! _mapCircleAddNum.insert(make_pair(pConfig->_NumId,pConfig->_AdditionRate)).second)
        {
            LOG_CRI << "Repeat Num :" << strCircleNumPath;
            return false;
        }

    }

    return true;
}

bool CTaskMgr::ReloadConfig(const string& rTaskName,bool bReload /* = true */)
{
    string strPath = Config._strConfigDir + "Conf/Task/";
    if(!CTaskConfMgr::Instance().LoadTaskFile(strPath,rTaskName))
    {
        LOG_RAW << CTaskConfMgr::Instance().GetLogStream().str();
        return false;
    }

    if(bReload)
        ++ _qwVersion;
    return true;
}

void CTaskMgr::ClearTaskScript()
{
    _mapID2TaskScript.clear();

}

STaskScript* CTaskMgr::GetTaskScript(UINT16 wTaskID)
{
    auto it = _mapID2TaskScript.find(wTaskID);
    if(it == _mapID2TaskScript.end())
    {
        STaskScript sScript;
        sScript._bHasCanAcceptTask = Config.GetScript().HasCanAcceptTaskFunction(wTaskID);
        sScript._bHasAcceptTask = Config.GetScript().HasOnAcceptTaskFunction(wTaskID);
        sScript._bHasCanFinishTask = Config.GetScript().HasCanFinishTaskFunction(wTaskID);
        sScript._bHasFinishTask = Config.GetScript().HasOnFinishTaskFunction(wTaskID);
        sScript._bHasGiveUpTask = Config.GetScript().HasOnGiveUpTaskFunction(wTaskID);
        sScript._bHasDoCaseForDgn = Config.GetScript().HasDoCaseForDgnFunction(wTaskID);
        _mapID2TaskScript[wTaskID] = sScript;
        return &(_mapID2TaskScript[wTaskID]);
    }
    return &it->second;
}
bool CTaskMgr::GetNpcAcceptTaskMsg(CNpc& rNpc, CUser& rUser, string& strMsg)
{
    static char szBuffer[1024];

    SNpcTask* pNpcTask = CTaskConfMgr::Instance().GetNpcTask(rNpc.GetNpcID());
    if(pNpcTask == NULL || pNpcTask->vecAcceptTask.empty())
        return false;

    for(size_t i = 0; i < pNpcTask->vecAcceptTask.size(); ++i)
    {
        UINT16 wTaskID = pNpcTask->vecAcceptTask[i];
        ETaskResult eResult = rUser.GetTaskPkg().CheckAcceptTask(wTaskID);
        if(eResult != eTaskSucceed)
        {
            LOG_INF << "ERR For: " << wTaskID <<"ERR  IS " << eResult;
            continue;
        }
        STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(wTaskID);
        if(pTaskConfig != NULL)
        {
            sprintf_s(szBuffer, "[1#TASK:%u#%s]", wTaskID, pTaskConfig->strName.c_str());
            strMsg = strMsg + szBuffer;
        }
    }
    return true;
} 

bool CTaskMgr::FinishTaskTalk(CNpc& rNpc, CUser& rUser, UINT16 wTask)
{
    SNpcTask* pNpcTask = CTaskConfMgr::Instance().GetNpcTask(rNpc.GetNpcID());
    if(pNpcTask == NULL || pNpcTask->mapTask2Talk.empty())
        return false;
    for(auto it = pNpcTask->mapTask2Talk.begin();it != pNpcTask->mapTask2Talk.end();it++)
    {
        UINT16 wTaskID = it->first;
        if(wTaskID != wTask)
        {
            continue;
        }
        CTaskPtr pTask = rUser.GetTaskPkg().FindTask(wTaskID);
        if(pTask != NULL && (pTask->GetTaskConfig().dwContentType & eContentTalk) != 0 && pTask->CanTalkWithNpc(rNpc.GetNpcID()))
        {
            rUser.GetTaskPkg().OnNpcTalk(rNpc.GetNpcID(), wTaskID);
            return true;
        };

    }
    return false;
}

bool CTaskMgr::GetNpcTalkTaskMsg(CNpc& rNpc, CUser& rUser, string& strMsg)
{
    static char szBuffer[1024];

    SNpcTask* pNpcTask = CTaskConfMgr::Instance().GetNpcTask(rNpc.GetNpcID());
    if(pNpcTask == NULL || pNpcTask->mapTask2Talk.empty())
        return true;

    std::vector<CTaskPtr> vecTalkTask;
    for(auto it = pNpcTask->mapTask2Talk.begin();it != pNpcTask->mapTask2Talk.end();it++)
    {
        UINT16 wTaskID = it->first;
        CTaskPtr pTask = rUser.GetTaskPkg().FindTask(wTaskID);
        if(pTask != NULL && (pTask->GetTaskConfig().dwContentType & eContentTalk) != 0 && pTask->CanTalkWithNpc(rNpc.GetNpcID()))
            vecTalkTask.emplace_back(pTask);
    }

    if(!vecTalkTask.empty())
    {
        for(size_t  i = 0;i < vecTalkTask.size();i++)
        {
            CTaskPtr& rpTask = vecTalkTask[i];
            sprintf_s(szBuffer, "[1#TALK:TALK,%u#%s]", rpTask->GetTaskID(), rpTask->GetTaskConfig().strName.c_str());
            strMsg = strMsg + szBuffer;
        }

    }

    return true;
}
bool CTaskMgr::IsDummyMonster(UINT16 wMonsterID)
{
    TTaskList* pTaskList = CTaskConfMgr::Instance().GetMonsterTask(wMonsterID);
    if(pTaskList == NULL)
        return false;
    for(UINT16 wTaskID : *pTaskList)
    {
        STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(wTaskID);
        if(pTaskConfig != NULL)
        {
            for(auto& rMonsterKill : pTaskConfig->vecMonsterKill)
            {
                if(rMonsterKill.bFake)
                    return true;
            }
        }
    }
    return false;
}


STaskConfig* CTaskMgr::GetTaskConfig(UINT16 wTaskID)
{
    STaskConfig* pTaskConfig = CTaskConfMgr::Instance().GetTaskConfig(wTaskID);
    if(pTaskConfig == NULL)
        return NULL;
    return pTaskConfig;
}

bool CTaskMgr::GetCircleTask(CUser& rUser,UINT16& wTaskId,UINT8 &byStar)
{
    UINT8 byID = GetCircleIdByLevel(rUser.GetLevel());
    if(byID == 0)
    {
        return false;
    }
    auto it = _mapCircleStar.find(byID);
    if(it == _mapCircleStar.end())
    {
        return false;
    }
    if(it->second.empty())
    {
        return false;
    }

    byStar = 0;
    const SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(rUser.GetVIPLevel());
    if(pCfgVip && pCfgVip->_CircleTaskMaxStar > 0) 
    {
        byStar = 5;
    }
    else
    {
        UINT16 wRate = CRandom::RandInt(0,10000);
        for (UINT8 byPos = 0;byPos != it->second.size();byPos++)
        {
            if(wRate >= it->second[byPos])
            {
                byStar = byPos+1;
                break;
            }
            else
            {
                wRate -= it->second[byPos];
            }
        }
    }
    if(byStar == 0)
    {
        return false;
    }
    auto iter = _mapCircleTask.find(byID);
    if(iter == _mapCircleTask.end())
    {
        return false;
    }
    if(iter->second.empty())
    {
        return false;
    }

    UINT32 dwRandom = CRandom::RandInt(0,iter->second.size()-1);
    wTaskId = iter->second[dwRandom];

    LOG_INF<<"roleID:"<<rUser.GetRoleID()<<" GetCircleTask:"<<dwRandom<<" size:"<<iter->second.size()<<" wTaskId:"<<wTaskId<<" level:"<<rUser.GetLevel();

    return true;
}

//获取单个环任务奖励
bool CTaskMgr::GetCircleTaskAward(CUser& rUser,UINT8 byStar,UINT8 byNum,TVecItemGenInfo &rvec)
{
    UINT8 byID = GetCircleIdByLevel(rUser.GetLevel());
    if(byID == 0)
    {
        return false;
    }
    auto it = _mapCircleTaskAward.find(byID);
    if(it == _mapCircleTaskAward.end())
    {
        return false;
    }
    rvec = it->second;
    UINT16 wNumAdd = 0;
    auto iter = _mapCircleAddNum.find(byNum);
    if(iter != _mapCircleAddNum.end())
    {
        wNumAdd = iter->second;
    }
    UINT16 wStarAdd = 0;
    switch (byStar)
    {
        case 1:
            {
                wStarAdd =  SParamConfig::wCircleTaskStar1Rate;
            }
            break;
        case 2:
            {
                wStarAdd =  SParamConfig::wCircleTaskStar2Rate; 
            }
            break;
        case 3:
            {
                wStarAdd =  SParamConfig::wCircleTaskStar3Rate; 
            }
            break;
        case 4:
            {
                wStarAdd =  SParamConfig::wCircleTaskStar4Rate; 
            }
            break;
        case 5:
            {
                wStarAdd =  SParamConfig::wCircleTaskStar5Rate; 
            }
            break;
        default:
            break;
    }
    if(wStarAdd+wNumAdd > 0)
    {
        for(auto pos = rvec.begin();pos != rvec.end();pos++)
        {
            SItemGenInfo &rItem = *pos;
            rItem.dwCount = rItem.dwCount *(float(wStarAdd+wNumAdd)/10000 +float(1));
        }
    }

    return true;

}

//获取完成所有环任务奖励
bool CTaskMgr::GetCircleFinishAward(CUser& rUser,TVecItemGenInfo &rvec)
{
    UINT8 byID = GetCircleIdByLevel(rUser.GetLevel());
    if(byID == 0)
    {
        return false;
    }
    auto it = _mapCircleFinishAward.find(byID);
    if(it == _mapCircleFinishAward.end())
    {
        return false;
    }
    rvec = it->second;
    return true;

}

UINT8 CTaskMgr::GetCircleIdByLevel(UINT8 byLevel)
{
    auto it = _mapCircleLevelID.lower_bound(byLevel);
    if(it == _mapCircleLevelID.end())
    {
        return 0;
    }
    return it->second;

}

