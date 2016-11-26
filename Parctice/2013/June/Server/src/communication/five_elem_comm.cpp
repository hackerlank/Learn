/****************************************************************
 * Filename: five_elem_comm.cpp
 * 
 * Description: 五行系统模块与客户端的通信
 *
 * Original Author : bison, 2012-7-12
 *
 ****************************************************************/
#include "command_return_define_data.h"
#include "role.h"
#include "five_asist.h"
#include <arpa/inet.h>

#include"wholeDefine.h"
extern int g_msg_len;
extern Hero* pg_hero;

//整形转成五行值
#define int2FiveElem(a) ((0 < (a) && (a) < 6) ? (FIVE_ELEMENT_T)(a) : NOELEM)

extern map<string, Hero*> heroId_to_pHero;
extern int sock_fd;
//获取五行数据
void viewFiveElemComm(char *buffer);

//宠物的五行开启是系统默认开启，只有人物的是由玩家选择开启
void openFiveElemComm(char *buffer)
{
	int elem;					//五行属性
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(elem);
	Hero *hero = pg_hero;
	
	char msg[64];
	//命令头8.8
	// string msg_head = "8";
	// msg = msg + msg_head + intTostring(OPEN_FIVE_ELEM_RETURN);
	
	if (openFiveElem(hero, int2FiveElem(elem), 20))
	{
		//开启成功
		// msg = msg + intTostring(SUCCESS); 
		sprintf(msg, "8,%d,1", OPEN_FIVE_ELEM_RETURN);
		send_msg(sock_fd, msg);
		//FiveElem *fiveElement = hero->getFiveElem();
		
		viewFiveElemComm(NULL);
	} else {
		//开启失败
		// msg = msg + intTostring(FAILED); 
		sprintf(msg, "8,%d,0", OPEN_FIVE_ELEM_RETURN);
		send_msg(sock_fd, msg);
		
	}
	
}

//更改五行属性的通信
void changFiveElemComm(char *buffer)
{
	int elem;					//五行属性
	int index;					//所要操作的宠物在宠物栏下标， 为-1时是对hero操作
	// int order;					//更改五行属性丹在背包中的下标
	
	char msg[64];
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT_MAX(index, 20);
	MSG_INT(elem);
	// MSG_INT(order);
	Hero *hero = pg_hero;
	
	// string msg_head = "8";
	// msg = msg + msg_head + intTostring(CHANGE_FIVE_ELEM_RETURN);
	
	// if (changeFiveElem(hero, int2FiveElem(elem), index, order))
	int ret = changeFiveElemNew(hero, int2FiveElem(elem), index);
	if (ret == 0)
	{
		//更改五行属性成功
		if (index == 20)
		{
			// msg = msg + intTostring(SUCCESS);
			sprintf(msg, "8,%d,1", CHANGE_FIVE_ELEM_RETURN);
			send_msg(hero->getFd(), msg);
			char p[] = "dd";
			viewFiveElemComm(p);
		}
	} else {
		//开启失败
		// msg = msg + intTostring(FAILED); 
		sprintf(msg, "8,%d,0,%d", CHANGE_FIVE_ELEM_RETURN, ret);
		send_msg(hero->getFd(),msg);
		
	}
	
}

//使用五行丹药提升五行等级
void useFiveElemGoodsComm(char *buffer)
{
	char len_arg;     			//参数长度
	int count = 6;
	int index;					//所要操作的宠物在宠物栏下标， 为-1时是对hero操作
	char *goodsId;				//五行丹ID
	int order;					//五行丹在背包中位置
	int net;
	
	char msg[16];
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT_MAX(index, 20);
	MSG_CHAR(goodsId);
	MSG_INT_MAX(order, 95);
	Hero *hero = pg_hero;
	
	//命令头3,12
	// string msg_head = "3";
	// msg = msg + msg_head + intTostring(USE_FIVE_ELEM_RETURN);
	
	if (useFiveElemGoods(hero, goodsId, order, index))
	{
		//更改五行属性成功
		// msg = msg + intTostring(SUCCESS); 
		// sprintf(msg,"3,12,1");
		// send_msg(hero->getFd(), msg);
		viewFiveElemComm(NULL);
		
	} else {
		//开启失败
		// msg = msg + intTostring(FAILED); 
		// sprintf(msg,"3,12,0");
		// send_msg(hero->getFd(), msg);
		
	}
	
}

//返回五行 数据 
void viewFiveElemComm(char *buffer)
{
	Hero *hero = pg_hero;
	FiveElem *fiveElement = hero->getFiveElem();
	// string viewMsg = "8";
	char viewMsg[400];
	// viewMsg += intTostring(VIEW_FIVE_ELEM_INFO);
	if (fiveElement == NULL)
	{
		//玩家还没有五行属性
		cout<<"BisonWarning: hero has no fiveElem when viewFive Elem!"<<endl;
		return;
	}
	
	if (fiveElement->getLevel() == 0)
	{
		// return;
	}
	
	// viewMsg += intTostring(fiveElement->getElem())
			 // + intTostring(fiveElement->getLevel())
			 // + intTostring(fiveElement->getExpNow())
			 // + intTostring(fiveElement->getExpForNext())
			 // + intTostring(fiveElement->getValue())
			 // + intTostring(fiveElement->getFactor(int2FiveElem(1)) * 100)
			 // + intTostring(fiveElement->getFactor(int2FiveElem(2)) * 100)
			 // + intTostring(fiveElement->getFactor(int2FiveElem(3)) * 100)
			 // + intTostring(fiveElement->getFactor(int2FiveElem(4)) * 100)
			 // + intTostring(fiveElement->getFactor(int2FiveElem(5)) * 100);
	sprintf(viewMsg, "8,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", VIEW_FIVE_ELEM_INFO, fiveElement->getElem(),
		fiveElement->getLevel(), fiveElement->getExpNow(), fiveElement->getExpForNext(), fiveElement->getValue(),
		int(fiveElement->getFactor(int2FiveElem(1)) * 100), int(fiveElement->getFactor(int2FiveElem(2)) * 100),
		int(fiveElement->getFactor(int2FiveElem(3)) * 100), int(fiveElement->getFactor(int2FiveElem(4)) * 100),
		int(fiveElement->getFactor(int2FiveElem(5)) * 100));
	send_msg(hero->getFd(), viewMsg);
	
}
