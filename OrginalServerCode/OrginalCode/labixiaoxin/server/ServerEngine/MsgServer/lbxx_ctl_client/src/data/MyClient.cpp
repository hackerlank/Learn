#include "MyClient.h"
#include "ServerConnection.h"
bool IGameBase::isLog = false;

CMyClient::CMyClient(boost::asio::io_service & ioservice) 
	:ClientSession(ioservice)
{

}

CMyClient::~CMyClient()
{

}

void CMyClient::OnRead(const std::vector<MsgInfo> & ver)
{
	std::vector<MsgInfo>::const_iterator c_it = ver.begin();
	while(c_it != ver.end())
	{
		if (IGameBase::isLog)
			std::cout << "deal message :"<<*c_it << std::endl;

		c_it++;
	}
// 	for (std::string mpv:ver)
// 	{
// 		if (IGameBase::isLog)
// 			std::cout << "deal message :"<<mpv << std::endl;
// 	}
}

bool CMyClient::OnSend(const boost::scoped_array<char> & str,MY_UINT32 len)
{
	WriteSomeSomething(str,len);
	if (IGameBase::isLog)
		std::cout << "Write data to client!" << std::endl;
	return true;
}

void CMyClient::OnConnect()
{
	if (IGameBase::isLog)
		std::cout << "get a new client!" << std::endl;
}

void CMyClient::DisConnect()
{
	if (IGameBase::isLog)
		std::cout << "close a client!" << std::endl;

	CServerConnectionData::instance()->DeleteOneConnection(shared_from_this());
}

