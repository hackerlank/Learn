#include "DBGuardEMeiTable.h"

void CDBGuardEMeiTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SGEMDBInfo oDataInfo;
    ar >> oDataInfo;
    static_cast<SGEMDBInfo&>(*this) = oDataInfo;
}

bool CDBGuardEMeiTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SGEMDBInfo oDataInfo;
    ar >> oDataInfo;
    SGEMDBInfo& newData = oDataInfo;

    DIFF(qwRoleID); 
    DIFF(wMissionID);
    DIFF(byGEMType); 
    DIFF(wCurProgress); 
    DIFF(wGuardProgress); 
    DIFF(dwGuardMonsterGroupID); 
    DIFF(dwSweepEndTime); 
    DIFF(strBuff); 
    
    return  !_setChanged.none();
}

bool CDBGuardEMeiTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleGEMdata(qwRoleID, wMissionID, byGEMType, wCurProgress, wGuardProgress, dwGuardMonsterGroupID, dwSweepEndTime, strBuff) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_int_unsigned)wMissionID;
    ostr << "," << (mysqlpp::sql_int_unsigned)byGEMType;
    ostr << "," << (mysqlpp::sql_int_unsigned)wCurProgress;
    ostr << "," << (mysqlpp::sql_int_unsigned)wGuardProgress;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwGuardMonsterGroupID;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSweepEndTime;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)strBuff;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;
}

bool CDBGuardEMeiTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleGEMdata SET";
    UPDATE_UINT_SAME(byGEMType);
    UPDATE_UINT_SAME(wCurProgress);
    UPDATE_UINT_SAME(wGuardProgress);
    UPDATE_UINT_SAME(dwGuardMonsterGroupID);
    UPDATE_UINT_SAME(dwSweepEndTime);
    UPDATE_STRING_CHAR_SAME(strBuff);
    ostr << " WHERE qwRoleID = " << _qwRoleID ;
    ostr <<" AND wMissionID = " << (mysqlpp::sql_int_unsigned)wMissionID; 
    ostr << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBGuardEMeiTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBGuardEMeiTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_UINT_SAME(wMissionID);
    GET_UINT_SAME(byGEMType);
    GET_UINT_SAME(wCurProgress);
    GET_UINT_SAME(wGuardProgress);
    GET_UINT_SAME(dwGuardMonsterGroupID);
    GET_UINT_SAME(dwSweepEndTime);
    GET_STRING_CHAR_SAME(strBuff);
    TableRowBase::InitDataByDBRow(rRow);
}

void CDBGuardEMeiTableManager::QueryDataByRoleId(UINT64 qwRoleID, QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleGEMdata WHERE qwRoleID = " << qwRoleID << ";";
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for (UINT32 i =0; i<ncount; i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBGuardEMeiTable dataTable(qwRoleID);
                dataTable.InitDataByDBRow(rRow);
                
                SGEMKey oDataKey(dataTable.qwRoleID, dataTable.wMissionID);
                _mapData.insert(std::make_pair(oDataKey, dataTable)); 
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBGuardEMeiTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SGEMDBInfo oDataInfo;
    ar >> oDataInfo;
   
    SGEMKey oDataKey(oDataInfo.qwRoleID, oDataInfo.wMissionID);
    
    map<SGEMKey, CDBGuardEMeiTable>::iterator iter = _mapData.find(oDataKey);
    if (iter == _mapData.end() /*&& bIsAdd*/)
    {
        CDBGuardEMeiTable GEMDataNew(_qwRoleID);
        GEMDataNew.Update(strData, true);
        _mapData.insert(std::make_pair(oDataKey, GEMDataNew));
    }
    else if(iter != _mapData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
}

void CDBGuardEMeiTableManager::GetALLInfo(RoleDataInfo& rData)
{
    map<SGEMKey, CDBGuardEMeiTable>::iterator iter;
    for (iter=_mapData.begin(); iter!=_mapData.end(); iter++)
    {
        rData.vecGEMDBInfo.push_back(iter->second);
    }
}

void CDBGuardEMeiTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelData.begin();deliter != _vecDelData.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblroleGEMdata WHERE qwRoleID = " << _qwRoleID;
        sqlstr<< " AND wMissionID = " << ((mysqlpp::sql_int_unsigned)(*deliter)._wMissionID);
        sqlstr<< ";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this, fun, sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){                              
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

UINT32 CDBGuardEMeiTableManager::GetUpdataNum()
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

void CDBGuardEMeiTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SGEMDBInfo oDataInfo;
    ar >> oDataInfo;
    
    SGEMKey oDataKey(oDataInfo.qwRoleID, oDataInfo.wMissionID);
    
    auto iter = _mapData.find(oDataKey);
    if (iter != _mapData.end())
    {
        if (iter->second.IsInDB())
            _vecDelData.push_back(oDataKey);

        _mapData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

