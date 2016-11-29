
#include "DBPetDataTable.h"

void CDBPetDataTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SPetDataInfo oPetDataInfo;
    ar >> oPetDataInfo;
    static_cast<SPetDataInfo&>(*this) = oPetDataInfo;
}

bool CDBPetDataTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SPetDataInfo oPetDataInfo;
    ar >> oPetDataInfo;
    SPetDataInfo& newData = oPetDataInfo;

    DIFF(wPetID);
    DIFF(bySelected);
    DIFF(byLevel);
    DIFF(dwExp);

    return  !_setChanged.none();
}

bool CDBPetDataTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblpetdata(qwRoleID,wPetID,bySelected,byLevel,dwExp) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)wPetID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)bySelected;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byLevel;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwExp;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;
}

bool CDBPetDataTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblpetdata SET";

    UPDATE_USMALLINT_SAME(wPetID);
    UPDATE_UTINYINT_SAME(bySelected);
    UPDATE_UTINYINT_SAME(byLevel);
    UPDATE_UINT_SAME(dwExp);

    ostr << " WHERE qwRoleID = " << _qwRoleID << " AND wPetID = " << wPetID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBPetDataTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBPetDataTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    //GET_UBIGINT_SAME(_qwRoleID); // XXX: RoleID in Super
    GET_USMALLINT_SAME(wPetID);
    GET_UTINYINT_SAME(bySelected);
    GET_UTINYINT_SAME(byLevel);
    GET_UINT_SAME(dwExp);

    TableRowBase::InitDataByDBRow(rRow);
}

void CDBPetDataTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "SELECT * FROM tblpetdata WHERE qwRoleID = " << qwRoleID << ";";
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblpetdata is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for (UINT32 i =0 ; i< ncount;i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            CDBPetDataTable PetDataTable(qwRoleID);
            PetDataTable.InitDataByDBRow(rRow);
            _mapPetDataData[PetDataTable.wPetID] = PetDataTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void CDBPetDataTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SPetDataInfo oPetDataInfo;
    ar >> oPetDataInfo;
    map<UINT16, CDBPetDataTable>::iterator iter = _mapPetDataData.find(oPetDataInfo.wPetID);
    if (iter == _mapPetDataData.end() && bIsAdd)
    {
        CDBPetDataTable PetDataNew(_qwRoleID);
        PetDataNew.Update(strData, bIsAdd);
        _mapPetDataData[oPetDataInfo.wPetID] = PetDataNew;
    }
    else if(iter != _mapPetDataData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBPetDataTableManager::GetALLInfo(RoleDataInfo & rData)
{
    map<UINT16,CDBPetDataTable>::iterator iter;
    for (iter = _mapPetDataData.begin();iter != _mapPetDataData.end();iter++)
        rData.vecPetDataInfo.push_back(iter->second);
}

void CDBPetDataTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelPetData.begin();deliter != _vecDelPetData.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblpetdata WHERE qwRoleID = " << _qwRoleID << " AND wPetID = " << *deliter << ";";
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
    _vecDelPetData.clear();
    for (auto iter = _mapPetDataData.begin();iter != _mapPetDataData.end();iter++)
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

UINT32 CDBPetDataTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapPetDataData.begin();iter != _mapPetDataData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelPetData.size();

}

void CDBPetDataTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SPetDataInfo oPetDataInfo;
    ar >> oPetDataInfo;
    auto iter = _mapPetDataData.find(oPetDataInfo.wPetID);
    if (iter != _mapPetDataData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDelPetData.push_back(oPetDataInfo.wPetID);

        }
        _mapPetDataData.erase(iter);

    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

