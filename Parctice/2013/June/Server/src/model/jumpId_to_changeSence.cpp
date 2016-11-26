/*
		file name： jumpId_to_changeSence.cpp
		author：    xhm
		created:    2012.7.19
	    directions: Analyze the information sended from the client,
	                Target MapId are divided into Tower defense scene and Ordinary scene,
				    Through the jumpID information,Find the target mapId;
*/

#include <string>
#include "hero.h"
#include"cpyLimit.h"
#include "map_inform.h"
#include"cpyAsist.h"
#include "jumpId_to_changeSence.h"
#include"cpy_series_command_function.h"
#include"command_other_function_all_over.h"

#define MAX_RANGE 1000   
#define MAX_MSG_SIZE 150 

extern int sock_fd;
extern int g_msg_len;
extern Hero* pg_hero;

extern int sock_fd;
extern map<string, Hero*> heroId_to_pHero;
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern map<string,Map_Inform*> mapId_connect_map;

void 
jumpid_to_change_sence(char *buffer){

    /*Analyze the information sended from the client,
	  And will be sent to the client data is saved to msg_body;
    */
	int fd=sock_fd;                  												 /*unclear;*/
	string nextMapId;               												/*Target mapId;*/
	Hero* msgSender=NULL;        
	char msg_body[MAX_MSG_SIZE]={0};
	
	
	MSG_BEGIN(buffer, g_msg_len);	
	MSG_CHAR(char* hero_id);
	MSG_CHAR_END(char* jumpId);
	
	msgSender=pg_hero;
	if(NULL == msgSender)
	{
		sprintf(msg_body,"2,%d,%d",CHANGE_SCENE,FAILED);
	    send_msg(fd, msg_body);
		return;
	}

	/*
	Through the jumpID information,Find the target mapId;
	Target MapId are divided into Tower defense scene and Ordinary scene;
	*/
	Map_Inform *map_now;
	map_now = msgSender->getMap();            															/*gain the current mapId information;*/
	map<string,const jumpId_infor*> jumpId_connect_jumpInfo = map_now->getJumpId_connect_jumpInfo();   /*we gain the current map  map<string,const jumpId_infor*> map;*/
	map<string,const jumpId_infor*>::iterator iter = jumpId_connect_jumpInfo.find(jumpId);      	   /*Verification jumpId is or not exit;*/
	if(iter == jumpId_connect_jumpInfo.end()) 
	{
		cout<<"in the jumpId_to_changesence.cpp "<<endl;
		cout<<"in the mapId:"<<map_now->getIdentity()<<"can't find the skipId:"<<jumpId<<endl;
		sprintf(msg_body,"2,%d,%d",CHANGE_SCENE,FAILED);
	    send_msg(fd, msg_body);
		return;
	}
	
	nextMapId=iter->second->mapId;                               /*Target mapId;*/
	
	/*副本跳转，调用副本退出函数*/
	if(map_now->getFlgCpy() && (*nextMapId.c_str()) == 'm')
	{
		cout<<"jumpId:"<<jumpId<<endl;
		outCpy(msgSender);
		return;
	}
	
	/*level Limit*/
	if(msgSender->getGradeNow() < iter->second->levelLowerLimit)
	{
	   cout<<"in the jumpId_to_changesence.cpp skipID"<<jumpId<<"Hero level is levelLowerLimit "<<iter->second->levelLowerLimit<<"!********"<<endl;
	   sprintf(msg_body,"2,%d,2,%d",CHANGE_SCENE,iter->second->levelLowerLimit);
	   send_msg(fd, msg_body);
	   return;
	}
	
	if(msgSender->getGradeNow() > iter->second->levelUpperLimit)
	{
	   cout<<"the msgSender->getGradeNow():"<<msgSender->getGradeNow()<<"iter->second->levelUpperLimit:"<<iter->second->levelUpperLimit<<endl;
	   cout<<"in the jumpId_to_changesence.cpp Hero level is levelUpperLimit!"<<endl;
	   sprintf(msg_body,"2,%d,3,%d",CHANGE_SCENE,iter->second->levelUpperLimit);
	   send_msg(fd, msg_body);
	   return;
	}
	
	if((msgSender->getCamp() < 0 || msgSender->getCamp() > 2) && iter->second->campEntFlag)
	{
	   cout<<"in the jumpId_to_changesence.cpp Hero level is campEntFlag!"<<endl;
	   cout<<"in the mapId:"<<map_now->getIdentity()<<" the skipId:"<<jumpId<<endl;
	   
	   sprintf(msg_body,"2,%d,4",CHANGE_SCENE);   
	   send_msg(fd, msg_body);
	   return;
	}

	/*Verification Jump Point location;*/
	Point verPt=iter->second->nowPt; 
	Point nowPt=msgSender->getLocation();
	if((verPt._x-nowPt._x)>MAX_RANGE ||(verPt._x-nowPt._x)<-MAX_RANGE ||(verPt._y-nowPt._y)>MAX_RANGE || (verPt._y-nowPt._y)<-MAX_RANGE)
	{
		cout<<"verPt._x:"<<verPt._x<<endl;
		cout<<"verPt._y:"<<verPt._y<<endl;
		
		cout<<"nowPt._x:"<<nowPt._x<<endl;
		cout<<"nowPt._y:"<<nowPt._y<<endl;
		
		cout<<"MAX_RANGE:"<<MAX_RANGE<<endl;
		cout<<"in the jumpId_to_changesence.cpp the position is more than the MAX_RANGE"<<endl;
		sprintf(msg_body,"2,%d,%d",CHANGE_SCENE,FAILED);
	    send_msg(fd, msg_body);
		return;
	}
	
	
	Point targetPt=iter->second->targetPt;                       /*Target map pt;*/
	nextMapId=iter->second->mapId;                               /*Target mapId;*/
	if(*nextMapId.c_str() != 'm')                                /*Tower defense duplicate scene jump;*/
	{	
		int found;  
		int roomNum,differ;      
		string room;
		string dupId;  
		char map_id[100] = {0};
		string dupRoom;
		string diff;
		string hero=hero_id;	
		vector<string> heroId; 	  
		map<string, Hero*>::iterator roleId_it;	  
		map<string,CpyLimit*>::iterator cpyLimt_it;	
	  
		/*gain the duplicate id*/
		dupRoom = msgSender->getFbRom();
		cout<<"dupRoom:"<<dupRoom<<endl;
		found = dupRoom.find_last_of("_");
		if(found == string::npos)
		{
			return;
		}		
		dupId = dupRoom.substr(0,found);	
		
		/*gain the duplicate map id*/
		room = dupRoom.substr(found + 1);
		roomNum = atoi(room.c_str());
		if(roomNum < 0)
		{
			sprintf(msg_body,"2,%d,%d",CHANGE_SCENE,FAILED);
			send_msg(fd, msg_body);
			return;
		}
		
		/*难度*/
		diff = dupId;		
		found = diff.find_last_of("_");
		if(found == string::npos)
		{
			return;
		}		
		diff = diff.substr(found + 1);
		differ = atoi(diff.c_str());
		if(differ < 0 || differ > 3)
		{
			sprintf(msg_body,"2,%d,%d",CHANGE_SCENE,FAILED);
			send_msg(fd, msg_body);
			return;
		}		
		
		strncpy(map_id,nextMapId.c_str(),strlen(nextMapId.c_str()));
		strncat(map_id,"_",strlen("_"));
		appendNum(map_id,differ,1);
		strncat(map_id,"_",strlen("_"));
		strncat(map_id,dupRoom.c_str(),strlen(dupRoom.c_str()));
		// strncat(map_id,"_",strlen("_"));
		// appendNum(map_id,roomNum,4);	
		
		/*find the duplicate*/
		cpyLimt_it = cpyId_to_cpyLimit.find(dupId);
		if(cpyLimt_it == cpyId_to_cpyLimit.end())
		{
			cout<<"in the jumpId_to_changesence.cpp can't find the dupId:"<<dupId<<endl;
			sprintf(msg_body,"2,%d,%d",CHANGE_SCENE,FAILED);
			send_msg(fd,msg_body);
			return;
		}
		
		
		heroId.push_back(hero_id);
		cpyLimt_it->second->enterRom(roomNum,heroId,map_id,&targetPt);
	
	}
	
	else{		 	/*Ordinary duplicate scene;*/	
	map<string,Map_Inform*>::iterator iter_map = mapId_connect_map.find(nextMapId);

	if(iter_map == mapId_connect_map.end())  //Ordinary duplicate scene not find the mapId；
	{
	   cout<<"in the jumpId_to changeSence.cpp can't find the nextMapId:"<<nextMapId<<endl;
	   cout<<"in the mapId:"<<map_now->getIdentity()<<"the skipId:"<<jumpId<<endl;
		sprintf(msg_body,"2,%d,%d",CHANGE_SCENE,FAILED);
	    send_msg(fd, msg_body);
		return;
	}
	
	Map_Inform *map_next;
	map_next = iter_map->second;
	if(map_next == NULL)
	{
		return ;
	}

	msgSender->quit_scene();
	msgSender->setMap(map_next);
	
	sprintf(msg_body,"2,%d,%d,%s,%d,%d,%d,%d,%d",CHANGE_SCENE,SUCCESS,nextMapId.c_str(),targetPt._x,targetPt._y,\
													map_next->getWarType(),map_next->getChangePkType(),map_next->getMapType());

	send_msg(msgSender->getFd(),msg_body); 

	msgSender->setLocation(targetPt);	
	msgSender->setWalkingFlg(false);
	// msgSender->enter_scene();
  }
}
