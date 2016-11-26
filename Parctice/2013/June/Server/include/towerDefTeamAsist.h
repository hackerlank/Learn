#ifndef TOWER_DEF_TEAM_ASIST_H
#define TOWER_DEF_TEAM_ASIST_H

// class Hero;
// class TowerTeam;

/**
函数参数；初始化队伍信息 max_rooms为初始化房间的数目；
函数作用：创建塔防副本队伍；
*/ 
// bool initTowerDefRoom(int max_rooms);


/**
函数参数；hero 创建塔防副本队伍的角色实例，ret为返回失败的原因；
  返回值：int -1 hero为空；
			  -2 创建失败，new失败；
			   0 成功；
函数作用：创建塔防副本队伍；
*/
// TowerTeam* TowerDefTeamCreat(Hero* hero,int & ret);


/**
函数参数；teamId 解散队伍的Id；
  返回值：int -1 teamId为空；
			  -2 解散的队伍不存在；
			  -3 实例为空；
			  -4 不是队长，不能解散；
函数作用：解散塔防副本队伍；
*/
// int delTowerDefTeam(string teamId,string teamLeaderId);


/**
函数参数；hero 获取塔防副本队伍的成员信息角色实例；
  返回值：string 字符串信息；
函数作用：获取塔防副本队伍的成员信息；
*/
// string gainTowerDefTeamMemInfo(Hero*  hero);


/**
函数参数；hero 获取塔防副本队伍申请成员信息角色实例；
  返回值：string 字符串信息；
函数作用：获取塔防副本队伍申请成员信息；
*/
// string gainTowerDefTeamAppMemInfo(Hero*  hero);


/**
函数参数；towerDefTeam 塔防队伍的实例指针；
		  hero 将要加入到队伍的角色实例；
  返回值：int -1 towerDefTeam或者hero位空；
			  -2 已经存在，错误返回；
			   0 成功；
函数作用：添加角色实例到塔防副本队伍实例；
*/
// int add2TowerDefTeam(TowerTeam* towerDefTeam,Hero* hero);


/**
函数参数；teamLeader 塔防队伍的实例指针；
		  Addhero 将要加入到队伍的角色实例；
		  isRefuse 是否拒绝；
  返回值：int -1 towerDefTeam或者hero位空；
函数作用：添加角色实例到塔防副本队伍实例；
*/
// int addAppMem2Team(Hero* teamLeader,Hero* Addhero,int isRefuse);


/**
函数参数；towerDefId 将要添加到塔防副本队伍的实例ID；
		  hero 将要加入到队伍申请列表的角色实例；
		  leader 队长实例；
  返回值：int -1 towerDefId或者hero位空；
			  -2 towerDefId找不到实例；
			  -3  获取到得塔防副本实例为空；

函数作用：添加角色实例到塔防副本队伍实例；
*/
// int add2TowerDefAppTeam(string towerDefId,Hero* hero);



/**
函数参数；towerDefId 队伍的实例ID；
		  heroId 将要选择位置的的实例ID；
		  leader 队长ID（只有队长可以设置位置）
		  index 将要加入到队伍的位置下标；
  返回值：int -1 towerDefId或者hero位空；
函数作用：设置塔防副本队伍角色的位置；
*/
// int setTowerDefLocation(string towerDefId,string heroId,string leader,int index,string ret_locationInfo);


/**
函数参数；towerDefTeam 将要设置的塔防难度的实例指针；
  返回值：int -1 towerDefTeam为空；
函数作用：设置塔防队伍难度；
*/
// int setTowerDefHardLevel(string towerDefId,string heroId,int level);


/**
函数参数；towerDefId 塔防队伍的实例ID；
		  heroId 将要退出的实例ID；
  返回值：int -1 hero为空；
			  -2 塔防队伍Id为空；
			  -3 没有实例，找不到塔防队伍实例；
			  -4 塔防实例指针为空；
			   0 成功；
函数作用：退出塔防队伍；
*/
// int exitFromTowerDefTeam(Hero* hero);
void exitFromTowerDefence(Hero* hero);


/**
函数参数；void
  返回值：string 信息的值（eg:,size,teamId,LeaderheroName,Leaderlevel,leaderCamp,leaderParty,TeamCounts,TeamHardLevel）
函数作用：获取所有的塔防队伍信息；
*/
// string gain_AllTowerDefTeam_Info();



/**
函数参数；towerDefTeam 将要塔防队伍的信息；
  返回值：string 信息的值（eg:,size,teamId,LeaderheroName,Leaderlevel,leaderCamp,leaderParty,TeamCounts,TeamHardLevel）
函数作用：获取所有的塔防队伍信息；
*/
// string gain_TowerDefTeamInfo(TowerTeam* towerDefTeam);



/**
函数参数；src_Leader原队长实例，dst_Leader将要上任的队长实例；
  返回值：int 
函数作用：转让队长；
*/
// int setTowerDefTeamLeader(Hero* src_Leader,Hero* dst_Leader);


/**
函数参数；src_Leader队长实例，dst_Leader将要设置位置的实例；
  返回值：int 
函数作用：设置队员位置；
*/
// int setTowerDefTeamPosition(Hero* src_Leader,Hero* dst_Leader,int area);


/**
函数参数；towerDefTeamt塔防队伍实例；
		  msg2send将要发送的消息；
  返回值：void
函数作用：给塔防队伍成员发送消息；
*/
// void SendMsg_2_TowerDefTeam(TowerTeam* towerDefTeam,string msg2send);


/**
函数参数；src_Leader队长实例，dst_Member将要被剔除实例；
  返回值：int 
函数作用：队长剔除队员；
*/
// int excludingTeamMem(Hero* src_Leader,Hero* dst_Member);


/**
函数参数；src_Leader队长实例，将要进入的塔防副本的难度系数（0普通，1英雄，2江湖）；
  返回值：int 
函数作用：进入塔防副本开始游戏；
*/
// int enterTowerDefRoom(Hero* src_Leader,int hardLeve);

int enterTowerDefRoom(Hero* src_Leader, char* inst_typeId);
/**
函数参数；towerDefTeamt塔防队伍实例；
  返回值：void 
函数作用：队伍退出塔防副本游戏；
*/
// void TowerDefWarEnd(TowerTeam* towerDefTeam,int ret);

/*
函数参数；src_Leader：队长； team：队伍实例
  返回值：bool 
函数作用：检测队员是否在队长周围
*/
bool isAround(Hero* src_Leader, Team* team);
#endif
