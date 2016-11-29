// =====================================================================================
//
//       Filename:  DBTripodLogTable.cpp
//
//    Description:  九疑鼎动态历史表
//
//        Version:  1.0
//        Created:  11/21/2014 01:49:38 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "DBTripodLogTable.h"
#include "Tokenizer.h"
#include "Protocols.h"

CDBTripodLogTableManager g_CDBTripodLogTableManager;

void CDBTripodLogTable::InitDataByStr(string& strData)
{
    CInArchive ar(strData);
    STripodLog oLogInfo;
    ar >> oLogInfo;
    static_cast<STripodLog&>(*this) = oLogInfo;
    ostringstream strTmp;
    for (auto it = oLogInfo.vecParam.begin(); it != oLogInfo.vecParam.end(); ++it)
    {
        strTmp << *it << ",";
    }

    _strParam = strTmp.str();

    strTmp.str("");
    for (auto it = oLogInfo.vecString.begin(); it != oLogInfo.vecString.end(); ++it)
    {
        strTmp <<  *it << ",";
    }
    _strString = strTmp.str();

}

void CDBTripodLogTable::InitDataByBase(const STripodLog& rInfo)
{
    static_cast<STripodLog&>(*this) = rInfo;
    ostringstream strTmp;
    for (auto it = rInfo.vecParam.begin(); it != rInfo.vecParam.end(); ++it)
    {
        strTmp << *it << ",";
    }

    DIFFONLY2(vecParam, strTmp.str(), _strParam);

    strTmp.str("");
    for (auto it = rInfo.vecString.begin(); it != rInfo.vecString.end(); ++it)
    {
        strTmp <<  *it << ",";
    }

}

bool CDBTripodLogTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    STripodLog oLogInfo;
    ar >> oLogInfo;
    STripodLog& newData = oLogInfo;

    DIFF(wMsgID);

    ostringstream strTmp;
    for (auto it = oLogInfo.vecParam.begin(); it != oLogInfo.vecParam.end(); ++it)
    {
        strTmp << *it << ",";
    }

    DIFFONLY2(vecParam, strTmp.str(), _strParam);

    strTmp.str("");
    for (auto it = oLogInfo.vecString.begin(); it != oLogInfo.vecString.end(); ++it)
    {
        strTmp <<  *it << ",";
    }

    DIFFONLY2(vecString, strTmp.str(), _strString);

    DIFF(dwTime);

    return  !_setChanged.none();
}

bool CDBTripodLogTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tbltripodlog(qwRoleID,wMsgID,vecParam,vecString,dwTime) Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," <<(mysqlpp::sql_smallint_unsigned)wMsgID;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strParam;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strString;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwTime;
    ostr << ");";
    sqlstr = ostr.str();
    return true;
}

bool CDBTripodLogTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tbltripodlog SET";

    UPDATE_USMALLINT_SAME(wMsgID);
    UPDATE_STRING_CHAR(vecParam, _strParam);
    UPDATE_STRING_CHAR(vecString, _strString);
    UPDATE_UINT_SAME(dwTime);

    ostr << " WHERE qwRoleID=" << _qwRoleID << " and wMsgID="<<wMsgID<<";";
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBTripodLogTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBTripodLogTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_USMALLINT_SAME(wMsgID);
    GET_STRING_CHAR(vecString, _strString);
    GET_STRING_CHAR(vecParam, _strParam);
    GET_UINT(dwTime, dwTime);

    TableRowBase::InitDataByDBRow(rRow);
}

void CDBTripodLogTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tbltripodlog WHERE qwRoleID = " << qwRoleID << " order by `dwTime` desc limit 10;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoSelectQuery(basesql.str(), NULL, 
            [this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable
            {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << static_cast<INT32>(byRet);
                LOG_INF<<"--------Load tbltripodlog is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
                UINT32 ncount = dataRes.size();
                if(byRet == 0)
                {
                    for(UINT32 i = 0; i< ncount; i++)
                    {
                        mysqlpp::Row& rRow = dataRes[i];
                        CDBTripodLogTable oTable(qwRoleID);
                        oTable.InitDataByDBRow(rRow);
                        _mapTripodLog[qwRoleID].push_back(oTable);
                    }
                }
                queryfun(byRet, ncount);
            });
}

void CDBTripodLogTableManager::Update(const STripodLog& oTripodLog)
{
    string strData;
    COutArchive iar(strData);
    iar << oTripodLog;
    UINT64 qwRoleID = oTripodLog.qwRoleID;
    if (!qwRoleID)
        LOG_CRI << "qwRoleID = 0.";

    // XXX: 日志只有增加
    /*
    SLogKey oKey(_qwRoleID,oTripodLog.wMsgID);
    auto iter = _mapTripodLog.find(oKey);
    if (iter == _mapTripodLog.end())
    {
        CDBTripodLogTable oTemp(_qwRoleID);
        oTemp.Update(strData,true);
        _mapTripodLog[oKey] = oTemp;
    }
    else
        iter->second.Update(strData, false);
    */
    CDBTripodLogTable oTemp(qwRoleID);
    oTemp.Update(strData,true);
    _mapTripodLog[qwRoleID].push_back(oTemp);
}

void CDBTripodLogTableManager::GetAllInfo(UINT64 qwRoleID, TVecTripodLog& rvecLog)
{
    for (auto& rTable : _mapTripodLog[qwRoleID])    
    {

        STripodLog oLogInfo;
        oLogInfo.qwRoleID   = rTable.qwRoleID;
        oLogInfo.wMsgID     = rTable.wMsgID;
        oLogInfo.dwTime     = rTable.dwTime;

        Tokenizer tk(rTable._strParam, ",");
        for (size_t i = 0; i < tk.size(); ++i)
        {               
            if (i == tk.size() - 1 && tk[i].empty())
                break;
            oLogInfo.vecParam.push_back(::atol(tk[i].c_str()));
        }               
        Tokenizer tk2(rTable._strString, ",");
        for (size_t i = 0; i < tk2.size(); ++i)
        {               
            if (i == tk2.size() - 1 && tk2[i].empty())
                break;
            oLogInfo.vecString.push_back(tk2[i].c_str());
        }               

        rvecLog.push_back(oLogInfo);
    }
}

void CDBTripodLogTableManager::DumpToDB()
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto& rID: _vecDelTripodLog)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tbltripodlog WHERE qwRoleID = "<< rID <<";";
        CDBMgr::Instance().DoModifyQuery(sqlstr.str(), NULL, 
                [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes)
                {                              
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << static_cast<INT32>(byRet);
                    this->_nNowQuery--;
                    if (byRet)
                        this->_nErrQuery++;
                });
    }
    _vecDelTripodLog.clear();
    for (auto iter = _mapTripodLog.begin();iter != _mapTripodLog.end();iter++)
    {
        for (auto & rTable : iter->second)
        {
            if (rTable.HasOP())
            {
                rTable.DumpToDBOther( 
                        [this](INT8 byRet)
                        {
                            this->_nNowQuery--;
                            if (byRet)
                                this->_nErrQuery++;
                        });
            }
        }
    }   
}

void CDBTripodLogTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto& rID: _vecDelTripodLog)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tbltripodlog WHERE qwRoleID = "<< rID <<";";
        CDBMgr::Instance().DoModifyQuery(sqlstr.str(), NULL, 
                [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes)
                {                              
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << static_cast<INT32>(byRet);
                    this->_nNowQuery--;
                    if (byRet)
                        this->_nErrQuery++;
                    if (this->_nNowQuery == 0)
                        fun(this->_nMaxQuery,this->_nErrQuery);
                });
    }
    _vecDelTripodLog.clear();
    for (auto iter = _mapTripodLog.begin();iter != _mapTripodLog.end();iter++)
    {
        for (auto & rTable : iter->second)
        {
            if (rTable.HasOP())
            {
                rTable.DumpToDBOther( 
                        [fun,this](INT8 byRet)
                        {
                            this->_nNowQuery--;
                            if (byRet)
                                this->_nErrQuery++;
                            if (this->_nNowQuery == 0)
                                fun(_nMaxQuery,this->_nErrQuery);
                        });
            }
        }
    }   
}

UINT32 CDBTripodLogTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapTripodLog.begin();iter != _mapTripodLog.end();iter++)
    {
        for (auto & rTable : iter->second)
        {
            if (rTable.HasOP())
                dwOP++;
        }
    }
    return dwOP + _vecDelTripodLog.size();

}

void CDBTripodLogTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    STripodLog oLogInfo;
    ar >> oLogInfo;
    UINT64 qwRoleID = oLogInfo.qwRoleID;
    auto iter = _mapTripodLog.find(qwRoleID);
    if (iter != _mapTripodLog.end())
    {
        _vecDelTripodLog.push_back(qwRoleID);
        //if (iter->second.IsInDB())
            _mapTripodLog.erase(iter);
    }
}

void CDBTripodLogTableManager::GetAllTripodLog(UINT32 dwPageSize)
{
    QueryData(dwPageSize,
            [dwPageSize,this](INT8 byRet, UINT32 dwTotalSize)
            {
                UINT32 dwTotalPage = dwTotalSize/dwPageSize;//总页数
                if(dwTotalSize % dwPageSize != 0)
                    dwTotalPage++;
                SendDataToCenter(dwTotalPage,dwPageSize);
            });
}

void CDBTripodLogTableManager::QueryData(UINT32 dwPageSize, QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "select count(distinct(qwRoleID)) as dwCount from tbltripodlog;";
    CDBMgr::Instance().DoSelectQuery(basesql.str(), NULL,
            [this, queryfun, basesql, dwPageSize, qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable
            {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << static_cast<INT32>(byRet) ;
                UINT32 dwCount = 0;
                if(!byRet && dataRes.size()== 1)
                {
                    mysqlpp::Row& rRow = dataRes[0];
                    GET_UINT_SAME(dwCount);
                }
                else
                {
                    queryfun(byRet,0);
                    return;
                }
                if(!dwCount)
                {
                    queryfun(byRet,0);
                    return;
                }
                UINT32 dwTotalPage = (dwCount % dwPageSize != 0) ? dwCount/dwPageSize + 1 : dwCount/dwPageSize;
                for(UINT32 dwPage = 0; dwPage != dwTotalPage; dwPage++)
                {
                    mysqlpp::SQLStream querysql(NULL);
                    querysql << "SELECT distinct(qwRoleID) FROM tbltripodlog LIMIT ";
                    querysql << dwPage * dwPageSize << "," << dwPageSize;
                    querysql << ";";
                    CDBMgr::Instance().DoSelectQuery(querysql.str(),NULL,
                            [this,dwCount, queryfun, querysql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& rDataRes) mutable
                            {
                                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << static_cast<INT32>(byRet) ;
                                UINT32 dwDataCount = rDataRes.size();
                                for (UINT32 dwIndex = 0; dwIndex< dwDataCount; ++ dwIndex)
                                {
                                    mysqlpp::Row& rRow = rDataRes[dwIndex];
                                    UINT64 qwRoleID;
                                    GET_UBIGINT_SAME(qwRoleID);
                                    if (!qwRoleID)
                                        continue;
                                    QueryDataByRoleId(qwRoleID,
                                            [this,dwCount,queryfun,querysql,qwLoadTimer] (INT8 byRet, UINT32 ncount) mutable
                                            {
                                                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << static_cast<INT32>(byRet) ;

                                                if(_mapTripodLog.size() == dwCount)
                                                {
                                                    queryfun(byRet, dwCount);
                                                    LOG_INF<<"--------Load tbltripodlog is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
                                                }
                                            });
                                }
                            });
                }
            });
}

void CDBTripodLogTableManager::SendDataToCenter(UINT32 dwTotalPage,UINT32 dwPageSize)
{
    UINT32 dwPageNum = 0;
    TVecTripodLog vecSendData;
    if(dwTotalPage == 0)
    {
        g_Center2DBCommS.Send_SendAllTripodLog(dwPageNum, dwTotalPage, vecSendData);
        return ;
    }

    UINT32 dwCount = 0;
    for(auto& rPair : _mapTripodLog)
    {
        GetAllInfo(rPair.first, vecSendData);
        if(++dwCount == dwPageSize)
        {
            dwCount = 0;
            dwPageNum++;
            g_Center2DBCommS.Send_SendAllTripodLog(dwPageNum, dwTotalPage, vecSendData);
            vecSendData.clear();
        }
    };
    if(!vecSendData.empty())
    {
        dwPageNum++;
        g_Center2DBCommS.Send_SendAllTripodLog(dwPageNum, dwTotalPage, vecSendData);
    }
    if(dwPageNum != dwTotalPage)
        LOG_CRI << "GetAllTripodLog ERROR";
}


/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

