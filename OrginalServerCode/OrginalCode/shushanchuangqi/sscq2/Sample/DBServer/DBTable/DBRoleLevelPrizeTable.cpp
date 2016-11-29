
#include "DBRoleLevelPrizeTable.h"

void CDBRoleLevelPrizeDBTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SPrize2DB oLevelPrize;
    ar >> oLevelPrize;
    static_cast<SPrize2DB&>(*this) = oLevelPrize;
}
void CDBRoleLevelPrizeDBTable::InitDataByBase(const SPrize2DB  &rInfo)
{
    static_cast<SPrize2DB&>(*this) = rInfo;
}

bool CDBRoleLevelPrizeDBTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SPrize2DB newData;
    ar >> newData;
    DIFF( wStatus    );
    return  !_setChanged.none();
}

bool CDBRoleLevelPrizeDBTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolelevelprize(qwRoleID";
    ostr << ","<< "wActID             ";
    ostr << ","<< "wLevel       ";
    ostr << ","<< "wStatus    ";
    ostr <<") Values(";
    ostr <<qwRoleID;
    ostr << "," <<wActID;
    ostr << "," <<wLevel;
    ostr << "," <<wStatus;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleLevelPrizeDBTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolelevelprize SET";
    UPDATE_SMALLINT_SAME(wStatus);
    ostr << " WHERE qwRoleID=" << qwRoleID << " and wActID="<<wActID<<" and wLevel="<<wLevel<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleLevelPrizeDBTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleLevelPrizeDBTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
 
    GET_UBIGINT_SAME(qwRoleID);
    GET_SMALLINT_SAME(wActID);
    GET_SMALLINT_SAME(wLevel);
    GET_SMALLINT_SAME(wStatus);
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleLevelPrizeTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolelevelprize WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblrolelevelprize is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for (UINT32 i = 0; i< ncount; i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBRoleLevelPrizeDBTable oTable(qwRoleID);
                oTable.InitDataByDBRow(rRow);
                SLevelPrizeKey oKey(qwRoleID,oTable.wActID,oTable.wLevel);
                _mapRoleLevelPrizeDBData[oKey]= oTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBRoleLevelPrizeTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SPrize2DB oLevelPrize;
    ar >> oLevelPrize;
    UINT64 qwRoleID = oLevelPrize.qwRoleID;
    SLevelPrizeKey oKey(oLevelPrize.qwRoleID,oLevelPrize.wActID,oLevelPrize.wLevel);
    auto iter = _mapRoleLevelPrizeDBData.find(oKey);
    if (iter == _mapRoleLevelPrizeDBData.end())
    {
        CDBRoleLevelPrizeDBTable oTemp(qwRoleID);
        oTemp.Update(strData,true);
        _mapRoleLevelPrizeDBData[oKey] = oTemp;
    }
    else if(iter != _mapRoleLevelPrizeDBData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleLevelPrizeTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleLevelPrizeDBData.begin();iter != _mapRoleLevelPrizeDBData.end();iter++)
    {

        SPrize2DB oLevelPrize;
        oLevelPrize.qwRoleID  =iter->second.qwRoleID;
        oLevelPrize.wActID    =iter->second.wActID;
        oLevelPrize.wLevel    =iter->second.wLevel;
        oLevelPrize.wStatus   =iter->second.wStatus       ;
        rData.vecLevelPrize.push_back(oLevelPrize);
    }


}

void CDBRoleLevelPrizeTableManager::DumpToDB(ManagerUpdateFun fun)
{
    for (auto deliter = _vecDel.begin();deliter != _vecDel.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblrolelevelprize WHERE qwRoleID = "<<deliter->qwRoleID<<" and wActID="<<deliter->wActID<<" and wLevel="<<deliter->wLevel<<";";
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
    for (auto iter = _mapRoleLevelPrizeDBData.begin();iter != _mapRoleLevelPrizeDBData.end();iter++)
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

UINT32 CDBRoleLevelPrizeTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleLevelPrizeDBData.begin();iter != _mapRoleLevelPrizeDBData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDel.size();

}

void CDBRoleLevelPrizeTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SPrize2DB oLevelPrize;
    ar >> oLevelPrize;
    SLevelPrizeKey oKey(oLevelPrize.qwRoleID,oLevelPrize.wActID,oLevelPrize.wLevel);
    auto iter = _mapRoleLevelPrizeDBData.find(oKey);
    if (iter != _mapRoleLevelPrizeDBData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDel.push_back(oKey);
        }

        _mapRoleLevelPrizeDBData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

