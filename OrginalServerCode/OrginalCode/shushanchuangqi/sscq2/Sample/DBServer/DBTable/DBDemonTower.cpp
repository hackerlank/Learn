#include "DBDemonTower.h"
void CDBDemonTowerPlayer::InitDataByStr(string& strData)
{
    SDemonTowerPlayer oData;
    CInArchive ar(strData);
    ar>>oData;
    Copy(&oData);    
    _qwRoleID = oData.qwRoleID;

}

bool CDBDemonTowerPlayer::UpdateDataByStr(string& strData)
{

    SDemonTowerPlayer oData;
    CInArchive ar(strData);
    ar>>oData;
    SDemonTowerPlayerEx newData;
    newData.Copy(&oData);
    
   DIFF(qwUserID);
   DIFF(qwRoleID);
   DIFF(strRoleName);
   DIFF(bySex);
   DIFF(byLevel);
   DIFF(dwFloorID);
   DIFF(dwGuardFloorID);
   DIFF(dwGuardPos);
   DIFF(dwGuardStartTime);
   DIFF(dwGuardEndTime);
   DIFF(dwGuardNextPrizeTime);
   DIFF(dwGuardNextReduceRateTime);
   DIFF(dwGuardGatherSpeed);
   DIFF(dwGuardGatherSpeedEndTimer); 
   DIFF(dwGuardReduceRate);
   DIFF(dwGuardNextAttackTime);
   DIFF(dwPower);
   DIFF(sFailSoulPrize);
   DIFF(sDaySoulPrize);
   DIFF(sGatherSoulPrize);
   DIFF(byColor);
     
    bool bUpdate = !_setChanged.none();
    return bUpdate;
}

bool CDBDemonTowerPlayer::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tbldemontower(qwUserID,qwRoleID,strRoleName,bySex,byLevel,dwFloorID,dwGuardFloorID,dwGuardPos,dwGuardStartTime";
    ostr << ",dwGuardEndTime";
    ostr << ",dwGuardNextPrizeTime";
    ostr << ",dwGuardNextReduceRateTime";
    ostr << ",dwGuardGatherSpeed";
    ostr << ",dwGuardGatherSpeedEndTimer";
    ostr << ",dwGuardReduceRate";
    ostr << ",dwGuardNextAttackTime";
    ostr << ",dwPower";
    ostr << ",sFailSoulPrize,sDaySoulPrize,sGatherSoulPrize";
    ostr << ",byColor";
    ostr << ") Values(";
    ostr<< (mysqlpp::sql_bigint_unsigned)qwUserID;
    ostr<<","<<(mysqlpp::sql_bigint_unsigned)qwRoleID;
    ostr<<","<<"'"<< (mysqlpp::sql_char)strRoleName<<"'";
    ostr<<"," << (mysqlpp::sql_int_unsigned)bySex;
    ostr<<"," << (mysqlpp::sql_int_unsigned)byLevel;
    ostr<<"," << (mysqlpp::sql_int_unsigned)dwFloorID;
    ostr<<"," << (mysqlpp::sql_int_unsigned)dwGuardFloorID;
    ostr<<"," << (mysqlpp::sql_int_unsigned)dwGuardPos;
    ostr<<"," << (mysqlpp::sql_int_unsigned)dwGuardStartTime;
    ostr<<"," << (mysqlpp::sql_int_unsigned)dwGuardEndTime;
    ostr<<"," << (mysqlpp::sql_int_unsigned)dwGuardNextPrizeTime;
    ostr<<"," << (mysqlpp::sql_int_unsigned)dwGuardNextReduceRateTime;
    ostr<<"," << (mysqlpp::sql_int_unsigned)dwGuardGatherSpeed;
    ostr<<"," << (mysqlpp::sql_int_unsigned)dwGuardGatherSpeedEndTimer;
    ostr<<"," << (mysqlpp::sql_int_unsigned)dwGuardReduceRate;
    ostr<<"," << (mysqlpp::sql_int_unsigned)dwGuardNextAttackTime;
    ostr<<"," << (mysqlpp::sql_int_unsigned)dwPower;
    ostr<<"," <<"'"<< (mysqlpp::sql_char)sFailSoulPrize<<"'";
    ostr<<"," <<"'"<< (mysqlpp::sql_char)sDaySoulPrize<<"'";
    ostr<<"," <<"'"<< (mysqlpp::sql_char)sGatherSoulPrize<<"'";
    ostr<<"," << (mysqlpp::sql_int_unsigned)byColor;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBDemonTowerPlayer::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tbldemontower SET";
    UPDATE_UBIGINT_SAME(qwUserID);
    UPDATE_STRING_CHAR_SAME(strRoleName);
    UPDATE_UINT_SAME(bySex);
    UPDATE_UINT_SAME(byLevel);
    UPDATE_UINT_SAME(dwFloorID);
    UPDATE_UINT_SAME(dwGuardFloorID);
    UPDATE_UINT_SAME(dwGuardPos);
    UPDATE_UINT_SAME(dwGuardStartTime);
    UPDATE_UINT_SAME(dwGuardEndTime);
    UPDATE_UINT_SAME(dwGuardNextPrizeTime);
    UPDATE_UINT_SAME(dwGuardNextReduceRateTime);
    UPDATE_UINT_SAME(dwGuardGatherSpeed);
    UPDATE_UINT_SAME(dwGuardGatherSpeedEndTimer); 
    UPDATE_UINT_SAME(dwGuardReduceRate);
    UPDATE_UINT_SAME(dwGuardNextAttackTime);
    UPDATE_UINT_SAME(dwPower);
    UPDATE_STRING_CHAR_SAME(sFailSoulPrize);
    UPDATE_STRING_CHAR_SAME(sDaySoulPrize);
    UPDATE_STRING_CHAR_SAME(sGatherSoulPrize);
    UPDATE_UINT_SAME(byColor);
    ostr << " WHERE  qwRoleID =" <<_qwRoleID <<  ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
if(pos == string::npos)
    return false;
    strsql[pos+3] = ' ';
    return true;
    }

void CDBDemonTowerPlayer::ResetChange(void)
{
    _setChanged.reset();
}

void CDBDemonTowerPlayer::InitDataByDBRow(const mysqlpp::Row &rRow)
{   
    GET_UBIGINT_SAME(qwRoleID);
    GET_UBIGINT_SAME(qwUserID);
    GET_STRING_CHAR_SAME(strRoleName);
    GET_UINT_SAME(bySex);
    GET_UINT_SAME(byLevel);
    GET_UINT_SAME(dwFloorID);
    GET_UINT_SAME(dwGuardFloorID);
    GET_UINT_SAME(dwGuardPos);
    GET_UINT_SAME(dwGuardStartTime);
    GET_UINT_SAME(dwGuardEndTime);
    GET_UINT_SAME(dwGuardNextPrizeTime);
    GET_UINT_SAME(dwGuardNextReduceRateTime);
    GET_UINT_SAME(dwGuardGatherSpeed);
    GET_UINT_SAME(dwGuardGatherSpeedEndTimer); 
    GET_UINT_SAME(dwGuardReduceRate);
    GET_UINT_SAME(dwGuardNextAttackTime);
    GET_UINT_SAME(dwPower);
    GET_STRING_CHAR_SAME(sFailSoulPrize);
    GET_STRING_CHAR_SAME(sDaySoulPrize);
    GET_STRING_CHAR_SAME(sGatherSoulPrize);
    GET_UINT_SAME(dwGuardGatherSpeed);
    GET_UINT_SAME(dwGuardGatherSpeedEndTimer);
    GET_UINT_SAME(dwGuardReduceRate);
    GET_UINT_SAME(byColor);
   
  
    TableRowBase::InitDataByDBRow(rRow);
    _qwRoleID=qwRoleID;

    }

void CDBDemonTowerPlayerManager::QueryData()
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tbldemontower;";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, basesql,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tbldemontower is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0 && ncount >=1)
            {

                for(size_t i = 0; i < ncount; ++i)
                {
                    mysqlpp::Row& rRow = dataRes[i];
                    CDBDemonTowerPlayer oTable(0);
                    oTable.InitDataByDBRow(rRow);
                    oTable.StrToVec();
                    _mapDemonTowerPlayer[oTable.qwRoleID]= oTable;
                }
            }
            if(byRet == 0)
              Config.SetPreLoad(eLoadDemonTower);
            //queryfun(byRet, ncount);
            });
}


void CDBDemonTowerPlayerManager::Update(const SDemonTowerPlayer& oData)
{
    SDemonTowerPlayerEx newData; 
    newData.Copy(&oData);        

    string strData;          
    COutArchive iar(strData);
    iar << oData;       

    auto iter = _mapDemonTowerPlayer.find(newData.qwRoleID);
    if (iter == _mapDemonTowerPlayer.end())
    {
        CDBDemonTowerPlayer oDemonTowerPlayerNew(newData.qwRoleID);
        oDemonTowerPlayerNew.Update(strData, true);
        _mapDemonTowerPlayer[newData.qwRoleID] = oDemonTowerPlayerNew;
    }
    else if(iter != _mapDemonTowerPlayer.end())
    {
        iter->second.Update(strData,false);
    }
}



void CDBDemonTowerPlayerManager::DumpToDB()
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDeleteDemonTowerPlayer.begin();deliter != _vecDeleteDemonTowerPlayer.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tbldemontower WHERE  qwRoleID="<<(*deliter) <<  ";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){                              
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
            {
                this->_nErrQuery++;
                LOG_INF<<"CDBDemonTowerPlayerManager::DumpToDB delete Error\n";
            }
            else
            {
               // LOG_INF<<"CDBDemonTowerPlayerManager::DumpToDB delete Error\n";
            }
            //if (this->_nNowQuery == 0)
            //{
            //    fun(this->_nMaxQuery,this->_nErrQuery);
            //}
        });
    }
    _vecDeleteDemonTowerPlayer.clear();
    for (auto iter =_mapDemonTowerPlayer.begin();iter !=_mapDemonTowerPlayer.end();iter++)
    {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDB(_byLine,[this](INT8 byRet) {
                this->_nNowQuery--;
                if (byRet)
                {
                    this->_nErrQuery++;
                    LOG_INF<<"CDBDemonTowerPlayerManager::DumpToDB update Error\n";
                }
                else
                {
                    //LOG_INF<<"CDBDemonTowerPlayerManager::DumpToDB update sucess\n";
                }
                //if (this->_nNowQuery == 0)
               // {
                 //   fun(_nMaxQuery,this->_nErrQuery);
               // }i
            });
        }
    }   


}

UINT32 CDBDemonTowerPlayerManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapDemonTowerPlayer.begin();iter != _mapDemonTowerPlayer.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP +_vecDeleteDemonTowerPlayer.size();

}

void CDBDemonTowerPlayerManager::GetALLInfo(TVecDemonTowerPlayer& VecDemonTowerPlayer)
{
    for (auto iter = _mapDemonTowerPlayer.begin();iter != _mapDemonTowerPlayer.end();iter++)
    {
        SDemonTowerPlayer oDemonTowerPlayer;
        iter->second.CopyTo(oDemonTowerPlayer);
        VecDemonTowerPlayer.push_back(oDemonTowerPlayer);                                                                         
    }                                                                                   
}                                                                                       

void CDBDemonTowerPlayerManager::DelData(const SDemonTowerPlayer& oData)
{
                                 
     SDemonTowerPlayerEx deleteData;
     deleteData.Copy(&oData);       
   
    auto iter = _mapDemonTowerPlayer.find(deleteData.qwRoleID);
    if (iter != _mapDemonTowerPlayer.end())
    {
        if(iter->second.IsInDB())
        {
           _vecDeleteDemonTowerPlayer.push_back(deleteData.qwRoleID);
        }
        _mapDemonTowerPlayer.erase(deleteData.qwRoleID);
    }
}

