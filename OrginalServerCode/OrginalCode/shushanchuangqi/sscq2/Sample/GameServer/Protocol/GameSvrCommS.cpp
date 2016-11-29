#include "stdafx.h"
#include "Protocols.h"

//接收：测试函数请求
void CGameSvrCommS::OnRecv_TestFuncReq(
	const STest& rTest //参数1
	)
{
	LOG_DBG << "Recved: " << rTest.dwParam;
	Send_TestFuncAck(rTest);
}

//接收：测试返回函数请求
bool CGameSvrCommS::OnRecv_TestRetFuncReq(
	const STest& rTest, //参数1
    shared_func<STestRetFuncReqAck>& fnAck //返回回调函数
	)
{
    fnAck->dwRetParam = 2;
	return true;
}
