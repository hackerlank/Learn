#include "hero_fight.h"
#include"wagon.h"

#define USE_HERO_SKILL_SUCCESS					0				//使用技能成功
#define USE_SKILL_FAILED_ATK_DEAD				1				//技能使用者已经死亡
#define USE_SKILL_FAILED_ATK_IN_ANMT			2				//播放上一技能动画
#define USE_SKILL_FAILED_ATK_IN_DIZZ			3				//玩家在眩晕中
#define USE_SKILL_FAILED_NO_THIS_SKILL			4				//没有此技能
#define USE_SKILL_FAILED_STATIC_SKILL			5				//被动技能
#define USE_SKILL_FAILED_SKILL_CONF_ERROR		6				//配置中新加技能
#define USE_SKILL_FAILED_NOT_UPGRADE			7				//未升级该技能
#define USE_SKILL_FAILED_IN_CD_TIME				8				//技能在CD中
#define USE_SKILL_FAILED_NO_ENOUGH_MP			9				//没有足够魔法
#define USE_SKILL_FAILED_CAN_NOT_ATK_SELF		10				//指向性攻击技能不能攻击自己
#define USE_SKILL_FAILED_NOT_FIND_ATKED_OBJ		11				//攻击的玩家不存在
#define USE_SKILL_FAILED_ATKED_HERO_DIED		12				//攻击者已经死亡
#define USE_SKILL_FAILED_ATKED_HERO_INVINC		13				//被攻击玩家无敌状态
#define USE_SKILL_FAILED_ATKED_IN_DIFF_MAP		14				//被攻击玩家不在同一张图
#define USE_SKILL_FAILED_CAN_NOT_ATK_FRIEND		15				//不能攻击友方单位
#define USE_SKILL_FAILED_CAN_NOT_CURE_ENEMY		16				//不能治疗敌方单位
#define USE_SKILL_FAILED_CAN_NOT_CURE_MON		17				//不能治疗怪物
#define USE_SKILL_FAILED_ATKED_MON_INVINC		18				//被攻击怪物处于无敌状态
#define USE_SKILL_FAILED_ATKED_MON_DIED			19				//被攻击怪物已经死亡
#define USE_SKILL_FAILED_ATKED_TOO_FAR			20				//攻击者距离太远
#define	USE_SKILL_FAILED_HAS_BARR_BETWEEN		21				//冲锋技能中间有障碍
#define USE_SKILL_FAILED_WAGON_DEAD				22				//被攻击马车已经死亡
#define USE_SKILL_FAILED_ATK_SELF_WAGON			23				//不能攻击自己的马车
#define	USE_SKILL_FAILED_ATKED_BOTT_BROKEN		24				//攻击的瓶子已经被打破
#define USE_SKILL_FAILED_PEACE_ATK_WAGON		25				//和平图模式下不能攻击马车

extern map<string, HeroSkill*> skillId_2_heroSkill;		//角色技能
extern map<string,Wagon*> wagonInstMap;						//马车实例
//技能释放者状态检查
int skill_owner_check(Hero *owner, HeroMemSkill_T* &p_memSkill, HeroSkill* &p_skill, char *skillId, int &remainCD);
//技能作用对象检查
int skill_aimed_obj_check(Hero *owner, unsigned skill_flag, unsigned &obj_flag,
	char *objId, void * &obj, Point &obj_loc);
//距离检查
int skill_distance_check(Point ownerPt, Point objPt, int skillType, unsigned distance, Map_Inform *mapNow);

int proc_use_skill(Hero* owner, char *skillId, char *objId, int &remainCD)
{
	owner->stopCollectTimer(2);				//玩家使用技能打断采集
	int ret = 0;
	//第一阶段，检查技能使用者信息
	HeroMemSkill_T *p_memSkill = NULL;
	HeroSkill *p_skill = NULL;
	ret = skill_owner_check(owner, p_memSkill, p_skill, skillId, remainCD);
	if (ret != 0)
	{
		return ret;
	}

	unsigned skill_flag = 0;		//技能类型		0：攻击；1：医疗
	unsigned obj_flag = 0;			//攻击者类型	0:无攻击目标；1:攻击人；2:攻击怪物
	unsigned aim_flag = 0;
	unsigned skillType = p_skill->getType();
	if (skillType == HERO_SKILL_SINGLE_TREAT_TYPE || skillType == HERO_SKILL_MANY_TREAT_TYPE)
	{
		skill_flag = 1;
	}
	if (skillType == HERO_SKILL_NORMAL_TYPE						//普攻
		|| skillType == HERO_SKILL_SINGLE_HURT_TYPE				//单体主动技能
		|| skillType == HERO_SKILL_RUSH_TYPE					//冲锋技能
		|| skillType == HERO_SKILL_MANY_HURT_WITH_AIM_TYPE)		//有指向群体技能
	{
		aim_flag = 1;
	}
	
	//第二阶段检查
	Point obj_loc;
	void *obj = NULL;
	if (aim_flag)			//如果需要有攻击对象的技能
	{
		ret = skill_aimed_obj_check(owner, skill_flag, obj_flag, objId, obj, obj_loc);
		if (ret != 0)
		{
			return ret;
		}
	}
	//第三阶段：距离检查,冲刺技能的是否有障碍检查也放这里
	unsigned distance = p_skill->getAttackRange();
	
	Point ownerPt = owner->getLocation();
	Map_Inform *mapNow = owner->getMap();
	ret = skill_distance_check(ownerPt, obj_loc, skillType, distance, mapNow);
	if (ret != 0)
	{
		return ret;
	}
	
	unsigned level = p_memSkill->level;
	int needMagic = p_skill->getNeedMagic(level);
	float animationTime = p_skill->getAnimationTime();
	//消耗魔法
	owner->setMagicVal(owner->getMagicVal() - needMagic);
	//检查ok
	//记录下技能当前使用时间，一作下次使用的CD判断
	p_memSkill->lastUsedTime = MY_TV_SEC;
	owner->startHeroSkillAnimationTimer(animationTime);
	//攻击处理
	if (skill_flag == 0)
	{
		if (obj_flag != 0)	
		{	
			//有指向技能
			if (skillType == HERO_SKILL_SINGLE_HURT_TYPE || skillType == HERO_SKILL_NORMAL_TYPE)	
			{
				//普通单体指向性技能
				single_aimed_skill_deal(owner, p_skill, level, obj_flag, obj, objId, animationTime);
				
			} else if (skillType == HERO_SKILL_RUSH_TYPE)	
			{
				//单体指向技能之冲锋
				single_aimed_rush_skill_deal(owner, p_skill, level, obj_flag, obj, objId, animationTime);
				
			} else if (skillType == HERO_SKILL_MANY_HURT_WITH_AIM_TYPE)
			{
				//群体指向性技能
				many_hurt_skill_deal(owner, p_skill, level, obj_flag, obj, true, animationTime);
				
			} else {
				cout<<"When you see this may be it caused by the follow three resons:"<<endl;
				cout<<"1:The client have send error comm msg without following the rule!"<<endl;
				cout<<"2:The client's hero skills conf is error"<<endl;
				cout<<"3:The server's hero skills conf is error and the skillId is "<<skillId<<endl;
				return USE_SKILL_FAILED_SKILL_CONF_ERROR;
			}
		} else {
			//无指向攻击技能
			if (skillType == HERO_SKILL_BUFF_TYPE)
			{
				//buff类型技能
				char msg[400] = {0};
				sprintf(msg, "26,2,1,%s,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d", skillId, (int)ceil(animationTime),
					owner->getIdentity(), owner->getLifeVal(), owner->getLifeUpperVal(),
					owner->getMagicVal(), owner->getMagicUpperVal(), 0, 0, 0, 0);
				send_nine_msg(owner, msg);
				owner->startBufOrDebuffTimer(owner->getIdentity(), skillId, level);
				return 0;
				
			} else if (skillType == HERO_SKILL_MANY_HURT_NO_AIM_TYPE) {
				//无指向性群攻技能
				many_hurt_skill_deal(owner, p_skill, level, obj_flag, obj, false, animationTime);
			} else {
				cout<<"When you see this may be it caused by the follow three resons:"<<endl;
				cout<<"1:The client have send error comm msg without following the rule!"<<endl;
				cout<<"2:The client's hero skills conf is error"<<endl;
				cout<<"3:The server's hero skills conf is error and the skillId is "<<skillId<<endl;
				return USE_SKILL_FAILED_SKILL_CONF_ERROR;
			}
		}
	} else {
		//医疗处理
		if (skillType == HERO_SKILL_SINGLE_TREAT_TYPE)
		{
			//单体医疗技能
			single_cure_skill_deal(owner, p_skill, level, animationTime);
			
		} else if (skillType == HERO_SKILL_MANY_TREAT_TYPE)
		{
			//群体医疗技能
			many_cure_skill_deal(owner, p_skill, level, animationTime);
			
		} else {
			cout<<"When you see this may be it caused by the follow three resons:"<<endl;
			cout<<"1:The client have send error comm msg without following the rule!"<<endl;
			cout<<"2:The client's hero skills conf is error"<<endl;
			cout<<"3:The server's hero skills conf is error and the skillId is "<<skillId<<endl;
			return USE_SKILL_FAILED_SKILL_CONF_ERROR;
		}
		
	}
	return USE_HERO_SKILL_SUCCESS;
}

//距离检查
int skill_distance_check(Point ownerPt, Point objPt, int skillType, unsigned distance, Map_Inform *mapNow)
{
	if (skillType == HERO_SKILL_SINGLE_HURT_TYPE				//单体主动技能
		|| skillType == HERO_SKILL_RUSH_TYPE					//冲锋技能
		|| skillType == HERO_SKILL_MANY_HURT_WITH_AIM_TYPE)		//有指向群体技能
	{
		cout<<"222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"<<endl;
		cout<<"222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222"<<endl;
		cout<<"atkRange is "<<distance<<" and distance from the obj is "<<GET_DISTANCE(ownerPt, objPt)<<endl;
		printf("ownerPt(%d,%d) and objPt(%d,%d)", ownerPt._x, ownerPt._y, objPt._x, objPt._y);
		if (distance < GET_DISTANCE(ownerPt, objPt))
		{
			//攻击距离不够
			cout<<"The attacked obj is out of hero skill attack range!"<<endl;
			return USE_SKILL_FAILED_ATKED_TOO_FAR;
		}
#if 0		
		if (skillType == HERO_SKILL_RUSH_TYPE)
		{
			//冲锋技能，中间有障碍点不能冲锋
			if (hasBarrier(ownerPt, objPt, mapNow))//TODO 
			{
				return USE_SKILL_FAILED_HAS_BARR_BETWEEN;
			}
		}
#endif		
	}
	return 0;
}

int skill_aimed_obj_check(Hero *owner, unsigned skill_flag, unsigned &obj_flag,
	char *objId, void * &obj, Point &obj_loc)
{
	Map_Inform* mapNow = owner->getMap();
	char *ownerMapId = owner->getMapId();
	
	if (skill_flag == 0)				//有指向攻击性技能
	{
		//攻击时作用对象不能为自己
		if (!strcmp(objId, owner->getIdentity()))
		{
			cout<<"the hero can't use skill to attack himself!"<<endl;
			return USE_SKILL_FAILED_CAN_NOT_ATK_SELF;
		}
	}
		
	Hero* obj_hero = heroid_to_hero(objId);
	if (obj_hero != NULL)
	{
		obj_flag = 1;			//攻击对象为人
		if (obj_hero->getLifeVal() <= 0)
		{
			cout<<"the hero_skill aimed hero is dead!"<<endl;
			return USE_SKILL_FAILED_ATKED_HERO_DIED;
		}
		
		if (obj_hero->skillBuffState & BUFF_INVINCIBLE_STATE)
		{
			cout<<"the attacked hero is in invincible state(forbiden attack)"<<endl;
			return USE_SKILL_FAILED_ATKED_HERO_INVINC;
		}
		
		char *mapId = obj_hero->getMapId();
		if (strcmp(ownerMapId, mapId) != 0)
		{
			//不在同一张地图上
			cout<<"the skill owner and the obj_hero is not in the same map!"<<endl;
			return USE_SKILL_FAILED_ATKED_IN_DIFF_MAP;
		}
		int rc = relationCheck(owner, obj_hero, mapNow);
		//不能攻击友方单位/和平地图不能相互攻击
		if (skill_flag == 0 && rc <= 1)
		{
			cout<<"the hero can't attack his friend or he can't fight in peace city!"<<endl;
			return USE_SKILL_FAILED_CAN_NOT_ATK_FRIEND;
		}
		
		//不能给敌方单位加血
		if (skill_flag == 1 && rc == 2)
		{
			cout<<"the hero can't cure his enemy!"<<endl;
			return USE_SKILL_FAILED_CAN_NOT_CURE_ENEMY;
		}
		obj_loc = obj_hero->getLocation();
		obj = obj_hero;
		return 0;
		// return USE_SKILL_FAILED_NOT_FIND_ATKED_HERO;
	} else {
		//指向性医疗技能不能作用于非角色对象
		if (skill_flag == 1)			//医疗技能不能医疗怪物
		{
			cout<<"the monsters are your enemy forever, so you can't cure them!"<<endl;
			return USE_SKILL_FAILED_CAN_NOT_CURE_MON;
		}
		//指向性攻击技能，只检查攻击人和攻击怪，如果连怪物都找不到，就判定攻击失败
		MonsterBase *obj_mon = mapNow->getMonsterObj(objId);
		if (obj_mon != NULL)
		{
			if (obj_mon->getLifeVal() <= 0 || !obj_mon->getLifeStation())
			{
				//怪物已经死亡
				cout<<"The hero attacked monster has been died!"<<endl;
				return USE_SKILL_FAILED_ATKED_MON_DIED;
			}
			if (obj_mon->getUnEnemySta())
			{
				//怪物处于无敌状态
				cout<<"The monster is invinc for attack"<<endl;
				return USE_SKILL_FAILED_ATKED_MON_INVINC;
			}
				
			obj_flag = 2;			//标记攻击对象为怪物
			obj = obj_mon;
			obj_loc = obj_mon->getLocation();
			return 0;
		}
		
		Wagon *wagon = NULL;
		map<string,Wagon*>::iterator it_wagon;
		it_wagon = wagonInstMap.find(objId);
		if (it_wagon != wagonInstMap.end())
		{
			wagon = it_wagon->second;
			if (wagon->getLifeVal() <= 0)
			{
				cout<<"attacked wagon has died!"<<endl;
				return USE_SKILL_FAILED_WAGON_DEAD;
			}
			//比较马车的主人是不是这个玩家
			Hero *wagonOwner = wagon->getOwner();
			if(wagonOwner == NULL)	//tory add 2013.1.10
			{
				return USE_SKILL_FAILED_ATK_SELF_WAGON;
			}
			if (owner != NULL && strcmp(wagonOwner->getIdentity(), owner->getIdentity()) == 0)
			{
				cout<<"use skill failed for can't attack self's wagon"<<endl;
				return USE_SKILL_FAILED_ATK_SELF_WAGON;
			}
			
			if (owner->gethero_PK_status() == PEACE_MODE)
			{
				//和平图模式下不能攻击马车
				cout<<"can't atk wagon in peace mode!"<<endl;
				return USE_SKILL_FAILED_PEACE_ATK_WAGON;
			}
			
			Map_Inform* wagonMap = wagon->getMap();
			char *wagonMapId = wagonMap->getIdentity();
			if (strcmp(wagonMapId, ownerMapId) != 0)
			{
				cout<<"use skill fail for attack wagon is not in the same map!"<<endl;
				return USE_SKILL_FAILED_ATKED_IN_DIFF_MAP;
			}
			
			obj_flag = 3;			//标记攻击对象为马车
			obj = wagon;
			obj_loc = wagon->getLocation();
			return 0;
		}
		//检查攻击对象是否为瓶子
		Bottle *bottInst = NULL;
		bottInst = mapNow->getBotInst(objId);
		if (bottInst != NULL)
		{
			if (bottInst->getLifeVal() <= 0)
			{
				cout<<"The atked bottle has already been broken!"<<endl;
				return USE_SKILL_FAILED_ATKED_BOTT_BROKEN;
			}
			obj_flag = 4;			//标记攻击对象为瓶子
			obj = bottInst;
			obj_loc = bottInst->getPiexPt();
			return 0;
		}
		cout<<"can't find the atked obj when use aimed skill!!!!"<<endl;
		return USE_SKILL_FAILED_NOT_FIND_ATKED_OBJ;
		
	}
}

int relationCheck(Hero *heroA, Hero* heroB, Map_Inform* map)
{
	int mapMode = heroA->gethero_PK_status();
	switch(mapMode)
	{
	case GUILD_WAR_MODE:	//帮战模式，不是同一帮的就是敌人
		if (!strcmp(heroA->getGuildName(), heroB->getGuildName()) && strlen(heroA->getGuildName()) != 0)
		{
			//相同帮的
			cout<<"The two hero in same guild!!!!!!!!"<<endl;
			return 1;
		} else {
			cout<<"The two hero not in same guild!!!!!!!!"<<endl;
			if (!strcmp(heroA->getTeamerId(), heroB->getTeamerId()) && strlen(heroA->getTeamerId()) != 0)
			{
				cout<<"The two hero in same team!!!!!!"<<endl;
				return 1;
			} 
			return 2;
		}
	case CAMP_WAR_MODE:		//阵营战模式
		if (heroA->getCamp() == heroB->getCamp() && heroA->getCamp() != -1)
		{
			//相同阵营
			cout<<"The two hero in same camp!!!!!!!!"<<endl;
			return 1;
		} else {
			if (!strcmp(heroA->getTeamerId(), heroB->getTeamerId()) && strlen(heroA->getTeamerId()) != 0)
			{
				cout<<"The two hero in same team!!!!!!"<<endl;
				return 1;
			} 
			cout<<"The two hero not in same camp!!!!!!!!"<<endl;
			return 2;
		}
	case PEACE_MODE:		//和平模式
	case 0:
		return 0;
	default:
		if (!strcmp(heroA->getTeamerId(), heroB->getTeamerId()) && strlen(heroA->getTeamerId()) != 0)
		{
			cout<<"The two hero in same team!!!!!!"<<endl;
			return 1;
		} else {
			cout<<"The two hero not in same team!!!!!!!!"<<endl;
			return 2;
		}
	}
}

int skill_owner_check(Hero *owner, HeroMemSkill_T* &p_memSkill, HeroSkill * &p_skill, char *skillId, int &remainCD)
{
	//技能使用者处于死亡状态
	if (owner->getLifeVal() == 0)
	{
		cout<<"The hero is dead so he is forbiden to use skills!"<<endl;
		return USE_SKILL_FAILED_ATK_DEAD;
	}
	//检查技能使用者状态，是否可以释放技能或攻击
	if (owner->skillBuffState & PLAY_ANIMATION_STATE)
	{
		//播放上一技能动画
		cout<<"The hero can't use this skill when last skill's animation is not finished!"<<endl;
		return USE_SKILL_FAILED_ATK_IN_ANMT;
	}
	if ((owner->skillBuffState & DEBUF_DIZZ_STATE) || (owner->skillBuffState & DEBUF_FORB_ATTK_STATE))
	{
		//眩晕或者点穴状态
		cout<<"The hero is in the forbiden_attack state when he wants to use skill!"<<endl;
		return USE_SKILL_FAILED_ATK_IN_DIZZ;
	}
	
	map<string, HeroSkill*>::iterator it_skill;
	it_skill = skillId_2_heroSkill.find(skillId);
	if (it_skill == skillId_2_heroSkill.end())
	{
		//无此技能
		cout<<"There is no this skill:"<<skillId<<" when hero use skill"<<endl;
		return USE_SKILL_FAILED_NO_THIS_SKILL;
	}
	p_skill = it_skill->second;
	if (p_skill->getType() < 100)
	{
		//被动技能，无法使用
		cout<<"The hero is try to use static skill, but it's no need to use! the skill type is "<<p_skill->getType()<<endl;
		return USE_SKILL_FAILED_STATIC_SKILL;
	}
	
	unsigned index = atoi(skillId + 1);
#if defined(PERFECTLY_CHECK)	//this normally wouldn't happen, just for perfectly check
	if (index >= HERO_SKILL_MAX_NUM)
	{
		cout<<"[System warning] the system should enlarge the val of HERO_SKILL_MAX_NUM for there more skills in conf and the skillId is "<<skillId<<endl;
		return USE_SKILL_FAILED_SKILL_CONF_ERROR;
	}
#endif	
	p_memSkill = &owner->memHero->skills[index];

#if defined(PERFECTLY_CHECK)	//this normally wouldn't happen, just for perfectly check
	if (strcmp(p_memSkill->skillId, skillId))
	{
		cout<<"owner's skills in memHero is error!!"<<endl;
		return USE_SKILL_FAILED_SKILL_CONF_ERROR;
	}
#endif

	if (index != 0 && p_memSkill->level == 0)
	{
		cout<<"The hero hasn't learn this skill when he want to use it!"<<endl;
		return USE_SKILL_FAILED_NOT_UPGRADE;
	}
	
	//CD时间检查(非普通攻击)
	if (index != 0 && p_memSkill->lastUsedTime + p_skill->getCdTime(p_memSkill->level) > MY_TV_SEC)
	{
		remainCD = p_memSkill->lastUsedTime + p_skill->getCdTime(p_memSkill->level) - MY_TV_SEC;
		cout<<"lastUsedTime is "<<p_memSkill->lastUsedTime<<" CD Time is "<<p_skill->getCdTime(p_memSkill->level)<<"now is "<<MY_TV_SEC<<endl;
		cout<<"The hero skill can't be used now for it is in CD time!"<<endl;
		return USE_SKILL_FAILED_IN_CD_TIME;
	}
	
	//是否有释放技能所需要的血或者魔法检查
	if (owner->getMagicVal() < p_skill->getNeedMagic(p_memSkill->level))
	{
		return USE_SKILL_FAILED_NO_ENOUGH_MP;
	}
	//耗血技能总是让他成功，即使血不够最后也给他留一点血
	//check ok
	return 0;
}