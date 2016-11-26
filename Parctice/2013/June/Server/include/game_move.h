/**********************************************
*	author	：	Tory
*	date	:	2012.3.26
*	文件名称：	game_move.h
*	文件作用：	角色移动消息的广播和心跳更新函数的定义
*********************************************/
#ifndef GAME_MOVE
#define GAME_MOVE
#include "pet.h"

/*移动命令函数*/
void move_get_road(char *buffer);        //处理移动命令

/*人物心跳函数*/
void timePoll(char* buffer);			//心跳处理函数

/*移动辅助函数*/
void objMoveAsist(int objTpe,char *objId,Point &newPiexPt,char *moveMsg);

/*宠物移动*/
void petMoveAsist(char *objId,Point &newPiexPt,char *moveMsg);

/*马车移动*/
void wagonMoveAsist(char *objId,Point &newPiexPt,char *moveMsg);


#endif