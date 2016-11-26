#include "internal_forces_comm.h"

void viewInternalForcesComm(char* buffer)
{
	char msg[128] = {0};
	int ret = viewHeroInternalForces(pg_hero);
	if (ret != 0)
	{
		sprintf(msg, "8,15,0,%d", ret);
		send_msg(pg_hero->getFd(), msg);
	}
}

void openInternalForcesComm(char* buffer)
{
	char msg[128] = {0};
	
	int newLevel = 0;
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(newLevel);
	
	int ret = internalForcesLvlUp(pg_hero, newLevel);
	if (ret != 0)
	{
		sprintf(msg, "8,16,0,%d", ret);
		send_msg(pg_hero->getFd(), msg);
	}
	
	
}


void addInternalForcesExpComm(char* buffer)
{
	char msg[128] = {0};
	int mode = 0;
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(mode);
	
	int ret = internalForcesIncExp(pg_hero, mode);
	if (ret != 0)
	{
		sprintf(msg, "8,17,0,%d", ret);
		send_msg(pg_hero->getFd(), msg);
	}
	
}

void viewInternalForcesValueComm(char* buffer)
{
	char msg[128] = {0};
	
	bool canLvlUp = isInForsCanLvlUp(pg_hero);
	
	sprintf(msg, "8,18,%d,%d", pg_hero->getInternalForces(), canLvlUp);
	
	send_msg(pg_hero->getFd(), msg);
}