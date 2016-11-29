#include "DBTripodTable.h"
#include "Protocols.h"
#include "DBRoleNameManager.h"

CDBTripodTableManager g_CDBTripodTableManager;

void CDBTripodTable::InitDataByData(const STripodInfo& rInData)
{
    static_cast<STripodInfo&>(*this) = const_cast<STripodInfo&>(rInData);
}

bool CDBTripodTable::UpdateDataByData(const STripodInfo& newData)
{
    DIFF(byTripodID);
    DIFF(byLevel);
    DIFF(dwExp);
    DIFF(wFireID);
    DIFF(byFireLvl);
    DIFF(dwStartTime);
    DIFF(dwShanfengTime);
    DIFF(dwSoul);
    DIFF(dwLine);

    return  !_setChanged.none();
}

bool CDBTripodTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tbltripoddata(qwRoleID,byTripodID,byLevel,dwExp,wFireID,byFireLvl,dwStartTime,dwShanfengTime,dwSoul, dwLine) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byTripodID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byLevel;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwExp;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)wFireID;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byFireLvl;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwStartTime;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwShanfengTime;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwSoul;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwLine;
    ostr << ");";
    sqlstr = ostr.str();
    return true;
}

bool CDBTripodTable::GetUpdateSqlStr(string& strsql)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tbltripoddata SET";

    UPDATE_UTINYINT_SAME(byTripodID);
    UPDATE_UTINYINT_SAME(byLevel);
    UPDATE_INT_SAME(dwExp);
    UPDATE_USMALLINT_SAME(wFireID);
    UPDATE_UTINYINT_SAME(byFireLvl);
    UPDATE_INT_SAME(dwStartTime);
    UPDATE_INT_SAME(dwShanfengTime);
    UPDATE_INT_SAME(dwSoul);
    UPDATE_INT_SAME(dwLine);

    ostr << " WHERE qwRoleID = " << _qwRoleID << " AND byTripodID = " << (mysqlpp::sql_tinyint_unsigned)byTripodID << ";";
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBTripodTable::ResetChange(void)
{
    SetNew(false);
    _setChanged.reset();
}

void CDBTripodTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    //GET_UBIGINT_SAME(_qwRoleID); // XXX: RoleID in Super
    GET_UTINYINT_SAME(byTripodID);
    GET_UTINYINT_SAME(byLevel);
    GET_INT_SAME(dwExp);
    GET_USMALLINT_SAME(wFireID);
    GET_UTINYINT_SAME(byFireLvl);
    GET_INT_SAME(dwStartTime);
    GET_INT_SAME(dwShanfengTime);
    GET_INT_SAME(dwSoul);
    GET_INT_SAME(dwLine);
}

void CDBTripodTableManager::QueryData(UINT32 dwPageSize, QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "select count(*) as dwCount from (select distinct qwRoleID FROM tbltripoddata) dwCount;";
    CDBMgr::Instance().DoSelectQuery(basesql.str(),NULL,[this, queryfun, basesql,dwPageSize,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {  
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet ;
            UINT32 dwCount = 0;
            if(byRet == 0 && dataRes.size()== 1)
            {
            mysqlpp::Row& rRow = dataRes[0];
            GET_UINT_SAME(dwCount);
            }
            else
            {
            queryfun(byRet,0);
            return ;
            }
            if(dwCount == 0)
            {
            queryfun(byRet,0);
            return ;
            }
            UINT32 dwTotalPage =dwCount % dwPageSize != 0 ? dwCount/dwPageSize+1 : dwCount/dwPageSize;
            for(UINT32 dwPage = 0; dwPage != dwTotalPage;dwPage++)
            {
                mysqlpp::SQLStream querysql(NULL);
                querysql << "select `qwRoleID` from ( ";
                querysql << "(select distinct `qwRoleID` FROM tbltripoddata) as ID)";
                querysql << " ORDER by qwRoleID asc ";
                querysql << "LIMIT ";
                querysql << dwPage * dwPageSize << "," << dwPageSize;
                querysql << ";";
                CDBMgr::Instance().DoSelectQuery(querysql.str(),NULL,[this,dwCount,queryfun,querysql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
                        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;

                        UINT32 ncount = dataRes.size();
                        mysqlpp::Row& rRow = dataRes[0];
                        UINT64 qwRoleID;
                        GET_UBIGINT_SAME(qwRoleID);
                        UINT64 qwRoleIDLow = qwRoleID;
                        rRow = dataRes[ncount-1];
                        GET_UBIGINT_SAME(qwRoleID);
                        UINT64 qwRoleIDMax = qwRoleID;

                        mysqlpp::SQLStream querysql1(NULL);
                        querysql1 << "SELECT * FROM tbltripoddata WHERE qwRoleID >= ";
                        querysql1 << qwRoleIDLow;
                        querysql1 << " AND qwRoleID <= ";
                        querysql1 << qwRoleIDMax;
                        querysql1 << ";";
                        CDBMgr::Instance().DoSelectQuery(querysql1.str(),NULL,[this,dwCount,queryfun,querysql1,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
                                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql1.str() << "result:" << byRet ;
                                UINT32 dwDataCount = dataRes.size();
                                for (UINT32 dwIndex = 0; dwIndex < dwDataCount; ++ dwIndex)
                                {
                                    mysqlpp::Row& rRow = dataRes[dwIndex];
                                    UINT64 qwRoleID;
                                    GET_UBIGINT_SAME(qwRoleID);
                                    if (!qwRoleID)
                                        continue;
                                    CDBTripodTable TripodTable(qwRoleID);
                                    TripodTable.InitDataByDBRow(rRow);

                                    auto iter = _mapAllTripodData.find(qwRoleID);
                                    if (iter != _mapAllTripodData.end())
                                    {
                                        bool bFind = false;
                                        for (size_t i = 0; i < iter->second._vecTripodInfo.size(); ++ i)
                                        {
                                            if (iter->second._vecTripodInfo[i].byTripodID == TripodTable.byTripodID)
                                                bFind = true;
                                        }
                                        if (!bFind)
                                            iter->second._vecTripodInfo.push_back(TripodTable);
                                    }
                                    else
                                    {
                                        STripodPlayerData oTripodData(qwRoleID);
                                        oTripodData._vecTripodInfo.push_back(TripodTable);
                                        _mapAllTripodData.insert(std::make_pair(qwRoleID, oTripodData));
                                    }
                                }
                                if(_mapAllTripodData.size() == dwCount)
                                {
                                    queryfun(byRet, _mapAllTripodData.size());
                                    LOG_INF<<"--------Load tbltripoddata is "<<GetTickCount() - qwLoadTimer<<" miscseconds! " << dwCount;
                                }
                            });
                });
            }
        });
}

void CDBTripodTableManager::UpdateData(UINT64 qwRoleID, const NTripodProt::STripodInfo& oTripodInfo, bool bIsAdd)
{
    CDBTripodTable TripodNew(qwRoleID);

    auto iter = _mapAllTripodData.find(qwRoleID);
    if (iter == _mapAllTripodData.end() && bIsAdd)
    {
        TripodNew.InitDataByData(oTripodInfo);
        TripodNew.SetNew(true);

        STripodPlayerData oTripodData(qwRoleID);
        oTripodData._vecTripodInfo.push_back(TripodNew);
        _mapAllTripodData.insert(std::make_pair(qwRoleID, oTripodData));
    }
    else if(iter != _mapAllTripodData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        bool bFind = false;
        for (size_t i = 0; i < iter->second._vecTripodInfo.size(); ++ i)
        {
            if (iter->second._vecTripodInfo[i].byTripodID == oTripodInfo.byTripodID)
            {
                iter->second._vecTripodInfo[i].UpdateDataByData(oTripodInfo);
                bFind = true;
                break;
            }
        }
        if (!bFind)
        {
            TripodNew.InitDataByData(oTripodInfo);
            TripodNew.SetNew(true);
            iter->second._vecTripodInfo.push_back(TripodNew);
        }
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

UINT32 CDBTripodTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapAllTripodData.begin();iter != _mapAllTripodData.end();iter++)
    {
        for (size_t i = 0; i < iter->second._vecTripodInfo.size(); ++ i)
        {
            CDBTripodTable TripodTable = iter->second._vecTripodInfo[i];
            if (TripodTable.IsNew() || TripodTable.IsChange())
            {
                dwOP++;
            }
        }
    }
    return dwOP + _mapDelTripod.size();

}

void CDBTripodTableManager::DelData(UINT64 qwRoleID, string& strData)
{
    CInArchive ar(strData);
    STripodInfo oTripodInfo;
    ar >> oTripodInfo;
    auto iter = _mapAllTripodData.find(qwRoleID);
    if (iter != _mapAllTripodData.end())
    {
        for (size_t i = 0; i < iter->second._vecTripodInfo.size(); ++ i)
        {
            if (iter->second._vecTripodInfo[i].byTripodID == oTripodInfo.byTripodID)
            {
                _mapDelTripod.insert(std::make_pair(qwRoleID, oTripodInfo));
                iter->second._vecTripodInfo.erase(iter->second._vecTripodInfo.begin()+i);
                break;
            }
        }
        if (iter->second._vecTripodInfo.size() == 0)
        {
            _mapAllTripodData.erase(iter);
        }
    }
}

void CDBTripodTableManager::DumpToDB(bool bForBit)
{
    if(GetUpdataNum() == 0)
    {
        return;
    }
    UINT32 nNowQuery = 0;
    UINT32 nMaxQuery = 1000;
    UINT32 nDelNum = _mapDelTripod.size();
    for (auto deliter = _mapDelTripod.begin(); deliter != _mapDelTripod.end(); deliter ++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tbltripoddata where qwRoleID = " << deliter->first << " AND byTripodID = " << deliter->second.byTripodID << ";";
        CDBMgr::Instance().DoModifyQuery(sqlstr.str(),NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
                });
    }
    _mapDelTripod.clear();
    if(nDelNum >= nMaxQuery && !bForBit)
    {
        return;
    }
    nNowQuery = nDelNum;

    for (auto iter = _mapAllTripodData.begin();iter != _mapAllTripodData.end();iter++)
    {
        if(nNowQuery >= nMaxQuery && !bForBit)
        {
            return;
        }
        bool bDoCaseAll = false;
        for (size_t i = 0; i < iter->second._vecTripodInfo.size(); ++ i)
        {
            bool bDoCase = true;
            CDBTripodTable& TripodTable = iter->second._vecTripodInfo[i];
            if (TripodTable.IsNew())
            {
                string sqlstr;
                TripodTable.GetInsertSqlStr(sqlstr);
                CDBMgr::Instance().DoModifyQuery(sqlstr,NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
                        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr << "result:" << byRet;
                        });
                bDoCaseAll = true;
            }
            else if(TripodTable.IsChange())
            {
                string sqlstr;
                TripodTable.GetUpdateSqlStr(sqlstr);
                CDBMgr::Instance().DoModifyQuery(sqlstr,NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
                        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr << "result:" << byRet;
                        });
                bDoCaseAll = true;
            }
            else
            {
                bDoCase = false;
            }
            if(bDoCase)
            {
                TripodTable.ResetChange();
            }
        }
        if(bDoCaseAll)
            nNowQuery++;
    }
}

void CDBTripodTableManager::GetAllTripod(UINT32 dwPageSize)
{
    QueryData(dwPageSize,
            [dwPageSize,this](INT8 byRet,UINT32 dwTotalSize)
            {
                UINT32 dwTotalPage = dwTotalSize / dwPageSize;//总页数
                if(dwTotalSize%dwPageSize != 0)
                    dwTotalPage++;
                if(dwTotalPage == 0)//无记录
                {
                    SendDataToCenter(dwTotalPage,dwTotalSize);
                    return ;
                }
                _dwQueryFighterMax = dwTotalSize;
                for(auto iter = _mapAllTripodData.begin();iter != _mapAllTripodData.end();iter++)
                {
                    // TODO: 动态日志的加载
                    QueryFighterData(iter->first,
                            [iter,dwTotalPage,dwPageSize,this](INT8 byRet,STripodPlayerPtr pFighter)
                            {
                                if(pFighter != NULL)
                                    iter->second._stPlayerAppear = *pFighter;
                                _dwQueryFighterMax--;
                                if(_dwQueryFighterMax == 0)
                                {
                                    SendDataToCenter(dwTotalPage,dwPageSize);
                                }
                            });
                }
            });
}

void CDBTripodTableManager::SendDataToCenter(UINT32 dwTotalPage,UINT32 dwPageSize)
{
    UINT32 dwPageNum = 0;
    TVecTripodData vecSendData;
    if(dwTotalPage == 0)
    {
        g_Center2DBCommS.Send_SendAllTripod(dwPageNum,dwTotalPage,vecSendData);
        return ;
    }
    for(auto iter = _mapAllTripodData.begin();iter != _mapAllTripodData.end();iter++)
    {
        STripodData rData;
        rData.qwRoleID = iter->first;
        rData.stPlayer = iter->second._stPlayerAppear;
        for (size_t i = 0; i < iter->second._vecTripodInfo.size(); ++ i)
        {
            STripodInfo oTripodInfo;
            static_cast<STripodInfo&>(oTripodInfo) = iter->second._vecTripodInfo[i];
            rData.vecTripods.push_back(oTripodInfo);
        }
        vecSendData.push_back(rData);
        if(vecSendData.size() == dwPageSize)
        {
            dwPageNum++;
            g_Center2DBCommS.Send_SendAllTripod(dwPageNum,dwTotalPage,vecSendData);
            vecSendData.clear();
        }
    }
    if(!vecSendData.empty())
    {
        dwPageNum++;
        g_Center2DBCommS.Send_SendAllTripod(dwPageNum,dwTotalPage,vecSendData);
    }
    if(dwPageNum != dwTotalPage)
    {
        LOG_CRI <<"GetAllTripod ERR";
    }
}

void CDBTripodTableManager::QueryFighterData(UINT64 qwRoleId,QueryPlayerFun fun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT tblroledata.eCareer,tblroledata.eSex,tblrolefighter.byLevel from tblroledata,tblrolefighter where tblroledata.qwRoleID = ";
    basesql <<(mysqlpp::sql_bigint_unsigned)qwRoleId;
    basesql << " and tblrolefighter.qwRoleID = ";
    basesql <<(mysqlpp::sql_bigint_unsigned)qwRoleId;
    basesql <<"  and tblrolefighter.wFighterID < 20;";
    CDBMgr::Instance().DoArenaSelectQuery(basesql.str(),NULL,[qwRoleId,this, fun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            UINT32 ncount = dataRes.size();
            STripodPlayerPtr pFighter(new SArenaFighter);
            if(pFighter == NULL)
            {
            fun(byRet,NULL);
            return ;
            }
            SArenaFighter &stFighter = *pFighter;
            if(ncount == 1)
            {
            mysqlpp::Row& rRow = dataRes[0];
            UINT8 byJob = (mysqlpp::sql_tinyint_unsigned)rRow["eCareer"];
            UINT8 bySex = (mysqlpp::sql_tinyint_unsigned)rRow["eSex"];
            stFighter.stAppear.eJob = static_cast<NProtoCommon::ECareerType>(byJob);
            stFighter.stAppear.eSex = static_cast<NProtoCommon::ESexType>(bySex);
            stFighter.wLevel  = (mysqlpp::sql_smallint_unsigned)rRow["byLevel"];
            stFighter.strName = RoleNameManager::Instance().GetPlayerName(qwRoleId);
            //外观
            mysqlpp::SQLStream subsql(NULL);
            subsql <<"select tblroleitemdata.wItemID,tblrolefashion.byLevel from tblrolefashion,tblroleitemdata where tblroleitemdata.qwInstID = tblrolefashion.qwInstID  and tblrolefashion.qwRoleID = ";
            subsql << qwRoleId;
            subsql <<" and tblrolefashion.bySelected > 0 and tblrolefashion.byHide = 0";
            CDBMgr::Instance().DoArenaSelectQuery(subsql.str(),NULL,[qwRoleId,pFighter,this,fun,subsql](INT8 byRet, mysqlpp::StoreQueryResult& dataRes)mutable{
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << subsql.str() << "result:" << byRet;
                    if(byRet != 0)
                    {
                    fun(byRet,NULL);
                    return;
                    }
                    for(size_t sz = 0; sz< dataRes.size(); sz++)
                    {
                    mysqlpp::Row& rRow = dataRes[sz];
                    NBattleGS::SEquipShowInfo sEquipInfo;
                    sEquipInfo.wEquipID = (mysqlpp::sql_smallint_unsigned)rRow["wItemID"];
                    sEquipInfo.byStrengthenLevel = (mysqlpp::sql_tinyint_unsigned)rRow["byLevel"];
                    sEquipInfo.byPos = 0;
                    pFighter->stAppear.vEquip.push_back(sEquipInfo);
                    }
                    fun(byRet,pFighter);
                    });
            }
    if(byRet != 0)
    {
        fun(byRet,NULL);
        return;
    }
    });
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

