#include"bottle.h"
#include"map_inform.h"
#include"hero.h"
#include"otherThingCalBack.h"
#include"dropgoods.h"
extern map<string,Hero*>heroId_to_pHero;
extern struct ev_loop *loops;
Bottle::Bottle(char *_typeId,int _lifeVal,int _hurt,int _brushStyle,double _bloodPre,double _magicPre,char *_name,size_t _dropNum,char* _dropStage,char *_photoId)
{	
	memset(id,'\0',sizeof(id));
	memset(typeId,'\0',sizeof(typeId));
	memset(photoId,'\0',sizeof(photoId));
	memset(name,'\0',sizeof(name));	
	memset(dropStage,'\0',sizeof(dropStage));
	
	strncpy(typeId,_typeId,strlen(_typeId));		
	strncpy(name,_name,strlen(_name));
	strncpy(dropStage,_dropStage,strlen(_dropStage));
	strncpy(photoId,_photoId,strlen(_photoId));
		
	lifeVal = _lifeVal;	
	hurt = _hurt;	
	bruOut = false;
	lifeValUpper = lifeVal;
	brushStyle = _brushStyle;
	bloodPre = _bloodPre;
	magicPre = _magicPre;
	dropNum = _dropNum;
}

/*生成刷出信息*/
void Bottle::formBornMsg(void)
{
	memset(bornMsg,'\0',IN_VIEW_LENGTH + 1);
	
	sprintf(bornMsg + strlen(bornMsg),"%d%s%d%s%d%s%s%s%s",2,",",9,",",\
			TYPEBOTTLE,",",id,",",name);
	
	sprintf(bornMsg + strlen(bornMsg),"%s%d%s%d%s%d%s%s",",",\
			pt._x,",",pt._y,",",lifeVal,",",photoId);
}

/*获得id*/
char* Bottle::getId(void)
{
	return id;
}

/*生成下线信息*/
void Bottle::formOutMsg(void)
{
	memset(outMsg,'\0',OUT_VIEW_LENGTH + 1);
	
	sprintf(outMsg + strlen(outMsg),"%d%s%d%s%s%s%d",2,",",5,",",id,",",1);
}

/*获得玩家实例指针*/
Hero* Bottle::getHero(char *heroId)
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
void Bottle::setMap(Map_Inform *_map_now)
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
Point Bottle::getLogicPt(void)
{
    return logicPt;
}

/*复制瓶罐*/
Bottle* Bottle::copyBottle(char *_mapId)
{	
	char newIntId[LONG_MID_VALUE_LENGTH + 1] = {'\0'};       //新地图id;
	Bottle* newBottle;
	
	/* 追加地图id，为了保证副本道具id的唯一性*/	
	strncpy(newIntId,_mapId,strlen(_mapId));
	strncat(newIntId,"_",strlen("_"));	
	strncat(newIntId,id,strlen(id));
		
	
	newBottle = new Bottle(typeId,lifeVal,hurt,brushStyle,bloodPre,magicPre,name,dropNum,dropStage,photoId);	
	newBottle->setPiexPt(pt);
	newBottle->setInstId(newIntId);	
	return newBottle;
}

/*复制瓶罐<重载函数，在读取地图配置文件里面用>*/
Bottle* Bottle::copyBottle(Point _pt)
{
	char _id[MONSTER_MID_LENGTH + 1] = {'\0'};	
	Bottle* newBottle;	
	newBottle = new Bottle(typeId,lifeVal,hurt,brushStyle,bloodPre,magicPre,name,dropNum,dropStage,photoId);
	
	strncpy(_id,typeId,strlen(typeId));
	strncat(_id,"_",strlen("_"));	
	
	count++;
	appendNum(_id,count,4);		
	
	newBottle->setPiexPt(_pt);
	newBottle->setInstId(_id);
	
	return newBottle;
}

/*设置像素坐标*/
void Bottle::setPiexPt(Point _pt)
{
	pt = _pt;
}

/*获得摘取物品id*/
char* Bottle::getBottleId(void)
{
	return id;
}

/*设置实例id*/
void Bottle::setInstId(char *_id)
{
	if(_id == NULL)
	{
		return;
	}
	memset(id,'\0',sizeof(id));
	strncpy(id,_id,strlen(_id));
}

/*刷出瓶罐*/
void Bottle::brushMsg(void)
{
	StyObj obj(id,BOTTLE_STYLE_TYPE);
	Nbox *box;
	
	if(bruOut)
	{
		return;		
	}
	
	formBornMsg();
	
	formOutMsg();                  
	                   
	box = map_now->getBox();	
	
	if(box == NULL)
	{
		return;
	}
	
	map_now->insertID(obj);
	
	box->getStaInSrcVec(obj);	
	
	box->sentBoxMsg(bornMsg);
	
	bruOut = true;

}

/*瓶罐从地图消亡*/
void Bottle::disperMsg(void)
{
	StyObj obj(id,BOTTLE_STYLE_TYPE);
	Nbox *box;
	
	formOutMsg();                  
	                   
	box = map_now->getBox();	
	if(box == NULL)
	{
		return;
	}
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(outMsg);
	
	map_now->deleteID(obj);
	
	lifeVal = lifeValUpper;
	
	bruOut = false;
	
}

Bottle::~Bottle(void)
{	
	map_now = NULL;	
	
	memset(bornMsg,'\0',IN_VIEW_LENGTH + 1);
	
	memset(outMsg,'\0',OUT_VIEW_LENGTH + 1);
	
	ev_timer_stop(loops,&think_timer);
}

/*获得瓶罐的生命值*/
int Bottle::getLifeVal(void)
{
	return lifeVal;
}

/*设置瓶罐的生命值*/
void Bottle::setLifeVal(int _lifeVal)
{
	if(_lifeVal < 0)
	{
		cout<<"the bottle blood is less 0:"<<id<<endl;
		return;
	}
	lifeVal = _lifeVal;
}

/*设置瓶罐的生命值*/
void Bottle::beAttack(const char* attackId)
{
	if(hurt >= lifeVal)
	{
		lifeVal = 0;
		
		if(attackId && strlen(dropStage) > 0 && dropNum >= 1)
		{		
			// cout<<""
			saveInPick(const_cast<char*>(attackId),map_now,dropNum,dropStage,pt,0);
		}
		
		ev_timer_stop(loops,&think_timer);
		
		ext_ev_timer_init(&think_timer,botThkCalBack,2,0, this);

		ev_timer_start(loops,&think_timer);

	}
	else
	{
		lifeVal -= hurt;
	}
}

/*获得瓶罐伤害值*/
int Bottle::getHurt(void)
{
	return hurt;
}

/*获得上线消息*/
char* Bottle::getBronMsg(void)
{
	return bornMsg;
}

/*获得下线信息*/
char* Bottle::getOutMsg(void)
{
	return outMsg;
}


/*获得像素坐标*/
Point Bottle::getPiexPt(void)
{
	return pt;
}

/*已打碎打碎标志*/
bool Bottle::dieOutFlg(void)
{
	if(bruOut && lifeVal == 0)
	{
		return true;
	}
	return false;
}

/*已打碎打碎标志*/
bool Bottle::aliveFlg(void)
{
	return !bruOut;
}

/*取地图实例指针*/
Map_Inform* Bottle::getMap(void)
{
	return map_now;
}

/*取类型id*/
char* Bottle::getTypeId(void)
{
	return typeId;
}

/*获得刷出模式值*/
int Bottle::getBrushStyle(void)
{
	return brushStyle;
}

/*重置瓶罐属性*/
void Bottle::initBot(void)
{
	ev_timer_stop(loops,&think_timer);	
	
	lifeVal = lifeValUpper;
	
	bruOut = false;
}

//血值上限
int Bottle::getLifeUpperVal()
{
	return lifeValUpper;
}

/*打碎者回血的百分比*/
double Bottle::getBloodPre(void)
{
	return bloodPre;
}

/*打碎者回蓝的百分比*/
double Bottle::getMagicPre(void)
{
	return magicPre;
}

const char* Bottle::getDropStage(void) const
{
	return dropStage;
}
	
	
		
		