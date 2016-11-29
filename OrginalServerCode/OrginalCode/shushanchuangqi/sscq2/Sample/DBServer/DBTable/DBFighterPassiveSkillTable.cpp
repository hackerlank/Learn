// =====================================================================================
//
//       Filename:  DBFighterPassiveSkillTable.cpp
//
//    Description:  散仙被动技能表
//
//        Version:  1.0
//        Created:  05/12/2015 01:49:33 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "DBFighterPassiveSkillTable.h"

void CDBFighterPassiveSkillTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SPassiveSkillDBInfo sInfo;
    ar >> sInfo;
    static_cast<SPassiveSkillDBInfo&>(*this) = sInfo;
}

bool CDBFighterPassiveSkillTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SPassiveSkillDBInfo sInfo;
    ar >> sInfo;

    SPassiveSkillDBInfo& newData = sInfo;

    DIFF(qwOwnerID);
    DIFF(qwRoleID);
    DIFF(dwSkillID);
    DIFF(dwSkillQuality);
    DIFF(dwSkillLevel);

    return  !_setChanged.none();
}

bool CDBFighterPassiveSkillTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolefighterpassiveskill(qwRoleID, qwOwnerID, dwSkillID, dwSkillQuality, dwSkillLevel) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)qwOwnerID;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkillID;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkillQuality;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkillLevel;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;
}

bool CDBFighterPassiveSkillTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolefighterpassiveskill SET";

    UPDATE_UINT_SAME(dwSkillID);
    UPDATE_UINT_SAME(dwSkillQuality);
    UPDATE_UINT_SAME(dwSkillLevel);

    ostr << " WHERE qwRoleID = " << qwRoleID << " AND qwOwnerID = " << qwOwnerID << " AND dwSkillID = " << dwSkillID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBFighterPassiveSkillTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBFighterPassiveSkillTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwOwnerID);
    GET_UBIGINT_SAME(qwRoleID); 

    GET_UINT_SAME(dwSkillID);
    GET_UINT_SAME(dwSkillQuality);
    GET_UINT_SAME(dwSkillLevel);

    TableRowBase::InitDataByDBRow(rRow);
}

CDBFighterPassiveSkillTableManager::CDBFighterPassiveSkillTableManager(UINT64 qwRoleID, UINT8 byLine) : 
    TableManagerBaseForRole(eTypePassiveSkillInfo, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) 
{
}

CDBFighterPassiveSkillTableManager::~CDBFighterPassiveSkillTableManager()
{

}
void CDBFighterPassiveSkillTableManager::QueryDataByRoleId(UINT64 qwRoleID, QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolefighterpassiveskill WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(), _byLine,
            [this, qwRoleID, queryfun, basesql, qwLoadTimer](INT8 byRet, mysqlpp::StoreQueryResult& vecData) mutable
            {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
                LOG_INF <<"--------Load tblrolefighterpassiveskill is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
                if(byRet == 0)
                {
                    for (auto & rRow : vecData)
                    {
                        CDBFighterPassiveSkillTable cTable;
                        cTable.InitDataByDBRow(rRow);
                        SPassiveSkillKey sKey(cTable.qwOwnerID, cTable.dwSkillID);
                        _mapPassiveSkillData[sKey] = cTable;
                    }
                }
                queryfun(byRet, vecData.size());
            });
}

void CDBFighterPassiveSkillTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SPassiveSkillDBInfo sInfo;
    ar >> sInfo;
    SPassiveSkillKey sKey(sInfo.qwOwnerID, sInfo.dwSkillID);
    auto iter = _mapPassiveSkillData.find(sKey);
    if (iter == _mapPassiveSkillData.end())
    {
        CDBFighterPassiveSkillTable cTable;
        cTable.Update(strData, bIsAdd);
        _mapPassiveSkillData[sKey] = cTable;
    }
    else if(iter != _mapPassiveSkillData.end())
        iter->second.Update(strData, false);
}

void CDBFighterPassiveSkillTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto & rPair : _mapPassiveSkillData)
        rData.vecPassiveSkillInfo.push_back(rPair.second);
}

void CDBFighterPassiveSkillTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;

    for (auto & rInfo : _vecDelPassiveSkill)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblrolefighterpassiveskill WHERE qwOwnerID = " << rInfo.qwOwnerID << " AND dwSkillID = " << rInfo.dwSkillID << ";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(), _byLine, 
                [this, fun, sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes)
                {                              
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
                    this->_nNowQuery--;
                    if (byRet)
                        this->_nErrQuery++;
                    if (this->_nNowQuery == 0)
                        fun(this->_nMaxQuery, this->_nErrQuery);
                });
    }
    _vecDelPassiveSkill.clear();
    for (auto & rPair : _mapPassiveSkillData)
    {
        if (rPair.second.HasOP())
        {
            rPair.second.DumpToDB(_byLine,
                    [fun, this](INT8 byRet)
                    {
                        this->_nNowQuery--;
                        if (byRet)
                            this->_nErrQuery++;
                        if (this->_nNowQuery == 0)
                            fun(_nMaxQuery, this->_nErrQuery);
                    });
        }
    }   
}

UINT32 CDBFighterPassiveSkillTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto & rPair : _mapPassiveSkillData)
    {
        if (rPair.second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelPassiveSkill.size();

}

void CDBFighterPassiveSkillTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SPassiveSkillDBInfo sInfo;
    ar >> sInfo;
    SPassiveSkillKey sKey(sInfo.qwOwnerID, sInfo.dwSkillID);
    auto iter = _mapPassiveSkillData.find(sKey);
    if (iter != _mapPassiveSkillData.end())
    {
        if (iter->second.IsInDB())
            _vecDelPassiveSkill.push_back(sKey);
        _mapPassiveSkillData.erase(iter);
    }
}

