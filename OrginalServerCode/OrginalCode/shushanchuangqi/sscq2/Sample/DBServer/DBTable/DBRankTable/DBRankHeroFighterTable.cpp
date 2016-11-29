// =====================================================================================
//
//       Filename:  DBRankHeroFighterTable.cpp
//
//    Description:  散仙排行榜表操作
//
//        Version:  1.0
//        Created:  09/05/2014 02:53:24 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#include "DBRankHeroFighterTable.h"

CDBRankHeroFighterTable::CDBRankHeroFighterTable():
    _qwRoleID(0), _dwBattlePoint(0), _dwUpdateTime(0), _wID(0), _wPlayerFighterID(0), _byQuality(0), _byInfoQuality(0), _byVIPLevel(0)
{
}

CDBRankHeroFighterTable::~CDBRankHeroFighterTable()
{
}

void CDBRankHeroFighterTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SRRHeroFighterInfo sRankHeroFighter;
    ar >> sRankHeroFighter;

    if(!InitDataByRankHeroFighter(sRankHeroFighter))
        return ;
}

bool CDBRankHeroFighterTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SRRHeroFighterInfo sRankHeroFighter;
    ar >> sRankHeroFighter;

    DIFFONLY2(qwRoleID, sRankHeroFighter.qwRoleID, _qwRoleID);
    DIFFONLY2(dwBattlePoint, sRankHeroFighter.dwBattlePoint, _dwBattlePoint);
    DIFFONLY2(strName, sRankHeroFighter.strName, _strName);
    DIFFONLY2(dwUpdateTime, sRankHeroFighter.dwUpdateTime, _dwUpdateTime);
    DIFFONLY2(strGuildName, sRankHeroFighter.strGuildName, _strGuildName);
    DIFFONLY2(wID, sRankHeroFighter.wID, _wID);
    DIFFONLY2(wPlayerFighterID, sRankHeroFighter.wPlayerFighterID, _wPlayerFighterID);
    DIFFONLY2(byQuality, sRankHeroFighter.byQuality, _byQuality);
    DIFFONLY2(byInfoQuality, sRankHeroFighter.byInfoQuality, _byInfoQuality);
    DIFFONLY2(byVIPLevel, sRankHeroFighter.byVIPLevel, _byVIPLevel);

    return  !_setChanged.none();
}

bool CDBRankHeroFighterTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolerankherofighter(qwRoleID, dwBattlePoint, strName, dwUpdateTime, strGuildName, wID, wPlayerFighterID, byQuality, byInfoQuality, byVIPLevel) "\
        "Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwBattlePoint;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strName;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwUpdateTime;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strGuildName;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wID;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wPlayerFighterID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byQuality;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byInfoQuality;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byVIPLevel;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRankHeroFighterTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolerankherofighter SET";

    UPDATE_UBIGINT(qwRoleID, _qwRoleID);
    UPDATE_UINT(dwBattlePoint, _dwBattlePoint);
    UPDATE_STRING_CHAR(strName, _strName);
    UPDATE_UINT(dwUpdateTime, _dwUpdateTime);
    UPDATE_STRING_CHAR(strGuildName, _strGuildName);
    UPDATE_USMALLINT(wID, _wID);
    UPDATE_USMALLINT(wPlayerFighterID, _wPlayerFighterID);
    UPDATE_UTINYINT(byQuality, _byQuality);
    UPDATE_UTINYINT(byInfoQuality, _byInfoQuality);
    UPDATE_UTINYINT(byVIPLevel, _byVIPLevel);

    ostr << " WHERE qwRoleID =" << _qwRoleID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRankHeroFighterTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRankHeroFighterTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwRoleID, _qwRoleID);
    GET_UINT(dwBattlePoint, _dwBattlePoint);
    GET_STRING_CHAR(strName, _strName);
    GET_UINT(dwUpdateTime, _dwUpdateTime);
    GET_STRING_CHAR(strGuildName, _strGuildName);
    GET_USMALLINT(wID, _wID);
    GET_USMALLINT(wPlayerFighterID, _wPlayerFighterID);
    GET_UTINYINT(byQuality, _byQuality);
    GET_UTINYINT(byInfoQuality, _byInfoQuality);
    GET_UTINYINT(byVIPLevel, _byVIPLevel);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  CDBRankHeroFighterTable::GetRoleID() const
{
    return _qwRoleID;
}

UINT32  CDBRankHeroFighterTable::GetBattlePoint() const
{
    return _dwBattlePoint;
}

const string& CDBRankHeroFighterTable::GetName() const
{
    return _strName;
}

UINT32 CDBRankHeroFighterTable::GetUpdataTime() const
{
    return _dwUpdateTime;
}

const string& CDBRankHeroFighterTable::GetGuildName() const
{
    return _strGuildName;
}

UINT16 CDBRankHeroFighterTable::GetID() const
{
    return _wID;
}

UINT16 CDBRankHeroFighterTable::GetPlayerFighterID() const
{
    return _wPlayerFighterID;
}

UINT8 CDBRankHeroFighterTable::GetQuality() const
{
    return _byQuality;
}

UINT8 CDBRankHeroFighterTable::GetInfoQuality() const
{
    return _byInfoQuality;
}

UINT8 CDBRankHeroFighterTable::GetVIPLevel() const
{
    return _byVIPLevel;
}

bool CDBRankHeroFighterTable::InitDataByRankHeroFighter(const SRRHeroFighterInfo& rRankInfo)
{
    _qwRoleID         = rRankInfo.qwRoleID;
    _dwBattlePoint    = rRankInfo.dwBattlePoint;
    _strName          = rRankInfo.strName;
    _dwUpdateTime     = rRankInfo.dwUpdateTime;
    _strGuildName     = rRankInfo.strGuildName;
    _wID              = rRankInfo.wID;
    _wPlayerFighterID = rRankInfo.wPlayerFighterID;
    _byQuality        = rRankInfo.byQuality;
    _byInfoQuality    = rRankInfo.byInfoQuality;
    _byVIPLevel       = rRankInfo.byVIPLevel;
    return true;
}

CDBRankHeroFighterTableManager::CDBRankHeroFighterTableManager(UINT64 qwRoleID) : 
    CTableManagerBaseForRoleRank(eRTHeroFighter,qwRoleID), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0)
{
}

CDBRankHeroFighterTableManager::~CDBRankHeroFighterTableManager()
{
}

void CDBRankHeroFighterTableManager::QueryDataByRoleID(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolerankherofighter WHERE qwRoleID = " << qwRoleID << " order by `dwBattlePoint`;";

    CDBMgr::Instance().DoRankSelectQuery(basesql.str(), NULL, 
            [this, qwRoleID, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable
            {
                UINT32 dwCount = dataRes.size();
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet << ", dwCount = " << dwCount << ".";
                if(byRet == 0)
                {
                    for (UINT32 dwIndex = 0 ; dwIndex < dwCount; ++dwIndex)
                    {
                        mysqlpp::Row& rRow = dataRes[dwIndex];
                        CDBRankHeroFighterTable cDBRankHeroFighterTable;
                        cDBRankHeroFighterTable.InitDataByDBRow(rRow);
                        SHeroFighterKey sKey(cDBRankHeroFighterTable.GetRoleID(), cDBRankHeroFighterTable.GetID());
                        //LOG_WRN << "cDBRankHeroFighterTable insert:" << cDBRankHeroFighterTable.GetRoleID() << ", " << cDBRankHeroFighterTable.GetID() << ".";
                        _mapRankData.insert(make_pair(sKey, cDBRankHeroFighterTable));
                    }
                }
                queryfun(byRet, dwCount);
            });
}

void CDBRankHeroFighterTableManager::Update(string& strData, EDataChange eUpdateType)
{
    CInArchive ar(strData);

    SRRHeroFighterInfo sRankHeroFighter;
    ar >> sRankHeroFighter;

    SHeroFighterKey sKey(sRankHeroFighter.qwRoleID, sRankHeroFighter.wID);
    auto iter = _mapRankData.find(sKey);
    if (iter == _mapRankData.end())
    {
        CDBRankHeroFighterTable cDBRankHeroFighterTable;
        cDBRankHeroFighterTable.Update(strData, true);
        _mapRankData.insert(make_pair(sKey, cDBRankHeroFighterTable));
    }
    else
        iter->second.Update(strData, false);
}

void CDBRankHeroFighterTableManager::GetAllInfo(TVecRankInfo& vecData)
{
    for (auto it = _mapRankData.begin(); it != _mapRankData.end(); ++it)
    {
        SRRHeroFighterInfoPtr pInfo (new SRRHeroFighterInfo);
        pInfo->qwRoleID         = (it->second).GetRoleID();
        pInfo->dwValue          = (it->second).GetBattlePoint();
        pInfo->dwBattlePoint    = (it->second).GetBattlePoint();
        pInfo->strName          = (it->second).GetName();
        pInfo->dwUpdateTime     = (it->second).GetUpdataTime();
        pInfo->strGuildName     = (it->second).GetGuildName();
        pInfo->wID              = (it->second).GetID();
        pInfo->wPlayerFighterID = (it->second).GetPlayerFighterID();
        pInfo->byQuality        = (it->second).GetQuality();
        pInfo->byInfoQuality    = (it->second).GetInfoQuality();
        pInfo->byVIPLevel       = (it->second).GetVIPLevel();
        vecData.push_back(pInfo);
    }
}

void CDBRankHeroFighterTableManager::DumpToDBRank(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto it = _mapRankData.begin();it != _mapRankData.end();it++)
    {
        if ((it->second).HasOP())
        {
            (it->second).DumpToDBRank(
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

    for (auto it = _vecDelKey.begin();it != _vecDelKey.end(); ++ it)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblrolerankherofighter WHERE "\
            "qwRoleID = " << (*it).qwRoleID << " and wID = " << (*it).wID << ";";
        CDBMgr::Instance().DoRankModifyQuery(sqlstr.str(),NULL, 
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
    _vecDelKey.clear();
}

UINT32 CDBRankHeroFighterTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto it = _mapRankData.begin();it != _mapRankData.end();it++)
    {
        if ((it->second).HasOP())
            dwOP++;
    }
    return dwOP + _vecDelKey.size();

}

void CDBRankHeroFighterTableManager::DelData(string& strData, UINT64 qwRoleID /* = 0 */)
{
    CInArchive ar(strData);
    SRRHeroFighterInfo sRankInfo;
    ar >> sRankInfo;

    SHeroFighterKey sKey(sRankInfo.qwRoleID, sRankInfo.wID);
    auto it = _mapRankData.find(sKey);
    if (it != _mapRankData.end())
    {
        if ((it->second).IsInDB())
            _vecDelKey.push_back(sKey);
        _mapRankData.erase(it);
    }
}


