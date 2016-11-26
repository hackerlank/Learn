#include "hero_title_use.h"
#include"user_role_manage_assist.h"
#include"command_other_function_all_over.h"
#include"nbox.h"
extern map<string, Hero*> heroId_to_pHero;
extern int sock_fd;
extern map<int, Role*> fd_to_pRole;
extern set<string>allTitle; 
extern struct timeval myTime;

static char title_msg[100];

#include "wholeDefine.h"

void askTitle(char *buff)
{
	MSG_BEGIN(buff,g_msg_len);
	pg_hero->sendMsgTitle();
}

void chooseTitle(char *buff)
{
	MSG_BEGIN(buff,g_msg_len);
	MSG_CHAR_END(char *titleId);
	Map_Inform *map_now;
	Nbox* box;
	
	// cout<<"[XHM TEST]:chooseTitle titleId:"<<titleId<<endl;
	
	if(pg_hero == NULL)
	{
		return;
	}
	
	StyObj obj(pg_hero->getIdentity(),HERO_STYLE_TYPE);	
	map_now = pg_hero->getMap();
	if(map_now == NULL)
	{
		return;
	}
	
	box = map_now->getBox();
	if(box == NULL)
	{
		return;
	}
		
	box->getStaInSrcVec(obj);		
	
	bool isSuccess=pg_hero->chooseTitle(titleId);	
	if(isSuccess)
	{
		sprintf(title_msg,"19,5,%s,%s",pg_hero->getIdentity(),titleId);
		box->sentBoxMsg(title_msg);
	}
}

void cancelTitle(char *buff)
{
	MSG_BEGIN(buff,g_msg_len)
    MSG_CHAR_END(char *titleId)
	
	// cout<<"[XHM TEST]: cancelTitle titleId:"<<titleId<<endl;	
	
	Map_Inform *map_now;
	Nbox* box;
	
	if(pg_hero == NULL)
	{
		return;
	}
	
	StyObj obj(pg_hero->getIdentity(),HERO_STYLE_TYPE);	
	map_now = pg_hero->getMap();
	if(map_now == NULL)
	{
		return;
	}
	
	box = map_now->getBox();
	if(box == NULL)
	{
		return;
	}
		
	box->getStaInSrcVec(obj);	

	
	if(strcmp(pg_hero->getTitle().c_str(),titleId)==0)
	{
		pg_hero->setTitle("0");
		
		sprintf(title_msg,"19,5,%s,0",pg_hero->getIdentity());
		box->sentBoxMsg(title_msg);		
	}
	
}

void updataCrime(char *buff)
{
	Hero *myHero;
	Map_Inform *map_now;
	Nbox* box;
	
	myHero = fd_to_hero();
	
	if(myHero == NULL)
	{
		return;
	}
	
	StyObj obj(myHero->getIdentity(),HERO_STYLE_TYPE);
	
	map_now = myHero->getMap();
	
	if(map_now == NULL)
	{
		return;
	}
		
	box = map_now->getBox();
	if(box == NULL)
	{
		return;
	}
	
	
	if(myHero->getCrimeValue())
	{
		int time = myTime.tv_sec;
		time -= myHero->crimeTime;
		if(time >= 3600)
		{
			myHero->cutCrimeValue();
		}
		else
		{
			cout<<"cut this client"<<endl;
		}
	}
	if(myHero->memHero->vipDailyData.stage!=0)
	{		
		box->getStaInSrcVec(obj);
		
		int vipTime=myTime.tv_sec;
		memset(g_out_buf,0,sizeof(g_out_buf));
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%d",19,4,myHero->getIdentity(),myHero->memHero->vipDailyData.stage);
		box->sentBoxMsg(g_out_buf);
	}
	
	
}
