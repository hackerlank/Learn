#include "baseTcpTaskQueue.h"

bool TcpTaskQueue::parse(const Cmd::NullCmd *cmd,const DWORD cmdLen)
{
	return cmdMsgParse(cmd,cmdLen);
}
