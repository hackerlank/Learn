#include "DBRoleArena.h"
void CDBRoleArena::InitDataByStr(string & strData)
{
    CInArchive ar(strData);
    ar >> static_cast<SRoleArenaInfo &>(*this);

}
void CDBRoleArena::DiffAward(const TVecArenaAward &rVecAward)
{
#define DIFFAWARD(byIndex,bySign) do {                  \
    if (GetAwardIDByIndex(rVecAward,byIndex) != GetAwardIDByIndex(vecAwards,byIndex))         \
    {                                       \
        _setChanged.set(UPCOL(AwardLoot##bySign));    \
    }                                       \
    if(GetAwardByDrawByIndex(rVecAward,byIndex) != GetAwardByDrawByIndex(vecAwards,byIndex)) \
    {                                          \
        _setChanged.set(UPCOL(AwardbyDraw##bySign));   \
    }                                                  \
    if(GetAwardTypeByIndex(rVecAward,byIndex) != GetAwardTypeByIndex(vecAwards,byIndex)) \
    {                                          \
        _setChanged.set(UPCOL(AwardType##bySign));   \
    }                                                  \
                                                  \
} while (0)     

DIFFAWARD(0,1);
DIFFAWARD(1,2);
DIFFAWARD(2,3); 
vecAwards = rVecAward;
}
void CDBRoleArena::DiffFighter(const TVecFlushFither &rVec)
{
#define DIFFFIGHTER(byIndex,bySign) do {                  \
    if (GetFighterIDByIndex(rVec,byIndex) != GetFighterIDByIndex(vecFlushFigter,byIndex))         \
    {                                       \
        _setChanged.set(UPCOL(FighterID##bySign));    \
    }                                       \
    if(GetFighterbySucByIndex(rVec,byIndex) != GetFighterbySucByIndex(vecFlushFigter,byIndex)) \
    {                                          \
        _setChanged.set(UPCOL(FighterbySuc##bySign));   \
    }                                                  \
} while (0)     

DIFFFIGHTER(0,1);
DIFFFIGHTER(1,2);
DIFFFIGHTER(2,3); 
DIFFFIGHTER(3,4);
DIFFFIGHTER(4,5); 
vecFlushFigter = rVec;
}

bool CDBRoleArena::UpdateDataByStr(string& strData)
{
    CInArchive ar(strData);
    SRoleArenaInfo newData;
    ar >> newData;
    DIFF(dwCDTime);
    DIFF(dwLadderCDTime);
    DIFF(dwLastAwardTimer);
    DiffAward(newData.vecAwards);
    DiffFighter(newData.vecFlushFigter);
    bool bUpdate = !_setChanged.none();
    return bUpdate;
}

bool CDBRoleArena::GetInsertSqlStr(string& sqlstr)
{
    mysqlpp::SQLStream ostr(NULL);
    ostr << "Insert into tblrolearena(qwRoleID,dwCDTime,dwLastAwardTimer,AwardLoot1,AwardType1,AwardbyDraw1,AwardLoot2,AwardType2,AwardbyDraw2,AwardLoot3,AwardType3,AwardbyDraw3,FighterID1,FighterbySuc1,FighterID2,FighterbySuc2,FighterID3,FighterbySuc3,FighterID4,FighterbySuc4,FighterID5,FighterbySuc5,dwLadderCDTime) Values(";
    ostr << (mysqlpp::sql_bigint_unsigned)_qwRoleID;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwCDTime;
    ostr << "," << (mysqlpp::sql_int_unsigned)dwLastAwardTimer;
    size_t start = 0;
    size_t end = 3;
    for(start = 0; start != end && start != vecAwards.size();start++)
    {
        SArenaAward &rAward = vecAwards[start];
        ostr << "," << (mysqlpp::sql_int_unsigned)rAward.dwDrawID;
        ostr << "," << (mysqlpp::sql_tinyint_unsigned)rAward.eType;
        ostr << "," << (mysqlpp::sql_tinyint_unsigned)rAward.byDraw;
    }
    for(size_t i = start; i != end ; i++)
    {
        ostr << "," << (mysqlpp::sql_int_unsigned)0;
        ostr << "," << (mysqlpp::sql_tinyint_unsigned)0; 
        ostr << "," << (mysqlpp::sql_tinyint_unsigned)0;
    }
    start = 0;
    end = 5;
    for(start = 0; start != end && start != vecFlushFigter.size();start++)
    {
        SFlushFighter &rFighter = vecFlushFigter[start];
        ostr << "," << (mysqlpp::sql_bigint_unsigned)rFighter.qwFighterID;
        ostr << "," << (mysqlpp::sql_tinyint_unsigned)rFighter.bySuc;
    }
    for(size_t i = start; i != end ; i++)
    {
        ostr << "," << (mysqlpp::sql_int_unsigned)0;
        ostr << "," << (mysqlpp::sql_tinyint_unsigned)0;
    }
    ostr << "," << (mysqlpp::sql_int_unsigned)dwLadderCDTime;
    ostr << ");"; 
    sqlstr = ostr.str(); 
    return true;           
}

bool CDBRoleArena::GetUpdateSqlStr(string& strsql)
{
    if(_setChanged.none())
        return false;
    mysqlpp::SQLStream ostr(NULL);
    ostr << "UPDATE tblrolearena SET";
    UPDATE_UINT_SAME(dwCDTime);
    UPDATE_UINT_SAME(dwLastAwardTimer);
#define UPDATEAWARD(byIndex,bySign) do { \
    UINT32 AwardLoot##bySign = GetAwardIDByIndex(vecAwards,byIndex); \
    UPDATE_UINT_SAME(AwardLoot##bySign);  \
    UINT8 AwardbyDraw##bySign = GetAwardByDrawByIndex(vecAwards,byIndex); \
    UPDATE_UTINYINT_SAME(AwardbyDraw##bySign);   \
    UINT8 AwardType##bySign = GetAwardTypeByIndex(vecAwards,byIndex); \
    UPDATE_UTINYINT_SAME(AwardType##bySign);   \
}while(0);
    UPDATEAWARD(0,1);
    UPDATEAWARD(1,2);
    UPDATEAWARD(2,3);
    /*
       UINT32 AwardLoot1 = GetAwardIDByIndex(vecAwards,0);
       UPDATE_UINT_SAME(AwardLoot1);
       UINT32 AwardLoot2 = GetAwardIDByIndex(vecAwards,1);
       UPDATE_UINT_SAME(AwardLoot2);
       UINT32 AwardLoot3 = GetAwardIDByIndex(vecAwards,2);
       UPDATE_UINT_SAME(AwardLoot3);
       UINT8 AwardbyDraw1 = GetAwardByDrawByIndex(vecAwards,0);
       UPDATE_UTINYINT_SAME(AwardbyDraw1);
       UINT8 AwardbyDraw2 = GetAwardByDrawByIndex(vecAwards,1);
       UPDATE_UTINYINT_SAME(AwardbyDraw2);
       UINT8 AwardbyDraw3 = GetAwardByDrawByIndex(vecAwards,2);
       UPDATE_UTINYINT_SAME(AwardbyDraw3);
       */
#define UPDATEFIGHTER(byIndex,bySign) do{   \
    UINT64 FighterID##bySign = GetFighterIDByIndex(vecFlushFigter,byIndex);   \
    UPDATE_UBIGINT_SAME(FighterID##bySign);  \
    UINT8 FighterbySuc##bySign = GetFighterbySucByIndex(vecFlushFigter,byIndex);   \
    UPDATE_UTINYINT_SAME(FighterbySuc##bySign); \
}while(0);
    UPDATEFIGHTER(0,1);
    UPDATEFIGHTER(1,2);
    UPDATEFIGHTER(2,3);
    UPDATEFIGHTER(3,4);
    UPDATEFIGHTER(4,5);
    /*
       UINT64 FighterID1 = GetFighterIDByIndex(vecFlushFigter,0);
       UPDATE_UBIGINT_SAME(FighterID1);
       UINT64 FighterID2 = GetFighterIDByIndex(vecFlushFigter,1);
       UPDATE_UBIGINT_SAME(FighterID2);
       UINT64 FighterID3 = GetFighterIDByIndex(vecFlushFigter,2);
       UPDATE_UBIGINT_SAME(FighterID3);
       UINT64 FighterID4 = GetFighterIDByIndex(vecFlushFigter,3);
       UPDATE_UBIGINT_SAME(FighterID4);
       UINT64 FighterID5 = GetFighterIDByIndex(vecFlushFigter,4);
       UPDATE_UBIGINT_SAME(FighterID5);
       UINT8 FighterbySuc1 = GetFighterbySucByIndex(vecFlushFigter,0);
       UPDATE_UTINYINT_SAME(FighterbySuc1);
       UINT8 FighterbySuc2 = GetFighterbySucByIndex(vecFlushFigter,1);
       UPDATE_UTINYINT_SAME(FighterbySuc2);
       UINT8 FighterbySuc3 = GetFighterbySucByIndex(vecFlushFigter,2);
       UPDATE_UTINYINT_SAME(FighterbySuc3);
       UINT8 FighterbySuc4 = GetFighterbySucByIndex(vecFlushFigter,3);
       UPDATE_UTINYINT_SAME(FighterbySuc4);
       UINT8 FighterbySuc5= GetFighterbySucByIndex(vecFlushFigter,4);
       UPDATE_UTINYINT_SAME(FighterbySuc5);
       */
    UPDATE_UINT_SAME(dwLadderCDTime); 
    ostr << " WHERE  qwRoleID =" <<_qwRoleID <<  ";";  
    strsql = ostr.str();
    size_t pos = strsql.find("SET,");
if(pos == string::npos)
    return false;
    strsql[pos+3] = ' ';
    return true;
    }

void CDBRoleArena::ResetChange(void)
{
    _setChanged.reset();
}

void CDBRoleArena::InitDataByDBRow(const mysqlpp::Row &rRow)
{   
    GET_UINT_SAME(dwCDTime);
    GET_UINT_SAME(dwLastAwardTimer);
#define GETAWARD(byIndex)     \
    UINT32 AwardLoot##byIndex = 0; \
    GET_UINT_SAME(AwardLoot##byIndex); \
    UINT8 AwardbyDraw##byIndex = 0;   \
    GET_UTINYINT_SAME(AwardbyDraw##byIndex);  \
    UINT8 AwardType##byIndex = 0;   \
    GET_UTINYINT_SAME(AwardType##byIndex);  

    GETAWARD(1);
    GETAWARD(2);
    GETAWARD(3);
    /*
       UINT32 AwardLoot1 = 0;
       GET_UINT_SAME(AwardLoot1);
       UINT32 AwardLoot2 = 0;
       GET_UINT_SAME(AwardLoot2);
       UINT32 AwardLoot3 = 0;
       GET_UINT_SAME(AwardLoot3);
       UINT8 AwardbyDraw1 = 0;
       GET_UTINYINT_SAME(AwardbyDraw1);
       UINT8 AwardbyDraw2 = 0;
       GET_UTINYINT_SAME(AwardbyDraw2);
       UINT8 AwardbyDraw3 = 0;
       GET_UTINYINT_SAME(AwardbyDraw3);
       */
#define GETFIGHTER(byIndex) \
    UINT64 FighterID##byIndex = 0; \
    GET_UBIGINT_SAME(FighterID##byIndex); \
    UINT8 FighterbySuc##byIndex = 0;   \
    GET_UTINYINT_SAME(FighterbySuc##byIndex);

    GETFIGHTER(1);
    GETFIGHTER(2);
    GETFIGHTER(3);
    GETFIGHTER(4);
    GETFIGHTER(5);
    /*
       UINT64 FighterID1 = 0;
       GET_UBIGINT_SAME(FighterID1);
       UINT64 FighterID2 = 0;
       GET_UBIGINT_SAME(FighterID2);
       UINT64 FighterID3 = 0;
       GET_UBIGINT_SAME(FighterID3);
       UINT64 FighterID4 = 0;
       GET_UBIGINT_SAME(FighterID4);
       UINT64 FighterID3 = 0;
       GET_UBIGINT_SAME(FighterID5);
       UINT8 FighterbySuc1 = 0;
       GET_UTINYINT_SAME(FighterbySuc1);
       UINT8 FighterbySuc2 = 0;
       GET_UTINYINT_SAME(FighterbySuc2);
       UINT8 FighterbySuc3 = 0;
       GET_UTINYINT_SAME(FighterbySuc3);
       UINT8 FighterbySuc4 = 0;
       GET_UTINYINT_SAME(FighterbySuc4);
       UINT8 FighterbySuc5= 0;
       GET_UTINYINT_SAME(FighterbySuc5);
       */
#define InSertAward(byIndex) do { \
    SArenaAward tpAward;\
    tpAward.dwDrawID = AwardLoot##byIndex; \
    tpAward.byDraw = AwardbyDraw##byIndex; \
    tpAward.eType = static_cast<EArenaAwardType>(AwardType##byIndex); \
    if(tpAward.dwDrawID > 0 && tpAward.eType != Type_NONE){ \
    vecAwards.push_back(tpAward);} \
}while(0);
    InSertAward(1);
    InSertAward(2);
    InSertAward(3);
#define InSertFighter(byIndex) do { \
    SFlushFighter tepFither;      \
    tepFither.qwFighterID = FighterID##byIndex; \
    tepFither.bySuc = FighterbySuc##byIndex; \
    if(tepFither.qwFighterID > 0){   \
    vecFlushFigter.push_back(tepFither);} \
}while(0);
    InSertFighter(1);
    InSertFighter(2); 
    InSertFighter(3); 
    InSertFighter(4); 
    InSertFighter(5); 
    GET_UINT_SAME(dwLadderCDTime);
    TableRowBase::InitDataByDBRow(rRow);
    }

void CDBRoleArenaManager::QueryDataByRoleId(UINT64 qwRoleID,QueryFun queryfun)
{
    mysqlpp::SQLStream basesql(NULL);
    basesql << "SELECT * FROM tblrolearena WHERE qwRoleID =  " <<
        qwRoleID <<";";
    UINT64 qwLoadTimer = GetTickCount();
    CDBMgr::Instance().DoRoleSelectQuery(basesql.str(),_byLine,[this, queryfun, basesql,qwRoleID,qwLoadTimer] (INT8 byRet, mysqlpp::StoreQueryResult& dataRes) mutable {
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << basesql.str() << "result:" << byRet;
            LOG_INF<<"--------Load tblrolearena is "<<GetTickCount() - qwLoadTimer<<" miscseconds";
            UINT32 ncount = dataRes.size();
            if(byRet == 0 && ncount ==1)
            {
            mysqlpp::Row& rRow = dataRes[0];
            CDBRoleArena ArenaTable(qwRoleID);
            ArenaTable.InitDataByDBRow(rRow);
            _mapRoleArenaData[0]= ArenaTable;
            }
            queryfun(byRet, ncount);
            });
}

void CDBRoleArenaManager::Update(string& strData, bool bIsAdd)
{
    CInArchive testAr(strData);
    SRoleArenaInfo testData;
    testAr >> testData;
    auto iter = _mapRoleArenaData.find(0);
    if (iter == _mapRoleArenaData.end()&& bIsAdd)
    {
        CDBRoleArena ArenaNew(_qwRoleID);
        ArenaNew.Update(strData, bIsAdd);
        _mapRoleArenaData[0] = ArenaNew;
    }
    else if(iter != _mapRoleArenaData.end()&& !bIsAdd)
    {
        iter->second.Update(strData,bIsAdd);
    }
}

void CDBRoleArenaManager::GetALLInfo(RoleDataInfo & rData)
{
    for (auto iter =_mapRoleArenaData.begin();iter !=_mapRoleArenaData.end();iter++)
    {
        rData.vecArenaInfo.push_back(static_cast<SRoleArenaInfo>(iter->second));
    }
}


void CDBRoleArenaManager::DumpToDB(ManagerUpdateFun fun)
{
    _nNowQuery = GetUpdataNum();
    _nMaxQuery = _nNowQuery;
    _nErrQuery = 0;
    for (auto deliter = _vecDelArena.begin();deliter != _vecDelArena.end();deliter++)
    {
        mysqlpp::SQLStream sqlstr(NULL);
        sqlstr<<"delete FROM tblrolearena WHERE  qwRoleID="<<_qwRoleID <<  ";";
        CDBMgr::Instance().DoRoleModifyQuery(sqlstr.str(),_byLine, [this,fun,sqlstr](INT8 byRet, mysqlpp::SimpleResult& simRes){                              
            LOG_SQL << "[" << Time().hhmmssuu() << "]" << "do sql = " << sqlstr.str() << "result:" << byRet;
            this->_nNowQuery--;
            if (byRet)
            {
                this->_nErrQuery++;
            }
            if (this->_nNowQuery == 0)
            {
                fun(this->_nMaxQuery,this->_nErrQuery);
            }
        });
    }
    _vecDelArena.clear();
    for (auto iter =_mapRoleArenaData.begin();iter !=_mapRoleArenaData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            iter->second.DumpToDB(_byLine,[fun,this](INT8 byRet) {
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


}

UINT32 CDBRoleArenaManager::GetUpdataNum()
{
    UINT32 dwOP = 0;
    for (auto iter = _mapRoleArenaData.begin();iter != _mapRoleArenaData.end();iter++)
    {
        if (iter->second.HasOP())
        {
            dwOP++;
        } 
    }
    return dwOP +_vecDelArena.size();

}

void CDBRoleArenaManager::DelData(string& strData)
{
    auto iter = _mapRoleArenaData.find(0);
    if (iter != _mapRoleArenaData.end())
    {
        if(iter->second.IsInDB())
        {
           _vecDelArena.push_back(0);
        }
        _mapRoleArenaData.erase(0);
    }
}

UINT32 CDBRoleArena::GetAwardIDByIndex(const TVecArenaAward &rVecAward,UINT8 byIndex)
{
    if( byIndex >= rVecAward.size())
    {
        return 0;
    }
    return rVecAward[byIndex].dwDrawID;

}

EArenaAwardType CDBRoleArena::GetAwardTypeByIndex(const TVecArenaAward &rVecAward,UINT8 byIndex)
{
    if( byIndex >= rVecAward.size())
    {
        return Type_NONE;
    }
    return rVecAward[byIndex].eType;
}


UINT8 CDBRoleArena::GetAwardByDrawByIndex(const TVecArenaAward &rVecAward,UINT8 byIndex)
{
    if( byIndex >= rVecAward.size())
    {
        return 0;
    }
    return rVecAward[byIndex].byDraw;

}
UINT64  CDBRoleArena::GetFighterIDByIndex(const TVecFlushFither &rVec,UINT8 byIndex)
{
    if( byIndex >= rVec.size())
    {
        return 0;
    }
    return rVec[byIndex].qwFighterID;

}
UINT8  CDBRoleArena::GetFighterbySucByIndex(const TVecFlushFither &rVec,UINT8 byIndex)
{
    if( byIndex >= rVec.size())
    {
        return 0;
    }
    return rVec[byIndex].bySuc;

}

