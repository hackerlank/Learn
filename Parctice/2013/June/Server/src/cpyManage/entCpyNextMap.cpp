/************************************************************
	文件名：entCpyNextMap.cpp
	文件作用：初进副本的方法
	作者：chenzhen
	创建日期：2012.06.27
************************************************************/
#include"command_other_function_all_over.h"
#include"cpy_series_command_function.h"
#include"cpyLimit.h"
#include"cpyAsist.h"
#include"hero.h"

extern int g_msg_len;
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern map<string, Hero*> heroId_to_pHero;

void entCpyNextMap(char *buffer)
{  
	char *mapId,*fbRom,*hero_id,room[LITTLE_MID_VALUE_LENGTH + 1] = {'\0'};	
	char fbId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,CpyLimit*>::iterator cpyLimt_it;
	map<string, Hero*>::iterator roleId_it;
	vector<string> heroId;   
	int roomNum;     	
	
	
	
	MSG_BEGIN(buffer, g_msg_len);
	
	/*解析副本难度*/
	MSG_CHAR(hero_id);
	
	/*解析id*/
	MSG_CHAR_END(mapId);	
	
	/*放进容器*/
	heroId.push_back(hero_id);	
	
	/*获得hero实例指针以及副本信息*/
	roleId_it = heroId_to_pHero.find(hero_id);
	if(roleId_it == heroId_to_pHero.end())
	{
		return;
	}	
	
	fbRom = roleId_it->second->getFbRom();
	if(!dealSerNumStr(fbRom,room,fbId))
	{
		cout<<"the fbRom is error:"<<fbRom<<endl;
	}
	
	roomNum = atoi(room);
	
	if(roomNum < 0)
	{
		cout<<"the fb room is error:"<<roomNum<<endl;
		return;
	}

	cout<<"mapIdNext:"<<mapId<<endl;
	/*在副本地图后面追加房间号，形成副本特定房间地图id*/
	strncat(mapId,"_",strlen("_"));		
	appendNum(mapId,roomNum,4);
	

	/*查找副本*/
	cpyLimt_it = cpyId_to_cpyLimit.find(fbId);
	if(cpyLimt_it == cpyId_to_cpyLimit.end())
	{
		return;
	}
	
	cpyLimt_it->second->enterRom(roomNum,heroId,mapId);
}
	
	
	