#include "reward_online.h"
#include "my_time.h"
using namespace std;

extern map<string,Reward_online_config*> id_to_reward_online;
Reward_Online::Reward_Online(void)
{
	
}

Reward_Online::Reward_Online(OnlineRewarData _onlineReward)
{
	onlineReward=_onlineReward;
}

void Reward_Online::startOnlineReward(char *msg,int len)
{
	if (msg==NULL)
	{
		return;
	}
	strncpy(onlineReward.stage,"p11",sizeof(onlineReward.stage));
	map<string,Reward_online_config*>::iterator it;
	it=id_to_reward_online.find(onlineReward.stage);
	if (it==id_to_reward_online.end())
	{
		cout<<"jolly:init online reward error reward_online.cpp 29"<<endl;
	}
	else
	{
		Reward_online_config *reward_online_config=it->second;
		onlineReward.totalTime=reward_online_config->getTime();
		onlineReward.startTime=myTime.tv_sec;
		snprintf(msg,len,"%d,%d,%d",23,ONLINE_REWARD_TIME,onlineReward.totalTime);
	}
}

void Reward_Online::normalRefresh(char *msg,int len)
{
	if (msg==NULL)
	{
		return;
	}
	int nowTime=myTime.tv_sec;
	if ((nowTime-onlineReward.startTime)>=onlineReward.totalTime)				//时间到
	{
		map<string,Reward_online_config*>::iterator it;
		onlineReward.stage[0]='p';
		// cout<<"onlineReward stage is:"<<onlineReward.stage<<endl;
		it=id_to_reward_online.find(onlineReward.stage);
		if (it==id_to_reward_online.end())
		{
			cout<<"jolly:init online reward error reward_online.cpp 53"<<endl;
			strncpy(onlineReward.stage,"p11",sizeof(onlineReward.stage));			
		}
		else
		{
			Reward_online_config *reward_online_config=it->second;
			vector<int> moneyPercent=reward_online_config->getMoneyPercent();
			vector<int> moneyNum=reward_online_config->getMoneyNum();
			vector<int>	goldPercent=reward_online_config->getGoldPercent();
			vector<int>	goldNum=reward_online_config->getGoldNum();
			vector<int>	goodsPercent=reward_online_config->getGoodsPercent();
			vector<string>	goodsid=reward_online_config->getGoodsid();
			int rand_money=random_number(1,100);
			int i=0;
			int j=0;
			int k=0;
			for (;i<5;i++)
			{
				if (rand_money<=moneyPercent[i])
				{
					onlineReward.rewardMoney=moneyNum[i];
					break;
				}
			}
			int rand_gold=random_number(1,100);
			for (;j<5;j++)
			{
				if (rand_gold<=goldPercent[j])
				{
					onlineReward.rewardGold=goldNum[j];
					break;
				}
			}
			int rand_goods=random_number(1,100);
			for (;k<10;k++)
			{
				// cout<<"goodsid:"<<goodsid[k]<<endl;
				if (rand_goods<=goodsPercent[k])
				{
					strncpy(onlineReward.goodsid,goodsid[k].c_str(),sizeof(onlineReward.goodsid));
					break;
				}
			}			
			snprintf(msg,len,"%d,%d,%s,%d,%d,%s,%d",23,ONLINE_REWARD_RETURN,onlineReward.stage,onlineReward.rewardGold,onlineReward.rewardMoney,onlineReward.goodsid,1);
			// cout<<"onlineReward.rewardMoney : "<<onlineReward.rewardMoney<<endl;
			// cout<<"onlineReward.rewardGold : "<<onlineReward.rewardGold<<endl;
			// cout<<"onlineReward.goodsid : "<<onlineReward.goodsid<<endl;
		}
	}
	else
	{
		msg_error(msg,56);
	}
}

void Reward_Online::goldRefresh(char *msg,int len)
{
	if (msg==NULL)
	{
		return;
	}
	int nowTime=myTime.tv_sec;
	if ((nowTime-onlineReward.startTime)>=onlineReward.totalTime)				//时间到
	{
		map<string,Reward_online_config*>::iterator it;
		onlineReward.stage[0]='f';
		// cout<<"onlineReward stage is:"<<onlineReward.stage<<endl;
		it=id_to_reward_online.find(onlineReward.stage);
		if (it==id_to_reward_online.end())
		{
			cout<<"jolly:init online reward error reward_online.cpp 119"<<endl;
			strncpy(onlineReward.stage,"p11",sizeof(onlineReward.stage));
		}
		else
		{
			Reward_online_config *reward_online_config=it->second;
			vector<int>::iterator it;
			vector<int> moneyPercent=reward_online_config->getMoneyPercent();
			vector<int> moneyNum=reward_online_config->getMoneyNum();
			vector<int>	goldPercent=reward_online_config->getGoldPercent();
			vector<int>	goldNum=reward_online_config->getGoldNum();
			vector<int>	goodsPercent=reward_online_config->getGoodsPercent();
			vector<string>	goodsid=reward_online_config->getGoodsid();
			// cout<<"#######################moneyNum##########################"<<endl;
			// for (int f=0;f<moneyNum.size();++f)
			// {
				// cout<<moneyNum[f]<<endl;
			// }
			// cout<<"########################goldNum######################"<<endl;
			// for (int f=0;f<goldNum.size();++f)
			// {
				// cout<<goldNum[f]<<endl;
			// }
			// cout<<"########################goodsid######################"<<endl;
			// for (int f=0;f<goodsid.size();++f)
			// {
				// cout<<goodsid[f]<<endl;
			// }
			int rand_money=random_number(1,100);
			// cout<<"rand_money:"<<rand_money<<endl;
			int i=0;
			int j=0;
			int k=0;
			for (;i<5;i++)
			{
				if (rand_money<=moneyPercent[i])
				{
					// cout<<"moneyNum["<<i<<"]:"<<moneyNum[i]<<endl;
					onlineReward.rewardMoney=moneyNum[i];
					break;
				}
			}
			int rand_gold=random_number(1,100);
			// cout<<"rand_gold:"<<rand_gold<<endl;
			for (;j<5;j++)
			{
				if (rand_gold<=goldPercent[j])
				{
					onlineReward.rewardGold=goldNum[j];
					break;
				}
			}
			int rand_goods=random_number(1,100);
			char goods[20]={'\0'};			
			cout<<"rand_goods:"<<rand_goods<<endl;	
			for (;k<10;k++)
			{
				// cout<<"goodsid:"<<goodsid[k]<<endl;
				if (rand_goods<=goodsPercent[k])
				{
					strncpy(onlineReward.goodsid,goodsid[k].c_str(),sizeof(onlineReward.goodsid));
					break;
				}
			}			
			snprintf(msg,len,"%d,%d,%s,%d,%d,%s,%d",23,ONLINE_REWARD_RETURN,onlineReward.stage,onlineReward.rewardGold,onlineReward.rewardMoney,onlineReward.goodsid,2);
			// cout<<"onlineReward.rewardMoney : "<<onlineReward.rewardMoney<<endl;
			// cout<<"onlineReward.rewardGold : "<<onlineReward.rewardGold<<endl;
			// cout<<"onlineReward.goodsid : "<<onlineReward.goodsid<<endl;
		}
	}
	else
	{
		msg_error(msg,56);
	}
}

void Reward_Online::judgeTotalTime(void)
{
	int nowTime=myTime.tv_sec;
	onlineReward.totalTime=onlineReward.totalTime-(nowTime-onlineReward.startTime);
	if (onlineReward.totalTime<0)
	{
		onlineReward.totalTime=0;
	}
	else if (onlineReward.totalTime>3600)
	{
		onlineReward.totalTime=3600;
	}
}

OnlineRewarData Reward_Online::getMemStruct(void)
{
	return onlineReward;
}
void Reward_Online::setStage(char *msg,int len)
{
	// cout<<"setStage begin onlineReward.stage:"<<onlineReward.stage<<endl;
	onlineReward.stage[2]++;
	// cout<<"setStage end onlineReward.stage:"<<onlineReward.stage<<endl;
	if (msg==NULL)
	{
		return;
	}
	map<string,Reward_online_config*>::iterator it;
	it=id_to_reward_online.find(onlineReward.stage);
	cout<<"onlineReward.stage:"<<onlineReward.stage<<endl;
	if (it==id_to_reward_online.end())
	{
		cout<<"jolly:init online reward error reward_online.cpp 196"<<endl;
		snprintf(msg,len,"%d,%d,%d",23,ONLINE_REWARD_TIME,-1);
	}
	else
	{
		Reward_online_config *reward_online_config=it->second;
		onlineReward.totalTime=reward_online_config->getTime();
		onlineReward.startTime=myTime.tv_sec;
		onlineReward.rewardMoney=0;
		onlineReward.rewardGold=0;
		memset(onlineReward.goodsid,'\0',sizeof(onlineReward.goodsid));
		snprintf(msg,len,"%d,%d,%d",23,ONLINE_REWARD_TIME,onlineReward.totalTime);
	}	
}

bool Reward_Online::judgeCanReceive(void)
{
	if (onlineReward.stage[2]=='9')
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Reward_Online::levelSetStage(void)
{
	// cout<<"levelSetStage begin onlineReward.stage:"<<onlineReward.stage<<endl;
	onlineReward.stage[1]++;
	// cout<<"levelSetStage end onlineReward.stage:"<<onlineReward.stage<<endl;
}

char *Reward_Online::getGoodsId(void)
{
	return onlineReward.goodsid;
}
		
int Reward_Online::getMoney(void)
{
	return onlineReward.rewardMoney;
}
		
int Reward_Online::getGold(void)
{
	return onlineReward.rewardGold;
}

void Reward_Online::msg_return(char *msg,int len)
{
	if (onlineReward.stage[2]=='9')
	{
		onlineReward.totalTime=-1;
	}
	snprintf(msg,len,"%d,%d,%d",23,ONLINE_REWARD_TIME,onlineReward.totalTime);
}

void Reward_Online::setNewDay(void)
{
	onlineReward.stage[2]='1';
	map<string,Reward_online_config*>::iterator it;
	it=id_to_reward_online.find(onlineReward.stage);
	if (it==id_to_reward_online.end())
	{
		cout<<"jolly:init online reward error reward_online.cpp 196"<<endl;
	}
	else
	{
		Reward_online_config *reward_online_config=it->second;
		onlineReward.rewardMoney=0;
		onlineReward.rewardGold=0;
		onlineReward.totalTime=reward_online_config->getTime();
		onlineReward.startTime=myTime.tv_sec;
		memset(onlineReward.goodsid,'\0',sizeof(onlineReward.goodsid));
	}	
}

void Reward_Online::onlineReward_msg(char *msg,int len)
{
	snprintf(msg,len,"%d,%d,%s,%d,%d,%s",23,ONLINE_REWARD_RETURN2,onlineReward.stage,onlineReward.rewardGold,onlineReward.rewardMoney,onlineReward.goodsid);
}