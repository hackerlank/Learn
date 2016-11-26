#include"command_other_function_all_over.h"
#include"command_return_define_data.h"
#include"timerContainer.h"
#include"monsterBase.h"
#include"five_asist.h"
#include<math.h>
#include "sitControl.h"



extern struct ev_loop *loops;
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Map_Inform*>mapId_connect_map;  
extern HatValRue *hatValRue;          
extern TimerContainer<MonsterBase*> *monThkContain;
extern map<string,SkillBase*> monster_skill_map; 
extern map<string,SkillBase*> monSkiInst;
extern int TileWidth;
extern int TileHeight;

const string DROP_BLOOD_ID = "X010"; // moved from .h to here by benliao

MonsterBase::MonsterBase(char *_mapId,char *_typeId,char *_nickName,\
char *_identity,char *_type,char *_kind,int _experience,double _cdTime,\
int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,\
int _getHrtSud,int _outHrt,int _inHrt,int _outAttVal, int _inAttVal,\
int _outDefVal, int _inDefVal,int _defSumVal,double _hit,double _crit,\
int _voids,int _tenacity,int _moveRange, int _hatRange,int _attRange,\
int _failGoodsless,int _failGoodsmost,int _hatVal,int _gold,set<string>&\
 _failId, Point _pt,int _rank,int _speed,int _fiveEleInt,\
int _fiveHurt,int _fiveRank,int _forGo,int _expTme,int _monyTme,char *_stage,\
char *_photoId,vector<string> &_skiIdSet,char *_genAttId,double _angVal,\
int _ownerAttriType,char* _ownerAttri,double _attackRatio,bool _isInnerAttack,LveCtnManger _lveCtnMager)
{

	memset(mapId,'\0',sizeof(mapId));
	memset(nickName,'\0',sizeof(nickName));
	memset(typeId,'\0',sizeof(typeId));
	memset(identity,'\0',sizeof(identity));
	memset(kind,'\0',sizeof(kind));
	memset(type,'\0',sizeof(type));
	memset(photoId,'\0',sizeof(photoId));
	memset(stage,'\0',sizeof(stage));
	memset(ownerAttri,'\0',sizeof(ownerAttri));
	
	ownerAttriType = _ownerAttriType;
	strncpy(ownerAttri,_ownerAttri,strlen(_ownerAttri));	    
	
    strncpy(mapId,_mapId,strlen(_mapId));    
    strncpy(typeId,_typeId,strlen(_typeId));  
    strncpy(nickName,_nickName,strlen(_nickName));
    
    strncpy(identity,_identity,strlen(_identity));
   
    strncpy(kind,_kind,strlen(_kind));
	
	strncpy(type,_type,strlen(_type));
   
    strncpy(photoId,_photoId,strlen(_photoId));
   

    lifeUpperVal = _lifeUpperVal;
	
    lifeVal=_lifeVal;

    hrtSud = _getHrtSud;

    outHrt = _outHrt;

    inHrt= _inHrt;

    outAttVal = _outAttVal;

    inAttVal = _inAttVal;

    outDefVal = _outDefVal;

    inDefVal = _inDefVal;

    defSumVal = _defSumVal;

    hit = _hit;

    crit = _crit;

    voids = _voids;

    tenacity = _tenacity;

    walk_ranage = _moveRange;

    hatRge = _hatRange;

    attack_range = _attRange;

    failGoodsLess = _failGoodsless;

    failGoodsMost = _failGoodsmost;

    hatVal = _hatVal;

    gold = _gold;

    failList = _failId;

    magicUpperVal =_magicUpperVal; 
	
    magicVal=_magicVal;

    pt = _pt;

    born_pt=_pt;

    cdTime = _cdTime;

    experience = _experience;
	
    astar = NULL;
	
	memset(perHerId,'\0',sizeof(perHerId));
	
	isAlive = true;
	
	initSkiInst(_skiIdSet);
	
	angVal = _angVal;

    Rec = false;  

    flgRun = false;         
	
	memset(goodsOwner,'\0',sizeof(goodsOwner));
	
	skiBody = true;   //true为可移动               
	attackPoint = true;             
	dizz = true; 
	
	storeAttDef();
	tena_city = tenacity;
	hitCopy = hit;
	
	unEnemySta = false;
	
	rank = _rank;
	
	speed = _speed;
	
	lveCtnMager = _lveCtnMager;
	
	fiveEleInt = _fiveEleInt;
	fiveEleRank = _fiveRank;    
	
	
	forGo =  _forGo;
	expTme = _expTme;
	monyTme = _monyTme;
	
	fiveElement = new FiveElem((FIVE_ELEMENT_T)fiveEleInt, fiveEleRank);
	
	kindIntInit();
	
	
	dealGoFor();
	
	repFlg = false;
	
	initPersuitPt();
	
	
	memset(genAttId,'\0',sizeof(genAttId));
	
	strncpy(genAttId,_genAttId,strlen(_genAttId));
	
	strncpy(stage,_stage,strlen(_stage));
	
	speed = 120;
	
	lastSpeed = speed;
	
	playCd = 2;
	
	plyCdCtn = 0;
	
	isHurt = false;
	
	isInPatrol = false;
	
	isBloodTmeOpenFlg = false;
	
	goForCtn = 0;
	
	isPersuitHero = false;
	
	attackRatio = _attackRatio;
	
	isInnerAttack = _isInnerAttack;
	
	memset(appendNickName,'\0',sizeof(appendNickName));

#if 0
	strncpy(appendNickName,nickName,strlen(nickName));
#endif
	
	isUsed = false;
	
	memset(taskOwnerId,'\0',sizeof(taskOwnerId));
	
#if 0

	/*测试npc任务怪*/
	strncpy(appendNickName,taskOwnerId,strlen(taskOwnerId));
	strncat(appendNickName,"_test",5);
	
#endif

	isCallType = false;
	isCalled = false;
	
	isCdCool = true;
	
	callBoss = NULL;

}

/* 获取仇恨列表*/
list<HatVal>& MonsterBase::getEnmityValues(void)    
{
	return enmityValues;
}

/* 删除仇恨id*/
void MonsterBase::dropOneEnmityValues(HatVal &hatva)
{

	list<HatVal>::iterator enmityValues_it;
	for(enmityValues_it = enmityValues.begin();enmityValues_it != enmityValues.end();enmityValues_it++)
	{
		if(strcmp((*enmityValues_it).id, hatva.id) == 0)
		{
			enmityValues.erase(enmityValues_it);
			break;
		}
	}
	enmityValues.sort(ComFun);
}

/* 获得单个仇恨id*/
HatVal* MonsterBase::getOneEnmityValues(void)
{
	if(enmityValues.empty())
	{
		return NULL;
	}
	list<HatVal>::iterator enmityValues_it;
	enmityValues_it=enmityValues.begin();	
	return &(*enmityValues_it);
}

/* 获得攻击范围*/
int MonsterBase::getAttackRange(void)
{
	return attack_range;
}

/* 获得地图指针*/
Map_Inform* MonsterBase::getMap(void)
{
	return map_now;
}


/* 获得图片id*/
char* MonsterBase::getPhotoId(void)
{
	return photoId;
}

/* 修改图片id*/
void MonsterBase::setPhotoId(char *_photoId)
{
	if(photoId == NULL || strlen(_photoId) == 0)
	{
		return;
	}
	
	memset(photoId,'\0',sizeof(photoId));
	strncpy(photoId,_photoId,strlen(_photoId));
}

/* 获得昵称*/
char* MonsterBase::getNickName(void)
{
	return nickName;
}

/* 修改生命上限值*/
void MonsterBase::setLifeUpperVal(int _lifeUpperVal)
{
	lifeUpperVal = _lifeUpperVal;
}

/* 修改当前生命值 tory_01_23*/
void MonsterBase::setLifeVal(int _lifeVal)
{
	if(_lifeVal >= lifeUpperVal)
	{
		lifeVal = lifeUpperVal;
	}
	else
	{
		lifeVal =  _lifeVal < 0 ? 1 : _lifeVal;
		
		if(lifeVal > 0)
		{
			/*add by chenzhen 201301311041 急速自卫反应*/
			initResponseAgain();

#if 0
			/*测试用*/
			if(strcmp(kind,"Boss") == 0)
			{
				cout<<"callTrap()"<<endl;
			//	callTrap();
				if(map_now)
				{
					map_now->callMon();
				}				
			}
#endif


		}
	}
#if 0	
	/*获取怒气值*/
	if(judgeBoss())
	{
		gainAngVal = (lifeVal - _lifeVal)/50;
		angVal += gainAngVal;
	}
#endif

}

/* 修改魔法上限值 tory_01_23 no use*/
void MonsterBase::setMagicUpperVal(int _MagicUpperVal)
{
	magicUpperVal = _MagicUpperVal;
}

/* 修改当前魔法值 tory_01_23 no use*/
void MonsterBase::setMagicVal(int _magicVal)
{
	magicVal = _magicVal;
}

/* 获得生命上限值*/
int MonsterBase::getLifeUpperVal(void)
{
	return lifeUpperVal;
}

/* 获得当前生命值*/
int MonsterBase::getLifeVal(void)
{
	return lifeVal;
}

/* 获得魔法上限值*/
int MonsterBase::getMagicUpperVal(void)
{
	return magicUpperVal;
}
/* 获得当前魔法值*/
int MonsterBase::getMagicVal(void)
{
	return magicVal;
}

/*获得id*/
char* MonsterBase::getIdentity(void)	
{
	return identity;
}

/*获得当前像素位置*/
Point MonsterBase::getLocation(void)	
{
	return pt; 
}

/*修改当前位置像素和逻辑*/
void MonsterBase::setLocation(Point _pt, int flag)  
{
	if (flag == 0)
	{
		endPt = currPt = _pt;
		keyPath.clear();
	}
	pt._x = _pt._x;
	pt._y = _pt._y;

	logic_pt = MapExchangeLogical(pt);
	logic_pt._y += map_now->getBaseDigst();	
}


/*获得生死状态*/
bool  MonsterBase::getLifeStation(void)    
{
	return isAlive;
}

/*修改生死状态*/
void MonsterBase::setLifeStation(bool _isAlive)  
{
	isAlive = _isAlive;
}

/*获取对应的地图Id*/
char* MonsterBase::getMapId(void)     
{
	return mapId;
}

/*获取对应的出生点（像素）*/
Point MonsterBase::getBornPoint(void)
{
	return born_pt;
}

/*获取当前逻辑坐标*/
Point MonsterBase::getLogicPt(void)
{
	return logic_pt;
}

/*修改逻辑坐标时，也对应的修改了其像素坐标*/
void MonsterBase::setLogicPt(Point _logPt)
{
	if(logic_pt._x == _logPt._x && logic_pt._y == _logPt._y)
	{
		return;
	}
    logic_pt = _logPt;
    _logPt._y -= map_now->getBaseDigst();
    pt = LogicalExchangeMap(_logPt);
}


/*插入技能id*/
void MonsterBase::pushSkillId(char *skillId)
{
	skill_list.push_back(skillId);
}

/*获得技能id的列表*/
vector<string>& MonsterBase::getSkillList(void)
{
	return skill_list;
}


/*更改目标*/
void MonsterBase::chageEny(char *_perHerId)
{

    if(perHerId != NULL && strlen(perHerId) != 0)
    {
        if(strcmp(perHerId,_perHerId) == 0)
        {
            return;
        }
    }
	memset(perHerId,'\0',SHOR_MID_VALUE_LENGTH + 1);
    strncpy(perHerId,_perHerId,strlen(_perHerId));
}

/*获得怪物秒伤*/
int MonsterBase::getHrtSud(void)
{
	return hrtSud;
}

/*设置怪物秒伤*/
void MonsterBase::setHrtSud(int _hrtSud)
{
	hrtSud = _hrtSud;
}
	
/*获得怪物外伤*/	
int MonsterBase::getOutHrt(void)
{
	return outHrt;
}

/*设置怪物外伤*/
void MonsterBase::setOutHrt(int _outHrt)
{
	outHrt = _outHrt;
}

/*获得怪物内伤*/	
int MonsterBase::getInHrt(void)
{
	return inHrt;
}

/*设置怪物内伤*/
void MonsterBase::setInHrt(int _inHrt)
{
	inHrt = _inHrt;
}

/* 获得走路范围*/
int MonsterBase::getWalkRange(void)
{
	return walk_ranage;
}

/*获得怪物外功*/
int MonsterBase::getOutAttVal(void)
{
	return outAttVal;
}

/*设置怪物外功*/
void MonsterBase::setOutAttVal(int _outAttVal)
{
	outAttVal = _outAttVal;
}

/*获得怪物内功*/	
int MonsterBase::getInAttVal(void)
{
	return inAttVal;
}

/*设置怪物内功*/
void MonsterBase::setInAttVal(int _inAttVal)
{
	inAttVal = _inAttVal;
}

/*获得怪物外防*/	
int MonsterBase::getOutDefVal(void)
{
	return outDefVal;
}

/*设置怪物外防*/
void MonsterBase::setOutDefVal(int _outDefVal)
{
	outDefVal = _outDefVal;
}

/*获得怪物内防*/	
int MonsterBase::getInDefVal(void)
{
	return inDefVal;
}

/*获得怪物内防*/	
void MonsterBase::setInDefVal(int _inDefVal)
{
	 inDefVal = _inDefVal;
}

/*获得怪物总防*/	
int MonsterBase::getDefSumVal(void)
{
	return defSumVal;
}

/*设置怪物总防*/
void MonsterBase::setDefSumVal(int _defSumVal)
{
	defSumVal = _defSumVal;
}
	
/*获得怪物命中*/	
int MonsterBase::getHit(void)
{
	return hit;
}

/*设置怪物命中*/
void MonsterBase::setHit(int _hit)
{
	hit = _hit;
}

/*获得怪物暴击*/	
int MonsterBase::getCrit(void)
{
	return crit;
}

/*设置怪物暴击*/
void MonsterBase::setCrit(int _crit)
{
	crit = _crit;
}
	
/*获得怪物闪避*/	
int MonsterBase::getVoids(void)
{
	return voids;
}

/*设置怪物闪避*/
void MonsterBase::setVoids(int _voids)
{
	voids = _voids;
}

/*获得怪物韧性*/	
int MonsterBase::getTenty(void)
{
	return tenacity;
}

/*设置怪物韧性*/
void MonsterBase::setTenty(int _tenacity)
{
	tenacity = _tenacity;
}

/*获得怪物仇恨范围*/	
int MonsterBase::getHatRge(void)
{
	return hatRge;
}

/*设置怪物仇恨范围*/
void MonsterBase::setHatRge(int _hatRange)
{
	hatRge = _hatRange;
}

/*获得怪物最小掉落值*/	
int MonsterBase::getFilGdsLess(void)
{
	return failGoodsLess;
}

/*设置怪物最小掉落值*/
void MonsterBase::setFilGdsLess(int _failGoodsLess)
{
	failGoodsLess = _failGoodsLess;
}

/*获得怪物最大掉落值*/	
int MonsterBase::getFilGdsMore(void)
{
	return failGoodsMost;
}

/*设置怪物最大掉落值*/
void MonsterBase::setFilGdsMore(int _failGoodsMost)
{
	failGoodsMost = _failGoodsMost;
}
	
/*获得怪物仇恨值*/	
int MonsterBase::getHatVal(void)
{
	return hatVal;
}

/*设置怪物仇恨值*/
void MonsterBase::setHatVal(int _hatVal)
{
	hatVal = _hatVal;
}	

/*获得怪物金币*/	
int MonsterBase::getGold(void)
{
	return gold;
}

/*设置怪物金币*/
void MonsterBase::setGold(int _gold)
{
	gold = _gold;
}	

/*获得怪物掉落列表*/	
set<string>& MonsterBase::getFailList(void)
{
	return failList;
}

/*设置怪物掉落列表*/
void MonsterBase::setFailList(set<string>& _failList)
{
	failList = _failList;
}

/*怪物下线函数*/
void MonsterBase::out(void)
{
	memset(outMsg,'\0',OUT_VIEW_LENGTH + 1);
	snprintf(outMsg + strlen(outMsg),sizeof(outMsg) - strlen(outMsg),"%d,%s,%d,%s,%s,%s,%d",2,",",5,",",identity,",",1);                 
    Nbox *box = map_now->getBox();  
	if(box == NULL)
	{
		return;
	}
	
	/*陈真改*/
	StyObj obj(identity,MONSTER_STYLE_TYPE);	
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(outMsg);
}

/*获得怪物类型*/
char* MonsterBase::getType(void)        //add chenzhen 5.11
{
	return type;
}

/*设置怪物类型*/
void MonsterBase::setType(char *_type)  //add chenzhen 5.11
{
	if(type != NULL || strlen(_type) == 0)
	{
		return;
	}
	memset(type,'\0',sizeof(type));	
	strncpy(type,_type,strlen(_type));
}

/*获得怪物类型id*/
char* MonsterBase::getTypeId(void)
{
	return typeId;
}

/*获得怪物种类*/
char* MonsterBase::getKind(void)        //add chenzhen 5.31
{
	return kind;
}

/*设置怪物种类*/
void MonsterBase::setKind(char *_kind)  //add chenzhen 5.31
{
	if(kind != NULL || strlen(_kind) == 0)
	{
		return;
	}
	strncpy(kind,_kind,strlen(_kind));
}

/*设置怪物物品所属者*/
void MonsterBase::setGoodsOwner(char *_owner)//add chenzhen 6.8
{
	if(_owner == NULL || strlen(_owner) == 0 || strlen(goodsOwner) > 0)
	{
		return;
	}
	memset(goodsOwner,'\0',IDL + 1);
	strncpy(goodsOwner,_owner,strlen(_owner));
}

/*获得怪物物品所属者*/
char* MonsterBase::getGoodsOwner(void)//add chenzhen 6.8
{
	return goodsOwner;
}
			
/*获得怪物经验值*/
int MonsterBase::getExperience(void)   //add chenzhen 6.25	
{
	return experience;
}
	
/* 获得Boss怪的怒气值*/
double MonsterBase::getAngVal(void)	//added by bison 	7.5
{
	return angVal;
}

/* 设置Boss怪的怒气值*/
void MonsterBase::setAngVal(double _angVal)	//added by bison 	7.5
{
	angVal = _angVal;
}

/*生成刷怪信息*/
void MonsterBase::formBshMsg(void)
{
	
	memset(selfMsg,'\0',sizeof(selfMsg));
	
#if 0	
	snprintf(selfMsg,sizeof(selfMsg),"%d,%d,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",\
	2,SHOW_MONSTER,MONSTER_TYPE,identity,nickName,photoId,rank,lifeUpperVal,lifeVal,magicUpperVal,\
	magicVal,attack_range,pt._x,pt._y,speed,kindInt);

#endif

#if 0	
	snprintf(selfMsg,sizeof(selfMsg),"%d,%d,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s",\
	2,SHOW_MONSTER,MONSTER_TYPE,identity,nickName,photoId,rank,lifeUpperVal,lifeVal,magicUpperVal,\
	magicVal,attack_range,pt._x,pt._y,speed,kindInt,ownerAttriType,ownerAttri);
#endif

#if 0	
	//添加一个玩家的昵称
	snprintf(selfMsg,sizeof(selfMsg),"%d,%d,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s",\
	2,SHOW_MONSTER,MONSTER_TYPE,identity,nickName,photoId,rank,lifeUpperVal,lifeVal,magicUpperVal,\
	magicVal,attack_range,pt._x,pt._y,speed,kindInt,ownerAttriType,ownerAttri,appendNickName);
#endif
	
	if(ownerAttriType == 3)
	{
		if(strlen(appendNickName) == 0)
		{
			return;
		}
		
		//添加一个玩家的昵称
		snprintf(selfMsg,sizeof(selfMsg),"%d,%d,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s",\
		2,SHOW_MONSTER,MONSTER_TYPE,identity,nickName,photoId,rank,lifeUpperVal,lifeVal,magicUpperVal,\
		magicVal,attack_range,pt._x,pt._y,speed,kindInt,ownerAttriType,appendNickName);
	}
	else
	{
		//添加一个玩家的昵称
		snprintf(selfMsg,sizeof(selfMsg),"%d,%d,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s",\
		2,SHOW_MONSTER,MONSTER_TYPE,identity,nickName,photoId,rank,lifeUpperVal,lifeVal,magicUpperVal,\
		magicVal,attack_range,pt._x,pt._y,speed,kindInt,ownerAttriType,ownerAttri);
	}
	

 #if 0
	snprintf(selfMsg + strlen(selfMsg),sizeof(selfMsg) - strlen(selfMsg),",%s,%d,%d,%d,%d,%d",\
			photoId,rank,lifeUpperVal,lifeVal,magicUpperVal,magicVal);
	
	snprintf(selfMsg + strlen(selfMsg),sizeof(selfMsg) - strlen(selfMsg),",%d,%d,%d,%d,%d",\
			attack_range,pt._x,pt._y,speed,kindInt);
	
	snprintf(selfMsg + strlen(selfMsg),sizeof(selfMsg) - strlen(selfMsg),",%d,%s",\
			,ownerAttriType,ownerAttri);
			
#endif				
	
}

/*获得刷怪信息*/
char* MonsterBase::getBshMsg(void)
{
    return selfMsg;
}

/*实例计时器函数*/
void MonsterBase::initTimer(void)
{
	
	ev_timer_stop(loops,&think_timer);
	
    ext_ev_timer_init(&think_timer,monThkCalBak,MONSTER_THINK_TIME,0, this);

    ev_timer_start(loops,&think_timer);
	
	startMoveTimer();
   
}

/*刷怪函数*/
void MonsterBase::brushMon(void)
{
	StyObj obj(identity,MONSTER_STYLE_TYPE);
	
	Nbox *box;
		
	if(strcmp(getType(),"MonStatuary") != 0)
	{
		initTimer();
	}	
	
	formBshMsg();
	
	formOutMsg();                 
	
	
	box = map_now->getBox();		
	
	if(box == NULL)
	{
		return;
	}
		
	map_now->insertID(obj);
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(selfMsg);
	
	
	if(strcmp(getType(),"EscapeMon") == 0)
	{
		// cout<<"selfMsg:"<<selfMsg<<endl;
	}
	
	isCalled = true;
}


/*怪物自身复活*/
void MonsterBase::reLife(void)
{
	StyObj obj(identity,MONSTER_STYLE_TYPE);
	
	Nbox *box;
	
	formBshMsg();
	
	formOutMsg();                 
	
	box = map_now->getBox();		
	
	if(box == NULL)
	{
		return;
	}	
	
	map_now->insertID(obj);
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(selfMsg);
			
	/*雕像怪则不启动计时器*/
	if(strcmp(getType(),"MonStatuary") == 0)
	{			
		return;
	}	
	ext_ev_timer_init(&think_timer,monThkCalBak,MONSTER_THINK_TIME,0, this);

	ev_timer_start(loops,&think_timer);
	
	startMoveTimer();
	
}


/*刷怪函数*/
void MonsterBase::outScence(void)
{
	
	StyObj obj(identity,MONSTER_STYLE_TYPE);		         
	Nbox *box;                  
	box = map_now->getBox();
	
	if(box == NULL)
	{
		return;
	}
	
	formOutMsg();	
	
	box->getStaInSrcVec(obj);	
	
	box->sentBoxMsg(outMsg);
	
	map_now->deleteID(obj);
	
	/*先停*/
	ev_timer_stop(loops,&think_timer);
}

/*寻路追击函数*/
void MonsterBase::findAttWay(Point &end,bool isPer)
{	
    if(astar == NULL)
    {
        astar = new Astar(map_now);
    }
	
	stopMove(false);
		
    /*如果当前点跟寻路终点重合，则直接返回*/
    if(logic_pt._x == end._x && logic_pt._y == end._y)
    {
        return; 
    }
	
//	printf("curLogic Pt is(%d,%d) \n", logic_pt._x, logic_pt._y);
//	cout<<"end of the findWay:end._x:"<<end._x<<"  end._y:"<<end._y<<endl;
    astar->findWay(logic_pt,end);    //寻得的路径就在astar中
	
//	cout<<"the findAttWay begin  of  logic_pt._x:"<<logic_pt._x<<" logic_pt._y:"<<logic_pt._y<<endl;
	
	if(astar->getWayArr().empty())
	{
		if(!map_now->judgeLogPtHind(logic_pt))
		{
			cout<<"the logicPt is hindPt:"<<endl;
		}
		cout<<"the find way is empty:"<<endl;
		return;
	}
	
	/*以防追人时贴着人走*/
	if(isPer && !astar->getWayArr().empty())
	{
		astar->getWayArr().pop_back();//by benliao to avoid core<it resolve the core chenzhen 12.25>
	}
	
	exchgeWayRod();
	
//	cout<<"the findAttWay begin  of  logic_pt._x:"<<logic_pt._x<<" logic_pt._y:"<<logic_pt._y<<endl;
}

/*封装的消息发送函数,全地图发送*/
void MonsterBase::sendMsg(string msg_perHero,string msg_others)    //整张地图发
{
    if(msg_others.length() == 0)
	{
        return;
	}
    map<string, Hero*>::iterator hero_it;
    string heroMapId;
    Hero *herop;
    for(hero_it = heroId_to_pHero.begin();hero_it != heroId_to_pHero.end();hero_it++)
    {
        herop = hero_it->second;
        heroMapId = herop->getMapId();
        if(strcmp(heroMapId.c_str(),map_now->getMapId()) == 0)
        {
            if(perHerId != NULL && strlen(perHerId) != 0 && strcmp(herop->getIdentity(),perHerId) == 0)
            {
                send_msg(herop->getFd(),const_cast<char*>(msg_perHero.c_str()));
                continue;
            }
            send_msg(herop->getFd(),const_cast<char*>(msg_others.c_str()));
        }
    }
}

/*获得被攻击玩家实例指针*/
Hero* MonsterBase::getHero(char *heroId)
{
    map<string,Hero*>::iterator hero_it;
    hero_it = heroId_to_pHero.find(heroId);
    if(hero_it == heroId_to_pHero.end())
    {
        return	NULL;
    }
    return hero_it->second;
}

/*设置怪物地图实例指针*/
void MonsterBase::setMap(Map_Inform* _map)
{
    if(_map == NULL)
    {
		return;
	}
	
    map_now = _map;

    /*设置相对应的地图id*/
	memset(mapId,'\0',sizeof(mapId));
	
    strncpy(mapId,map_now->getMapId(),strlen(map_now->getMapId()));
    

    /*设置相对应坐标*/
	logic_pt = MapExchangeLogical(pt);
	logic_pt._y += map_now->getBaseDigst();  
	perLstPt = logic_pt;
}



/*怪物再次启动思考函数*/
void MonsterBase::resetTimer(void)		//add chenzhen 6.6
{
	initTimer();
}

/*寻路*/
void MonsterBase::findSlfWay(Point endPt)
{
    /*当仇恨范围为空时，则走自己的路*/
    if(astar == NULL)
    {
        astar = new Astar(map_now);
    }
	
	stopMove();
	
    /*此处findWay方法占用大量的cpu，需要优化*/
    astar->findWay(logic_pt,endPt);    //寻得的路径就在astar中	

	exchgeWayRod();
}


/* 搜寻自己一个屏幕上的hero，看是不是在仇恨范围内*/
void MonsterBase::schRge(void) 
{
	set<string>::iterator her_it;
	set<string>HeroIdSet;	
    list<HatVal>new_enmy;	
	Point heroPt;       
	Hero *myHero;
	Nbox *box;
	bool isCpy;
	
	isCpy = false;
	
	box = map_now->getBox();
	if(box == NULL)
	{
		return;
	}
	
	box->getCentPtSrcHerIdSet(pt,HeroIdSet);	
    
	
    for(her_it = HeroIdSet.begin(); her_it != HeroIdSet.end(); ++her_it)
    {		
		myHero = heroid_to_hero(*her_it);
        if(myHero == NULL || myHero->getLifeStation() == DEAD || !myHero->getWalkingFlg())
        {
            continue;
        }
        /*为了减少误差，用像素判断*/
        heroPt = myHero->getLocation();   
		
		// cout<<"heroPt._x:"<<heroPt._x<<endl;
		// cout<<"heroPt._y:"<<heroPt._y<<endl;
		
		// cout<<"hatRge:"<<hatRge<<endl;
        /*判断是否在仇恨范围内*/		
		/*现在是以出生点为圆心，仇恨范围不动的格式做的*/
		
        if(sqrt(pow(fabs(heroPt._x - born_pt._x),2)+pow(fabs(heroPt._y - born_pt._y),2)) <= hatRge)
        {
            HatVal hat(const_cast<char *>((*her_it).c_str()),hatValRue->getHatInRag());
            new_enmy.push_back(hat);
			
			myHero->insertAttList(identity);
        }
    }
	
	
	if(map_now != NULL && map_now->getFlgCpy())
	{
		//isCpy = true; copy and wild same. by benliao 2012.12.09
		enmityValues.swap(new_enmy);
	}
	else
	{
		/*交换新仇恨列表*/
		enmityValues.swap(new_enmy);		
	}
	
	int flag;
	/*这里调用一个函数，进行仇恨值列表和物品归属进行操作*/
	flag = HatFun(enmityValues,new_enmy,perHerId,goodsOwner,identity,isCpy);
	
    /*仇恨列表为空*/
    if(enmityValues.empty())
    {
        /*把当前目标玩家至空*/ 
		if(strlen(perHerId) != 0) 
		{
			memset(perHerId,'\0',SHOR_MID_VALUE_LENGTH + 1);
		}
		
		/*把当前物品归属玩家至空*/
        if(strlen(goodsOwner) != 0)      //add chenzhen 6.8
        {
			memset(goodsOwner,'\0',IDL + 1);
        }
        return;
    }

   
	
    list<HatVal>::iterator hatf_it;  //仇恨列表头结点（仇恨值最大）
    list<HatVal>::iterator hats_it;  //仇恨列表头第二结点（仇恨值第二大）
	
	sortByPt();
	
    /*如果目标不为空，且目标还在仇恨范围内*/
    if(flag > 0)
    {
        /*仇恨列表中不止1个人*/
        if(enmityValues.size() >= 2)
        {
            hatf_it = enmityValues.begin();
            hats_it =  hatf_it;
            ++hats_it ;
			
            /*判断是否满足条件，更改目标*/
            if(perHerId != NULL && strcmp(perHerId,(*hatf_it).id) == 0 && (*hats_it).value > (*hatf_it).value * hatValRue->getChageAirPer())
            {
                chageEny(((*hats_it).id));
            }
			else
			{
				/*更改目标为仇恨列表的头结点*/
				chageEny((*hatf_it).id);  
			}
//			cout<<"(*hats_it).value:"<<(*hats_it).value<<endl;
//			cout<<"(*hats_it).id:"<<(*hats_it).id<<endl;
//			cout<<"(*hatf_it).value + :"<<(*hatf_it).value * hatValRue->getChageAirPer()<<endl;
//			cout<<"(*hatf_it).id:"<<(*hatf_it).id<<endl;
			
        }
    } 
	else
    {
		
        /*更改目标为仇恨列表的头结点*/
        chageEny((*(enmityValues.begin())).id);      
    }
}   

MonsterBase::~MonsterBase(void)
{	
    ev_timer_stop(loops,&think_timer);
	
	stopMoveTimer();
	
    if(astar !=NULL)
    {
        delete astar;
        astar = NULL;
    }
    if(enmityValues.empty())
    {
        enmityValues.clear();
    }
    if(skill_list.empty())
    {
        skill_list.clear();
    } 
	deleteSkillInst();
}

/*怪物析构时，释放技能实例*/
void MonsterBase::deleteSkillInst(void)
{	
	int i,length;
	SkillBase *skill;
	
	if(skiInstSet.empty())
	{
		return;
	}
	
	length = skiInstSet.size();	
	
	for(i = 0;i < length;++i)
	{
		skill = skiInstSet[i];
		delete skill;
		skill = NULL;
		skiInstSet[i] = skill;
	}
	skiInstSet.clear();
}
		

/*死亡函数*/
void MonsterBase::die(bool flgInit)
{
	StyObj obj(identity,MONSTER_STYLE_TYPE);		
	Nbox *box;
	
	box= map_now->getBox();	
	
	if(box == NULL || isAlive)
	{
		cout<<"it is error of the monster die:"<<identity<<endl;
		return;
	}	
	
	stopMove();	
	
	/*暂停任务怪存活计时器*/		
	ev_timer_stop(loops,&taskTime);	
	
	ev_timer_stop(loops,&cdTimer);
	
	if(strcmp(type,"MonStatuary") != 0)
	{
		/*暂停回血计时器*/
		ev_timer_stop(loops,&bloodTimer);			
	}
	
	ev_timer_stop(loops,&think_timer);	
	
	/*死亡消息*/
	ext_ev_timer_init(&think_timer,monThkCalBak,2,0, this);
	
	ev_timer_start(loops,&think_timer);		
	
	if(map_now->getFlgCpy())
	{
		/*非被召唤怪*/
		if(!isCallType)
		{
			/*发送怪物数目信息*/
			map_now->killOneMon();	
		
			map_now->sentSumMonMsg();	
		}
		
		/*复活次数已满*/
		if(!lveCtnMager.isLveCtn())
		{
			map_now->GromonDead(identity);
		}
	}
	
	if(ownerAttriType == 3)
	{
		cout<<"taskOwnerId is "<<taskOwnerId<<endl;
		
		Hero *perHero = getHero(taskOwnerId);
		if (perHero == NULL)
		{
			return;
		}
		cout<<"Type Id is "<<typeId<<endl;
		char *needId = typeId;
		needId++;needId++;
		perHero->updateHeroTaskStatus(KILL_NPC_BOSS_TASK_NEED_TYPE, needId);
		perHero->clrTskStSomeBit(TASK_NEED_KILL_NPC_BOSS);
	}	
	
}

/*重置怪物部分属性*/
void MonsterBase::initMonsterBaseAsist(void)
{	
	 /*清空仇恨列表*/
	dealPerByEmy();
	
    enmityValues.clear();

    /*清空A*所寻得路径*/
    if(astar != NULL)
    {
        astar->getWayArr().clear();
    }	 
	
	/*生命值复原*/
    lifeVal = lifeUpperVal; 
	
	/*魔法值复原*/
	magicVal = magicUpperVal;	
	
	/*出生点复原*/
	pt = born_pt;
	
#if 0
	cout<<"MonsterBase::initMonsterBaseAsist begin:"<<endl;
	cout<<"id:"<<identity<<" pt._x:"<<pt._x<<" pt._y:"<<pt._y<<endl;
	cout<<"MonsterBase::initMonsterBaseAsist end:"<<endl;
#endif
	
	/*逻辑点复原*/
	logic_pt = MapExchangeLogical(pt);	
	logic_pt._y += map_now->getBaseDigst(); 
	
	/*路径点复原*/
	perLstPt = logic_pt;
	
	/*生命状态复原*/
	isAlive = true;
	
	/*路径迭代器复原*/
	pt_it = selfWay.begin();
	
	/*目标器复原*/
	memset(perHerId,'\0',SHOR_MID_VALUE_LENGTH + 1); 
	
	/*重置标记值*/
	initFlgVal();
	
	/*重置攻防值*/
	initRecAttDef();
		
	/*重置怪物所受延时性技能影响*/
	initHitedSki();
	
	/*重置掉落物品主人id*/
	memset(goodsOwner,'\0',IDL + 1);
	
	/*重置自卫反应值*/
	repFlg = false;
	
	/*追人点重置*/
	initPersuitPt();
	
	/*技能重置*/
	delSki();	
	
	/*巡逻标记值重置*/
	isInPatrol = false;	
	
	/*是否受到攻击标记值*/
	isHurt = false;
	
	/*播放cd*/
	plyCdCtn = 0;
	
	/*暂停*/
	stopMove();	
	
	/*暂停‘走路’计时器*/
	stopMoveTimer();
	
	/*设置回血计时器开启标记值*/
	isBloodTmeOpenFlg = false;
	
	/*设置追人标记值*/
	isPersuitHero = false;
	
	//任务怪处理
	if(getOwnerAttriType() == 3 || getOwnerAttriType() == 4)
	{
		ev_timer_stop(loops,&taskTime);	
		
		if(getOwnerAttriType() == 3)
		{
		#if 0
			memset(nickName,'\0',sizeof(nickName));
			strncpy(nickName,appendNickName,strlen(appendNickName));
		#endif
			memset(appendNickName,'\0',sizeof(appendNickName));
		}
		memset(taskOwnerId,'\0',sizeof(taskOwnerId));	
		isUsed = false;		
	}
	
	isCalled = false;
	
	isCdCool = true;		
}

/*重置整个怪物数据*/
void MonsterBase::initMonsterALL(void)
{
	stopMove();
	
	ev_timer_stop(loops,&moveTimer);	
	
	ev_timer_stop(loops,&think_timer);	
	
	initMonsterBaseAsist();
	
	lveCtnMager.initCover();
	
	
	
	/*暂停回血计时器*/
	ev_timer_stop(loops,&bloodTimer);	
	
	callBoss = NULL;

}
	
/*Boss逃跑函数*/
void MonsterBase::escape(void)
{
    if(strcmp(kind,"Boss") == 0 && lifeVal < (1.0/3) * lifeUpperVal)   //这个1/3要从配置文件里面读，
    {
        flgRun = true;
        Point mapIntPt = map_now->getEntPt();
        Point mapIntLogPt;
        mapIntLogPt = MapExchangeLogical(mapIntPt);
        mapIntLogPt._y += map_now->getBaseDigst();

        findSlfWay(mapIntLogPt);    //寻得的路径就在astar中	
		initPersuitPt();
    }

}

/* 插入仇恨id，有则叠加，没有则添加*/
void MonsterBase::InpushEnmityValues(HatVal &hatva)
{
    
    list<HatVal>::iterator enmityValues_it;
    for(enmityValues_it = enmityValues.begin();enmityValues_it != enmityValues.end();++enmityValues_it)
    {
        if(strcmp((*enmityValues_it).id, hatva.id) == 0)
		{
            (*enmityValues_it).value += hatva.value;    
             break;
        }
    }
    if(enmityValues_it == enmityValues.end())
    {
        enmityValues.push_back(hatva);
    }
    enmityValues.sort(ComFun);
   
}

/*获得diedNoThink的值*/
bool MonsterBase::getDiedNoThink(void)
{
	return false;
}

/*暂停思考*/
void MonsterBase::stopThk(void)         
{
	ev_timer_stop(loops,&think_timer);
}	

/*初始化技能实例指针列表*/
void MonsterBase::initSkiInst(vector<string> &_skiIdSet)
{
	if(_skiIdSet.empty())
	{
		return;
	}
	
	vector<string>::iterator skiId_it;
	map<string,SkillBase*>::iterator skiInst_it;
	SkillBase *skill;
	skill = NULL;
	for(skiId_it = _skiIdSet.begin();skiId_it != _skiIdSet.end();++skiId_it)
	{
		skiInst_it = monster_skill_map.find(*skiId_it);
		if(skiInst_it != monster_skill_map.end())
		{
			skill = skiInst_it->second->copySkillInst(this);
			monSkiInst[skill->getId()] = skill;
			skiInstSet.push_back(skill);			
		}
		
	}
}

/*获得技能id列表*/
void MonsterBase::getSkiIdSet(vector<string> &skillIdSet)
{
	
	if(skiInstSet.empty())
	{
		return;
	}
	
	vector<SkillBase*>::iterator skiInst_it;
	for(skiInst_it = skiInstSet.begin();skiInst_it != skiInstSet.end();++skiInst_it)
	{
		string skiId = (*skiInst_it)->getId();		
		skillIdSet.push_back(asistSkiId(skiId));
	}
	return;
}

# if 0

/*使用技能*/
bool MonsterBase::useSkill(vector<string> &herId,bool _station)
{
	/*测试打印技能*/
	// testPrintSki();	
	
	if(skiInstSet.empty())
	{
		return false;
	}
	
	vector<SkillBase*>::iterator skiInst_it;
	for(skiInst_it = skiInstSet.begin();skiInst_it != skiInstSet.end();++skiInst_it)
	{
		if((*skiInst_it)->useSkill(herId,_station))
		{
			return true;
		}
	}
	return false;
}

#endif
void MonsterBase::exchageHat(vector<string> &herId)
{	
	list<HatVal>::iterator hat_it; 
	if(enmityValues.empty())
	{
		return;
	}
	for(hat_it = enmityValues.begin();hat_it != enmityValues.end();++hat_it)
	{	
		herId.push_back((*hat_it).id);
	}
	return;
}

/*怪物死亡处理技能函数*/
void MonsterBase::delSki(void)
{	
    if(skiInstSet.empty())
	{
		return ;
	}
	
	vector<SkillBase*>::iterator skiInst_it;
	for(skiInst_it = skiInstSet.begin();skiInst_it != skiInstSet.end();++skiInst_it)
	{
		(*skiInst_it)->ownerDie();
	}
}

/*测试打印Boss技能*/
void MonsterBase::testPrintSki(void)
{
	vector<SkillBase*>::iterator skiInst_it;
	cout<<"test skill begin:"<<endl;
	if(skiInstSet.empty())
	{
		cout<<"skill Inst is empty:"<<endl;
	}
	
	for(skiInst_it = skiInstSet.begin();skiInst_it != skiInstSet.end();++skiInst_it)
	{
		cout<<"skill id:"<<(*skiInst_it)->getId()<<endl;
	}
	cout<<"test skill end:"<<endl;
}

/*辅助生成技能id*/
string MonsterBase::asistSkiId(string &_skiId)
{
	int founds;
	string result;
	founds = _skiId.find_last_of("_");
	if(founds == string::npos)
	{
		return result;
	}
	
	result = _skiId.substr(founds + 1);
	return result;
}

/*攻击消息生成函数*/
void MonsterBase::formAttMsg(char *msg_others,int length,Hero *hitHero,int attack,int attFlg,int voidFlg)
{
	int perSon = 1;
	int lifeValChgSelf = 0;
	int isBounce = 0;
	

	/*add chenzhen 20130124，等客户端的新的攻击命令改好*/
	snprintf(msg_others,length,"%d,%d,%d,%s,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d,%d,%d,%d",\
	FIGHT_FRIST_HEAD,FIGHT_SECOND_HEAD,SUCCESS,genAttId,playCd,identity,lifeVal,\
	lifeUpperVal,magicVal,magicUpperVal,lifeValChgSelf,isBounce,attFlg,perSon,\
	hitHero->getIdentity(),hitHero->getLifeVal(),hitHero->getLifeUpperVal(),\
	hitHero->getMagicVal(),hitHero->getMagicUpperVal(),attack,voidFlg);
	

	
#if 0
	snprintf(msg_others,length,"%d,%d,%d,%s,%d,%s,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d",\
	FIGHT_FRIST_HEAD,FIGHT_SECOND_HEAD,SUCCESS,\
	genAttId,playCd,identity,lifeVal,magicVal,\
	lifeValChgSelf,isBounce,attFlg,perSon,hitHero->getIdentity(),\
	hitHero->getLifeVal(),attack,voidFlg);
#endif
	
}
   
   
/*获得普通攻击值*/
int MonsterBase::countAttPerGen(Hero *perHero)
{
    int genAtt;  //普通攻击值     

	/*普通攻击计算*/	
	if(!isInnerAttack)
	{
		genAtt = (outAttVal * (1 - perHero->ctnDefenseRatio(false))) * 1;
	}	
	else
	{
		/*偏内功*/
		genAtt = (inAttVal * (1 - perHero->ctnDefenseRatio(true))) * 1;
	}
	
	return genAtt;
	
	
#if 0
	/*普通攻击计算*/
    genAtt = outHrt * 2 * outAttVal/(outHrt + perHero->getOutDefense()) +\
			 inHrt * 2 * inAttVal/(inHrt + perHero->getInDefense());
	
	return genAtt;
#endif
			 
#if 0
    /*普通攻击计算,20130119*/
    genAtt = outHrt * 2 * outAttVal/(outAttVal + perHero->getOutDefense()) +\
			 inHrt * 2 * inAttVal/(inAttVal + perHero->getInDefense());
			 
	return genAtt;
#endif
   
}

/*计算暴击率*/
int MonsterBase::coutFlgCrit(double &critTme)
{
	double critPer;        //暴击率    
	int flgCrit;       //暴击
	flgCrit = 0;	
	
	/*暴击率计算*/
    if(int(crit) <= 5000)
    {
        critPer = 0.0001 * crit;
        critTme = 2;
    }
	else
    {
        critPer = 0.5;
        critTme = 1 + 0.0002 * crit;
    }
	
	
    int critRand = rand()%1000;
	
	/*暴击随机数*/
    if(critRand <= critPer * 1000)
    {
        flgCrit = 1;
    }
	return flgCrit;
}

/*计算暴击率<后面更改的公式20130110*/
int MonsterBase::coutFlgCrit(Hero *perHero,double &critTme)
{
	double critPer;        //暴击率    
	int flgCrit;       //暴击
	flgCrit = 0;
	int hitTen;        //被攻击者韧性
	hitTen = perHero->getTenacity();
	
	if(crit <= hitTen)
	{
		critPer = 0.1;
		
		critTme = 1.1;
	}
	else
	{
		critPer = 0.1 + 0.9*(crit - hitTen)*0.002*\
		(1 + (crit - hitTen)*0.002);
		
		critTme = 1.1 + 0.002*(crit - hitTen);
	}

    int critRand = rand()%1000;
	
	/*暴击随机数*/
    if(critRand <= critPer * 1000)
    {
        flgCrit = 1;
    }
	return flgCrit;
}


/*计算闪避率*/
int MonsterBase::coutFlgVoid(Hero *perHero,double &hitPer)
{
	int flgVoid;          //闪避率（只有2个值，0为闪避失败，1为闪避成功）
	double heroVoidPer ;  //被攻击者闪避率   
    int heroVoid ;       //被攻击者闪避值
	
	flgVoid = 0;
	
	/*被攻击者闪避值*/
	heroVoid = perHero->getDodge(); 
	if(heroVoid < hit)
	{
		heroVoidPer = 0.05;
	}
	else
	{
		heroVoidPer = 0.05 + 0.95*0.002*(heroVoid - hit)\
		/(1 + 0.002*(heroVoid - hit));
	}
	
	hitPer = 1;
	
		
	/*闪避随机数*/
	int randNum = rand()%1000;
    if(randNum >= heroVoidPer * 1000)
    {
        flgVoid = 1;
    }
	return flgVoid;
	
	
	
#if 0
	/*原来的战斗公式*/
	
	/*被攻击者闪避值*/
	heroVoid = perHero->getDodge();   
	
	/*闪避计算*/
    if(heroVoid < VOID_BASE_NUM)            //闪避率计算
    {
        heroVoidPer = (1.0 * ATTACK_VOID_BASE_NUM * heroVoid) /(1+ ATTACK_VOID_BASE_NUM * heroVoid);
        hitPer = 1 + ATTACK_VOID_BASE_NUM * hit;

    } 
	else if(VOID_BASE_NUM <= heroVoid && heroVoid < hit + VOID_BASE_NUM)
    {
        heroVoidPer = (1.0 * VOID_BASE ) /(1+ VOID_BASE);
        hitPer = 1 + ATTACK_VOID_BASE_NUM * (hit + VOID_BASE_NUM - heroVoid);
    }
	else
    {
        heroVoidPer = (1.0 * ATTACK_VOID_BASE_NUM * (heroVoid - hit))/(1 + ATTACK_VOID_BASE_NUM *(heroVoid - hit)) ;
        hitPer = 1.0;
    }

    /*闪避随机数*/
	int randNum = rand()%1000;
    if(randNum >= heroVoidPer * 1000)
    {
        flgVoid = 1;
    }
	return flgVoid;
#endif	

}

/*计算伤害值，技能也可以用*/
int MonsterBase::countAttVal(int genAtt,Hero *perHero,int &attTypeFlg,int &attVoidFlg,double skiHrtRatio,double _cdTime)
{
	/*无暴击无闪避*/
	attTypeFlg = 0;     
	attVoidFlg = 0;
    int flgVoid ;       //闪避
	int flgCrit;       //暴击
	double tenDue;     //韧性
	double tenDueRes;  //韧性减行
	int attack;        //攻击伤害	
	
	double hitPer ;       //命中率 
	double critTme;           //暴击倍数
	
	/*计算命中率*/
	flgVoid = ctnHitRatio(perHero->getDodge());
	
	if(flgVoid == 0)
	{
		attVoidFlg = 1;
	}
	
	/*计算暴击率*/
	flgCrit = ctnCritRatio(perHero);
	
	if(flgCrit == 1)
	{
		attTypeFlg = 1;
	}	
	
	/*暴击为2倍*/
	attack = attTypeFlg == 0 ? flgVoid * genAtt * 1:flgVoid * genAtt * 2;
	
	
	
	
#if 0
	/*计算闪避率*/
	flgVoid = coutFlgVoid(perHero,hitPer);
	
	if(flgVoid == 0)
	{
		attVoidFlg = 1;
	}
	
	/*计算暴击率*/
	flgCrit = coutFlgCrit(perHero,critTme);
	
	if(flgCrit == 1)
	{
		attTypeFlg = 1;
	}
	
	
	/*计算韧性减行*/
	tenDue = 0.0001 * perHero->getTenacity();       //韧性减行
    tenDueRes = tenDue/(1 + tenDue);
#endif


#if 0
	/*20130410注释*/
	/*最终伤害值*/
    attack = flgVoid * (genAtt * (1 * _cdTime + skiHrtRatio) +\
			 flgCrit * (genAtt * (1 * _cdTime + skiHrtRatio) *\
			 critTme - genAtt * (1 * _cdTime + skiHrtRatio)) *\
			 (hitPer * (1 - tenDueRes)));
#endif

#if 0			 
	if(attack == 0)
	{
		attack = 0;
	}
#endif

    /*测试用，减少伤害值*/
    // attack = rand()%15;
	return attack;
}

/*攻击玩家函数*/
void MonsterBase::attPerHero(char *msg_others,int length,Hero *perHero,bool moveFlg,double skiHrtRatio,double _cdTime)
{
	char stopPos[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	int genAtt;  //普通攻击值
	int attack;  //伤害值	
	int heroLife;
	int attTypFlg;   //暴击
	int voidFlg;     //闪避类型
		
	cancelSit(perHero);
	
	StyObj obj(identity,MONSTER_STYLE_TYPE);
	Nbox *box;

	box = map_now->getBox();
	
	if(box == NULL)
	{
		return;
	}	
	
	box->getStaInSrcVec(obj);
	
	
	if(perHero == NULL)
	{
		return;
	}
	
	perHero->stopCollectTimer(3);
	
	/*如果是跑过来攻击的，则不计算cd时间*/
	if(!moveFlg && !repFlg)
	{
		if(!isCdCool || !judgeAtt(perHero))
		{
			return;
		}
	}  
	
	/*人物处于无敌状态,add by chenzhen 20130128*/
	if(perHero->skillBuffState & BUFF_INVINCIBLE_STATE)
	{
		return;
	}
	
	/*设置自卫状态值*/
	repFlg = false;
	
	/*击杀红名怪*/
	if(strcmp(getType(),"AttRedMon") == 0)
	{
		attack = attackRatio * perHero->getLifeUpperVal();
	}
	else
	{
		genAtt = countAttPerGen(perHero);
		attack = countAttVal(genAtt,perHero,attTypFlg,voidFlg,skiHrtRatio,_cdTime);
	}
	if(attack != 0)
	{
#if 0
		//没有五行伤害，目前
		FiveElem *heroFive = perHero->getFiveElem();	
		attack += getFiveElemHurt(fiveElement, heroFive); 
#endif
	}
	
	heroLife = perHero->getLifeVal();	
	
	//类似血包技能
	if (perHero->skillBuffState & BUFF_MAGIC_SHIELD_STATE)
	{
		int decHurt = perHero->skillBuff[perHero->getIndexByState(BUFF_MAGIC_SHIELD_STATE)].perVal;
		if (attack >= decHurt)
		{
			int lastAttack = attack - decHurt;
			perHero->skillBuff[perHero->getIndexByState(BUFF_MAGIC_SHIELD_STATE)].perVal = 0;
			int index = perHero->getIndexByState(BUFF_MAGIC_SHIELD_STATE);
			perHero->stop_buff_debuff_by_index(index);
		
			if(heroLife - lastAttack  <= 0)
			{
				heroLife = 0;
			}
			else
			{
				heroLife -= lastAttack;
			}
	
			if(heroLife == 0)
			{
				perHero->setLifeStation(DEAD);
			}
	
			perHero->setLifeVal(heroLife);	
		}
		else
		{			
			perHero->skillBuff[perHero->getIndexByState(BUFF_MAGIC_SHIELD_STATE)].perVal -= attack;
			attack = 0;
		}		
	}
	
	else
	{
		if(heroLife - attack  <= 0)
		{
			heroLife = 0;
		}
		else
		{
			heroLife -= attack;
		}
	
		if(heroLife == 0)
		{
			perHero->setLifeStation(DEAD);
		}		
		perHero->setLifeVal(heroLife);
	}
	
	
	
	formAttMsg(msg_others,length,perHero,attack,attTypFlg,voidFlg);	
	
	isHurt = true;
	
	plyCdCtn = 0;
	
	isCdCool = false;
	
	ev_timer_stop(loops,&cdTimer);
	
    ext_ev_timer_init(&cdTimer,monCdCalBal,cdTime,0, this);

    ev_timer_start(loops,&cdTimer);
	
	
}
/*判断攻击玩家是否已死或者不存在*/
bool MonsterBase::judgeAtt(Hero *perHero)
{
    /*判断玩家是否已死*/
    if(perHero == NULL || perHero->getLifeVal() <= 0 )
    {
        return false;
    }	
	return true;
}


/*群攻攻击消息生成函数*/
void MonsterBase::skiAttHero(char *msg_others,int legnthStr,vector<string> &heroIds,char *skiId,double skiHrtRatio,double _cdTime)
{
	char midMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	int genAtt;  //普通攻击值
	int attack;  //伤害值	
	int attTypFlg;   //暴击
	int voidFlg;     //闪避类型  
	vector<string>::iterator heroId_it;
	Hero *perHero;
	int realPersonCnt;
	int lifeBefore,heroLife;
	perHero = NULL;
	
	if(msg_others == NULL || skiId == NULL || strlen(skiId) == 0)
	{
		return;
	}	
	
	
	
	/*add chenzhen 20130124，等客户端的新的攻击命令改好*/
	snprintf(msg_others,legnthStr,"%d,%d,%d,%s,%d,%s,%d,%d,%d,%d,%d,%d",\
			FIGHT_FRIST_HEAD,FIGHT_SECOND_HEAD,SUCCESS,\
			skiId,playCd,identity,lifeVal,lifeUpperVal,magicVal,magicUpperVal,0,0);

	
#if 0
	snprintf(msg_others,legnthStr,"%d,%d,%d,%s,%d,%s,%d,%d,%d,%d",\
			FIGHT_FRIST_HEAD,FIGHT_SECOND_HEAD,SUCCESS,\
			skiId,playCd,identity,lifeVal,magicVal,0,0);
#endif
	for(heroId_it = heroIds.begin(),realPersonCnt = 0;heroId_it != heroIds.end();heroId_it++)
	{
		perHero = getHero(const_cast<char *>((*heroId_it).c_str()));
		if(!perHero)
		{
			continue;
		}
		
		/*人物处于无敌状态,add by chenzhen 20130128*/
		if(perHero->skillBuffState & BUFF_INVINCIBLE_STATE)
		{
			continue;
		}
		
		realPersonCnt ++;
		genAtt = countAttPerGen(perHero);
		lifeBefore = perHero->getLifeVal();
		heroLife = lifeBefore;
		
		/*击杀红名怪*/
		if(strcmp(getType(),"AttRedMon") == 0)
		{
			attack = attackRatio * perHero->getLifeUpperVal();
		}
		else
		{
			attack = countAttVal(genAtt,perHero,attTypFlg,voidFlg,skiHrtRatio,_cdTime);
		}
		
		//类似血包技能
		if (perHero->skillBuffState & BUFF_MAGIC_SHIELD_STATE)
		{
			int decHurt = perHero->skillBuff[perHero->getIndexByState(BUFF_MAGIC_SHIELD_STATE)].perVal;
			if (attack >= decHurt)
			{
				int lastAttack = attack - decHurt;
				perHero->skillBuff[perHero->getIndexByState(BUFF_MAGIC_SHIELD_STATE)].perVal = 0;
				int index = perHero->getIndexByState(BUFF_MAGIC_SHIELD_STATE);
				perHero->stop_buff_debuff_by_index(index);
				if(heroLife - lastAttack  <= 0)
				{
					heroLife = 0;
				}
				else
				{
					heroLife -= lastAttack;
				}
	
				if(heroLife == 0)
				{
					perHero->setLifeStation(DEAD);
				}		
				perHero->setLifeVal(heroLife);
			}
			else
			{			
				perHero->skillBuff[perHero->getIndexByState(BUFF_MAGIC_SHIELD_STATE)].perVal -= attack;
				attack = 0;
			}
		}
		
		else
		{		
			if(heroLife - attack  <= 0)
			{
				heroLife = 0;
			}
			else
			{
				heroLife -= attack;
			}
	
			if(heroLife == 0)
			{
				perHero->setLifeStation(DEAD);
			}
	
			perHero->setLifeVal(heroLife);	
		}	
			
		
		cancelSit(perHero);

		/*add chenzhen 20130124，等客户端的新的攻击命令改好*/
		snprintf(midMsg + strlen(midMsg),sizeof(midMsg) - strlen(midMsg),",%s,%d,%d,%d,%d,%d,%d",\
				perHero->getIdentity(),heroLife,perHero->getLifeUpperVal(),\
				perHero->getMagicVal(),perHero->getMagicUpperVal(),attack,voidFlg);

		
#if 0
		snprintf(midMsg + strlen(midMsg),sizeof(midMsg) - strlen(midMsg),",%s,%d,%d,%d,%d,%d,%d",\
				perHero->getIdentity(),heroLife,perHero->getLifeUpperVal(), perHero->getMagicVal(),
				perHero->getMagicUpperVal(), attack,voidFlg);
#endif
	}
	snprintf(msg_others + strlen(msg_others),legnthStr - strlen(msg_others),",%d,%d",attTypFlg,realPersonCnt);
	strncat(msg_others,midMsg,strlen(midMsg));

	if(realPersonCnt == 0)
	{
		memset(msg_others,'\0',MONSTER_ROAD_LENGTH + 1);
		return;
	}
	
	isHurt = true;
	plyCdCtn = 0;
}

/*判断是否为Boss怪，是返回1，否则返回0*/	
bool MonsterBase::judgeBoss(void)
{
	if(strcmp(kind,"Boss") == 0)
	{
		return true;
	}
	return false;
}	
   
/*被延时性技能攻击*/
void MonsterBase::inputHitTime(char *attId,int typeEffect,double lastTme,int value)
{
	SkillTime newSkiTime(attId,lastTme,typeEffect,value);
	
	/*如果为非叠加延时性技能,定身*/
	if(typeEffect == MON_DEBUF_FORB_MOVE_STATE)
	{		
		oneAtt.clear();	
		{
			std::vector<SkillTime> tmp;
			oneAtt.swap(tmp);
		}				
		oneAtt.push_back(newSkiTime);		
	}
	/*如果为非叠加延时性技能,点穴*/
	if(typeEffect == MON_DEBUF_FORB_ATTK_STATE)
	{		
		oneAttPt.clear();
		{
			std::vector<SkillTime> tmp;
			oneAttPt.swap(tmp);
		}
		
		oneAttPt.push_back(newSkiTime);		
	}
	/*如果为非叠加延时性技能,眩晕*/
	if(typeEffect == MON_DEBUF_DIZZ_STATE)
	{		
		oneAttDizz.clear();	
		{
			std::vector<SkillTime> tmp;
			oneAttDizz.swap(tmp);
		}		
		oneAttDizz.push_back(newSkiTime);		
	}
	
	/*如果为叠加延时性技能,持续掉血*/
	else if(typeEffect == MON_DEBUF_IN_POISON_STATE)
	{
		moreAtt.push_back(newSkiTime);
	}
	/*如果为叠加延时性技能,攻防*/
	else if(typeEffect == MON_DEBUF_LOSE_DF_AT_STATE)
	{
		if(!judgeAttDef())
		{
			return;
		}
		moreAttDef.push_back(newSkiTime);
		reduceAttDef(newSkiTime);
	}
	/*如果为叠加延时性技能，韧性*/
	else if(typeEffect == MON_DEBUF_LOSE_TENC_STATE)
	{
		if(!judgeAttTen())
		{
			return;
		}
		moreAttTen.push_back(newSkiTime);
		reduceAttTen(newSkiTime);
	}
	/*如果为叠加延时性技能，命中*/
	else if(typeEffect == MON_DEBUF_LOSE_HIT_STATE)
	{
		if(!judgeAttHit())
		{
			return;
		}
		moreAttHit.push_back(newSkiTime);
		reduceAttHit(newSkiTime);
	}
}


/*被延时性技能攻击*/
void MonsterBase::inputHitTime(double _cdTimes,int _flgType,int _dropBlood,char *_heroId,int _outAttVals,\
							   int _inAttVals,int _outDefVals,int _inDefVals)
{
	// SkillTime newSkiTime(_cdTimes,_flgType,_dropBlood,_heroId,_outAttVals,_inAttVals,_outDefVals,_inDefVals);
	
	// /*如果为非叠加延时性技能,定身*/
	// if(_flgType == 0)
	// {		
		// oneAtt.clear();		
		// oneAtt.push_back(newSkiTime);		
	// }
	// /*如果为非叠加延时性技能,点穴*/
	// if(_flgType == 1)
	// {		
		// oneAttPt.clear();		
		// oneAttPt.push_back(newSkiTime);		
	// }
	// /*如果为非叠加延时性技能,眩晕*/
	// if(_flgType == 2)
	// {		
		// oneAttDizz.clear();		
		// oneAttDizz.push_back(newSkiTime);		
	// }
	
	// /*如果为叠加延时性技能*/
	// else if(_flgType == 3)
	// {
		// moreAtt.push_back(newSkiTime);
	// }
	// /*如果为叠加延时性技能,攻防*/
	// else if(_flgType == 4)
	// {
		// if(!judgeAttDef())
		// {
			// return;
		// }
		// moreAttDef.push_back(newSkiTime);
		// reduceAttDef(newSkiTime);
	// }
	// /*如果为叠加延时性技能，韧性*/
	// else if(_flgType == 5)
	// {
		// if(!judgeAttTen())
		// {
			// return;
		// }
		// moreAttTen.push_back(newSkiTime);
		// reduceAttTen(newSkiTime);
	// }
	// /*如果为叠加延时性技能，命中*/
	// else if(_flgType == 6)
	// {
		// if(!judgeAttHit())
		// {
			// return;
		// }
		// moreAttHit.push_back(newSkiTime);
		// reduceAttHit(newSkiTime);
	// }
}



/*被延时性技能攻击,重载*/
void MonsterBase::hitedEffectBySki(SkillTime &_skiTme)
{
	char msg_others[MONSTER_MSG_LENGTH + 1] = {0};	
	
	/*定身*/
	if(_skiTme.effectType == MON_DEBUF_FORB_MOVE_STATE)
	{
		skiBody = false;
		
	}
	/*点穴*/
	if(_skiTme.effectType == MON_DEBUF_FORB_ATTK_STATE)
	{
		attackPoint = false;
		
	}
	/*眩晕*/
	if(_skiTme.effectType == MON_DEBUF_DIZZ_STATE)
	{
		dizz = false;		
	}
	/*持续掉血*/
	else if(_skiTme.effectType == MON_DEBUF_IN_POISON_STATE)
	{
		formDropBldMsg(_skiTme,msg_others,sizeof(msg_others));	                   
	    sendDropBldMsg(_skiTme,msg_others);              		
	}
	/*降低攻防*/
	else if(_skiTme.effectType == MON_DEBUF_LOSE_DF_AT_STATE)
	{
		
	}
}

/*调用被击覆盖类技能,定身*/
void MonsterBase::callOneAtt(void)
{
	if(oneAtt.empty())
	{
		skiBody = true;
		return;
	}
	oneAtt[0].gain();
	if(!oneAtt[0].timeOut())
	{
		hitedEffectBySki(oneAtt[0]);
	}
	else
	{
		oneAtt.clear();
		skiBody = true;
	}
}

/*调用被击覆盖类技能,点穴*/
void MonsterBase::callOneAttPt(void)
{
	if(oneAttPt.empty())
	{
		attackPoint = true;
		return;
	}
	oneAttPt[0].gain();
	if(!oneAttPt[0].timeOut())
	{
		hitedEffectBySki(oneAttPt[0]);
	}
	else
	{
		oneAttPt.clear();
		attackPoint = true;
	}
}

/*调用被击覆盖类技能,眩晕*/
void MonsterBase::callOneAttDizz(void)
{
	if(oneAttDizz.empty())
	{
		dizz = true;
		return;
	}
	oneAttDizz[0].gain();
	if(!oneAttDizz[0].timeOut())
	{
		hitedEffectBySki(oneAttDizz[0]);
	}
	else
	{
		oneAttDizz.clear();
		dizz = true;
	}
}

/*调用被非击覆盖类技能*/
void MonsterBase::callMoreAtt(SkillTime &_skiTme)
{
	hitedEffectBySki(_skiTme);
}

/*调用所有非击覆盖类技能*/
void MonsterBase::dealMoreAtt(void)
{
	int length,index;
	if(moreAtt.empty())
	{
		return;
	}
	vector<SkillTime> ::iterator skiTme_it;
	length = moreAtt.size();
	for(skiTme_it = moreAtt.begin();skiTme_it != moreAtt.end();)
	{
		(*skiTme_it).gain();
		/*时间还没到*/
		if(!((*skiTme_it).timeOut()))
		{
			if((*skiTme_it).sentPos())
			{
				callMoreAtt(*skiTme_it);
			}
			skiTme_it++;
		}
		
		/*时间已到*/
		else
		{
			skiTme_it = moreAtt.erase(skiTme_it);
		}
	}
	return;
} 

/*调用所有非击覆盖类技能*/
void MonsterBase::dealMoreAttDef(void)
{
	if(moreAttDef.empty())
	{
		return;
	}
	vector<SkillTime> ::iterator skiTme_it;
	for(skiTme_it = moreAttDef.begin();skiTme_it != moreAttDef.end();)
	{
		(*skiTme_it).gain();
		/*时间还没到*/
		if(!((*skiTme_it).timeOut()))
		{
			skiTme_it++;
		}
		
		/*时间已到*/
		else
		{			
			
			
			/*判断攻防是否达到上限*/
			if(!judgeAttDef())
			{
				skiTme_it = moreAttDef.erase(skiTme_it);
				continue;
			}
			
			recoverAttDef(*skiTme_it);
			skiTme_it = moreAttDef.erase(skiTme_it);
		}
	}
	return;
} 

/*调用击覆盖类技能,降低韧性*/
void MonsterBase::dealMoreAttTen(void)
{
	if(moreAttTen.empty())
	{
		return;
	}
	vector<SkillTime> ::iterator skiTme_it;
	for(skiTme_it = moreAttTen.begin();skiTme_it != moreAttTen.end();)
	{
		(*skiTme_it).gain();
		/*时间还没到*/
		if(!((*skiTme_it).timeOut()))
		{
			skiTme_it++;
		}
		
		/*时间已到*/
		else
		{	
			/*判断韧性是否达到上限*/
			if(!judgeAttTen())
			{
				skiTme_it = moreAttTen.erase(skiTme_it);
				continue;
			}
			
			recoverAttTen(*skiTme_it);
			skiTme_it = moreAttTen.erase(skiTme_it);
		}
	}
	return;
} 

/*调用击覆盖类技能,降低韧性*/
void MonsterBase::dealMoreAttHit(void)
{
	if(moreAttHit.empty())
	{
		return;
	}
	vector<SkillTime> ::iterator skiTme_it;
	for(skiTme_it = moreAttHit.begin();skiTme_it != moreAttHit.end();)
	{
		(*skiTme_it).gain();
		/*时间还没到*/
		if(!((*skiTme_it).timeOut()))
		{
			skiTme_it++;
		}
		
		/*时间已到*/
		else
		{						
			/*判断韧性是否达到上限*/
			if(!judgeAttHit())
			{
				skiTme_it = moreAttHit.erase(skiTme_it);
				continue;
			}
			
			recoverAttHit(*skiTme_it);
			skiTme_it = moreAttHit.erase(skiTme_it);
		}
	}
	return;
} 
/*调用所有非击覆盖类技能*/
void MonsterBase::hitedSkiFun(void)
{
	callOneAtt();
	callOneAttPt();
	callOneAttDizz();
	dealMoreAtt();
	dealMoreAttDef();
	dealMoreAttTen();
	dealMoreAttHit();
	return;
} 

/*持续掉血消息形成*/
void MonsterBase::formDropBldMsg(SkillTime &_skiTme,char *msg_other,int lengStr)
{
	if(msg_other == NULL)
	{
		return;
	}
	snprintf(msg_other + strlen(msg_other),lengStr - strlen(msg_other),"%d,%s,%d,%s,%s,%s,%s,%s,%d,%s,%s,%s,%d",\
			MONSTER_SKILL_HEAD,",",MONSTER_SKILL_SINGLE,",",_skiTme.attheroId,\
			",",const_cast<char *>(DROP_BLOOD_ID.c_str()),",",HIT_TYPE_MONSTER,",",identity,\
			",",_skiTme.effectType);
	
	// msg_other = intTostring(MONSTER_SKILL_HEAD);
	// msg_other.erase(msg_other.begin());
	// msg_other += intTostring(MONSTER_SKILL_SINGLE);
	// msg_other += charTostring(const_cast<char *>(_skiTme.attheroId.c_str()));	
	// msg_other += charTostring(const_cast<char *>(DROP_BLOOD_ID.c_str()));	
	// msg_other += intTostring(HIT_TYPE_MONSTER);	
	// msg_other += charTostring(identity);
	// msg_other += intTostring(_skiTme.effectType);
	formSelDropBldMsg(_skiTme,msg_other,lengStr);
	snprintf(msg_other + strlen(msg_other),lengStr - strlen(msg_other),\
	"%s,%d",",",_skiTme.values);
	// msg_other += intTostring(_skiTme.dropBlood);
	
	isHurt = true;
	plyCdCtn = 0;
}

/*持续掉血消息形成*/
void MonsterBase::formSelDropBldMsg(SkillTime &_skiTme,char *msg_other,int lengStr)
{
	if(msg_other == NULL)
	{
		return;
	}
	
	if(_skiTme.alCtn > 1)
	{
		snprintf(msg_other + strlen(msg_other),lengStr - strlen(msg_other),"%s,%d",",",1);
		// msg_other += intTostring(1);
	}
	else
	{
		snprintf(msg_other + strlen(msg_other),lengStr - strlen(msg_other),"%s,%d",",",int(_skiTme.cdTimes));
		// msg_other += intTostring(int(_skiTme.cdTimes));
	}
}

/*持续掉血消息形成*/
void MonsterBase::sendDropBldMsg(SkillTime &_skiTme,char *msg_other)
{
	Nbox *box;	
	if(_skiTme.alCtn > 1 && msg_other != NULL && strlen(msg_other) != 0)
	{
		box = map_now->getBox();
		
		if(box == NULL)
		{
			return;
		}
		
		/*陈真改*/
		
		StyObj obj(identity,MONSTER_STYLE_TYPE);
		
		box->getStaInSrcVec(obj);
	
		// SendMsgClass::sendMapMsg(map_now,msg_other);
		
		box->sentBoxMsg(msg_other);	
	
	}
}

/*保存攻防总值*/
void MonsterBase::storeAttDef(void)
{
	
	out_AttVal = outAttVal;   
	
	in_AttVal = inAttVal;   
	
	out_DefVal = outDefVal;    
	
	in_DefVal = inDefVal;  
}	

/*还原攻防总值*/
void MonsterBase::recoverAttDef(SkillTime &skiTme)
{
	
	outAttVal += skiTme.values;   
	
	inAttVal += skiTme.values;   
	
	outDefVal += skiTme.values;    
	
	inDefVal += skiTme.values;  
}	

/*改变攻防总值*/
void MonsterBase::reduceAttDef(SkillTime &skiTme)
{
	
	outAttVal -= skiTme.values;   
	
	inAttVal -= skiTme.values;   
	
	outDefVal -= skiTme.values;    
	
	inDefVal -= skiTme.values;  
}	

/*判断攻防是否达到上限,或者降到下限*/
bool MonsterBase::judgeAttDef(void)
{
	if(outAttVal > out_AttVal || outAttVal <= 0)
	{
		return false;
	}
	if(inAttVal > in_AttVal || inAttVal <= 0)
	{
		return false;
	}
	if(outDefVal > out_DefVal || outDefVal <= 0)
	{
		return false;
	}
	if(inDefVal > in_DefVal || inDefVal <= 0)
	{
		return false;
	}
	return true;
}	

/*判断韧性是否达到上限,或者降到下限*/
bool MonsterBase::judgeAttTen(void)
{
	if(tenacity > tena_city || tenacity <= 0)
	{
		return false;
	}
	return true;
}

/*减韧性*/
void MonsterBase::reduceAttTen(SkillTime &newSkiTime)
{
	if(tenacity >= newSkiTime.values)
	{
		tenacity -= newSkiTime.values;
	}
	else
	{
		tenacity = 0;
	}
}

/*恢复韧性*/
void MonsterBase::recoverAttTen(SkillTime &newSkiTime)
{
	if(tenacity + newSkiTime.values >= tena_city)
	{
		tenacity = tena_city;
	}
	else
	{
		tenacity += newSkiTime.values;
	}
}

/*减命中*/
void MonsterBase::reduceAttHit(SkillTime &newSkiTime)
{
	if(hit - newSkiTime.values <= 0)
	{
		hit = 0;
	}
	else
	{
		hit -= newSkiTime.values;
	}
}

/*恢复命中*/
void MonsterBase::recoverAttHit(SkillTime &newSkiTime)
{
	if(hit + newSkiTime.values >= hitCopy)
	{
		hit = hitCopy;
	}
	else
	{
		hit += newSkiTime.values;
	}
}

/*判断韧性是否达到上限,或者降到下限*/
bool MonsterBase::judgeAttHit(void)
{
	if(hit > hitCopy || hit <= 0)
	{
		return false;
	}
	return true;
}

/*设置无敌状态*/
void MonsterBase::setUnEnemySta(bool _unEnemySta)
{
	unEnemySta = _unEnemySta;
}

/*设置无敌状态*/
bool MonsterBase::getUnEnemySta(void)
{
	return unEnemySta;
}

/*获得等级*/
int MonsterBase::getRank(void)
{
	return rank;
}
	
/*重置怪物所受延时性技能影响*/
void MonsterBase::initHitedSki(void)
{
	moreAtt.clear();      
	moreAttDef.clear();      
	oneAtt.clear();       
	oneAttPt.clear();       
	oneAttDizz.clear();      
	moreAttTen.clear();      
	moreAttHit.clear(); 
}	

/*重置攻防值*/
void MonsterBase::initRecAttDef(void)
{
	outAttVal = out_AttVal;   
	
	inAttVal = in_AttVal ;   
	
	outDefVal = out_DefVal ;    
	
	inDefVal = in_DefVal;  
}

/*重置标记值*/
void MonsterBase::initFlgVal(void)
{
	/*定身*/
	skiBody = true; 
	
	/*点穴*/
	attackPoint = true;  
	
	/*眩晕*/
	dizz = true; 
	
	/*回归标记值*/
    Rec = false;  
	
	/*逃跑标记值*/
    flgRun = false;  

	/*无敌状态*/
	unEnemySta = false;
	
}

/*处理宠物的仇恨列表容器，如果为真，则插入，否则则删除*/
void MonsterBase::dealPetLst(bool _flg)
{
	list<HatVal>::iterator enmityValues_it;
	map<string,Hero*>::iterator hero_it;
	Hero* hero;
	hero = NULL;
    for(enmityValues_it = enmityValues.begin();enmityValues_it != enmityValues.end();)
    {
		hero = getHero(((*enmityValues_it).id));
		if(hero == NULL)
		{
			enmityValues_it = enmityValues.erase(enmityValues_it);
			continue;
		}
		if(_flg)
		{
			hero->insertAttList(identity);
		}
		else
		{
			hero->deleteAttList(identity);
		}
		enmityValues_it++;
	}
}
			

/*处理宠物的仇恨列表容器，全删除*/
void MonsterBase::dealPerByEmy(void)
{
	list<HatVal>::iterator val_it;
	map<string,Hero*>::iterator hero_it;
	Hero* hero;
	hero = NULL;
	for(val_it = enmityValues.begin();val_it != enmityValues.end();)
	{
		hero = getHero(((*val_it).id));
		if(hero == NULL)
		{
			val_it = enmityValues.erase(val_it);
			continue;
		}
				
		hero->deleteAttList(identity);
		val_it++;
	}		
}

/*判断次数够否*/
bool MonsterBase::dealLveCtn(void)
{
	/*刷出次数还木有完*/
	if(lveCtnMager.isLveCtn())
	{
		return true;
	}
	return false;
}

/*判断时间够否*/
bool MonsterBase::dealDurTme(void)
{
	/*刷出次数还木有完*/
	if(lveCtnMager.isWaitTme())
	{
		return true;
	}
	return false;
}

/*判断追击的玩家是否移动,移动则返回真*/
bool MonsterBase::jdgSmePt(Point heroPt)
{
	/*进行追击,如果玩家没有动，则不必每次都寻路*/	
	if(astar == NULL || heroPt._x != presuitPt._x || heroPt._y != presuitPt._y)
	{
		presuitPt = heroPt;
		return true;
	}
	return false;
}

/*下线消息*/
void MonsterBase::formOutMsg(void)
{
	memset(outMsg,'\0',OUT_VIEW_LENGTH + 1);	
	sprintf(outMsg + strlen(outMsg),"%d%s%d%s%s%s%d",2,",",5,",",identity,",",1);
}

/*获得下线消息*/
char* MonsterBase::getOutMsg(void)
{
	return outMsg;
}

LveCtnManger MonsterBase::getLveMag(void)
{
	return lveCtnMager;
}

int MonsterBase::getExpTme(void)
{
	return expTme;
}

int MonsterBase::getMonyTme(void)
{
	return monyTme;
}
 
//获取五行属性
FiveElem* MonsterBase::getFiveElem()
{
	return fiveElement;
}
   
/*生成移动固定头文件*/
void MonsterBase::getMovHeadMsg(string &moveMsg)
{
	moveMsg += intTostring(MONSTER_RETURN_MOVE);
    moveMsg.erase(moveMsg.begin());
    moveMsg += intTostring(MOVE_RETURN_OTHER);   

    moveMsg +=  charTostring(identity);
    moveMsg += intTostring(pt._x);
    moveMsg += intTostring(pt._y);   
}


/*怪物类型的用int型表示*/
void MonsterBase::kindIntInit(void)
{
	if(strcmp(kind,"General") == 0)
	{
		kindInt = 1;
	}
	else if(strcmp(kind,"Elite") == 0)
	{
		kindInt = 2;
	}
	else 
	{
		kindInt = 3;
	}
}

/*巡逻怪走动频率（随机和概率同时进行判断）*/
bool MonsterBase::judgeGoFor(void)
{
	int critRand;
	
    critRand = rand()%100;
	goForCtn++;
	if(critRand == forGo || goForCtn == forGo)
	{
		goForCtn = 0;
		isInPatrol = true;
		return true;
	}		
	return false;
}

/*把forGo全部进行对10取余数处理*/
void MonsterBase::dealGoFor(void)
{
	forGo *= 10;
	
	forGo %= 100;
	
//	forGo += 10;
	
//	forGo %= 30;
}

/*测试怪物存活属性*/
int MonsterBase::testLveManger(void)
{
	int sums;
	cout<<"test monsterId begin:"<<identity<<endl;
	sums = lveCtnMager.testPro();
	cout<<"test monsterId end:"<<identity<<endl;
	return sums;
}

/*获得自卫反应标记值*/
bool MonsterBase::getRepFlg(void)
{
	return repFlg;
}

/*修改自卫反应标记值*/
void MonsterBase::setRepFlg(bool _repFlg)
{
	 repFlg = _repFlg;
}

/*初始化追踪点坐标*/
void MonsterBase::initPersuitPt(void)
{
	presuitPt._x = -1;
	presuitPt._y = -1;	
}

/*定时发送下线消息*/
void MonsterBase::sendOutMsg(void)
{
	StyObj obj(identity,MONSTER_STYLE_TYPE);
	bool resultVal;
	Nbox *box;
	
	box = map_now->getBox();	
	if(box == NULL)
	{
		return;
	}	

	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(outMsg);
	
	if(strcmp(type,"ActiveBossMon") == 0)
	{
		map_now->deleteID(obj);
	}
	
	//任务怪
	if(getOwnerAttriType() == 3)
	{
		map_now->deleteID(obj);
	}
}

/*把寻路寻到的逻辑点转换成像素点*/
void MonsterBase::exchgeWayRod(void)
{

//	cout<<"the exchgeWayRod begin  of  logic_pt._x:"<<logic_pt._x<<" logic_pt._y:"<<logic_pt._y<<endl;
	list<Point>::iterator sendPt_it,key_it;
	Point lastPt,lastPiexRodPt;	
	
//	cout<<"stop for chageWayRod:"<<endl;	
	if(astar->getWayArr().empty())
	{
		// cout<<"it is empty of the findWay:"<<endl;
		return;
	}
	
	keyPath.clear();
	
	for(sendPt_it = astar->getWayArr().begin();sendPt_it !=\
	astar->getWayArr().end();sendPt_it++)
	{	
	
		lastPt = *sendPt_it;
		
		lastPt._y -= map_now->getBaseDigst();
	
		lastPiexRodPt = LogicalExchangeMap(lastPt);
	
		keyPath.push_back(lastPiexRodPt);	
	}
	
	astar->getWayArr().clear();
	
	keyPath.pop_front();
	keyPath.push_front(pt);	
	
	//smoothRoadPt();
	
	/*路径平滑处理,调用地图里面的一个函数*/
	//smoothRoadPtSelf();

	stopMoveTimer();
	
	mon_move_cb(loops, &moveTimer, 3);
	
//	cout<<"the exchgeWayRod end  of  logic_pt._x:"<<logic_pt._x<<" logic_pt._y:"<<logic_pt._y<<endl;
	
}


/*路径平滑处理*/
void MonsterBase::smoothRoadPt(void)
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
	astar->getWayArr().rend();++sendPt_it)
	{	
	
		lastPt = *sendPt_it;
		
		if(logic_pt == lastPt)
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
	
	astar->getWayArr().clear();
	
	// for(key_it = keyPath.begin();key_it != keyPath.end();++key_it)
	// {	
		// lastPt = MapExchangeLogical(*key_it);
		// lastPt._y += map_now->getBaseDigst();
		// map_now->judgeLogPtHind(lastPt);
	// }
}
	
		
void MonsterBase::disappear()
{
	return;
}

void MonsterBase::StandStill()
{
	return;
}

/*根据人物初始化怪物属性*/
void MonsterBase::initOnwer(Hero *owner)
{
	return;
}

void MonsterBase::startMoveTimer()
{
	keyPath.clear();
	currPt = endPt = getLocation();
	ext_ev_timer_init(&moveTimer, mon_move_cb, 0.5, 0, this);
	ev_timer_start(loops, &moveTimer);
}
void MonsterBase::stopMoveTimer()
{
	ev_timer_stop(loops, &moveTimer);
}

int MonsterBase::getSpeed()
{
	return speed;
}

int MonsterBase::getLastSpeed()
{
	return lastSpeed;
}

void MonsterBase::stopMove(bool _isChgePerPt)
{
	if(_isChgePerPt)
	{
		initPersuitPt();
	}
	mon_move_cb(loops, &moveTimer, 1);
}


/*判断动画是否播放完*/
bool MonsterBase::isPlayOver()
{
	if(isHurt)
	{
		plyCdCtn++;
		if(plyCdCtn >= playCd)
		{
			plyCdCtn = 0;
			
			isHurt = false;				
			return true;
		}
		return false;
	}
	else
	{
		return true;
	}
	
}

/*获得掉落阶段*/
char* MonsterBase::getStage(void)
{
	return stage;
}

/*怪物回血功能*/
void MonsterBase::recoverBloodSelf(void)
{
	if(lifeVal < lifeUpperVal)
	{
		if(isRecoverBlood())
		{
			if(!isBloodTmeOpenFlg)
			{			
				/*暂停，重来吧*/
				ev_timer_stop(loops,&bloodTimer);	
				
				/*回血消息*/
				ext_ev_timer_init(&bloodTimer,monRecoverBooldCalBak,10,0, this);	
				ev_timer_start(loops,&bloodTimer);	
				isBloodTmeOpenFlg = true;
			}
		}
		else
		{
			/*暂停*/
			ev_timer_stop(loops,&bloodTimer);	
			isBloodTmeOpenFlg = false;
		}			
	}

#if 0
	/*原来的回血*/
	if(lifeVal < lifeUpperVal)
	{
		if(isRecoverBlood())
		{
			lifeVal = lifeUpperVal;
			brushMon();
		}
	}
#endif
}

/*路径平滑处理,调用地图里面的一个函数*/
void MonsterBase::smoothRoadPtSelf(void)
{	
	list<Point>::reverse_iterator sendPt_it;	
	list<Point>::iterator temp_it,key_it;
	Point lastPt,lastPiexRodPt;		
	list<Point> temp;
	
	
	
	if(astar->getWayArr().empty() || map_now == NULL)
	{
		return;
	}	
	
	
	cout<<"the smoothRoadPtSelf begin  of  logic_pt._x:"<<logic_pt._x<<" logic_pt._y:"<<logic_pt._y<<endl;
	
	keyPath.push_back(pt);	
	
	for(sendPt_it = astar->getWayArr().rbegin();sendPt_it !=\
	astar->getWayArr().rend();++sendPt_it)
	{	
	
		lastPt = *sendPt_it;
		
		
		if(logic_pt == lastPt)
		{
			break;
		}
		
		lastPt._y -= map_now->getBaseDigst();	
		lastPiexRodPt = LogicalExchangeMap(lastPt);
		
		if(!map_now->judgeLogPtHind(*sendPt_it))
		{
			cout<<"the *sendPt_it._x:"<<(*sendPt_it)._x<<" *sendPt_it._y:"<<(*sendPt_it)._y<<endl;
		}
			
		if(!map_now->judgeLogPtHind(logic_pt))
		{
			cout<<"the hind of  logic_pt._x:"<<logic_pt._x<<" logic_pt._y:"<<logic_pt._y<<endl;
		}
		
		if(!map_now->judgeLineCanPas(logic_pt,*sendPt_it))
		{			
			temp.push_front(lastPiexRodPt);
		}
		else
		{
			keyPath.push_back(lastPiexRodPt);
			break;
		}
	}
		
	/*处理那些障碍点*/
	if(!temp.empty())
	{		
		keyPath.insert(keyPath.end(),temp.begin(),temp.end());
	}
	
	astar->getWayArr().clear();
	
	for(key_it = keyPath.begin();key_it != keyPath.end();++key_it)
	{	
		lastPt = MapExchangeLogical(*key_it);
		lastPt._y += map_now->getBaseDigst();
		
		if(!map_now->judgeLogPtHind(lastPt))
		{
			cout<<"the send pt is hind:"<<endl;
		}
	}
	
	cout<<"the smoothRoadPtSelf end  of  logic_pt._x:"<<logic_pt._x<<" logic_pt._y:"<<logic_pt._y<<endl;
}

/*回血条件判断*/
bool MonsterBase::isRecoverBlood(void) 
{
	set<string>::iterator her_it;
	set<string>HeroIdSet;	
	Point heroPt;       
	Hero *myHero;
	Nbox *box;

	
	box = map_now->getBox();
	if(box == NULL)
	{
		return false;
	}
	
	box->getCentPtSrcHerIdSet(pt,HeroIdSet);	
    
	
    for(her_it = HeroIdSet.begin(); her_it != HeroIdSet.end(); her_it++)
    {		
		myHero = heroid_to_hero(*her_it);
        if(myHero == NULL || myHero->getLifeStation() == DEAD || !myHero->getWalkingFlg())
        {
            continue;
        }
        /*为了减少误差，用像素判断*/
        heroPt = myHero->getLocation();   
		
		// cout<<"heroPt._x:"<<heroPt._x<<endl;
		// cout<<"heroPt._y:"<<heroPt._y<<endl;
		
		// cout<<"hatRge:"<<hatRge<<endl;
        /*判断是否在仇恨范围内*/	
		
		/*现在是以当前点为圆心，仇恨范围不动的格式做的*/
		
        if(sqrt(pow(fabs(heroPt._x - pt._x),2)+pow(fabs(heroPt._y - pt._y),2)) <= hatRge)
        {
          return false;
        }
    }
	return true;
}   

/*获得回血计时器标记值*/
bool MonsterBase::getIsBloodTmeOpenFlg(void)
{
	return isBloodTmeOpenFlg;
}

/*设置回血计时器标记值*/
void MonsterBase::setIsBloodTmeOpenFlg(bool _isBloodTmeOpenFlg)
{
	isBloodTmeOpenFlg = _isBloodTmeOpenFlg;
}


/*怪物自卫攻击时缩短思考时间*/
void MonsterBase::initResponseAgain(void)
{
	ev_timer_stop(loops,&think_timer);
	ext_ev_timer_init(&think_timer,monThkCalBak,0.01,0, this);
	ev_timer_start(loops,&think_timer);
}

/*获得帮派，阵营属性*/
char* MonsterBase::getOwnerAttri(void)
{
	return ownerAttri;
}

/*修改帮派，阵营属性*/
void MonsterBase::setOwnerAttri(char *_ownerAttri)
{
	if(_ownerAttri)
	{
		memset(ownerAttri,'\0',sizeof(ownerAttri));
		strncpy(ownerAttri,_ownerAttri,strlen(_ownerAttri));	
	}
}

/*获得怪物帮派，阵营类型*/
int MonsterBase::getOwnerAttriType(void)
{
	return ownerAttriType;
}

/*修改怪物帮派，阵营类型*/
void MonsterBase::setOwnerAttriType(int _ownerType)
{
	ownerAttriType = _ownerType;
}

/*阵营怪的变换*/
void MonsterBase::exchgeCampAttriType(int _ownerType)
{
	/*阵营*/
	ownerAttriType = 2;
	snprintf(ownerAttri,sizeof(ownerAttri),"%d",_ownerType);
}

/*判断是否命中*/
int MonsterBase::ctnHitRatio(int hitVoid)
{
	int hitRatio =  (1.0 * hit * 20 )/(hit * 20 + hitVoid) * 100;
	
	/*闪避随机数*/
	int randNum = rand()%100;
    if(randNum <= hitRatio)
    {
        return 1;
    }
	return 0;
}


/*判断是否命中*/
int MonsterBase::ctnCritRatio(Hero *hitPerson)
{
	int monCritRatio = 15 + crit/30;
	double realCritRatio = monCritRatio * (100 - hitPerson->ctnTenacityRatio())/10000;
	
	
	/*闪避随机数*/
	int randNum = rand()%100;
    if(randNum >= realCritRatio * 100)
    {
        return 0;
    }
	return 1;
}


/*任务怪，追加此任务的玩家信息*/
bool MonsterBase::appendTaskInfo(Hero *hero)
{

	cout<<" MonsterBase::appendTaskInfo here:"<<endl;
	if(!hero)
	{
		cout<<"MonsterBase::appendTaskInfo the hero is NULL:"<<endl;
		return false;
	}

	/*可采集任务怪不需要追加玩家名称*/
	if(ownerAttriType == 3)
	{	
	#if 0
		memset(nickName,'\0',sizeof(nickName));
		strncpy(nickName,appendNickName,strlen(appendNickName));
		strncat(nickName,hero->getNickName(),strlen(hero->getNickName()));		
	#endif
	
		memset(appendNickName,'\0',sizeof(appendNickName));
		strncpy(appendNickName,hero->getNickName(),strlen(hero->getNickName()));
	
		//重新生成消息
	//	formBshMsg();
	}	
	
	if(strlen(appendNickName) == 0)
	{
		return false;
	}
	
	memset(taskOwnerId,'\0',sizeof(taskOwnerId));
	strncpy(taskOwnerId,hero->getIdentity(),strlen(hero->getIdentity()));
	
	isUsed = true;	
	
	cout<<"MonsterBase::appendTaskInfo(Hero *hero) the appendNickName:"<<appendNickName<<endl;
	//刷出怪
	brushMon();
	
	if(getOwnerAttriType() == 3)
	{
		cout<<"MonsterBase::appendTaskInfo(Hero *hero) begin:"<<getIdentity()<<endl;
		cout<<"getBshMsg:"<<getBshMsg()<<endl;
		cout<<"MonsterBase::appendTaskInfo(Hero *hero) end:"<<getIdentity()<<endl;
	}
	
	ev_timer_stop(loops,&taskTime);	
	
	ext_ev_timer_init(&taskTime,monTaskCalBak,180,0, this);

    ev_timer_start(loops,&taskTime);
	
	return true;
}

/*任务怪里面（判断此怪是否被刷出）*/
bool MonsterBase::getIsUsed(void)
{
	return isUsed;
}



/*任务怪存活时间到*/
void MonsterBase::taskMonCalBack(void)
{	
	/*暂停动*/
	stopMove();		
	
	/*暂停回血计时器*/
	ev_timer_stop(loops,&bloodTimer);
	
	/*暂停思考*/		
	ev_timer_stop(loops,&think_timer);	
	
	/*暂停任务怪存活计时器*/		
	ev_timer_stop(loops,&taskTime);	
	
	/*从地图中干掉*/
	sendOutMsg();
	
	Hero *perHero = getHero(taskOwnerId);
	if (perHero != NULL)
	{
		perHero->abandTaskBySubType(1, false);
	}
	/*属性重置*/
	initMonsterBaseAsist();	
	
	callBoss = NULL;
}

/*判断任务怪的主人是否还在*/
bool MonsterBase::judgeTask(void)
{
	if(isCallBossLife())
	{
		return true;
	}
	
	if(ownerAttriType != 3 && ownerAttriType != 4)
	{
		return false;
	}

#if 1	
	/*测试用*/
	if(strlen(taskOwnerId) == 0)
	{
		return false;
	}
	
#endif	

	Hero *perHero = getHero(taskOwnerId);
	
	if(perHero == NULL)
	{		
		taskMonCalBack();		
		return true;
	}
	
	if(strcmp(map_now->getMapId(),perHero->getMap()->getMapId()) != 0)
	{
		/*调用任务相关函数*/
		perHero->abandTaskBySubType(1, false);		
		taskMonCalBack();
		return true;
	}
	
	if(attackRangePoint(pt,perHero->getLocation(),1000) == 0)
	{
		/*调用任务相关函数*/
		perHero->abandTaskBySubType(1, false);		
		taskMonCalBack();
		return true;
	}
}

/*召唤怪*/
void MonsterBase::callMon()
{
	if(map_now)
	{
		map_now->callMon(this);
	}
}

/*召唤陷阱*/
void MonsterBase::callTrap(const vector<string> &herId)
{
	if(map_now)
	{
		map_now->callTrap(herId);
	}
}

/*设置召唤怪标志值*/
void MonsterBase::setIsCallType(bool _isCallType)
{
	isCallType = _isCallType;
}

/*获得召唤标记值*/
bool MonsterBase::getIsCallType(void)
{
	return isCallType;
}

/*设置召唤怪召唤出来的标志值*/
void MonsterBase::setIsCalled(bool _isCalled)
{
	isCalled = _isCalled;
}

/*获得召唤怪召唤出来的标志值*/
bool MonsterBase::getIsCalled(void)
{
	return isCalled;
}

/*设置cd冷却标记值*/
void MonsterBase::setIsCdCool(bool _isCdCool)
{
	isCdCool = _isCdCool;
}

/*使用技能,随机取技能*/
bool MonsterBase::useSkill(vector<string> &herId,bool _station)
{
	if(skiInstSet.empty())
	{
		return false;
	}
	
	int randIndex;
	vector<SkillBase*>::iterator begin_it,skiInst_it = skiInstSet.begin();
	if(skiInstSet.size()  == 1)
	{
		randIndex = 0;
	}
	else
	{		
		randIndex = rand() % (skiInstSet.size() -1);
	}
	
	advance(skiInst_it,randIndex);
	
	for(begin_it = skiInst_it;begin_it != skiInstSet.end();++begin_it)
	{
		if((*begin_it)->useSkill(herId,_station))
		{
			return true;
		}
	}
	
	for(begin_it = skiInstSet.begin();begin_it != skiInst_it;++begin_it)
	{
		if((*begin_it)->useSkill(herId,_station))
		{
			return true;
		}
	}
	
	return false;
}

double MonsterBase::getLength(Point heroPt)
{
	return sqrt(pow(fabs(heroPt._x - pt._x),2)+pow(fabs(heroPt._y - pt._y),2));
}


void MonsterBase::sortByPt(void) 
{
	if(enmityValues.size() < 2)
	{
		return;
	}
	
	list<HatVal>::iterator hat_it = enmityValues.begin();
	list<HatVal>::iterator after_it,afterA;
	++hat_it;
	
	while(hat_it != enmityValues.end())
	{		
		HatVal temp = *hat_it;
		
		Hero *hatHero = heroid_to_hero((*hat_it).id);
		
		after_it = hat_it;
		afterA = after_it;
		--afterA;
		
		if((*afterA).value != (*(hat_it)).value)
		{
			return;
		}
		
		while(after_it != enmityValues.begin())
		{
			afterA = after_it;
			--afterA;
			
			Hero *afterHero = heroid_to_hero((*(afterA)).id);
			
			if(afterHero && hatHero)
			{
						
				if(getLength(hatHero->getLocation()) > getLength(afterHero->getLocation()))
				{
					*after_it = *(afterA);
				}
			}
			
			--after_it;
		}
		
		*after_it = temp;
		
		++hat_it;
	}
} 

void MonsterBase::setCallBoss(MonsterBase* _callBoss)
{
	if(!_callBoss)
	{
		return;
	}
	callBoss = _callBoss;
}

//判断召唤怪的boss是否已死掉，真为死掉
bool MonsterBase::isCallBossLife(void)  
{
	if(!(isCallType && isCalled && callBoss))
	{
		return false;
	}
	if(!callBoss->getLifeStation())
	{
		taskMonCalBack();
		return true;
	}
}
		
	