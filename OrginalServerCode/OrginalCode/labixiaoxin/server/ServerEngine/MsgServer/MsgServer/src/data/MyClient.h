/********************************************************************
	创建时间：	2015/04/25  0:37:22
	文件名：	MyClient.h
	作者：		谢小军
	
	功能：		1. 主要逻辑类，在这里处理所有具体消息
				2.
				
	说明：	    1. 
				2. 
*********************************************************************/
#ifndef __MYCLIENT_H_
#define __MYCLIENT_H_

#include "..\asio\ClientSession.h"
#include "..\tools\DefineBase.h"
#include "..\json\MyJson.h"

class CMyClient:public ClientSession
{
public:
	CMyClient(boost::asio::io_service & ioservice);
	~CMyClient();
public://IGameBase 接口
	//读取到的文件
	virtual void OnRead(std::vector<MsgInfo> & ver);

	//发送事件
	virtual bool OnSend(const boost::scoped_array<char> & str,MY_UINT32 len);

	//连接成功调用
	virtual void OnConnect();
	//断开
	virtual void DisConnect();
public://IModelBase接口
	virtual void OnInit();
	virtual bool OnTimeOut();
public://处理消息
	bool DealMsg(MsgInfo & Msg);//消息处理函数开始
private:
	MY_UINT32 m_loginTime;
	//CMyJson m_myJsonOp;
	void OnDestroye();//销毁自己
	bool OnLogin(const MsgInfo & json);//登录
	bool OnChangeName(const MsgInfo & json);//改名字
	bool OnChangeLevel(const MsgInfo & json);//改等级
	bool OnSendMsg(MsgInfo & json);//发送消息

};

#endif // !__MYCLIENT_H_
