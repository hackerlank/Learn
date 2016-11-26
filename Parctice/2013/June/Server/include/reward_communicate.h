#ifndef REWARD_COMMUNIICATE_H
#define REWARD_COMMUNIICATE_H

#include <iostream>
#include "hero.h" 
#include "reward_operator.h"


void receiveWelfare(char *buffer);
void reward_return(char *buffer);
void rechargeRewardReturn(char *buffer);
void receiveRechargeReward(char *buffer);
void onlineRewardRefresh(char *buffer);
void onlineRewardReceive(char *buffer);
void onlineRewardGoldRefresh(char *buffer);
void onlineRewardReturn(char *buffer);
void levelRewardReturn(char *buffer);
void levelRewardReceive(char *buffer);
void levelRewardExist(char *buffer);
void receiveSignReward(char *buffer);

#endif