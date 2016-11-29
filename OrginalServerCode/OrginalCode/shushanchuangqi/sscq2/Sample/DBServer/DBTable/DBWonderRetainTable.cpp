
#include "DBWonderRetainTable.h"

void CDBWonderRetainTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SRetain oLevelPrize;
    ar >> oLevelPrize;
    static_cast<SRetain&>(*this) = oLevelPrize;
}
void CDBWonderRetainTable::InitDataByBase(const SRetain  &rInfo)
{
    static_cast<SRetain&>(*this) = rInfo;
}

bool CDBWonderRetainTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SRetain newData;
    ar >> newData;
    DIFF(dwValue        );
    DIFF(wID            );
    DIFF(strGuildName   );
    DIFF(dwTime         );
    return  !_setChanged.none();
}

bool CDBWonderRetainTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblwonderretain(qwRoleID";
    ostr << ","<< "strName    ";
    ostr << ","<< "byCareer    ";
    ostr << ","<< "bySex    ";
    ostr << ","<< "wActID    ";
    ostr << ","<< "wType     ";
    ostr << ","<< "dwValue   ";
    ostr << ","<< "dwTime    ";
    ostr << ","<< "strGuildName    ";
    ostr << ","<< "wID    ";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)strName;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byCareer;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)bySex;
    ostr << "," <<(mysqlpp::sql_smallint_unsigned)wActID;
    ostr << "," <<(mysqlpp::sql_smallint_unsigned)wType;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwValue;
    ostr << "," <<(mysqlpp::sql_int_unsigned)dwTime;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)strGuildName;
    ostr << "," <<(mysqlpp::sql_smallint_unsigned)wID;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBWonderRetainTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblwonderretain SET";
    UPDATE_UINT_SAME(dwValue);
    UPDATE_UINT_SAME(dwTime);
    UPDATE_UTINYINT_SAME(byCareer);
    UPDATE_UTINYINT_SAME(bySex);
    UPDATE_USMALLINT_SAME(wType);
    UPDATE_STRING_CHAR_SAME(strGuildName); 
    UPDATE_USMALLINT_SAME(wID);
    ostr << " WHERE qwRoleID=" << qwRoleID << " and wActID="<<wActID<<" and wType="<<wType<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBWonderRetainTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBWonderRetainTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_STRING_CHAR_SAME(strName);
    GET_STRING_CHAR_SAME(strGuildName);
    GET_SMALLINT_SAME(wID);
    GET_SMALLINT_SAME(wActID);
    GET_UTINYINT_SAME(byCareer);
    GET_UTINYINT_SAME(bySex);
    GET_SMALLINT_SAME(wType);
    GET_UINT_SAME(dwValue);
    GET_UINT_SAME(dwTime);
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBWonderRetainTableManager::QueryData()
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblwonderretain;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblwonderretain is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        UINT64 qwRoleID;
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                qwRoleID = (mysqlpp::sql_bigint_unsigned)rRow[0];
                CDBWonderRetainTable oTable(qwRoleID);
                oTable.InitDataByDBRow(rRow);
                SWonderRetainKey oKey(qwRoleID,oTable.wActID,oTable.wType);
               // LOG_CRI <<"DB:qwRoleID(" << qwRoleID<<")|wActID("<<oTable.wActID<<")|wType(" <<oTable.wType<<").";
                _mapRetainDBData[oKey]= oTable;
            }
        }
        if(byRet == 0)
           Config.SetPreLoad(eLoadRetain);
        //queryfun(byRet, ncount);
    });
}

void CDBWonderRetainTableManager::Update(const SRetain& oLevelPrize,bool bIsAdd)
{
    string strData;
    COutArchive iar(strData);
    iar << oLevelPrize;

    UINT64 qwRoleID = oLevelPrize.qwRoleID;
    SWonderRetainKey oKey(qwRoleID,oLevelPrize.wActID,oLevelPrize.wType);
    auto iter = _mapRetainDBData.find(oKey);
    if (iter == _mapRetainDBData.end())
    {
        CDBWonderRetainTable oTemp(qwRoleID);
        oTemp.Update(strData,true);
        _mapRetainDBData[oKey] = oTemp;
    }
    else if(iter != _mapRetainDBData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBWonderRetainTableManager::GetALLInfo(TVecRetain & rData)
{
    for (auto iter = _mapRetainDBData.begin();iter != _mapRetainDBData.end();iter++)
    {

        SRetain oLevelPrize;
        oLevelPrize.qwRoleID    =   iter->second.qwRoleID;
        oLevelPrize.strName     =   iter->second.strName;
        oLevelPrize.strGuildName     =   iter->second.strGuildName;
        oLevelPrize.wID     =   iter->second.wID;
        oLevelPrize.byCareer    =   iter->second.byCareer;
        oLevelPrize.bySex       =   iter->second.bySex;
        oLevelPrize.wActID      =   iter->second.wActID;
        oLevelPrize.wType       =   iter->second.wType;
        oLevelPrize.dwValue     =   iter->second.dwValue;
        oLevelPrize.dwTime      =   iter->second.dwTime;
        rData.push_back(oLevelPrize);
    }
}

void CDBWonderRetainTableManager::DumpToDB()
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;

    for (auto deliter = _vecDel.begin();deliter != _vecDel.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblwonderretain WHERE qwRoleID = "<<deliter->qwRoleID<<" and wActID="<<deliter->wActID<<" and wType="<<deliter->wType<<";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){                              
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
            {
                this->_nErrQuery++;
            }
            //if (this->_nNowQuery == 0)
            //{
            //    fun(this->_nMaxQuery,this->_nErrQuery);
            //}
        });
    }
    _vecDel.clear();

   for (auto iter = _mapRetainDBData.begin();iter != _mapRetainDBData.end();iter++)
   {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDB(_byLine,[this](INT8 byRet) {
                this->_nNowQuery--;
                if (byRet)
                {
                    this->_nErrQuery++;
                }
                else
                {

                }
                //if (this->_nNowQuery == 0)
                //{
                //    fun(_nMaxQuery,this->_nErrQuery);
                //}
            });
        }
    }   


}

UINT32 CDBWonderRetainTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRetainDBData.begin();iter != _mapRetainDBData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDel.size();

}

void CDBWonderRetainTableManager::DelData(const SRetain& oLevelPrize)
{  
    SWonderRetainKey oKey(oLevelPrize.qwRoleID,oLevelPrize.wActID,oLevelPrize.wType);
    auto iter = _mapRetainDBData.find(oKey);
    if (iter != _mapRetainDBData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDel.push_back(oKey);
        }

        _mapRetainDBData.erase(iter);
    }
}

void CDBWonderRetainTableManager::DelData(const UINT16& wActID)
{
    mysqlpp::SQLStream sqlstr(NULL);
    sqlstr<<"delete FROM tblwonderretain WHERE wActID = "<< wActID <<" ;";
    CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){                              
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
            {
                this->_nErrQuery++;
            }
            //if (this->_nNowQuery == 0)
            //{
            //    fun(this->_nMaxQuery,this->_nErrQuery);
            //}
        });
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

