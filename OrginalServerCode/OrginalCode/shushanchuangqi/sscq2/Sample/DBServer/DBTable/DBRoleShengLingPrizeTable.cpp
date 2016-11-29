
#include "DBRoleShengLingPrizeTable.h"

void CDBRoleShengLingPrizeDBTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SShengLingPrize2DB oItem;
    ar >> oItem;
    static_cast<SShengLingPrize2DB&>(*this) = oItem;
}
bool CDBRoleShengLingPrizeDBTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SShengLingPrize2DB newData;
    ar >> newData;
    DIFF( wNum    );
    return  !_setChanged.none();
}

bool CDBRoleShengLingPrizeDBTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleshenglingprize(qwRoleID";
    ostr << ","<< "wItemID       ";
    ostr << ","<< "wNum          ";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wItemID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wNum;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleShengLingPrizeDBTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleshenglingprize SET";
    UPDATE_UINT_SAME(wNum);
    ostr << " WHERE qwRoleID=" << qwRoleID << " and wItemID= "<<wItemID<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleShengLingPrizeDBTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleShengLingPrizeDBTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_UINT_SAME(wItemID);
    GET_UINT_SAME(wNum);
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleShengLingPrizeTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleshenglingprize WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblroleshenglingprize is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        LOG_CRI <<"dataRes.size() = " <<ncount;
        if(byRet == 0)
        {
            for (UINT32 i = 0; i< ncount; i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBRoleShengLingPrizeDBTable oTable(qwRoleID);
                oTable.InitDataByDBRow(rRow);
                SShengLingPrizeKey oKey(qwRoleID,oTable.wItemID);
                _mapRoleShengLingPrizeDBData[oKey]= oTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBRoleShengLingPrizeTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SShengLingPrize2DB oItem;
    ar >> oItem;
    UINT64 qwRoleID = oItem.qwRoleID;
    SShengLingPrizeKey oKey(qwRoleID,oItem.wItemID);
    auto iter = _mapRoleShengLingPrizeDBData.find(oKey);
    if (iter == _mapRoleShengLingPrizeDBData.end())
    {
        CDBRoleShengLingPrizeDBTable oTemp(qwRoleID);
        oTemp.Update(strData,true);
        _mapRoleShengLingPrizeDBData[oKey] = oTemp;
    }
    else if(iter != _mapRoleShengLingPrizeDBData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleShengLingPrizeTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleShengLingPrizeDBData.begin();iter != _mapRoleShengLingPrizeDBData.end();iter++)
    {

        SShengLingPrize2DB oItem;
        oItem.qwRoleID   = iter->second.qwRoleID;
        oItem.wItemID    = iter->second.wItemID;
        oItem.wNum       = iter->second.wNum;
        rData.vecShengLingPrize.push_back(oItem);
    }
}

void CDBRoleShengLingPrizeTableManager::DumpToDB(ManagerUpdateFun fun)
{
    for (auto deliter = _vecDel.begin();deliter != _vecDel.end();deliter++)
    {
      
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblroleshenglingprize WHERE qwRoleID = "<<*deliter<<";";
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
    for (auto iter = _mapRoleShengLingPrizeDBData.begin();iter != _mapRoleShengLingPrizeDBData.end();iter++)
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

UINT32 CDBRoleShengLingPrizeTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleShengLingPrizeDBData.begin();iter != _mapRoleShengLingPrizeDBData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDel.size();

}

void CDBRoleShengLingPrizeTableManager::DelData(string &strData)
{  
    CInArchive ar(strData);
    UINT64 qwRoleID;
    ar >> qwRoleID;
    auto it = _mapRoleShengLingPrizeDBData.begin();
    for(; it != _mapRoleShengLingPrizeDBData.end();)
    {
        if(qwRoleID == it->second.GetRoleID())
        {
            it =  _mapRoleShengLingPrizeDBData.erase(it);
            continue;
        }
        ++ it;
    }
    bool bFind = (std::find(_vecDel.begin(),_vecDel.end(),qwRoleID) != _vecDel.end());
    if(!bFind)
        _vecDel.push_back(qwRoleID);
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

