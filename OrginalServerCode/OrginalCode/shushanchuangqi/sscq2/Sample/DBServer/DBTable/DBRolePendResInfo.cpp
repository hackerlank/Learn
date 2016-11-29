#include "DBRolePendResInfo.h"

void DBRolePendResTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    ar >> static_cast<SPendRes &>(*this);
}


bool DBRolePendResTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SPendRes newData;
    ar >> newData;
    DIFF(dwValue);
    DIFF(dwParam);
    return  !_setChanged.none();
}

bool DBRolePendResTable::GetInsertSqlStr(string& sqlstr)
{

    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblpendres(qwRoleID,byResType,dwValue,dwParam,bySource) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byResType;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwValue;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwParam;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)bySource;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool DBRolePendResTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblpendres SET";
    UPDATE_UINT_SAME(dwValue);
    UPDATE_UINT_SAME(dwParam);
    ostr << " WHERE byResType =" << (mysqlpp::sql_tinyint_unsigned)byResType <<" And bySource = " << (mysqlpp::sql_tinyint_unsigned)bySource <<" AND qwRoleID =" <<_qwRoleID <<  ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void DBRolePendResTable::ResetChange(void)
{
    _setChanged.reset();
}

void DBRolePendResTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{   
    GET_UTINYINT_SAME(byResType);
    GET_UINT_SAME(dwValue);
    GET_UTINYINT_SAME(bySource);
    GET_UINT_SAME(dwParam);
    TableRowBase::InitDataByDBRow(rRow);
}

void DBRolePendResTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblpendres  WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblpendres is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for (UINT32 i = 0; i< ncount; i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            DBRolePendResTable PendResTable(_qwRoleID);
            PendResTable.InitDataByDBRow(rRow);
            UINT16 wKey = 0;
            MAMK_KEY(PendResTable,wKey);
            _mapRolePendResData[wKey]= PendResTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void DBRolePendResTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive testAr(strData);
    SPendRes testData;
    testAr >> testData;
    UINT16 wKey = 0;
    MAMK_KEY(testData,wKey);    
    auto iter = _mapRolePendResData.find(wKey);
    if (iter == _mapRolePendResData.end() && bIsAdd)
    {
        DBRolePendResTable PendResNew(_qwRoleID);
        PendResNew.Update(strData, bIsAdd);
        _mapRolePendResData[wKey] = PendResNew;
    }
    else if(iter != _mapRolePendResData.end()&& !bIsAdd)
    {
        iter->second.Update(strData, bIsAdd);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void DBRolePendResTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRolePendResData.begin();iter != _mapRolePendResData.end();iter++)
    {
        rData.vecPendRes.push_back(static_cast<SPendRes>(iter->second));
    }
}

void DBRolePendResTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    //先删除，然后执行插入
    if(!_vecDelPendRes.empty())
    {
        mysqlpp::SQLStream sqlstr(NULL);
        for(auto iter = _vecDelPendRes.begin();iter != _vecDelPendRes.end(); iter++)
        {
            UINT16 wKey = *iter;
            UINT8 byResType = 0;
            UINT8 bySource  = 0 ;
            DisPatchKey(byResType,bySource,wKey);
            sqlstr << "delete FROM tblpendres WHERE qwRoleID = " << _qwRoleID << " AND byResType  = ";
            sqlstr << (mysqlpp::sql_tinyint_unsigned)byResType;
            sqlstr << " AND bySource  = ";
            sqlstr << (mysqlpp::sql_tinyint_unsigned)bySource;
            sqlstr << ";";
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
                        return ;
                        }
                        });

        }
    }
    for (auto iter = _mapRolePendResData.begin();iter != _mapRolePendResData.end();iter++)
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
    //删除执行完成，然后执行插入
    _vecDelPendRes.clear();

}

UINT32 DBRolePendResTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRolePendResData.begin();iter != _mapRolePendResData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelPendRes.size();

}

void DBRolePendResTableManager::DelData(string& strData)
{
    CInArchive rdelData(strData);
    SPendRes delData;
    rdelData >> delData;
    UINT16 wKey;
    MAMK_KEY(delData,wKey);
    auto iter = _mapRolePendResData.find(wKey);
    if (iter != _mapRolePendResData.end())
    {
        if(iter->second.IsInDB())
        {
            _vecDelPendRes.push_back(wKey);
        }
        _mapRolePendResData.erase(wKey);
    }
}

