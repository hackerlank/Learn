#include "DBShipReportManager.h"
#include "DBTableBase.h"
#include "DBRoleMgr.h"
#include "Protocols.h"
CDBShipReportManager g_CDBShipReportManager;
void CDBShipReportManager::AddShipReport(UINT64 qwRoleID,const NShipProt::ShipReport& sData)
{
    SDBRoleData* pRole = CDBRoleMgr::Instance().GetRoleData(qwRoleID);
    if(pRole)//在线
    {
        pRole->vecShipReport.push_back(sData);

    }
    mysqlpp::SQLStream sqlstr(NULL);
    sqlstr << "insert into tbltotalshipreport(qwRoleID,eSource,qwInsID,qwOwer,byOwerColor,wShipId,qwDefense,byDefenseColor,qwRoBId,byRoBColor,qwBattleID,dwFinishTimer,dwTimer,byRobTimes,dwAwardRate) Values(";
    sqlstr << (mysqlpp::sql_bigint_unsigned)(qwRoleID);
    sqlstr << "," << (mysqlpp::sql_tinyint_unsigned)sData.eSource;
    sqlstr << "," << (mysqlpp::sql_bigint_unsigned)sData.qwInsID;
    sqlstr << "," << (mysqlpp::sql_bigint_unsigned)sData.qwOwer;
    sqlstr << "," <<(mysqlpp::sql_tinyint_unsigned)sData.byOwerColor;
    sqlstr << "," <<(mysqlpp::sql_smallint_unsigned)sData.wShipId;
    sqlstr << "," <<(mysqlpp::sql_bigint_unsigned)(sData.qwDefense);
    sqlstr << "," <<(mysqlpp::sql_tinyint_unsigned)sData.byDefenseColor;
    sqlstr << "," <<(mysqlpp::sql_bigint_unsigned)(sData.qwRoBId);
    sqlstr << "," <<(mysqlpp::sql_tinyint_unsigned)sData.byRoBColor;
    sqlstr << "," <<(mysqlpp::sql_bigint_unsigned)(sData.qwBattleID);
    sqlstr << "," <<(mysqlpp::sql_int_unsigned)(sData.dwFinishTimer);
    sqlstr << "," <<(mysqlpp::sql_int_unsigned)(sData.dwTimer);
    sqlstr << "," << (mysqlpp::sql_tinyint_unsigned)sData.byRobTimes; 
    sqlstr << "," << (mysqlpp::sql_int_unsigned)sData.dwAwardRate; 
    sqlstr <<");";
    CDBMgr::Instance().DoMailModifyQuery(sqlstr.str(),NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){      
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            });


}

void CDBShipReportManager::DelShipReport(UINT64 qwRoleID,UINT64 qwInsID)
{
    SDBRoleData* pRole = CDBRoleMgr::Instance().GetRoleData(qwRoleID);
    if(pRole)
    {
        for(auto pos =pRole->vecShipReport.begin() ; pos != pRole->vecShipReport.end();)
        {
            ShipReport &rData = *pos;
            if(rData.qwInsID == qwInsID)
            {
                pos = pRole->vecShipReport.erase(pos);

                continue;
            }
            else
            {
                ++pos;
            }
        }
    }

    mysqlpp::SQLStream sqlstr(NULL);
    sqlstr << "delete from tbltotalshipreport where qwRoleID =";
    sqlstr << (mysqlpp::sql_bigint_unsigned)qwRoleID;
    sqlstr << " and qwInsID = ";
    sqlstr <<  (mysqlpp::sql_int_unsigned)qwInsID;
    sqlstr <<";";
    CDBMgr::Instance().DoMailModifyQuery(sqlstr.str(),NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){      
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            });
}


void CDBShipReportManager::LoadShipReport(UINT64 qwRoleID,QueryShipReportFun fun)
{
    mysqlpp::SQLStream querysql(NULL);
    querysql << "select * from tbltotalshipreport "; 
    querysql << " where qwRoleID =  ";
    querysql << qwRoleID;
    querysql << " order by dwTimer";
    querysql << ";";
    CDBMgr::Instance().DoMailSelectQuery(querysql.str(),NULL,[this,fun,querysql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;
            UINT32 ncount = dataRes.size();
            TVecShipReport vecShipReport;
            for (UINT32 i = 0 ; i< ncount;i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            NShipProt::ShipReport sReportData;
            GET_UBIGINT(qwInsID,sReportData.qwInsID);
            UINT8 bySource;
            GET_UTINYINT(eSource,bySource);
            sReportData.eSource = static_cast<EShipBattleSource>(bySource);
            GET_UBIGINT(qwOwer,sReportData.qwOwer);
            GET_UTINYINT(byOwerColor,sReportData.byOwerColor);
            GET_USMALLINT(wShipId,sReportData.wShipId);
            GET_UBIGINT(qwDefense,sReportData.qwDefense);
            GET_USMALLINT(byDefenseColor,sReportData.byDefenseColor);
            GET_UBIGINT(qwRoBId,sReportData.qwRoBId);
            GET_USMALLINT(byRoBColor,sReportData.byRoBColor);
            GET_UBIGINT(qwBattleID,sReportData.qwBattleID); 
            GET_UINT(dwFinishTimer,sReportData.dwFinishTimer);
            GET_UINT(dwTimer,sReportData.dwTimer);
            GET_UTINYINT(byRobTimes,sReportData.byRobTimes);
            GET_UINT(dwAwardRate,sReportData.dwAwardRate); 
            vecShipReport.push_back(sReportData);
            }
    fun(vecShipReport);
    });

}
