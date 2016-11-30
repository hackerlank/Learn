#include "ClientSession.h"
#include <boost\format.hpp>
#include <boost\date_time\posix_time\time_formatters.hpp>
#include "..\..\..\lbxx_ctl_client\src\client\MyTools.h"

ClientSession::ClientSession(boost::asio::io_service & ioservice)
	:m_socket(ioservice)
{
	memset(_data, '\0', sizeof(_data));
}

ClientSession::~ClientSession()
{
// 	if (m_socket.is_open())
// 		m_socket.close();
}

void ClientSession::Start()
{
	ReadSomeSomething();
}

void ClientSession::ReadSomeSomething()
{
	//异步读取
	m_socket.async_read_some(boost::asio::buffer(_data, max_len),
		boost::bind(&ClientSession::handle_read, shared_from_this(),
		boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
}

void ClientSession::WriteSomeSomething( const boost::scoped_array<char> & str ,MY_UINT32 len)
{
	boost::asio::async_write(m_socket,
		boost::asio::buffer(str.get(),len),
		boost::bind(&ClientSession::handle_write,
		shared_from_this(), boost::asio::placeholders::error));
}

void ClientSession::handle_write(const boost::system::error_code& error)
{
	if (error)
	{
		DisConnect();
		m_socket.close();
	}
}

void ClientSession::handle_read(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (!error)
	{
		if (IGameBase::isLog)
			std::cout <<"read data from client:"<< bytes_transferred << std::endl;

		__try
		{
			_DoTry(bytes_transferred);
		}
		__except(puts("exception error"),1)
		{
			std::cout << "exception error：" << std::endl;//请输入参数
			DisConnect();
			m_socket.close();
		}

// 		try
// 		{
// 			std::vector<MsgInfo> ver = m_myAsioTools.UnSerializing(_data, bytes_transferred);//解包
// 			ReadSomeSomething();//继续读取
// 			this->OnRead(ver);
// 		}
// 		catch (std::exception & e)
// 		{
// 			std::vector<std::string> ver;
// 			ver.push_back(boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time()) +"\t"+e.what());
// 			MyTools::PrintToFile("MsgLog/error.txt",ver,false);
// 			std::cout << "error：" <<e.what()<< std::endl;//请输入参数
// 			DisConnect();
// 			m_socket.close();
// 		}
	}
	else
	{
		DisConnect();
		m_socket.close();
	}
}

void ClientSession::WriteResult( int nResult )
{
	MsgInfo info;
	info.m_head.unMsgID = MSG_SEND_RESULT_ID;
	info.m_head.nResult = nResult;
	boost::scoped_array<char> _buffer;
	CMyAsioTools tools;
	MY_UINT32 len = tools.Serializing(info,_buffer);
	if(len > 0)
	{
		WriteSomeSomething(_buffer,len);
	}
}

void ClientSession::CloseSocket()
{
	if (m_socket.is_open())
	{
		m_socket.close();
	}
}

void ClientSession::_DoTry(std::size_t bytes_transferred)
{
	std::vector<MsgInfo> ver = m_myAsioTools.UnSerializing(_data, bytes_transferred);//解包
	ReadSomeSomething();//继续读取
	this->OnRead(ver);
}

