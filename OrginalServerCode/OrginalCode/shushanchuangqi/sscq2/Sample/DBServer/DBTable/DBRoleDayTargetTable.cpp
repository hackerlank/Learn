
#include "DBRoleDayTargetTable.h"

void CDBRoleDayTargetTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SDayTargetDBInfo oDayTarget;
    ar >> oDayTarget;
    static_cast<SDayTargetDBInfo&>(*this) = oDayTarget;
}
void CDBRoleDayTargetTable::InitDataByBase(const SDayTargetDBInfo  &rInfo)
{
    static_cast<SDayTargetDBInfo&>(*this) = rInfo;
}

bool CDBRoleDayTargetTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SDayTargetDBInfo newData;
    ar >> newData;

    DIFF(qwRoleID      );
    DIFF(wTaskID);
    DIFF(byStatus       );
    DIFF(dwProcess     );
    return  !_setChanged.none();
}

bool CDBRoleDayTargetTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroletarget(qwRoleID";
    ostr << ","<< "wTaskID";
    ostr << ","<< "byStatus       ";
    ostr << ","<< "dwProcess     ";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wTaskID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)byStatus;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwProcess;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleDayTargetTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroletarget SET";

    //    UPDATE_UINT_SAME(dwHorseID   );
    UPDATE_UTINYINT_SAME(byStatus);
    UPDATE_UINT_SAME(dwProcess);

    ostr << " WHERE qwRoleID=" << qwRoleID << " and wTaskID="<<wTaskID<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleDayTargetTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleDayTargetTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_UINT_SAME(wTaskID);
    GET_UTINYINT_SAME(byStatus  );
    GET_UINT_SAME(dwProcess     );
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleDayTargetTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroletarget WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblroletarget is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for(UINT32 i =0 ; i< ncount;i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            CDBRoleDayTargetTable oTable(qwRoleID);
            oTable.InitDataByDBRow(rRow);
            SDayTargetKey oKey(oTable.qwRoleID,oTable.wTaskID);
            _mapRoleDayTargetData[oKey]= oTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void CDBRoleDayTargetTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SDayTargetDBInfo oDayTarget;
    ar >> oDayTarget;
    SDayTargetKey oKey(oDayTarget.qwRoleID,oDayTarget.wTaskID);
    auto iter = _mapRoleDayTargetData.find(oKey);
    if (iter == _mapRoleDayTargetData.end())
    {
        CDBRoleDayTargetTable oTemp(oDayTarget.qwRoleID);
        oTemp.Update(strData,true);

        _mapRoleDayTargetData[oKey] = oTemp;
    }
    else if(iter != _mapRoleDayTargetData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleDayTargetTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleDayTargetData.begin();iter != _mapRoleDayTargetData.end();iter++)
    {
        rData.vecDayTargetDBInfo.push_back(iter->second);
    }


}

void CDBRoleDayTargetTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelDayTarget.begin();deliter != _vecDelDayTarget.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblroletarget WHERE qwRoleID = "<<deliter->qwRoleID<<" and wTaskID="<<deliter->wTaskID<<";";
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
    _vecDelDayTarget.clear();
    for (auto iter = _mapRoleDayTargetData.begin();iter != _mapRoleDayTargetData.end();iter++)
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

UINT32 CDBRoleDayTargetTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleDayTargetData.begin();iter != _mapRoleDayTargetData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelDayTarget.size();

}

void CDBRoleDayTargetTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SDayTargetDBInfo oDayTarget;
    ar >> oDayTarget;
    SDayTargetKey oKey(oDayTarget.qwRoleID,oDayTarget.wTaskID);
    auto iter = _mapRoleDayTargetData.find(oKey);
    if (iter != _mapRoleDayTargetData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDelDayTarget.push_back(oKey);
        }

        _mapRoleDayTargetData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

