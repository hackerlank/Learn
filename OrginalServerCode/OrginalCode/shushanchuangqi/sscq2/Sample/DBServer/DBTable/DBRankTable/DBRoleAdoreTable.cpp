// =====================================================================================
//
//       Filename:  DBRoleAdoreTable.cpp
//
//    Description:  崇拜数据
//
//        Version:  1.0
//        Created:  09/29/2014 10:39:05 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#include "DBRoleAdoreTable.h"

CDBRoleAdoreTable::CDBRoleAdoreTable():
    _qwRoleID(0), _dwCount(0), _dwUpdateTime(0)
{
}

CDBRoleAdoreTable::~CDBRoleAdoreTable()
{
}

void CDBRoleAdoreTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SDBAdoreInfo sRoleAdore;
    ar >> sRoleAdore;

    if(!InitDataByRoleAdore(sRoleAdore))
        return ;
}

bool CDBRoleAdoreTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SDBAdoreInfo sRoleAdore;
    ar >> sRoleAdore;

    DIFFONLY2(qwRoleID, sRoleAdore.qwRoleID, _qwRoleID);
    DIFFONLY2(dwCount, sRoleAdore.dwCount, _dwCount);
    DIFFONLY2(dwUpdateTime, sRoleAdore.dwUpdateTime, _dwUpdateTime);

    return  !_setChanged.none();
}

bool CDBRoleAdoreTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleadore(qwRoleID, dwCount, dwUpdateTime) "\
        "Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwCount;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwUpdateTime;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleAdoreTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleadore SET";

    UPDATE_UBIGINT(qwRoleID, _qwRoleID);
    UPDATE_UINT(dwCount, _dwCount);
    UPDATE_UINT(dwUpdateTime, _dwUpdateTime);

    ostr << " WHERE qwRoleID =" << _qwRoleID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleAdoreTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleAdoreTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwRoleID, _qwRoleID);
    GET_UINT(dwCount, _dwCount);
    GET_UINT(dwUpdateTime, _dwUpdateTime);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  CDBRoleAdoreTable::GetRoleID() const
{
    return _qwRoleID;
}

UINT32  CDBRoleAdoreTable::GetCount() const
{
    return _dwCount;
}

UINT32 CDBRoleAdoreTable::GetUpdataTime() const
{
    return _dwUpdateTime;
}

bool CDBRoleAdoreTable::InitDataByRoleAdore(const SDBAdoreInfo& rRankInfo)
{
    _qwRoleID  = rRankInfo.qwRoleID;
    _dwCount  = rRankInfo.dwCount;
    _dwUpdateTime   = rRankInfo.dwUpdateTime;
    return true;
}

CDBRoleAdoreTableManager::CDBRoleAdoreTableManager(UINT64 qwRoleID) : 
    _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0)
{
}

CDBRoleAdoreTableManager::~CDBRoleAdoreTableManager()
{
}

void CDBRoleAdoreTableManager::QueryDataByRoleID(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleadore WHERE qwRoleID = " << qwRoleID << ";";

    CDBMgr::Instance().DoRankSelectQuery(basesql.str(), NULL, 
            [this, qwRoleID, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable
            {
                UINT32 dwCount = dataRes.size();
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet << ", dwCount = " << dwCount << ".";
                if(byRet == 0)
                {
                    for (UINT32 dwIndex = 0 ; dwIndex < dwCount; ++dwIndex)
                    {
                        mysqlpp::Row& rRow = dataRes[dwIndex];
                        CDBRoleAdoreTable cDBRoleAdoreTable;
                        cDBRoleAdoreTable.InitDataByDBRow(rRow);
                        _mapAdoreData.insert(make_pair(qwRoleID, cDBRoleAdoreTable));
                    }
                }
                queryfun(byRet, dwCount);
            });
}

void CDBRoleAdoreTableManager::Update(string& strData, EDataChange eUpdateType)
{
    CInArchive ar(strData);

    SDBAdoreInfo sRoleAdore;
    ar >> sRoleAdore;

    auto iter = _mapAdoreData.find(sRoleAdore.qwRoleID);
    if (iter == _mapAdoreData.end())
    {
        CDBRoleAdoreTable cDBRoleAdoreTable;
        cDBRoleAdoreTable.Update(strData, true);
        _mapAdoreData.insert(make_pair(cDBRoleAdoreTable.GetRoleID(), cDBRoleAdoreTable));
    }
    else
        iter->second.Update(strData, false);
}

void CDBRoleAdoreTableManager::GetAllInfo(TVecDBAdoreInfo& vecData)
{
    for (auto it = _mapAdoreData.begin(); it != _mapAdoreData.end(); ++it)
    {
        SDBAdoreInfo sDBAdoreInfo;
        sDBAdoreInfo.qwRoleID         = (it->second).GetRoleID();
        sDBAdoreInfo.dwCount          = (it->second).GetCount();
        sDBAdoreInfo.dwUpdateTime     = (it->second).GetUpdataTime();
        vecData.push_back(sDBAdoreInfo);
    }
}

void CDBRoleAdoreTableManager::DumpToDBRank(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto it = _mapAdoreData.begin();it != _mapAdoreData.end();it++)
    {
        if ((it->second).HasOP())
        {
            (it->second).DumpToDBRank(
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

    for (auto it = _vecDelRoleID.begin();it != _vecDelRoleID.end(); ++ it)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblroleadore WHERE qwRoleID = " << (*it) << ";";
        CDBMgr::Instance().DoRankModifyQuery(sqlstr.str(),NULL, 
                [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes)
                {
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
                    this->_nNowQuery--;
                    if (byRet)
                        this->_nErrQuery++;
                    if (this->_nNowQuery == 0)
                        fun(this->_nMaxQuery,this->_nErrQuery);
                });
    }
    _vecDelRoleID.clear();
}

UINT32 CDBRoleAdoreTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto it = _mapAdoreData.begin();it != _mapAdoreData.end();it++)
    {
        if ((it->second).HasOP())
            dwOP++;
    }
    return dwOP + _vecDelRoleID.size();

}

void CDBRoleAdoreTableManager::DelData(UINT64 qwRoleID)
{
    auto it = _mapAdoreData.find(qwRoleID);
    if (it != _mapAdoreData.end())
    {
        if ((it->second).IsInDB())
            _vecDelRoleID.push_back(qwRoleID);
        _mapAdoreData.erase(it);
    }
}


