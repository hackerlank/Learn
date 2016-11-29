
#include "DBRoleAchievementTable.h"

void CDBRoleAchievementTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SAchievementInfo oAchievement;
    ar >> oAchievement;
    static_cast<SAchievementInfo&>(*this) = oAchievement;
}
void CDBRoleAchievementTable::InitDataByBase(const SAchievementInfo  &rInfo)
{
    static_cast<SAchievementInfo&>(*this) = rInfo;
}

bool CDBRoleAchievementTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SAchievementInfo newData;
    ar >> newData;

    DIFF(qwRoleID      );
    DIFF(wAchievementID);
    DIFF(dwCount       );
    DIFF(dwProcess     );
    DIFF(dwFinishTime  );
    return  !_setChanged.none();
}

bool CDBRoleAchievementTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleAchievement(qwRoleID";
    ostr << ","<< "wAchievementID";
    ostr << ","<< "dwCount       ";
    ostr << ","<< "dwProcess     ";
    ostr << ","<< "dwFinishTime  ";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wAchievementID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwCount;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwProcess;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwFinishTime;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleAchievementTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleAchievement SET";

    //    UPDATE_UINT_SAME(dwHorseID   );
    UPDATE_UINT_SAME(dwCount);
    UPDATE_UINT_SAME(dwProcess);
    UPDATE_UINT_SAME(dwFinishTime);

    ostr << " WHERE qwRoleID=" << qwRoleID << " and wAchievementID="<<wAchievementID<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleAchievementTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleAchievementTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_UINT_SAME(wAchievementID);
    GET_UINT_SAME(dwCount       );
    GET_UINT_SAME(dwProcess     );
    GET_UINT_SAME(dwFinishTime  );
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleAchievementTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleAchievement WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblroleAchievement is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for (UINT32 i =0; i < ncount; i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            CDBRoleAchievementTable oTable(qwRoleID);
            oTable.InitDataByDBRow(rRow);
            SAchieveKey oKey(oTable.qwRoleID,oTable.wAchievementID);
            _mapRoleAchievementData[oKey]= oTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void CDBRoleAchievementTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SAchievementInfo oAchievement;
    ar >> oAchievement;
    SAchieveKey oKey(oAchievement.qwRoleID,oAchievement.wAchievementID);
    auto iter = _mapRoleAchievementData.find(oKey);
    if (iter == _mapRoleAchievementData.end())
    {
        CDBRoleAchievementTable oTemp(oAchievement.qwRoleID);
        oTemp.Update(strData,true);

        _mapRoleAchievementData[oKey] = oTemp;
    }
    else if(iter != _mapRoleAchievementData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleAchievementTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleAchievementData.begin();iter != _mapRoleAchievementData.end();iter++)
    {
        rData.vecAchievementInfo.push_back(iter->second);
    }


}

void CDBRoleAchievementTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelAchievement.begin();deliter != _vecDelAchievement.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblroleAchievement WHERE qwRoleID = "<<deliter->qwRoleID<<" and wAchievementID="<<deliter->wAchievementID<<";";
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
    _vecDelAchievement.clear();
    for (auto iter = _mapRoleAchievementData.begin();iter != _mapRoleAchievementData.end();iter++)
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

UINT32 CDBRoleAchievementTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleAchievementData.begin();iter != _mapRoleAchievementData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelAchievement.size();

}

void CDBRoleAchievementTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SAchievementInfo oAchievement;
    ar >> oAchievement;
    SAchieveKey oKey(oAchievement.qwRoleID,oAchievement.wAchievementID);
    auto iter = _mapRoleAchievementData.find(oKey);
    if (iter != _mapRoleAchievementData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDelAchievement.push_back(oKey);
        }

        _mapRoleAchievementData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

