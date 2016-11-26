/*      
函数：void yiliaoupgrade(Hero *hero,Skill *skill)     
作用：buff技能升级
返回值：void
完成人：Evan
完成时间：2012.6.15
*/
#include<map>
#include<string>
#include<iostream>
#include"hero.h"
#include"skill.h"
#include"skill_struct.h"
#include"user_role_manage_skill.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
#include "money_operator.h"
using namespace std;
void yiliaoupgrade(Hero *hero,Skill *skill)
{
	string msg = "3";
	msg = msg + intTostring(HERO_SKILL_UPGRADE);
	int num_value;
	map<string,Skill*> skill_list;
	skill_list = hero->getSkill_list();
	int skill_grade = skill->getskill_grade();
	skill_grade = skill_grade + 1;
	int control_grade = skill->getcontrol_grade();	
	if(skill_grade == 2)
	{
		control_grade += 2;
	}
	int useup_money = skill->getuseup_money();
	unsigned int useup_exp = skill->getuseup_exp();
	int level =hero->getLevel();
	int money = hero->getMoney()->money_getBoundGameMoney();
	unsigned int expNow = hero->getExpNow();	
	if(level<(control_grade+1))
	{
		return;
	}
	if(money < useup_money)
	{
		num_value = 3;
		msg = msg + intTostring(num_value);
		send_msg(hero->getFd(),const_cast<char*>(msg.c_str()));
		return ;
	}	
	if(expNow < useup_exp)
	{
		num_value = 2;
		msg = msg + intTostring(num_value);
		send_msg(hero->getFd(),const_cast<char*>(msg.c_str()));
		return ;
	}
	useBoundGameMoney(hero,useup_money);		//从背包内删除游戏币
	hero->setExpNow(expNow-useup_exp, 1);	
	
	control_grade = control_grade+2;
	
	if(control_grade == 4)
	{
		useup_money = skillneedmoney(level,skill_grade,control_grade -1);
	}
	else
	{
		useup_money = skillneedmoney(level,skill_grade,control_grade);
	}
	// useup_money = skillneedmoney(level,skill_grade,control_grade);
	useup_exp = skillneedexp(control_grade);
	skill->setcontrol_grade(control_grade);
	skill->setuseup_money(useup_money);
	skill->setuseup_exp(useup_exp);

	string id = skill->getid();           		//技能Id
	int genuine = skill->getgenuine();
	int factor = skill->getfactor();
	int factor_growup = skill->getfactor_growup();
	int value1 = skill->getvalue1();
	
	genuine += value1;
	
	// genuine = genuine * skill_grade;
	factor = factor + factor_growup;
	skill->setgenuine(genuine);
	skill->setfactor(factor);
	skill->setskill_grade(skill_grade);
	skill_list[id] = skill;
	
	hero->setSkill_list(skill_list);
	num_value = 1;			//技能升级成功
	msg = msg + intTostring(num_value);
	msg = msg + "," + id;
	msg = msg + intTostring(skill_grade);
	msg = msg + intTostring(control_grade);
	msg = msg + intTostring(genuine);
	msg = msg + intTostring(useup_money);
	msg = msg + intTostring(useup_exp);//evan add 2012.10.13
	send_msg(hero->getFd(),const_cast<char*>(msg.c_str()));
	cout<<"the beidong skill upgrade:"<<msg<<endl;
	skill->newmem();
	MemSkill *memskill = skill->getmemskill();
	MemHero *memhero = hero->memHero;
	int num = memhero->skilllists.size;
	for(int i=0;i<num;i++)
	{
		
		string id2 = memhero->skilllists.skills[i].id;
		cout<<"have id:"<<id2<<endl;
		if(id==id2)
		{
			memcpy(memhero->skilllists.skills+i , memskill, sizeof(MemSkill));
			break;
		}
	}
	cout<<"_____________________________________________________________"<<endl;
}
