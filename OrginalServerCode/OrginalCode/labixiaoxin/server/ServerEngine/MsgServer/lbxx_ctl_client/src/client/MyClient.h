#ifndef MYCLIENT_H_
#define MYCLIENT_H_
#include <string>
#include <vector>

//boost asio head 
#ifdef _MSC_VER
#define _WIN32_WINNT 0x0501
#endif 
#define BOOST_REGEX_NO_LIB
#define BOOST_DATE_TIME_SOURCE
#define BOOST_SYSTEM_NO_LOB
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "MyTools.h"
#include <boost/locale/encoding.hpp>
#include "../tools/Mytools.h"
#include <iostream>
#include <boost/smart_ptr/scoped_array.hpp>
#include "../asio/MyAsioTools.h"

typedef unsigned int MY_UINT32;

#define MAX_RESERVE_SIZE 1024*8  //最大接收尺寸
//#define max_len 1024

class CMyClient
{
public:
	typedef boost::shared_ptr<boost::asio::ip::tcp::socket> sock_pt;//client 不需要accept，直接connect

	static boost::asio::io_service g_ios;
	static CMytools g_tools;
private:
	boost::asio::io_service & ios;//io_server对象
	boost::asio::ip::tcp::endpoint ep;//TCP 端点
	CMyAsioTools m_myAsioTools;
	char _Data[MAX_RESERVE_SIZE];
public:
	CMyClient(boost::asio::io_service & io);
	~CMyClient(){};

	void Start();

	void Conn_handler(const boost::system::error_code & ec,sock_pt sock);

	void Read_handler(const boost::system::error_code & ec, sock_pt sock,std::size_t bytes_transferred);

	static void Write_handler(const boost::system::error_code & ec,sock_pt sock);

	static void StartClient();
	static void WriteSomeSomething( const boost::scoped_array<char> & str, MY_UINT32 len);
};

#endif