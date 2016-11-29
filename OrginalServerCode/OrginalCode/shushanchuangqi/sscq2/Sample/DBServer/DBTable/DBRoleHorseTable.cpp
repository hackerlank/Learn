
#include "DBRoleHorseTable.h"

void CDBRoleHorseDBTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SHorseDB oHorseDB;
    ar >> oHorseDB;
    static_cast<SHorseDB&>(*this) = oHorseDB;
}
void CDBRoleHorseDBTable::InitDataByBase(const SHorseDB  &rInfo)
{
    static_cast<SHorseDB&>(*this) = rInfo;
}

bool CDBRoleHorseDBTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SHorseDB oHorseDB;
    ar >> oHorseDB;
    SHorseDB newData = oHorseDB;

    DIFF(qwUserID     );
    DIFF(dwHorseLevel );
    DIFF(dwPos        );
    DIFF(dwModelID    );
    DIFF(dwExp        );
    DIFF(dwLock       );
    DIFF(strModel     );

    return  !_setChanged.none();
}

bool CDBRoleHorseDBTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolehorse(qwRoleID";
    ostr << ","<< "qwUserID    ";
    ostr << ","<< "dwHorseID   ";
    ostr << ","<< "dwHorseLevel";
    ostr << ","<< "dwPos       ";
    ostr << ","<< "dwModelID   ";
    ostr << ","<< "dwExp       ";
    ostr << ","<< "dwLock      ";
    ostr << ","<< "strModel    ";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," <<(mysqlpp::sql_bigint_unsigned)qwUserID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwHorseID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwHorseLevel;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwPos       ;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwModelID   ;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwExp       ;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwLock      ;
    ostr << ",'" <<(mysqlpp::sql_char)strModel  <<"'"    ;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleHorseDBTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolehorse SET";

    UPDATE_UINT_SAME(dwHorseLevel);
    UPDATE_UINT_SAME(dwPos       );
    UPDATE_UINT_SAME(dwModelID   );
    UPDATE_UINT_SAME(dwExp       );
    UPDATE_UINT_SAME(dwLock      );
    UPDATE_STRING_CHAR_SAME(strModel    );

    ostr << " WHERE qwRoleID=" << qwRoleID << " and dwHorseID="<<dwHorseID<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleHorseDBTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleHorseDBTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_UBIGINT_SAME(qwUserID);
    GET_UINT_SAME(dwHorseID   );
    GET_UINT_SAME(dwHorseLevel);
    GET_UINT_SAME(dwPos       );
    GET_UINT_SAME(dwModelID   );
    GET_UINT_SAME(dwExp       );
    GET_UINT_SAME(dwLock      );     
    GET_STRING_CHAR_SAME(strModel);
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleHorseDBTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolehorse WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblrolehorse is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBRoleHorseDBTable oTable(qwRoleID);
                oTable.InitDataByDBRow(rRow);
                SHorseKey oKey(qwRoleID,oTable.dwHorseID);
                _mapRoleHorseDBData[oKey]= oTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBRoleHorseDBTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SHorseDB oHorseDB;
    ar >> oHorseDB;
    UINT64 qwRoleID = oHorseDB.qwRoleID;
    SHorseKey oKey(oHorseDB.qwRoleID,oHorseDB.dwHorseID);
    auto iter = _mapRoleHorseDBData.find(oKey);
    if (iter == _mapRoleHorseDBData.end())
    {
        CDBRoleHorseDBTable oTemp(qwRoleID);
        oTemp.Update(strData,true);
        _mapRoleHorseDBData[oKey] = oTemp;
    }
    else if(iter != _mapRoleHorseDBData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleHorseDBTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleHorseDBData.begin();iter != _mapRoleHorseDBData.end();iter++)
    {

        SHorseDB oHorseDB;
        oHorseDB.qwRoleID    =iter->second.qwRoleID    ;
        oHorseDB.qwUserID    =iter->second.qwUserID    ;
        oHorseDB.dwHorseID   =iter->second.dwHorseID   ;
        oHorseDB.dwHorseLevel=iter->second.dwHorseLevel;
        oHorseDB.dwPos       =iter->second.dwPos       ;
        oHorseDB.dwModelID   =iter->second.dwModelID   ;
        oHorseDB.dwExp       =iter->second.dwExp       ;
        oHorseDB.dwLock      =iter->second.dwLock      ;        
        oHorseDB.strModel    =iter->second.strModel    ;

        rData.vecHorseDB.push_back(oHorseDB);
    }


}

void CDBRoleHorseDBTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelHorseDB.begin();deliter != _vecDelHorseDB.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblrolehorse WHERE qwRoleID = "<<deliter->qwRoleID<<" and dwHorseID="<<deliter->dwHorseID<<";";
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
    _vecDelHorseDB.clear();
    for (auto iter = _mapRoleHorseDBData.begin();iter != _mapRoleHorseDBData.end();iter++)
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

UINT32 CDBRoleHorseDBTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleHorseDBData.begin();iter != _mapRoleHorseDBData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelHorseDB.size();

}

void CDBRoleHorseDBTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SHorseDB oHorseDB;
    ar >> oHorseDB;
    SHorseKey oKey(oHorseDB.qwRoleID,oHorseDB.dwHorseID);
    auto iter = _mapRoleHorseDBData.find(oKey);
    if (iter != _mapRoleHorseDBData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDelHorseDB.push_back(oKey);
        }

        _mapRoleHorseDBData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

