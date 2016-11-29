
#include "DBRoleFriendsTable.h"
#include "DBRoleNameManager.h"

void CDBRoleFriendsTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SFriendDBInfo oFriendsDBInfo;
    ar >> oFriendsDBInfo;
    static_cast<SFriendDBInfo&>(*this) = oFriendsDBInfo;
}

bool CDBRoleFriendsTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SFriendDBInfo oFriendsDBInfo;
    ar >> oFriendsDBInfo;
    SFriendDBInfo& newData = oFriendsDBInfo;

    DIFF(byGroup);
    DIFF(byVIPLevel);

    return  !_setChanged.none();
}

bool CDBRoleFriendsTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolefriends(qwRoleID,qwUserID,byGroup,byVIPLevel,byColor) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)qwUserID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byGroup;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byVIPLevel;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byColor;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;
}

bool CDBRoleFriendsTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolefriends SET";

    UPDATE_UTINYINT_SAME(byGroup);
    UPDATE_UTINYINT_SAME(byVIPLevel);
    UPDATE_UTINYINT_SAME(byColor);

    ostr << " WHERE qwRoleID =" << _qwRoleID << " AND qwUserID =" << qwUserID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleFriendsTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleFriendsTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    //GET_UBIGINT_SAME(_qwRoleID); // XXX: RoleID in Super
    GET_UBIGINT_SAME(qwUserID);
    GET_UTINYINT_SAME(byGroup);
    GET_USMALLINT_SAME(wFighterID);
    GET_UTINYINT_SAME(byLevel);
    GET_USMALLINT_SAME(wMood);
    GET_UTINYINT_SAME(byVIPLevel)
    GET_UTINYINT_SAME(byColor);
    strName = RoleNameManager::Instance().GetPlayerName(qwUserID);

    TableRowBase::InitDataByDBRow(rRow);
}

void CDBRoleFriendsTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{

    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "SELECT f.qwRoleID, f.qwUserID,f.byGroup, f.byVIPLevel,f.byColor, "
        "ft.wFighterID, ft.byLevel, p.wMood "
        "FROM tblrolefriends as f,tblrolefighter as ft,tblroledata as p  "
        "WHERE f.qwRoleID = " << qwRoleID 
        << " AND p.qwRoleID = f.qwRoleID "
        "AND ft.qwRoleID = f.qwUserID "
        "AND wFighterID < 20;";

    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,
            [this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable
            {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
                LOG_INF<<"--------Load Friends is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
                UINT32 ncount = dataRes.size();
                if(byRet == 0)
                {
                    for(UINT32 i = 0; i< ncount; ++i)
                    {
                        mysqlpp::Row& rRow = dataRes[i];
                        CDBRoleFriendsTable FriendsTable(qwRoleID);
                        FriendsTable.InitDataByDBRow(rRow);
                        _mapFriendsData[FriendsTable.qwUserID] = FriendsTable;
                    }
                }
                queryfun(byRet, ncount);
            });
}

void CDBRoleFriendsTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SFriendDBInfo oFriendsDBInfo;
    ar >> oFriendsDBInfo;
    map<UINT64, CDBRoleFriendsTable>::iterator iter = _mapFriendsData.find(oFriendsDBInfo.qwUserID);
    if (iter == _mapFriendsData.end() && bIsAdd)
    {
        CDBRoleFriendsTable FriendsNew(_qwRoleID);
        FriendsNew.Update(strData, bIsAdd);
        _mapFriendsData[oFriendsDBInfo.qwUserID] = FriendsNew;
    }
    else if(iter != _mapFriendsData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleFriendsTableManager::GetALLInfo(RoleDataInfo & rData)
{
    map<UINT64,CDBRoleFriendsTable>::iterator iter;
    for (iter = _mapFriendsData.begin();iter != _mapFriendsData.end();iter++)
        rData.vecFriendsInfo.push_back(iter->second);
}

void CDBRoleFriendsTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelFriends.begin();deliter != _vecDelFriends.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblrolefriends WHERE qwRoleID = "<< _qwRoleID << " AND qwUserID =" << *deliter << ";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(), _byLine, 
                [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes)
                {
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
                    this->_nNowQuery--;
                    if (byRet)
                        this->_nErrQuery++;
                    if (this->_nNowQuery == 0)
                        fun(this->_nMaxQuery,this->_nErrQuery);
                });
    }
    _vecDelFriends.clear();

    for (auto iter = _mapFriendsData.begin();iter != _mapFriendsData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDB(_byLine,
                    [fun,this](INT8 byRet)
                    {
                        this->_nNowQuery--;
                        if (byRet)
                            this->_nErrQuery++;
                        if (this->_nNowQuery == 0)
                            fun(_nMaxQuery,this->_nErrQuery);
                    });
        }
    }   

}

UINT32 CDBRoleFriendsTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapFriendsData.begin();iter != _mapFriendsData.end();iter++)
    {
        if (iter->second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelFriends.size();

}

void CDBRoleFriendsTableManager::DelData(string& strData)
{
    CInArchive ar(strData);
    SFriendDBInfo oFriendsDBInfo;
    ar >> oFriendsDBInfo;
    auto iter = _mapFriendsData.find(oFriendsDBInfo.qwUserID);
    if (iter != _mapFriendsData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDelFriends.push_back(oFriendsDBInfo.qwUserID);

        }
        _mapFriendsData.erase(iter);

    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

