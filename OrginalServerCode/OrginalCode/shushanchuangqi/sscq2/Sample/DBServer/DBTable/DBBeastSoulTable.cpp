// =====================================================================================
//
//       Filename:  DBBeastSoulTable.cpp
//
//    Description:  兽魂数据表
//
//        Version:  1.0
//        Created:  10/10/2014 12:07:15 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================


#include "DBBeastSoulTable.h"

void CDBBeastSoulTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SBeastSoulInfo oBeastSoulInfo;
    ar >> oBeastSoulInfo;
    static_cast<SBeastSoulInfo&>(*this) = oBeastSoulInfo;
}

bool CDBBeastSoulTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SBeastSoulInfo oBeastSoulInfo;
    ar >> oBeastSoulInfo;
    SBeastSoulInfo& newData = oBeastSoulInfo;

    DIFFONLY2(byType, eType, oBeastSoulInfo.eType);
    DIFF(byRank);
    DIFF(byLevel);

    return  !_setChanged.none();
}

bool CDBBeastSoulTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblbeastsouldata(qwRoleID,byType,byRank,byLevel) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)eType;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byRank;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byLevel;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;
}

bool CDBBeastSoulTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblbeastsouldata SET";

    UPDATE_UTINYINT(byType, eType);
    UPDATE_UTINYINT_SAME(byRank);
    UPDATE_UTINYINT_SAME(byLevel);

    ostr << " WHERE qwRoleID = " << _qwRoleID << " AND byType = " << static_cast<UINT32>(eType) << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBBeastSoulTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBBeastSoulTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    //GET_UBIGINT_SAME(_qwRoleID); // XXX: RoleID in Super
    //GET_UTINYINT(byType, eType);
    eType = static_cast<EBeastSoulType>(static_cast<UINT8>((mysqlpp::sql_tinyint_unsigned)(rRow["byType"])));
    GET_UTINYINT_SAME(byRank);
    GET_UTINYINT_SAME(byLevel);

    TableRowBase::InitDataByDBRow(rRow);
}

void CDBBeastSoulTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "SELECT * FROM tblbeastsouldata WHERE qwRoleID = " << qwRoleID << ";";
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,
            [this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable
            {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
                LOG_INF<<"--------Load tblbeastsouldata is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
                UINT32 ncount = dataRes.size();
                if(byRet == 0)
                {
                    for (UINT32 i =0 ; i< ncount;i++)
                    {
                        mysqlpp::Row& rRow = dataRes[i];
                        CDBBeastSoulTable cBeastDataTable(qwRoleID);
                        cBeastDataTable.InitDataByDBRow(rRow);
                        _mapBeastSoulData[cBeastDataTable.eType] = cBeastDataTable;
                    }
                }
                queryfun(byRet, ncount);
            });
}

void CDBBeastSoulTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SBeastSoulInfo oBeastSoulInfo;
    ar >> oBeastSoulInfo;
    auto iter = _mapBeastSoulData.find(oBeastSoulInfo.eType);
    if (iter == _mapBeastSoulData.end())
    {
        CDBBeastSoulTable BeastDataNew(_qwRoleID);
        BeastDataNew.Update(strData, bIsAdd);
        _mapBeastSoulData[oBeastSoulInfo.eType] = BeastDataNew;
    }
    else if(iter != _mapBeastSoulData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
}

void CDBBeastSoulTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapBeastSoulData.begin();iter != _mapBeastSoulData.end();iter++)
        rData.vecBeastSoulInfo.push_back(iter->second);
}

void CDBBeastSoulTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelBeastData.begin();deliter != _vecDelBeastData.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblbeastsouldata WHERE qwRoleID = " << _qwRoleID << " AND byType = " << static_cast<UINT32>(*deliter) << ";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){                              
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
                this->_nNowQuery--;
                if (byRet)
                {
                this->_nErrQuery++;
                }
                if (this->_nNowQuery == 0)
                {
                fun(this->_nMaxQuery,this->_nErrQuery);
                }
                });
    }
    _vecDelBeastData.clear();
    for (auto iter = _mapBeastSoulData.begin();iter != _mapBeastSoulData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDB(_byLine,[fun,this](INT8 byRet) {
                    this->_nNowQuery--;
                    if (byRet)
                    {
                    this->_nErrQuery++;
                    }
                    if (this->_nNowQuery == 0)
                    {
                    fun(_nMaxQuery,this->_nErrQuery);
                    }
                    });
        }
    }   
}

UINT32 CDBBeastSoulTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapBeastSoulData.begin();iter != _mapBeastSoulData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelBeastData.size();

}

void CDBBeastSoulTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SBeastSoulInfo oBeastSoulInfo;
    ar >> oBeastSoulInfo;
    auto iter = _mapBeastSoulData.find(oBeastSoulInfo.eType);
    if (iter != _mapBeastSoulData.end() )
    {
        if (iter->second.IsInDB())
        { 
            _vecDelBeastData.push_back(oBeastSoulInfo.eType);
        }
        _mapBeastSoulData.erase(iter);

    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */


