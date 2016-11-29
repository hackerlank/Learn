#ifndef  DBROLE_ARENA_ROLE_TABLE_H__
#define  DBROLE_ARENA_ROLE_TABLE_H__
#include "DBTableBase.h"
#include "ArenaGS.h"
using namespace NArenaGS;
class CDBRoleArena :public TableRowBase, public SRoleArenaInfo, public CPoolObj<CDBRoleArena>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(dwCDTime),
            UPCOL(dwLastAwardTimer),
            UPCOL(AwardLoot1),
            UPCOL(AwardType1),
            UPCOL(AwardbyDraw1),
            UPCOL(AwardLoot2),
            UPCOL(AwardType2),
            UPCOL(AwardbyDraw2),
            UPCOL(AwardLoot3),
            UPCOL(AwardType3),
            UPCOL(AwardbyDraw3),
            UPCOL(FighterID1),
            UPCOL(FighterbySuc1),
            UPCOL(FighterID2),
            UPCOL(FighterbySuc2),
            UPCOL(FighterID3),
            UPCOL(FighterbySuc3),
            UPCOL(FighterID4),
            UPCOL(FighterbySuc4),
            UPCOL(FighterID5),
            UPCOL(FighterbySuc5),
            UPCOL(dwLadderCDTime),
            UPCOL(Max)
        };

    public:
        CDBRoleArena(UINT64 setqwRoleID):_qwRoleID(setqwRoleID){}
        CDBRoleArena():_qwRoleID(0){}
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);
 private:
        UINT32 GetAwardIDByIndex(const TVecArenaAward &rVecAward,UINT8 byIndex);
        UINT8 GetAwardByDrawByIndex(const TVecArenaAward &rVecAward,UINT8 byIndex);
        EArenaAwardType GetAwardTypeByIndex(const TVecArenaAward &rVecAward,UINT8 byIndex);
        UINT64 GetFighterIDByIndex(const TVecFlushFither &rVec,UINT8 byIndex);
        UINT8 GetFighterbySucByIndex(const TVecFlushFither &rVec,UINT8 byIndex);
       void DiffAward(const TVecArenaAward &rVecAward);
       void DiffFighter(const TVecFlushFither &rVec);
    private:
        bitset<UPCOL(Max)> _setChanged;
    public:
        UINT64 _qwRoleID;

};

class CDBRoleArenaManager :  public TableManagerBaseForRole, public CPoolObj<CDBRoleArenaManager>
{ 
    public:
        CDBRoleArenaManager(UINT64 setqwRoleID,UINT8 byLine): TableManagerBaseForRole(eTypeArena, setqwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
       virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT32,CDBRoleArena> _mapRoleArenaData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT32> _vecDelArena;
};
#endif

