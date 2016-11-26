#include"trap.h"
#include"map_inform.h"
#include"hero.h"
#include"otherThingCalBack.h"

extern map<string,Hero*>heroId_to_pHero;
extern struct ev_loop *loops;
Trap::Trap(char *_typeId,double _attack,int _attackRge,int _attStyle,double _cdTme,bool _isWarning,double _waringTime,char *_name,char *_photoId)
{	
	memset(typeId,'\0',sizeof(typeId));
	memset(id,'\0',sizeof(id));
	memset(photoId,'\0',sizeof(photoId));
	memset(name,'\0',sizeof(name));
	
	memset(bornMsg,'\0',sizeof(bornMsg));
	memset(outMsg,'\0',sizeof(outMsg));
	memset(attMsg,'\0',sizeof(attMsg));
	
	strncpy(typeId,_typeId,strlen(_typeId));
	strncpy(name,_name,strlen(_name));
	strncpy(photoId,_photoId,strlen(_photoId));

	attPercent = _attack;	
	attackRge = _attackRge;
	cdTme = _cdTme;
	cdPlay = 4;
	isAtt = false;
	playCtn = 0;
	attStyle = _attStyle;
	isDispear = false;
	isWarned = false;
	isWarning = _isWarning;
	warnTime = _waringTime;
	memset(warningMsg,'\0',sizeof(warningMsg));
	isCalled = false;
	isUsed = false;
	isMove = false;
}

/*生成刷出信息*/
void Trap::formBornMsg(void)
{
	memset(bornMsg,'\0',sizeof(bornMsg));
	
	snprintf(bornMsg,sizeof(bornMsg),"%d%s%d%s%d%s%s%s%s",\
			2,",",9,",",TYPETRAP,",",id,",",name);

	snprintf(bornMsg + strlen(bornMsg),sizeof(bornMsg) - strlen(bornMsg),"%s%d%s%d%s%d%s%s",\
			",",pt._x,",",pt._y,",",0,",",photoId);
}

/*获得id*/
char* Trap::getId(void)
{
	return id;
}

/*生成下线信息*/
void Trap::formOutMsg(void)
{
	memset(outMsg,'\0',OUT_VIEW_LENGTH + 1);
	
	snprintf(outMsg,sizeof(outMsg),"%d,%d,%s,%d",2,5,id,1);
}

/*获得玩家实例指针*/
Hero* Trap::getHero(char *heroId)
{
    map<string,Hero*>::iterator hero_it;
    hero_it = heroId_to_pHero.find(heroId);
    if(hero_it == heroId_to_pHero.end())
    {
        return	NULL;
    }
    return hero_it->second;
}

/*设置地图实例指针*/
void Trap::setMap(Map_Inform *_map_now)
{
	if(_map_now != NULL)
	{
		map_now = _map_now;
	}
	
	if(map_now != NULL)
	{
		logicPt = MapExchangeLogical(pt);
		logicPt._y += map_now->getBaseDigst();
	}
}

/*获得逻辑坐标点*/
Point Trap::getLogicPt(void)
{
    return logicPt;
}

/*复制陷阱*/
Trap* Trap::copyTrap(char *_mapId)
{

	char newIntId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};     //在新地图上的id
	Trap* newTrap;
	
	if(_mapId == NULL)
	{
		return NULL;
	}
	
	/* 追加地图id，为了保证副本道具id的唯一性*/
	
	strncpy(newIntId,_mapId,strlen(_mapId));
	
	strncat(newIntId,"_",strlen("_"));
	
	strncat(newIntId,id,strlen(id));	
	
	
	newTrap = new Trap(typeId,attPercent,attackRge,attStyle,cdTme,isWarning,warnTime,name,photoId);
	
	newTrap->setPiexPt(pt);
	
	newTrap->setInstId(newIntId);
	
	newTrap->formBornMsg();
	
	newTrap->formOutMsg();	
	
	newTrap->formWarnMsg();
	
	newTrap->setIsCalled(isCalled);
	
	return newTrap;
}

/*复制陷阱<重载函数，在读取地图配置文件里面用>*/
Trap* Trap::copyTrap(Point _pt,bool _isCalled)
{
	char _id[MONSTER_MID_LENGTH + 1] = {'\0'};	
	
	Trap* newTrap;	
	
	newTrap = new Trap(typeId,attPercent,attackRge,attStyle,cdTme,isWarning,warnTime,name,photoId);
						
	strncpy(_id,typeId,strlen(typeId));
	
	strncat(_id,"_",strlen("_"));	

	count++;
	
	appendNum(_id,count,4);		
	
	newTrap->setPiexPt(_pt);
	
	newTrap->setInstId(_id);
	
	newTrap->formBornMsg();
	
	newTrap->formOutMsg();	
	
	newTrap->formWarnMsg();
	
	newTrap->setIsCalled(_isCalled);
	
	return newTrap;
}

/*设置像素坐标*/
void Trap::setPiexPt(Point _pt,bool flag)
{
	pt = _pt;
	
	if(flag && map_now != NULL)
	{
		logicPt = MapExchangeLogical(pt);
		logicPt._y += map_now->getBaseDigst();
	}
}

/*获得陷阱的实例id*/
char* Trap::getTrapId(void)
{
	return id;
}

/*设置实例id*/
void Trap::setInstId(char *_id)
{
	if(_id == NULL || strlen(_id) == 0)
	{
		cout<<"the trap id is error:"<<endl;
		return;
	}
	memset(id,'\0',sizeof(id));	
	strncpy(id,_id,strlen(_id));	
}

/*刷出陷阱*/
void Trap::brushMsg(void)
{
	StyObj obj(id,TRAP_STYLE_TYPE);
	
	Nbox *box;            
	                   
	box = map_now->getBox();
	
	if(box == NULL)
	{
		return;
	}
	
	map_now->insertID(obj);
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(bornMsg);
	
	isUsed = true;
	
}

/*陷阱从地图消亡*/
void Trap::disperMsg(void)
{
	StyObj obj(id,TRAP_STYLE_TYPE);
	
	Nbox *box;          
	                   
	box = map_now->getBox();
	
	if(box == NULL)
	{
		return;
	}
	
	box->getStaInSrcVec(obj);	
	
	box->sentBoxMsg(outMsg);
	
	map_now->deleteID(obj);
	
	initTrap();
}

Trap::~Trap(void)
{
	ev_timer_stop(loops,&think_timer);
	memset(typeId,'\0',sizeof(typeId));
	memset(id,'\0',sizeof(id));
	memset(photoId,'\0',sizeof(photoId));
	memset(name,'\0',sizeof(name));
	
	memset(bornMsg,'\0',sizeof(bornMsg));
	memset(outMsg,'\0',sizeof(outMsg));
	memset(attMsg,'\0',sizeof(attMsg));
	
	map_now = NULL;		
}

/*获得陷阱的攻击力*/
double Trap::getAttack(void)
{
	return attPercent;
}

/*获得陷阱的攻击距离*/
int Trap::getAttackRge(void)
{
	return attackRge;
}

/*获得陷阱的折算成地图思考次数*/
double Trap::getCdTme(void)
{
	return cdTme;
}


/*获得上线消息*/
char* Trap::getBronMsg(void)
{
	return bornMsg;
}

/*攻击人物,如果是要消失的陷阱，则返回真*/
bool Trap::AttackPerson(void)
{	
	StyObj obj(id,TRAP_STYLE_TYPE);	
	char midVal[TRAP_ATT_LENGTH + 1] = {'\0'};
	char attId[] = {"000"};
	int person,magicVal,attPow;
	Hero *myHero;
	Nbox *box;
	set<string>HeroIdSet;
	set<string>::iterator her_it;
	Point heroPt;
	memset(attMsg,'\0',sizeof(attMsg));
	magicVal = 0;
	
	box = map_now->getBox();
	
#if 0	
	if(box == NULL || !isPlayCd())
	{
		return false;
	}
	
#endif

	if(box == NULL)
	{
		return false;
	}
	
	box->getStaInSrcVec(obj);	
	
	box->getCentPtSrcHerIdSet(pt,HeroIdSet);
	
	snprintf(attMsg,sizeof(attMsg),"%d,%d,%d,%s,%d,%s,%d,%d,%d,%d,%d,%d",\
	FIGHT_FRIST_HEAD,FIGHT_SECOND_HEAD,SUCCESS,\
	attId,cdPlay,id,1,1,1,1,0,0);
	
#if 0
	snprintf(attMsg,sizeof(attMsg),"%d,%d,%d,%s,%d,%s,%d,%d,%d,%d",\
	FIGHT_FRIST_HEAD,FIGHT_SECOND_HEAD,SUCCESS,\
	attId,cdPlay,id,1,1,0,0);
#endif			
	person = 0;
	for(her_it = HeroIdSet.begin(); her_it != HeroIdSet.end() && person < 15; ++her_it)
    {		
		myHero = heroid_to_hero(*her_it);
	
        if(myHero == NULL || myHero->getLifeStation() == DEAD)
        {
            continue;
        }
		
		/*人物处于无敌状态,add by chenzhen 20130128*/
		if(myHero->skillBuffState & BUFF_INVINCIBLE_STATE)
		{
			continue;
		}
		
		heroPt = myHero->getLocation();
		
		if(sqrt(pow(fabs(heroPt._x - pt._x),2)+pow(fabs(heroPt._y - pt._y),2)) > attackRge)
		{
			continue;
		}
		
		attPow = getAttackPow(myHero->getLifeUpperVal());
		
		//矫正伤害值
		attPow = judgeAttackPersonDie(myHero,attPow);	
		
			
		/*无暴击，无闪避*/
		snprintf(midVal + strlen(midVal),sizeof(midVal) - strlen(midVal),\
		",%s,%d,%d,%d,%d,%d,%d",myHero->getIdentity(),myHero->getLifeVal(),myHero->getLifeUpperVal(),\
		myHero->getMagicVal(),myHero->getMagicUpperVal(),attPow,0);
		
#if 0
		/*无暴击，无闪避*/
		snprintf(midVal + strlen(midVal),sizeof(midVal) - strlen(midVal),\
		",%s,%d,%d,%d",myHero->getIdentity(),myHero->getLifeVal(),attPow,0);		
#endif		
		person++;		
	}	
	
	if(person == 0)
	{
		/*没有预警*/
		if(!isWarned)
		{
			/*没人就不触发攻击*/
			if(attStyle == 1 || attStyle == 2)
			{
				return false;
			}
		}
		else
		{
			isWarned = false;						
		}
		snprintf(attMsg + strlen(attMsg),sizeof(attMsg) - strlen(attMsg),",%d,%d",0,person);
	}
	else
	{
		snprintf(attMsg + strlen(attMsg),sizeof(attMsg) - strlen(attMsg),",%d,%d",0,person);
		strncat(attMsg,midVal,strlen(midVal));
		
		playCtn = 0;
		isAtt = true;
	}	
	box->sentBoxMsg(attMsg);
	
	/*触发后就消失(包括召唤出来的陷阱）*/
	if(attStyle == 1 || attStyle == 3 || isCalled)
	{
		isDispear = true;  
		return true;
	}
	return false;
}

/*人物掉血处理*/
int Trap::judgeAttackPersonDie(Hero *hitedHero,int attPow)	
{
	if(hitedHero == NULL)
	{
		return 0;
	}
	
	int lifeVal = hitedHero->getLifeVal();
	
	//类似血包技能
	if (hitedHero->skillBuffState & BUFF_MAGIC_SHIELD_STATE)
	{
		int decHurt = hitedHero->skillBuff[hitedHero->getIndexByState(BUFF_MAGIC_SHIELD_STATE)].perVal;
		if (attPow >= decHurt)
		{
			int lastAttack = attPow - decHurt;
			hitedHero->skillBuff[hitedHero->getIndexByState(BUFF_MAGIC_SHIELD_STATE)].perVal = 0;
			int index = hitedHero->getIndexByState(BUFF_MAGIC_SHIELD_STATE);
			hitedHero->stop_buff_debuff_by_index(index);
			if(lifeVal - lastAttack  <= 0)
			{
				hitedHero->setLifeVal(0);
				hitedHero->setLifeStation(DEAD);
				return lastAttack;
			}
			else
			{
				hitedHero->setLifeVal(lifeVal - lastAttack);
				return lastAttack;
			}
		}
		else
		{
			hitedHero->skillBuff[hitedHero->getIndexByState(BUFF_MAGIC_SHIELD_STATE)].perVal -= attPow;
			return 0;
		}
	}

	if(lifeVal - attPow > 0)
	{
		hitedHero->setLifeVal(lifeVal - attPow);
		return attPow;
	}
		
	hitedHero->setLifeVal(0);
	hitedHero->setLifeStation(DEAD);
	return attPow;	
}

/*获得下线消息*/
char* Trap::getOutMsg(void)
{
	return outMsg;
}

/*获得像素坐标*/
Point Trap::getPiexPt(void)
{
	return pt;
}

/*启动思考计时器*/
void Trap::initTimer(void)
{
	ev_timer_stop(loops,&think_timer);
		
	ext_ev_timer_init(&think_timer,trapThkCalBack,cdTme,0, this);

	ev_timer_start(loops,&think_timer);
}

/*启动消失计时器*/
void Trap::initTimerDispear(void)
{
	ev_timer_stop(loops,&think_timer);
		
	ext_ev_timer_init(&think_timer,trapDispearCalBack,2,0, this);

	ev_timer_start(loops,&think_timer);
}


/*暂停计时器*/
void Trap::stopTimer(void)
{
	ev_timer_stop(loops,&warnTimer);
	ev_timer_stop(loops,&think_timer);
}

/*陷阱回调函数*/
bool Trap::calBack(void)
{
	return AttackPerson();
}

/*重置陷阱信息*/
void Trap::initTrap(void)
{
	ev_timer_stop(loops,&think_timer);
	isAtt = false;
	playCtn = 0;
	isDispear = false;
	
	initWarnDispear();
	isUsed = false;
}

/*是否在cd攻击动画中*/
bool Trap::isPlayCd(void)
{
	if(isAtt)
	{
		playCtn++;
		if(playCtn >= cdPlay)
		{
			playCtn = 0;
			isAtt = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}

/*计算攻击力*/
int Trap::getAttackPow(int heroLife)
{
	return attPercent * heroLife;
}

/*获得是否会消失的标记值*/
bool Trap::getIsDispear(void)
{
	return isDispear;
}

/*生成警示消息*/
void Trap::formWarnMsg(void)
{	
	if(isWarning && strlen(warningMsg) == 0)
	{
		sprintf(warningMsg,"26,4,%s",id);
	}
}

/*判断攻击范围内是否有人*/
bool Trap::isAttackPerson(set<string> &HeroIdSet)
{
	set<string>::iterator her_it;
	Hero *myHero;
	for(her_it = HeroIdSet.begin(); her_it != HeroIdSet.end(); ++her_it)
    {		
		myHero = heroid_to_hero(*her_it);
	
        if(myHero == NULL || myHero->getLifeStation() == DEAD)
        {
            continue;
        }
		
		/*人物处于无敌状态,add by chenzhen 20130128*/
		if(myHero->skillBuffState & BUFF_INVINCIBLE_STATE)
		{
			continue;
		}
		
		Point heroPt = myHero->getLocation();
		
		if(sqrt(pow(fabs(heroPt._x - pt._x),2)+pow(fabs(heroPt._y - pt._y),2)) > attackRge)
		{
			continue;
		}
		
		return true;
	}	
	
	return false;
}

/*重置陷阱警示信息*/
void Trap::initWarnDispear(void)
{
	if(isWarning)
	{		
		ev_timer_stop(loops,&warnTimer);
		isWarned = false;
	}
}

/*预警函数*/
bool Trap::warning(void)
{		
	if(isWarning)
	{
		StyObj obj(id,TRAP_STYLE_TYPE);	
		Nbox *box;
		set<string>HeroIdSet;	
		box = map_now->getBox();

		if(box == NULL)
		{
			return false;
		}
	
		box->getStaInSrcVec(obj);		
		box->getCentPtSrcHerIdSet(pt,HeroIdSet);
			
		/*示警*/
		if(isAttackPerson(HeroIdSet))
		{		
			box->sentBoxMsg(warningMsg);	
			ext_ev_timer_init(&warnTimer,trapWarnCalBack,warnTime,0, this);
			ev_timer_start(loops,&warnTimer);	
			isWarned = true;
			return true;
		}
	}
	
	return false;
}

/*设置召唤标记值*/
void Trap::setIsCalled(bool _isCalled)
{
	isCalled = _isCalled;
}

/*获得召唤标记值*/
bool Trap::getIsCalled(void)
{
	return isCalled;
}

/*获得是否被刷出的标记值*/
bool Trap::getIsUsed(void)
{
	return isUsed;
}

/*移动更改坐标*/
void Trap::move(Point piexPt)
{
	if(!isMove)
	{
		return;
	}
	
	StyObj obj(id,TRAP_STYLE_TYPE);	
	Nbox *box;
	set<string>HeroIdSet;	
	box = map_now->getBox();

	if(box == NULL)
	{
		return;
	}
	
	box->getStaInSrcVec(obj);		
	box->getCentPtSrcHerIdSet(pt,HeroIdSet);		
	
	/*有人劈则不移动*/
	if(isAttackPerson(HeroIdSet))
	{
		return;
	}
	
	/*如果新坐标也木有人劈，则不动*/
	box->getCentPtSrcHerIdSet(piexPt,HeroIdSet);
	if(!isAttackPerson(HeroIdSet))	
	{
		cout<<"Trap::move new place have not person:"<<endl;
		return;
	}
	
	setPiexPt(piexPt);
}

/*判断是否可以移动*/
bool Trap::getIsMove(void)
{
	return isMove;
}
	
	
	
	

