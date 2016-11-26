
#include<string>
#include<set>
using namespace std;

typedef struct ActivityTime_S
{
	int weekDay;				//活动的日（按每周计算（0-6））
	int beginHour;				//活动开始时数
	int beginMin;				//活动开始分钟数
	int endHour;				//活动结束的时数
	int endMin;					//活动结束分钟数
	
	ActivityTime_S(int wd, int bh, int bm, int eh, int em)
	{
		weekDay = wd;
		beginHour = bh;
		beginMin = bm;
		endHour = eh;
		endMin = em;
	}
}ActivityTime_T;

//帮派活动是所有帮派所共享，不加到帮派的属性里
class GuildActivity
{
	private:
	char id[50 + 1];								//帮派活动的ID
	int guildLevelLimit;							//帮派活动的等级要求
	set<ActivityTime_T*> timeSet;					//活动时间序列
	public:
	GuildActivity(char* _id, int limit, set<ActivityTime_T*> _timeSet);
	
	char* getId();
	int getLevelLimit();
	set<ActivityTime_T*> getTimeSet();
	bool isInGuildActTime();			//是否在该活动时间
	
};