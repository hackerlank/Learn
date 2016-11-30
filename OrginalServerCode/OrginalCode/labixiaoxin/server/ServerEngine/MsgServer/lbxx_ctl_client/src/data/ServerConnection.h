/********************************************************************
	创建时间：	2014/08/07  10:58:17 
	文件名：    ServerConnection
	作者：		谢小军
	
	功能：		1.通信接口类
				2.
				
	说明：	    1. 服务器中连接的客户端连接信息
				2. 
*********************************************************************/
#ifndef _SERVERCONNECTION_H_
#define _SERVERCONNECTION_H_
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <vector>
#include "..\tools\MySingleton.h"
#include "MyClient.h"


//通信接口
class CServerConnectionData:public MySingleton<CServerConnectionData>
{
public:
	typedef boost::shared_ptr<ClientSession> Session_ptr;
public:	
	boost::shared_mutex m_rw_mutex;
	std::vector<Session_ptr> m_verConnection;
	void AddOneConnection(const Session_ptr & _ptr);
	bool DeleteOneConnection(Session_ptr & _ptr);

	void SendAllMessage( MsgInfo & info );//发送消息
};

#endif