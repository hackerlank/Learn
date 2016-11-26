#include "ride_comm.h"
#include "hero_fight.h"
#include "money_operator.h"

extern Ride_Special_Skill_Config rideSpecialSkill_config[3];
extern map<string, Hero*> heroId_to_pHero;
//准备骑乘通信
void prepareRideComm(char *buffer)
{
	char msg[200] = {0};
	int ret = pg_hero->prepareRide();
	if (ret == 0 || ret == 1)
	{
		sprintf(msg, "31,0,1,%d", RIDE_PREPARE_TIME);
	} else if (ret == 2) {
		//命令头31,1；1表示开始骑乘成功，坐骑图片ID，人物乘上坐骑的新速度
		Ride *ride = pg_hero->getRide();
		if (ride==NULL)
		{
			return;
		}
		char *photoId = ride->getPhotoId();
		sprintf(msg, "31,1,1,%s,%s,%d", pg_hero->getIdentity(), photoId, pg_hero->getSpeed());
		send_nine_msg(pg_hero, msg);
	}
	else if (ret==6)
	{
		memset(g_out_buf,0,sizeof(g_out_buf));
		msg_error(g_out_buf,128);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else {
		sprintf(msg, "31,0,0,%d", ret);
	}
	
	send_msg(pg_hero->getFd(), msg);
}

//开始骑乘通信
void startRideComm(char *buffer)
{
	char msg[200] = {0};
	int ret = pg_hero->startRide();
	if (ret == 0)
	{
		//命令头31,1；1表示开始骑乘成功，坐骑图片ID，人物乘上坐骑的新速度
		Ride *ride = pg_hero->getRide();
		char *photoId = ride->getPhotoId();
		sprintf(msg, "31,1,1,%s,%s,%d", pg_hero->getIdentity(), photoId, pg_hero->getSpeed());
		send_nine_msg(pg_hero, msg);
	} else {
		sprintf(msg, "31,1,0,%d", ret);
		send_msg(pg_hero->getFd(), msg);
	}
}

void stopRideComm(char *buffer)
{
	char msg[200] = {0};
	int ret = pg_hero->stopRide();
	if (ret == 0)
	{
		//命令头31,1；1表示开始骑乘成功，坐骑图片ID，人物乘上坐骑的新速度
		sprintf(msg, "31,2,1,%s,%d", pg_hero->getIdentity(), pg_hero->getSpeed());
		send_nine_msg(pg_hero, msg);
	} else {
		sprintf(msg, "31,2,0,%d", ret);
		send_msg(pg_hero->getFd(), msg);
	}
}

//请求单个坐骑详细信息
void rideDetailComm(char *buffer)
{
	cout<<"30,0"<<endl;
	Ride *ride=pg_hero->getRide();
	if (ride==NULL)
	{
		return;
	}
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	
	ride->ride_msg_return(g_out_buf,sizeof(g_out_buf),pg_hero);
	
	send_msg(pg_hero->getFd(),g_out_buf);

	memset(g_out_buf,0,sizeof(g_out_buf));
	ride->ride_evolution_return(g_out_buf,sizeof(g_out_buf),pg_hero->memHero->vipDailyData.zuoqiFresh);
	send_msg(pg_hero->getFd(),g_out_buf);
}

//坐骑进阶
void rideEvolutionComm(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_INT(int flag)
	
	cout<<"30,2,"<<flag<<endl;
	
	Ride *ride=pg_hero->getRide();
	if (ride==NULL)
	{
		return;
	}
	
	if (flag==0)
	{
		memset(g_out_buf,0,sizeof(g_out_buf));
		ride->ride_evolution_return(g_out_buf,sizeof(g_out_buf),pg_hero->memHero->vipDailyData.zuoqiFresh);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else if (flag==1)
	{
		if (ride->getQuality()==7)
		{
			//坐骑已到最大品阶,无法进阶
			return;
		}
		int evolution=pg_hero->memHero->vipDailyData.zuoqiNumber;
		if (pg_hero->memHero->vipDailyData.zuoqiFresh>0)
		{
			pg_hero->memHero->vipDailyData.zuoqiFresh--;
		}
		else
		{
			int cost=ride->getCost();
			if (!useGold(pg_hero,cost))
			{
				cout<<"pg_hero has no enough gold ,need gold is :"<<cost<<endl;
				return;
			}
			else
			{
				ride->evolutionIncreaseCost();
			}
		}
		
		int number=random_number(1,100);
		if (number<=pg_hero->memHero->vipDailyData.zuoqiRate)
		{
			evolution=evolution*2;
		}
		
		if (evolution<0)
		{
			cout<<"evolution<0 and evolution:"<<evolution<<endl;
			return;
		}
		
		if (ride->evolutionIncrease(evolution,pg_hero))
		{			
			memset(g_out_buf,0,sizeof(g_out_buf));
			ride->ride_msg_return(g_out_buf,sizeof(g_out_buf),pg_hero);
			send_msg(pg_hero->getFd(),g_out_buf);
			
			memset(g_out_buf,0,sizeof(g_out_buf));
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%s,%s",30,4,pg_hero->getIdentity(),ride->getPhotoId());
			
			Nbox *box = pg_hero->getMap()->getBox();
			if(box == NULL)
			{
				return;
			}
			StyObj obj(pg_hero->getIdentity(),HERO_STYLE_TYPE);		
			box->getStaInSrcVec(obj);	
			box->sentBoxMsg(g_out_buf);
			
			pg_hero->send_msg_att();
		
			/*全服广播*/
			char info[1024]={'\0'};
			snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d",7,SYSTEM_WARN,"xf027",3,1,pg_hero->getNickName(),pg_hero->getIdentity(),0,0,3,ride->getQuality(),0,0,0,3,ride->getNickName(),0,0,0);
			map<string, Hero*>::iterator it_hero;

			for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
			{
				if (it_hero->second!=NULL)
				{						
					send_msg(it_hero->second->getFd(),info);
				}
			}
		}
		
		memset(g_out_buf,0,sizeof(g_out_buf));
		ride->ride_evolution_return(g_out_buf,sizeof(g_out_buf),pg_hero->memHero->vipDailyData.zuoqiFresh);
		send_msg(pg_hero->getFd(),g_out_buf);
		
		/*有一个7代坐骑，给头衔，不要羡慕哥*/
		if (ride->getQuality()==7)
		{
			pg_hero->addTitle("T021");
		}
	}	
}

//坐骑终极技能相关
void rideFinalSkillComm(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_INT(int flag)  //1为请求数据,2为开格子,3为刷新
	int flagArr[3];
	for (int i=0;i<3;i++)
	{
		MSG_INT(flagArr[i]);
	}
	
	Ride *ride=pg_hero->getRide();
	if (ride==NULL)
	{
		return;
	}
	
	memset(g_out_buf,0,sizeof(g_out_buf));
	if (flag==1)
	{		
		ride->ride_finalSkill_return(g_out_buf,sizeof(g_out_buf));
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else if (flag==2)
	{
		int gridNumber=ride->getFinalGrid();
		if (gridNumber!=3)
		{
			int stage=ride->getFinalSkillStage();
			int gold=rideSpecialSkill_config[stage].openCost[gridNumber-1];
			if (useBoundGold(pg_hero,gold))
			{
				ride->openOneSkillGrid();
				ride->ride_finalSkill_return(g_out_buf,sizeof(g_out_buf));
				send_msg(pg_hero->getFd(),g_out_buf);
			}
		}
	}
	else if (flag==3)
	{
		int moneyFlag=0;
		
		for (int i=0;i<3;i++)
		{
			if (flagArr[i]==1)
			{
				moneyFlag++;
			}
		}
		
		int money;
		if (moneyFlag==3)
		{
			return;
		}
		else 
		{
			money=ride->getRefreshMoney(moneyFlag);
		}

		if (useBoundGold(pg_hero,money))
		{
			vector<int> flagV;
			int gridNumber=ride->getFinalGrid();
			flagV.push_back(flagArr[0]);
			flagV.push_back(flagArr[1]);
			flagV.push_back(flagArr[2]);		
			ride->refreshSkill(flagV,pg_hero);	
			ride->ride_finalSkill_return(g_out_buf,sizeof(g_out_buf));
			send_msg(pg_hero->getFd(),g_out_buf);		
			pg_hero->send_msg_att();
		}		
	}	
}