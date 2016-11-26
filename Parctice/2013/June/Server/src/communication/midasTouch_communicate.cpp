#include "midasTouch.h"
#include "money_operator.h"
#include "wholeDefine.h"
using namespace std;
extern int g_msg_len; //除去消息头的有效消息长度
extern Hero* pg_hero; //当前角色对象
extern char g_out_buf[20480];
extern Role *pg_role;
extern char server_name[10];
void midasTouchRefresh(char *buffer)
{
	cout<<"22,2"<<endl;
	MidasTouch *midasTouch=pg_hero->getMidasTouch();
	if (midasTouch==NULL)
	{
		return;
	}
	int refreshNum=midasTouch->getRefreshNum();
	if (refreshNum==0)
	{
		msg_error(g_out_buf,54);
		send_msg(pg_hero->getFd(),g_out_buf);	
		cout<<"jolly:your refresh time is used up midasTouch_communicate 26"<<endl;
	}
	else
	{
		midasTouch->normalRefresh(g_out_buf,sizeof(g_out_buf),pg_hero);
		send_msg(pg_hero->getFd(),g_out_buf);	
		//jolly add wulintarget 12.4 start
		pg_hero->updataSingleTarget(2,5);
		//jolly add wulintarget 12.4 end
	}
}


void midasTouchInform(char *buffer)
{	
	MidasTouch *midasTouch=pg_hero->getMidasTouch();
	if (midasTouch==NULL)
	{
		return;
	}
	midasTouch->msg_midasTouchInform(g_out_buf,sizeof(g_out_buf));
	send_msg(pg_hero->getFd(),g_out_buf);
}

void midasTouchReceive(char *buffer)
{
	MidasTouch *midasTouch=pg_hero->getMidasTouch();
	if (midasTouch==NULL)
	{
		return;
	}
	int money=midasTouch->getMoney();
	increaseBoundGameMoney(pg_hero,money);
	int popularity=midasTouch->getPopularity();
	pg_hero->addPrestigeValue(popularity);
	// snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",23,POPULARITY_RETURN,pg_hero->getPrestigeValue());
	// send_msg(pg_hero->getFd(),g_out_buf);
	midasTouch->receiveReward();
	int refreshNum=midasTouch->getRefreshNum();
	if (refreshNum==0)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",23,2,0);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
}

void midasTouchModify(char *buffer)
{
	MidasTouch *midasTouch=pg_hero->getMidasTouch();
	if (midasTouch==NULL)
	{
		return;
	}
	if (midasTouch->isMax())
	{
		msg_error(g_out_buf,93);
		send_msg(pg_hero->getFd(),g_out_buf);
		midasTouch->msg_midasTouchInform(g_out_buf,sizeof(g_out_buf));
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else
	{
		int freeRefreshNum=midasTouch->getLuckyRefreshNum();
		if (freeRefreshNum==0)
		{
			cout<<"jolly:the free num is used up will use money midasTouch_communicate.cpp 132"<<endl;
			int luckyGold=midasTouch->getLuckyRefreshMoney();
			if (useGold(pg_hero,luckyGold))
			{
				int flag=midasTouch->getFlag();
				if (flag==1)
				{
					int money=midasTouch->getMoney();
					increaseBoundGameMoney(pg_hero,money);
					int popularity=midasTouch->getPopularity();
					pg_hero->addPrestigeValue(popularity);
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",23,POPULARITY_RETURN,pg_hero->getPrestigeValue());
					send_msg(pg_hero->getFd(),g_out_buf);
					midasTouch->setFlag(0);
				}

				midasTouch->luckyRefresh(g_out_buf,2,sizeof(g_out_buf),pg_hero);
				
				//记录日志2013.4.28
				char account_msg[1024]={'\0'};
				snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d",16,3,server_name,(int)myTime.tv_sec,pg_hero->getIdentity(),pg_hero->getNickName(),pg_role->getUserName(),luckyGold);
				write_log(account_msg);	
			}
			else
			{
				msg_error(g_out_buf,49);
			}
		}
		else
		{			
			int flag=midasTouch->getFlag();
			if (flag==1)
			{
				int money=midasTouch->getMoney();
				increaseBoundGameMoney(pg_hero,money);
				int popularity=midasTouch->getPopularity();
				// string msg="23";
				// msg+=intTostring(POPULARITY_RETURN);
				pg_hero->addPrestigeValue(popularity);
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",23,POPULARITY_RETURN,pg_hero->getPrestigeValue());
				send_msg(pg_hero->getFd(),g_out_buf);
				midasTouch->setFlag(0);
			}
			midasTouch->luckyRefresh(g_out_buf,1,sizeof(g_out_buf),pg_hero);
			// cout<<"jollyTest:4"<<endl;
		}
		send_msg(pg_hero->getFd(),g_out_buf);
	}	
}

void midasTouchResponse(char *buffer)
{	
	MidasTouch *midasTouch=pg_hero->getMidasTouch();	
	if (midasTouch==NULL)
	{
		return;
	}
	int money=midasTouch->getMoney();
	int refreshNum=midasTouch->getRefreshNum();
	int heroLevel=pg_hero->getGradeNow();
	if ((money!=0||refreshNum!=0)&&heroLevel>=25)
	{
		if (money!=0)
		{
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",23,2,2);
		}
		else
		{
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",23,2,1);
		}		
	}
	else 
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",23,2,0);
	}
	
	char* guildName=pg_hero->getGuildName();
	if (strlen(guildName)==0)
	{
		snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d",0);
	}
	else
	{
		snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d",1);
	}			
	
	if (pg_hero->getOffline_exp()==0&&pg_hero->getLast_day_flag()!=1&&pg_hero->getChief_flag()!=1)
	{
		snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d",0);
	}
	else
	{
		snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d",1);
	}
	
	send_msg(pg_hero->getFd(),g_out_buf);
}
