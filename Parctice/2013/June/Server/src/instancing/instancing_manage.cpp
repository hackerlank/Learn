#include <stdio.h>
#include"mapAction.h"
#include "instancing_manage.h"
#include "instancing_communication.h"
#include"cpyLimit.h"
#include"cpyAsist.h"

#include"teamManager.h"

#define MAX_MSG_SIZE 300
#define INIT_ROOM_SIZE 	5	//初始化副本房间个数
#define MAX_ROOM_SIZE	10	//最大房间上限

extern struct ev_loop *loops;
extern map<string, TD_Conf_T> id_2_tdConf;      //塔防副本的全局配置
extern map<string, Map_Inform *> mapId_connect_map;
extern map<string, Map_Cpy *> cpyMapConf;
extern Instancing_manage *Inst_MNG;   			//副本管理类的全局配置
extern map<string,Team*> id_to_team;			//队伍容器
extern map<string, Hero*> heroId_to_pHero;		//在线角色容器


/* 初始化塔防副本管理实例 */
void initInstManage()
{ 
    Inst_MNG = new Instancing_manage();
}


/* 
* author：Tory	
* date:2013.1.29
* describe: 副本锁定时间到期后的回调函数
*/
void cpyOutOfLockCB(struct ev_loop *loop, ev_timer *watcher, int revents)
{
	ev_timer_stop(loops, watcher);			//停止定时器

	Team* team = (Team*)watcher->target;
	if(team == NULL)
		return;
	
	/*add by chenzhen 201301291740*/	
//	team->stopTimerWatcher();
#if 0		
	if(team->cpyRoomStr.size() == 0)	//数据错误，队伍中没有锁定的副本房间Id
		return;
		
	if(team->cpyRoomStr.compare(0, 3, "008") == 0)	//塔防副本
	{
		TD_Instancing *tdRoom = Inst_MNG->id2tdRoom(team->cpyRoomStr);
		if (NULL == tdRoom)	
			return;
		tdRoom->reset();        //reset塔防副本数据
		Inst_MNG->idleRooms.push_back(tdRoom);				
	}
#endif 
	/* 	want to reset cpy,please add code in here  */

}

/*
 * Instancing_manage - 	副本管理类的构造
 * @
 * Description: 在初始构造中初始部分副本房间实例
 */
Instancing_manage::Instancing_manage()
{
    if (id_2_tdConf.size() != 3) 
    {
        cout << "@@Tory tower defence configure error!" << endl;
        exit(-1);	//启动服务器时，检测塔防配置是否正确
    }

    for (int row = 0; row < INIT_ROOM_SIZE; row++)       //row作房间号，实例一个塔防副本
    {
        TD_Instancing *new_TD = new TD_Instancing(row);
        idleRooms.push_back(new_TD);                        //将塔防副本加到未使用的副本序列
        instId2totalRooms.insert(map<string, TD_Instancing *>::value_type(new_TD->get_instancing_id(), new_TD));
    }
//	cout << "@@Tory::instId2totalRooms.size():" << instId2totalRooms.size() << endl;
}


/*
* author:	tory
* date	:	2013.1.28
* arg	:   @ Hero* heroPtr执行副本申请操作的队长Hero*实例，inst_typeId：包含难度等级的副本ID（010_0）
* describe: 队长申请进入塔防副本，申请成功，则向队员发送挑战副本的邀请；否则向队长返回申请副本失败的原因
* return value: 0:进入副本成功，1:条件不满足，进入副本失败 -1：数据错误，服务器不响应
*/
int Instancing_manage::apply_td_inst(Hero* heroPtr, char* inst_typeId)
{
	if(heroPtr == NULL || strlen(inst_typeId) != 5)
	{
		return -1;	//数据错误
	}
	
	if (strlen(heroPtr->getTeamerId()) == 0)    //无组队状态,仅需验证申请者的进入条件和空闲副本房间
    {
		//1、检查进入者的进入条件
		int error_code = Instancing_manage::enableEnter(heroPtr, inst_typeId);
        if (error_code >= 0)		//进入条件判定失败
        {
			memset(g_out_buf, 0, 20480);
			sprintf(g_out_buf, "%d,%d,%d,%s", 6, 7, error_code, heroPtr->getNickName());
			send_msg(heroPtr->getFd(), g_out_buf);								
            return 1;
        }
		
        //2、申请副本房间
        string tdRoomId = Instancing_manage::gain_towerDefTeam_roomId(inst_typeId); //获取塔防副本房间号；
        if (tdRoomId.size() == 0)           //房间已满
		{
			memset(g_out_buf, 0, 20480);
			sprintf(g_out_buf, "%d,%d,%s", 6, 13, inst_typeId);
			send_msg(heroPtr->getFd(), g_out_buf);
            return 1;
        }
		cout << "@@Tory tdRoomId:" << tdRoomId << endl;

        //3、通过副本管理类进入相应副本实例
        if (Instancing_manage::enter_inst_room(heroPtr, tdRoomId, 0) == false)       //进入房间
        {
            cout << "Warning(towerDefTeamAsist.cpp):(enterTowerDefRoom)::enter_inst_room error,cause tdRoomId is error" << endl;
            return -1;  //数据错误
        }

        //4、设置副本挑战模式 2012.12.18
        TD_Instancing *tdPtr = Instancing_manage::id2tdRoom(tdRoomId);
        if (tdPtr == NULL) 
			return -1;
        tdPtr->heroPtr_vec.push_back(heroPtr);
		tdPtr->isSingleChall == true;	//单人挑战模式

        //5、开启副本定时器
        Instancing_manage::start_instancing(tdPtr);

        return 0;
	
	}
	else
	{
		TeamManager* teamManger = TeamManager::getManagerInst();
	
		Team *team = teamManger->getTeamHandle(heroPtr->getTeamerId());
		
		if(!team)
		{
			cout<<"Instancing_manage::apply_td_inst team is NULL:"<<endl;
			return -1;		
		}

        //1、验证是不是队长在进行操作
        if (!team->isHeader(heroPtr->getIdentity()))		
		{
			memset(g_out_buf, 0, 20480);
			sprintf(g_out_buf, "%d,%d,%d,%s", 6, 7, 6, heroPtr->getNickName());	//已在队伍中，但不是队长ERROR_IN_TEAM 6
			send_msg(heroPtr->getFd(), g_out_buf);
			return 1;
		}
	
		//2、申请副本房间
        string tdRoomId = Instancing_manage::gain_towerDefTeam_roomId(inst_typeId); //获取塔防副本房间号；
        if (tdRoomId.size() == 0)           //房间已满
		{
			memset(g_out_buf, 0, 20480);
			sprintf(g_out_buf, "%d,%d,%s", 6, 13, inst_typeId);
			send_msg(heroPtr->getFd(), g_out_buf);
            return 1;
        }
		cout << "@@Tory tdRoomId:" << tdRoomId << endl;
		
		TD_Instancing *tdPtr = Instancing_manage::id2tdRoom(tdRoomId);
		if (tdPtr == NULL) 
			return -1;
				
		//3、检查队伍中各个成员的进入条件
		vector<string> teamMemberIdVec;
		team->getTeamMemberId(teamMemberIdVec);
        for (vector<string>::const_iterator mem_it = teamMemberIdVec.begin(); mem_it != teamMemberIdVec.end(); ++mem_it)
        {        
            Hero *myHero = heroid_to_hero(*mem_it);
            if (myHero == NULL) 
				return -1;	//数据错误
		
			int error_code = Instancing_manage::enableEnter(myHero, inst_typeId);
			if (error_code >= 0)		//队伍中有成员进入条件不满足
			{
				memset(g_out_buf, 0, 20480);
				sprintf(g_out_buf, "%d,%d,%d,%s", 6, 7, error_code, myHero->getNickName());
				sendFailMsg(teamMemberIdVec,g_out_buf);	
				return 1;
			}
			else
			{
				tdPtr->heroPtr_vec.push_back(myHero);	//将在线角色对象放入塔防副本实例管理的容器中，回收副本时记得清理
			}
        }
		
		//4、进入副本条件满足且副本房间申请成功，向队友发送挑战副本的邀请
		if(tdPtr->heroPtr_vec.size() == 1)
		{
			//验证塞入到tdPtr->heroPtr_vec中的角色对象是否正确
			if(strcmp(heroPtr->getIdentity(), tdPtr->heroPtr_vec[0]->getIdentity()) != 0)
			{
				return -1;
			}
			//a、通过副本管理类进入相应副本实例
			if (Instancing_manage::enter_inst_room(heroPtr, tdRoomId, 0) == false)       //进入房间
			{
				cout << "Warning(towerDefTeamAsist.cpp):(enterTowerDefRoom)::enter_inst_room error,cause tdRoomId is error" << endl;
				return -1;  //数据错误
			}

			//b、设置副本挑战模式 2012.12.18
			tdPtr->heroPtr_vec.clear();
			tdPtr->heroPtr_vec.push_back(heroPtr);
			tdPtr->isSingleChall == true;	//单人挑战模式

			//c、开启副本定时器
			Instancing_manage::start_instancing(tdPtr);

			return 0;
		
		}
		else
		{			
			memset(g_out_buf, 0, 20480);
			sprintf(g_out_buf, "%d,%d,%s,%d", 6, 6, tdPtr->infor.name.c_str(), tdPtr->infor.degree);
			cout<<"@@Tory: broadcast:"<<g_out_buf<<endl;

            //向除队长外的其他队员发送邀请挑战副本的广播
            vector<Hero*>::iterator iter = tdPtr->heroPtr_vec.begin();
			for(iter; iter != tdPtr->heroPtr_vec.end(); iter++)
			{
				Hero* other_hero = *iter;
				if(strcmp(other_hero->getIdentity(), heroPtr->getIdentity()) != 0)	//排除队长
				{
                    send_msg(other_hero->getFd(), g_out_buf);  
				}

            }           
			team->holdCaptureCopyId(tdRoomId.c_str());
			return 0;
		}		
	
	}
	
}


/*
* author:	tory
* date	:	2013.1.29
* arg	:   @ Team* team
* describe:	
*/
int Instancing_manage::teamEnter(Team* team)
{
	if(team == NULL)
		return -1;
	string tdRoom = team->getCaptureCopy();
	if(tdRoom.size() == 0)
		return -1;
		
	TD_Instancing *tdPtr = Instancing_manage::id2tdRoom(tdRoom);
	if (tdPtr == NULL) 
		return -1;
			
	if(tdPtr->heroPtr_vec.size() < 2)
		return -1;
		
	//1、通过副本管理类进入相应副本实例
	int index = 0;
	vector<Hero*>::iterator iter = tdPtr->heroPtr_vec.begin();            
	for (iter; iter != tdPtr->heroPtr_vec.end(); iter++)
	{
		Hero *myHero = *iter;
		if (myHero == NULL) 
			return -1;

		if (!Instancing_manage::enter_inst_room(myHero, tdRoom, index % 4))       //进入房间；
		{
			cout << "Warning(towerDefTeamAsist.cpp):(enterTowerDefRoom)::enter_inst_room error,cause tdRoom is error" << endl;
			return -1;  //数据错误
		}
		index++;		

	}
	
	//2、设置副本挑战模式
	if(tdPtr->heroPtr_vec.size() > 1)
		tdPtr->isSingleChall == false;  //非单人条找模式

	
	//3、开启副本定时器
	Instancing_manage::start_instancing(tdRoom);

	return 0;
}

/*
* author:	tory
* date	:	2012.12.17
* arg	:   @ Hero* myHero
* describe:	对申请进入副本的角色进行检测，如满足进副本条件，则返回0;条件不满足返回相应失败代码，数据错误返回-1
*/
int Instancing_manage::enableEnter(Hero *myHero, char *inst_typeId)
{
    if (myHero == NULL || strlen(inst_typeId) != 5)	return -1;   //数据错误
	
    HeroCpyRecord *record = myHero->getCpyRecord();
    if (record == NULL) 	return -1;   //数据错误

	Map_Inform* map_now = myHero->getMap();
	if (map_now == NULL) 	return -1;   //数据错误
	 
    char *wagonId = myHero->memHero->wagonId;
    char *fbRom = myHero->getFbRom();
	
	map<string, TD_Conf_T>::iterator iter = id_2_tdConf.find(inst_typeId);
    if (iter == id_2_tdConf.end())
    {
        return -1;
    }
    TD_Conf_T td_config = iter->second;
	
	//玩家等级不够
	if(myHero->getLevel() < td_config.require.level)
	{
		return ERROR_LOWER_RANK;
	}
	
	//体力值不够
	if(myHero->memHero->lastStrength < 5)
	{
		return ERROR_LOWER_LAST_POWER;
	}
	
	//此人处于摆摊状态
    if (myHero->getHeroState()==5)
    {
		cout<<"@@Tory can't enable enter,cause is stall"<<endl;
        // failure_reason->member[fail_index].failure_flag = ERROR_IN_SELL;
        // strncpy(failure_reason->member[fail_index].nickName, myHero->getNickName(), IDL);
        // failure_reason->size += 1;
        return ERROR_IN_SELL;
    }
#if 0
    //此人不在主城
    if (strcmp(myHero->getMapId(), "map_001") != 0 && strcmp(myHero->getMapId(), "map_010") != 0)
    {
		cout<<"@@Tory can't enable enter,cause didn't in Major city"<<endl;
        // failure_reason->member[fail_index].failure_flag = ERROR_IN_MAIN_CITY;
        // strncpy(failure_reason->member[fail_index].nickName, myHero->getNickName(), IDL);
        // failure_reason->size += 1;
        return ERROR_IN_MAIN_CITY;
    }
#endif
    /*副本没有开启*/
	if (!record->judUperRank(inst_typeId))
    {
		cout<<"@@Tory can't enable enter,cause haven't open"<<endl;
        // failure_reason->member[fail_index].failure_flag = ERROR_NO_OPEN;
        // strncpy(failure_reason->member[fail_index].nickName, myHero->getNickName(), IDL);
        return ERROR_NO_OPEN;
    } 

    /*此人处于押镖状态*/
    if (strlen(wagonId) != 0)
    {
		cout<<"@@Tory can't enable enter,cause have wagonId"<<endl;
        // failure_reason->member[fail_index].failure_flag = ERROR_YA_BIAO;
        // strncpy(failure_reason->member[fail_index].nickName, myHero->getNickName(), IDL);
        // failure_reason->size += 1;
        return ERROR_YA_BIAO;
    }
    /*此人处于副本状态*/
	if(map_now->getFlgCpy())
	{
		cout<<"@@Tory can't enable enter,cause have enter other cpy:"<<map_now->getIdentity()<<endl;
        // failure_reason->member[fail_index].failure_flag = ERROR_IN_COPY;
        // strncpy(failure_reason->member[fail_index].nickName, myHero->getNickName(), IDL);
        // failure_reason->size += 1;
        return ERROR_IN_COPY;
    }
	/*此人处于pk状态*/
	if(map_now->getWarType() != 1)
	{
		cout<<"@@Tory can't enable enter,cause have enter PK scene"<<endl;
		// failure_reason->member[fail_index].failure_flag = ERROR_PK;
        // strncpy(failure_reason->member[fail_index].nickName, myHero->getNickName(), IDL);
        // failure_reason->size += 1;
        return ERROR_PK;
	}
	
	/*是否处于娱乐地图*/
	if(isHappyMap(map_now->getMapId()))
	{
        return ERROR_IN_HAPPY;
	}

    return -1;
}

/*
* author:	xhm
* date	:	2012.8.15
* amend :	tory 2012.11.29
* 传入参数：申请进入的副本类型ID,申请进入副本失败的原因结构体指针
* describe:	对申请进入副本的队伍进行检测，如该队伍能接进入相应副本，则为其分配房间号，
*				否则则返回一个为空的sting类型值
*/
string Instancing_manage::gain_towerDefTeam_roomId(string inst_typeId)
{
    string roomId;

    if (inst_typeId.empty()) return roomId;

    map<string, TD_Conf_T>::iterator iter = id_2_tdConf.find(inst_typeId);
    if (iter == id_2_tdConf.end())
    {
        return "";
    }
    TD_Conf_T td_config = iter->second;
    if (td_config.scenes_id_vec.size() != 2)
    {
        return "";
    }
    map<string, Map_Cpy *>::iterator cpy_iter = cpyMapConf.find(td_config.scenes_id_vec[0]);
    if (cpy_iter == cpyMapConf.end())
    {
        return "";
    }
    Map_Cpy *mapCpy = cpy_iter->second;
    if (mapCpy == NULL)
    {
        return "";
    }
    //房间总数未达上限
    if (instId2totalRooms.size() < MAX_ROOM_SIZE)
    {
        //已无空闲副本房间,继续分配
        if (idleRooms.size() == 0)
        {
            int roomNum = instId2totalRooms.size() + 1; //新开房间号
            Map_Cpy *scene = mapCpy->copyMap(roomNum); //拷贝地图

			TD_Instancing *new_TD = new TD_Instancing(roomNum);
			instId2totalRooms.insert(map<string, TD_Instancing *>::value_type(new_TD->get_instancing_id(), new_TD));
			
            if(!new_TD->loadNewInstance(td_config, scene))	//加载塔防副本数据失败
            {
				//释放地图数据
				delete scene;
				return "";
			}
            cout << "in Instancing_manage::get a new room" << new_TD->get_instancing_id() << endl;
            roomId = new_TD->td_inst_id;

            return roomId;
        } else
        {
            TD_Instancing *td_room = idleRooms.back();
            cout << "in Instancing_manage::enter room" << td_room->get_instancing_id() << endl;
            Map_Cpy *scene = mapCpy->copyMap(td_room->roomNum);             //拷贝地图
            if(!td_room->loadNewInstance(td_config, scene))					//加载塔防副本数据失败
            {
				//释放地图数据
				delete scene;
				return "";
			}
            roomId = td_room->td_inst_id;
            idleRooms.pop_back();

            return roomId;
        }
    } else
    {
        return "";
    }
}

/*
* author	:	bison
* Description: 根据副本实例ID（房间号），从副本管理容器中得到副本实例指针
*/
TD_Instancing* Instancing_manage::id2tdRoom(string roomId)
{
    map<string, TD_Instancing *>::iterator iter = instId2totalRooms.find(roomId);
    if (iter != instId2totalRooms.end()) return iter->second;
    else return NULL;
}

//开启副本轮询机制,在进入副本时调用
bool Instancing_manage::start_instancing(TD_Instancing *tdPtr)
{
//	TD_Instancing* tdPtr = Instancing_manage::id2tdRoom(roomId);
    if (tdPtr == NULL) return false;
//	tdPtr->setPollState(true);
    ext_ev_timer_init(tdPtr->timer, inst_poll_callback, 1, 0, tdPtr);
    ev_timer_start(loops, tdPtr->timer);
    return true;
}
//开启副本轮询机制,在进入副本时调用
bool Instancing_manage::start_instancing(string roomId)
{
    TD_Instancing *tdPtr = Instancing_manage::id2tdRoom(roomId);
    if (tdPtr == NULL) return false;

    ext_ev_timer_init(tdPtr->timer, inst_poll_callback, 1, 0, tdPtr);
    ev_timer_start(loops, tdPtr->timer);
    return true;
}

/*
* author:	tory
* data	:	2012.8.27
* Description: 通过副本管理类，对相应角色进入相应的副本房间进行处理, Hero *heroWillEnter, string tdRoom(副本房间ID), int index（站立的区域）
*/
bool Instancing_manage::enter_inst_room(Hero *heroWillEnter, string tdRoom, int _index)
{
    TD_Instancing *this_inst = Instancing_manage::id2tdRoom(tdRoom);
    if (this_inst == NULL) return false;

    if (_index < 0 || _index > 3) return false;

    //保存跳转之前的位置和地图ID
    heroWillEnter->setBeforePiexPt(heroWillEnter->getLocation());
    heroWillEnter->setMainSrc(heroWillEnter->getMapId());
    heroWillEnter->setFbRom(tdRoom.c_str());
    heroWillEnter->quit_scene();

    //通过副本实例的配置，修改heroWillEnter中的位置数据：mapId, Map_Inform*,location
    this_inst->setHeroLocation(heroWillEnter, _index);
//	cout << "@@Tory enter_tower_defence, nickName:" << heroWillEnter->getNickName() << endl;
	heroWillEnter->initCpyRecTme();	//初始角色在副本中的死亡次数记录 tory add 2013.1.7

	Point stand_point = heroWillEnter->getLocation();

    char msg_body[1024] = { 0 };
    sprintf(msg_body, "%d,%d,%d,ectype_map_034,%d,%d,%d,%d,%d", 2, 6, 1, stand_point._x, stand_point._y,\
               heroWillEnter->getMap()->getWarType(), heroWillEnter->getMap()->getChangePkType(), heroWillEnter->getMap()->getMapType());
    send_msg(heroWillEnter->getFd(), msg_body);
	
	
	heroWillEnter->setWalkingFlg(false);	
	
	heroWillEnter->enter_scene();	//tory add 2013.1.21 may coredump so amend!!!	
    return true;

}

/*
* author:	tory
* data	:	2012.8.27
* Description: 通过副本管理类，使相应角色退出相应的副本房间（暂时仅管理塔防副本）Hero *heroWillQuit, string roomId
*/
bool Instancing_manage::exit_inst_room(Hero *heroWillQuit, TD_Instancing *tdRoom)
{
    if (heroWillQuit == NULL || tdRoom == NULL) return false;
   
	//将heroWillQuit从tdRoom->heroPtr_vec中删掉
	vector<Hero*>::iterator memIter = tdRoom->heroPtr_vec.begin();
	for (memIter; memIter != tdRoom->heroPtr_vec.end(); memIter++)
	{
		Hero *h_ptr = *memIter;
		if (h_ptr != NULL) 
		{	
			if(strcmp(heroWillQuit->getIdentity(), h_ptr->getIdentity()) == 0)
				break;
		}	
    }
	if(memIter == tdRoom->heroPtr_vec.end())
		return false;
	else 
		tdRoom->heroPtr_vec.erase(memIter);
		
	char mapIdentity[40]={'\0'};
	strncpy(mapIdentity,heroWillQuit->getMap()->getIdentity(),sizeof(mapIdentity));
	cout<<"############################################"<<endl;
	cout<<"mapIdentity:"<<mapIdentity<<endl;
	cout<<"############################################"<<endl;
	if (strncmp(mapIdentity,"ectype_map_034_1",16)==0)
	{
		heroWillQuit->updataSingleTarget(4,5);
	}
		
	char msg_body[1024] = { 0 };
    Point prePt = heroWillQuit->getBeforePiexPt();
    string mainSrcId = heroWillQuit->getMainSrc();

    map<string, Map_Inform *>::iterator iter_map  = mapId_connect_map.find(mainSrcId);
    if (iter_map == mapId_connect_map.end()) return false;

    heroWillQuit->quit_scene();
    heroWillQuit->setMap(iter_map->second);
    heroWillQuit->setMapId(mainSrcId.c_str());
    sprintf(msg_body, "%d,%d,%d,%s,%d,%d,%d,%d,%d", 2, 6, 1, mainSrcId.c_str(), prePt._x, prePt._y,\
               iter_map->second->getWarType(), iter_map->second->getChangePkType(), iter_map->second->getMapType());
    heroWillQuit->setLocation(prePt);
    send_msg(heroWillQuit->getFd(), msg_body);
    return true;
}


//停止副本的轮询，在退出副本时调用
bool Instancing_manage::stop_instancing(TD_Instancing *tdPtr)
{
//	TD_Instancing* tdPtr = Instancing_manage::id2tdRoom(roomId);
    if (NULL == tdPtr) return false;
//	tdPtr->setPollState(false);
    ev_timer_stop(loops, tdPtr->timer);
	tdPtr->stopMonThk();
    return true;
}

//停止副本的轮询，在退出副本时调用
bool Instancing_manage::stop_instancing(string roomId)
{
    TD_Instancing *tdPtr = Instancing_manage::id2tdRoom(roomId);
    if (NULL == tdPtr) return false;
//	tdPtr->setPollState(false);
    ev_timer_stop(loops, tdPtr->timer);
	tdPtr->stopMonThk();
    return true;
}