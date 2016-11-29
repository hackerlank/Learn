#ifndef DB_GUILD_BUILDING_TABLE_H
#define DB_GUILD_BUILDING_TABLE_H
#include "DBGuildTableBase.h"

struct SBuildingKey
{
    SBuildingKey(UINT64 qwGuildID, UINT8 byType)
        : qwGuildID(qwGuildID), byType(byType){}

    UINT64  qwGuildID;
    UINT8   byType;

    bool operator < (const SBuildingKey& sk) const
    {
        if (qwGuildID !=  sk.qwGuildID)
            return qwGuildID < sk.qwGuildID;
        return byType < sk.byType;
    }
};

class CDBGuildBuildingTable : public TableRowBase, public CPoolObj<CDBGuildBuildingTable>
{
    friend class CDBGuildBuildingTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwGuildID),
            UPCOL(byType),
            UPCOL(wLevel),
            UPCOL(Max)
        };

    public:
        CDBGuildBuildingTable();
        virtual ~CDBGuildBuildingTable();


        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64  GetGuildID() const;
        UINT8   GetBuildingType() const;
        UINT16  GetLevel() const;

    private:
        bool InitDataByGuildBuilding(const SGuildBuildingInfo& rBuilding);

    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwGuildID;
        UINT8  _byType;
        UINT16 _wLevel;
};

class CDBGuildBuildingTableManager : public CTableManagerBaseForGuild, public CPoolObj<CDBGuildBuildingTableManager>
{ 
    public:
        CDBGuildBuildingTableManager(UINT64 qwGuildID);
        virtual ~CDBGuildBuildingTableManager();

        virtual void QueryDataByGuildID(UINT64 qwGuildID, QueryFun fun);
        virtual void DelData(string& strData, UINT64 qwGuildID = 0);
        virtual void Update(string& strData, EDataChange eUpdateType);
        virtual void GetAllInfo(SDBGuildAllInfo& rData);
        virtual void DumpToDBGuild(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:

        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;

        map<SBuildingKey, CDBGuildBuildingTable> _mapGuildData;
        TVecUINT64  _vecDelGuildID;
        TSetUINT64  _setDelGuildID;
};

#endif // #define DB_GUILD_BUILDING_TABLE_H
