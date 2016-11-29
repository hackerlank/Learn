
#include "DBRoleEventTable.h"

void CDBRoleEventDBTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SEventInfo oInfo;
    ar >> oInfo;
    static_cast<SEventInfo&>(*this) = oInfo;
}
void CDBRoleEventDBTable::InitDataByBase(const SEventInfo  &rInfo)
{
    static_cast<SEventInfo&>(*this) = rInfo;
}

bool CDBRoleEventDBTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SEventInfo newData;
    ar >> newData;
    DIFF(wEventStatus);
    DIFF(bySave);
    DIFF(dwParam1);
    DIFF(dwParam2);
    return  !_setChanged.none();
}

bool CDBRoleEventDBTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleevent(qwRoleID";
    ostr << ","<< "byActClassID             ";
    ostr << ","<< "dwEventInstID       ";
    ostr << ","<< "dwApplyID    ";
    ostr << ","<< "wEventStatus    ";
    ostr << ","<< "bySave    ";
    ostr << ","<< "dwParam1    ";
    ostr << ","<< "dwParam2    ";
    ostr <<") Values(";
    ostr <<qwRoleID;
    ostr << "," <<(UINT32)byActClassID;
    ostr << "," <<dwEventInstID;
    ostr << "," <<dwApplyID;
    ostr << "," <<wEventStatus;
    ostr << "," <<(UINT32)bySave;
    ostr << "," <<dwParam1;    
    ostr << "," <<dwParam2;    
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleEventDBTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleevent SET";
    UPDATE_SMALLINT_SAME(dwApplyID);
    UPDATE_SMALLINT_SAME(wEventStatus);
    UPDATE_UTINYINT_SAME(bySave);
    UPDATE_UINT_SAME(dwParam1);
    UPDATE_UINT_SAME(dwParam2);
    ostr << " WHERE qwRoleID=" << qwRoleID 
         << " and byActClassID="<<(UINT32)byActClassID
         << " and dwEventInstID="<<dwEventInstID
         << " and dwApplyID="<<dwApplyID
        <<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleEventDBTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleEventDBTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
 
    GET_UBIGINT_SAME(qwRoleID);
    GET_UTINYINT_SAME(byActClassID);
    GET_UINT_SAME(dwEventInstID);
    GET_UINT_SAME(dwApplyID);
    GET_USMALLINT_SAME(wEventStatus);
    GET_UTINYINT_SAME(bySave);
    GET_UINT_SAME(dwParam1);
    GET_UINT_SAME(dwParam2);
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleEventTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleevent WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblroleevent is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBRoleEventDBTable oTable(qwRoleID);
                oTable.InitDataByDBRow(rRow);
                SEventKey oKey(qwRoleID,oTable.byActClassID,oTable.dwEventInstID,oTable.dwApplyID);
                _mapRoleDBData[oKey]= oTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBRoleEventTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SEventInfo oInfo;
    ar >> oInfo;
    UINT64 qwRoleID = oInfo.qwRoleID;
    SEventKey oKey(oInfo.qwRoleID,oInfo.byActClassID,oInfo.dwEventInstID,oInfo.dwApplyID);
    auto iter = _mapRoleDBData.find(oKey);
    if (iter == _mapRoleDBData.end())
    {
        CDBRoleEventDBTable oTemp(qwRoleID);
        oTemp.Update(strData,true);
        _mapRoleDBData[oKey] = oTemp;
    }
    else if(iter != _mapRoleDBData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleEventTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleDBData.begin();iter != _mapRoleDBData.end();iter++)
    {

        SEventInfo oInfo;
        oInfo.qwRoleID  =iter->second.qwRoleID;
        oInfo.byActClassID    =iter->second.byActClassID;
        oInfo.dwEventInstID    =iter->second.dwEventInstID;
        oInfo.dwApplyID   =iter->second.dwApplyID       ;
        oInfo.wEventStatus = iter->second.wEventStatus;
        oInfo.bySave = iter->second.bySave;
        oInfo.dwParam1 = iter->second.dwParam1;
        oInfo.dwParam2 = iter->second.dwParam2;
        rData.vecEventInfo.push_back(oInfo);
    }


}

void CDBRoleEventTableManager::DumpToDB(ManagerUpdateFun fun)
{
    for (auto deliter = _vecDel.begin();deliter != _vecDel.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblroleevent WHERE qwRoleID = "<<deliter->qwRoleID
            <<" and byActClassID="<<(UINT32)deliter->byActClassID
            <<" and dwEventInstID="<<deliter->dwEventInstID
            <<" and dwApplyID="<<deliter->dwApplyID
            <<";";
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
    for (auto iter = _mapRoleDBData.begin();iter != _mapRoleDBData.end();iter++)
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

UINT32 CDBRoleEventTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleDBData.begin();iter != _mapRoleDBData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDel.size();

}

void CDBRoleEventTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SEventInfo oInfo;
    ar >> oInfo;
    SEventKey oKey(oInfo.qwRoleID,oInfo.byActClassID,oInfo.dwEventInstID,oInfo.dwApplyID);
    auto iter = _mapRoleDBData.find(oKey);
    if (iter != _mapRoleDBData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDel.push_back(oKey);
        }

        _mapRoleDBData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

