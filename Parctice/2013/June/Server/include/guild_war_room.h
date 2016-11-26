/****************************************************************
 * Filename: guild_war_room.h
 * 
 * Description: 帮战房间类
 *
 * Original Author : bison, 2012-7-23
 *
 ****************************************************************/
#ifndef _GUILD_WAR_ROOM_H_
#define _GUILD_WAR_ROOM_H_
#include"guild.h"
#include"guild_asist.h"
#include "hero.h"
#include "libev.h"
#include"map_src.h"
#include "command_other_function_all_over.h"

#define GWR_IDLE			0			//房间空闲
#define	GWR_ONE				1			//有一个帮派进入房间
#define GWR_LOCK			2			//设置房间密码
#define GWR_TWO				4			//两个帮派进入房间
#define GWR_PREPARE			8			//一个帮派领头按下准备开始
#define GWR_READY			16			//两个帮派领头都按下准备开始
#define GWR_START			32			//战斗开始
#define GWR_OVER			64			//战斗结束

#define GWR_KILL_2_SCORE	10			//杀人数转换积分数	

//统计信息

//帮战中每个成员的统计信息
typedef struct GuildWarCount_S
{
	int index;			//在数组中对应的下标
	int score;			//帮派战积分
	int killNum;
	int ranking;
	char heroId[51];
	int nextFreeIndex;	
}GuildWarCount_T;

//帮派战旗
typedef struct GuildWarFlag_S
{
	int state;					//0:采集前 1:采集中 2:采集完 3:保护成功
	int group;
	char ownerHeroId[51];
	char ownerGuildName[51];
	GuildWarFlag_S()
	{
		state = 0;
		group = -1;
		memset(ownerHeroId, 0, sizeof ownerHeroId);
		memset(ownerGuildName, 0, sizeof ownerGuildName);
	}
	
	void init()
	{
		state = 0;
		group = -1;
		memset(ownerHeroId, 0, sizeof ownerHeroId);
		memset(ownerGuildName, 0, sizeof ownerGuildName);
	}
	
	GuildWarFlag_S(int state, int _group, char* id1, char *id2, char *guildName)
	{
		state = 0;
		group = _group;
		memset(ownerHeroId, 0, sizeof ownerHeroId);
		memset(ownerGuildName, 0, sizeof ownerGuildName);
	}
	
}GuildWarFlag_T;

typedef struct GuildWarReward_S
{
	int money;
	int glory;
	int reserved;
}GuildWarReward_T;

typedef struct GuildWarControl_S
{
	int quickStartNeedHeroNum;
	int lockTime;
	int perpareTime;
	int readyTime;
	int pkTime;
	int rewardTime;
	int protectTime;
	int killScoreOfHero;
	int killScoreOfGuild;
	int flagScoreOfHero[3];
	int flagScoreOfGuild[3];
	GuildWarReward_T joinReward;
	GuildWarReward_T scoreRewardBase;
	GuildWarReward_T winRankReward[4];
	GuildWarReward_T loseRankReward[4];
	
} GuildWarControl_T;

extern GuildWarControl_T guildWarCtl;

class GuildWarRoom
{
private:
	char roomId[IDL + 1];				//房间号
	Map_Inform *scene;					//帮战地图
	char host[2][IDL + 1];				//host[0]:房主，host[1]:房客
	// Guild* warGuild[2];				//参战帮派
	char sideName[2][IDL + 1];			//sideName[0]:主帮名；sideName[1]:客帮名
	int joinNum[2];						//每帮的参与人数
	bool guildPrepare[2];				//帮派开始准备
	unsigned callFreqCtl[2];			//召唤频率控制
	int totalKills[2];					//总的杀人数
	int totalScore[2];					//帮派总积分
	int killLastTime[2];				//杀最后一个人的时间
	int winIndex;						//获胜方下标
	// int guildFlag[3];				//帮派旗状态			 
	GuildWarFlag_T guildFlag[3];		//三个帮战旗
	int groupFlagState[2];				//帮派采了哪些旗
	GuildWarCount_T
		warCount[2][MAX_GUILD_MEMBS];	//帮战统计信息
	int firstFreeIndex[2];				//统计信息数组的第一个可使用下标
	map<string, GuildWarCount_T*>
		heroId_2_countInfo[2];			//角色ID对应的统计数据
	GuildWarCount_T *p_rank[2][MAX_GUILD_MEMBS];		//帮战排行		
	map<string, int> heroId_2_score[2];	//两个帮派的积分统计
	map<int, string> score_2_heroId[2];	//两个帮派的按积分排名
	int roomState;						//房间状态
	char password[18];					//房间密码
	ev_timer timer;						//房间计时器
	ev_timer flagTimer[3];				//旗帜定时器				
	void initRoomInfo();				//初始房间数据
	int addOneGroupMem(int group, char* heroId);		//参战一方增加一个成员
	int delOneGroupMem(int group, char* heroId);		//删除参战一方的一个成员
	void newCompMethod();

public:
	//房间初始化
	GuildWarRoom(int num, Map_Inform *mapRoom);
	//占领房间
	int holdRoom(Hero *hero);
	//召唤加入
	void callJoin(Hero *hero);
	//开始战斗
	int startWar();
	//清除帮派成员
	int remove(char* heroId);
	
	int startDefendFlagTimer(int index);
	
	int stopDefendFlagTimer(int index);
	
	//设置帮会密码
	void lockRoom(char* password);
	//获取房间ID
	char* getId();
	//获取地图
	Map_Inform *getScene();
	//设置房间状态
	void setRoomState(int state);
	//查看房间状态
	int getRoomState(void);
	//解锁房间
	void unlockRoom();
	//检查密码是否正确
	bool isPassOK(char* pass);
	
	//开启锁定房间定时器
	void startLockTimer();
	//停止锁定房间定时器
	void stopLockTimer();
	//开启房间准备定时器
	void startPrepareTimer();
	//终止房间的准备状态
	void stopPrepareTimer();
	//开启就绪定时器
	void startReadyTimer();
	//停止就绪定时器
	void stopReadyTimer();
	//帮战开始计时
	void startStartTimer();
	//开始房间重置定时器计时
	void startResetTimer();
	
	//切入房间地图
	void enterMap(Hero *hero, int group);
	//切出房间地图
	void exitMap(Hero *hero);
	//加入房间
	int joinRoom(Hero *hero);
	//通知帮主可以开始
	void informManagerCanStart(Hero* hero);
	
	//判断玩家所属
	int groupJudge(Hero *hero);
	//玩家的帮会已经占领了该房间
	bool isInThisRoom(char* heroId, int index);
	
	//帮主点击开始按钮
	int prepareGuildWar(Hero *hero);
	//帮派战排名
	void rankGuildWar();
	
	//帮派战玩家杀人数统计，杀人数和统计积分转换比例是1:5000
	void guildWarAddOneHeroKillNum(Hero *hero);
	//帮派战玩家伤害输出统计，伤害值和统计积分转换的比例是1:1
	void guildWarAddHurtCount(Hero *hero, int hurt);
	//分发帮战奖励
	void giveReward();
	//获取房间领头人
	Hero* getHost(int index);
	//获取定时器剩余时间
	int getRemainTime();
	//退出帮派战
	void exit(Hero *hero, bool offlineFlag);
	//向一边的参战人员发消息
	void sendMsgToOneGroup(int group, char* msg, int flag);
	//查看一方帮派房间信息
	int viewOneGuildMsg(int group, char* msg);
	//重置房间
	void resetRoom();
	//帮战中复活
	int revival(Hero* hero);
	//玩家是否可以采集某个旗帜
	int isPickFlagOk(Hero* hero, int index);
	//采旗完成
	int finishPickFlag(Hero* hero, int index);
	//停止采旗
	int stopPickFlag(int index);
	//占据旗帜
	void occupyFlag(int index);
};
#endif
