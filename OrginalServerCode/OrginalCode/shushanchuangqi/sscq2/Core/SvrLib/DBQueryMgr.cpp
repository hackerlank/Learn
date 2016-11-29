/********************************************************************
//	Server Common Source File.
//	File name:	DBQueryMgr.cpp
//	Created:	2011/05/30	10:00
//	Organization:
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:
//	Version:	1.0
//	Histroy:
*********************************************************************/

#include "DBQueryMgr.h"
#include "Config.h"
#include "NetMgr.h"

const SRes& operator>>(const SRes& src, string& str)
{
	str = src.strVal;
	return src;
}

const SRes& operator>>(const SRes& src, mysqlpp::DateTime& rDateTime)
{
	rDateTime.convert(src.strVal.c_str());
	return src;
}

const SRes& operator>>(const SRes& src, mysqlpp::Date& rDate)
{
	rDate.convert(src.strVal.c_str());
	return src;
}

const SRes& operator>>(const SRes& src, mysqlpp::Time& rTime)
{
	rTime.convert(src.strVal.c_str());
	return src;
}

void CQuery::AddParam(const mysqlpp::DateTime& rDateTime)
{
	vecParam.emplace_back(eTypeDateTime, rDateTime.str());
}

void CQuery::AddParam(const mysqlpp::Date& rDate)
{
	vecParam.emplace_back(eTypeDate, rDate.str());
}

void CQuery::AddParam(const mysqlpp::Time& rTime)
{
	vecParam.emplace_back(eTypeTime, rTime.str());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define QUERY_TIMEOUT_SEC 5 * 60

CDBQueryMgr g_DBQueryMgr;		//DBServer连接
CDBQueryMgr g_LogQueryMgr;		//LogServer连接

void CDBQueryMgr::Init(CDBProtClt& rDBProt)
{
	_pDBProt = &rDBProt;
}

bool CDBQueryMgr::DoQuery(IDBQuery& rDBQuery, EQueryType eQueryType /*= eQueryNormal*/)
{
	CConfig* pConfig = CConfig::GetConfig();
	if(pConfig != NULL && pConfig->_bIsCrossServer)
		return false;
	if(_pDBProt == NULL)
	{
		LOG_CRI << "_pDBProt is NULL!";
		return false;
	}
	UINT32 dwTransID = _dwNextTransID;
	++_dwNextTransID;
	if(_dwNextTransID == 0)
		_dwNextTransID = 1;
	if(_pDBProt->Send_QueryReq(dwTransID, eQueryType, rDBQuery))
	{
		rDBQuery._tStartTime = time(NULL);
		_mapID2Query.insert(make_pair(dwTransID, ToThisPtr(rDBQuery)));
		return true;
	}
	return false;
}

bool CDBQueryMgr::DoQuerySvr(EHostType eType, UINT32 dwSvrID, IDBQuery& rDBQuery, EQueryType eQueryType /*= eQueryNormal*/)
{
	if(_pDBProt == NULL || 0 == dwSvrID)
	{
		LOG_CRI << "_pDBProt is NULL!";
		return false;
	}
	CNetMgr* pNetMgr = CNetMgr::GetNetMgr();
	if (NULL == pNetMgr)
	{
		LOG_CRI << "CNetMgr is NULL";
		return false;
	}

	CSvrHandler* pSvrHandler = pNetMgr->GetSvrHandler(eType);
	if (NULL == pSvrHandler)
	{
		LOG_CRI << "CSvrHandler is NULL Type : " << eType;
		return false;
	}
	
	UINT32 dwTransID = _dwNextTransID;
	++_dwNextTransID;
	if(_dwNextTransID == 0)
		_dwNextTransID = 1;

	std::string& strMsg = _pDBProt->BuildPkg_QueryReq(dwTransID, eQueryType, rDBQuery);
	if(pSvrHandler->SendSvr(&dwSvrID, 1, &strMsg[0], (UINT32)strMsg.size()))
	{
		rDBQuery._tStartTime = time(NULL);
		_mapID2Query.insert(make_pair(dwTransID, ToThisPtr(rDBQuery)));
		return true;
	}
	return false;
}

void CDBQueryMgr::OnResult(UINT32 dwTransID, INT8 byRet, UINT32 dwAffectRow)
{
	auto it = _mapID2Query.find(dwTransID);
	if(it == _mapID2Query.end())
		return;
	IDBQuery& rDBQuery = *it->second;
	rDBQuery.OnResult(byRet, dwAffectRow);
	_mapID2Query.erase(it);
}

void CDBQueryMgr::OnResultData(UINT32 dwTransID, INT8 byRet, const TVecTable& vecTable, UINT8 byCount)
{
	auto it = _mapID2Query.find(dwTransID);
	if(it == _mapID2Query.end())
		return;
	IDBQuery& rDBQuery = *it->second;
	if(rDBQuery._vecTable.size() != byCount)
	{
		rDBQuery._vecTable.resize(byCount);
		for(size_t i = 0; i < rDBQuery._vecTable.size(); ++i)
			rDBQuery._vecTable[i].byIndex = (UINT8)i;
	}
	bool bMore = false;
	for(size_t i = 0; i < vecTable.size(); ++i)
	{
		const STable& rSrcTable = vecTable[i];
		if(rSrcTable.byIndex < byCount)
		{
			STable& rDestTable = rDBQuery._vecTable[rSrcTable.byIndex];
			rDestTable.vecRow.insert(rDestTable.vecRow.end(), rSrcTable.vecRow.begin(), rSrcTable.vecRow.end());
			if(rSrcTable.bMore)
				bMore = true;
		}
		else
		{
			LOG_CRI << "Exception. rSrcTable.byIndex=" << rSrcTable.byIndex << " byCount=" << byCount << " strQuery=" << rDBQuery.strQuery;
		}
	}
	if(!bMore)
	{
		rDBQuery.OnResultData(byRet, rDBQuery._vecTable);
		_mapID2Query.erase(it);
	}
}

struct SModifyDBQuery : public IDBQuery
{
	function<void(INT8, UINT32)> fnCallback;
	virtual void OnResult(INT8 byRet, UINT32 dwAffectRow) override
	{
		if(fnCallback != nullptr)
			fnCallback(byRet, dwAffectRow);
	}
};

struct SSelectDBQuery : public IDBQuery
{
	function<void(INT8, const TVecTable&)> fnCallback;
	virtual void OnResultData(INT32 byRet, const TVecTable& rVecTable) override
	{
		if(fnCallback != nullptr)
			fnCallback(byRet, rVecTable);
	}
};

bool CDBQueryMgr::DoModifyQuery(CQuery& rQuery, function<void(INT8 byRet, UINT32 dwAffectRow)> fnSimpResult /*= nullptr*/, EQueryType eQueryType /*= eQueryNormal*/)
{
	shared_ptr<SModifyDBQuery> pDBQuery(new SModifyDBQuery);
	if(pDBQuery == NULL)
		return false;
	(CQuery&)*pDBQuery = rQuery;
	pDBQuery->SetHasResult(false);
	pDBQuery->fnCallback = fnSimpResult;
	return DoQuery(*pDBQuery, eQueryType);
}

bool CDBQueryMgr::DoModifyQuery(const string& strSQL, function<void(INT8 byRet, UINT32 dwAffectRow)> fnSimpResult /*= nullptr*/, EQueryType eQueryType /*= eQueryNormal*/)
{
	CQuery oQuery;
	oQuery.strQuery = strSQL;
	return DoModifyQuery(oQuery, fnSimpResult, eQueryType);
}

bool CDBQueryMgr::DoSelectQuery(CQuery& rQuery, function<void(INT8 byRet, const TVecTable& vecTable)> fnDataResult /*= nullptr*/, EQueryType eQueryType /*= eQueryNormal*/)
{
	shared_ptr<SSelectDBQuery> pDBQuery(new SSelectDBQuery);
	if(pDBQuery == NULL)
		return false;
	(CQuery&)*pDBQuery = rQuery;
	pDBQuery->SetHasResult(true);
	pDBQuery->fnCallback = fnDataResult;
	return DoQuery(*pDBQuery, eQueryType);
}

bool CDBQueryMgr::DoSelectQuery(const string& strSQL, function<void(INT8 byRet, const TVecTable& vecTable)> fnDataResult /*= nullptr*/, EQueryType eQueryType /*= eQueryNormal*/)
{
	CQuery oQuery;
	oQuery.strQuery = strSQL;
	return DoSelectQuery(oQuery, fnDataResult, eQueryType);
}

void CDBQueryMgr::TimerCheck(time_t tNow)
{
	for(auto it = _mapID2Query.begin(); it != _mapID2Query.end();)
	{
		IDBQuery& rDBQuery = *it->second;
		if(tNow > rDBQuery._tStartTime && tNow - rDBQuery._tStartTime > QUERY_TIMEOUT_SEC)
		{
			if(rDBQuery.bHasResult)
				rDBQuery.OnResultData(2, TVecTable());
			else
				rDBQuery.OnResult(2, 0);
			it = _mapID2Query.erase(it);
		}
		else
		{
			++it;
		}
	}
}
