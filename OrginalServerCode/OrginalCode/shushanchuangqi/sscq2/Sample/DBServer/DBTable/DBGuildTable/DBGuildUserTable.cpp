#include "DBGuildUserTable.h"
#include "DBRoleNameManager.h"
#include "Tokenizer.h"

CDBGuildUserTable::CDBGuildUserTable():
    _qwGuildID(0), _qwRoleID(0),
    _wLevel(0), _dwContribution(0), _dwLastOnline(0), _byMemberRank(0), _byMemberLastRank(0),
    _dwBattleScore(0), _byVIPLevel(0)
{
}

CDBGuildUserTable::~CDBGuildUserTable()
{
}

void CDBGuildUserTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SDBGuildUserInfo sGuildUser;
    ar >> sGuildUser;

    if(!InitDataByGuildUser(sGuildUser))
        return ;
}

bool CDBGuildUserTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SDBGuildUserInfo sGuildUser;
    ar >> sGuildUser;

    DIFFONLY2(qwGuildID, sGuildUser.sBaseInfo.qwGuildID, _qwGuildID);
    DIFFONLY2(qwRoleID, sGuildUser.sBaseInfo.qwRoleID, _qwRoleID);
    DIFFONLY2(wLevel, sGuildUser.sBaseInfo.wLevel, _wLevel);
    DIFFONLY2(dwContribution, sGuildUser.sBaseInfo.dwContribution, _dwContribution);
    DIFFONLY2(dwLastOnline, sGuildUser.sBaseInfo.dwLastOnlineTime, _dwLastOnline);
    DIFFONLY2(byMemberRank, static_cast<UINT8>(sGuildUser.sBaseInfo.eMemberRank), _byMemberRank);
    DIFFONLY2(byMemberLastRank, static_cast<UINT8>(sGuildUser.sBaseInfo.eMemberLastRank), _byMemberLastRank);
    DIFFONLY2(dwBattleScore, sGuildUser.dwBattleScore, _dwBattleScore);
    DIFFONLY2(byVIPLevel, sGuildUser.sBaseInfo.byVIPLevel, _byVIPLevel);
    DIFFONLY2(wPlayerFighterID, sGuildUser.wPlayerFighterID, _wPlayerFighterID);
    DIFFONLY2(byQuality, sGuildUser.byQuality, _byQuality);

    ostringstream strTmp;
    for (auto it = sGuildUser.vecTechInfo.begin(); it != sGuildUser.vecTechInfo.end(); ++it)
    {
        strTmp << static_cast<UINT32>((*it)->eType) << ","  << (*it)->wLevel << "|";
    }

    DIFFONLY2(strTech, strTmp.str(), _strTech);

    return  !_setChanged.none();
}

bool CDBGuildUserTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleguilddata(qwGuildID,qwRoleID,"\
        "wLevel,dwContribution, dwLastOnline, byMemberRank, byMemberLastRank, strTech, dwBattleScore, byVIPLevel, wPlayerFighterID, byQuality) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwGuildID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wLevel;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_dwContribution;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_dwLastOnline;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byMemberRank;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byMemberLastRank;
    ostr << "," << mysqlpp::quote << (mysqlpp::sql_char)_strTech;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)_dwBattleScore;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byVIPLevel;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wPlayerFighterID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byQuality;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBGuildUserTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleguilddata SET";

    UPDATE_UBIGINT(qwGuildID, _qwGuildID);
    UPDATE_UBIGINT(qwRoleID, _qwRoleID);
    UPDATE_USMALLINT(wLevel, _wLevel);
    UPDATE_UBIGINT(dwContribution, _dwContribution);
    UPDATE_UBIGINT(dwLastOnline, _dwLastOnline);
    UPDATE_TINYINT(byMemberRank, _byMemberRank);
    UPDATE_TINYINT(byMemberLastRank, _byMemberLastRank);
    UPDATE_STRING_CHAR(strTech, _strTech);
    UPDATE_UBIGINT(dwBattleScore, _dwBattleScore);
    UPDATE_UTINYINT(byVIPLevel, _byVIPLevel);
    UPDATE_USMALLINT(wPlayerFighterID, _wPlayerFighterID);
    UPDATE_UTINYINT(byQuality, _byQuality);

    ostr << " WHERE qwRoleID =" << _qwRoleID << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBGuildUserTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBGuildUserTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwGuildID, _qwGuildID);
    GET_UBIGINT(qwRoleID, _qwRoleID);
    GET_USMALLINT(wLevel, _wLevel);
    GET_UBIGINT(dwContribution, _dwContribution);
    GET_UBIGINT(dwLastOnline, _dwLastOnline);
    GET_UTINYINT(byMemberRank, _byMemberRank);
    GET_UTINYINT(byMemberLastRank, _byMemberLastRank);
    GET_STRING_CHAR(strTech, _strTech);
    GET_UBIGINT(dwBattleScore, _dwBattleScore);

    _strName = RoleNameManager::Instance().GetPlayerName(_qwRoleID);
    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  CDBGuildUserTable::GetRoleID() const
{
    return _qwRoleID;
}

UINT64  CDBGuildUserTable::GetGuildID() const
{
    return _qwGuildID;
}

UINT16  CDBGuildUserTable::GetLevel() const
{
    return _wLevel;
}

UINT32 CDBGuildUserTable::GetContribution() const
{
    return _dwContribution;
}

UINT32 CDBGuildUserTable::GetLastOnline() const
{
    return _dwLastOnline;
}

UINT8 CDBGuildUserTable::GetMemberRank() const
{
    return _byMemberRank;
}

UINT8 CDBGuildUserTable::GetMemberLastRank() const
{
    return _byMemberLastRank;
}

const string& CDBGuildUserTable::GetName() const
{
    return _strName;
}

const string& CDBGuildUserTable::GetTech() const
{
    return _strTech;
}

UINT32 CDBGuildUserTable::GetBattleScore() const
{
    return _dwBattleScore;
}

UINT8 CDBGuildUserTable::GetVIPLevel() const
{
    return _byVIPLevel;
}

UINT16 CDBGuildUserTable::GetPlayerFighterID() const
{
    return _wPlayerFighterID;
}

UINT8 CDBGuildUserTable::GetQuality() const
{
    return _byQuality;
}

bool CDBGuildUserTable::ToDBGuildUserInfo(SDBGuildUserInfo& rUserInfo) const
{
    rUserInfo.sBaseInfo.qwGuildID        = GetGuildID();
    rUserInfo.sBaseInfo.qwRoleID         = GetRoleID();
    rUserInfo.sBaseInfo.wLevel           = GetLevel();
    rUserInfo.sBaseInfo.dwContribution   = GetContribution();
    rUserInfo.sBaseInfo.dwLastOnlineTime = GetLastOnline();
    rUserInfo.sBaseInfo.strName          = GetName();
    rUserInfo.sBaseInfo.eMemberRank      = static_cast<EMemberRank>(GetMemberRank());
    rUserInfo.sBaseInfo.eMemberLastRank  = static_cast<EMemberRank>(GetMemberLastRank());
    rUserInfo.dwBattleScore              = GetBattleScore();
    rUserInfo.sBaseInfo.byVIPLevel       = GetVIPLevel();
    rUserInfo.wPlayerFighterID           = GetPlayerFighterID();
    rUserInfo.byQuality                  = GetQuality();
    Tokenizer tk(GetTech(), "|");
    for (size_t i = 0; i < tk.size(); ++i)
    {               
        Tokenizer tk2(tk[i], ",");
        if (tk2.size() <= 1)
            continue;

        SGuildTechInfoPtr pTechInfo(new SGuildTechInfo);
        pTechInfo->eType = static_cast<ETechType>(::atoi(tk2[0].c_str()));
        pTechInfo->wLevel = ::atoi(tk2[1].c_str());
        rUserInfo.vecTechInfo.push_back(pTechInfo);
    }               
    return true;
}

bool CDBGuildUserTable::InitDataByGuildUser(const SDBGuildUserInfo& rGuildInfo)
{
    _qwGuildID          = rGuildInfo.sBaseInfo.qwGuildID;
    _qwRoleID           = rGuildInfo.sBaseInfo.qwRoleID;
    _wLevel             = rGuildInfo.sBaseInfo.wLevel;
    _dwContribution     = rGuildInfo.sBaseInfo.dwContribution;
    _dwLastOnline       = rGuildInfo.sBaseInfo.dwLastOnlineTime;
    _strName            = RoleNameManager::Instance().GetPlayerName(_qwRoleID);
    _byMemberRank       = static_cast<UINT8>(rGuildInfo.sBaseInfo.eMemberRank);
    _byMemberLastRank   = static_cast<UINT8>(rGuildInfo.sBaseInfo.eMemberLastRank);
    _dwBattleScore      = rGuildInfo.dwBattleScore;
    _byVIPLevel         = rGuildInfo.sBaseInfo.byVIPLevel;
    _wPlayerFighterID = rGuildInfo.wPlayerFighterID;
    _byQuality        = rGuildInfo.byQuality;

    ostringstream strTmp;
    for (auto it = rGuildInfo.vecTechInfo.begin(); it != rGuildInfo.vecTechInfo.end(); ++it)
    {
        strTmp << static_cast<UINT32>((*it)->eType) << ","  << (*it)->wLevel << "|";
    }

    _strTech = strTmp.str();
    return true;
}

CDBGuildUserTableManager::CDBGuildUserTableManager(UINT64 qwGuildID) : 
    CTableManagerBaseForGuild(eGDTUser,qwGuildID), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0)
{
}

CDBGuildUserTableManager::~CDBGuildUserTableManager()
{
}

void CDBGuildUserTableManager::QueryDataByGuildID(UINT64 qwGuildID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleguilddata WHERE qwGuildID = " << qwGuildID << ";";

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
                        CDBGuildUserTable cDBGuildUserTable;
                        cDBGuildUserTable.InitDataByDBRow(rRow);
                        _mapGuildData[cDBGuildUserTable.GetRoleID()] = cDBGuildUserTable;
                    }
                }
                queryfun(byRet, dwCount);
            });
}

void CDBGuildUserTableManager::QueryDataByRoleID(UINT64 qwGuildID, UINT64 qwRoleID, QueryFun fun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleguilddata WHERE qwGuildID = 0 and qwRoleID = " << qwRoleID << ";";

    CDBMgr::Instance().DoGuildSelectQuery(basesql.str(), NULL, 
            [this, qwGuildID, fun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable
            {
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
                UINT32 dwCount = dataRes.size();
                if(byRet == 0)
                {
                    for (UINT32 dwIndex = 0 ; dwIndex < dwCount; ++dwIndex)
                    {
                        mysqlpp::Row& rRow = dataRes[dwIndex];
                        CDBGuildUserTable cDBGuildUserTable;
                        cDBGuildUserTable.InitDataByDBRow(rRow);
                        _mapGuildData[cDBGuildUserTable.GetRoleID()] = cDBGuildUserTable;
                    }
                }
                fun(byRet, dwCount);
            });
}

void CDBGuildUserTableManager::Update(string& strData, EDataChange eUpdateType)
{
    CInArchive ar(strData);
    SDBGuildUserInfo sGuildUser;
    ar >> sGuildUser;
    auto iter = _mapGuildData.find(sGuildUser.sBaseInfo.qwRoleID);
    if (iter == _mapGuildData.end())
    {
        CDBGuildUserTable CDBGuildUserTable;
        CDBGuildUserTable.Update(strData, eUpdateType);
        _mapGuildData[sGuildUser.sBaseInfo.qwRoleID] = CDBGuildUserTable;
    }
    else 
        iter->second.Update(strData, false);
}

void CDBGuildUserTableManager::GetAllInfo(SDBGuildAllInfo & rData)
{
    for (auto it = _mapGuildData.begin(); it != _mapGuildData.end(); ++it)
    {
        SDBGuildUserInfo sGuildUser;
        it->second.ToDBGuildUserInfo(sGuildUser);
        rData.vecMemberInfo.push_back(sGuildUser);
    }
}

bool CDBGuildUserTableManager::GetUserInfo(SDBGuildUserInfo& rInfo, UINT64 qwRoleID)
{
    auto it = _mapGuildData.find(qwRoleID);
    if (it == _mapGuildData.end())
        return false;
    it->second.ToDBGuildUserInfo(rInfo);
    return true;
}

void CDBGuildUserTableManager::GetAllRoleID(TVecUINT64& vecRoleID) const
{
    for (auto it = _mapGuildData.begin(); it != _mapGuildData.end(); ++it)
    {
        vecRoleID.push_back((it->second).GetRoleID());
    }

}

void CDBGuildUserTableManager::DumpToDBGuild(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto it = _vecDelGuildID.begin();it != _vecDelGuildID.end(); ++ it)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblroleguilddata WHERE "\
            "qwRoleID = " << (*it) << ";";
        LOG_DBG << "DumpToDBGuild: " << sqlstr.str();
        CDBMgr::Instance().DoGuildModifyQuery(sqlstr.str(),NULL, [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet << ", rows: " << simRes.rows() << ".";
            this->_nNowQuery--;
            if (byRet)
                this->_nErrQuery++;
            if (this->_nNowQuery == 0)
                fun(this->_nMaxQuery,this->_nErrQuery);
        });
    }
    _vecDelGuildID.clear();

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

}

UINT32 CDBGuildUserTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapGuildData.begin();iter != _mapGuildData.end();iter++)
    {
        if (iter->second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelGuildID.size();

}

void CDBGuildUserTableManager::DelData(string& strData, UINT64 qwGuildID /* = 0 */)
{
    CInArchive ar(strData);
    SDBGuildUserInfo sGuildUser;
    ar >> sGuildUser;

    auto iter = _mapGuildData.find(sGuildUser.sBaseInfo.qwRoleID);
    if (iter != _mapGuildData.end())
    {
        //LOG_DBG << "Start Delete GuildUser(" << sGuildUser.sBaseInfo.qwRoleID << ").";
        if (iter->second.IsInDB())
        {
            //LOG_DBG << "Start Delete GuildUser(" << sGuildUser.sBaseInfo.qwRoleID << ") push_back.";
            _vecDelGuildID.push_back(sGuildUser.sBaseInfo.qwRoleID);
        }
        _mapGuildData.erase(iter);
    }
    else
    {
        LOG_CRI << "Delete no GuildUser(" << sGuildUser.sBaseInfo.qwRoleID << ").";
        _vecDelGuildID.push_back(sGuildUser.sBaseInfo.qwRoleID);  // FIXME: 找不到该用户，还是也一块删除
    }
}

