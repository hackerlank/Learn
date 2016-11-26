#include"monsterCamp.h"
#include<math.h>
#include<list>
#include"timerContainer.h"
extern struct ev_loop *loops;
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Map_Inform*>mapId_connect_map;  
extern HatValRue *hatValRue;         
extern TimerContainer<MonsterBase*> *monThkContain;
MonsterCamp::MonsterCamp(char *_mapId,char *_typeId,char *_nickName,char *_identity,\
char *_type,char *_kind,int _experience,double _cdTime,int _lifeUpperVal,int _lifeVal,\
int _magicUpperVal,int _magicVal,int _getHrtSud,int _outHrt,int _inHrt, int _outAttVal,\
int _inAttVal,int _outDefVal, int _inDefVal,int _defSumVal,double _hit,double _crit,\
int _voids,int _tenacity,int _moveRange,int _hatRange,int _attRange,\
int _failGoodsless,int _failGoodsmost,int _hatVal,int _gold,set<string>& _failList,\
Point _pt,int _rank,int _speed,int _fiveEleInt,int _fiveHurt,int _fiveEleRank,\
int _forGo,int _expTme,int _monyTme,char *_stage,char *_photoId,\
vector<string> &skiIdSet,char *_genAttId,double _angVal,\
int _ownerAttriType,char* _ownerAttri,double _attackRatio,bool _isInnerAttack,LveCtnManger _lveCtnMager,int _campFlg):MonsterBase(_mapId,_typeId,_nickName,\
_identity,_type,_kind,_experience,_cdTime,_lifeUpperVal,_lifeVal,\
_magicUpperVal,_magicVal,_getHrtSud,_outHrt,_inHrt, _outAttVal, _inAttVal,\
_outDefVal,_inDefVal,_defSumVal,_hit,_crit,_voids,_tenacity,_moveRange,_hatRange,\
_attRange,_failGoodsless,_failGoodsmost,_hatVal,_gold,_failList,_pt,_rank,_speed,\
_fiveEleInt,_fiveHurt,_fiveEleRank,_forGo,_expTme,_monyTme,_stage,_photoId,skiIdSet,\
_genAttId,_angVal,_ownerAttriType,_ownerAttri,_attackRatio,_isInnerAttack,_lveCtnMager)
{
	campFlg = _campFlg;
	exchgeCampAttriType(campFlg);

}		
		


void MonsterCamp::response(void)
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
	//	cout<<"it is playCd time:"<<endl;
		return;
	}
	
	memset(otherMsg,'\0',MONSTER_MSG_LENGTH + 1);
	
	box->getStaInSrcVec(obj);
	
	/*处理延时性技能*/
	hitedSkiFun();
	
	/*判断是否已眩晕*/
	if(!dizz)
	{
		stopMove();
		return;
	}	
	
	/*脱战即回血功能*/
	recoverBloodSelf();
	
	/*boss逃跑*/
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
					
		/*仇恨范围搜寻*/
		schCamp();
		
		/*如果仇恨列表不为空*/
		if(!enmityValues.empty())   
		{						
			/*这个是从仇恨列表里面得到的最高值，至于怎么得到的，则要看仇恨计算*/
			perHero = getHero(perHerId);
			
			if(perHero == NULL || !perHero->getLifeStation())
			{
				return;	
			}
			
			heroPt = perHero->getLogPt();
			
			/*攻击距离判断*/
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
		}
		else
		{	
			/*如果上次正在追人，而这次仇恨没人，则立即停下来*/
			if(isPersuitHero)
			{
				stopMove();
				
				isPersuitHero = false;
			}
			
			/*回血功能*/
//			recoverBloodSelf();
		
			/*归位*/
            if(Rec)
            { 			
				/*判断是否已定身*/
				if(!skiBody)
				{
					stopMove();
					return;
				}
				
				if(perLstPt == logic_pt)
				{
					Rec = false;
					return;
				}
				/*避免多次寻路*/
				if(keyPath.empty())
				{
					/*寻自己的路*/
					findSlfWay(perLstPt);
				}
				
			}			
		}		
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
	


MonsterCamp::~MonsterCamp(void)
{

}

MonsterBase* MonsterCamp::copyMon(char *_mapId)
{
	char newIntId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};     
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
	
	newMon = new MonsterCamp(_mapId,typeId,nickName,newIntId,type,kind,experience,\
	cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,outAttVal,\
	inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,walk_ranage,hatRge,\
	attack_range,failGoodsLess,failGoodsMost,hatVal,gold,failList,pt,rank,speed,\
	fiveEleInt,fiveHurt,fiveEleRank,forGo,expTme,monyTme,stage,photoId,skiIdSet,\
	genAttId,angVal,ownerAttriType,ownerAttri,attackRatio,isInnerAttack,lveCtnMager,campFlg);
	newMon->setIsCallType(isCallType);
	return newMon;
}
	
/*怪物死亡函数*/
void MonsterCamp::die(bool flgInit)
{	
	MonsterBase::die(flgInit);
}

/*重置怪物数据*/
void MonsterCamp::initMonsterALL(void)
{
	MonsterBase::initMonsterALL();
}

/* 搜寻自己一个屏幕上的hero，看是不是在仇恨范围内*/
void MonsterCamp::schCamp(void) 
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
	
    
	
    for(her_it = HeroIdSet.begin(); her_it != HeroIdSet.end(); her_it++)
    {		
		myHero = heroid_to_hero(*her_it);
        if(myHero == NULL || myHero->getLifeStation() == DEAD || !myHero->getWalkingFlg())
        {
            continue;
        }
		
		if(myHero->getCamp() == campFlg)
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
		
        if(sqrt(pow(fabs(heroPt._x - born_pt._x),2)+pow(fabs(heroPt._y - born_pt._y),2)) < hatRge)
        {
            HatVal hat(const_cast<char *>((*her_it).c_str()),hatValRue->getHatInRag());
            new_enmy.push_back(hat);
			
			myHero->insertAttList(identity);
        }
    }
	
	if(map_now != NULL && map_now->getFlgCpy())
	{
		isCpy = true;
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

    /*如果目标不为空，且目标还在仇恨范围内*/
    if(flag > 0)
    {
        /*仇恨列表中不止1个人*/
        if(enmityValues.size() >= 2)
        {
            hatf_it = enmityValues.begin();
            hats_it =  hatf_it;
            hats_it ++;

            /*判断是否满足条件，更改目标*/
            if((*hats_it).value > (*hatf_it).value * hatValRue->getChageAirPer())
            {
                chageEny(((*hats_it).id));
            }
        }
    } 
	else
    {
        /*更改目标为仇恨列表的头结点*/
        chageEny((*(enmityValues.begin())).id);      
    }
}   




	

































			




	





			














	



			




