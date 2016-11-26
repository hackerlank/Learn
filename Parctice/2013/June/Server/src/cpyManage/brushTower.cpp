/************************************************************
    文件名：brushTower.cpp
    文件作用：刷新黑木崖副本
    作者：chenzhen
    创建日期：2013.04.22
************************************************************/
#include"cpy_series_command_function.h"
#include"cpyLimit.h"
#include"command_other_function_all_over.h"
#include"cpyAsist.h"
#include"cpyManager.h"
#include"towerLayerRecord.h"
#include "instancing_manage.h"
#include "instancing_communication.h"

extern int sock_fd;
extern int g_msg_len;
extern Hero* pg_hero;
 
/*刷新青衣楼副本*/
void brushTower(char *buffer)
{
	char *hero_id,failMsg[LONG_MID_VALUE_LENGTH + 1] = {'\0'};       
	TowerLayerRecord *towerLayerRecord;
	
	MSG_BEGIN(buffer, g_msg_len);
	
	/*解析id*/
	MSG_CHAR(hero_id);	
	
	towerLayerRecord = pg_hero->getTowerLayerRecord();
	
	if(towerLayerRecord == NULL)
	{
		cout<<"brushTower the towerLayerRecord is NULL:"<<endl;
		return;
	}
	
#if 0
	//先注释掉，等冯伟亮把warning添上
	//没必要刷新
	if(!towerLayerRecord->isShouldBrushLayer())
	{
		cout<<"brushTower the towerLayerRecord is not should to brush:"<<endl;
		return;
	}
#endif	
	
	/*刷新一次暂定20元宝*/
	if(pg_hero->useMoney(0,20))
	{
		towerLayerRecord->brushLayerFlg();	
	}
}			









	
