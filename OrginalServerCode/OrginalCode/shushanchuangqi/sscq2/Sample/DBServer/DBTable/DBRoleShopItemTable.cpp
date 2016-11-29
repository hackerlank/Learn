
#include "DBRoleShopItemTable.h"

void CDBRoleShopItemTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SBuyItemDBInfo oSBuyItemDBInfo;
    ar >> oSBuyItemDBInfo;
    static_cast<SBuyItemDBInfo&>(*this) = oSBuyItemDBInfo;
}
void CDBRoleShopItemTable::InitDataByBase(const SBuyItemDBInfo  &rInfo)
{
    static_cast<SBuyItemDBInfo&>(*this) = rInfo;
}

bool CDBRoleShopItemTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SBuyItemDBInfo oSBuyItemDBInfo;
    ar >> oSBuyItemDBInfo;
    SBuyItemDBInfo newData = oSBuyItemDBInfo;
    DIFF( dwCount       );
    return  !_setChanged.none();
}

bool CDBRoleShopItemTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolebuyitemlimit(qwRoleID";
    ostr << ","<< "dwInstID             ";
    ostr << ","<< "dwCount    ";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwInstID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwCount;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleShopItemTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolebuyitemlimit SET";

    UPDATE_UINT_SAME(dwCount);
    ostr << " WHERE qwRoleID=" << qwRoleID << " and dwInstID="<<dwInstID<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleShopItemTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleShopItemTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
 
    GET_UBIGINT_SAME(qwRoleID);
    GET_UINT_SAME(dwInstID   );
    GET_UINT_SAME(dwCount);
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleShopItemTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolebuyitemlimit WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblrolebuyitemlimit is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBRoleShopItemTable oTable(qwRoleID);
                oTable.InitDataByDBRow(rRow);
                SShopItemKey oKey(qwRoleID,oTable.dwInstID);
                _mapRoleShopItemData[oKey]= oTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBRoleShopItemTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SBuyItemDBInfo oSBuyItemDBInfo;
    ar >> oSBuyItemDBInfo;
    UINT64 qwRoleID = oSBuyItemDBInfo.qwRoleID;
    SShopItemKey oKey(oSBuyItemDBInfo.qwRoleID,oSBuyItemDBInfo.dwInstID);
    auto iter = _mapRoleShopItemData.find(oKey);
    if (iter == _mapRoleShopItemData.end())
    {
        CDBRoleShopItemTable oTemp(qwRoleID);
        oTemp.Update(strData,true);
        _mapRoleShopItemData[oKey] = oTemp;
    }
    else if(iter != _mapRoleShopItemData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleShopItemTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleShopItemData.begin();iter != _mapRoleShopItemData.end();iter++)
    {

        SBuyItemDBInfo oSBuyItemDBInfo;
        oSBuyItemDBInfo.qwRoleID    =iter->second.qwRoleID;
        oSBuyItemDBInfo.dwInstID   =iter->second.dwInstID;
        oSBuyItemDBInfo.dwCount       =iter->second.dwCount;
        rData.vecBuyItemDBInfo.push_back(oSBuyItemDBInfo);
    }


}

void CDBRoleShopItemTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDel.begin();deliter != _vecDel.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblrolebuyitemlimit WHERE qwRoleID = "<<deliter->qwRoleID<<" and dwInstID="<<deliter->dwInstID<<";";
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
    _vecDel.clear();
    for (auto iter = _mapRoleShopItemData.begin();iter != _mapRoleShopItemData.end();iter++)
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

UINT32 CDBRoleShopItemTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleShopItemData.begin();iter != _mapRoleShopItemData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDel.size();

}

void CDBRoleShopItemTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SBuyItemDBInfo oSBuyItemDBInfo;
    ar >> oSBuyItemDBInfo;
    SShopItemKey oKey(oSBuyItemDBInfo.qwRoleID,oSBuyItemDBInfo.dwInstID);
    auto iter = _mapRoleShopItemData.find(oKey);
    if (iter != _mapRoleShopItemData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDel.push_back(oKey);
        }

        _mapRoleShopItemData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

