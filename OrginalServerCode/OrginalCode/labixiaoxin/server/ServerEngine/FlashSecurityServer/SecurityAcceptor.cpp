#include "SecurityAcceptor.h"

//#if _MEMORY_DEBUG
//#include "../GameBase/Common/debugnew.h"
//#define new new(__FILE__, __LINE__)
//#endif


SecurityAcceptor::SecurityAcceptor()
{
}

SecurityHandler *SecurityAcceptor::make_handler(void)
{
	return (new SecurityHandler());
}