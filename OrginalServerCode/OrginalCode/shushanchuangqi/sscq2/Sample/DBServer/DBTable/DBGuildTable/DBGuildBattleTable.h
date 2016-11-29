// =====================================================================================
//
//       Filename:  DBGuildBattleTable.h
//
//    Description:  帮派战相关数据存取
//
//        Version:  1.0
//        Created:  08/01/2014 06:01:25 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef DB_GUILD_BATTLE_TABLE_H
#define DB_GUILD_BATTLE_TABLE_H
#include "DBGuildTableBase.h"

class CDBGuildBattleTable : public TableRowBase, public CPoolObj<CDBGuildBattleTable>
{
    friend class CDBGuildBattleTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwGuildID),
            UPCOL(dwScore),
            UPCOL(Max)
        };

    public:
        CDBGuildBattleTable();
        virtual ~CDBGuildBattleTable();

        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64  GetGuildID() const;
        UINT32  GetScore() const;

    private:
        bool InitDataByGuildBattle(const SDBGuildBattleInfo& rBattle);
    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwGuildID;
        UINT32 _dwScore;
};

class CDBGuildBattleTableManager : public CTableManagerBaseForGuildPub, public CPoolObj<CDBGuildBattleTableManager>
{ 
    public:
        CDBGuildBattleTableManager(UINT64 qwGuildID);
        virtual ~CDBGuildBattleTableManager();

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

        map<UINT64, CDBGuildBattleTable> _mapGuildData;
        TVecUINT64  _vecDelGuildID;
};

#endif // #ifndef DB_GUILD_BATTLE_TABLE_H

