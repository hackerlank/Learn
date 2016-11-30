#include "DailyTaskMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\Map.h"

void DailyTaskMgr::Reset()
{

	std::map<ACE_UINT32, ActivenessInfo> &refActivenessInfo = GAME_CONFIG_INSTANCE::instance()->m_oActivenessList;
	std::map<ACE_UINT32, ActivenessInfo>::iterator itMap;
	
	if (refActivenessInfo.size() != m_setDailyTask.size())
	{
		ActiveEvent stEvent;
		for (itMap=refActivenessInfo.begin();itMap!=refActivenessInfo.end();++itMap)
		{
			stEvent.m_unTaskID = itMap->first;
			stEvent.m_unActiveEventType = itMap->second.unActiveEventType;
			if (m_setDailyTask.count(stEvent) == 0)
			{
				m_setDailyTask.insert(stEvent);
				insert_2_db(stEvent.m_unTaskID, stEvent.m_unCurrentProgress, stEvent.m_byTaskStatus);
			}
		}
	}

	std::set<ActiveEvent, TaskComp>::iterator itSet = m_setDailyTask.begin();
	for (;itSet!=m_setDailyTask.end();++itSet)
	{
		(*itSet).Reset();
		update_2_db((*itSet).m_unTaskID, (*itSet).m_unCurrentProgress, (*itSet).m_byTaskStatus);
	}
	m_unActivenessPoints = 0;
	m_setObtainedActivenessReward.clear();
}

void DailyTaskMgr::Init(MsgDBTaskList *info)
{
	if (info != NULL)
	{
		std::map<ACE_UINT32, ActivenessInfo> &refActivenessInfo = GAME_CONFIG_INSTANCE::instance()->m_oActivenessList;
		std::map<ACE_UINT32, ActivenessInfo>::iterator itMap;
		ActiveEvent stEvent;
		for (int i=0;i<MAX_CURRENT_TASK_COUNT && i<info->m_unCount;++i)
		{
			itMap = refActivenessInfo.find(info->m_taskList[i].unTaskID);
			if (itMap != refActivenessInfo.end())
			{
				stEvent.m_byTaskStatus = info->m_taskList[i].byStatus;
				stEvent.m_unActiveEventType = itMap->second.unActiveEventType;
				stEvent.m_unTaskID = info->m_taskList[i].unTaskID;
				stEvent.m_unCurrentProgress = info->m_taskList[i].unCurrentProgress;
				m_setDailyTask.insert(stEvent);
				if (stEvent.m_unCurrentProgress >= itMap->second.unCompleteCount && stEvent.m_byTaskStatus == TASK_STATUS_REWARED )
				{
					m_unActivenessPoints += itMap->second.unActivenessPoints;
				}
			}
		}	
	}
	m_map->CheckDateChanged();
}

void DailyTaskMgr::InitObtainedReward(MsgDBObtainedActivenessRewardList *info)
{
	if (info != NULL)
	{
		for (int i=0;i<info->m_unCount&&i<MAX_ACTIVENESS_COUNT;++i)
		{
			m_setObtainedActivenessReward.insert(info->m_ObtainedList[i]);
		}
	}
	m_map->CheckDateChanged();
}

bool DailyTaskMgr::RefreshTask(ACE_UINT32 unTaskType, ACE_UINT32 unAttachID,int multEnergy/* = 1*/)
{
	m_map->CheckDateChanged();
	
	std::set<ActiveEvent, TaskComp>::iterator itSet = m_setDailyTask.begin();
	for (;itSet!=m_setDailyTask.end();++itSet)
	{
		if ((*itSet).m_unActiveEventType == unTaskType)
		{
			std::map<ACE_UINT32, ActivenessInfo> &refActivenessInfo = GAME_CONFIG_INSTANCE::instance()->m_oActivenessList;
			std::map<ACE_UINT32, ActivenessInfo>::iterator itMap = refActivenessInfo.find((*itSet).m_unTaskID);
			if (itMap != refActivenessInfo.end())
			{
				if (itMap->second.unAttachID == 0 || itMap->second.unAttachID == unAttachID)
				{
					if ((*itSet).m_byTaskStatus == TASK_STATUS_OPEN && ((*itSet).m_unCurrentProgress += multEnergy )>= itMap->second.unCompleteCount)
					{
						(*itSet).m_byTaskStatus = TASK_STATUS_FINISHED;
						m_isHaveNew = true;
						//m_unActivenessPoints += itMap->second.unActivenessPoints;
						/*MsgActivenessChanged package;
						package.unActivenessChanged = m_unActivenessPoints;
						m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_ACTIVENESS_CHANGED,(char *)&package, sizeof(MsgActivenessChanged), OBJ_ID_NONE, ADAPTER_GATEWAY_MGR, m_map->m_unUserID);*/
					}
					update_2_db((*itSet).m_unTaskID, (*itSet).m_unCurrentProgress, (*itSet).m_byTaskStatus);
					/*MsgTaskList response;
					response.iListType = TASK_LIST_DAILY;
					BuildTaskListPkg(response);
					m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_TASK_LIST,(char *)&response, sizeof(MsgTaskList), OBJ_ID_NONE, ADAPTER_GATEWAY_MGR, m_map->m_unUserID);*/
				}
			}
		}
	}
	return true;
}

bool DailyTaskMgr::GetSingleTaskReward(ACE_UINT32 unTaskID, RewardInfo &oRewardInfo, ACE_UINT32 &unActivenessChanged)
{
	m_map->CheckDateChanged();
	ActiveEvent stEvent;
	stEvent.m_unTaskID = unTaskID;
	std::set<ActiveEvent, TaskComp>::iterator itSet = m_setDailyTask.find(stEvent);
	if (itSet == m_setDailyTask.end() || itSet->m_byTaskStatus != TASK_STATUS_FINISHED)
	{
		return false;
	}
	std::map<ACE_UINT32, ActivenessInfo> &refActivenessInfo = GAME_CONFIG_INSTANCE::instance()->m_oActivenessList;
	std::map<ACE_UINT32, ActivenessInfo>::iterator itMap = refActivenessInfo.find((*itSet).m_unTaskID);
	if (itMap != refActivenessInfo.end())
	{
		m_map->get_reward_from_config_reward(oRewardInfo, itMap->second.stReward, 1, 1);
		//-----------log日志
		//每日任务
		LogItemInfo logInfo;
		logInfo.m_op_action = enum_LOG_ACTION::LOG_ACTION_daily_Single_task;//动作原因
		logInfo.SetOp_Way(_LOG_OP_WAY_daily_Single_task);//途径(附加信息)
		m_map->get_reward(oRewardInfo,logInfo);
		(*itSet).m_byTaskStatus = TASK_STATUS_REWARED;
		m_unActivenessPoints += itMap->second.unActivenessPoints;
		unActivenessChanged = itMap->second.unActivenessPoints;
		update_2_db((*itSet).m_unTaskID, (*itSet).m_unCurrentProgress, (*itSet).m_byTaskStatus);
		return true;
	}

	return false;
}


int DailyTaskMgr::GetReward(ACE_UINT32 unActivenessPoints, RewardInfo &oRewardInfo)
{
	m_map->CheckDateChanged();
	std::map<ACE_UINT32, ConfigReward> &refActivenessReward = GAME_CONFIG_INSTANCE::instance()->m_oActivenessReward;
	if (unActivenessPoints > m_unActivenessPoints)
	{
		return ERROR_MSG_PROSS_ERROR;
	}
	std::map<ACE_UINT32, ConfigReward>::iterator itMap = refActivenessReward.find(unActivenessPoints);
	if (itMap != refActivenessReward.end() && m_setObtainedActivenessReward.count(unActivenessPoints) == 0)
	{
		m_map->get_reward_from_config_reward(oRewardInfo, itMap->second, 1, 1);
		//-----------log日志
		//每日任务
		LogItemInfo logInfo;
		logInfo.m_op_action = enum_LOG_ACTION::LOG_ACTION_daily_task;//动作原因
		logInfo.SetOp_Way(_LOG_OP_WAY_daily_task);//途径(附加信息)
		m_map->get_reward(oRewardInfo,logInfo);
		m_setObtainedActivenessReward.insert(unActivenessPoints);
		insert_obtained_2_db(unActivenessPoints);
		/*MsgObtainedActivenessReward obtained;
		obtained.nResult = 0;
		obtained.unObtainedCount = 0;
		std::set<ACE_UINT32>::iterator itSet = m_setObtainedActivenessReward.begin();
		for (;obtained.unObtainedCount<MAX_ACTIVENESS_COUNT && itSet != m_setObtainedActivenessReward.end();++itSet)
		{
			obtained.obtainedList[obtained.unObtainedCount++] = *itSet;
		}
		m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_OBTAINED_ACTIVENESS_REWARD, (char *)&obtained, sizeof(MsgObtainedActivenessReward), OBJ_ID_NONE, ADAPTER_GATEWAY_MGR, m_map->m_unUserID);*/
		return 0;
	}

	return ERROR_MSG_ACTIVE_GOT;
}

bool DailyTaskMgr::AddTask(ACE_UINT32 unNewTaskID)
{
	m_map->CheckDateChanged();
	std::map<ACE_UINT32, ActivenessInfo> &refActivenessInfo = GAME_CONFIG_INSTANCE::instance()->m_oActivenessList;
	std::map<ACE_UINT32, ActivenessInfo>::iterator itMap = refActivenessInfo.find(unNewTaskID);
	if (itMap != refActivenessInfo.end())
	{
		if (itMap->second.unLevelCase <= m_map->m_unLevel)
		{
			ActiveEvent stEvent;
			stEvent.m_unTaskID = unNewTaskID;
			stEvent.m_unActiveEventType = itMap->second.unActiveEventType;
			if (m_setDailyTask.insert(stEvent).second)
			{
				insert_2_db(stEvent.m_unTaskID, stEvent.m_unCurrentProgress, stEvent.m_byTaskStatus);
				return true;
			}
		}
	}
	return false;
}

void DailyTaskMgr::BuildTaskListPkg(MsgTaskList &response)
{
	m_map->CheckDateChanged();
	std::set<ActiveEvent, TaskComp>::iterator itSet = m_setDailyTask.begin();
	response.iTaskNum = 0;
	response.iListType = TASK_LIST_DAILY;
	memset(&response.taskInfo, 0, sizeof(TaskInfo) * MAX_CURRENT_TASK_COUNT);
	for (int i=0;i<MAX_CURRENT_TASK_COUNT&&itSet!=m_setDailyTask.end();++itSet,++i)
	{
		response.taskInfo[i].unTaskID = (*itSet).m_unTaskID;
		response.taskInfo[i].unCurrentProgress = (*itSet).m_unCurrentProgress;
		response.taskInfo[i].byStatus = (*itSet).m_byTaskStatus;
		++response.iTaskNum;
	}

	m_isHaveNew = false;
}


void DailyTaskMgr::update_2_db(ACE_UINT32 m_unTaskID, ACE_UINT32 m_unProgress, ACE_Byte m_byStatus)
{
	MsgDBUpdateTaskInfoRequest db_request;
	db_request.m_taskInfo.byStatus = m_byStatus;
	db_request.m_taskInfo.unTaskID = m_unTaskID;
	db_request.m_taskInfo.unCurrentProgress = m_unProgress;
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_TASK_LIST, (char *)&db_request, sizeof(MsgDBUpdateTaskInfoRequest));
}

void DailyTaskMgr::insert_2_db(ACE_UINT32 m_unTaskID, ACE_UINT32 m_unProgress, ACE_Byte m_byStatus)
{
	MsgDBUpdateTaskInfoRequest db_request;
	db_request.m_taskInfo.byStatus = m_byStatus;
	db_request.m_taskInfo.unTaskID = m_unTaskID;
	db_request.m_taskInfo.unCurrentProgress = m_unProgress;
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_INSERT_TASK_LIST, (char *)&db_request, sizeof(MsgDBUpdateTaskInfoRequest));
}

void DailyTaskMgr::insert_obtained_2_db(ACE_UINT32 unActivenessPoints)
{
	MsgDBInsertObtainedActivenessRewardRequest db_request;
	db_request.m_unObtainedActivenessReward = unActivenessPoints;
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_INSERT_OBTAINED_ACTIVENESS_REWARD, (char *)&db_request, sizeof(MsgDBInsertObtainedActivenessRewardRequest));
}