
#include "DBRoleSkillTable.h"

void CDBRoleSkillTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SSkillDBInfo oSkillDBInfo;
    ar >> oSkillDBInfo;
    static_cast<SSkillDBInfo&>(*this) = oSkillDBInfo;
}

bool CDBRoleSkillTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SSkillDBInfo oSkillDBInfo;
    ar >> oSkillDBInfo;
    SSkillDBInfo& newData = oSkillDBInfo;

    DIFF(dwUpSkill1);
    DIFF(dwUpSkill2);
    DIFF(dwUpSkill3);
    DIFF(dwUpSkill4);
    DIFF(dwUpSkill5);
    DIFF(dwUpSkill6);
    DIFF(dwSkill1);
    DIFF(dwSkill2);
    DIFF(dwSkill3);
    DIFF(dwSkill4);
    DIFF(dwSkill5);
    DIFF(dwSkill6);
    DIFF(dwSkill7);
    DIFF(dwSkill8);
    DIFF(dwSkill9);
    DIFF(dwRune1);
    DIFF(dwRune2);
    DIFF(dwRune3);
    DIFF(dwRune4);
    DIFF(dwRune5);
    DIFF(dwRune6);
    DIFF(dwRune7);
    DIFF(dwRune8);
    DIFF(dwRune9);
    DIFF(dwSkillAdv1);
    DIFF(dwSkillAdv2);
    DIFF(dwSkillAdv3);
    DIFF(dwSkillAdv4);
    DIFF(dwSkillAdv5);
    DIFF(dwSkillAdv6);
    DIFF(dwSkillAdv7);
    DIFF(dwSkillAdv8);
    DIFF(dwSkillAdv9);

    return  !_setChanged.none();
}

bool CDBRoleSkillTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleskill(qwRoleID,qwOwnerID,dwUpSkill1,dwUpSkill2,dwUpSkill3,dwUpSkill4,dwUpSkill5,dwUpSkill6,dwSkill1,dwSkill2,dwSkill3,dwSkill4,dwSkill5,dwSkill6,dwSkill7,dwSkill8,dwSkill9,dwRune1,dwRune2,dwRune3,dwRune4,dwRune5,dwRune6,dwRune7,dwRune8,dwRune9,dwSkillAdv1,dwSkillAdv2,dwSkillAdv3,dwSkillAdv4,dwSkillAdv5,dwSkillAdv6,dwSkillAdv7,dwSkillAdv8,dwSkillAdv9) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)qwOwnerID;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwUpSkill1;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwUpSkill2;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwUpSkill3;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwUpSkill4;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwUpSkill5;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwUpSkill6;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkill1;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkill2;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkill3;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkill4;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkill5;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkill6;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkill7;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkill8;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkill9;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwRune1;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwRune2;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwRune3;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwRune4;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwRune5;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwRune6;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwRune7;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwRune8;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwRune9;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkillAdv1;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkillAdv2;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkillAdv3;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkillAdv4;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkillAdv5;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkillAdv6;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkillAdv7;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkillAdv8;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSkillAdv9;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;
}

bool CDBRoleSkillTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleskill SET";

    UPDATE_UINT_SAME(dwUpSkill1);
    UPDATE_UINT_SAME(dwUpSkill2);
    UPDATE_UINT_SAME(dwUpSkill3);
    UPDATE_UINT_SAME(dwUpSkill4);
    UPDATE_UINT_SAME(dwUpSkill5);
    UPDATE_UINT_SAME(dwUpSkill6);
    UPDATE_UINT_SAME(dwSkill1);
    UPDATE_UINT_SAME(dwSkill2);
    UPDATE_UINT_SAME(dwSkill3);
    UPDATE_UINT_SAME(dwSkill4);
    UPDATE_UINT_SAME(dwSkill5);
    UPDATE_UINT_SAME(dwSkill6);
    UPDATE_UINT_SAME(dwSkill7);
    UPDATE_UINT_SAME(dwSkill8);
    UPDATE_UINT_SAME(dwSkill9);
    UPDATE_UINT_SAME(dwRune1);
    UPDATE_UINT_SAME(dwRune2);
    UPDATE_UINT_SAME(dwRune3);
    UPDATE_UINT_SAME(dwRune4);
    UPDATE_UINT_SAME(dwRune5);
    UPDATE_UINT_SAME(dwRune6);
    UPDATE_UINT_SAME(dwRune7);
    UPDATE_UINT_SAME(dwRune8);
    UPDATE_UINT_SAME(dwRune9);
    UPDATE_UINT_SAME(dwSkillAdv1);
    UPDATE_UINT_SAME(dwSkillAdv2);
    UPDATE_UINT_SAME(dwSkillAdv3);
    UPDATE_UINT_SAME(dwSkillAdv4);
    UPDATE_UINT_SAME(dwSkillAdv5);
    UPDATE_UINT_SAME(dwSkillAdv6);
    UPDATE_UINT_SAME(dwSkillAdv7);
    UPDATE_UINT_SAME(dwSkillAdv8);
    UPDATE_UINT_SAME(dwSkillAdv9);

    ostr << " WHERE qwRoleID =" << _qwRoleID << " AND qwOwnerID=" << qwOwnerID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleSkillTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleSkillTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwOwnerID);
    //GET_UBIGINT_SAME(_qwRoleID); // XXX: RoleID in Super
    GET_UINT_SAME(dwUpSkill1);
    GET_UINT_SAME(dwUpSkill2);
    GET_UINT_SAME(dwUpSkill3);
    GET_UINT_SAME(dwUpSkill4);
    GET_UINT_SAME(dwUpSkill5);
    GET_UINT_SAME(dwUpSkill6);
    GET_UINT_SAME(dwSkill1);
    GET_UINT_SAME(dwSkill2);
    GET_UINT_SAME(dwSkill3);
    GET_UINT_SAME(dwSkill4);
    GET_UINT_SAME(dwSkill5);
    GET_UINT_SAME(dwSkill6);
    GET_UINT_SAME(dwSkill7);
    GET_UINT_SAME(dwSkill8);
    GET_UINT_SAME(dwSkill9);
    GET_UINT_SAME(dwRune1);
    GET_UINT_SAME(dwRune2);
    GET_UINT_SAME(dwRune3);
    GET_UINT_SAME(dwRune4);
    GET_UINT_SAME(dwRune5);
    GET_UINT_SAME(dwRune6);
    GET_UINT_SAME(dwRune7);
    GET_UINT_SAME(dwRune8);
    GET_UINT_SAME(dwRune9);
    GET_UINT_SAME(dwSkillAdv1);
    GET_UINT_SAME(dwSkillAdv2);
    GET_UINT_SAME(dwSkillAdv3);
    GET_UINT_SAME(dwSkillAdv4);
    GET_UINT_SAME(dwSkillAdv5);
    GET_UINT_SAME(dwSkillAdv6);
    GET_UINT_SAME(dwSkillAdv7);
    GET_UINT_SAME(dwSkillAdv8);
    GET_UINT_SAME(dwSkillAdv9);

    TableRowBase::InitDataByDBRow(rRow);
}

void CDBRoleSkillTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleskill WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer](INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblroleskill tblbuffdata is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for (UINT32 i = 0; i< ncount; i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBRoleSkillTable SkillTable(qwRoleID);
                SkillTable.InitDataByDBRow(rRow);
                _mapSkillData[SkillTable.qwOwnerID] = SkillTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBRoleSkillTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SSkillDBInfo oSkillDBInfo;
    ar >> oSkillDBInfo;
    UINT64 qwOwnerID = oSkillDBInfo.qwOwnerID;
    map<UINT64, CDBRoleSkillTable>::iterator iter = _mapSkillData.find(qwOwnerID);
    if (iter == _mapSkillData.end() && bIsAdd)
    {
        CDBRoleSkillTable SkillNew(_qwRoleID);
        SkillNew.Update(strData, bIsAdd);
        _mapSkillData[qwOwnerID] = SkillNew;
    }
    else if(iter != _mapSkillData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleSkillTableManager::GetALLInfo(RoleDataInfo & rData)
{
    map<UINT64,CDBRoleSkillTable>::iterator iter;
    for (iter = _mapSkillData.begin();iter != _mapSkillData.end();iter++)
        rData.vecSkillInfo.push_back(iter->second);
}

void CDBRoleSkillTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelSkill.begin();deliter != _vecDelSkill.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblroleskill WHERE qwOwnerID = " << *deliter << ";";
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
    _vecDelSkill.clear();
    for (auto iter = _mapSkillData.begin();iter != _mapSkillData.end();iter++)
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

UINT32 CDBRoleSkillTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapSkillData.begin();iter != _mapSkillData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelSkill.size();

}

void CDBRoleSkillTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SSkillDBInfo oSkillDBInfo;
    ar >> oSkillDBInfo;
    UINT64 qwOwnerID = oSkillDBInfo.qwOwnerID;
    auto iter = _mapSkillData.find(qwOwnerID);
    if (iter != _mapSkillData.end())
    {
        if (iter->second.IsInDB())
            _vecDelSkill.push_back(qwOwnerID);

        _mapSkillData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

