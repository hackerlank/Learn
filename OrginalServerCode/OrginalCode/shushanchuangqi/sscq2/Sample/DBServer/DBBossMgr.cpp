
#include "stdafx.h"
#include "Protocols.h"
#include "DBBossMgr.h"
#include "DBTableBase.h"
#include "DBMgr.h"

void CDBBossMgr::LoadWorldBoss(shared_func<CGame2DBCommSvr::SLoadWorldBossInfoAck>& fnAck)
{
    for(auto itr = _vecWorldBossInfo.begin(); itr != _vecWorldBossInfo.end(); ++itr)
    {
        fnAck->vecWorldBossInfo.push_back(*itr);
    }

    //LOG_CRI<<"LoadWorldBoss query:"<<fnAck->vecWorldBossInfo.size();

   //fnAck(true);
}
void CDBBossMgr::Init()
{
    mysqlpp::SQLStream sql(NULL);
    sql << "SELECT * FROM tblworldboss;";
    CDBMgr::Instance().DoSelectQuery(sql.str(), NULL, [this](INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        for (size_t i = 0; i < dataRes.size(); ++i)
        {
            SWBossDBInfo sBossInfo;
            mysqlpp::Row& rRow = dataRes[i];
            GET_USMALLINT(wBossID, sBossInfo.wBossID);
            GET_USMALLINT(dwLast, sBossInfo.dwLast);
            GET_UINT(dwHP, sBossInfo.dwHP);
            GET_UINT(dwAtk, sBossInfo.dwAtk);
            GET_UINT(dwMAtk, sBossInfo.dwMAtk);
            GET_UINT(dwLastEndTime,sBossInfo.dwLastEndTime);
            this->Insert(sBossInfo);
            LOG_INF<<"LOAD tblworldboss!!!";

        }
        Config.SetPreLoad(eLoadBoss);
    });

}
void CDBBossMgr::Insert(const SWBossDBInfo& sBossInfo)
{
    _vecWorldBossInfo.push_back(sBossInfo);
}
void CDBBossMgr::SaveWorldBoss(const SWBossDBInfo& sBossInfo)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "REPLACE INTO tblworldboss (wBossID, dwLast, dwHP, dwAtk, dwMAtk,dwLastEndTime) VALUES ("
        << sBossInfo.wBossID << ","
        << sBossInfo.dwLast << ","
        << sBossInfo.dwHP << ","
        << sBossInfo.dwAtk << ","
        << sBossInfo.dwMAtk <<","
        << sBossInfo.dwLastEndTime
        << ");";
    CDBMgr::Instance().DoModifyQuery(ostr.str(), NULL, [ostr](INT8 byRet, mysqlpp::SimpleResult& simRes){
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << ostr.str() << "result:" << byRet;
    });
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

