
#include "DBExchangedItemTable.h"

void CDBRoleExchangedItemTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    ExchangeInfo oExchangeInfo;
    ar >> oExchangeInfo;
    static_cast<ExchangeInfo&>(*this) = oExchangeInfo;
}
void CDBRoleExchangedItemTable::InitDataByBase(const ExchangeInfo  &rInfo)
{
    static_cast<ExchangeInfo&>(*this) = rInfo;
}

bool CDBRoleExchangedItemTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    ExchangeInfo oExchangeInfo;
    ar >> oExchangeInfo;
    ExchangeInfo newData = oExchangeInfo;
    DIFF( dwCount       );
    DIFF( dwFinishTime    );
    return  !_setChanged.none();
}

bool CDBRoleExchangedItemTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleexchangeditem(qwRoleID";
    ostr << ","<< "dwExchangeID             ";
    ostr << ","<< "dwCount    ";
    ostr << ","<< "dwFinishTime     ";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwExchangeID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwCount;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwFinishTime;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleExchangedItemTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleexchangeditem SET";

    UPDATE_UINT_SAME(dwCount);
    UPDATE_UINT_SAME(dwFinishTime );
    ostr << " WHERE qwRoleID=" << qwRoleID << " and dwExchangeID="<<dwExchangeID<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleExchangedItemTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleExchangedItemTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
 
    GET_UBIGINT_SAME(qwRoleID);
    GET_UINT_SAME(dwExchangeID   );
    GET_UINT_SAME(dwCount);
    GET_UINT_SAME(dwFinishTime);
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleExchangedItemTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleexchangeditem WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblroleexchangeditem is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for (UINT32 i = 0; i< ncount; i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBRoleExchangedItemTable oTable(qwRoleID);
                oTable.InitDataByDBRow(rRow);
                SExchangedItemedKey oKey(qwRoleID,oTable.dwExchangeID);
                _mapRoleExchangedItemData[oKey]= oTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBRoleExchangedItemTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    ExchangeInfo oExchangeInfo;
    ar >> oExchangeInfo;
    UINT64 qwRoleID = oExchangeInfo.qwRoleID;
    SExchangedItemedKey oKey(oExchangeInfo.qwRoleID,oExchangeInfo.dwExchangeID);
    auto iter = _mapRoleExchangedItemData.find(oKey);
    if (iter == _mapRoleExchangedItemData.end())
    {
        CDBRoleExchangedItemTable oTemp(qwRoleID);
        oTemp.Update(strData,true);
        _mapRoleExchangedItemData[oKey] = oTemp;
    }
    else if(iter != _mapRoleExchangedItemData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleExchangedItemTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleExchangedItemData.begin();iter != _mapRoleExchangedItemData.end();iter++)
    {

        ExchangeInfo oExchangeInfo;
        oExchangeInfo.qwRoleID    =iter->second.qwRoleID;
        oExchangeInfo.dwExchangeID   =iter->second.dwExchangeID;
        oExchangeInfo.dwCount       =iter->second.dwCount;
        oExchangeInfo.dwFinishTime      =iter->second.dwFinishTime;        

        rData.vecExchangeInfo.push_back(oExchangeInfo);
    }


}

void CDBRoleExchangedItemTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDel.begin();deliter != _vecDel.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblroleexchangeditem WHERE qwRoleID = "<<deliter->qwRoleID<<" and dwExchangeID="<<deliter->dwExchangeID<<";";
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
    for (auto iter = _mapRoleExchangedItemData.begin();iter != _mapRoleExchangedItemData.end();iter++)
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

UINT32 CDBRoleExchangedItemTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleExchangedItemData.begin();iter != _mapRoleExchangedItemData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDel.size();

}

void CDBRoleExchangedItemTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    ExchangeInfo oExchangeInfo;
    ar >> oExchangeInfo;
    SExchangedItemedKey oKey(oExchangeInfo.qwRoleID,oExchangeInfo.dwExchangeID);
    auto iter = _mapRoleExchangedItemData.find(oKey);
    if (iter != _mapRoleExchangedItemData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDel.push_back(oKey);
        }

        _mapRoleExchangedItemData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

