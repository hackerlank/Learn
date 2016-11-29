#include "DBOffLineEventManager.h"
#include "DBTableBase.h"
#include "DBRoleMgr.h"
#include "Protocols.h"
CDBOffLineEventManager g_CDBOffLineEventManager;
void CDBOffLineEventManager::AddOffLineEvent(UINT8 byServerType,const TVecUINT64& vecRoleID,const NRoleInfoDefine::SEventOffLine& sEvent)
{
    NRoleInfoDefine::SEventOffLine sEventData = sEvent;
    sEventData.byServerType = byServerType;
    assert(sEventData.dwEventType != 0);

    for(auto it = vecRoleID.begin();it != vecRoleID.end();it++)
    {
        SDBRoleData* pRole = CDBRoleMgr::Instance().GetRoleData(*it);
        if(pRole)
        {
            bool bFind = false;
            for(size_t pos =0 ; pos != pRole->vecEventOffLine.size();pos++)
            {
                SEventOffLine &rEvent = pRole->vecEventOffLine[pos];
                if(rEvent.byServerType == sEventData.byServerType && rEvent.dwEventType == sEventData.dwEventType)
                {

                    LOG_DBG << sEventData.dwEventType << "RelapceEvent";
                    bFind = true;
                    rEvent = sEventData;
                    break;
                }

            }
            if(!bFind)
            {
                LOG_DBG << sEventData.dwEventType << "InsertEvent";
                pRole->vecEventOffLine.push_back(sEventData);
            }
        }
    }
    for(auto it = vecRoleID.begin();it != vecRoleID.end();it++)
    {
        LOG_INF << sEventData.dwEventType << "ADDEvent";
        UINT64 qwRoleId = *it;
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "replace  into tbltotaloffevent(qwRoleID,dwEventType,byServerType,strParam1,strParam2,dwTime) Values(";
        sqlstr << (mysqlpp::sql_bigint_unsigned)(*it);
        sqlstr << "," << (mysqlpp::sql_int_unsigned)sEventData.dwEventType;
        sqlstr << "," << (mysqlpp::sql_tinyint_unsigned)sEventData.byServerType;
        sqlstr << "," <<mysqlpp::quote << (mysqlpp::sql_char)sEventData.strParam1;
        sqlstr << "," <<mysqlpp::quote << (mysqlpp::sql_char)sEventData.strParam2;
        sqlstr << "," << (mysqlpp::sql_int_unsigned)sEventData.dwTime;

        sqlstr <<");";
        CDBMgr::Instance().DoMailModifyQuery(sqlstr.str(),NULL, [this,sqlstr,sEventData,qwRoleId](INT8 byRet, mysqlpp::SimpleResult& simRes){      
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
                //如果玩家在线，发一个更新消息
                SDBRoleData* pRole = CDBRoleMgr::Instance().GetRoleData(qwRoleId);
                if(pRole && pRole->GetUserState() == eUserInGame)
                {
                g_Game2DBCommS.SendSvr_NewOffEventNotice(&pRole->nServerId, 1,qwRoleId,sEventData);
                }
                });
    }


}
void CDBOffLineEventManager::DelOffLineEvent(UINT64 qwRoleID,const NRoleInfoDefine::TVecEventOffLine& vecEventType)
{
    SDBRoleData* pRole = CDBRoleMgr::Instance().GetRoleData(qwRoleID);
    if(pRole)
    {
        for(auto it = vecEventType.begin();it != vecEventType.end();it++)
        {
            for(auto pos =pRole->vecEventOffLine.begin() ; pos != pRole->vecEventOffLine.end();)
            {
                SEventOffLine &rEvent = *pos;
                const SEventOffLine &rDel = *it;
                if(rEvent.byServerType == rDel.byServerType && rEvent.dwEventType == rDel.dwEventType)
                {
                    pos = pRole->vecEventOffLine.erase(pos);
                    LOG_DBG << (*it).dwEventType << "Erase Event";
                }
                else
                {
                    ++pos;
                }

            }
        }
    }

    for(auto it = vecEventType.begin();it != vecEventType.end();it++)
    {
        LOG_DBG << (*it).dwEventType << "Del Event";
        const SEventOffLine &rDel = *it;
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr << "delete from tbltotaloffevent where qwRoleID =";
        sqlstr << (mysqlpp::sql_bigint_unsigned)qwRoleID;
        sqlstr << " and dwEventType = ";
        sqlstr <<  (mysqlpp::sql_int_unsigned)rDel.dwEventType;
        sqlstr << " and byServerType = ";  
        sqlstr <<  (mysqlpp::sql_tinyint_unsigned)rDel.byServerType;
        sqlstr <<";";
        CDBMgr::Instance().DoMailModifyQuery(sqlstr.str(),NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){      
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
                });
    }



}
void CDBOffLineEventManager::LoadOffLineEvent(UINT64 qwRoleID,QueryOffEventFun fun)
{
    mysqlpp::SQLStream querysql(NULL);
    querysql << "select * from tbltotaloffevent"; 
    querysql << " where qwRoleID =  ";
    querysql << qwRoleID;
    querysql << ";";
    CDBMgr::Instance().DoMailSelectQuery(querysql.str(),NULL,[this,fun,querysql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;
            UINT32 ncount = dataRes.size();
            TVecEventOffLine vecEventOffLine;
            for (UINT32 i = 0 ; i< ncount;i++)
            {
            mysqlpp::Row& rRow = dataRes[i];
            NRoleInfoDefine::SEventOffLine sEventData;
            GET_UTINYINT(byServerType,sEventData.byServerType);
            GET_UINT(dwEventType,sEventData.dwEventType);
            GET_UINT(dwTime,sEventData.dwTime);
            GET_STRING_CHAR(strParam1,sEventData.strParam1);
            GET_STRING_CHAR(strParam2,sEventData.strParam2);
            vecEventOffLine.push_back(sEventData);
            LOG_DBG << sEventData.dwEventType << "Load Event";
            }
            fun(vecEventOffLine);
            });

}
