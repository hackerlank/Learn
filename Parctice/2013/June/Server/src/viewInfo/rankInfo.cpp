/*************************************************

Copyright: xhm

Author:xhm

Date:2012-12-7 

Description:GM server排名数据逻辑实现文件；

**************************************************/

#include <queue>
#include "money.h"
#include "rankInfo.h"
#include "meridian_asist.h"
#include "pet_box.h"
#include "ride.h"
#include "mail_systerm_interface.h"
static char tempRankInfo[MAX_RANK_VALUE*200];

extern char sendName[30];
extern char sendTitle[30];
extern char heroRankContent[1024];
extern char petRankContent[1024];
extern char rideRankContent[1024];
extern char server_name[10];

//用于优先队列排序；
class queue_cmp{
public:
    bool operator()(RankInfo_T& x,RankInfo_T& y)
    {
		if(x.value < y.value)
			return true;  
		
		if(x.value == y.value && x.grade < y.grade)
			return true;
		
		return false;
    }
};


/**************************
函数作用  初始化数据；
***************************/
RankInfo::RankInfo()
{
	initBasicData();//初始化数据；
	memset(lowLimit,0,sizeof(lowLimit));
	memset(RankInfoLastSize,0,sizeof(RankInfoLastSize));
	memset(petId,0,sizeof(petId));
	memset(petName,0,sizeof(petName));
	
	RankCountLimit[0]=40;
	RankCountLimit[1]=40;
	RankCountLimit[2]=40;//排名个数限制；
	RankCountLimit[3]=40;
	RankCountLimit[4]=40;
	RankCountLimit[5]=40;
	RankCountLimit[6]=40;
	RankCountLimit[7]=40;
	
	myRankVector.push_back(&powerRank);
	myRankVector.push_back(&levelRank);
	myRankVector.push_back(&wealthRank);//将容器放置到myRankVector管理；
	myRankVector.push_back(&shamblesRank);
	myRankVector.push_back(&prestigeRank);
	myRankVector.push_back(&activityRankInfo);
	myRankVector.push_back(&petRank);
	myRankVector.push_back(&rideRank);
	
	for (int i=0;i<3;i++)
	{
		strncpy(rewardHero[i],"0",sizeof(rewardHero[i]));
	}
		
	for (int j=0;j<32;j++)
	{
		memset(rankInfoMsg[j],0,sizeof(rankInfoMsg[j]));
		snprintf(rankInfoMsg[j],sizeof(rankInfoMsg[j]),"%d,%d,%d",11,11,j/4);
	}
}


RankInfo::~RankInfo()
{

}


/**************************
函数作用  初始化数据；
***************************/
void 
RankInfo::initBasicData()
{	
	if(!powerRank.empty())
	{
		powerRank.clear();
		map<string,RankInfo_T>().swap(powerRank);
	}
	
	if(!wealthRank.empty())	
	{		
		wealthRank.clear();
		map<string,RankInfo_T>().swap(wealthRank);
	}
	
	if(!shamblesRank.empty())	
	{	
		shamblesRank.clear();
		map<string,RankInfo_T>().swap(shamblesRank);
	}
	
	if(!prestigeRank.empty())
	{	
		prestigeRank.clear();
		map<string,RankInfo_T>().swap(prestigeRank);
	}	
	
	if(!activityRankInfo.empty())
	{
		activityRankInfo.clear();	
		map<string,RankInfo_T>().swap(activityRankInfo);
	}
	
	if(!levelRank.empty())
	{
		levelRank.clear();
		map<string,RankInfo_T>().swap(levelRank);
	}
	
	if(!petRank.empty())
	{
		petRank.clear();
		map<string,RankInfo_T>().swap(petRank);
	}
	
	if(!rideRank.empty())
	{
		rideRank.clear();
		map<string,RankInfo_T>().swap(rideRank);
	}
}


/**************************
函数作用 根据类型，将角色信息加入到用于排序列表中；
函数参数 _type  加入排序信息类型；
		 _value 用于当前角色类型排名值的大小；
  返回值 bool 	加入成功ture 否则false; 
    调用 角色获取排名信息时；
***************************/
bool RankInfo::updateRankInfo(int _type,unsigned long _value)
{
	if(_type <0 || _type >= MAX_INFO_TYPE)
		return false;	

	if(_value < 0)
		return false;
	
	if (_type<6)
	{
		RankInfo_T myRankInfo(grade,_value,heroName,camp,party,heroId,power);			
		myRankVector[_type]->insert(AddRankInfo(heroId,myRankInfo));
	}
	else
	{
		RankInfo_T myRankInfo(grade,_value,heroName,heroId,petId,petName);			
		myRankVector[_type]->insert(AddRankInfo(petId,myRankInfo));
	}
}


/**************************
函数作用 开始获取排名信息列表，从memcached里面读取到能参加排名的角色信息并且保存；
  返回值 bool 获取信息成功; 
    调用 排序时间调用(在文件model/my_time.cpp)；
***************************/
void RankInfo::setInfoToLocal()
{
    priority_queue<RankInfo_T, vector<RankInfo_T>, queue_cmp> rank_queue;
		
	for(int i = 0; i < MAX_INFO_TYPE; i++)
	{

		if(RankInfoLastSize[i] >= myRankVector[i]->size())
		{
			// cout<<"RankInfoLastSize[i] >= myRankVector[i]->size()"<<endl;
			continue;
		}
		else
		{
			switch(i)
			{
			case 0:
				memset(myMemRankInfo.powerRankKey,0,sizeof(myMemRankInfo.powerRankKey));
				memset(myMemRankInfo.powerRankInfo,0,sizeof(myMemRankInfo.powerRankInfo));	
			break;			 
			case 1:
				memset(myMemRankInfo.levelRankKey,0,sizeof(myMemRankInfo.levelRankKey));
				memset(myMemRankInfo.levelRankInfo,0,sizeof(myMemRankInfo.levelRankInfo));		
			 break;			 
			case 2:		
				memset(myMemRankInfo.wealthRankKey,0,sizeof(myMemRankInfo.wealthRankKey));
				memset(myMemRankInfo.wealthRankInfo,0,sizeof(myMemRankInfo.wealthRankInfo));
			 break;			 
			case 3:
				memset(myMemRankInfo.shamblesRankKey,0,sizeof(myMemRankInfo.shamblesRankKey));
				memset(myMemRankInfo.shamblesRankInfo,0,sizeof(myMemRankInfo.shamblesRankInfo));			
			 break;			 
			case 4:
				memset(myMemRankInfo.prestigeRankKey,0,sizeof(myMemRankInfo.prestigeRankKey));
				memset(myMemRankInfo.prestigeRankInfo,0,sizeof(myMemRankInfo.prestigeRankInfo));			
			 break;			 
			case 5:	
				memset(myMemRankInfo.activityRankKey,0,sizeof(myMemRankInfo.activityRankKey));
				memset(myMemRankInfo.activityRankInfo,0,sizeof(myMemRankInfo.activityRankInfo));
			 break;			 
			case 6:
				memset(myMemRankInfo.petRankKey,0,sizeof(myMemRankInfo.petRankKey));
				memset(myMemRankInfo.petRankInfo,0,sizeof(myMemRankInfo.petRankInfo));			
			 break;			 
			case 7:
				memset(myMemRankInfo.rideRankKey,0,sizeof(myMemRankInfo.rideRankKey));
				memset(myMemRankInfo.rideRankInfo,0,sizeof(myMemRankInfo.rideRankInfo));			
			 break;
			
			default:
				break;
			}
		}
		
		while (!rank_queue.empty())
		{			//清空容器；
			rank_queue.pop();
		}
		
		int index=0;
		for(map<string,RankInfo_T>::iterator curr = myRankVector[i]->begin();curr != myRankVector[i]->end();)
		{	
			map<string,RankInfo_T>::iterator temp=curr++;
			if(curr->second.value < lowLimit[i])
			{
				myRankVector[i]->erase(temp);
			}
			else
			{
				rank_queue.push(temp->second);
			}
		}
	
		memset(tempRankInfo,'\0',MAX_RANK_VALUE*180);
		int len=0;
		int row = 0;
		
		for (int j=0;j<4;j++)
		{
			memset(rankInfoMsg[i*4+j],0,sizeof(rankInfoMsg[i*4+j]));
			snprintf(rankInfoMsg[i*4+j],sizeof(rankInfoMsg[i*4+j]),"%d,%d,%d",11,11,i);
		}	
		
		int saveIndex=0;
		while (!rank_queue.empty())
		{						
			
			RankInfo_T tempInfo = rank_queue.top();
			
			if(tempInfo.grade <=0 || strlen(tempInfo.HeroName)==0)//出错处理；
			{
				rank_queue.pop();
				cout<<"hero grade error or heroName error in rankInfo.cpp 285    grade:"<<tempInfo.grade<<"        HeroName:"<<tempInfo.HeroName<<endl;
				continue;
			}
			if(row >= RankCountLimit[i])
			{
				cout<<"row >= RankCountLimit[i] in rankInfo.cpp 290"<<endl;	
				break;
			}

			if(len < MAX_RANK_VALUE*180) //TODO 这里可以更新最新等级；看有没有必要。xhm added;
			
			saveIndex=i*4+row/10;
			
			if (saveIndex<0||saveIndex>=32)
			{
				cout<<"saveIndex error in rankInfo.cpp 276"<<endl;
				break;
			}			
			
			if (i<6)
			{
				snprintf(rankInfoMsg[saveIndex]+strlen(rankInfoMsg[saveIndex]),sizeof(rankInfoMsg[saveIndex])-strlen(rankInfoMsg[saveIndex]),",%d,%s,%s,%d,%s,%d,%d,%lu",row,tempInfo.HeroId,tempInfo.HeroName,tempInfo.grade,tempInfo.party,tempInfo.camp,tempInfo.power,tempInfo.value);
			}
			else
			{
				if (strcmp(tempInfo.petName,"0")==0)
				{
					continue;
				}
				if (tempInfo.grade<0)
				{
					continue;
				}
				snprintf(rankInfoMsg[saveIndex]+strlen(rankInfoMsg[saveIndex]),sizeof(rankInfoMsg[saveIndex])-strlen(rankInfoMsg[saveIndex]),",%d,%s,%s,%s,%s,%d,%lu,-2",row,tempInfo.HeroId,tempInfo.HeroName,tempInfo.petId,tempInfo.petName,tempInfo.grade,tempInfo.value);
			}
			
			if(i==0)
			{
				memcpy(myMemRankInfo.powerRankKey[row],tempInfo.HeroId,strlen(tempInfo.HeroId));
				myMemRankInfo.powerRankInfo[row]=tempInfo;
			}			
			if (i==1)
			{
				memcpy(myMemRankInfo.levelRankKey[row],tempInfo.HeroId,strlen(tempInfo.HeroId));
				myMemRankInfo.levelRankInfo[row]=tempInfo;
			}	
			if(i==2)
			{
				memcpy(myMemRankInfo.wealthRankKey[row],tempInfo.HeroId,strlen(tempInfo.HeroId));
				myMemRankInfo.wealthRankInfo[row]=tempInfo;
			}
			if(i==3)
			{
				memcpy(myMemRankInfo.shamblesRankKey[row],tempInfo.HeroId,strlen(tempInfo.HeroId));
				myMemRankInfo.shamblesRankInfo[row]=tempInfo;
			}
			if(i==4)
			{
				memcpy(myMemRankInfo.prestigeRankKey[row],tempInfo.HeroId,strlen(tempInfo.HeroId));
				myMemRankInfo.prestigeRankInfo[row]=tempInfo;
			}	
			if(i==5)
			{
				memcpy(myMemRankInfo.activityRankKey[row],tempInfo.HeroId,strlen(tempInfo.HeroId));
				myMemRankInfo.activityRankInfo[row]=tempInfo;
			}
			if (i==6)
			{
				memcpy(myMemRankInfo.petRankKey[row],tempInfo.petId,strlen(tempInfo.petId));
				myMemRankInfo.petRankInfo[row]=tempInfo;
			}	
			if (i==7)
			{
				memcpy(myMemRankInfo.rideRankKey[row],tempInfo.petId,strlen(tempInfo.petId));
				myMemRankInfo.rideRankInfo[row]=tempInfo;
			}
			rank_queue.pop();
			row++;
		}
		
		RankInfoLastSize[i]=row;
		
		// cout<<"rankInfoMsg["<<saveIndex<<"]:"<<rankInfoMsg[saveIndex]<<endl;
	}
}


/**************************
函数作用 获取排名信息，信息用string类型表示；
函数参数 _index 将要获取的信息类型下标；
  返回值 char* 获取信息的具体值; 
***************************/
char* RankInfo::gainRankInfo(int _index)
{
	if(_index < 0 || _index >= 32)
	{
		cout<<"_index is error in rankInfo.cpp 356"<<endl;
		return NULL;
	}
	else
	{
		if (strlen(rankInfoMsg[_index])!=0)
		{
			// cout<<"rankInfoMsg["<<_index<<"]:"<<rankInfoMsg[_index]<<endl;
			return rankInfoMsg[_index];
		}
		else
		{
			cout<<"rankInfoMsg["<<_index<<"]:is null return nothing and msg:"<<rankInfoMsg[_index]<<endl;
			return NULL;
		}
	}
}

void RankInfo::analysis(void)
{
	strncpy(rewardHero[0],myMemRankInfo.powerRankKey[0],sizeof(rewardHero[0]));
	strncpy(rewardHero[1],myMemRankInfo.powerRankKey[1],sizeof(rewardHero[1]));
	strncpy(rewardHero[2],myMemRankInfo.powerRankKey[2],sizeof(rewardHero[2]));
	strncpy(rewardHero[3],myMemRankInfo.petRankInfo[0].HeroId,sizeof(rewardHero[3]));
	strncpy(rewardHero[4],myMemRankInfo.petRankInfo[1].HeroId,sizeof(rewardHero[4]));
	strncpy(rewardHero[5],myMemRankInfo.petRankInfo[2].HeroId,sizeof(rewardHero[5]));
	strncpy(rewardHero[6],myMemRankInfo.rideRankInfo[0].HeroId,sizeof(rewardHero[6]));
	strncpy(rewardHero[7],myMemRankInfo.rideRankInfo[1].HeroId,sizeof(rewardHero[7]));
	strncpy(rewardHero[8],myMemRankInfo.rideRankInfo[2].HeroId,sizeof(rewardHero[8]));
	for (int i=0;i<9;i++)
	{
		if (strlen(rewardHero[i])>35)
		{
			//创建邮件
			char content[2048]={0};
			if (i<3)
			{
				snprintf(content,sizeof(content),heroRankContent,(i%3+1));
			}
			else if (i<6)
			{
				snprintf(content,sizeof(content),petRankContent,(i%3+1));
			}
			else
			{
				snprintf(content,sizeof(content),rideRankContent,(i%3+1));
			}
			Mail_Txt mail(sendName, sendTitle, content);//构建收件箱中的邮件数据
			mail.isRead = 1;//收件箱内未读	
		
			Hero *hero=heroid_to_hero(rewardHero[i]);
			int value_ret=-1;
			if (hero!=NULL)
			{
				value_ret = MailSystermInterface::add_mail_data(hero, 0, (int)sizeof(mail), &mail);
				if(value_ret == -1)	
				{	
					cout<<"[XHM MSG] MailSystermInterface::add_mail_data ERROR<recharge_reward.cpp>:"<<rewardHero[i]<<endl;
					continue;
				}
			}
			else 
			{
				value_ret = MailSystermInterface::create_mail_data(rewardHero[i], 0, (int)sizeof(mail), (char*)&mail);//将邮件数据写入收件人的收件箱中
				if(value_ret == -1)
				{
					cout<<"MailSystermInterface::create_mail_data ERROR<rankInfo.cpp>:"<<rewardHero[i]<<endl;
					continue;
				}
			}
		}
	}
}

void RankInfo::saveRankLog(void)
{
	char accountMsg[5120]={0};
	for (int i=0;i<8;i++)
	{
		if (i<6)
		{
			for (int j=0;j<4;j++)
			{
				memset(accountMsg,0,sizeof(accountMsg));
				snprintf(accountMsg,sizeof(accountMsg),"30,0,%s,%d,%s",server_name,(int)myTime.tv_sec,rankInfoMsg[i*4+j]);
				cout<<"accountMsg["<<i*4+j<<"]:"<<accountMsg<<endl;
				write_log(accountMsg);	
			}
		}
		else
		{
			for (int j=0;j<4;j++)
			{
				memset(accountMsg,0,sizeof(accountMsg));
				snprintf(accountMsg,sizeof(accountMsg),"30,1,%s,%d,%s",server_name,(int)myTime.tv_sec,rankInfoMsg[i*4+j]);
				cout<<"accountMsg["<<i*4+j<<"]:"<<accountMsg<<endl;
				write_log(accountMsg);	
			}			
		}
	}
}


/**************************
函数作用 更新临时数据保存map；
  返回值 bool 获取信息成功; 
	调用 角色下线时调用；
***************************/
bool RankInfo::updateTempData(Hero* hero)
{
	if(NULL == hero)
		return false;
	
	
	/*对rankInfo的属性进行赋值*/
	long temp=0;
	unsigned long activity[6]={0};
	unsigned long fightPower[17]={0};
	hero->getPowerInfo(fightPower);	//获取战斗力
	power=0;
	power += LIFE_VALUE_MODULUS*(fightPower[0]);
	power += MAGIC_VALUE_MODULUS*(fightPower[1]);
	power += OUTER_ATTACK_MODULUS*(fightPower[2]);
	power += INTER_ATTACK_MODULUS*(fightPower[3]);
	power += OUTER_DEF_MODULUS*(fightPower[4]);
	power += INTER_DEF_MODULUS*(fightPower[5]);
	power += HIT_MODULUS*(fightPower[6]);
	power += CRIT_MODULUS*(fightPower[7]);
	power += DUCK_MODULUS*(fightPower[8]);
	power += TOUGH_MODULUS*(fightPower[9]);		
	
	memcpy(heroId,hero->getIdentity(),HERO_ID_LEN);//当前英雄id;
	heroId[HERO_ID_LEN]='\0';
	if(strlen(heroId) == 0)
	{
		cout<<"[XHM WARNING] heroId length equal zero(rankInfo.cpp),Data ERROR!"<<endl;
		return false;
	}
		
	grade=hero->getLevel();
	if(grade<=0 || grade >= 200)
	{
		cout<<"[XHM WARNING] hero grade less than or equal zero(rankInfo.cpp),Data ERROR!"<<endl;
		return false;
	}
	
	camp=hero->getCamp();
	if(camp < -1 || camp > 2)
	{
		cout<<"[XHM WARNING] hero campData ERROR(rankInfo.cpp)!"<<endl;
		return false;
	}
	
	memcpy(party,hero->getParty(),strlen(hero->getParty()));
	party[strlen(hero->getParty())]='\0';
	if(party[0] != 'M' && party[0] != 'G' && party[0] != 'X' && party[0] != 'H' && strlen(party) != 1)
	{
		cout<<"party[0]:"<<party[0]<<"strlen(party):"<<strlen(party)<<endl;
		cout<<"[XHM WARNING] hero party length not equal 1,Data ERROR(rankInfo.cpp)!"<<endl;	
		return false;
	}
	
	memcpy(heroName,hero->getNickName(),HERO_MAME_LEN-1);			//当前英雄昵称；
	heroName[HERO_MAME_LEN-1]='\0';
	if(strlen(heroName)==0)
	{
		cout<<"[XHM WARNING] hero heroName equal 0,Data ERROR(rankInfo.cpp)!"<<endl;		
		return false;
    }
		
	if(!hero->getMoney()){
		return false;
	}
	temp=hero->getMoney()->money_getBoundGameMoney();
	if(temp < 0)
	{
		//重新赋值，值错误；
		cout<<"[XHM WARNING] hero->getMoney()->getBoundGameMoney() value is less than 0(rankInfo.cpp)!"<<endl;			
		temp=0;
	}
	unsigned long money=temp;
	
	temp = hero->getMoney()->money_getGameMoney();	
	if(temp < 0)
	{
		cout<<"[XHM WARNING] hero->getMoney()->getGameMoney() value is less than 0(rankInfo.cpp)!"<<endl;				
		//重新赋值，值错误；
		temp=0;
	}	
	money+=temp;
	
	hero->getActivityCounts(activity);
	
	unsigned long meridTotalLevel=getTotalLevel(hero);//经脉总等级系数	
	unsigned long shambles=hero->getCrimeValue();	
	unsigned long killReadName=hero->getReadNameKills();	
	unsigned long prestige=hero->getPrestigeValue();
	
	map<string,RankInfo_T>::iterator iter;	
	
	/**
	*	战力值
	*/
	iter = (myRankVector[0])->find(heroId);	
	if(iter != (myRankVector[0])->end())
	{
		 (myRankVector[0])->erase(iter);
		updateRankInfo(0,power);
		if(RankInfoLastSize[0])
			RankInfoLastSize[0]--;
	}else if(power >= lowLimit[0])
	{
		if(power == lowLimit[0] && myRankVector[0]->size() >= RankCountLimit[0]) 
			;
		else
			updateRankInfo(0,power);
	}	
	cout<<"[XHM MSG] power size<rankInfo.cpp>:"<<power<<endl;	
	
	/**
	* 等级
	*/	
	int _level=hero->memHero->level;
	int _expNow=hero->memHero->expNow;
	int _expMax=hero->memHero->expForGrow;
	if (_expMax!=0)
	{
		int _judgeLeve=_level*100+(_expNow*100/_expMax);
		iter=(myRankVector[1])->find(heroId);
		if(iter != (myRankVector[1])->end())
		{
			(myRankVector[1])->erase(iter);
			updateRankInfo(1,_judgeLeve);	
			if(RankInfoLastSize[1])
				RankInfoLastSize[1]--;
		}else if(_judgeLeve >= lowLimit[1])
		{
			if(_judgeLeve == lowLimit[1] && myRankVector[1]->size() >= RankCountLimit[1]) 
				;
			else
				updateRankInfo(1,_judgeLeve);
		}	
	}	
	
	/**
	*	银两值
	*/
	iter = (myRankVector[2])->find(heroId);
	if(iter != (myRankVector[2])->end())
	{
		(myRankVector[2])->erase(iter);
		updateRankInfo(2,money);
		if(RankInfoLastSize[2])	//added by xhm，refresh the all infomation!
			RankInfoLastSize[2]--;
	}else if(money >= lowLimit[2])
	{
		if(money == lowLimit[2] && myRankVector[2]->size() >= RankCountLimit[2]) 
			;
		else
			updateRankInfo(2,money);
	}
	// cout<<"[XHM TEST] the money:"<<money<<endl;
	
	/**
	*	违规杀人数
	*/
	unsigned long _shambles=MAX_SHAMBLES_RANK_VALUE*shambles;
	iter = (myRankVector[3])->find(heroId);	
	if(iter != (myRankVector[3])->end())
	{
		(myRankVector[3])->erase(iter);
		updateRankInfo(3,_shambles);
		if(RankInfoLastSize[3])
			RankInfoLastSize[3]--;
	}else if(_shambles >= lowLimit[3])
	{
		if(_shambles == lowLimit[3] && myRankVector[3]->size() >= RankCountLimit[3]) 
			;
		else		
			updateRankInfo(3,_shambles);
	}	
	// cout<<"[XHM TEST] the _shambles:"<<_shambles<<endl;
	
	/**
	*	总声望
	*/
	unsigned long _prestige=PRESTIGE_MODULUS*(prestige);
	iter = (myRankVector[4])->find(heroId);	
	if(iter != (myRankVector[4])->end())
	{
		(myRankVector[4])->erase(iter);
		 updateRankInfo(4,_prestige);	
		if(RankInfoLastSize[4])
			RankInfoLastSize[4]--;
	}else if(_prestige >= lowLimit[4])
	{
		if(_prestige == lowLimit[4] && myRankVector[4]->size() >= RankCountLimit[4]) 
			;
		else
			updateRankInfo(4,_prestige);
	}	
	// cout<<"the 	myRankVector[4]->size:"<<myRankVector[4]->size()<<endl;
	// cout<<"[XHM TEST] the _prestige:"<<_prestige<<endl;	
	
	/**
	*	活动值
	*/
	unsigned long _activity=0;
	_activity+=COUNT_FACTIONWAR_MODULUS*(activity[0]);			// 参与帮战次数
	_activity+=COUNT_ORDCAMPWAR_MODULUS*(activity[1]);			// 参与阵营战1次数
	_activity+=COUNT_LEADERCAMPWAR_MODULUS*(activity[2]);		// 参与阵营战2次数
	_activity+=COUNT_CHIEFCAMPWAR_MODULUS*(activity[3]);		// 参与阵营战3次数
	_activity+=COUNT_ENTER_DUPLICATION_MODULUS*(activity[4]);	// 下副本次数
	_activity+=COUNT_ATTRACK_BOSS_MODULUS*(activity[5]);		// 击打活动boss次数
	
	iter = (myRankVector[5])->find(heroId);	
	if(iter != (myRankVector[5])->end())
	{
		(myRankVector[5])->erase(iter);
		updateRankInfo(5,_activity);
		if(RankInfoLastSize[5])
			RankInfoLastSize[5]--;
	}else if(_activity >= lowLimit[5])
	{
		if(_activity == lowLimit[5] && myRankVector[5]->size() >= RankCountLimit[5]) 
			;
		else
			updateRankInfo(5,_activity);
	}
	// cout<<"[XHM TEST] the _activity:"<<_activity<<endl;

	/**
	* 宠物
	*/	
	Pet_Box *pet_box=hero->getPetBox();
	if (pet_box==NULL)
	{
		cout<<"jolly:when hero downline judge rankInfo ,but can't find the *pet_box int rankInfo.cpp 556"<<endl;
		return false;
	}
	
	int petBoxNumber=pet_box->getNumber();
	unsigned int petPower=0;
	for (int i=0;i<petBoxNumber;i++)
	{
		Pet *pet=pet_box->getPet(i);
		if (pet!=NULL)
		{
			petPower=pet->countPower();		
			memset(petId,0,sizeof(petId));
			strncpy(petId,pet->getIdentity(),sizeof(petId));
			memset(petName,0,sizeof(petName));
			strncpy(petName,pet->getNickName(),sizeof(petName));
			grade=pet->getLevel();
			iter=(myRankVector[6])->find(petId);
			if(iter != (myRankVector[6])->end())
			{
				(myRankVector[6])->erase(iter);
				updateRankInfo(6,petPower);	
				if(RankInfoLastSize[6])
					RankInfoLastSize[6]--;
			}
			else if(petPower >= lowLimit[6])
			{
				if(petPower == lowLimit[6] && myRankVector[6]->size() >= RankCountLimit[6]) 
				{
					
				}
				else
				{
					updateRankInfo(6,petPower);
				}
			}	
		}
	}
	
	/**
	*	坐骑
	*/
	
	Ride *ride=hero->getRide();
	if (ride==NULL)
	{
		cout<<"jolly:wher hero downline judge rankIfo ,but can't find the *ride in rankInfo 576"<<endl;
		return false;
	}
	
	if (ride->ifFull())
	{		
		unsigned int ridePower=ride->countPower();
		memset(petId,0,sizeof(petId));
		strncpy(petId,ride->getIdentity(),sizeof(petId));
		memset(petName,0,sizeof(petName));
		strncpy(petName,ride->getNickName(),sizeof(petName));
		grade=ride->getLevel();
		iter=(myRankVector[7])->find(petId);
		if(iter != (myRankVector[7])->end())
		{
			(myRankVector[7])->erase(iter);
			updateRankInfo(7,ridePower);	
			if(RankInfoLastSize[7])
				RankInfoLastSize[7]--;
		}
		else if(ridePower >= lowLimit[7])
		{
			if(ridePower == lowLimit[7] && myRankVector[7]->size() >= RankCountLimit[7]) 
			{
				
			}	
			else
			{
				updateRankInfo(7,ridePower);			
			}
		}
	}	
	
	return true;
}


