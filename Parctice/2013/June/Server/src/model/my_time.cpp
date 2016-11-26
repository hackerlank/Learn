#include"my_time.h"
#include"vip.h"
#include"guild_war_asist.h"
#include"guild_asist.h"
#include "rankInfoAsist.h"
#include "campWarManagement.h"
#include"mapAction.h"
#include "systemMessage.h"
#include"dailyActive.h"
#include"activeAsist.h"
#include"function_read_configuration_files.h"
#include "recharge_reward.h"
#include "consume_reward.h"
#include "system_activity_reward_assist.h"
#include "goods_use_reward.h"
#include "rankInfoAsist.h"

extern GuildWarAsist *guildWarManage;			//帮派战管理
extern campWarManagement campWarController;
extern bool flgActiveBoss;
extern map<string,string> timeToDailyActiveId;
extern map<string,DailyActive*> dailyActiveConfMap;
extern int expTimesForActive;
extern int yabiaoDouble;							//活动双倍经验,初始值为1,到了活动时间,设为2
extern int shengyanDouble;						//活动双倍经验,初始值为1,到了活动时间,设为2
extern int daguaiDouble;							//活动双倍经验,初始值为1,到了活动时间,设为2
extern ActiveDouble activeDouble;

extern Recharge_reward_time_T reward_time_conf;//时间配置文件；
extern Recharge_reward *recharge_reward_asist;

extern Consume_reward_time_T consume_reward_time_conf;//时间配置文件；
extern Consume_reward *consume_reward_asist;

extern Goods_oper_reward_T flowers_send_reward_detail;//送鲜花奖励
extern Goods_oper_reward_T flowers_gain_reward_detail;//得到鲜花奖励
extern Goods_use_reward* goods_use_reward_asist;
extern bool isSetDishTodayActiveFlg;

extern struct tm* timeNow;

void initHappyManageTimer(int time);

void recharge_reward_cb();
void consume_reward_cb();
void goods_opr_reward_cb();

static void myTimer_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	gettimeofday(&myTime, NULL);
	
	// guildRank(0);
	// guildRank(1);
	// cout<<"MY_TV_USEC is "<<MY_TV_USEC<<" MY_TV_SEC is "<<MY_TV_SEC<<endl;
	// cout<<"MY_TV_USEC is "<<MY_TV_USEC<<" MY_TV_SEC is "<<MY_TV_SEC<<endl;
	
	timeNow = localtime(&myTime.tv_sec);
	mySecond = timeNow->tm_sec;				//这个秒只做内部判断用，外部不用
	myMin = timeNow->tm_min;				//更新分钟数
	myHour = timeNow->tm_hour;			//更新小时数
	myWeekDay = timeNow->tm_wday;	//更新天

	static int count = 0;
	count++;
	count %= 60;
	
#if 0
	/*一天更新一次*/
	if(myMin % 12 == 0 && count == 0)
	{
		isSetDishTodayActiveFlg = true;
		
		/*设置关闭帮派盛宴活动是否为今天的标记值*/
		setCloseDishTodayActiveFlgTset();
	}
	
	/*一天更新一次*/
	if(myMin % 15 == 0 && count == 0)
	{
		isSetDishTodayActiveFlg = false;
		
		/*设置关闭帮派盛宴活动是否为今天的标记值*/
		setCloseDishTodayActiveFlg();
	}
#endif
	

	/*一天更新一次*/
	if(myHour % 24 == 0 && myMin % 60 == 0 && count == 0)
	{
		isSetDishTodayActiveFlg = false;
		
		/*设置关闭帮派盛宴活动是否为今天的标记值*/
		setCloseDishTodayActiveFlg();
		
		
	}
	
	if (myHour==4 && count == 0)
	{
		saveRankLog();
	}
	
	if ((myMin%5)==0){
		if(count == 0)
		{
			controlActiveOpenAndClose(myHour,myMin,myWeekDay);/*所有的活动控制开启与关闭*/
			setRankInfoToLocal();//每5分钟对下线更新一次排名；
		}
	}
	
	
	if ((myMin%15)==0){
		if(count == 0)
		{
			//热读cdkey配置文件
			int rc = read_files_cdkey("config/cdkey.xml");
			if(rc != 0)
			{
				cout<<"read read_files_cdkey error"<<endl;
			}
		}
	}
	
	
	//TODO 请不要删除，这里测试用，有疑问RTX xhm。	
	// if ((myMin%1)==0 ){	
		// if(count == 0)
		// {
			// cout<<"reward reward reward reward"<<endl;
			// goods_opr_reward_cb();
			// goods_use_reward_asist->send_use_reward();
			// goods_use_reward_asist->send_gain_reward();	
		// }			
	// }
	// if ((myMin%2)==0 ){
		// if(count == 0)
			// campWarController.startApplyLeaderCampWar(time(NULL));
	// }
	/*if (myMin == 0 && myHour == 18){//每周5 19:00开启阵营大乱斗战
	// if ((myMin%10)==8 ){
		if(count == 0)
			campWarController.startOrdinaryCampWar(time(NULL));
	}
	if (myMin == 45 && myHour == 18){//每周7的14:00开启阵营统领争夺战报名
	// if ((myMin%10)==0){
		if(count == 0)
			campWarController.startApplyLeaderCampWar(time(NULL));
	}
	if (myMin ==0 && myHour == 19){//每周6的10:30开启阵营统领争夺战
	// if ((myMin%10)==2){
		if(count == 0)
			campWarController.startLeaderCampWar(time(NULL));
	}
	if (myMin == 0 && myHour == 20){//每周5的10:30开启盟主争夺战
	// if ((myMin%10)==5 ){
		if(count == 0)
			campWarController.startChiefCampWar(time(NULL));
	}*/
	
	if (myMin % 10 == 0)
	{
		//半小时
		if(myMin%30 == 0)
		{
			
			//每半个小时进来3次
			if(count == 0)
			{
				//整小时
				if(myMin % 60 == 0) 
				{
					if (myHour == 12)
					{
						//12点开始娱乐图开启两小时
						initHappyManageTimer(7200);
					}
					if (myHour == 18)
					{
						//18点开始娱乐图开启6小时
						initHappyManageTimer(216000);
					}
#if 0					
					//在此可以加入精确到小时需要激活的活动
					if (myHour == 11 && (myWeekDay == 2 || myWeekDay == 6))
					{
						//帮派战开始
						// if (count % 4 == 0)
						// {
							guildWarManage->setIsInGuildWarTime(true);
						// }
					}
					
					if (myHour == 12 && (myWeekDay == 2 || myWeekDay == 6))
					{
						//帮派战结束	周三和周日11:30帮派战结束
						guildWarManage->setIsInGuildWarTime(false);
					}
#endif					
					//整天
					if(myHour % 24 == 0)
					{
					
						if(count==0)
						{
							//刷新日常
							refreshSrvDaily();
							goods_opr_reward_cb();//物品使用奖励；
							recharge_reward_cb();//充值活动；
							consume_reward_cb();//消费活动；
						}
						// if (count % 5 == 0)
						// {
							//每天24点帮派内日排名
							guildRank(0);
						// }
						// if (count % 2 == 0)
						// {
							//每天24点进行一次全帮派排行
							allGuildRank();
						// }
						
						
						if (myWeekDay == 1)
						{
							// if (count % 6 == 0)
							// {
								//每周进行帮派内周排名
								// guildRank(1);
							// }
							
							//每周对人物排行,宠物排行,坐骑排行前三记录
							rankAnalysis();							
						}						
					}
				}
			}
		}		
	}
	
	//定时开启活动(双倍经验)
	if (timeNow->tm_hour>=activeDouble.yabiao.beginHour&&timeNow->tm_hour<=activeDouble.yabiao.endHour)
	{
		if (timeNow->tm_mon>=activeDouble.yabiao.beginMouth&&timeNow->tm_mon<=activeDouble.yabiao.endMouth)
		{
			if (timeNow->tm_year>=activeDouble.yabiao.beginYear&&timeNow->tm_year<=activeDouble.yabiao.endYear)
			{
				if (activeDouble.yabiao.beginMouth==activeDouble.yabiao.endMouth)
				{
					if (timeNow->tm_mday>=activeDouble.yabiao.beginDay&&timeNow->tm_mday<=activeDouble.yabiao.endDay)
					{
						yabiaoDouble=2;
					}
					else
					{
						yabiaoDouble=1;
					}
				}
				else if (activeDouble.yabiao.beginMouth<activeDouble.yabiao.endMouth)
				{
					if (timeNow->tm_mon==activeDouble.yabiao.endMouth)
					{
						if (timeNow->tm_mday<=activeDouble.yabiao.endDay)
						{
							yabiaoDouble=2;
						}
						else
						{
							yabiaoDouble=1;
						}
					}
					else if (timeNow->tm_mon<activeDouble.yabiao.endMouth)
					{
						yabiaoDouble=2;
					}
					else
					{
						yabiaoDouble=1;
					}
				}
			}
			else
			{
				yabiaoDouble=1;
			}
		}
		else
		{
			yabiaoDouble=1;
		}
	}
	else
	{
		yabiaoDouble=1;
	}
	
	if (timeNow->tm_hour>=activeDouble.daguai.beginHour&&timeNow->tm_hour<=activeDouble.daguai.endHour)
	{
		if (timeNow->tm_mon>=activeDouble.daguai.beginMouth&&timeNow->tm_mon<=activeDouble.daguai.endMouth)
		{
			if (timeNow->tm_year>=activeDouble.daguai.beginYear&&timeNow->tm_year<=activeDouble.daguai.endYear)
			{
				if (activeDouble.daguai.beginMouth==activeDouble.daguai.endMouth)
				{
					if (timeNow->tm_mday>=activeDouble.daguai.beginDay&&timeNow->tm_mday<=activeDouble.daguai.endDay)
					{
						daguaiDouble=2;
					}
					else
					{
						daguaiDouble=1;
					}
				}
				else if (activeDouble.daguai.beginMouth<activeDouble.daguai.endMouth)
				{
					if (timeNow->tm_mon==activeDouble.daguai.endMouth)
					{
						if (timeNow->tm_mday<=activeDouble.daguai.endDay)
						{
							daguaiDouble=2;
						}
						else
						{
							daguaiDouble=1;
						}
					}
					else if (timeNow->tm_mon<activeDouble.daguai.endMouth)
					{
						daguaiDouble=2;
					}
					else
					{
						daguaiDouble=1;
					}
				}
			}
			else
			{
				daguaiDouble=1;
			}
		}
		else
		{
			daguaiDouble=1;
		}
	}
	else
	{
		daguaiDouble=1;
	}
	
	if (timeNow->tm_hour>=activeDouble.shengyan.beginHour&&timeNow->tm_hour<=activeDouble.shengyan.endHour)
	{
		if (timeNow->tm_mon>=activeDouble.shengyan.beginMouth&&timeNow->tm_mon<=activeDouble.shengyan.endMouth)
		{
			if (timeNow->tm_year>=activeDouble.shengyan.beginYear&&timeNow->tm_year<=activeDouble.shengyan.endYear)
			{
				if (activeDouble.shengyan.beginMouth==activeDouble.shengyan.endMouth)
				{
					if (timeNow->tm_mday>=activeDouble.shengyan.beginDay&&timeNow->tm_mday<=activeDouble.shengyan.endDay)
					{
						// cout<<"111111111111111111111111"<<endl;
						shengyanDouble=2;
					}
					else
					{
						// cout<<"22222222222222222222222"<<endl;
						shengyanDouble=1;
					}
				}
				else if (activeDouble.shengyan.beginMouth<activeDouble.shengyan.endMouth)
				{
					if (timeNow->tm_mon==activeDouble.shengyan.endMouth)
					{
						if (timeNow->tm_mday<=activeDouble.shengyan.endDay)
						{
						// cout<<"3333333333333333333333"<<endl;
							shengyanDouble=2;
						}
						else
						{
						// cout<<"444444444444444444444"<<endl;
							shengyanDouble=1;
						}
					}
					else if (timeNow->tm_mon<activeDouble.shengyan.endMouth)
					{
						// cout<<"5555555555555555555555"<<endl;
						shengyanDouble=2;
					}
					else
					{
						// cout<<"6666666666666666666"<<endl;
						shengyanDouble=1;
					}
				}
			}
			else
			{	
			// cout<<"timeNow->tm_year:"<<timeNow->tm_year<<endl;
			// cout<<"activeDouble.shengyan.beginYear:"<<activeDouble.shengyan.beginYear<<endl;
			// cout<<"activeDouble.shengyan.endYear	:"<<activeDouble.shengyan.endYear	<<endl;
						// cout<<"777777777777777777"<<endl;
				shengyanDouble=1;
			}
		}
		else
		{
			// cout<<"timeNow->tm_mon:"<<timeNow->tm_mon<<endl;
			// cout<<"activeDouble.shengyan.beginMouth:"<<activeDouble.shengyan.beginMouth<<endl;
			// cout<<"activeDouble.shengyan.endMouth:"<<activeDouble.shengyan.endMouth<<endl;
						// cout<<"8888888888888888888"<<endl;
			shengyanDouble=1;
		}
	}
	else
	{
						// cout<<"999999999999999999999"<<endl;
		shengyanDouble=1;
	}
	
	
	
	ev_timer_start(loop, think);
	// cout<<myTime.tv_usec<<endl;
}


void recharge_reward_cb(){
	//TODO 不要删除，正是上线后，充值奖励全部由这里触发；
	
	//开启充值奖励；
	if(reward_time_conf.year == timeNow->tm_year+1900 && reward_time_conf.month == timeNow->tm_mon+1 &&\
		reward_time_conf.start_day == timeNow->tm_mday){
		recharge_reward_asist->isActivity=true;
	}	
	
	bool flag=false;//是否触发充值累积奖励
	if(reward_time_conf.year == timeNow->tm_year+1900 && reward_time_conf.month == timeNow->tm_mon+1 &&\
		reward_time_conf.end_day+1 == timeNow->tm_mday){
				flag=true;
	}else if(reward_time_conf.year == timeNow->tm_year+1900 && reward_time_conf.month+1 == timeNow->tm_mon+1 &&\
		timeNow->tm_mday==1){
		if(reward_time_conf.month==1 || reward_time_conf.month==3 || reward_time_conf.month==5 || reward_time_conf.month==7||\
				reward_time_conf.month==8|| reward_time_conf.month==10 ||reward_time_conf.month==12 && reward_time_conf.end_day==31)
			flag=true;
		else if(reward_time_conf.month==4 || reward_time_conf.month==6 || reward_time_conf.month==9 || reward_time_conf.month==11&&\
			reward_time_conf.end_day==30)
				flag=true;
		else if(reward_time_conf.month==2)	
		{
			if((reward_time_conf.year%4==0)&&(reward_time_conf.year%100!=0)||(reward_time_conf.year%400==0))//是闰年
			{
				if(reward_time_conf.end_day==29)//闰年
					flag=true;				
			}else{
				if(reward_time_conf.end_day==28)
					flag=true;								
			}		
		}
	}else if(reward_time_conf.year+1 == timeNow->tm_year+1900 && reward_time_conf.month == 12 && timeNow->tm_mon+1==1&&\
		reward_time_conf.end_day == 31&& timeNow->tm_mday==1){
			flag=true;
		}
		
	if(flag){
			recharge_reward_asist->send_reward();
	} 

}

void consume_reward_cb(){
	//TODO 不要删除，正是上线后，充值奖励全部由这里触发；
	if(consume_reward_time_conf.year == timeNow->tm_year+1900 && consume_reward_time_conf.month == timeNow->tm_mon+1 &&\
		consume_reward_time_conf.start_day == timeNow->tm_mday){
		consume_reward_asist->isActivity=true;		
	}
	
	bool flag=false;//是否触发充值累积奖励
	if(consume_reward_time_conf.year == timeNow->tm_year+1900 && consume_reward_time_conf.month == timeNow->tm_mon+1 &&\
		consume_reward_time_conf.end_day+1 == timeNow->tm_mday){
				flag=true;
	}else if(consume_reward_time_conf.year == timeNow->tm_year+1900 && consume_reward_time_conf.month+1 == timeNow->tm_mon+1 &&\
		timeNow->tm_mday==1){
		if(consume_reward_time_conf.month==1 || consume_reward_time_conf.month==3 || consume_reward_time_conf.month==5 || consume_reward_time_conf.month==7||\
				consume_reward_time_conf.month==8|| consume_reward_time_conf.month==10 ||consume_reward_time_conf.month==12 && consume_reward_time_conf.end_day==31)
			flag=true;
		else if(consume_reward_time_conf.month==4 || consume_reward_time_conf.month==6 || consume_reward_time_conf.month==9 || consume_reward_time_conf.month==11&&\
			consume_reward_time_conf.end_day==30)
				flag=true;
		else if(consume_reward_time_conf.month==2)	
		{
			if((consume_reward_time_conf.year%4==0)&&(consume_reward_time_conf.year%100!=0)||(consume_reward_time_conf.year%400==0))//是闰年
			{
				if(consume_reward_time_conf.end_day==29)//闰年
					flag=true;				
			}else{
				if(consume_reward_time_conf.end_day==28)
					flag=true;								
			}		
		}
	}else if(consume_reward_time_conf.year+1 == timeNow->tm_year+1900 && consume_reward_time_conf.month == 12 && timeNow->tm_mon+1==1&&\
		consume_reward_time_conf.end_day == 31&& timeNow->tm_mday==1){
			flag=true;
		}
		
	if(flag){
			consume_reward_asist->send_reward();
	} 

}


void goods_opr_reward_cb(){
	//开启物品使用奖励
	if(flowers_send_reward_detail.year == timeNow->tm_year+1900 && flowers_send_reward_detail.month == timeNow->tm_mon+1 &&\
		flowers_send_reward_detail.start_day == timeNow->tm_mday){
		// cout<<"88888888888888888888888888"<<endl;
		goods_use_reward_asist->isUseActivity=true;
	}	
	
	if(flowers_gain_reward_detail.year == timeNow->tm_year+1900 && flowers_gain_reward_detail.month == timeNow->tm_mon+1 &&\
		flowers_gain_reward_detail.start_day == timeNow->tm_mday){
		goods_use_reward_asist->isGainActivity=true;
	}
	
	bool flag=false;//是否触发充值累积奖励
	if(flowers_send_reward_detail.year == timeNow->tm_year+1900 && flowers_send_reward_detail.month == timeNow->tm_mon+1 &&\
		flowers_send_reward_detail.end_day+1 == timeNow->tm_mday){
				flag=true;
	}else if(flowers_send_reward_detail.year == timeNow->tm_year+1900 && flowers_send_reward_detail.month+1 == timeNow->tm_mon+1 &&\
		timeNow->tm_mday==1){
		if(flowers_send_reward_detail.month==1 || flowers_send_reward_detail.month==3 || flowers_send_reward_detail.month==5 || flowers_send_reward_detail.month==7||\
				flowers_send_reward_detail.month==8|| flowers_send_reward_detail.month==10 ||flowers_send_reward_detail.month==12 && flowers_send_reward_detail.end_day==31)
			flag=true;
		else if(flowers_send_reward_detail.month==4 || flowers_send_reward_detail.month==6 || flowers_send_reward_detail.month==9 || flowers_send_reward_detail.month==11&&\
			flowers_send_reward_detail.end_day==30)
				flag=true;
		else if(flowers_send_reward_detail.month==2)	
		{
			if((flowers_send_reward_detail.year%4==0)&&(flowers_send_reward_detail.year%100!=0)||(flowers_send_reward_detail.year%400==0))//是闰年
			{
				if(flowers_send_reward_detail.end_day==29)//闰年
					flag=true;				
			}else{
				if(flowers_send_reward_detail.end_day==28)
					flag=true;								
			}		
		}
	}else if(flowers_send_reward_detail.year+1 == timeNow->tm_year+1900 && flowers_send_reward_detail.month == 12 && timeNow->tm_mon+1==1&&\
		flowers_send_reward_detail.end_day == 31&& timeNow->tm_mday==1){
			flag=true;
		}
		
	if(flag){
			// cout<<"999999999999999999999999999"<<endl;
			goods_use_reward_asist->send_use_reward();
	} 
	
	
	flag = false;
	
	if(flowers_gain_reward_detail.year == timeNow->tm_year+1900 && flowers_gain_reward_detail.month == timeNow->tm_mon+1 &&\
		flowers_gain_reward_detail.end_day+1 == timeNow->tm_mday){
				flag=true;
	}else if(flowers_gain_reward_detail.year == timeNow->tm_year+1900 && flowers_gain_reward_detail.month+1 == timeNow->tm_mon+1 &&\
		timeNow->tm_mday==1){
		if(flowers_gain_reward_detail.month==1 || flowers_gain_reward_detail.month==3 || flowers_gain_reward_detail.month==5 || flowers_gain_reward_detail.month==7||\
				flowers_gain_reward_detail.month==8|| flowers_gain_reward_detail.month==10 ||flowers_gain_reward_detail.month==12 && flowers_gain_reward_detail.end_day==31)
			flag=true;
		else if(flowers_gain_reward_detail.month==4 || flowers_gain_reward_detail.month==6 || flowers_gain_reward_detail.month==9 || flowers_gain_reward_detail.month==11&&\
			flowers_gain_reward_detail.end_day==30)
				flag=true;
		else if(flowers_gain_reward_detail.month==2)	
		{
			if((flowers_gain_reward_detail.year%4==0)&&(flowers_gain_reward_detail.year%100!=0)||(flowers_gain_reward_detail.year%400==0))//是闰年
			{
				if(flowers_gain_reward_detail.end_day==29)//闰年
					flag=true;				
			}else{
				if(flowers_gain_reward_detail.end_day==28)
					flag=true;								
			}		
		}
	}else if(flowers_gain_reward_detail.year+1 == timeNow->tm_year+1900 && flowers_gain_reward_detail.month == 12 && timeNow->tm_mon+1==1&&\
		flowers_gain_reward_detail.end_day == 31&& timeNow->tm_mday==1){
			flag=true;
		}
		
	if(flag){
			// cout<<"101010101010101010101010"<<endl;
			goods_use_reward_asist->send_gain_reward();
	} 
}

ev_timer *happyManageTimer;					//娱乐活动定时器
bool isInHappyTime;							//是否在娱乐时间
bool isInFirstRoomHappyTime;				//是否在天下第一楼的娱乐时间
bool isInSecondRoomHappyTime;				//是否在天上人间的娱乐时间
static void happy_manage_cb(struct ev_loop *loop, ev_timer *think, int revents)
{
	isInHappyTime = false;
}

void initHappyManageTimer(int time)
{
	isInHappyTime = true;
	ev_timer_init(happyManageTimer, happy_manage_cb, time, 0);
	ev_timer_start(loops, happyManageTimer);
}

unsigned getHappyRemain()
{
	if (!isInHappyTime)
	{
		return 0;
	}
	return unsigned(ev_timer_remaining(loops, happyManageTimer));
}

void initMyTimer()
{
	myTimer = new ev_timer;
	happyManageTimer = new ev_timer;
	gettimeofday(&myTime, NULL);
	struct tm* timeNow = localtime(&myTime.tv_sec);
	mySecond = timeNow->tm_sec;
	myMin = timeNow->tm_min;
	myHour = timeNow->tm_hour;
	myWeekDay = timeNow->tm_wday;
	ev_timer_init(myTimer, myTimer_cb, 1, 0);
	ev_timer_start(loops, myTimer);
	// initHappyManageTimer();
	//test reinit question
	//ev_timer_init(myTimer, myTimer_cb, 0.1, 0.1);
	//ev_timer_start(loops, myTimer);
	
	/*当服务器开启时，判断哪些活动此时，应该开启*/
	controlActiveOpenStartServer(myHour,myMin,myWeekDay);
}

timeval getMyTime()
{
	return myTime;
}

int getMySecond()
{
	return myTime.tv_sec;
}

int getMyUSecond()
{
	return myTime.tv_usec;
}

void initMyTime()
{
	gettimeofday(&myTime, NULL);
}

bool isSameDayWithNow(int second)
{
	struct tm* todayTm = localtime(&myTime.tv_sec);
	struct tm today;
	memcpy(&today, todayTm, sizeof(tm));
	cout<<"BisonTest: last time is  "<<second<<endl;
	cout<<"BisonTest: now time is "<<MY_TV_SEC<<endl;
	time_t sec = second;
	struct tm* lastTm = localtime(&sec);
	cout<<"BisonSHow today_yday: "<<today.tm_yday<<endl;
	cout<<"BisonSHow last_yday: "<<lastTm->tm_yday<<endl;
	if (today.tm_yday != lastTm->tm_yday || today.tm_year != lastTm->tm_year)
	{
		//如果天数不同或者天数相同年数不同，则这次是今天的第一次登陆）
		return false;
	} else {
		return true;
	}
	
}

bool isNextDayWithNow(int second)		//判断是否是下一天,是下一天返回true,否则返回false
{
	struct tm* todayTm = localtime(&myTime.tv_sec);
	struct tm today;
	memcpy(&today, todayTm, sizeof(tm));
	time_t sec = second;
	struct tm* lastTm = localtime(&sec);
	if (today.tm_yday == (lastTm->tm_yday+1) && today.tm_year == lastTm->tm_year)
	{		
		return true;
	}
	else
	{
		return false;
	}
}


