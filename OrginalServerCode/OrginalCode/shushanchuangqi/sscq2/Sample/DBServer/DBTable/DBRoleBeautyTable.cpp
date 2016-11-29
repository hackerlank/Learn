
#include "DBRoleBeautyTable.h"

void CDBRoleBeautyTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SBeauty oBeauty;
    ar >> oBeauty;
    static_cast<SBeauty&>(*this) = oBeauty;
}
void CDBRoleBeautyTable::InitDataByBase(const SBeauty  &rInfo)
{
    static_cast<SBeauty&>(*this) = rInfo;
}

bool CDBRoleBeautyTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SBeauty oBeauty;
    ar >> oBeauty;
    SBeauty newData = oBeauty;

    DIFF(wBeautyLevel );
    DIFF(dwBeautyExp        );
    DIFF(wDayLoveType    );
    DIFF(dwChatTime        );
    DIFF(dwPrizeExp);

    return  !_setChanged.none();
}

bool CDBRoleBeautyTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolebeauty(qwRoleID";
    ostr << ","<< "wBeautyID   ";
    ostr << ","<< "wBeautyLevel";
    ostr << ","<< "dwBeautyExp       ";
    ostr << ","<< "wDayLoveType   ";
    ostr << ","<< "dwChatTime       ";
    ostr << ","<< "dwPrizeExp       ";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wBeautyID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wBeautyLevel;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwBeautyExp       ;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wDayLoveType   ;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwChatTime       ;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwPrizeExp       ;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleBeautyTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolebeauty SET";

    UPDATE_USMALLINT_SAME(wBeautyLevel);
    UPDATE_UINT_SAME(dwBeautyExp       );
    UPDATE_USMALLINT_SAME(wDayLoveType   );
    UPDATE_UINT_SAME(dwChatTime       );
    UPDATE_UINT_SAME(dwPrizeExp       );
    ostr << " WHERE qwRoleID=" << qwRoleID << " and wBeautyID="<<wBeautyID<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleBeautyTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleBeautyTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_USMALLINT_SAME(wBeautyID   );
    GET_USMALLINT_SAME(wBeautyLevel);
    GET_UINT_SAME(dwBeautyExp       );
    GET_USMALLINT_SAME(wDayLoveType   );
    GET_UINT_SAME(dwChatTime       );
    GET_UINT_SAME(dwPrizeExp);
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleBeautyTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolebeauty WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblrolebeauty is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBRoleBeautyTable oTable(qwRoleID);
                oTable.InitDataByDBRow(rRow);
                SBeautyKey oKey(qwRoleID,oTable.wBeautyID);
                _mapRoleBeautyData[oKey]= oTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBRoleBeautyTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SBeauty oBeauty;
    ar >> oBeauty;
    UINT64 qwRoleID = oBeauty.qwRoleID;
    SBeautyKey oKey(oBeauty.qwRoleID,oBeauty.wBeautyID);
    auto iter = _mapRoleBeautyData.find(oKey);
    if (iter == _mapRoleBeautyData.end())
    {
        CDBRoleBeautyTable oTemp(qwRoleID);
        oTemp.Update(strData,true);
        _mapRoleBeautyData[oKey] = oTemp;
    }
    else if(iter != _mapRoleBeautyData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleBeautyTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleBeautyData.begin();iter != _mapRoleBeautyData.end();iter++)
    {
        rData.vecBeauty.push_back(iter->second);
    }
}

void CDBRoleBeautyTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelBeauty.begin();deliter != _vecDelBeauty.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblrolebeauty WHERE qwRoleID = "<<deliter->qwRoleID<<" and wBeautyID="<<deliter->wBeautyID<<";";
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
    _vecDelBeauty.clear();
    for (auto iter = _mapRoleBeautyData.begin();iter != _mapRoleBeautyData.end();iter++)
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

UINT32 CDBRoleBeautyTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleBeautyData.begin();iter != _mapRoleBeautyData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelBeauty.size();

}

void CDBRoleBeautyTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SBeauty oBeauty;
    ar >> oBeauty;
    SBeautyKey oKey(oBeauty.qwRoleID,oBeauty.wBeautyID);
    auto iter = _mapRoleBeautyData.find(oKey);
    if (iter != _mapRoleBeautyData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDelBeauty.push_back(oKey);
        }

        _mapRoleBeautyData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

