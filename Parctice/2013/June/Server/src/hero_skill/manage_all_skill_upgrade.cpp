/*      
函数：void skillupgrade(char *buffer)	      
作用：技能升级
参数：buffer：技能升级命令
返回值：void
完成人：Evan
完成时间：2012.6.15
*/
#include<map>
#include<string>
#include<iostream>
#include"hero.h"
#include"skill.h"
#include"user_role_manage_skill.h"
extern map<string, Hero*> heroId_to_pHero;
using namespace std;

#include "wholeDefine.h"
extern Hero *pg_hero;
extern int g_msg_len;

void skillupgrade(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_CHAR(char *heroid)//目标玩家Id
	MSG_CHAR_END(char *skillid)////技能Id

	Hero *hero = pg_hero;
	
	Skill *skill;
	map<string,Skill*> skill_list;
	map<string,Skill*>::iterator skill_iter;
	skill_list = hero->getSkill_list();
	skill_iter = skill_list.find(skillid);
	if(skill_iter == skill_list.end())
	{cout<<"the hero has not this skill!"<<endl;
		return ;
	}
	skill = skill_iter->second;
	cout<<"the hero grade:"<<hero->getLevel()<<endl;
	cout<< "the skill grade :"<<skill->getskill_grade()<<endl;
	if((skill->getskill_grade()+1)>20)
	{
		return ;
	}
	int type = skill->gettype();
	switch(type)
	{
		case 1: 
				zhudongupgrade(hero,skill);
				break;
		case 2:	
				beidongupgrade(hero,skill);
				break;
		case 4:	
				buffupgrade(hero,skill);
				break;
		case 5:	
				yiliaoupgrade(hero,skill);
				break;
	}
	

}