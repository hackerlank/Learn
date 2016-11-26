#include"monsterPatrol.h"
#include<math.h>
#include "instancing_manage.h"
#include <assert.h>
extern int Rd;         
extern Instancing_manage *Inst_MNG;
extern map<string, Hero*> heroId_to_pHero;

MonsterPatrol::MonsterPatrol(char *_mapId,char *_typeId,char *_nickName,\
char *_identity,char *_type,char *_kind,int _experience,double _cdTime,\
int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,\
int _getHrtSud,int _outHrt,int _inHrt,int _outAttVal, int _inAttVal,\
int _outDefVal, int _inDefVal,int _defSumVal,double _hit,double _crit,\
int _voids,int _tenacity,int _moveRange, int _hatRange,int _attRange,\
int _failGoodsless,int _failGoodsmost,int _hatVal,int _gold,set<string>\
& _failId, Point _pt,int _rank,int _speed,int _fiveEleInt,int _fiveHurt,\
int _fiveRank,int _forGo,int _expTme,int _monyTme,char *_stage,char *_photoId,\
vector<string> &skiIdSet,char *_genAttId,double _angVal,int _ownerAttriType,\
char* _ownerAttri,double _attackRatio,bool _isInnerAttack,LveCtnManger _lveCtnMager,\
Point logicPt,int _radius):MonsterBase(_mapId,_typeId,_nickName,_identity,_type,_kind,\
_experience,_cdTime,_lifeUpperVal,_lifeVal,_magicUpperVal,_magicVal,_getHrtSud,\
_outHrt,_inHrt, _outAttVal, _inAttVal,_outDefVal,_inDefVal,_defSumVal,_hit,_crit,\
_voids,_tenacity,_moveRange,_hatRange,_attRange,_failGoodsless,_failGoodsmost,\
_hatVal,_gold,_failId,_pt,_rank,_speed,_fiveEleInt,_fiveHurt,_fiveRank,_forGo,\
_expTme,_monyTme,_stage,_photoId,skiIdSet,_genAttId,_angVal,_ownerAttriType,\
_ownerAttri,_attackRatio,_isInnerAttack,_lveCtnMager)
{

    radius = _radius;        //寻路半径 

    endFinPt = logicPt;    //寻路终点
	
	flgEnd = false;
	
	
}

/*
    被动怪思考回调函数：response
    参数：
    返回值：无
*/  
void MonsterPatrol::response(void)
{  
	StyObj obj(identity,MONSTER_STYLE_TYPE);	
	vector<string> herId;
	Point heroPt;
	Hero *perHero;
	Nbox *box;
	
	if(map_now == NULL)
	{
		return;
	}
	
	box = map_now->getBox();
	
	if(box == NULL || !isAlive)
	{
		return;
	}
	
	/*判断任务是否还在*/
	if(judgeTask())
	{
		cout<<"the task mon of the task is illeay:"<<endl;
		return;
	}
	
	if(!isPlayOver())
	{
//		cout<<"it is playCd time:"<<endl;
		return;
	}
	
	memset(otherMsg,'\0',MONSTER_MSG_LENGTH + 1);
	
	box->getStaInSrcVec(obj);

    /*处理延时性技能*/
    hitedSkiFun();

   /*判断地图是否有人，怪物是否已眩晕*/
	if(!dizz)
	{
		stopMove();
		return;
	}	

    /*脱战即回血功能*/
	recoverBloodSelf();
	
    /*Boss逃跑*/
    if(flgRun)
    {
        /*判断是否已定身*/
		if(!skiBody)
		{
			stopMove();
			return;
		}		              
    } 
	else
    {
        /*仇恨范围搜索*/
        schRge();

        /*如果仇恨列表为空*/
        if(enmityValues.empty())   //自己巡逻
        {
			/*如果上次正在追人，而这次仇恨没人，则立即停下来*/
			if(isPersuitHero)
			{
				stopMove();
				
				isPersuitHero = false;
			}
		
			if(Rec && !isInPatrol)
			{					
				/*判断是否已定身*/
				if(!skiBody)
				{
					stopMove();	
					return;
				}
				
				if(logic_pt == perLstPt)
				{
					Rec = false;
					return;						
				}	
				
				/*避免多次寻路*/
				if(keyPath.empty())
				{
					/*寻自己的路*/
					findAttWay(perLstPt);
				}								
			}
			else
			{	
				if(!isInPatrol)
				{
					/*模糊反应*/
					if(!judgeGoFor())
					{
						stopMove();	
						return;
					}	
				}
				
				/*判断是否已定身*/
				if(!skiBody)
				{
					stopMove();	
					return;
				}
				
				/*生成寻路终点*/
				getEnd(endFinPt);  
				
				if(logic_pt == endFinPt)
				{
					Rec = true;
					isInPatrol = false;
					return;							
				}
				
				/*避免多次寻路*/
				if(keyPath.empty())
				{
					/*寻自己的路*/
					findSlfWay(endFinPt);	
				}					
			}
			
        }
        else
        {
            /*这个是从仇恨列表里面得到的最高值，至于怎么得到的，则要看仇恨计算*/
           perHero = getHero(perHerId);
			
            if(perHero == NULL || !perHero->getLifeStation())
            {
                return;
            }
			
			heroPt = perHero->getLogPt();
			
            int fight_state = attackRangePoint(pt,perHero->getLocation(),attack_range);   
			      
			if(fight_state != 1)
            {

                /*判断是否已定身*/
				if(!skiBody)
				{
					stopMove();				
					return;
				}
				
				 /*如果人物没动，则这次就不必要再寻一次路*/
                if(jdgSmePt(heroPt))
                {					
                    findAttWay(heroPt);
					isPersuitHero = true;
                }
				isInPatrol = false;				
            }
			else
			{
				stopMove();	
				exchageHat(herId);
				if(attackPoint && useSkill(herId))
				{					
					return;
				}
				attPerHero(otherMsg,sizeof(otherMsg),perHero);					
				box->sentBoxMsg(otherMsg);
			}
			
			if(perLstPt == logic_pt)
			{
				Rec = false;
			}
			else
			{
				Rec = true;
			}
			
        }
    }
}

/*地图怪物拷贝函数*/
MonsterBase* MonsterPatrol::copyMon(char *_mapId)
{
	char newIntId[SHOR_MID_VALUE_LENGTH + 1] = {0};  
    MonsterBase* newMon;  
  
	
	if(_mapId == NULL || strlen(_mapId) == 0)
	{
		return NULL;
	}
	
    /* 追加地图id，为了保证副本怪物id的唯一性*/
	strncpy(newIntId,_mapId,strlen(_mapId));
	strncat(newIntId,"_",strlen("_"));
	strncat(newIntId,identity,strlen(identity));

    vector<string> skiIdSet;
    getSkiIdSet(skiIdSet);

    newMon = new MonsterPatrol(_mapId,typeId,nickName,newIntId,type,kind,experience,\
	cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,outAttVal,\
	inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,walk_ranage,hatRge,\
	attack_range,failGoodsLess,failGoodsMost,hatVal,gold,failList,pt,rank,speed,\
	fiveEleInt,fiveHurt,fiveEleRank,forGo,expTme,monyTme,stage,photoId,skiIdSet,\
	genAttId,angVal,ownerAttriType,ownerAttri,attackRatio,isInnerAttack,lveCtnMager,endFinPt,radius);    
	newMon->setIsCallType(isCallType);
    return newMon;
}

/*析构函数*/
MonsterPatrol::~MonsterPatrol(void)
{

}

/*获得巡逻终点*/
void MonsterPatrol::getEnd(Point _logicPt)
{
	if(flgEnd)
	{
		return;
	}
	endFinPt = born_pt;
	
	endFinPt._x += 50;
	endFinPt._y += 50;
	
    endFinPt = MapExchangeLogical(endFinPt);
    endFinPt._y += map_now->getBaseDigst();
    if(!map_now->judgeLogPtHind(endFinPt))
    {
        //cout<<"it is hinder:"<<endl;
		flgEnd = false;
		return;
    }
	flgEnd = true;
}  

/*怪物死亡函数*/
void MonsterPatrol::die(bool flgInit)
{

    MonsterBase::die(flgInit);
}   

/*重置怪物数据*/
void MonsterPatrol::initMonsterALL(void)
{
	
	flgEnd = false;
	
	MonsterBase::initMonsterALL();
}







 
