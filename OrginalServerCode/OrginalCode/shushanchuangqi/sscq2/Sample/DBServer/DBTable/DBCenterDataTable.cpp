
#include "DBCenterDataTable.h"

void CDBCenterDataDBTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SCenterData oCenterData;
    ar >> oCenterData;
    static_cast<SCenterData&>(*this) = oCenterData;
}
void CDBCenterDataDBTable::InitDataByBase(const SCenterData  &rInfo)
{
    static_cast<SCenterData&>(*this) = rInfo;
}

bool CDBCenterDataDBTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SCenterData oCenterData;
    ar >> oCenterData;
    SCenterData newData = oCenterData;
    DIFF(qwParam );
    DIFF(strParam        );
    DIFF(dwParam1    );
    DIFF(dwParam2        );
    DIFF(dwParam3        );
    DIFF(qwParam4        );

    return  !_setChanged.none();
}

bool CDBCenterDataDBTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblcenterdata(qwInstID";
    ostr << ","<< "qwInstID2";
    ostr << ","<< "wType";
    ostr << ","<< "qwParam";
    ostr << ","<< "strParam";
    ostr << ","<< "dwParam1";
    ostr << ","<< "dwParam2";
    ostr << ","<< "dwParam3";
    ostr << ","<< "qwParam4";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)qwInstID;
    ostr << "," <<(mysqlpp::sql_bigint_unsigned)qwInstID2;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wType;
    ostr << "," <<(mysqlpp::sql_bigint_unsigned)qwParam;
    ostr << ",'" <<(mysqlpp::sql_char)strParam  <<"'"   ;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwParam1   ;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwParam2   ;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwParam3   ;
    ostr << "," <<(mysqlpp::sql_bigint_unsigned)qwParam4   ;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBCenterDataDBTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblcenterdata SET";

    UPDATE_UBIGINT_SAME(qwParam);
    UPDATE_STRING_CHAR_SAME(strParam);
    UPDATE_UINT_SAME(dwParam1       );
    UPDATE_UINT_SAME(dwParam2       );
    UPDATE_UINT_SAME(dwParam3       );
    UPDATE_UBIGINT_SAME(qwParam4    ); 

    ostr << " WHERE qwInstID=" << qwInstID << " and wType="<<wType<<" and qwInstID2="<<qwInstID2<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBCenterDataDBTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBCenterDataDBTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{

    GET_UINT_SAME(wType          );
    GET_UBIGINT_SAME(qwInstID    );
    GET_UBIGINT_SAME(qwInstID2   );
    GET_UBIGINT_SAME(qwParam     );
    GET_STRING_CHAR_SAME(strParam);
    GET_UINT_SAME(dwParam1       );
    GET_UINT_SAME(dwParam2       );
    GET_UINT_SAME(dwParam3       );
    GET_UBIGINT_SAME(qwParam4     );
    TableRowBase::InitDataByDBRow(rRow);
}

void CDBCenterDataDBTableManager::QueryData()
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblcenterdata;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this,basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblcenterdata is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBCenterDataDBTable oTable;
                oTable.InitDataByDBRow(rRow);
                SCenterDataKey oKey(oTable.qwInstID,oTable.qwInstID2,oTable.wType);
                _mapCenterDataDBData[oKey]= oTable;
            }
        }
        if(byRet == 0)
            Config.SetPreLoad(eLoadCenterData);
    });
}

void CDBCenterDataDBTableManager::Update(const SCenterData& oCenterData)
{
    string strData;          
    COutArchive iar(strData);
    iar << oCenterData;       

    SCenterDataKey oKey(oCenterData.qwInstID,oCenterData.qwInstID2,oCenterData.wType);
    auto iter = _mapCenterDataDBData.find(oKey);
    if (iter == _mapCenterDataDBData.end())
    {
        CDBCenterDataDBTable oTemp;
        oTemp.Update(strData,true);
        _mapCenterDataDBData[oKey] = oTemp;
    }
    else if(iter != _mapCenterDataDBData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBCenterDataDBTableManager::GetALLInfo(TVecCenterData& vecCenterData)
{
    for (auto iter = _mapCenterDataDBData.begin();iter != _mapCenterDataDBData.end();iter++)
    {
        vecCenterData.push_back(iter->second);
    }
}

void CDBCenterDataDBTableManager::DumpToDB()
{
    for (auto deliter = _vecDelCenterData.begin();deliter != _vecDelCenterData.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblcenterdata WHERE qwInstID = "<<deliter->qwInstID<<" and wType="<<deliter->wType<<" and qwInstID2="<<deliter->qwInstID2<<";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){                              
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            if (byRet)
            {
                this->_nErrQuery++;
            }
        });
    }
    _vecDelCenterData.clear();
    for (auto iter = _mapCenterDataDBData.begin();iter != _mapCenterDataDBData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDB(_byLine,[this](INT8 byRet) {
                    if (byRet)
                    {
                        LOG_CRI<<"CDBCenterDataDBTableManager Error!!!";
                    }
              });
        }
    }   

}

UINT32 CDBCenterDataDBTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapCenterDataDBData.begin();iter != _mapCenterDataDBData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelCenterData.size();

}

void CDBCenterDataDBTableManager::DelData(const SCenterData& oCenterData)
{  
    SCenterDataKey oKey(oCenterData.qwInstID,oCenterData.qwInstID2,oCenterData.wType);
    auto iter = _mapCenterDataDBData.find(oKey);
    if (iter != _mapCenterDataDBData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDelCenterData.push_back(oKey);
        }

        _mapCenterDataDBData.erase(iter);
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

