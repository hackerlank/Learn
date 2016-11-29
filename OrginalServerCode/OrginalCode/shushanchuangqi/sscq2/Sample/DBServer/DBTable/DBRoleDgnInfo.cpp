#include "DBRoleDgnInfo.h"

void DBRoleDgnTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    ar >> static_cast<RoleDgnInfo &>(*this);
}
bool DBRoleDgnTable::OnRecv_SaveOffLineDgnInfo(UINT8 byIsFail)
{
    if (!byIsFail)
    {
        dwCompleteTimes++;
        dwLastCompleteTimer = time(NULL);
        _setChanged.set(UPCOL(dwLastCompleteTimer)); 
        _setChanged.set(UPCOL(dwCompleteTimes)); 
        _eDBState = eInDBUpdate;

    }
    if( byCost != 0)
    {
        byCost = 0;
        _setChanged.set(UPCOL(byCost)); 
        _eDBState = eInDBUpdate;

    }
    return  !_setChanged.none();  
}


bool DBRoleDgnTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    RoleDgnInfo newData;
    ar >> newData;
    DIFF(dwLastEnterTimer);
    DIFF(byCost);
    DIFF(dwEnterTimesAppend);
    DIFF(dwAppendEndTimer);
    DIFF(dwEnterTimes);
    DIFF(dwLastCompleteTimer);
    DIFF(dwCompleteTimes);
    DIFF(wMinTurns);
    DIFF(dwBuyTimer);
    DIFF(dwBuyTimesToday);
    DIFF(dwFinishTimesToday);
    //DIFF(wDgnType);
    return  !_setChanged.none();
}

bool DBRoleDgnTable::GetInsertSqlStr(string& sqlstr)
{

    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroledgninfo(dwDgnType,qwRoleID,dwLastEnterTimer,byCost,dwEnterTimesAppend,dwAppendEndTimer,dwEnterTimes,dwLastCompleteTimer,dwCompleteTimes,wMinTurns,dwBuyTimer,dwBuyTimesToday,dwFinishTimesToday) Values(";
    ostr << (mysqlpp::sql_int_unsigned)dwDgnType;
    ostr << ",";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr <<",";
    ostr <<(mysqlpp::sql_int_unsigned)dwLastEnterTimer;
    ostr <<",";
    ostr <<(mysqlpp::sql_tinyint_unsigned)byCost;
    ostr <<",";
    ostr <<(mysqlpp::sql_int_unsigned)dwEnterTimesAppend;
    ostr <<",";
    ostr <<(mysqlpp::sql_int_unsigned)dwAppendEndTimer;
    ostr <<",";
    ostr <<(mysqlpp::sql_int_unsigned)dwEnterTimes;
    ostr <<",";
    ostr <<(mysqlpp::sql_int_unsigned)dwLastCompleteTimer;
    ostr <<",";
    ostr <<(mysqlpp::sql_int_unsigned)dwCompleteTimes;
    ostr <<",";
    ostr <<(mysqlpp::sql_smallint_unsigned)wMinTurns;
    ostr <<",";
    ostr <<(mysqlpp::sql_int_unsigned)dwBuyTimer;
    ostr <<",";
    ostr <<(mysqlpp::sql_int_unsigned)dwBuyTimesToday;
    ostr <<",";
    ostr <<(mysqlpp::sql_int_unsigned)dwFinishTimesToday;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool DBRoleDgnTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroledgninfo SET";
    UPDATE_UINT_SAME(dwLastEnterTimer);
    UPDATE_UTINYINT_SAME(byCost);
    UPDATE_UINT_SAME(dwEnterTimesAppend);
    UPDATE_UINT_SAME(dwAppendEndTimer);
    UPDATE_UINT_SAME(dwEnterTimes);
    UPDATE_UINT_SAME(dwLastCompleteTimer);
    UPDATE_UINT_SAME(dwCompleteTimes);
    UPDATE_USMALLINT_SAME(wMinTurns);
    UPDATE_UINT_SAME(dwBuyTimer);
    UPDATE_UINT_SAME(dwBuyTimesToday);
    UPDATE_UINT_SAME(dwFinishTimesToday);
    ostr << " WHERE dwDgnType =" << dwDgnType << " AND qwRoleID =" <<_qwRoleID <<  ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void DBRoleDgnTable::ResetChange(void)
{
    _setChanged.reset();
}

void DBRoleDgnTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{   
    GET_UINT_SAME(dwDgnType);
    GET_UINT_SAME(dwLastEnterTimer);
    GET_UTINYINT_SAME(byCost);
    GET_UINT_SAME(dwEnterTimesAppend);
    GET_UINT_SAME(dwAppendEndTimer);
    GET_UINT_SAME(dwEnterTimes);
    GET_UINT_SAME(dwLastCompleteTimer);
    GET_UINT_SAME(dwCompleteTimes);
    GET_USMALLINT_SAME(wMinTurns);
    GET_UINT_SAME(dwBuyTimer);
    GET_UINT_SAME(dwBuyTimesToday);
    GET_UINT_SAME(dwFinishTimesToday);
    TableRowBase::InitDataByDBRow(rRow);
}

void DBRoleDgnTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroledgninfo  WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblroledgninfo is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for (UINT32 i = 0 ; i < ncount; i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            DBRoleDgnTable DgnTable(_qwRoleID);
            DgnTable.InitDataByDBRow(rRow);
            _mapRoleDgnData[DgnTable.dwDgnType] = DgnTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void DBRoleDgnTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive testAr(strData);
    RoleDgnInfo testData;
    testAr >> testData;

    auto iter = _mapRoleDgnData.find(testData.dwDgnType);
    if (iter == _mapRoleDgnData.end() && bIsAdd)
    {
        DBRoleDgnTable DgnNew(_qwRoleID);
        DgnNew.Update(strData, bIsAdd);
        _mapRoleDgnData[testData.dwDgnType] = DgnNew;
    }
    else if(iter != _mapRoleDgnData.end()&& !bIsAdd)
    {
        iter->second.Update(strData, bIsAdd);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void DBRoleDgnTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleDgnData.begin();iter != _mapRoleDgnData.end();iter++)
    {
        rData.vecRoleDgnInfo.push_back(static_cast<RoleDgnInfo>(iter->second));
    }
}

void DBRoleDgnTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelDgn.begin();deliter != _vecDelDgn.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblroledgninfo WHERE dwDgnType = "<<*deliter<<" AND qwRoleID="<<_qwRoleID <<  ";";
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
    _vecDelDgn.clear();

    for (auto iter = _mapRoleDgnData.begin();iter != _mapRoleDgnData.end();iter++)
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

UINT32 DBRoleDgnTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleDgnData.begin();iter != _mapRoleDgnData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelDgn.size();

}

void DBRoleDgnTableManager::DelData(string& strData)
{
    CInArchive rdelData(strData);
    RoleDgnInfo delData;
    rdelData >> delData;
    auto iter = _mapRoleDgnData.find(delData.dwDgnType);
    if (iter != _mapRoleDgnData.end())
    {
        if(iter->second.IsInDB())
        {
            _vecDelDgn.push_back(delData.dwDgnType);
        }
        _mapRoleDgnData.erase(delData.dwDgnType);
    }
}

bool DBRoleDgnTableManager::OnRecv_SaveOffLineDgnInfo(UINT32 dwDgnType,UINT8 byIsFail)
{
    auto iter = _mapRoleDgnData.find(dwDgnType);
    if(iter != _mapRoleDgnData.end())
    {
        return  iter->second.OnRecv_SaveOffLineDgnInfo(byIsFail);
    }
    return true;
}

