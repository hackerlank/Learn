
#include "DBTripodFireTable.h"

void CDBTripodFireTable::InitDataByStr(string& strData)
{
    CInArchive ar(strData);
    SFireInfo oFireInfo;
    ar >> oFireInfo;
    static_cast<SFireInfo&>(*this) = oFireInfo;
}
void CDBTripodFireTable::InitDataByBase(const SFireInfo& rInfo)
{
    static_cast<SFireInfo&>(*this) = rInfo;
}

bool CDBTripodFireTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SFireInfo oFireInfo;
    ar >> oFireInfo;
    SFireInfo& newData = oFireInfo;

    DIFF(wFireID   );
    DIFF(dwSucceed );
    DIFF(dwRemain  );

    return  !_setChanged.none();
}

bool CDBTripodFireTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tbltripodfiredata(qwRoleID,wFireID,dwSucceed,dwRemain) Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," <<(mysqlpp::sql_smallint_unsigned)wFireID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwSucceed;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwRemain;
    ostr << ");";
    sqlstr = ostr.str();
    return true;
}

bool CDBTripodFireTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tbltripodfiredata SET";

    UPDATE_USMALLINT_SAME(wFireID);
    UPDATE_UINT_SAME(dwSucceed);
    UPDATE_UINT_SAME(dwRemain);

    ostr << " WHERE qwRoleID=" << _qwRoleID << " and wFireID="<<wFireID<<";";
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBTripodFireTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBTripodFireTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    //GET_UBIGINT_SAME(_qwRoleID); // XXX: RoleID in Super
    GET_USMALLINT_SAME(wFireID);
    GET_UINT_SAME(dwSucceed);
    GET_UINT_SAME(dwRemain);

    TableRowBase::InitDataByDBRow(rRow);
}

void CDBTripodFireTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tbltripodfiredata WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tbltripodfiredata is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for (UINT32 i = 0; i < ncount; i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBTripodFireTable oTable(qwRoleID);
                oTable.InitDataByDBRow(rRow);
                SFireKey oKey(qwRoleID, oTable.wFireID);
                _mapTripodFireData[oKey]= oTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBTripodFireTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SFireInfo oFireInfo;
    ar >> oFireInfo;

    SFireKey oKey(_qwRoleID,oFireInfo.wFireID);
    auto iter = _mapTripodFireData.find(oKey);
    if (iter == _mapTripodFireData.end())
    {
        CDBTripodFireTable oTemp(_qwRoleID);
        oTemp.Update(strData,true);
        _mapTripodFireData[oKey] = oTemp;
    }
    else if(iter != _mapTripodFireData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBTripodFireTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapTripodFireData.begin();iter != _mapTripodFireData.end();iter++)
    {

        SFireInfo oFireInfo;
        oFireInfo.wFireID  = iter->second.wFireID;
        oFireInfo.dwSucceed = iter->second.dwSucceed;
        oFireInfo.dwRemain  = iter->second.dwRemain;

        rData.vecFireInfo.push_back(oFireInfo);
    }
}

void CDBTripodFireTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelTripodFire.begin();deliter != _vecDelTripodFire.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tbltripodfiredata WHERE qwRoleID = "<<deliter->qwRoleID<<" and wFireID="<<deliter->wFireID<<";";
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
    _vecDelTripodFire.clear();
    for (auto iter = _mapTripodFireData.begin();iter != _mapTripodFireData.end();iter++)
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

UINT32 CDBTripodFireTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapTripodFireData.begin();iter != _mapTripodFireData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelTripodFire.size();

}

void CDBTripodFireTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SFireInfo oFireInfo;
    ar >> oFireInfo;
    SFireKey oKey(_qwRoleID, oFireInfo.wFireID);
    auto iter = _mapTripodFireData.find(oKey);
    if (iter != _mapTripodFireData.end())
    {
        _vecDelTripodFire.push_back(oKey);
        if (iter->second.IsInDB())
        {
            _mapTripodFireData.erase(iter);
        }
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

