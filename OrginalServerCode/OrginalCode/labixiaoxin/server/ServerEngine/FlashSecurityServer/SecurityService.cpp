#include "SecurityService.h"

#include "ace\Proactor.h"

SecurityService::SecurityService()
{

}

SecurityService::~SecurityService()
{

}

void SecurityService::activate(char *strIP)
{
	//ACE_INET_Addr listen_addr(30000, strIP);
	ACE_INET_Addr listen_addr(30000, "192.168.1.12");

	_listener.open(listen_addr);

	intptr_t nRc = ACE_Proactor::instance()->proactor_run_event_loop();

	while(ACE_Proactor::instance()->proactor_event_loop_done() != 1)
	{
		Sleep(1);
	}
}