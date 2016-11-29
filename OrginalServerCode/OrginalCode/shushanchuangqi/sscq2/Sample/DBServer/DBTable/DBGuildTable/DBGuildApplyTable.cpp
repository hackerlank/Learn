#include "DBGuildApplyTable.h"

CDBGuildApplyTable::CDBGuildApplyTable():
    _qwGuildID(0), _qwRoleID(0),
    _wLevel(0), _dwBattlePoint(0)
{
}

CDBGuildApplyTable::~CDBGuildApplyTable()
{
}

void CDBGuildApplyTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SGuildApplyInfo sGuildApply;
    ar >> sGuildApply;

    if(!InitDataByGuildApply(sGuildApply))
        return ;
}

bool CDBGuildApplyTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SGuildApplyInfo sGuildApply;
    ar >> sGuildApply;

    DIFFONLY2(qwGuildID, sGuildApply.qwGuildID, _qwGuildID);
    DIFFONLY2(qwRoleID, sGuildApply.qwRoleID, _qwRoleID);
    DIFFONLY2(wLevel, sGuildApply.wLevel, _wLevel);
    DIFFONLY2(strName, sGuildApply.strName, _strName);
    DIFFONLY2(dwBattlePoint, sGuildApply.dwBattlePoint, _dwBattlePoint);

    return  !_setChanged.none();
}

bool CDBGuildApplyTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblguildapplydata(qwGuildID,qwRoleID,"\
        "wLevel,strName,dwBattlePoint) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwGuildID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_wLevel;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strName;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwBattlePoint;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBGuildApplyTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblguildapplydata SET";

    UPDATE_UBIGINT(qwGuildID, _qwGuildID);
    UPDATE_UBIGINT(qwRoleID, _qwRoleID);
    UPDATE_UTINYINT(wLevel, _wLevel);
    UPDATE_STRING_CHAR(strName, _strName);
    UPDATE_UINT(dwBattlePoint, _dwBattlePoint);

    ostr << " WHERE qwGuildID =" << _qwRoleID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBGuildApplyTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBGuildApplyTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwGuildID, _qwGuildID);
    GET_UBIGINT(qwRoleID, _qwRoleID);
    GET_UTINYINT(wLevel, _wLevel);
    GET_STRING_CHAR(strName, _strName);
    GET_UINT(dwBattlePoint, _dwBattlePoint);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  CDBGuildApplyTable::GetRoleID() const
{
    return _qwRoleID;
}

UINT64  CDBGuildApplyTable::GetGuildID() const
{
    return _qwGuildID;
}

UINT8  CDBGuildApplyTable::GetLevel() const
{
    return _wLevel;
}

const string& CDBGuildApplyTable::GetName() const
{
    return _strName;
}

UINT32 CDBGuildApplyTable::GetBattlePoint() const
{
    return _dwBattlePoint;
}

bool CDBGuildApplyTable::InitDataByGuildApply(const SGuildApplyInfo& rGuildInfo)
{
    _qwGuildID  = rGuildInfo.qwGuildID;
    _qwRoleID  = rGuildInfo.qwRoleID;
    _wLevel    = rGuildInfo.wLevel;
    _strName    = rGuildInfo.strName;
    _dwBattlePoint    = rGuildInfo.dwBattlePoint;
    return true;
}

CDBGuildApplyTableManager::CDBGuildApplyTableManager(UINT64 qwGuildID) : 
    CTableManagerBaseForGuild(eGDTApplyInfo,qwGuildID), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0)
{
}

CDBGuildApplyTableManager::~CDBGuildApplyTableManager()
{
}

void CDBGuildApplyTableManager::QueryDataByGuildID(UINT64 qwGuildID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblguildapplydata WHERE qwGuildID = " << qwGuildID << ";";

    CDBMgr::Instance().DoGuildSelectQuery(basesql.str(), NULL, [this, qwGuildID, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        UINT32 dwCount = dataRes.size();
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet << ", dwCount = " << dwCount << ".";
        if(byRet == 0)
        {
            for (UINT32 dwIndex = 0 ; dwIndex < dwCount; ++dwIndex)
            {
                mysqlpp::Row& rRow = dataRes[dwIndex];
                CDBGuildApplyTable cDBGuildApplyTable;
                cDBGuildApplyTable.InitDataByDBRow(rRow);
                _mapGuildData[cDBGuildApplyTable.GetGuildID()] = cDBGuildApplyTable;
            }
        }
        queryfun(byRet, dwCount);
    });
}

void CDBGuildApplyTableManager::Update(string& strData, EDataChange eUpdateType)
{
    CInArchive ar(strData);
    SGuildApplyInfo sGuildApply;
    ar >> sGuildApply;
    switch (eUpdateType)
    {
        case eOpAdd:
            break;
        case eOpDel:
            break;
        case eOpUpdate:
            break;
        default:
            break;
    }

    auto iter = _mapGuildData.find(sGuildApply.qwGuildID);
    if (iter == _mapGuildData.end())
    {
        CDBGuildApplyTable CDBGuildApplyTable;
        CDBGuildApplyTable.Update(strData, eUpdateType);
        _mapGuildData[sGuildApply.qwGuildID] = CDBGuildApplyTable;
    }
    else if(iter != _mapGuildData.end())
        iter->second.Update(strData, false);
}

void CDBGuildApplyTableManager::GetAllInfo(SDBGuildAllInfo & rData)
{
    for (auto it = _mapGuildData.begin(); it != _mapGuildData.end(); ++it)
    {
        SGuildApplyInfoPtr pGuildApply (new SGuildApplyInfo);
        pGuildApply->qwGuildID    = (it->second).GetGuildID();
        pGuildApply->qwRoleID    = (it->second).GetRoleID();
        pGuildApply->wLevel      = (it->second).GetLevel();
        pGuildApply->strName      = (it->second).GetName();
        pGuildApply->dwBattlePoint      = (it->second).GetBattlePoint();
        rData.vecApplyInfo.push_back(pGuildApply);
    }
}

void CDBGuildApplyTableManager::DumpToDBGuild(ManagerUpdateFun fun)
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
        sqlstr << "delete FROM tblguildapplydata WHERE "\
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

UINT32 CDBGuildApplyTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapGuildData.begin();iter != _mapGuildData.end();iter++)
    {
        if (iter->second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelGuildID.size();

}

void CDBGuildApplyTableManager::DelData(string& strData, UINT64 qwGuildID /* = 0 */)
{
    CInArchive ar(strData);
    SGuildApplyInfo sGuildApply;
    ar >> sGuildApply;

    auto iter = _mapGuildData.find(sGuildApply.qwGuildID);
    if (iter != _mapGuildData.end())
    {
        if (iter->second.IsInDB())
            _vecDelGuildID.push_back(sGuildApply.qwGuildID);
        _mapGuildData.erase(iter);
    }
}

