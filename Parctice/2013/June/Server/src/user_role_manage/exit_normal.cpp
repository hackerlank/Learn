/*
		文件类型：实现文件
		文件名称：exit_normal.cpp
		文件作用：处理命令退出的命令的函数的实现
		更改时间：3.13
		更改人：陈真
*/

#include"command_user_role_manage.h"
#include"command_return_define_data.h"
#include"command_other_function_all_over.h"

#include"libev.h"
#include"map_inform.h"
#include"boxAsist.h"
extern map<string,Map_Inform*>mapId_connect_map;
//extern map<string, Role*> userName_to_pRole;
extern map<string, Hero*> heroId_to_pHero;
extern map<int,Role*>fd_to_pRole;

#include "wholeDefine.h"


/*      
		函数：void exit_normal(char *buffer)	      
		作用：退出函数，处理正常退出命令
		参数：void
		返回值：void
*/

void exit_normal(char *buffer)				
{
	char *mapId;     //次下线玩家所在地图id
	Point pt;

	/*解析且追加坐标*/
	MSG_BEGIN(buffer, g_msg_len)
	MSG_CHAR(char* uid)
	MSG_INT(pt._x)
	MSG_INT(pt._y)

	string msg_others = "0";    // 发给其他玩家当前登录者玩家的信息
	msg_others = msg_others + intTostring(DOWN_LINE);  
	Hero* cur_hero=pg_hero;
	string Identity_body = charTostring(cur_hero->getIdentity());
	msg_others = msg_others + Identity_body;   //追加用户id
	msg_others = msg_others + intTostring(pt._y);    	
	
	mapId=cur_hero->getMapId();	      //获得地图id
	
	/*用地图id查找相对应的地图实例指针*/
	map<string,Map_Inform*>::iterator map_it;
	map_it=mapId_connect_map.find(mapId);
	if(map_it==mapId_connect_map.end())
	{
		return;
	}
	Map_Inform *map_now;
	map_now=map_it->second;
	
	/*获得九宫格*/
	map<string,StyObj> nbox_id_set;                    //将当前登陆角色所在点(九宫格内)周围的Hero对象的id集合在一起
	Nbox *box=map_now->getBox();	
	
	StyObj obj(cur_hero->getIdentity(),HERO_STYLE_TYPE);
	
	if(box == NULL)
	{
		return;
	}
	
	box->getStaInSrcVec(obj);
	
	box->heroEnter(cur_hero,2);
	
	map_now->deleteID(obj);	
	
	/*下线处理*/
//	players->setLoginState(false);								//将下线的Role对象的在线状态isLogin改为false
	fd_to_pRole.erase(cur_hero->getFd());						//将下线的Role对象从fd_to_pRole容器中删掉
	// cur_hero->setFd(0);
}
	
	
