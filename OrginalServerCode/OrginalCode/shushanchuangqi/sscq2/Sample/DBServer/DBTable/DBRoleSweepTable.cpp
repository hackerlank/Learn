
#include "DBRoleSweepTable.h"

void CDBRoleSweepTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SSweepInfo oDataInfo;
    ar >> oDataInfo;
    static_cast<SSweepInfo&>(*this) = oDataInfo;
}

bool CDBRoleSweepTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SSweepInfo oDataInfo;
    ar >> oDataInfo;
    SSweepInfo& newData = oDataInfo;

    DIFF(qwRoleID); 
    DIFF(wCurDgnID);
    DIFF(wCurCount); 
    DIFF(dwReserverTime); 
    DIFF(dwSaveTime); 
    DIFF(wOptions); 
    DIFF(wCount); 
    DIFF(strVecDgn);

    return  !_setChanged.none();
}

bool CDBRoleSweepTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolesweep(qwRoleID,wCurDgnID,wCurCount,dwReserverTime,dwSaveTime,wOptions,wCount,strVecDgn) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)wCurDgnID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)wCurCount;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwReserverTime;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSaveTime;
    ostr << "," << (mysqlpp::sql_int)wOptions;
    ostr << "," << (mysqlpp::sql_int)wCount;
    ostr << ",'" <<strVecDgn <<"'";
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;
}

bool CDBRoleSweepTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolesweep SET";
    UPDATE_USMALLINT_SAME(wCurDgnID);
    UPDATE_USMALLINT_SAME(wCurCount);
    UPDATE_UINT_SAME(dwReserverTime);
    UPDATE_UINT_SAME(dwSaveTime);
    UPDATE_USMALLINT_SAME(wOptions);
    UPDATE_USMALLINT_SAME(wCount);
    UPDATE_STRING_CHAR_SAME(strVecDgn);
    ostr << " WHERE qwRoleID = " << _qwRoleID ;
    ostr << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleSweepTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleSweepTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_USMALLINT_SAME(wCurDgnID);
    GET_USMALLINT_SAME(wCurCount);
    GET_UINT_SAME(dwReserverTime);
    GET_UINT_SAME(dwSaveTime);
    GET_USMALLINT_SAME(wOptions);
    GET_USMALLINT_SAME(wCount);
    GET_STRING_CHAR_SAME(strVecDgn);
    TableRowBase::InitDataByDBRow(rRow);
}

void CDBRoleSweepTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolesweep WHERE qwRoleID = " << qwRoleID << ";";
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for (UINT32 i = 0; i < ncount; i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            CDBRoleSweepTable dataTable(qwRoleID);
            dataTable.InitDataByDBRow(rRow);

            _mapData[qwRoleID] = dataTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void CDBRoleSweepTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SSweepInfo oDataInfo;
    ar >> oDataInfo;

    UINT64 qwRoleID = oDataInfo.qwRoleID;

    map<UINT64, CDBRoleSweepTable>::iterator iter = _mapData.find(qwRoleID);
    if (iter == _mapData.end() /*&& bIsAdd*/)
    {
        CDBRoleSweepTable PetDataNew(_qwRoleID);
        PetDataNew.Update(strData, true);
        _mapData[qwRoleID] = PetDataNew;
    }
    else if(iter != _mapData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleSweepTableManager::GetALLInfo(RoleDataInfo & rData)
{
    map<UINT64,CDBRoleSweepTable>::iterator iter;
    for (iter = _mapData.begin();iter != _mapData.end();iter++)
    {
        SSweepInfo rSweepInfo = iter->second;
        rData.vecSweepInfo.push_back(rSweepInfo);
    }
}

void CDBRoleSweepTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelData.begin();deliter != _vecDelData.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblrolesweep WHERE qwRoleID = " << _qwRoleID;
        sqlstr<< ";";
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
    _vecDelData.clear();
    for (auto iter = _mapData.begin();iter != _mapData.end();iter++)
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

UINT32 CDBRoleSweepTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapData.begin();iter != _mapData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelData.size();

}

void CDBRoleSweepTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SSweepInfo oDataInfo;
    ar >> oDataInfo;

    UINT64 qwRoleID = oDataInfo.qwRoleID;

    auto iter = _mapData.find(qwRoleID);
    if (iter != _mapData.end() )
    {
        if (iter->second.IsInDB())
        {
            _vecDelData.push_back(qwRoleID);

        }
        _mapData.erase(iter);

    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

