/********************************************************************
//	Server Common Source File.
//	File name:	BaseDBMgr.cpp
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

#include "BaseDBMgr.h"
#include "Config.h"
#include "UtilFunc.h"

///////////////////////////////////////////////////////////////////////////////////////////

class CDBProcessor
{
	friend class CBaseDBMgr;
public:
	CDBProcessor(EQueryType eQueryType) : _eQueryType(eQueryType), _tLastPingTime(0) { }
	bool Connect();
	void Run();
	bool Ping();
	bool KeepAlive();
protected:
	EQueryType _eQueryType;
	mysqlpp::Connection _con;
	time_t _tLastPingTime;
	CThread _thread;
};

bool CDBProcessor::Connect()
{
	mysqlpp::NoExceptions ne(_con);
	_con.disconnect();
	if(!_con.set_option(new mysqlpp::MultiStatementsOption(true))
		|| !_con.set_option(new mysqlpp::MultiResultsOption(true))
		|| !_con.set_option(new mysqlpp::ReconnectOption(true)))
	{
		LOG_CRI << "set_option fails!";
		return false;
	}
	CConfig* pConfig = CConfig::GetConfig();
	if(!_con.connect(pConfig->_strDBName.c_str(), pConfig->_strDBAddr.c_str(), pConfig->_strDBUser.c_str(), pConfig->_strDBPassword.c_str(), pConfig->_wDBPort))
		return false;
	if(!_con.select_db(pConfig->_strDBName))
		return false;
    // XXX: SET NAMES UTF8
    mysqlpp::Query query = _con.query();
    query << "SET NAMES UTF8;";
    query.execute();
	return true;
}

void CDBProcessor::Run()
{
	_thread.Start(CBaseDBMgr::QueryThread, &CBaseDBMgr::Instance(), this);
}

bool CDBProcessor::Ping()
{
	if(!_con.ping())
	{
		LOG_WRN << "mysql ping fails!";
		if(!Connect())
		{
			LOG_CRI << "Cannot connect MySQL!";
			return false;
		}
	}
	return true;
}

#define PING_INTERVAL_SECONDS 20

bool CDBProcessor::KeepAlive()
{
	time_t tNow = time(NULL);
	if(tNow > _tLastPingTime && tNow - _tLastPingTime > PING_INTERVAL_SECONDS && Ping())
	{
		_tLastPingTime = tNow;
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////

CBaseDBMgr* CBaseDBMgr::_sDBMgr;

CBaseDBMgr::CBaseDBMgr() : _bRun(false), _dwResultCount(0), _dwFinishCount(0), _qwTotolTick(0)
{
	_sDBMgr = this;
}

CBaseDBMgr::~CBaseDBMgr()
{
	Stop();
}

CBaseDBMgr& CBaseDBMgr::Instance()
{
	return *_sDBMgr;
}

bool CBaseDBMgr::Init()
{
	CConfig* pConfig = CConfig::GetConfig();
	try {
		mysqlpp::Connection con(NULL, pConfig->_strDBAddr.c_str(), pConfig->_strDBUser.c_str(), pConfig->_strDBPassword.c_str(), pConfig->_wDBPort);
		{
			mysqlpp::NoExceptions ne(con);
			if(!con.select_db(pConfig->_strDBName))
			{
#if 0
				// Database doesn't exist yet, so create and select it.
				if(!con.create_db(pConfig->_strDBName) || !con.select_db(pConfig->_strDBName))
				{
					LOG_CRI << "Error creating DB: " << con.error();
					return false;
				}
#else
                LOG_CRI << "Execute DBInitPatch.inc......";
#include "DBInitPatch.inc"
#endif
			}
		}

        LOG_CRI << "Execute DBUpdatePatch.inc......";
#include "DBUpdatePatch.inc"

		mysqlpp::Query query = con.query();
		InitDataBase(query);
	}
	catch(const mysqlpp::BadQuery& er)
	{
		// Handle any query errors
		LOG_CRI << "Query error: " << er.what();
		return false;
	}
	catch(const mysqlpp::BadConversion& er)
	{
		// Handle bad conversions
		LOG_CRI << "Conversion error: " << er.what() <<
			"\tretrieved data size: " << er.retrieved <<
			", actual size: " << er.actual_size;
		return false;
	}
	catch(const mysqlpp::Exception& er)
	{
		// Catch-all for any other MySQL++ exceptions
		LOG_CRI << "Error: " << er.what();
		return false;
	}
	return true;
}

bool CBaseDBMgr::Start(map<EQueryType, UINT8>& mapThreadCount)
{
	_bRun = true;
	for(auto& p : mapThreadCount)
	{
		CDBProcessor* pDBProcessor = NULL;
		EQueryType eQueryType = p.first;
		UINT8 byCount = p.second;
		if(byCount > 0)
			_arQueryInfo[eQueryType].bUsed = true;
		for(UINT8 i = 0; i < byCount; ++i)
		{
			pDBProcessor = new CDBProcessor(eQueryType);
			if(pDBProcessor == NULL)
				return false;
			_vecDBProc.push_back(pDBProcessor);
		}
	}
	for(auto& pDBProcessor : _vecDBProc)
	{
		if(!pDBProcessor->Connect())
		{
			delete pDBProcessor;
			return false;
		}
		pDBProcessor->Run();
	}
	return true;
}

void CBaseDBMgr::Stop()
{
	_bRun = false;
	for(size_t i = 0; i < _vecDBProc.size(); ++i)
	{
		_vecDBProc[i]->_thread.Join();
		delete _vecDBProc[i];
	}
	_vecDBProc.clear();
}

void CBaseDBMgr::QueryThread(CBaseDBMgr* pThis, CDBProcessor* pProc)
{
    UINT32 dwSleepTimer = 25;
	IDBEvtPtr pDBEvt;
	UINT64 qwStartTick = 0, qwTotalTick = 0;
	while(pThis->IsRunning() || pDBEvt != NULL)
	{
		pDBEvt = pThis->PopQueryEvt(pProc->_eQueryType);
REDO:
		if(pDBEvt != NULL)
		{
			try
			{
				pDBEvt->SetRet(0);
				qwStartTick = GetTickCount64();
				pDBEvt->OnQuery(pProc->_con);
				qwTotalTick = GetTickCount64() - qwStartTick;
				pThis->AddQueryTick(qwTotalTick);
//#ifdef _DEBUG
				if(qwTotalTick > 100)
					LOG_INF << LOGCTL_NO_CONSOLE << "Query overtime: " << qwTotalTick << ". Query: " << pDBEvt->GetQueryStr();
//#endif
			}
			catch(const mysqlpp::BadQuery& er)
			{
				// Handle any query errors
				LOG_CRI << "Query error: " << er.what() << ". Query: " << pDBEvt->GetQueryStr();
				pDBEvt->SetRet(-1);
				if(er.errnum() == 2006)
				{
					//assert(strcasecmp(er.what(), "MySQL server has gone away") == 0);
					if(!pProc->Ping())
						Sleep(1000);
					goto REDO;
				}
			}
			catch(const mysqlpp::BadConversion& er)
			{
				// Handle bad conversions
				LOG_CRI << "Conversion error: " << er.what() <<
					"\tretrieved data size: " << er.retrieved <<
					", actual size: " << er.actual_size << ". Query: " << pDBEvt->GetQueryStr();
				pDBEvt->SetRet(-2);
			}
			catch(const mysqlpp::ConnectionFailed& er)
			{
				LOG_WRN << "Connection fails: " << er.what() << ". Query: " << pDBEvt->GetQueryStr();
				pDBEvt->SetRet(-3);
				if(!pProc->Ping())
					Sleep(1000);
				goto REDO;
			}
			catch(const mysqlpp::Exception& er)
			{
				// Catch-all for any other MySQL++ exceptions
				LOG_CRI << "Error: " << er.what() << ". Query: " << pDBEvt->GetQueryStr();
				pDBEvt->SetRet(-4);
			}
			pDBEvt->_query.reset();
			pThis->PushResultEvt(pDBEvt);
		}
		else if(!pProc->KeepAlive())
		{
			Sleep(dwSleepTimer);
		}
	}
}

bool CBaseDBMgr::ProcessResult()
{
	if(!Instance()._bRun)
		return false;
	IDBEvtPtr pDBEvt = Instance().PopResultEvt();
	if(pDBEvt == NULL)
		return false;
	if(pDBEvt->OnResult())
		return true;
	if(pDBEvt->_wPushCount <= 200)
		Instance().PushResultEvt(pDBEvt);
	else
		LOG_CRI << "Too much push count!";
	return true;
}

void CBaseDBMgr::PushQueryEvt(EQueryType eQueryType, const IDBEvtPtr& pDBEvt)
{
	if(!_bRun)
		return;
	assert(eQueryType < ARRAYSIZE(_arQueryInfo));
	SQueryInfo& rQueryInfo = _arQueryInfo[eQueryType];
	assert(rQueryInfo.bUsed);
	++rQueryInfo.dwQueryCount;
	CAutoLock<CLock> oAutoLock(rQueryInfo.oLock);
	rQueryInfo.lstQueryEvt.push_back(pDBEvt);
}

IDBEvtPtr CBaseDBMgr::PopQueryEvt(EQueryType eQueryType)
{
	if(!_bRun)
		return NULL;
	assert(eQueryType < ARRAYSIZE(_arQueryInfo));
	SQueryInfo& rQueryInfo = _arQueryInfo[eQueryType];
	assert(rQueryInfo.bUsed);
	CAutoLock<CLock> oAutoLock(rQueryInfo.oLock);
	if(rQueryInfo.lstQueryEvt.empty())
		return NULL;
	--rQueryInfo.dwQueryCount;
	IDBEvtPtr pDBEvt = rQueryInfo.lstQueryEvt.front();
	rQueryInfo.lstQueryEvt.pop_front();
	return pDBEvt;
}

void CBaseDBMgr::PushResultEvt(const IDBEvtPtr& pDBEvt)
{
	if(!_bRun)
		return;
	++_dwResultCount;
	CAutoLock<CLock> oAutoLock(_oResLock);
	_lstResultEvt.push_back(pDBEvt);
	++pDBEvt->_wPushCount;
}

IDBEvtPtr CBaseDBMgr::PopResultEvt()
{
	if(!_bRun)
		return NULL;
	IDBEvtPtr pDBEvt = NULL;
	CAutoLock<CLock> oAutoLock(_oResLock);
	if(_lstResultEvt.empty())
		return NULL;
	--_dwResultCount;
	pDBEvt = _lstResultEvt.front();
	_lstResultEvt.pop_front();
	return pDBEvt;
}

string CBaseDBMgr::GetListLength()
{
	string strLength;
	for(size_t i = 0; i < ARRAYSIZE(_arQueryInfo); ++i)
	{
		SQueryInfo& rQueryInfo = _arQueryInfo[i];
		UINT32 dwQueryCount = rQueryInfo.dwQueryCount.load(memory_order_relaxed);
		if(dwQueryCount > 500)
			strLength += "\tQuery List Size: " + NumberToString(dwQueryCount) + ", Type: " + NumberToString(i) + "\n";
	}
	UINT32 dwResultCount = _dwResultCount.load(memory_order_relaxed);
	if(dwResultCount > 50)
		strLength += "\tResult List Size: " + NumberToString(dwResultCount) + "\n";
	return strLength;
}

void CBaseDBMgr::PrintListLength()
{
	if(!_bRun)
		return;
	for(size_t i = 0; i < ARRAYSIZE(_arQueryInfo); ++i)
	{
		SQueryInfo& rQueryInfo = _arQueryInfo[i];
		UINT32 dwQueryCount = rQueryInfo.dwQueryCount.load(memory_order_relaxed);
		if(dwQueryCount > 500)
			LOG_INF << "Query List Size: " << dwQueryCount << ", Type: " << i;
	}
	UINT32 dwResultCount = _dwResultCount.load(memory_order_relaxed);
	if(dwResultCount > 50)
		LOG_INF << "Result List Size: " << dwResultCount;
}

bool CBaseDBMgr::DoModifyQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult)
{
	CModifyDBEvtPtr pModifyDBEvt(new CModifyDBEvt(strSQL, pParams, fnOnSimpResult));
	if(pModifyDBEvt == NULL)
		return false;
	PushQueryEvt(eQueryNormal, pModifyDBEvt);
	return true;
}

bool CBaseDBMgr::DoMailModifyQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult)
{
	CModifyDBEvtPtr pModifyDBEvt(new CModifyDBEvt(strSQL, pParams, fnOnSimpResult));
	if(pModifyDBEvt == NULL)
		return false;
	PushQueryEvt(eQueryMail, pModifyDBEvt);
	return true;
}

bool CBaseDBMgr::DoGuildModifyQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult)
{
	CModifyDBEvtPtr pModifyDBEvt(new CModifyDBEvt(strSQL, pParams, fnOnSimpResult));
	if(pModifyDBEvt == NULL)
		return false;
	PushQueryEvt(eQueryGuild, pModifyDBEvt);
	return true;
}

bool CBaseDBMgr::DoRankModifyQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult)
{
	CModifyDBEvtPtr pModifyDBEvt(new CModifyDBEvt(strSQL, pParams, fnOnSimpResult));
	if(pModifyDBEvt == NULL)
		return false;
	PushQueryEvt(eQueryRank, pModifyDBEvt);
	return true;
}

bool CBaseDBMgr::DoArenaModifyQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult)
{
	CModifyDBEvtPtr pModifyDBEvt(new CModifyDBEvt(strSQL, pParams, fnOnSimpResult));
	if(pModifyDBEvt == NULL)
		return false;
	PushQueryEvt(eQueryArena, pModifyDBEvt);
	return true;
}

bool CBaseDBMgr::DoRechargeModifyQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult)
{
	CModifyDBEvtPtr pModifyDBEvt(new CModifyDBEvt(strSQL, pParams, fnOnSimpResult));
	if(pModifyDBEvt == NULL)
		return false;
	PushQueryEvt(eQueryRecharge, pModifyDBEvt);
	return true;
}

/*
bool CBaseDBMgr::DoSaveQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::SimpleResult&)> fnOnSimpResult)
{
	CModifyDBEvtPtr pModifyDBEvt(new CModifyDBEvt(strSQL, pParams, fnOnSimpResult));
	if(pModifyDBEvt == NULL)
		return false;
	PushQueryEvt(eQuerySave, pModifyDBEvt);
	return true;
}
*/
bool CBaseDBMgr::DoSelectQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::StoreQueryResult&)> fnOnDataResult)
{
	CSelectDBEvtPtr pSelectDBEvt(new CSelectDBEvt(strSQL, pParams, fnOnDataResult));
	if(pSelectDBEvt == NULL)
		return false;
	PushQueryEvt(eQueryNormal, pSelectDBEvt);
	return true;
}

bool CBaseDBMgr::DoMailSelectQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::StoreQueryResult&)> fnOnDataResult)
{
	CSelectDBEvtPtr pSelectDBEvt(new CSelectDBEvt(strSQL, pParams, fnOnDataResult));
	if(pSelectDBEvt == NULL)
		return false;
	PushQueryEvt(eQueryMail, pSelectDBEvt);
	return true;
}

bool CBaseDBMgr::DoGuildSelectQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::StoreQueryResult&)> fnOnDataResult)
{
	CSelectDBEvtPtr pSelectDBEvt(new CSelectDBEvt(strSQL, pParams, fnOnDataResult));
	if(pSelectDBEvt == NULL)
		return false;
	PushQueryEvt(eQueryGuild, pSelectDBEvt);
	return true;
}

bool CBaseDBMgr::DoRankSelectQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::StoreQueryResult&)> fnOnDataResult)
{
	CSelectDBEvtPtr pSelectDBEvt(new CSelectDBEvt(strSQL, pParams, fnOnDataResult));
	if(pSelectDBEvt == NULL)
		return false;
	PushQueryEvt(eQueryRank, pSelectDBEvt);
	return true;
}

bool CBaseDBMgr::DoArenaSelectQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::StoreQueryResult&)> fnOnDataResult)
{
	CSelectDBEvtPtr pSelectDBEvt(new CSelectDBEvt(strSQL, pParams, fnOnDataResult));
	if(pSelectDBEvt == NULL)
		return false;
	PushQueryEvt(eQueryArena, pSelectDBEvt);
	return true;
}

bool CBaseDBMgr::DoRechargeSelectQuery(const string& strSQL, mysqlpp::SQLQueryParms* pParams, function<void(INT8, mysqlpp::StoreQueryResult&)> fnOnDataResult)
{
	CSelectDBEvtPtr pSelectDBEvt(new CSelectDBEvt(strSQL, pParams, fnOnDataResult));
	if(pSelectDBEvt == NULL)
		return false;
	PushQueryEvt(eQueryRecharge, pSelectDBEvt);
	return true;
}

UINT32 CBaseDBMgr::GetQueryCount(EQueryType eQueryType)
{
	SQueryInfo& rQueryInfo = _arQueryInfo[eQueryType];
	return rQueryInfo.dwQueryCount;
}
