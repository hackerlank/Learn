
#include "DBRoleAutoStoreTable.h"

void CDBRoleAutoStoreTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SAutoStoreDBInfo oAutoStore;
    ar >> oAutoStore;
    static_cast<SAutoStoreDBInfo&>(*this) = oAutoStore;
}
void CDBRoleAutoStoreTable::InitDataByBase(const SAutoStoreDBInfo  &rInfo)
{
    static_cast<SAutoStoreDBInfo&>(*this) = rInfo;
}

bool CDBRoleAutoStoreTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SAutoStoreDBInfo newData;
    ar >> newData;

    DIFF(qwRoleID      );
    DIFF(wType);
    DIFF(dwClassID       );
    DIFF(dwValue     );
    return  !_setChanged.none();
}

bool CDBRoleAutoStoreTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleautostore(qwRoleID";
    ostr << ","<< "wType";
    ostr << ","<< "dwClassID       ";
    ostr << ","<< "dwValue     ";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wType;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwClassID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwValue;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleAutoStoreTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleautostore SET";

    //    UPDATE_UINT_SAME(dwHorseID   );
    //UPDATE_UINT_SAME(dwClassID);
    UPDATE_UINT_SAME(dwValue);

    ostr << " WHERE qwRoleID=" << qwRoleID << " and wType="<<wType<<" and dwClassID="<<dwClassID<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleAutoStoreTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleAutoStoreTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_USMALLINT_SAME(wType);
    GET_UINT_SAME(dwClassID  );
    GET_UINT_SAME(dwValue     );
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleAutoStoreTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleautostore WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblroleautostore is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for (UINT32 i = 0 ; i< ncount;i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            CDBRoleAutoStoreTable oTable(qwRoleID);
            oTable.InitDataByDBRow(rRow);
            SAutoStoreKey oKey(oTable.qwRoleID,oTable.wType,oTable.dwClassID);
            _mapRoleAutoStoreData[oKey]= oTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void CDBRoleAutoStoreTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SAutoStoreDBInfo oAutoStore;
    ar >> oAutoStore;
    SAutoStoreKey oKey(oAutoStore.qwRoleID,oAutoStore.wType,oAutoStore.dwClassID);
    auto iter = _mapRoleAutoStoreData.find(oKey);
    if (iter == _mapRoleAutoStoreData.end())
    {
        CDBRoleAutoStoreTable oTemp(oAutoStore.qwRoleID);
        oTemp.Update(strData,true);

        _mapRoleAutoStoreData[oKey] = oTemp;
    }
    else if(iter != _mapRoleAutoStoreData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleAutoStoreTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleAutoStoreData.begin();iter != _mapRoleAutoStoreData.end();iter++)
    {
        rData.vecAutoStoreDBInfo.push_back(iter->second);
    }


}

void CDBRoleAutoStoreTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelAutoStore.begin();deliter != _vecDelAutoStore.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblroleautostore WHERE qwRoleID = "<<deliter->qwRoleID<<" and wType="<<deliter->wType<<" and dwClassID="<<deliter->dwClassID<<";";
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
    _vecDelAutoStore.clear();
    for (auto iter = _mapRoleAutoStoreData.begin();iter != _mapRoleAutoStoreData.end();iter++)
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

UINT32 CDBRoleAutoStoreTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleAutoStoreData.begin();iter != _mapRoleAutoStoreData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelAutoStore.size();

}

void CDBRoleAutoStoreTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SAutoStoreDBInfo oAutoStore;
    ar >> oAutoStore;
    SAutoStoreKey oKey(oAutoStore.qwRoleID,oAutoStore.wType,oAutoStore.dwClassID);
    auto iter = _mapRoleAutoStoreData.find(oKey);
    if (iter != _mapRoleAutoStoreData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDelAutoStore.push_back(oKey);
        }

        _mapRoleAutoStoreData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

