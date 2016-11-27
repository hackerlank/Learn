#ifndef BASE_NET_SERVICE_H
#define BASE_NET_SERVICE_H
#include "baseService.h"
#include "baseTaskPool.h"
#include <netinet/in.h>
#include "baseTcpService.h"
class NetService : public Service
{
	public:
		virtual ~NetService();
		virtual void newTcpTask(const int sock,const struct sockaddr_in *addr) = 0;
		virtual const SDWORD getPoolState() const
		{
			return 0;
		}
		const DWORD getPoolSize() const;
		static NetService &getInstance()
		{
			return Service::getInstance<NetService>();
		}
	protected:
		NetService(const std::string &name);
		TcpTaskPool *m_taskPool;
		bool init(const WORD port);
		bool serviceCallBack();
		void final();
	private:
		TcpService *m_tcpService;
	protected:
		virtual void switchAnalysis(bool switchON)
		{
		}
};
#endif
