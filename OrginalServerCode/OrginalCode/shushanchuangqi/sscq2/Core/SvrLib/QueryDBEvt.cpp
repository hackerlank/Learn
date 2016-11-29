#include "QueryDBEvt.h"
#include <boost/algorithm/string.hpp>

template<typename T>
void AssignValue(const string& strVal, T& rT)
{
	memcpy_s(&rT, sizeof rT, strVal.c_str(), strVal.size());
}

void CQueryDBEvt::OnQuery(mysqlpp::Connection& rCon)
{
	_strQuery = _oQuery.strQuery;
	auto range = boost::algorithm::ifind_first(_strQuery, "select");
	if(!range.empty() && !_oQuery.bHasResult)
	{
		LOG_CRI << "SELECT query should has result: " << _strQuery;
		_oQuery.bHasResult = true;
	}
	size_t pos = 0, prev = 0;
	char arBuf[10];
	size_t num = 0;
	UINT8 byParamCount = 0;
	for(UINT32 i = 0; i < _oQuery.vecParam.size(); ++i)
	{
		bool bParse = false;
		SParam& rParam = _oQuery.vecParam[i];
		switch(rParam.eType)
		{
		case eTypeINT8:
			{
				mysqlpp::sql_tinyint byVal = 0;
				AssignValue(rParam.strVal, byVal);
				_sqp << byVal;
			}
			break;
		case eTypeUINT8:
			{
				mysqlpp::sql_tinyint_unsigned byVal = 0;
				AssignValue(rParam.strVal, byVal);
				_sqp << byVal;
			}
			break;
		case eTypeINT16:
			{
				mysqlpp::sql_smallint wVal = 0;
				AssignValue(rParam.strVal, wVal);
				_sqp << wVal;
			}
			break;
		case eTypeUINT16:
			{
				mysqlpp::sql_smallint_unsigned wVal = 0;
				AssignValue(rParam.strVal, wVal);
				_sqp << wVal;
			}
			break;
		case eTypeINT32:
			{
				mysqlpp::sql_int dwVal = 0;
				AssignValue(rParam.strVal, dwVal);
				_sqp << dwVal;
			}
			break;
		case eTypeUINT32:
			{
				mysqlpp::sql_int_unsigned dwVal = 0;
				AssignValue(rParam.strVal, dwVal);
				_sqp << dwVal;
			}
			break;
		case eTypeINT64:
			{
				mysqlpp::sql_bigint qwVal = 0;
				AssignValue(rParam.strVal, qwVal);
				_sqp << qwVal;
			}
			break;
		case eTypeUINT64:
			{
				mysqlpp::sql_bigint_unsigned qwVal = 0;
				AssignValue(rParam.strVal, qwVal);
				_sqp << qwVal;
			}
			break;
		case eTypeFloat:
			{
				mysqlpp::sql_float fVal = 0;
				AssignValue(rParam.strVal, fVal);
				_sqp << fVal;
			}
			break;
		case eTypeDouble:
			{
				mysqlpp::sql_double dVal = 0;
				AssignValue(rParam.strVal, dVal);
				_sqp << dVal;
			}
			break;
		case eTypeString:
			{
				_sqp << rParam.strVal;
				bParse = true;
			}
			break;
		case eTypeBlob:
			{
				_sqp << rParam.strVal;
				bParse = true;
			}
			break;
		case eTypeDateTime:
			{
				mysqlpp::sql_datetime oDateTime(rParam.strVal);
				_sqp << oDateTime;
			}
			break;
		case eTypeDate:
			{
				mysqlpp::sql_date oDate(rParam.strVal);
				_sqp << oDate;
			}
			break;
		case eTypeTime:
			{
				mysqlpp::sql_time oTime(rParam.strVal);
				_sqp << oTime;
			}
			break;
		}
		pos = _strQuery.find('%', prev);
		if(pos >= _strQuery.size() || pos == string::npos)
			goto FAIL;
		++byParamCount;
		prev = pos + 1;
		if(bParse)
			num = sprintf(arBuf, "%uq", i);
		else
			num = sprintf(arBuf, "%u", i);
		_strQuery.replace(pos + 1, 1, arBuf, num);
	}
	if(byParamCount != _oQuery.vecParam.size())
		goto FAIL;
	_query = rCon.query(_strQuery);
	_query.parse();
	if(_oQuery.bHasResult)
	{
		mysqlpp::StoreQueryResult res = _query.store(_sqp);
		if(!res.empty())
		{
			SResult oResult = { 0, res, 0 };
			_vecResult.push_back(oResult);
		}
		++_byTotalCount;
		UINT8 byLastEmptyCount = 0;
		for(size_t i = 1; _query.more_results(); ++i)
		{
			res = _query.store_next();
			if(res.empty())
			{
				++byLastEmptyCount;
			}
			else
			{
				byLastEmptyCount = 0;
				if(_vecResult.size() < 0xFF)
				{
					SResult oResult = { (UINT8)i, res, 0 };
					_vecResult.push_back(oResult);
				}
			}
			++_byTotalCount;
		}
		_byTotalCount -= byLastEmptyCount;
	}
	else
	{
		_simpRes = _query.execute(_sqp);
	}
	return;
FAIL:
	throw mysqlpp::BadQuery("Parameter Count Error!", 1);
}

bool CQueryDBEvt::OnResult()
{
	if(_oQuery.bHasResult)
	{
		TVecTable vecTable;
		bool bFinish = true;
		if(_byRet == 0)
		{
			for(size_t i = 0; i < _vecResult.size(); ++i)
			{
				STable oTable;
				SResult& rResult = _vecResult[i];
				for(; rResult.dwCurRow < rResult.dataRes.size() && oTable.vecRow.size() < 0xFF; ++rResult.dwCurRow)
				{
					mysqlpp::Row& rRow = rResult.dataRes[rResult.dwCurRow];
					SRow row;
					for(size_t k = 0; k < rRow.size(); ++k)
					{
						SRes res;
						const mysqlpp::String& strVal = rRow[(int)k];
						if(!strVal.empty() && !strVal.is_null())
							strVal.to_string(res.strVal);
						row.vecRes.push_back(res);
					}
					oTable.vecRow.push_back(row);
				}
				if(!oTable.vecRow.empty())
				{
					oTable.byIndex = rResult.byIndex;
					oTable.bMore = rResult.dwCurRow < rResult.dataRes.size();
					vecTable.push_back(oTable);
					if(oTable.bMore)
						bFinish = false;
				}
			}
		}
		_rDBProt.SendSvr_ResultDataRet(&_dwSvrID, 1, _dwTransID, _byRet, vecTable, _byTotalCount);
		return bFinish;
	}
	else
	{
		UINT32 dwAffectRow = (UINT32)_simpRes.rows();
		_rDBProt.SendSvr_ResultRet(&_dwSvrID, 1, _dwTransID, _byRet, dwAffectRow);
		return true;
	}
}