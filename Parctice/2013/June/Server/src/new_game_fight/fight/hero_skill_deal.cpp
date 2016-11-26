#include "hero_fight.h"

extern map<string,Wagon*> wagonInstMap;						//马车实例
//技能附带debuff处理--技能没有被闪避的时候调用
void deal_skill_debuff(Hero* atker, HeroSkill* p_skill, unsigned skillLevel,
	unsigned obj_flag, void *obj);
//普通单体指向性技能
void single_aimed_skill_deal(Hero* atker, HeroSkill* p_skill, unsigned skillLevel,
	unsigned obj_flag, void *obj, char *objId, float animationTime)
{
	if (obj_flag == 4)
	{
		puts("come here really really really!!!");
	}
	char msg[1024] = {0};
	sprintf(msg, "26,2,1,");
	int lifeHurt = 0;
	int needMagic = p_skill->getNeedMagic(skillLevel);
	float hitTimes = 0.0f;
	bool isCrit = false;
	bool isReflect = false;
	if (!is_hited_judge(atker, obj_flag, obj, hitTimes, false))
	{
		//出现闪避, 到此结束,满屏发消息，出现了闪避
		sprintf(msg + strlen(msg), "%s,%d,%s,%d,%d,%d,%d,%d,%d,%d", p_skill->getId(), (int)ceil(animationTime),
		atker->getIdentity(), atker->getLifeVal(), atker->getLifeUpperVal(), atker->getMagicVal(),
		atker->getMagicUpperVal(), 0, 0, isCrit);
		if (obj_flag == 1)
		{
			Hero *hero_obj = (Hero*)obj;
			sprintf(msg + strlen(msg), ",%d,%s,%d,%d,%d,%d,%d,%d", 1, objId, hero_obj->getLifeVal(),
			hero_obj->getLifeUpperVal(), hero_obj->getMagicVal(), hero_obj->getMagicUpperVal(), 0, 1);
		} else if (obj_flag == 2) {
			MonsterBase *mon_obj = (MonsterBase*)obj;
			sprintf(msg + strlen(msg), ",%d,%s,%d,%d,%d,%d,%d,%d", 1, objId, mon_obj->getLifeVal(),
			mon_obj->getLifeUpperVal(), 100, 100, 0, 1);
		} else {
			return;
		}
		send_nine_msg(atker, msg);
	} else {
		
		if (obj_flag == 1)
		{
			Hero *obj_hero = (Hero*)obj;
			lifeHurt = attack_hero_cal(atker, obj_hero, hitTimes, p_skill, skillLevel, isCrit);
			int reflectLife = 0;
			decHurtBuffDeal(obj_hero, lifeHurt, reflectLife);
			isReflect = (reflectLife != 0);
			
			sprintf(msg + strlen(msg), "%s,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d,%d,%d,%d", p_skill->getId(),
				(int)ceil(animationTime), atker->getIdentity(),JUDGE_WILL_LIFE(atker, reflectLife),
				atker->getLifeUpperVal(), atker->getMagicVal(), atker->getMagicUpperVal(), reflectLife,
				isReflect, isCrit, 1, objId, JUDGE_WILL_LIFE(obj_hero, lifeHurt), obj_hero->getLifeUpperVal(),
				obj_hero->getMagicVal(), obj_hero->getMagicUpperVal(), lifeHurt, 0);
			send_nine_msg(atker, msg);
			proc_hero_lose_life(obj_hero, atker, reflectLife);
			proc_hero_lose_life(atker, obj_hero, lifeHurt);
			
		} else if (obj_flag == 2)
		{
			MonsterBase* obj_mon = (MonsterBase*)obj;
			lifeHurt = attack_monster_cal(atker, obj_mon, hitTimes, p_skill, skillLevel, isCrit);
			sprintf(msg + strlen(msg), "%s,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d,%d,%d,%d", p_skill->getId(),
				(int)ceil(animationTime),atker->getIdentity(),atker->getLifeVal(), atker->getLifeUpperVal(),
				atker->getMagicVal(), atker->getMagicUpperVal(), 0, 0, isCrit, 1, objId,
				JUDGE_WILL_LIFE(obj_mon, lifeHurt), obj_mon->getLifeUpperVal(), 100, 100, lifeHurt, 0);
			send_nine_msg(atker, msg);
			
			proc_mon_lose_life(atker, obj_mon, lifeHurt);
		} else if (obj_flag == 3)
		{
			Wagon* wagon = (Wagon*)obj;
			lifeHurt = wagon->getHurt();
			sprintf(msg + strlen(msg), "%s,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d,%d,%d,%d", p_skill->getId(),
				(int)ceil(animationTime),atker->getIdentity(),atker->getLifeVal(), atker->getLifeUpperVal(),
				atker->getMagicVal(), atker->getMagicUpperVal(), 0, 0, 0, 1, objId, JUDGE_WILL_LIFE(wagon, lifeHurt),
				wagon->getLifeUpperVal(), 100, 100, lifeHurt, 0);
			send_nine_msg(atker, msg);
			
			proc_wagon_lose_life(atker, wagon, lifeHurt);
			
		} else if (obj_flag == 4)
		{
			Bottle *bottle = (Bottle*) obj;
			lifeHurt = bottle->getHurt();
			proc_bottle_lose_life(atker, bottle, lifeHurt);
			sprintf(msg + strlen(msg), "%s,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d,%d,%d,%d", p_skill->getId(),
				(int)ceil(animationTime),atker->getIdentity(),atker->getLifeVal(),  atker->getLifeUpperVal(),
				atker->getMagicVal(), atker->getMagicUpperVal(), 0, 0, 0, 1, objId, bottle->getLifeVal(),
				bottle->getLifeUpperVal(), 100, 100, lifeHurt, 0);
			cout<<"[BisonShow] msg is :"<<msg<<endl;
			send_nine_msg(atker, msg);
			
		}
		
		//没有出现闪避，检查是否有debuff效果，如果有，先把debuff作用上
		unsigned buffType = p_skill->getBuffType();
		if (buffType != 0)
		{
			deal_skill_debuff(atker, p_skill, skillLevel, obj_flag, obj);
		}
	}
}

//单体指向技能之冲锋
void single_aimed_rush_skill_deal(Hero* atker, HeroSkill* p_skill, unsigned skillLevel,
	unsigned obj_flag, void *obj, char *objId, float animationTime)
{
	char msg[400] = {0};
	sprintf(msg, "26,2,1,");
	int lifeHurt = 0;
	int needMagic = p_skill->getNeedMagic(skillLevel);
	float hitTimes = 0.0f;
	Point destPt;
	//冲锋技能不闪避，
	hitTimes = 1.0f;
	bool isCrit = false;
	bool isReflect = false;
	if (obj_flag == 1)
	{	
		Hero *obj_hero = (Hero*) obj;
		destPt = obj_hero->getLocation();
		lifeHurt = attack_hero_cal(atker, obj_hero, hitTimes, p_skill, skillLevel, isCrit);
		
		int reflectLife = 0;
		decHurtBuffDeal(obj_hero, lifeHurt, reflectLife);
		isReflect = (reflectLife != 0);

		atker->setLocation(destPt);
		
		sprintf(msg + strlen(msg), "%s,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d,%d,%d,%d", p_skill->getId(),
			(int)ceil(animationTime), atker->getIdentity(),JUDGE_WILL_LIFE(atker, reflectLife),
			atker->getLifeUpperVal(), atker->getMagicVal(), atker->getMagicUpperVal(), reflectLife,
			isReflect, isCrit, 1, objId, JUDGE_WILL_LIFE(obj_hero, lifeHurt), obj_hero->getLifeUpperVal(),
			obj_hero->getMagicVal(), obj_hero->getMagicUpperVal(), lifeHurt, 0);
		send_nine_msg(atker, msg);
		proc_hero_lose_life(obj_hero, atker, reflectLife);
		proc_hero_lose_life(atker, obj_hero, lifeHurt);
	} else if (obj_flag == 2)
	{
		MonsterBase* obj_mon = (MonsterBase*)obj;
		destPt = obj_mon->getLocation();
		atker->setLocation(destPt);
		lifeHurt = attack_monster_cal(atker, obj_mon, hitTimes, p_skill, skillLevel, isCrit);
		sprintf(msg + strlen(msg), "%s,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d,%d,%d,%d", p_skill->getId(),
			(int)ceil(animationTime),atker->getIdentity(),atker->getLifeVal(), atker->getLifeUpperVal(),
			atker->getMagicVal(), atker->getMagicUpperVal(), 0, 0, isCrit, 1, objId,
			JUDGE_WILL_LIFE(obj_mon, lifeHurt), obj_mon->getLifeUpperVal(), 100, 100, lifeHurt, 0);
		send_nine_msg(atker, msg);
		proc_mon_lose_life(atker, obj_mon, lifeHurt);
	} else if (obj_flag == 3)
	{
		Wagon* wagon = (Wagon*)obj;
		destPt = wagon->getLocation();
		atker->setLocation(destPt);
		lifeHurt = wagon->getHurt();
		sprintf(msg + strlen(msg), "%s,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d,%d,%d,%d", p_skill->getId(),
			(int)ceil(animationTime),atker->getIdentity(),atker->getLifeVal(), atker->getLifeUpperVal(),
			atker->getMagicVal(), atker->getMagicUpperVal(), 0, 0, 0, 1, objId, JUDGE_WILL_LIFE(wagon, lifeHurt),
			wagon->getLifeUpperVal(), 100, 100, lifeHurt, 0);
		send_nine_msg(atker, msg);
		proc_wagon_lose_life(atker, wagon, lifeHurt);
	} else if (obj_flag == 4)
	{
		Bottle* bottle = (Bottle*)obj;
		destPt = bottle->getPiexPt();
		atker->setLocation(destPt);
		lifeHurt = bottle->getHurt();
		proc_bottle_lose_life(atker, bottle, lifeHurt);
		sprintf(msg + strlen(msg), "%s,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d,%d,%d,%d", p_skill->getId(),
			(int)ceil(animationTime),atker->getIdentity(),atker->getLifeVal(),  atker->getLifeUpperVal(),
			atker->getMagicVal(), atker->getMagicUpperVal(), 0, 0, 0, 1, objId, bottle->getLifeVal(),
			bottle->getLifeUpperVal(), 100, 100, lifeHurt, 0);
		send_nine_msg(atker, msg);
	
	}
	//没有出现闪避，检查是否有debuff效果，如果有，先把debuff作用上
	unsigned buffType = p_skill->getBuffType();
	if (buffType != 0)
	{
		deal_skill_debuff(atker, p_skill, skillLevel, obj_flag, obj);
	}
}

//群体技能 flag = true:群体指向性技能；flag = false:无指向性
void many_hurt_skill_deal(Hero* atker, HeroSkill* p_skill, unsigned skillLevel,
	unsigned obj_flag, void *obj, bool flag, float animationTime)
{
	//群体指向性技能不闪避
	float hitTimes = 1.0f;
	int lifeHurt = 0;
	int needMagic = p_skill->getNeedMagic(skillLevel);
	unsigned range = 0;
	bool isCrit = false;
	//群攻技能不带debuff
	
	int atkNum = 0;			//受攻击人数
	char msg[40960] = {0};
	char tempMsg[40960] = {0};
	sprintf(msg, "26,2,1,%s,%d,%s,%d,%d,%d,%d,%d,%d,%d", p_skill->getId(), int(animationTime),
		atker->getIdentity(), atker->getLifeVal(), atker->getLifeUpperVal(), atker->getMagicVal(),
		atker->getMagicUpperVal(),0, 0, isCrit);
	cout<<"It have enter here and msg is "<<msg<<endl;
	Map_Inform *mapNow = atker->getMap();
	if (mapNow == NULL)
	{
		cout<<"1111111111111111111111111111"<<endl;
		return;
	}
	Nbox *box = mapNow->getBox();
	if (box == NULL)
	{
		cout<<"222222222222222222222222222"<<endl;
		return;
	}
	Point objPt;
	Point tempPt;
	if (flag)
	{
		if (obj_flag == 1)
		{
			objPt = ((Hero*)obj)->getLocation();
		} else if(obj_flag == 2) {
			objPt = ((MonsterBase*)obj)->getLocation();
		} else if (obj_flag == 3) {
			objPt = ((Wagon*)obj)->getLocation();
		}else if (obj_flag == 4) {
			objPt = ((Bottle*)obj)->getPiexPt();
		}
		else {
			cout<<"333333333333333333333333333"<<endl;
			return;
		}
		
		range = p_skill->getHurtRange();
		if (range == 0)
		{
			range = p_skill->getAttackRange();
		}
	} else {
		objPt = atker->getLocation();
		range = p_skill->getHurtRange();
		if (range == 0)
		{
			range = p_skill->getAttackRange();
		}
	}
	if (range == 0)
	{
		cout<<"4444444444444444444444"<<endl;
		return;
	}
	
	OneScreen *neighborScrs[4] = {0}, *oneScr = NULL;
	box->getNeighbour(objPt, neighborScrs);
	set<string> tempSet;
	map<Hero*, int> needProAtkedHero;
	map<MonsterBase*, int> needProAtkedMon;
	map<Bottle*, int> needProAtkedBottle;
	map<Wagon*, int> needProAtkedWagon;
	
	int skillAtkNum = p_skill->getAttkNum(skillLevel);
	cout<<"this many hurt skill skillAtkNum is "<<skillAtkNum<<endl;
	for (int i = 0; i < 4; i++)
	{
		oneScr = neighborScrs[i];
		if (oneScr == NULL)
		{
			continue;
		}
		cout<<"hero pk state is "<<atker->gethero_PK_status()<<endl;
		if (atker->gethero_PK_status() != PEACE_MODE)
		{
			set<string>::iterator it_id;
			tempSet = oneScr->heroSet;
			for (it_id = tempSet.begin(); it_id != tempSet.end(); it_id++)
			{
				if (!strcmp(atker->getIdentity(), (*it_id).c_str()))
				{
					//攻击者自身
					continue;
				}
				Hero *hitedHero = heroid_to_hero(*it_id);
				if (hitedHero == NULL)
				{
					continue;
				}
				//已经死亡
				if (hitedHero->getLifeVal() <= 0)
				{
					cout<<"The atked hero is dead when use many atk skill"<<endl;
					continue;
				}
				//无敌状态
				if (hitedHero->skillBuffState & BUFF_INVINCIBLE_STATE)
				{
					cout<<"The atked hero is invinc for atk"<<endl;
					continue;
				}
				if (relationCheck(atker, hitedHero, mapNow) != 2)
				{
					//不是敌人，不能攻击
					cout<<"The hero is not your enemy when use many atk skill !!"<<endl;
					continue;
				}
				tempPt = hitedHero->getLocation();
				cout<<"really distance is:"<<GET_DISTANCE(tempPt, objPt)<<endl;
				cout<<"can hurt range is:"<<range<<endl;
				if (IS_OUT_RANGE(tempPt, objPt, range))
				{
					//不在作用范围内
					cout<<"The atked hero is out of range when use many atk skill!!"<<endl;
					continue;
				}
				//群体伤害不算攻击后反弹
				lifeHurt = attack_hero_cal(atker, hitedHero, hitTimes, p_skill, skillLevel, isCrit);
				int reflectLife = 0;
				decHurtBuffDeal(hitedHero, lifeHurt, reflectLife);
			
				sprintf(tempMsg + strlen(tempMsg), ",%s,%d,%d,%d,%d,%d,%d", hitedHero->getIdentity(),
				JUDGE_WILL_LIFE(hitedHero, lifeHurt), hitedHero->getLifeUpperVal(), hitedHero->getMagicVal(),
				hitedHero->getMagicUpperVal(), lifeHurt, 0);
				atkNum++;
				// proc_hero_lose_life(atker, hitedHero, lifeHurt);
				needProAtkedHero.insert(pair<Hero*, int>(hitedHero, lifeHurt));
				if (atkNum >= skillAtkNum)
				{
					goto LE;
				}
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
					//怪物已经死亡
					continue;
				}
				tempPt = mon->getLocation();
				if (IS_OUT_RANGE(tempPt, objPt, range))
				{
					//不在作用范围内
					continue;
				}
				if (mon->getUnEnemySta())
				{
					//怪物处于无敌状态
					continue;
				}
				lifeHurt = attack_monster_cal(atker, mon, hitTimes, p_skill, skillLevel, isCrit);
				sprintf(tempMsg + strlen(tempMsg), ",%s,%d,%d,%d,%d,%d,%d", mon->getIdentity(),
				JUDGE_WILL_LIFE(mon, lifeHurt), mon->getLifeUpperVal(), 100,100, lifeHurt, 0);
				atkNum++;
				
				// proc_mon_lose_life(atker, mon, lifeHurt);
				needProAtkedMon.insert(pair<MonsterBase*, int>(mon, lifeHurt));
				if (atkNum >= skillAtkNum)
				{
					goto LE;
				}
			}
		}
		
		if (oneScr->wagonSet.size() != 0 && atker->gethero_PK_status() != PEACE_MODE)
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
					//怪物已经死亡
					continue;
				}
				Hero *wagonOwner = wagon->getOwner();
				if (wagonOwner != NULL && strcmp(wagonOwner->getIdentity(), atker->getIdentity()) == 0)
				{
					//自己的马车不能攻击
					continue;
				}
				tempPt = wagon->getLocation();
				if (IS_OUT_RANGE(tempPt, objPt, range))
				{
					//不在作用范围内
					continue;
				}
				lifeHurt = wagon->getHurt();
				sprintf(tempMsg + strlen(tempMsg), ",%s,%d,%d,%d,%d,%d,%d", wagon->getIdentity(),
					JUDGE_WILL_LIFE(wagon, lifeHurt), wagon->getLifeUpperVal(), 100, 100, lifeHurt, 0);
				atkNum++;
				
				// proc_wagon_lose_life(atker, wagon, lifeHurt);
				needProAtkedWagon.insert(pair<Wagon*, int>(wagon, lifeHurt));
				
				if (atkNum >= skillAtkNum)
				{
					goto LE;
				}
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
					//怪物已经死亡
					continue;
				}
				
				tempPt = bottInst->getPiexPt();
				if (IS_OUT_RANGE(tempPt, objPt, range))
				{
					//不在作用范围内
					continue;
				}
				lifeHurt = bottInst->getHurt();
				//但是瓶子的掉血处理又必须放到群发攻击消息之前，这里一定是设计存在的问题
				proc_bottle_lose_life(atker, bottInst, lifeHurt);
				sprintf(tempMsg + strlen(tempMsg), ",%s,%d,%d,%d,%d,%d,%d", bottInst->getId(),
					bottInst->getLifeVal(), bottInst->getLifeUpperVal(),100, 100, lifeHurt, 0);
				atkNum++;
				
				if (atkNum >= skillAtkNum)
				{
					goto LE;
				}
				
			}
		}
	}

LE:	sprintf(msg + strlen(msg), ",%d%s",atkNum, tempMsg);
	// cout<<"strlen of send_nine_msg "<<strlen(msg)<<"and msg is:"<<endl;
	// cout<<msg<<endl;
	send_nine_msg(atker, msg);
	
	map<Hero*, int>::iterator it_hero;
	map<MonsterBase*, int>::iterator it_mon;
	map<Wagon*, int>::iterator it_wagon;
	
	for (it_hero = needProAtkedHero.begin(); it_hero != needProAtkedHero.end(); it_hero++)
	{
		proc_hero_lose_life(atker, it_hero->first, it_hero->second);
	}
	
	cout<<"needProMon size is "<<needProAtkedMon.size()<<endl;
	for (it_mon = needProAtkedMon.begin(); it_mon != needProAtkedMon.end(); it_mon++)
	{
		proc_mon_lose_life(atker, it_mon->first, it_mon->second);
	}
	
	for (it_wagon = needProAtkedWagon.begin(); it_wagon != needProAtkedWagon.end(); it_wagon++)
	{
		proc_wagon_lose_life(atker, it_wagon->first, it_wagon->second);
	}
}

//单体医疗技能
void single_cure_skill_deal(Hero* owner, HeroSkill* p_skill, unsigned skillLevel, float animationTime)
{
	char msg[400] = {0};
	unsigned cureVal = cure_life_cal(owner, p_skill, skillLevel);
	if (cureVal == 0)
	{
		return;
	}
	unsigned lifeVal = owner->getLifeVal();
	unsigned lifeUpperVal = owner->getLifeUpperVal();
	if (lifeVal + cureVal > lifeUpperVal)
	{
		owner->setLifeVal(lifeUpperVal);
	} else {
		owner->setLifeVal(lifeVal + cureVal);
	}
	sprintf(msg, "26,2,1,%s,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d", p_skill->getId(), (int)ceil(animationTime),
		owner->getIdentity(), owner->getLifeVal(), owner->getLifeUpperVal(),
		owner->getMagicVal(), owner->getMagicUpperVal(), cureVal, 0, 0, 0);
	send_nine_msg(owner, msg);
}

//群体医疗技能
void many_cure_skill_deal(Hero* owner, HeroSkill* p_skill, unsigned skillLevel, float animationTime)
{
	char msg[4000] = {0};
	char temp[4000] = {0};
	unsigned hurtRange = p_skill->getAttackRange();
	
	unsigned cureVal = cure_life_cal(owner, p_skill, skillLevel);
	if (cureVal == 0)
	{
		return;
	}
	unsigned lifeVal = owner->getLifeVal();
	unsigned lifeUpperVal = owner->getLifeUpperVal();
	if (lifeVal + cureVal > lifeUpperVal)
	{
		owner->setLifeVal(lifeUpperVal);
	} else {
		owner->setLifeVal(lifeVal + cureVal);
	}
	sprintf(msg, "26,2,1,%s,%d,%s,%d,%d,%d,%d,%d,%d,%d", p_skill->getId(), (int)ceil(animationTime),
		owner->getIdentity(), owner->getLifeVal(), owner->getLifeUpperVal(), owner->getMagicVal(),
		owner->getMagicUpperVal(), cureVal, 0, 0);
	int cureNum = 0;
	int skillCureMaxNum = p_skill->getAttkNum(skillLevel);
	
	Map_Inform *mapNow = owner->getMap();
	if (mapNow == NULL)
	{
		send_nine_msg(owner, msg);
		// cout<<"11111111111111111111111111111111122"<<endl;
		return;
	}
	Nbox *box = mapNow->getBox();
	if (box == NULL)
	{
		send_nine_msg(owner, msg);
		// cout<<"222222222222222222222222222222233"<<endl;
		return;
	}
	Point objPt;
	Point tempPt;
	
	objPt = owner->getLocation();
#if 0	
	OneScreen *oneScr = &box->getOneSrcMap(objPt);
	if (oneScr == NULL)
	{
		send_nine_msg(owner, msg);
		// cout<<"33333333333333333333333333333344"<<endl;
		return;
	}
#endif

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
			
		set<string>::iterator it_id;
		tempSet = oneScr->heroSet;
		for (it_id = tempSet.begin(); it_id != tempSet.end(); it_id++)
		{
			if (!strcmp(owner->getIdentity(), (*it_id).c_str()))
			{
				//自己已经被医疗过
				continue;
			}
			Hero *hitedHero = heroid_to_hero(*it_id);
			if (hitedHero == NULL)
			{
				continue;
			}
			//已经死亡
			if (hitedHero->getLifeVal() <= 0)
			{
				// cout<<"The hero is dead ,can't cure him"<<endl;
				continue;
			}
			if (relationCheck(owner, hitedHero, mapNow) == 2)
			{
				//是敌人，不能给他加血
				// cout<<"The hero is enemy ,don't cure him!!!!!"<<endl;
				continue;
			}
			tempPt = hitedHero->getLocation();
			if (IS_OUT_RANGE(tempPt, objPt, hurtRange))
			{
				//在作用范围外
				// cout<<"The hero is out cure range!!!!!!"<<endl;
				continue;
			}
			unsigned lifeVal = hitedHero->getLifeVal();
			unsigned lifeUpperVal = hitedHero->getLifeUpperVal();
			if (lifeVal + cureVal > lifeUpperVal)
			{
				hitedHero->setLifeVal(lifeUpperVal);
			} else {
				hitedHero->setLifeVal(lifeVal + cureVal);
			}
			cureNum++;
			sprintf(temp + strlen(temp), ",%s,%d,%d,%d,%d,%d,%d", hitedHero->getIdentity(), hitedHero->getLifeVal(),
			hitedHero->getLifeUpperVal(), hitedHero->getMagicVal(), hitedHero->getMagicUpperVal(), cureVal, 0);
			if (cureNum >= skillCureMaxNum)
			{
				break;
			}
		}
	}
	sprintf(msg + strlen(msg), ",%d%s", cureNum, temp);
	cout<<"cureMsg is :"<<msg<<endl;
	send_nine_msg(owner, msg);
}

//技能没有被闪避的时候调用
void deal_skill_debuff(Hero* atker, HeroSkill* p_skill, unsigned skillLevel,
	unsigned obj_flag, void *obj)
{
	if (obj_flag == 1)
	{
		Hero *obj_hero = (Hero*) obj;
		if (obj_hero->getLifeVal() <= 0)
		{
			return;
		}
		obj_hero->startBufOrDebuffTimer(atker->getIdentity(), p_skill->getId(), skillLevel);
	} else if (obj_flag == 2) {
		MonsterBase *obj_mon = (MonsterBase*)obj;
		if (obj_mon->getLifeVal() <= 0)
		{
			return;
		}
		map<string, Buff_debuff_conf_T*>::iterator it;
		it = buf_debuf_conf.find(p_skill->getId());
		if (it == buf_debuf_conf.end())
		{
			return;
		}
		Buff_debuff_conf_T *conf = it->second;
		int effect = conf->effect;
		int lastTime = conf->lastTimeFactor * skillLevel + conf->lastTimeBase;	//持续时间
		int value = conf->effectIncFactor * skillLevel + conf->effectBase;		//效果值
		//怪物中debuff效果待修改
		obj_mon->inputHitTime(atker->getIdentity(), effect, lastTime, value);
	}
}

void send_nine_msg(Hero *attack, char* msg)
{
	/*九宫格消息发送*/
	Map_Inform *map_now;
    map_now = attack->getMap();
	if(map_now == NULL)
	{
		return;
	}                 				     
    Nbox *box=map_now->getBox(); 	
	if(box == NULL)
	{
		return;
	}
	StyObj obj(attack->getIdentity(),HERO_STYLE_TYPE);
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(msg);
	return;
}
