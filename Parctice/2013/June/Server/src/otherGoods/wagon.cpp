#include"wagon.h"
#include"hero.h"
#include"nbox.h"
#include"other_define_data.h"
#include"timerContainer.h"
#include"wagonAction.h"
#include"move_asist.h"
extern map<string,Hero*>heroId_to_pHero;
extern map<string,Wagon*> wagonInstMap;
extern TimerContainer<Wagon*> *wagonTimer;
extern struct ev_loop *loops;
Wagon::Wagon(char *_typeId,int _lifeVal,int _hurt,char *_color,char *_name,char *_photoId, float _rewardTimes, bool _haveSpeedGame,
	int _blackSpeed, int _yellowSpeed, int _redSpeed, double _gameLastTime, double _gameCdTime, double _incSpeedTime)
{	
	speed = NORMAL_WAGON_SPEED;
	lastSpeed = NORMAL_WAGON_SPEED;
	memset(photoId,'\0',sizeof(photoId));	
	memset(bornMsg,'\0',sizeof(bornMsg));
	memset(typeId,'\0',sizeof(typeId));
	memset(outMsg,'\0',sizeof(outMsg));	
	memset(color,'\0',sizeof(color));
	memset(name,'\0',sizeof(name));
	memset(id,'\0',sizeof(id));
	memset(ownerId, '\0', sizeof(ownerId));
	strncpy(photoId,_photoId,strlen(_photoId));	
	strncpy(typeId,_typeId,strlen(_typeId));	
	strncpy(color,_color,strlen(_color));	
	strncpy(name,_name,strlen(_name));	
	
	routeClear();

	lifeVal = _lifeVal;	
	lifeUperVal = lifeVal;
	hurt = _hurt;	
	rewardTimes = _rewardTimes;
	haveSpeedGame = _haveSpeedGame;
	blackSpeed = _blackSpeed;
	yellowSpeed  = _yellowSpeed;
	redSpeed = _redSpeed;
	gameLastTime = _gameLastTime;
	gameCdTime = _gameCdTime;
	incSpeedTime = _incSpeedTime;
	
	gameCtlState = 0;
	SpeedUpOnce = false;
	
	bruOut = false;
	mapNow = NULL;
}

/*生成刷出信息*/
void Wagon::formBornMsg(void)
{
	memset(bornMsg,'\0',IN_VIEW_LENGTH + 1);
	
	snprintf(bornMsg,sizeof(bornMsg),"%d%s%d%s%d%s%s%s%s",\
			2,",",9,",",TYPEWAGON,",",id,",",name);
	
	snprintf(bornMsg + strlen(bornMsg),sizeof(bornMsg)- strlen(bornMsg),"%s%d%s%d%s%d%s%d%s%s",\
			",",pt._x,",",pt._y,",",lifeUperVal,\
			",",lifeVal,",",photoId);
	
	if (getHero(ownerId) == NULL)
	// if (owner == NULL)
	{
		snprintf(bornMsg + strlen(bornMsg),sizeof(bornMsg)- strlen(bornMsg),"%s%s",",","noOwner");
	}
	else
	{
		snprintf(bornMsg + strlen(bornMsg),sizeof(bornMsg)- strlen(bornMsg),\
				"%s%s",",",ownerId);
	}
}

/*获得id*/
char* Wagon::getId(void)
{
	return id;
}

/*生成下线信息*/
void Wagon::formOutMsg(void)
{
	memset(outMsg,'\0',sizeof(outMsg));
	
	snprintf(outMsg,sizeof(outMsg),"%d%s%d%s%s%s%d",2,",",5,",",id,",",1);
}

/*获得玩家实例指针*/
Hero* Wagon::getHero(char *heroId)
{
    map<string,Hero*>::iterator hero_it;
    hero_it = heroId_to_pHero.find(heroId);
    if(hero_it == heroId_to_pHero.end())
    {
        return	NULL;
    }
    return hero_it->second;
}

/*设置马车主人实例指针*/
bool Wagon::setOwnerId(char* _ownerId, Hero *owner)
{
	if (owner == NULL || _ownerId == NULL || strlen(_ownerId) == 0)
	{
		cout<<"get error args when set wagon owner"<<endl;
		return false;
	}
	if (strlen(ownerId) != 0)
	{
		if (strcmp(ownerId, _ownerId) == 0)
		{
			owner->setSpeed(NORMAL_WAGON_SPEED);
			gameCtlState = 1;
			startSpeedGameCtlTimer(1);
			return true;
		} else {
			return false;
		}
	} else {
		if (strcmp(_ownerId, owner->getIdentity()) != 0)
		{
			cout<<"Oh, fuck is the fuck! who can make this happen!"<<endl;
			return false;
		} else {
			strncpy(ownerId, _ownerId, sizeof(ownerId));
			owner->setSpeed(NORMAL_WAGON_SPEED);
			gameCtlState = 1;
			startSpeedGameCtlTimer();
			return true;
			
		}
	}
}

//马车和主人脱离
void Wagon::divorceWithOwner(void)
{
	if (strlen(ownerId) == 0)
	{
		return;
	}
	Hero *owner = getOwner();
	if (owner == NULL)
	{
		return;
	}
	// stopSpeedGameCtlTimer();
	
	int heroSpeed = NORMAL_HERO_SPEED;
	if (owner->getRide()->ifFull())
	{
		heroSpeed += owner->getRide()->getMove();
	}
	owner->setSpeed(heroSpeed);
	
	mapNow = owner->getMap();
	// stopMoveTimer();
}

/*领出马车*/
void Wagon::dirveWagon(char* _ownerId)
{
	/*设置马车主人*/
	Hero *owner = getHero(_ownerId);
	if (owner == NULL)
	{
		cout<<"if this happen, must someboby also driveWagon and give an error arg of ownerId!"<<endl;
		return;
	}
	if(!setOwnerId(_ownerId, owner))
	{
		cout<<"this wouldn't happenned"<<endl;
		return;
	}
	
	initTimer();
	mapNow = owner->getMap();
	/*设置马车坐标*/
	pt = owner->getLocation();
	// logicPt = owner->getLogPt();
	startMoveTimer();
	/*刷出马车信息*/
	brushMsg();
	
}

/*修改逻辑坐标时，也对应的修改了其像素坐标,匹配客户端的心跳*/
void Wagon::setLogicPt(Point _logPt)
{
	if (strlen(ownerId) == 0)
	{
		return;
	}
    logicPt = _logPt;
	Hero *owner = getOwner();
	if (owner == NULL)
	{
		return;
	}
	mapNow = owner->getMap();
    _logPt._y -= mapNow->getBaseDigst();
    pt = LogicalExchangeMap(_logPt);
	routeClear();
	currPt = endPt = pt;
}

/*修改像素坐标时，也对应的修改了其逻辑坐标,匹配客户端的心跳*/
void Wagon::setLocation(Point _pt, int flag)  
{
	if (strlen(ownerId) == 0)
	{
		return;
	}
	Hero *owner = getOwner();
	if (owner == NULL)
	{
		return;
	}
	if (flag == 0)
	{
		if (getRouteSize() == 0)
		{
			routeClear();
		}
		currPt = endPt = _pt;
	}
    pt._x = _pt._x;
    pt._y = _pt._y;
	
	mapNow = owner->getMap();
    // logicPt = MapExchangeLogical(pt);
    // logicPt._y += mapNow->getBaseDigst();
}

/*获得逻辑坐标点*/
Point Wagon::getLogicPt(void)
{
    return logicPt;
}

/*获得像素坐标点*/
Point Wagon::getPt(void)
{
    return pt;
}

/*当主人切换地图时*/
void Wagon::ownerChageMap(void)
{	
	/*设置马车坐标*/
	if (strlen(ownerId) == 0)
	{
		return;
	}
	Hero *owner = getOwner();
	mapNow = owner->getMap();
	pt = owner->getLocation();
	// logicPt = owner->getLogPt();
	
	/*刷出马车信息*/
	brushMsg();	
}

/*复制马车*/
Wagon* Wagon::copyWagon(void)
{
	Wagon* newWagon;
	
	char *uuId,_id[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};		
	newWagon = new Wagon(typeId,lifeVal,hurt,color,name,photoId, rewardTimes, haveSpeedGame, blackSpeed, yellowSpeed, redSpeed, gameLastTime, gameCdTime, incSpeedTime);
	
	uuId = cid();
	
	strncpy(_id,uuId,strlen(uuId));
	free(uuId);
	
	// cidOtherWay(_id,sizeof(_id));
	
	// strncpy(_id,typeId,strlen(typeId));
	
	// strncat(_id,"_",strlen("_"));	
	
	// count++;
	
	// appendNum(_id,count,4);
	cout<<"wagonUUiD:"<<_id<<endl;
	newWagon->setInstId(_id);
	
	wagonInstMap[_id] = newWagon;
	
	return newWagon;
}

/*获得摘取物品id*/
char* Wagon::getWagonId(void)
{
	return id;
}

/*设置实例id*/
void Wagon::setInstId(char *_id)
{
	if(_id == NULL || strlen(_id) == 0)
	{
		return;
	}
	memset(id,'\0',sizeof(id));
	strncpy(id,_id,strlen(_id));
}

/*刷出马车*/
void Wagon::brushMsg(void)
{
	StyObj obj(id,WAGON_STYLE_TYPE);
	Nbox *box;
	if (strlen(ownerId) == 0)
	{
		return;
	}
	
	Hero* owner = getOwner();
	if (owner != NULL)
	{
		mapNow = owner->getMap();  
	}
	  
	if (mapNow == NULL)
	{
		return;
	}
	box = mapNow->getBox();
	
	if(box == NULL)
	{
		return;
	}
	formBornMsg();   
	
	mapNow->insertID(obj);
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(bornMsg);
}

/*马车从地图消亡*/
void Wagon::disperMsg(void)
{
	StyObj obj(id,WAGON_STYLE_TYPE);
	
	Nbox *box;
	
	Hero *owner = getOwner();
	
	if (owner != NULL)
	{
		mapNow = owner->getMap();
	}
	if(mapNow == NULL)
	{
		return;
	}
	formOutMsg();  
	
	box = mapNow->getBox();		
	if(box == NULL)
	{
		return;
	}
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(outMsg);
	cout<<"outMsg:"<<outMsg<<endl;
	mapNow->deleteID(obj);
	
	
}

//马车被攻击，返回马车是否还活着
bool Wagon::beAttacked(void)
{
	if (lifeVal == 0)
	{
		return false;
	}
	
	lifeVal -= hurt;
	
	cout<<"lifeVal:"<<lifeVal<<endl;
	cout<<"hurt:"<<hurt<<endl;
	
	if (lifeVal <= 0)
	{
		lifeVal = 0;
		return false;
		
	} else {
		return true;
	}
}

/*设置马车的生命值*/
void Wagon::setLifeVal(int _lifeVal)
{
	lifeVal = _lifeVal;
}
//获取马车当前血量
int Wagon::getLifeVal(void)
{
	return lifeVal;
}

//获取每次攻击伤害
int Wagon::getHurt(void)
{
	return hurt;
}

//获取马车主人
Hero* Wagon::getOwner(void)
{
	map<string,Hero*>::iterator hero_it;
    hero_it = heroId_to_pHero.find(ownerId);
    if(hero_it == heroId_to_pHero.end())
    {
        return	NULL;
    }
    return hero_it->second;
}


//马车主人ID
char* Wagon::getOwnerId(void)
{
	return ownerId;
}

//获取上线消息
char* Wagon::getOnlineMsg(void)
{
	return bornMsg;
}
//获取下线消息
char* Wagon::getOfflineMsg(void)
{
	return outMsg;
}

Wagon::~Wagon(void)
{
	stopMoveTimer();
	stopSpeedGameCtlTimer();
	
	Hero *owner = getOwner();
	if (owner != NULL)
	{
		int heroSpeed = NORMAL_HERO_SPEED;
		if (owner->getRide()->ifFull())
		{
			heroSpeed += owner->getRide()->getMove();
		}
		owner->setSpeed(heroSpeed);
		
	}
	ev_timer_stop(loops,&think_timer);
	owner = NULL;
	
	memset(photoId,'\0',sizeof(photoId));	
	memset(bornMsg,'\0',sizeof(bornMsg));
	memset(typeId,'\0',sizeof(typeId));
	memset(outMsg,'\0',sizeof(outMsg));	
	memset(color,'\0',sizeof(color));
	memset(name,'\0',sizeof(name));
	memset(id,'\0',sizeof(id));
	memset(ownerId, '\0', sizeof(ownerId));
}

/*马车场景跳转*/
bool Wagon::enter_scene()
{
	StyObj obj(id,WAGON_STYLE_TYPE);
	
	Nbox *box;	
	
	Hero *owner = getOwner();
	
	if(owner == NULL)
	{
		cout<<"wagon enter_scene fail for no owner!"<<endl;
		return false;
	}
	mapNow = owner->getMap();
	
	if(mapNow == NULL)
	{
		cout<<"wagon enter_scene fail for no map ptr"<<endl;
		return false;
	}
	box = mapNow->getBox();
	
	if(box == NULL)
	{
		cout<<"wagon enter_scene fail for no box !"<<endl;
		return false;
	}
	
	// setLogicPt(owner->getLogPt());
	setLocation(owner->getLocation());
	
	bool ret = mapNow->insertID(obj);
	
	cout<<"wagon enter_scene insert to nine box return is "<<ret<<endl;
	
	  
	              
   	formBornMsg();   
	
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(bornMsg);  
	
	return true;
}

/*马车退出场景*/
bool Wagon::quit_scene()
{
	
	Nbox *box;
	
	StyObj obj(id,WAGON_STYLE_TYPE);
	
	Hero *owner = getOwner();
	
	if(owner == NULL)
	{
		cout<<"wagon quit_scene fail for no owner"<<endl;
		return false;
	}
	mapNow = owner->getMap();
	
	if(mapNow == NULL)
	{
		cout<<"wagon quit_scene fail for no map ptr"<<endl;
		return false;
	}        
 	
	box = mapNow->getBox();
	
	if(box == NULL)
	{
		cout<<"wagon quit_scene fail for no box"<<endl;
		return false;
	}
	
	formOutMsg(); 
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(outMsg);
	
	mapNow->deleteID(obj);  
	cout<<"wagon quit_scene success"<<endl;
	return true;
}


/*实例计时器函数*/
void Wagon::initTimer(void)
{
    ext_ev_timer_init(&think_timer,wagonThkCalBak,WAGON_WALK_TIME,0,this);
    ev_timer_start(loops,&think_timer);
    // wagonTimer->inPushObj(this);
}


/*暂停思考*/
void Wagon::deleteTimer(void)         
{
	ev_timer_stop(loops,&think_timer);
	// wagonTimer->dropObj(id);
	// wagonTimer->dropId(id);	
	
}	

char* Wagon::getIdentity(void)
{
	return getWagonId();
}

//获取马车地图
Map_Inform *Wagon::getMap()
{
	return mapNow;
}

Point Wagon::getLocation()
{
	return pt;
}

void Wagon::startMoveTimer()
{
	currPt = endPt = pt;
	speedPt._x = 0; speedPt._y = 0;
	ext_ev_timer_init(&moveTimer, wagon_move_cb, 0.5, 0, this);
	ev_timer_start(loops, &moveTimer);
}

void Wagon::stopSpeedGameCtlTimer()
{
	ev_timer_stop(loops, &speedGameCtlTimer);
	stopIncSpeedTimer();
	gameCtlState = 0;
	SpeedUpOnce = false;
}

static void speed_game_timer_cb(struct event_base *loop, ev_timer* think, int revents)
{
	Wagon* wagon = (Wagon*)think->target;
	if (wagon == NULL)
	{
		return;
	}
	
	wagon->startSpeedGameCtlTimer();
}

void Wagon::startSpeedGameCtlTimer(int flag)
{
	if (!haveSpeedGame)
	{
		return;
	}
	
	Hero* owner = getOwner();
	if (owner == NULL && flag != 1)
	{
		return;
	}
	
	if (gameCtlState == 0)
	{
		SpeedUpOnce = false;
		ext_ev_timer_init(&speedGameCtlTimer, speed_game_timer_cb, gameLastTime, 0, this);
		ev_timer_start(loops, &speedGameCtlTimer);
		gameCtlState = 1;
		
		char startGameMsg[64] = {0};
		sprintf(startGameMsg, "5,24");
		send_msg(owner->getFd(), startGameMsg);
	} else {
		ext_ev_timer_init(&speedGameCtlTimer, speed_game_timer_cb, gameCdTime, 0, this);
		ev_timer_start(loops, &speedGameCtlTimer);
		gameCtlState = 0;
	}
}

static void inc_speed_timer_cb(struct event_base *loop, ev_timer* think, int revents)
{
	Wagon* wagon = (Wagon*)think->target;
	if (wagon == NULL)
	{
		return;
	}
	
	wagon->changeSpeed();
}

void Wagon::stopIncSpeedTimer()
{
	ev_timer_stop(loops, &incSpeedTimer);
	changeSpeed();
}

void Wagon::startIncSpeedTimer(int speedColor)
{
	if (!haveSpeedGame)
	{
		return;
	}
	
	if (gameCtlState != 1)
	{
		cout<<"wagon speed up game time is over"<<endl;
		return;
	}
	
	if (speedColor == 0)
	{
		return;
	}
	
	if (SpeedUpOnce)
	{
		cout<<"You have already speed up this time!"<<endl;
		return;
	}
	
	if (speedColor == 1)
	{
		changeSpeed(yellowSpeed);
	} else if (speedColor == 2)
	{
		changeSpeed(redSpeed);
	} else {
		return;
	}
	ext_ev_timer_init(&incSpeedTimer, inc_speed_timer_cb, incSpeedTime, 0, this);
	ev_timer_start(loops, &incSpeedTimer);
	SpeedUpOnce = true;
	
}


int Wagon::getLifeUpperVal()
{
	return lifeUperVal;
}

void Wagon::stopMoveTimer()
{
	ev_timer_stop(loops, &moveTimer);
}

float Wagon::getRewardTimes()
{
	return rewardTimes;
}


void Wagon::setSpeed(int newSpeed)
{
	Hero* owner = getOwner();
	if (owner == NULL)
	{
		return;
	}
	
	if (speed != newSpeed)
	{
		owner->setSpeed(newSpeed);
		speed = newSpeed;
		wagon_move_cb(loops, &moveTimer, 2);
		lastSpeed = newSpeed;
	}
		
}


void Wagon::changeSpeed(int chgSpeed)
{
	Hero* owner = getOwner();
	if (owner == NULL || chgSpeed < 0)
	{
		return;
	}
	
	if (chgSpeed == 0)
	{
		setSpeed(NORMAL_WAGON_SPEED);
	} else {
		setSpeed(chgSpeed);
	}
}

int Wagon::getSpeed()
{
	return speed;
}

int Wagon::getLastSpeed()
{
	return lastSpeed;
}


void Wagon::pushOneRoutePt(int x, int y)
{
	if (routeArrUsedIndex >= (sizeof(routeArr) / 8) - 1)
	{
		return;
	}
	routeArr[2 * routeArrUsedIndex] = x;
	routeArr[2 * routeArrUsedIndex + 1] = y;
	routeArrUsedIndex++;
	routeSize++;
}

void Wagon::popOneRoutePt(Point &pt)
{
	if (routeIndex < routeArrUsedIndex)
	{
		pt._x = routeArr[2 * routeIndex];
		pt._y = routeArr[2 * routeIndex + 1];
		routeIndex++;
		routeSize--;
	}
}

void Wagon::routeClear()
{
	for (int i = 0; i < 1024; i++)
	{
		routeArr[i] = 0;
	}
	
	routeArrUsedIndex = 0;
	routeIndex = 0; 
	routeSize = 0;
}

int Wagon::getRouteIndex()
{
	return routeIndex;
}

int Wagon::getRouteSize()
{
	return routeSize;
}

void Wagon::viewRouteMsg(char* routeMsg)
{
	int tempIndex = routeIndex;
	for (tempIndex; tempIndex < routeArrUsedIndex; tempIndex++)
	{
		sprintf(routeMsg + strlen(routeMsg), ",%d,%d", routeArr[2 * tempIndex], routeArr[2 * tempIndex + 1]);
	}
}
