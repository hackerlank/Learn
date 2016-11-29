#include "DBRoleActivityTask.h"

void DBRoleActivityTaskTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    ar >> static_cast<SActivityTaskInfo&>(*this);
}


bool DBRoleActivityTaskTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SActivityTaskInfo newData;
    ar >> newData;
    DIFF(byTimes);
    DIFF(byIsSpecial);
    return  !_setChanged.none();
}

bool DBRoleActivityTaskTable::GetInsertSqlStr(string& sqlstr)
{

    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleActivitytaskinfo(wId,qwRoleID,byTimes,byIsSpecial) Values(";
    ostr << (mysqlpp::sql_smallint_unsigned)wId;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byTimes;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byIsSpecial;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool DBRoleActivityTaskTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleActivitytaskinfo SET";
    UPDATE_UTINYINT_SAME(byTimes);
    UPDATE_UTINYINT_SAME(byIsSpecial);
    ostr << " WHERE wId =" << wId << " AND qwRoleID =" <<_qwRoleID <<  ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void DBRoleActivityTaskTable::ResetChange(void)
{
    _setChanged.reset();
}

void DBRoleActivityTaskTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{   
    GET_UINT_SAME(wId);
    GET_UTINYINT_SAME(byTimes);
    GET_UTINYINT_SAME(byIsSpecial);
    TableRowBase::InitDataByDBRow(rRow);
}

void DBRoleActivityTaskTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleActivitytaskinfo  WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblroleActivitytaskinfo is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for (UINT32 i =0 ; i< ncount;i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            DBRoleActivityTaskTable ActivityTaskTable(_qwRoleID);
            ActivityTaskTable.InitDataByDBRow(rRow);
            _mapRoleActivityTaskData[ActivityTaskTable.wId]= ActivityTaskTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void DBRoleActivityTaskTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive testAr(strData);
    SActivityTaskInfo testData;
    testAr >> testData;

    auto iter = _mapRoleActivityTaskData.find(testData.wId);
    if (iter == _mapRoleActivityTaskData.end() && bIsAdd)
    {
        DBRoleActivityTaskTable ActivityTaskNew(_qwRoleID);
        ActivityTaskNew.Update(strData, bIsAdd);
        _mapRoleActivityTaskData[testData.wId] = ActivityTaskNew;
    }
    else if(iter != _mapRoleActivityTaskData.end()&& !bIsAdd)
    {
        iter->second.Update(strData, bIsAdd);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void DBRoleActivityTaskTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleActivityTaskData.begin();iter != _mapRoleActivityTaskData.end();iter++)
    {
        rData.vecActivityTask.push_back(static_cast<SActivityTaskInfo>(iter->second));
    }
}

void DBRoleActivityTaskTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelActivityTask.begin();deliter != _vecDelActivityTask.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblroleActivitytaskinfo WHERE wId = "<<*deliter<<" AND qwRoleID="<<_qwRoleID <<  ";";
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
    _vecDelActivityTask.clear();
    for (auto iter = _mapRoleActivityTaskData.begin();iter != _mapRoleActivityTaskData.end();iter++)
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

UINT32 DBRoleActivityTaskTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleActivityTaskData.begin();iter != _mapRoleActivityTaskData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelActivityTask.size();

}

void DBRoleActivityTaskTableManager::DelData(string& strData)
{
    CInArchive rdelData(strData);
    SActivityTaskInfo delData;
    rdelData >> delData;
    auto iter = _mapRoleActivityTaskData.find(delData.wId);
    if (iter != _mapRoleActivityTaskData.end())
    {
        if(iter->second.IsInDB())
        {
            _vecDelActivityTask.push_back(delData.wId);
        }
        _mapRoleActivityTaskData.erase(delData.wId);
    }
}

