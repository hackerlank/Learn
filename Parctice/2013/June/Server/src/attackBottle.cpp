/************************************************************
	文件名：attackBottle.cpp
	文件作用：定义九宫格辅助功能函数
	作者：chenzhen
	创建日期：2012.12.13
************************************************************/
#include"attackBottle.h"
#include"hero.h"
#include"wholeDefine.h"
#include"command_game_fight_manage.h"
extern int sock_fd; 
extern int g_msg_len;
extern Hero* pg_hero;
 
void attactBottleCom(char *buff)
{
#if 0
	char *bottleId,*skillId;								 
	Bottle *bottInst;
	Map_Inform *mapNow;	
	Hero *hero = pg_hero;				
	Point bottPt,heroPt;
	Skill *skill;	
	
	MSG_BEGIN(buff, g_msg_len);
	MSG_CHAR(bottleId);
	MSG_CHAR_END(skillId);
	
	mapNow = hero->getMap();
	if(mapNow == NULL)
	{
		return;
	}	
	
	bottInst = mapNow->getBotInst(bottleId);
	
	if(bottInst == NULL)
	{
		cout<<"the bottInst is NULL:"<<bottleId<<endl;
		return;
	}
	
	
	bottPt = bottInst->getPiexPt();
	
	heroPt = hero->getLocation();	
	
	map<string,Skill*> attack_skill_list;				//玩家角色的技能列表	
	map<string,Skill*>::iterator skill_iter;
	attack_skill_list = hero->getSkill_list();	
	skill_iter = attack_skill_list.find(skillId);
	if(skill_iter == attack_skill_list.end())
	{
		cout<<"chenzhen: hero does not has this skill to use when attack bottle"<<bottleId<<endl;
		return;
	}                   
	skill = skill_iter->second;							//玩家所使用的技能
		
	if (skill->gettype() != 1 || skill->geteffect() != 1)
	{
		/*管你是群攻还是医疗，只要不是主动技能都别用来打瓶罐*/
		cout<<"skill type can't attack wagon"<<endl;
		return;
	}
		
	/*判断玩家的真气，和技能的时间是否符合条件*/
	if(!isFightStatusOfHero(hero, skill))					
	{
		cout<<"chenzhen: magical or time is not enough to use this skill"<<endl;
		return;
	}

	/*判断距离是否够*/
	int deltaX = bottPt._x - heroPt._x;
	int deltaY = bottPt._y - heroPt._y;
	int distance = sqrt(deltaX * deltaX + deltaY * deltaY);
	int range = hero->getAtk_range();
	
	if (distance > range)
	{
		cout<<"chenzhen: distance is not enough "<<distance<<" hero attack range is "<<range<<endl; 
		return;			
	} 
	
	/*攻击者者扣蓝*/
	PropertyOfAttackerChange(hero, skill);	
	
	attackBottle(hero,skillId, bottInst);
#endif
}


/*攻击瓶罐函数*/
void attackBottle(Hero *attHero,char *skillId,Bottle *bottInst)
{
#if 0
	char *bottId,*attId,attMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	Map_Inform *map_now;
	int lifeVal,attPow;
	Point piexPt;
	Nbox* box;	
	
	
	if(attHero == NULL || bottInst == NULL)
	{
		cout<<"the attHero or the hited bottInst is NULL:"<<endl;
		return;
	}
	
	bottId = bottInst->getBottleId();
	attId = attHero->getIdentity();
	StyObj obj(bottId,BOTTLE_STYLE_TYPE);
	
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
		
	lifeVal = bottInst->getLifeVal();
	attPow = bottInst->getHurt();
	
	if(lifeVal <= attPow)
	{
		lifeVal = 0;
	}
	else
	{
		lifeVal -= attPow;
	}
	piexPt = attHero->getLocation();
	box->getStaInSrcVec(obj);	
	
		
	/*向周围人发瓶罐被攻击消息*/
	sprintf(attMsg, "2,%d,1,%s,%s,%d,%d,0,%s,%d,%d,0,%d,%d", ATTACK_RETURN_SELF, skillId,\
			attId,attHero->getLifeVal(), attHero->getMagicVal(), bottId, lifeVal,\
			attPow,piexPt._x, piexPt._y);
			
	box->sentBoxMsg(attMsg);
	bottInst->beAttack();
#endif
}

/*宠物攻击瓶罐函数*/
void petAttackBottle(char* ownerId,char *identity,Point piexPt,char *skillId,Bottle *bottInst)
{
	char *bottId,attMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	Map_Inform *map_now;
	int lifeVal,attPow;
	Nbox* box;	
	
	
	if(bottInst == NULL)
	{
		cout<<"the hited bottInst is NULL:"<<endl;
		return;
	}
	
	bottId = bottInst->getBottleId();
	StyObj obj(bottId,BOTTLE_STYLE_TYPE);
	
	map_now = bottInst->getMap();	
	if(map_now == NULL)
	{
		return;
	}
	box = map_now->getBox();
	if(box == NULL)
	{
		return;
	}
		
	lifeVal = bottInst->getLifeVal();
	attPow = bottInst->getHurt();
	
	if(lifeVal <= attPow)
	{
		lifeVal = 0;
	}
	else
	{
		lifeVal -= attPow;
	}
	
	box->getStaInSrcVec(obj);	
	
		
	snprintf(attMsg,sizeof(attMsg),"%d,%d,%d,%s,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,%d,%d,%d,%d",26,2,1,skillId,1,identity,\
	100,100,100,100,0,0,0,1,bottId,lifeVal,bottInst->getLifeUpperVal(),100,100,attPow,0);

	/*向周围人发瓶罐被攻击消息*/
	// sprintf(attMsg, "2,%d,1,%s,%s,%d,%d,0,%s,%d,%d,0,%d,%d", ATTACK_RETURN_SELF, skillId,identity,100, 100, bottId, lifeVal,attPow,piexPt._x, piexPt._y);
			
	box->sentBoxMsg(attMsg);
	bottInst->beAttack(ownerId);
}