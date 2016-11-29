#ifndef DB_GUILD_USER_TABLE_H
#define DB_GUILD_USER_TABLE_H
#include "DBGuildTableBase.h"

#include "GuildProt.h"

class CDBGuildUserTable : public TableRowBase, public CPoolObj<CDBGuildUserTable>
{
    friend class CDBGuildUserTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwGuildID),
            UPCOL(qwRoleID),
            UPCOL(wLevel),
            UPCOL(dwContribution),
            UPCOL(dwLastOnline),
            UPCOL(byMemberRank),
            UPCOL(byMemberLastRank),
            UPCOL(strTech),
            UPCOL(dwBattleScore),
            UPCOL(byVIPLevel),
            UPCOL(wPlayerFighterID),
            UPCOL(byQuality),
            UPCOL(Max)
        };

    public:
        CDBGuildUserTable();
        virtual ~CDBGuildUserTable();

        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64  GetGuildID() const;
        UINT64  GetRoleID() const;
        UINT16  GetLevel() const;
        UINT32  GetContribution() const;
        UINT32  GetLastOnline() const;
        UINT8   GetMemberRank() const;
        UINT8   GetMemberLastRank() const;
        const string& GetName() const;
        const string& GetTech() const;
        UINT32  GetBattleScore() const;
        UINT8   GetVIPLevel() const;
        UINT16  GetPlayerFighterID() const;
        UINT8   GetQuality() const;

        bool ToDBGuildUserInfo(SDBGuildUserInfo& rUserInfo) const;

    private:
        bool InitDataByGuildUser(const SDBGuildUserInfo& rUser);

    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwGuildID;          // 帮派ID
        UINT64 _qwRoleID;           // 玩家ID
        UINT16 _wLevel;             // 玩家等级
        UINT32 _dwContribution;     // 贡献值
        UINT32 _dwLastOnline;       // 最后在线时间
        UINT8  _byMemberRank;       // 帮派职位
        UINT8  _byMemberLastRank;   // 帮派上一次职位
        string _strName;            // 玩家名称 （从NameManager里面获取，数据库里面没有存储）
        string _strTech;            // 玩家科技
        UINT32 _dwBattleScore;      // 帮派战积分
        UINT8  _byVIPLevel;         // VIP等级
        UINT16 _wPlayerFighterID;   // 主将ID
        UINT8  _byQuality;          // 主将品质
};

class CDBGuildUserTableManager : public CTableManagerBaseForGuild, public CPoolObj<CDBGuildUserTableManager>
{ 
    public:
        CDBGuildUserTableManager(UINT64 qwGuildID);
        virtual ~CDBGuildUserTableManager();

        virtual void QueryDataByGuildID(UINT64 qwGuildID, QueryFun fun);
        virtual void DelData(string& strData, UINT64 qwGuildID = 0);
        virtual void Update(string& strData, EDataChange eUpdateType);
        virtual void GetAllInfo(SDBGuildAllInfo& rData);
        virtual void DumpToDBGuild(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

        void QueryDataByRoleID(UINT64 qwGuildID, UINT64 qwRoleID, QueryFun fun);
        bool GetUserInfo(SDBGuildUserInfo& rInfo, UINT64 qwRoleID);
        void GetAllRoleID(TVecUINT64& vecRoleID) const;
    private:

        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;

        map<UINT64, CDBGuildUserTable> _mapGuildData;
        TVecUINT64  _vecDelGuildID;
};
#endif // #ifndef DB_GUILD_USER_TABLE_H
