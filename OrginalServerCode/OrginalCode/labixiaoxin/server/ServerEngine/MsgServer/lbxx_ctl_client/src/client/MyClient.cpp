#include "..\data\IGameBase.h"
#include "MyClient.h"
#include "data\DoAction.h"

boost::asio::io_service CMyClient::g_ios;
bool IGameBase::isLog = false;
CMytools CMyClient::g_tools;
CMyClient::sock_pt g_sock;

CMyClient::CMyClient( boost::asio::io_service & io ):ios(io),ep(boost::asio::ip::address::from_string(g_tools.m_serverIP),g_tools.m_serverPort)
{

}

void CMyClient::Start()
{
	//m_str = "123";
	g_sock.reset();
	sock_pt sock(new boost::asio::ip::tcp::socket(ios));

	sock->async_connect(ep,//异步连接
		boost::bind(&CMyClient::Conn_handler,this,boost::asio::placeholders::error,sock));
}

void CMyClient::Conn_handler( const boost::system::error_code & ec,sock_pt sock )
{
	if (ec)
	{
		sock->async_connect(ep,//异步连接
			boost::bind(&CMyClient::Conn_handler,this,boost::asio::placeholders::error,sock));
		std::cout<<"reconnection !\n";
		//g_ios.stop();
		return;
	}

	g_sock = sock;
	// 		sock->async_write_some(boost::asio::buffer(m_str),
	// 			boost::bind(&CMyClient::Write_handler,this,boost::asio::placeholders::error,sock));//先请求

	// 		sock->async_read_some(boost::asio::buffer(_Data), 
	// 			boost::bind(&CMyClient::Read_handler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	//boost::shared_ptr<std::vector<char> > str(new std::vector<char>(1024,0));
	sock->async_read_some(boost::asio::buffer(_Data),boost::bind(&CMyClient::Read_handler,this,boost::asio::placeholders::error,sock,boost::asio::placeholders::bytes_transferred));

}

void CMyClient::Read_handler( const boost::system::error_code & ec, sock_pt sock,std::size_t bytes_transferred )
{
	if (ec)
	{
		std::cout<<"close reconnectin\n";
		Start();
		//g_ios.stop();
		return;
	}

	std::vector<MsgInfo> ver = m_myAsioTools.UnSerializing(_Data, bytes_transferred);

	//具体业务逻辑处理
	std::vector<MsgInfo>::iterator it = ver.begin();
	while(it != ver.end())
	{
		std::cout<<it->m_head.unMsgID<<std::endl;
		if (it->m_head.unMsgID == MSG_SEND_ALL_MSG_ID)
		{
			std::string str(it->text.begin(),it->text.end());
			std::cout<<str<<std::endl;
		}
		
		it++;
	}
// 	CDoAction doaction;
// 	std::vector<std::string>::iterator it = ver.begin();
// 	while(it != ver.end())
// 	{
// 		doaction.OnMessage(*it);
// 		it++;
// 	}
	//---------------------end

	//boost::shared_ptr<std::vector<char> > _str(new std::vector<char>(1024,0));
	sock->async_read_some(boost::asio::buffer(_Data),boost::bind(&CMyClient::Read_handler,this,boost::asio::placeholders::error,sock,boost::asio::placeholders::bytes_transferred));


	// 		sock->close();//关闭链接
	// 		g_ios.stop();
};

void CMyClient::Write_handler( const boost::system::error_code & ec,sock_pt sock )
{
	if (ec)
	{
		//Start();
		//g_ios.stop();
		return;
	}

	//str;
	//sock->close();//关闭链接
};

void CMyClient::StartClient()
{
	try
	{
		g_tools.ReadText();
		CMyClient cl(g_ios);
		cl.Start();
		g_ios.run();
		g_ios.reset();
	}
	catch (std::exception &)
	{

	}
}

void CMyClient::WriteSomeSomething( const boost::scoped_array<char> & str ,MY_UINT32 len)
{
	if (g_sock)
	{
		g_sock->async_write_some(boost::asio::buffer(str.get(),len),
			boost::bind(&CMyClient::Write_handler,boost::asio::placeholders::error,g_sock));//先请求
		std::cout<<"write seccess!\n";
	}

}

