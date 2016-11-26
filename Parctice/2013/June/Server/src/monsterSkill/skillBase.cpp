/************************************************************
	文件名：skillBase.cpp
	文件作用：实现SkillBase（Boss技能基类）类的属性和成员
	作者：chenzhen
	创建日期：2012.07.13
************************************************************/
#include"skillBase.h"
#include"monsterBase.h"
#include"cpyAsist.h"
#include"hero.h"
extern map<string,SkillBase*> monSkiInst;  
extern map<string, Hero*> heroId_to_pHero;
extern struct ev_loop *loops;
SkillBase::SkillBase(char *_name,char *_id,int _rank,double _relPer,\
					double _angVal,double _cdTime,double _playCd,\
					double _hrtRatio,bool _lastSki)
{
	memset(name,'\0',sizeof(name));
	memset(id,'\0',sizeof(id));	
	memset(typeId,'\0',sizeof(typeId));	
	
	strncpy(name,_name,strlen(_name));
	strncpy(id,_id,strlen(_id));	
	
	rank = _rank;
	relPer = _relPer;
	angVal = _angVal;	
	cdTime = _cdTime;
	hrtRatio = _hrtRatio;
	lastSki = _lastSki;	
	
	playCd = _playCd;
	
	isOverTme = true;
}

/*初始化技能类型id*/
void SkillBase::initTypeId(void)
{
	char strNum[SHOR_MID_VALUE_LENGTH + 1] = {'\0'}; 
	char midVal[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	if(!dealSerNumStr(id,midVal,strNum))
	{
		cout<<"the skill id is error:"<<id<<endl;
		return;
	}	
	memset(strNum,'\0',sizeof(strNum));
	strncpy(strNum,midVal + strlen(midVal) - 2,2);
	if(atoi(strNum) == 0)
	{
		strncpy(typeId,midVal,strlen(midVal));
	}
	else
	{
		strncpy(typeId,midVal,strlen(midVal) - 2);
	}
}

/*获得技能名称*/
char* SkillBase::getName(void)
{
	return name;
}

/*初始化此技能宿主*/
void SkillBase::initOwner(MonsterBase *monster)
{
	owner = monster;
}

/*获得此技能宿主*/
MonsterBase* SkillBase::getOwner(void)
{
	return owner;
}

/*获得技能id*/
char* SkillBase::getId(void)
{
	return id;
}

/*获得技能使用等级*/
int SkillBase::getRank(void)
{
	return rank;
}

/*获得技能触发频率*/
double SkillBase::getRelPer(void)
{	
	return relPer;
}

/*获得技能触发所需怒气值*/
double SkillBase::getAngVal(void)
{
	return angVal;
}

/*获得技能cd时间*/
double SkillBase::getCdTme(void)
{
	return cdTime;
}

/*判断技能触发频率是否满足*/
bool SkillBase::judgeRelPer(void)
{
	srand ( time(NULL) );
	int randNum = rand()%100;
	int result = relPer * 100;
	if(randNum <= result)
	{
		return true;
	}
	return false;
}

/*判断技能触发怒气值是否满足*/
bool SkillBase::judgeAngVal(void)
{
	/*判断宿主是否已死*/
	if(owner == NULL)
	{
		return false;
	}
	
	/*判断宿主怒气值是否达标*/
	if(owner->getAngVal() >= getAngVal())
	{
		return true;
	}
	return false;
}

/*获得技能id*/
char* SkillBase::getIdentity(void)
{
	return getId();
}

/*判断是否为延迟性技能*/
bool SkillBase::getLastSki(void)
{
	return lastSki;
}

/*宿主死亡时调用*/
void SkillBase::ownerDie(void)
{
	stopTme();
}

/*发送消息，单发*/
void SkillBase::sendOneMsg(char *_heroId,char *msg_others)
{
	if(_heroId == NULL || msg_others == NULL || strlen(msg_others) == 0)
	{
		return;
	}
	
	map<string,Hero*>::iterator hero_it;		
	hero_it = heroId_to_pHero.find(_heroId);
    if(hero_it != heroId_to_pHero.end())
    {
		send_msg(hero_it->second->getFd(),msg_others);			
    }
	memset(msg_others,'\0',strlen(msg_others));
}	

/*发送技能使用后消息（群发）*/
void SkillBase::sendMsgNineBox(char *msg_others)
{
	StyObj obj(owner->getIdentity(),MONSTER_STYLE_TYPE);
	Map_Inform *map_now;
	Nbox *box;
	map_now = owner->getMap();
	if(map_now == NULL || msg_others == NULL || strlen(msg_others) == 0)
	{
		return;
	}
	
	box = map_now->getBox();	
	if(box == NULL)
	{
		return;
	}		
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(msg_others);
}

/*析构函数*/
SkillBase::~SkillBase(void)
{
	if(owner != NULL)
	{
		owner = NULL;
	}
	stopTme();
}

/*获得技能伤害系数*/
double SkillBase::getHrtRatio(void)
{
	return hrtRatio;
}

/*使用技能*/
bool SkillBase::useSkill(vector<string> &herId,bool _station)
{
	char msg_others[MONSTER_ROAD_LENGTH + 1] = {'\0'};
	
	/*为了定身时调用，不用检查条件*/
	if(_station || !isOverTme || herId.empty())
	{
		cout<<"the cd or the dingshen station:"<<id<<endl;
		return false;
	}
	
	/*判断发生频率*/
	if(!judgeRelPer())
	{
		cout<<"the relPercent is not meet:"<<id<<endl;
		return false;
	}		
	
	/*调用寄主使用技能攻击函数*/
	owner->skiAttHero(msg_others,sizeof(msg_others),herId,typeId,hrtRatio,cdTime);		
	/*消息群发*/
	sendMsgNineBox(msg_others);
	
	initCdAndPlayTmer();
	
	return true;
}

/*拷贝技能实例*/
SkillBase* SkillBase::copySkillInst(MonsterBase *_owner)
{
	char *monId,instId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	if(_owner == NULL)
	{
		return NULL;
	}
	
	monId = _owner->getIdentity();
	strncpy(instId,monId,strlen(monId));
	snprintf(instId + strlen(instId),sizeof(instId) - strlen(instId),"%s%s","_",id);
	SkillBase *newSkillInst;
	newSkillInst = new SkillBase(name,instId,rank,relPer,angVal,cdTime,\
	playCd,hrtRatio,lastSki);
	newSkillInst->initTypeId();
	newSkillInst->initOwner(_owner);
	return newSkillInst;
}

/*暂停计时器*/
void SkillBase::stopTme(void)
{	
	ev_timer_stop(loops,&think_timer);
	isOverTme = true;
}

/*获得技能冷却时间和cd时间是否已过*/
bool SkillBase::getIsOverTme(void)
{
	return isOverTme;
}

/*设置技能冷却时间和cd时间是否已过*/
void SkillBase::setIsOverTme(bool _isOver)
{
	isOverTme = _isOver;
}

/*启动技能cd和播放cd计时器*/
void SkillBase::initCdAndPlayTmer(void)
{
	isOverTme = false;	
	
	if(cdTime >= playCd)
	{	
		ext_ev_timer_init(&think_timer,monCdCalBak,cdTime,0,this);
	}
	else
	{
		ext_ev_timer_init(&think_timer,monCdCalBak,playCd,0,this);
	}
	
	ev_timer_start(loops,&think_timer);	
}
		
	



		
		

	