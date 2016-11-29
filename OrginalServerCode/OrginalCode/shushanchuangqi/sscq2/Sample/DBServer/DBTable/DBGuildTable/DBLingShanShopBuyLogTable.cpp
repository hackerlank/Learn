#include "DBLingShanShopBuyLogTable.h"
#include "Tokenizer.h"

CDBLingShanShopBuyLogTable::CDBLingShanShopBuyLogTable():
    _qwGuildID(0), _wMsgID(0), _dwTime(0)
{
}

CDBLingShanShopBuyLogTable::~CDBLingShanShopBuyLogTable()
{
}

void CDBLingShanShopBuyLogTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SGuildLogInfo sGuildLog;
    ar >> sGuildLog;

    if(!InitDataByLingShanShopBuyLog(sGuildLog))
        return ;
}

bool CDBLingShanShopBuyLogTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SGuildLogInfo sGuildLog;
    ar >> sGuildLog;

    DIFFONLY2(qwGuildID, sGuildLog.qwGuildID, _qwGuildID);
    DIFFONLY2(wMsgID, sGuildLog.wMsgID, _wMsgID);

    ostringstream strTmp;
    for (auto it = sGuildLog.vecParam.begin(); it != sGuildLog.vecParam.end(); ++it)
    {
        strTmp << *it << ",";
    }

    DIFFONLY2(vecParam, strTmp.str(), _strParam);

    strTmp.str("");
    for (auto it = sGuildLog.vecString.begin(); it != sGuildLog.vecString.end(); ++it)
    {
        strTmp <<  *it << ",";
    }

    DIFFONLY2(vecString, strTmp.str(), _strString);
    DIFFONLY2(dwTime, sGuildLog.dwTime, _dwTime);

    return  !_setChanged.none();
}

bool CDBLingShanShopBuyLogTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tbllingshanshopbuylog(qwGuildID, wMsgID, vecString, vecParam, dwTime) "\
        "Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwGuildID;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wMsgID;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strString;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strParam;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwTime;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBLingShanShopBuyLogTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    // XXX: 日志没有修改操作
    /*
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblguildlog SET";

    UPDATE_UBIGINT(qwInstID, _qwInstID);
    UPDATE_UBIGINT(qwGuildID, _qwGuildID);
    UPDATE_USMALLINT(wMsgID, _wMsgID);
    UPDATE_STRING_CHAR(vecParam, _strParam);
    UPDATE_STRING_CHAR(vecString, _strString);
    UPDATE_UINT(dwTime, _dwTime);

    ostr << " WHERE qwInstID =" << _qwInstID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    */
    return true;
}

void CDBLingShanShopBuyLogTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBLingShanShopBuyLogTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwGuildID, _qwGuildID);
    GET_USMALLINT(wMsgID, _wMsgID);
    GET_STRING_CHAR(vecString, _strString);
    GET_STRING_CHAR(vecParam, _strParam);
    GET_UINT(dwTime, _dwTime);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64 CDBLingShanShopBuyLogTable::GetGuildID() const
{
    return _qwGuildID;
}

UINT16 CDBLingShanShopBuyLogTable::GetMsgID() const
{
    return _wMsgID;
}

const string& CDBLingShanShopBuyLogTable::GetParam() const
{
    return _strParam;
}

const string&  CDBLingShanShopBuyLogTable::GetString() const
{
    return _strString;
}

UINT32  CDBLingShanShopBuyLogTable::GetTime() const
{
    return _dwTime;
}

bool CDBLingShanShopBuyLogTable::InitDataByLingShanShopBuyLog(const SGuildLogInfo& rGuildInfo)
{
    _qwGuildID  = rGuildInfo.qwGuildID;
    _wMsgID     = rGuildInfo.wMsgID;
    _dwTime     = rGuildInfo.dwTime;

    ostringstream strTmp;
    for (auto it=rGuildInfo.vecParam.begin(); it!=rGuildInfo.vecParam.end(); ++it)
    {
        strTmp << *it << ",";
    }

    _strParam = strTmp.str();

    strTmp.str("");
    for (auto it=rGuildInfo.vecString.begin(); it!=rGuildInfo.vecString.end(); ++it)
    {
        strTmp <<  *it << ",";
    }
    _strString = strTmp.str();
    return true;
}

CDBLingShanShopBuyLogTableManager::CDBLingShanShopBuyLogTableManager(UINT64 qwGuildID) : 
    CTableManagerBaseForGuild(eGDTLSSBLog, qwGuildID), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0)
{
}

CDBLingShanShopBuyLogTableManager::~CDBLingShanShopBuyLogTableManager()
{
}

void CDBLingShanShopBuyLogTableManager::QueryDataByGuildID(UINT64 qwGuildID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tbllingshanshopbuylog WHERE qwGuildID = " << qwGuildID << " order by `dwTime` desc limit 20;";

    CDBMgr::Instance().DoGuildSelectQuery(basesql.str(), NULL, [this, qwGuildID, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        UINT32 dwCount = dataRes.size();
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet << ", dwCount = " << dwCount << ".";
        if(byRet == 0)
        {
            for (UINT32 dwIndex = 0 ; dwIndex < dwCount; ++dwIndex)
            {
                mysqlpp::Row& rRow = dataRes[dwIndex];
                CDBLingShanShopBuyLogTable cDBLingShanShopBuyLogTable;
                cDBLingShanShopBuyLogTable.InitDataByDBRow(rRow);
                _vecLingShanShopBuyData.push_back(cDBLingShanShopBuyLogTable);
            }
        }
        queryfun(byRet, dwCount);
    });
}

void CDBLingShanShopBuyLogTableManager::Update(string& strData, EDataChange eUpdateType)
{
    CInArchive ar(strData);

    SGuildLogInfo sGuildLog;
    ar >> sGuildLog;

    CDBLingShanShopBuyLogTable CDBLingShanShopBuyLogTable;
    CDBLingShanShopBuyLogTable.Update(strData, eUpdateType);
    _vecLingShanShopBuyData.push_back(CDBLingShanShopBuyLogTable);
}

void CDBLingShanShopBuyLogTableManager::GetAllInfo(SDBGuildAllInfo & rData)
{
    for (auto it=_vecLingShanShopBuyData.begin(); it!=_vecLingShanShopBuyData.end(); ++it)
    {
        SGuildLogInfoPtr pInfo (new SGuildLogInfo);
        //pInfo->qwInstID  = (*it).GetInstID();
        pInfo->qwInstID  = 0;
        pInfo->qwGuildID = (*it).GetGuildID();
        pInfo->wMsgID    = (*it).GetMsgID();
        pInfo->dwTime    = (*it).GetTime();
        Tokenizer tk((*it).GetParam(), ",");
        for (size_t i = 0; i < tk.size(); ++i)
        {               
            if (i == tk.size() - 1 && tk[i].empty())
                break;
            pInfo->vecParam.push_back(::atol(tk[i].c_str()));
        }               
        Tokenizer tk2((*it).GetString(), ",");
        for (size_t i = 0; i < tk2.size(); ++i)
        {               
            if (i == tk2.size() - 1 && tk2[i].empty())
                break;
            pInfo->vecString.push_back(tk2[i].c_str());
        }               
        rData.vecLingShanShopBuyLogInfo.push_back(pInfo);
    }
}

void CDBLingShanShopBuyLogTableManager::DumpToDBGuild(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto it = _vecLingShanShopBuyData.begin();it != _vecLingShanShopBuyData.end();it++)
    {
        if ((*it).HasOP())
        {
            (*it).DumpToDBGuild([fun,this](INT8 byRet) {
                this->_nNowQuery--;
                if (byRet)
                    this->_nErrQuery++;
                if (this->_nNowQuery == 0)
                    fun(_nMaxQuery,this->_nErrQuery);
            });
        }
    }   

    for (auto it=_vecDelGuildID.begin(); it!= _vecDelGuildID.end(); ++it)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tbllingshanshopbuylog WHERE "\
            "qwGuildID = " << (*it) << ";";
        CDBMgr::Instance().DoGuildModifyQuery(sqlstr.str(),NULL, [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
                this->_nErrQuery++;
            if (this->_nNowQuery == 0)
                fun(this->_nMaxQuery,this->_nErrQuery);
        });
    }
    _vecDelGuildID.clear();
}

UINT32 CDBLingShanShopBuyLogTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto it = _vecLingShanShopBuyData.begin();it != _vecLingShanShopBuyData.end();it++)
    {
        if ((*it).HasOP())
            dwOP++;
    }
    return dwOP + _vecDelGuildID.size();

}

void CDBLingShanShopBuyLogTableManager::DelData(string& strData, UINT64 qwInstID /* = 0 */)
{
    CInArchive ar(strData);
    SGuildLogInfo sLogInfo;
    ar >> sLogInfo;

    auto iter = _vecLingShanShopBuyData.begin();
    if (iter != _vecLingShanShopBuyData.end())
    {
        if ((*iter).IsInDB())
            _vecDelGuildID.push_back(sLogInfo.qwGuildID);
        _vecLingShanShopBuyData.clear();
    }
}

