
#include "DBWonderPrizeTable.h"

void CDBWonderPrizeTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    SWonderPrize2DB oLevelPrize;
    ar >> oLevelPrize;
    static_cast<SWonderPrize2DB&>(*this) = oLevelPrize;
}
void CDBWonderPrizeTable::InitDataByBase(const SWonderPrize2DB  &rInfo)
{
    static_cast<SWonderPrize2DB&>(*this) = rInfo;
}

bool CDBWonderPrizeTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SWonderPrize2DB newData;
    ar >> newData;
    DIFF( byStatus    );
    return  !_setChanged.none();
}

bool CDBWonderPrizeTable::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblwonderprize(qwRoleID";
    ostr << ","<< "wActType             ";
    ostr << ","<< "wActID             ";
    ostr << ","<< "wCond       ";
    ostr << ","<< "byStatus    ";
    ostr <<") Values(";
    ostr <<(mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," <<(mysqlpp::sql_smallint_unsigned)wActType;
    ostr << "," <<(mysqlpp::sql_smallint_unsigned)wActID;
    ostr << "," <<(mysqlpp::sql_int_unsigned)wCond;
    ostr << "," <<(mysqlpp::sql_tinyint_unsigned)byStatus;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBWonderPrizeTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblwonderprize SET";
    UPDATE_UTINYINT_SAME(byStatus);
    ostr << " WHERE qwRoleID=" << qwRoleID << " and wActID="<<wActID<<" and wCond="<<wCond<<";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBWonderPrizeTable::ResetChange(void)
{
    _setChanged.reset();
}

void CDBWonderPrizeTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{
    GET_UBIGINT_SAME(qwRoleID);
    GET_SMALLINT_SAME(wActType);
    GET_SMALLINT_SAME(wActID);
    GET_UINT_SAME(wCond);
    GET_UTINYINT_SAME(byStatus);
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID = qwRoleID;
}

void   CDBWonderPrizeTableManager::QueryLevelData()
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT qwRoleID,byLevel FROM tblroledata;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblwonderprize is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        UINT64 qwRoleID;
        UINT8 byLevel;
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                qwRoleID = (mysqlpp::sql_bigint_unsigned)rRow[0];
                byLevel = (mysqlpp::sql_tinyint_unsigned)rRow[1];
                _mapRoleID2Level.insert(make_pair(qwRoleID,byLevel));
            }
        }
        if(byRet == 0)
           Config.SetPreLoad(eLoadWonderPrizeLevel);
        //queryfun(byRet, ncount);
    });

}
void   CDBWonderPrizeTableManager::QueryTrumpData()
{
    mysqlpp::SQLStream basesql(NULL);
    //4500 - 6499 法宝ID
    basesql << "SELECT qwRoleID,wItemID FROM tblroleitemdata where wItemID >=4500 AND wItemID <= 6499;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblwonderprize is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        UINT64 qwRoleID;
        UINT16 wItemID;
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                qwRoleID = (mysqlpp::sql_bigint_unsigned)rRow[0];
                wItemID = (mysqlpp::sql_smallint_unsigned)rRow[1];
                _mapRoleID2Trump.insert(make_pair(qwRoleID,wItemID));
            }
        }
        if(byRet == 0)
          Config.SetPreLoad(eLoadWonderPrizeTrump);
        //queryfun(byRet, ncount);
    });


}

void   CDBWonderPrizeTableManager::QueryFighterData()
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT qwRoleID,wFighterID FROM tblrolefighter;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblwonderprize is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        UINT64 qwRoleID;
        UINT16 wFighterID;
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                qwRoleID = (mysqlpp::sql_bigint_unsigned)rRow[0];
                wFighterID = (mysqlpp::sql_smallint_unsigned)rRow[1];
                //LOG_CRI << "QueryFighter qwRoleID = " <<qwRoleID << " | wFighterID = " <<wFighterID ;
                _mapRoleID2Fighter.insert(make_pair(qwRoleID,wFighterID));
            }
        }
        if(byRet == 0)
           Config.SetPreLoad(eLoadWonderPrizeFighter);
        //queryfun(byRet, ncount);
    });


}
void   CDBWonderPrizeTableManager::QueryFormationData()
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT qwRoleID,wPetID FROM tblpetdata;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblwonderprize is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        UINT64 qwRoleID;
        UINT16 wPetID;
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                qwRoleID = (mysqlpp::sql_bigint_unsigned)rRow[0];
                wPetID = (mysqlpp::sql_smallint_unsigned)rRow[1];
                _mapRoleID2Formation.insert(make_pair(qwRoleID,wPetID));
            }
        }
        if(byRet == 0)
          Config.SetPreLoad(eLoadWonderPrizeFormation);
        //queryfun(byRet, ncount);
    });


}

void   CDBWonderPrizeTableManager::QueryBeautyData()
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT qwRoleID,wBeautyID FROM tblrolebeauty;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblwonderprize is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        UINT64 qwRoleID;
        UINT16 wBeautyID;
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                qwRoleID = (mysqlpp::sql_bigint_unsigned)rRow[0];
                wBeautyID = (mysqlpp::sql_smallint_unsigned)rRow[1];
                _mapRoleID2Beauty.insert(make_pair(qwRoleID,wBeautyID));
            }
        }
        //queryfun(byRet, ncount);
        if(byRet == 0)
           Config.SetPreLoad(eLoadWonderPrizeBeauty);
    });


}

void   CDBWonderPrizeTableManager::QueryHorseData()
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT qwRoleID,dwHorseID FROM tblrolehorse;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblwonderprize is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        UINT64 qwRoleID;
        UINT32 dwHorseID;
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                qwRoleID = (mysqlpp::sql_bigint_unsigned)rRow[0];
                dwHorseID = (mysqlpp::sql_smallint_unsigned)rRow[1];
                _mapRoleID2Horse.insert(make_pair(qwRoleID,dwHorseID));
            }
        }
        //queryfun(byRet, ncount);
       if(byRet == 0)
          Config.SetPreLoad(eLoadWonderPrizeHorse);
    });


}
void   CDBWonderPrizeTableManager::QueryDungonData()
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT qwRoleID,dwDgnType FROM tblroledgninfo where dwCompleteTimes >= 1;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblwonderprize is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        UINT64 qwRoleID;
        UINT32 dwDgnType;
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                qwRoleID = (mysqlpp::sql_bigint_unsigned)rRow[0];
                dwDgnType = (mysqlpp::sql_int_unsigned)rRow[1];
                _mapRoleID2Dungon.insert(make_pair(qwRoleID,dwDgnType));
            }
        }
        if(byRet == 0)
            Config.SetPreLoad(eLoadWonderPrizeDungon);
        //queryfun(byRet, ncount);
    });
}

void CDBWonderPrizeTableManager::QueryData()
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblwonderprize;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
        LOG_INF<<"--------Load tblwonderprize is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
        UINT32 ncount = dataRes.size();
        UINT64 qwRoleID;
        if(byRet == 0)
        {
            for(UINT32 i =0 ; i< ncount;i++)
            {
                mysqlpp::Row& rRow = dataRes[i];
                qwRoleID = (mysqlpp::sql_bigint_unsigned)rRow[0];
                CDBWonderPrizeTable oTable(qwRoleID);
                oTable.InitDataByDBRow(rRow);
                SWonderPrizeKey oKey(qwRoleID,oTable.wActID,oTable.wCond);
                _mapWonderPrizeDBData[oKey]= oTable;
            }
        }
        if(byRet == 0)
             Config.SetPreLoad(eLoadWonderPrize);

        //queryfun(byRet, ncount);
    });
}

void CDBWonderPrizeTableManager::Update(const SWonderPrize2DB& oLevelPrize,bool bIsAdd)
{
    string strData;
    COutArchive iar(strData);
    iar << oLevelPrize;

    UINT64 qwRoleID = oLevelPrize.qwRoleID;
    SWonderPrizeKey oKey(oLevelPrize.qwRoleID,oLevelPrize.wActID,oLevelPrize.wCond);
    auto iter = _mapWonderPrizeDBData.find(oKey);
    if (iter == _mapWonderPrizeDBData.end())
    {
        CDBWonderPrizeTable oTemp(qwRoleID);
        oTemp.Update(strData,true);
        _mapWonderPrizeDBData[oKey] = oTemp;
    }
    else if(iter != _mapWonderPrizeDBData.end()/*&& !bIsAdd XXX: 如果存在时增加转换成更新*/)
    {
        iter->second.Update(strData, false);
    }
    else
    {
        // LOGERR("ERR update!");
    }
}

void CDBWonderPrizeTableManager::GetALLInfo(TVecWonderPrize2DB & rData)
{
    for (auto iter = _mapWonderPrizeDBData.begin();iter != _mapWonderPrizeDBData.end();iter++)
    {

        SWonderPrize2DB oLevelPrize;
        oLevelPrize.qwRoleID  =iter->second.qwRoleID;
        oLevelPrize.wActType    =iter->second.wActType;
        oLevelPrize.wActID    =iter->second.wActID;
        oLevelPrize.wCond    =iter->second.wCond;
        oLevelPrize.byStatus   =iter->second.byStatus       ;
        rData.push_back(oLevelPrize);
    }


}

void CDBWonderPrizeTableManager::DumpToDB()
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;

    for (auto deliter = _vecDel.begin();deliter != _vecDel.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblwonderprize WHERE qwRoleID = "<<deliter->qwRoleID<<" and wActID="<<deliter->wActID<<" and wCond="<<deliter->wCond<<";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){                              
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
            {
                this->_nErrQuery++;
            }
            //if (this->_nNowQuery == 0)
            //{
            //    fun(this->_nMaxQuery,this->_nErrQuery);
            //}
        });
    }
    _vecDel.clear();

       for (auto iter = _mapWonderPrizeDBData.begin();iter != _mapWonderPrizeDBData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDB(_byLine,[this](INT8 byRet) {
                this->_nNowQuery--;
                if (byRet)
                {
                    this->_nErrQuery++;
                    LOG_INF<< "CDBWonderPrizeManager::DumpToDB update Error!";
                }
                else
                {

                }
                //if (this->_nNowQuery == 0)
                //{
                //    fun(_nMaxQuery,this->_nErrQuery);
                //}
            });
        }
    }   


}

UINT32 CDBWonderPrizeTableManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapWonderPrizeDBData.begin();iter != _mapWonderPrizeDBData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDel.size();

}

void CDBWonderPrizeTableManager::DelData(const SWonderPrize2DB& oLevelPrize)
{  
    SWonderPrizeKey oKey(oLevelPrize.qwRoleID,oLevelPrize.wActID,oLevelPrize.wCond);
    auto iter = _mapWonderPrizeDBData.find(oKey);
    if (iter != _mapWonderPrizeDBData.end())
    {
        if (iter->second.IsInDB())
        {
            _vecDel.push_back(oKey);
        }

        _mapWonderPrizeDBData.erase(iter);
    }
}

void CDBWonderPrizeTableManager::DelData(const UINT16& wActID)
{
    mysqlpp::SQLStream sqlstr(NULL);
    sqlstr<<"delete FROM tblwonderprize WHERE wActID = "<< wActID <<" ;";
    CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){                              
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
            {
                this->_nErrQuery++;
            }
            //if (this->_nNowQuery == 0)
            //{
            //    fun(this->_nMaxQuery,this->_nErrQuery);
            //}
        });
}

void   CDBWonderPrizeTableManager::GetALLInfo(std::map<UINT64,UINT8>& _mapID2Level)
{
    UINT64 qwRoleID;
    UINT8 byLevel;
    for (auto iter = _mapRoleID2Level.begin();iter != _mapRoleID2Level.end();iter++)
    {
        qwRoleID = iter->first;
        byLevel = iter->second;
        _mapID2Level.insert(make_pair(qwRoleID,byLevel));
    }
}

void   CDBWonderPrizeTableManager::GetInfoForDungon(multimap<UINT64,UINT32>& _mapID2Level)
{
    for (auto iter = _mapRoleID2Dungon.begin();iter != _mapRoleID2Dungon.end();iter++)
    {
        //LOG_CRI << "DungonID = "<<iter->first<< " | qwRoleID = " <<iter->second;
        _mapID2Level.insert(make_pair(iter->first,iter->second));
    }
}

void   CDBWonderPrizeTableManager::GetInfoForTrump(multimap<UINT64,UINT16>& _mapID2Level)
{
    for (auto iter = _mapRoleID2Trump.begin();iter != _mapRoleID2Trump.end();iter++)
    {
        //LOG_CRI << "TrumpID = "<<iter->first<< " | qwRoleID = " <<iter->second;
        _mapID2Level.insert(make_pair(iter->first,iter->second));
    }
}

void   CDBWonderPrizeTableManager::GetInfoForFighter(multimap<UINT64,UINT16>& _mapID2Level)
{
    for (auto iter = _mapRoleID2Fighter.begin();iter != _mapRoleID2Fighter.end();iter++)
    {
        //LOG_CRI << "fighterID = "<<iter->first<< " | qwRoleID = " <<iter->second;
        _mapID2Level.insert(make_pair(iter->first,iter->second));
    }
}

void   CDBWonderPrizeTableManager::GetInfoForFormation(multimap<UINT64,UINT16>& _mapID2Level)
{
    for (auto iter = _mapRoleID2Formation.begin();iter != _mapRoleID2Formation.end();iter++)
    {
        //LOG_CRI << "PetID = "<<iter->first<< " | qwRoleID = " <<iter->second;
        _mapID2Level.insert(make_pair(iter->first,iter->second));
    }
}
void   CDBWonderPrizeTableManager::GetInfoForBeauty(multimap<UINT64,UINT16>& _mapID2Level)
{
    for (auto iter = _mapRoleID2Beauty.begin();iter != _mapRoleID2Beauty.end();iter++)
    {
        //LOG_CRI << "PetID = "<<iter->first<< " | qwRoleID = " <<iter->second;
        _mapID2Level.insert(make_pair(iter->first,iter->second));
    }
}
void   CDBWonderPrizeTableManager::GetInfoForHorse(multimap<UINT64,UINT32>& _mapID2Level)
{
    for (auto iter = _mapRoleID2Horse.begin();iter != _mapRoleID2Horse.end();iter++)
    {
        //LOG_CRI << "PetID = "<<iter->first<< " | qwRoleID = " <<iter->second;
        _mapID2Level.insert(make_pair(iter->first,iter->second));
    }
}
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

