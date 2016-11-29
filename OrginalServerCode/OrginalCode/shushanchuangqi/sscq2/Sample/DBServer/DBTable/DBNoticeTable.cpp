#include "DBNoticeTable.h"
#include "DBTableBase.h"
#include "Protocols.h"

CDBNoticeTable g_CDBNoticeTable;

void CDBNoticeTable::AddNotice(const SNotice& sNotice)
{
    mysqlpp::SQLStream sqlstr(NULL);
    sqlstr << "Insert into tblnotice(dwNoticeID, byNoticeType, strContent, dwBeginTime, dwEndTime) Values(";
    sqlstr << (mysqlpp::sql_int_unsigned)sNotice.dwNoticeID;
    sqlstr << "," << (mysqlpp::sql_int_unsigned)sNotice.byNoticeType;
    sqlstr << "," <<mysqlpp::quote << (mysqlpp::sql_char)sNotice.strContent;
    sqlstr << "," << (mysqlpp::sql_int_unsigned)sNotice.dwBeginTime;
    sqlstr << "," << (mysqlpp::sql_int_unsigned)sNotice.dwEndTime;
    sqlstr <<");";
    CDBMgr::Instance().DoMailModifyQuery(sqlstr.str(), NULL, [this, sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){      
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            });
}

void CDBNoticeTable::DelNotice(UINT32 dwNoticeID)
{
    mysqlpp::SQLStream sqlstr(NULL);
    sqlstr << "delete FROM tblnotice WHERE dwNoticeID = " << dwNoticeID;
    sqlstr <<";";

    CDBMgr::Instance().DoMailModifyQuery(sqlstr.str(),NULL, [this, sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){      
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            });
}

void CDBNoticeTable::LoadNotice()
{
   mysqlpp::SQLStream querysql(NULL);
   querysql << "select * from tblnotice"; 
   querysql << ";";
   CDBMgr::Instance().DoMailSelectQuery(querysql.str(), NULL, [this, querysql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;
        
        TVecNotice vecNotice;
        UINT32 dwCount = dataRes.size();
        for (size_t i=0 ; i<dwCount; i++)
        {
            mysqlpp::Row& rRow = dataRes[i];
            SNotice sNotice;
            GET_UINT(dwNoticeID, sNotice.dwNoticeID);
            GET_UTINYINT(byNoticeType, sNotice.byNoticeType);
            GET_STRING_CHAR(strContent, sNotice.strContent);
            GET_UINT(dwBeginTime, sNotice.dwBeginTime);
            GET_UINT(dwEndTime, sNotice.dwEndTime);
            vecNotice.push_back(sNotice);
        }

        g_Center2DBCommS.Send_SendAllNotice(vecNotice);
        });

}

