#include "ServerApp.h"
#include "..\data\ServerConnection.h"

CserverApp::CserverApp(boost::asio::io_service& ioservice, boost::asio::ip::tcp::endpoint& endpoint)
	:m_ioservice(ioservice),
	acceptor_(ioservice, endpoint/*,false*/)//false 设置端口不可复用
{
	std::cout<<"strat!"<<std::endl;
	std::cout<<"listen [ip:port]:"<<endpoint<<std::endl;
	OnAccept();
}

CserverApp::~CserverApp()
{

}

void CserverApp::Handle_accept(const boost::system::error_code& error, Session_ptr& session)
{
	if (!error)
	{
		session->OnConnect();//通知连接
		//实现对每个客户端的数据处理
		session->Start();

		OnAccept();

		CServerConnectionData::instance()->AddOneConnection(session);
	}
}

void CserverApp::OnAccept()
{
	//每一个session就是一个客户端
	Session_ptr new_session(new CMyClient(m_ioservice));
	acceptor_.async_accept(new_session->Socket(),
		boost::bind(&CserverApp::Handle_accept, this, boost::asio::placeholders::error,
		new_session));
}


