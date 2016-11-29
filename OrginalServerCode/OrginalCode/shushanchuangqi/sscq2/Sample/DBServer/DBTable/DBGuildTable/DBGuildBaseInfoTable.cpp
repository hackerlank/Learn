#include "DBGuildBaseInfoTable.h"

CDBGuildBaseInfoTable::CDBGuildBaseInfoTable():
    _qwGuildID(0), _qwOwnerID(0),
    _byLevel(0), _qwQQGroupID(0), _dwMoney(0),
    _wPlayerFighterID(0), _byQuality(0), _dwCount(0), _dwScore(0)
{
}

CDBGuildBaseInfoTable::~CDBGuildBaseInfoTable()
{
} 
void CDBGuildBaseInfoTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SGuildBaseInfo sGuildBaseInfo;
    ar >> sGuildBaseInfo;

    if(!InitDataByGuildBaseInfo(sGuildBaseInfo))
        return ;
}

bool CDBGuildBaseInfoTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SGuildBaseInfo sGuildBaseInfo;
    ar >> sGuildBaseInfo;

    DIFFONLY2(qwGuildID, sGuildBaseInfo.qwGuildID, _qwGuildID);
    DIFFONLY2(qwOwnerID, sGuildBaseInfo.qwOwnerID, _qwOwnerID);
    //DIFFONLY2(byLevel, sGuildBaseInfo.byLevel, _byLevel);
    DIFFONLY2(strName, sGuildBaseInfo.strName, _strName);
    DIFFONLY2(strInfo, sGuildBaseInfo.strInfo, _strInfo);
    DIFFONLY2(qwQQGroupID, sGuildBaseInfo.qwQQGroupID, _qwQQGroupID);
    DIFFONLY2(dwMoney, sGuildBaseInfo.dwMoney, _dwMoney);
    DIFFONLY2(wPlayerFighterID, sGuildBaseInfo.wPlayerFighterID, _wPlayerFighterID);
    DIFFONLY2(byQuality, sGuildBaseInfo.byQuality, _byQuality);
    DIFFONLY2(dwCount, sGuildBaseInfo.dwCount, _dwCount);
    DIFFONLY2(dwScore,  sGuildBaseInfo.dwScore, _dwScore);
    DIFFONLY2(strLingShan, sGuildBaseInfo.strLingShan, _strLingShan);

    return  !_setChanged.none();
}

bool CDBGuildBaseInfoTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblguilddata(qwGuildID,qwOwnerID,"\
        "byLevel,strName,strInfo, qwQQGroupID, dwMoney, wPlayerFighterID, byQuality, dwCount, dwScore, strLingShan) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwGuildID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwOwnerID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byLevel;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strName;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strInfo;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwQQGroupID;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwMoney;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wPlayerFighterID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byQuality;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwCount;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwScore;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strLingShan;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBGuildBaseInfoTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblguilddata SET";

    UPDATE_UBIGINT(qwGuildID, _qwGuildID);
    UPDATE_UBIGINT(qwOwnerID, _qwOwnerID);
    //UPDATE_UTINYINT(byLevel, _byLevel);
    UPDATE_STRING_CHAR(strName, _strName);
    UPDATE_STRING_CHAR(strInfo, _strInfo);
    UPDATE_UBIGINT(qwQQGroupID, _qwQQGroupID);
    UPDATE_UINT(dwMoney, _dwMoney);
    UPDATE_USMALLINT(wPlayerFighterID, _wPlayerFighterID);
    UPDATE_UTINYINT(byQuality, _byQuality);
    UPDATE_UINT(dwCount, _dwCount);
    UPDATE_UINT(dwScore, _dwScore);
    UPDATE_STRING_CHAR(strLingShan, _strLingShan);

    ostr << " WHERE qwGuildID =" << _qwGuildID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBGuildBaseInfoTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBGuildBaseInfoTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwGuildID, _qwGuildID);
    GET_UBIGINT(qwOwnerID, _qwOwnerID);
    //GET_UTINYINT(byLevel, _byLevel);
    GET_STRING_CHAR(strName, _strName);
    GET_STRING_CHAR(strInfo, _strInfo);
    GET_UBIGINT(qwQQGroupID, _qwQQGroupID);
    GET_UINT(dwMoney, _dwMoney);
    GET_USMALLINT(wPlayerFighterID, _wPlayerFighterID);
    GET_UTINYINT(byQuality, _byQuality);
    GET_UINT(dwCount, _dwCount);
    GET_UINT(dwScore, _dwScore);
    GET_STRING_CHAR(strLingShan, _strLingShan);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  CDBGuildBaseInfoTable::GetOwnerID() const
{
    return _qwOwnerID;
}

UINT64  CDBGuildBaseInfoTable::GetGuildID() const
{
    return _qwGuildID;
}

UINT8  CDBGuildBaseInfoTable::GetLevel() const
{
    return _byLevel;
}

const string& CDBGuildBaseInfoTable::GetName() const
{
    return _strName;
}

const string& CDBGuildBaseInfoTable::GetInfo() const
{
    return _strInfo;
}

UINT64 CDBGuildBaseInfoTable::GetQQGroupID() const
{
    return _qwQQGroupID;
}

UINT32 CDBGuildBaseInfoTable::GetMoney() const
{
    return _dwMoney;
}

UINT32 CDBGuildBaseInfoTable::GetCount() const
{
    return _dwCount;
}

UINT16 CDBGuildBaseInfoTable::GetPlayerFighterID() const
{
    return _wPlayerFighterID;
}

UINT8 CDBGuildBaseInfoTable::GetQuality() const
{
    return _byQuality;
}

UINT32 CDBGuildBaseInfoTable::GetScore() const
{
    return _dwScore;
}

const string& CDBGuildBaseInfoTable::GetLingShan() const
{
    return _strLingShan;
}

bool CDBGuildBaseInfoTable::InitDataByGuildBaseInfo(const SGuildBaseInfo& rGuildInfo)
{
    _qwGuildID        = rGuildInfo.qwGuildID;
    _qwOwnerID        = rGuildInfo.qwOwnerID;
    //_byLevel          = rGuildInfo.byLevel;
    _strName          = rGuildInfo.strName;
    _strInfo          = rGuildInfo.strInfo;
    _qwQQGroupID      = rGuildInfo.qwQQGroupID;
    _dwMoney          = rGuildInfo.dwMoney;
    _wPlayerFighterID = rGuildInfo.wPlayerFighterID;
    _byQuality        = rGuildInfo.byQuality;
    _dwCount          = rGuildInfo.dwCount;
    _dwScore          = rGuildInfo.dwScore;
    _strLingShan      = rGuildInfo.strLingShan;

    return true;
}

CDBGuildBaseInfoTableManager::CDBGuildBaseInfoTableManager(UINT64 qwGuildID) : 
    CTableManagerBaseForGuild(eGDTBaseInfo,qwGuildID), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) 
{
}

CDBGuildBaseInfoTableManager::~CDBGuildBaseInfoTableManager()
{
}

void CDBGuildBaseInfoTableManager::QueryDataByGuildID(UINT64 qwGuildID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblguilddata WHERE qwGuildID = " << qwGuildID << ";";

    CDBMgr::Instance().DoGuildSelectQuery(basesql.str(), NULL, [this, qwGuildID, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        UINT32 dwCount = dataRes.size();
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet << ", dwCount = " << dwCount << ".";
        if(byRet == 0)
        {
            for (UINT32 dwIndex = 0 ; dwIndex < dwCount; ++dwIndex)
            {
                mysqlpp::Row& rRow = dataRes[dwIndex];
                CDBGuildBaseInfoTable cDBGuildBaseInfoTable;
                cDBGuildBaseInfoTable.InitDataByDBRow(rRow);
                _mapGuildData[cDBGuildBaseInfoTable.GetGuildID()] = cDBGuildBaseInfoTable;
            }
        }
        queryfun(byRet, dwCount);
    });
}

void CDBGuildBaseInfoTableManager::Update(string& strData, EDataChange eUpdateType)
{
    CInArchive ar(strData);
    SGuildBaseInfo sGuildBaseInfo;
    ar >> sGuildBaseInfo;

    auto iter = _mapGuildData.find(sGuildBaseInfo.qwGuildID);
    if (iter == _mapGuildData.end())
    {
        CDBGuildBaseInfoTable CDBGuildBaseInfoTable;
        CDBGuildBaseInfoTable.Update(strData, eUpdateType);
        _mapGuildData[sGuildBaseInfo.qwGuildID] = CDBGuildBaseInfoTable;
    }
    else
        iter->second.Update(strData, false);
}

void CDBGuildBaseInfoTableManager::GetAllInfo(SDBGuildAllInfo & rData)
{
    for (auto it = _mapGuildData.begin(); it != _mapGuildData.end(); ++it)
    {
        SGuildBaseInfo& rGuildBaseInfo = rData.sBaseInfo;
        rGuildBaseInfo.qwGuildID        = (it->second).GetGuildID();
        rGuildBaseInfo.qwOwnerID        = (it->second).GetOwnerID();
        //rGuildBaseInfo.byLevel          = (it->second).GetLevel();
        rGuildBaseInfo.strName          = (it->second).GetName();
        rGuildBaseInfo.strInfo          = (it->second).GetInfo();
        rGuildBaseInfo.qwQQGroupID      = (it->second).GetQQGroupID();
        rGuildBaseInfo.dwMoney          = (it->second).GetMoney();
        rGuildBaseInfo.wPlayerFighterID = (it->second).GetPlayerFighterID();
        rGuildBaseInfo.byQuality        = (it->second).GetQuality();
        rGuildBaseInfo.dwCount          = (it->second).GetCount();
        rGuildBaseInfo.dwScore          = (it->second).GetScore();
        rGuildBaseInfo.strLingShan      = (it->second).GetLingShan();
    }
}

void CDBGuildBaseInfoTableManager::DumpToDBGuild(ManagerUpdateFun fun)
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
                    this->_nErrQuery++;
                if (this->_nNowQuery == 0)
                    fun(_nMaxQuery,this->_nErrQuery);
            });
        }
    }   

    for (auto it = _vecDelGuildID.begin();it != _vecDelGuildID.end(); ++ it)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblguilddata WHERE "\
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

UINT32 CDBGuildBaseInfoTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapGuildData.begin();iter != _mapGuildData.end();iter++)
    {
        if (iter->second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelGuildID.size();

}

void CDBGuildBaseInfoTableManager::DelData(string& strData, UINT64 qwGuildID /* = 0 */)
{
    CInArchive ar(strData);
    SGuildBaseInfo sGuildBaseInfo;
    ar >> sGuildBaseInfo;

    if (!qwGuildID)
        qwGuildID = sGuildBaseInfo.qwGuildID;

    auto iter = _mapGuildData.find(qwGuildID);
    if (iter != _mapGuildData.end())
    {
        if (iter->second.IsInDB())
            _vecDelGuildID.push_back(qwGuildID);
        _mapGuildData.erase(iter);
    }
}

