
#include "DBRoleYDTable.h"

void CDBRoleYDDBTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SPlatformParam oYD;
    ar >> oYD;
    static_cast<SPlatformParam&>(*this) = oYD;
}
void CDBRoleYDDBTable::InitDataByBase(const SPlatformParam  &rInfo)
{
    static_cast<SPlatformParam&>(*this) = rInfo;
}

bool CDBRoleYDDBTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SPlatformParam newData;
    ar >> newData;
    DIFF(byQQPtLv);
    DIFF(bySPType);
    return  !_setChanged.none();
}

bool CDBRoleYDDBTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Replace into tblroleyd(qwRoleID";
    ostr << ","<< "byPtType";
    ostr << ","<< "byQQPtType";
    ostr << ","<< "byQQPtLv";
    ostr << ","<< "bySPType";
    ostr << ") Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byPtType;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byQQPtType;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byQQPtLv;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)bySPType;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleYDDBTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleyd SET";
    UPDATE_UTINYINT_SAME(byQQPtLv);
    UPDATE_UTINYINT_SAME(bySPType);
    ostr << " WHERE qwRoleID=" << _qwRoleID << " and byPtType = " << byPtType << " and byQQPtType = " << byQQPtType << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleYDDBTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleYDDBTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
   
    UINT8 byType = 0;
    UINT8 byQQType = 0;
    GET_UBIGINT(qwRoleID, _qwRoleID);
    GET_UTINYINT(byPtType, byType);
    GET_UTINYINT(byQQPtType, byQQType);
    byPtType = static_cast<EPtType>(byType);
    byQQPtType = static_cast<EQQPtType>(byQQType);
    GET_UTINYINT_SAME(byQQPtLv);
    GET_UTINYINT_SAME(bySPType);
    TableRowBase::InitDataByDBRow(rRow);
}

void CDBRoleYDTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleyd WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblroleyd is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBRoleYDDBTable oTable(qwRoleID);
                oTable.InitDataByDBRow(rRow);
                SYDKey oKey(qwRoleID,oTable.byPtType,oTable.byQQPtType);
                _mapRoleYDDBData[oKey]= oTable;
            }
        }
        queryfun(byRet, ncount);
    });
}

void CDBRoleYDTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);
    SPlatformParam oYD;
    ar >> oYD;
    SYDKey oKey(_qwRoleID,oYD.byPtType,oYD.byQQPtType);
    auto iter = _mapRoleYDDBData.find(oKey);
    if (iter == _mapRoleYDDBData.end())
    {
        CDBRoleYDDBTable oTemp(_qwRoleID);
        oTemp.Update(strData,true);
        _mapRoleYDDBData[oKey] = oTemp;
    }
    else if(iter != _mapRoleYDDBData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBRoleYDTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter = _mapRoleYDDBData.begin();iter != _mapRoleYDDBData.end();iter++)
    {
        rData.vecPlatformParam.push_back(iter->second);
    }
}

void CDBRoleYDTableManager::GetAllInfo(TVecPlatformParam& rvecPlatform)
{
    for (auto&rPair : _mapRoleYDDBData)
    {
        SPlatformParam sPlatformParam;
        sPlatformParam.byPtType     = rPair.second.byPtType; //平台类型
        sPlatformParam.byQQPtType   = rPair.second.byQQPtType; //QQ平台类型
        sPlatformParam.byQQPtLv     = rPair.second.byQQPtLv; //QQ平台类型等级
        sPlatformParam.bySPType     = rPair.second.bySPType; //Bit位定义见EPlatformBitType
        rvecPlatform.push_back(sPlatformParam);
    }
}

void CDBRoleYDTableManager::GetAllInfo(TVecUINT64& rvecRoleID, TVecPlatformParam& rvecPlatform)
{
    for (auto&rPair : _mapRoleYDDBData)
    {
        SPlatformParam sPlatformParam;
        sPlatformParam.byPtType     = rPair.second.byPtType; //平台类型
        sPlatformParam.byQQPtType   = rPair.second.byQQPtType; //QQ平台类型
        sPlatformParam.byQQPtLv     = rPair.second.byQQPtLv; //QQ平台类型等级
        sPlatformParam.bySPType     = rPair.second.bySPType; //Bit位定义见EPlatformBitType
        rvecRoleID.push_back(_qwRoleID);
        rvecPlatform.push_back(sPlatformParam);
    }
}

void CDBRoleYDTableManager::DumpToDB(ManagerUpdateFun fun)
{
    for (auto deliter = _vecDel.begin();deliter != _vecDel.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblroleyd WHERE qwRoleID = "<<deliter->qwRoleID<<" and byPtType="<<deliter->byPtType<<" and byQQPtType="<<deliter->byQQPtType<<";";
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

    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto iter = _mapRoleYDDBData.begin();iter != _mapRoleYDDBData.end();iter++)
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

UINT32 CDBRoleYDTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleYDDBData.begin();iter != _mapRoleYDDBData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDel.size();

}

void CDBRoleYDTableManager::DelData(string& strData)
{  
    CInArchive ar(strData);
    SPlatformParam oYD;
    ar >> oYD;
    SYDKey oKey(_qwRoleID,oYD.byPtType,oYD.byQQPtType);
    auto iter = _mapRoleYDDBData.find(oKey);
    if (iter != _mapRoleYDDBData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDel.push_back(oKey);
        }

        _mapRoleYDDBData.erase(iter);
    }
}

map<UINT64, CDBRoleYDTableManager*> CDBRoleYDTableManager::s_mapRoleYDTable;

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

