#include "DBGuildStatueTable.h"

CDBGuildStatueTable::CDBGuildStatueTable():
    _qwGuildID(0), _wLevel(0), _dwExp(0), _byWorshipCount(0),_dwTime(0)
{
}

CDBGuildStatueTable::~CDBGuildStatueTable()
{
}

void CDBGuildStatueTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SGuildStatueInfo sGuildStatue;
    ar >> sGuildStatue;

    if(!InitDataByGuildStatue(sGuildStatue))
        return ;
}

bool CDBGuildStatueTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SGuildStatueInfo sGuildStatue;
    ar >> sGuildStatue;

    DIFFONLY2(qwGuildID, sGuildStatue.qwGuildID, _qwGuildID);
    DIFFONLY2(wLevel, sGuildStatue.wLevel, _wLevel);
    DIFFONLY2(dwExp, sGuildStatue.dwExp, _dwExp);
    DIFFONLY2(byWorshipCount, sGuildStatue.byWorshipCount, _byWorshipCount);
    DIFFONLY2(dwTime, sGuildStatue.dwTime, _dwTime);

    return  !_setChanged.none();
}

bool CDBGuildStatueTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblguildstatue(qwGuildID,wLevel,dwExp,byWorshipCount,dwTime) "\
        "Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwGuildID;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wLevel;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwExp;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byWorshipCount;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwTime;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBGuildStatueTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblguildstatue SET";

    UPDATE_UBIGINT(qwGuildID, _qwGuildID);
    UPDATE_USMALLINT(wLevel, _wLevel);
    UPDATE_UINT(dwExp, _dwExp);
    UPDATE_UTINYINT(byWorshipCount, _byWorshipCount);
    UPDATE_UINT(dwTime, _dwTime);

    ostr << " WHERE qwGuildID =" << _qwGuildID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBGuildStatueTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBGuildStatueTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwGuildID, _qwGuildID);
    GET_USMALLINT(wLevel, _wLevel);
    GET_UINT(dwExp, _dwExp);
    GET_UTINYINT(byWorshipCount, _byWorshipCount);
    GET_UINT(dwTime, _dwTime);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  CDBGuildStatueTable::GetGuildID() const
{
    return _qwGuildID;
}

UINT16  CDBGuildStatueTable::GetLevel() const
{
    return _wLevel;
}

UINT32  CDBGuildStatueTable::GetExp() const
{
    return _dwExp;
}

UINT32  CDBGuildStatueTable::GetTime() const
{
    return _dwTime;
}

UINT8 CDBGuildStatueTable::GetWorshipCount() const
{
    return _byWorshipCount;
}

bool CDBGuildStatueTable::InitDataByGuildStatue(const SGuildStatueInfo& rGuildInfo)
{
    _qwGuildID      = rGuildInfo.qwGuildID;
    _wLevel         = rGuildInfo.wLevel;
    _dwExp          = rGuildInfo.dwExp;
    _byWorshipCount = rGuildInfo.byWorshipCount;
    _dwTime          = rGuildInfo.dwTime;
    return true;
}

CDBGuildStatueTableManager::CDBGuildStatueTableManager(UINT64 qwGuildID) : 
    CTableManagerBaseForGuild(eGDTStatue,qwGuildID), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0)
{
}

CDBGuildStatueTableManager::~CDBGuildStatueTableManager()
{
}

void CDBGuildStatueTableManager::QueryDataByGuildID(UINT64 qwGuildID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblguildstatue WHERE qwGuildID = " << qwGuildID << ";";

    CDBMgr::Instance().DoGuildSelectQuery(basesql.str(), NULL, [this, qwGuildID, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        UINT32 dwCount = dataRes.size();
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet << ", dwCount = " << dwCount << ".";
        if(byRet == 0)
        {
            for (UINT32 dwIndex = 0 ; dwIndex < dwCount; ++dwIndex)
            {
                mysqlpp::Row& rRow = dataRes[dwIndex];
                CDBGuildStatueTable cDBGuildStatueTable;
                cDBGuildStatueTable.InitDataByDBRow(rRow);
                _mapGuildData[cDBGuildStatueTable.GetGuildID()] = cDBGuildStatueTable;
            }
        }
        queryfun(byRet, dwCount);
    });
}

void CDBGuildStatueTableManager::Update(string& strData, EDataChange eUpdateType)
{
    CInArchive ar(strData);

    SGuildStatueInfo sStatueInfo;
    ar >> sStatueInfo;

    auto iter = _mapGuildData.find(sStatueInfo.qwGuildID);
    if (iter == _mapGuildData.end())
    {
        CDBGuildStatueTable CDBGuildStatueTable;
        CDBGuildStatueTable.Update(strData, eUpdateType);
        _mapGuildData[sStatueInfo.qwGuildID] = CDBGuildStatueTable;
    }
    else
        iter->second.Update(strData, false);
}

void CDBGuildStatueTableManager::GetAllInfo(SDBGuildAllInfo & rData)
{
    for (auto it = _mapGuildData.begin(); it != _mapGuildData.end(); ++it)
    {
        rData.sStatueInfo.qwGuildID    = (it->second).GetGuildID();
        rData.sStatueInfo.wLevel  = (it->second).GetLevel();
        rData.sStatueInfo.dwExp  = (it->second).GetExp();
        rData.sStatueInfo.byWorshipCount  = (it->second).GetWorshipCount();
        rData.sStatueInfo.dwTime  = (it->second).GetTime();
    }
}

void CDBGuildStatueTableManager::DumpToDBGuild(ManagerUpdateFun fun)
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
        sqlstr << "delete FROM tblguildstatue WHERE "\
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

UINT32 CDBGuildStatueTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapGuildData.begin();iter != _mapGuildData.end();iter++)
    {
        if (iter->second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelGuildID.size();

}

void CDBGuildStatueTableManager::DelData(string& strData, UINT64 qwGuildID)
{
    if (!qwGuildID)
    {
        CInArchive ar(strData);
        SGuildStatueInfo sStatueInfo;
        ar >> sStatueInfo;
        qwGuildID = sStatueInfo.qwGuildID;
    }

    auto iter = _mapGuildData.find(qwGuildID);
    if (iter != _mapGuildData.end())
    {
        if (iter->second.IsInDB())
            _vecDelGuildID.push_back(qwGuildID);
        _mapGuildData.erase(iter);
    }
}

