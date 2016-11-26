#include"rigidity.h"
#include"timerContainer.h"
#include"monsterBase.h"
#include"bossSkiThk.h"
#include"user_role_manage_assist.h"
#include"cpyAsist.h"
extern TimerContainer<SkillBase *> *timerMonSkiRig;
extern struct ev_loop *loops;
extern map<string,SkillBase*> monSkiInst; 
extern map<string, Hero*> heroId_to_pHero;
Rigidity::Rigidity(char *_name,char *_id,int _rank,double _relPer,\
double _angVal,double _cdTime,double _playCd,double _hrtRatio,\
bool _lastSki,double _trigPer,double _lastTime):SkillBase(\
_name,_id,_rank,_relPer,_angVal,_cdTime,_playCd,_hrtRatio,_lastSki)
{
	lastTime = _lastTime;
	trigPer = _trigPer;
	flgThk = false;
}

/*判断生命值是否已经达到额外触发条件*/
bool Rigidity::judgeLifePer(void)
{
	int lifeUpperVal;
	int lifeVal;
	lifeUpperVal = owner->getLifeUpperVal();
	lifeVal = owner->getLifeVal();
	if(1.0 * lifeVal/lifeUpperVal <= trigPer)
	{
		return true;
	}
	return false;
}

/*定身功能*/
bool Rigidity::standStill(vector<string> &heroId)
{
	char msg_others[MONSTER_ROAD_LENGTH + 1] = {'\0'};
	
	/*为了定身时调用，不用检查条件*/
	if(!isOverTme || heroId.empty())
	{
		cout<<"in cd time or the herId is empty:"<<id<<endl;
		return false;
	}
		
	/*血值触发，判断发生频率*/
	if(!judgeLifePer() && !judgeRelPer())
	{
		cout<<"the  the relPercent is not meet:"<<id<<endl;
		return false;
	}
		
	insertHerId(heroId);
		
	/*调用寄主使用技能攻击函数*/
	owner->skiAttHero(msg_others,sizeof(msg_others),heroId,typeId,hrtRatio,cdTime);

	/*启动技能冷却和播放时间定时器*/
	initCdAndPlayTmer();
	
	/*消息群发*/
	sendMsgNineBox(msg_others);	
	
	if(!flgThk)
	{
		initTimer();
	}		
	
	return true;	
}
		
/*拷贝技能实例*/
SkillBase* Rigidity::copySkillInst(MonsterBase *_owner)
{
	char *monId,instId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	
	if(_owner == NULL)
	{
		return NULL;
	}
	
	monId = _owner->getIdentity();
	snprintf(instId + strlen(instId),sizeof(instId),"%s%s%s",monId,"_",id);	
	SkillBase *newSkillInst;
	newSkillInst = new Rigidity(name,instId,rank,relPer,angVal,\
	cdTime,playCd,hrtRatio,lastSki,trigPer,lastTime);
	
	newSkillInst->initOwner(_owner);
	newSkillInst->initTypeId();
	return newSkillInst;
}

/*计时器初始化函数*/
void Rigidity::initTimer(void)
{
	flgThk = true;	
	ext_ev_timer_init(&think_timer,monSkiCalBak,lastTime,0,this);
	ev_timer_start(loops,&think_timer);		
}

/*放入那些被技能击中者id*/
void Rigidity::insertHerId(vector<string> &heroId)
{
	char msg_still[MONSTER_ROAD_LENGTH + 1] = {'\0'};	
	int i,length;
	set<string> herSet;
	length = heroId.size();
	for(i = 0;i < length;i++)
	{		
		memset(msg_still,'\0',sizeof(msg_still));
		
		/*修改人物标记值属性*/
		if(!setHerStiFlg(heroId[i],true))
		{
			continue;
		}
		herSet.insert(heroId[i]);			
		formMsg(msg_still,sizeof(msg_still),const_cast<char *>((heroId[i]).c_str()));
		sendOneMsg(const_cast<char *>((heroId[i]).c_str()),msg_still);
	}
	skiTme.input(herSet);
}

/*计时器暂停函数*/
void Rigidity::stopThk(void)
{
	ev_timer_stop(loops,&think_timer);
	flgThk = false;
}

/*技能持续时间到，则清掉玩家id*/			
bool Rigidity::delHerId(void)
{	
	set<string>::iterator herSet_it;
	set<string> herSet;
	string herId;
	skiTme.output(herSet);
	
	if(herSet.empty())
	{
		return false;
	}
	
	for(herSet_it = herSet.begin();herSet_it != herSet.end();herSet_it++)
	{
		herId = *herSet_it;
		setHerStiFlg(herId,false);			
	}
	
	if(skiTme.isEmpty())
	{
		return false;
	}
	
	return true;
}

/*计时器响应函数*/
bool Rigidity::response(void)
{
	delHerId();
	return true;
}

/*获得技能持续时间*/
double Rigidity::getLastTme(void)
{
	return lastTime;
}

/*使用技能*/
bool Rigidity::useSkill(vector<string> &herId,bool _station)
{
	return standStill(herId);  //注意：消息还没有生成
}

/*生成相应消息*/
void Rigidity::formMsg(char *msg_others,int lengthStr,char *_heroId)
{	
	if(msg_others == NULL || _heroId == NULL || lengthStr <= 0)
	{
		cout<<"the skill msg is error:"<<id<<endl;
		return;
	}
	snprintf(msg_others + strlen(msg_others),lengthStr - strlen(msg_others),"%d%s%d%s%s%s%s%s%d%s%s%s%d%s%f%s%d",\
			MONSTER_SKILL_HEAD,",",MONSTER_SKILL_SINGLE,",",owner->getIdentity(),\
			",",typeId,",",HIT_TYPE_HERO,",",_heroId,",",STAND_STILL_FUNCTION,\
			",",lastTime,",",0);
}

/*析构函数*/
Rigidity::~Rigidity(void)
{	
	stopThk();	
	skiTme.init();
}

/*设置被定身玩家定时标记值属性,true为被定身*/
bool Rigidity::setHerStiFlg(string &heroId,bool _flg)
{
	map<string,Hero*>::iterator hero_it;
	hero_it = heroId_to_pHero.find(heroId);
	if(hero_it == heroId_to_pHero.end())
	{
		return false;
	}
	if(hero_it->second->getStillFlg() == _flg)
	{
		return false;
	}
	hero_it->second->setStillFlg(_flg);
	
	/*定身，不许移动*/
	if(hero_it->second->getStillFlg())
	{
		hero_it->second->stopMove();
	}
	
	return true;
}
	
/*获得定身类型*/
int Rigidity::getStillType(char *_SkillId)
{ 
	string _skillId = _SkillId;
	
	if(_skillId.find("delMethod") != string::npos)
	{
		return DELUDE;
	}
	else if(_skillId.find("tightEncir") != string::npos)
	{
		return TIGHT_ENCIRCLE;
	}
	else if(_skillId.find("proArms") != string::npos)
	{
		return FIST;
	}
	return -1;
}


/*宿主死亡时调用*/
void Rigidity::ownerDie(void)
{
	stopThk();
	SkillBase::ownerDie();
}
