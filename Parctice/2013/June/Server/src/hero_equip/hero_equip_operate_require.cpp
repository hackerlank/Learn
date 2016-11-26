#include<string>
#include<iostream>
#include<stdlib.h>
#include<map>
#include"user_role_manage_equip.h"
#include"hero.h"
#include"bag.h"
#include"map_inform.h"
#include"equipment.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"
#include"command_game_fight_manage.h"
#include "wholeDefine.h"

extern int g_msg_len;
extern Hero* pg_hero;
extern char g_out_buf[20480];
extern Equip_Operator equip_operator[51];
using namespace std;
/*
* author: evan
* amend:  tory
* describe:锻造系统交互功能，处理各种锻造产生的预期效果回发给客户端，响应客户端的4,10命令
*/
void require_equip_operater(char *buffer)
{
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(int type);						//操作类型	
	
	if(type == 0)				//开刃
	{	
		MSG_CHAR_END(char* equip_id);				//装备实例ID
		cout<<"4,10,"<<type<<","<<equip_id<<endl;
		
		Equipment* equipment = pg_hero->getEquip(equip_id);		
		if(equipment == NULL)
		{
			return; 
		}
		
		if (equipment->gettype()==0||equipment->gettype()==13)
		{
			return;
		}
					
		memset(g_out_buf,0,sizeof(g_out_buf));
		equipment->msg_kaiRen(g_out_buf,sizeof(g_out_buf));
		send_msg(pg_hero->getFd(),g_out_buf);
	}	
	else if(type == 1)		//熔炼
	{
		MSG_CHAR_END(char* equip_id);				//装备实例ID
		cout<<"4,10,"<<type<<","<<equip_id<<endl;
	
		Equipment* equipment = pg_hero->getEquip(equip_id);		
		if(equipment == NULL)
		{
			return; 
		}
		
		if (equipment->gettype()==0||equipment->gettype()==13)
		{
			return;
		}
		
		cout<<"pg_hero->memHero->vipDailyData.rongLianRate:"<<pg_hero->memHero->vipDailyData.rongLianRate<<endl;
		memset(g_out_buf,0,sizeof(g_out_buf));
		equipment->msg_rongLian(g_out_buf,sizeof(g_out_buf),pg_hero->memHero->vipDailyData.rongLianRate); 
		send_msg(pg_hero->getFd(),g_out_buf);
	}
	
	else if(type == 3)	//移植
	{	
		MSG_CHAR(char* equip_id);					//原装备实例ID
		MSG_CHAR_END(char* des_equip_id);				//目标装备实例ID
		cout<<"4,10,"<<type<<","<<equip_id<<","<<equip_id<<endl;
	
		Equipment* src_quipment = pg_hero->getEquip(equip_id);		
		if(src_quipment == NULL)
		{
			return; 
		}
		
		Equipment* des_equipment = pg_hero->getEquip(des_equip_id);		
		if(des_equipment == NULL) 
		{
			return; 
		}		
		
		msg_yiZhi(pg_hero, src_quipment, des_equipment);
	}
		
}
