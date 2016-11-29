#include "DBRoleTaskInfo.h"

void DBRoleTaskTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    ar >> static_cast<RoleTaskInfo &>(*this);
}


bool DBRoleTaskTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    RoleTaskInfo newData;
    ar >> newData;
    DIFF(eTaskState);
    DIFF(dwAcceptTimes);
    DIFF(dwLastAcceptTimer);
    DIFF(dwFinishTimes);
    DIFF(dwLastFinishTimer);
    DIFF(byProcessType1);
    DIFF(dwProcessParam11);
    DIFF(dwProcessParam12);
    DIFF(byProcessType2);
    DIFF(dwProcessParam21);
    DIFF(dwProcessParam22);
    DIFF(byProcessType3);
    DIFF(dwProcessParam31);
    DIFF(dwProcessParam32);
    DIFF(dwRepeatAcceptTimes);
    return  !_setChanged.none();
}

bool DBRoleTaskTable::GetInsertSqlStr(string& sqlstr)
{

    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroletaskinfo(dwTaskId,qwRoleID,eTaskState,dwAcceptTimes,dwLastAcceptTimer,dwFinishTimes,dwLastFinishTimer,byProcessType1,dwProcessParam11,dwProcessParam12,byProcessType2,dwProcessParam21,dwProcessParam22,byProcessType3,dwProcessParam31,dwProcessParam32,dwRepeatAcceptTimes) Values(";
    ostr << (mysqlpp::sql_int_unsigned)dwTaskId;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)eTaskState;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwAcceptTimes;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwLastAcceptTimer;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwFinishTimes;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwLastFinishTimer;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byProcessType1;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwProcessParam11;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwProcessParam12;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byProcessType2;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwProcessParam21;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwProcessParam22;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byProcessType3;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwProcessParam31;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwProcessParam32;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwRepeatAcceptTimes;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool DBRoleTaskTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroletaskinfo SET";
    UPDATE_UTINYINT_SAME(eTaskState);
    UPDATE_UINT_SAME(dwAcceptTimes);
    UPDATE_UINT_SAME(dwLastAcceptTimer);
    UPDATE_UINT_SAME(dwFinishTimes);
    UPDATE_UINT_SAME(dwLastFinishTimer);
    UPDATE_UTINYINT_SAME(byProcessType1);
    UPDATE_UINT_SAME(dwProcessParam11);
    UPDATE_UINT_SAME(dwProcessParam12);
    UPDATE_UTINYINT_SAME(byProcessType2);
    UPDATE_UINT_SAME(dwProcessParam21);
    UPDATE_UINT_SAME(dwProcessParam22);
    UPDATE_UTINYINT_SAME(byProcessType3);
    UPDATE_UINT_SAME(dwProcessParam31);
    UPDATE_UINT_SAME(dwProcessParam32);
    UPDATE_UINT_SAME(dwRepeatAcceptTimes);
    ostr << " WHERE dwTaskId =" << dwTaskId << " AND qwRoleID =" <<_qwRoleID <<  ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void DBRoleTaskTable::ResetChange(void)
{
    _setChanged.reset();
}

void DBRoleTaskTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{   
    GET_UINT_SAME(dwTaskId);
    UINT8 byTaskState;
    GET_UTINYINT(eTaskState,byTaskState);
    eTaskState = static_cast<NTaskProt::ETaskState>(byTaskState);
    GET_UINT_SAME(dwAcceptTimes);
    GET_UINT_SAME(dwLastAcceptTimer);
    GET_UINT_SAME(dwFinishTimes);
    GET_UINT_SAME(dwLastFinishTimer);
    GET_UTINYINT_SAME(byProcessType1);
    GET_UINT_SAME(dwProcessParam11);
    GET_UINT_SAME(dwProcessParam12);
    GET_UTINYINT_SAME(byProcessType2);
    GET_UINT_SAME(dwProcessParam21);
    GET_UINT_SAME(dwProcessParam22);
    GET_UTINYINT_SAME(byProcessType3);
    GET_UINT_SAME(dwProcessParam31);
    GET_UINT_SAME(dwProcessParam32);
    GET_UINT_SAME(dwRepeatAcceptTimes);
    TableRowBase::InitDataByDBRow(rRow);
}

void DBRoleTaskTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroletaskinfo  WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblroletaskinfo is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for(UINT32 i =0 ; i< ncount;i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            DBRoleTaskTable TaskTable(_qwRoleID);
            TaskTable.InitDataByDBRow(rRow);
            _mapRoleTaskData[TaskTable.dwTaskId]= TaskTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void DBRoleTaskTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive testAr(strData);
    RoleTaskInfo testData;
    testAr >> testData;

    auto iter = _mapRoleTaskData.find(testData.dwTaskId);
    if (iter == _mapRoleTaskData.end() && bIsAdd)
    {
        DBRoleTaskTable TaskNew(_qwRoleID);
        TaskNew.Update(strData, bIsAdd);
        _mapRoleTaskData[testData.dwTaskId] = TaskNew;
    }
    else if(iter != _mapRoleTaskData.end()&& !bIsAdd)
    {
        iter->second.Update(strData, bIsAdd);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void DBRoleTaskTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleTaskData.begin();iter != _mapRoleTaskData.end();iter++)
    {
        rData.vecRoleTaskInfo.push_back(static_cast<RoleTaskInfo>(iter->second));
    }
}

void DBRoleTaskTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelTask.begin();deliter != _vecDelTask.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblroletaskinfo WHERE dwTaskId = "<<*deliter<<" AND qwRoleID="<<_qwRoleID <<  ";";
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
    _vecDelTask.clear();
    for (auto iter = _mapRoleTaskData.begin();iter != _mapRoleTaskData.end();iter++)
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

UINT32 DBRoleTaskTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleTaskData.begin();iter != _mapRoleTaskData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelTask.size();

}

void DBRoleTaskTableManager::DelData(string& strData)
{
    CInArchive rdelData(strData);
    RoleTaskInfo delData;
    rdelData >> delData;
    auto iter = _mapRoleTaskData.find(delData.dwTaskId);
    if (iter != _mapRoleTaskData.end())
    {
        if(iter->second.IsInDB())
        {
            _vecDelTask.push_back(delData.dwTaskId);
        }
        _mapRoleTaskData.erase(delData.dwTaskId);
    }
}

