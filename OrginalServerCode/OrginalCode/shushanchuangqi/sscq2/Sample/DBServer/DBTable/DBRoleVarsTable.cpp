
#include "DBRoleVarsTable.h"

void CDBRoleVarsTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SVarsDBInfo oVarsDBInfo;
    ar >> oVarsDBInfo;
    static_cast<SVarsDBInfo&>(*this) = oVarsDBInfo;
}

bool CDBRoleVarsTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SVarsDBInfo oVarsDBInfo;
    ar >> oVarsDBInfo;
    SVarsDBInfo& newData = oVarsDBInfo;

    DIFF(qwValue);
    DIFF(dwExpired);

    return  !_setChanged.none();
}

bool CDBRoleVarsTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolevars(qwRoleID,byServerType,wVar,qwValue,dwExpired) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byServerType;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)wVar;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)qwValue;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwExpired;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;
}

bool CDBRoleVarsTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolevars SET";

    UPDATE_UBIGINT_SAME(qwValue);
    UPDATE_UINT_SAME(dwExpired);

    ostr << " WHERE qwRoleID = " << _qwRoleID << " AND wVar = " << wVar << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleVarsTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleVarsTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    //GET_UBIGINT_SAME(_qwRoleID); // XXX: RoleID in Super
    GET_UTINYINT_SAME(byServerType);
    GET_USMALLINT_SAME(wVar);
    GET_UBIGINT_SAME(qwValue);
    GET_UINT_SAME(dwExpired);

    TableRowBase::InitDataByDBRow(rRow);
}

void CDBRoleVarsTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolevars WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblrolevars is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0)
            {
            for(UINT32 i =0 ; i< ncount;i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            CDBRoleVarsTable VarsTable(qwRoleID);
            VarsTable.InitDataByDBRow(rRow);
            _mapVarsData[VarsTable.wVar] = VarsTable;
            }
            }
            queryfun(byRet, ncount);
            });
}

void CDBRoleVarsTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SVarsDBInfo oVarsDBInfo;
    ar >> oVarsDBInfo;
    map<UINT16, CDBRoleVarsTable>::iterator iter = _mapVarsData.find(oVarsDBInfo.wVar);
    if (iter == _mapVarsData.end() && bIsAdd)
    {
        CDBRoleVarsTable VarsNew(_qwRoleID);
        VarsNew.Update(strData, bIsAdd);
        _mapVarsData[oVarsDBInfo.wVar] = VarsNew;
        //LOG_INF<<"var add:"<<oVarsDBInfo.wVar<<" map size:"<<_mapVarsData.size();
    }
    else if(iter != _mapVarsData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleVarsTableManager::GetALLInfo(RoleDataInfo & rData)
{
    map<UINT16,CDBRoleVarsTable>::iterator iter;
    for (iter = _mapVarsData.begin();iter != _mapVarsData.end();iter++)
        rData.vecGameVars.push_back(iter->second);
}

void CDBRoleVarsTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    //先删除，然后执行插入
    mysqlpp::SQLStream sqlstr(NULL);
    if(!_vecDelVars.empty())
    {
        sqlstr << "delete FROM tblrolevars WHERE qwRoleID = " << _qwRoleID << " AND wVar IN ( ";
        for(auto deliter = _vecDelVars.begin();deliter != _vecDelVars.end();deliter++)
        {
            if(deliter != _vecDelVars.begin())
            {
                sqlstr<< " , ";
            }
            sqlstr<<*deliter;
        }
        sqlstr <<");";
    }
    string strDel = sqlstr.str();
    if(strDel.empty())
    {

    }
    else
    {
        CDBMgr::Instance().DoRoleModifyQuery(strDel,_byLine, [this,fun,strDel](INT8 byRet, mysqlpp::SimpleResult& simRes){                              
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << strDel << "result:" << byRet;
                this->_nNowQuery-= _vecDelVars.size();
                //LOG_CRI<<"strDel---VAR--------"<<strDel;
                if (byRet)
                {
                this->_nErrQuery++;
                }
                if (this->_nNowQuery == 0)
                {
                fun(this->_nMaxQuery,this->_nErrQuery);
                return ;
                }
                        });
    }
    //删除执行完成，然后执行插入
    _vecDelVars.clear();

    for (auto iter = _mapVarsData.begin();iter != _mapVarsData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDB(_byLine,[fun,this](INT8 byRet) {
                    this->_nNowQuery--;
                     //LOG_INF<<"update ---var----11111";
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

UINT32 CDBRoleVarsTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapVarsData.begin();iter != _mapVarsData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelVars.size();

}

void CDBRoleVarsTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SVarsDBInfo oVarsDBInfo;
    ar >> oVarsDBInfo;
    auto iter = _mapVarsData.find(oVarsDBInfo.wVar);
    if (iter != _mapVarsData.end() )
    {
        if (iter->second.IsInDB())
        {
            _vecDelVars.push_back(oVarsDBInfo.wVar);

        }
        _mapVarsData.erase(iter);

    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

