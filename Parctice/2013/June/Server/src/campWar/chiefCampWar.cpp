#include <math.h>
#include "money_operator.h"
#include "guild_asist.h"
#include "camp_war_reward.h"
#include "libev.h"
#include "chiefCampWar.h"
#include "campWarManagement.h"

extern struct ev_loop *loops;
extern MapType_T mapTypeInfo;//某些特殊地图的ID；
extern campWarManagement campWarController;//阵营战管理实例；	
extern CampRewardData_T camp_reward_info[CAMP_WAR_REWARD_SIZE];//奖励	

static char chief_camp_msg[300];//奖励数据；
static ev_timer *chief_campWar_timer;
static char msg2Leader[]={'1','1',',','2','3',',','1'};

static void
ChiefCampWarFinishCall(struct ev_loop *loop,ev_timer *think,int revents)
{
	if(think == NULL)
		return;
    ev_timer_stop(loop,think);
	
	ChiefCampWar *chiefCampWar = (ChiefCampWar *)think->target;
	if(chiefCampWar == NULL)
	{
		return;
	}
	// cout<<"[XHM MSG] ChiefCampWar time is out(campWarMangement.cpp),Going to call finishChiefCampWar()"<<endl;
	chiefCampWar->finishChiefCampWar();
}

ChiefCampWar::ChiefCampWar()
{
	factionAName="";					
	factionBName="";
	factionCName="";
	Champion="";								//当前盟主阵营的帮派；
	secondPlace="";	
	thirdPlace="";	
	startChiefCampWar();
}

ChiefCampWar::~ChiefCampWar()
{

}
	
int 
ChiefCampWar::getWarHeroSize(void)			//获取盟主阵营战的所有人数；
{
	return factionA.size()+factionB.size()+factionC.size();
}

/*
argument hero 英雄实例指针
  return int -1 hero为空；
			 -2 帮派名字不是当前盟主战的帮派；
			 -3 insert失败，已经参加过比赛；
			  0 加入成功；
*/
int 
ChiefCampWar::addHero2Chiefwar(Hero* myHero)		//添加英雄ID到阵营战；
{
	if(NULL == myHero)
		return -1;
		
	ChiefCampWarData_T tempChiefCampWarData(0,0);	
	pair< map< string,ChiefCampWarData_T>::iterator,bool > ret;//用于insert的返回值，判断insert是否成功。
	

	char* factionName=myHero->getGuildName();  //判断帮派名字；	
	if(factionName==NULL || strlen(factionName)==0)
		return -2;
		
	string currFactionName=factionName;
	if(currFactionName == factionAName)
	{
		curr_factionA_counts++;
		ret = factionA.insert(HEROID_VAL_CHIEF(myHero->getIdentity(),tempChiefCampWarData));
	}
	else if(currFactionName == factionBName)
	{
		curr_factionB_counts++;
		ret = factionB.insert(HEROID_VAL_CHIEF(myHero->getIdentity(),tempChiefCampWarData));
	}
	else if(currFactionName == factionCName)
	{
		curr_factionC_counts++;
		ret = factionC.insert(HEROID_VAL_CHIEF(myHero->getIdentity(),tempChiefCampWarData));
	}
	else 
	{
		return -2;
	}
	
	if(ret.second)
		return 0;
	else{
		if(myHero->isInCampWar())
			return -3;
		
		return 0;
	}

}    

/*
argument hero 英雄实例指针
  return int -1 hero为空；
			 -2 帮派名字不是当前盟主战的帮派；
			 -3 找不到要删除掉的角色ID；
			  0 删除成功；
*/
int 
ChiefCampWar::delHeroFromChiefWar(Hero* myHero)	//从杀敌战中删除；
{
	if(myHero==NULL)
		return -1;
		
	char* pfactionName=myHero->getGuildName();//获取帮派的名字;
	if(NULL == pfactionName)
		return -2;
		
	string currFactionName =  pfactionName;
	map<string,ChiefCampWarData_T>::iterator iter;
	
	if(currFactionName==factionAName)
	{
		iter = factionA.find(myHero->getIdentity());
		if(iter ==factionA.end())
			return -3;
		if(curr_factionA_counts>0)
		curr_factionA_counts--;
	}
	else if(currFactionName==factionBName)
	{
		iter = factionB.find(myHero->getIdentity());
		if(iter ==factionB.end())
			return -3;
		if(curr_factionB_counts>0)
		curr_factionB_counts--;
	}
	else if(currFactionName==factionCName)
	{
		iter = factionC.find(myHero->getIdentity());
		if(iter ==factionC.end())
			return -3;
		if(curr_factionC_counts>0)
		curr_factionC_counts--;
	}else
		return -2;
		
	if(myHero->isInCampWar()){
		sendMsgStartPK();//	发送命令更新数据	
		
		//TODO 增加俩个帮派有人全部阵亡，结束战斗；	
		if(curr_factionC_counts==0&&curr_factionB_counts==0 ||\
			curr_factionC_counts==0&&curr_factionA_counts==0||\
			curr_factionB_counts==0&&curr_factionA_counts==0)
		
			//增加定时器终止；	
			ev_timer_stop(loops,chief_campWar_timer);
			finishChiefCampWar();
	}	
	return 0;
}

bool 
ChiefCampWar::startChiefCampWar()//盟主战争开始处理；
{
	num_factionA_leader_deaths=0;//初次赋值为默认值，表示死亡次数达到最大；
	num_factionB_leader_deaths=0;
	num_factionC_leader_deaths=0;
	
	curr_factionA_counts=0;
	curr_factionB_counts=0;
	curr_factionC_counts=0;

	map<string, Hero*>::iterator iter;
	factionA.clear();
	{
		map<string,ChiefCampWarData_T> temp=factionA;
		factionA.swap(temp);
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
	}
	
	factionB.clear();
	{
		map<string,ChiefCampWarData_T> temp=factionB;
		factionB.swap(temp);
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
	
	factionC.clear();
	{
		map<string,ChiefCampWarData_T> temp=factionC;
		factionC.swap(temp);
		if(!factionCName.empty())
		{
			char* p_hero_id = getGuildPresidId(const_cast<char*>(factionCName.c_str()));
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
}

//判断统领阵营胜利
int 
ChiefCampWar::JudgeWinner(int factionANum,int leaderA_deaths,string& leaderAname,int factionBNum,int leaderB_deaths,string& leaderBname)
{
	/*判断统领阵营胜利*/
	if(factionANum != 0 && factionBNum == 0)
	{
		return 1;
	}
	else if(factionANum == 0 && factionBNum != 0)
	{
		return 0;
	}else{	
		//如果帮主不存在，对方赢；
		if(leaderA_deaths == MAX_DEATHS && leaderB_deaths < MAX_DEATHS)	
			return 0;
		else if(leaderA_deaths <  MAX_DEATHS && leaderB_deaths == MAX_DEATHS)
			return 1;
		else{
			//帮主都存在或者帮主均死亡，则人数多一方获胜；
			if(factionANum > factionBNum)
				return 1;
			else if(factionANum < factionBNum)	
				return 0;
			else{
				//上条件均不满足，帮主死亡次数少的一方胜利；
				if(leaderA_deaths < leaderB_deaths)
					return 1;
				else{
						if(Champion.empty())
							return 1;
						else if(Champion==leaderBname)
							return 0;
						else if(Champion==leaderAname)
							return 1;
						else
							return 1;
							
					}
				}
			}
		}
}

static int 
cmp(const PAIR_CHIEF_CAMP_WAR_DATA& x, const PAIR_CHIEF_CAMP_WAR_DATA& y)  
{  
    return x.second.kills > y.second.kills;  
}

void 
ChiefCampWar::finishChiefCampWar() 	//盟主战争结束处理；
{
	int size;
	char CampWarInfo[50]={0};
	sprintf(CampWarInfo,"11,8,4");	//给所有人发一条数据，战争结束；
	map<string, Hero*>::iterator iter;
	
	if(factionA.size()==0 && factionB.size()==0 && factionC.size()==0)
	{
		cout<<"[XHM MSG] no member enter the leader campWar.<chiefCampWar.cpp>"<<endl;
		return;
	}

	vector<PAIR_CHIEF_CAMP_WAR_DATA> vecA;  
	for(map<string,ChiefCampWarData_T>::iterator curr = factionA.begin();curr != factionA.end();curr++)
	{
		iter = heroId_to_pHero.find(curr->first);
		if(iter!=heroId_to_pHero.end())	//该英雄id不存在；
		{
			if(iter->second->getCampWarType() == 3)
			{
				// cout<<"[XHM MSG] in the chiefCampWar,send msg:"<<CampWarInfo<<endl;		
				iter->second->setCampWarStartMark(false);				
				send_msg(iter->second->getFd(),CampWarInfo);
			}else{
				// cout<<"[XHM MSG] in the chiefCampWar,enter but exit :"<<curr->first<<endl;
				//打过阵营战，但是不在线的处理；
			}
		}
		
		vecA.push_back(make_pair(curr->first, curr->second));  
	}
	
    sort(vecA.begin(), vecA.end(), cmp);	//阵营a按照杀人次数排序；
	
	factionARank.clear();
	map<string,int>().swap(factionARank);
	
	size= vecA.size();
	for(int i=0;i<size;i++)
	{
		factionARank.insert(HEROID_RANK_CHIEF(vecA[i].first,i));
	}
	
  
	vector<PAIR_CHIEF_CAMP_WAR_DATA> vecB;  
	for(map<string,ChiefCampWarData_T>::iterator curr = factionB.begin();curr != factionB.end();curr++)
	{	
	    iter = heroId_to_pHero.find(curr->first);
		if(iter!=heroId_to_pHero.end())		//该英雄id不存在；
		{
			if(iter->second->getCampWarType() == 3)
			{
				iter->second->setCampWarStartMark(false);				
				send_msg(iter->second->getFd(),CampWarInfo);
			}else{
				//打过阵营战，但是不在线的处理；
			}
		}
		
		vecB.push_back(make_pair(curr->first, curr->second));  
	}
	sort(vecB.begin(), vecB.end(), cmp);//阵营b按照杀人次数排序；
	
	factionBRank.clear();
	map<string,int>().swap(factionBRank);
	
	size= vecB.size();
	for(int i=0;i<size;i++)
	{
		factionBRank.insert(HEROID_RANK_CHIEF(vecB[i].first,i));
	}
	
	vector<PAIR_CHIEF_CAMP_WAR_DATA> vecC;  
	for(map<string,ChiefCampWarData_T>::iterator curr = factionC.begin();curr != factionC.end(); ++curr)
	{
		iter = heroId_to_pHero.find(curr->first);
		if(iter!=heroId_to_pHero.end())//该英雄id不存在；
		{
			if(iter->second->getCampWarType() == 3)
			{
				iter->second->setCampWarStartMark(false);				
				send_msg(iter->second->getFd(),CampWarInfo);
			}else{
				//打过阵营战，但是不在线的处理；
			}
		}
		
		vecC.push_back(make_pair(curr->first, curr->second));  
	}
	sort(vecC.begin(), vecC.end(),cmp);	//阵营c按照杀人次数排序；
	
	factionCRank.clear();
	map<string,int>().swap(factionCRank);
	
	size= vecC.size();
	for(int i=0;i<size;i++)
	{
		factionCRank.insert(HEROID_RANK_CHIEF(vecC[i].first,i));
	}
	
	//判断胜负，决策出冠军，亚军，季军；
	int ret  = JudgeWinner(curr_factionA_counts,num_factionA_leader_deaths,factionAName,curr_factionB_counts,num_factionB_leader_deaths,factionBName);
		ret += JudgeWinner(curr_factionA_counts,num_factionA_leader_deaths,factionAName,curr_factionC_counts,num_factionC_leader_deaths,factionCName);
	
	if(ret == 2){
		Champion=factionAName;
		if(JudgeWinner(curr_factionB_counts,num_factionB_leader_deaths,factionBName,curr_factionC_counts,num_factionC_leader_deaths,factionCName))
		{
			secondPlace=factionBName;
			thirdPlace=factionCName;
		}else{
			secondPlace=factionCName;
			thirdPlace=factionBName;
		}			
	}else if(ret == 1){
		secondPlace=factionAName;	
		if(JudgeWinner(curr_factionB_counts,num_factionB_leader_deaths,factionBName,curr_factionC_counts,num_factionC_leader_deaths,factionCName))
		{
			Champion=factionBName;
			thirdPlace=factionCName;
		}else{
			Champion=factionCName;
			thirdPlace=factionBName;
		}	
	}else if(ret == 0){
		thirdPlace=factionAName;	
		if(JudgeWinner(curr_factionB_counts,num_factionB_leader_deaths,factionBName,curr_factionC_counts,num_factionC_leader_deaths,factionCName))
		{
			Champion=factionBName;
			secondPlace=factionCName;
		}else{
			Champion=factionCName;
			secondPlace=factionBName;
		}	
	}
	
	/*判断统领阵营胜利*/
	/*
	if(numFactiona != 0 && numFactionb == 0 && numFactionc == 0)
	{
		winnerFaction=factionAName;
	}
	else if(numFactionb == 0 && numFactiona != 0 && numFactionc == 0)
	{
		winnerFaction=factionBName;
	}
	else if(numFactionb == 0 && numFactiona == 0 && numFactionc != 0)
	{
		winnerFaction=factionCName;
	}else{	
		//如果帮主不存在，对方赢；
		if(num_factionA_leader_deaths == MAX_DEATHS && num_factionB_leader_deaths == MAX_DEATHS && num_factionC_leader_deaths < MAX_DEATHS)	//
			winnerFaction=factionCName;
		else if(num_factionA_leader_deaths == MAX_DEATHS && num_factionB_leader_deaths < MAX_DEATHS && num_factionC_leader_deaths == MAX_DEATHS)
			winnerFaction=factionBName;
		else if(num_factionA_leader_deaths < MAX_DEATHS && num_factionB_leader_deaths == MAX_DEATHS && num_factionC_leader_deaths == MAX_DEATHS)
			winnerFaction=factionAName;
		else{
			//如果帮主均存在或者帮主死亡次数相等，则帮主死亡次数少的一方胜利；
			winnerFaction=num_factionA_leader_deaths>=num_factionB_leader_deaths?\
			  (num_factionA_leader_deaths>=num_factionC_leader_deaths?factionAName:factionCName):\
			  (num_factionB_leader_deaths>=num_factionC_leader_deaths?factionBName:factionCName);
			}
		}
	*/
	campWarController.finishChiefCampWar(Champion);//结束处理，设置阵营缓存数据；
}


/**
argument hero 英雄实例指针
  return int -1 hero为空；
			 -4 帮派名字不是当前盟主战的帮派；
			 >0 死亡次数；
*/
int 
ChiefCampWar::addDeathCounts(Hero* myHero)//增加英雄ID死亡次数；
{
	bool sendMsgFlg=false;
	
	if(NULL == myHero)
		return -1;
		

	char* pName = myHero->getGuildName();//获取帮派的名字;
	if(NULL == pName)
		return -2;
	string currFactionName=	pName;
	
	map<string,ChiefCampWarData_T>::iterator iter;
	char* presidId=getGuildPresidId(const_cast<char*>(currFactionName.c_str()));//获取帮主ID；
	
	if(currFactionName==factionAName)
	{
		iter = factionA.find(myHero->getIdentity());
		if(iter ==factionA.end())
			return -1;
			
		if(presidId!=NULL)
		{
			if(!strcmp(myHero->getIdentity(),presidId))//如果是帮主ID
			{
				num_factionA_leader_deaths++;
				sendMsgFlg=true;
			}
		}	
		
	}else if(currFactionName==factionBName)
	{
		iter = factionB.find(myHero->getIdentity());
		if(iter ==factionB.end())
			return -1;
		
		if(presidId!=NULL)
		{
			if(!strcmp(myHero->getIdentity(),presidId))//如果是帮主ID
			{
				num_factionB_leader_deaths++;
				sendMsgFlg=true;
			}
		}	
			
	}else if(currFactionName==factionCName)
	{
		iter = factionC.find(myHero->getIdentity());
		if(iter ==factionC.end())
			return -1;
		
		if(presidId!=NULL)
		{
			if(!strcmp(myHero->getIdentity(),presidId))//如果是帮主ID
			{
				num_factionC_leader_deaths++;
				sendMsgFlg=true;
			}
		}	
					
	}else
	{
		return -4;
	}
	
	int deathCounts = ++(iter->second.deaths);	
	if(deathCounts >= MAX_DEATHS)
	{
		delHeroFromChiefWar(myHero);//减少在线人数；
	}else if(sendMsgFlg)
	{
		if(myHero->isInCampWar())
			sendMsgStartPK();//杀敌数；
	}
	
	
	return deathCounts;
}


/**
argument hero 英雄实例指针
  return int -1 hero为空；
			 -2 帮派名字不是当前盟主战的帮派；
			 -3 找不到角色ID；
			 >0 杀敌数量；
*/
int 
ChiefCampWar::addKills(Hero* myHero)//增加杀敌数；
{
	if(NULL == myHero)
		return -1;
		

	char* pName = myHero->getGuildName();//获取帮派的名字;
	if(NULL == pName)
		return -2;
		
	string currFactionName=pName;
	
	map<string,ChiefCampWarData_T>::iterator iter;//查找角色的迭代器迭代器；
	
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
	}else if(currFactionName==factionCName)
	{
		iter = factionC.find(myHero->getIdentity());
		if(iter ==factionC.end())
			return -3;
	}else
	{
		return -2;
	}
	
	return ++(iter->second.kills);
}


bool
ChiefCampWar::setFactionName(string _factionName,int index)
{
	if(_factionName.empty())
		return false;

	//此处最好加上帮派名字到实例帮派的查询验证；
	// cout<<"[XHM TEST] <src/campWar/chiefCampWar.cpp>leaderFactionName:"<<_factionName<<" factionAName:"<<factionAName<<" factionBName:"<<factionBName<<" factionCName:"<<factionCName<<endl;	
	if(0 == index){
		factionAName=_factionName;
	}else if(1 == index){
		factionBName=_factionName;	
	}else if(2 == index){
		factionCName=_factionName;
	}else 
		return false;
	return true;	
}

char* 
ChiefCampWar::viewAwards(Hero* myHero)//查看奖励；
{
	sprintf(chief_camp_msg,"11,4,3,-1,0,0,0,0,1");
	
	int rankFlg=0;
	int rank= CHIEF_CAMP_WAR_AWARDS_LOWEST_RANGE-1;
	if(NULL == myHero)
		return chief_camp_msg;
	
	char *myHeroId = myHero->getIdentity();
	if(NULL == myHeroId)
		return chief_camp_msg;
		
	string SmyHeroId = myHeroId;		
	int heroTitle=1;
		
	map<string,ChiefCampWarData_T>::iterator iter;	
	map<string,int>::iterator rankIter;
	
	char* pName = myHero->getGuildName();//获取帮派的名字;
	if(NULL == pName)
		return chief_camp_msg;
		
	string currFactionName=pName;	//获取帮派的名字;
	// cout<<"[XHM TEST] <src/campWar/chiefCampWar.cpp>currFactionName:"<<currFactionName<<" Champion:"<<Champion<<"secondPlace:"<<secondPlace<<" thirdPlace:"<<thirdPlace<<endl;
	
	if(currFactionName == factionAName)
	{	
		rankIter=factionARank.find(myHeroId);	
		if(rankIter == factionARank.end())//如果找不到
		{
			sprintf(chief_camp_msg,"11,4,3,-4,0,0,0,0,0");	
			return chief_camp_msg;
		}
			
		rank=(rankIter->second);	
	}else if(currFactionName==factionBName)
	{
		rankIter=factionBRank.find(myHeroId);	
		if(rankIter == factionBRank.end())//如果找不到
		{
			sprintf(chief_camp_msg,"11,4,3,-4,0,0,0,0,0");	
			return chief_camp_msg;
		}
		
		rank=(rankIter->second);	
	}else if(currFactionName==factionCName)
	{	
		rankIter=factionCRank.find(myHeroId);	
		if(rankIter == factionCRank.end())//如果找不到
		{
			sprintf(chief_camp_msg,"11,4,3,-4,0,0,0,0,0");	
			return chief_camp_msg;
		}
		rank=(rankIter->second);
	}else
	{
		sprintf(chief_camp_msg,"11,4,3,-2,0,0,0,0,0");	
		return chief_camp_msg;
	}
		
	if(Champion==currFactionName)
	{
		if(SmyHeroId == chiefHeroId)
			heroTitle=0;
			
		if(rank >= camp_reward_info[FIRST_CHIEF_REWARD].rank_limit_value)//如果大于配置文件最大奖励等级限制；
			rank=camp_reward_info[FIRST_CHIEF_REWARD].rank_limit_value-1;		
		rankFlg=1;
	}
	else if(secondPlace==currFactionName)
	{
		if(rank >= camp_reward_info[SECOND_CHIEF_REWARD].rank_limit_value)//如果大于配置文件最大奖励等级限制；
			rank=camp_reward_info[SECOND_CHIEF_REWARD].rank_limit_value-1;	
		    rankFlg=2;
	}
	else if(thirdPlace==currFactionName)
	{
		if(rank >= camp_reward_info[THIRD_CHIEF_REWARD].rank_limit_value)//如果大于配置文件最大奖励等级限制；
			rank=camp_reward_info[THIRD_CHIEF_REWARD].rank_limit_value-1;	
			 rankFlg=3;
	}
	
	if(rankFlg <= 0 || rankFlg > 3)
	{
		sprintf(chief_camp_msg,"11,4,3,-4,0,0,0,0,0");	
		return chief_camp_msg;
	}	
	//生成奖励消息；
	sprintf(chief_camp_msg,"11,4,3,0,%d,%d,%d,%d,%d,%d,%d",camp_reward_info[rankFlg+2].guidExp_base_value-\
											camp_reward_info[rankFlg+2].guidExp_dec_value*rank,\
											camp_reward_info[rankFlg+2].gold_base_value-camp_reward_info[rankFlg+2].gold_dec_value*rank,\
											camp_reward_info[rankFlg+2].prestige_base_value-camp_reward_info[rankFlg+2].prestige_dec_value*rank,\
											camp_reward_info[rankFlg+2].guidGlory_base_value-camp_reward_info[rankFlg+2].guidGlory_dec_value*rank,\
											heroTitle,rankFlg,rankIter->second+1);	

	return chief_camp_msg;
}

int 
ChiefCampWar::receiveAwards(Hero* myHero)//领取奖励；
{
	int rank=0;
	int rankFlg=0;
	if(NULL == myHero)
		return -1;
	
	string SmyHeroId=myHero->getIdentity();
	
	map<string,ChiefCampWarData_T>::iterator iter;	
	char* pName = myHero->getGuildName();//获取帮派的名字;
	if(NULL == pName)
		return -2;
	string currFactionName=pName;//获取帮派的名字;
	
	if(currFactionName == factionAName)
	{
		map<string,int>::iterator rankIter=factionARank.find(SmyHeroId);	
		if(rankIter == factionARank.end())
			return -4;	
		rank=(rankIter->second);
		if(rank >= camp_reward_info[FIRST_CHIEF_REWARD].rank_limit_value)
			rank=camp_reward_info[FIRST_CHIEF_REWARD].rank_limit_value-1;		
		rankFlg=1;
		
		factionARank.erase(rankIter);		
	}else if(currFactionName == factionBName)
	{
		map<string,int>::iterator rankIter=factionBRank.find(SmyHeroId);	
		if(rankIter == factionBRank.end())
			return -4;	
		rank=(rankIter->second);//取到等级；
		if(rank >= camp_reward_info[SECOND_CHIEF_REWARD].rank_limit_value)
			rank=camp_reward_info[SECOND_CHIEF_REWARD].rank_limit_value-1;	
		rankFlg=2;
		factionBRank.erase(rankIter);//删除领完奖励；
	}else if(currFactionName == factionCName)
	{	
		map<string,int>::iterator rankIter=factionCRank.find(SmyHeroId);	
		if(rankIter == factionCRank.end())
			return -4;	
		rank=(rankIter->second);//取到等级；
		if(rank >= camp_reward_info[THIRD_CHIEF_REWARD].rank_limit_value)
			rank=camp_reward_info[THIRD_CHIEF_REWARD].rank_limit_value-1;
			
		rankFlg=3;
		factionCRank.erase(rankIter);//删除领完奖励；
	}else
	{
		return -2;
	}	
	
	if(rankFlg <= 0 || rankFlg > 3)
		return -2;
		
	
	//帮派经验
	addGuildExp(const_cast<char*>(currFactionName.c_str()),myHero->getIdentity(),\
					camp_reward_info[rankFlg+2].guidExp_base_value-camp_reward_info[rankFlg+2].guidExp_dec_value*rank);
	//个人金钱
	if(myHero->getMoney() == NULL)
		return -3;
	increaseBoundGameMoney(myHero,camp_reward_info[rankFlg+2].gold_base_value-camp_reward_info[rankFlg+2].gold_dec_value*rank);
	
	//帮派贡献
	addMyGuildGlory(const_cast<char*>(currFactionName.c_str()),myHero->getIdentity(),\
					camp_reward_info[rankFlg+2].prestige_base_value-camp_reward_info[rankFlg+2].prestige_dec_value*rank);	
	
	//声望 
	myHero->addPrestigeValue(camp_reward_info[rankFlg+2].guidGlory_base_value-camp_reward_info[rankFlg+2].guidGlory_dec_value*rank);
	
	if(SmyHeroId == chiefHeroId)
			myHero->addTitle(CAMP_CHIEF_TITLE);
	return 0;
}


bool
ChiefCampWar::sendMsgStartPK(time_t _last_time)
{
	//生成正式开启PK消息；群发给所有参赛帮派；
	sprintf(chief_camp_msg,"11,20,%s,%d,%d,%s,%d,%d,%s,%d,%d",factionAName.c_str(),curr_factionA_counts,num_factionA_leader_deaths,\
																	factionBName.c_str(),curr_factionB_counts,num_factionB_leader_deaths,\
																	factionCName.c_str(),curr_factionC_counts,num_factionC_leader_deaths);				
	//生成刷新自己死亡次数消息；
	char initTime[50]={0};
	sprintf(initTime,"11,22,0,%lu",_last_time);
	
	int len=strlen(chief_camp_msg);
	for(map<string,ChiefCampWarData_T>::iterator iterFaction=factionA.begin();iterFaction != factionA.end();iterFaction++)
	{//帮派A消息转发；
		map<string,Hero*>::iterator iter=heroId_to_pHero.find(iterFaction->first);
		if(iter!=heroId_to_pHero.end()&& strstr(iter->second->getMapId(),(mapTypeInfo.campWarMapId).c_str()))
		{
			iter->second->setCampWarStartMark(true);
			send_msg(iter->second->getFd(),chief_camp_msg);
			if(_last_time > 0)
			{
				send_msg(iter->second->getFd(),initTime);
			}
		}		
	}
	

	for(map<string,ChiefCampWarData_T>::iterator iterFaction=factionB.begin();iterFaction != factionB.end();iterFaction++)
	{//帮派B消息转发；
		map<string,Hero*>::iterator iter=heroId_to_pHero.find(iterFaction->first);
		if(iter!=heroId_to_pHero.end() && strstr(iter->second->getMapId(),(mapTypeInfo.campWarMapId).c_str()))
		{
			iter->second->setCampWarStartMark(true);
			send_msg(iter->second->getFd(),chief_camp_msg);
			if(_last_time > 0)
			{
				send_msg(iter->second->getFd(),initTime);
			}
		}		
	
	}
	
	for(map<string,ChiefCampWarData_T>::iterator iterFaction=factionC.begin();iterFaction != factionC.end();iterFaction++)
	{//帮派C消息转发；
		map<string,Hero*>::iterator iter=heroId_to_pHero.find(iterFaction->first);
		if(iter!=heroId_to_pHero.end()&& strstr(iter->second->getMapId(),(mapTypeInfo.campWarMapId).c_str()))
		{
			iter->second->setCampWarStartMark(true);
			send_msg(iter->second->getFd(),chief_camp_msg);
			if(_last_time > 0)
			{
				send_msg(iter->second->getFd(),initTime);
			}
		}		
	
	}
	
	if(_last_time > 0)//如果是第一次触发；
	{
		int size_a=factionA.size();
		int size_b=factionB.size();
		int size_c=factionC.size();	
		
		if(size_a==0 && size_b == 0||size_a==0 && size_c == 0||size_b==0 && size_c == 0)
		{
			finishChiefCampWar();
			return false;
		}
		
		ChiefCampWarStartTime=time(NULL);//盟主阵营战开始时间		
		ChiefCampWarEndTime=ChiefCampWarStartTime+_last_time;//盟主阵营战结束时间；
		
		if(NULL == chief_campWar_timer)//启动计时器
			chief_campWar_timer = new ev_timer;
		ext_ev_timer_init(chief_campWar_timer,ChiefCampWarFinishCall,_last_time,0,this);
		ev_timer_start(loops,chief_campWar_timer); 
	}
	
	return true;
}

bool
ChiefCampWar::setChiefHeroId(char *p_hero_id)//设置武林盟主角色Id；
{
	if(p_hero_id == NULL)
		return false;
	chiefHeroId = p_hero_id;
	return true;
}

bool 
ChiefCampWar::setChampion(char * _Champion)//设置战斗统领帮派
{
	if(_Champion == NULL)
		return false;
	Champion = _Champion;
	return true;
}

