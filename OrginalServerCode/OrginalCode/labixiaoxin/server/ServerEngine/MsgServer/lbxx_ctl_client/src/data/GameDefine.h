/********************************************************************
    创建时间：    2015/08/08  16:22:27 
    文件名：      GameDefine.h
    作者：        xxj
    
    功能:		1.消息定义
				2.
                
    说明:		1. 
                2. 
*********************************************************************/
#ifndef __GAMEDEFINE_H_
#define __GAMEDEFINE_H_

#include <string>

typedef unsigned int MY_UINT32;
//"ID"
#define MSG_SEND_RESULT_ID 0 //返回消息

#define MSG_LOGIN_ID 1//登录
#define MSG_CHANGE_NAME_ID 2//改名字
#define MSG_CHANGE_LEVEL_ID 3//改名字
#define MSG_SEND_FROM_MSG_ID 4//发送消息

#define MSG_SEND_ALL_MSG_ID 10//收消息 (广播)
#define MSG_SEND_TO_MSG_ID 11//收消息 (私人消息)

typedef struct tagMsgBaseHead
{
	MY_UINT32 unMsgID;
	int nResult;

	tagMsgBaseHead()
	{
		Clear();
	}
	void Clear()
	{
		unMsgID = 0;
		nResult = 0;
	}
}MsgBaseHead;

typedef struct tagUserInfo
{
	MY_UINT32 m_id;//谁说
	MY_UINT32 m_level;
	MY_UINT32 m_vipLevel;

	std::vector<char> m_name;
	//std::string m_name;

	tagUserInfo()
	{
		Clear();		
	}
	void Clear()
	{
		m_id = 0;
		m_level = 0;
		m_vipLevel = 0;
		m_name.clear();
		//m_name.swap(std::vector<char>());
	}
}UserInfo;

typedef struct tagMsgInfo
{
	MsgBaseHead m_head;//消息头
	UserInfo m_user;//谁说的

	MY_UINT32 toID;//向谁说
	std::vector<char> text;
	
	tagMsgInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_head.Clear();
		m_user.Clear();
		toID = 0;
		text.clear();
	}
}MsgInfo;
//"uID"


#endif
