#include "DBLadderRobotManger.h"
#include "Protocols.h"
CDBTotalLadderRobotManager g_CDBTotalLadderRobotManager;
void CDBTotalLadderRobot::InitDataByData(const SLadderRobot & rData)
{
    static_cast<SLadderRobot &>(*this) = const_cast<SLadderRobot&>(rData);
}

bool CDBTotalLadderRobot::UpdateDataByData(const SLadderRobot& newData)
{
    DIFF(wRank);
    return  !_setChanged.none();
}

bool CDBTotalLadderRobot::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into ladderrobot(wMonsterID,wRank) Values(";
    ostr << (mysqlpp::sql_smallint_unsigned)wMonsterID;
    ostr << "," <<(mysqlpp::sql_smallint_unsigned)wRank;
    ostr <<");";
    sqlstr = ostr.str();
    return true;           
}

bool CDBTotalLadderRobot::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE ladderrobot SET";
    UPDATE_USMALLINT_SAME(wRank);
    ostr << " WHERE  wMonsterID =" << wMonsterID <<  ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
    if(pos == string::npos)
        return false;
    strsql[pos+3] = ' ';
    return true;
}

void CDBTotalLadderRobot::ResetChange(void)
{
    _setChanged.reset();
    _bIsNew = false;
}

void CDBTotalLadderRobot::InitDataByDBRow(const mysqlpp::Row &rRow)
{   
    GET_USMALLINT_SAME(wMonsterID);
    GET_USMALLINT_SAME(wRank);

}

void CDBTotalLadderRobotManager::GetAllLadderRobot()
{
    switch(_byLoad)
    {
        case 0:
            {
                _byLoad = 1;
                mysqlpp::SQLStream basesql(NULL);
                basesql << "select *  from ladderrobot;";
                CDBMgr::Instance().DoArenaSelectQuery(basesql.str(),NULL,[this,basesql] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {  
                        LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet ;
                        for(size_t i = 0; i != dataRes.size();i++)
                        {
                        mysqlpp::Row& rRow = dataRes[i];
                        CDBTotalLadderRobot stRobot;
                        stRobot.InitDataByDBRow(rRow);
                        _mapLadderRobotData[stRobot.wMonsterID] = stRobot;
                        }
                        SendAllDataToCenter();
                        _byLoad = 2;
                        });

            }
            break;
        case 1:
            {
                return ;
            }
            break;
        case 2:
            {
                SendAllDataToCenter();
            }
            break;
        default:
            break;
    }

}
void CDBTotalLadderRobotManager::SendAllDataToCenter()
{
    TVecLadderRobot vecData;
    for(auto iter = _mapLadderRobotData.begin(); iter != _mapLadderRobotData.end(); iter++)
    {
        SLadderRobot &rRobot =  static_cast<SLadderRobot&>(iter->second);
        vecData.push_back(rRobot);

    }
    g_Center2DBCommS.Send_SendAllRobot(vecData);  

}

void CDBTotalLadderRobotManager::UpdateData(const SLadderRobot &stData)
{
    auto iter = _mapLadderRobotData.find(stData.wMonsterID);
    if(iter == _mapLadderRobotData.end())
    {
        CDBTotalLadderRobot LadderRobotNew;
        LadderRobotNew.InitDataByData(stData);
        LadderRobotNew.SetNew(true);
        _mapLadderRobotData[stData.wMonsterID] = LadderRobotNew;

    }
    else 
    {
        iter->second.UpdateDataByData(stData);
    }
}

void CDBTotalLadderRobotManager::DumpToDB(bool bForBit)
{
    if(GetUpdataNum() ==0 )
    {
        return ;
    }
    UINT32 nNowQuery = 0;
    UINT32 nMaxQuery = 1000;
    for (auto iter = _mapLadderRobotData.begin();iter != _mapLadderRobotData.end();iter++)
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

UINT32 CDBTotalLadderRobotManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapLadderRobotData.begin();iter != _mapLadderRobotData.end();iter++)
    {
        if (iter->second.IsNew() ||iter->second.IsChange())
        {
            dwOP++;
        } 
    }
    return dwOP ;

}

