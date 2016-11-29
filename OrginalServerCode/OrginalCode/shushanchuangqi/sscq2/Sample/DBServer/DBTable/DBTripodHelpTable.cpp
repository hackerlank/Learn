#include "DBTripodHelpTable.h"
#include "Protocols.h"
#include "DBRoleNameManager.h"

CDBTripodHelpTableManager g_CDBTripodHelpTableManager;

void CDBTripodHelpTable::InitDataByStr(string& strData)
{
    STripodHelp oData;
    CInArchive ar(strData);
    ar >> oData;
    Copy(&oData);
    _qwRoleID = oData.qwRoleID;
}

bool CDBTripodHelpTable::UpdateDataByStr(string& strData)
{
    STripodHelp oData;
    CInArchive ar(strData);
    ar >> oData;
    STripodHelpEx newData;
    newData.Copy(&oData);
    
    DIFF(qwRoleID);
    DIFF(strFighterHelp);
    DIFF(strPlayerHelp);

    return !_setChanged.none();
}

bool CDBTripodHelpTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tbltripodhelpdata(qwRoleID,strFighterHelp,strPlayerHelp";
    ostr << ") Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," <<"'"<< (mysqlpp::sql_char)strFighterHelp<<"'";
    ostr << "," <<"'"<< (mysqlpp::sql_char)strPlayerHelp<<"'";
    ostr << ");"; 
    sqlstr = ostr.str();
    return true;
}

bool CDBTripodHelpTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tbltripodhelpdata SET";
    UPDATE_UBIGINT_SAME(qwRoleID);
    UPDATE_STRING_CHAR_SAME(strFighterHelp);
    UPDATE_STRING_CHAR_SAME(strPlayerHelp);
    ostr << " WHERE qwRoleID =" << _qwRoleID << ";";
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBTripodHelpTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBTripodHelpTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{   
    GET_UBIGINT_SAME(qwRoleID);
    GET_STRING_CHAR_SAME(strFighterHelp);
    GET_STRING_CHAR_SAME(strPlayerHelp);
   
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void CDBTripodHelpTableManager::Update(const STripodHelp& oData)
{
    STripodHelpEx newData;
    newData.Copy(&oData);

    string strData;
    COutArchive iar(strData);
    iar << oData;

    auto iter = _mapTripodHelp.find(newData.qwRoleID);
    if (iter == _mapTripodHelp.end())
    {
        CDBTripodHelpTable oTripodHelpNew(newData.qwRoleID);
        oTripodHelpNew.Update(strData, true);
        _mapTripodHelp[newData.qwRoleID] = oTripodHelpNew;
    }
    else if(iter != _mapTripodHelp.end())
        iter->second.Update(strData,false);
}

void CDBTripodHelpTableManager::DumpToDB()
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelTripodHelp.begin();deliter != _vecDelTripodHelp.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"DELETE FROM tbltripodhelpdata WHERE qwRoleID = " << (*deliter) <<  ";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, 
                [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes)
                {                              
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
                    this->_nNowQuery--;
                    if (byRet)
                    {
                        this->_nErrQuery++;
                        LOG_CRI<<"CDBTripodHelpTableManager::DumpToDB delete Error\n";
                    }
                });
    }
    _vecDelTripodHelp.clear();
    for (auto iter =_mapTripodHelp.begin();iter !=_mapTripodHelp.end();iter++)
    {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDB(_byLine,
                    [this](INT8 byRet)
                    {
                        this->_nNowQuery--;
                        if (byRet)
                        {
                            this->_nErrQuery++;
                            LOG_CRI<<"CDBTripodHelpTableManager::DumpToDB update Error\n";
                        }
                    });
        }
    }
}

UINT32 CDBTripodHelpTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapTripodHelp.begin();iter != _mapTripodHelp.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        }
    }
    return dwOP +_vecDelTripodHelp.size();
}

void CDBTripodHelpTableManager::GetALLInfo(TVecTripodHelp& vecTripodHelp)
{
    for (auto iter = _mapTripodHelp.begin();iter != _mapTripodHelp.end();iter++)
    {
        STripodHelp oTripodHelp;
        iter->second.CopyTo(oTripodHelp);
        vecTripodHelp.push_back(oTripodHelp);
    }
}

void CDBTripodHelpTableManager::DelData(const STripodHelp& oData)
{
    STripodHelpEx deleteData;
    deleteData.Copy(&oData);

    auto iter = _mapTripodHelp.find(deleteData.qwRoleID);
    if (iter != _mapTripodHelp.end())
    {
        if(iter->second.IsInDB())
        {
           _vecDelTripodHelp.push_back(deleteData.qwRoleID);
        }
        _mapTripodHelp.erase(deleteData.qwRoleID);
    }
}

void CDBTripodHelpTableManager::QueryData(UINT32 dwPageSize, QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "select count(*) as dwCount from tbltripodhelpdata;";
    CDBMgr::Instance().DoSelectQuery(basesql.str(), NULL,
            [this, queryfun, basesql, dwPageSize, qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable
            {
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
                    return;
                }
                if(dwCount == 0)
                {
                    queryfun(byRet,0);
                    return;
                }
                UINT32 dwTotalPage = dwCount % dwPageSize != 0 ? dwCount/dwPageSize+1 : dwCount/dwPageSize;
                for(UINT32 dwPage = 0; dwPage != dwTotalPage;dwPage++)
                {
                    mysqlpp::SQLStream querysql(NULL);
                    querysql << "SELECT * FROM tbltripodhelpdata";
                    querysql << " WHERE qwRoleID >= (SELECT qwRoleID FROM tbltripodhelpdata LIMIT ";
                    querysql << dwPage*dwPageSize;
                    querysql << " ,1) LIMIT ";
                    querysql << dwPageSize;
                    querysql << ";";
                    CDBMgr::Instance().DoSelectQuery(querysql.str(),NULL,
                            [this,dwCount,queryfun,querysql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable
                            {
                                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;

                                UINT32 ncount = dataRes.size();
                                for(UINT32 i = 0 ; i< ncount;i++)
                                {
                                    mysqlpp::Row& rRow = dataRes[i];
                                    UINT64 qwRoleID;
                                    GET_UBIGINT_SAME(qwRoleID);
                                    CDBTripodHelpTable oTripodHelpNew(qwRoleID);
                                    oTripodHelpNew.InitDataByDBRow(rRow);
                                    oTripodHelpNew.StrToVec();
                                    _mapTripodHelp[qwRoleID]= oTripodHelpNew;
                                }
                                if(_mapTripodHelp.size() == dwCount)
                                {
                                    queryfun(byRet, dwCount);
                                    LOG_INF<<"--------Load tbltripodhelpdata is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
                                }
                            });
                }
            });
}

void CDBTripodHelpTableManager::GetAllTripodHelper(UINT32 dwPageSize)
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
            for(auto iter = _mapTripodHelp.begin(); iter != _mapTripodHelp.end(); iter++)
            {
                size_t iSize = iter->second.vecPlayerHelp.size();
                if (iSize == 0)     //无玩家协助
                    _dwQueryFighterMax --;
                for (size_t i = 0; i < iSize; ++ i)
                {
                    bool bIsEnd = iSize == i+1 ? true : false;
                    UINT64 qwHelpID = iter->second.vecPlayerHelp[i].qwRoleID;
                    if (qwHelpID == 0)
                        continue;
                    QueryFighterData(qwHelpID,[this,iter,dwTotalPage,dwPageSize,i,bIsEnd](INT8 byRet,STripodHelpPlayerPtr pFighter)
                            {
                            SPlayerHelpInfo& oPlayerHelp = iter->second.vecPlayerHelp[i];
                            if(pFighter != NULL)
                            {
                                oPlayerHelp.stPlayer = *pFighter;
                            }
                            if (bIsEnd)
                                _dwQueryFighterMax --;
                            if(_dwQueryFighterMax ==0)
                            {
                                SendDataToCenter(dwTotalPage,dwPageSize);
                            }
                            });
                }
            }
            });
}

void CDBTripodHelpTableManager::SendDataToCenter(UINT32 dwTotalPage,UINT32 dwPageSize)
{
    UINT32 dwPageNum = 0;
    TVecTripodHelp vecSendData;
    if(dwTotalPage == 0)
    {
        g_Center2DBCommS.Send_SendAllTripodHelper(dwPageNum,dwTotalPage,vecSendData);
        return ;
    }
    for(auto iter = _mapTripodHelp.begin();iter != _mapTripodHelp.end();iter++)
    {
        STripodHelp rData;
        rData.qwRoleID = iter->first;
        rData.vecFighterHelp = iter->second.vecFighterHelp;
        rData.vecPlayerHelp = iter->second.vecPlayerHelp;
        vecSendData.push_back(rData);
        if(vecSendData.size() == dwPageSize)
        {
            dwPageNum++;
            g_Center2DBCommS.Send_SendAllTripodHelper(dwPageNum,dwTotalPage,vecSendData);
            vecSendData.clear();
        }
    };
    if(!vecSendData.empty())
    {
        dwPageNum++;
        g_Center2DBCommS.Send_SendAllTripodHelper(dwPageNum,dwTotalPage,vecSendData);
    }
    if(dwPageNum != dwTotalPage)
    {
        LOG_CRI <<"GetAllTripodHelper ERROR";
    }
}

void CDBTripodHelpTableManager::QueryFighterData(UINT64 qwRoleId,QueryPlayerFun fun)
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
            STripodHelpPlayerPtr pFighter(new SArenaFighter);
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
        return;
    }
    });
}

