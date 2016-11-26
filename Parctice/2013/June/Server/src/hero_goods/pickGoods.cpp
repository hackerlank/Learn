#include<iostream>
#include<string>
#include"command_other_function_all_over.h"
#include"command_return_define_data.h"
#include"dropgoods.h"
#include"libev.h"
#include"nbox.h"
#include<stdlib.h>
#include"map_inform.h"
#include"bag_operator.h"
#include"team.h" 
#include"money_operator.h"
#include"boxAsist.h"
#include"hero_fight.h"
#include "guild_war_asist.h"
#include "rob_flag_war_logic.h"
#include"team.h"
#include"teamManager.h"

extern GuildWarAsist *guildWarManage;			//帮派战管理
extern struct ev_loop *loops;
extern map<string,Pick*> goods_to_hero; 
extern map<string,Map_Inform*> mapId_connect_map;
extern list<ev_timer*> goods_timer;
extern list<ev_timer*> pick_timer;
extern list<string> time_flag;
extern list<string> three_flag;
extern int sock_fd;
extern map<int, Role*> fd_to_pRole;
extern map<string,TakeGoods*> takeGoodsMap;
extern char g_out_buf[20480];

extern char server_name[10];

using namespace std;
#include "wholeDefine.h"

void pickgoods(char *buffer)
{
	MSG_BEGIN(buffer, g_msg_len)
	MSG_CHAR(char *identity)
	MSG_CHAR(char* flag)
	MSG_INT(int pt_x)
	MSG_INT(int pt_y)
	MSG_CHAR_END(char *goodsid);

	int bound;
	char* killheroid;
	
	int ptx=pt_x;
	int pty=pt_y;
	char pt_flag[100]={'\0'};
	sprintf(pt_flag,",%d,%d",pt_x,pt_y);
	char msg[150]={'\0'};
	memset(msg,'\0',150);
	sprintf(msg,",%s%s",flag,pt_flag);
	Map_Inform *map_now;
	StyObj obj(flag,PICK_STYLE_TYPE);
	Pick *pick;
	
	Hero *hero=pg_hero;
	
	map_now = hero->getMap();	
	
	if(map_now == NULL)
	{
		cout<<"the map is NULL:"<<endl;
		return;
	}
	
	pick = map_now->getDropPickInst(flag);
	// if(pick == NULL)
	// {
		// cout<<"the pickId is not find the inst:"<<flag<<endl;
		// snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s",9,PICK_RETURN,SUCCESS,msg);
		// send_error_nbox(hero,g_out_buf);
		// Map_Inform *map_now=hero->getMap();
		// map_now->deleteID(obj);
		// return;
	// }
		
	
	// Equipment* pickEquip;
	// pickEquip = getEquipInst(flag);
	// if (pickEquip == NULL)
	// {
		// snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s",9,PICK_RETURN,SUCCESS,msg);
		// send_error_nbox(hero,g_out_buf);
		// Map_Inform *map_now=hero->getMap();
		// map_now->deleteID(obj);
		// cout<<"jolly:no goods flag in pickgoods 67"<<endl;
	// }	
	
	/*拾取红名装备*/
	// else if(pickEquip != NULL)
	// {
		// if(hero->pickDropEquipment(pickEquip))
		// {
			// reaseEquip(flag);
			// pickEquip->disperMsg();
		// }
		// return;
	// }
	
	if (pick == NULL)
	{
		Equipment* pickEquip;
		pickEquip = getEquipInst(flag);
		if (pickEquip == NULL)
		{
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s",9,PICK_RETURN,SUCCESS,msg);
			send_error_nbox(hero,g_out_buf);
			Map_Inform *map_now=hero->getMap();
			map_now->deleteID(obj);
			cout<<"jolly:no goods flag in pickgoods 67"<<endl;
		}	
		/*拾取红名装备*/
		else if(pickEquip != NULL)
		{
			if(hero->pickDropEquipment(pickEquip))
			{
				reaseEquip(flag);
				// pickEquip->disperMsg();
			}
		}	
	}	
	else
	{	
		killheroid=pick->getKillHeroId();
		int num=pick->getNum();
		map<string,string> pt_goodsid=pick->getDropGoods();
		map<string,string>::iterator pt_it;
		pt_it=pt_goodsid.find(pt_flag);
		if (pt_it==pt_goodsid.end())
		{
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s",9,PICK_RETURN,SUCCESS,msg);
			send_error_nbox(hero,g_out_buf);
			Map_Inform *map_now=hero->getMap();
			map_now->deleteID(obj);			
			cout<<"jolly:According to picked point can't find any goods (in pickGoods 77)"<<pt_flag<<endl;
		}
		else
		{			
			char goodsid[40];
			memset(goodsid,'\0',40);
			strncpy(goodsid,(pt_it->second).c_str(),sizeof(goodsid));
			bound=pick->getBound();					
			
			Team *team;
			
			if(strlen(hero->getTeamerId()) == 0)	//判断玩家是否有队伍
			{
				team=NULL;						//无队伍,返回false
			}
			
			else								
			{		
				TeamManager* teamManger = TeamManager::getManagerInst();
			
				if(!teamManger)
				{
					cout<<"getexperience teamManger is NULL:"<<endl;
					return;
				}	
			
				team = teamManger->getTeamHandle(hero->getTeamerId());
			}
			if (bound==1)
			{
				if (pick_success(goodsid,hero,msg,flag,team))
				{					
					num--;
					if (num==0)
					{
						map_now->deleteDropInst(flag);
					}
					else
					{			
						pick->setNum(num);
						pt_goodsid.erase(pt_it);	
						pick->setDropGoods(pt_goodsid);
					}
				}
			}
			else if (bound==0)
			{
				if (strcmp(killheroid,hero->getIdentity())==0||isTeamGoods(hero,killheroid,team)==0)
				{	
					if  (pick_success(goodsid,hero,msg,flag,team))
					{					
						num--;
						if (num==0)
						{
							map_now->deleteDropInst(flag);
						}
						else
						{
							pick->setNum(num);
							pt_goodsid.erase(pt_it);
							pick->setDropGoods(pt_goodsid);
						}				
					}		
				}
				else
				{
					msg_error(g_out_buf,109);
					send_msg(hero->getFd(),g_out_buf);
				}
			}
			else if (bound==2)
			{
				msg_error(g_out_buf,110);
				send_msg(hero->getFd(),g_out_buf);
			}
		}
	}	
}

#if 0
//采集任务采集的物品验证
void pickTaskGoods(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_CHAR(char *realGoodsId)				//物品实例ID
	cout<<"realGoodsId::"<<realGoodsId<<endl;
	//解析实例物品ID
	
	Hero *hero=pg_hero;
	if (hero == NULL)
	{
		return;
	}
	
	Map_Inform* heroMap = hero->getMap();
	//实例ID找到实例指针
	TakeGoods *take = heroMap->getTakeObj(realGoodsId);
	if (take == NULL)
	{
		cout<<"BisonWarning: there is no takeGoods!"<<endl;
		return;
	}
	
	//获得物品ID
	char *goodsId = take->getGoodsId();
	//hero下接的有收集道具的任务

	list<Task*> map_task=hero->getAccepted_Task_List();
	if (!map_task.empty())
	{
		list<Task*>::iterator task_it;
		for (task_it = map_task.begin(); task_it != map_task.end(); task_it++)
		{
			Task* task=(*task_it);
			if (task->needMoreCollection(goodsId))
			{
				if (!strcmp(goodsId, "b_rw_100_00402_1"))
				{
					cout<<"BisonTest before use Random goods!"<<endl;
					//如果是藏宝图任务，打开宝箱要随机一个物品出来
					if (useRandomGoods(hero, goodsId, -1))
					{
						heroMap->disperTakeGood(realGoodsId);
						//更新任务数据，类型为采集
						hero->updateHeroTaskStatus(TREASURE_MAP_TASK_NEED_TYPE, "b_rw_100_00402_1");
					}
				}
				else if (!strcmp(goodsId, "b_rw_100_00415_1") || !strcmp(goodsId, "b_rw_100_00068_1"))
				{
					//救死扶伤任务
					heroMap->disperTakeGood(realGoodsId);
					//更新任务数据，类型为采集
					hero->updateHeroTaskStatus(RESCUE_TASK_NEED_TYPE, goodsId);
				}
				else
				{
					//放到包中成功，再在地图上消失
					if (saveGoodsInBag(hero,goodsId, 1))
					{
						heroMap->disperTakeGood(realGoodsId);
						//更新任务数据，类型为采集
						hero->updateHeroTaskStatus(PICKUP_TASK_NEED_TYPE, goodsId);
					}
				}
				break;
			}
		}
	}
	
	
	cout<<"collected goods is "<<goodsId<<endl;

}
#endif

int check_collect(Hero* hero, char* collectId)
{
	if (hero->isInCollecting())
	{
		//正在采集中
		return 6;
	}
	Map_Inform* heroMap = hero->getMap();
	//实例ID找到实例指针
	TakeGoods *take = heroMap->getTakeObj(collectId);
	if (take == NULL)
	{
		cout<<"BisonWarning: there is no takeGoods!"<<endl;
		return 2;
	}
	
	Point collectPt = take->getPt();
	Point heroPt = hero->getLocation();
	if (GET_DISTANCE(collectPt, heroPt) > 500)
	{
		//采集物和人距离太远
		return 7;
	}
	int type = take->getTaskStyle();
	int brandType = take->getBrandType();
	//获得物品ID
	char *goodsId = take->getGoodsId();
	//任务采集类型
	if (type == 1)
	{
		//hero下接的有收集道具的任务
		if (strlen(goodsId) != 16)
		{
			//物品ID不是任务道具
			return 3;
		}
#if 0		
		if (!(hero->memHero->taskState & TASK_NEED_COLLECT_GOODS))
		{
			//玩家没有接此任务
			return 4;
		}
#endif		
		list<Task*> taskList = hero->getAccepted_Task_List();
		if (taskList.size() == 0)
		{
			//玩家没有接此任务
			return 4;
		}
		list<Task*>::iterator it_task = taskList.begin();
		Task* task = NULL;
		for (it_task; it_task != taskList.end(); it_task++)
		{
			task = *it_task;
			if (task->needMoreCollection(goodsId))
			{
				goto LE;
			}
		}
		//玩家已经不需要收集此物品
		return 5;
	
	} else if (type == 2) {
	//帮派吃饭
		if (hero->getGuild()==NULL)
		{
			//还没有加入帮派
			return 12;
		}
		if (!hero->getGuild()->ifHeroCanEatFeast(hero,collectId))			//判断玩家是否可以吃盛宴
		{
			return 0;
		}
		goto LE;
	} else if (type == 3) {
		//帮派战夺旗
		// int ret = guildWarManage->isHeroPickFlagOk(hero, brandType);
		
		if (!robFlagWarManage->IspickOk(hero, brandType))
		{
			// char msg[1024] = {0};
			// sprintf(msg, "18,18,%d", ret);
			// send_msg(hero->getFd(), msg);
			return 8;
		}
		
	} 
	else if (type == 4) 
	{
		//此为捕捉宠物,已写另外的借口采集,此type已占用,请勿重复 jolly add 2013.1.14
	}
	else if (type == 5)
	{
		//阵营资源战中资源
		if (take->isPicking())
		{
			return 13;
		}
	}
	else {
		cout<<"collect goods and error type is "<<type<<endl;
		return -1;
	}
	
LE:	;	
	char msg[128] = {0};
	int collectTime = take->getTakeTme();
	sprintf(msg, "28,0,1,%s,%d", take->getOfferWords(), collectTime);
	send_msg(hero->getFd(), msg);
	hero->startCollectTimer(collectTime, collectId);
	take->inPutOwner(hero->getIdentity());
	return 0;
}

void collectGoodsComm(char* buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_CHAR_END(char *realGoodsId)				//物品实例ID
	Bag *bag=pg_hero->getBag();					//jolly add 若背包已满,则不允许采集
	if (bag==NULL)
	{
		return;
	}
	if (bag->bagIsFull(1))
	{
		msg_error(g_out_buf,44);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	else
	{
		int ret = check_collect(pg_hero, realGoodsId);
		if (ret != 0)
		{
			char msg[32] = {0};
			sprintf(msg, "28,0,0,%d", ret);
			send_msg(pg_hero->getFd(), msg);
		}
	}
}

bool pick_success(char* goodsid,Hero *hero,char* _msg,char* flag,Team *team)
{	
	char msg[100]={'\0'};
	sprintf(msg,"%d,%d,%d%s",9,PICK_RETURN,SUCCESS,_msg);
		
	if (team==NULL)
	{
		if (saveGoodsInBag(hero,goodsid,1)==0)
		{
			return false;
		}
		else 
		{			
			int goodsType=getGoodsType(goodsid);
			char account_msg[1024]={'\0'};
			if (goodsType==1)
			{				
				/*记录获得装备的流水账 jolly 12.10 start*/
				snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d,%d",7,0,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),goodsid,1,0);
				write_log(account_msg);	
				/*记录获得装备的流水账 jolly 12.10 end*/	
			}
			else 
			{
				/*记录保存物品的流水账 jolly 12.11 start*/
				snprintf(account_msg,sizeof(account_msg),"%d,%d,%s,%d,%s,%s,%s,%d,%d",8,0,server_name,(int)myTime.tv_sec,hero->getIdentity(),hero->getNickName(),goodsid,1,0);
				write_log(account_msg);	
				/*记录保存物品的流水账 jolly 12.11 end*/
			}
		}
	}
	else
	{
		if (!team->assignGoods(goodsid,1))
		{
			return false;
		}
	}
	sprintf(msg,"%s,%s",msg,hero->getIdentity());
	send_nbox(hero->getMap(),msg,flag);												////////////////////////////////////////捡取删除九宫格///////////////////////		
	return true;
}

bool isTeamGoods(Hero *hero,char* killPerson,Team *team)				//判断该物品是不是队伍内的玩家打掉的,若是,则返回true,否则返回false
{
	if (!team==NULL || !hero || killPerson)
	{
		return false;
	}
	return team->isInTeam(killPerson);
}
 
void pick_failed()
{
	return;
}

void send_nbox(Map_Inform *map_now,char* _msg,char* goodsId)
{
	StyObj obj(goodsId,PICK_STYLE_TYPE);
	
	Nbox *box;
			
	box = map_now->getBox();
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(_msg);
	
	return;
}

void send_error_nbox(Hero *hero,char* _msg)
{	
	Nbox *box;
	
	Map_Inform *map_now=hero->getMap();
	
	box = map_now->getBox();
	
	StyObj obj(hero->getIdentity(),HERO_STYLE_TYPE);	
	
	box->getStaInSrcVec(obj);
	
	box->sentBoxMsg(_msg);
}

void pickMoney(char* buffer)
{
	MSG_BEGIN(buffer, g_msg_len)
	MSG_CHAR(char *identity)
	MSG_CHAR(char* flag)
	MSG_INT(int pt_x)
	MSG_INT(int pt_y)
	cout<<"9,21,"<<identity<<","<<flag<<","<<pt_x<<","<<pt_y<<endl;
	
	int ptx=pt_x;
	int pty=pt_y;
	char pt_flag[100]={'\0'};
	sprintf(pt_flag,",%d,%d",pt_x,pt_y);
	cout<<"pt_flag is:"<<pt_flag<<endl;
	
	Map_Inform *map_now;
	StyObj obj(flag,PICK_STYLE_TYPE);
	Pick *pick;
		
	map_now = pg_hero->getMap();	
	
	if(map_now == NULL)
	{
		cout<<"the map is NULL:"<<endl;
		return;
	}
	
	pick = map_now->getDropPickInst(flag);
	if(pick == NULL)
	{
		cout<<"the pickId is not find the inst:"<<flag<<endl;
	}
	else
	{
		int num=pick->getNum();
		map<string,string> pt_goodsid=pick->getDropGoods();
		map<string,string>::iterator pt_it;
		pt_it=pt_goodsid.find(pt_flag);
		if (pt_it==pt_goodsid.end())
		{			
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s%s",9,PICK_RETURN,SUCCESS,flag,pt_flag);
			send_error_nbox(pg_hero,g_out_buf);
			Map_Inform *map_now=pg_hero->getMap();
			map_now->deleteID(obj);			
			cout<<"jolly:According to picked point can't find any goods (in pickGoods 495),"<<pt_flag<<endl;
		}	
		else
		{
			char goodsid[40];
			memset(goodsid,'\0',40);
			strncpy(goodsid,(pt_it->second).c_str(),sizeof(goodsid));
			int moneyNum=atoi(goodsid);	
			
			if (increaseBoundGameMoney(pg_hero,moneyNum))
			{			
				snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s%s,%s",9,PICK_RETURN,SUCCESS,flag,pt_flag,pg_hero->getIdentity());
				cout<<"g_out_buf:"<<g_out_buf<<endl;
				send_nbox(pg_hero->getMap(),g_out_buf,flag);	
				num--;
				if (num==0)
				{
					map_now->deleteDropInst(flag);
				}
				else
				{
					pick->setNum(num);
					pt_goodsid.erase(pt_it);	
					pick->setDropGoods(pt_goodsid);
				}				
			}
		}		
	}
}

void pickPetToBox(char *buffer)
{
	MSG_BEGIN(buffer,g_msg_len)
	MSG_CHAR(char *realGoodsId)				//拾取的物品实例ID
	MSG_INT(int index)						//物品索引
	
	
	
	Bag *bag=pg_hero->getBag();
	if (bag==NULL)
	{
		return;
	}
	int bagNum=bag->getBagNum();
	if (index<0||index>bagNum)
	{
		return; 
	}
	
	int ret = -1;
	
	if (pg_hero->isInCollecting())
	{
		//正在采集中
		ret = 6;
	}
	Map_Inform* heroMap = pg_hero->getMap();
	//实例ID找到实例指针
	TakeGoods *take = heroMap->getTakeObj(realGoodsId);
	if (take == NULL)
	{
		cout<<"BisonWarning: there is no takeGoods!"<<endl;
		ret = 2;
	}
	
	Point collectPt = take->getPt();
	Point heroPt = pg_hero->getLocation();
	if (GET_DISTANCE(collectPt, heroPt) > 500)
	{
		//采集物和人距离太远
		ret = 7;
	}
	int type = take->getTaskStyle();
	if (type==4)
	{
		if (bag->test(index,"f_cl_132_100")||bag->test(index,"b_cl_132_100"))
		{			
			char msg[128] = {0};
			int collectTime = take->getTakeTme();
			sprintf(msg, "28,0,1,%s,%d", take->getOfferWords(), collectTime);
			send_msg(pg_hero->getFd(), msg);
			pg_hero->startCollectTimer(collectTime, realGoodsId);
			take->inPutOwner(pg_hero->getIdentity());
			ret = 0;
		}
	}
	
	if (ret != 0)
	{
		char msg[32] = {0};
		sprintf(msg, "28,0,0,%d", ret);
		send_msg(pg_hero->getFd(), msg);
	}
}