#include "reward_communicate.h"
#include "reward_level_config.h"
#include "reward_recharge_config.h"
#include "money_operator.h"

using namespace std;
extern map<int,Reward_level_config*>id_to_reward_level;
extern map<int,Reward_recharge_config*>id_to_reward_recharge;
extern LevelRewardData levelRewardData[10];
extern int g_msg_len; //除去消息头的有效消息长度
extern Hero* pg_hero; //当前角色对象
extern char g_out_buf[20480];
extern Role *pg_role;
extern EveryDaySignRewardData signRewardData[30];
extern char server_name[10];

void receiveWelfare(char *buffer)
{	
	int flag; 
	
	int tip;
	
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(flag);
	
	cout<<"36,4,"<<flag<<endl;

	if (flag==1)
	{
		receive_offLine_reward(pg_hero);
	}
	else if (flag==2)
	{
		receive_chief_reward(pg_hero);
	}		
	else if (flag==3)
	{
		receive_VIP_reward(pg_hero);
	}
	else
	{
		cout<<"jolly:flag is error in reward_communicate.cpp 33"<<endl;
	}
	//领取完了奖励,保存数据  2.22
	pg_hero->memSet();
	
	int vipLevel = pg_hero->getVipStage();
	
	if(vipLevel < 1)
	{
		return;
	}
	
	/*充值成为vip，对应给头衔，1——3 ，尊武大侠*/
	if(vipLevel <= 3)
	{
		pg_hero->addTitle("T038");
		return;
	}
	
	/*充值成为vip，对应给头衔，4——7 ，圣武大侠*/
	if(vipLevel <= 7)
	{
		pg_hero->addTitle("T039");
		return;
	}
	
	/*充值成为vip，对应给头衔，8——10 ，神武大侠*/
	if(vipLevel <= 10)
	{
		pg_hero->addTitle("T040");
		return;
	}
	
}

void rechargeRewardReturn(char *buffer)
{
	pg_hero->judgeRechargeReward();
	Money *money=pg_hero->getMoney();
	if (money==NULL)
	{
		return;
	}

	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%ld,%s",23,10,money->getAccMoney(),pg_hero->memHero->recharge_flag);
	send_msg(pg_hero->getFd(),g_out_buf);
}

void receiveRechargeReward(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_INT(int index)
	
	cout<<"22,14,"<<index<<endl;
	
	Money *money=pg_hero->getMoney();
	if (money==NULL)
	{
		return;
	}
	long accGold=money->getAccMoney();
	cout<<"accGold:"<<accGold<<endl;

	if (pg_hero->isRechargeRewardReceive(index))
	{
		map<int,Reward_recharge_config*>::iterator it;
		// cout<<"gold is "<<gold<<endl;
		it=id_to_reward_recharge.find(index);
		if (it==id_to_reward_recharge.end())
		{
			cout<<"jolly:the accGold has no recharge reward reward_communicate 147"<<endl;
		}
		else
		{			
			Reward_recharge_config *reward=it->second;
			long gold=reward->getType();
			if (gold>accGold)
			{
				cout<<"jolly:you have no such accGold your accGold is:"<<index<<"    but gold is:"<<gold<<endl;
			}
			else
			{
				int number=reward->getNum();
				int repeat=reward->getRepeat();
				cout<<"number is :"<<number<<endl;
				Bag *bag=pg_hero->getBag();
				if (bag==NULL)
				{
					return;
				}
				if (!bag->bagIsFull(repeat))
				{
					char* goodsid=reward->getGoodsid();
					cout<<"goodis is :"<<goodsid<<endl;
					char effects[80][20]={'\0'};
					int num=0;
					int len=0;
					char b[2];
					strncpy(b,";",sizeof(";"));
					char d[2]={'\0'};
					for(int i=0;i<strlen(goodsid);i++)
					{			
						strncpy(d,goodsid+i,1);
						if (strcmp(b,d)==0)
						{							
							strncpy(effects[num],goodsid+len,i-len);						
							len=i+1;
							num++;
						}
					}	
					for (int i=0;i<number;)
					{
						saveGoodsInBag(pg_hero,effects[i+1],atoi(effects[i]));
						i=i+2;
					}
					
					if (reward->getFlag()==1)
					{
						increaseBoundGold(pg_hero,reward->getMoney());
					}					
					pg_hero->receiveRechargeChange(index);
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%ld,%s",23,10,money->getAccMoney(),pg_hero->memHero->recharge_flag);
					send_msg(pg_hero->getFd(),g_out_buf);
				}				
				else
				{
					msg_error(g_out_buf,44);
					send_msg(pg_hero->getFd(),g_out_buf);
				}
			}				
		}
	}
	else
	{
		cout<<"jolly:you have already receive the recharge reward"<<endl;
	}
}

void onlineRewardRefresh(char *buffer)
{
	cout<<"22,8"<<endl;
	Reward_Online *reward_online=pg_hero->getRewardOnline();
	if (reward_online!=NULL)
	{
		cout<<"###################################"<<endl;
		cout<<reward_online->getGoodsId()<<endl;
		cout<<"###################################"<<endl;
		if (strlen(reward_online->getGoodsId())==0)
		{				
			reward_online->normalRefresh(g_out_buf,sizeof(g_out_buf));
			send_msg(pg_hero->getFd(),g_out_buf);
		}		
		else 
		{
			reward_online->onlineReward_msg(g_out_buf,sizeof(g_out_buf));
			send_msg(pg_hero->getFd(),g_out_buf);
			cout<<"jolly:you have already normal refresh once"<<endl;
		}
	}
}

void onlineRewardReceive(char *buffer)
{
	Reward_Online *reward_online=pg_hero->getRewardOnline();
	if (reward_online!=NULL)
	{
		if (reward_online->judgeCanReceive())
		{
			if (saveGoodsInBag(pg_hero,reward_online->getGoodsId(),1))
			{
				increaseBoundGameMoney(pg_hero,reward_online->getMoney());
				increaseBoundGold(pg_hero,reward_online->getGold());
				reward_online->setStage(g_out_buf,sizeof(g_out_buf));
				send_msg(pg_hero->getFd(),g_out_buf);
			}
		}		
	}
}
void onlineRewardGoldRefresh(char *buffer)
{
	Reward_Online *reward_online=pg_hero->getRewardOnline();
	if (reward_online!=NULL)
	{
		if (useGold(pg_hero,2))
		{
			reward_online->goldRefresh(g_out_buf,sizeof(g_out_buf));
			send_msg(pg_hero->getFd(),g_out_buf);
			
			//记录日志2013.4.28
			char account_msg[1024]={'\0'};
			snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d",16,2,server_name,(int)myTime.tv_sec,pg_hero->getIdentity(),pg_hero->getNickName(),pg_role->getUserName(),2);
			write_log(account_msg);	
		}		
	}
}

void onlineRewardReturn(char *buffer)
{
	cout<<"22,12"<<endl;
	Reward_Online *reward_online=pg_hero->getRewardOnline();
	if (reward_online!=NULL)
	{
		reward_online->msg_return(g_out_buf,sizeof(g_out_buf));
		send_msg(pg_hero->getFd(),g_out_buf);
	}
}

void levelRewardReturn(char *buffer)
{
	cout<<"36,0"<<endl;
	memset(g_out_buf,0,sizeof(g_out_buf));
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",36,0,levelRewardData[pg_hero->memHero->levelFlag].level);
	send_msg(pg_hero->getFd(),g_out_buf);
}

void levelRewardReceive(char *buffer)
{
	cout<<"36,1"<<endl;
	int flag=pg_hero->memHero->levelFlag;
	memset(g_out_buf,0,sizeof(g_out_buf));
	if (flag<0||flag>8)
	{
		cout<<"jolly:levelFlag is error in reward_communicate.cpp 342 and levelFlag:"<<flag<<endl;
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",36,1,0);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else
	{	
		int level=levelRewardData[flag].level;
		int heroLevel=pg_hero->getGradeNow();
		if (heroLevel<level)
		{
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",36,1,0);
			send_msg(pg_hero->getFd(),g_out_buf);
		}	
		else
		{
			if (receive_levelReward(pg_hero,flag))
			{
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",36,1,1);
				send_msg(pg_hero->getFd(),g_out_buf);
				pg_hero->memHero->levelFlag++;
				memset(g_out_buf,0,sizeof(g_out_buf));
				if (pg_hero->memHero->levelFlag>8)
				{
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",36,0,0);
					send_msg(pg_hero->getFd(),g_out_buf);	
				}
				else
				{						
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",36,0,levelRewardData[pg_hero->memHero->levelFlag].level);
					send_msg(pg_hero->getFd(),g_out_buf);	
				}
			}			
		}
	}
}

void levelRewardExist(char *buffer)
{	
	cout<<"36,2"<<endl;
	memset(g_out_buf,0,sizeof(g_out_buf));
	if (pg_hero->memHero->levelFlag>8||pg_hero->memHero->levelFlag<0)
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",36,2,0,0);
	}
	else
	{		
		if (levelRewardData[pg_hero->memHero->levelFlag].level>pg_hero->getGradeNow())
		{
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",36,2,1,0);
		}
		else
		{
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",36,2,1,1);
		}
	}
	send_msg(pg_hero->getFd(),g_out_buf);	
}


void reward_return(char *buffer)
{	
	cout<<"36,3"<<endl;
	pg_hero->send_msg_reward();
}

void receiveSignReward(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_INT(int flag) 
	cout<<"36,5,"<<flag<<endl;
	
	if (flag==1)			//补签
	{
		int allowSign=pg_hero->getAllowSign();
		if (allowSign==0)
		{
			return;
		}
		else if (allowSign>3)
		{
			return;
		}
		else
		{
			int gold=pg_hero->getAllowSignGold();
			if (useGold(pg_hero,gold))
			{
				allowSign--;
				pg_hero->setAllowSign(allowSign);
				if (allowSign==0)
				{
					gold=10;
				}
				else
				{
					gold=gold*2;	
				}
				pg_hero->setAllowSignGold(gold);
				
				pg_hero->memHero->rewarddata.last_day++;
				pg_hero->memHero->downLineDay+=86400;
			}
		}
	}
	else if (flag==2)			//领取
	{
		if (pg_hero->getAllowSign()!=0)
		{
			cout<<"allowSign is not 0,in this, reward_communicate.cpp 343"<<endl;
			saveGoodsInBag(pg_hero,signRewardData[0].goodsid,signRewardData[0].number);
			pg_hero->memHero->rewarddata.last_day=1;
			pg_hero->setAllowSign(0);
		}
		else
		{
			cout<<"pg_hero->memHero->rewarddata.last_day::"<<pg_hero->memHero->rewarddata.last_day<<endl;
			saveGoodsInBag(pg_hero,signRewardData[pg_hero->memHero->rewarddata.last_day].goodsid,signRewardData[pg_hero->memHero->rewarddata.last_day].number);
			pg_hero->memHero->rewarddata.last_day++;
		}
		pg_hero->memHero->downLineDay=myTime.tv_sec;
		pg_hero->memHero->rewarddata.last_day_flag=0;
	}	
	
	pg_hero->send_msg_reward();
}