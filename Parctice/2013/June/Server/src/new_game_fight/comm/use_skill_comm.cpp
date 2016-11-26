#include "wholeDefine.h"
#include "hero_fight.h"
#include "ride_comm.h"

void use_skill_comm(char *buffer)
{
	char *skillId;
	char *hitedId;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR(skillId);
	MSG_CHAR_END(hitedId);
	char msg[64] ={0};
	if (strlen(skillId) != 4)
	{
		//技能ID有误
		cout<<"The client has send a error skillId when use skill!"<<endl;
		return;
	}
	
	/*被定身*/
	if(pg_hero->getStillFlg())
	{
		cout<<"use_skill_comm dingshen do not move:"<<pg_hero->getIdentity()<<endl;
		return;
	}
	
	if (pg_hero->getRideState() == RIDE_STATE_RIDING)
	{
		stopRideComm(NULL);
	}
	
	if (pg_hero->getRideState() == RIDE_STATE_PREPARE)
	{
		pg_hero->breakRide();
	}
	
	cout<<"attack "<<hitedId<<" use skill of "<<skillId<<endl;
	int remainCD = 0;
	int ret = proc_use_skill(pg_hero, skillId, hitedId, remainCD);
	if (ret != 0)
	{
		sprintf(msg, "26,2,0,%d,%s,%d", ret, skillId, remainCD);
		send_msg(pg_hero->getFd(), msg);
	}
}