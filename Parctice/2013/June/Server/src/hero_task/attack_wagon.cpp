/****************************************************************
 * Filename: hero_attack_wagon.cpp
 * 
 * Description: 马车被击
 *
 * Original Author : bison, 2012-9-10
 *
 ****************************************************************/
#include"attack_wagon.h"
#include"hero.h"
// #include"command_game_fight_manage.h"
#include"task_failed_comm.h"
#include"wholeDefine.h"

extern map<string,Wagon*> wagonInstMap;						//马车实例
extern map<string, Hero*> heroId_to_pHero;					//玩家实例
extern map<string,Pet*>	id_to_activePet;					//宠物实例

extern int sock_fd; 
extern int g_msg_len;
extern Hero* pg_hero;

void attactWagonComm(char *buff)
{
#if 0
	char *wagonId;							//马车Id
	char *skillId;							//使用技能的Id
	int index = 0;							//攻击者类型
	
	MSG_BEGIN(buff, g_msg_len);
	MSG_INT(index);
	MSG_CHAR(wagonId);
	MSG_CHAR_END(skillId);
	
	//由fd查hero实例
	Hero *hero = pg_hero;
	
	map<string,Wagon*>::iterator it_wagon;
	//cout<<"BisonTest：wagonInstMap size is "<<wagonInstMap.size()<<endl;
	it_wagon = wagonInstMap.find(wagonId);
	if (it_wagon == wagonInstMap.end())
	{
		//没有这个马车
		cout<<"BisonTest: Attack failed because of no the wagon of this id "<<wagonId<<endl;
		return;
	}
	
	Wagon *wagon = it_wagon->second;
	
	Map_Inform *wagonMap = hero->getMap();
	if (wagonMap == NULL)
	{
		cout<<"This Map no Id ????????????????????"<<endl;
		return;
	}
	char *wagonMapId = wagonMap->getIdentity();
	if (strcmp(wagonMapId, "map_001") == 0)
	{
		cout<<"You can't attack wagon In This Map"<<endl;
		return;
	}
	char* owerId;
	Hero *owner = wagon->getOwner();
	if (owner == NULL)
	{
		cout<<"This wagon has no owner, but you can attack it"<<endl;
		goto LG;	//没有主人的马车也能被打
		// return;
	}
	//马车主人不能打自己的马车
	owerId = owner->getIdentity();
	if (!strcmp(owerId, hero->getIdentity()))
	{
		return;
	}
LG: ;	
	//全用像素点
	Point wagonLocation = wagon->getPt();
	int range;			//攻击者的攻击范围
	//bool isLive;		//马车是否还活着
	int distance = 0;	//攻击者离马车距离
	
	Skill *skill; 
	//int skillNeedMagic = 0;						//技能的魔法消耗
	int attackLife = 100;						//攻击者当前血量……置为宠物的属性值
	int attackMagic = 100;						//攻击者魔法……置为宠物的属性值
	//int attackHurt = wagon->getHurt();			//马车每次被攻击掉血固定
	//index = 0 为人攻击马车
	if (index == 0)
	{
		map<string,Skill*> attack_skill_list;				//玩家角色的技能列表	
		map<string,Skill*>::iterator skill_iter;
		attack_skill_list = hero->getSkill_list();	
		skill_iter = attack_skill_list.find(skillId);
		if(skill_iter == attack_skill_list.end())
		{
			cout<<"BisonTest: hero does not has this skill to use when attack wagon"<<endl;
			return;
		}                   
		skill = skill_iter->second;							//玩家所使用的技能
		
		if (skill->gettype() != 1 || skill->geteffect() != 1)
		{
			//管你是群攻还是医疗，只要不是主动技能都别用来搞马车
			cout<<"skill type can't attack wagon"<<endl;
			return;
		}
		
		if(!isFightStatusOfHero(hero, skill))					//判断玩家的真气，和技能的时间是否符合条件
		{
			cout<<"BisonTest: magical or time is not ok to use this skill"<<endl;
			return;
		}
		
		cout<<"BisonTest: Hero attacks the wagon "<<wagonId<<endl;
		//判断距离是否够
		Point heroLocation = hero->getLocation();
		int deltaX = wagonLocation._x - heroLocation._x;
		int deltaY = wagonLocation._y - heroLocation._y;
		int distance = sqrt(deltaX * deltaX + deltaY * deltaY);
		range = hero->getAtk_range();
		cout<<"BisonTest: distance is "<<distance<<" hero attack range is "<<range<<endl; 
		if (distance > range)
		{
			cout<<"BisonTest: The wagon is out attack range"<<endl;
			return;
			
		} else {
			//攻击者者扣蓝
			//hero->setMagicVal(hero->getMagicVal() - skillNeedMagic);
			PropertyOfAttackerChange(hero, skill);
			//玩家的当前血蓝
			attackLife = hero->getLifeVal();		//难道还有攻击者自身会掉血的情况？不懂，随着他们用
			attackMagic = hero->getMagicVal();
		}
	} else if (index == 1) {
		//index = 1，为宠物打马车
		Pet *pet = hero->getPetBox()->getActivePet();
		if (pet == NULL)
		{
			cout<<"BisonTest: hero have no active Pet "<<endl;
			return;
		} else {
			//宠物位置
			Point petLocation = pet->getLogicNow();
			petLocation = LogicalExchangeMap(petLocation);
			int deltaX = wagonLocation._x - petLocation._x;
			int deltaY = wagonLocation._y - petLocation._y;
			int distance = sqrt(deltaX * deltaX + deltaY * deltaY);
			range = pet->getAttackRange();
			cout<<"BisonTest: distance is "<<distance<<" pet attack range is "<<range<<endl; 
			if (distance > range)
			{
				cout<<"BisonTest: The wagon is out attack range"<<endl;
				return;
				
			} 
		}
	} else {
		return;
	}
	
	attackWagon(hero->getIdentity(), attackLife, attackMagic, skillId, wagonId);
#endif
}

void attackWagon(char* attackerId, int attackerCurLife, int attackerCurMagic, char* skillId, char* wagonId)
{
#if 0
	Hero *attHero;
	Map_Inform *map_now;
	Nbox* box;
	map<string,Wagon*>::iterator it_wagon;
	//cout<<"BisonTest：wagonInstMap size is "<<wagonInstMap.size()<<endl;
	it_wagon = wagonInstMap.find(wagonId);
	if (it_wagon == wagonInstMap.end())
	{
		//没有这个马车
		return;
	}
	attHero = heroid_to_hero(attackerId);
	if(attHero == NULL)
	{
		return;
	}
	
	Wagon *wagon = it_wagon->second;
	
	// string msg;						//消息
	map<string,StyObj> nbox_id_set;		//马车的九宫格成员
	Point wagonLocation = wagon->getLogicPt();
	Point piexPt;
	piexPt = attHero->getLocation();	
	StyObj obj(wagonId,WAGON_STYLE_TYPE);
	
	//获取马车的九宫格,改用攻击者九宫格
	map_now = attHero->getMap();
	if(map_now == NULL)
	{
		return;
	}
	box = map_now->getBox();
	if(box == NULL)
	{
		return;
	}
	box->getStaInSrcVec(obj);
	
	cout<<"BisonTest: nbox size is "<<nbox_id_set.size()<<endl;
	bool isLive = wagon->beAttacked();
	
	char msg[400];
	//向周围人发马车被攻击消息
	// msg = "2";
	// msg += intTostring(ATTACK_RETURN_SELF);
	// msg += intTostring(SUCCESS);
	// msg = msg + "," + skillId;
	// msg = msg + "," + attackerId;
	// msg += intTostring(attackerCurLife);
	// msg += intTostring(attackerCurMagic);
	// msg += intTostring(0);
	// msg += "," + wagonId;
	// msg += intTostring(wagon->getLifeVal());
	// msg += intTostring(wagon->getHurt());
	// msg += intTostring(0);			//表明无暴击无闪避
	// msg += intTostring(piexPt._x);	
	// msg += intTostring(piexPt._y);
	sprintf(msg, "2,%d,1,%s,%s,%d,%d,0,%s,%d,%d,0,%d,%d", ATTACK_RETURN_SELF, skillId, attackerId,
		attackerCurLife, attackerCurMagic, wagonId, wagon->getLifeVal(), wagon->getHurt(),
		piexPt._x, piexPt._y);
	box->sentBoxMsg(msg);
	
	cout<<"BisonTest isLive value is "<<isLive<<endl;
	//马车已经死亡
	if (!isLive)
	{
		cout<<"[BisonSHow] the wagon has been distroyed!"<<endl;
		//向九宫格发马车死亡消息
		wagon->disperMsg();
			
		wagonInstMap.erase(wagonInstMap.find(wagonId));
		
		Hero *owner = wagon->getOwner();
		if(owner != NULL)
		{
			
			//hero的马车没有了
			strncpy(owner->memHero->wagonId, "\0", 2);	
			
			//玩家的马车任务失败
			char taskId[10] = "task00295"; 
			taskFailedDeal(owner, taskId, 1);
			strncpy(taskId, "task00419", 10);
			taskFailedDeal(owner, taskId, 0);
		}
		
		/* Task *task = owner->delAcceptedTaskList(taskId);
		string msg = "5";
		msg += intTostring(TASK_FAILED_RETURN);
		msg += "," + taskId;
		send_msg(owner->getFd(), msg);
		if (task != NULL)
		{
			delete task;
		} */
		delete wagon;
	}
#endif
}
 