// =====================================================================================
//
//       Filename:  DBRankFormationTable.h
//
//    Description:  阵灵排行榜表操作
//
//        Version:  1.0
//        Created:  09/05/2014 02:54:39 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef DB_RANK_FORMATION_TABLE_H
#define DB_RANK_FORMATION_TABLE_H

#include "DBRankTableBase.h"
class CDBRankFormationTable : public TableRowBase, public CPoolObj<CDBRankFormationTable>
{
    friend class CDBRankFormationTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(dwBattlePoint),
            UPCOL(strName),
            UPCOL(dwUpdateTime),
            UPCOL(strGuildName),
            UPCOL(wPlayerFighterID),
            UPCOL(wID),
            UPCOL(byQuality),
            UPCOL(byVIPLevel),
            UPCOL(Max)
        };

    public:
        CDBRankFormationTable();
        virtual ~CDBRankFormationTable();


        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64          GetRoleID() const;
        UINT32          GetBattlePoint() const;
        const string&   GetName() const;
        UINT32          GetUpdataTime() const;
        const string&   GetGuildName() const;
        UINT16          GetPlayerFighterID() const;
        UINT16          GetID() const;
        UINT8           GetQuality() const;
        UINT8           GetVIPLevel() const;

    private:
        bool InitDataByRankFormation(const SRRFormationInfo& rLog);

    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwRoleID;
        UINT32 _dwBattlePoint;
        string _strName;
        UINT32 _dwUpdateTime;
        string _strGuildName;
        UINT8  _wPlayerFighterID;
        UINT16 _wID;
        UINT8  _byQuality;
        UINT8  _byVIPLevel;
};

class CDBRankFormationTableManager : public CTableManagerBaseForRoleRank, public CPoolObj<CDBRankFormationTableManager>
{ 
    public:
        CDBRankFormationTableManager(UINT64 qwRoleID);
        virtual ~CDBRankFormationTableManager();

        virtual void QueryDataByRoleID(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData, UINT64 qwRoleID = 0);
        virtual void Update(string& strData, EDataChange eUpdateType);
        virtual void GetAllInfo(TVecRankInfo& vecRankInfo);
        virtual void DumpToDBRank(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:

        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;

        map<UINT64, CDBRankFormationTable> _mapRankData;
        TVecUINT64  _vecDelRoleID;
};


#endif // #ifndef DB_RANK_FORMATION_TABLE_H

