#include "GroupTaskManager.h"
#include "Tokenizer.h"
#include "Random.h"
#include "Player.h"
CGroupTaskManager g_CGroupTaskManager;
bool CGroupTaskManager::Init()
{
    if(!LoadConfig())
        return false;
    if(!LoadLevel())
        return false;
    return LoadColor();

}

bool CGroupTaskManager::ReLoadConfig(const string& strFile)
{
    if("Daily_shimentask.xml" == strFile)
    {
        if(!LoadConfig())
            return false;
    }
    else if("Daily_shimen.xml" == strFile)
    {
        if(!LoadLevel())
            return false;
    }
    else if("Daily_shimentaskColor.xml" == strFile)
    {
        if(!LoadColor())
            return false;
    }
    return true;
}

void CGroupTaskManager::GetTasksByLevel(CPlayer &rPlayer,UINT8 byNum,vector<UINT16>& vecTask,bool bFirst,bool bCost)
{
    UINT16 wLevel = rPlayer.GetLevel();
    if(byNum == 0)
    {
        return ;
    }
    const SDaily_shimentaskCFGEx *pConfig = NULL;
    for(size_t it = 0 ;it != _vecCroupTask.size();it++)
    {
        SDaily_shimentaskCFGEx& rCfg = _vecCroupTask[it];
        if(wLevel <= rCfg._Level_max)
        {
            pConfig = &rCfg;
            break;
        }
    }
    if(pConfig == NULL && _vecCroupTask.size() != 0)
    {
        pConfig = &(_vecCroupTask[_vecCroupTask.size()-1]);
    }
    if(pConfig != NULL)
    {
        SDaily_shimentaskCFGEx tepCfg = *pConfig;
        CheckRepeatTask(rPlayer,tepCfg,bCost);
        bool bDoFirst = bFirst;
        vector<SDaily_shimentaskCFGEx::RateTask> * pTaskVec = NULL;
        if(!bCost)
        {
            pTaskVec = &(tepCfg.vecRateTask);

        }
        else
        {
            pTaskVec = &(tepCfg.vecRateTaskCost);
        }
        vector<SDaily_shimentaskCFGEx::RateTask> &rvecRateTask = *pTaskVec;
        while(vecTask.size() != byNum && !rvecRateTask.empty() )
        {
            UINT16 wRate = CRandom::RandInt(0,10000);
            auto  i = rvecRateTask.size();
            if(bDoFirst)
            {
                bDoFirst = false;
                i = 3;
            }
            else
            {
                LOG_INF << "Rate is " << wRate;
                for(i = 0; i< rvecRateTask.size() ;i++)
                {
                    if(wRate >= rvecRateTask[i].wRate)
                    {
                        wRate -= rvecRateTask[i].wRate;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            if(i == rvecRateTask.size())
            {
                i = rvecRateTask.size() - 1;
            }
            TVecUINT16 &rVecTask = rvecRateTask[i].vecTask;
            UINT16 wSize = rVecTask.size();
            if(wSize > 0)
            {
                UINT16 wTaskRate = CRandom::RandInt(0,wSize-1);
                vecTask.push_back(rVecTask[wTaskRate]);
                rVecTask.erase(rVecTask.begin()+wTaskRate);
                if(rVecTask.empty())
                {
                    ResetRateMap(tepCfg,bCost);
                }
            }
        }

    }
}

const SDaily_shimenCFG * CGroupTaskManager::GetLevelCFGbyLevel(UINT16 wLevel)//获得师门等级配 
{
    auto it = _mapGroupLevel.find(wLevel);
    if(it == _mapGroupLevel.end())
    {
        return NULL;
    }
    return &(it->second);

}

UINT16 CGroupTaskManager::GetReputeLvByRepute(UINT32 dwRepute)
{
    UINT16 wLevel = 0;
    for(auto it = _mapGroupLevel.begin();it != _mapGroupLevel.end();it++)
    {
        SDaily_shimenCFG &rCfg = it->second;
        if(dwRepute >= rCfg._Cost)
        {
            wLevel = it->first;
        }
        else
        {
            break;
        }

    }
    return wLevel;
}

UINT16 CGroupTaskManager::GetReputeLvByTaskId(UINT32 wTaskId,UINT32 dwRepute)
{
    UINT16 wLevel = 0;
    for(auto it = _mapGroupLevel.begin();it != _mapGroupLevel.end();it++)
    {
        SDaily_shimenCFG &rCfg = it->second;
        if(dwRepute >= rCfg._Cost)
        {
            if(rCfg._Task == wTaskId)
            {
                wLevel = it->first;
            }
        }
        else
        {
            break;
        }

    }
    if(wLevel== 0)
    {
        LOG_CRI << "ERR Levelk";
    }
    return wLevel;
}
const SDaily_shimentaskColorCFG *CGroupTaskManager::GetConfigByTaskID(UINT16 wTaskID)
{
    auto it = _mapColor.find(wTaskID);
    if(it != _mapColor.end())
    {
        return &(it->second);
    }
    return NULL;
}


void CGroupTaskManager::CheckRepeatTask(CPlayer &rPlayer,SDaily_shimentaskCFGEx &tepCfg,bool bCost)
{
    if(Config.CheckTaskCanRepeat(eTaskForGroup))
        return ;

    vector<SDaily_shimentaskCFGEx::RateTask> *pVec = NULL;
    if(!bCost)
    {
        pVec = &(tepCfg.vecRateTask);
    }
    else
    {
        pVec =  &(tepCfg.vecRateTaskCost);
    }
    vector<SDaily_shimentaskCFGEx::RateTask>& rvecRateTask = *pVec;
    for(auto it = rvecRateTask.begin();it != rvecRateTask.end();it++)
    {

        TVecUINT16 &rVec = (*it).vecTask;
        for(auto iter = rVec.begin();iter != rVec.end();)
        {
            if(rPlayer.GetUser().GetTaskPkg().FindTask(*iter) != NULL)
            {
                iter = rVec.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }
    ResetRateMap(tepCfg,bCost);
}


void  CGroupTaskManager::ResetRateMap(SDaily_shimentaskCFGEx &tepCfg,bool bCost)
{
    if(Config.CheckTaskCanRepeat(eTaskForGroup))
        return ;
    vector<SDaily_shimentaskCFGEx::RateTask> *pvecRateTask = NULL;
    if(!bCost)
    {
        pvecRateTask = &(tepCfg.vecRateTask);
    }
    else
    {
        pvecRateTask = &(tepCfg.vecRateTaskCost);
    }
    vector<SDaily_shimentaskCFGEx::RateTask> &vecRateTask = *pvecRateTask;
    //先查出空位
    UINT16 wTotalRate = 0;
    for(auto it = vecRateTask.begin();it != vecRateTask.end();)
    {

        TVecUINT16 &rVec = (*it).vecTask;
        if(rVec.empty())
        {
            wTotalRate += (*it).wRate;
            it = vecRateTask.erase(it);
        }
        else
        {
            ++it;
        }
    }
    if(vecRateTask.empty()|| wTotalRate == 0)
    {
        return ;
    }
    UINT16 wUseRate = 0;
    for(auto it = vecRateTask.begin();it != vecRateTask.end();it++)
    {
        UINT16 wAddRate = wTotalRate *((*it).wRate)/(10000 - wTotalRate);
        (*it).wRate += wAddRate;
        wUseRate += wAddRate;
    }
    if(wTotalRate > wUseRate)
    {
        (*(vecRateTask.begin())).wRate += wTotalRate -wUseRate;
    }

}

bool CGroupTaskManager::LoadConfig()
{
    _vecCroupTask.clear();
    CDaily_shimentaskLoader oTaskLoader;
    string strPath = Config._strConfigDir + "Conf/Table/Daily_shimentask.xml";
    if(!oTaskLoader.LoadData(strPath))
    {
        LOG_CRI << "Load " << strPath << "ERR";
        return false;
    }
    for(auto iter = oTaskLoader._vecData.begin(); iter != oTaskLoader._vecData.end();iter++)
    {
        SDaily_shimentaskCFGEx cFg(*(*iter));
        buf::Tokenizer tkRate(cFg._Chance_Award,'|');
        UINT16 wCount = 0;
        for(size_t i = 0; i < tkRate.size() ;i++)
        {
            SDaily_shimentaskCFGEx::RateTask tepRateTask;
            UINT16 wRate = atoi(tkRate[i].c_str());
            tepRateTask.wRate = wRate;
            cFg.vecRateTask.push_back(tepRateTask);
            wCount+= wRate;
        }
        if(wCount != 10000 || tkRate.size() != 5)
        {
            LOG_CRI << "Load Rate" << strPath << "ERR"; 
            return false;
        }
        buf::Tokenizer tkRateCost(cFg._Chance_Award_Gold,'|');
        wCount = 0;
        for(size_t i = 0; i < tkRateCost.size() ;i++)
        {
            SDaily_shimentaskCFGEx::RateTask tepRateTask;
            UINT16 wRate = atoi(tkRateCost[i].c_str());
            tepRateTask.wRate = wRate;
            cFg.vecRateTaskCost.push_back(tepRateTask);
            wCount+= wRate;
        }
        if(wCount != 10000 || tkRateCost.size() != 5)
        {
            LOG_CRI << "Load CostRate" << strPath << "ERR"; 
            return false;
        }
        buf::Tokenizer tkTask1(cFg._Task_1,';');
        TVecUINT16 &vecTask1 = cFg.vecRateTask[0].vecTask;
        for(size_t i = 0; i < tkTask1.size() ;i++)
        {

            UINT16 wTask = atoi(tkTask1[i].c_str());
            vecTask1.push_back(wTask);
        }
        if(vecTask1.empty())
        {
            LOG_CRI << "Load Task" << strPath << "ERR";
            return false;
        }
        cFg.vecRateTaskCost[0].vecTask = vecTask1;
        buf::Tokenizer tkTask2(cFg._Task_2,';');
        TVecUINT16 &vecTask2 = cFg.vecRateTask[1].vecTask;
        for(size_t i = 0; i < tkTask2.size() ;i++)
        {

            UINT16 wTask = atoi(tkTask2[i].c_str());
            vecTask2.push_back(wTask);
        }
        if(vecTask2.empty())
        {
            LOG_CRI << "Load Task" << strPath << "ERR";
            return false;
        }
        cFg.vecRateTaskCost[1].vecTask = vecTask2;
        buf::Tokenizer tkTask3(cFg._Task_3,';');
        TVecUINT16 &vecTask3 = cFg.vecRateTask[2].vecTask;
        for(size_t i = 0; i < tkTask3.size() ;i++)
        {

            UINT16 wTask = atoi(tkTask3[i].c_str());
            vecTask3.push_back(wTask);
        }
        if(vecTask3.empty())
        {
            LOG_CRI << "Load Task" << strPath << "ERR";
            return false;
        }
        cFg.vecRateTaskCost[2].vecTask = vecTask3;
        buf::Tokenizer tkTask4(cFg._Task_4,';');
        TVecUINT16 &vecTask4 = cFg.vecRateTask[3].vecTask;
        for(size_t i = 0; i < tkTask4.size() ;i++)
        {

            UINT16 wTask = atoi(tkTask4[i].c_str());
            vecTask4.push_back(wTask);
        }
        if(vecTask4.empty())
        {
            LOG_CRI << "Load Task" << strPath << "ERR";
            return false;
        }
        cFg.vecRateTaskCost[3].vecTask = vecTask4;    
        buf::Tokenizer tkTask5(cFg._Task_5,';');
        TVecUINT16& vecTask5 = cFg.vecRateTask[4].vecTask;
        for(size_t i = 0; i < tkTask5.size() ;i++)
        {

            UINT16 wTask = atoi(tkTask5[i].c_str());
            vecTask5.push_back(wTask);
        }
        if(vecTask5.empty())
        {
            LOG_CRI << "Load Task" << strPath << "ERR";
            return false;
        }
        cFg.vecRateTaskCost[4].vecTask = vecTask5; 
        _vecCroupTask.push_back(cFg);
    }
    return true;

}
bool CGroupTaskManager::LoadLevel()
{        
    _mapGroupLevel.clear();
    CDaily_shimenLoader oLoader;
    string strPath = Config._strConfigDir + "Conf/Table/Daily_shimen.xml";
    if(!oLoader.LoadData((strPath)))
    {
        LOG_CRI << "Load " << strPath << "ERR";   
        return false;
    }
    for(auto iter = oLoader._vecData.begin(); iter != oLoader._vecData.end();iter++)
    {
        SDaily_shimenCFG & Cfg = *(*iter);

        if(!_mapGroupLevel.insert(make_pair(Cfg._Level,Cfg)).second)
        {
            LOG_CRI << "Dubble Level " << Cfg._Level << "ERR";
            return false;
        }

    }
    return true;

}

bool CGroupTaskManager::LoadColor()
{
    _mapColor.clear();
    CDaily_shimentaskColorLoader oColorLoader;
    string strPath = Config._strConfigDir + "Conf/Table/Daily_shimentaskColor.xml";
    if(!oColorLoader.LoadData((strPath)))
    {
        LOG_CRI << "Load " << strPath << "ERR";   
        return false;
    }
    for(auto iter = oColorLoader._vecData.begin(); iter != oColorLoader._vecData.end();iter++)
    {
        SDaily_shimentaskColorCFG & Cfg = *(*iter);
        if(!_mapColor.insert(make_pair(Cfg._TaskId,Cfg)).second)
        {
            LOG_CRI << "Dubble Level Task :" << strPath;
        }
    }

    return true;
}
