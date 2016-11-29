
#include "DBRoleXinFaDataTable.h"

void CDBRoleXinFaDataTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SXinFaDBInfo oDataInfo;
    ar >> oDataInfo;
    static_cast<SXinFaDBInfo&>(*this) = oDataInfo;
}

bool CDBRoleXinFaDataTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SXinFaDBInfo oDataInfo;
    ar >> oDataInfo;
    SXinFaDBInfo& newData = oDataInfo;

    DIFF(qwRoleID); 
    DIFF(qwOwnerID);
    DIFF(dwXinFaID); 
    DIFF(byXinFaLvl); 
    DIFF(iSlot); 
    
    return  !_setChanged.none();
}

bool CDBRoleXinFaDataTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblfighterxinfa(qwRoleID, qwOwnerID, dwXinFaID, byXinFaLvl, iSlot) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)qwOwnerID;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwXinFaID;
    ostr << "," << (mysqlpp::sql_int_unsigned)byXinFaLvl;
    ostr << "," << (mysqlpp::sql_int)iSlot;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;
}

bool CDBRoleXinFaDataTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblfighterxinfa SET";
    UPDATE_UINT_SAME(byXinFaLvl);
    UPDATE_INT_SAME(iSlot);
    ostr << " WHERE qwRoleID = " << _qwRoleID ;
    ostr <<" AND qwOwnerID = " << qwOwnerID;
    ostr <<" AND dwXinFaID = " << dwXinFaID; 
    ostr << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleXinFaDataTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleXinFaDataTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_UBIGINT_SAME(qwOwnerID);
    GET_UINT_SAME(dwXinFaID);
    GET_UINT_SAME(byXinFaLvl);
    GET_INT_SAME(iSlot);
    TableRowBase::InitDataByDBRow(rRow);
}

void CDBRoleXinFaDataTableManager::QueryDataByRoleId(UINT64 qwRoleID, QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblfighterxinfa WHERE qwRoleID = " << qwRoleID << ";";
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBRoleXinFaDataTable dataTable(qwRoleID);
                dataTable.InitDataByDBRow(rRow);
                
                SXinFaKey oDataKey(dataTable.qwRoleID, dataTable.qwOwnerID, dataTable.dwXinFaID);
                _mapData.insert(std::make_pair(oDataKey, dataTable)); 
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBRoleXinFaDataTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SXinFaDBInfo oDataInfo;
    ar >> oDataInfo;
   
    SXinFaKey oDataKey(oDataInfo.qwRoleID, oDataInfo.qwOwnerID, oDataInfo.dwXinFaID);
    
    //LOG_CRI << "xINFA_KEY" << oDataInfo.qwRoleID << "," << oDataInfo.qwOwnerID << "," << oDataInfo.dwXinFaID;
    map<SXinFaKey, CDBRoleXinFaDataTable>::iterator iter = _mapData.find(oDataKey);
    if (iter == _mapData.end() /*&& bIsAdd*/)
    {
        CDBRoleXinFaDataTable PetDataNew(_qwRoleID);
        PetDataNew.Update(strData, true);
        _mapData.insert(std::make_pair(oDataKey, PetDataNew));

        //LOG_CRI << "ADD xINFA : " << "AAAAAAAAAAAAAAAAAAA";
    }
    else if(iter != _mapData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
        //LOG_CRI << "UPDATE xINFA : " << "BBBBBBBBBBBBBBBBBBB";
    }
}

void CDBRoleXinFaDataTableManager::GetALLInfo(RoleDataInfo& rData)
{
    map<SXinFaKey,CDBRoleXinFaDataTable>::iterator iter;
    for (iter = _mapData.begin();iter != _mapData.end();iter++)
    {
        rData.vecXinFaDBInfo.push_back(iter->second);
    }
}

void CDBRoleXinFaDataTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelData.begin();deliter != _vecDelData.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblfighterxinfa WHERE qwRoleID = " << _qwRoleID;
        sqlstr<< " AND qwOwnerID = " << (*deliter)._qwOwnerID;
        sqlstr<< " AND dwXinFaID = " << (*deliter)._dwXinFaID;
        sqlstr<< ";";
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

UINT32 CDBRoleXinFaDataTableManager::GetUpdataNum()
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

void CDBRoleXinFaDataTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SXinFaDBInfo oDataInfo;
    ar >> oDataInfo;
    
    SXinFaKey oDataKey(oDataInfo.qwRoleID, oDataInfo.qwOwnerID, oDataInfo.dwXinFaID);
    
    auto iter = _mapData.find(oDataKey);
    if (iter != _mapData.end())
    {
        if (iter->second.IsInDB())
            _vecDelData.push_back(oDataKey);

        _mapData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */


