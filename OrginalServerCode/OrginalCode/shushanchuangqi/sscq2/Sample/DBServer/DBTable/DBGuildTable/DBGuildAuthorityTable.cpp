#include "DBGuildAuthorityTable.h"

CDBGuildAuthorityTable::CDBGuildAuthorityTable():
    _qwGuildID(0), _byMemberRank(0), _dwAuthority(0)
{
}

CDBGuildAuthorityTable::~CDBGuildAuthorityTable()
{
}

void CDBGuildAuthorityTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SGuildAuthorityInfo sGuildAuthority;
    ar >> sGuildAuthority;

    if(!InitDataByGuildAuthority(sGuildAuthority))
        return ;
}

bool CDBGuildAuthorityTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SGuildAuthorityInfo sGuildAuthority;
    ar >> sGuildAuthority;

    DIFFONLY2(qwGuildID, sGuildAuthority.qwGuildID, _qwGuildID);
    DIFFONLY2(byMemberRank, static_cast<UINT8>(sGuildAuthority.eMemberRank), _byMemberRank);
    DIFFONLY2(dwAuthority, sGuildAuthority.dwAuthority, _dwAuthority);

    return  !_setChanged.none();
}

bool CDBGuildAuthorityTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblguildauthority(qwGuildID,byMemberRank,dwAuthority) "\
        "Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwGuildID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byMemberRank;
    ostr << "," << (mysqlpp::sql_int_unsigned)_dwAuthority;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBGuildAuthorityTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblguildauthority SET";

    UPDATE_UBIGINT(qwGuildID, _qwGuildID);
    UPDATE_UTINYINT(byMemberRank, _byMemberRank);
    UPDATE_UINT(dwAuthority, _dwAuthority);

    ostr << " WHERE `qwGuildID` =" << _qwGuildID << " AND `byMemberRank` = " << static_cast<UINT32>(_byMemberRank) << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBGuildAuthorityTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBGuildAuthorityTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwGuildID, _qwGuildID);
    GET_UTINYINT(byMemberRank, _byMemberRank);
    GET_UINT(dwAuthority, _dwAuthority);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  CDBGuildAuthorityTable::GetGuildID() const
{
    return _qwGuildID;
}

UINT8   CDBGuildAuthorityTable::GetMemberRank() const
{
    return _byMemberRank;
}

UINT32  CDBGuildAuthorityTable::GetAuthority() const
{
    return _dwAuthority;
}

bool CDBGuildAuthorityTable::InitDataByGuildAuthority(const SGuildAuthorityInfo& rGuildInfo)
{
    _qwGuildID      = rGuildInfo.qwGuildID;
    _byMemberRank   = static_cast<UINT8>(rGuildInfo.eMemberRank);
    _dwAuthority    = rGuildInfo.dwAuthority;
    return true;
}

CDBGuildAuthorityTableManager::CDBGuildAuthorityTableManager(UINT64 qwGuildID) : 
    CTableManagerBaseForGuild(eGDTAuthority,qwGuildID), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0)
{
}

CDBGuildAuthorityTableManager::~CDBGuildAuthorityTableManager()
{
}

void CDBGuildAuthorityTableManager::QueryDataByGuildID(UINT64 qwGuildID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblguildauthority WHERE qwGuildID = " << qwGuildID << ";";

    CDBMgr::Instance().DoGuildSelectQuery(basesql.str(), NULL, [this, qwGuildID, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        UINT32 dwCount = dataRes.size();
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet << ", dwCount = " << dwCount << ".";
        if(byRet == 0)
        {
            for (UINT32 dwIndex = 0 ; dwIndex < dwCount; ++dwIndex)
            {
                mysqlpp::Row& rRow = dataRes[dwIndex];
                CDBGuildAuthorityTable cDBGuildAuthorityTable;
                cDBGuildAuthorityTable.InitDataByDBRow(rRow);
                SAuthorityKey sKey( cDBGuildAuthorityTable.GetGuildID(), cDBGuildAuthorityTable.GetMemberRank());
                _mapGuildData[sKey] = cDBGuildAuthorityTable;
            }
        }
        queryfun(byRet, dwCount);
    });
}

void CDBGuildAuthorityTableManager::Update(string& strData, EDataChange eUpdateType)
{
    CInArchive ar(strData);

    TVecGuildAuthorityInfo vecAuthority;
    ar >> vecAuthority;

    for (auto it = vecAuthority.begin(); it != vecAuthority.end(); ++it)
    {
        string strData2;
        COutArchive ar2(strData2);
        ar2 << (*(*it));
        SAuthorityKey sKey ((*it)->qwGuildID, static_cast<UINT8>((*it)->eMemberRank));
        auto iter = _mapGuildData.find(sKey);
        if (iter == _mapGuildData.end())
        {
            CDBGuildAuthorityTable CDBGuildAuthorityTable;
            CDBGuildAuthorityTable.Update(strData2, eUpdateType);
            _mapGuildData[sKey] = CDBGuildAuthorityTable;
        }
        else
            iter->second.Update(strData2, false);
    }
}

void CDBGuildAuthorityTableManager::GetAllInfo(SDBGuildAllInfo & rData)
{
    for (auto it = _mapGuildData.begin(); it != _mapGuildData.end(); ++it)
    {
        SGuildAuthorityInfoPtr pGuildAuthority (new SGuildAuthorityInfo);
        pGuildAuthority->qwGuildID    = (it->second).GetGuildID();
        pGuildAuthority->eMemberRank  = static_cast<EMemberRank>((it->second).GetMemberRank());
        pGuildAuthority->dwAuthority  = (it->second).GetAuthority();
        rData.vecAuthority.push_back(pGuildAuthority);
    }
}

void CDBGuildAuthorityTableManager::DumpToDBGuild(ManagerUpdateFun fun)
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

    for (auto it = _setDelGuildID.begin();it != _setDelGuildID.end(); ++ it)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblguildauthority WHERE "\
            "`qwGuildID` = " << (*it) << ";";
        CDBMgr::Instance().DoGuildModifyQuery(sqlstr.str(),NULL, [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
                this->_nErrQuery++;
            if (this->_nNowQuery == 0)
                fun(this->_nMaxQuery,this->_nErrQuery);
        });
    }
    _setDelGuildID.clear();
    /*
    for (auto it = _vecDelGuildID.begin();it != _vecDelGuildID.end(); ++ it)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblguildauthority WHERE "\
            "`qwGuildID` = " << (*it).qwGuildID << " AND `byMemberRank` = " << static_cast<UINT32>((*it).byMemberRank) << ";";
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
    */
}

UINT32 CDBGuildAuthorityTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapGuildData.begin();iter != _mapGuildData.end();iter++)
    {
        if (iter->second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelGuildID.size() + _setDelGuildID.size();

}

void CDBGuildAuthorityTableManager::DelData(string& strData, UINT64 qwGuildID)
{
    _setDelGuildID.insert(qwGuildID);
    for (auto it = _mapGuildData.begin(); it != _mapGuildData.end(); ++it)
    {
        _setDelGuildID.insert((it->first).qwGuildID);
    }
    _mapGuildData.clear();
    /*
    CInArchive ar(strData);
    TVecGuildAuthorityInfo vecAuthority;
    ar >> vecAuthority;

    for (auto it = vecAuthority.begin(); it != vecAuthority.end(); ++it)
    {
        SAuthorityKey sKey ((*it)->qwGuildID, static_cast<UINT8>((*it)->eMemberRank));
        auto iter = _mapGuildData.find(sKey);
        if (iter != _mapGuildData.end())
        {
            if (iter->second.IsInDB())
                _vecDelGuildID.push_back(sKey);
            _mapGuildData.erase(iter);
        }
    }
    */
}

