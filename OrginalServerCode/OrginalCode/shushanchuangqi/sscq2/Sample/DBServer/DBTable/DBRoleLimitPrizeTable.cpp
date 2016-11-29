
#include "DBRoleLimitPrizeTable.h"

void CDBRoleLimitPrizeDBTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SLimitPrize2DB oLimitPrize;
    ar >> oLimitPrize;
    static_cast<SLimitPrize2DB&>(*this) = oLimitPrize;
}

void CDBRoleLimitPrizeDBTable::InitDataByBase(const SLimitPrize2DB  &rInfo)
{
    static_cast<SLimitPrize2DB&>(*this) = rInfo;
}

bool CDBRoleLimitPrizeDBTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SLimitPrize2DB newData;
    ar >> newData;
    DIFF( qwRoleID  );
    DIFF( wPrizeID  );
    DIFF( wNum      );
    return  !_setChanged.none();
}

bool CDBRoleLimitPrizeDBTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolelimitprize(qwRoleID";
    ostr << ","<< "wPrizeID   ";
    ostr << ","<< "wNum     ";
    ostr <<") Values(";
    ostr <<       (mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wPrizeID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wNum;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleLimitPrizeDBTable::GetUpdateSqlStr(string& strsql)
{
    /*
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolelimitprize SET";
    UPDATE_UINT_SAME(wPrizeID);
    UPDATE_UINT_SAME(wNum);
    ostr << " WHERE qwRoleID=" << qwRoleID <<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    */
    return true;
}

void CDBRoleLimitPrizeDBTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleLimitPrizeDBTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
 
    GET_UBIGINT_SAME(qwRoleID);
    GET_UINT_SAME(wPrizeID);
    GET_UINT_SAME(wNum);
    TableRowBase::InitDataByDBRow(rRow);
}

void CDBRoleLimitPrizeTableManager::QueryData()
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolelimitprize;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblrolegodmonster is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        if(byRet == 0)
        {
            for (UINT32 i = 0; i< ncount; i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                CDBRoleLimitPrizeDBTable oTable;
                oTable.InitDataByDBRow(rRow);
                _vecData.push_back(oTable);
            }
        }
        if(byRet == 0) 
           Config.SetPreLoad(eLoadLimitPrize);
        //queryfun(byRet, ncount);
    });
}


void CDBRoleLimitPrizeTableManager::Update(const SLimitPrize2DB& oLimitPrize)
{
    string strData;
    COutArchive oArchive(strData);
    oArchive << oLimitPrize;
LOG_CRI << "DBRecv Data For Limit";
    CDBRoleLimitPrizeDBTable oTemp;
    oTemp.Update(strData,true);
    _vecData.push_back(oTemp);
}


void CDBRoleLimitPrizeTableManager::GetALLInfo(TVecLimitPrize2DB & rData)
{
    for (auto iter = _vecData.begin();iter != _vecData.end();iter++)
    {

        SLimitPrize2DB oLimitPrize;
        oLimitPrize.qwRoleID    = iter->qwRoleID;
        oLimitPrize.wPrizeID    = iter->wPrizeID;
        oLimitPrize.wNum        = iter->wNum;
        rData.push_back(oLimitPrize);
    }
}

void CDBRoleLimitPrizeTableManager::DumpToDB()
{
 /*   
    for (auto deliter = _vecDel.begin();deliter != _vecDel.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblrolelimitprize WHERE qwRoleID = "<<*deliter<<";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){                              
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
            {
                this->_nErrQuery++;
            }
            if (this->_nNowQuery == 0)
            {
                //fun(this->_nMaxQuery,this->_nErrQuery);
            }
        });
    }
    _vecDel.clear();
  */  
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto iter = _vecData.begin();iter != _vecData.end();iter++)
    {
        if (iter->HasOP())
        {
            iter->DumpToDB(_byLine,[this](INT8 byRet) {
                this->_nNowQuery--;
                if (byRet)
                {
                    this->_nErrQuery++;
                }
                if (this->_nNowQuery == 0)
                {
                    //fun(_nMaxQuery,this->_nErrQuery);
                }
            });
        }
    }   


}

UINT32 CDBRoleLimitPrizeTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _vecData.begin();iter != _vecData.end();iter++)
    {
        if (iter->HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP;

}
/*
void CDBRoleLimitPrizeTableManager::DelData(const SLimitPrize2DB& oLimitPrize)
{  
    UINT64 qwRoleID = oLimitPrize.qwRoleID;
    for(auto iter=_vecData.begin(); iter!=_vecData.end(); ++iter)
    {
        if (iter->IsInDB())
        {
            _vecDel.push_back(*iter);
        }

        _vecData.erase(iter);
    }
}
*/

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

