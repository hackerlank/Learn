#include "ClientSession.h"

ClientSession::ClientSession(boost::asio::io_service & ioservice)
	:m_socket(ioservice)
{
	memset(_data, '\0', sizeof(_data));
}

ClientSession::~ClientSession()
{

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

void ClientSession::WriteSomeSomething(const boost::scoped_array<char> & str,MY_UINT32 len)
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
			std::cout <<"read data from client:"<< _data << std::endl;

		std::vector<MsgInfo> ver = m_myAsioTools.UnSerializing(_data, bytes_transferred);
		this->OnRead(ver);

		ReadSomeSomething();//继续读取
	}
	else
	{
		DisConnect();
		m_socket.close();
	}
}

