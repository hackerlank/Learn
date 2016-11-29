#ifndef DB_GUILD_BASE_INFO_TABLE_H
#define DB_GUILD_BASE_INFO_TABLE_H
#include "DBGuildTableBase.h"

class CDBGuildBaseInfoTable : public TableRowBase, public CPoolObj<CDBGuildBaseInfoTable>
{
    friend class CDBGuildBaseInfoTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwGuildID),
            UPCOL(qwOwnerID),
            UPCOL(byLevel),
            UPCOL(strName),
            UPCOL(strInfo),
            UPCOL(qwQQGroupID),
            UPCOL(dwMoney),
            UPCOL(wPlayerFighterID),
            UPCOL(byQuality),
            UPCOL(dwCount),
            UPCOL(dwScore),
            UPCOL(strLingShan),
            UPCOL(Max)
        };

    public:
        CDBGuildBaseInfoTable();
        virtual ~CDBGuildBaseInfoTable();

        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64  GetGuildID() const;
        UINT64  GetOwnerID() const;
        UINT8   GetLevel() const;
        const string& GetName() const;
        const string& GetInfo() const;
        UINT64  GetQQGroupID() const;
        UINT32  GetMoney() const;
        UINT16  GetPlayerFighterID() const;
        UINT8   GetQuality() const;
        UINT32  GetCount() const;
        UINT32  GetScore() const;
        const string& GetLingShan() const;

    private:
        bool InitDataByGuildBaseInfo(const SGuildBaseInfo& rBaseInfo);
    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwGuildID;
        UINT64 _qwOwnerID;
        UINT8  _byLevel;
        string _strName;
        string _strInfo;
        UINT64 _qwQQGroupID;
        UINT32 _dwMoney;
        UINT16 _wPlayerFighterID;
        UINT8  _byQuality;
        UINT32 _dwCount;
        UINT32 _dwScore;
        string _strLingShan;
};

class CDBGuildBaseInfoTableManager : public CTableManagerBaseForGuild, public CPoolObj<CDBGuildBaseInfoTableManager>
{ 
    public:
        CDBGuildBaseInfoTableManager(UINT64 qwGuildID);
        virtual ~CDBGuildBaseInfoTableManager();

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

        map<UINT64, CDBGuildBaseInfoTable> _mapGuildData;
        TVecUINT64  _vecDelGuildID;
};

#endif // #define DB_GUILD_BASE_INFO_TABLE_H
