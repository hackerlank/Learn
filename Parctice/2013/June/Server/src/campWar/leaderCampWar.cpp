#include "libev.h"
#include "guild_asist.h"
#include "leaderCampWar.h"
#include "camp_war_reward.h"
#include "campWarManagement.h"
#include "money_operator.h"
#include "command_other_function_all_over.h"

static char leader_camp_msg[300];	
static ev_timer *leader_campWar_timer;
static char msg2Leader[]={'1','1',',','2','3',',','0'};

extern struct ev_loop *loops;
extern MapType_T mapTypeInfo;//某些特殊地图的ID；
extern campWarManagement campWarController;//阵营战管理实例；							
extern CampRewardData_T camp_reward_info[CAMP_WAR_REWARD_SIZE];//奖励配置	

static 	char apply_info[10240];
/**
*统领战结束回调函数
*/
void
LeaderCampWarFinishCall(struct ev_loop *loop,ev_timer *think,int revents)
{
	if(think == NULL)
		return;
    ev_timer_stop(loop,think);
	
	LeaderCampWar *leaderCampWar = (LeaderCampWar *)think->target;
	
	if(leaderCampWar == NULL)
	{
		return;
	}
	
	// cout<<"[XHM MSG] LeaderCampeWar Time is Over,We going to run finishFactionCampWar()."<<endl;
	string winner = leaderCampWar->finishFactionCampWar();
	campWarController.finishLeaderCampWar(winner,leaderCampWar->index);
}


/**
*统领战构造函数
*/
LeaderCampWar::LeaderCampWar()
{
	winnerFaction = "";
	guildLeaderAId = "";
	guildLeaderBId = "";
	index=-1;//默认管理下标为-1；
	initFactionCampWar();
}


/**
argument hero 英雄实例指针；
  return int -1：实例指针为空；
			 -2：表示实例指针对应对象的帮派名字不是当前作战的帮派名字；
			 -3：表示insert失败，已经参加过，不能参加；
			  0：表示成功；
*/
int 
LeaderCampWar::addHero2Factionwar(Hero* myHero)
{
	if(NULL == myHero)
		return -1;
		
	LeaderCampWarData tempLeaderCampWarData(0,0);//默认杀敌数和死亡次数都为零；
	pair< map< string,LeaderCampWarData>::iterator,bool > ret;//用于insert的返回值，判断insert是否成功。
	
	char* pName = myHero->getGuildName();//获取帮派的名字;
	if(NULL == pName || strlen(pName) == 0)
		return -2;
		
	string currFactionName=pName;
	if(currFactionName == factionAName)//如果当前帮派名是系统作战帮派a;
	{
		ret = factionA.insert(HEROID_Val(myHero->getIdentity(),tempLeaderCampWarData));
		if(ret.second)
		{
			factionAActiveSize++;
			return 1;	
		}else{
			if(myHero->isInCampWar())
				return -3;		
				
			factionAActiveSize++;			
			return 1;
		}

	}
	else if(currFactionName == factionBName)//如果当前帮派名是系统作战帮派b;
	{
		ret = factionB.insert(HEROID_Val(myHero->getIdentity(),tempLeaderCampWarData));

		if(ret.second)
		{
			factionBActiveSize++;
			return 2;
		}else{
			if(myHero->isInCampWar())
				return -3;	
				
			factionBActiveSize++;			
			return 2;
		}
	}else{
		return -2;
	}
}
 

/**
argument: myHero 	实例英雄指针；
  return: 	 int    -1:实例指针为空；
					-2:帮派名字不是系统正在作战的帮派；
					-3:在阵营统领战中找不到英雄ID；
					0:删除成功；
*/ 
int 
LeaderCampWar::delHeroFromFactionWar(Hero* myHero)
{
	if(myHero==NULL)
		return -1;

	char* pName = myHero->getGuildName();//获取帮派的名字;
	if(NULL == pName)
		return -2;
	string factionName=pName;//获取帮派的名字;		
	
	map<string,LeaderCampWarData>::iterator iter;
	
	if(factionName==factionAName)
	{
		iter = factionA.find(myHero->getIdentity());
		if(iter ==factionA.end())
			return -3;
		factionA.erase(iter);
	}
	else if(factionName==factionBName)
	{
		iter = factionB.find(myHero->getIdentity());
		if(iter ==factionB.end())
			return -3;
		factionB.erase(iter);
	}else
		return -2;
		
	return 0;
}


bool 
LeaderCampWar::initFactionCampWar()
{
	factionA.clear();
	map<string,LeaderCampWarData>().swap(factionA);
	
	factionB.clear();
	map<string,LeaderCampWarData>().swap(factionB);
	
	factionAActiveSize=0;
	factionBActiveSize=0;
	
	num_factionA_leader_deaths=0;//初次赋值为默认值；
	num_factionB_leader_deaths=0;
	
	LeaderCampWarEndTime=0;//统领阵营战结束时间；
	leaderCampWarLastTime=0;
	LeaderCampWarStartTime=0;//统领阵营战开始时间；	
	
	//清空；
	if(!winnerFaction.empty())
		factionAName=winnerFaction;//保存上一次的统领
	else
		factionAName="";
	 
	factionBName="";
}


bool 
LeaderCampWar::startLeaderCampWar()
{
	LeaderCampWarStartTime=0;//统领阵营战开始时间；
	LeaderCampWarEndTime=0;//统领阵营战结束时间；
	
	map<string, Hero*>::iterator iter;
	if(!factionAName.empty())
	{
		char* p_hero_id = getGuildPresidId(const_cast<char*>(factionAName.c_str()));
		if(p_hero_id)
		{
			iter=heroId_to_pHero.find(p_hero_id);	
			if(iter!=heroId_to_pHero.end())
			{
				send_msg(iter->second->getFd(),msg2Leader);
			}
		}
	}

	if(!factionBName.empty())
	{
		char* p_hero_id = getGuildPresidId(const_cast<char*>(factionBName.c_str()));
		if(p_hero_id)
		{
			iter=heroId_to_pHero.find(p_hero_id);	
			if(iter!=heroId_to_pHero.end())
			{
				send_msg(iter->second->getFd(),msg2Leader);
			}
		}
	}
	
}


static int 
cmp(const PAIR_LEADER_CAMP_WAR_DATA& x, const PAIR_LEADER_CAMP_WAR_DATA& y)  
{  
    return x.second.kills > y.second.kills;//按照杀人数排名；
}


/**
return string 	胜利方的帮派名字；
*/
string
LeaderCampWar::finishFactionCampWar()
{
	if(factionAName.empty())
		return winnerFaction;
	
	/*给所有人发一条数据，战争结束,按照杀敌数排序*/
	char CampWarInfo[50]={0};
	sprintf(CampWarInfo,"11,8,2");
	map<string, Hero*>::iterator iter;
	
	vector<PAIR_LEADER_CAMP_WAR_DATA> vecA;  
	for(map<string,LeaderCampWarData>::iterator curr = factionA.begin();curr != factionA.end(); ++curr)
	{
		iter = heroId_to_pHero.find(curr->first);
		if(iter!=heroId_to_pHero.end())//该英雄id不存在；
		{
			if(iter->second->getCampWarType() == 2)
			{
				iter->second->setCampWarStartMark(false);		
				send_msg(iter->second->getFd(),CampWarInfo);
			}else{
				// cout<<"in the leaderCampWar,some one "<<CampWarInfo<<" is exit!"<<endl;
				//打过阵营战，但是退出不在线的处理；
			}
		}
		
		vecA.push_back(make_pair(curr->first, curr->second));  
	}
	
    sort(vecA.begin(), vecA.end(), cmp);//阵营a按照杀人次数排序；
	
	factionARank.clear();
	map<string,int>().swap(factionARank);	
	
	int size= vecA.size();
	for(int i=0;i<size;i++)
	{
		factionARank.insert(HEROID_RANK_LEADER(vecA[i].first,i));
	}
  
	vector<PAIR_LEADER_CAMP_WAR_DATA> vecB;  
	for(map<string,LeaderCampWarData>::iterator curr = factionB.begin();curr != factionB.end(); ++curr)
	{
		iter = heroId_to_pHero.find(curr->first);
		if(iter!=heroId_to_pHero.end())//该英雄id存在；
		{
			if(iter->second->getCampWarType() == 2)
			{
				iter->second->setCampWarStartMark(false);		
				send_msg(iter->second->getFd(),CampWarInfo);
			}else{
				//打过阵营战，但是退出不在线的处理；
			}
		}	
		vecB.push_back(make_pair(curr->first, curr->second));  
	}
	
	// cout<<"the factionAActiveSize:"<<factionAActiveSize<<"num_factionA_leader_deaths:"<<num_factionA_leader_deaths<<endl;
	// cout<<"the factionBActiveSize:"<<factionBActiveSize<<"num_factionB_leader_deaths:"<<num_factionB_leader_deaths<<endl;	
	
	sort(vecB.begin(), vecB.end(), cmp);							//阵营b按照杀人次数排序；
	factionBRank.clear();
	map<string,int>().swap(factionBRank);		
	
	size= vecB.size();
	for(int i=0;i<size;i++)
	{
		factionBRank.insert(HEROID_RANK_LEADER(vecB[i].first,i));
	}

	
	/*判断统领阵营胜利*/
	if(factionAActiveSize == 0 && factionBActiveSize != 0)//若甲方全灭掉，乙方赢。
	{
		winnerFaction=factionBName;
	}
	else if(factionBActiveSize == 0 && factionAActiveSize != 0)
	{
		winnerFaction=factionAName;
	}
	else
	{	
		if(num_factionA_leader_deaths == MAX_DEATHS && num_factionB_leader_deaths < MAX_DEATHS)//若甲方帮主不存在，乙方赢；
			winnerFaction=factionBName;
		else if(num_factionA_leader_deaths < MAX_DEATHS && num_factionB_leader_deaths == MAX_DEATHS)
			winnerFaction=factionAName;
		else{
			if(factionBActiveSize < factionAActiveSize)//若甲方的在线存活人数大于乙方存活人数，甲方赢。
				winnerFaction=factionAName;
			else if(factionBActiveSize > factionAActiveSize)
				winnerFaction=factionBName;
			else{
				if(num_factionA_leader_deaths > num_factionB_leader_deaths)//若存活人数相等，甲方的帮主死亡次数少，甲方胜。
					winnerFaction=factionBName;
				else
					winnerFaction=factionAName;
			}
		}
	}
	
	return winnerFaction;//返回用于保存到阵营缓存数据；
}



/**
argument: hero 	实例英雄指针；
  return  int -1:实例指针为空；
  			  -2:帮派名字不是系统正在作战的帮派；
			  -3:在阵营统领战中找不到英雄ID；
			 >=0:返回死亡次数；
*/ 
int 
LeaderCampWar::addDeathCounts(Hero* myHero)
{
	if(NULL == myHero)
		return -1;

	char* pName = myHero->getGuildName();//获取帮派的名字;
	if(NULL == pName || strlen(pName)==0)
		return -2;
		
	bool sendMsgFlg=false;
	string currFactionName=pName;	
	
	map<string,LeaderCampWarData>::iterator iter;
	char* presidId=getGuildPresidId(const_cast<char*>(currFactionName.c_str()));
	
	if(currFactionName==factionAName)
	{
		iter = factionA.find(myHero->getIdentity());
		if(iter ==factionA.end())//找不到，退出！
			return -3;
			
		if(presidId!=NULL)
		{
			if(!strcmp(myHero->getIdentity(),presidId))//是帮主，帮主死亡次数加加；
			{
				num_factionA_leader_deaths++;
				sendMsgFlg=true;
			}
		}			
	}else if(currFactionName==factionBName)
	{
		iter = factionB.find(myHero->getIdentity());
		if(iter ==factionB.end())//找不到，退出！
			return -3;
			
		if(presidId!=NULL)
		{
			if(!strcmp(myHero->getIdentity(),presidId))//是帮主，帮主死亡次数加加；
			{
				num_factionB_leader_deaths++;
				sendMsgFlg=true;
			}
		}			
	}else
	{
		return -2;
	}
	
	int deathCounts = ++(iter->second.deaths);//死亡次数加加；
	if(deathCounts >= MAX_DEATHS)
	{
		reduceActiveHero(myHero);//死亡5次处理,活动人数减1；
	}else if(sendMsgFlg){
		if(myHero->isInCampWar())//死亡次数不足5次，但是是帮主死亡，更新客户端数据；
			sendMsgStart();
	}
	
	return deathCounts;
}


void 
LeaderCampWar::setWinnerFaction(string _winnerFaction)
{
	winnerFaction=_winnerFaction;
	factionAName=winnerFaction;
}

void 
LeaderCampWar::setchallengeGuild(string _GuildName)
{
	factionBName=_GuildName;
}

void 
LeaderCampWar::setGuildLeaderAId(string _GuildLeaderAId)//用于保存重新上线，统领不用报名；
{
	guildLeaderAId=_GuildLeaderAId;
}


string 
LeaderCampWar::setFactionName(string _factionAName,string _factionBName)
{
	factionAName=_factionAName;
	factionBName=_factionBName;
}

/**
argument: hero 	实例英雄指针；
  return  int -1:实例指针为空；
  			  -2:帮派名字不是系统正在作战的帮派；
			  -3:在阵营统领战中找不到英雄ID；
			 >=0:返回杀人数；
*/ 
int 
LeaderCampWar::addKills(Hero* myHero)
{
	if(NULL == myHero)
		return -1;
		
	char* pName = myHero->getGuildName();//获取帮派的名字;
	if(NULL == pName)
		return -2;
	string currFactionName=pName;
	
	map<string,LeaderCampWarData>::iterator iter;
	
	if(currFactionName==factionAName)
	{
		iter = factionA.find(myHero->getIdentity());
		if(iter ==factionA.end())
			return -3;
	}else if(currFactionName==factionBName)
	{
		iter = factionB.find(myHero->getIdentity());
		if(iter ==factionB.end())
			return -3;
	}else
	{
		return -2;
	}
	
	return ++(iter->second.kills);
}


/**
argument: hero 	实例英雄指针；
  return  int -1:实例指针为空；
  			  -2:帮派名字不是系统正在作战的帮派；
			  -3:在阵营统领战中找不到英雄ID；
			 >=0:返回英雄对应的阵营活动人数；
*/ 
int 
LeaderCampWar::reduceActiveHero(Hero* myHero)
{
	if(NULL == myHero)
		return -1;
		
	char* pName = myHero->getGuildName();//获取帮派的名字;
	if(NULL == pName)
		return -2;	
	string currFactionName=	pName;
	
	if(currFactionName.empty())
		return -1;
		
	char CampWarInfo[50]={0};
	sprintf(CampWarInfo,"11,8,2");
		
	map<string,LeaderCampWarData>::iterator iter;

	if(currFactionName==factionAName)
	{
		iter = factionA.find(myHero->getIdentity());
		if(iter ==factionA.end())
			return -3;
			
		if(factionAActiveSize)
			factionAActiveSize--;
		
		if(myHero->isInCampWar())
		{
			sendMsgStart();//如果正式开启，更新客户端数据；
			if(0 == factionAActiveSize && myHero->isInCampWar())
			{
				map<string, Hero*>::iterator iterHero;
				for(iter=factionB.begin();iter!=factionB.end();iter++)
				{
					iterHero = heroId_to_pHero.find(iter->first);
					if(iterHero!=heroId_to_pHero.end())	//该英雄id不存在；
					{
						send_msg(iterHero->second->getFd(),CampWarInfo);//战争结束,给所有的人发一条信息；
					}
			
				}
				//增加定时器终止；	
				ev_timer_stop(loops,leader_campWar_timer);//战争结束；
				string winner = finishFactionCampWar();
				campWarController.finishLeaderCampWar(winner,index);//设置阵营数据;
			}
		}
		
		return factionAActiveSize;
	}else if(currFactionName==factionBName)
	{
		iter = factionB.find(myHero->getIdentity());
		if(iter ==factionB.end())
			return -3;
		
		if(factionBActiveSize)	
			factionBActiveSize--;
		if(myHero->isInCampWar())	
		{	
			sendMsgStart();	//如果正式开启，更新客户端数据；
			if( 0 == factionBActiveSize)
			{
				map<string, Hero*>::iterator iterHero;
				for(iter=factionA.begin();iter!=factionA.end();iter++)
				{
					iterHero = heroId_to_pHero.find(iter->first);
					if(iterHero!=heroId_to_pHero.end())		//该英雄id不存在；
					{
						send_msg(iterHero->second->getFd(),CampWarInfo);		
					}
			
				}
				//增加定时器终止	
				ev_timer_stop(loops,leader_campWar_timer);									//战争结束；
				string winner = finishFactionCampWar();
				campWarController.finishLeaderCampWar(winner,index);
			}
		}
		return factionBActiveSize;
	}else{
		return -2;
	}
	
}

/**获取奖励的字符串*/
char* 
LeaderCampWar::viewAwards(Hero* myHero)
{
	int rank=0;
	if(NULL == myHero)
	{
		sprintf(leader_camp_msg,"11,4,2,-1,0,0,0,0,1,0,-1");
		return leader_camp_msg;
	}
	char* myHeroId = myHero->getIdentity();
	
	map<string,LeaderCampWarData>::iterator iter;	
	map<string,int>::iterator rankIter;
	char* pName = myHero->getGuildName();//获取帮派的名字;
	if(NULL == pName)
	{
		sprintf(leader_camp_msg,"11,4,2,-2,0,0,0,0,1,0,-1");	
		return leader_camp_msg;
	}
	string currFactionName=	pName;
	
	if(currFactionName==factionAName)
	{
		iter = factionA.find(myHeroId);
		if(iter ==factionA.end())
		{
			sprintf(leader_camp_msg,"11,4,2,-3,0,0,0,0,1,0,-1");	
			return leader_camp_msg;
		}
			
		rankIter=factionARank.find(myHeroId);	
		if(rankIter == factionARank.end())
		{
			sprintf(leader_camp_msg,"11,4,2,-4,0,0,0,0,1,0,-1");	
			return leader_camp_msg;
		}
		rank=(rankIter->second);	
	}else if(currFactionName==factionBName)
	{
		iter = factionB.find(myHeroId);
		if(iter ==factionB.end())
		{
			sprintf(leader_camp_msg,"11,4,2,-3,0,0,0,0,1,0,-1");	
			return leader_camp_msg;
		}
			
		rankIter=factionBRank.find(myHeroId);	
		if(rankIter == factionBRank.end())
		{
			sprintf(leader_camp_msg,"11,4,2,-4,0,0,0,0,1,0,-1");	
			return leader_camp_msg;
		}
		rank=(rankIter->second);
	}else
	{
		sprintf(leader_camp_msg,"11,4,2,-2,0,0,0,0,1,0,-1");	
		return leader_camp_msg;
	}
	
	int heroTitle=1;//无头衔；
	if(winnerFaction==currFactionName)
	{
		if(rank >= camp_reward_info[WIN_LEADER_REWARD].rank_limit_value)
			rank=camp_reward_info[WIN_LEADER_REWARD].rank_limit_value-1;	
		
		string SmyHeroId=myHeroId;
		if(guildLeaderAId == SmyHeroId || guildLeaderBId == SmyHeroId)
			heroTitle=0;//有头衔；
		
		sprintf(leader_camp_msg,"11,4,2,0,%d,%d,%d,%d,%d,%d,%d",\
				camp_reward_info[WIN_LEADER_REWARD].guidExp_base_value-camp_reward_info[WIN_LEADER_REWARD].guidExp_dec_value*rank,\
				camp_reward_info[WIN_LEADER_REWARD].gold_base_value-rank*camp_reward_info[WIN_LEADER_REWARD].gold_dec_value,\
				camp_reward_info[WIN_LEADER_REWARD].guidGlory_base_value-camp_reward_info[WIN_LEADER_REWARD].guidGlory_dec_value*rank,\
				camp_reward_info[WIN_LEADER_REWARD].prestige_base_value-camp_reward_info[WIN_LEADER_REWARD].prestige_dec_value*rank,\
				heroTitle,1,rankIter->second+1);	
	}else{
		if(rank >= camp_reward_info[FAI_LEADER_REWARD].rank_limit_value)
			rank=camp_reward_info[FAI_LEADER_REWARD].rank_limit_value-1;
			
		sprintf(leader_camp_msg,"11,4,2,0,%d,%d,%d,%d,%d,%d,%d",\
				camp_reward_info[FAI_LEADER_REWARD].guidExp_base_value-camp_reward_info[FAI_LEADER_REWARD].guidExp_dec_value*rank,\
				camp_reward_info[FAI_LEADER_REWARD].gold_base_value-rank*camp_reward_info[FAI_LEADER_REWARD].gold_dec_value,\
				camp_reward_info[FAI_LEADER_REWARD].guidGlory_base_value-camp_reward_info[FAI_LEADER_REWARD].guidGlory_dec_value*rank,\
				camp_reward_info[FAI_LEADER_REWARD].prestige_base_value-camp_reward_info[FAI_LEADER_REWARD].prestige_dec_value*rank,\
				heroTitle,0,rankIter->second+1);
	}
	
	return leader_camp_msg;
}


int 
LeaderCampWar::receiveAwards(Hero* myHero)
{
	int rank=LEADER_CAMP_WAR_AWARDS_LOWEST_RANGE-1;
	if(NULL == myHero)
		return -1;
	char* myHeroId = myHero->getIdentity();
	
	map<string,LeaderCampWarData>::iterator iter;	
	
	char* pName = myHero->getGuildName();//获取帮派的名字;
	if(NULL == pName)
		return -2;
	string currFactionName=pName;//获取帮派的名字;	
	
	if(currFactionName==factionAName)
	{
		iter = factionA.find(myHeroId);
		if(iter ==factionA.end())
			return -3;
			
		map<string,int>::iterator rankIter=factionARank.find(myHeroId);	
		if(rankIter == factionARank.end())
			return -4;	
		rank=(rankIter->second);
		factionA.erase(iter);		
	}else if(currFactionName==factionBName)
	{
		iter = factionB.find(myHeroId);
		if(iter ==factionB.end())
			return -3;
			
		map<string,int>::iterator rankIter=factionBRank.find(myHeroId);	
		if(rankIter == factionBRank.end())
			return -4;	
		rank=(rankIter->second);//取到等级；
		factionB.erase(iter);//删除领完奖励；
	}else
	{
		return -2;
	}
	
	if(rank >= LEADER_CAMP_WAR_AWARDS_LOWEST_RANGE)
		rank=LEADER_CAMP_WAR_AWARDS_LOWEST_RANGE-1;		
		
	if(winnerFaction==currFactionName)
	{	
		if(rank >= camp_reward_info[WIN_LEADER_REWARD].rank_limit_value)
			rank=camp_reward_info[WIN_LEADER_REWARD].rank_limit_value-1;	
	
		addGuildExp(const_cast<char*>(currFactionName.c_str()),myHeroId,\
			camp_reward_info[WIN_LEADER_REWARD].guidExp_base_value-camp_reward_info[WIN_LEADER_REWARD].guidExp_dec_value*rank);//增加帮派经验
		addMyGuildGlory(const_cast<char*>(currFactionName.c_str()),myHeroId,\
			camp_reward_info[WIN_LEADER_REWARD].guidGlory_base_value-camp_reward_info[WIN_LEADER_REWARD].guidGlory_dec_value*rank);//增加个人帮贡
		if(myHero->getMoney() == NULL)
			return -3;
		increaseBoundGameMoney(myHero,camp_reward_info[WIN_LEADER_REWARD].gold_base_value-rank*camp_reward_info[WIN_LEADER_REWARD].gold_dec_value);		
		myHero->addPrestigeValue(camp_reward_info[WIN_LEADER_REWARD].prestige_base_value-camp_reward_info[WIN_LEADER_REWARD].prestige_dec_value*rank);//声望 
		string SmyHeroId=myHeroId;
		if(guildLeaderAId == SmyHeroId || guildLeaderBId == SmyHeroId)
		{
			myHero->addTitle(CAMP_LEADER_TITLE);//设置头衔；
		}
	}else{
		if(rank >= camp_reward_info[FAI_LEADER_REWARD].rank_limit_value)
			rank=camp_reward_info[FAI_LEADER_REWARD].rank_limit_value-1;
	
		addGuildExp(const_cast<char*>(currFactionName.c_str()),myHeroId,\
				camp_reward_info[FAI_LEADER_REWARD].guidExp_base_value-camp_reward_info[FAI_LEADER_REWARD].guidExp_dec_value*rank);//增加帮派经验
		addMyGuildGlory(const_cast<char*>(currFactionName.c_str()),myHeroId,\
			camp_reward_info[FAI_LEADER_REWARD].guidGlory_base_value-camp_reward_info[FAI_LEADER_REWARD].guidGlory_dec_value*rank);	//增加个人帮贡
		if(myHero->getMoney() == NULL)
			return -3;
		increaseBoundGameMoney(myHero,camp_reward_info[FAI_LEADER_REWARD].gold_base_value-rank*camp_reward_info[FAI_LEADER_REWARD].gold_dec_value);		
		myHero->addPrestigeValue(camp_reward_info[FAI_LEADER_REWARD].prestige_base_value-camp_reward_info[FAI_LEADER_REWARD].prestige_dec_value*rank);//声望 
	}
	
	return 0;
}


bool
LeaderCampWar::sendMsgStart(time_t _last_time)
{
	sprintf(leader_camp_msg,"11,19,%s,%d,%d,%s,%d,%d",factionAName.c_str(),factionAActiveSize,num_factionA_leader_deaths,\
													 factionBName.c_str(),factionBActiveSize,num_factionB_leader_deaths);
	
	char initTime[50]={0};
	sprintf(initTime,"11,21,0,%lu",_last_time);
	
	for(map<string,LeaderCampWarData>::iterator iterFaction=factionA.begin();iterFaction != factionA.end();iterFaction++)
	{
		map<string,Hero*>::iterator iter=heroId_to_pHero.find(iterFaction->first);
		if(iter!=heroId_to_pHero.end()&& strstr(iter->second->getMapId(),(mapTypeInfo.campWarMapId).c_str()))
		{
			iter->second->setCampWarStartMark(true);
			send_msg(iter->second->getFd(),leader_camp_msg);
			if(_last_time > 0)
			{
				send_msg(iter->second->getFd(),initTime);
			}
		}		
	}
	

	for(map<string,LeaderCampWarData>::iterator iterFaction=factionB.begin();iterFaction != factionB.end();iterFaction++)
	{
		map<string,Hero*>::iterator iter=heroId_to_pHero.find(iterFaction->first);
		if(iter!=heroId_to_pHero.end()&& strstr(iter->second->getMapId(),(mapTypeInfo.campWarMapId).c_str()))
		{
			iter->second->setCampWarStartMark(true);
			send_msg(iter->second->getFd(),leader_camp_msg);
			if(_last_time > 0)
			{
				send_msg(iter->second->getFd(),initTime);
			}
		}		
	
	}
	
	if(_last_time > 0)//如果开战后，有一方帮派的人数未满，结束战斗！
	{
		if(factionB.size()==0 || factionA.size()==0)//调用终止阵营战函数；
		{
			string winner = finishFactionCampWar();
			campWarController.finishLeaderCampWar(winner,index);
		}

		leaderCampWarLastTime=_last_time;
		LeaderCampWarStartTime=time(NULL);//统领阵营战开始时间；	
		LeaderCampWarEndTime=LeaderCampWarStartTime+leaderCampWarLastTime;//统领阵营战结束时间；
		
		if(NULL == leader_campWar_timer)//启动计时器
			leader_campWar_timer = new ev_timer;
		ext_ev_timer_init(leader_campWar_timer,LeaderCampWarFinishCall,_last_time,0,this);
		ev_timer_start(loops,leader_campWar_timer); 
	}
	
	return true;
}

/*****************************************/
/************ 报名处理 ******************/
/***************************************/
/**
argument: _factionName 帮派名字。
  return: int   0:报名成功；
			    -1：表示已经报名；
*/
char*
LeaderCampWar::viewApplyInfo()
{
	if(applyWarFactionInfo.size() <= 0)
	{
		cout<<"[XHM MSG] applyWarFactionInfo.size() == 0 ,return!"<<endl;
	}
	
	Guild* guild = NULL;
	int len=0;
	int size=0;
	memset(my_apply_info,0,sizeof(my_apply_info));
	memset(apply_info,0,sizeof(apply_info));
	string guildName;	
	// for(map<string,int>::iterator curr = applyWarFactionInfo.begin();curr != applyWarFactionInfo.end(); ++curr)
	for(map<string,int>::iterator curr = applyWarFactionInfo.begin();curr != applyWarFactionInfo.end(); ++curr)	
	{
		len = strlen(my_apply_info);
		guildName=curr->first;
		guild = getGuildWithName(const_cast<char *>((guildName).c_str()));
		if(NULL == guild)
			continue;	
		size++;	
		sprintf(my_apply_info+len,",%s,%d,%d,%ld",guild->getName(),guild->getLevel(),guild->getCurMembs(),guild->getGuildScore());
	}
	snprintf(apply_info,10240,"11,28,%d,%d%s",index,size,my_apply_info);
	return apply_info;
}


int 
LeaderCampWar::apply2FactionWar(string _factionName,int _camp)
{
	if(_factionName.empty())
		return -6;
		
	if(winnerFaction == _factionName)
		return 1;
		
	if(applyWarFactionInfo.size() > 250)
		return 2;
		
	pair< map< string,int >::iterator,bool > ret;
	int level=getGuildRankInCamp(const_cast<char*>(_factionName.c_str()),_camp);//根据帮派名字找到帮派排名；
	ret = applyWarFactionInfo.insert(FACTION_Val(_factionName,++level));
	cout<<"[XHM MSG] (src/campWar/leaderCampWar.cpp)camp:"<<_camp<<" Apply2FactionWar size:"<<applyWarFactionInfo.size()<<endl;
	if(ret.second)
		return 0;
	else 
		return -6;
}


static int 
applyWarcmp(const PAIR_INT& x, const PAIR_INT& y) //报名筛选比较函数
{  
    return x.second > y.second;  
}


/**
argument: _factionName 帮派名字。
  return: int   0:成功；
			    -1:表示报名不足，系统无法参赛；
function: 筛选统领战排名，选出能参战帮派；
*/
char* 
LeaderCampWar::endApplyFactionWar()
{
	char *Bname=NULL;
	Guild* guild = NULL;
	
	char enterInfo[50]={0};
	sprintf(enterInfo,"11,16,2,0");
	
	char failureInfo[50]={0};
	sprintf(failureInfo,"11,16,2,1");
	
	if(applyWarFactionInfo.size() == 0)
	{
		cout<<"[XHM MSG] no body apply for the leader campWar!"<<endl;
		return Bname;
	}
	
  	vector<PAIR_INT> vec;  
	for(map<string,int>::iterator curr = applyWarFactionInfo.begin();curr != applyWarFactionInfo.end(); ++curr)
	{
		//cout<<"[XHM MSG] Test for the leaderCampWar applyName(leaderCampWar.cpp):"<<curr->first<<endl;
		//TODO 更改后面排序的值，这个值是帮派总战力值；
		
		guild = getGuildWithName(const_cast<char *>((curr->first).c_str()));
		if(NULL == guild)
			continue;	
		vec.push_back(make_pair(curr->first, guild->getGuildScore()));  
	}
	
	sort(vec.begin(), vec.end(), applyWarcmp);
	
	applyWarFactionInfo.clear();//清空报名信息容器
	map<string,int>().swap(applyWarFactionInfo);
	
	initFactionCampWar();//清空数据准备开展数据；
	
	int enterCampWarFlg=0;
	
	if(factionAName.empty())//第一次，统领确定为排名第一的玩家；
	{
		if(vec.size()<2)
		{
			//给当前报名的帮主发信息，表明没有人挑战。
			if(vec.size() == 1)
				setWinnerFaction(vec[0].first);				
			return Bname;
		}
		else
		{
			factionAName = vec[0].first;
			factionBName = vec[1].first;
		}
		enterCampWarFlg=2;
		setWinnerFaction(factionAName);
	}else{						//默认当前阵营的统领帮派的名字为factionAName；
		if(vec.size()<1)		//排名不足，不能比赛；
		{
			//给当前阵营统领发数据，表示没有人挑战。
			return Bname;
		}
		
		factionBName = vec[0].first;
		enterCampWarFlg=1;	
	}
	map<string, Hero*>::iterator iter;
	
	//帮派名字给帮主和副帮主发信息 可以参加统领战
	char* presidId=getGuildPresidId(const_cast<char*>(factionAName.c_str()));
	if(presidId){
		guildLeaderAId=presidId;
		iter = heroId_to_pHero.find(presidId);
		if(iter!=heroId_to_pHero.end())//该英雄id存在；
		{
			//在线，给帮主发信息	
			send_msg(iter->second->getFd(),enterInfo);
		}
	}
	
	char* vicePresidId=getGuildVicePresidId(const_cast<char*>(factionAName.c_str()));
	if(vicePresidId){
		iter = heroId_to_pHero.find(vicePresidId);
		if(iter!=heroId_to_pHero.end())//该英雄id存在；
		{
			send_msg(iter->second->getFd(),enterInfo);//在线，给副帮主帮主发信息
		}
	}
	

	presidId=getGuildPresidId(const_cast<char*>(factionBName.c_str()));
	if(presidId){
		guildLeaderBId=presidId;	
		iter = heroId_to_pHero.find(presidId);
		if(iter!=heroId_to_pHero.end())//该英雄id存在；
		{
			send_msg(iter->second->getFd(),enterInfo);//在线，给帮主发信息
		}
	}
	
	vicePresidId=getGuildVicePresidId(const_cast<char*>(factionBName.c_str()));
	if(vicePresidId){
		iter = heroId_to_pHero.find(vicePresidId);
		if(iter!=heroId_to_pHero.end())//该英雄id存在；
		{
			send_msg(iter->second->getFd(),enterInfo);//在线，给副帮主发信息
		}

	}
	
	for(;enterCampWarFlg<vec.size();enterCampWarFlg++)//给排名安排不上的发信息，表示排名不足，无法参赛；
	{
		char* heroId=getGuildVicePresidId(const_cast<char*>(vec[enterCampWarFlg].first.c_str()));	
		iter = heroId_to_pHero.find(heroId);
		if(iter!=heroId_to_pHero.end())//该英雄id存在；
			send_msg(iter->second->getFd(),failureInfo);

	}
	
	cout<<"[XHM MSG] Enter LeaderCampWar CuildName Aname:"<<factionAName<<" Bname:"<<factionBName<<endl;
	Bname = const_cast<char *>(factionBName.c_str());
	return Bname;
}
