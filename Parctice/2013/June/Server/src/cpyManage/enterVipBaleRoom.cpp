/************************************************************
    文件名：enterVipBaleRoom.cpp
    文件作用：进vip包间辅助函数
    作者：chenzhen
    创建日期：2012.12.14
************************************************************/
#include"entCpy.h"
#include"cpyAsist.h"
#include"vipBaleRoomLimit.h"
#include "instancing_manage.h"
extern int g_msg_len;
extern Hero* pg_hero;
extern map<string,VipBaleRoomLimit*> mapIdToVipBaleRomLimit;
void entVipBaleRoom(char *buffer)
{
	map<string,VipBaleRoomLimit*>::iterator vipRom_it;	
	char failMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};
	Failure_Reason* failure_reason;
	VipBaleRoomLimit *vipRoom;
	char *vipMapId,*heroId;
	vector<string> herIdVec;
	
	
	MSG_BEGIN(buffer, g_msg_len);
	// MSG_CHAR(heroId);	
	MSG_CHAR_END(vipMapId);		
	
	heroId = pg_hero->getIdentity();
	
	herIdVec.push_back(heroId);
	
	cout<<"vipMapId first:"<<vipMapId<<endl;
	if(vipMapId == NULL || strlen(vipMapId) == 0 || heroId == NULL || strlen(heroId) ==0)
	{
		cout<<"the mapId is NULL:"<<endl;
		return;
	}	
	
	if(!(strcmp(vipMapId,"map_025") == 0 || strcmp(vipMapId,"map_026") == 0 ||\
	  strcmp(vipMapId,"map_027") == 0 || strcmp(vipMapId,"map_028") == 0))
	{
		cout<<"the mapId is not vipMapId:"<<vipMapId<<endl;
		return;
	}
	
	vipRom_it = mapIdToVipBaleRomLimit.find(vipMapId);	
	if(vipRom_it == mapIdToVipBaleRomLimit.end())
	{
		cout<<"the vip mapId is error:"<<vipMapId<<endl;
		return;
	}
	
	cout<<"vipMapId second:"<<vipMapId<<endl;
	
	vipRoom = vipRom_it->second;
	
	failure_reason = (Failure_Reason*)malloc(sizeof(Failure_Reason));		
	failure_reason->size = 0;

	if(!initFailReson(failure_reason))
	{
		free(failure_reason);
		cout<<"failure_reason is NULL:"<<endl;
		return;
	}
	
	/*资格审查*/
	if(!vipRoom->qualifyExam(herIdVec,failure_reason))
	{			
		cout<<"vipMapId second:"<<vipMapId<<endl;
		dealFailRson(failure_reason,failMsg,sizeof(failMsg),1);
		sendFailMsg(herIdVec,failMsg);				
		free(failure_reason);			
	    return;
	}
	vipRoom->assignRom(herIdVec);
	free(failure_reason); 
}