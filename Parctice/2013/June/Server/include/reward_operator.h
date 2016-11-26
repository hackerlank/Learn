#ifndef REWARD_OPERATOR_H
#define REWARD_OPERATOR_H

#include "hero.h"

bool receive_levelReward(Hero *hero,int flag);
void receive_offLine_reward(Hero *hero);
void receive_sign_reward(Hero *hero);
void receive_chief_reward(Hero *hero);
void receive_level_reward(Hero *hero);
void receive_VIP_reward(Hero *hero);
long AccordingToIndexGetRecharge(int index);

#endif