#include "DBRoleShipInfo.h"

void DBRoleShipTable::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    ar >> static_cast<PlayerSelfShipData &>(*this);
}


bool DBRoleShipTable::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    PlayerSelfShipData newData;
    ar >> newData;
    DIFF(dwBuyOpenShipTimes); //购买的运船次数
    DIFF(dwBuyRoBShipTimes); //购买的抢劫次数
    DIFF(dwBuyReflushShipTimes);//购买的刷新次数
    DIFF(wReflushShip); //刷出来的船
    DIFF(qwInviteDefense); //邀请的护送者
    DIFF(dwInviteDefenseAgreeTime); //别人同意护送的时间
    DIFF(dwInviteDefensePoint);//被邀请人战斗力
    DIFF(byInviteDefenseLevel);//被邀请人等级
    DIFF(byInviteDefenseColor);//被邀请人颜色
    DIFF(qwAgreeDefenseShipOwer); //我同意护送的船
    DIFF(dwAgreeDefenseShipOwerTime); //我同意护送的时间
    DIFF(dwReflushShipTimer); //刷船时间

    return  !_setChanged.none();
}

bool DBRoleShipTable::GetInsertSqlStr(string& sqlstr)
{

    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblroleshipinfo(qwRoleID,dwBuyOpenShipTimes,dwBuyRoBShipTimes,dwBuyReflushShipTimes,wReflushShip,qwInviteDefense,dwInviteDefenseAgreeTime,dwInviteDefensePoint,byInviteDefenseLevel,byInviteDefenseColor,qwAgreeDefenseShipOwer,dwAgreeDefenseShipOwerTime,dwReflushShipTimer) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwBuyOpenShipTimes;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwBuyRoBShipTimes;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwBuyReflushShipTimes;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)wReflushShip;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)qwInviteDefense;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwInviteDefenseAgreeTime;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwInviteDefensePoint;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byInviteDefenseLevel;
    ostr << ","<< (mysqlpp::sql_tinyint_unsigned)byInviteDefenseColor;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)qwAgreeDefenseShipOwer;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwAgreeDefenseShipOwerTime;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwReflushShipTimer;

    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool DBRoleShipTable::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblroleshipinfo SET";
    UPDATE_UINT_SAME(dwBuyOpenShipTimes); //购买的运船次数
    UPDATE_UINT_SAME(dwBuyRoBShipTimes); //购买的抢劫次数
    UPDATE_UINT_SAME(dwBuyReflushShipTimes);//购买的刷新次数
    UPDATE_USMALLINT_SAME(wReflushShip); //刷出来的船
    UPDATE_UBIGINT_SAME(qwInviteDefense); //邀请的护送者
    UPDATE_UINT_SAME(dwInviteDefenseAgreeTime); //别人同意护送的时间
    UPDATE_UINT_SAME(dwInviteDefensePoint);//被邀请人战斗力
    UPDATE_UTINYINT_SAME(byInviteDefenseLevel);//被邀请人等级
    UPDATE_UTINYINT_SAME(byInviteDefenseColor);//被邀请人颜色
    UPDATE_UBIGINT_SAME(qwAgreeDefenseShipOwer); //我同意护送的船
    UPDATE_UINT_SAME(dwAgreeDefenseShipOwerTime); //我同意护送的时间
    UPDATE_UINT_SAME(dwReflushShipTimer);//刷船时间
    ostr << " WHERE  qwRoleID =" <<_qwRoleID <<  ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void DBRoleShipTable::ResetChange(void)
{
    _setChanged.reset();
}

void DBRoleShipTable::InitDataByDBRow(const mysqlpp::Row &rRow)
{   
    GET_UINT_SAME(dwBuyOpenShipTimes); //购买的运船次数
    GET_UINT_SAME(dwBuyRoBShipTimes); //购买的抢劫次数
    GET_UINT_SAME(dwBuyReflushShipTimes);//购买的刷新次数
    GET_USMALLINT_SAME(wReflushShip); //刷出来的船
    GET_UBIGINT_SAME(qwInviteDefense); //邀请的护送者
    GET_UINT_SAME(dwInviteDefenseAgreeTime); //别人同意护送的时间
    GET_UINT_SAME(dwInviteDefensePoint);//被邀请人战斗力
    GET_UTINYINT_SAME(byInviteDefenseLevel);//被邀请人等级
    GET_UTINYINT_SAME(byInviteDefenseColor);//被邀请人颜色
    GET_UBIGINT_SAME(qwAgreeDefenseShipOwer); //我同意护送的船
    GET_UINT_SAME(dwAgreeDefenseShipOwerTime); //我同意护送的时间
    GET_UINT_SAME(dwReflushShipTimer);//刷船时间
    TableRowBase::InitDataByDBRow(rRow);
}

void DBRoleShipTableManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblroleshipinfo  WHERE qwRoleID = " << qwRoleID << ";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, qwRoleID, queryfun, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblroleshipinfo is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0 &&ncount == 1)
            {
            mysqlpp::Row& rRow = dataRes[0];
            _rShipData.InitDataByDBRow(rRow);
            }
            queryfun(byRet, ncount);
            });
}

void DBRoleShipTableManager::Update(string& strData, bool bIsAdd)
{
    _rShipData.Update(strData,TableRowBase::eInInit == _rShipData.GetDBState());
}

void DBRoleShipTableManager::GetALLInfo(RoleDataInfo & rData)
{
    rData.sShipData = (static_cast<PlayerSelfShipData>(_rShipData));
}

void DBRoleShipTableManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    if (_rShipData.HasOP())
    {
        _rShipData.DumpToDB(_byLine,[fun,this](INT8 byRet) {
                this->_nNowQuery--;
                if (byRet)
                {
                this->_nErrQuery++;
                }
                if (this->_nNowQuery == 0)
                {
                fun(_nMaxQuery,this->_nErrQuery);
                }
                });
    }
}   

UINT32 DBRoleShipTableManager::GetUpdataNum()
{
    return _rShipData.HasOP() ? 1 : 0;

}
DBRoleShipTableManager::DBRoleShipTableManager(UINT64 setqwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeShip, setqwRoleID,byLine), _rShipData(setqwRoleID),_nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}


