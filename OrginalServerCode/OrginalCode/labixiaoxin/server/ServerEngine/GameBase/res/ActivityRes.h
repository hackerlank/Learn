#pragma once

#include "BaseRes.h"

typedef struct tagActivityPeriod
{
	ACE_UINT32 unStart;
	ACE_UINT32 unEnd;
}ActivityPeriod;

#define MAX_ACTIVITY_PERIOD 8

class ActivityRes : public BaseRes
{
public:
	ActivityRes(ACE_UINT32 unType);
	virtual ~ActivityRes();

	virtual int parse_xml_node(xmlNodePtr node);
	virtual void process_res_id_by_name();

	bool is_activity_online(ACE_UINT32 unTime, ACE_UINT32 unTimes);

	ACE_UINT32 m_unStartTime;
	ACE_UINT32 m_unEndTime;

	//ACE_UINT32 m_unDayStartTime;
	//ACE_UINT32 m_unDayEndTime;

	ACE_UINT32 m_unPeriodCount;
	ActivityPeriod m_periodList[MAX_ACTIVITY_PERIOD];

	ACE_UINT32 m_unWeekFlag;

	ACE_UINT32 m_unRelatedCount;
	ACE_UINT32 m_relatedList[MAX_RELATED_ID_PER_ACTIVITY];

private:
	void parse_related_list(char *str);
	void parse_week_flag(char *str);
	void parse_period_list(char *str);
	void parse_period(char *str, ActivityPeriod &period);
};