#pragma once

#include "ace/ace.h"
#include "BaseModule.h"
//#include "../../Base/Observer/Observer.h"
//#include "../task/ActiveEvent.h"
#include <set>

class TaskMgr : public BaseModule
{
public:
	TaskMgr();
public:
	void init(MsgDBTaskList *info);

	bool AddTask(ACE_UINT32 unNewTaskID);
	bool RefreshTask(ACE_UINT32 unTaskType, ACE_UINT32 unAttachID,int multEnergy = 1);
	bool RefreshTaskEx(ACE_UINT32 unTaskType, ACE_UINT32 unAttachID,int multEnergy = 1);//闯关副本
	bool RefreshTaskEx(ACE_UINT32 unTaskType, TaskConfig &task,int multEnergy = 1);//闯关副本
	bool GetReward(ACE_UINT32 unTaskID, RewardInfo &oRewardInfo);

	void BuildTaskListPkg(MsgTaskList &response);

	bool ChickPreMissionIsComplete(ACE_UINT32 unNewTaskID);//判断前置任务是否完成

	bool m_isHaveNew;
private:
	//void update_2_db(ACE_UINT32 m_unTaskID, ACE_UINT32 m_unProgress, ACE_Byte m_byStatus);
	//void insert_2_db(ACE_UINT32 m_unTaskID, ACE_UINT32 m_unProgress, ACE_Byte m_byStatus);
	//void delete_2_db(ACE_UINT32 m_unTaskID);
	void update_2_db();
	std::set<ActiveEvent, TaskComp> m_setCurrentTask;
	std::map<ACE_UINT32, ActiveEvent> m_mapSendTaskList;
};