/****************************************************************
 * Filename: rob_flag_war_comm.cpp
 * 
 * Description: °ïÅÉ¶áÆìÕ½Í¨ÐÅ
 *
 * Original Author : bison, 2013-4-12
 *
 ****************************************************************/


#include "rob_flag_war_comm.h"
#include "command_other_function_all_over.h"


void viewRobFlagWarRoomInfoComm(char *buffer)
{
	char temp[2048] = {0};
	char msg[2048] = {0};
	int ret = robFlagWarManage->viewRoomState(pg_hero, temp);
	if (ret == 0)
	{
		sprintf(msg, "34,1,1");
	} else if (ret == 7) {
		sprintf(msg, "34,0,1,%s", temp);
	} else {
		sprintf(msg, "34,0,0,%d", ret);
	}
	
	send_msg(pg_hero->getFd(), msg);
}

void enterRobFlagWarRoomComm(char *buffer)
{
	int channel = 0;
	int mode = 0;
	char *password = NULL;
	char *roomId = NULL;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(channel);
	switch(channel)
	{
	case 1:
		MSG_INT(mode);
		if (mode == 1)
		{
			MSG_CHAR(password);
		}
		break;
	
	case 2:
		MSG_CHAR(roomId);
		MSG_INT(mode)
		if (mode == 1)
		{
			MSG_CHAR(password);
		}
	
	case 3:
		break;
		
	default:
		return;
	}
	
	int ret = robFlagWarManage->joinRoom(pg_hero, roomId, password, 2);
	char msg[128] = {0};
	if (ret != 0)
	{
		sprintf(msg, "34,1,0,%d", ret);
	} else {
		sprintf(msg, "34,1,1");
	}
	
	send_msg(pg_hero->getFd(), msg);
}

void exitRobFlagWarRoomComm(char* buffer)
{
	char msg[256] = {0};
	int ret = robFlagWarManage->exitRoom(pg_hero, false);
	cout<<"have come into robFlagWarManagerobFlagWarManagerobFlagWarManage!!!!!!!!!!!!!"<<endl;
	cout<<"have come into robFlagWarManagerobFlagWarManagerobFlagWarManage!!!!!!!!!!!!!"<<endl;
	cout<<"have come into robFlagWarManagerobFlagWarManagerobFlagWarManage!!!!!!!!!!!!!"<<endl;
	if (ret != 0)
	{
		sprintf(msg, "34,3,0,%d", ret);
	} else {
		sprintf(msg, "34,3,1");
	}
	
	send_msg(pg_hero->getFd(), msg);
}

void callJoinRobFlagWarRoomComm(char* buffer)
{
	char msg[256] = {0};
	int ret = robFlagWarManage->callJoin(pg_hero);
	if (ret != 0)
	{
		sprintf(msg, "34,4,0,%d", ret);
	} else {
		sprintf(msg, "34,4,1");
	}
	
	send_msg(pg_hero->getFd(), msg);
}

void prepareRobFlagWarRoomComm(char *buffer)
{
	char msg[256] = {0};
	int ret = robFlagWarManage->prepare(pg_hero);
	if (ret != 0)
	{
		sprintf(msg, "34,12,0,%d", ret);
	} else {
		sprintf(msg, "34,12,1");
	}
	
	send_msg(pg_hero->getFd(), msg);
}