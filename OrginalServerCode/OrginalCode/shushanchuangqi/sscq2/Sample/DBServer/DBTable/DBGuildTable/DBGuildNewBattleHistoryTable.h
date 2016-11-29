// =====================================================================================
//
//       Filename:  DBGuildNewBattleHistoryTable.h
//
//    Description:  新帮派战历史占领帮派数数据
//
//        Version:  1.0
//        Created:  03/20/2015 04:42:40 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef DB_GUILD_NEW_BATTLE_HISTORY_TABLE_H
#define DB_GUILD_NEW_BATTLE_HISTORY_TABLE_H

#include "DBTableBase.h"

#include "Singleton.h"

class CDBGuildNewBattleHistoryTable : 
    public TableRowBase, public CPoolObj<CDBGuildNewBattleHistoryTable>
{
    friend class CDBGuildNewBattleHistoryTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(byMountainType),
            UPCOL(qwGuildID),
            UPCOL(strGuildName),
            UPCOL(strGuildOwnerName),
            UPCOL(dwTime),
            UPCOL(Max)
        };

    public:
        CDBGuildNewBattleHistoryTable();
        virtual ~CDBGuildNewBattleHistoryTable();

        virtual void InitDataByStr(string& strData); //利用更新初始化
        virtual bool UpdateDataByStr(string& strData){return false;}//返回值：变化值大于0 true
        virtual bool GetInsertSqlStr(string& sqlstr);//生成插入语句 
        virtual bool GetUpdateSqlStr(string& sqlstr){ return false;};//根据变化生成sql语句
        virtual void ResetChange(void) {};// 清理变化的记录

        void InitDataByDBRow(const mysqlpp::Row &rRow);

        UINT8   GetMountainType() const;
        UINT64  GetGuildID() const;
        const string& GetGuildName() const;
        const string& GetGuildOwnerName() const;
        UINT32  GetTime() const;


    private:
        UINT8  _byMountainType;
        UINT64 _qwGuildID;
        string _strGuildName;
        string _strGuildOwnerName;
        UINT32 _dwTime;
};

typedef vector<CDBGuildNewBattleHistoryTable> TVecDBGuildNewBattleHistoryTable;

class CDBGuildNewBattleHistoryTableManager : 
    public Singleton<CDBGuildNewBattleHistoryTableManager>,
    public CPoolObj<CDBGuildNewBattleHistoryTableManager>
{ 
    public:
        CDBGuildNewBattleHistoryTableManager();
        virtual ~CDBGuildNewBattleHistoryTableManager();

        virtual void GetAllInfo(TVecDBGuildNewBattleHistoryInfo& vecInfo, 
                UINT32 dwIndex, UINT32 dwCount, UINT32& dwCurIndex, UINT32& dwMaxCount);

        void InitDataByDBRow(const mysqlpp::Row &rRow);

        void QueryAllData(QueryFun queryfun);

        void InsertNewData(string& strData);

    private:
        TVecDBGuildNewBattleHistoryTable _vecData;
};

#endif // #ifndef DB_GUILD_NEW_BATTLE_HISTORY_TABLE_H

