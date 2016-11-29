#include "DBSoulSpaceTable.h"

CDBSoulSpaceTable::CDBSoulSpaceTable()
{
}

void CDBSoulSpaceTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SSoulSpaceInfo oSoulSpaceInfo;
    ar >> oSoulSpaceInfo;

    if(!InitDataBySoulSpace(oSoulSpaceInfo))
        return ;
}

bool CDBSoulSpaceTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SSoulSpaceInfo newData;
    ar >> newData;
    DIFF(dwSoulSpaceLevel);

    return  !_setChanged.none();
}

bool CDBSoulSpaceTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblsoulspace(qwRoleID,dwSoulSpaceID,dwSoulSpaceLevel) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSoulSpaceID;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSoulSpaceLevel;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBSoulSpaceTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblbuffdata SET";
    UPDATE_UINT_SAME(dwSoulSpaceLevel);
    ostr << " WHERE qwRoleID  =" << qwRoleID <<" and dwSoulSpaceID ="<<dwSoulSpaceID<< ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBSoulSpaceTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBSoulSpaceTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_UINT_SAME(dwSoulSpaceID);
    GET_UINT_SAME(dwSoulSpaceLevel);
    TableRowBase::InitDataByDBRow(rRow);
}


bool CDBSoulSpaceTable::InitDataBySoulSpace(const SSoulSpaceInfo& rSoulSpaceInfo)
{
    qwRoleID = rSoulSpaceInfo.qwRoleID;
    dwSoulSpaceID = rSoulSpaceInfo.dwSoulSpaceID;
    dwSoulSpaceLevel = rSoulSpaceInfo.dwSoulSpaceLevel;
    return true;
}

void CDBSoulSpaceTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblsoulspace WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(), _byLine, [this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblsoulspace  is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i < ncount; ++i)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBSoulSpaceTable oDBSoulSpaceTable;
                oDBSoulSpaceTable.InitDataByDBRow(rRow);
                SSoulSpaceKey oSoulSpaceKey(oDBSoulSpaceTable.qwRoleID,oDBSoulSpaceTable.dwSoulSpaceID);
                _mapSoulSpaceData[oSoulSpaceKey] = oDBSoulSpaceTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBSoulSpaceTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SSoulSpaceInfo oSoulSpaceInfo;
    ar >> oSoulSpaceInfo;

    SSoulSpaceKey oSoulSpaceKey(oSoulSpaceInfo.qwRoleID,oSoulSpaceInfo.dwSoulSpaceID);
    auto iter = _mapSoulSpaceData.find(oSoulSpaceKey);
    if (iter == _mapSoulSpaceData.end())
    {
        CDBSoulSpaceTable oDBSoulSpaceTable;
        oDBSoulSpaceTable.Update(strData, true);
        _mapSoulSpaceData[oSoulSpaceKey] = oDBSoulSpaceTable;
    }
    else if(iter != _mapSoulSpaceData.end())
        iter->second.Update(strData, false);
    else
         LOG_CRI << "ERR update! bIsAdd = " << (UINT32)bIsAdd << ".";
}

void CDBSoulSpaceTableManager::GetALLInfo(RoleDataInfo & rData)
{
    map<UINT64,CDBSoulSpaceTable>::iterator iter;

    for (auto iter = _mapSoulSpaceData.begin();iter != _mapSoulSpaceData.end();iter++)
    {
        SSoulSpaceInfo oSoulSpaceInfo;
        oSoulSpaceInfo.qwRoleID = (iter->second).qwRoleID;
        oSoulSpaceInfo.dwSoulSpaceID = (iter->second).dwSoulSpaceID;
        oSoulSpaceInfo.dwSoulSpaceLevel = (iter->second).dwSoulSpaceLevel;
        rData.vecSoulSpaceInfo.push_back(oSoulSpaceInfo);
    }
}

void CDBSoulSpaceTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelSoulSpace.begin();deliter != _vecDelSoulSpace.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblsoulspace WHERE "\
            "qwRoleID = " << (*deliter)._qwRoleID << " and "\
            "dwSoulSpaceID = " << (*deliter)._dwSoulSpaceID << ";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
                this->_nErrQuery++;
            if (this->_nNowQuery == 0)
                fun(this->_nMaxQuery,this->_nErrQuery);
        });
    }
    _vecDelSoulSpace.clear();

    for (auto iter = _mapSoulSpaceData.begin();iter != _mapSoulSpaceData.end();iter++)
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

UINT32 CDBSoulSpaceTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapSoulSpaceData.begin();iter != _mapSoulSpaceData.end();iter++)
    {
        if (iter->second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelSoulSpace.size();

}

void CDBSoulSpaceTableManager::DelData(string& strData)
{
    CInArchive ar(strData);
    SSoulSpaceInfo oSoulSpaceInfo;
    ar >> oSoulSpaceInfo;

    SSoulSpaceKey sSoulSpaceKey(oSoulSpaceInfo.qwRoleID,oSoulSpaceInfo.dwSoulSpaceID);

    auto iter = _mapSoulSpaceData.find(sSoulSpaceKey);
    if (iter != _mapSoulSpaceData.end())
    {
        if (iter->second.IsInDB())
            _vecDelSoulSpace.push_back(sSoulSpaceKey);
        _mapSoulSpaceData.erase(iter);
    }
}

