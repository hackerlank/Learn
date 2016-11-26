#ifndef _CAMP_RES_WAR_H_
#define _CAMP_RES_WAR_H_

#include"hero.h"
#include"map_src.h"

#define	CAMP_RES_ROOM_MAX_HERO_NUM			3
#define CAMP_RES_ROOM_MAX_CAMP_NUM			1


#define CAMP_RES_WAR_IDLE_STATE				0
#define CAMP_RES_WAR_PREPARE_STATE			1
#define CAMP_RES_WAR_START_STATE			2
#define CAMP_RES_WAR_OVER_STATE				3


typedef struct INT
{
	int a;
	INT (int x)
	{
		a = x;
	}

	bool operator < (const INT &val) const
	{
		return (a >= val.a);
	}
	operator int() const
	{
		return a;
	}

}INT;

typedef struct CampResWarReward_S
{
	char heroId[51];
	int money;
	int prestige;
	char goodsId[51];
	CampResWarReward_S(char *hid, int mny, int ptg, char *gid)
	{
		strncpy(heroId, hid, sizeof heroId);
		money = mny; 
		prestige = ptg;
		if (gid != NULL)
		{
			strncpy(goodsId, gid, sizeof goodsId);
		} else {	
			memset(goodsId, 0, sizeof goodsId);
		}
	}
}CampResWarReward_T;

typedef struct RankReward_S
{
	int minScore;
	int money;
	int prestige;
	char goodsId[51];
} RankReward_T;

//阵营资源战控制
typedef struct CRW_Control_S
{
	int brushNumPerTimes;
	int pickScore;
	int perCampLimitHeros;
	int roomLimitHeros;
	int prepareTime;
	int pkTime;
	int brushTime;
	int rewardTime;
	Location_T from;
	int winCampRewardMinScore;
	int winCampRewardMoney;
	int winCampRewardPtg;
	int joinRewardMoney;
	int joinRewardPtg;
	int resNumRewardMoneyBase;
	int resNumRewardPtgBases;
	RankReward_T rankReward[3];
}CRW_Control_T;

extern CRW_Control_T campResWarCtl;

class CampResWar
{
private:
	map<string, int> heroId_2_resNum[3];
	map<INT, string> rankAll;
	int totalJoinNum;
	int remainResCnt;
	int perCampJoinNum[3];
	int perCampResCnt[3];
	int isWinnerCamp[3];
	
	ev_timer roomCtlTimer;
	ev_timer brushResTimer;
	int index;
	int times;							//资源刷新次数
	int roomState;
	int timeState;
	char mapId[51];
	Map_Src* scene;
public:
	CampResWar();
	~CampResWar();
	
	void create(int index, Map_Src* mapPtr);
	void reset();
	//房间开启
	void open();
	//判断房间是否开启
	bool isOpen();
	//获取房间号
	int getRoomIndex();
	//获取房间状态
	int getRoomState();
	//获取房间时间状态
	int getTimeState();
	//获取房间人数(0 ~ 2:获取每个阵营加入人数；3:获取总人数)
	int getJoinNum(int index);
	bool canHeroJoin();
	int join(Hero *hero, int &openNext);
	int exit(Hero* hero);
	//更新房间信息
	void update_room_infor();
	//房间内发送消息
	void send_room_msg(char *msg, int flag = 3, int tag = 0);
	//定时器剩余时间
	int getCtlTimerRemain();
	//刷新时间剩余
	int getBrushTimerRemain();
	//开启准备计时
	void startPrepareTimer();
	//开启战斗计时
	void startPkTimer();
	//开启刷资源计时
	void startBrushTimer();
	//开启房间重置计时
	void startResetTimer();
	//停止刷资源定时器
	void stopBrushTimer();

	
	//资源战开始
	void start();
	//刷出资源
	int brush();
	//资源战结束
	void over();
	//奖励
	void award();
	//房间清场
	void clear();
	//资源采集
	int collect(Hero* hero);
	//杀人抢劫
	int kill(Hero* atker, Hero* atked);
	//复活
	int revival(Hero* hero);
	
	int viewResNum(Hero* hero, char* heroId);
	
};

#endif