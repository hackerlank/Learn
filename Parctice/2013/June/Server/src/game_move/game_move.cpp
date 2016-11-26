/************************************************************
	文件名：game_move.cpp
	文件作用：移动命令处理
	作者：chenzhen
	创建日期：2012.06.11
************************************************************/
#include"command_other_function_all_over.h"
#include"command_return_define_data.h"
#include"command_game_fight_manage.h"
#include"data_structure_struct.h"
#include"map_inform.h"
#include"hero_help.h"
#include"game_move.h"
#include"boxAsist.h"
#include<sys/time.h>
#include<unistd.h>
#include"wagon.h"

extern map<string, Hero*> heroId_to_pHero;
extern map<string,Pet*>id_to_activePet;
extern map<string,Wagon*> wagonInstMap;						//马车实例

void move_get_road(char *buffer)
{
	//跳图中
	if(!pg_hero->getWalkingFlg())
	{
		cout<<"the owner is jump map when the wagon/pet want to move"<<endl;
		return;
	}
	Map_Inform *heroMap = pg_hero->getMap();
	if (heroMap == NULL)
	{
		return;
	}
	Nbox *box = heroMap->getBox();
	if (box == NULL)
	{
		return;
	}
	
	int objType;
	char *objId;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(objType);
	MSG_CHAR(objId);
	
	Wagon * wagon = NULL;
	Pet *movePet = NULL;
	char moveMsg[5120] = {0};	
	char temp[4000] = {0};
	int realPtNum = 0;
	int ptNum;
	Point startPt, endPt, speedPt, curPt;
	
	if (objType == WAGON_STYLE_TYPE)
	{
		map<string, Wagon*>::iterator wagon_it;
		wagon_it = wagonInstMap.find(objId);
		if (wagon_it == wagonInstMap.end())
		{
			cout<<"the move wagon can not find the inst:"<<objId<<endl;
			return;	
		}
			
		wagon = wagon_it->second;
		Hero *owner = wagon->getOwner();
		if (owner == NULL)
		{
			cout<<"the wagon can't find its owner when it want to move!"<<endl;
			return;
		}
		if (strcmp(owner->getIdentity(), pg_hero->getIdentity()) != 0)
		{
			cout<<"the wagon's owner is not me when it want to move!"<<endl;
			return;
		}
		
		// cout<<"wagon wagon wagon waogon  move move move move !"<<endl;
		MSG_INT(ptNum);
		if (ptNum < 1)
		{
			return;
		}
		
		MSG_INT(curPt._x);
		MSG_INT(curPt._y);
		
		if (!heroMap->judgePiex(curPt))
		{
			return;
		}
		if (sqrt((curPt._x - wagon->currPt._x) * (curPt._x - wagon->currPt._x)
			+ (curPt._y - wagon->currPt._y) * (curPt._y - wagon->currPt._y)) > 200)
		{
			cout<<"888888888wagon888888888888"<<endl;
			cout<<"the distance is "<<sqrt((curPt._x - wagon->currPt._x) * (curPt._x - wagon->currPt._x)
			+ (curPt._y - wagon->currPt._y) * (curPt._y - wagon->currPt._y))<<endl;
			printf("client curPt is (%d,%d) server curPt is (%d,%d)", curPt._x, curPt._y, wagon->currPt._x, wagon->currPt._y);
			cout<<"888888888wagon888888888888"<<endl;
			// return;
			
			curPt = wagon->currPt;
			ptNum = 1;
		}
		
		
		if (ptNum > 20)
		{
			Point heroPt = owner->getLocation();
			realPtNum = 1;
			sprintf(temp, "%d,%d", heroPt._x, heroPt._y);
			wagon->currPt = heroPt;
			wagon->endPt = heroPt;
			
		} else {
			realPtNum  = 1;
			sprintf(temp, "%d,%d", curPt._x, curPt._y);
			wagon->routeClear();
			wagon->currPt = curPt;
			wagon->endPt = curPt;
			startPt = curPt;
			
			for (int i = 0; i < ptNum - 1; i++)
			{
				MSG_INT(endPt._x);
				MSG_INT(endPt._y);
				if (!heroMap->judgePiex(endPt))
				{
					break;
				}
				if (endPt == startPt)
				{
					break;
				}
				realPtNum++;
				startPt = endPt;
				wagon->pushOneRoutePt(endPt._x, endPt._y);
				sprintf(temp + strlen(temp), ",%d,%d", endPt._x, endPt._y);
			}
		}
		sprintf(moveMsg, "2,1,%s,%d,%s,%d", objId, realPtNum, temp, wagon->speed);
		StyObj obj(objId, WAGON_STYLE_TYPE);	
		// cout<<"wagon move Msg is "<<moveMsg<<endl;
		if(heroMap->updateID(obj,curPt))
		{
			box->wagonMove(wagon, moveMsg, true, NULL);			
			wagon->setLocation(curPt, 1);	
			return ;
		}
		else
		{
			return ;
		}
		
	}
	else if (objType == PET_STYLE_TYPE)
	{
		map<string,Pet*>::iterator pet_it;
		pet_it = id_to_activePet.find(objId);
		if (pet_it == id_to_activePet.end())
		{
			cout<<"the move pet can not find the inst:"<<objId<<endl;
			return;
		}
		movePet = pet_it->second;
		
		if (movePet->getMasterId() == NULL || strcmp(movePet->getMasterId(), pg_hero->getIdentity()) != 0)
		{
			cout<<"the pet isn't mine when it want to move!!"<<endl;
			return;
		}
		
		
		MSG_INT(ptNum);
		if (ptNum < 1)
		{
			return;
		}
		MSG_INT(curPt._x);
		MSG_INT(curPt._y);
		
		if (!heroMap->judgePiex(curPt))
		{
			return;
		}
		Point petPt = movePet->getPiexPt();
		if (sqrt((curPt._x - petPt._x) * (curPt._x - petPt._x)
			+ (curPt._y - petPt._y) * (curPt._y - petPt._y)) > 200)
		{
			cout<<"888888888--pet--888888888888"<<endl;
			cout<<"the distance is "<<sqrt((curPt._x - petPt._x) * (curPt._x - petPt._x)
			+ (curPt._y - petPt._y) * (curPt._y - petPt._y))<<endl;
			printf("client curPt is (%d,%d) server curPt is (%d,%d)", curPt._x, curPt._y, petPt._x, petPt._y);
			cout<<"888888888--pet--888888888888"<<endl;
			// return;
			curPt = petPt;
			ptNum = 1;
		}
		
		if (ptNum > 20)
		{
			Point heroPt = pg_hero->getLocation();
			realPtNum = 1;
			sprintf(temp, "%d,%d", heroPt._x, heroPt._y);
			movePet->currPt = heroPt;
			movePet->endPt = heroPt;
			
		} else {
			realPtNum  = 1;
			sprintf(temp, "%d,%d", curPt._x, curPt._y);
			movePet->routeClear();
			movePet->currPt = curPt;
			movePet->endPt = curPt;
			startPt = curPt;
			
			for (int i = 0; i < ptNum - 1; i++)
			{
				MSG_INT(endPt._x);
				MSG_INT(endPt._y);
				if (!heroMap->judgePiex(endPt))
				{
					break;
				}
				if (endPt == startPt)
				{
					break;
				}
				realPtNum++;
				startPt = endPt;
				movePet->pushOneRoutePt(endPt._x, endPt._y);
				sprintf(temp + strlen(temp), ",%d,%d", endPt._x, endPt._y);
			}
		}
		
		int petSpeed = movePet->speed;
		int ownerSpeed = pg_hero->getSpeed();
		if (petSpeed < ownerSpeed)
		{
			petSpeed = ownerSpeed;
		}
		
		sprintf(moveMsg, "2,1,%s,%d,%s,%d", objId, realPtNum, temp, petSpeed);
		StyObj obj(objId, PET_STYLE_TYPE);	
		
		if(heroMap->updateID(obj,curPt))
		{
			box->petMove(movePet, moveMsg, true, NULL);			
			movePet->setNowPix(curPt, 1);	
			return ;
		}
		else
		{
			return ;
		}
	}
	
}






