#include "stdafx.h"
#include "Protocols.h"

//接收：测试函数返回
void CGameSvrCommC::OnRecv_TestFuncAck(
	const STest& rTest //参数1
	)
{
	LOG_DBG << "Recved: " << rTest.dwParam;
}