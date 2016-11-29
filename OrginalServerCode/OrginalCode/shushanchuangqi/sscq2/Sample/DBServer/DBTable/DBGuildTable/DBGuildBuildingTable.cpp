#include "DBGuildBuildingTable.h"

CDBGuildBuildingTable::CDBGuildBuildingTable():
    _qwGuildID(0), _byType(0), _wLevel(0)
{
}

CDBGuildBuildingTable::~CDBGuildBuildingTable()
{
}

void CDBGuildBuildingTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SGuildBuildingInfo sGuildBuilding;
    ar >> sGuildBuilding;

    if(!InitDataByGuildBuilding(sGuildBuilding))
        return ;
}

bool CDBGuildBuildingTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SGuildBuildingInfo sGuildBuilding;
    ar >> sGuildBuilding;

    DIFFONLY2(qwGuildID, sGuildBuilding.qwGuildID, _qwGuildID);
    DIFFONLY2(byType, static_cast<UINT8>(sGuildBuilding.eBuildingType), _byType);
    DIFFONLY2(wLevel, sGuildBuilding.wLevel, _wLevel);

    return  !_setChanged.none();
}

bool CDBGuildBuildingTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblguildbuilding(qwGuildID,byType,wLevel) "\
        "Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwGuildID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)_byType;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)_wLevel;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBGuildBuildingTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblguildbuilding SET";

    UPDATE_UBIGINT(qwGuildID, _qwGuildID);
    UPDATE_UTINYINT(byType, _byType);
    UPDATE_USMALLINT(wLevel, _wLevel);

    ostr << " WHERE qwGuildID =" << _qwGuildID << " and byType = " << static_cast<UINT32>(_byType) << ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBGuildBuildingTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBGuildBuildingTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT(qwGuildID, _qwGuildID);
    GET_UTINYINT(byType, _byType);
    GET_USMALLINT(wLevel, _wLevel);

    TableRowBase::InitDataByDBRow(rRow);
}

UINT64  CDBGuildBuildingTable::GetGuildID() const
{
    return _qwGuildID;
}

UINT8   CDBGuildBuildingTable::GetBuildingType() const
{
    return _byType;
}

UINT16  CDBGuildBuildingTable::GetLevel() const
{
    return _wLevel;
}

bool CDBGuildBuildingTable::InitDataByGuildBuilding(const SGuildBuildingInfo& rGuildInfo)
{
    _qwGuildID      = rGuildInfo.qwGuildID;
    _byType   = static_cast<UINT8>(rGuildInfo.eBuildingType);
    _wLevel    = rGuildInfo.wLevel;
    return true;
}

CDBGuildBuildingTableManager::CDBGuildBuildingTableManager(UINT64 qwGuildID) : 
    CTableManagerBaseForGuild(eGDTBuilding,qwGuildID), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0)
{
}

CDBGuildBuildingTableManager::~CDBGuildBuildingTableManager()
{
}

void CDBGuildBuildingTableManager::QueryDataByGuildID(UINT64 qwGuildID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblguildbuilding WHERE qwGuildID = " << qwGuildID << ";";

    CDBMgr::Instance().DoGuildSelectQuery(basesql.str(), NULL, [this, qwGuildID, queryfun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        UINT32 dwCount = dataRes.size();
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet << ", dwCount = " << dwCount << ".";
        if(byRet == 0)
        {
            for (UINT32 dwIndex = 0 ; dwIndex < dwCount; ++dwIndex)
            {
                mysqlpp::Row& rRow = dataRes[dwIndex];
                CDBGuildBuildingTable cDBGuildBuildingTable;
                cDBGuildBuildingTable.InitDataByDBRow(rRow);
                SBuildingKey sKey( cDBGuildBuildingTable.GetGuildID(), cDBGuildBuildingTable.GetBuildingType());
                _mapGuildData[sKey] = cDBGuildBuildingTable;
            }
        }
        queryfun(byRet, dwCount);
    });
}

void CDBGuildBuildingTableManager::Update(string& strData, EDataChange eUpdateType)
{
    CInArchive ar(strData);

    TVecGuildBuildingInfo vecBuilding;
    ar >> vecBuilding;

    for (auto it = vecBuilding.begin(); it != vecBuilding.end(); ++it)
    {
        string strData2;
        COutArchive ar2(strData2);
        ar2 << (*(*it));
        SBuildingKey sKey ((*it)->qwGuildID, static_cast<UINT8>((*it)->eBuildingType));
        auto iter = _mapGuildData.find(sKey);
        if (iter == _mapGuildData.end())
        {
            CDBGuildBuildingTable CDBGuildBuildingTable;
            CDBGuildBuildingTable.Update(strData2, eUpdateType);
            _mapGuildData[sKey] = CDBGuildBuildingTable;
        }
        else
            iter->second.Update(strData2, false);
    }
}

void CDBGuildBuildingTableManager::GetAllInfo(SDBGuildAllInfo & rData)
{
    for (auto it = _mapGuildData.begin(); it != _mapGuildData.end(); ++it)
    {
        SGuildBuildingInfoPtr pGuildBuilding (new SGuildBuildingInfo);
        pGuildBuilding->qwGuildID    = (it->second).GetGuildID();
        pGuildBuilding->eBuildingType  = static_cast<EBuildingType>((it->second).GetBuildingType());
        pGuildBuilding->wLevel  = (it->second).GetLevel();
        rData.vecBuildingInfo.push_back(pGuildBuilding);
    }
}

void CDBGuildBuildingTableManager::DumpToDBGuild(ManagerUpdateFun fun)
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
        sqlstr << "delete FROM tblguildbuilding WHERE "\
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
    _setDelGuildID.clear();

    /*
    for (auto it = _vecDelGuildID.begin();it != _vecDelGuildID.end(); ++ it)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete FROM tblguildbuilding WHERE "\
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
    */
}

UINT32 CDBGuildBuildingTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapGuildData.begin();iter != _mapGuildData.end();iter++)
    {
        if (iter->second.HasOP())
            dwOP++;
    }
    return dwOP + _vecDelGuildID.size() + _setDelGuildID.size();

}

void CDBGuildBuildingTableManager::DelData(string& strData, UINT64 qwGuildID)
{
    _setDelGuildID.insert(qwGuildID);
    for (auto it = _mapGuildData.begin(); it != _mapGuildData.end(); ++it)
    {
        _setDelGuildID.insert((it->first).qwGuildID);
    }
    _mapGuildData.clear();
    /*
    CInArchive ar(strData);
    TVecGuildBuildingInfo vecBuilding;
    ar >> vecBuilding;

    for (auto it = vecBuilding.begin(); it != vecBuilding.end(); ++it)
    {

        SBuildingKey sKey ((*it)->qwGuildID, static_cast<UINT8>((*it)->eBuildingType));
        auto iter = _mapGuildData.find(sKey);
        if (iter != _mapGuildData.end())
        {
            if (iter->second.IsInDB())
                _vecDelGuildID.push_back((*it)->qwGuildID);
            _mapGuildData.erase(iter);
        }
    }
    */
}

