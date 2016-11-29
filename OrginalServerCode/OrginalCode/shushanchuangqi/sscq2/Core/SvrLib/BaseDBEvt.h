#pragma once
#include <string>
#include <vector>
#ifndef MYSQLPP_NO_DLL
#define MYSQLPP_NO_DLL
#endif
#ifndef MYSQLPP_EXPORT
#define MYSQLPP_EXPORT
#endif
#include <mysql++.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <Linux.h>
#endif
#include "ObjPool.h"
#include "ServerDefine.h"

using namespace std;

#define MAX_PRINT_SQL_LENGTH 0x100
/*
 
bref: 数据库查询事件的接口类
 *
 *
 *
 */
class IDBEvt : public enable_shared_from_this<IDBEvt>
{
	friend class CBaseDBMgr;
	friend class CDBProcessor;
public:
	IDBEvt() : _byRet(0), _query(NULL), _wPushCount(0) { }
	virtual ~IDBEvt() { }
	virtual void OnQuery(mysqlpp::Connection& rCon) = 0;
	virtual bool OnResult() { return true; }
	void SetRet(INT8 byRet) { _byRet = byRet; }
	virtual string GetQueryStr() const { return _strQuery.size() > MAX_PRINT_SQL_LENGTH ? _strQuery.substr(0, MAX_PRINT_SQL_LENGTH) : _strQuery; }
protected:
	//查询返回值：0为成功，-1为查询串错误，-2为数据转换错误，-3为连接错误，-4为其它错误，正数为用户定义错误
	INT8 _byRet;
	mysqlpp::Query _query;
	mysqlpp::SQLQueryParms _sqp;
	mysqlpp::StoreQueryResult _dataRes;
	mysqlpp::SimpleResult _simpRes;
	UINT16 _wPushCount;
	string _strQuery;
};

typedef shared_ptr<IDBEvt> IDBEvtPtr;
typedef weak_ptr<IDBEvt> IDBEvtWtr;
