
#include "DBFormationTable.h"

void CDBFormationTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SFormationInfo oFormationInfo;
    ar >> oFormationInfo;
    static_cast<SFormationInfo&>(*this) = oFormationInfo;
}

bool CDBFormationTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SFormationInfo oFormationInfo;
    ar >> oFormationInfo;
    SFormationInfo& newData = oFormationInfo;

    DIFF(wFormationID);
    DIFF(bySelected);

    return  !_setChanged.none();
}

bool CDBFormationTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblformation(qwRoleID,wFormationID,bySelected) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)wFormationID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)bySelected;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;
}

bool CDBFormationTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblformation SET";

    UPDATE_USMALLINT_SAME(wFormationID);
    UPDATE_UTINYINT_SAME(bySelected);

    ostr << " WHERE qwRoleID = " << _qwRoleID << " AND wFormationID = " << wFormationID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBFormationTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBFormationTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    //GET_UBIGINT_SAME(_qwRoleID); // XXX: RoleID in Super
    GET_USMALLINT_SAME(wFormationID);
    GET_UTINYINT_SAME(bySelected);

    TableRowBase::InitDataByDBRow(rRow);
}

void CDBFormationTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblformation WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblformation is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for (UINT32 i =0 ; i< ncount;i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            CDBFormationTable FormationTable(qwRoleID);
            FormationTable.InitDataByDBRow(rRow);
            _mapFormationData[FormationTable.wFormationID] = FormationTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void CDBFormationTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SFormationInfo oFormationInfo;
    ar >> oFormationInfo;
    map<UINT16, CDBFormationTable>::iterator iter = _mapFormationData.find(oFormationInfo.wFormationID);
    if (iter == _mapFormationData.end() && bIsAdd)
    {
        CDBFormationTable FormationNew(_qwRoleID);
        FormationNew.Update(strData, bIsAdd);
        _mapFormationData[oFormationInfo.wFormationID] = FormationNew;
    }
    else if(iter != _mapFormationData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBFormationTableManager::GetALLInfo(RoleDataInfo & rData)
{
    map<UINT16,CDBFormationTable>::iterator iter;
    for (iter = _mapFormationData.begin();iter != _mapFormationData.end();iter++)
        rData.vecFormationInfo.push_back(iter->second);
}

void CDBFormationTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelFormation.begin();deliter != _vecDelFormation.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblformation WHERE qwRoleID = " << _qwRoleID << " AND wFormationID = " << *deliter << ";";
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
    _vecDelFormation.clear();

    for (auto iter = _mapFormationData.begin();iter != _mapFormationData.end();iter++)
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

UINT32 CDBFormationTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapFormationData.begin();iter != _mapFormationData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelFormation.size();

}

void CDBFormationTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SFormationInfo oFormationInfo;
    ar >> oFormationInfo;
    auto iter = _mapFormationData.find(oFormationInfo.wFormationID);
    if (iter != _mapFormationData.end() )
    {
        if (iter->second.IsInDB())
        {
            _vecDelFormation.push_back(oFormationInfo.wFormationID);

        }
        _mapFormationData.erase(iter);

    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

