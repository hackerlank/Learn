/********************************************************************

    created	:	2012/2/28  9:24
	
	文件名	：	command_time_poll.cpp

    author	:   Tory	

    purpose	:  接收客户端“心跳”发送的数据，按时更新游戏玩家当前的状态
	
*********************************************************************/
#include"command_other_function_all_over.h"
#include"command_game_fight_manage.h"
#include"command_user_role_manage.h"
#include"command_return_define_data.h"
#include"map_inform.h"
#include"game_move.h"
#include"boxAsist.h"
#include "sitControl.h"
using namespace std;
extern int sock_fd;
void timePoll(char* buffer)
{
	//jolly add 摆摊中 不允许移动
	if (pg_hero->getHeroState()==5)
	{
		msg_error(g_out_buf,75);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	
	if(pg_hero->getStillFlg())
	{
		cout<<"dingshen do not move:"<<pg_hero->getIdentity()<<endl;
		return;
	}
	
	cancelSit(pg_hero);
	
	pg_hero->stopCollectTimer(1);		//因移动打断采集
	pg_hero->stopMove();
	Map_Inform *map_in;
	char msgResult[4000] = {0};
	/*跳图当中不许动*/
	if(!pg_hero->getWalkingFlg())
	{
		sprintf(msgResult, "40,1,1");
		send_msg(sock_fd, msgResult);
		cout<<"222222222222222222222222222"<<endl;
		return;
	}
	
	if (pg_hero->getLifeStation() == DEAD)
	{
		
		sprintf(msgResult, "40,1,2");
		send_msg(sock_fd, msgResult);
		return;
	}
	
	//通过id找到玩家实例	
	map_in = pg_hero->getMap();
	
	if(map_in == NULL)
	{
		cout<<"333333333333333333333"<<endl;
		
		sprintf(msgResult, "40,1,3");
		send_msg(sock_fd, msgResult);
		return;
	}
	Nbox *box;
	box = map_in->getBox();
	
	if(box == NULL)
	{
		sprintf(msgResult, "40,1,4");
		send_msg(sock_fd, msgResult);
		cout<<"444444444444444444444444"<<endl;
		return;
	}
	
	if((pg_hero->skillBuffState & DEBUF_FORB_MOVE_STATE)
		|| (pg_hero->skillBuffState & DEBUF_DIZZ_STATE)
		|| ((pg_hero->skillBuffState & PLAY_ANIMATION_STATE)
		&& !(pg_hero->skillBuffState & BUFF_BLADE_STORM_STATE)))
	{
		//玩家有被眩晕或者被定身的效果,或者在播放攻击动画
		//cout<<"*******************hero can't move game_move 115***********************"<<endl;
		cout<<"55555555555555555555555555555"<<endl;
		sprintf(msgResult, "40,1,5,%d", pg_hero->skillBuffState);
		send_msg(sock_fd, msgResult);
		return;
	}	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR(char *heroId);
	if (strcmp(pg_hero->getIdentity(),heroId)!=0)
	{
		return;
	}
	int ptNum;
	MSG_INT(ptNum);
	if (ptNum == 1)
	{
		// cout<<"One Point One PointOne Point One PointOne Point One PointOne Point One PointOne Point One Point"<<endl;
	}
	if (ptNum < 1)
	{
		cout<<"66666666666666666666"<<endl;
		sprintf(msgResult, "40,1,6");
		send_msg(sock_fd, msgResult);
		return;
	} if (ptNum > 500)
	{
		cout<<"10101010101001010101010"<<endl;
		sprintf(msgResult, "40,1,10");
		send_msg(sock_fd, msgResult);
		return;
	}
	
	Point curPt;
	MSG_INT(curPt._x);
	MSG_INT(curPt._y);
	
	Point heroPt = pg_hero->getLocation();
	if (sqrt((curPt._x - heroPt._x) * (curPt._x - heroPt._x)
		+ (curPt._y - heroPt._y) * (curPt._y - heroPt._y)) > 200)
	{
		cout<<"8888888888hero88888888888"<<endl;
		cout<<"the distance is "<<sqrt((curPt._x - heroPt._x) * (curPt._x - heroPt._x)
		+ (curPt._y - heroPt._y) * (curPt._y - heroPt._y))<<endl;
		printf("client curPt is (%d,%d) server curPt is (%d,%d)", curPt._x, curPt._y, heroPt._x, heroPt._y);
		cout<<"8888888888hero888888888"<<endl;
		// return;
		curPt = heroPt;
		ptNum = 1;
		
		sprintf(msgResult, "40,1,7,nomal,client curPt is far away 200");
		send_msg(sock_fd, msgResult);
		
	}
	if (!map_in->judgePiex(curPt))
	{
		cout<<"client curPt is not in the map"<<endl;
		sprintf(msgResult, "40,1,8,curPt not in this map");
		// send_msg(sock_fd, msgResult);
		// return;
		curPt = heroPt;
		ptNum = 1;
		
	}
	
	pg_hero->keyPath.clear();
	pg_hero->currPt = pg_hero->endPt = curPt;
	char moveMsg[MONSTER_MSG_LENGTH + 1] = {0};	
	char temp[4000] = {0};
	int realPtNum = 1;
	sprintf(temp, "%d,%d", curPt._x, curPt._y);
	pg_hero->currPt = curPt;
	pg_hero->endPt = curPt;
	Point startPt, endPt;
	startPt = curPt;
	for (int i = 0; i < ptNum - 1; i++)
	{
		MSG_INT(endPt._x);
		MSG_INT(endPt._y);
		if (!map_in->judgePiex(endPt))
		{
			break;
		}
		if (endPt == startPt)
		{
			cout<<"99999999999999999999999"<<endl;
			
			sprintf(msgResult, "40,1,9,two same point");
			send_msg(sock_fd, msgResult);
			break;
		}
		realPtNum++;
		
		startPt = endPt;
		pg_hero->keyPath.push_back(endPt);
		sprintf(temp + strlen(temp), ",%d,%d", endPt._x, endPt._y);
	}
	
	sprintf(moveMsg, "2,1,%s,%d,%s,%d", heroId, realPtNum, temp, pg_hero->getSpeed());
	
	// sprintf(msgResult, "40,1,10,%s", moveMsg);
		// send_msg(sock_fd, msgResult);
	
	if (realPtNum == 1)
	{
		// cout<<"client moveMsg is one point ,want stop: "<<moveMsg<<endl;
	}
	StyObj obj(heroId,HERO_STYLE_TYPE);	
	
	if(map_in->updateID(obj,curPt))
	{
		box->heroPollTme(pg_hero,moveMsg, true);			
		pg_hero->setLocation(curPt, 1);	
		
		// sprintf(msgResult, "40,1,11, OK!");
		// send_msg(sock_fd, msgResult);
		return ;
	} 

}

void beginRideComm(char* buffer)
{
	
}