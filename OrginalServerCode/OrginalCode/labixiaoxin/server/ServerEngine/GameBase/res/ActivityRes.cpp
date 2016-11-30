#include "ActivityRes.h"
#include "ItemResMgr.h"

ActivityRes::ActivityRes(ACE_UINT32 unType)
:BaseRes(unType)
{
	m_unStartTime = 0;
	m_unEndTime = 0;
	m_unRelatedCount = 0;

	m_unWeekFlag = 0;
	//m_unDayStartTime = 0;
	//m_unDayEndTime = 0;
	m_unPeriodCount = 0;

	ACE_OS::memset(m_relatedList, 0, sizeof(ACE_UINT32) * MAX_RELATED_ID_PER_ACTIVITY);
	ACE_OS::memset(m_periodList, 0, sizeof(ActivityPeriod) * MAX_ACTIVITY_PERIOD);
}

ActivityRes::~ActivityRes()
{

}

int ActivityRes::parse_xml_node(xmlNodePtr node)
{
	BaseRes::parse_xml_node(node);

	if(xmlStrcasecmp(node->name, BAD_CAST"start_time") == 0)
	{
		m_unStartTime = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"end_time") == 0)
	{
		m_unEndTime = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	/*
	else if(xmlStrcasecmp(node->name, BAD_CAST"start_everyday") == 0)
	{
		m_unDayStartTime = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"end_everyday") == 0)
	{
		m_unDayEndTime = ACE_OS::atoi((char *)xmlNodeGetContent(node));
	}
	*/
	else if(xmlStrcasecmp(node->name, BAD_CAST"last_time") == 0)
	{
		parse_period_list((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"week_circle") == 0)
	{
		parse_week_flag((char *)xmlNodeGetContent(node));
	}
	else if(xmlStrcasecmp(node->name, BAD_CAST"related_id") == 0)
	{
		parse_related_list((char *)xmlNodeGetContent(node));
	}
	
	return 0;
}

void ActivityRes::process_res_id_by_name()
{
}

void ActivityRes::parse_related_list(char *str)
{
	m_unRelatedCount = 0;

	int len = strlen(str);

	char tmp[64];
	
	int offset = 0;
	int c = 0;

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		//m_relatedList[c] = ACE_OS::strtol(tmp, NULL, 16);
		m_relatedList[c] = GameUtils::parse_res_id(tmp);

		c ++;
	}

	m_unRelatedCount = c;
}

void ActivityRes::parse_week_flag(char *str)
{
	int len = strlen(str);

	char tmp[64];
	
	int offset = 0;
	int idx;

	m_unWeekFlag = 0;

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		idx= ACE_OS::atoi(tmp)/* - 1*/;

		m_unWeekFlag = m_unWeekFlag | (1 << idx);
	}
}

void ActivityRes::parse_period_list(char *str)
{
	int len = strlen(str);

	char tmp[64];
	
	int offset = 0;
	//int idx;

	m_unPeriodCount = 0;

	int c = 0;

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ';');

		parse_period(tmp, m_periodList[c]);
		c ++;
	}

	m_unPeriodCount = c;
}

void ActivityRes::parse_period(char *str, ActivityPeriod &period)
{
	ACE_OS::memset(&period, 0, sizeof(ActivityPeriod));

	int len = strlen(str);

	char tmp[64];
	
	int offset = 0;
	int c = 0;

	while(offset != -1)
	{
		offset = GameUtils::value_token(str, offset, len, tmp, ',');

		if(c == 0)
		{
			period.unStart = ACE_OS::atoi(tmp);
		}
		else
		{
			period.unEnd = ACE_OS::atoi(tmp);
		}

		c ++;
	}
}

bool ActivityRes::is_activity_online(ACE_UINT32 unCurrentTime, ACE_UINT32 unTimes)
{
	int week = GameUtils::get_week(unCurrentTime);

	if((m_unWeekFlag & (1 << week)) == 0)
	{
		return false;
	}

	int day = GameUtils::get_day_time(unCurrentTime);

	if (unTimes != (ACE_UINT32)-1)
	{
		if (unTimes < m_unPeriodCount)
			return day >= m_periodList[unTimes].unStart && day <= m_periodList[unTimes].unEnd;
	}
	else
	{
		for(ACE_UINT32 i = 0;i < m_unPeriodCount;i ++)
		{
			if(day >= m_periodList[i].unStart && day <= m_periodList[i].unEnd)
			{
				return true;
			}
		}
	}

	return false;
}