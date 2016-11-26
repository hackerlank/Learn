#include "pet.h"
#include "dropgoods.h"
#include "boxAsist.h"
#include "hero_fight.h"
#include "instancing_manage.h"		//塔防副本管理类头文件
extern map<string, Hero*> heroId_to_pHero;
extern Instancing_manage *Inst_MNG;
extern map<string,Wagon*> wagonInstMap;						//马车实例
void Pet::attactMonster(MonsterBase *monster,double skiHrtRatio,double _cdTime,char* skill_id)
{
	int attack;  //伤害值	
	int monsterLife;
	
	monsterLife = monster->getLifeVal();
	attack = countAttValMonster(monster,skiHrtRatio,_cdTime);
	if (attack==0)
	{
		attackFlag=3;
	}
	else
	{			
		if (monsterLife>=attack)
		{
			monsterLife=monsterLife-attack;
		}
		else
		{
			monsterLife=0;
		}			
		monster->setLifeVal(monsterLife);	
	}
	sendAttactMsgMonster(monster,attack,skill_id);	
	monster->setGoodsOwner(masterId);
	if(monsterLife == 0)
	{
		char* heroId=monster->getGoodsOwner();
		if (heroId==NULL)
		{
			heroId=masterId;
		}
		Hero *hero=heroid_to_hero(heroId);
		if (hero!=NULL)
		{				
			dropTaskGoods(hero,monster);
			getexperience(hero,monster);
		}
		
		/*活动boss没有所有者*/
		if(strcmp(monster->getType(),"ActiveBossMon") == 0)
		{			
			strncpy(heroId,"0",2);
		}
		monsterDropGoods(heroId,monster);
		monster->setLifeStation(false);
		
		
		//Tory add 2012.7.20 starting 塔防怪物死亡后的数值处理
		//塔防副本怪,怪物死亡后应将死亡怪物ID从角色吸引怪物的Id列表中删除
		string behavior_type = monster->getType();
		if(behavior_type.find("Tower") != string::npos)   	
		{
			HatVal* hatva = monster->getOneEnmityValues();
			if(hatva != NULL)
			{
				string des_heroId = hatva->id;
				map<string, Hero*>::iterator hero_it;
				hero_it = heroId_to_pHero.find(des_heroId);
				if(hero_it == heroId_to_pHero.end())
				{
					cout<<"return from attack_monster_success,cause can't find the enermy hero: "<<des_heroId<<endl;
				}
				Hero *in_hero = hero_it->second;            //in_hero--->怪物判定范围之内包含的角色	
				//cout<<"before in_hero->getAttracMonNum()"<<in_hero->getAttracMonNum()<<endl;
				in_hero->delAttracMonId(monster->getIdentity());		//从吸引怪物ID容器删除掉死亡了的怪物ID
				//cout<<"after in_hero->getAttracMonNum()"<<in_hero->getAttracMonNum()<<endl;        
			}
				
			Map_Inform *map_now = monster->getMap();
			string td_room = map_now->getTd_roomid();
			TD_Instancing *this_inst = Inst_MNG->id2tdRoom(td_room);
			this_inst->AddSelfInstancingStatus(INST_STATUS_HELP_VAL);			//统计击杀怪物数目，增加斗气值
			this_inst->AddSelfInstancingStatus(INST_STATUS_MONSTER_DISAPPEAR);	//MONSTER_DISAPPEAR加1
			
		}
		// cout<<"die monsterId:"<<monster->getIdentity()<<endl;
		//tory add 2012.7.20 ending
		
		
		monster->die();		
	}	
}

/*宠物群攻判定*/
void Pet::attactMonsterArrange(MonsterBase *monster,double skiHrtRatio,double _cdTime,int index)
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
	
	objPt = monster->getLocation();
	
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

int Pet::countAttPerGenMonster(MonsterBase *monster)
{
	int genAtt;  //普通攻击值           

    /*普通攻击计算*/
	if (petdata->flag==1)
	{
		genAtt=outAttackValTotal*(1-monster->getOutDefVal()/(monster->getRank()*500+monster->getOutDefVal()));	
	}
	else
	{
		genAtt=inAttackValTotal*(1-monster->getInDefVal()/(monster->getRank()*500+monster->getInDefVal()));	
	}
	// cout<<"genAtt:"<<genAtt<<endl;
	return genAtt;
}

int Pet::countCritPerMonster(MonsterBase *monster)
{
	int monTenacity=monster->getTenty();
	double critPer;        //暴击率  
	
	critPer=(15+critTotal/30)*(100-(5+monTenacity/30))/100;

	int test=random(1,100);
	// cout<<"--------------------------"<<endl;
	// cout<<"pet crit:"<<critTotal<<endl;
	// cout<<"monster monTenacity:"<<monTenacity<<endl;
	// cout<<"critPer:"<<critPer<<endl;
	// cout<<"test:"<<test<<endl;
	// cout<<"--------------------------"<<endl<<endl<<endl;
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

int Pet::countHitPerMonster(MonsterBase *monster)
{
	int dodge=monster->getVoids();
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

int Pet::countAttValMonster(MonsterBase *monster,double skiHrtRatio,double _cdTime)
{
	if (monster==NULL)
	{
		return 0;
	}
	int critFlag;       //暴击
	int hitFlag ;       //命中率 
	int getAttackVal;
	double attackVal;			//最终伤害值
	attackFlag=0;
	critFlag = countCritPerMonster(monster);	
	hitFlag=countHitPerMonster(monster);
	getAttackVal=countAttPerGenMonster(monster);
	getAttackVal=getAttackVal*(1+skiHrtRatio);
	
	// cout<<"critFlag:"<<critFlag<<endl;
	// cout<<"hitFlag:"<<hitFlag<<endl;
	// cout<<"getAttackVal:"<<getAttackVal<<endl;
	// cout<<"critTimes:"<<critTimes<<endl;
	// cout<<"fiveHarmValue:"<<fiveHarmValue<<endl;
	
	// cout<<critFlag<<"  "<<reduceInjury<<"  "<<hitHarmPer<<"  "<<hitFlag<<"  "<<getAttackVal<<endl;
	
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
//	cout<<"this attack damage is "<<attack<<" in pet_attact_monster.cpp 130"<<endl;
	return attackVal;
}

void Pet::sendAttactMsgMonster(MonsterBase *monster,int attack,char* skill_id)
{
	if (monster==NULL)
	{
		return;
	}
	// cout<<"begin to send msg"<<endl;
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
	snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d,%s,%d,%d,%d,%d,%d",1,monster->getIdentity(),monster->getLifeVal(),monster->getLifeUpperVal(),monster->getMagicVal(),monster->getMagicUpperVal(),attack);
	if (attackFlag==3)
	{
		snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d",1);
	}
	else
	{
		snprintf(g_out_buf+strlen(g_out_buf),sizeof(g_out_buf)-strlen(g_out_buf),",%d",0);
	}
	
	StyObj obj(petdata->identity,PET_STYLE_TYPE);	
	
	Map_Inform *mapNow;
	mapNow = monster->getMap();
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
