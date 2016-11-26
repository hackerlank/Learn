#include "reward_operator.h"
#include "campWarManagement.h"
#include "reward_recharge_config.h"
#include "money_operator.h"

extern struct timeval myTime;
extern LevelRewardData levelRewardData[10];
extern map<int,Reward_recharge_config*>id_to_reward_recharge;
extern struct tm* timeNow;
//打坐经验配置文件
extern map<int,int> dazuo_factor;

using namespace std;
bool receive_levelReward(Hero *hero,int flag)
{
	if (hero==NULL)
	{
		return false;
	}
	
	Bag *bag=hero->getBag();
	if (bag==NULL)
	{
		return false;
	}

	int number=levelRewardData[flag].number;
	int repeat=levelRewardData[flag].repeat;

	cout<<"flag:"<<flag<<endl;
	cout<<"levelRewardData[flag].level:"<<levelRewardData[flag].level<<endl;
	cout<<"levelRewardData[flag].repeat:"<<levelRewardData[flag].repeat<<endl;
	cout<<"levelRewardData[flag].number:"<<levelRewardData[flag].number<<endl;
	cout<<"levelRewardData[flag].goodsid:"<<levelRewardData[flag].goodsid<<endl;	
	
	if (!bag->bagIsFull(repeat))
	{
		
		char effect[20][20]={'\0'};
		int num=0;
		int len=0;
		
		int count=0;
		
		for(int i=0;i<strlen(levelRewardData[flag].goodsid);i++)
		{			
			if (levelRewardData[flag].goodsid[i]==';'&&(num < number))
			{							
				for (int loop=len;loop<i;loop++)
				{
					effect[num][count]=levelRewardData[flag].goodsid[loop];
					count++;
				}				
				count=0;
				len=i+1;
				num++;
			}
			
		}
		for (int j=0;j<number-1;)
		{
			saveGoodsInBag(hero,effect[j+1],atoi(effect[j]));
			j=j+2;
		}
		return true;
	}
	else
	{	
		msg_error(g_out_buf,44);
		send_msg(hero->getFd(),g_out_buf);
		cout<<"bag is full in reward_operator.cpp 28"<<endl;
		return false;
	}
}

void receive_offLine_reward(Hero *hero)
{
	if (hero==NULL)
	{
		return;
	}
	int offline_time=hero->getOffline_time();
	int online_time=hero->getOnline_time();
	int offline_exp=hero->getOffline_exp();
	int exp;
	if (offline_time!=0&&offline_time!=-1)
	{
		if (offline_exp!=0)				//没有任何离线经验
		{					
			exp=(offline_exp*hero->memHero->vipDailyData.lixianTimes)/10;
			hero->setExpNow(exp);
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,REWARD_EXP,hero->getExpNow());
			send_msg(hero->getFd(),g_out_buf);
		}
		hero->setOffline_exp(0);
		hero->setOffline_time(-1); //将下线时间变为-1,有很多地方需要用这个判断的 jolly add 2013.1.15
		hero->send_msg_reward();
	}	
}

void receive_sign_reward(Hero *hero)
{	
	if (hero==NULL)
	{
		return;
	}
	int expSign=hero->getLast_exp();
	int exp;
	int flag=hero->getLast_day_flag();
	if (flag==1)
	{
		exp=(expSign*hero->memHero->vipDailyData.lianxuTimes)/10;
		hero->setExpNow(exp);
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,REWARD_EXP,hero->getExpNow());
		send_msg(hero->getFd(),g_out_buf);
		flag=0;
		hero->setLast_day_flag(flag);
		hero->send_msg_reward();
		hero->memHero->downLineDay=timeNow->tm_year*365+timeNow->tm_yday;
	}
	else
	{
		cout<<"This hero has already receive a sign reard int reard_operator.cpp 134"<<endl;
	}
}

void receive_chief_reward(Hero *hero)
{
	if (hero==NULL)
	{
		return;
	}
	int flag=hero->getChief_flag();
	int level=hero->getLevel();
	int expChief=level*level*300+5000;
	int exp;
	int money=level*1500;
	if (flag==1)
	{
		if (hero->memHero->vipDailyData.stage!=0)
		{
			exp=expChief*2.5;
			money=money*2.5;
		}
		else
		{
			exp=expChief;
		}
		hero->setExpNow(exp);
		increaseBoundGameMoney(hero,money);
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,REWARD_EXP,hero->getExpNow());
		send_msg(hero->getFd(),g_out_buf);
		flag=0;
		hero->setChief_flag(flag);
		hero->send_msg_reward();
	}
	else
	{
		cout<<"you are not in the guild , so you can't receive the reward reward_operator 174"<<endl;
	}
}

void receive_VIP_reward(Hero *hero)
{
	if (hero==NULL)
	{
		cout<<"hero is null in reward_operator.cpp 167"<<endl;
		return;
	}
	
	if (hero->memHero->vipDailyData.receiveFlag==1)
	{			
		if (saveGoodsInBag(hero,hero->memHero->vipDailyData.bagId,1))
		{
			hero->memHero->vipDailyData.receiveFlag=0;
			hero->send_msg_reward();
		}
	}
	else
	{
		cout<<"hero->memHero->vipDailyData.receiveFlag:"<<hero->memHero->vipDailyData.receiveFlag<<endl;
	}
}

long AccordingToIndexGetRecharge(int index)
{
	int gold;
	map<int,Reward_recharge_config*>::iterator it;
	it=id_to_reward_recharge.find(index);
	if (it==id_to_reward_recharge.end())
	{
		gold=-1;
	}
	else
	{
		gold=it->second->getType();
	}	
	return gold;
}
