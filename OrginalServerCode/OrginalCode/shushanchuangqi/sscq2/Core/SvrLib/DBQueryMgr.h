/********************************************************************
//	Server Common Source File.
//	File name:	DBQueryMgr.h
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

#pragma once
#include <boost/mpl/map.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/int.hpp>
#ifndef MYSQLPP_NO_DLL
#define MYSQLPP_NO_DLL
#endif
#ifndef MYSQLPP_EXPORT
#define MYSQLPP_EXPORT
#endif
#include <mysql++.h>
#include "DBProtClt.h"

using namespace NDBProt;

typedef mpl::map<
	mpl::pair<mpl::int_<eTypeINT8>, INT8>,
	mpl::pair<mpl::int_<eTypeUINT8>, UINT8>,
	mpl::pair<mpl::int_<eTypeINT16>, INT16>,
	mpl::pair<mpl::int_<eTypeUINT16>, UINT16>,
	mpl::pair<mpl::int_<eTypeINT32>, INT32>,
	mpl::pair<mpl::int_<eTypeUINT32>, UINT32>,
	mpl::pair<mpl::int_<eTypeINT64>, INT64>,
	mpl::pair<mpl::int_<eTypeUINT64>, UINT64>,
	mpl::pair<mpl::int_<eTypeFloat>, float>,
	mpl::pair<mpl::int_<eTypeDouble>, double>
> TMapParamType;

template<typename T>
const SRes& operator>>(const SRes& src, T& val)
{
	static_assert(mpl::and_<is_scalar<T>, mpl::not_<is_pointer<T>>>::value, "None Scalar Data Not Allowed!");
	stringstream buf(src.strVal, ios_base::in);
	if(is_same<T, INT8>::value || is_same<T, UINT8>::value)
	{
		INT32 dwVal = 0;
		buf >> dwVal;
		val = (T)dwVal;
	}
	else
	{
		buf >> val;
	}
	return src;
}

const SRes& operator>>(const SRes& src, string& str);
const SRes& operator>>(const SRes& src, mysqlpp::DateTime& rDateTime);
const SRes& operator>>(const SRes& src, mysqlpp::Date& rDate);
const SRes& operator>>(const SRes& src, mysqlpp::Time& rTime);

class CQuery : public SQuery
{
public:
	void AddSQL(const string& strSQL) { strQuery = strSQL; }

	template<EParamType eParamType, typename T>
	void AddParam(T val)
	{
		typedef typename mpl::at<TMapParamType, mpl::int_<eParamType>>::type TVal;
		static_assert(is_same<T, TVal>::value, "eParamType and T should be consistent!");

		string str;
		str.assign((char*)&val, sizeof val);
		vecParam.emplace_back(eParamType, move(str));
	}

	template<EParamType eParamType>
	void AddParam(const string& val)
	{
		static_assert(eParamType == eTypeString || eParamType == eTypeBlob, "eParamType is invalid!");
		vecParam.emplace_back(eParamType, val);
	}

	template<EParamType eParamType>
	void AddParam(const char* pVal)
	{
		static_assert(eParamType == eTypeString || eParamType == eTypeBlob, "eParamType is invalid!");
		vecParam.emplace_back(eParamType, pVal);
	}

	void AddParam(const mysqlpp::DateTime& rDateTime);
	void AddParam(const mysqlpp::Date& rDate);
	void AddParam(const mysqlpp::Time& rTime);
};

class IDBQuery : public enable_shared_from_this<IDBQuery>, public CQuery
{
	friend class CDBQueryMgr;
public:
	IDBQuery() : _tStartTime(0) { bHasResult = false; }
	virtual ~IDBQuery() { }

	void SetHasResult(bool bHasResult) { this->bHasResult = bHasResult; }

	//byRet: 数据库查询结果，0为成功，1为失败，2为超时
	virtual void OnResult(INT8 byRet, UINT32 dwAffectRow) { if(bHasResult) DebugBreak(); }
	virtual void OnResultData(INT32 byRet, const TVecTable& rVecTable) { if(!bHasResult) DebugBreak(); }

protected:
	time_t _tStartTime;
	TVecTable _vecTable;
};

typedef shared_ptr<IDBQuery> IDBQueryPtr;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CDBQueryMgr
{
public:
	CDBQueryMgr() : _dwNextTransID(1), _pDBProt(NULL) { }

	void Init(CDBProtClt& rDBProt);
	void TimerCheck(time_t tNow);
	bool DoQuery(IDBQuery& rDBQuery, EQueryType eQueryType = eQueryNormal);
	bool DoQuerySvr(EHostType eType, UINT32 dwSvrID, IDBQuery& rDBQuery, EQueryType eQueryType = eQueryNormal);
	void OnResult(UINT32 dwTransID, INT8 byRet, UINT32 dwAffectRow);
	void OnResultData(UINT32 dwTransID, INT8 byRet, const TVecTable& vecTable, UINT8 byCount);

	bool DoModifyQuery(CQuery& rQuery, function<void(INT8 byRet, UINT32 dwAffectRow)> fnSimpResult = nullptr, EQueryType eQueryType = eQueryNormal);
	bool DoModifyQuery(const string& strSQL, function<void(INT8 byRet, UINT32 dwAffectRow)> fnSimpResult = nullptr, EQueryType eQueryType = eQueryNormal);

	bool DoSelectQuery(CQuery& rQuery, function<void(INT8 byRet, const TVecTable& vecTable)> fnDataResult = nullptr, EQueryType eQueryType = eQueryNormal);
	bool DoSelectQuery(const string& strSQL, function<void(INT8 byRet, const TVecTable& vecTable)> fnDataResult = nullptr, EQueryType eQueryType = eQueryNormal);

protected:
	UINT32 _dwNextTransID;
	map<UINT32, IDBQueryPtr> _mapID2Query;
	CDBProtClt* _pDBProt;
};

extern CDBQueryMgr g_DBQueryMgr;		//DBServer连接
extern CDBQueryMgr g_LogQueryMgr;		//LogServer连接
