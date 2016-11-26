#include "sitControl.h"
#include "my_time.h"
using namespace std;

//added by benliao
extern int g_msg_len;
extern Hero* pg_hero;
extern char g_out_buf[20480];

void sitControl(char *buffer)
{		
	MSG_BEGIN(buffer,g_msg_len)
	MSG_INT(int state)
	
	cout<<"3,1,"<<state<<endl;
	if (pg_hero->getHeroState()==7)
	{
		msg_error(g_out_buf,83);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else if (pg_hero->getHeroState()==5)
	{
		msg_error(g_out_buf,128);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else
	{
		if (state==6)
		{		
			pg_hero->memHero->autoRecover=myTime.tv_sec;		
			Map_Inform* map=pg_hero->getMap();
			if (map==NULL)
			{
				return;
			}
			
			Nbox *box = map->getBox();                     
			 
			if(box == NULL)
			{
				return;
			}
			
			StyObj obj(pg_hero->getIdentity(),HERO_STYLE_TYPE);
			
			box->getStaInSrcVec(obj);
			
			pg_hero->setHeroState(state);
			pg_hero->stopMove();
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d",3,SIT_STATE,pg_hero->getIdentity(),pg_hero->getHeroState());
			
			box->sentBoxMsg(g_out_buf);
		}	
		else if (state==0)
		{
			cout<<"state is 0 prepare cancelsit"<<endl;
			cancelSit(pg_hero);
		}
	}	
}

void cancelSit(Hero *hero)
{
	// cout<<"cancelSit begin"<<endl;
	// cout<<"hero->getHeroState():"<<hero->getHeroState()<<endl;
	if (hero->getHeroState()==6)
	{
		// cout<<"222222222222222222222222222222222"<<endl;
		hero->setHeroState(0);
		Map_Inform* map=hero->getMap();
		if (map==NULL)
		{
			return;
		}

		Nbox *box = map->getBox();                     

		if(box == NULL)
		{
			return;
		}

		StyObj obj(hero->getIdentity(),HERO_STYLE_TYPE);

		box->getStaInSrcVec(obj);

		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d",3,SIT_STATE,hero->getIdentity(),hero->getHeroState());

		box->sentBoxMsg(g_out_buf);
	}
	// cout<<"cancelSit end"<<endl;
}