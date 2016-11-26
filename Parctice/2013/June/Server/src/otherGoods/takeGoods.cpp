#include"takeGoods.h"
#include"map_inform.h"
#include"nbox.h"
#include"otherThingCalBack.h"
#include"move_asist.h"
using namespace std;
extern map<string,Hero*>heroId_to_pHero;
extern struct ev_loop *loops;

TakeGoods::TakeGoods(char *_typeId,char *_goodsId,char *_name,char *_photoId,\
bool _isDis,bool _trigByMsg,int _takeModle,int _taskStyle,int _brandType,\
double _takeTme,char *_offerWords,int _durTme,bool _isMove,bool _isInterrupt)
{

	memset(typeId,'\0',sizeof(typeId));
	memset(id,'\0',sizeof(id));
	memset(photoId,'\0',sizeof(photoId));
	memset(name,'\0',sizeof(name));
	
	memset(bornMsg,'\0',sizeof(bornMsg));
	memset(outMsg,'\0',sizeof(outMsg));
	memset(goodsId,'\0',sizeof(goodsId));
	
	memset(dishOwner,'\0',sizeof(dishOwner));
	memset(dishNewNme,'\0',sizeof(dishNewNme));
	memset(offerWords,'\0',sizeof(offerWords));	
	memset(emptyPhotoId,'\0',sizeof(emptyPhotoId));
	
	memset(ownerNickName,'\0',sizeof(ownerNickName));
	memset(ownerValue,'\0',sizeof(ownerValue));
	
	
	
	strncpy(emptyPhotoId,"I020",4);
	strncpy(typeId,_typeId,strlen(_typeId));
	strncpy(name,_name,strlen(_name));
	strncpy(photoId,_photoId,strlen(_photoId));
	strncpy(goodsId,_goodsId,strlen(_goodsId));
	strncpy(offerWords,_offerWords,strlen(_offerWords));
	trigByMsg = _trigByMsg;
	
	bruOut = false;
	
	isDispear = _isDis;
	
	takeModle = _takeModle;
	
	taskStyle = _taskStyle;
	
	brandType = _brandType;
	
	takeTme = _takeTme;	
	
	isMove = _isMove;
	
	astar = NULL;
	
	flgEndPt = false;	
	
	durTme = _durTme;
	
	speed = lastSpeed = 120;
	
	moveRate = -1;
	
	moveCtn = 0;
	
	ctnMoveRate();
	
	dishState = 0;
	
	isDished = false;
	
	chgState = true;
	
	isUsed = false;
	
	/*帮派战，则阵容归属,否则无归属*/
	if(taskStyle == 3)
	{
		ownerType = 2;
	}
	else
	{
		ownerType = 0;
	}
	
	isInterrupt = _isInterrupt;
}


/*析构函数*/
TakeGoods::~TakeGoods(void)
{
	memset(typeId,'\0',sizeof(typeId));
	memset(id,'\0',sizeof(id));
	memset(photoId,'\0',sizeof(photoId));
	memset(name,'\0',sizeof(name));
	
	memset(bornMsg,'\0',sizeof(bornMsg));
	memset(outMsg,'\0',sizeof(outMsg));
	memset(goodsId,'\0',sizeof(goodsId));
	map_now = NULL;
	ev_timer_stop(loops,&think_timer);
	ev_timer_stop(loops,&moveTimer);
	
	if(astar != NULL)
	{
		delete astar;
		astar = NULL;
	}
}
	
	
/*生成刷出信息*/
void TakeGoods::formBornMsg(void)
{
	
	int dishLastTme;
	
	/*如果不是宴席，不是可动的，且已经被刷出来的则return*/
	if(bruOut && !isMove)
	{
		return;
	}
	
	if(isMove)
	{
		memset(bornMsg,'\0',IN_VIEW_LENGTH + 1);
	
		snprintf(bornMsg,sizeof(bornMsg),"%d,%d,%d,%s,%s",2,9,TYPETAKEGOODS,id,name);
			
		snprintf(bornMsg + strlen(bornMsg),sizeof(bornMsg) - strlen(bornMsg),",%d,%d,%d,%s,%d,%d",pt._x,pt._y,0,photoId,taskStyle,1);
		
		return;
	}
	else if(trigByMsg)
	{
		/*已刷出过*/
		if(!chgState)
		{
			return;
		}
		
		chgState = false;
		
		/*获得宴席剩余时间*/
		dishLastTme = getLastTme();		
		
		snprintf(bornMsg,sizeof(bornMsg),"%d,%d,%d,%s,%s",2,9,TYPETAKEGOODS,id,dishNewNme);
		
		if(isDished)
		{
			snprintf(bornMsg + strlen(bornMsg),sizeof(bornMsg) - strlen(bornMsg),",%d,%d,%d,%s,%d",pt._x,pt._y,0,photoId,1);
		}
		else
		{
			snprintf(bornMsg + strlen(bornMsg),sizeof(bornMsg) - strlen(bornMsg),",%d,%d,%d,%s,%d",pt._x,pt._y,0,emptyPhotoId,0);
		}		
		return;
	}
	else
	{
	
		memset(bornMsg,'\0',sizeof(bornMsg));
		
		/*阵营战旗帜换名字*/
		if(taskStyle == 3 && strlen(ownerNickName) > 0)
		{
			snprintf(bornMsg,sizeof(bornMsg),"%d,%d,%d,%s,%s",2,9,TYPETAKEGOODS,id,ownerNickName);
		}
		else
		{			
			snprintf(bornMsg,sizeof(bornMsg),"%d,%d,%d,%s,%s",2,9,TYPETAKEGOODS,id,name);
		}
			
		snprintf(bornMsg + strlen(bornMsg),sizeof(bornMsg) - strlen(bornMsg),",%d,%d,%d,%s,%d",pt._x,pt._y,0,photoId,1);
		
		bruOut = true;
	}
		
}

/*获得id*/
char* TakeGoods::getId(void)
{
	return id;
}

/*生成下线信息*/
void TakeGoods::formOutMsg(void)
{
	memset(outMsg,'\0',OUT_VIEW_LENGTH + 1);
	snprintf(outMsg,sizeof(outMsg),"%d%s%d%s%s%s%d",2,",",5,",",id,",",1);
}

/*获得被攻击玩家实例指针*/
Hero* TakeGoods::getHero(char *heroId)
{
    map<string,Hero*>::iterator hero_it;
    hero_it = heroId_to_pHero.find(heroId);
    if(hero_it == heroId_to_pHero.end())
    {
        return	NULL;
    }
    return hero_it->second;
}

/*设置地图以及逻辑坐标*/
void TakeGoods::setLogicMap(Map_Inform *_map_now)
{	
	if(_map_now != NULL)
    {
        map_now = _map_now;
		
        /*设置相对应坐标*/
        logicPt = MapExchangeLogical(pt);
        logicPt._y += map_now->getBaseDigst();
		
		bornLogPt = MapExchangeLogical(bornPiexPt);
		bornLogPt._y += map_now->getBaseDigst();
		if(isMove && astar == NULL)
		{	
			astar = new Astar(map_now);
		}   
    }
}

/*设置像素坐标*/
void TakeGoods::setPt(Point _pt)
{
	pt = _pt;
	
	bornPiexPt = _pt;
}

/*设置像素坐标和逻辑坐标*/
void TakeGoods::setLocation(Point _pt,int flag)
{
	if(map_now == NULL)
	{
		cout<<"the map_now is NULL of the takeGoods is :"<<id<<endl;
		return;
	}
	
	if (flag == 0)
	{
		endPt = currPt = _pt;
		keyPath.clear();
	}
	
	pt = _pt;
	
	/*设置相对应坐标*/
    logicPt = MapExchangeLogical(pt);
    logicPt._y += map_now->getBaseDigst();
}

/*获得像素坐标*/
Point TakeGoods::getPt(void)
{	
	return pt;
}

/*设置地图以及逻辑坐标*/
TakeGoods* TakeGoods::copyTakeGoods(Point _pt,bool _isResource,bool isUid)
{	
	TakeGoods* takeGoods;
	char *uuId,_id[HEROID_LENGTH + 1] = {'\0'};		
	takeGoods = new TakeGoods(typeId,goodsId,name,photoId,isDispear,\
	trigByMsg,takeModle,taskStyle,brandType,takeTme,offerWords,durTme,isMove,isInterrupt);
	takeGoods->setPt(_pt);
	takeGoods->setDishState(0);
	takeGoods->setIsCampSource(_isResource);
	strncpy(_id,typeId,strlen(typeId));
	strncat(_id,"_",strlen("_"));	
	
	if(isUid)
	{
		uuId = cid();	
		strncat(_id,uuId,strlen(uuId));
		free(uuId);
	}
	else
	{
		count++;
		appendNum(_id,count,4);
	}
	takeGoods->setInstId(_id);
	return takeGoods;
}


/*复制瓶罐*/
TakeGoods* TakeGoods::copyTakeGoods(char *_mapId)
{	
	char newIntId[LONG_MID_VALUE_LENGTH + 1] = {'\0'};       //新地图id;
	TakeGoods* newTakeGoods;
	
	/* 追加地图id，为了保证副本道具id的唯一性*/	
	strncpy(newIntId,_mapId,strlen(_mapId));
	strncat(newIntId,"_",strlen("_"));	
	strncat(newIntId,id,strlen(id));
		
	newTakeGoods = new TakeGoods(typeId,goodsId,name,photoId,isDispear,\
	trigByMsg,takeModle,taskStyle,brandType,takeTme,offerWords,durTme,isMove,isInterrupt);	
	newTakeGoods->setPt(pt);
	newTakeGoods->setDishState(0);
	newTakeGoods->setInstId(newIntId);	
	newTakeGoods->setIsCampSource(isCampSource);
	return newTakeGoods;
}


/*获得摘取物品id*/
char* TakeGoods::getTakeId(void)
{
	return id;
}

/*获得像素坐标*/
Point TakeGoods::getLogicPt(void)
{	
	return logicPt;
}

/*设置实例id*/
void TakeGoods::setInstId(char *_id)
{
	if(_id == NULL || strlen(_id) == 0)
	{
		cout<<"the trap id is error:"<<endl;
		return;
	}
	memset(id,'\0',sizeof(id));	
	strncpy(id,_id,strlen(_id));
}

/*刷出可摘取物品*/
void TakeGoods::brushMsg(void)
{
	StyObj obj(id,TAKEGOODS_STYLE_TYPE);
	Nbox *box;	
	
	if(bruOut)
	{
		return;
	}
	
	formBornMsg();
	
	formOutMsg();
	
	if(map_now == NULL)
	{
		return;
	}
	                   
	box = map_now->getBox();	
	
	if(box == NULL)
	{
		return;
	}
	
//	bruOut = true;	
	
	map_now->insertID(obj);
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(bornMsg);
	
	if(isMove)
	{
		ev_timer_stop(loops,&think_timer);
		
		ext_ev_timer_init(&think_timer,takeGoodsThkCalBack,2,0, this);

		ev_timer_start(loops,&think_timer);
		
		startMoveTimer();
	}
	
}

/*摘取物品消亡*/
void TakeGoods::disperMsg(void)
{
	StyObj obj(id,TAKEGOODS_STYLE_TYPE);
	Nbox *box;
	
	
	if(!isDispear)
	{
		return;
	}
	
	formOutMsg();                  
	             
	box = map_now->getBox();	
	
	if(box == NULL)
	{
		return;
	}
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(outMsg);
	
	map_now->deleteID(obj);
	
	bruOut = false;
	
	memset(dishOwner,'\0',sizeof(dishOwner));
	memset(dishNewNme,'\0',sizeof(dishNewNme));
	
	/*可移动摘取物*/
	if(isMove)
	{		
		stopMove();
		keyPath.clear();
		currPt = endPt = pt;
		stopMoveTimer();
		
		moveCtn = 0;	
		ctnMoveRate();
	}
	
	if(!trigByMsg)
	{		
		/*资源战中，资源不再自动刷出*/
		if(isCampSource && taskStyle == 3)
		{
			initTakeGoods();
			return;
		}
		
		ev_timer_stop(loops,&think_timer);
		
		ext_ev_timer_init(&think_timer,takeGoodsThkCalBack,2,0, this);

		ev_timer_start(loops,&think_timer);
	}
}
bool TakeGoods::getBruOut(void)
{
	return bruOut;
}

char* TakeGoods::getBronMsg(void)
{
	return bornMsg;
}

char* TakeGoods::getGoodsId(void)
{
	return goodsId;
}


char* TakeGoods::getOutMsg(void)
{
	return outMsg;
}

/*获得触发方式*/
bool TakeGoods::getTrigFlg(void)
{
	return trigByMsg;
}

/*获得采集持续时间*/
double TakeGoods::getTakeTme(void)
{
	return takeTme;
}

/*清空采集人集合*/
void TakeGoods::clearOwner(char *ownerId)
{
	set<string>::iterator owner_it;
	
	if(ownerId == NULL || strlen(ownerId) == 0)
	{
		cout<<"the ownerId is NULL:"<<endl;
		return;
	}	
	
	owner_it = onwerSet.find(ownerId);
	
	if(owner_it == onwerSet.end())
	{
		cout<<"it is not find the ownerId to take the goods:"<<ownerId<<endl;
		return;
	}
	
	if(takeModle == 2)
	{
		onwerSet.clear();
	}
	else
	{
		onwerSet.erase(owner_it);
	}
}

/*插入采集人集合*/
void TakeGoods::inPutOwner(char *ownerId)
{
	if(ownerId == NULL || strlen(ownerId) == 0)
	{
		return;
	}
	onwerSet.insert(ownerId);
}

/*获得是否会动的标志*/
bool TakeGoods::getIsMove(void)
{
	return isMove;
}


/*判断此采摘物是否归位*/
bool TakeGoods::isRec(void)   	
{
    if(bornLogPt == logicPt)
	{
		return true;
	}
	return false;
}

 /*寻路追击函数*/
void TakeGoods::findAttWay(Point &end)
{
    if(astar == NULL)
    {
		cout<<"the astar is error NULL:"<<id<<endl;
        return;
    }
	
    /*如果当前点跟寻路终点重合，则直接返回*/
    if(logicPt == end)
    {
		cout<<"the logicPt is the equip endPt:"<<endl;
        return; 
    }	
    astar->findWay(logicPt,end);    //寻得的路径就在astar中	
	exchgeWayRod();
}


/*把寻路寻到的逻辑点转换成像素点*/
void TakeGoods::exchgeWayRod(void)
{

	stopMove();	
	
	if(astar->getWayArr().empty())
	{
		return;
	}	
	
	smoothRoadPt();
	
	stopMoveTimer();
	
	takeGoods_move_cb(loops, &moveTimer, 3);
	
}

/*路径平滑处理*/
void TakeGoods::smoothRoadPt(void)
{	
	list<Point>::reverse_iterator sendPt_it;	
	list<Point>::iterator temp_it,key_it;
	Point lastPt,lastPiexRodPt;		
	list<Point> temp;
	
	if(astar->getWayArr().empty())
	{
		return;
	}	
	
	keyPath.push_back(pt);	
	
	for(sendPt_it = astar->getWayArr().rbegin();sendPt_it !=\
	astar->getWayArr().rend();sendPt_it++)
	{	
	
		lastPt = *sendPt_it;
		
		if(logicPt == lastPt)
		{
			continue;
		}
		
		lastPt._y -= map_now->getBaseDigst();
	
		lastPiexRodPt = LogicalExchangeMap(lastPt);
	
		if(!hasBarrier(pt,lastPiexRodPt,map_now))
		{
			keyPath.push_back(lastPiexRodPt);
			break;
		}
		else
		{
			temp.push_front(lastPiexRodPt);
		}
	}
	
	/*处理那些障碍点*/
	if(!temp.empty())
	{		
		keyPath.insert(keyPath.end(),temp.begin(),temp.end());
	}
	
	// for(key_it = keyPath.begin();key_it != keyPath.end();key_it++)
	// {	
		// lastPt = MapExchangeLogical(*key_it);
		// lastPt._y += map_now->getBaseDigst();
		// map_now->judgeLogPtHind(lastPt);
	// }
}

/*暂停移动*/
void TakeGoods::stopMove(void)
{
	takeGoods_move_cb(loops, &moveTimer, 1);
}

/*暂停掐点计时器*/
void TakeGoods::stopMoveTimer()
{
	ev_timer_stop(loops, &moveTimer);
}

/*启动掐点计时器*/
void TakeGoods::startMoveTimer()
{
	keyPath.clear();
	currPt = endPt = pt;
	ext_ev_timer_init(&moveTimer, takeGoods_move_cb, 0.5, 0, this);
	ev_timer_start(loops, &moveTimer);
}

/*获得地图实例指针*/
Map_Inform* TakeGoods::getMap(void)
{
	return map_now;
}

/*获得速度*/
int TakeGoods::getSpeed(void)
{
	return speed;
}

/*获得最后点速度*/
int TakeGoods::getLastSpeed(void)
{
	return lastSpeed;
}


/*获得移动终点*/
void TakeGoods::getEndPt(void)
{
	if(flgEndPt)
	{
		return;
	}
	
	endFinPt = bornPiexPt;
	
	endFinPt._x += 50;
	endFinPt._y += 50;
	
    endFinPt = MapExchangeLogical(endFinPt);
    endFinPt._y += map_now->getBaseDigst();
	if(!map_now->judgeLogPtHind(endFinPt))
	{    
		flgEndPt = false;
		return;
    }
	flgEndPt = true;
}  


/*获得可摘取物品类型*/
int TakeGoods::getTaskStyle(void)
{
	return taskStyle;
}

/*会动的可摘取物的回调函数*/
void TakeGoods::calBack(void)
{
	if(!isMove)
	{
		return;
	}
	if(!flgEndPt)
	{
		getEndPt();
	}
	if(!flgEndPt)
	{
		return;
	}
	if(isRec())
	{
	
		if(keyPath.empty() && isMoveTme())
		{
			findAttWay(endFinPt);	
		}		
	}
	else
	{
		
		if(keyPath.empty() && isMoveTme())
		{
			findAttWay(bornLogPt);
		}		
	}
}

/*获取采集物品子类型*/
int TakeGoods::getBrandType(void)
{
	return brandType;
}

/*设置宴请主人*/
void TakeGoods::setDIshOwner(char *_ownerId)
{
	if(_ownerId == NULL || strlen(_ownerId) == 0)
	{
		cout<<"the _ownerId is empty:"<<endl;
		return;
	}
	strncpy(dishOwner,_ownerId,strlen(_ownerId));
	
	/*初始化开始时间*/
	gettimeofday(&beginTme,NULL);	
}


/*获得宴席持续总时间*/
int TakeGoods::getTolDurTme(void)
{
	return durTme;
}

/*获得宴席持续还剩多长时间*/
int TakeGoods::getLastTme(void)
{
	struct timeval endTme;	
	int costTme;
	
	gettimeofday(&endTme,NULL);	
	costTme = endTme.tv_sec - beginTme.tv_sec;
	if(costTme <= 0)
	{
		return 0;
	}
	if(durTme >= costTme)
	{
		return durTme - costTme;
	}
	return 0;
}

/*获得宴席的新名字*/
void TakeGoods::setDishNewNme(char *nickNme)
{
	if(nickNme == NULL)
	{
		return;
	}
	
	strncpy(dishNewNme,nickNme,strlen(nickNme));
	strncat(dishNewNme,"钦点的",strlen("钦点的"));
	strncat(dishNewNme,name,strlen(name));
}

/*重置宴席的名字*/
void TakeGoods::initDishNewNme(void)
{
	memset(dishNewNme,'\0',sizeof(dishNewNme));
}

/*重置宴席的主人名字*/
void TakeGoods::initDishOwner(void)
{
	memset(dishOwner,'\0',sizeof(dishOwner));
}


/*获得可摘取物品相应的提示信息*/
char* TakeGoods::getOfferWords(void)
{
	return offerWords;
}

/*计算获得运动频率*/
void  TakeGoods::ctnMoveRate(void)
{
	int srandInt;
	
	srandInt = rand()%30;
	
	if(moveRate == -1)
	{
		moveRate = srandInt;
	}
	else
	{
		if(srandInt % 2 != 0)
		{
			moveRate = srandInt;
		}
	}
}

/*是否可以动*/
bool TakeGoods::isMoveTme(void)
{
	moveCtn++;
	
	if(moveCtn < moveRate)
	{
		return false;
	}
	moveCtn = 0;
	return true;
}

/*获得类型id*/
char* TakeGoods::getTypeId(void)
{
	return typeId;
}

/*获得宴席是否可吃状态值*/
int TakeGoods::getDishState(void)
{
	return dishState;
}

/*设置宴席是否可吃状态值*/
void TakeGoods::setDishState(int _newState)
{
	dishState = _newState;
}

/*设置空宴席的图片id*/
void TakeGoods::setEmptyPhotoId(char *_emptyPhotoId)
{
	memset(emptyPhotoId,'\0',sizeof(emptyPhotoId));
	strncpy(emptyPhotoId,_emptyPhotoId,strlen(_emptyPhotoId));
}

/*设置宴席是否已点菜*/
void TakeGoods::setIsDished(bool _isDished)
{	
	if(_isDished != isDished)
	{
		isDished = _isDished;	
		
		chgState = true;
		
		memset(bornMsg,'\0',sizeof(bornMsg));
		
		/*重新设置图片*/
		formBornMsg();
		
	}
}

/*获得宴席是否已点菜*/
bool TakeGoods::getIsDished(void)
{
	return isDished;
}

/*设置宴席图片id*/
void TakeGoods::setPhotoId(char *_photoId)
{
	if(_photoId == NULL)
	{
		cout<<"TakeGoods::setPhotoId _photoId is NULL:"<<id<<endl;
		return;
	}
	memset(photoId,'\0',sizeof(photoId));
	strncpy(photoId,_photoId,strlen(_photoId));
}

/*获得宴席图片id*/
char* TakeGoods::getPhotoId(void)
{
	return photoId;
}


/*设置宴席名字*/
void TakeGoods::setName(char *_name)
{
	if(_name == NULL)
	{
		cout<<"TakeGoods::setPhotoId _name is NULL:"<<id<<endl;
		return;
	}
	memset(name,'\0',sizeof(name));
	strncpy(name,_name,strlen(_name));	
}

/*获得宴席名字*/
char* TakeGoods::getName(void)
{
	return name;
}



/*获得是否是阵营资源战里面的资源,真为是*/
bool TakeGoods::getIsCampSource(void)
{
	return isCampSource;
}

/*获得是否是阵营资源战里面的资源,真为是*/
void TakeGoods::setIsCampSource(bool _isCampSource)
{
	isCampSource = _isCampSource;
}

/*阵容资源是否已经刷出了，真为是*/
bool TakeGoods::getIsUsed(void)
{
	return isUsed;
}

/*阵容资源是否已经刷出了，真为是*/
void TakeGoods::setIsUsed(bool _isUsed)
{
	isUsed = _isUsed;
}

/*重置可摘取物品的数据*/
void TakeGoods::initTakeGoods(void)
{
	ev_timer_stop(loops,&think_timer);
	onwerSet.clear();
	isUsed = false;
	bruOut = false;
	
	memset(ownerNickName,'\0',sizeof(ownerNickName));
	memset(ownerValue,'\0',sizeof(ownerValue));
	
}

/*重置帮派战里面的旗帜*/
void TakeGoods::initFlagByHero(char *heroId)
{
	memset(ownerNickName,'\0',sizeof(ownerNickName));
	memset(ownerValue,'\0',sizeof(ownerValue));
	
	if(heroId == NULL || strlen(heroId) == 0)
	{
		cout<<"TakeGoods::initFlagByHero the heroId is empty:"<<id<<endl;
		return;
	}
	
	Hero *hero = getHero(heroId);
	
	if(hero == NULL)
	{
		cout<<"TakeGoods::initFlagByHero hero is NULL:"<<id<<endl;
	}
	strncpy(ownerNickName,hero->getNickName(),strlen(hero->getNickName()));
	
	/*帮派*/
	if(ownerType == 1)
	{		
		strncpy(ownerValue,hero->getGuildName(),strlen(hero->getGuildName()));
	}
	
	/*阵营*/
	else if(ownerType == 2)
	{
		sprintf(ownerValue,"%d",hero->getCamp());
	}
}

/*获得归属值*/
char* TakeGoods::getOwnerValue(void)
{
	return ownerValue;
}
	
/*获得归属类型*/
int TakeGoods::getOwnerType(void)
{
	return ownerType;
}

bool TakeGoods::isPicking()
{
	return (onwerSet.size() != 0);
}

//是否打断，真为可以打断
bool TakeGoods::IsInterrupt()
{
	return isInterrupt;
}