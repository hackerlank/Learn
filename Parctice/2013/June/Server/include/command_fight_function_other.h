#ifndef COMMAND_FIGHT_FUNCTION_OTHER
#define COMMAND_FIGHT_FUNCTION_OTHER
#include"hero.h"
#include"skill.h"
#include"map_inform.h"
int fightMonster(Hero *attack,MonsterBase *monster_now,Skill *skill);
int fightHero(Hero *attack,Hero *hited,Skill *skill);

/*进入场景地图函数*/
//add chenzhen 6.14
void enter_scenes(Hero *myHero, Map_Inform *map_now);
#endif
