#include "DBTreasureHuntTable.h"

void CDBTreasureHuntTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    STHDBInfo oDataInfo;
    ar >> oDataInfo;
    static_cast<STHDBInfo&>(*this) = oDataInfo;
}

bool CDBTreasureHuntTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    STHDBInfo oDataInfo;
    ar >> oDataInfo;
    STHDBInfo& newData = oDataInfo;

    DIFF(qwRoleID); 
    DIFF(byCopyID);
    DIFF(byStatus); 
    DIFF(dwBossCurHP); 
    DIFF(dwLastTime); 
    DIFF(dwTime); 
    DIFF(dwNum); 
    DIFF(strAward); 
    
    return  !_setChanged.none();
}

bool CDBTreasureHuntTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleTHdata(qwRoleID, byCopyID, byStatus, dwBossCurHP, dwLastTime, dwTime, dwNum, strAward) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_int_unsigned)byCopyID;
    ostr << "," << (mysqlpp::sql_int_unsigned)byStatus;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwBossCurHP;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwLastTime;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwTime;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwNum;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)strAward;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;
}

bool CDBTreasureHuntTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleTHdata SET";
    UPDATE_UINT_SAME(byStatus);
    UPDATE_UINT_SAME(dwBossCurHP);
    UPDATE_UINT_SAME(dwLastTime);
    UPDATE_UINT_SAME(dwTime);
    UPDATE_UINT_SAME(dwNum);
    UPDATE_STRING_CHAR_SAME(strAward);
    ostr << " WHERE qwRoleID = " << _qwRoleID ;
    ostr <<" AND byCopyID = " << (mysqlpp::sql_int_unsigned)byCopyID; 
    ostr << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBTreasureHuntTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBTreasureHuntTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_UINT_SAME(byCopyID);
    GET_UINT_SAME(byStatus);
    GET_UINT_SAME(dwBossCurHP);
    GET_UINT_SAME(dwLastTime);
    GET_UINT_SAME(dwTime);
    GET_UINT_SAME(dwNum);
    GET_STRING_CHAR_SAME(strAward);
    TableRowBase::InitDataByDBRow(rRow);
}

void CDBTreasureHuntTableManager::QueryDataByRoleId(UINT64 qwRoleID, QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleTHdata WHERE qwRoleID = " << qwRoleID << ";";
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for (UINT32 i =0; i<ncount; i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBTreasureHuntTable dataTable(qwRoleID);
                dataTable.InitDataByDBRow(rRow);
                
                STHKey oDataKey(dataTable.qwRoleID, dataTable.byCopyID);
                _mapData.insert(std::make_pair(oDataKey, dataTable)); 
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBTreasureHuntTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    STHDBInfo oDataInfo;
    ar >> oDataInfo;
   
    STHKey oDataKey(oDataInfo.qwRoleID, oDataInfo.byCopyID);
    
    map<STHKey, CDBTreasureHuntTable>::iterator iter = _mapData.find(oDataKey);
    if (iter == _mapData.end() /*&& bIsAdd*/)
    {
        CDBTreasureHuntTable THDataNew(_qwRoleID);
        THDataNew.Update(strData, true);
        _mapData.insert(std::make_pair(oDataKey, THDataNew));
    }
    else if(iter != _mapData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
}

void CDBTreasureHuntTableManager::GetALLInfo(RoleDataInfo& rData)
{
    map<STHKey, CDBTreasureHuntTable>::iterator iter;
    for (iter=_mapData.begin(); iter!=_mapData.end(); iter++)
    {
        rData.vecTHDBInfo.push_back(iter->second);
    }
}

void CDBTreasureHuntTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelData.begin();deliter != _vecDelData.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblroleTHdata WHERE qwRoleID = " << _qwRoleID;
        sqlstr<< " AND byCopyID = " << ((mysqlpp::sql_int_unsigned)(*deliter)._byCopyID);
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

UINT32 CDBTreasureHuntTableManager::GetUpdataNum()
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

void CDBTreasureHuntTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    STHDBInfo oDataInfo;
    ar >> oDataInfo;
    
    STHKey oDataKey(oDataInfo.qwRoleID, oDataInfo.byCopyID);
    
    auto iter = _mapData.find(oDataKey);
    if (iter != _mapData.end())
    {
        if (iter->second.IsInDB())
            _vecDelData.push_back(oDataKey);

        _mapData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

