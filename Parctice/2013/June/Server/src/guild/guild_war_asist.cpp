/****************************************************************
 * Filename: guild_war_asist.cpp
 * 
 * Description: 帮战房间辅助类
 *
 * Original Author : bison, 2012-8-28
 *
 ****************************************************************/
 
#include"guild_war_asist.h"

#define NORMAL_VESION_FOR_GUILD_WAR

extern map<string,Map_Src*> mapId_connect_map;
extern MapType_T mapTypeInfo;		//默写特殊地图的ID；
//帮战辅助类构造
GuildWarAsist::GuildWarAsist()
{
	int i;
	Map_Src  *warMap = NULL;	
	map<string,Map_Src*>::iterator it_map;
	
	// char* scene_id = mapTypeInfo.guidWarMapId;  //帮派战地图ID；
	it_map = mapId_connect_map.find(mapTypeInfo.guidWarMapId);
	if(it_map == mapId_connect_map.end()){
		return ;
	}
	warMap = it_map->second;
	
	for(i = MAX_GUILD_WAR_ROOM_NUM - 1; i >= 0; i--)
	{
		Map_Src *scene = NULL;
		//调用地图里面的复制方法
		scene = warMap->copyMap(i);
		
		GuildWarRoom *room = new GuildWarRoom(i, scene);
		
		//cout<<"BisonShow : all thing is OK!"<<endl;
		//加到所有帮战房间的容器
		allGuildWarRooms.insert(pair<string, GuildWarRoom*>(room->getId(), room));
		//加入到空闲房间容器
		idleGuildWarRooms.push_back(room);
	}
//	isInGuildWarTime = false; //set to true for test benliao 20121126
#if defined(NORMAL_VESION_FOR_GUILD_WAR)
	isInGuildWarTime = false;
#else
	isInGuildWarTime = true;
#endif
}

//帮主占领帮战房间主帮位置
int GuildWarAsist::hostHoldGuildWarRoom(Hero *manager, int mode, char* password)
{
#if defined(NORMAL_VESION_FOR_GUILD_WAR)
	if (!isInGuildWarTime)
	{
		//不在帮战房间时间
		return 5;
	}
#endif
#if 0
	if (!manager->canJoinGuildWar())
	{
		//玩家今天已经参加过帮派战
		return 7;
	}
#endif

	if (strlen(manager->memHero->wagonId) != 0)
	{
		//玩家在拉马车中，不能进入
		return 6;
	}
	if(idleGuildWarRooms.size() == 0)
	{
		//没有空闲房间资源
		return 1;
	}
	
	if (manager->isInGuildWarRoom())
	{
		//玩家已经在帮战房间中了，不能再创建进入房间
		return 2;
	}
	
	
	if (mode == 1 && (password == NULL || strlen(password) == 0))
	{
		//选择约战要设房间保护密码
		return 4;
	}
	
	int title = manager->getGuildTitle();
	if (title != 0 && title != 1)
	{
		//只有帮主能占领房间
		return 3;
	}
	
	Guild *guild = getGuildWithName(manager->getGuildName());
	if (guild == NULL)
	{
		return 8;
	}
	if (guild->isInGuildWarRoom())
	{
		return 9;
	}
	
	//所在帮派还没有参加帮战
	guild->setJoinGuildWar(true);
	
	GuildWarRoom *room = idleGuildWarRooms.back();
	idleGuildWarRooms.pop_back();

	//更新房间状态
	room->setRoomState(GWR_ONE);
	//房主占领房间
	
	//cout<<"BisonTest cout<<!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	room->holdRoom(manager);
	
	//cout<<"BisonTest cout<<^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
	if (mode == 1)
	{
		//约战模式
		room->lockRoom(password);
		room->startLockTimer();
	}
	//cout<<"BisonTest cout<<$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
	return 0;
}

//帮主占领帮战房间客帮位置
int GuildWarAsist::guestHoldGuildWarRoom(Hero *manager, char* roomId, char* password)
{
#if defined(NORMAL_VESION_FOR_GUILD_WAR)
	if (!isInGuildWarTime)
	{
		//不在帮战房间时间
		return 6;
	}
#endif	
#if 0	
	if (!manager->canJoinGuildWar())
	{
		//玩家今天已经参加过帮派战
		return 8;
	}
#endif
	if (strlen(manager->memHero->wagonId) != 0)
	{
		//玩家在拉马车中，不能进入
		return 7;
	}
	int title = manager->getGuildTitle();
	if (title != 0 && title != 1)
	{
		//只有帮主能占领房间
		return 1;
	}
	
	if (manager->isInGuildWarRoom())
	{
		//该帮主已经在一个帮战房间中了
		return 2;
	}
	
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//没有该房间Id对应的房间
		return 3;
	}
	
	GuildWarRoom *room;
	room = it->second;
	
	unsigned roomState = room->getRoomState();
	if (!(roomState & GWR_ONE))
	{
		//房间中未加入其他帮派，无法挑战
		return 12;
	}
	
	if (roomState & GWR_TWO)
	{
		//房间已经被两个帮派占领
		return 4;
	}
	
	if ((roomState & GWR_LOCK) && ( (password == NULL || strlen(password) == 0) || !room->isPassOK(password)))
	{
		//输入的房间密码不正确
		return 5;
	}
	
	Guild *guild = getGuildWithName(manager->getGuildName());
	if (guild == NULL)
	{
		//玩家的帮派不存在
		return 10;
	}
	if (guild->isInGuildWarRoom())
	{
		//玩家的帮派正在参加帮战中
		return 11;
	}
	
	//更新房间状态
	room->setRoomState(GWR_TWO);
	//房客占领房间
	int ret = room->holdRoom(manager);
	if (ret != 0)
	{
		//不能挑战自己帮派
		return 9;
	}
	
	//所在帮派还没有参加帮战
	guild->setJoinGuildWar(true);
	
	//设置hero已经在帮战房间
	manager->setInGuildWarRoom(true, room->getId());
	
	
	//房间开始召唤帮众
	return 0;
}

//帮众进入帮战房间
int GuildWarAsist::JoinGuildWar(Hero *hero, char* roomId)
{
	int title = hero->getGuildTitle();
	if (title == -1)
	{
		//没有帮派的人
		return 1;
	}

#if 0	
	if (!hero->canJoinGuildWar())
	{
		//玩家今天已经参加过帮派战
		return 5;
	}
#endif

	if (strlen(hero->memHero->wagonId) != 0)
	{
		//玩家在拉马车中，不能进入
		return 4;
	}
	
	if (hero->isInGuildWarRoom())
	{
		//该玩家已经在帮战房间中
		return 2;
	}
	
	Guild *guild = getGuildWithName(hero->getGuildName());
	if (guild == NULL)
	{
		//玩家的帮派已经不存在或者玩家未加入帮派
		return 6;
	}
	if (!guild->isInGuildWarRoom())
	{
		//玩家的帮派没有正在参战
		return 7;
	}
	
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//没有该房间Id对应的房间
		return 3;
	}
	
	GuildWarRoom *room;
	room = it->second;
	
	//0是成功，-1玩家所在帮派未占领该房间
	return room->joinRoom(hero);
}

//帮派战伤害统计
int GuildWarAsist::hurtCount(Hero *hero, int value)
{
	if (!hero->isInGuildWarRoom())
	{
		return 1;
	}
	
	string roomId = hero->getGuildWarRoomId();
	
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//没有该房间Id对应的房间
		return 2;
	}
	
	GuildWarRoom *room;
	room = it->second;
	
	room->guildWarAddHurtCount(hero, value);
	return 0;
}

//杀人数统计
int GuildWarAsist::killCount(Hero *hero)
{
	if (!hero->isInGuildWarRoom())
	{
		return 1;
	}
	
	string roomId = hero->getGuildWarRoomId();
	
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//没有该房间Id对应的房间
		return 2;
	}
	
	GuildWarRoom *room;
	room = it->second;
	room->guildWarAddOneHeroKillNum(hero);
	return 0;
}

//查看帮战房间状态
int GuildWarAsist::viewRoomState(Hero *hero, char* result)
{
	// char* viewResult;
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.begin();
	
	//房间数
	// viewResult += intTostring(isInGuildWarTime);
	// viewResult += intTostring(allGuildWarRooms.size());
	sprintf(result + strlen(result), ",%d,%d", isInGuildWarTime, (int)(allGuildWarRooms.size()));
	//逐个遍历房间状态
	for (it; it != allGuildWarRooms.end(); it++)
	{
		GuildWarRoom* room;
		room = it->second;
		int state = room->getRoomState();
		
		int remain = 0;
		if (state & GWR_LOCK)
		{
			remain = room->getRemainTime();
		}
		// viewResult += "," + room->getId();
		//remain为0表明房间未上锁
		// viewResult += intTostring(remain);
		sprintf(result + strlen(result), ",%s,%d", room->getId(), remain);
		for (int i = 0; i < 2; i++)
		{
			Hero *hero = room->getHost(i);
			if (hero != NULL)
			{
				sprintf(result + strlen(result), ",%s", hero->getGuildName());
				// viewResult += "," + hero->getGuildName();
			} else {
				// viewResult += ",";
				sprintf(result + strlen(result), ",");
			}
		}
	}
	
	return 0;
}

//召唤加入
void GuildWarAsist::callJoinWar(Hero *hero)
{
	if (!hero->isInGuildWarRoom())
	{
		return;
	}
	
	// if (hero->getGuildTitle() != 0)
	// {
		//不是帮主，不能召唤，这里有待斟酌--如果房间主人不是帮主本人
		// return;
	// }
	
	char* roomId = hero->getGuildWarRoomId();
	
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//没有该房间Id对应的房间
		return;
	}
	
	GuildWarRoom *room;
	room = it->second;
	
	room->callJoin(hero);
}

//房主准备
int GuildWarAsist::managerPrepare( Hero *hero)
{
	if (!hero->isInGuildWarRoom())
	{
		return 1;
	}
	
	// if (hero->getGuildTitle() != 0)
	// {
		//不是帮主，不能创建，这里有待斟酌--如果房间主人不是帮主本人
		// return 2;
	// }
	
	char* roomId = hero->getGuildWarRoomId();
	
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//没有该房间Id对应的房间
		cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
		cout<<"BisonWarn: you record the wrong guildWarRoom Id"<<endl;
		cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
		return 3;
	}
	
	GuildWarRoom *room;
	room = it->second;
	
	room->prepareGuildWar(hero);
}

//帮派战退出
void GuildWarAsist::exitGuildWar(Hero *hero, bool offlineFlag)
{
	if (!hero->isInGuildWarRoom())
	{
		return;
	}
	
	char* roomId = hero->getGuildWarRoomId();
	
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//没有该房间Id对应的房间
		return;
	}
	
	GuildWarRoom *room;
	room = it->second;
	//不是因为下线的退出
	room->exit(hero, offlineFlag);
	hero->setInGuildWarRoom(false, NULL);
}

//释放一个房间资源
void GuildWarAsist::freeOneRoom(GuildWarRoom *room)
{
	room->resetRoom();
	idleGuildWarRooms.push_back(room);
}

//设置是否在帮战时间
void GuildWarAsist::setIsInGuildWarTime(bool start)
{
	isInGuildWarTime = start;
}
//查看是否在帮派战房间中
bool GuildWarAsist::getIsInGuildWarTime()
{
	return isInGuildWarTime;
}

//查看玩家所在帮派战房间的状态
int GuildWarAsist::getOneRoomState(Hero* hero)
{
	char* roomId = hero->getGuildWarRoomId();
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//没有该房间Id对应的房间
		return 0;
	}
	
	GuildWarRoom *room;
	room = it->second;
	return room->getRoomState();
}

int GuildWarAsist::guildWarRevival(Hero* hero)
{
	
	char* roomId = hero->getGuildWarRoomId();
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//没有该房间Id对应的房间
		return 1;
	}
	
	GuildWarRoom *room;
	room = it->second;
	int ret = room->revival(hero);
	return ret;
}

//是否可以采集大旗
/**
 * 采旗失败原因
	1:不在帮派战房间中
	2:不在帮战房间时间
	3:玩家所在帮战房间不存在
	4:帮战未到开始状态
	-1:采集物品类型不为帮战旗
	-2:旗帜正在被采集中
	-3:旗帜已经被占据
	-4:旗帜已被自己帮派采集
	-5:主旗需在两副旗被占据后可采
 */
int GuildWarAsist::isHeroPickFlagOk(Hero *hero, int type)
{
	//帮派战夺旗
	if(!hero->isInGuildWarRoom())
	{
		//不在帮派战房间中不能采集帮派旗
		return 1;
	}

	if (!isInGuildWarTime)
	{
		//不在帮战房间时间
		return 2;
	}
	
	char* roomId = hero->getGuildWarRoomId();
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//没有该房间Id对应的房间
		return 3;
	}
	
	GuildWarRoom *room;
	room = it->second;
	int roomState = room->getRoomState();
	if (!(roomState & GWR_START))
	{
		return 4;
	}
	
	int ret = room->isPickFlagOk(hero, type);
	return ret;
	
}

//采旗
int GuildWarAsist::finishPickFlag(Hero *hero, int type)
{
	//帮派战夺旗
	if(!hero->isInGuildWarRoom())
	{
		//不在帮派战房间中不能采集帮派旗
		return 1;
	}

	if (!isInGuildWarTime)
	{
		//不在帮战房间时间
		return 2;
	}
	
	char* roomId = hero->getGuildWarRoomId();
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//没有该房间Id对应的房间
		return 3;
	}
	
	GuildWarRoom *room;
	room = it->second;
	
	int ret = room->finishPickFlag(hero, type);
	return ret;
}

//停止采旗
int GuildWarAsist::stopPickFlag(Hero *hero, int type)
{
	//帮派战夺旗
	if(!hero->isInGuildWarRoom())
	{
		//不在帮派战房间中不能采集帮派旗
		return 1;
	}
	
	
	char* roomId = hero->getGuildWarRoomId();
	map<string, GuildWarRoom*>::iterator it;
	it = allGuildWarRooms.find(roomId);
	if (it == allGuildWarRooms.end())
	{
		//没有该房间Id对应的房间
		return 2;
	}
	
	GuildWarRoom *room;
	room = it->second;
	int ret = room->stopPickFlag(type);
	return ret;
}
