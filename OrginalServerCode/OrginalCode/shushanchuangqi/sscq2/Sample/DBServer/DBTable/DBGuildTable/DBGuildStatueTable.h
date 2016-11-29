#ifndef DB_GUILD_STATUE_TABLE_H
#define DB_GUILD_STATUE_TABLE_H
#include "DBGuildTableBase.h"

class CDBGuildStatueTable : public TableRowBase, public CPoolObj<CDBGuildStatueTable>
{
    friend class CDBGuildStatueTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwGuildID),
            UPCOL(wLevel),
            UPCOL(dwExp),
            UPCOL(byWorshipCount),
            UPCOL(dwTime),
            UPCOL(Max)
        };

    public:
        CDBGuildStatueTable();
        virtual ~CDBGuildStatueTable();


        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64  GetGuildID() const;
        UINT16  GetLevel() const;
        UINT32  GetExp() const;
        UINT8   GetWorshipCount() const;
        UINT32  GetTime() const;

    private:
        bool InitDataByGuildStatue(const SGuildStatueInfo& rStatue);

    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwGuildID;
        UINT16 _wLevel;
        UINT32 _dwExp;
        UINT8  _byWorshipCount;
        UINT32 _dwTime;
};

class CDBGuildStatueTableManager : public CTableManagerBaseForGuild, public CPoolObj<CDBGuildStatueTableManager>
{ 
    public:
        CDBGuildStatueTableManager(UINT64 qwGuildID);
        virtual ~CDBGuildStatueTableManager();

        virtual void QueryDataByGuildID(UINT64 qwGuildID, QueryFun fun);
        virtual void DelData(string& strData, UINT64 qwGuildID);
        virtual void Update(string& strData, EDataChange eUpdateType);
        virtual void GetAllInfo(SDBGuildAllInfo& rData);
        virtual void DumpToDBGuild(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:

        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;

        map<UINT64, CDBGuildStatueTable> _mapGuildData;
        TVecUINT64  _vecDelGuildID;
};

#endif // #define DB_GUILD_STATUE_TABLE_H
