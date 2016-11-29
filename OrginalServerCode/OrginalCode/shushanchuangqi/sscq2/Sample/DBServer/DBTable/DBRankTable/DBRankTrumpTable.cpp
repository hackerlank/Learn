// =====================================================================================
//
//       Filename:  DBRankTrumpTable.cpp
//
//    Description:  法宝排行榜表操作
//
//        Version:  1.0
//        Created:  09/05/2014 02:52:07 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#include "DBRankTrumpTable.h"

CDBRankTrumpTable::CDBRankTrumpTable():
    _qwRoleID(0), _dwBattlePoint(0), _dwUpdateTime(0), _wPlayerFighterID(0), _wID(0), _byQuality(0), _byVIPLevel(0)
{
}

CDBRankTrumpTable::~CDBRankTrumpTable()
{
}

void CDBRankTrumpTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SRRTrumpInfo sRankTrump;
    ar >> sRankTrump;

    if(!InitDataByRankTrump(sRankTrump))
        return ;
}

bool CDBRankTrumpTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SRRTrumpInfo sRankTrump;
    ar >> sRankTrump;

    DIFFONLY2(qwRoleID, sRankTrump.qwRoleID, _qwRoleID);
    DIFFONLY2(dwBattlePoint, sRankTrump.dwBattlePoint, _dwBattlePoint);
    DIFFONLY2(strName, sRankTrump.strName, _strName);
    DIFFONLY2(dwUpdateTime, sRankTrump.dwUpdateTime, _dwUpdateTime);
    DIFFONLY2(strGuildName, sRankTrump.strGuildName, _strGuildName);
    DIFFONLY2(wPlayerFighterID, sRankTrump.wPlayerFighterID, _wPlayerFighterID);
    DIFFONLY2(wID, sRankTrump.wID, _wID);
    DIFFONLY2(byQuality, sRankTrump.byQuality, _byQuality);
    DIFFONLY2(byVIPLevel, sRankTrump.byVIPLevel, _byVIPLevel);

    return  !_setChanged.none();
}

bool CDBRankTrumpTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleranktrump(qwRoleID, dwBattlePoint, strName, dwUpdateTime, strGuildName, wPlayerFighterID, wID, byQuality, byVIPLevel) "\
        "Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwBattlePoint;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strName;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwUpdateTime;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strGuildName;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_wPlayerFighterID;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byQuality;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byVIPLevel;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRankTrumpTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleranktrump SET";

    UPDATE_UBIGINT(qwRoleID, _qwRoleID);
    UPDATE_UINT(dwBattlePoint, _dwBattlePoint);
    UPDATE_STRING_CHAR(strName, _strName);
    UPDATE_UINT(dwUpdateTime, _dwUpdateTime);
    UPDATE_STRING_CHAR(strGuildName, _strGuildName);
    UPDATE_UTINYINT(wPlayerFighterID, _wPlayerFighterID);
    UPDATE_SMALLINT(wID, _wID);
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

void CDBRankTrumpTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRankTrumpTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwRoleID, _qwRoleID);
    GET_UINT(dwBattlePoint, _dwBattlePoint);
    GET_STRING_CHAR(strName, _strName);
    GET_UINT(dwUpdateTime, _dwUpdateTime);
    GET_STRING_CHAR(strGuildName, _strGuildName);
    GET_UTINYINT(wPlayerFighterID, _wPlayerFighterID);
    GET_SMALLINT(wID, _wID);
    GET_UTINYINT(byQuality, _byQuality);
    GET_UTINYINT(byVIPLevel, _byVIPLevel);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  CDBRankTrumpTable::GetRoleID() const
{
    return _qwRoleID;
}

UINT32  CDBRankTrumpTable::GetBattlePoint() const
{
    return _dwBattlePoint;
}

const string& CDBRankTrumpTable::GetName() const
{
    return _strName;
}

UINT32 CDBRankTrumpTable::GetUpdataTime() const
{
    return _dwUpdateTime;
}

const string& CDBRankTrumpTable::GetGuildName() const
{
    return _strGuildName;
}

UINT16 CDBRankTrumpTable::GetPlayerFighterID() const
{
    return _wPlayerFighterID;
}

UINT16 CDBRankTrumpTable::GetID() const
{
    return _wID;
}

UINT8 CDBRankTrumpTable::GetQuality() const
{
    return _byQuality;
}

UINT8 CDBRankTrumpTable::GetVIPLevel() const
{
    return _byVIPLevel;
}

bool CDBRankTrumpTable::InitDataByRankTrump(const SRRTrumpInfo& rRankInfo)
{
    _qwRoleID         = rRankInfo.qwRoleID;
    _dwBattlePoint    = rRankInfo.dwBattlePoint;
    _strName          = rRankInfo.strName;
    _dwUpdateTime     = rRankInfo.dwUpdateTime;
    _strGuildName     = rRankInfo.strGuildName;
    _wPlayerFighterID = rRankInfo.wPlayerFighterID;
    _wID              = rRankInfo.wID;
    _byQuality        = rRankInfo.byQuality;
    _byVIPLevel       = rRankInfo.byVIPLevel;
    return true;
}

CDBRankTrumpTableManager::CDBRankTrumpTableManager(UINT64 qwRoleID) : 
    CTableManagerBaseForRoleRank(eRTTrump,qwRoleID), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0)
{
}

CDBRankTrumpTableManager::~CDBRankTrumpTableManager()
{
}

void CDBRankTrumpTableManager::QueryDataByRoleID(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleranktrump WHERE qwRoleID = " << qwRoleID << " order by `dwBattlePoint`;";

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
                        CDBRankTrumpTable cDBRankTrumpTable;
                        cDBRankTrumpTable.InitDataByDBRow(rRow);
                        //STrumpKey sKey(cDBRankTrumpTable.GetRoleID(), cDBRankTrumpTable.GetID());
                        //_mapRankData.insert(make_pair(sKey, cDBRankTrumpTable));
                        _mapRankData.insert(make_pair(cDBRankTrumpTable.GetRoleID(), cDBRankTrumpTable));
                    }
                }
                queryfun(byRet, dwCount);
            });
}

void CDBRankTrumpTableManager::Update(string& strData, EDataChange eUpdateType)
{
    CInArchive ar(strData);

    SRRTrumpInfo sRankTrump;
    ar >> sRankTrump;

    //STrumpKey sKey(sRankTrump.qwRoleID, sRankTrump.wID);
    //auto iter = _mapRankData.find(sKey);
    auto iter = _mapRankData.find(sRankTrump.qwRoleID);
    if (iter == _mapRankData.end())
    {
        CDBRankTrumpTable cDBRankTrumpTable;
        cDBRankTrumpTable.Update(strData, true);
        //_mapRankData.insert(make_pair(sKey, cDBRankTrumpTable));
        _mapRankData.insert(make_pair(cDBRankTrumpTable.GetRoleID(), cDBRankTrumpTable));
    }
    else
        iter->second.Update(strData, false);
}

void CDBRankTrumpTableManager::GetAllInfo(TVecRankInfo& vecData)
{
    for (auto it = _mapRankData.begin(); it != _mapRankData.end(); ++it)
    {
        SRRTrumpInfoPtr pInfo (new SRRTrumpInfo);
        pInfo->qwRoleID         = (it->second).GetRoleID();
        pInfo->dwValue          = (it->second).GetBattlePoint();
        pInfo->dwBattlePoint    = (it->second).GetBattlePoint();
        pInfo->strName          = (it->second).GetName();
        pInfo->dwUpdateTime     = (it->second).GetUpdataTime();
        pInfo->strGuildName     = (it->second).GetGuildName();
        pInfo->wPlayerFighterID = (it->second).GetPlayerFighterID();
        pInfo->wID              = (it->second).GetID();
        pInfo->byQuality        = (it->second).GetQuality();
        pInfo->byVIPLevel       = (it->second).GetVIPLevel();
        vecData.push_back(pInfo);
    }
}

void CDBRankTrumpTableManager::DumpToDBRank(ManagerUpdateFun fun)
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
        sqlstr << "delete FROM tblroleranktrump WHERE "\
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

UINT32 CDBRankTrumpTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto it = _mapRankData.begin();it != _mapRankData.end();it++)
    {
        if ((it->second).HasOP())
            dwOP++;
    }
    return dwOP + _vecDelRoleID.size();

}

void CDBRankTrumpTableManager::DelData(string& strData, UINT64 qwRoleID /* = 0 */)
{
    CInArchive ar(strData);
    SRRTrumpInfo sRankInfo;
    ar >> sRankInfo;

    //STrumpKey sKey(sRankInfo.qwRoleID, sRankInfo.wID);
    //auto it = _mapRankData.find(sKey);
    auto it = _mapRankData.find(sRankInfo.qwRoleID);
    if (it != _mapRankData.end())
    {
        if ((it->second).IsInDB())
            _vecDelRoleID.push_back(qwRoleID?qwRoleID:sRankInfo.qwRoleID);
        _mapRankData.erase(it);
    }
}


