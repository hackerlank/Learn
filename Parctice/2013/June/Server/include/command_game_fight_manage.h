/*
		文件类型：头文件
		文件名称：command_game_fight_manage.h
		文件作用：处理战斗部分命令的函数的实现
*/

#ifndef COMMAND_GAME_FIGHT_MANAGE_H
#define COMMAND_GAME_FIGHT_MANAGE_H
#include<vector>
#include"data_structure_struct.h"
#include"hero.h"
#include"skill.h"
#include"map_inform.h"
#include"monsterBase.h"
/*处理单对单客户端发来的命令解析并处理*/
void flightAction(char *buffer);     					 	 		 //处理一般战斗命令
/*判断攻击者自身状态以及攻击者使用的技能是否符合攻击要求*/
bool isFightStatusOfHero(Hero *hero,Skill *skill);
/*通过heroId查找Hero实例*/
Hero* findbyheroid(char *heroid);
/*通过skillId查找skill实例*/
Skill* findbyskillid(Hero *hero,char *skillid);
/*通过monsterId查找monster实例*/
MonsterBase* findbymonsterid(Map_Inform *mapinform,char *monsterid);
/*判断玩家是否可以战斗或者移动，或者无敌：type=1:战斗；type=2：移动；type=3：无敌；*/
bool isHeroFightMoveInvincible(Hero *hero,int type);	
/*判断受击者是玩家时的状态以及攻击者与受击者之间的距离判断是否符合战斗要求*/
bool isFightStatusOfHitHero(Hero *hero,Point point1,Hero *hiter,int range);
/*判断受击者是怪物时的状态以及攻击者与受击者之间的距离判断是否符合战斗要求*/
bool isFightStatusOfHitMonster(Hero *hero,Point point1,MonsterBase *hiter,int range);
/*计算受击者是玩家时，受击者的扣血值*/
int redloseOfHero(Hero *hero,Hero *hiter,Skill *skill);
/*计算受击者是玩家时，受击者的扣血值*/
int redloseOfMonster(Hero *hero,MonsterBase *hiter,Skill *skill);
/*受击者是玩家时，获取攻击者，受击者血值扣除的基本处理*/
int redloseOfHeroManage(Hero *attack,Hero *hited,Skill *skill);
/*受击者是怪物时，获取攻击者，受击者血值扣除的基本处理*/
int redloseOfMonsterManage(Hero *attack,MonsterBase *hiter,Skill *skill);
/*判断受击者是否出现闪避,若不出现闪避，返回命中伤害率*/
double  dodgeOfHiterMange(int dodge,int hit);
/*判断受击者是否出现暴击，返回暴击率*/
double critOfHeroMange(int crit,int tenacity);
/*战斗结束后，攻击者自身属性的改变*/
int PropertyOfAttackerChange(Hero *hero,Skill *skill);
/*战斗结束后，受击者为玩家时自身属性的改变*/
int PropertyOfHiterHeroChange(Hero *hero,int redlose);
/*战斗结束后，受击者为怪物时怪物自身属性的改变*/
int PropertyOfHiterMonsterChange(Hero *attack,MonsterBase *hited,int redlose);
/*战斗结束后，将受击者为玩家的攻击成功的消息发送给客户端*/
void SendMsg_AttackHero(Hero *attack,Hero *hited,Skill *skill,int redlose);
/*战斗结束后，将受击者为怪物的攻击成功的消息发送给客户端*/
void SendMsg_AttackMonster(Hero *attack,MonsterBase *hited,Skill *skill,int redlose);
/*九宫格消息群发的方法实现*/
void sendmsg_manage(Hero *attack,string msg);
/*客户端发来的群攻命令信息解析并处理*/
void qungongskill(char *buffer);
/*玩家施放群体医疗的方法实现,如果成功，则返回发送给客户端的消息*/
string herotreatAll(Hero *hero,Skill *skill,vector<string> hits);
/*玩家施放群体攻击的方法实现，如果成功，则返回发送给客户端的消息*/
string heroattackAll(Hero *hero,char* hiterid,Skill *skill,vector<string> hits);
/*玩家施放群体攻击的技能，受击者的扣血处理方法实现*/
string redloseOfattackAll(Hero *hero,Point pt_hit,int range,Skill *skill,vector<string> hits);
/*玩家施放buff技能，解析客户端发来的消息*/
void  attackusebuff(char *buffer);
/*玩家处理buff技能的方法实现*/
string buffmanage(Hero *hero,Skill *skill);
/*特效的持续时间到时的处理*/
void debuffstop(char *buffer);
/*玩家战斗前属性变化，type=1，攻击者；type=2，受击者*/
void HeroPropertybeforeFight(Hero *hero,int type);
/*计算出伤害值后，type=1,玩家吸血；type=2:玩家反弹伤害；type=3：玩家是否释放血包技能*/				
int HeroPropertybackFight(Hero *hero,int type,int redlose);
/*因战斗，攻击者与被攻击者自身的属性改变:type=1,受击者是玩家；type=2,受击者是怪物*/
int ManagePropertyAttackerAndHiter(Hero *hero,int type,Hero *hiter,MonsterBase *hited,int redlose);
/*玩家持续掉血的计时函数*/
void heroThink(struct ev_loop *loop,ev_timer *think,int revents); 
/*玩家播放战斗动画时，不能移动*/
void nomove(Hero *hero,Skill *skill);

/*对人物技能请求*/
void acceptSkillMsg(char *buffer);
#endif