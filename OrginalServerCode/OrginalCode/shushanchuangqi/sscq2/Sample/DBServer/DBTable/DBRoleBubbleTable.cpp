#include "DBRoleBubbleTable.h"

#include "Tokenizer.h"

CDBRoleBubbleTable::CDBRoleBubbleTable():
    _qwRoleID(0), _qwTransID(0), _wMsgID(0), _dwTime(0)
{
}

CDBRoleBubbleTable::~CDBRoleBubbleTable()
{
}

void CDBRoleBubbleTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SDBBubbleInfo sBubble;
    ar >> sBubble;

    if(!InitDataByBubble(sBubble))
        return ;
}

bool CDBRoleBubbleTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SDBBubbleInfo sBubble;
    ar >> sBubble;

    DIFFONLY2(qwRoleID, sBubble.qwRoleID, _qwRoleID);
    DIFFONLY2(qwTransID, sBubble.qwTransID, _qwTransID);
    DIFFONLY2(wMsgID, sBubble.wMsgID, _wMsgID);

    ostringstream strTmp;
    for (auto it = sBubble.vecParam.begin(); it != sBubble.vecParam.end(); ++it)
    {
        strTmp << *it << ",";
    }
    DIFFONLY2(vecParam, strTmp.str(), _strParam);

    strTmp.str("");
    for (auto it = sBubble.vecString.begin(); it != sBubble.vecString.end(); ++it)
    {
        strTmp <<  *it << ",";
    }
    DIFFONLY2(vecString, strTmp.str(), _strString);

    DIFFONLY2(dwTime, sBubble.dwTime, _dwTime);

    return  !_setChanged.none();
}

bool CDBRoleBubbleTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolebubble(qwRoleID, qwTransID, wMsgID, vecString, vecParam, dwTime) "\
        "Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwTransID;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wMsgID;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strString;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strParam;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwTime;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleBubbleTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolebubble SET";

    UPDATE_UBIGINT(qwRoleID, _qwRoleID);
    UPDATE_UBIGINT(qwTransID, _qwTransID);
    UPDATE_USMALLINT(wMsgID, _wMsgID);
    UPDATE_STRING_CHAR(vecParam, _strParam);
    UPDATE_STRING_CHAR(vecString, _strString);
    UPDATE_UINT(dwTime, _dwTime);

    ostr << " WHERE qwRoleID = " << _qwRoleID << " and qwTransID =" << _qwTransID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBRoleBubbleTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleBubbleTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwRoleID, _qwRoleID);
    GET_UBIGINT(qwTransID, _qwTransID);
    GET_USMALLINT(wMsgID, _wMsgID);
    GET_STRING_CHAR(vecString, _strString);
    GET_STRING_CHAR(vecParam, _strParam);
    GET_UINT(dwTime, _dwTime);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  CDBRoleBubbleTable::GetRoleID() const
{
    return _qwRoleID;
}

UINT64  CDBRoleBubbleTable::GetTransID() const
{
    return _qwTransID;
}

UINT16 CDBRoleBubbleTable::GetMsgID() const
{
    return _wMsgID;
}

const string&  CDBRoleBubbleTable::GetParam() const
{
    return _strParam;
}

const string&  CDBRoleBubbleTable::GetString() const
{
    return _strString;
}

UINT32  CDBRoleBubbleTable::GetTime() const
{
    return _dwTime;
}

bool CDBRoleBubbleTable::InitDataByBubble(const SDBBubbleInfo& rBubbleInfo)
{
    _qwRoleID   = rBubbleInfo.qwRoleID;
    _qwTransID  = rBubbleInfo.qwTransID;
    _wMsgID     = rBubbleInfo.wMsgID;
    _dwTime     = rBubbleInfo.dwTime;

    ostringstream strTmp;
    for (auto it = rBubbleInfo.vecParam.begin(); it != rBubbleInfo.vecParam.end(); ++it)
    {
        strTmp << *it << ",";
    }

    _strParam = strTmp.str();

    strTmp.str("");
    for (auto it = rBubbleInfo.vecString.begin(); it != rBubbleInfo.vecString.end(); ++it)
    {
        strTmp <<  *it << ",";
    }
    _strString = strTmp.str();
    return true;
}

CDBRoleBubbleTableManager::CDBRoleBubbleTableManager(UINT64 qwRoleID, UINT8 byLine) : 
    TableManagerBaseForRole(eTypeBubbleInfo, qwRoleID, byLine), 
    _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0)
{
}

CDBRoleBubbleTableManager::~CDBRoleBubbleTableManager()
{
}

void CDBRoleBubbleTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolebubble WHERE qwRoleID = " << qwRoleID << ";";

    CDBMgr::Instance().DoSelectQuery(basesql.str(), NULL, [this, qwRoleID, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        UINT32 dwCount = dataRes.size();
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet << ", dwCount = " << dwCount << ".";
        if(byRet == 0)
        {
            for (UINT32 dwIndex = 0 ; dwIndex < dwCount; ++dwIndex)
            {
                mysqlpp::Row& rRow = dataRes[dwIndex];
                CDBRoleBubbleTable cDBRoleBubbleTable;
                cDBRoleBubbleTable.InitDataByDBRow(rRow);
                _mapBubbleData[cDBRoleBubbleTable.GetTransID()] = cDBRoleBubbleTable;
            }
        }
        queryfun(byRet, dwCount);
    });
}

void CDBRoleBubbleTableManager::Update(string& strData, bool bIsAdd)
{
    CInArchive ar(strData);

    SDBBubbleInfo sBubble;
    ar >> sBubble;

    auto iter = _mapBubbleData.find(sBubble.qwTransID);
    if (iter == _mapBubbleData.end())
    {
        CDBRoleBubbleTable CDBRoleBubbleTable;
        CDBRoleBubbleTable.Update(strData, true);
        _mapBubbleData[sBubble.qwTransID] = CDBRoleBubbleTable;
    }
    else
        iter->second.Update(strData, false);
}

void CDBRoleBubbleTableManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto it = _mapBubbleData.begin(); it != _mapBubbleData.end(); ++it)
    {
        SDBBubbleInfo sInfo;
        sInfo.qwRoleID  = (it->second).GetRoleID();
        sInfo.qwTransID = (it->second).GetTransID();
        sInfo.wMsgID    = (it->second).GetMsgID();
        sInfo.dwTime    = (it->second).GetTime();
        Tokenizer tk((it->second).GetParam(), ",");
        for (size_t i = 0; i < tk.size(); ++i)
        {               
            if (i == tk.size() - 1 && tk[i].empty())
                break;
            sInfo.vecParam.push_back(::atol(tk[i].c_str()));
        }               
        Tokenizer tk2((it->second).GetString(), ",");
        for (size_t i = 0; i < tk2.size(); ++i)
        {               
            if (i == tk2.size() - 1 && tk2[i].empty())
                break;
            sInfo.vecString.push_back(tk2[i].c_str());
        }               
        rData.vecBubbleInfo.push_back(sInfo);
    }
}

void CDBRoleBubbleTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto it = _vecDelTransID.begin();it != _vecDelTransID.end(); ++ it)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblrolebubble WHERE  qwRoleID = " << _qwRoleID <<" and qwTransID = " << *it << ";";
        CDBMgr::Instance().DoModifyQuery(sqlstr.str(),NULL, [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
                this->_nErrQuery++;
            if (this->_nNowQuery == 0)
                fun(this->_nMaxQuery,this->_nErrQuery);
        });
    }
    _vecDelTransID.clear();

    for (auto iter = _mapBubbleData.begin();iter != _mapBubbleData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDB(_byLine, [fun,this](INT8 byRet) {
                this->_nNowQuery--;
                if (byRet)
                    this->_nErrQuery++;
                if (this->_nNowQuery == 0)
                    fun(_nMaxQuery,this->_nErrQuery);
            });
        }
    }   

}

UINT32 CDBRoleBubbleTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapBubbleData.begin();iter != _mapBubbleData.end();iter++)
    {
        if (iter->second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelTransID.size();

}

void CDBRoleBubbleTableManager::DelData(string& strData)
{
    CInArchive ar(strData);
    SDBBubbleInfo sBubbleInfo;
    ar >> sBubbleInfo;

    auto iter = _mapBubbleData.find(sBubbleInfo.qwTransID);
    if (iter != _mapBubbleData.end())
    {
        if (iter->second.IsInDB())
            _vecDelTransID.push_back(sBubbleInfo.qwTransID);
        _mapBubbleData.erase(iter);
    }
}

