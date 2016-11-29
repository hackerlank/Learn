#include "stdafx.h"
#include "QueryDBEvt.h"

//接收：查询请求
void CDBProtS::OnRecv_QueryReq(
	UINT32 dwTransID, //事务的ID
    EQueryType eQueryType, //查询类型
	const SQuery& query //查询
	)
{
	EHostType ePeerType = GetPeerType();
	UINT32 dwSvrID = GetCurSvrID();
	CQueryDBEvtPtr pQueryDBEvt(new CQueryDBEvt(dwTransID, const_cast<SQuery&>(query), ePeerType, dwSvrID, *this));
	if(pQueryDBEvt == NULL)
		return;
    //assert(eQueryType == eQueryNormal);
    LOG_INF <<"Query Type is "<< eQueryType<< "string is" <<query.strQuery;
    CDBMgr::Instance().PushQueryEvt(eQueryType, pQueryDBEvt);
}
