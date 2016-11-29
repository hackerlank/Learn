#pragma once
#include "BaseDBEvt.h"
#include "DBProtSvr.h"

using namespace NDBProt;

class CQueryDBEvt : public IDBEvt
{
public:
	DEF_NEW_DELETE(CQueryDBEvt);
	CQueryDBEvt(UINT32 dwTransID, SQuery& rQuery, EHostType ePeerType, UINT32 dwSvrID, CDBProtSvr& rDBProt) : _dwTransID(dwTransID),
		_oQuery(rQuery), _ePeerType(ePeerType), _dwSvrID(dwSvrID), _byTotalCount(0), _rDBProt(rDBProt) { }
	virtual void OnQuery(mysqlpp::Connection& rCon);
	virtual bool OnResult();
	virtual string GetQueryStr() const override { return _strQuery; }
private:
	UINT32 _dwTransID;
	SQuery _oQuery;
	EHostType _ePeerType;
	UINT32 _dwSvrID;

	struct SResult
	{
		UINT8 byIndex;
		mysqlpp::StoreQueryResult dataRes;
		UINT32 dwCurRow;
	};
	vector<SResult> _vecResult;
	UINT8 _byTotalCount;
	string _strQuery;
	CDBProtSvr& _rDBProt;
};
