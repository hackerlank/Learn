/****************************************************************
 * Filename: guild_comm.cpp
 * 
 * Description: 帮派系统的通信
 *
 * Original Author : bison, 2012-8-15
 *
 ****************************************************************/

#include "command_return_define_data.h"
#include "role.h"
#include "guild_asist.h"
#include <arpa/inet.h>
#include"wholeDefine.h"
extern int g_msg_len;
extern Hero* pg_hero;

extern int sock_fd;
extern map<string, Hero*> heroId_to_pHero;

void createGuildComm(char *buffer)
{
	char msg[200] = {0};
	// string msg_head = "12";					//命令头12,0
	// msg = msg + msg_head + intTostring(CREATE_GUILD_RETURN);
	
	char *guildName;						//帮派名
	int mode;								//建帮模式
	int index = 0;								//建帮令在背包中下标
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR(guildName);
	MSG_INT(mode);
	if (mode == 1)
	{
		MSG_INT(index);
	}
	Hero *hero = pg_hero;
	
	//创建帮派返回
	int ret = createGuild(hero, guildName, mode, index);
	cout<<"Create guild return is "<<ret<<endl;
	if (ret == 0)
	{
		sprintf(msg, "12,0,1");
		// msg = msg + intTostring(SUCCESS);
		send_msg(sock_fd, msg);
	} else {
		// msg = msg + intTostring(FAILED); 
		// msg += intTostring(ret);
		sprintf(msg, "12,0,0,%d", ret);
		send_msg(sock_fd, msg);
	}
}

void viewGuildPageRankComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,1
	// msg = msg + msg_head + intTostring(VIEW_GUILD_RANK_PAGE);
	
	char len_arg;     						//参数长度
	int count = 6;
	int net;
	int camp = 3;							//阵营
	int page;								//排行榜页数
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(camp);
	MSG_INT(page);
	
	//查看帮派某页排行榜信息返回
	sprintf(msg, "12,1");
	// sprintf(msg, "12,1");
	int ret = viewGuildRankInfo(page, camp, msg + strlen(msg));
	cout<<"rankInfo is "<<msg<<endl;
	send_msg(sock_fd, msg);
}

//搜索某个帮派
void searchOneGuildComm(char *buffer)
{
	char msg[20480] = {0};
	char msg1[20480] = {0};
	// string msg_head = "12";					//命令头12,2
	// msg = msg + msg_head + intTostring(SEARCH_ONE_GUILD);
	
	char len_arg;     						//参数长度
	int count = 6;
	int net;
	int camp = 3;							//阵营
	char *guildName;						//帮派名
	
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(camp);
	MSG_CHAR_END(guildName);
	
	cout<<"guildName :"<<guildName<<endl;
	
	//搜索某个帮派
	// string ret = searchOneGuild(guildName, camp);
	int ret = searchOneGuild(guildName, camp, msg1);
	if (ret != 0)
	{
		sprintf(msg, "12,2,0");
		//msg += intTostring(FAILED);
	} else {
		//msg += intTostring(SUCCESS);
		//msg += ret;
		sprintf(msg, "12,2,1%s", msg1);
	}
	
	send_msg(sock_fd, msg);
}

void applyJoinGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,3
	// msg = msg + msg_head + intTostring(APPLY_JOIN_GUILD);
	
	char *guildName;						//帮派名
	
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(guildName);
	//申请加入帮派
	int ret = applyJoinGuild(pg_hero, guildName);
	
	if (ret == 0)
	{
		// msg = msg + intTostring(SUCCESS);
		sprintf(msg, "12,3,1");
		send_msg(sock_fd, msg);
	} else {
		sprintf(msg, "12,3,0,%d", ret);
		// msg = msg + intTostring(FAILED); 
		// msg += intTostring(ret);
		send_msg(sock_fd, msg);
	}
}

void viewOneGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,4
	// msg = msg + msg_head + intTostring(VIEW_ONE_GUILD_INFO);
	
	char *guildName;						//帮派名
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(guildName);
	
	//查看某个帮派信息
	sprintf(msg, "12,4");
	int ret = viewOneGuildInfo(guildName, msg + strlen(msg));
	
	// msg += ret;
	send_msg(sock_fd, msg);
}

void viewMyGuildComm(char *buffer)
{
	char msg[4096] = {0};
	memset(msg, 0, sizeof(msg));
	// string msg_head = "12";					//命令头12,5
	// msg = msg + msg_head + intTostring(VIEW_MY_GUILD_INFO);

	//查看自己帮派信息
	sprintf(msg, "12,5");
	int ret = viewMyGuildInfo(pg_hero, msg + strlen(msg));
	// msg += ret;
	send_msg(sock_fd, msg);
}

//升级帮派
void upgradeGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,6
	// msg = msg + msg_head + intTostring(GUILD_UPGRADE_RETURN);
	
	//升级帮派
	int ret = upgradeGuild(pg_hero);
	if (ret == 0)
	{
		// msg += intTostring(SUCCESS);
		sprintf(msg, "12,6,1");
	} else {
		sprintf(msg, "12,6,0,%d", ret);
		// msg += intTostring(FAILED);
	}
	// msg += intTostring(ret);
	send_msg(sock_fd, msg);
	
}

//领取帮派排名奖励
void getGuildRankRewardComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,7
	// msg = msg + msg_head + intTostring(GET_GUILD_RANK_REWARD);
	
	int index = 0;							//奖励项
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(index);
	
	bool ret = getGuildRankReward(pg_hero, index);
	sprintf(msg, "12,7,%d,%d", ret, index);
	// msg = msg + intTostring(ret);
	send_msg(sock_fd, msg);
}

//修改公告
void changeGuildNoticesComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,8
	// msg = msg + msg_head + intTostring(CHANGE_GUILD_NOTICE);
	
	char *notices;							//公告
	int flag = 0;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(flag);
	MSG_CHAR(notices);
	
	//更改帮派公告
	int ret = changeNotices(pg_hero, notices, flag);
	
	if (ret == 0)
	{
		sprintf(msg, "12,8,1,%d", flag);
		// msg += intTostring(SUCCESS);
	} else {
		sprintf(msg, "12,8,0,%d", ret);
		// msg += intTostring(FAILED);
	}
	// msg += intTostring(ret);
	send_msg(sock_fd, msg);
	
}

//退出帮派
void exitGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,9
	// msg = msg + msg_head + intTostring(EXIT_FROM_GUILD);
	
	//帮派退出
	int ret = exitGuild(pg_hero);
	sprintf(msg, "12,9,%d", ret);
	// msg += intTostring(ret);
	send_msg(sock_fd, msg);
}

//查看帮派成员信息
void viewGuildMembsListComm(char *buffer)
{
	char msg[16000] = {0};
	// string msg_head = "12";					//命令头12,10
	// msg = msg + msg_head + intTostring(GUILD_MEMBS_LIST);
	
	
	//查看帮派成员信息
	sprintf(msg, "12,10");
	int ret = viewGuildMembsList(pg_hero, msg + strlen(msg));
	// msg += ret;
	send_msg(sock_fd, msg);
}

//查看帮派申请列表
void viewGuildApplyListComm(char *buffer)
{
	char msg[16000] = {0};
	// string msg_head = "12";					//命令头12,11
	// msg = msg + msg_head + intTostring(GUILD_APPLY_LIST);
	int flag = 0;							//表明是哪个面板发出的申请
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(flag);
	
	//查看帮派成员信息
	sprintf(msg, "12,11,%d", flag);
	int ret = viewGuildApplyList(pg_hero, msg + strlen(msg));
	// msg += intTostring(flag);
	// msg += ret;
	send_msg(sock_fd, msg);
}

//移除帮派
void removeFromGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,12
	// msg = msg + msg_head + intTostring(REMOVE_FROM_GUILD);
	
	char *heroId;							//被移除者Id
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(heroId);
	
	
	//驱逐出帮派
	int ret = driveOutGuild(pg_hero, heroId);
	if (ret == 0)
	{
		sprintf(msg, "12,12,1,%d", ret);
		// msg += intTostring(SUCCESS);
	} else {
		// msg += intTostring(FAILED);
		sprintf(msg, "12,12,0,%d", ret);
	}
	
	// msg += intTostring(ret);
	send_msg(sock_fd, msg);
	
}

//同意加入帮派
void agreeJoinGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,13
	// msg = msg + msg_head + intTostring(AGREE_JOIN_GUILD);
	char *heroId;							//被同意者Id

	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(heroId);
	
	//同意加入帮派
	int ret = agreeOneJoinGuild(pg_hero, heroId);
	if (ret == 0)
	{
		sprintf(msg, "12,13,1,%d", ret);
		// msg += intTostring(SUCCESS);
	} else {
		// msg += intTostring(FAILED);
		sprintf(msg, "12,13,0,%d", ret);
	}
	// msg += intTostring(ret);
	send_msg(sock_fd, msg);
	
}

//拒绝加入帮派
void disagreeJoinGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,14
	// msg = msg + msg_head + intTostring(DISAGREE_JOIN_GUILD);
	
	char *heroId;							//被拒绝者Id

	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(heroId);
	
	//拒绝加入帮派
	int ret = disagreeJoinGuild(pg_hero, 0, heroId);
	sprintf(msg, "12,14,%d", ret);
	// msg += intTostring(ret);
	send_msg(sock_fd, msg);
	
}

//清空帮派申请列表
void clrGuildApplyListComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,15
	// msg = msg + msg_head + intTostring(CLEAR_APPLY_LIST);
	
	//清空帮派申请列表
	bool ret = disagreeJoinGuild(pg_hero, 1);
	// msg += intTostring(ret);
	sprintf(msg, "12,15,%d", ret);
	send_msg(sock_fd, msg);
}

//同意帮派所有申请
void agreeGuildAllApplyComm(char *buffer)
{
	char msg[6400] = {0};
	char msg1[6400] = {0};
	// string msg_head = "12";					//命令头12,26
	// msg = msg + msg_head + intTostring(AGREE_GUILD_ALL_APPLY);
	char *heroId;							//帮主ID
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(heroId);
	
	//同意所有申请者加入帮派
	int ret = agreeAllApply(pg_hero, msg1);
	
	if (ret != 0)
	{
		sprintf(msg, "12,26,0");
		// msg += intTostring(0);
	} else {
		// msg += ret;
		sprintf(msg, "12,26,1%s", msg1);
	}
	
	send_msg(sock_fd, msg);
	
}

//查看帮派技能信息
void viewGuildSkillInfoComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,16
	// msg = msg + msg_head + intTostring(VIEW_GUILD_SKILL_INFO);
	
	//清空帮派申请列表
	sprintf(msg, "12,16");
	int ret = viewGuildSkillInfo(pg_hero, msg + strlen(msg));
	send_msg(sock_fd, msg);
}

//激活帮派技能
void openGuildSkillComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,17
	// msg = msg + msg_head + intTostring(OPEN_GUILD_SKILL);
	
	int index = 0;							//技能项
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(index);
	cout<<"open guild skill and index is "<<index<<endl;
	
	int ret = openGuildSkill(pg_hero, index);
	if (ret == 0)
	{
		sprintf(msg, "12,17,1,%d", index);
		// msg += intTostring(SUCCESS);
		// msg += intTostring(index);
	} else {
		// msg += intTostring(FAILED);
		// msg = msg + intTostring(ret);
		sprintf(msg, "12,17,0,%d", ret);
	}
	send_msg(sock_fd, msg);
}

//升级帮派技能
void upgradeGuildSkillComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,18
	// msg = msg + msg_head + intTostring(UPGRADE_GUILD_SKILL);
	
	int index = 0;							//技能项
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(index);
	
	int ret = upgradeGuildSkill(pg_hero, index);
	if (ret == 0)
	{
		sprintf(msg, "12,18,1");
		// msg += intTostring(SUCCESS);
	} else {
		// msg += intTostring(FAILED);
		// msg = msg + intTostring(ret);
		sprintf(msg, "12,18,0,%d", ret);
	}
	send_msg(sock_fd, msg);
}

//查看帮派历史信息
void viewGuildHistoryInfoComm(char *buffer)
{
	char msg[3096] = {0};
	// string msg_head = "12";					//命令头12,19
	// msg = msg + msg_head + intTostring(VIEW_GUILD_HISTORY_INFO);
	
	int page = 1;							//查看的页数
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(page);
	
	//清空帮派申请列表
	cout<<"1219. "<<page<<endl;
	sprintf(msg, "12,19");
	int ret = viewGuildHistory(pg_hero, page, msg+strlen(msg));
	// msg += ret;
	send_msg(sock_fd, msg);
}

/**
 * sendJoinGuildMsg - 向申请帮派的玩家发送同意加入帮派或者被拒绝加入帮派的消息
 * @hero: 申请帮派的玩家
 * @guildName:	帮派名
 * @guildLevel: 帮派等级，加入失败返回的等级为0
 * Return: 无返回值
 */
void sendJoinGuildMsg(char* heroId, char* guildName, int guildLevel)
{
	//角色id得到角色实例
	Hero *hero;
	map<string, Hero*>::iterator it_hero;
	it_hero = heroId_to_pHero.find(heroId);
	if(it_hero == heroId_to_pHero.end())
	{
		return;
	}
	hero = it_hero->second;
	
	char msg[2048] = {0};
	// = "12";
	// msg += intTostring(JOIN_GUILD_RETURN);
	// msg += intTostring(guildLevel);
	// msg += "," + guildName;
	sprintf(msg, "12,20,%d,%s", guildLevel, guildName);
	send_msg(hero->getFd(), msg);
}

void viewGuildActivityComm(char *buffer)
{
	char msg[16000] = {0};
	// string msg_head = "12";					//命令头12,21
	// msg = msg + msg_head + intTostring(VIEW_GUILD_ACTIVITY);
	
	// msg += viewGuildActivity(hero);
	sprintf(msg, "12,21");
	int ret = viewGuildActivity(pg_hero, msg + strlen(msg));
	send_msg(sock_fd, msg);
}

//领取帮派签到奖励
void getGuildSignRewardComm(char *buffer)
{
	char msg[2048] = {0};
	char msg1[200] = {0};
	// string msg_head = "12";					//命令头12,22
	// msg = msg + msg_head + intTostring(GET_GUILD_SIGN_REWARD);
	
	int mode = 1;							//签到模式，0:普通签到；1：使用道具签到
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(mode);
	
	int err;
	//领取签到奖励
	int ret = getGuildSignReaward(pg_hero, mode, &err, msg1);
	if (err == 0)
	{
		sprintf(msg, "12,22,1%s", msg1);
		// msg += intTostring(SUCCESS);
		// msg += ret;
	} else {
		sprintf(msg, "12,22,0,%d", err);
		// msg += intTostring(FAILED);
		// msg += intTostring(err);
	}
	send_msg(sock_fd, msg);
}

//向帮派捐献的通信
void guildDonateComm(char *buffer)
{
	char msg[2048] = {0};
	char msg1[64] = {0};
	// string msg_head = "12";					//命令头12,23
	// msg = msg + msg_head + intTostring(GUILD_DONATE_RETURN);
	
	int mode = 1;							//捐献标志，0:捐献帮派；1：捐献游戏币
	int val;								//捐献的值
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(mode);
	MSG_INT(val);
	int ret;
	if (mode == 0)
	{
		//捐献帮贡
		ret = donateGloryToGuild(pg_hero, val, msg1);
		
	} else if (mode == 1) {
		//捐献资金
		ret = donateMoneyToGuild(pg_hero, val, msg1);
	}
	
	if (ret != 0)
	{
		//msg += intTostring(FAILED);
		sprintf(msg, "12,23,0,%d,%d", mode, ret);
	}else {
		// msg += intTostring(SUCCESS);
		// msg += ret;
		sprintf(msg, "12,23,1,%d,%s", mode, msg1);
	}
	send_msg(sock_fd, msg);
}

//帮派职务调整
void changeGuildTitleComm(char *buffer)
{
	cout<<"#####################################"<<endl;
	cout<<"buffer is "<<buffer<<endl;
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,24
	// msg = msg + msg_head + intTostring(CHANGE_GUILD_TITLE);
	
	int mode = 3;							//操作选择
	char *heroId;							//角色名
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(mode);
	MSG_CHAR_END(heroId);
	
	
	int managerTitle = pg_hero->getGuildTitle();
	cout<<"###############################"<<endl;
	
	cout<<"heroId :"<<heroId<<endl;
	cout<<"mode is "<<mode<<endl;
	cout<<"managerTitle is "<<managerTitle<<endl;
	
	if (managerTitle == 0 && mode == 0)
	{
		//帮主让贤
		if (demiseGuildTitle(pg_hero, heroId))
		{
			sprintf(msg, "12,24,1");
			// msg += intTostring(SUCCESS);
		} else {
			// msg += intTostring(FAILED);
			sprintf(msg, "12,24,0");
		}
		
	} else if (managerTitle == 0 && mode == 1)
	{
		//帮主任命副帮主
		if (appointGuildTitle(pg_hero, heroId))
		{
			sprintf(msg, "12,24,1");
			// msg += intTostring(SUCCESS);
		} else {
			// msg += intTostring(FAILED);
			sprintf(msg, "12,24,0");
		}
	} else if (managerTitle == 1 && mode  == 1)
	{
		//副帮主转让
		if (demiseGuildTitle(pg_hero, heroId))
		{
			// msg += intTostring(SUCCESS);
			sprintf(msg, "12,24,1");
		} else {
			// msg += intTostring(FAILED);
			sprintf(msg, "12,24,0");
		}
	} else {
		// msg += intTostring(FAILED);
		sprintf(msg, "12,24,0");
	}
	
	send_msg(sock_fd, msg);
}

//解散帮派
void disbandGuildComm(char *buffer)
{
	char msg[2048] = {0};
	// string msg_head = "12";					//命令头12,25
	// msg = msg + msg_head + intTostring(DISBAND_GUILD_RETURN);
	
	//清空帮派申请列表
	bool ret = disbandGuild(pg_hero);
	sprintf(msg, "12,25,%d",ret);
	// msg += intTostring(ret);
	send_msg(sock_fd, msg);
}

void inviteJoinGuildComm(char* buffer)
{
	char msg[2048] = {0};
	char* heroId;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(heroId);
	
	int ret = inviteJoinGuild(pg_hero, heroId);
	
	sprintf(msg, "12,27,%d", ret);
	send_msg(pg_hero->getFd(), msg);
}

void guildGameComm(char* buffer)
{
	char msg[16000] = {0};
	int camp = 0;
	int num = 0;
	int page = 0;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(camp);
	MSG_INT(page);
	MSG_INT(num);
	sprintf(msg, "12,31,%d", page);
	int ret = viewGuildGameInfo(camp, num, page, msg + strlen(msg));
	if (ret != 0)
	{
		sprintf(msg + strlen(msg), ",%d", ret);
	}
	send_msg(pg_hero->getFd(), msg);
}

void refreshGuildTaskComm(char* buffer)
{
	int ret = refreshGuildTaskForAll(pg_hero);
	char msg[2048] = {0};
	if (ret != 0)
	{
		sprintf(msg, "12,35,0,%d", ret);
	} else {
		sprintf(msg, "12,35,1");
	}
	
	send_msg(pg_hero->getFd(), msg);
}

void viewFreshGuildTaskInfoComm(char* buffer)
{
	char msg[2048] = {0};
	sprintf(msg, "12,37");
	viewFreshGuildTaskInfo(pg_hero, msg);
	send_msg(pg_hero->getFd(), msg);
	
}
