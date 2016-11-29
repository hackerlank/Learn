#include "DBGuildListInfoTable.h"

CDBGuildListInfoTable::CDBGuildListInfoTable():
    _qwGuildID(0), _byLevel(0), _wUserCount(0), _wMaxUserCount(0)
{
}

CDBGuildListInfoTable::~CDBGuildListInfoTable()
{
}

void CDBGuildListInfoTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SGuildListInfo sGuildListInfo;
    ar >> sGuildListInfo;

    if(!InitDataByGuildListInfo(sGuildListInfo))
        return ;
}

bool CDBGuildListInfoTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SGuildListInfo sGuildListInfo;
    ar >> sGuildListInfo;

    DIFFONLY2(qwGuildID, sGuildListInfo.qwGuildID, _qwGuildID);
    DIFFONLY2(strName, sGuildListInfo.strName, _strName);
    DIFFONLY2(strInfo, sGuildListInfo.strInfo, _strInfo);
    DIFFONLY2(qwOwnerID, sGuildListInfo.qwOwnerID, _qwOwnerID);
    DIFFONLY2(strOwnerName, sGuildListInfo.strOwnerName, _strOwnerName);
    DIFFONLY2(byLevel, sGuildListInfo.byLevel, _byLevel);
    DIFFONLY2(wUserCount, sGuildListInfo.wUserCount, _wUserCount);
    DIFFONLY2(wMaxUserCount, sGuildListInfo.wMaxUserCount, _wMaxUserCount);

    return  !_setChanged.none();
}

bool CDBGuildListInfoTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblguildlistinfo(qwGuildID,strName, strInfo, qwOwnerID, strOwnerName,"\
        "byLevel,wUserCount,wMaxUserCount) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwGuildID;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strName;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strInfo;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwOwnerID;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strOwnerName;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byLevel;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wUserCount;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wMaxUserCount;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBGuildListInfoTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblguildlistinfo SET";

    UPDATE_UBIGINT(qwGuildID, _qwGuildID);
    UPDATE_STRING_CHAR(strName, _strName);
    UPDATE_STRING_CHAR(strInfo, _strInfo);
    UPDATE_UBIGINT(qwOwnerID, _qwOwnerID);
    UPDATE_STRING_CHAR(strOwnerName, _strOwnerName);
    UPDATE_UTINYINT(byLevel, _byLevel);
    UPDATE_SMALLINT(wUserCount, _wUserCount);
    UPDATE_SMALLINT(wMaxUserCount, _wMaxUserCount);

    ostr << " WHERE qwGuildID =" << _qwGuildID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBGuildListInfoTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBGuildListInfoTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwGuildID, _qwGuildID);
    GET_STRING_CHAR(strName, _strName);
    GET_STRING_CHAR(strInfo, _strInfo);
    GET_UBIGINT(qwOwnerID, _qwOwnerID);
    GET_STRING_CHAR(strOwnerName, _strOwnerName);
    GET_UTINYINT(byLevel, _byLevel);
    GET_SMALLINT(wUserCount, _wUserCount);
    GET_SMALLINT(wMaxUserCount, _wMaxUserCount);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  CDBGuildListInfoTable::GetGuildID() const
{
    return _qwGuildID;
}

const string&  CDBGuildListInfoTable::GetName() const
{
    return _strName;
}

const string&   CDBGuildListInfoTable::GetInfo() const
{
    return _strInfo;
}

UINT64 CDBGuildListInfoTable::GetOwnerID() const
{
    return _qwOwnerID;
}

const string&  CDBGuildListInfoTable::GetOwnerName() const
{
    return _strOwnerName;
}

UINT8  CDBGuildListInfoTable::GetLevel() const
{
    return _byLevel;
}

UINT16 CDBGuildListInfoTable::GetUserCount() const
{
    return _wUserCount;
}

UINT16 CDBGuildListInfoTable::GetMaxUserCount() const
{
    return _wMaxUserCount;
}

bool CDBGuildListInfoTable::InitDataByGuildListInfo(const SGuildListInfo& rGuildInfo)
{
    _qwGuildID      = rGuildInfo.qwGuildID;
    _strName        = rGuildInfo.strName;
    _strInfo        = rGuildInfo.strInfo;
    _qwOwnerID      = rGuildInfo.qwOwnerID;
    _strOwnerName   = rGuildInfo.strOwnerName;
    _byLevel        = rGuildInfo.byLevel;
    _wUserCount     = rGuildInfo.wUserCount;
    _wMaxUserCount  = rGuildInfo.wMaxUserCount;
    return true;
}

CDBGuildListInfoTableManager::CDBGuildListInfoTableManager(UINT64 qwGuildID) : 
    CTableManagerBaseForGuildPub(eGPDTListInfo,qwGuildID), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0)
{
}

CDBGuildListInfoTableManager::~CDBGuildListInfoTableManager()
{
}

void CDBGuildListInfoTableManager::QueryDataByGuildID(UINT64 qwGuildID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblguildlistinfo WHERE qwGuildID = " << qwGuildID << ";";

    CDBMgr::Instance().DoGuildSelectQuery(basesql.str(), NULL, 
            [this, qwGuildID, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable
            {
                UINT32 dwCount = dataRes.size();
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet << ", dwCount = " << dwCount << ".";
                if(byRet == 0)
                {
                    for (UINT32 dwIndex = 0 ; dwIndex < dwCount; ++dwIndex)
                    {
                        mysqlpp::Row& rRow = dataRes[dwIndex];
                        CDBGuildListInfoTable cDBGuildListInfoTable;
                        cDBGuildListInfoTable.InitDataByDBRow(rRow);
                        _mapGuildData[cDBGuildListInfoTable.GetGuildID()] = cDBGuildListInfoTable;
                    }
                }
                queryfun(byRet, dwCount);
            });
}

void CDBGuildListInfoTableManager::Update(string& strData, EDataChange eUpdateType)
{
    CInArchive ar(strData);
    SGuildListInfo sGuildListInfo;
    ar >> sGuildListInfo;

    auto iter = _mapGuildData.find(sGuildListInfo.qwGuildID);
    if (iter == _mapGuildData.end())
    {
        CDBGuildListInfoTable CDBGuildListInfoTable;
        CDBGuildListInfoTable.Update(strData, eUpdateType == eOpAdd);
        _mapGuildData[sGuildListInfo.qwGuildID] = CDBGuildListInfoTable;
    }
    else
        iter->second.Update(strData, false);
}

void CDBGuildListInfoTableManager::GetAllInfo(SPubGuildAllInfo& rData)
{
    // FIXME:
    if (_mapGuildData.size() > 1)
        LOG_CRI << "CDBGuildListInfoTableManager _mapGuildData.size() = " << _mapGuildData.size() << ".";

    for (auto it = _mapGuildData.begin(); it != _mapGuildData.end(); ++it)
    {
        rData.sGuildListInfo.qwGuildID    = (it->second).GetGuildID();
        rData.sGuildListInfo.strName      = (it->second).GetName();
        rData.sGuildListInfo.strInfo      = (it->second).GetInfo();
        rData.sGuildListInfo.qwOwnerID    = (it->second).GetOwnerID();
        rData.sGuildListInfo.strOwnerName = (it->second).GetOwnerName();
        rData.sGuildListInfo.byLevel      = (it->second).GetLevel();
        rData.sGuildListInfo.wUserCount   = (it->second).GetUserCount();
        rData.sGuildListInfo.wMaxUserCount= (it->second).GetMaxUserCount();
        break;
    }

}

void CDBGuildListInfoTableManager::DumpToDBGuild(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto iter = _mapGuildData.begin();iter != _mapGuildData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDBGuild([fun,this](INT8 byRet) {
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

    for (auto it = _vecDelGuildID.begin();it != _vecDelGuildID.end(); ++ it)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblguildlistinfo WHERE "\
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

UINT32 CDBGuildListInfoTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapGuildData.begin();iter != _mapGuildData.end();iter++)
    {
        if (iter->second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelGuildID.size();

}

void CDBGuildListInfoTableManager::DelData(string& strData, UINT64 qwGuildID /* = 0 */)
{
    CInArchive ar(strData);
    SGuildListInfo sGuildListInfo;
    ar >> sGuildListInfo;

    if (!qwGuildID)
        qwGuildID = sGuildListInfo.qwGuildID;

    auto iter = _mapGuildData.find(qwGuildID);
    if (iter != _mapGuildData.end())
    {
        if (iter->second.IsInDB())
            _vecDelGuildID.push_back(qwGuildID);
        _mapGuildData.erase(iter);
        LOG_DBG << "Delete ListInfo(" << qwGuildID << ").";
    }
}

void CDBGuildListInfoTableManager::InitDataByDBRow(UINT64 qwGuildID, const mysqlpp::Row &rRow)
{
    _mapGuildData[qwGuildID].InitDataByDBRow(rRow);
}

