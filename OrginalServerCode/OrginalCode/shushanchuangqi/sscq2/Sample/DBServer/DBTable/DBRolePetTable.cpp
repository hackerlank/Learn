
#include "DBRolePetTable.h"

void CDBRolePetTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SRolePetInfo oRolePetInfo;
    ar >> oRolePetInfo;
    static_cast<SRolePetInfo&>(*this) = oRolePetInfo;
}

bool CDBRolePetTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SRolePetInfo oRolePetInfo;
    ar >> oRolePetInfo;
    SRolePetInfo& newData = oRolePetInfo;

    DIFF(dwExp);
    DIFF(byLevel);
    DIFF(dwSpirit);

    return  !_setChanged.none();
}

bool CDBRolePetTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolepetdata(qwRoleID,dwExp,byLevel,dwSpirit) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwExp;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byLevel;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSpirit;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;
}

bool CDBRolePetTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolepetdata SET";

    UPDATE_INT_SAME(dwExp);
    UPDATE_UTINYINT_SAME(byLevel);
    UPDATE_INT_SAME(dwSpirit);

    ostr << " WHERE qwRoleID = " << _qwRoleID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRolePetTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRolePetTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    //GET_UBIGINT_SAME(_qwRoleID); // XXX: RoleID in Super
    GET_INT_SAME(dwExp);
    GET_UTINYINT_SAME(byLevel);
    GET_INT_SAME(dwSpirit);

    TableRowBase::InitDataByDBRow(rRow);
}

void CDBRolePetTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolepetdata WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,
            [this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable
            {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
                LOG_INF<<"--------Load tblrolepetdata is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
                UINT32 ncount = dataRes.size();
                if(byRet == 0)
                {
                    for (UINT32 i =0 ; i< ncount;i++)
                    {
                        mysqlpp::Row& rRow = dataRes[i];
                        CDBRolePetTable RolePetTable(qwRoleID);
                        RolePetTable.InitDataByDBRow(rRow);
                        _mapRolePetData[qwRoleID] = RolePetTable;
                    }
                }
                queryfun(byRet, ncount);
            });
}

void CDBRolePetTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SRolePetInfo oRolePetInfo;
    ar >> oRolePetInfo;
    map<UINT64, CDBRolePetTable>::iterator iter = _mapRolePetData.find(_qwRoleID);
    if (iter == _mapRolePetData.end() && bIsAdd)
    {
        CDBRolePetTable RolePetNew(_qwRoleID);
        RolePetNew.Update(strData, bIsAdd);
        _mapRolePetData[_qwRoleID] = RolePetNew;
    }
    else if(iter != _mapRolePetData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRolePetTableManager::GetALLInfo(RoleDataInfo & rData)
{
    map<UINT64,CDBRolePetTable>::iterator iter;
    for (iter = _mapRolePetData.begin();iter != _mapRolePetData.end();iter++)
        rData.oRolePetInfo = iter->second;
}

void CDBRolePetTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelRolePet.begin();deliter != _vecDelRolePet.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblrolepetdata WHERE qwRoleID = " << *deliter << ";";
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
    _vecDelRolePet.clear();

    for (auto iter = _mapRolePetData.begin();iter != _mapRolePetData.end();iter++)
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

UINT32 CDBRolePetTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRolePetData.begin();iter != _mapRolePetData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelRolePet.size();

}

void CDBRolePetTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SRolePetInfo oRolePetInfo;
    ar >> oRolePetInfo;
    auto iter = _mapRolePetData.find(_qwRoleID);
    if (iter != _mapRolePetData.end() )
    {
        if (iter->second.IsInDB())
        {
            _vecDelRolePet.push_back(_qwRoleID);
        }
        _mapRolePetData.erase(iter);

    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

