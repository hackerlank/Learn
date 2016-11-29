#include "DBRoleTitle.h"

void DBRoleTitleTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    ar >> static_cast<STitle&>(*this);
}


bool DBRoleTitleTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    STitle newData;
    ar >> newData;
    DIFF(byEquipPos);
    DIFF(dwValidTime);
    return  !_setChanged.none();
}

bool DBRoleTitleTable::GetInsertSqlStr(string& sqlstr)
{

    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroletitle(wId,qwRoleID,byEquipPos,dwValidTime) Values(";
    ostr << (mysqlpp::sql_smallint_unsigned)wId;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byEquipPos;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwValidTime;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool DBRoleTitleTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroletitle SET";
    UPDATE_UTINYINT_SAME(byEquipPos);
    UPDATE_UINT_SAME(dwValidTime);
    ostr << " WHERE wId =" << wId << " AND qwRoleID =" <<_qwRoleID <<  ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void DBRoleTitleTable::ResetChange(void)
{
    _setChanged.reset();
}

void DBRoleTitleTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{   
    GET_UINT_SAME(wId);
    GET_UTINYINT_SAME(byEquipPos);
    GET_UINT_SAME(dwValidTime);
    TableRowBase::InitDataByDBRow(rRow);
}

void DBRoleTitleTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroletitle  WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblroletitle is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for(UINT32 i =0 ; i< ncount;i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            DBRoleTitleTable TitleTable(_qwRoleID);
            TitleTable.InitDataByDBRow(rRow);
            _mapRoleTitleData[TitleTable.wId]= TitleTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void DBRoleTitleTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive testAr(strData);
    STitle testData;
    testAr >> testData;

    auto iter = _mapRoleTitleData.find(testData.wId);
    if (iter == _mapRoleTitleData.end() && bIsAdd)
    {
        DBRoleTitleTable TitleNew(_qwRoleID);
        TitleNew.Update(strData, bIsAdd);
        _mapRoleTitleData[testData.wId] = TitleNew;
    }
    else if(iter != _mapRoleTitleData.end()&& !bIsAdd)
    {
        iter->second.Update(strData, bIsAdd);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void DBRoleTitleTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleTitleData.begin();iter != _mapRoleTitleData.end();iter++)
    {
        rData.vecTitle.push_back(static_cast<STitle>(iter->second));
    }
}

void DBRoleTitleTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelTitle.begin();deliter != _vecDelTitle.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblroletitle WHERE wId = "<<*deliter<<" AND qwRoleID="<<_qwRoleID <<  ";";
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
    _vecDelTitle.clear();

    for (auto iter = _mapRoleTitleData.begin();iter != _mapRoleTitleData.end();iter++)
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

UINT32 DBRoleTitleTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleTitleData.begin();iter != _mapRoleTitleData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelTitle.size();

}

void DBRoleTitleTableManager::DelData(string& strData)
{
    CInArchive rdelData(strData);
    STitle delData;
    rdelData >> delData;
    auto iter = _mapRoleTitleData.find(delData.wId);
    if (iter != _mapRoleTitleData.end())
    {
        if(iter->second.IsInDB())
        {
            _vecDelTitle.push_back(delData.wId);
        }
        _mapRoleTitleData.erase(delData.wId);
    }
}

