
#include "DBRoleCollectionTable.h"

void CDBRoleCollectionTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SCollectionInfo oCollection;
    ar >> oCollection;
    static_cast<SCollectionInfo&>(*this) = oCollection;
}
void CDBRoleCollectionTable::InitDataByBase(const SCollectionInfo  &rInfo)
{
    static_cast<SCollectionInfo&>(*this) = rInfo;
}

bool CDBRoleCollectionTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SCollectionInfo newData;
    ar >> newData;

    DIFF(qwRoleID      );
    DIFF(wCollectionID);
    DIFF(dwCount       );
    DIFF(dwProcess     );
    DIFF(dwFinishTime  );
    return  !_setChanged.none();
}

bool CDBRoleCollectionTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleCollection(qwRoleID";
    ostr << ","<< "wCollectionID";
    ostr << ","<< "dwCount       ";
    ostr << ","<< "dwProcess     ";
    ostr << ","<< "dwFinishTime  ";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wCollectionID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwCount;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwProcess;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwFinishTime;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleCollectionTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleCollection SET";

    //    UPDATE_UINT_SAME(dwHorseID   );
    UPDATE_UINT_SAME(dwCount);
    UPDATE_UINT_SAME(dwProcess);
    UPDATE_UINT_SAME(dwFinishTime);

    ostr << " WHERE qwRoleID=" << qwRoleID << " and wCollectionID="<<wCollectionID<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleCollectionTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleCollectionTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_UINT_SAME(wCollectionID);
    GET_UINT_SAME(dwCount       );
    GET_UINT_SAME(dwProcess     );
    GET_UINT_SAME(dwFinishTime  );
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleCollectionTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleCollection WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblroleCollection is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for(UINT32 i =0 ; i< ncount;i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            CDBRoleCollectionTable oTable(qwRoleID);
            oTable.InitDataByDBRow(rRow);
            SCollectKey oKey(oTable.qwRoleID,oTable.wCollectionID);
            _mapRoleCollectionData[oKey]= oTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void CDBRoleCollectionTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SCollectionInfo oCollection;
    ar >> oCollection;
    SCollectKey oKey(oCollection.qwRoleID,oCollection.wCollectionID);
    auto iter = _mapRoleCollectionData.find(oKey);
    if (iter == _mapRoleCollectionData.end())
    {
        CDBRoleCollectionTable oTemp(oCollection.qwRoleID);
        oTemp.Update(strData,true);

        _mapRoleCollectionData[oKey] = oTemp;
    }
    else if(iter != _mapRoleCollectionData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleCollectionTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleCollectionData.begin();iter != _mapRoleCollectionData.end();iter++)
    {
        rData.vecCollectionInfo.push_back(iter->second);
    }


}

void CDBRoleCollectionTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelCollection.begin();deliter != _vecDelCollection.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblroleCollection WHERE qwRoleID = "<<deliter->qwRoleID<<" and wCollectionID="<<deliter->wCollectionID<<";";
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
    _vecDelCollection.clear();

    for (auto iter = _mapRoleCollectionData.begin();iter != _mapRoleCollectionData.end();iter++)
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

UINT32 CDBRoleCollectionTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleCollectionData.begin();iter != _mapRoleCollectionData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelCollection.size();

}

void CDBRoleCollectionTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SCollectionInfo oCollection;
    ar >> oCollection;
    SCollectKey oKey(oCollection.qwRoleID,oCollection.wCollectionID);
    auto iter = _mapRoleCollectionData.find(oKey);
    if (iter != _mapRoleCollectionData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDelCollection.push_back(oKey);
        }

        _mapRoleCollectionData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

