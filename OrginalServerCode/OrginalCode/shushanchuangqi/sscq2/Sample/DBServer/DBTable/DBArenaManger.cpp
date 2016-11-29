#include "DBArenaManger.h"
#include "Protocols.h"
#include "DBRoleNameManager.h"
CDBTotalArenaManager g_CDBTotalArenaManager;
void CDBTotalArena::InitDataByData(const SArenaPlayerBaseData& rInData)
{
    static_cast<SArenaPlayerBaseData &>(*this) = const_cast<SArenaPlayerBaseData&>(rInData);
}

bool CDBTotalArena::UpdateDataByData(const SArenaPlayerBaseData& newData)
{
    DIFF(dwRanking);
    DIFF(dwScore);
    DIFF(eLevel);
    //DIFF(dwSameDays);
    DIFF(dwLastFlushTime);
    DIFF(dwLastRank);
    DIFF(eLastLevel);
    DIFF(dwFighterPower); 
    DIFF(dwLadderRank);
    DIFF(dwLastLadderRank);
    DIFF(byQuality);
    DIFF(byVIPLevel);

    return  !_setChanged.none();
}

bool CDBTotalArena::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tbltotalarena(qwRoleID,dwRanking,dwScore,eLevel,dwLastFlushTime,dwLastRank,eLastLevel,dwFighterPower,dwLadderRank,dwLastLadderRank,byQuality, byVIPLevel) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwRanking;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwScore;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)eLevel;
   // ostr << "," << (mysqlpp::sql_int_unsigned)dwSameDays;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwLastFlushTime;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwLastRank;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)eLastLevel;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwFighterPower;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwLadderRank;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwLastLadderRank;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byQuality;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byVIPLevel;
    ostr <<");";
    sqlstr = ostr.str();
    return true;           
}

bool CDBTotalArena::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tbltotalarena SET";
    UPDATE_UINT_SAME(dwRanking);
    UPDATE_UINT_SAME(dwScore);
    UPDATE_UTINYINT_SAME(eLevel);
    //UPDATE_UINT_SAME(dwSameDays);
    UPDATE_UINT_SAME(dwLastFlushTime);
    UPDATE_UINT_SAME(dwLastRank);
    UPDATE_UTINYINT_SAME(eLastLevel);
    UPDATE_UINT_SAME(dwFighterPower);
    UPDATE_UINT_SAME(dwLadderRank);
    UPDATE_UINT_SAME(dwLastLadderRank);
    UPDATE_UTINYINT_SAME(byQuality);
    UPDATE_UTINYINT_SAME(byVIPLevel);
    ostr << " WHERE  qwRoleID =" <<_qwRoleID <<  ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBTotalArena::ResetChange(void)
{
    _setChanged.reset();
    _bIsNew = false;
}

void CDBTotalArena::InitDataByDBRow(const mysqlpp::Row &rRow)
{   
    GET_UINT_SAME(dwRanking);
    UINT8 byLevel;
    GET_UTINYINT(eLevel,byLevel);
    eLevel = static_cast<EArenaLevel>(byLevel);
    GET_UINT_SAME(dwScore);
    //GET_UINT_SAME(dwSameDays);
    GET_UINT_SAME(dwLastFlushTime);
    GET_UINT_SAME(dwLastRank);
    UINT8 byLastLevel;
    GET_UTINYINT(eLastLevel,byLastLevel);
    GET_UINT_SAME(dwFighterPower);
    GET_UINT_SAME(dwLadderRank);
    GET_UINT_SAME(dwLastLadderRank);
    GET_UTINYINT_SAME(byQuality);
    GET_UTINYINT_SAME(byVIPLevel);
    eLastLevel = static_cast<EArenaLevel>(byLastLevel);


}

void CDBTotalArenaManager::QueryData(UINT32 dwPageSize,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "select count(*) as dwCount from tbltotalarena;";
    CDBMgr::Instance().DoArenaSelectQuery(basesql.str(),NULL,[this, queryfun, basesql,dwPageSize,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {  
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
                querysql << "SELECT * FROM tbltotalarena"; 
                querysql << " WHERE qwRoleID >= (SELECT qwRoleID FROM tbltotalarena LIMIT ";
                querysql << dwPage*dwPageSize;
                querysql << " ,1) LIMIT ";
                querysql << dwPageSize;
                querysql << ";";
                CDBMgr::Instance().DoArenaSelectQuery(querysql.str(),NULL,[this,dwCount, queryfun, querysql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
                        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;
                        UINT32 ncount = dataRes.size();
                        for(UINT32 i = 0; i< ncount; ++i)
                        {
                        mysqlpp::Row& rRow = dataRes[i];
                        UINT64 qwRoleID;
                        GET_UBIGINT_SAME(qwRoleID);
                        CDBTotalArena ArenaTable(qwRoleID);
                        ArenaTable.InitDataByDBRow(rRow);
                        _mapRoleArenaData[qwRoleID]= ArenaTable;
                        }
                        if(_mapRoleArenaData.size() == dwCount)
                        {
                        queryfun(byRet, dwCount);
                        LOG_INF<<"--------Load tbltotalarena is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
                        }
                        });
            }


    });

}

void CDBTotalArenaManager::UpdateData(UINT64 qwRoleID,const SArenaPlayerBaseData &testData)
{
    auto iter = _mapRoleArenaData.find(qwRoleID);
    if(iter == _mapRoleArenaData.end())
    {
        CDBTotalArena ArenaNew(qwRoleID);
        ArenaNew.InitDataByData(testData);
        ArenaNew.SetNew(true);
        _mapRoleArenaData[qwRoleID] = ArenaNew;

    }
    else 
    {
        iter->second.UpdateDataByData(testData);
    }
}

void CDBTotalArenaManager::DumpToDB(bool bForBit)
{
    if(GetUpdataNum() ==0 )
    {
        return ;
    }
    UINT32 nNowQuery = 0;
    UINT32 nMaxQuery = 1000;
    UINT32 nDelNum = _vecDelArena.size();
    for (auto deliter = _vecDelArena.begin();deliter != _vecDelArena.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tbltotalarena where qwRoleID="<<*deliter <<  ";";
        CDBMgr::Instance().DoArenaModifyQuery(sqlstr.str(),NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){      
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
                });
    }
    _vecDelArena.clear();
    if(nDelNum >= nMaxQuery && !bForBit)
    {
        return ;
    }
    nNowQuery = nDelNum;

    for (auto iter = _mapRoleArenaData.begin();iter != _mapRoleArenaData.end();iter++)
    {
        if(nNowQuery >= nMaxQuery && !bForBit)
        {
            return ;
        }
        bool bDoCase = true;
        if (iter->second.IsNew())
        {
            string sqlstr;
            iter->second.GetInsertSqlStr(sqlstr);
            CDBMgr::Instance().DoArenaModifyQuery(sqlstr,NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr << "result:" << byRet;
                    });
        }
        else if(iter->second.IsChange())
        {
            string sqlstr;
            iter->second.GetUpdateSqlStr(sqlstr);
            CDBMgr::Instance().DoArenaModifyQuery(sqlstr,NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr << "result:" << byRet;
                    });

        }
        else
        {
            bDoCase = false;
        }
        if(bDoCase)
        {
            iter->second.ResetChange();
            nNowQuery++;
        }
    }   

}

UINT32 CDBTotalArenaManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleArenaData.begin();iter != _mapRoleArenaData.end();iter++)
    {
        if (iter->second.IsNew() ||iter->second.IsChange())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelArena.size();

}

void CDBTotalArenaManager::DelData(UINT64 qwRoleID)
{
    auto iter = _mapRoleArenaData.find(qwRoleID);
    if (iter != _mapRoleArenaData.end())
    {
        if(!iter->second.IsNew())
        {
            _vecDelArena.push_back(qwRoleID);
        }
        _mapRoleArenaData.erase(qwRoleID);
    }
}

void CDBTotalArenaManager::GetAllArena(UINT32 dwPageSize)
{
    QueryData(dwPageSize,[dwPageSize,this](INT8 byRet,UINT32 dwTotalSize)
            {
            UINT32 dwTotalPage = dwTotalSize/dwPageSize;//总页数
            if(dwTotalSize%dwPageSize != 0)
            {
            dwTotalPage++;
            }
            if(dwTotalPage == 0)//无记录
            {
            SendDataToCenter(dwTotalPage,dwTotalSize);
            return ;
            }
            _dwQueryFighterMax = dwTotalSize;
            for(auto iter = _mapRoleArenaData.begin();iter != _mapRoleArenaData.end();iter++)
            {
            QueryFighterData(iter->first,[iter,dwTotalPage,dwPageSize,this](INT8 byRet,SArenaFighterPtr pFighter)
                {
                if(pFighter != NULL)
                {
                iter->second._stFighter = *pFighter;
                }
                _dwQueryFighterMax--;
                if(_dwQueryFighterMax ==0)
                {
                SendDataToCenter(dwTotalPage,dwPageSize);     
                }

                });

            }
            });
}

void CDBTotalArenaManager::SendDataToCenter(UINT32 dwTotalPage,UINT32 dwPageSize)
{

    UINT32 dwPageNum = 0;
    NArenaGS::TVecArenaPlayerData vecSendData;
    if(dwTotalPage == 0)
    {
        g_Center2DBCommS.Send_SendAllArena(dwPageNum,dwTotalPage,vecSendData);
        return ;
    }
    for(auto iter = _mapRoleArenaData.begin();iter != _mapRoleArenaData.end();iter++)
    {
        SArenaPlayerData rData;
        rData.qwRoleID =iter->second._qwRoleID;
        rData.stBaseData = static_cast<SArenaPlayerBaseData>(iter->second);
        rData.stFighter = iter->second._stFighter;
        vecSendData.push_back(rData);
        if(vecSendData.size() == dwPageSize)
        {
            dwPageNum++;
            g_Center2DBCommS.Send_SendAllArena(dwPageNum,dwTotalPage,vecSendData);
            vecSendData.clear();
        }
    }
    if(!vecSendData.empty())
    {
        dwPageNum++;
        g_Center2DBCommS.Send_SendAllArena(dwPageNum,dwTotalPage,vecSendData);
    }
    if(dwPageNum != dwTotalPage)
    {
        LOG_CRI <<"GetAllArena ERR";
    }

}

void CDBTotalArenaManager::QueryFighterData(UINT64 qwRoleId,QueryFighterFun fun)
{
    mysqlpp::SQLStream basesql(NULL);   
    basesql << "SELECT  eCareer,eSex,byLevel from tblroledata where qwRoleID = ";
    basesql <<(mysqlpp::sql_bigint_unsigned)qwRoleId;
    CDBMgr::Instance().DoArenaSelectQuery(basesql.str(),NULL,[qwRoleId,this, fun, basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            UINT32 ncount = dataRes.size();
            SArenaFighterPtr pFighter(new SArenaFighter);
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
            UINT8 byLevel =    (mysqlpp::sql_tinyint_unsigned)rRow["byLevel"];
            stFighter.wLevel= byLevel;
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
                    return ;
                    }
                    for(size_t i = 0;i< dataRes.size();i++)
                    {
                    mysqlpp::Row& rRow = dataRes[i];
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
        return ;
    }

    });
}
