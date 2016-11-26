#include "money_operator.h"

#include "consume_reward.h"
#include "system_activity_reward_assist.h"

extern Consume_reward *consume_reward_asist;

extern char g_out_buf[20480];
extern char server_name[10];

bool increaseBoundGold(Hero *hero,long _boundGold)	//增加绑定元宝
{
	Money *money=hero->getMoney();
	if (money==NULL)								//money类为空 返回false;
	{
		return false;
	}
	if (_boundGold<0)								//增加的绑定元宝为负数,返回false
	{
		cout<<"jolly:you can increase a negative number money_operator 12"<<endl;
		return false;
	}
	
	money->money_increaseBoundGold(_boundGold);	
	money->money_inform(g_out_buf,sizeof(g_out_buf));
	send_msg(hero->getFd(),g_out_buf);				//发送增加了绑定元宝之后的金币状态
	/*记录使用绑定元宝的流水账 jolly 2,2 start*/
	char account_msg[1024]={'\0'};
	snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%ld,%ld",11,1,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),_boundGold,money->money_getBoundGold());
	write_log(account_msg);	
	/*记录使用绑定元宝的流水账 jolly 2,2 end*/	
	return true;
}
	
bool useBoundGold(Hero *hero,long _boundGold)	//使用绑定元宝数量
{
	Money *money=hero->getMoney();
	if (money==NULL)								//money类为空 返回false;
	{
		return false;
	}
	if (_boundGold<0)								//使用的绑定元宝为负数,返回false
	{
		cout<<"jolly:you can increase a negative number money_operator 32"<<endl;
		return false;
	}
	
	long boundGold=money->money_getBoundGold();
	if ((boundGold-_boundGold)<0)										//当前绑定元宝不足以使用
	{
		if (money->getGoldFlag())					//玩家已打开自动使用非绑定元宝功能
		{
			if ((boundGold+money->money_getGold()-_boundGold)<0)						//两种元宝均不够使用,则通知玩家要充值
			{
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%ld",9,MONEY_NOT_ENOUGH,_boundGold-boundGold);
				// msg_error(g_out_buf,81);
				send_msg(hero->getFd(),g_out_buf);
				return false;
			}
			else									//两种元宝够使用,则使用成功
			{
				money->money_useBoundGold(boundGold);
				money->money_useGold(_boundGold-boundGold);
				money->money_inform(g_out_buf,sizeof(g_out_buf));
				send_msg(hero->getFd(),g_out_buf);				//发送使用了绑定元宝之后的金币状态
				/*记录使用绑定元宝的流水账 jolly 2,2 start*/
				char account_msg[1024]={'\0'};
				snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%ld,%ld",11,0,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),_boundGold,money->money_getBoundGold());
				write_log(account_msg);	
				/*记录使用绑定元宝的流水账 jolly 2,2 end*/	
				return true;
			}
		}
		else
		{
			// snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,MONEY_NOT_ENOUGH,0);
			msg_error(g_out_buf,81);
			send_msg(hero->getFd(),g_out_buf);
			return false;
		}
	}		
	else												//当前绑定元宝足够使用
	{
		money->money_useBoundGold(_boundGold);
		money->money_inform(g_out_buf,sizeof(g_out_buf));
		send_msg(hero->getFd(),g_out_buf);				//发送使用了绑定元宝之后的金币状态
		/*记录使用绑定元宝的流水账 jolly 2,2 start*/
		char account_msg[1024]={'\0'};
		snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%ld,%ld",11,0,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),_boundGold,money->money_getBoundGold());
		write_log(account_msg);	
		/*记录使用绑定元宝的流水账 jolly 2,2 end*/	
		return true;
	}
}

bool campareBoundGold(Hero *hero,long _boundGold)		//判断绑定元宝是否够用
{
	Money *money=hero->getMoney();
	if (money==NULL)								//money类为空 返回false;
	{
		return false;
	}
	if (_boundGold<0)								//比较的绑定元宝为负数,返回false
	{
		cout<<"jolly:you can increase a negative number money_operator 82"<<endl;
		return false;
	}
	
	if ((money->money_getBoundGold()+money->money_getGold())<_boundGold)		//若比较的绑定元宝数量大于了绑定元宝加上非绑定元宝的数量,则提示充值
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%ld",9,MONEY_NOT_ENOUGH,_boundGold-money->money_getBoundGold()+money->money_getGold());
		send_msg(hero->getFd(),g_out_buf);
		return false;
	}
	else if (money->money_getBoundGold()>_boundGold)					//比较的绑定元宝数小于了自有的绑定元宝,则提示成功
	{
		return true;
	}
	
	//大于自身的绑定元宝但小于绑定+非绑定元报之和,则判断是否开启了自动使用非绑定元宝功能
	if (!money->getGoldFlag())					//未开自动使用非绑定元宝功能,则提示开启
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,MONEY_NOT_ENOUGH,0);
		send_msg(hero->getFd(),g_out_buf);
		return false;
	}
	else										//已经开启,则提示成功
	{
		return true;
	}
}

bool increaseGold(Hero *hero,long _gold)	//增加元宝	
{
	Money *money=hero->getMoney();
	if (money==NULL)								//money类为空 返回false;
	{
		return false;
	}
	if (_gold<0)								//增加的元宝为负数,返回false
	{
		cout<<"jolly:you can increase a negative number money_operator 86"<<endl;
		return false;
	}
	
	money->money_increaseGold(_gold);
	money->money_inform(g_out_buf,sizeof(g_out_buf));
	send_msg(hero->getFd(),g_out_buf);				//发送增加了元宝之后的金币状态	
	
	// 增加获得货币写日志功能,jolly 2012 12 17 start
	char account_msg[1024]={'\0'};
	sprintf(account_msg,"%d,%d,%s,%d,%s,%s,%ld,%ld",4,0,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),money->money_getGold(),_gold);
	write_log(account_msg);	
	// 增加获得货币写日志功能,jolly 2012 12 17 end
	
	hero->memSet();
	return true;
}

bool useGold(Hero *hero,long _gold)	//使用元宝数量
{
	Money *money=hero->getMoney();
	if (money==NULL)							//money类为空 返回false;
	{
		return false;
	}
	if (_gold<0)								//使用的元宝为负数,返回false
	{
		cout<<"jolly:you can increase a negative number money_operator 111"<<endl;
		return false;
	}
	
	if ((money->money_getGold()-_gold)<0)				//当前元宝不足以使用
	{		
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%ld",9,MONEY_NOT_ENOUGH,_gold-money->money_getGold());
		send_msg(hero->getFd(),g_out_buf);
		return false;
	}
	else										//当前元宝可以使用
	{
		money->money_useGold(_gold);
		money->money_inform(g_out_buf,sizeof(g_out_buf));
		send_msg(hero->getFd(),g_out_buf);				//发送使用了了元宝之后的金币状态
		// 增加获得货币写日志功能,jolly 2012 12 17 start
		char account_msg[1024]={'\0'};
		sprintf(account_msg,"%d,%d,%s,%d,%s,%s,%ld,%ld",4,1,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),money->money_getGold(),_gold);
		write_log(account_msg);	
		// 增加获得货币写日志功能,jolly 2012 12 17 end
		
		hero->memSet();
		/**
			*添加到消费奖励队伍中，added by xhm;
		*/
		if(consume_reward_asist != NULL)
		{
			if(!isNowConsumeReward(time(NULL)))		
			{
				hero->memHero->useGoldForActive=0;
			}else{
				//记录使用的元宝数量,用于发奖励
				hero->memHero->useGoldForActive+=_gold;
				int succ = consume_reward_asist->add_to_reward_team(hero->getIdentity(),hero->memHero->useGoldForActive);
				if(succ==1)
				{
					hero->memHero->useGoldForActive=0;
					cout<<"[XHM MSG]:recharge_reward_asist->add_to_reward_team ERROR<money_operater.cpp> "<<endl;	
				}
			}
		}
		
		return true;
	}
}

bool campareGold(Hero *hero,long _gold)		//判定元宝是否够用
{
	Money *money=hero->getMoney();
	if (money==NULL)							//money类为空 返回false;
	{
		return false;
	}
	if (_gold<0)								//比较的元宝为负数,返回false
	{
		cout<<"jolly:you can increase a negative number money_operator 177"<<endl;
		return false;
	}	

	if (_gold>money->money_getGold())				//比较的元宝大于了自身的元宝,则提示充值
	{
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%ld",9,MONEY_NOT_ENOUGH,_gold-money->money_getGold());
		send_msg(hero->getFd(),g_out_buf);
		return false;
	}
	else
	{
		return true;
	}	
}

bool increaseBoundGameMoney(Hero *hero,long _boundGameMoney)	//增加绑定游戏币	
{
	Money *money=hero->getMoney();
	if (money==NULL)								//money类为空 返回false;
	{
		return false;
	}
	if (_boundGameMoney<0)								//增加的绑定游戏币为负数,返回false
	{
		cout<<"jolly:you can increase a negative number money_operator 141"<<endl;
		return false;
	}
	
	money->money_increaseBoundGameMoney(_boundGameMoney);
	money->money_inform(g_out_buf,sizeof(g_out_buf));
	send_msg(hero->getFd(),g_out_buf);				//发送绑定游戏币之后的金币状态	
	if (_boundGameMoney)
	{
		/*记录使用绑定游戏币的流水账 jolly 2,2 start*/
		char account_msg[1024]={'\0'};
		snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%ld,%ld",12,1,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),_boundGameMoney,money->money_getBoundGameMoney());
		write_log(account_msg);	
		/*记录使用绑定游戏币的流水账 jolly 2,2 end*/	
	}
	return true;	
}

bool useBoundGameMoney(Hero *hero,long _boundGameMoney)	//使用绑定游戏币数量
{
	Money *money=hero->getMoney();
	if (money==NULL)								//money类为空 返回false;
	{
		return false;
	}
	if (_boundGameMoney<0)								//使用的绑定游戏币为负数,返回false
	{
		cout<<"jolly:you can increase a negative number money_operator 160"<<endl;
		return false;
	}
	
	long boundGameMoney=money->money_getBoundGameMoney();
	if ((boundGameMoney-_boundGameMoney)<0)				//当前绑定游戏币不足以使用
	{
		if (money->getMoneyFlag())						//当前开启了自动使用非绑定游戏币功能
		{
			if ((boundGameMoney+money->money_getGameMoney()-_boundGameMoney)<0)		//绑定游戏币和非绑定游戏币都不足以使用
			{
				msg_error(g_out_buf,1);
				send_msg(hero->getFd(),g_out_buf);
				return false;
			}
			else										//消耗部分非绑定游戏币可以使用成功
			{
				money->money_useBoundGameMoney(boundGameMoney);
				money->money_useGameMoney(_boundGameMoney-boundGameMoney);
				money->money_inform(g_out_buf,sizeof(g_out_buf));
				send_msg(hero->getFd(),g_out_buf);				//发送使用绑定游戏币之后的金币状态	
				if (_boundGameMoney>50000)
				{
					/*记录使用绑定游戏币的流水账 jolly 2,2 start*/
					char account_msg[1024]={'\0'};
					snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%ld,%ld",12,0,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),_boundGameMoney,money->money_getBoundGameMoney());
					write_log(account_msg);	
					/*记录使用绑定游戏币的流水账 jolly 2,2 end*/	
				}
				return true;
			}
		}
		else											//当前未开启自动使用非绑定游戏币功能
		{
			msg_error(g_out_buf,66);
			send_msg(hero->getFd(),g_out_buf);
			return false;
		}
	}	
	else												//当前绑定游戏币足够使用
	{
		money->money_useBoundGameMoney(_boundGameMoney);
		money->money_inform(g_out_buf,sizeof(g_out_buf));
		send_msg(hero->getFd(),g_out_buf);				//发送使用绑定游戏币之后的金币状态	
		if (_boundGameMoney>50000)
		{
			/*记录使用绑定游戏币的流水账 jolly 2,2 start*/
			char account_msg[1024]={'\0'};
			snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%ld,%ld",12,0,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),_boundGameMoney,money->money_getBoundGameMoney());
			write_log(account_msg);	
			/*记录使用绑定游戏币的流水账 jolly 2,2 end*/	
		}
		return true;
	}
}

bool campareBoundGameMoney(Hero *hero,long _boundGameMoney)		//判断绑定游戏币是否够用
{	
	Money *money=hero->getMoney();
	if (money==NULL)								//money类为空 返回false;
	{
		return false;
	}
	if (_boundGameMoney<0)								//比较的绑定游戏币为负数,返回false
	{
		cout<<"jolly:you can increase a negative number money_operator 211"<<endl;
		return false;
	}

	if (_boundGameMoney>(money->money_getBoundGameMoney()+money->money_getGameMoney()))			//若比较的钱大于绑定和非绑定的游戏币之和,则直接返回false		
	{
		msg_error(g_out_buf,1);
		send_msg(hero->getFd(),g_out_buf);
		return false;
	}
	else					//若比较的钱比绑定和非绑定的游戏币少,则接着比较是否开启了自动使用游戏币功能
	{
		if (money->getMoneyFlag()) 					//开启了自动使用非绑定游戏币功能							
		{
			return true;							//返回true
		}
		else										//未开启自动使用非绑定游戏币功能
		{
			if (_boundGameMoney>money->money_getBoundGameMoney())		//比较的钱比绑定游戏币多,则提示玩家是否使用非绑定游戏币
			{			
				msg_error(g_out_buf,66);
				send_msg(hero->getFd(),g_out_buf);
				return false;
			}
			else								//绑定的游戏币已经比比较的游戏币多了,则直接返回true;
			{
				return true;
			}
		}
	}
}

bool increaseGameMoney(Hero *hero,long _gameMoney)	//增加游戏币
{	
	Money *money=hero->getMoney();
	if (money==NULL)								//money类为空 返回false;
	{
		return false;
	}
	if (_gameMoney<0)								//增加的游戏币为负数,返回false
	{
		cout<<"jolly:you can increase a negative number money_operator 210"<<endl;
		return false;
	}
	
	money->money_increaseGameMoney(_gameMoney);
	money->money_inform(g_out_buf,sizeof(g_out_buf));
	send_msg(hero->getFd(),g_out_buf);				//发送增加游戏币之后的金币状态	
	
	// 增加获得货币写日志功能,jolly 2012 12 17 start
	char account_msg[1024]={'\0'};
	sprintf(account_msg,"%d,%d,%s,%d,%s,%s,%ld,%ld",3,0,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),money->money_getGameMoney(),_gameMoney);
	write_log(account_msg);	
	// 增加获得货币写日志功能,jolly 2012 12 17 end
	return true;
}

bool useGameMoney(Hero *hero,long _gameMoney)	//使用游戏币数量
{
	Money *money=hero->getMoney();
	if (money==NULL)								//money类为空 返回false;
	{
		return false;
	}
	if (_gameMoney<0)								//使用的游戏币为负数,返回false
	{
		cout<<"jolly:you can increase a negative number money_operator 228"<<endl;
		return false;
	}
	
	if ((money->money_getGameMoney()-_gameMoney)<0)
	{
		msg_error(g_out_buf,1);
		send_msg(hero->getFd(),g_out_buf);
		return false;
	}
	else
	{
		money->money_useGameMoney(_gameMoney);
		money->money_inform(g_out_buf,sizeof(g_out_buf));
		send_msg(hero->getFd(),g_out_buf);				//发送使用游戏币之后的金币状态	
		
		// 增加获得货币写日志功能,jolly 2012 12 17 start
		char account_msg[1024]={'\0'};
		sprintf(account_msg,"%d,%d,%s,%d,%s,%s,%ld,%ld",3,1,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),money->money_getGameMoney(),_gameMoney);
		write_log(account_msg);	
		// 增加获得货币写日志功能,jolly 2012 12 17 end
		return true;
	}
}

bool campareGameMoney(Hero *hero,long _gameMoney)		//判断游戏币是否够用
{
	Money *money=hero->getMoney();
	if (money==NULL)								//money类为空 返回false;
	{
		return false;
	}
	if (_gameMoney<0)								//使用的游戏币为负数,返回false
	{
		cout<<"jolly:you can increase a negative number money_operator 228"<<endl;
		return false;
	}
	
	if ((money->money_getGameMoney()-_gameMoney)<0)
	{
		msg_error(g_out_buf,1);
		send_msg(hero->getFd(),g_out_buf);
		return false;
	}
	else
	{
		return true;
	}
}

void killMonsterEarnMoney(Hero *hero,long _money)			//杀怪获得金币
{	
	Money *money=hero->getMoney();
	if (money==NULL)
	{
		return; 
	}
	money->money_increaseBoundGameMoney(_money);
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%ld",9,KILLMON_EARN_MONEY,money->money_getBoundGameMoney());
	send_msg(hero->getFd(),g_out_buf);
}

bool increaseAccMoney(Hero *hero,long accMoney)		//充值
{
	if (accMoney<0)
	{
		return false;
	}
	hero->getMoney()->increaseAccMoney(accMoney);
	
	hero->judgeVipLevel();
	return true;
}