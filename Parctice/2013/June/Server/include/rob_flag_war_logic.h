/****************************************************************
 * Filename: rob_flag_war_logic.h
 * 
 * Description: 帮派夺旗战逻辑
 *
 * Original Author : bison, 2013-4-12
 *
 ****************************************************************/

#ifndef _ROB_FLAG_WAR_LOGIC_H_
#define _ROB_FLAG_WAR_LOGIC_H_

#include "hero.h"
#include "guild.h"
#include "guild_asist.h"
#include "rob_flag_war.h"
#include "command_other_function_all_over.h"
#include "camp_leader_and_chief.h"

#define MAX_ROB_FLAG_WAR_ROOM_NUM		12

class RobFlagWarLogic
{
private:
	map<string, RobFlagWar*> allRobFlagWarRooms;
	vector<RobFlagWar*> idleRobFlagWarRooms;
	bool isInRobFlagWarTime;
	
	//func
	int basicHeroCheck();
	int oneJoin(RobFlagWar* room, Hero* hero);
	
	int pickFlagCheck(Hero *hero, int brandType);
public:
	RobFlagWarLogic();
	RobFlagWar* roomId_2_room(char *roomId);
	
	void startRoomTimer(RobFlagWar *room);
	void stopRoomTimer(RobFlagWar *room);
	int getRoomTimerRemain(RobFlagWar *room);
	
	int viewRoomState(Hero *hero, char* result);
	
	int joinRoom(Hero *hero, char *roomId = NULL, char *password = NULL, int channel = 0);
	
	void enterMap(Map_Inform* scene, Hero *hero, int group);
	
	void exitMap(Hero* hero);
	
	
	int exitRoom(Hero* hero, bool offFlag);
	
	int callJoin(Hero* hero);
	
	void updateRoomJoinList(RobFlagWar* room);
	
	void informHostPrepare(RobFlagWar* room, int group);
	
	void robFlagSendRomMsg(RobFlagWar* room, char *msg, int group = 2);
	
	void sendOutRobWarMsg(Hero* hero);
	
	void resetRoom(RobFlagWar* room);
	
	void gameOver(RobFlagWar* room, int awayGroup = -1);
	
	void giveAward(RobFlagWar* room, int winIndex);
	
	void chgHost(RobFlagWar* room, int group);
	
	int revival(Hero* hero);
	
	bool IspickOk(Hero *hero, int brandType);
	
	int stopPicking(Hero* hero);
	
	int finishPick(Hero *hero, int brandType);
	
	int stopBring(Hero* hero);
	
	bool scorePlaceCheck(Hero *hero, int group = 2);
	
	int bringFlagBack(Hero *hero);
	
	int prepare(Hero* hero);
	//设置是否在夺旗战时间
	void setIsInRobFlagWarTime(bool start);
	
};

extern RobFlagWarLogic *robFlagWarManage;
#endif