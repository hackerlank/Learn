/********************************************************************
	创建时间：	2015/04/25  0:37:22
	文件名：	MyClient.h
	作者：		谢小军
	
	功能：		1. 主要逻辑类，在这里处理所以具体消息
				2.
				
	说明：	    1. 
				2. 
*********************************************************************/
#ifndef __MYCLIENT_H_
#define __MYCLIENT_H_

#include "..\asio\ClientSession.h"

class CMyClient:public ClientSession
{
public:
	CMyClient(boost::asio::io_service & ioservice);
	~CMyClient();
public:
	//读取到的文件
	virtual void OnRead(const std::vector<MsgInfo> & ver);

	//发送事件
	virtual bool OnSend(const boost::scoped_array<char> & str,MY_UINT32 len);

	//连接成功调用
	virtual void OnConnect();
	//断开
	virtual void DisConnect();
private:

};

#endif // !__MYCLIENT_H_
