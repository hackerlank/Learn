
#include "DBRoleAttackedTable.h"

void CDBRoleAttackedDBTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SRoleAttaked oRoleAttaked;
    ar >> oRoleAttaked;
    static_cast<SRoleAttaked&>(*this) = oRoleAttaked;
}
void CDBRoleAttackedDBTable::InitDataByBase(const SRoleAttaked  &rInfo)
{
    static_cast<SRoleAttaked&>(*this) = rInfo;
}

bool CDBRoleAttackedDBTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SRoleAttaked oRoleAttaked;
    ar >> oRoleAttaked;
    SRoleAttaked newData = oRoleAttaked;

    DIFF( qwAtkRoleID       );
    DIFF( strRoleName   );
    DIFF( dwAttackedTime       );
    DIFF( dwFighterType    );
    DIFF( byLevel    );
    return  !_setChanged.none();
}

bool CDBRoleAttackedDBTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleAttaked(qwRoleID";
    ostr << ","<< "dwPos             ";
    ostr << ","<< "qwAtkRoleID       ";
    ostr << ","<< "strRoleName       ";
    ostr << ","<< "dwAttackedTime    ";
    ostr << ","<< "dwFighterType     ";
    ostr << ","<< "byLevel           ";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwPos;
    ostr << "," <<(mysqlpp::sql_bigint_unsigned)qwAtkRoleID;
    ostr << "," <<"'"<<(mysqlpp::sql_char)strRoleName<<"'";
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwAttackedTime;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwFighterType;
    ostr << "," <<(mysqlpp::sql_int_unsigned)byLevel;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleAttackedDBTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleAttaked SET";

    UPDATE_UBIGINT_SAME(qwAtkRoleID   );
    UPDATE_STRING_CHAR_SAME(strRoleName   );
    UPDATE_UINT_SAME(dwAttackedTime);
    UPDATE_UINT_SAME(dwFighterType );
    UPDATE_UINT_SAME(byLevel);
    ostr << " WHERE qwRoleID=" << qwRoleID << " and dwPos="<<dwPos<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleAttackedDBTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleAttackedDBTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
 
    GET_UBIGINT_SAME(qwRoleID);
    GET_UINT_SAME(dwPos   );
    GET_UBIGINT_SAME(qwAtkRoleID);
    GET_STRING_CHAR_SAME(strRoleName   );
    GET_UINT_SAME(dwAttackedTime);
    GET_UINT_SAME(dwFighterType);
    GET_UINT_SAME(byLevel);
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBRoleAttackedTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleAttaked WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblroleAttaked is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for (UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBRoleAttackedDBTable oTable(qwRoleID);
                oTable.InitDataByDBRow(rRow);
                SAttackedKey oKey(qwRoleID,oTable.dwPos);
                _mapRoleAttackedDBData[oKey]= oTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBRoleAttackedTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SRoleAttaked oRoleAttaked;
    ar >> oRoleAttaked;
    UINT64 qwRoleID = oRoleAttaked.qwRoleID;
    SAttackedKey oKey(oRoleAttaked.qwRoleID,oRoleAttaked.dwPos);
    auto iter = _mapRoleAttackedDBData.find(oKey);
    if (iter == _mapRoleAttackedDBData.end())
    {
        CDBRoleAttackedDBTable oTemp(qwRoleID);
        oTemp.Update(strData,true);
        _mapRoleAttackedDBData[oKey] = oTemp;
    }
    else if(iter != _mapRoleAttackedDBData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleAttackedTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleAttackedDBData.begin();iter != _mapRoleAttackedDBData.end();iter++)
    {

        SRoleAttaked oRoleAttaked;
        oRoleAttaked.qwRoleID    =iter->second.qwRoleID;
        oRoleAttaked.dwPos   =iter->second.dwPos;
        oRoleAttaked.qwAtkRoleID    =iter->second.qwAtkRoleID;
        oRoleAttaked.dwPos       =iter->second.dwPos       ;
        oRoleAttaked.strRoleName   =iter->second.strRoleName;
        oRoleAttaked.dwAttackedTime       =iter->second.dwAttackedTime;
        oRoleAttaked.dwFighterType      =iter->second.dwFighterType;        
        oRoleAttaked.byLevel      = iter->second.byLevel;

        rData.vecRoleAttaked.push_back(oRoleAttaked);
    }


}

void CDBRoleAttackedTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDel.begin();deliter != _vecDel.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblroleAttaked WHERE qwRoleID = "<<deliter->qwRoleID<<" and dwPos="<<deliter->dwPos<<";";
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
    _vecDel.clear();
    for (auto iter = _mapRoleAttackedDBData.begin();iter != _mapRoleAttackedDBData.end();iter++)
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

UINT32 CDBRoleAttackedTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleAttackedDBData.begin();iter != _mapRoleAttackedDBData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDel.size();

}

void CDBRoleAttackedTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SRoleAttaked oRoleAttaked;
    ar >> oRoleAttaked;
    SAttackedKey oKey(oRoleAttaked.qwRoleID,oRoleAttaked.dwPos);
    auto iter = _mapRoleAttackedDBData.find(oKey);
    if (iter != _mapRoleAttackedDBData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDel.push_back(oKey);
        }

        _mapRoleAttackedDBData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

