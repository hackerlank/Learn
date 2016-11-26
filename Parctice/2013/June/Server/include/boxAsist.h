/************************************************************
	文件名：boxAsist.h
	文件作用：定义九宫格辅助功能函数
	作者：chenzhen
	创建日期：2012.11.15
************************************************************/
#ifndef BOX_ASIST_H
#define BOX_ASIST_H
#include"wholeDefine.h"
#include<string.h>
#include<string>
#include<map>
#include<set>
#include<iostream>
using namespace std;

/*九宫格存取内容*/
#define HERO_STYLE_TYPE			0
#define MONSTER_STYLE_TYPE		1
#define PET_STYLE_TYPE			2
#define WAGON_STYLE_TYPE		3
#define BOTTLE_STYLE_TYPE		4
#define TAKEGOODS_STYLE_TYPE	5
#define PICK_STYLE_TYPE			6
#define DROP_EQUIP_STYLE_TYPE	7
#define TRAP_STYLE_TYPE			8
#define STATUARY_STYLE_TYPE		9

class Map_Inform;
class Hero;

typedef struct StyObj
{
	char objId[SHOR_MID_VALUE_LENGTH + 1];
	int type;
	StyObj(char *_objId,int _type)
	{
		memset(objId,'\0',SHOR_MID_VALUE_LENGTH + 1);
		strncpy(objId,_objId,strlen(_objId));
		type = _type;
	}
}StyObj;


typedef struct OneScreen_S {
	set<string> heroSet;			//heroId容器
	set<string> monsterSet;			//怪物Id容器
	set<string> petSet;				//宠物ID容器
	set<string> wagonSet;			//马车Id容器
	set<string> bottleSet;			//瓶子罐子
	set<string> takeSet;			//采集物
	set<string> pickSet;			//掉落物
	set<string> dropEqpSet;			//dropEqp
	set<string> trapSet;			//trap
	set<string> statuarySet;		//statuary

}OneScreen;

inline bool isValidType(int _type)
{
	if(_type < HERO_STYLE_TYPE || _type > STATUARY_STYLE_TYPE)
	{
		return false;
	}
	return true;
	
}

inline bool ScreenDel(OneScreen & screen, StyObj &obj)
{
	set<string> *p = (set<string>*) &screen;
	if (!isValidType(obj.type))
	{
		return false;
	}
	set<string> *temp = p + obj.type;
	if (temp->find(obj.objId) == temp->end())
	{
		return false;
	}
	temp->erase(obj.objId);
	return true;
}

inline bool ScreenInsert(OneScreen & screen, StyObj &obj)
{
//	cout<<"ScreenInsert begin obj.objId:"<<obj.objId<<endl;
	set<string> *p = (set<string>*) &screen;
	if (!isValidType(obj.type))
	{
		return false;
	}
//	cout<<"ScreenInsert front obj.type:"<<obj.type<<endl;
	set<string> *temp = p + obj.type;
	if (temp->find(obj.objId) != temp->end())
	{
		return false;
	}
//	cout<<"ScreenInsert back obj.type:"<<obj.type<<endl;
	
	temp->insert(obj.objId);
//	cout<<"ScreenInsert end obj.objId:"<<obj.objId<<endl;
	return true;
}

inline void ScreenPrint(OneScreen & screen)
{
	set<string> *p = (set<string>*) &screen;
	set<string> *temp;
	set<string>::iterator it;
	for (int i = 0; i < 10; i++)
	{
		temp = p + i;
		cout<<"type is "<<i<<endl;
		for (it = temp->begin(); it != temp->end(); it++)
		{
			cout<<"id is "<<*it<<endl;
		}
	}
}

inline void ScreenClear(OneScreen & screen)
{
	set<string> *p = (set<string>*) &screen;
	set<string> *temp;
	set<string>::iterator it;
	for (int i = 0; i < 10; i++)
	{
		temp = p + i;
		temp->clear();
	}
}

/*判断放入九宫格的类型是否正确*/
bool isStyObjTpe(int _type);

/*消息发送类*/
class SendMsgClass
{
	public:
		/*封装的消息发送函数，以九宫格发送*/
		static void sentBoxMsg(set<string> &nbox_id_set,char *msg,char *heroId = NULL);	
		
		/*全地图发送消息*/
		static void sendMapMsg(Map_Inform *map_now,char *msg,int fd = -1);		
		//将整张地图的角色信息发送给指定的fd
		static void sendMapMsg(Map_Inform *map_now, int fd);
		
		/*封装的消息发送函数，以九宫格发送,为相互看见的,主要用在玩家的消息发送*/
		static void sentBoxViewMsg(OneScreen &nbox_id_set,\
					char *msg,Map_Inform *map_now,Hero *myHero,int style);
};
#endif