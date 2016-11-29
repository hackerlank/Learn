// =====================================================================================
//
//       Filename:  DBRankHeroFighterTable.h
//
//    Description:  散仙排行榜表操作
//
//        Version:  1.0
//        Created:  09/05/2014 02:53:24 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef DB_RANK_HERO_FIGHTER_TABLE_H
#define DB_RANK_HERO_FIGHTER_TABLE_H

#include "DBRankTableBase.h"

struct SHeroFighterKey
{
    SHeroFighterKey(UINT64 qwRoleID, UINT16 wID)
        : qwRoleID(qwRoleID), wID(wID) {}

    UINT64 qwRoleID;
    UINT16 wID;

    bool operator < (const SHeroFighterKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        return wID < sk.wID;
    }
};

class CDBRankHeroFighterTable : public TableRowBase, public CPoolObj<CDBRankHeroFighterTable>
{
    friend class CDBRankHeroFighterTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(dwBattlePoint),
            UPCOL(strName),
            UPCOL(dwUpdateTime),
            UPCOL(strGuildName),
            UPCOL(wID),
            UPCOL(wPlayerFighterID),
            UPCOL(byQuality),
            UPCOL(byInfoQuality),
            UPCOL(byVIPLevel),
            UPCOL(Max)
        };

    public:
        CDBRankHeroFighterTable();
        virtual ~CDBRankHeroFighterTable();


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
        UINT16          GetID() const;
        UINT16          GetPlayerFighterID() const;
        UINT8           GetQuality() const;
        UINT8           GetInfoQuality() const;
        UINT8           GetVIPLevel() const;

    private:
        bool InitDataByRankHeroFighter(const SRRHeroFighterInfo& rLog);

    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwRoleID;
        UINT32 _dwBattlePoint;
        string _strName;
        UINT32 _dwUpdateTime;
        string _strGuildName;
        UINT16 _wID;
        UINT16 _wPlayerFighterID;
        UINT8  _byQuality;
        UINT8  _byInfoQuality;
        UINT8  _byVIPLevel;
};

class CDBRankHeroFighterTableManager : public CTableManagerBaseForRoleRank, public CPoolObj<CDBRankHeroFighterTableManager>
{ 
    public:
        CDBRankHeroFighterTableManager(UINT64 qwRoleID);
        virtual ~CDBRankHeroFighterTableManager();

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

        map<SHeroFighterKey, CDBRankHeroFighterTable> _mapRankData;
        vector<SHeroFighterKey> _vecDelKey;
};

#endif //#ifndef DB_RANK_HERO_FIGHTER_TABLE_H

