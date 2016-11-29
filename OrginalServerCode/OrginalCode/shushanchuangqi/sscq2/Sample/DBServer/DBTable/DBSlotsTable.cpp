#include "DBSlotsTable.h"

DBSlotsTable::DBSlotsTable():
    qwRoleID(0), qwOwnerID(0), byStoreType(0),
    wMaxSlot(0), wMaxAvaliableSlot(0)
{
}

void DBSlotsTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SRoleSlotsInfo sRoleSlotsInfo;
    ar >> sRoleSlotsInfo;
    if(!InitDataBySlots(sRoleSlotsInfo))
        return ;
}

bool DBSlotsTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SRoleSlotsInfo sRoleSlotsInfo;
    ar >> sRoleSlotsInfo;

    DIFFONLY2(qwOwnerID, sRoleSlotsInfo.qwOwnerID, qwOwnerID);
    DIFFONLY2(wMaxSlot, sRoleSlotsInfo.wMaxSlot, wMaxSlot);
    DIFFONLY2(wMaxAvaliableSlot, sRoleSlotsInfo.wMaxAvaliableSlot, wMaxAvaliableSlot);
    return  !_setChanged.none();
}

bool DBSlotsTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblslotsdata(qwRoleID,qwOwnerID,byStoreType,"\
        "wMaxSlot, wMaxAvaliableSlot) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)qwOwnerID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byStoreType;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)wMaxSlot;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)wMaxAvaliableSlot;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool DBSlotsTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblslotsdata SET";

    UPDATE_UBIGINT_SAME(qwOwnerID);
    UPDATE_UBIGINT_SAME(qwRoleID);
    UPDATE_UTINYINT_SAME(byStoreType);
    UPDATE_USMALLINT_SAME(wMaxSlot);
    UPDATE_USMALLINT_SAME(wMaxAvaliableSlot);

    ostr << " WHERE qwRoleID = " << qwRoleID 
        << " AND qwOwnerID = " << qwOwnerID
        << " AND byStoreType = " << (UINT32)byStoreType << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void DBSlotsTable::ResetChange(void)
{
    _setChanged.reset();
}

void DBSlotsTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwOwnerID);
    GET_UBIGINT_SAME(qwRoleID);
    GET_UTINYINT_SAME(byStoreType);
    GET_USMALLINT_SAME(wMaxSlot);
    GET_USMALLINT_SAME(wMaxAvaliableSlot);

    TableRowBase::InitDataByDBRow(rRow);
}

bool DBSlotsTable::InitDataBySlots(const SRoleSlotsInfo& rRoleSlotsInfo)
{
    qwRoleID = rRoleSlotsInfo.qwRoleID;
    qwOwnerID = rRoleSlotsInfo.qwOwnerID;
    byStoreType = rRoleSlotsInfo.eStoreType;
    wMaxSlot = rRoleSlotsInfo.wMaxSlot;
    wMaxAvaliableSlot = rRoleSlotsInfo.wMaxAvaliableSlot;
    return true;
}

void DBSlotsTableManager::QueryDataByRoleId(UINT64 qwRoleID, QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblslotsdata WHERE qwRoleID = " << qwRoleID  << ";";
     UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(), _byLine, [this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblslotsdata is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for (UINT32 i = 0; i < ncount; ++i)
            {
                mysqlpp::Row& rRow = dataRes[i];
                DBSlotsTable SlotsTable;
                SlotsTable.InitDataByDBRow(rRow);

                SlotsDataKey key(SlotsTable.GetRoleID(), SlotsTable.GetOwnerID(), SlotsTable.GetStoreType());
                auto iter = _mapSlotsData.find(key);
                if (iter == _mapSlotsData.end())
                    _mapSlotsData[key] = SlotsTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void DBSlotsTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SRoleSlotsInfo sRoleSlotsInfo;
    ar >> sRoleSlotsInfo;

    SlotsDataKey key(sRoleSlotsInfo.qwRoleID, sRoleSlotsInfo.qwOwnerID, (UINT8)sRoleSlotsInfo.eStoreType);
    auto iter = _mapSlotsData.find(key);
    if (iter == _mapSlotsData.end()/* && bIsAdd*/)
    {
        DBSlotsTable SlotsNew;
        SlotsNew.Update(strData, true);
        _mapSlotsData[key] = SlotsNew;
    }
    else if(iter != _mapSlotsData.end())
        iter->second.Update(strData, bIsAdd);
}

void DBSlotsTableManager::GetALLInfo(RoleDataInfo & rData)
{
    SRoleSlotsInfo rRoleSlotsInfo;
    for (auto iter = _mapSlotsData.begin(); iter != _mapSlotsData.end(); ++iter)
    {
        rRoleSlotsInfo.qwRoleID = (iter->second).GetRoleID();
        rRoleSlotsInfo.qwOwnerID = (iter->second).GetOwnerID();
        rRoleSlotsInfo.eStoreType = NItemProt::EStoreType((iter->second).GetStoreType());
        rRoleSlotsInfo.wMaxSlot = (iter->second).GetMaxSlot();
        rRoleSlotsInfo.wMaxAvaliableSlot = (iter->second).GetMaxAvaliableSlot();
        rData.vecRoleSlotsInfo.push_back(rRoleSlotsInfo);
    }
}

void DBSlotsTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelSlots.begin();deliter != _vecDelSlots.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblslotsdata WHERE qwRoleID = " << deliter->qwRoleID << " AND qwOwnerID = " << deliter->qwOwnerID << " AND byStoreType = " << (UINT32)deliter->byType << ";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
                this->_nErrQuery++;
            if (this->_nNowQuery == 0)
                fun(this->_nMaxQuery,this->_nErrQuery);
        });
    }
    _vecDelSlots.clear();
    for (auto iter = _mapSlotsData.begin();iter != _mapSlotsData.end();iter++)
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

UINT32 DBSlotsTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapSlotsData.begin();iter != _mapSlotsData.end();iter++)
    {
        if (iter->second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelSlots.size();

}

void DBSlotsTableManager::DelData(string& strData)
{
    CInArchive ar(strData);
    SRoleSlotsInfo sRoleSlotsInfo;
    ar >> sRoleSlotsInfo;

    SlotsDataKey key(sRoleSlotsInfo.qwRoleID, sRoleSlotsInfo.qwOwnerID, (UINT8)sRoleSlotsInfo.eStoreType);
    auto iter = _mapSlotsData.find(key);
    if (iter != _mapSlotsData.end())
    {
        if (iter->second.IsInDB())
            _vecDelSlots.push_back(key);
        _mapSlotsData.erase(iter);
    }
}

