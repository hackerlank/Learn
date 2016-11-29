#pragma once
#include "DBProtSvr.h"

using namespace NDBProt;

class CDBProtS : public CDBProtSvr
{
public:
	//接收：查询请求
	virtual void OnRecv_QueryReq(
		UINT32 dwTransID, //事务的ID
        EQueryType eQueryType, //查询类型
		const SQuery& query //查询
		);
};
