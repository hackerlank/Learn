#ifndef  DBTOTAL_ARENA_TABLE_H__
#define  DBTOTAL_ARENA_TABLE_H__
#include "DBTableBase.h"
#include "ArenaGS.h"
using namespace NArenaGS;
class CDBTotalArena : public SArenaPlayerBaseData, public CPoolObj<CDBTotalArena>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(dwRanking),
            UPCOL(dwScore),
            UPCOL(eLevel),
            //UPCOL(dwSameDays),
            UPCOL(dwLastFlushTime),
            UPCOL(dwLastRank),
            UPCOL(eLastLevel),
            UPCOL(dwFighterPower),
            UPCOL(dwLadderRank),
            UPCOL(dwLastLadderRank),
            UPCOL(byQuality),
            UPCOL(byVIPLevel),
            UPCOL(Max)
        };

    public:
        CDBTotalArena(UINT64 setqwRoleID):_bIsNew(false), _qwRoleID(setqwRoleID){}
        CDBTotalArena():_qwRoleID(0){}
        void InitDataByData(const SArenaPlayerBaseData & rData);
        bool UpdateDataByData(const SArenaPlayerBaseData & rData);
        bool GetInsertSqlStr(string& sqlstr);
        bool GetUpdateSqlStr(string& sqlstr);
        void ResetChange(void);
        void InitDataByDBRow(const mysqlpp::Row &row);
        void SetNew(bool bNew) {_bIsNew = bNew;}
        bool IsNew(){return _bIsNew;}
        bool IsChange(){ return !_setChanged.none();}
    private:
        bitset<UPCOL(Max)> _setChanged;
        bool _bIsNew;

    public:
        UINT64 _qwRoleID;
        SArenaFighter _stFighter;
};


typedef shared_ptr<SArenaFighter> SArenaFighterPtr;
typedef function<void(INT8,SArenaFighterPtr)> QueryFighterFun;
class CDBTotalArenaManager : public CPoolObj<CDBTotalArenaManager>
{ 
    public:
        CDBTotalArenaManager():_dwQueryFighterMax(0){}
        void GetAllArena(UINT32 dwPageSize);
        void QueryData(UINT32 dwPageSize,QueryFun fun);
        void QueryFighterData(UINT64 qwRoleId, QueryFighterFun fun);
        void SendDataToCenter(UINT32 dwTotalPage,UINT32 dwPageSize);
        void DelData(UINT64 qwRoleID);
        void UpdateData(UINT64 qwRoleID,const SArenaPlayerBaseData &stData);

        void DumpToDB(bool bForBit =false);
        UINT32 GetUpdataNum();
    private:
        map<UINT64,CDBTotalArena> _mapRoleArenaData;
        vector<UINT64> _vecDelArena;
        UINT32 _dwQueryFighterMax;
};
extern CDBTotalArenaManager g_CDBTotalArenaManager;
#endif

