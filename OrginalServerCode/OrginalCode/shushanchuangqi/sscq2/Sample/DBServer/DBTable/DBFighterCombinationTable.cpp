
#include "DBFighterCombinationTable.h"

void CDBFighterCombinationTable::InitDataByStr(string& strData)
{
    CInArchive ar(strData);
    SFighterCombination oFighterCombination;
    ar >> oFighterCombination;
    static_cast<SFighterCombination&>(*this) = oFighterCombination;
}

void CDBFighterCombinationTable::InitDataByData(const SFighterCombination& rInData)
{
    static_cast<SFighterCombination&>(*this) = rInData;
}

bool CDBFighterCombinationTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SFighterCombination oFighterCombination;
    ar >> oFighterCombination;
    SFighterCombination& newData = oFighterCombination;

    DIFF(byGroupID );
    DIFF(byGroupLvl);
    DIFF(dwGroupExp);
    DIFF(byInLineUp);
    DIFF(byInEMei);

    return  !_setChanged.none();
}

bool CDBFighterCombinationTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblfightercombination(qwRoleID,byGroupID,byGroupLvl,dwGroupExp,byInLineUp,byInEMei) Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byGroupID;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byGroupLvl;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwGroupExp;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byInLineUp;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byInEMei;
    ostr << ");";
    sqlstr = ostr.str();
    return true;
}

bool CDBFighterCombinationTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblfightercombination SET";

    UPDATE_UTINYINT_SAME(byGroupID);
    UPDATE_UTINYINT_SAME(byGroupLvl);
    UPDATE_UINT_SAME(dwGroupExp);
    UPDATE_UTINYINT_SAME(byInLineUp);
    UPDATE_UTINYINT_SAME(byInEMei);

    ostr << " WHERE qwRoleID=" << _qwRoleID << " and byGroupID="<<int(byGroupID)<<";";
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBFighterCombinationTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBFighterCombinationTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    //GET_UBIGINT_SAME(_qwRoleID); // XXX: RoleID in Super
    GET_UTINYINT_SAME(byGroupID);
    GET_UTINYINT_SAME(byGroupLvl);
    GET_UINT_SAME(dwGroupExp);
    GET_UTINYINT_SAME(byInLineUp);
    GET_UTINYINT_SAME(byInEMei);

    TableRowBase::InitDataByDBRow(rRow);
}

void CDBFighterCombinationTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblfightercombination WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblfightercombination is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for (UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBFighterCombinationTable oTable(qwRoleID);
                oTable.InitDataByDBRow(rRow);
                SCombinationKey oKey(qwRoleID, oTable.byGroupID);
                _mapFighterCombinationData[oKey]= oTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBFighterCombinationTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SFighterCombination oFighterCombination;
    ar >> oFighterCombination;

    SCombinationKey oKey(_qwRoleID,oFighterCombination.byGroupID);
    auto iter = _mapFighterCombinationData.find(oKey);
    if (iter == _mapFighterCombinationData.end())
    {
        CDBFighterCombinationTable oTemp(_qwRoleID);
        oTemp.Update(strData,true);
        _mapFighterCombinationData[oKey] = oTemp;
    }
    else if(iter != _mapFighterCombinationData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBFighterCombinationTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapFighterCombinationData.begin();iter != _mapFighterCombinationData.end();iter++)
    {

        SFighterCombination oFighterCombination;
        oFighterCombination.byGroupID  = iter->second.byGroupID;
        oFighterCombination.byGroupLvl = iter->second.byGroupLvl;
        oFighterCombination.dwGroupExp = iter->second.dwGroupExp;
        oFighterCombination.byInLineUp = iter->second.byInLineUp;
        oFighterCombination.byInEMei   = iter->second.byInEMei;

        rData.vecFighterCombination.push_back(oFighterCombination);
    }
}

void CDBFighterCombinationTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelCombination.begin();deliter != _vecDelCombination.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblfightercombination WHERE qwRoleID = "<<deliter->qwRoleID<<" and byGroupID="<<int(deliter->byGroupID)<<";";
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
    _vecDelCombination.clear();
    for (auto iter = _mapFighterCombinationData.begin();iter != _mapFighterCombinationData.end();iter++)
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

UINT32 CDBFighterCombinationTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapFighterCombinationData.begin();iter != _mapFighterCombinationData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        }
    }
    return dwOP + _vecDelCombination.size();
}

void CDBFighterCombinationTableManager::DelData(string& strData)
{
    CInArchive ar(strData);
    SFighterCombination oFighterCombination;
    ar >> oFighterCombination;
    SCombinationKey oKey(_qwRoleID, oFighterCombination.byGroupID);
    auto iter = _mapFighterCombinationData.find(oKey);
    if (iter != _mapFighterCombinationData.end())
    {
        _vecDelCombination.push_back(oKey);
        if (iter->second.IsInDB())
        {
            _mapFighterCombinationData.erase(iter);
        }
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

