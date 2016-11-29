#include "DBRoleTrumpTable.h"

DBRoleTrumpTable::DBRoleTrumpTable():
    _qwInstID(0), _qwRoleID(0),
    _byUsed(0), _dwExp(0), _wLevel(0), _wRank(0)
{
}

void DBRoleTrumpTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_STrump)
        return ;

    STrumpPtr pTrump = dynamic_pointer_cast<STrump>(weakPtr.ptr);
    if(!InitDataByTrump(pTrump))
        return ;
}

bool DBRoleTrumpTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_STrump)
        return false;
    STrumpPtr pTrump = dynamic_pointer_cast<STrump>(weakPtr.ptr);
    if(NULL == pTrump)
        return false;

    DIFFONLY2(byUsed, pTrump->byUsed, _byUsed);
    DIFFONLY2(dwExp, pTrump->dwExp, _dwExp);
    DIFFONLY2(wLevel, pTrump->wLevel, _wLevel);
    DIFFONLY2(wRank, pTrump->wRank, _wRank);

    return  !_setChanged.none();
}

bool DBRoleTrumpTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroletrumpdata(qwInstID,qwRoleID,"\
        "byUsed,dwExp,wLevel,wRank) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwInstID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byUsed;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwExp;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wLevel;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wRank;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool DBRoleTrumpTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroletrumpdata SET";

    UPDATE_UBIGINT(qwRoleID, _qwRoleID);
    UPDATE_TINYINT(byUsed, _byUsed);
    UPDATE_UINT(dwExp, _dwExp);
    UPDATE_SMALLINT(wLevel, _wLevel);
    UPDATE_SMALLINT(wRank, _wRank);

    ostr << " WHERE qwInstID =" << _qwInstID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void DBRoleTrumpTable::ResetChange(void)
{
    _setChanged.reset();
}

void DBRoleTrumpTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwInstID, _qwInstID);
    GET_UBIGINT(qwRoleID, _qwRoleID);
    GET_UTINYINT(byUsed, _byUsed);
    GET_UINT(dwExp, _dwExp);
    GET_USMALLINT(wLevel, _wLevel);
    GET_USMALLINT(wRank, _wRank);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  DBRoleTrumpTable::GetInstID() const
{
    return _qwInstID;
}

UINT64  DBRoleTrumpTable::GetRoleID() const
{
    return _qwRoleID;
}

bool DBRoleTrumpTable::InitDataByTrump(STrumpPtr pTrump)
{
    if (!pTrump)
        return false;
    _qwInstID = (pTrump->sItemInfo).qwInstID;
    _qwRoleID = pTrump->qwRoleID;
    _byUsed = pTrump->byUsed;
    _dwExp = pTrump->dwExp;
    _wLevel = pTrump->wLevel;
    _wRank  = pTrump->wRank;
    return true;
}

void DBRoleTrumpTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroletrumpdata WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(), _byLine, [this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblroletrumpdata is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for (UINT32 i = 0; i < ncount; ++i)
            {
                mysqlpp::Row& rRow = dataRes[i];
                DBRoleTrumpTable TrumpTable;
                TrumpTable.InitDataByDBRow(rRow);
                _mapRoleTrumpData[TrumpTable.GetInstID()]= TrumpTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void DBRoleTrumpTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_STrump)
        return ;

    STrumpPtr pTrump = dynamic_pointer_cast<STrump>(weakPtr.ptr);
    if(pTrump == NULL)
        return ;

    map<UINT64, DBRoleTrumpTable>::iterator iter = _mapRoleTrumpData.find(pTrump->sItemInfo.qwInstID);
    if (iter == _mapRoleTrumpData.end() && bIsAdd)
    {
        DBRoleTrumpTable TrumpNew;
        TrumpNew.Update(strData, bIsAdd);
        _mapRoleTrumpData[pTrump->sItemInfo.qwInstID] = TrumpNew;
    }
    else if(iter != _mapRoleTrumpData.end() && !bIsAdd)
        iter->second.Update(strData, bIsAdd);
    else
         LOG_CRI << "ERR update! bIsAdd = " << (UINT32)bIsAdd << ".";
}

void DBRoleTrumpTableManager::GetALLInfo(RoleDataInfo & rData)
{
    map<UINT64,DBRoleTrumpTable>::iterator iter;
    set<UINT64> setUseTrump;
    for (auto it = rData.vecRoleItemInfo.begin();it != rData.vecRoleItemInfo.end();it++)
    {
        if ((*it)->GetClassType() == eType_STrump)
        {
            STrumpPtr pTrump = dynamic_pointer_cast<STrump>(*it);
            if(NULL == pTrump)
                continue;
            iter = _mapRoleTrumpData.find(pTrump->sItemInfo.qwInstID);
            if(iter != _mapRoleTrumpData.end())
            {
                const DBRoleTrumpTable& rTrumpData = iter->second;
                pTrump->byUsed = rTrumpData._byUsed;
                pTrump->dwExp = rTrumpData._dwExp;
                pTrump->wLevel = rTrumpData._wLevel;
                pTrump->wRank = rTrumpData._wRank;
                setUseTrump.insert(rTrumpData.GetInstID());
            }
        }
    }

    if (setUseTrump.size() != _mapRoleTrumpData.size())
        LOG_CRI << "数据不一致，清除多余数据";
    else
        return ;

    for (iter = _mapRoleTrumpData.begin();iter != _mapRoleTrumpData.end();iter++)
    {
        if(setUseTrump.find(iter->first) == setUseTrump.end())
        {
            if (iter->second.IsInDB())
                _vecDelTrump.push_back(iter->first);
        }
    }
}

void DBRoleTrumpTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelTrump.begin();deliter != _vecDelTrump.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblroletrumpdata WHERE qwInstID = " << *deliter << ";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
                this->_nErrQuery++;
            if (this->_nNowQuery == 0)
                fun(this->_nMaxQuery,this->_nErrQuery);
        });
    }
    _vecDelTrump.clear();

    for (auto iter = _mapRoleTrumpData.begin();iter != _mapRoleTrumpData.end();iter++)
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

UINT32 DBRoleTrumpTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleTrumpData.begin();iter != _mapRoleTrumpData.end();iter++)
    {
        if (iter->second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelTrump.size();

}

void DBRoleTrumpTableManager::DelData(string& strData)
{
    CInArchive ar(strData);
    SItem_Wrapper weakPtr;
    ar >> weakPtr;
    if(weakPtr.ptr->GetClassType() != eType_STrump)
        return ;

    STrumpPtr pTrump = dynamic_pointer_cast<STrump>(weakPtr.ptr);
    if(pTrump == NULL)
    {
        return ;
    }
    auto iter = _mapRoleTrumpData.find(pTrump->sItemInfo.qwInstID);
    if (iter != _mapRoleTrumpData.end())
    {
        if (iter->second.IsInDB())
            _vecDelTrump.push_back(pTrump->sItemInfo.qwInstID);
        _mapRoleTrumpData.erase(iter);
    }
}

