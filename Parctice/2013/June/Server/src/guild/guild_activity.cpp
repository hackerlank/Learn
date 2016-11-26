#include"guild_activity.h"
#include"my_time.h"

//帮派活动构造
GuildActivity::GuildActivity(char* _id, int limit, set<ActivityTime_T*> _timeSet)
{
	strncpy(id, _id, strlen(_id) + 1);
	guildLevelLimit = limit;
	timeSet = _timeSet;
}

char* GuildActivity::getId()
{
	return id;
}

int GuildActivity::getLevelLimit()
{
	return guildLevelLimit;
}

bool GuildActivity::isInGuildActTime()
{
	set<ActivityTime_T*>::iterator it;
	it = timeSet.begin();
	for(it; it != timeSet.end(); it++)
	{
		ActivityTime_T* timeAct = (*it);
		if (MY_WEEK_DAY == timeAct->weekDay)
		{
			int realTime = MY_HOUR * 60 + MY_MIN;
			int beginTime = timeAct->beginHour * 60 + timeAct->beginMin;
			int endTime = timeAct->endHour * 60 + timeAct->endMin;
			if (realTime >= beginTime && realTime < endTime)
			{
				return true;
			}
		}
	}
	return false;
}

set<ActivityTime_T*> GuildActivity::getTimeSet()
{
	return timeSet;
}