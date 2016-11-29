
#include "DBRoleFightHeroTable.h"

void CDBRoleFightHeroTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SFightHeroDBInfo oFightHero;
    ar >> oFightHero;
    static_cast<SFightHeroDBInfo&>(*this) = oFightHero;
}
void CDBRoleFightHeroTable::InitDataByBase(const SFightHeroDBInfo  &rInfo)
{
    static_cast<SFightHeroDBInfo&>(*this) = rInfo;
}

bool CDBRoleFightHeroTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SFightHeroDBInfo newData;
    ar >> newData;

    DIFF(qwRoleID      );
    DIFF(wBattleType);
    DIFF(qwInstID       );
    DIFF(dwHP     );
    DIFF(dwMaxHP     );
    DIFF(dwAura     );
    return  !_setChanged.none();
}

bool CDBRoleFightHeroTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolefighthero(qwRoleID";
    ostr << ","<< "wBattleType";
    ostr << ","<< "qwInstID";
    ostr << ","<< "dwHP";
    ostr << ","<< "dwMaxHP";
    ostr << ","<< "dwAura";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wBattleType;
    ostr << "," <<(mysqlpp::sql_bigint_unsigned)qwInstID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwHP;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwMaxHP; 
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwAura; 
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleFightHeroTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolefighthero SET";

    //    UPDATE_UINT_SAME(dwHorseID   );
    //UPDATE_UINT_SAME(qwInstID);
    UPDATE_UINT_SAME(dwHP);
    UPDATE_UINT_SAME(dwMaxHP);
    UPDATE_UINT_SAME(dwAura);

    ostr << " WHERE qwRoleID=" << qwRoleID << " and wBattleType="<<wBattleType<<" and qwInstID="<<qwInstID<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleFightHeroTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleFightHeroTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_USMALLINT_SAME(wBattleType);
    GET_UBIGINT_SAME(qwInstID  );
    GET_UINT_SAME(dwHP     );
    GET_UINT_SAME(dwMaxHP     );
    GET_UINT_SAME(dwAura     );
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleFightHeroTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolefighthero WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblrolefighthero is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for (UINT32 i = 0 ; i< ncount;i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            CDBRoleFightHeroTable oTable(qwRoleID);
            oTable.InitDataByDBRow(rRow);
            SFightHeroKey oKey(oTable.qwRoleID,oTable.wBattleType,oTable.qwInstID);
            _mapRoleFightHeroData[oKey]= oTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void CDBRoleFightHeroTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SFightHeroDBInfo oFightHero;
    ar >> oFightHero;
    SFightHeroKey oKey(oFightHero.qwRoleID,oFightHero.wBattleType,oFightHero.qwInstID);
    auto iter = _mapRoleFightHeroData.find(oKey);
    if (iter == _mapRoleFightHeroData.end())
    {
        CDBRoleFightHeroTable oTemp(oFightHero.qwRoleID);
        oTemp.Update(strData,true);

        _mapRoleFightHeroData[oKey] = oTemp;
    }
    else if(iter != _mapRoleFightHeroData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleFightHeroTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleFightHeroData.begin();iter != _mapRoleFightHeroData.end();iter++)
    {
        rData.vecFightHeroDBInfo.push_back(iter->second);
    }


}

void CDBRoleFightHeroTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelFightHero.begin();deliter != _vecDelFightHero.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblrolefighthero WHERE qwRoleID = "<<deliter->qwRoleID<<" and wBattleType="<<deliter->wBattleType<<" and qwInstID="<<deliter->qwInstID<<";";
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
    _vecDelFightHero.clear();
    for (auto iter = _mapRoleFightHeroData.begin();iter != _mapRoleFightHeroData.end();iter++)
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

UINT32 CDBRoleFightHeroTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleFightHeroData.begin();iter != _mapRoleFightHeroData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelFightHero.size();

}

void CDBRoleFightHeroTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SFightHeroDBInfo oFightHero;
    ar >> oFightHero;
    SFightHeroKey oKey(oFightHero.qwRoleID,oFightHero.wBattleType,oFightHero.qwInstID);
    auto iter = _mapRoleFightHeroData.find(oKey);
    if (iter != _mapRoleFightHeroData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDelFightHero.push_back(oKey);
        }

        _mapRoleFightHeroData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

