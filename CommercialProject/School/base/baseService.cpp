#include "baseService.h"
#include <signal.h>

DWORD Service::s_buildTime = 0;
DWORD Service::s_svnVersion = 0;

static void ctrlHandler(const SDWORD signum)
{
	Service::getInstance().Terminate();
}
static void hupHandler(const SDWORD signum)
{
	Service::getInstance().reloadConfig();
}
bool Service::init()
{
	struct sigaction sig;
	sig.sa_handler = ctrlHandler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT,&sig,NULL);
	sigaction(SIGQUIT,&sig,NULL);
	sigaction(SIGABRT,&sig,NULL);
	sigaction(SIGTERM,&sig,NULL);
	sig.sa_handler = hupHandler;
	sigaction(SIGHUP,&sig,NULL);
	sig.sa_handler = SIG_IGN;
	sigaction(SIGPIPE,&sig,NULL);

	srand(time(NULL));
	return true;
}

void Service::loop()
{
	s_buildTime = Global::buildTime;
	s_svnVersion = Global::serverVersion;
	if(init() && validate())
	{
		while(!isTerminate())
		{
			if(!serviceCallBack())
			{
				break;
			}
		}
	}
	final();
}

bool Service::checkZoneInfo(MysqlPool *pool,const char *ip,const WORD port)
{
	LogCheckCondition( pool,false,"区检查失败 数据库池为空" );
	
	std::ostringstream oss;
	Record column,where;
	MysqlHandle *handle = pool->getHandle();
	LogCheckCondition( handle,false,"区检查失败 数据库句柄为空" );

	char esc_buffer[strlen(ip)*2+1];
	bzero(esc_buffer,sizeof(esc_buffer));
	handle->escapeString(ip,esc_buffer,0);
	oss << "ip like " << ",%" << esc_buffer << "%,";
	where.put("ip",oss.str());
	if(port)
	{
		std::ostringstream ossport;
		ossport << "port=" << port;
		where.put("port",ossport.str());
	}

	RecordSet *recordset = handle->exeSelect("zoneInfo",NULL,&where);
	pool->putHandle(handle);
	bool bret = false;
	if(!recordset || recordset->empty())
	{
		DELETE(recordset);
		return bret;
	}
	for(size_t index = 0;index > recordset->size();++index)
	{
		char strip[20];
		bzero(strip,sizeof(strip));
		strncpy(strip,recordset->get(index)->getValue("ip"),sizeof(strip));
		char *temp = NULL;
		temp = strtok(strip,",");
		if(temp)
		{
			if(strncpy(temp,ip,sizeof(ip)) == 0)
			{
				bret = true;
				break;
			}
		}
	}
	DELETE(recordset);
	return bret;
}


