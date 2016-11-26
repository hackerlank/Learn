/****************************************************************
 * Filename: rob_flag_war.h
 * 
 * Description: 帮派夺旗战
 *
 * Original Author : bison, 2013-4-12
 *
 ****************************************************************/

#ifndef _ROB_FLAG_WAR_H_
#define _ROB_FLAG_WAR_H_

#include "libev.h"
#include "map_src.h"
#include "my_time.h"


#define ROB_FLAG_WAR_ROOM_IDLE_STATE 			0
#define ROB_FLAG_WAR_ROOM_OCCUPY_STATE			1
#define ROB_FLAG_WAR_ROOM_LOCK_STATE			2
#define ROB_FLAG_WAR_ROOM_PREPARE_STATE			3
#define ROB_FLAG_WAR_ROOM_READY_STATE			4
#define ROB_FLAG_WAR_ROOM_START_STATE			5
#define ROB_FLAG_WAR_ROOM_OVER_STATE			6

#define ROB_FLAG_WAR_FLAG_INVALID_STATE			0
#define ROB_FLAG_WAR_FLAG_IDLE_STATE			1
#define ROB_FLAG_WAR_FLAG_PICKING_STATE			2
#define ROB_FLAG_WAR_FLAG_BRING_STATE			3

// #define ROB_FLAG_WAR_HERO_NO_MOVE_STATE			0
#define ROB_FLAG_WAR_HERO_IDLE_STATE			0
#define ROB_FLAG_WAR_HERO_PICKING_STATE			1
#define ROB_FLAG_WAR_HERO_BRING_STATE			2


typedef struct RobFlagWarReward_S
{
	int money;
	int glory;
	int prestige;
	int reserved;
}RobFlagWarReward_T;

typedef struct RobFlagWarControl_S
{
	int quickStartNeedHeroNum;
	int scoreRadius;
	int lockTime;
	int prepareTime;
	int readyTime;
	int pkTime;
	int rewardTime;
	int flagScore;
	Location_T scorePlace[2];
	RobFlagWarReward_T winGuildReward;
	RobFlagWarReward_T loseGuildReward;
	RobFlagWarReward_T encourageReward;
	
} RobFlagWarControl_T;

extern RobFlagWarControl_T robFlagWarCtl;

//帮战中每个成员的统计信息  
typedef struct RobFlagWarHeroData_S
{
	int index;			//在数组中对应的下标
	char heroId[51];
	char nickName[51];
	char party[2];
	int level;
	int heroState;
	
	int nextFreeIndex;
	
	void init()
	{
		memset(heroId, 0, sizeof heroId);
		memset(nickName, 0, sizeof nickName);
		memset(party, 0, sizeof party);
		level = 0;
		heroState = ROB_FLAG_WAR_HERO_IDLE_STATE;
	}
}RobFlagWarHeroData_T;

typedef struct RobFlagWarData_S
{
	char guildName[51];
	int guildRank;					//帮派排名
	char hostId[51];
	int joinNum;
	bool isPrepare;
	unsigned callFreqCtl;			//召唤频率控制(记录上次召唤时间)
	int robTimes;					//抢下旗帜次数
	int robSuccessTimes;			//成功抢回旗帜次数
	int totalScore;					//总积分
	int flagState;					//旗帜状态		0:初始状态；1:在大本营；2:正在被抢中；3:被抢着
	char flagOwnerId[51];			//旗帜主人
	
	
	//这个不是我想搞这么复杂，仅仅是为了以后可扩展考虑，尽管目前它里面狗屁数据没有
	RobFlagWarHeroData_T
		warCount[MAX_GUILD_MEMBS];	//帮战统计信息
	int firstFreeIndex;				//统计信息数组的第一个可使用下标
	map<string, RobFlagWarHeroData_T*>
		heroId_2_countInfo;			//角色ID对应的统计数据
	
	void init()
	{
		memset(guildName, 0, sizeof guildName);
		memset(hostId, 0, sizeof hostId);
		memset(flagOwnerId, 0, sizeof flagOwnerId);
		joinNum = 0;
		guildRank = 0;
		isPrepare = false;
		callFreqCtl = MY_TV_SEC;
		robTimes = 0;
		robSuccessTimes = 0;
		flagState = ROB_FLAG_WAR_FLAG_INVALID_STATE;
		totalScore = 0;
		firstFreeIndex = 0;
		heroId_2_countInfo.clear();
		
		int i = 0;
		for (i; i < MAX_GUILD_MEMBS - 1; i++)
		{
			warCount[i].init();
			
			warCount[i].index = i;
			warCount[i].nextFreeIndex = i + 1;
		}
		warCount[i].nextFreeIndex = GUILD_END_FLAG;
	}
} RobFlagWarData_T;


class RobFlagWar
{
private:
	//data
	char roomId[51];
	Map_Inform *scene;
	int roomState;						//房间状态
	int winIndex;						//获胜方下标
	char password[18];					//也是扩展用的
	ev_timer timer;						//房间控制定时器
	RobFlagWarData_T groupData[2];		//参战双方数据
	
	//func
	void initRoomData();
	
public:
	
	//房间初始化
	RobFlagWar(int num, Map_Inform *mapRoom);
	void reset();
	
	char* getRoomId();
	Map_Inform* getScene();
	int getRoomState();
	int getWinIndex();
	char *getPassword();
	ev_timer* getTimer();
	
	char *getGuildName(int group);
	char *getHostId(int group);
	int getJoinNum(int group);
	bool getIsPrepare(int group);
	int getCallFreqCtl(int group);
	int getRobTimes(int group);
	int getRobSuccessTimes(int group);
	int getTotalScore(int group);
	int getFlagState(int group);
	char* getFlagOwner(int group);
	void viewOneGroupMsg(int group, char *result);
	
	map<string, RobFlagWarHeroData_T*> *getJoinList(int group);
	
	void setRoomState(int state);
	void setFlagState(int group, int state, char *ownerId = NULL);
	
	void setIsPrepare(int group, bool prepare);
	void setcallFreqCtl(int group);
	void addScore(int group);
	void initOneGroup(int group, int guildRank = 0, char *guildName = NULL, char *hostId = NULL);
	void brushFlag(int group);
	void setWinIndex(int winIndex);
	void setPassword(char *password = NULL);
	void setHostId(int group, char *id);
	
	int groupJudge(char *guildName);
	int heroGroupJudge(char *heroId);
	int judgeWin();
	bool isLock();
	bool pwdCheckOk(char *password);
	
	int addOneMem(int group, char *heroId, char *nickName, char *party, int level);
	int delOneMem(int group, char *heroId);
	
	
};

#endif