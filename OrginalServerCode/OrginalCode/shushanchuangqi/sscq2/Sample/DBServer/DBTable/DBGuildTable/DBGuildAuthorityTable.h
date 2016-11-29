#ifndef DB_GUILD_AUTHORITY_TABLE_H
#define DB_GUILD_AUTHORITY_TABLE_H
#include "DBGuildTableBase.h"

struct SAuthorityKey
{
    SAuthorityKey(UINT64 qwGuildID, UINT8 byMemberRank)
        : qwGuildID(qwGuildID), byMemberRank(byMemberRank){}

    UINT64  qwGuildID;
    UINT8   byMemberRank;

    bool operator < (const SAuthorityKey& sk) const
    {
        if (qwGuildID !=  sk.qwGuildID)
            return qwGuildID < sk.qwGuildID;
        return byMemberRank < sk.byMemberRank;
    }
};

class CDBGuildAuthorityTable : public TableRowBase, public CPoolObj<CDBGuildAuthorityTable>
{
    friend class CDBGuildAuthorityTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwGuildID),
            UPCOL(byMemberRank),
            UPCOL(dwAuthority),
            UPCOL(Max)
        };

    public:
        CDBGuildAuthorityTable();
        virtual ~CDBGuildAuthorityTable();

        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64  GetGuildID() const;
        UINT8   GetMemberRank() const;
        UINT32  GetAuthority() const;

    private:
        bool InitDataByGuildAuthority(const SGuildAuthorityInfo& rAuthority);

    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwGuildID;
        UINT8  _byMemberRank;       // 帮派职位
        UINT32 _dwAuthority;
};

class CDBGuildAuthorityTableManager : public CTableManagerBaseForGuild, public CPoolObj<CDBGuildAuthorityTableManager>
{ 
    public:
        CDBGuildAuthorityTableManager(UINT64 qwGuildID);
        virtual ~CDBGuildAuthorityTableManager();

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

        map<SAuthorityKey, CDBGuildAuthorityTable> _mapGuildData;
        vector<SAuthorityKey>  _vecDelGuildID;
        TSetUINT64 _setDelGuildID;
};

#endif // #define DB_GUILD_AUTHORITY_TABLE_H
