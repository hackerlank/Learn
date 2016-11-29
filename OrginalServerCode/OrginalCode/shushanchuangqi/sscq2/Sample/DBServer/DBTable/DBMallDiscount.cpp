#include "DBMallDiscount.h"

CDBMallDiscountManager g_CDBMallDiscountManager;

void CDBMallDiscount::InitDataByStr(string& strData)
{
    SDiscount oData;
    CInArchive ar(strData);
    ar>>oData;
    Copy(&oData);
    _byPos = oData.byPos;
}

bool CDBMallDiscount::UpdateDataByStr(string& strData)
{

    SDiscount oData;
    CInArchive ar(strData);
    ar>>oData;
    SMallDiscountEx newData;
    newData.Copy(&oData);
    
    DIFF(byPos);
    DIFF(qwMarkID);
    DIFF(strDisItem);
    DIFF(byLimitType);
    DIFF(dwLimitValue);
    DIFF(wLimitCount);
    DIFF(dwBeginTime);
    DIFF(dwEndTime);
     
    return !_setChanged.none();
}

bool CDBMallDiscount::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tbldiscount(byPos,qwMarkID,strDisItem,byLimitType,dwLimitValue,wLimitCount,dwBeginTime,dwEndTime";
    ostr << ") Values(";
    ostr<< (mysqlpp::sql_tinyint_unsigned)byPos;
    ostr<<"," << (mysqlpp::sql_bigint_unsigned)qwMarkID;
    ostr<<"," <<"'"<< (mysqlpp::sql_char)strDisItem<<"'";
    ostr<<"," << (mysqlpp::sql_tinyint_unsigned)UINT8(byLimitType);
    ostr<<"," << (mysqlpp::sql_int_unsigned)dwLimitValue;
    ostr<<"," << (mysqlpp::sql_smallint_unsigned)wLimitCount;
    ostr<<"," << (mysqlpp::sql_int_unsigned)dwBeginTime;
    ostr<<"," << (mysqlpp::sql_int_unsigned)dwEndTime;
    ostr << ");";
    sqlstr = ostr.str();
    return true;
}

bool CDBMallDiscount::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tbldiscount SET";
    UPDATE_UTINYINT_SAME(byPos);
    UPDATE_UBIGINT_SAME(qwMarkID);
    UPDATE_STRING_CHAR_SAME(strDisItem);
    UPDATE_UTINYINT_SAME(byLimitType);
    UPDATE_UINT_SAME(dwLimitValue);
    UPDATE_USMALLINT_SAME(wLimitCount);
    UPDATE_UINT_SAME(dwBeginTime);
    UPDATE_UINT_SAME(dwEndTime);
    ostr << " WHERE byPos = " << int(_byPos) << ";";
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBMallDiscount::ResetChange(void)
{
    _setChanged.reset();
}

void CDBMallDiscount::InitDataByDBRow(const mysqlpp::Row &rRow)
{   
    GET_UTINYINT_SAME(byPos);
    GET_UBIGINT_SAME(qwMarkID);
    GET_STRING_CHAR_SAME(strDisItem);
    GET_UTINYINT_SAME(byLimitType);
    GET_UINT_SAME(dwLimitValue);
    GET_USMALLINT_SAME(wLimitCount);
    GET_UINT_SAME(dwBeginTime);
    GET_UINT_SAME(dwEndTime);
  
    TableRowBase::InitDataByDBRow(rRow);
    _byPos = byPos;
}

void CDBMallDiscountManager::QueryData()
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tbldiscount;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tbldiscount is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0 && ncount >=1)
            {
                for(size_t i = 0; i < ncount; ++i)
                {
                    mysqlpp::Row& rRow = dataRes[i];
                    CDBMallDiscount oTable(0);
                    oTable.InitDataByDBRow(rRow);
                    oTable.StrToVec();
                    _mapMallDiscount[oTable.byPos]= oTable;
                }
            }
            if(byRet == 0)
               Config.SetPreLoad(eLoadMallDiscount);
            //queryfun(byRet, ncount);
            });
}

void CDBMallDiscountManager::Update(const TVecDiscount& vecDisItems)
{
    for (size_t i = 0; i < vecDisItems.size(); ++ i)
    {
        const SDiscount& oData = vecDisItems[i];
        SMallDiscountEx newData; 
        newData.Copy(&oData);

        string strData;
        COutArchive iar(strData);
        iar << oData;

        auto iter = _mapMallDiscount.find(newData.byPos);
        if (iter == _mapMallDiscount.end())
        {
            CDBMallDiscount oDiscountNew(newData.byPos);
            oDiscountNew.Update(strData, true);
            _mapMallDiscount[newData.byPos] = oDiscountNew;
        }
        else if(iter != _mapMallDiscount.end())
        {
            iter->second.Update(strData,false);
        }
    }
}

void CDBMallDiscountManager::DumpToDB()
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDeleteDiscount.begin();deliter != _vecDeleteDiscount.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tbldiscount WHERE byPos = "<<(*deliter) << ";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){                              
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
            {
                this->_nErrQuery++;
                LOG_INF<<"CDBMallDiscountManager::DumpToDB delete Error\n";
            }
            else
            {
               // LOG_INF<<"CDBMallDiscountManager::DumpToDB delete Error\n";
            }
            //if (this->_nNowQuery == 0)
            //{
            //    fun(this->_nMaxQuery,this->_nErrQuery);
            //}
        });
    }
    _vecDeleteDiscount.clear();
    for (auto iter =_mapMallDiscount.begin();iter !=_mapMallDiscount.end();iter++)
    {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDB(_byLine,[this](INT8 byRet) {
                this->_nNowQuery--;
                if (byRet)
                {
                    this->_nErrQuery++;
                    LOG_INF<<"CDBMallDiscountManager::DumpToDB update Error\n";
                }
                else
                {
                    //LOG_INF<<"CDBMallDiscountManager::DumpToDB update sucess\n";
                }
                //if (this->_nNowQuery == 0)
               // {
                 //   fun(_nMaxQuery,this->_nErrQuery);
               // }
            });
        }
    }
}

UINT32 CDBMallDiscountManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapMallDiscount.begin();iter != _mapMallDiscount.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        }
    }
    return dwOP +_vecDeleteDiscount.size();
}

void CDBMallDiscountManager::GetALLInfo(TVecDiscount& VecDiscount)
{
    for (auto iter = _mapMallDiscount.begin();iter != _mapMallDiscount.end();iter++)
    {
        SDiscount oDiscount;
        iter->second.CopyTo(oDiscount);
        VecDiscount.push_back(oDiscount);
    }
}

void CDBMallDiscountManager::DelAllData()
{
    for (auto iter = _mapMallDiscount.begin(); iter != _mapMallDiscount.end(); ++ iter)
    {
        _vecDeleteDiscount.push_back(iter->first);
    }
    _mapMallDiscount.clear();
}

