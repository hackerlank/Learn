/************************************************************
	文件名：dropEquipAction.cpp
	文件作用：红名被杀掉落装回调函数
	作者：chenzhen
	创建日期：2012.12.3
************************************************************/
#include"dropEquipAction.h"
#include"equipment.h"
#include"libev.h"
extern map<string,Equipment*> dropEquipMent;
void dropEquipCalBak(struct ev_loop *loop,ev_timer *think,int revents)
{
	map<string,Equipment*>::iterator equip_it;
	Equipment *timeOutEquip;
	
	/*先暂停*/
	ev_timer_stop(loop,think);		
	
	/*获得思考对象指针*/
	timeOutEquip = (Equipment *)think->target;
	
	
	/*判断思考对象指针是否为空*/
	if(timeOutEquip == NULL)
	{
		return;
	}	
	
	
	timeOutEquip->disperMsg();
	
	equip_it = dropEquipMent.find(timeOutEquip->getentityid());
	if(equip_it != dropEquipMent.end())
	{
		dropEquipMent.erase(equip_it);
	}		
	delete timeOutEquip;
	timeOutEquip = NULL;
}
	
