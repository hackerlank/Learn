
#ifndef  DBWONDERPRIZETABLE_H__
#define  DBWONDERPRIZETABLE_H__
#include "DBTableBase.h"
#include "RoleInfoDefine.h"
#include "WonderActivityProt.h"

using namespace NRoleInfoDefine;
using namespace NWonderActivityProt;
struct SWonderPrizeKey
{
    SWonderPrizeKey(UINT64 qwRoleID,UINT16 wActID,UINT32 wCond)
        : qwRoleID(qwRoleID),wActID(wActID),wCond(wCond) {}

    UINT64  qwRoleID;
    UINT16  wActID;
    UINT32  wCond;

    bool operator < (const SWonderPrizeKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        if(wCond != sk.wCond)
            return wCond < sk.wCond;
        return wActID < sk.wActID;
    }
};

class CDBWonderPrizeTable: public TableRowBase, public SWonderPrize2DB, public CPoolObj<CDBWonderPrizeTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID      ),
            UPCOL(wActType      ),
            UPCOL(wActID        ),
            UPCOL(wCond         ),
            UPCOL(byStatus      ),
            UPCOL(Max           )
        };

    public:
        CDBWonderPrizeTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBWonderPrizeTable():_qwRoleID(0){}
        void InitDataByBase(const SWonderPrize2DB &rInfo);
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);
    private:
        bitset<UPCOL(Max)> _setChanged;
        UINT64 _qwRoleID;
};

class CDBWonderPrizeTableManager : public Singleton<CDBWonderPrizeTableManager>
{ 
    public:
        CDBWonderPrizeTableManager(UINT8 byLine = 0) : _byLine(byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        UINT32 GetUpdataNum();
        void   GetALLInfo(TVecWonderPrize2DB& vecWonderPrize2DB);
        void   GetALLInfo(std::map<UINT64,UINT8>& _mapID2Level);
        void   GetInfoForDungon(multimap<UINT64,UINT32>& _mapID2Level);
        void   GetInfoForTrump(multimap<UINT64,UINT16>& _mapID2Level);
        void   GetInfoForFighter(multimap<UINT64,UINT16>& _mapID2Level);
        void   GetInfoForFormation(multimap<UINT64,UINT16>& _mapID2Level);
        void   GetInfoForBeauty(multimap<UINT64,UINT16>& _mapID2Level);
        void   GetInfoForHorse(multimap<UINT64,UINT32>& _mapID2Level);
        void   DumpToDB();
        void   DelData(const SWonderPrize2DB& oData);
        void   DelData(const UINT16& wActID);
        void   Update(const SWonderPrize2DB&  oData,bool bIsAdd);
        void   QueryData();
        void   QueryLevelData();
        void   QueryTrumpData();
        void   QueryFighterData();
        void   QueryFormationData();
        void   QueryBeautyData();
        void   QueryDungonData();
        void   QueryHorseData();
          
    private:
        map<SWonderPrizeKey,CDBWonderPrizeTable> _mapWonderPrizeDBData;
        map<UINT64,UINT8> _mapRoleID2Level;
        multimap<UINT64,UINT16> _mapRoleID2Trump;
        multimap<UINT64,UINT16> _mapRoleID2Fighter;
        multimap<UINT64,UINT16> _mapRoleID2Formation;
        multimap<UINT64,UINT32> _mapRoleID2Dungon;
        multimap<UINT64,UINT16> _mapRoleID2Beauty;
        multimap<UINT64,UINT32> _mapRoleID2Horse;
        vector<SWonderPrizeKey> _vecDel;
        UINT8 _byLine;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

