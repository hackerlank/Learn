#include "pet.h"
#include"boxAsist.h"
#include "campWarManagement.h"		//阵营战管理类头文件
#include "hero_fight.h"
extern map<string,Wagon*> wagonInstMap;						//马车实例

extern map<string, Hero*> heroId_to_pHero;
extern campWarManagement campWarController;

void Pet::attactHero(Hero *hero,double skiHrtRatio,double _cdTime,char* skill_id)
{
	Hero *owner;
	int attack;  //伤害值	
	int heroLife;
	heroLife = hero->getLifeVal();
	hero->stopCollectTimer(3);
	attack = countAttValHero(hero,skiHrtRatio,_cdTime);
	if (attack==0)
	{
		attackFlag=3;
	}
	else if (attack<0)
	{
		attackFlag=3;
	}
	else
	{			
		if (heroLife>=attack)
		{
			heroLife=heroLife-attack;
		}
		else
		{
			heroLife=0;
		}	
		hero->setLifeVal(heroLife);	
	}	
	
	sendAttactMsgHero(hero,attack,skill_id);
	if(heroLife == 0)
	{
		/*add chenzhen 20130124 ,宠物打人也会导致主人红名*/
		owner = heroid_to_hero(masterId);
		if(owner != NULL)
		{
			owner->term(hero);	
			
			/*****************added by xhm******************/
			if(hero->getisRedName())//如果被击杀者是红名，增加角色击杀红名值大小；
			{
				if(owner->addReadNameKillsValue(1))
					cout<<"[XHM WARNING] AddReadNameKillsValue ERROR(pet_atack_hero.cpp)."<<endl;
			}
			
			if(owner->isInCampWar()&&hero->isInCampWar())//如果击杀者和被击杀者都是在阵营战中，执行以下操作。
			{
				int campWarType = hero->getCampWarType();//如果被击杀者条件符合，增加被击杀者的死亡次数；
				if(campWarType >= 2&& campWarController.addDeathInCampWar(hero) < 0)
				{
					cout<<"[XHM WARNING] Added deaths in the CampWar ERROR(pet_atack_hero.cpp)."<<endl;
				}
				
				campWarType = owner->getCampWarType();//如果击杀者条件符合，增加击杀者的杀敌次数；
				if(campWarType >= 1 && campWarController.addKillsInCampWar(owner) < 0)
				{
					cout<<"[XHM WARNING] Added kills in the CampWar ERROR(pet_atack_hero.cpp)."<<endl;
				}
			}
			/*****************end by xhm******************/			
		}
		hero->setLifeStation(DEAD);
	}
}

/*宠物群攻判定*/
void Pet::attactHeroArrange(Hero* hero,double skiHrtRatio,double _cdTime,int index)
{
	Hero *owner=heroid_to_hero(masterId);
	if (owner==NULL)
	{
		return;
	}
	
	Map_Inform *mapNow = owner->getMap();
	if (mapNow==NULL)
	{
		return;
	}
	
	
	// 群体指向性技能不闪避
	float hitTimes = 1.0f;
	int lifeHurt = 0;
	unsigned range = 0;
	bool isCrit = false;
	// 群攻技能不带debuff
	
	int atkNum = 0;			//受攻击人数
	char msg[4096] = {0};
	char tempMsg[4096] = {0};
	sprintf(msg, "26,2,1,%s,%d,%s,%d,%d,%d,%d,%d,%d,%d",petdata->petskilldata[index-1].id, 1,
		petdata->identity, 100, 100, 100,100,0, 0, isCrit);
	// cout<<"It have enter here and msg is "<<msg<<endl;
	Nbox *box = mapNow->getBox();
	if (box == NULL)
	{
		return;
	}
	Point objPt;
	Point tempPt;
	
	objPt = hero->getLocation();
	
	range = petdata->petskilldata[index-1].range;
	if (range != 200)
	{
		range = 200;
	}

	range += 50;								//比客户端放大50范围
	
	OneScreen *neighborScrs[4] = {0}, *oneScr = NULL;
	box->getNeighbour(objPt, neighborScrs);
	set<string> tempSet;
	for (int i = 0; i < 4; i++)
	{
		oneScr = neighborScrs[i];
		if (oneScr == NULL)
		{
			continue;
		}
		// cout<<"hero pk state is "<<owner->gethero_PK_status()<<endl;
		if (owner->gethero_PK_status() != PEACE_MODE)
		{
			set<string>::iterator it_id;
			tempSet = oneScr->heroSet;
			for (it_id = tempSet.begin(); it_id != tempSet.end(); it_id++)
			{
				if (!strcmp(owner->getIdentity(), (*it_id).c_str()))
				{
					// 是宠物的主人
					continue;
				}
				Hero *hitedHero = heroid_to_hero(*it_id);
				if (hitedHero == NULL)
				{
					continue;
				}
				// 已经死亡
				if (hitedHero->getLifeVal() <= 0)
				{
					cout<<"The atked hero is dead when use many atk skill"<<endl;
					continue;
				}
				// 无敌状态
				if (hitedHero->skillBuffState & BUFF_INVINCIBLE_STATE)
				{
					cout<<"The atked hero is invinc for atk"<<endl;
					continue;
				}
				if (relationCheck(owner, hitedHero, mapNow) != 2)
				{
					// 不是敌人，不能攻击
					cout<<"The hero is not your enemy when use many atk skill !!"<<endl;
					continue;
				}
				tempPt = hitedHero->getLocation();
				cout<<"really distance is:"<<GET_DISTANCE(tempPt, objPt)<<endl;
				cout<<"can hurt range is:"<<range<<endl;
				if (IS_OUT_RANGE(tempPt, objPt, range))
				{
					// 不在作用范围内
					cout<<"The atked hero is out of range when use many atk skill!!"<<endl;
					continue;
				}
				// 群体伤害不算攻击后反弹
				lifeHurt = countAttValHero(hitedHero, skiHrtRatio, 1);
				sprintf(tempMsg + strlen(tempMsg), ",%s,%d,%d,%d,%d,%d,%d", hitedHero->getIdentity(),
				JUDGE_WILL_LIFE(hitedHero, lifeHurt), hitedHero->getLifeUpperVal(), hitedHero->getMagicVal(),
				hitedHero->getMagicUpperVal(), lifeHurt, 0);
				atkNum++;
				proc_hero_lose_life(owner, hitedHero, lifeHurt);
			}
		}
		if (oneScr->monsterSet.size() != 0)
		{
			set<string>::iterator it_monId;
			tempSet.clear();
			tempSet = oneScr->monsterSet;
			for (it_monId = tempSet.begin(); it_monId != tempSet.end(); it_monId++)
			{
				// cout<<"attack one mon and monId is "<<(*it_monId)<<endl;
				if((*it_monId).size()==0) continue; //added by benliao
				MonsterBase *mon = mapNow->getMonsterObj((*it_monId).c_str());
				if (mon == NULL)
				{
					continue;
				}
				if (mon->getLifeVal() <= 0 || !mon->getLifeStation())
				{
					// 怪物已经死亡
					continue;
				}
				tempPt = mon->getLocation();
				if (IS_OUT_RANGE(tempPt, objPt, range))
				{
					// 不在作用范围内
					continue;
				}
				if (mon->getUnEnemySta())
				{
					// 怪物处于无敌状态
					continue;
				}
				lifeHurt = countAttValMonster(mon, skiHrtRatio, 1);
				sprintf(tempMsg + strlen(tempMsg), ",%s,%d,%d,%d,%d,%d,%d", mon->getIdentity(),
				JUDGE_WILL_LIFE(mon, lifeHurt), mon->getLifeUpperVal(), 100,100, lifeHurt, 0);
				atkNum++;
				
				proc_mon_lose_life(owner, mon, lifeHurt);
			}
		}
		
		if (oneScr->wagonSet.size() != 0 && owner->gethero_PK_status() != PEACE_MODE)
		{
			set<string>::iterator it_wagonId;
			tempSet.clear();
			tempSet = oneScr->wagonSet;
			for (it_wagonId = tempSet.begin(); it_wagonId != tempSet.end(); it_wagonId++)
			{
				cout<<"attack one wagon and wagonId is "<<(*it_wagonId)<<endl;
				Wagon* wagon = NULL;
				map<string, Wagon*>::iterator it_wagon;
				it_wagon = wagonInstMap.find(*it_wagonId);
				if (it_wagon == wagonInstMap.end())
				{
					continue;
				}
				
				wagon = it_wagon->second;
				
				if (wagon == NULL)
				{
					continue;
				}
				if (wagon->getLifeVal() <= 0)
				{
					// 怪物已经死亡
					continue;
				}
				Hero *wagonOwner = wagon->getOwner();
				if (wagonOwner != NULL && strcmp(wagonOwner->getIdentity(), owner->getIdentity()) == 0)
				{
					// 自己的马车不能攻击
					continue;
				}
				tempPt = wagon->getLocation();
				if (IS_OUT_RANGE(tempPt, objPt, range))
				{
					// 不在作用范围内
					continue;
				}
				lifeHurt = wagon->getHurt();
				sprintf(tempMsg + strlen(tempMsg), ",%s,%d,%d,%d,%d,%d,%d", wagon->getIdentity(),
					JUDGE_WILL_LIFE(wagon, lifeHurt), wagon->getLifeUpperVal(), 100, 100, lifeHurt, 0);
				atkNum++;
				
				proc_wagon_lose_life(owner, wagon, lifeHurt);
			}
		}
		
		
		if (oneScr->bottleSet.size() != 0)
		{
			set<string>::iterator it_bottleId;
			tempSet.clear();
			tempSet = oneScr->bottleSet;
			for (it_bottleId = tempSet.begin(); it_bottleId != tempSet.end(); it_bottleId++)
			{
				cout<<"attack one bottle and bottleId is "<<(*it_bottleId)<<endl;
				Bottle *bottInst = NULL;
				bottInst = mapNow->getBotInst(const_cast<char*>((*it_bottleId).c_str()));
				if (bottInst == NULL)
				{
					continue;
				}
				
				if (bottInst->getLifeVal() <= 0)
				{
					// 怪物已经死亡
					continue;
				}
				
				tempPt = bottInst->getPiexPt();
				if (IS_OUT_RANGE(tempPt, objPt, range))
				{
					// 不在作用范围内
					continue;
				}
				lifeHurt = bottInst->getHurt();
				sprintf(tempMsg + strlen(tempMsg), ",%s,%d,%d,%d,%d,%d,%d", bottInst->getId(),
					JUDGE_WILL_LIFE(bottInst, lifeHurt), bottInst->getLifeUpperVal(),100, 100, lifeHurt, 0);
				atkNum++;
				
				proc_bottle_lose_life(owner, bottInst, lifeHurt);
			}
		}
	}
	sprintf(msg + strlen(msg), ",%d%s",atkNum, tempMsg);
	send_nine_msg(owner, msg);
}

int Pet::countAttPerGenHero(Hero *hero)
{
	int genAtt;  //普通攻击值           

    /*普通攻击计算*/
	if (petdata->flag==1)
	{
		genAtt=outAttackValTotal*(1-hero->getOutDefense()/(hero->getGradeNow()*500+hero->getOutDefense()));
	}
	else
	{
		genAtt=inAttackValTotal*(1-hero->getInDefense()/(hero->getGradeNow()*500+hero->getInDefense()));
	}	
	return genAtt;
}

int Pet::countHitPerHero(Hero *hero)
{
	int dodge=hero->getDodge();
	double hitPer=((hitTotal*20*100)/(hitTotal*20+dodge));
	int test=random(1,100);
	
	if (test>hitPer)
	{
		attackFlag=3;
		return 0;
	}
	else
	{
		return 1;
	}
}

/*计算暴击率*/
int Pet::countCritPerHero(Hero *hero)
{
	int heroTenacity=hero->getTenacity();
	double critPer;        //暴击率  	
	
	critPer=(15+critTotal/30)*(100-(5+heroTenacity/30))/100;	

	int test=random(1,100);

	if (test<=critPer)
	{
		attackFlag=1;
		return 1;
	}
	else 
	{
		return 0;
	}
}

int Pet::countAttValHero(Hero *hero,double skiHrtRatio,double _cdTime)
{
	if (hero==NULL)
	{
		return 0;
	}
	int critFlag;       //暴击
	int hitFlag ;       //命中率 
	int getAttackVal;
	double attackVal;			//最终伤害值
	attackFlag=0;
	critFlag = countCritPerHero(hero);	
	hitFlag=countHitPerHero(hero);
	getAttackVal=countAttPerGenHero(hero);
		
	// cout<<"hitFlag:"<<hitFlag<<endl;
	// cout<<"getAttackVal:"<<getAttackVal<<endl;
	// cout<<"_cdTime:"<<_cdTime<<endl;
	// cout<<"skiHrtRatio:"<<skiHrtRatio<<endl;
	// cout<<"critFlag:"<<critFlag<<endl;
	// cout<<"critTimes:"<<critTimes<<endl;
	// cout<<"fiveHarmVal:"<<fiveHarmVal<<endl;
    if (hitFlag==0)
	{
		attackVal=0;
	}
	else
	{
		if (critFlag==0)
		{
			attackVal=getAttackVal;
		}
		else
		{
			attackVal=getAttackVal*2;
		}
	}  
	// cout<<"this attack damage is "<<attack<<" in pet_attact.cpp 105"<<endl;
	cout<<"attackVal:"<<attackVal<<endl;
	return attackVal;
}

void Pet::sendAttactMsgHero(Hero *hero,int attack,char* skill_id)
{
	if (hero==NULL)
	{
		return;
	}
	
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%d,%s,%d,%d,%d,%d,%d,%d",26,2,1,skill_id,1,petdata->identity,\
	100,100,100,100,0,0);
	if (attackFlag==1)
	{
		snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d",1);
	}
	else
	{
		snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d",0);
	}
	snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d,%s,%d,%d,%d,%d,%d",1,hero->getIdentity(),hero->getLifeVal(),hero->getLifeUpperVal(),hero->getMagicVal(),hero->getMagicUpperVal(),attack);
	if (attackFlag==3)
	{
		snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d",1);
	}
	else
	{
		snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d",0);
	}
	
	
    map<string,Hero*>::iterator hero_it;

	map<string,StyObj>nbox_id_set;
	
	StyObj obj(petdata->identity,PET_STYLE_TYPE);
	
	Map_Inform *mapNow;
	mapNow = hero->getMap();
	if(mapNow == NULL)
	{
		return;
	}
	
	Nbox *box;
	box = mapNow->getBox();
	if(box == NULL)
	{
		return;
	}
	
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(g_out_buf);	
	
	return;
	
	
}
