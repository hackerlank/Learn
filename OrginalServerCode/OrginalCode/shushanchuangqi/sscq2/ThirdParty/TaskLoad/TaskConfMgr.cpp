/********************************************************************
//	TaskLoad Library Source File.
//	File name:	TaskConfMgr.cpp
//	Created:	2011/09/12	15:00
//	Organization:	
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:	
//	Version:	1.0
//	Histroy:
 *********************************************************************/

#include "TaskConfMgr.h"
#ifdef __GNUG__
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#endif

#define TASK_LEVEL_MAX 150

/**
 *	根据key从map容器中得到value项的指针， 如果不存在则返回NULL;
 */
    template<typename KEY, typename VALUE>
VALUE* GetValueFromMap(map<KEY, VALUE> &myMap, const KEY key)
{
    typename map<KEY, VALUE>::iterator it = myMap.find(key);
    if(it == myMap.end())
        return NULL;
    return &it->second;
}


bool CTaskConfMgr::LoadTaskFile(const string& strPath,const string &strFileName)
{
    if(strPath.empty() || strFileName.empty())
        return false;
    string strTaskFile = strPath + strFileName;
#ifdef _WIN32
    WIN32_FIND_DATA ffd;
    HANDLE hFind = FindFirstFile(strTaskFile.c_str(), &ffd);
    if(INVALID_HANDLE_VALUE == hFind) 
        return false;
    if((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
    {
#else
        if(0 != access(strTaskFile.c_str() , F_OK))
            return false;
#endif
        if(strFileName.find("Task") != string::npos)
        {
            size_t start = sizeof("Task") - 1;
            size_t pos = strFileName.find(".xml");
            if(pos != string::npos)
            {
                UINT16 wTaskID = (UINT16)atoi(strFileName.substr(start, pos - start).c_str());
                if(wTaskID != 0)
                {
                    if(!LoadTask(wTaskID, strTaskFile))
                        return false;
                }
            }
        }
#ifdef _WIN32
    }
    FindClose(hFind);
#endif
    return true;
}

bool CTaskConfMgr::LoadTaskDirectory(const string& strPath)
{
    if(strPath.empty())
        return false;
    string strTaskFile = strPath + "/Task*";
    string strDir = strPath + "/";
#ifdef _WIN32
    WIN32_FIND_DATA ffd;
    HANDLE hFind = FindFirstFile(strTaskFile.c_str(), &ffd);
    if(INVALID_HANDLE_VALUE == hFind) 
        return false;
    do
    {
        if((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
        {
            string strFileName = ffd.cFileName;
#else
            dirent* entry = NULL;
            int ret = 1;
            DIR* dir = opendir(strPath.c_str());
            if(dir == NULL)
                return false;
            while((entry = readdir(dir)) != NULL)
            {
                if(entry->d_type == DT_REG || entry->d_type == DT_UNKNOWN)
                {
                    string strFileName = entry->d_name;
#endif
                    if(strFileName.find("Task") != string::npos)
                    {
                        size_t start = sizeof("Task") - 1;

                        size_t pos = strFileName.find(".xml");
                        if(pos != string::npos)
                        {
                            UINT16 wTaskID = (UINT16)atoi(strFileName.substr(start, pos - start).c_str());
                            if(wTaskID != 0)
                            {
                                string strFilePath = strDir + strFileName;
                                if(!LoadTask(wTaskID, strFilePath))
                                    return false;
                            }
                        }
                    }
                }
            }
#ifdef _WIN32
            while(FindNextFile(hFind, &ffd) != 0);
            FindClose(hFind);
#else
            closedir(dir);
#endif
            return true;
        }

        bool CTaskConfMgr::LoadTask(UINT16 wTaskID, const string& strXmlPath)
        {
            STaskConfig& taskConf = _mapID2TaskConf[wTaskID];
            if(!taskConf.ParseXML(strXmlPath))
                return false;
            //根据taskinfo的内容将其放入不同的分类中
            SIdxType& rIdxType = taskConf.oTriggerTarget;
            if (rIdxType.eType == eTargetNone || rIdxType.eType >= eTargetEnd)
                return false;
            switch(rIdxType.eType)
            {
#if 0
                case eTargetItem:
                    if (eTaskTypeExtent_reward == taskConf.eTaskTypeExtent)
                    {
                        bool bAdd = false;
                        for (auto it = taskConf.vecLimitProp.begin();it != taskConf.vecLimitProp.end();it++)
                        {
                            if (eLimtPropLevel == it->eLimitType)
                            {
                                AddChurchTask(it->wValue, wTaskID);
                                bAdd = true;
                            }
                        }
                        if (!bAdd)
                            AddChurchTask(0, wTaskID);
                    }
                    break;
#endif
                case eTargetNpc:
                    {
#if 0
                        if (eTaskTypeExtent_reward == taskConf.eTaskTypeExtent)
                        {
                            bool bAdd = false;
                            for (auto it = taskConf.vecLimitProp.begin();it != taskConf.vecLimitProp.end();it++)
                            {
                                if (eLimtPropLevel == it->eLimitType)
                                {
                                    AddChurchTask(it->wValue, wTaskID);
                                    bAdd = true;
                                }
                            }
                            if (!bAdd)
                                AddChurchTask(0, wTaskID);
                        }
                        else
#endif
                            _mapNpc2Task[rIdxType.dwIdx].vecAcceptTask.push_back(wTaskID);
                    }
                    break;
                case eTargetScene:
                    {
                        if (!taskConf.vecTrigger.empty())//区域触发任务
                        {
                            for(size_t i = 0, size = taskConf.vecTrigger.size(); i < size; ++i)
                            {
                                SMapArea& rMapArea = taskConf.vecTrigger[i];
                                SProbeInfo oProbeInfo;
                                oProbeInfo.wTaskID = wTaskID;
                                oProbeInfo.oMapArea = rMapArea;
                                _mapMap2TriggerList[rMapArea.wMapID].push_back(oProbeInfo);
                            }
                            break;
                        }
                        if (taskConf.eTaskType == eTaskConfMain || taskConf.eTaskType == eTaskConfBranch)
                        {
                            _vecBegin2TaskList.push_back(wTaskID);
                        }
                        else if(taskConf.eTaskType == eTaskConfDay)
                        {
                        
                            _vecEveryDayTask.push_back(wTaskID);
                        }


                        for (auto it = taskConf.vecLimitProp.begin();it != taskConf.vecLimitProp.end();it++)
                        {
                            switch(it->eLimitType)
                            {
                                case eLimtPropLevel:
                                    AddLevelTask(it->wValue, wTaskID);
                                    break;
                                case eLimtPropRepute:
                                    _mapRepute2TaskList[taskConf.wLimitCampID].push_back(wTaskID);
                                    break;
                            }
                        }

                        for (auto it_pre = taskConf.vecLimitPreTasks.begin(); it_pre != taskConf.vecLimitPreTasks.end();it_pre++)
                        {
                            _mapTaskPre2TaskList[*it_pre].push_back(wTaskID);
                        }
                    }
                    break;
            }
            //任务都是直接交
            /*for(size_t i = 0, size = taskConf.vecSubmitTarget.size(); i < size; ++i)
              {
              SIdxType& rIdxType = taskConf.vecSubmitTarget[i];
              switch(rIdxType.eType)
              {
              case eTargetNpc:
              _mapNpc2Task[rIdxType.dwIdx].vecFinishTask.push_back(wTaskID);
              break;
              }
              }*/
            for(size_t i = 0, size = taskConf.vecMonsterKill.size(); i < size; ++i)
            {
                UINT32 wMonsterID = taskConf.vecMonsterKill[i].wMonsterID;
                _mapMst2TaskList[wMonsterID].push_back(wTaskID);
            }
            for(size_t i = 0, size = taskConf.vecItemCollect.size(); i < size; ++i)
            {
                UINT16 wItemID = taskConf.vecItemCollect[i].wItemID;
                UINT16 wMonsterID = taskConf.vecItemCollect[i].wMonsterID;
                _mapItem2ColTaskList[wItemID].push_back(wTaskID);
                if(wMonsterID != 0)
                    _mapMst2ColTaskList[wMonsterID].push_back(wTaskID);
            }
            for(size_t i = 0, size = taskConf.vecProbe.size(); i < size; ++i)
            {
                SMapArea& rMapArea = taskConf.vecProbe[i];
                SProbeInfo oProbeInfo;
                oProbeInfo.wTaskID = wTaskID;
                oProbeInfo.oMapArea = rMapArea;
                _mapMap2ProbeList[rMapArea.wMapID].push_back(oProbeInfo);
            }

            /*
               for(size_t i = 0, size = taskConf.vecUseItem.size(); i < size; ++i)
               {
               SUseItem& rUseItem = taskConf.vecUseItem[i];
               _mapItem2UseTaskList[rUseItem.wItemID].push_back(wTaskID);
               }
               for(size_t i = 0, size = taskConf.vecUseSkill.size(); i < size; ++i)
               {
               SUseSkill& rUseSkill = taskConf.vecUseSkill[i];
               _mapSkill2UseTaskList[rUseSkill.dwSkillID].push_back(wTaskID);
               }
               */

            for(auto it = taskConf.mapNpc2Talk.begin(); 
                    it != taskConf.mapNpc2Talk.end(); 
                    ++it)
            {
                UINT16 wNpcID = it->first;
                SNpcTalk& rNpcTalk = it->second;
                _mapNpc2Task[wNpcID].mapTask2Talk.insert(make_pair(wTaskID, rNpcTalk));
            }

            for(size_t i = 0, size = taskConf.vecGather.size(); i < size; ++i)
            {
                UINT32 id = taskConf.vecGather[i].dwIdx;
                _mapGather2TaskList[id].push_back(wTaskID);
            }

            //成长
            for(size_t i = 0, size = taskConf.vecRoleProps.size(); i < size; ++i)
            {
                _mapGrow2TaskList[taskConf.vecRoleProps[i].type].push_back(wTaskID);
            }

            //行为
            for(size_t i = 0, size = taskConf.vecRoleActions.size(); i < size; ++i)
            {
                _mapAction2TaskList[taskConf.vecRoleActions[i].type].push_back(wTaskID);
            }

            //建设_建筑
            for(size_t i = 0, size = taskConf.vecBuildings.size(); i < size; ++i)
            {
                _mapBuilding2TaskList[taskConf.vecBuildings[i].dwIdx].push_back(wTaskID);
            }

            //建设_科技
            for(size_t i = 0, size = taskConf.vecTechnics.size(); i < size; ++i)
            {
                _mapTechnic2TaskList[taskConf.vecTechnics[i].dwIdx].push_back(wTaskID);
            }

            return true;
        }

        TMapTaskConfig& CTaskConfMgr::GetTaskConfig()
        {
            return _mapID2TaskConf;
        }

        STaskConfig* CTaskConfMgr::GetTaskConfig(UINT16 wTaskID)
        {
            map<UINT16, STaskConfig>::iterator it = _mapID2TaskConf.find(wTaskID);
            if(it == _mapID2TaskConf.end())
                return NULL;

            return &it->second;
        }

        TTaskList* CTaskConfMgr::GetMonsterTask(UINT16 wMonsterID)
        {
            return GetValueFromMap(_mapMst2TaskList, wMonsterID);
        }

        TTaskList* CTaskConfMgr::GetCollectTask(UINT16 wItemID)
        {
            return GetValueFromMap(_mapItem2ColTaskList, wItemID);
        }

        TTaskList* CTaskConfMgr::GetCollectKillTask(UINT16 wMonsterID)
        {
            return GetValueFromMap(_mapMst2ColTaskList, wMonsterID);
        }

        bool CTaskConfMgr::HasTask(UINT16 wMonsterID)
        {
            if(GetMonsterTask(wMonsterID) != NULL)
                return true;
            if(GetCollectKillTask(wMonsterID) != NULL)
                return true;
            return false;
        }

        /*
           TTaskList* CTaskConfMgr::GetUseItemTask(UINT32 wItemID)
           {
           map<UINT32, vector<UINT16>>::iterator it = _mapItem2UseTaskList.find(wItemID);
           if(it == _mapItem2UseTaskList.end())
           return NULL;
           return &it->second;
           }

           TTaskList* CTaskConfMgr::GetUseSkillTask(UINT32 dwSkillID)
           {
           map<UINT32, vector<UINT16>>::iterator it = _mapSkill2UseTaskList.find(dwSkillID);
           if(it == _mapSkill2UseTaskList.end())
           return NULL;
           return &it->second;
           }
           */

        SNpcTask* CTaskConfMgr::GetNpcTask(UINT16 wNpcID)
        {
            map<UINT16, SNpcTask>::iterator it = _mapNpc2Task.find(wNpcID);
            if(it == _mapNpc2Task.end())
                return NULL;
            return &it->second;
        }

        TTaskList* CTaskConfMgr::GetGatherTask(UINT16 wItemID)
        {
            return GetValueFromMap(_mapGather2TaskList, wItemID);
        }

        TTaskList* CTaskConfMgr::GetRoleProperty(EProcessRoleProperty type)
        {
            return GetValueFromMap(_mapGrow2TaskList, type);
        }

        TTaskList* CTaskConfMgr::GetBehaviorTask(EProcessAction type)
        {
            return GetValueFromMap(_mapAction2TaskList, type);
        }

        TTaskList* CTaskConfMgr::GetBuildingTask(UINT32 id)
        {
            return GetValueFromMap(_mapBuilding2TaskList, id);
        }

        TTaskList* CTaskConfMgr::GetTechnicTask(UINT32 id)
        {
            return GetValueFromMap(_mapTechnic2TaskList, id);
        }

        TVecProbeInfo* CTaskConfMgr::GetProbeTask(UINT16 wMapID)
        {
            return GetValueFromMap(_mapMap2ProbeList, wMapID);
        }

        void CTaskConfMgr::AddLevelTask(UINT16 wLevel, UINT16 wTaskID)
        {
            for (int i = 1;i <= TASK_LEVEL_MAX;i++)
            {
                if (i < wLevel)
                    continue;
                _mapLevel2TaskList[i].push_back(wTaskID);
            }
        }

        TTaskList* CTaskConfMgr::GetLevelTask(UINT16 wLevel)
        {
            return GetValueFromMap(_mapLevel2TaskList, wLevel);
        }

        TTaskList* CTaskConfMgr::GetReputeTask(UINT16 wCamp)
        {
            return GetValueFromMap(_mapRepute2TaskList, wCamp);
        }

        TTaskList* CTaskConfMgr::GetTaskPreTask(UINT16 wTaskID)
        {
            return GetValueFromMap(_mapTaskPre2TaskList, wTaskID);
        }

        TTaskList* CTaskConfMgr::GetBeginTask()
        {
            return &_vecBegin2TaskList;
        }

        TVecProbeInfo* CTaskConfMgr::GetTriggerTask(UINT16 wMapID)
        {
            return GetValueFromMap(_mapMap2TriggerList, wMapID);
        }
#if 0
        void CTaskConfMgr::AddChurchTask(UINT16 wLevel, UINT16 wTaskID)
        {
            for (int i = wLevel;i <= TASK_LEVEL_MAX;i++)
                _mapChurch2TaskList[i].emplace_back(wTaskID);
        }

        TTaskList* CTaskConfMgr::GetChurchTask(UINT16 wLevel)
        {
            auto it = _mapChurch2TaskList.find(wLevel);
            if (it != _mapChurch2TaskList.end())
                return &it->second;

            return NULL;
        }
#endif
        const TTaskList& CTaskConfMgr::GetEveryDayTask()
        {
            return _vecEveryDayTask;
        }
