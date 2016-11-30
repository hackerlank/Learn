#include "TaskMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\Map.h"
#include "..\..\Base\Service\BaseService.h"

TaskMgr::TaskMgr()
{
	m_isHaveNew = false;
}

void TaskMgr::init(MsgDBTaskList *info)
{
	if (info != NULL)
	{
		std::map<ACE_UINT32, TaskConfig> &refTaskConfig = GAME_CONFIG_INSTANCE::instance()->m_oTaskConfig;
		std::map<ACE_UINT32, TaskConfig>::const_iterator itMap;
		ActiveEvent stEvent;
		for (int i=0;i<MAX_TOTAL_TASK_COUNT && i<info->m_unCount;++i)
		{
			itMap = refTaskConfig.find(info->m_taskList[i].unTaskID);
			if (itMap != refTaskConfig.end() /*&& itMap->second.unExpiredTime == 0*/)
			{
				stEvent.m_byTaskStatus = info->m_taskList[i].byStatus;
				stEvent.m_unActiveEventType = itMap->second.unActiveEventType;
				stEvent.m_unTaskID = info->m_taskList[i].unTaskID;
				stEvent.m_unCurrentProgress = info->m_taskList[i].unCurrentProgress;
				m_setCurrentTask.insert(stEvent);

				AddTask(stEvent.m_unTaskID);	
			}
		}	

		for (itMap = refTaskConfig.begin();itMap!= refTaskConfig.end();itMap++)
		{
			if (itMap->second.unPremiseTaskCase == 0)
				AddTask(itMap->second.unID);
		}

	}
}

bool TaskMgr::AddTask(ACE_UINT32 unNewTask)
{
	std::map<ACE_UINT32, TaskConfig> &refTaskConfig = GAME_CONFIG_INSTANCE::instance()->m_oTaskConfig;
	std::map<ACE_UINT32, TaskConfig>::iterator itMap = refTaskConfig.find(unNewTask);
	if (itMap != refTaskConfig.end())
	{
		if (itMap->second.unPremiseTaskCase != 0)
		{
			ActiveEvent stEvent;
			stEvent.m_unTaskID = itMap->second.unPremiseTaskCase;
			std::set<ActiveEvent, TaskComp>::iterator itSet = m_setCurrentTask.find(stEvent);
			if (itSet != m_setCurrentTask.end() && ((*itSet).m_byTaskStatus == TASK_STATUS_REWARED ||
				(*itSet).m_byTaskStatus == TASK_STATUS_FINISHED) && itMap->second.unLevelCase <= m_map->m_unLevel)
			{
				stEvent.m_unTaskID = unNewTask;
				itSet = m_setCurrentTask.find(stEvent);
				if (itSet != m_setCurrentTask.end()) //在接受任务之前，已经做过
				{
					m_mapSendTaskList[unNewTask] = *itSet;
				}
				else
				{
					stEvent.m_unActiveEventType = itMap->second.unActiveEventType;
					m_mapSendTaskList.insert(std::make_pair(stEvent.m_unTaskID, stEvent));
					m_setCurrentTask.insert(stEvent);
					update_2_db();
				}
				
				{
					//insert_2_db(stEvent.m_unTaskID, stEvent.m_unCurrentProgress, stEvent.m_byTaskStatus);
					/*std::set<ActiveEvent, TaskComp>::iterator itTmpSet;
					for (itSet = m_setCurrentTask.begin();itSet!=m_setCurrentTask.end();++itSet)
					{
						itMap = refTaskConfig.find((*itSet).m_unTaskID);
						if (itMap != refTaskConfig.end())
						{
							stEvent.m_unTaskID = itMap->second.unPremiseTaskCase;
							itTmpSet = m_setCurrentTask.find(stEvent);
							if (itTmpSet != m_setCurrentTask.end())
							{
								if ((*itTmpSet).m_byTaskStatus == TASK_STATUS_REWARED)
								{
									delete_2_db((*itTmpSet).m_unTaskID);
									m_setCurrentTask.erase(itTmpSet);
									break;
								}
							}
						}
					}*/
					CLogBase *pLog = BaseService::GetLogInstance();
					sprintf(pLog->m_szLogBuffer, "[%s][%d]:AddTask taskid = %d",__FILE__, __LINE__, unNewTask);
					pLog->RecordLog(Log_Type_Info, pLog->m_szLogBuffer);
					return true;
				}
			}
		}
		else if (itMap->second.unLevelCase <= m_map->m_unLevel)
		{
			ActiveEvent stEvent;
			stEvent.m_unTaskID = unNewTask;
			stEvent.m_unActiveEventType = itMap->second.unActiveEventType;
			std::set<ActiveEvent, TaskComp>::iterator itSet = m_setCurrentTask.find(stEvent);

			if (itSet != m_setCurrentTask.end()) //在接受任务之前，已经做过
			{
				m_mapSendTaskList[unNewTask] = *itSet;
			}
			else
			{
				stEvent.m_unTaskID = unNewTask;
				stEvent.m_unActiveEventType = itMap->second.unActiveEventType;
				m_mapSendTaskList.insert(std::make_pair(stEvent.m_unTaskID, stEvent));
				m_setCurrentTask.insert(stEvent);
				update_2_db();
			}
			//m_mapSendTaskList.insert(std::make_pair(stEvent.m_unTaskID,stEvent));
			{
				//update_2_db();
				//insert_2_db(stEvent.m_unTaskID, stEvent.m_unCurrentProgress, stEvent.m_byTaskStatus);
				CLogBase *pLog = BaseService::GetLogInstance();
				sprintf(pLog->m_szLogBuffer, "[%s][%d]:AddTask taskid = %d",__FILE__, __LINE__, unNewTask);
				pLog->RecordLog(Log_Type_Info, pLog->m_szLogBuffer);
				return true;
			}
		}
	}
	return false;
}

bool TaskMgr::RefreshTask(ACE_UINT32 unTaskType, ACE_UINT32 unAttachID,int multEnergy/* = 1*/)
{
	std::multimap<ACE_UINT32, TaskConfig> &refTaskType = GAME_CONFIG_INSTANCE::instance()->m_oTaskTypeConfig;
	std::pair<std::multimap<ACE_UINT32, TaskConfig>::iterator, std::multimap<ACE_UINT32, TaskConfig>::iterator> itPairMultiMap;
	std::multimap<ACE_UINT32, TaskConfig>::iterator itMultiMap;
	std::set<ActiveEvent, TaskComp>::iterator itSet;
	itPairMultiMap = refTaskType.equal_range(unTaskType);
	ActiveEvent tmpEvent;
	for (itMultiMap=itPairMultiMap.first;itMultiMap != itPairMultiMap.second;++itMultiMap)
	{
		bool bFinished = false;
		tmpEvent.m_unTaskID = itMultiMap->second.unID;
		itSet = m_setCurrentTask.find(tmpEvent);
		if (itSet != m_setCurrentTask.end() && ((itSet->m_byTaskStatus == TASK_STATUS_FINISHED) ||
			(itSet->m_byTaskStatus == TASK_STATUS_REWARED)))
		{
			continue; //该任务已完成
		}
		if (itMultiMap->second.unAttachID != 0)
		{
			switch (unTaskType)
			{
			case Event_Base_Type_ReachSpecificLevel:
			case Event_Base_Type_ReachSpecificStar:
			case Event_Base_Type_EquipmentSpecificLevel:
			case Event_Base_Type_EquipmentSpecificStar:
				{
					if (itMultiMap->second.unAttachID <= unAttachID)
					{
						bFinished = true;
					}
				}break;
			default:
				break;
			}
		}

		if (bFinished || itMultiMap->second.unAttachID == 0 || itMultiMap->second.unAttachID == unAttachID)
		{
			if (itSet != m_setCurrentTask.end())//当前已经添加了此任务
			{
				if ((*itSet).m_byTaskStatus == TASK_STATUS_OPEN && ((*itSet).m_unCurrentProgress += multEnergy) >= itMultiMap->second.unCompleteCount)
				{
					itMultiMap->second.unCompleteCount = itMultiMap->second.unCompleteCount;
					(*itSet).m_byTaskStatus = TASK_STATUS_FINISHED;
					m_isHaveNew = true;
				}
			}
			else//添加新的任务
			{
				ActiveEvent stEvent;
				stEvent.m_unTaskID = itMultiMap->second.unID;
				stEvent.m_unActiveEventType = unTaskType;
				stEvent.m_unCurrentProgress = multEnergy;
				if (itMultiMap->second.unCompleteCount == 1)
				{
					stEvent.m_unCurrentProgress = itMultiMap->second.unCompleteCount;
					stEvent.m_byTaskStatus = TASK_STATUS_FINISHED;
					m_isHaveNew = true;
				}
				itSet = m_setCurrentTask.insert(stEvent).first;
			}
			update_2_db();
			m_mapSendTaskList[itMultiMap->second.unID] = *itSet;
			//update_2_db((*itSet).m_unTaskID, (*itSet).m_unCurrentProgress, (*itSet).m_byTaskStatus);
		}
	}
	return true;
}


bool TaskMgr::RefreshTaskEx( ACE_UINT32 unTaskType, ACE_UINT32 unAttachID,int multEnergy /*= 1*/ )
{
	std::multimap<ACE_UINT32, TaskConfig> &refTaskType = GAME_CONFIG_INSTANCE::instance()->m_oTaskTypeConfig;
	std::pair<std::multimap<ACE_UINT32, TaskConfig>::iterator, std::multimap<ACE_UINT32, TaskConfig>::iterator> itPairMultiMap;
	std::multimap<ACE_UINT32, TaskConfig>::iterator itMultiMap;
	itPairMultiMap = refTaskType.equal_range(unTaskType);
	TaskConfig taskNow;
	ZeroVar(taskNow);

	for (itMultiMap=itPairMultiMap.first;itMultiMap != itPairMultiMap.second;++itMultiMap)//先找到任务id
	{
		if(itMultiMap->second.unAttachID == unAttachID)//找到了
		{
			taskNow = itMultiMap->second;
			break;
		}
	}

	if (taskNow.unID != 0)
	{
		return RefreshTaskEx(unTaskType,taskNow,multEnergy);
	}

	return true;
}

bool TaskMgr::RefreshTaskEx( ACE_UINT32 unTaskType, TaskConfig & taskNow,int multEnergy )
{
	std::set<ActiveEvent, TaskComp>::iterator itSet;
	ActiveEvent tmpEvent;

	std::map<ACE_UINT32, TaskConfig> &refTaskConfig = GAME_CONFIG_INSTANCE::instance()->m_oTaskConfig;
	for (std::map<ACE_UINT32, TaskConfig>::const_iterator c_it = refTaskConfig.begin();c_it != refTaskConfig.end();c_it++)
	{
		if (c_it->second.unPremiseTaskCase == taskNow.unID)//找到了这个前置任务id
		{
			tmpEvent.m_unTaskID = c_it->second.unID;
			itSet = m_setCurrentTask.find(tmpEvent);
			if (itSet != m_setCurrentTask.end() && ((itSet->m_byTaskStatus == TASK_STATUS_FINISHED) ||
				(itSet->m_byTaskStatus == TASK_STATUS_REWARED)))
			{
				continue; //该任务已完成
			}

			//				Event_Base_Type_SpecificDuplication
			// 				switch (unTaskType)
			// 				{}
			// 				if (itSet != m_setCurrentTask.end())//当前已经添加了此任务
			// 				{
			// 					if ((*itSet).m_byTaskStatus == TASK_STATUS_OPEN && ((*itSet).m_unCurrentProgress += multEnergy) >= taskNow.unCompleteCount)
			// 					{
			// 						(*itSet).m_byTaskStatus = TASK_STATUS_FINISHED;
			// 					}
			// 				}
			if(itSet == m_setCurrentTask.end())//添加新的任务
			{
				ActiveEvent stEvent;
				stEvent.m_unTaskID = tmpEvent.m_unTaskID;
				stEvent.m_unActiveEventType = unTaskType;
				//stEvent.m_unCurrentProgress = multEnergy;
				// 					if (taskNow.unCompleteCount == 1)
				// 					{
				// 						stEvent.m_byTaskStatus = TASK_STATUS_FINISHED;
				// 					}
				itSet = m_setCurrentTask.insert(stEvent).first;
				update_2_db();
				m_mapSendTaskList[stEvent.m_unTaskID] = *itSet;
			}
		}
	}

	return true;
}

bool TaskMgr::GetReward(ACE_UINT32 unTaskID, RewardInfo &oRewardInfo)
{
	ActiveEvent stEvent;
	stEvent.m_unTaskID = unTaskID;
	std::set<ActiveEvent, TaskComp>::iterator itSet = m_setCurrentTask.find(stEvent);
	if (itSet != m_setCurrentTask.end())
	{
		if ((*itSet).m_byTaskStatus == TASK_STATUS_FINISHED)
		{
			std::map<ACE_UINT32, TaskConfig> refTaskConfig = GAME_CONFIG_INSTANCE::instance()->m_oTaskConfig;
			std::map<ACE_UINT32, TaskConfig>::iterator itMap = refTaskConfig.find(unTaskID);
			if (itMap != refTaskConfig.end())
			{
				m_map->get_reward_from_config_reward(oRewardInfo, itMap->second.stReward, 1, 1);
				//-----------log日志
				//任务
				LogItemInfo logInfo;
				logInfo.m_goodsID = unTaskID;
				logInfo.m_op_action = enum_LOG_ACTION::LOG_ACTION_task;//动作原因
				logInfo.SetOp_Way(_LOG_OP_WAY_task);//途径(附加信息)
				m_map->get_reward(oRewardInfo,logInfo);
				CLogBase *pLog = BaseService::GetLogInstance();
				sprintf(pLog->m_szLogBuffer, "[%s][%d]:TaskGetReward taskid = %d, bell=%d, money=%d",__FILE__, __LINE__,
					unTaskID, oRewardInfo.unCoin, oRewardInfo.unMoney);
				pLog->RecordLog(Log_Type_Info, pLog->m_szLogBuffer);

				(*itSet).m_byTaskStatus = TASK_STATUS_REWARED;
				m_mapSendTaskList[unTaskID] = *itSet;
				//update_2_db((*itSet).m_unTaskID, (*itSet).m_unCurrentProgress, (*itSet).m_byTaskStatus);
				update_2_db();

				return true;
			}	
		}
	}

	return false;
}

void TaskMgr::BuildTaskListPkg(MsgTaskList &response)
{
	std::map<ACE_UINT32, ActiveEvent>::iterator itMap = m_mapSendTaskList.begin();
	response.iTaskNum = 0;
	response.iListType = TASK_LIST_MAIN;
	memset(&response.taskInfo, 0, sizeof(TaskInfo) * MAX_CURRENT_TASK_COUNT);
	for (int i=0;i<MAX_CURRENT_TASK_COUNT&&itMap!=m_mapSendTaskList.end();++itMap)
	{
		//判断前置任务是否完成
		if (/*itMap->second.m_byTaskStatus == TASK_STATUS_OPEN || */ChickPreMissionIsComplete(itMap->second.m_unTaskID))//
		{
			response.taskInfo[i].unTaskID = itMap->second.m_unTaskID;
			response.taskInfo[i].unCurrentProgress = itMap->second.m_unCurrentProgress;
			response.taskInfo[i].byStatus = itMap->second.m_byTaskStatus;
			++response.iTaskNum;
			++i;
		}
	}

	m_isHaveNew = false;
}

bool TaskMgr::ChickPreMissionIsComplete( ACE_UINT32 unNewTaskID )
{
	ActiveEvent tmpEvent;

	std::map<ACE_UINT32, TaskConfig> &refTaskConfig = GAME_CONFIG_INSTANCE::instance()->m_oTaskConfig;
	std::map<ACE_UINT32, TaskConfig>::const_iterator itMap = refTaskConfig.find(unNewTaskID);
	if (itMap != refTaskConfig.end() /*&& itMap->second.unExpiredTime == 0*/)
	{
		tmpEvent.m_unTaskID = itMap->second.unPremiseTaskCase;
		if(tmpEvent.m_unTaskID == 0)
			return true;

		std::set<ActiveEvent, TaskComp>::iterator itSet = m_setCurrentTask.find(tmpEvent);
		if (itSet != m_setCurrentTask.end() && itSet->m_byTaskStatus == TASK_STATUS_REWARED)
			return true; //该任务已完成
	}

	return false;
}

/*
void TaskMgr::update_2_db(ACE_UINT32 m_unTaskID, ACE_UINT32 m_unProgress, ACE_Byte m_byStatus)
{
	MsgDBUpdateTaskInfoRequest db_request;
	db_request.m_taskInfo.byStatus = m_byStatus;
	db_request.m_taskInfo.unTaskID = m_unTaskID;
	db_request.m_taskInfo.unCurrentProgress = m_unProgress;
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_TASK_LIST, (char *)&db_request, sizeof(MsgDBUpdateTaskInfoRequest));
}

void TaskMgr::insert_2_db(ACE_UINT32 m_unTaskID, ACE_UINT32 m_unProgress, ACE_Byte m_byStatus)
{
	MsgDBUpdateTaskInfoRequest db_request;
	db_request.m_taskInfo.byStatus = m_byStatus;
	db_request.m_taskInfo.unTaskID = m_unTaskID;
	db_request.m_taskInfo.unCurrentProgress = m_unProgress;
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_INSERT_TASK_LIST, (char *)&db_request, sizeof(MsgDBUpdateTaskInfoRequest));
}

void TaskMgr::delete_2_db(ACE_UINT32 m_unTaskID)
{
	MsgDBDeleteTaskInfoRequest db_request;
	db_request.m_unTaskID = m_unTaskID;
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_DELETE_TASK, (char *)&db_request, sizeof(MsgDBDeleteTaskInfoRequest));
}*/

void TaskMgr::update_2_db()
{
	MsgDBTaskList db_request;
	memset(&db_request, 0, sizeof(MsgDBTaskList));
	std::set<ActiveEvent, TaskComp>::iterator itSet = m_setCurrentTask.begin();
	int i=0;
	for (;i<MAX_TOTAL_TASK_COUNT && itSet != m_setCurrentTask.end();++i, ++itSet)
	{
		db_request.m_taskList[i].byStatus = itSet->m_byTaskStatus;
		db_request.m_taskList[i].unCurrentProgress = itSet->m_unCurrentProgress;
		db_request.m_taskList[i].unTaskID = itSet->m_unTaskID;
	}
	db_request.m_unCount = i;
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_TASK_PROGRESS_REQUEST, (char *)&db_request, sizeof(MsgDBTaskList));
}


