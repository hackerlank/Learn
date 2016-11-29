#include "DBGuildExchangedItemTable.h"
#include "DBTableBase.h"
#include "Protocols.h"
#include "Center2DBGuildS.h"

CDBGuildExchangedItemTable g_CDBGuildExchangedItemTable;

void CDBGuildExchangedItemTable::AddGuildExchangedItem(const SGuildExchangedItem& sGuildExchangedItem)
{
    mysqlpp::SQLStream sqlstr(NULL);
    sqlstr << "Insert into tblguildexchangeditem(qwGuildID, dwExchangeID, dwCount) Values(";
    sqlstr << (mysqlpp::sql_bigint_unsigned)sGuildExchangedItem.qwGuildID;
    sqlstr << "," << (mysqlpp::sql_int_unsigned)sGuildExchangedItem.dwExchangeID;
    sqlstr << "," << (mysqlpp::sql_int_unsigned)sGuildExchangedItem.dwCount;
    sqlstr <<");";
    CDBMgr::Instance().DoMailModifyQuery(sqlstr.str(), NULL, [this, sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){      
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            });
}

void CDBGuildExchangedItemTable::UpdateGuildExchangedItem(const SGuildExchangedItem& sGuildExchangedItem)
{
    mysqlpp::SQLStream sqlstr(NULL);
    sqlstr << "UPDATE tblguildexchangeditem SET";
    sqlstr << " dwCount = " << sGuildExchangedItem.dwCount;
    sqlstr << " WHERE qwGuildID = " << sGuildExchangedItem.qwGuildID;
    sqlstr << " AND dwExchangeID = " << sGuildExchangedItem.dwExchangeID;
    sqlstr << ";"; 
    CDBMgr::Instance().DoMailModifyQuery(sqlstr.str(), NULL, [this, sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){      
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            });
}

void CDBGuildExchangedItemTable::DelGuildExchangedItem()
{
    mysqlpp::SQLStream sqlstr(NULL);
    sqlstr << "delete FROM tblguildexchangeditem";
    sqlstr <<";";

    CDBMgr::Instance().DoMailModifyQuery(sqlstr.str(),NULL, [this, sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){      
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            });
}

void CDBGuildExchangedItemTable::LoadGuildExchangedItem()
{
   mysqlpp::SQLStream querysql(NULL);
   querysql << "select * from tblguildexchangeditem"; 
   querysql << ";";
   CDBMgr::Instance().DoMailSelectQuery(querysql.str(), NULL, [this, querysql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;
        
    TVecGuildExchangedItem vecGuildExchangedItem;
    UINT32 dwCnt = dataRes.size();
    for (size_t i=0 ; i<dwCnt; i++)
    {
        mysqlpp::Row& rRow = dataRes[i];
        SGuildExchangedItem sGuildExchangedItem;
        GET_BIGINT(qwGuildID, sGuildExchangedItem.qwGuildID);
        GET_UINT(dwExchangeID, sGuildExchangedItem.dwExchangeID);
        GET_UINT(dwCount, sGuildExchangedItem.dwCount);
        
        vecGuildExchangedItem.push_back(sGuildExchangedItem);
    }

    g_Center2DBGuildS.Send_SendAllGuildExchangedItem(vecGuildExchangedItem);
    });
}

