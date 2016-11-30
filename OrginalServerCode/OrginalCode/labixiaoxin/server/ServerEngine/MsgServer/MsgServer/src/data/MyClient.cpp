#include "MyClient.h"
#include "ServerConnection.h"
#include "..\tools\MyTimes.h"
#include "GameDefine.h"
#include "ClientList.h"
#include "..\tools\Mytools.h"
#include <boost\locale\encoding.hpp>
bool IGameBase::isLog = false;

CMyClient::CMyClient(boost::asio::io_service & ioservice) 
	:ClientSession(ioservice)
{
	m_loginTime = 0;
}

CMyClient::~CMyClient()
{
}

void CMyClient::OnRead(std::vector<MsgInfo> & ver)
{
	std::vector<MsgInfo>::iterator it = ver.begin();
	while(it != ver.end())
	{
		if (!DealMsg(*it))
			break;

		it++;
	}
// 	for (std::string mpv:ver)
// 	{
// 		if (IGameBase::isLog)
// 			std::cout << "deal message :"<<mpv << std::endl;
// 	}
}

bool CMyClient::OnSend(const boost::scoped_array<char> & str,MY_UINT32 len )
{
	WriteSomeSomething(str,len);
	return true;
}

void CMyClient::OnConnect()
{
	if (IGameBase::isLog)
		std::cout << "get a new client:"<<Socket().remote_endpoint().address()<<":"<<Socket().remote_endpoint().port() << std::endl;
}

void CMyClient::DisConnect()
{
	if (IGameBase::isLog)
		std::cout << "close a client"<< std::endl;

	OnDestroye();
}

void CMyClient::OnInit()
{
	m_loginTime = CMyTimes::get_utc();
}

bool CMyClient::OnTimeOut()
{
	if(m_isInit)
		return false;
	else
	{
		MY_UINT32 now = CMyTimes::get_utc();
		if(now - MAX_TIME_OUT_LOGIN > m_loginTime)
			return true;
		
		return false;//还没有超时
	}
}

bool CMyClient::DealMsg( MsgInfo & info )
{
	try
	{
		unsigned int id = info.m_head.unMsgID;

		//第一个消息必须是登录消息
		if (!m_isInit)
		{
			if (id != MSG_LOGIN_ID)
			{
				OnDestroye();
				return false;
			}
		}
		else
		{
			if (id == MSG_LOGIN_ID)
			{
				OnDestroye();
				return false;
			}
		}


		bool isDo = false;
		switch(id)
		{
		case MSG_LOGIN_ID:
			{
				isDo = OnLogin(info);
				WriteResult(isDo?0:-1);
			}break;
		case MSG_CHANGE_NAME_ID:
			{
				isDo = OnChangeName(info);
				WriteResult(isDo?0:-1);
			}break;
		case MSG_CHANGE_LEVEL_ID:
			{
				isDo = OnChangeLevel(info);
				WriteResult(isDo?0:-1);
			}break;
		case MSG_SEND_FROM_MSG_ID:
			{
				isDo = OnSendMsg(info);
			}break;
		}

		if (!isDo)
		{
// 			OnDestroye();
// 			return false;
		}
		else
			return true;


	}
	catch (std::exception & e)
	{
		std::cout << "error：" <<e.what()<< std::endl;//请输入参数

		//数据异常，删除此用户
		OnDestroye();
		return false;
	}
}

void CMyClient::OnDestroye()
{
	if (!m_isDelete)//已经删除过
	{
		if (m_isInit)
			CClientList::instance()->DeleteOnClient(shared_from_this());
		else
			CServerConnectionData::instance()->DeleteOneConnection(shared_from_this());
	}
}

bool CMyClient::OnLogin(const MsgInfo & info )
{
	assert(!m_isInit);

	//初始化数据
	m_user = info.m_user;

	std::cout<<"OnLogin:"<<boost::locale::conv::between(std::string(m_user.m_name.begin(),m_user.m_name.end()), "gb2312", "UTF-8")<<std::endl;

	if(CServerConnectionData::instance()->DeleteOneNoSoket(shared_from_this()))//删除连接缓存数据
	{
		CClientList::instance()->AddOneClient(shared_from_this());
		m_isInit = true;
		return true;
	}
	else
		assert(false);

	return false;
}

bool CMyClient::OnChangeName(const MsgInfo & info )
{
	//初始化数据
	m_user.m_name = info.m_user.m_name;
	return true;
}

bool CMyClient::OnSendMsg( MsgInfo & info )
{
	info.m_user = m_user;
	if (info.toID == 0)//广播
	{
		info.m_head.unMsgID = MSG_SEND_ALL_MSG_ID;
		CClientList::instance()->SendMsgToBroadcast(info);
	}
	else
	{
		info.m_head.unMsgID = MSG_SEND_TO_MSG_ID;
		CClientList::instance()->SendMsgToOne(info);
	}

	return true;
}

bool CMyClient::OnChangeLevel( const MsgInfo & json )
{
	m_user.m_level = json.m_user.m_level;
	m_user.m_vipLevel = json.m_user.m_vipLevel;
	return true;
}

