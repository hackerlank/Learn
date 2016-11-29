#include "DBGameVarsMananger.h"
#include "Protocols.h"

CDBTotalGameVarsManager g_CDBTotalGameVarsManager;

void CDBTotalGameVars::InitDataByData(const SGameVarsDBInfo& rInData)
{
    static_cast<SGameVarsDBInfo &>(*this) = const_cast<SGameVarsDBInfo&>(rInData);

}

bool CDBTotalGameVars::UpdateDataByData(const SGameVarsDBInfo& newData)
{
    DIFF(qwValue);
    DIFF(dwExpired);
    return  !_setChanged.none();
}

bool CDBTotalGameVars::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream sql(NULL);
    sql <<"insert into tblgamevars(wGroup,byServerType,wVar,qwValue,dwExpired) VALUES";
    sql << "(";
    sql <<(mysqlpp::sql_smallint_unsigned)Config._wGroup;
    sql << ",";
    sql <<(mysqlpp::sql_tinyint_unsigned)byServerType;
    sql << ",";
    sql <<(mysqlpp::sql_smallint_unsigned)wVar;
    sql <<",";
    sql <<(mysqlpp::sql_bigint_unsigned)qwValue;
    sql <<",";
    sql <<(mysqlpp::sql_int_unsigned)dwExpired;
    sql <<")";
    sql <<";";
    sqlstr = sql.str();
    return true;           
}

bool CDBTotalGameVars::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblgamevars SET";
    UPDATE_UINT_SAME(qwValue);
    UPDATE_UINT_SAME(dwExpired);
    ostr << " WHERE  byServerType =" <<(mysqlpp::sql_tinyint_unsigned)byServerType << " AND " << "wVar = " << (mysqlpp::sql_smallint_unsigned)wVar <<" AND  wGroup = " <<Config._wGroup <<  ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBTotalGameVars::ResetChange(void)
{
    _setChanged.reset();
    _bIsNew = false;
}

void CDBTotalGameVars::InitDataByDBRow(const mysqlpp::Row &rRow)
{   
    GET_USMALLINT_SAME(wVar);
    GET_UTINYINT_SAME(byServerType);
    GET_UBIGINT_SAME(qwValue);
    GET_UINT_SAME(dwExpired);
}

void CDBTotalGameVarsManager::QueryData(QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblgamevars  where wGroup = "<<Config._wGroup<<";";
    CDBMgr::Instance().DoArenaSelectQuery(basesql.str(),NULL,[this, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet ;
            UINT32 ncount = dataRes.size();
            for (UINT32 i = 0; i< ncount; i++)
            {

            mysqlpp::Row& rRow = dataRes[i];
            CDBTotalGameVars GameVarsTable;
            GameVarsTable.InitDataByDBRow(rRow);
            _mapGameVarsData[GameVarsTable.GetVar()]= GameVarsTable;
            }

            queryfun(byRet, ncount);
            });
}

void CDBTotalGameVarsManager::UpdateData(const SGameVarsDBInfo &testData)
{
    auto iter = _mapGameVarsData.find(testData.wVar);
    if(iter == _mapGameVarsData.end())
    {
        CDBTotalGameVars GameVarsNew;
        GameVarsNew.InitDataByData(testData);
        GameVarsNew.SetNew(true);
        _mapGameVarsData[testData.wVar] = GameVarsNew;
    }
    else 
        iter->second.UpdateDataByData(testData);
}


void CDBTotalGameVarsManager::DumpToDB()
{
    if(GetUpdataNum() ==0 )
    {
        return ;
    }
    mysqlpp::SQLStream sqlstr(NULL);
    if(!_vecDelGameVars.empty())
    {
        sqlstr << "delete FROM tblgamevars WHERE wGroup = "<<Config._wGroup<<" AND wVar IN ( ";
        for(auto deliter = _vecDelGameVars.begin();deliter != _vecDelGameVars.end();deliter++)
        {
            if(deliter != _vecDelGameVars.begin())
            {
                sqlstr<< " , ";
            }
            sqlstr<<*deliter;
        }
        sqlstr <<");";
        LOG_CRI <<"HasDel";
    }
    string strDel = sqlstr.str();
    if(!strDel.empty())
    {
        CDBMgr::Instance().DoArenaModifyQuery(strDel,NULL, [this,strDel](INT8 byRet, mysqlpp::SimpleResult& simRes){
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << strDel << "result:" << byRet;
                LOG_CRI <<"Del_DONE";

                });
    }
    _vecDelGameVars.clear();
    for (auto iter = _mapGameVarsData.begin();iter != _mapGameVarsData.end();iter++)
    {

        bool bDoCase = true;
        if (iter->second.IsNew())
        {
            string sqlstr;
            iter->second.GetInsertSqlStr(sqlstr);
            CDBMgr::Instance().DoArenaModifyQuery(sqlstr,NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr << "result:" << byRet;
                    });
        }
        else if(iter->second.IsChange())
        {
            string sqlstr;
            iter->second.GetUpdateSqlStr(sqlstr);
            CDBMgr::Instance().DoArenaModifyQuery(sqlstr,NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr << "result:" << byRet;
                    });

        }
        else
        {
            bDoCase = false;
        }
        if(bDoCase)
        {
            iter->second.ResetChange();
        }
    }



}

UINT32 CDBTotalGameVarsManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapGameVarsData.begin();iter != _mapGameVarsData.end();iter++)
    {
        if (iter->second.IsNew() ||iter->second.IsChange())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelGameVars.size();

}

void CDBTotalGameVarsManager::DelData(UINT16 wVar)
{
    LOG_CRI << "rev Del";
    auto iter = _mapGameVarsData.find(wVar);
    if (iter != _mapGameVarsData.end())
    {
        if(!iter->second.IsNew())
        {
            _vecDelGameVars.push_back(wVar);
        }
        _mapGameVarsData.erase(wVar);
    }
}
void CDBTotalGameVarsManager::LoadData(QueyAllFun fnAck)
{
    if(_byLoadStatus == 0)
    {
        _byLoadStatus  = 1;
        _vecLoad.push_back(fnAck);
        QueryData([this](INT8 byRet,UINT32 nCount)
                {
                _byLoadStatus = 2;
                for(auto iter = _vecLoad.begin();iter != _vecLoad.end();iter++)
                {
                vecSGameVarsDBInfoPtr vecPtr(new vector<SGameVarsDBInfo>);
                if(vecPtr == NULL)
                {
                (*iter)(NULL);
                return ;
                }
                for(auto iter = _mapGameVarsData.begin();iter != _mapGameVarsData.end();iter++)
                {
                vecPtr->push_back(static_cast<SGameVarsDBInfo>(iter->second));
                }
                (*iter)(vecPtr);
                }
                _vecLoad.clear();
                });
    }
    else if(_byLoadStatus ==1)
    {
        _vecLoad.push_back(fnAck);
    }
    else if(_byLoadStatus ==2)
    {
        vecSGameVarsDBInfoPtr vecPtr(new vector<SGameVarsDBInfo>);
        if(vecPtr == NULL)
        {
            fnAck(NULL);
            return ;
        }
        for(auto iter = _mapGameVarsData.begin();iter != _mapGameVarsData.end();iter++)
        {
            vecPtr->push_back(static_cast<SGameVarsDBInfo>(iter->second));
        }
        fnAck(vecPtr);


    }
}
