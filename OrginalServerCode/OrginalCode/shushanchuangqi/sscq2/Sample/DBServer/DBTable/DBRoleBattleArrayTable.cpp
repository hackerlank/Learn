
#include "DBRoleBattleArrayTable.h"

void CDBRoleBattleArrayTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SBattleArrayDBInfo oBattleArray;
    ar >> oBattleArray;
    static_cast<SBattleArrayDBInfo&>(*this) = oBattleArray;
}
void CDBRoleBattleArrayTable::InitDataByBase(const SBattleArrayDBInfo  &rInfo)
{
    static_cast<SBattleArrayDBInfo&>(*this) = rInfo;
}

bool CDBRoleBattleArrayTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SBattleArrayDBInfo newData;
    ar >> newData;

    DIFF(qwRoleID      );
    DIFF(wBattleArrayID);
    DIFF(dwBattleArrayLevelID       );
    DIFF(byBattleArrayStatus     );
    return  !_setChanged.none();
}

bool CDBRoleBattleArrayTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolebattlearray(qwRoleID";
    ostr << ","<< "wBattleArrayID";
    ostr << ","<< "dwBattleArrayLevelID       ";
    ostr << ","<< "byBattleArrayStatus     ";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wBattleArrayID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwBattleArrayLevelID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)byBattleArrayStatus;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleBattleArrayTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolebattlearray SET";

    UPDATE_UINT_SAME(dwBattleArrayLevelID);
    UPDATE_UTINYINT_SAME(byBattleArrayStatus);

    ostr << " WHERE qwRoleID=" << qwRoleID << " and wBattleArrayID="<<wBattleArrayID<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleBattleArrayTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleBattleArrayTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_USMALLINT_SAME(wBattleArrayID);
    GET_UINT_SAME(dwBattleArrayLevelID  );
    GET_UTINYINT_SAME(byBattleArrayStatus     );
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleBattleArrayTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolebattlearray WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblrolebattlearray is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for (UINT32 i =0 ; i< ncount;i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            CDBRoleBattleArrayTable oTable(qwRoleID);
            oTable.InitDataByDBRow(rRow);
            SBattleArrayKey oKey(oTable.qwRoleID,oTable.wBattleArrayID);
            _mapRoleBattleArrayData[oKey]= oTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void CDBRoleBattleArrayTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SBattleArrayDBInfo oBattleArray;
    ar >> oBattleArray;
    SBattleArrayKey oKey(oBattleArray.qwRoleID,oBattleArray.wBattleArrayID);
    auto iter = _mapRoleBattleArrayData.find(oKey);
    if (iter == _mapRoleBattleArrayData.end())
    {
        CDBRoleBattleArrayTable oTemp(oBattleArray.qwRoleID);
        oTemp.Update(strData,true);

        _mapRoleBattleArrayData[oKey] = oTemp;
    }
    else if(iter != _mapRoleBattleArrayData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleBattleArrayTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleBattleArrayData.begin();iter != _mapRoleBattleArrayData.end();iter++)
    {
        rData.vecBattleArrayDBInfo.push_back(iter->second);
    }


}

void CDBRoleBattleArrayTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelBattleArray.begin();deliter != _vecDelBattleArray.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblrolebattlearray WHERE qwRoleID = "<<deliter->qwRoleID<<" and wBattleArrayID="<<deliter->wBattleArrayID<<";";
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
    _vecDelBattleArray.clear();
    for (auto iter = _mapRoleBattleArrayData.begin();iter != _mapRoleBattleArrayData.end();iter++)
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

UINT32 CDBRoleBattleArrayTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleBattleArrayData.begin();iter != _mapRoleBattleArrayData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelBattleArray.size();

}

void CDBRoleBattleArrayTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SBattleArrayDBInfo oBattleArray;
    ar >> oBattleArray;
    SBattleArrayKey oKey(oBattleArray.qwRoleID,oBattleArray.wBattleArrayID);
    auto iter = _mapRoleBattleArrayData.find(oKey);
    if (iter != _mapRoleBattleArrayData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDelBattleArray.push_back(oKey);
        }

        _mapRoleBattleArrayData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

