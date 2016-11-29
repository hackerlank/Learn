
#include "DBFighterTable.h"

void CDBFighterTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SFighterDBInfo oFighterDBInfo;
    ar >> oFighterDBInfo;
    static_cast<SFighterDBInfo&>(*this) = oFighterDBInfo;
}

bool CDBFighterTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SFighterDBInfo oFighterDBInfo;
    ar >> oFighterDBInfo;
    SFighterDBInfo& newData = oFighterDBInfo;

    DIFF(byRecruited);
    DIFF(byStar);
    DIFF(iSlot);
    DIFF(iPos);
    DIFF(byLevel);
    DIFF(qwExp);
    DIFF(byLianPi);
    DIFF(byTongJin);
    DIFF(byQiangJi);
    DIFF(byDuanGu);
    DIFF(byHuoLuo);
    DIFF(byXiSui);
    DIFF(dwDujieExp);
    DIFF(dwSpiritPower);

    return  !_setChanged.none();
}

bool CDBFighterTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolefighter(qwInstID,qwRoleID,wFighterID,byRecruited,byStar,iSlot,iPos,byLevel,qwExp,byLianPi,byTongJin,byQiangJi,byDuanGu,byHuoLuo,byXiSui,dwDujieExp,dwSpiritPower) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)qwInstID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_int_unsigned)wFighterID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byRecruited;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byStar;
    ostr << "," << (mysqlpp::sql_int)iSlot;
    ostr << "," << (mysqlpp::sql_int)iPos;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byLevel;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)qwExp;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byLianPi;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byTongJin;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byQiangJi;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byDuanGu;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byHuoLuo;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byXiSui;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwDujieExp;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSpiritPower;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBFighterTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolefighter SET";

    UPDATE_UTINYINT_SAME(byRecruited);
    UPDATE_UTINYINT_SAME(byStar);
    UPDATE_INT_SAME(iSlot);
    UPDATE_INT_SAME(iPos);
    UPDATE_UTINYINT_SAME(byLevel);
    UPDATE_UBIGINT_SAME(qwExp);
    UPDATE_UTINYINT_SAME(byLianPi);
    UPDATE_UTINYINT_SAME(byTongJin);
    UPDATE_UTINYINT_SAME(byQiangJi);
    UPDATE_UTINYINT_SAME(byDuanGu);
    UPDATE_UTINYINT_SAME(byHuoLuo);
    UPDATE_UTINYINT_SAME(byXiSui);
    UPDATE_INT_SAME(dwDujieExp);
    UPDATE_USMALLINT_SAME(dwSpiritPower);

    ostr << " WHERE qwInstID =" << qwInstID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBFighterTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBFighterTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwInstID);
    GET_USMALLINT_SAME(wFighterID);
    GET_UTINYINT_SAME(byRecruited);
    GET_UTINYINT_SAME(byStar);
    GET_INT_SAME(iSlot);
    GET_INT_SAME(iPos);
    GET_UTINYINT_SAME(byLevel);
    GET_UBIGINT_SAME(qwExp);
    GET_UTINYINT_SAME(byLianPi);
    GET_UTINYINT_SAME(byTongJin);
    GET_UTINYINT_SAME(byQiangJi);
    GET_UTINYINT_SAME(byDuanGu);
    GET_UTINYINT_SAME(byHuoLuo);
    GET_UTINYINT_SAME(byXiSui);
    GET_INT_SAME(dwDujieExp);
    GET_USMALLINT_SAME(dwSpiritPower);
    TableRowBase::InitDataByDBRow(rRow);
}

void CDBFighterTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "SELECT * FROM tblrolefighter WHERE qwRoleID = " << qwRoleID << ";";
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine
            ,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblrolefighter is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for (UINT32 i = 0; i< ncount; i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            CDBFighterTable FighterTable(qwRoleID);
            FighterTable.InitDataByDBRow(rRow);
            _mapFighterData[FighterTable.qwInstID] = FighterTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void CDBFighterTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SFighterDBInfo oFighterDBInfo;
    ar >> oFighterDBInfo;
    UINT64 qwInstID = oFighterDBInfo.qwInstID;
    map<UINT64, CDBFighterTable>::iterator iter = _mapFighterData.find(qwInstID);
    if (iter == _mapFighterData.end() && bIsAdd)
    {
        CDBFighterTable FighterNew(_qwRoleID);
        FighterNew.Update(strData, bIsAdd);
        _mapFighterData[qwInstID] = FighterNew;
    }
    else if(iter != _mapFighterData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBFighterTableManager::GetALLInfo(RoleDataInfo & rData)
{
    map<UINT64,CDBFighterTable>::iterator iter;
    for (iter = _mapFighterData.begin();iter != _mapFighterData.end();iter++)
        rData.vecFighterInfo.push_back(iter->second);
}

void CDBFighterTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelFighter.begin();deliter != _vecDelFighter.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblrolefighter WHERE qwInstID = " << *deliter << ";";
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
    _vecDelFighter.clear();

    for (auto iter = _mapFighterData.begin();iter != _mapFighterData.end();iter++)
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

UINT32 CDBFighterTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapFighterData.begin();iter != _mapFighterData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelFighter.size();

}

void CDBFighterTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SFighterDBInfo oFighterDBInfo;
    ar >> oFighterDBInfo;
    UINT64 qwInstID = oFighterDBInfo.qwInstID;
    auto iter = _mapFighterData.find(qwInstID);
    if (iter != _mapFighterData.end() )
    {
        if (iter->second.IsInDB())
        {
            _vecDelFighter.push_back(qwInstID);

        }
        _mapFighterData.erase(iter);

    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

