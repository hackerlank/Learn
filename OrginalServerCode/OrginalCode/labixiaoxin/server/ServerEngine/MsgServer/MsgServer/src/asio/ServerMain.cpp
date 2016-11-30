#include "ServerMain.h"
#include <boost\date_time\posix_time\time_formatters.hpp>
#include <boost\foreach.hpp>
#include "ServerApp.h"
#include "..\tools\Mytools.h"
#include "..\data\ClientList.h"


void CServerMain::StartServer()
{
	if (tools.ReadText())
	{
		try
		{
			boost::asio::ip::tcp::endpoint endPoint(boost::asio::ip::tcp::v4(), tools.m_serverPort);//我们用的是inet4
			//终端（可以看作sockaddr_in）完成后，就要accept了

			CserverApp sa(m_ioService,endPoint);

			std::vector<boost::shared_ptr<boost::thread> > _listThread;//附加io线程
			//创建10个读(io)线程
			for (int i = 0; i < MAX_IO_THREAD; ++i)
			{
				boost::shared_ptr<boost::thread> pTh(new boost::thread(
					boost::bind(&boost::asio::io_service::run,&m_ioService)));
				_listThread.push_back(pTh);
			}

			m_ioService.run();//数据收发逻辑

			//结束所有线程
			BOOST_FOREACH(const boost::shared_ptr<boost::thread> & it,_listThread)
			{
				it->join();//等待线程结束
			}
		}
		catch (std::exception & e)
		{
			std::vector<std::string> ver;
			ver.push_back(boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time()) +"\t"+e.what());
			MyTools::PrintToFile("MsgLog/error.txt",ver,false);
			std::cout << "error：" <<e.what()<< std::endl;//请输入参数
		}
	}
} 

void CServerMain::OnStop()
{
	CClientList::instance()->OnStop();

	m_ioService.stop();//停止
	m_mainThrd.join();
	CClientList::instance()->OnClear();
}

void CServerMain::OnStart()
{
	m_mainThrd = boost::thread(boost::bind(&CServerMain::StartServer,this));//用于与客户端连接线程
	m_mainThrd.yield();//自动运行

	CClientList::instance()->OnStart();
}

