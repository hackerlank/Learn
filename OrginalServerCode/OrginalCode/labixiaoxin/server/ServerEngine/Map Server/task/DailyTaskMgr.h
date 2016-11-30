#pragma once

#include "ace/ace.h"
#include "../module/BaseModule.h"
#include <set>
#include "../../GameBase/Common/GameUtils.h"

/*struct DateChangedDataBase
{
	//ACE_UINT32 m_unDateTime;
	virtual void Reset() = 0;
	bool CheckDateChanged(ACE_UINT32 &unDateTime)
	{
		ACE_UINT32 unCurrentUTC = GameUtils::get_utc();
		if (GameUtils::get_day_different(unCurrentUTC, unDateTime) > 0)
		{
			this->Reset();
			unDateTime = unCurrentUTC;
			return true;
		}
		else
		{
			return false;
		}
	}
};*/

class DailyTaskMgr : public BaseModule/*, public DateChangedDataBase*/
{
public:
	DailyTaskMgr() {m_unActivenessPoints = 0;m_isHaveNew = false;}
	virtual ~DailyTaskMgr() {};
	
	void Reset();

	void Init(MsgDBTaskList *info);

	void InitObtainedReward(MsgDBObtainedActivenessRewardList *info);

	bool RefreshTask(ACE_UINT32 unTaskType, ACE_UINT32 unAttachID,int multEnergy = 1);
	bool GetSingleTaskReward(ACE_UINT32 unTaskID, RewardInfo &oRewardInfo, ACE_UINT32 &unActivenessChanged);
	int GetReward(ACE_UINT32 unActivenessPoints, RewardInfo &oRewardInfo);
	bool AddTask(ACE_UINT32 unNewTaskID);

	void BuildTaskListPkg(MsgTaskList &response);

	UINT32 m_unActivenessPoints;
	std::set<ACE_UINT32> m_setObtainedActivenessReward;

	bool m_isHaveNew;//ºìµã
private:
	void insert_obtained_2_db(ACE_UINT32 unActivenessPoints);
	void update_2_db(ACE_UINT32 m_unTaskID, ACE_UINT32 m_unProgress, ACE_Byte m_byStatus);
	void insert_2_db(ACE_UINT32 m_unTaskID, ACE_UINT32 m_unProgress, ACE_Byte m_byStatus);
	std::set<ActiveEvent, TaskComp> m_setDailyTask;
};