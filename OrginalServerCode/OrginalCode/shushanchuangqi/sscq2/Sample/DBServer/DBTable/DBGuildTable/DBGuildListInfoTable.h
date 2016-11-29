#ifndef DB_GUILD_LIST_INFO_TABLE_H
#define DB_GUILD_LIST_INFO_TABLE_H
#include "DBGuildTableBase.h"

class CDBGuildListInfoTable : public TableRowBase, public CPoolObj<CDBGuildListInfoTable>
{
    friend class CDBGuildListInfoTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwGuildID),
            UPCOL(strName),
            UPCOL(strInfo),
            UPCOL(qwOwnerID),
            UPCOL(strOwnerName),
            UPCOL(byLevel),
            UPCOL(wUserCount),
            UPCOL(wMaxUserCount),
            UPCOL(Max)
        };

    public:
        CDBGuildListInfoTable();
        virtual ~CDBGuildListInfoTable();

        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64  GetGuildID() const;
        const string& GetName() const;
        const string& GetInfo() const;
        UINT64  GetOwnerID() const;
        const string& GetOwnerName() const;
        UINT8   GetLevel() const;
        UINT16  GetUserCount() const;
        UINT16  GetMaxUserCount() const;

    private:
        bool InitDataByGuildListInfo(const SGuildListInfo& rListInfo);
    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwGuildID;
        string _strName;
        string _strInfo;
        UINT64 _qwOwnerID;
        string _strOwnerName;
        UINT8  _byLevel;
        UINT16 _wUserCount;
        UINT16 _wMaxUserCount;
};

class CDBGuildListInfoTableManager : public CTableManagerBaseForGuildPub, public CPoolObj<CDBGuildListInfoTableManager>
{ 
    public:
        CDBGuildListInfoTableManager(UINT64 qwGuildID);
        virtual ~CDBGuildListInfoTableManager();

        virtual void QueryDataByGuildID(UINT64 qwGuildID, QueryFun fun);
        virtual void DelData(string& strData, UINT64 qwGuildID = 0);
        virtual void Update(string& strData, EDataChange eUpdateType);
        virtual void GetAllInfo(SPubGuildAllInfo& rData);
        virtual void DumpToDBGuild(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

        void InitDataByDBRow(UINT64 qwGuildID, const mysqlpp::Row &rRow);
    private:

        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;

        map<UINT64, CDBGuildListInfoTable> _mapGuildData;
        TVecUINT64  _vecDelGuildID;
};

#endif // #define DB_GUILD_LIST_INFO_TABLE_H
