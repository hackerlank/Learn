#include "libev.h"		
#include "hero.h"
#include "map_src.h"
#include "timerContainer.h"
#include "ordinaryCampWar.h"
#include "camp_war_reward.h"
#include "money_operator.h"

static char msg_ordinary_campWar[200];
extern MapType_T mapTypeInfo;//某些特殊地图的ID；
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Map_Src*> mapId_connect_map;
extern CampRewardData_T camp_reward_info[CAMP_WAR_REWARD_SIZE];//奖励	

/**
	构造函数
*/
OrdinaryCampWar::OrdinaryCampWar()
{
	sumSize=0;

	activeSize[0]=0;
	activeSize[1]=0;
	activeSize[2]=0;
	
	campVector.clear();
	campVector.push_back(&religion);	
	campVector.push_back(&tribes);
	campVector.push_back(&ranger);
}


/**
	析构函数
*/
OrdinaryCampWar::~OrdinaryCampWar()
{
/*
	if(NULL != timer)
	{
		ev_timer_stop(loops,timer);
		delete timer;
		timer=NULL;
	}
*/
}


/**
argument：Hero* myHero 英雄实例指针；
return:   int   -1: myHero==NULL,对象指针为空;
				-2:	英雄实例的阵营不属于系统三个阵营之内；
				 0：在阵营tribes（支教/正派）里面。
				 1：在阵营religion（宗教/邪派）里面。
				 2：在阵营ranger（游侠）里面。
function:  查找阵营下标；这函数是由于开始阵营保存的是个字符串，此函数有用，现在改成int,意义不大；
*/
int 
OrdinaryCampWar::findCampIndex(Hero* myhero)
{
		if(NULL == myhero)
			return -1;
			
		if(myhero->getCamp()==0)
			return 0;
		else if(myhero->getCamp()==1)
			return 1;
		else if(myhero->getCamp()==2)
			return 2;	
		else
			return -2;
}


/**
argument：void；
return:   bool; ture 成功，失败；
function: 数据初始化；
*/
bool 
OrdinaryCampWar::initCampWar()
{
	sumSize=0;
	activeSize[0]=0;
	activeSize[1]=0;
	activeSize[2]=0;
	
	tribes.clear();//支派/正派信息；
	map<string,KillsInfo>().swap(tribes);
	
	religion.clear();//宗教/邪派信息；
	map<string,KillsInfo>().swap(religion);
	
	ranger.clear();//游侠信息；
	map<string,KillsInfo>().swap(ranger);
	
	WinnerHero.clear();//胜利者清零；
	map<string,KillsInfo>().swap(WinnerHero);
	
	return true;
}
	

/**
argument：void；
return:   int  阵营战总人数；
function: 获取阵营战总人数；
*/	
int 
OrdinaryCampWar::getWarHeroSize()			//获取阵营战的所有人数；
{
	return activeSize[0]+activeSize[1]+activeSize[2];
}


/**
argument：Hero* myHero 英雄实例指针；
return:   int   -1: myHero==NULL,对象指针为空;
				-2: 表示阵营战已饱和，达到最大允许人数；
				-3：表示插入insert失败；
				-4:	英雄实例的阵营不属于系统三个阵营之内；
				 0：表示添加成功。
function:  插入阵营参加角色；
*/
int 
OrdinaryCampWar::addHero2war(Hero *myHero,int kills)			//添加英雄ID到阵营战；
{
	if(NULL==myHero)
		return -1;
	
	if(kills<0)
		kills=0;
		
	pair< map< string,KillsInfo >::iterator,bool > ret;
    int index= findCampIndex(myHero);
	
	if(0 <= index && index < 3)
	{
		if(activeSize[index] >= MAX_CAMP_WAR_COUNTS)
			return -2;
		KillsInfo tempKillInfo(kills,getMySecond());			//初始化当前杀人数和本地时间；
		ret =campVector[index]->insert(HeroId_Val(myHero->getIdentity(),tempKillInfo));
		if( ret.second ){
			activeSize[index]++;
			return 0;  
        }else{
			if(!myHero->isInCampWar())
				return -3;
		
			return 0;			
	   }
	}
	return -4;	
}


/**
argument：Hero* myHero 英雄实例指针；
return:   int   -1: myHero==NULL,对象指针为空;
				-4:	英雄实例的阵营不属于系统三个阵营之内；
				-9: 在此次阵营战中，在其阵营队列中找不到；				 
				 0：表示删除成功。
function:  从阵营战中删除角色信息；
*/
int 
OrdinaryCampWar::delHeroFromWar(Hero *myHero)	//从杀敌战中删除；
{
	if(myHero==NULL)
		return -1;
		
	int index=findCampIndex(myHero);
	
	if(index >=0 && index <3 )
	{
		map<string, KillsInfo>::iterator iter = campVector[index]->find(myHero->getIdentity());
		if(iter == campVector[index]->end())
			return 0;
			
		campVector[index]->erase(iter);
		return 0;
	}
	
	return -4;
}


/**
argument：Hero* myHero 英雄实例指针；
  return: int   -1,表示实例指针为空；
				-2,表示这个英雄ID阵营信息没有在系统中找到；
		        -3,表示该英雄没有在这阵营战对应的阵营队伍中；
		        >=0,表示杀敌数；
function: 角色获取杀敌数；
*/
int  
OrdinaryCampWar::getKills(Hero* myHero)		//获取杀敌数；
{ 
	if(NULL == myHero)
		return -1;
		
	int index = findCampIndex(myHero);
	if(index >= 0 && index < 3)
	{
		map<string,KillsInfo>::iterator iter = campVector[index]->find(myHero->getIdentity());
		if(iter != campVector[index]->end())
		{
			return iter->second.kills;
		}
		return -3;
	}
	
	return -2;
}


/**
	设置这次普通阵营战的ID；
*/
void 
OrdinaryCampWar::setIdentity(string _ordinaryId)
{
	ordinaryId=_ordinaryId;
}


/**
	获取这次普通阵营战的ID；
*/
string 
OrdinaryCampWar::getIdentity()
{
	return ordinaryId;
}


/**
	排序比较函数；
*/
static int 
cmp(const ORD_CAMP_WAR_DATA_PAIR& x, const ORD_CAMP_WAR_DATA_PAIR& y)  
{  
	if(x.second.kills > y.second.kills)
		return 1;
	else if(x.second.kills == y.second.kills && x.second.lastKillTime < y.second.lastKillTime)
		return 1;
	return 0;	
}


/**
argument； void;
  return:  map<string,KillsInfo>&  返回此房间的前9名，如果没有9名，有多少，返回多少；
function:  战斗结束处理，算出优胜者；  
*/	
const map<string,KillsInfo>& 
OrdinaryCampWar::finishCampWar()    	//阵营战争结束处理；
{
  string CampWarInfo="11,8,1";
  vector<ORD_CAMP_WAR_DATA_PAIR> vec;  
  map<string, Hero*>::iterator iter;
  
  for(int i=0;i<campVector.size();i++)
  {
	map<string,KillsInfo>::iterator curr;
	for(curr = (campVector[i])->begin();curr != (campVector[i])->end(); ++curr)
	{
		//给每个人发送信息，表明普通阵营战结束；
		iter = heroId_to_pHero.find(curr->first);
		if(iter!=heroId_to_pHero.end())//该英雄id不存在；
		{
			if(iter->second->isInCampWar())//如果在阵营战中，发送消息；
			{
				iter->second->setCampWarStartMark(false);	
				send_msg(iter->second->getFd(),const_cast<char*>(CampWarInfo.c_str()));
			}
			else//如果不存在，存邮件；待完善；
				;	
		}
					
		vec.push_back(make_pair(curr->first, curr->second));  
	}
  }
  
  sort(vec.begin(), vec.end(), cmp);
  
  /*测试数据*/
  // for(int index=0;index < vec.size(); index++)
	// cout<<"in the ordinaryCampWar.cpp the name:"<<vec[index].first<<"the kills:"<<vec[index].second.kills<<"Time: "<<vec[index].second.lastKillTime<<endl;
  
  /*返回给管理器，本房间的前9位杀敌人数最多英雄*/
  WinnerHero.clear();
  map<string,KillsInfo>().swap(WinnerHero);
  
  int size= vec.size()>ORDINARY_CAMP_WAR_AWARDS_LOWEST_RANGE?ORDINARY_CAMP_WAR_AWARDS_LOWEST_RANGE:vec.size();
  for(int i=0;i<size;i++)
  {
	WinnerHero.insert(HeroId_Val(vec[i].first,vec[i].second));
  }
	
	/*活动人人数清空*/
	activeSize[0]=0;
	activeSize[1]=0;
	activeSize[2]=0;
	
   return WinnerHero;
}


/**
argument：Hero* myHero 英雄实例指针,此实例指向杀敌数加1；
return:   int  -1,myHero为空；
		       -2,表示该英雄没有在这阵营战对应的阵营队伍中；
			   -3,表示这个英雄ID阵营信息没有在系统中找到;
		       >0,表示杀敌数；
*/
int 
OrdinaryCampWar::addKills(Hero* myHero)
{
	// cout<<"in the ordinaryCampWar.cpp ----> in the addKills"<<endl;
	if(NULL == myHero)
		return -1;
		
	int index = findCampIndex(myHero);
	if(index<0 || index > 2)
		return -3;
		
	map<string,KillsInfo>::iterator iter = campVector[index]->find(myHero->getIdentity());
	if(iter ==campVector[index]->end())
		return -2;
		
	iter->second.kills++;
	
	(iter->second).lastKillTime=getMySecond();
	
	return iter->second.kills;
}


/**
argument：Hero* myHero 英雄实例指针；
return:   int  -1,英雄实例指针为空；
			   -2,阵营类型不是默认类型；
		       -3,表示该英雄没有在这阵营战对应的阵营队伍中；
		        0,表示减少成功；
*/
int 
OrdinaryCampWar::reduceActiveHero(Hero* myHero)
{
	if(NULL == myHero)
		return -1;
		
	int index = findCampIndex(myHero);
	if(index<0 || index > 2)
		return -2;
		
	map<string,KillsInfo>::iterator iter = campVector[index]->find(myHero->getIdentity());
	if(iter ==campVector[index]->end())
		return -3;
		
	if(activeSize[index])	
		activeSize[index]--;
		
	return 0;
}


/**
argument myHero 实例英雄指针，_rank 排名(默认为AWARDS_LEADT_RANGE)；
  return string 奖励的字符串；//类型，绑定游戏币数目，声望大小;
*/
char*
OrdinaryCampWar::viewAwards(Hero* myHero,int _rank)//查看奖励；
{						
	int myRank=_rank;
	if(_rank<0||_rank>2)
		myRank=-1;
		
	if(NULL == myHero)
	{
		sprintf(msg_ordinary_campWar,"11,4,1,-1,0,0,%d,%d,-1",camp_reward_info[ORD_REWARD].rank_limit_value-1,_rank+1);
		return msg_ordinary_campWar;
	}
	
	int index = findCampIndex(myHero);//查找阵营类型；
	
	if(index<0 || index > 2)
	{
		sprintf(msg_ordinary_campWar,"11,4,1,-2,0,0,%d,%d,-1",(camp_reward_info[ORD_REWARD].rank_limit_value-1)*5,_rank+1);
		return msg_ordinary_campWar;
	}
	

	if(myHero->getIdentity())
	{
		map<string,KillsInfo>::iterator iter = campVector[index]->find(myHero->getIdentity());
		if(iter ==campVector[index]->end())
		{
			sprintf(msg_ordinary_campWar,"11,4,1,-3,0,0,%d,%d,-1",camp_reward_info[ORD_REWARD].rank_limit_value-1,_rank+1);
			return msg_ordinary_campWar;
		}
		
		if(_rank < 0 || _rank >= camp_reward_info[ORD_REWARD].rank_limit_value)	
			_rank=camp_reward_info[ORD_REWARD].rank_limit_value-1;
			
		sprintf(msg_ordinary_campWar,"11,4,1,0,%d,%d,%d,%d,%d",
				camp_reward_info[ORD_REWARD].gold_base_value-_rank*camp_reward_info[ORD_REWARD].gold_dec_value,\
				camp_reward_info[ORD_REWARD].prestige_base_value-_rank*camp_reward_info[ORD_REWARD].prestige_dec_value,\
				(camp_reward_info[ORD_REWARD].rank_limit_value-1)*5,myRank+1,_rank+1);
	}
	
	return msg_ordinary_campWar;
}


/**
argument myHero 实例英雄指针，_rank 排名(默认为AWARDS_LEADT_RANGE)；
  return int -1 实例英雄指针为空
			 -2 不属于系统默认阵营类型；
			 -3  在此房间没有找到英雄战斗痕迹；
			 -4  给背包装东西失败；
			  0  表示成功；
*/
int 
OrdinaryCampWar::receiveAwards(Hero* myHero,int _rank)		//领取奖励；
{
	if(NULL == myHero)
		return -1;
		
	int index = findCampIndex(myHero);
	if(index<0 || index > 2)
		return -2;
		
	map<string,KillsInfo>::iterator iter = campVector[index]->find(myHero->getIdentity());
	if(iter ==campVector[index]->end())
		return -3;

	//给物品奖励；策划需求更改；
	// if(!saveGoodsInBag(myHero,goods,1))
		// return -4;
		
	if(_rank >= ORDINARY_CAMP_WAR_AWARDS_LOWEST_RANGE || _rank < 0)
		_rank=ORDINARY_CAMP_WAR_AWARDS_LOWEST_RANGE-1;
		
	//给绑定金币的奖励；
	if(myHero->getMoney() == NULL)
		return -3;
		
	increaseBoundGameMoney(myHero,camp_reward_info[ORD_REWARD].gold_base_value-_rank*camp_reward_info[ORD_REWARD].gold_dec_value);
	
	/*设置声望；*/
	myHero->addPrestigeValue(camp_reward_info[ORD_REWARD].prestige_base_value-_rank*camp_reward_info[ORD_REWARD].prestige_dec_value);
	
	/*设置头衔*/
	if(_rank == 0)
	{
		myHero->addTitle(FIRST_TITLE);
	}else if(_rank == 1)
	{
		myHero->addTitle(SECOND_TITLE);	
	}else if(_rank == 2)
	{
		myHero->addTitle(THIRD_TITLE);	
	}
	
	campVector[index]->erase(iter);
	return 0;
}



/**
argument void
  return bool 如果成功，返回true,失败false;
*/
bool 
OrdinaryCampWar::sengMsgStartCampWar()
{
	string msg="11,10,1";
	for(int index=0;index<3;index++)
	{
		for(map<string,KillsInfo>::iterator iterCampWar = campVector[index]->begin();iterCampWar != campVector[index]->end();iterCampWar++)
		{
			map<string,Hero*>::iterator iter=heroId_to_pHero.find(iterCampWar->first);
			if(iter!=heroId_to_pHero.end())
			{
				if(iter->second->getLoadState() == true)
					send_msg(iter->second->getFd(),const_cast<char*>(msg.c_str()));
			}	
		}
	}		
	return true;
}


/**
argument void
  return bool 是否成功;
function 更新普通阵营战房间任务信息；
*/
bool 
OrdinaryCampWar::update_ord_camp_info(void)
{
	sprintf(msg_ordinary_campWar,"11,29,%d,%d,%d",activeSize[0],activeSize[1],activeSize[2]);

	for(int index=0;index<3;index++)
	{
		for(map<string,KillsInfo>::iterator iterCampWar = campVector[index]->begin();iterCampWar != campVector[index]->end();iterCampWar++)
		{
			map<string,Hero*>::iterator iter=heroId_to_pHero.find(iterCampWar->first);
			if(iter!=heroId_to_pHero.end())
			{
				if(iter->second->getLoadState() == true && strstr(iter->second->getMapId(),(mapTypeInfo.campWarMapId).c_str()))
					send_msg(iter->second->getFd(),msg_ordinary_campWar);
			}	
		}
	}		
	return true;
}

/**
argument Hero* my_hero角色实例指针；
  return bool 是否成功;
function 更新角色信息；
*/
bool  
OrdinaryCampWar::update_hero_info(Hero* my_hero,int time)
{
	// snprintf(msg_ordinary_campWar,"11,29,%d,%d,%d",activeSize[0],activeSize[1],activeSize[2]);
}