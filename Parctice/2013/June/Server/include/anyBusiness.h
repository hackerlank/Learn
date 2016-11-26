#ifndef COMMODITY_H
#define COMMODITY_H
#include<string>
#include<iostream>
#include "bag_operator.h"
using namespace::std;
void shopBusiness(char *buff);
void draw(char *buff);
//onLineStallBusiness
void createStall(char *buff);
void stallBusiness(char *buff);
void changeStallCommodityPrice(char *buff);
void deleteStallCommodity(char *buff);
void deleteStall(char *buff);
void changeName(char *buff);
void addCommodity(char *buff);
void checkStall(char *buff);

//npcBusiness
void npcBusinessBuy(char *buff);
void npcBusinessSell(char *buffer);
void repair(char *buff);
//playerBusiness
void askForBusiness(char *buff);
void feedbackForAsk(char *buff);
void addGoods(char *buff);
void deleteGoods(char *buff);
void businessCancel(char *buff);
void bussinessCancelDeal(Hero *hero);
void businessLock(char *buff);
void verifyThisBusiness(char *buff);

int returnFreeGrid(Hero *hero);

#endif