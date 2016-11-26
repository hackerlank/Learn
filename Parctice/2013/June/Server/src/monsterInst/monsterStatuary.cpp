#include"monsterStatuary.h"
#include<math.h>
#include<list>

extern struct ev_loop *loops;
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Map_Inform*>mapId_connect_map;  
extern HatValRue *hatValRue;          //仇恨值规则类实例指针  


MonsterStatuary::MonsterStatuary(char *_mapId,char *_typeId,char *_nickName,\
char *_identity,char *_type,char *_kind,int _experience,double _cdTime,\
int _lifeUpperVal,int _lifeVal,int _magicUpperVal,int _magicVal,\
int _getHrtSud,int _outHrt,int _inHrt, int _outAttVal,int _inAttVal,\
int _outDefVal, int _inDefVal,int _defSumVal,double _hit,double _crit,\
int _voids,int _tenacity,int _moveRange,int _hatRange,int _attRange,\
int _failGoodsless,int _failGoodsmost,int _hatVal,int _gold,\
set<string>& _failList,Point _pt,int _rank,int _speed,int _fiveEleInt,\
int _fiveHurt,int _fiveEleRank,int _forGo,int _expTme,int _monyTme,\
char *_stage,char *_photoId,vector<string> &skiIdSet,char *_genAttId,\
double _angVal,int _ownerAttriType,char* _ownerAttri,double _attackRatio,bool _isInnerAttack,LveCtnManger _lveCtnMager)\
:MonsterBase(_mapId,_typeId,_nickName,_identity,_type,_kind,_experience,_cdTime,\
_lifeUpperVal,_lifeVal,_magicUpperVal,_magicVal,_getHrtSud,_outHrt,_inHrt, _outAttVal,\
 _inAttVal,_outDefVal,_inDefVal,_defSumVal,_hit,_crit,_voids,_tenacity,_moveRange,_hatRange,\
 _attRange,_failGoodsless,_failGoodsmost,_hatVal,_gold,_failList,_pt,_rank,_speed,_fiveEleInt,\
 _fiveHurt,_fiveEleRank,_forGo,_expTme,_monyTme,_stage,_photoId,skiIdSet,_genAttId,_angVal,\
_ownerAttriType,_ownerAttri,_attackRatio,_isInnerAttack,_lveCtnMager)
{

}	

void MonsterStatuary::response(void)
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
		// cout<<"it is playCd time:"<<endl;
		return;
	}
	
	memset(otherMsg,'\0',MONSTER_MSG_LENGTH + 1);
	
	box->getStaInSrcVec(obj);
	
	/*处理延时性技能*/
	hitedSkiFun();
	
	/*地图没人,判断是否已眩晕*/
	if(!dizz)     
	{
		stopMove();
		return;
	}	
	
	/*回血功能*/
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
		schRge();
		
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
	


MonsterStatuary::~MonsterStatuary(void)
{

}

MonsterBase* MonsterStatuary::copyMon(char *_mapId)
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
	
	newMon = new MonsterStatuary(_mapId,typeId,nickName,newIntId,type,kind,experience,\
	cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,outAttVal,\
	inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,walk_ranage,hatRge,\
	attack_range,failGoodsLess,failGoodsMost,hatVal,gold,failList,pt,rank,speed,\
	fiveEleInt,fiveHurt,fiveEleRank,forGo,expTme,monyTme,stage,photoId,skiIdSet,\
	genAttId,angVal,ownerAttriType,ownerAttri,attackRatio,isInnerAttack,lveCtnMager);
	newMon->setIsCallType(isCallType);
	return newMon;
}
	
/*怪物死亡函数*/
void MonsterStatuary::die(bool flgInit)
{	
	MonsterBase::die(flgInit);
}

/*重置怪物数据*/
void MonsterStatuary::initMonsterALL(void)
{
	MonsterBase::initMonsterALL();
}

/*设置最后一刀者*/
void MonsterStatuary::setHeroId(char *_heroId)
{
	if(_heroId == NULL)
	{
		return;
	}
	memset(heroId,'\0',sizeof(heroId));
	strncpy(heroId,_heroId,strlen(_heroId));
}

/*设置雕像怪属性*/
void MonsterStatuary::setStatuaryAttrit(void)
{
	memset(ownerAttri,'\0',sizeof(ownerAttri));
	
	if(strlen(heroId) == 0)
	{
		cout<<"MonsterStatuary::setStatuaryAttrit the heroId is empty:"<<endl;
		return;
	}
	Hero *hero = getHero(heroId);
	
	setStatuaryAttritByHero(hero);
}
	

/*设置雕像怪属性*/
void MonsterStatuary::setStatuaryAttrit(MemStatuaryHero* memStatuaryHero)
{
	if(memStatuaryHero == NULL)
	{
		cout<<"MonsterStatuary::setStatuaryAttrit the memStatuaryHero is NULL:"<<endl;
		return;
	}
	memset(nickName,'\0',sizeof(nickName));
	strncpy(nickName,memStatuaryHero->heroName,strlen(memStatuaryHero->heroName));
	lifeUpperVal = memStatuaryHero->lifeUpperVal;
	lifeVal = memStatuaryHero->lifeVal;
	magicUpperVal = memStatuaryHero->magicUpperVal;
	magicVal = memStatuaryHero->magicVal;
	rank = memStatuaryHero->level;
}

/*合成雕像怪图片*/
void MonsterStatuary::composPhotoId(void)
{
}
		
/*设置雕像怪属性通过角色*/
void MonsterStatuary::setStatuaryAttritByHero(Hero *hero)
{
	memset(ownerAttri,'\0',sizeof(ownerAttri));
	
	if(hero == NULL)
	{
		cout<<"MonsterStatuary::setStatuaryAttritByHero the hero is NULL:"<<endl;
		
		/*如果角色下线，则设置默认值*/
		lifeUpperVal = 100;
		lifeVal = 100;
		magicUpperVal = 100;
		magicVal = 100;
		rank = 10;
		return;
	}
	
	memset(nickName,'\0',sizeof(nickName));
	strncpy(nickName,hero->getNickName(),strlen(hero->getNickName()));
	lifeUpperVal = hero->getLifeUpperVal();
	lifeVal = lifeUpperVal;
	magicUpperVal = hero->getMagicUpperVal();
	magicVal = hero->getMagicUpperVal();
	rank = hero->getLevel();
	
	/*帮派怪*/
	if(ownerAttriType == 1)
	{		
		strncpy(ownerAttri,hero->getGuildName(),strlen(hero->getGuildName()));
		
		cout<<"MonsterStatuary::setStatuaryAttrit ownerAttri:"<<ownerAttri<<endl;
	}
	/*阵营怪*/
	else if(ownerAttriType == 2)
	{
		sprintf(ownerAttri,"%d",hero->getCamp());
	}
	
}
	





	

































			




	





			














	



			




