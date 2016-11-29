#include "DBShipManger.h"
#include "Protocols.h"
CDBTotalShipManager g_CDBTotalShipManager;
void CDBTotalShip::InitDataByData(const PlayerShip& rInData)
{
    static_cast<PlayerShip &>(*this) = const_cast<PlayerShip&>(rInData);
}

bool CDBTotalShip::UpdateDataByData(const PlayerShip& newData)
{
    DIFF(dwOwerPoint); //金船拥有者战斗力
    DIFF(byOwerLevel); //拥有者等级
    DIFF(byOwerColor); //拥有者颜色
    DIFF(byChannel); //航道
    DIFF(wShipId); //金船模板
    DIFF(qwDefense); //护送者ID
    DIFF(dwDefensePoint); //护送者战斗力
    DIFF(byDefenseLevel); //护送者等级
    DIFF(byDefenseColor); //护送者颜色
    DIFF(qwRoBId1); //打劫者1
    DIFF(byRoB1Color); //打劫者1颜色
    DIFF(dwRoB1Point);//打劫者1战斗力
    DIFF(byRoB1Level);//打劫者1等级
    DIFF(qwRoBId2); //打劫者2
    DIFF(byRoB2Color); //打劫者2颜色
    DIFF(dwRoB2Point);//打劫者2战斗力
    DIFF(byRoB2Level);//打劫者2等级
    DIFF(qwRoBId3); //打劫者3
    DIFF(byRoB3Color); //打劫者3颜色
    DIFF(dwRoB3Point);//打劫者3战斗力
    DIFF(byRoB3Level);//打劫者3等级
    DIFF(dwBeginTimer); //开船时间
    DIFF(dwEndTimer); //结束时间
    DIFF(dwAwardRate);//倍率
    return  !_setChanged.none();
}

bool CDBTotalShip::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tbltotalship(qwInsID,qwOwer,dwOwerPoint,byOwerLevel,byOwerColor,byChannel,wShipId,qwDefense,dwDefensePoint,byDefenseLevel,byDefenseColor,qwRoBId1, byRoB1Color,dwRoB1Point,byRoB1Level,qwRoBId2,byRoB2Color,dwRoB2Point,byRoB2Level,qwRoBId3,byRoB3Color,dwRoB3Point,byRoB3Level,dwBeginTimer,dwEndTimer,dwAwardRate) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)qwInsID;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)qwOwer; 
    ostr << "," << (mysqlpp::sql_int_unsigned)dwOwerPoint;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byOwerLevel;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byOwerColor;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byChannel;
    ostr << "," << (mysqlpp::sql_smallint_unsigned)wShipId;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)qwDefense;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwDefensePoint;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byDefenseLevel;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byDefenseColor;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)qwRoBId1;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byRoB1Color;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwRoB1Point;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byRoB1Level;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)qwRoBId2;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byRoB2Color;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwRoB2Point;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byRoB2Level;
    ostr << "," << (mysqlpp::sql_bigint_unsigned)qwRoBId3;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byRoB3Color;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwRoB3Point;
    ostr << "," << (mysqlpp::sql_tinyint_unsigned)byRoB3Level;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwBeginTimer;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwEndTimer;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwAwardRate;
    ostr <<");";
    sqlstr = ostr.str();
    return true;           
}

bool CDBTotalShip::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tbltotalship SET";
    UPDATE_UINT_SAME(dwOwerPoint); //金船拥有者战斗力
    UPDATE_UTINYINT_SAME(byOwerLevel); //拥有者等级
    UPDATE_UTINYINT_SAME(byOwerColor); //拥有者颜色
    UPDATE_UTINYINT_SAME(byChannel); //航道
    UPDATE_USMALLINT_SAME(wShipId); //金船模板
    UPDATE_UBIGINT_SAME(qwDefense); //护送者ID
    UPDATE_UINT_SAME(dwDefensePoint); //护送者战斗力
    UPDATE_UTINYINT_SAME(byDefenseLevel); //护送者等级
    UPDATE_UTINYINT_SAME(byDefenseColor); //护送者颜色
    UPDATE_UBIGINT_SAME(qwRoBId1); //打劫者1
    UPDATE_UTINYINT_SAME(byRoB1Color); //打劫者1颜色
    UPDATE_UINT_SAME(dwRoB1Point);//打劫者1战斗力
    UPDATE_UTINYINT_SAME(byRoB1Level);//打劫者1等级
    UPDATE_UBIGINT_SAME(qwRoBId2); //打劫者2
    UPDATE_UTINYINT_SAME(byRoB2Color); //打劫者2颜色
    UPDATE_UINT_SAME(dwRoB2Point);//打劫者2战斗力
    UPDATE_UTINYINT_SAME(byRoB2Level);//打劫者2等级
    UPDATE_UBIGINT_SAME(qwRoBId3); //打劫者3
    UPDATE_UTINYINT_SAME(byRoB3Color); //打劫者3颜色
    UPDATE_UINT_SAME(dwRoB3Point);//打劫者3战斗力
    UPDATE_UTINYINT_SAME(byRoB3Level);//打劫者3等级
    UPDATE_UINT_SAME(dwBeginTimer); //开船时间
    UPDATE_UINT_SAME(dwEndTimer); //结束时间
    UPDATE_UINT_SAME(dwAwardRate);//倍率

    ostr << " WHERE  qwInsID =" <<qwInsID <<  ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBTotalShip::ResetChange(void)
{
    _setChanged.reset();
    _bIsNew = false;
}

void CDBTotalShip::InitDataByDBRow(const mysqlpp::Row &rRow)
{   
    GET_UBIGINT_SAME(qwInsID);
    GET_UBIGINT_SAME(qwOwer); 
    GET_UINT_SAME(dwOwerPoint); //金船拥有者战斗力
    GET_UTINYINT_SAME(byOwerLevel); //拥有者等级
    GET_UTINYINT_SAME(byOwerColor); //拥有者颜色
    GET_UTINYINT_SAME(byChannel); //航道
    GET_USMALLINT_SAME(wShipId); //金船模板
    GET_UBIGINT_SAME(qwDefense); //护送者ID
    GET_UINT_SAME(dwDefensePoint); //护送者战斗力
    GET_UTINYINT_SAME(byDefenseLevel); //护送者等级
    GET_UTINYINT_SAME(byDefenseColor); //护送者颜色
    GET_UBIGINT_SAME(qwRoBId1); //打劫者1
    GET_UTINYINT_SAME(byRoB1Color); //打劫者1颜色
    GET_UINT_SAME(dwRoB1Point);//打劫者1战斗力
    GET_UTINYINT_SAME(byRoB1Level);//打劫者1等级
    GET_UBIGINT_SAME(qwRoBId2); //打劫者2
    GET_UTINYINT_SAME(byRoB2Color); //打劫者2颜色
    GET_UINT_SAME(dwRoB2Point);//打劫者2战斗力
    GET_UTINYINT_SAME(byRoB2Level);//打劫者2等级
    GET_UBIGINT_SAME(qwRoBId3); //打劫者3
    GET_UTINYINT_SAME(byRoB3Color); //打劫者3颜色
    GET_UINT_SAME(dwRoB3Point);//打劫者3战斗力
    GET_UTINYINT_SAME(byRoB3Level);//打劫者3等级
    GET_UINT_SAME(dwBeginTimer); //开船时间
    GET_UINT_SAME(dwEndTimer); //结束时间
    GET_UINT_SAME(dwAwardRate); //倍率


}

void CDBTotalShipManager::QueryData(UINT32 dwPageSize,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    UINT64 qwLoadTimer = GetTickCount();
    basesql << "select count(*) as dwCount from tbltotalship;";
    CDBMgr::Instance().DoMailSelectQuery(basesql.str(),NULL,[this, queryfun, basesql,dwPageSize,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {  
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
                querysql << "SELECT * FROM tbltotalship"; 
                querysql << " WHERE qwInsID >= (SELECT qwInsID FROM tbltotalship LIMIT ";
                querysql << dwPage*dwPageSize;
                querysql << " ,1) LIMIT ";
                querysql << dwPageSize;
                querysql << ";";
                CDBMgr::Instance().DoMailSelectQuery(querysql.str(),NULL,[this,dwCount, queryfun, querysql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
                        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << querysql.str() << "result:" << byRet ;
                        UINT32 ncount = dataRes.size();
                        for(UINT32 i = 0; i< ncount; ++i)
                        {
                        mysqlpp::Row& rRow = dataRes[i];
                        CDBTotalShip ShipTable;
                        ShipTable.InitDataByDBRow(rRow);
                        _mapRoleShipData[ShipTable.qwInsID]= ShipTable;
                        }
                        if(_mapRoleShipData.size() == dwCount)
                        {
                        queryfun(byRet, dwCount);
                        LOG_INF<<"--------Load tbltotalship is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
                        }
                        });
            }


    });

}

void CDBTotalShipManager::UpdateData(const PlayerShip &testData)
{
    auto iter = _mapRoleShipData.find(testData.qwInsID);
    if(iter == _mapRoleShipData.end())
    {
        CDBTotalShip ShipNew;
        ShipNew.InitDataByData(testData);
        ShipNew.SetNew(true);
        _mapRoleShipData[ShipNew.qwInsID] = ShipNew;

    }
    else 
    {
        iter->second.UpdateDataByData(testData);
    }
}

void CDBTotalShipManager::DumpToDB(bool bForBit)
{
    if(GetUpdataNum() ==0 )
    {
        return ;
    }
    UINT32 nNowQuery = 0;
    UINT32 nMaxQuery = 1000;
    UINT32 nDelNum = _vecDelShip.size();
    for (auto deliter = _vecDelShip.begin();deliter != _vecDelShip.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tbltotalship where qwInsID="<<*deliter <<  ";";
        CDBMgr::Instance().DoMailModifyQuery(sqlstr.str(),NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){      
                LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
                });
    }
    _vecDelShip.clear();
    if(nDelNum >= nMaxQuery && !bForBit)
    {
        return ;
    }
    nNowQuery = nDelNum;

    for (auto iter = _mapRoleShipData.begin();iter != _mapRoleShipData.end();iter++)
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
            CDBMgr::Instance().DoMailModifyQuery(sqlstr,NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
                    LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr << "result:" << byRet;
                    });
        }
        else if(iter->second.IsChange())
        {
            string sqlstr;
            iter->second.GetUpdateSqlStr(sqlstr);
            CDBMgr::Instance().DoMailModifyQuery(sqlstr,NULL, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){
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

UINT32 CDBTotalShipManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleShipData.begin();iter != _mapRoleShipData.end();iter++)
    {
        if (iter->second.IsNew() ||iter->second.IsChange())
        {
            dwOP++;
        } 
    }
    return dwOP + _vecDelShip.size();

}

void CDBTotalShipManager::DelData(UINT64 qwInsID)
{
    auto iter = _mapRoleShipData.find(qwInsID);
    if (iter != _mapRoleShipData.end())
    {
        if(!iter->second.IsNew())
        {
            _vecDelShip.push_back(qwInsID);
        }
        _mapRoleShipData.erase(qwInsID);
    }
}

void CDBTotalShipManager::GetAllShip(UINT32 dwPageSize)
{
    QueryData(dwPageSize,[dwPageSize,this](INT8 byRet,UINT32 dwTotalSize)
            {
            UINT32 dwTotalPage = dwTotalSize/dwPageSize;//总页数
            if(dwTotalSize%dwPageSize != 0)
            {
            dwTotalPage++;
            }
            SendDataToCenter(dwTotalPage,dwPageSize);
            return ;
            });
}

void CDBTotalShipManager::SendDataToCenter(UINT32 dwTotalPage,UINT32 dwPageSize)
{

    UINT32 dwPageNum = 0;
    TVecPlayerShip vecSendData;
    if(dwTotalPage == 0)
    {
        g_Center2DBCommS.Send_SendAllShip(dwPageNum,dwTotalPage,vecSendData);
        return ;
    }
    for(auto iter = _mapRoleShipData.begin();iter != _mapRoleShipData.end();iter++)
    {
        PlayerShip rData = static_cast<PlayerShip>(iter->second);
        vecSendData.push_back(rData);
        if(vecSendData.size() == dwPageSize)
        {
            dwPageNum++;
            g_Center2DBCommS.Send_SendAllShip(dwPageNum,dwTotalPage,vecSendData);
            vecSendData.clear();
        }
    }
    if(!vecSendData.empty())
    {
        dwPageNum++;
        g_Center2DBCommS.Send_SendAllShip(dwPageNum,dwTotalPage,vecSendData);
    }
    if(dwPageNum != dwTotalPage)
    {
        LOG_CRI <<"GetAllShip ERR";
    }
}

