
#ifndef DBTRIPODTABLE_H_
#define DBTRIPODTABLE_H_

#include "DBTableBase.h"
#include "TripodProt.h"
#include "ArenaGS.h"

using namespace NArenaGS;
using namespace NTripodProt;

class CDBTripodTable : public STripodInfo, public CPoolObj<CDBTripodTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(byTripodID),
            UPCOL(byLevel),
            UPCOL(dwExp),
            UPCOL(wFireID),
            UPCOL(byFireLvl),
            UPCOL(dwStartTime),
            UPCOL(dwShanfengTime),
            UPCOL(dwSoul),
            UPCOL(dwLine),
            UPCOL(Max)
        };

    public:
        CDBTripodTable(UINT64 qwRoleID) : _qwRoleID(qwRoleID),_bIsNew(false) {}
        CDBTripodTable() : _qwRoleID(0),_bIsNew(false) {}

        void InitDataByData(const STripodInfo& rInData);
        bool UpdateDataByData(const STripodInfo& newData);
        bool GetInsertSqlStr(string& sqlstr);
        bool GetUpdateSqlStr(string& sqlstr);
        void ResetChange(void);
        void InitDataByDBRow(const mysqlpp::Row &row);
        void SetNew(bool bNew) { _bIsNew = bNew; }
        bool IsNew() { return _bIsNew; }
        bool IsChange() { return !_setChanged.none(); }
    private:
        bitset<UPCOL(Max)> _setChanged;
        UINT64 _qwRoleID;
        bool _bIsNew;
};

struct STripodPlayerData
{
    STripodPlayerData(UINT64 qwRoleID) : _qwOwnerID(qwRoleID) {}

    UINT64 _qwOwnerID;
    vector<CDBTripodTable> _vecTripodInfo;
    TVecUINT32 _vecFighterID;
    SArenaFighter _stPlayerAppear;
    TVecArenaFighter _vecHelpPlayer;
};

typedef shared_ptr<SArenaFighter> STripodPlayerPtr;
typedef function<void(INT8,STripodPlayerPtr)> QueryPlayerFun;

class CDBTripodTableManager: public CPoolObj<CDBTripodTableManager>
{ 
    public:
        CDBTripodTableManager() : _dwQueryFighterMax(0) {}
        void GetAllTripod(UINT32 dwPageSize);
        void QueryData(UINT32 dwPageSize,QueryFun fun);
        void QueryFighterData(UINT64 qwRoleId, QueryPlayerFun fun);
        void SendDataToCenter(UINT32 dwTotalPage,UINT32 dwPageSize);
        void DelData(UINT64 qwRoleID, string& strData);
        void UpdateData(UINT64 qwRoleID, const NTripodProt::STripodInfo& oTripodInfo, bool bIsAdd);

        void DumpToDB(bool bForBit =false);
        UINT32 GetUpdataNum();
    private:
        map<UINT64, STripodPlayerData> _mapAllTripodData;
        map<UINT64, STripodInfo> _mapDelTripod;
        UINT32 _dwQueryFighterMax;
};
extern CDBTripodTableManager g_CDBTripodTableManager;

#endif // DBTRIPODTABLE_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

