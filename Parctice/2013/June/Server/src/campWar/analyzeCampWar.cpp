/*
		文件名字： analyzeCampWar.cpp
			创建： xhm
		    时间:  2012.8.10
			作用:  解析客户短发送过来的数据命令,
	               阵营战分为三类，普通阵营战，统领阵营战，盟主阵营战；
*/
#include "analyzeCampWar.h"

#include "map_src.h"
#include"wholeDefine.h"
#include "campWarManagement.h"

#define CAMP_WAR_TYPE_ERROR 1000//阵营战类型错误，返回给客户端；
#define CAMP_WAR_MAX_MSG_SIZE 400

static 	char MyallPre[51200];
static 	char ret_campWarInfo[CAMP_WAR_MAX_MSG_SIZE];//信息返回通用数组；  

extern int sock_fd;
extern int g_msg_len;
extern Hero* pg_hero;
extern MapType_T mapTypeInfo;//某些特殊地图的ID；
extern map<int, Role*> fd_to_pRole;
extern map<string, Hero*> heroId_to_pHero;
extern campWarManagement campWarController;//阵营战管理实例；
extern map<string,Map_Src*>mapId_connect_map;

/*********************************************************************
	参数：char* buffers	客户端发送需要解析的字符串；
	说明：该函数解析客户端发送过来申请加入阵营数据。
		  格式：信息头，英雄Id，阵营战类型；
		  函数将服务器返回给客户端的数据存储在ret_campWarInfo中；
**********************************************************************/
void 
enterCampWar(char* buffers)
{
	int retType; 
	int remainTime=0;           
	string roomStatus;

	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR(char* hero_id);
	MSG_CHAR(char* campWarType);
	MSG_CHAR_END(char* roomNum);
	
	/*根据阵营战类型，选择加入不同的阵营战.*/
	int type=atoi(campWarType);
	switch(type)
	{
	case 1:
	/*    		-1: 该英雄id不存在；
				-2: 表示阵营战已饱和，达到最大允许人数；
				-3：表示插入insert失败；
				-4:	英雄实例的阵营不属于系统三个阵营之内；
				-5: 英雄ID等级小于30级；
				-6: 表示该阵营战人数已满或者未激活；
				-7: 阵营战偏移量选择房间数不在系统默认范围内；
				-8: 地图信息找不到；
				-9: 删除时，在此次阵营战中，在其阵营队列中找不到；
				-10:表示加入的时间不在活动的时间；
				 0:表示加入成功；	
	*/
	    retType = campWarController.add2OrdinaryCampWar(hero_id,atoi(roomNum));//添加到普通阵营战中；
		roomStatus=campWarController.getOrdinaryCampWarStatus();
		remainTime = campWarController.getOrdinaryCampWarOverTime();
		break;
	case 2:		
			/*argument hero 英雄实例指针；
			return int -1：实例指针为空；
					-2：表示实例指针对应对象的帮派名字不是当前作战的帮派名字；
					-3：表示insert失败，已经参加过，不能参加；
					-4: 表示阵营类型不是系统默认类型；
					-5: 表示找不到地图；
					-6: 表示时间不是对战时间；
					0：表示成功；
					*/
		retType = campWarController.add2LeaderCampWar(hero_id);
		roomStatus=campWarController.getLeaderCampWarStatus();
		remainTime = campWarController.LeaderCampWarPeaceTime();
		break;
	case 3:	//添加到盟主争夺阵营战中；
		/*
		argument hero 英雄id;
		return int -1 hero为空；
			 -2 帮派名字不是当前盟主战的帮派；
			 -3 insert失败，已经参加过比赛；
			 -4 阵营类型不是系统默认三种类型；
			 -5 找不到地图的实例指针；
			 -6: 表示时间不是对战时间；
			  0 加入成功；
		*/
		retType = campWarController.add2ChiefCampWar(hero_id);
		roomStatus=campWarController.getChiefCampWarStatus();
		remainTime = campWarController.ChiefCampWarPeaceTime();
		break;
	default:
		retType=CAMP_WAR_TYPE_ERROR;//阵营战类型错误返回给客户端；
		break;
	}
	
	/*给客户端发送申请加入阵营战的服务器返回信息.*/
	if(retType!=0)
		sprintf(ret_campWarInfo,"11,0,%d,%d%s,%d",type,retType,roomStatus.c_str(),remainTime);
	else{
		sprintf(ret_campWarInfo,"11,0,%d,%d,%d",type,retType,remainTime);
	}
	send_msg(pg_hero->getFd(),ret_campWarInfo);	
	
}



/*******************************************************************
	参数：char* buffers	客户端发送需要解析的字符串；
	说明：该函数解析客户端发送过来申请退出阵营数据。
		  格式：信息头，英雄Id；
		  函数将服务器返回给客户端的数据存储在ret_exitCampWarInfo中；
********************************************************************/
void 
exitCampWar(char* buffers)
{
	int retType;
	int campWarType;
	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR_END(char* hero_id);
	
	CampData_T campWardata= pg_hero->getCampWarData();
	
	/*根据阵营战类型，选择加入不同的阵营战.*/
	campWarType=campWardata.campWarType;
	switch(campWarType)
	{
	case 1:								
		/*    
		  -1:该英雄id不存在；
		  -2:英雄ID等级小于30级；
		  -3:表示加入者的阵营人数已达到上限；
		  -4：表示加入insert函数失败；
		  -5：表示该heroId没有加入阵营；
		  -6:表示该阵营战正在进行或者已经结束；
		   0：表示加入成功；		  
		*/
	    retType = campWarController.exitFromOrdinayCampWar(hero_id,campWardata.campWarRoomNum);		
		break;
	case 2:															
		retType = campWarController.exitFromLeaderCampWar(hero_id);	
		break;
	case 3:														
		retType = campWarController.exitFromChiefCampWar(hero_id);	
		break;
	default:
		retType=CAMP_WAR_TYPE_ERROR;  										//阵营战类型错误返回给客户端；
		break;
	}
	/*给客户端发送申请加入阵营战的服务器返回信息.*/
	sprintf(ret_campWarInfo,"11,1,%d,%d",campWarType,retType);
	
	send_msg(pg_hero->getFd(),ret_campWarInfo);
}



/********************************************************************
	参数：char* buffers	客户端发送需要解析的字符串；
	说明：该函数解析客户端发送过来申请战斗类型的数据。
		  格式：信息头，英雄Id，阵营战类型；
		  函数将服务器返回给客户端的数据存储在ret_enterCampWarInfo中；
*********************************************************************/

void 
applyCampWar(char* buffers)
{
	int retType;
	int fd=sock_fd;       
	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR(char*hero_id);
	MSG_CHAR_END(char*campWarType);
	
	/*根据阵营战类型，选择退出不同的阵营战.*/
	int type=atoi(campWarType);
	switch(type)
	{
	case 2:
		retType = campWarController.applyLeaderCampWar(hero_id); 
		break;		
	default:
		retType=CAMP_WAR_TYPE_ERROR;  						//阵营战类型错误返回给客户端；
		break;
	}
	
	sprintf(ret_campWarInfo,"11,3,%d,%d",type,retType);
	// cout<<"[XHM TEST] applyCampWar(campWar.cpp) ret:"<<ret_campWarInfo<<endl;
	
	send_msg(fd,ret_campWarInfo);	
}


/********************************************************************
	参数：char* buffers	客户端发送需要解析的字符串；
	说明：该函数解析客户端发送过来申请战斗类型的数据。
		  格式：信息头，英雄Id，阵营战类型；
		  函数将服务器返回给客户端的数据存储在ret_countsCampWarInfo中；
		  获取相对应的阵营战的房间人数；每种阵营的人数；
		  一个房间有三个数据，分别表示支派，宗教，游侠人数；
**********************************************************************/
void 
getCampWarCounts(char* buffers)
{
	int fd=sock_fd;                  
	string warCounts;
	char* hero_id;
	char* campWarType;
	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR(hero_id);
	MSG_CHAR_END(campWarType);
	
	/*根据阵营战类型，获取不同信息.*/
	int type=atoi(campWarType);
	switch(type)
	{
	case 1:
		warCounts = campWarController.getOrdinaryCampWarStatus();//获取普通阵营战类型房间数据；
		break;
	case 2:
		warCounts = campWarController.getLeaderCampWarStatus();//获取统领阵营战类型房间数据；
		break;
	case 3:
		warCounts = campWarController.getChiefCampWarStatus();
		break;
	default:
		warCounts.insert(0,"");//阵营战类型错误返回给客户端；
		break;
	}
	
	sprintf(ret_campWarInfo,"11,2,%d%s",type,warCounts.c_str());

	send_msg(fd,ret_campWarInfo);	
}


/********************************************************************
	参数：char* buffers	客户端发送需要解析的字符串；
	说明：该函数解析客户端发送过来申请战斗类型的数据。
		  格式：信息头，英雄Id，阵营战类型；
		  函数将服务器返回给客户端的数据存储在ret_countsCampWarInfo中；
		  获取相对应的阵营战的房间人数；每种阵营的人数；
		  一个房间有三个数据，分别表示支派，宗教，游侠人数；
**********************************************************************/
void viewCampWarAwards(char* buffers)
{
	int fd=sock_fd;                  
	bool isSucc=false;
	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR(char*hero_id);
	MSG_CHAR_END(char*campWarType);
	
	CampData_T campWardata= pg_hero->getCampWarData();
	
	/*根据阵营战类型，获取不同信息.*/
	int type=campWardata.campWarType;
	switch(type)
	{
	case 1:
		campWarController.viewOrdinaryCampWarAwards(pg_hero,campWardata.campWarRoomNum);
		break;
	case 2:
		campWarController.viewLeaderCampWarAwards(pg_hero);	
		break;
	case 3:
		campWarController.viewChiefCampWarAwards(pg_hero);
		break;
	default:
		return;
	}
}


/**
*领取奖励,消息内容:11,5,HeroId,Type
*/
void receiveWarAwards(char* buffers)
{
	int retType;
	int fd=sock_fd;       
	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR(char*hero_id);
	MSG_CHAR_END(char*campWarType);

	CampData_T campWardata= pg_hero->getCampWarData();
	
	/*根据阵营战类型，选择退出不同的阵营战.*/
	int type=campWardata.campWarType;
	switch(type)
	{
	case 1:
		retType = campWarController.receiveOrdinaryCampWarAwards(pg_hero,campWardata.campWarRoomNum);
		break;
	case 2:
		retType = campWarController.receiveLeaderCampWarAwards(pg_hero); 	
		break;		
	case 3:
		retType = campWarController.receiveChiefCampWarAwards(pg_hero); 
		break;
	default:
		retType = CAMP_WAR_TYPE_ERROR;//阵营战类型错误返回给客户端；
		break;
	}
	
	sprintf(ret_campWarInfo,"11,1,%d,%d",type,retType);//TODO 此消息便于客户端去掉定时器面板，有疑问RTX xhm
	send_msg(fd,ret_campWarInfo);		
	sprintf(ret_campWarInfo,"11,5,%d,%d",type,retType);//此消息便于告诉客户端领取奖励是否成功；
	send_msg(fd,ret_campWarInfo);	
}



/********************************************************************
	参数：char* buffers	客户端发送需要解析的字符串；
	说明：该函数解析客户端发送过来申请复活类型的数据。
		  格式：信息头，英雄Id，阵营战类型；
		        阵营战中，英雄的复活, 11,8 heroId,type(0，安全区复活，1，主城复活)
**********************************************************************/
void heroCampWarRevival(char* buffers)
{
	int retType;
	int fd=sock_fd; 
	int revivalPt=-1;
	
	int	remainTime=0;
	int revival_life;
	int revival_magic;
	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR(char* hero_id);
	MSG_CHAR_END(char* revivalCampWarType);
	
	CampData_T campWardata= pg_hero->getCampWarData();
	
	// cout<<"##############pg_hero->getMap():"<<pg_hero->getMap()->getIdentity()<<endl;			
	
	
	/*根据阵营战类型，选择退出不同的阵营战.*/
	int type=campWardata.campWarType;
	// cout<<"[XHM MSG]type:"<<type<<endl;
	
	switch(type)
	{
	case 1:	
			remainTime = campWarController.getOrdinaryCampWarOverTime();
	break;
	case 2:	
		if(pg_hero->isInCampWar())
			remainTime = campWarController.getOrdinaryCampWarOverTime();	
		else
			remainTime = campWarController.LeaderCampWarPeaceTime();
		revivalPt = campWarController.getRevivalPt(pg_hero);
	break;
	case 3:			//添加到盟主争夺阵营战中；
		if(pg_hero->isInCampWar())
			remainTime = campWarController.getOrdinaryCampWarOverTime();	
		else
			remainTime = campWarController.ChiefCampWarPeaceTime();
	break;
	default:
		remainTime= 0;  										//阵营战类型错误返回给客户端；
		cout<<"[XHM WARNING]:<analyzeCampWar.cpp>heroCampWarRevival::ont in the campWar,and send msg Revival"<<endl;
		return;
	break;
	}
	
	
	revival_life=pg_hero->getLifeUpperVal();
	revival_magic=pg_hero->getMagicUpperVal();
	
	pg_hero->setLifeStation(1);
	pg_hero->setLifeVal(revival_life);
	pg_hero->setMagicVal(revival_magic);
	sprintf(ret_campWarInfo,"7,0,%d,%d",revival_life,revival_magic);	
	send_msg(fd,ret_campWarInfo);
		
	if(revivalCampWarType[0]=='0')//安全区复活；
	{
		Map_Inform *map_now=pg_hero->getMap();
		int len;
		char mapId[20]={0};
		char* PmapId=map_now->getIdentity();
		snprintf(mapId,15,"%s",map_now->getIdentity());
		
	// cout<<"##############[XHM MSG]mapId:"<<mapId<<endl;		
	
		Point targetPt;
		if(revivalPt == -1)
			targetPt=map_now->getCampWarPt(pg_hero->getCamp());
		else
			targetPt=map_now->getCampWarPt(revivalPt);
		
		pg_hero->quit_scene();	
		pg_hero->setMap(map_now);
		pg_hero->setMapId(PmapId);
		pg_hero->setLocation(targetPt);   

		sprintf(ret_campWarInfo,"2,%d,%d,%s,%d,%d,%d,%d,%d",CHANGE_SCENE,SUCCESS,mapId,targetPt._x,targetPt._y,\
														map_now->getWarType(),map_now->getChangePkType(),map_now->getMapType());
		
		send_msg(sock_fd,ret_campWarInfo);
		
		// cout<<"[XHM TEST] (anlyzeCampWar.cpp)The PmapId:"<<PmapId<<" The mapId:"<<mapId<<endl;
		
		if(remainTime < 0)
			remainTime = 0;
			
		sprintf(ret_campWarInfo,"11,9,%d,%d",type,remainTime);
		send_msg(fd,ret_campWarInfo);	
		
	}else if(revivalCampWarType[0]=='1'){//回城复活；
		CampData_T campWardata= pg_hero->getCampWarData();

		/*根据阵营战类型，退出不同的阵营战.*/
		int campWarType=campWardata.campWarType;
		
	// cout<<"##############[XHM MSG]campWarType:"<<campWarType<<endl;
		
		
		switch(campWarType)
		{
		case 1:	//普通阵营战退出；
	       retType = campWarController.exitFromOrdinayCampWar(hero_id,campWardata.campWarRoomNum);		
		break;
		case 2:	//统领争夺阵营战退出；
			retType = campWarController.exitFromLeaderCampWar(hero_id);	
		break;
		case 3:	//盟主争夺阵营战退出；
			retType = campWarController.exitFromChiefCampWar(hero_id);	
		break;
		default://阵营战类型错误返回给客户端；
			retType=CAMP_WAR_TYPE_ERROR; 
		break;
		}
		
		/*给客户端发送申请加入阵营战的服务器返回信息.*/
		sprintf(ret_campWarInfo,"11,1,%d,%d",campWarType,retType);
		send_msg(pg_hero->getFd(),ret_campWarInfo);		
	}else{//未知类型复活；不处理；
		return;
	}
}


/********************************************************************
	参数：char* buffers	客户端发送需要解析的字符串；
	说明：该函数解析客户端发送过来申请时间剩余秒数。
		  格式：信息头，英雄Id，阵营战类型；
**********************************************************************/
void heroCampWarLevalTime(char* buffers)
{
	int fd=sock_fd;                   
	int remainTime=0;
	
	char* hero_id;
	char* campWarType;
	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR_END(hero_id);
	
	CampData_T campWardata= pg_hero->getCampWarData();
	
	/*根据阵营战类型，选择退出不同的阵营战.*/
	int type=campWardata.campWarType;
	switch(type)
	{
	case 1:
		remainTime = campWarController.getOrdinaryCampWarOverTime();
		break;
	case 2:		
		remainTime = campWarController.getLeaderCampWarOverTime(pg_hero->getCamp());
		break;
	case 3:	//添加到盟主争夺阵营战中；
		remainTime = campWarController.getChiefCampWarOverTime();
		break;
	default: //阵营战类型错误返回给客户端；
		remainTime= 0;
		break;
	}

	sprintf(ret_campWarInfo,"11,10,%d,%d",type,remainTime);
	send_msg(fd,ret_campWarInfo);	
}


/*********************************************************************
	参数：char* buffers	客户端发送需要解析的字符串；
	说明：该函数解析客户端发送过来进入阵营边境数据。
		  格式：信息头，英雄Id；
		  函数将服务器返回给客户端的数据存储在ret_applyCampSenceInfo中；
**********************************************************************/
void 
applyCampSence(char* buffers)
{
	int retType;
	int fd=sock_fd;                   
	string nextMapId = mapTypeInfo.campSenceMapId;
	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR_END(char* hero_id);
	
	map<string,Map_Src*>::iterator iter_map = mapId_connect_map.find(nextMapId);
	if(iter_map == mapId_connect_map.end())  //找不到地图实例；
	{
	   cout<<"W[XHM WARNING]::(analyzeCampWar.cpp)::applyCampSence, Can't find the nextMapId:"<<nextMapId<<endl;
	   sprintf(ret_campWarInfo,"2,%d,%d",CHANGE_SCENE,FAILED);
	   send_msg(fd, ret_campWarInfo);
	   return;
	}
	
	Map_Inform *map_next= iter_map->second;
	
	if(pg_hero->getCamp() >2 || pg_hero->getCamp() < 0)
	{
	   cout<<"[XHM WARNING]:(analyzeCampWar.cpp)::applyCampSence,in the analyzeEnterCampSence.cpp heroNot enter camp!"<<endl;
	   sprintf(ret_campWarInfo,"2,%d,4",CHANGE_SCENE);
	   send_msg(fd,ret_campWarInfo);
	   return;
	}
	
	Point targetPt=map_next->getCampWarPt(pg_hero->getCamp());
	
	//cout<<"[XHM TEST] applyCampSence The targetPt_X:"<<targetPt._x<<",targetPt_y:"<<targetPt._y<<endl;
	
	pg_hero->quit_scene();
	pg_hero->setMap(map_next);

	sprintf(ret_campWarInfo,"2,%d,%d,%s,%d,%d,%d,%d,%d",CHANGE_SCENE,SUCCESS,nextMapId.c_str(),targetPt._x,targetPt._y,\
														map_next->getWarType(),map_next->getChangePkType(),map_next->getMapType());	
	send_msg(fd,ret_campWarInfo); 
	
	pg_hero->setLocation(targetPt);	
}


/*********************************************************************
	参数：char* buffers	客户端发送需要解析的字符串；
	说明：该函数解析客户端发送过来退出阵营边境数据。
		  格式：信息头，英雄Id；
		  函数将服务器返回给客户端的数据存储在ret_exitCampSenceInfo中；
**********************************************************************/
void exitCampSence(char * buffers)
{
	int retType=pg_hero->getCampWarType();
	int fd=sock_fd;    
	string nextMapId = mapTypeInfo.mainCityMapId;	
	char ret_exitCampSenceInfo[200]={0};
	
	char* hero_id;
	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR_END(hero_id);
	
	if(retType>0 && retType<4)
	{
		cout<<"[XHM MSG] Exit from the campWar!"<<endl;
		exitCampWar(buffers);//从阵营战场退出到主城；
		return;
	}
	
	if(pg_hero->getCamp() >2 || pg_hero->getCamp() < 0)
	{
	   cout<<"[XHM WARNING]  hero Not enter camp(analyzeEnterCampSence.cpp)!"<<endl;
	   sprintf(ret_campWarInfo,"2,%d,4",CHANGE_SCENE);
	   send_msg(fd, ret_campWarInfo);
	   return;
	}
	
	map<string,Map_Src*>::iterator iter_map = mapId_connect_map.find(nextMapId);
	if(iter_map == mapId_connect_map.end())  
	{
	   cout<<"[XHM WARNING]  can't find the nextMapId(analyzeEnterCampSence.cpp):"<<nextMapId<<endl;
	   sprintf(ret_campWarInfo,"2,%d,%d",CHANGE_SCENE,FAILED);
	   send_msg(fd, ret_campWarInfo);
	   return;
	}
	
	Map_Inform *map_next= iter_map->second;
	Point targetPt=map_next->getEntPt();
	
	pg_hero->quit_scene();
	pg_hero->setMap(map_next);

	sprintf(ret_campWarInfo,"2,%d,%d,%s,%d,%d,%d,%d,%d",CHANGE_SCENE,SUCCESS,nextMapId.c_str(),targetPt._x,targetPt._y,\
														map_next->getWarType(),map_next->getChangePkType(),map_next->getMapType());	
	
	send_msg(fd,ret_campWarInfo); 
	pg_hero->setLocation(targetPt);	
}

/*********************************************************************
	参数：char* buffers	客户端发送需要解析的字符串；
	说明：该函数解析客户端发送过来请求对应阵营帮主的列表数据。
		  格式：信息头，英雄Id；
		  函数将服务器返回给客户端的数据存储在ret_viewCampFactionInfo中；
**********************************************************************/
void viewCampFactionInfo(char * buffers)
{
	int fd=sock_fd;                   
	char* hero_id;
	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR_END(hero_id);
	
	sprintf(MyallPre,"11,12%s",campWarController.viewCampFactionInfo(pg_hero));
	send_msg(fd,MyallPre); 
}



/*********************************************************************
	参数：char* buffers	客户端发送需要解析的字符串；
	说明：该函数解析客户端发送过来请求阵营数据。
		  格式：信息头，英雄Id；
		  函数将服务器返回给客户端的数据存储在ret_viewCampInfo中；
**********************************************************************/
void viewCampInfo(char * buffers)
{							
	int fd=sock_fd;                   
	char* hero_id;
	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR_END(hero_id);
	
	sprintf(MyallPre,"11,13%s",campWarController.viewCampInfo(pg_hero));
	send_msg(fd,MyallPre); 
}


/*********************************************************************
	参数：char* buffers	客户端发送需要解析的字符串；
	说明：该函数解析客户端发送过来设置阵营公告数据。
		  格式：信息头，英雄Id；
		  函数将服务器返回给客户端的数据存储在ret_setBroadcastCampInfo中；
**********************************************************************/
void 
setCampBroadcast(char*buffers)
{
	int fd=sock_fd;                   
	
	char* hero_id;
	char* broadcastCampInfo;
	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR(hero_id);
	MSG_CHAR_END(broadcastCampInfo);

	int ret = campWarController.setCampBroadcast(pg_hero,broadcastCampInfo);
	sprintf(ret_campWarInfo,"11,14,%d",ret);
	send_msg(fd,ret_campWarInfo); 
}


//任命或者撤职副统领；
void 
setCampViceLeader(char*buffers)
{
	int fd=sock_fd;                   
	int operateType;
	int ret_type=1;
	
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR(char* type);
	MSG_CHAR(char* hero_id);
	MSG_CHAR(char* viceLeaderId);	
	MSG_CHAR_END(char* viceLeaderName);	
	
	// cout<<"[XHM TEST] setCampViceLeader type(analyzeCampWar.cpp):"<<type<<endl;
	// cout<<"[XHM TEST] setCampViceLeader hero_id(analyzeCampWar.cpp):"<<hero_id<<endl;
	// cout<<"[XHM TEST] setCampViceLeader viceLeaderId(analyzeCampWar.cpp):"<<viceLeaderId<<endl;
	// cout<<"[XHM TEST] setCampViceLeader viceLeaderName(analyzeCampWar.cpp):"<<viceLeaderName<<endl;
	
	operateType=atoi(type);
	switch(operateType)
	{
		case 0:
			ret_type = campWarController.setViceLeaderName(pg_hero,viceLeaderName,viceLeaderId);
			break;
			
		case 1:
			ret_type = campWarController.cancelViceLeaderName(pg_hero,viceLeaderName,viceLeaderId);
			break;

		default:
			break;
	}
	
	sprintf(ret_campWarInfo,"11,15,%d,%d",operateType,ret_type);
	
	send_msg(fd,ret_campWarInfo); 
}

//获取报名信息；
void 
getLeaderCampWarAppInfo(char*buffers)
{
	int fd=sock_fd;    
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_INT(int type);

	char * msg =  campWarController.get_apply_camp_war_info(type);
	// cout<<"[XHM TEST] get_apply_camp_war_info the msg:"<<msg<<endl;
	send_msg(fd,msg);
}

void 
getLeaderWarAppLastTime(char*buffers)
{
	int fd=sock_fd;
	int isGuidLeader=0;
	MSG_BEGIN(buffers, g_msg_len);	
	MSG_CHAR_END(char* viceLeaderName);	
	char msg[50]={0};
	
	Guild*	guild = pg_hero->getGuild();
	if(NULL != guild)
	{
		string heroId = pg_hero->getIdentity();			
		if(guild->getPresidId()==heroId || guild->getVicePresidId()==heroId)//判断是不是帮主和副帮主报名,返回	
			isGuidLeader = 1;
	}
	
	snprintf(msg,50,"11,27,%d,%d",campWarController.CampWarApplyLastTime(),isGuidLeader);
	cout<<"[XHM TEST] getLeaderWarAppLastTime the msg:"<<msg<<endl;
	send_msg(fd,msg);
}


void viewCampResWarInforComm(char *buffer)
{
	char msg[1024] = {0};
	sprintf(msg, "32,0,1,%d", ROOM_OF_CAMP_RES_WAR);
	int ret = campWarController.getCampResWarStatus(pg_hero, msg + strlen(msg));
	if (ret != 0)
	{
		memset(msg, 0, sizeof msg);
		sprintf(msg, "32,0,0,%d", ret);
	}
	
	send_msg(pg_hero->getFd(), msg);
}

void entCampResWarComm(char* buffer)
{
	int roomIndex;
	char msg[64] = {0};
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(roomIndex);
	int ret = campWarController.entCampResWar(pg_hero, roomIndex);
	if (ret != 0)
	{
		sprintf(msg, "32,1,%d", ret);
		send_msg(pg_hero->getFd(), msg);
		if (ret == -2 || ret == -3)
		{
			viewCampResWarInforComm(NULL);
		}
	}
}

void exitCampResWarComm(char* buffer)
{
	char msg[1024] = {0};
	sprintf(msg, "32,2");
	int ret = campWarController.exitCampResWar(pg_hero);
	if (ret != 0)
	{
		sprintf(msg + strlen(msg), ",%d", ret);
		send_msg(pg_hero->getFd(), msg);
	}
}

void campResWarViewHeroResNumComm(char* buffer)
{
	char *heroId;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR(heroId);
	int ret = campWarController.viewHeroResNum(pg_hero, heroId);
	char viewMsg[64] = {0};
	if (ret != 0)
	{
		sprintf(viewMsg, "32,9,0,%d", ret);
		send_msg(pg_hero->getFd(), viewMsg);
	}
}


void getCampResWarComm(char* buffer)
{
	char msg[64] = {0};
	int ret = campWarController.getCampResWarReward(pg_hero);
	if (ret != 0)
	{
		sprintf(msg, "32,10,0,%d", ret);
	} else {
		sprintf(msg, "32,10,1");
	}
	
	send_msg(pg_hero->getFd(), msg);
}