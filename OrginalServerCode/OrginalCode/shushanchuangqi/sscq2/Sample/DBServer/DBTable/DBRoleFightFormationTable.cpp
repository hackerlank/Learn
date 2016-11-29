
#include "DBRoleFightFormationTable.h"

void CDBRoleFightFormationTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SFightFormationDBInfo oFightFormation;
    ar >> oFightFormation;
    static_cast<SFightFormationDBInfo&>(*this) = oFightFormation;
}
void CDBRoleFightFormationTable::InitDataByBase(const SFightFormationDBInfo  &rInfo)
{
    static_cast<SFightFormationDBInfo&>(*this) = rInfo;
}

bool CDBRoleFightFormationTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SFightFormationDBInfo newData;
    ar >> newData;

    DIFF(qwRoleID      );
    DIFF(wBattleType);
    DIFF(wFormationID       );
    DIFF(strBattlePosInfo     );
    return  !_setChanged.none();
}

bool CDBRoleFightFormationTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolefightformation(qwRoleID";
    ostr << ","<< "wBattleType";
    ostr << ","<< "wFormationID       ";
    ostr << ","<< "strBattlePosInfo     ";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wBattleType;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wFormationID;
    ostr << "," <<"'"<<strBattlePosInfo<<"'";
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleFightFormationTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolefightformation SET";

    UPDATE_USMALLINT_SAME(wFormationID);
    UPDATE_STRING_CHAR_SAME(strBattlePosInfo);

    ostr << " WHERE qwRoleID=" << qwRoleID << " and wBattleType="<<wBattleType<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleFightFormationTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleFightFormationTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_USMALLINT_SAME(wBattleType);
    GET_USMALLINT_SAME(wFormationID  );
    GET_STRING_CHAR_SAME(strBattlePosInfo     );
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleFightFormationTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolefightformation WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblrolefightformation is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for (UINT32 i =0 ; i< ncount;i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            CDBRoleFightFormationTable oTable(qwRoleID);
            oTable.InitDataByDBRow(rRow);
            SFightFormationKey oKey(oTable.qwRoleID,oTable.wBattleType);
            _mapRoleFightFormationData[oKey]= oTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void CDBRoleFightFormationTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SFightFormationDBInfo oFightFormation;
    ar >> oFightFormation;
    SFightFormationKey oKey(oFightFormation.qwRoleID,oFightFormation.wBattleType);
    auto iter = _mapRoleFightFormationData.find(oKey);
    if (iter == _mapRoleFightFormationData.end())
    {
        CDBRoleFightFormationTable oTemp(oFightFormation.qwRoleID);
        oTemp.Update(strData,true);

        _mapRoleFightFormationData[oKey] = oTemp;
    }
    else if(iter != _mapRoleFightFormationData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleFightFormationTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleFightFormationData.begin();iter != _mapRoleFightFormationData.end();iter++)
    {
        rData.vecFightFormationDBInfo.push_back(iter->second);
    }


}

void CDBRoleFightFormationTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelFightFormation.begin();deliter != _vecDelFightFormation.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblrolefightformation WHERE qwRoleID = "<<deliter->qwRoleID<<" and wBattleType="<<deliter->wBattleType<<";";
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
    _vecDelFightFormation.clear();
    for (auto iter = _mapRoleFightFormationData.begin();iter != _mapRoleFightFormationData.end();iter++)
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

UINT32 CDBRoleFightFormationTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleFightFormationData.begin();iter != _mapRoleFightFormationData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelFightFormation.size();

}

void CDBRoleFightFormationTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SFightFormationDBInfo oFightFormation;
    ar >> oFightFormation;
    SFightFormationKey oKey(oFightFormation.qwRoleID,oFightFormation.wBattleType);
    auto iter = _mapRoleFightFormationData.find(oKey);
    if (iter != _mapRoleFightFormationData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDelFightFormation.push_back(oKey);
        }

        _mapRoleFightFormationData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

