#include<map>
#include<string>
#include<iostream>
#include"hero.h"
#include"skill.h"
#include"hero_help.h"
#include"user_role_manage_skill.h"
using namespace std;
extern map<int,int> exp_upgrade_list;
/*
	技能升级所需要的经验值
*/
unsigned int  skillneedexp(int level)
{
	unsigned int exp = 0;
	map<int,int>::iterator iter;
	iter = exp_upgrade_list.find(level);
	if(iter == exp_upgrade_list.end())
	{
		return 0;
	}
	exp = iter->second;
	exp = exp/20;
	return exp;
}
/*
	技能升级所需要的经验值
*/
int  skillneedmoney(int hero_grade,int skill_grade,int control_grade)
{
	int money = 0;
	// if(hero_grade<=20)
	if(control_grade<=20)
	{
		// money = 50 + (skill_grade - 1)*150;
		money = 50 + (control_grade - 5)*150;
	}else{
		money = control_grade*250;
	}
	return money;
}