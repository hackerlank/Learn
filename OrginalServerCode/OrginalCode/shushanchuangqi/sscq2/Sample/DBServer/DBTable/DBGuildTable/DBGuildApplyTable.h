#ifndef DB_GUILD_APPLY_TABLE_H
#define DB_GUILD_APPLY_TABLE_H
#include "DBGuildTableBase.h"

#include "GuildProt.h"

class CDBGuildApplyTable : public TableRowBase, public CPoolObj<CDBGuildApplyTable>
{
    friend class CDBGuildApplyTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwGuildID),
            UPCOL(qwRoleID),
            UPCOL(strName),
            UPCOL(wLevel),
            UPCOL(dwBattlePoint),
            UPCOL(Max)
        };

    public:
        CDBGuildApplyTable();
        virtual ~CDBGuildApplyTable();

        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64  GetGuildID() const;
        UINT64  GetRoleID() const;
        UINT8   GetLevel() const;
        const string& GetName() const;
        UINT32  GetBattlePoint() const;

    private:
        bool InitDataByGuildApply(const SGuildApplyInfo& rApply);
    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwGuildID;
        UINT64 _qwRoleID;
        string _strName;
        UINT8  _wLevel;
        UINT32 _dwBattlePoint;
};

class CDBGuildApplyTableManager : public CTableManagerBaseForGuild, public CPoolObj<CDBGuildApplyTableManager>
{ 
    public:
        CDBGuildApplyTableManager(UINT64 qwGuildID);
        virtual ~CDBGuildApplyTableManager();

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

        map<UINT64, CDBGuildApplyTable> _mapGuildData;
        TVecUINT64  _vecDelGuildID;
};

#endif // #define DB_GUILD_APPLY_TABLE_H
