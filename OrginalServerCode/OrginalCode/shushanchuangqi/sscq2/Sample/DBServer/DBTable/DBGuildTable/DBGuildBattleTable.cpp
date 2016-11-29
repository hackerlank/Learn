// =====================================================================================
//
//       Filename:  DBGuildBattleTable.cpp
//
//    Description:  帮派战相关数据存取
//
//        Version:  1.0
//        Created:  08/01/2014 06:01:25 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#include "DBGuildBattleTable.h"

CDBGuildBattleTable::CDBGuildBattleTable():
    _qwGuildID(0), _dwScore(0)
{
}

CDBGuildBattleTable::~CDBGuildBattleTable()
{
}

void CDBGuildBattleTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SDBGuildBattleInfo sGuildBattleInfo;
    ar >> sGuildBattleInfo;

    if(!InitDataByGuildBattle(sGuildBattleInfo))
        return ;
}

bool CDBGuildBattleTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SDBGuildBattleInfo sGuildBattleInfo;
    ar >> sGuildBattleInfo;

    DIFFONLY2(qwGuildID, sGuildBattleInfo.qwGuildID, _qwGuildID);
    DIFFONLY2(dwScore, sGuildBattleInfo.dwScore, _dwScore);

    return  !_setChanged.none();
}

bool CDBGuildBattleTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblguildbattle(qwGuildID,dwScore) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwGuildID;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwScore;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBGuildBattleTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblguildbattle SET";

    UPDATE_UBIGINT(qwGuildID, _qwGuildID);
    UPDATE_UINT(dwScore, _dwScore);

    ostr << " WHERE qwGuildID =" << _qwGuildID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBGuildBattleTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBGuildBattleTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwGuildID, _qwGuildID);
    GET_UINT(dwScore, _dwScore);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  CDBGuildBattleTable::GetGuildID() const
{
    return _qwGuildID;
}

UINT32  CDBGuildBattleTable::GetScore() const
{
    return _dwScore;
}

bool CDBGuildBattleTable::InitDataByGuildBattle(const SDBGuildBattleInfo& rGuildInfo)
{
    _qwGuildID      = rGuildInfo.qwGuildID;
    _dwScore        = rGuildInfo.dwScore;
    return true;
}

CDBGuildBattleTableManager::CDBGuildBattleTableManager(UINT64 qwGuildID) : 
    CTableManagerBaseForGuildPub(eGPDTBattleInfo, qwGuildID), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0)
{
}

CDBGuildBattleTableManager::~CDBGuildBattleTableManager()
{
}

void CDBGuildBattleTableManager::QueryDataByGuildID(UINT64 qwGuildID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblguildbattle WHERE qwGuildID = " << qwGuildID << ";";

    CDBMgr::Instance().DoGuildSelectQuery(basesql.str(), NULL, 
            [this, qwGuildID, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable
            {
                UINT32 dwCount = dataRes.size();
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet << ", dwCount = " << dwCount << ".";
                if(byRet == 0)
                {
                    for (UINT32 dwIndex = 0 ; dwIndex < dwCount; ++dwIndex)
                    {
                        mysqlpp::Row& rRow = dataRes[dwIndex];
                        CDBGuildBattleTable cDBGuildBattleTable;
                        cDBGuildBattleTable.InitDataByDBRow(rRow);
                        _mapGuildData[cDBGuildBattleTable.GetGuildID()] = cDBGuildBattleTable;
                    }
                }
                queryfun(byRet, dwCount);
            });
}

void CDBGuildBattleTableManager::Update(string& strData, EDataChange eUpdateType)
{
    CInArchive ar(strData);
    SDBGuildBattleInfo sGuildBattleInfo;
    ar >> sGuildBattleInfo;

    auto iter = _mapGuildData.find(sGuildBattleInfo.qwGuildID);
    if (iter == _mapGuildData.end())
    {
        CDBGuildBattleTable cDBGuildBattleTable;
        cDBGuildBattleTable.Update(strData, eUpdateType == eOpAdd);
        _mapGuildData[sGuildBattleInfo.qwGuildID] = cDBGuildBattleTable;
    }
    else
        iter->second.Update(strData, false);
}

void CDBGuildBattleTableManager::GetAllInfo(SPubGuildAllInfo& rData)
{
    // FIXME:
    if (_mapGuildData.size() > 1)
        LOG_CRI << "CDBGuildBattleTableManager _mapGuildData.size() = " << _mapGuildData.size() << ".";

    for (auto it = _mapGuildData.begin(); it != _mapGuildData.end(); ++it)
    {
        rData.sGuildBattleInfo.qwGuildID = (it->second).GetGuildID();
        rData.sGuildBattleInfo.dwScore   = (it->second).GetScore();
        break;
    }

}

void CDBGuildBattleTableManager::DumpToDBGuild(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto iter = _mapGuildData.begin();iter != _mapGuildData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDBGuild([fun,this](INT8 byRet) {
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

    for (auto it = _vecDelGuildID.begin();it != _vecDelGuildID.end(); ++ it)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblguildbattle WHERE "\
            "qwGuildID = " << (*it) << ";";
        CDBMgr::Instance().DoGuildModifyQuery(sqlstr.str(),NULL, [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
                this->_nErrQuery++;
            if (this->_nNowQuery == 0)
                fun(this->_nMaxQuery,this->_nErrQuery);
        });
    }
    _vecDelGuildID.clear();
}

UINT32 CDBGuildBattleTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapGuildData.begin();iter != _mapGuildData.end();iter++)
    {
        if (iter->second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelGuildID.size();

}

void CDBGuildBattleTableManager::DelData(string& strData, UINT64 qwGuildID /* = 0 */)
{
    CInArchive ar(strData);
    SDBGuildBattleInfo sGuildBattleInfo;
    ar >> sGuildBattleInfo;

    if (!qwGuildID)
        qwGuildID = sGuildBattleInfo.qwGuildID;

    auto iter = _mapGuildData.find(qwGuildID);
    if (iter != _mapGuildData.end())
    {
        if (iter->second.IsInDB())
            _vecDelGuildID.push_back(qwGuildID);
        _mapGuildData.erase(iter);
        LOG_DBG << "Delete Battle(" << qwGuildID << ").";
    }
}

void CDBGuildBattleTableManager::InitDataByDBRow(UINT64 qwGuildID, const mysqlpp::Row &rRow)
{
    _mapGuildData[qwGuildID].InitDataByDBRow(rRow);
}

