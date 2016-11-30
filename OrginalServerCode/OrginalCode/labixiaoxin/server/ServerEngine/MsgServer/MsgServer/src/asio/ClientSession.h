/********************************************************************
	创建时间：	2015/04/24  23:58:33
	文件名：	ClientSession.h
	作者：		谢小军
	
	功能：		1. 主要用于跟客户端交互
				2.一个连接一个实例
				3.主要用于真正网络数据读写使用，包括流量控制，粘包，网络数据缓存
				
	说明：	    1. 
				2. 
*********************************************************************/
#ifndef __CLIENTSESSION_H_
#define __CLIENTSESSION_H_
#include <iostream>
#include <boost/enable_shared_from_this.hpp>//可进行安全的share_ptr转换
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "../data/IGameBase.h"
#include "MyAsioTools.h"
#include "../data/IModelBase.h"

#define max_len 1024

class ClientSession :public boost::enable_shared_from_this<ClientSession>,public IGameBase,public IModelBase
{
public:
	ClientSession(boost::asio::io_service & ioservice);
	~ClientSession();
public:
	boost::asio::ip::tcp::socket& Socket(){ return m_socket;}
	void CloseSocket();
	void Start();//开始交换消息
	void WriteSomeSomething(const boost::scoped_array<char> & str,MY_UINT32 len);//写一些东西给app
	void WriteResult(int nResult);//发送操作结果消息
	void ReadSomeSomething();//读取数据
private:
	void handle_write(const boost::system::error_code& error);//写完成回调
	void handle_read(const boost::system::error_code& error, std::size_t bytes_transferred);//读完成回调
	void _DoTry(std::size_t bytes_transferred);
private:
	boost::asio::ip::tcp::socket m_socket;
	char _data[max_len];
	CMyAsioTools m_myAsioTools;
};

#endif // !__CLIENTSESSION_H_
