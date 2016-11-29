// =====================================================================================
//
//       Filename:  DBRankLevelTable.cpp
//
//    Description:  排行榜等级表操作
//
//        Version:  1.0
//        Created:  12/01/2014 05:58:53 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================



#include "DBRankLevelTable.h"

CDBRankLevelTable::CDBRankLevelTable():
    _qwRoleID(0), _wLevel(0), _qwExp(0), _dwUpdateTime(0), _wPlayerFighterID(0), _byQuality(0), _byVIPLevel(0)
{
}

CDBRankLevelTable::~CDBRankLevelTable()
{
}

void CDBRankLevelTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SRRLevelInfo sRankLevel;
    ar >> sRankLevel;

    if(!InitDataByRankLevel(sRankLevel))
        return ;
}

bool CDBRankLevelTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SRRLevelInfo sRankLevel;
    ar >> sRankLevel;

    DIFFONLY2(qwRoleID, sRankLevel.qwRoleID, _qwRoleID);
    DIFFONLY2(wLevel, sRankLevel.wLevel, _wLevel);
    DIFFONLY2(qwExp, sRankLevel.qwExp, _qwExp);
    DIFFONLY2(strName, sRankLevel.strName, _strName);
    DIFFONLY2(dwUpdateTime, sRankLevel.dwUpdateTime, _dwUpdateTime);
    DIFFONLY2(wPlayerFighterID, sRankLevel.wPlayerFighterID, _wPlayerFighterID);
    DIFFONLY2(byQuality, sRankLevel.byQuality, _byQuality);
    DIFFONLY2(byVIPLevel, sRankLevel.byVIPLevel, _byVIPLevel);

    return  !_setChanged.none();
}

bool CDBRankLevelTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleranklevel(qwRoleID, wLevel, qwExp, strName, dwUpdateTime, wPlayerFighterID, byQuality, byVIPLevel) "\
        "Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_int_unsigned)_wLevel;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwExp;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strName;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwUpdateTime;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wPlayerFighterID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byQuality;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byVIPLevel;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRankLevelTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleranklevel SET";

    UPDATE_UBIGINT(qwRoleID, _qwRoleID);
    UPDATE_USMALLINT(wLevel, _wLevel);
    UPDATE_UBIGINT(qwExp, _qwExp);
    UPDATE_STRING_CHAR(strName, _strName);
    UPDATE_UINT(dwUpdateTime, _dwUpdateTime);
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

void CDBRankLevelTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRankLevelTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwRoleID, _qwRoleID);
    GET_USMALLINT(wLevel, _wLevel);
    GET_UBIGINT(qwExp, _qwExp);
    GET_STRING_CHAR(strName, _strName);
    GET_UINT(dwUpdateTime, _dwUpdateTime);
    GET_USMALLINT(wPlayerFighterID, _wPlayerFighterID);
    GET_UTINYINT(byQuality, _byQuality);
    GET_UTINYINT(byVIPLevel, _byVIPLevel);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  CDBRankLevelTable::GetRoleID() const
{
    return _qwRoleID;
}

UINT16  CDBRankLevelTable::GetLevel() const
{
    return _wLevel;
}

UINT64  CDBRankLevelTable::GetExp() const
{
    return _qwExp;
}

const string& CDBRankLevelTable::GetName() const
{
    return _strName;
}

UINT32 CDBRankLevelTable::GetUpdataTime() const
{
    return _dwUpdateTime;
}

UINT16 CDBRankLevelTable::GetPlayerFighterID() const
{
    return _wPlayerFighterID;
}

UINT8 CDBRankLevelTable::GetQuality() const
{
    return _byQuality;
}

UINT8 CDBRankLevelTable::GetVIPLevel() const
{
    return _byVIPLevel;
}

bool CDBRankLevelTable::InitDataByRankLevel(const SRRLevelInfo& rRankInfo)
{
    _qwRoleID         = rRankInfo.qwRoleID;
    _wLevel           = rRankInfo.wLevel;
    _qwExp            = rRankInfo.qwExp;
    _strName          = rRankInfo.strName;
    _dwUpdateTime     = rRankInfo.dwUpdateTime;
    _wPlayerFighterID = rRankInfo.wPlayerFighterID;
    _byQuality        = rRankInfo.byQuality;
    _byVIPLevel       = rRankInfo.byVIPLevel;
    return true;
}

CDBRankLevelTableManager::CDBRankLevelTableManager(UINT64 qwRoleID) : 
    CTableManagerBaseForRoleRank(eRTLevel,qwRoleID), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0)
{
}

CDBRankLevelTableManager::~CDBRankLevelTableManager()
{
}

void CDBRankLevelTableManager::QueryDataByRoleID(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleranklevel WHERE qwRoleID = " << qwRoleID << " order by `wLevel` DESC;";

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
                        CDBRankLevelTable cDBRankLevelTable;
                        cDBRankLevelTable.InitDataByDBRow(rRow);
                        _mapRankData.insert(make_pair(cDBRankLevelTable.GetRoleID(), cDBRankLevelTable));
                    }
                }
                queryfun(byRet, dwCount);
            });
}

void CDBRankLevelTableManager::Update(string& strData, EDataChange eUpdateType)
{
    CInArchive ar(strData);

    SRRLevelInfo sRankLevel;
    ar >> sRankLevel;

    auto iter = _mapRankData.find(sRankLevel.qwRoleID);
    if (iter == _mapRankData.end())
    {
        CDBRankLevelTable cDBRankLevelTable;
        cDBRankLevelTable.Update(strData, true);
        _mapRankData.insert(make_pair(sRankLevel.qwRoleID, cDBRankLevelTable));
    }
    else
        iter->second.Update(strData, false);
}

void CDBRankLevelTableManager::GetAllInfo(TVecRankInfo& vecData)
{
    for (auto it = _mapRankData.begin(); it != _mapRankData.end(); ++it)
    {
        SRRLevelInfoPtr pInfo (new SRRLevelInfo);
        pInfo->qwRoleID         = (it->second).GetRoleID();
        pInfo->dwValue          = (it->second).GetLevel();
        pInfo->wLevel           = (it->second).GetLevel();
        pInfo->qwExp            = (it->second).GetExp();
        pInfo->strName          = (it->second).GetName();
        pInfo->dwUpdateTime     = (it->second).GetUpdataTime();
        pInfo->wPlayerFighterID = (it->second).GetPlayerFighterID();
        pInfo->byQuality        = (it->second).GetQuality();
        pInfo->byVIPLevel       = (it->second).GetVIPLevel();
        vecData.push_back(pInfo);
    }
}

void CDBRankLevelTableManager::DumpToDBRank(ManagerUpdateFun fun)
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
        sqlstr << "delete FROM tblroleranklevel WHERE "\
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

UINT32 CDBRankLevelTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto it = _mapRankData.begin();it != _mapRankData.end();it++)
    {
        if ((it->second).HasOP())
            dwOP++;
    }
    return dwOP + _vecDelRoleID.size();

}

void CDBRankLevelTableManager::DelData(string& strData, UINT64 qwRoleID /* = 0 */)
{
    CInArchive ar(strData);
    SRRLevelInfo sRankInfo;
    ar >> sRankInfo;

    auto it = _mapRankData.find(sRankInfo.qwRoleID);
    if (it != _mapRankData.end())
    {
        if ((it->second).IsInDB())
            _vecDelRoleID.push_back(qwRoleID?qwRoleID:sRankInfo.qwRoleID);
        _mapRankData.erase(it);
    }
}


