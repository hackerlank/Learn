#ifndef PLATE_SERVER_H
#define PLATE_SERVER_H

#include <stdio.h>
#include "base/baseNetService.h"
#include "base/baseSubService.h"
#include "base/baseTcpClientTaskPool.h"
#include "base/baseSqlRecord.h"
#include "base/baseSqlPool.h"
#include "base/baseProperty.h"
#include "plateTask.h"

class PlateServer : public NetService
{
	private:
		friend class SingletonBase<Service,false>;
		PlateServer();
		~PlateServer();
		bool init();

		/// @brief 设置服务器基本数据
		bool getServerInfo();
		
		/// @brief 接收新的请求
		void newTcpTask(const SDWORD sock,const struct sockaddr_in *addr );
		
		/// @brief 命令统计开关
		void switchAnalysis(const bool switchFlg);
		
		/// @brief 服务器停机时执行的操作
		void final();

	public:
		static PlateServer& getInstance()
		{
			return Service::getInstance<PlateServer>();
		}
		
		const WORD getID() const
		{
			return m_serverID;
		}
		
		const WORD getType() const
		{
			return m_serverType;
		}
		
		const char* getIP() const
		{
			return m_ip;
		}
		
		const WORD getPort() const
		{
			return m_port;
		}
		
		TcpClientTaskPool* getClientPool()
		{
			return m_clientPool;
		}

	public:
		///数据库连接池
		static MysqlPool *s_mySqlPool;
	private:
		///客户端连接池
		TcpClientTaskPool *m_clientPool;
		/// 服务器编号
		WORD m_serverID;
		/// 服务器类型
		WORD m_serverType;
		/// 服务器ip
		char m_ip[MAX_IP_LENGTH];
		/// 服务器端口
		WORD m_port;
		/// 服务器对外开放ip(只有网关用得着)
		char m_outIP[MAX_IP_LENGTH];
		/// 服务器对外监听端口(只有网关用得着)
		WORD m_outPort;
};

#endif

		
