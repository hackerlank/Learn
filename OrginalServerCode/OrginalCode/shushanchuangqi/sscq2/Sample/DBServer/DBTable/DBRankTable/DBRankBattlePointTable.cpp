// =====================================================================================
//
//       Filename:  DBRankBattlePointTable.cpp
//
//    Description:  排行榜战斗力表操作
//
//        Version:  1.0
//        Created:  09/05/2014 02:50:46 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#include "DBRankBattlePointTable.h"

CDBRankBattlePointTable::CDBRankBattlePointTable():
    _qwRoleID(0), _dwBattlePoint(0), _dwUpdateTime(0), _wPlayerFighterID(0), _byQuality(0), _byVIPLevel(0)
{
}

CDBRankBattlePointTable::~CDBRankBattlePointTable()
{
}

void CDBRankBattlePointTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SRRBattlePointInfo sRankBattlePoint;
    ar >> sRankBattlePoint;

    if(!InitDataByRankBattlePoint(sRankBattlePoint))
        return ;
}

bool CDBRankBattlePointTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SRRBattlePointInfo sRankBattlePoint;
    ar >> sRankBattlePoint;

    DIFFONLY2(qwRoleID, sRankBattlePoint.qwRoleID, _qwRoleID);
    DIFFONLY2(dwBattlePoint, sRankBattlePoint.dwBattlePoint, _dwBattlePoint);
    DIFFONLY2(strName, sRankBattlePoint.strName, _strName);
    DIFFONLY2(dwUpdateTime, sRankBattlePoint.dwUpdateTime, _dwUpdateTime);
    DIFFONLY2(strGuildName, sRankBattlePoint.strGuildName, _strGuildName);
    DIFFONLY2(wPlayerFighterID, sRankBattlePoint.wPlayerFighterID, _wPlayerFighterID);
    DIFFONLY2(byQuality, sRankBattlePoint.byQuality, _byQuality);
    DIFFONLY2(byVIPLevel, sRankBattlePoint.byVIPLevel, _byVIPLevel);

    return  !_setChanged.none();
}

bool CDBRankBattlePointTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolerankbattlepoint(qwRoleID, dwBattlePoint, strName, dwUpdateTime, strGuildName, wPlayerFighterID, byQuality, byVIPLevel) "\
        "Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwBattlePoint;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strName;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwUpdateTime;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strGuildName;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wPlayerFighterID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byQuality;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byVIPLevel;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRankBattlePointTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolerankbattlepoint SET";

    UPDATE_UBIGINT(qwRoleID, _qwRoleID);
    UPDATE_UINT(dwBattlePoint, _dwBattlePoint);
    UPDATE_STRING_CHAR(strName, _strName);
    UPDATE_UINT(dwUpdateTime, _dwUpdateTime);
    UPDATE_STRING_CHAR(strGuildName, _strGuildName);
    UPDATE_USMALLINT(wPlayerFighterID, _wPlayerFighterID);
    UPDATE_UTINYINT(byQuality, _byQuality);
    UPDATE_UTINYINT(byVIPLevel, _byVIPLevel);

    ostr << " WHERE qwRoleID =" << _qwRoleID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRankBattlePointTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRankBattlePointTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwRoleID, _qwRoleID);
    GET_UINT(dwBattlePoint, _dwBattlePoint);
    GET_STRING_CHAR(strName, _strName);
    GET_UINT(dwUpdateTime, _dwUpdateTime);
    GET_STRING_CHAR(strGuildName, _strGuildName);
    GET_USMALLINT(wPlayerFighterID, _wPlayerFighterID);
    GET_UTINYINT(byQuality, _byQuality);
    GET_UTINYINT(byVIPLevel, _byVIPLevel);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  CDBRankBattlePointTable::GetRoleID() const
{
    return _qwRoleID;
}

UINT32  CDBRankBattlePointTable::GetBattlePoint() const
{
    return _dwBattlePoint;
}

const string& CDBRankBattlePointTable::GetName() const
{
    return _strName;
}

UINT32 CDBRankBattlePointTable::GetUpdataTime() const
{
    return _dwUpdateTime;
}

const string& CDBRankBattlePointTable::GetGuildName() const
{
    return _strGuildName;
}

UINT16 CDBRankBattlePointTable::GetPlayerFighterID() const
{
    return _wPlayerFighterID;
}

UINT8 CDBRankBattlePointTable::GetQuality() const
{
    return _byQuality;
}

UINT8 CDBRankBattlePointTable::GetVIPLevel() const
{
    return _byVIPLevel;
}

bool CDBRankBattlePointTable::InitDataByRankBattlePoint(const SRRBattlePointInfo& rRankInfo)
{
    _qwRoleID  = rRankInfo.qwRoleID;
    _dwBattlePoint    = rRankInfo.dwBattlePoint;
    _strName          = rRankInfo.strName;
    _dwUpdateTime     = rRankInfo.dwUpdateTime;
    _strGuildName     = rRankInfo.strGuildName;
    _wPlayerFighterID = rRankInfo.wPlayerFighterID;
    _byQuality        = rRankInfo.byQuality;
    _byVIPLevel       = rRankInfo.byVIPLevel;
    return true;
}

CDBRankBattlePointTableManager::CDBRankBattlePointTableManager(UINT64 qwRoleID) : 
    CTableManagerBaseForRoleRank(eRTBattlePoint,qwRoleID), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0)
{
}

CDBRankBattlePointTableManager::~CDBRankBattlePointTableManager()
{
}

void CDBRankBattlePointTableManager::QueryDataByRoleID(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolerankbattlepoint WHERE qwRoleID = " << qwRoleID << " order by `dwBattlePoint`;";

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
                        CDBRankBattlePointTable cDBRankBattlePointTable;
                        cDBRankBattlePointTable.InitDataByDBRow(rRow);
                        _mapRankData.insert(make_pair(cDBRankBattlePointTable.GetRoleID(), cDBRankBattlePointTable));
                    }
                }
                queryfun(byRet, dwCount);
            });
}

void CDBRankBattlePointTableManager::Update(string& strData, EDataChange eUpdateType)
{
    CInArchive ar(strData);

    SRRBattlePointInfo sRankBattlePoint;
    ar >> sRankBattlePoint;

    auto iter = _mapRankData.find(sRankBattlePoint.qwRoleID);
    if (iter == _mapRankData.end())
    {
        CDBRankBattlePointTable cDBRankBattlePointTable;
        cDBRankBattlePointTable.Update(strData, true);
        _mapRankData.insert(make_pair(sRankBattlePoint.qwRoleID, cDBRankBattlePointTable));
    }
    else
        iter->second.Update(strData, false);
}

void CDBRankBattlePointTableManager::GetAllInfo(TVecRankInfo& vecData)
{
    for (auto it = _mapRankData.begin(); it != _mapRankData.end(); ++it)
    {
        SRRBattlePointInfoPtr pInfo (new SRRBattlePointInfo);
        pInfo->qwRoleID         = (it->second).GetRoleID();
        pInfo->dwValue          = (it->second).GetBattlePoint();
        pInfo->dwBattlePoint    = (it->second).GetBattlePoint();
        pInfo->strName          = (it->second).GetName();
        pInfo->dwUpdateTime     = (it->second).GetUpdataTime();
        pInfo->strGuildName     = (it->second).GetGuildName();
        pInfo->wPlayerFighterID = (it->second).GetPlayerFighterID();
        pInfo->byQuality        = (it->second).GetQuality();
        pInfo->byVIPLevel       = (it->second).GetVIPLevel();
        vecData.push_back(pInfo);
    }
}

void CDBRankBattlePointTableManager::DumpToDBRank(ManagerUpdateFun fun)
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

    for (auto it = _vecDelRoleID.begin();it != _vecDelRoleID.end(); ++ it)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblrolerankbattlepoint WHERE "\
            "qwRoleID = " << (*it) << ";";
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
    _vecDelRoleID.clear();
}

UINT32 CDBRankBattlePointTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto it = _mapRankData.begin();it != _mapRankData.end();it++)
    {
        if ((it->second).HasOP())
            dwOP++;
    }
    return dwOP + _vecDelRoleID.size();

}

void CDBRankBattlePointTableManager::DelData(string& strData, UINT64 qwRoleID /* = 0 */)
{
    CInArchive ar(strData);
    SRRBattlePointInfo sRankInfo;
    ar >> sRankInfo;

    auto it = _mapRankData.find(sRankInfo.qwRoleID);
    if (it != _mapRankData.end())
    {
        if ((it->second).IsInDB())
            _vecDelRoleID.push_back(qwRoleID?qwRoleID:sRankInfo.qwRoleID);
        _mapRankData.erase(it);
    }
}


