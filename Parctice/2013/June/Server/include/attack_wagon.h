/****************************************************************
 * Filename: hero_attack_wagon.cpp
 * 
 * Description: 马车被击
 *
 * Original Author : bison, 2012-9-10
 *
 ****************************************************************/
#include"wagon.h"

//攻击马车的通信
void attactWagonComm(char *buffer);

void attackWagon(char* attackerId, int attackerCurLife, int attackerCurMagic, char* skillId, char* wagonId);