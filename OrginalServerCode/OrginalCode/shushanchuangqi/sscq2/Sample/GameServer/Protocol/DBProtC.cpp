#include "stdafx.h"
#include "Protocols.h"
#include "DBQueryMgr.h"

//接收：无结果集的返回
void CDBProtC::OnRecv_ResultRet(
    UINT32 dwTransID, //事务的ID
    INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
    UINT32 dwAffectRow //影响的行数
)
{
	switch(GetPeerType())
	{
	case eHostLog:
		g_LogQueryMgr.OnResult(dwTransID, byRet, dwAffectRow);
		break;
	case eHostDB:
		g_DBQueryMgr.OnResult(dwTransID, byRet, dwAffectRow);
		break;
    default:
        break;
	}
}

//接收：有结果集的返回
void CDBProtC::OnRecv_ResultDataRet(
    UINT32 dwTransID, //事务的ID
    INT8 byRet, //返回结果：0为成功，1为语法错误，2为参数错误，3为其它错误
    const TVecTable& vecTable, //返回的结果表集
    UINT8 byCount //结果表数量
)
{
	switch(GetPeerType())
	{
	case eHostLog:
		g_LogQueryMgr.OnResultData(dwTransID, byRet, vecTable, byCount);
		break;
	case eHostDB:
		g_DBQueryMgr.OnResultData(dwTransID, byRet, vecTable, byCount);
		break;
    default:
        break;
	}
}
