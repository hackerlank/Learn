
#include "DBRoleShengLingTable.h"

void CDBRoleShengLingDBTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SShengLingInfo2DB oShengLing;
    ar >> oShengLing;
    static_cast<SShengLingInfo2DB&>(*this) = oShengLing;
}
void CDBRoleShengLingDBTable::InitDataByBase(const SShengLingInfo2DB  &rInfo)
{
    static_cast<SShengLingInfo2DB&>(*this) = rInfo;
}

bool CDBRoleShengLingDBTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SShengLingInfo2DB newData;
    ar >> newData;
    DIFF( byType    );
    DIFF( wNoteID   );
    DIFF( byRandom  );
    DIFF( byFinish  );
    return  !_setChanged.none();
}

bool CDBRoleShengLingDBTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleshengling(qwRoleID";
    ostr << ","<< "byLevel       ";
    ostr << ","<< "byIndex       ";
    ostr << ","<< "byType        ";
    ostr << ","<< "wNoteID       ";
    ostr << ","<< "byRandom      ";
    ostr << ","<< "byFinish      ";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byLevel;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byIndex;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byType;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wNoteID;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byRandom;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byFinish;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleShengLingDBTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleshengling SET";
    UPDATE_UTINYINT_SAME(byType);
    UPDATE_UINT_SAME(wNoteID);
    UPDATE_UTINYINT_SAME(byRandom);
    UPDATE_UTINYINT_SAME(byFinish);
    ostr << " WHERE qwRoleID=" << qwRoleID << " and byLevel="<<(UINT16)byLevel<<" and byIndex="<<(UINT16)byIndex<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleShengLingDBTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleShengLingDBTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_UTINYINT_SAME(byLevel);
    GET_UTINYINT_SAME(byIndex);
    GET_UTINYINT_SAME(byType);
    GET_UINT_SAME(wNoteID);
    GET_UTINYINT_SAME(byRandom);
    GET_UTINYINT_SAME(byFinish);
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleShengLingTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleshengling WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblroleshengling is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        LOG_CRI <<"dataRes.size() = " <<ncount;
        if(byRet == 0)
        {
            for (UINT32 i = 0; i< ncount; i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBRoleShengLingDBTable oTable(qwRoleID);
                oTable.InitDataByDBRow(rRow);
                SShengLingKey oKey(qwRoleID,oTable.byLevel,oTable.byIndex);
                _mapRoleShengLingDBData[oKey]= oTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBRoleShengLingTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SShengLingInfo2DB oShengLing;
    ar >> oShengLing;
    UINT64 qwRoleID = oShengLing.qwRoleID;
    SShengLingKey oKey(qwRoleID,oShengLing.byLevel,oShengLing.byIndex);
    auto iter = _mapRoleShengLingDBData.find(oKey);
    if (iter == _mapRoleShengLingDBData.end())
    {
        CDBRoleShengLingDBTable oTemp(qwRoleID);
        oTemp.Update(strData,true);
        _mapRoleShengLingDBData[oKey] = oTemp;
    }
    else if(iter != _mapRoleShengLingDBData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleShengLingTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleShengLingDBData.begin();iter != _mapRoleShengLingDBData.end();iter++)
    {

        SShengLingInfo2DB oShengLing;
        oShengLing.qwRoleID   = iter->second.qwRoleID;
        oShengLing.byLevel    = iter->second.byLevel;
        oShengLing.byIndex    = iter->second.byIndex;
        oShengLing.byType     = iter->second.byType;
        oShengLing.wNoteID    = iter->second.wNoteID;
        oShengLing.byRandom   = iter->second.byRandom;
        oShengLing.byFinish   = iter->second.byFinish;
        rData.vecShengLing.push_back(oShengLing);
    }
}

void CDBRoleShengLingTableManager::DumpToDB(ManagerUpdateFun fun)
{
    for (auto deliter = _vecDel.begin();deliter != _vecDel.end();deliter++)
    {
      
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblroleshengling WHERE qwRoleID = "<<deliter->qwRoleID<<" and byLevel="<<deliter->byLevel<<" and byIndex="<<deliter->byIndex<<";";
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

    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto iter = _mapRoleShengLingDBData.begin();iter != _mapRoleShengLingDBData.end();iter++)
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

UINT32 CDBRoleShengLingTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleShengLingDBData.begin();iter != _mapRoleShengLingDBData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDel.size();

}

void CDBRoleShengLingTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SShengLingInfo2DB oShengLing;
    ar >> oShengLing;
    SShengLingKey oKey(oShengLing.qwRoleID,oShengLing.byLevel,oShengLing.byIndex);
    auto iter = _mapRoleShengLingDBData.find(oKey);
    if (iter != _mapRoleShengLingDBData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDel.push_back(oKey);
        }

        _mapRoleShengLingDBData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

