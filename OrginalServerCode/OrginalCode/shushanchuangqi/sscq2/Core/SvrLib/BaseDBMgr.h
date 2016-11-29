/********************************************************************
//	Server Common Source File.
//	File name:	BaseDBMgr.h
//	Created:	2011/06/03	15:00
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

#pragma once
#include <atomic>
#include "BaseDBEvt.h"
#include "DBProt.h"
#include "RTime.h"

using namespace std;
using namespace NDBProt;

typedef CSpinLock CLock;

struct SQueryInfo
{
	bool bUsed;
	list<IDBEvtPtr> lstQueryEvt;
	atomic<UINT32> dwQueryCount;
	CLock oLock;

	SQueryInfo() : bUsed(false) { }
};
typedef function<void(INT8, mysqlpp::SimpleResult&)> FnOnSimpResult;
typedef function<void(INT8, mysqlpp::StoreQueryResult&)> FnOnDataResult;

class CModifyDBEvt : public IDBEvt
{
public:
	CModifyDBEvt(const string& strSQL, mysqlpp::SQLQueryParms* pParams, FnOnSimpResult fnOnResult) : _fnOnResult(fnOnResult), _bNeedParse(pParams != NULL)
	{
		_strQuery = strSQL;
		if(pParams != NULL)
			_sqp = *pParams;
	}

	virtual void OnQuery(mysqlpp::Connection& rCon) override
	{
		_query = rCon.query(_strQuery);
		if(_bNeedParse)
		{
			_query.parse();
			_simpRes = _query.execute(_sqp);
		}
		else
		{
			_simpRes = _query.execute();
		}
		while(_query.more_results())
			_query.store_next();
	}

	virtual bool OnResult() override
	{
		if(_fnOnResult)
			_fnOnResult(_byRet, _simpRes);
		return true;
	}

protected:
	FnOnSimpResult _fnOnResult;
	bool _bNeedParse;
};

typedef shared_ptr<CModifyDBEvt> CModifyDBEvtPtr;

class CSelectDBEvt : public IDBEvt
{
public:
	CSelectDBEvt(const string& strSQL, mysqlpp::SQLQueryParms* pParams, FnOnDataResult fnOnResult) : _fnOnResult(fnOnResult), _bNeedParse(pParams != NULL)
	{
		_strQuery = strSQL;
		if(pParams != NULL)
			_sqp = *pParams;
	}

	virtual void OnQuery(mysqlpp::Connection& rCon) override
	{
		_query = rCon.query(_strQuery);
		if(_bNeedParse)
		{
			_query.parse();
			_dataRes = _query.store(_sqp);
		}
		else
		{
			_dataRes = _query.store();
		}
		while(_query.more_results())
		{
			mysqlpp::StoreQueryResult res = _query.store_next();
			if(!res.empty())
				assert(false);
		}
		assert(!_query.more_results());
	}

	virtual bool OnResult() override
	{
		if(_fnOnResult)
			_fnOnResult(_byRet, _dataRes);
		return true;
	}

protected:
	FnOnDataResult _fnOnResult;
	bool _bNeedParse;
};

typedef shared_ptr<CSelectDBEvt> CSelectDBEvtPtr;


class CDBProcessor;

class CBaseDBMgr
{
public:
	CBaseDBMgr();
	virtual ~CBaseDBMgr();
	static CBaseDBMgr& Instance();
	bool Init();
	bool Start(map<EQueryType, UINT8>& mapThreadCount);
	void Stop();
	bool IsRunning() const { return _bRun; }

	virtual bool InitDataBase(mysqlpp::Query& query) { return false; }

	static void QueryThread(CBaseDBMgr* pThis, CDBProcessor* pProc);
	static bool ProcessResult();

	void PushQueryEvt(EQueryType eQueryType, const IDBEvtPtr& pDBEvt);
	IDBEvtPtr PopQueryEvt(EQueryType eQueryType);

	void PushResultEvt(const IDBEvtPtr& pDBEvt);
	IDBEvtPtr PopResultEvt();
//杂项专用线程
	bool DoModifyQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult);
	bool DoSelectQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::StoreQueryResult&)> fnOnDataResult);
 /*
	bool DoSaveQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult);
   */
 //角色数据线程
 //
	bool DoMailModifyQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult);
	bool DoMailSelectQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::StoreQueryResult&)> fnOnDataResult);
    //竞技场专用线程
    bool DoArenaModifyQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult);
	bool DoArenaSelectQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::StoreQueryResult&)> fnOnDataResult);

    // 帮派专用线程
	bool DoGuildModifyQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult);
	bool DoGuildSelectQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::StoreQueryResult&)> fnOnDataResult);

    // 排行榜专用线程
	bool DoRankModifyQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult);
	bool DoRankSelectQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::StoreQueryResult&)> fnOnDataResult);

    // 充值专用线程
	bool DoRechargeModifyQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult);
	bool DoRechargeSelectQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::StoreQueryResult&)> fnOnDataResult);


	UINT32 GetQueryCount(EQueryType eQueryType);

	void AddQueryTick(UINT64 qwTick) { _qwTotolTick += qwTick; ++_dwFinishCount; }
	UINT32 GetAverageTick() const { return UINT32(_qwTotolTick / _dwFinishCount); }
	string GetListLength();
	void PrintListLength();

private:

	bool _bRun;
	list<IDBEvtPtr> _lstResultEvt;
	CLock _oResLock;
	atomic<UINT32> _dwResultCount;

	SQueryInfo _arQueryInfo[eQueryEnd];

	vector<CDBProcessor*> _vecDBProc;
	UINT32 _dwFinishCount;
	UINT64 _qwTotolTick;

	static CBaseDBMgr* _sDBMgr;
};
