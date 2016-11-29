// =====================================================================================
//
//       Filename:  DBRankLevelTable.h
//
//    Description:  排行榜等级表操作
//
//        Version:  1.0
//        Created:  12/01/2014 05:58:53 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef DB_RANK_LEVEL_TABLE_H
#define DB_RANK_LEVEL_TABLE_H

#include "DBRankTableBase.h"
class CDBRankLevelTable : public TableRowBase, public CPoolObj<CDBRankLevelTable>
{
    friend class CDBRankLevelTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(wLevel),
            UPCOL(qwExp),
            UPCOL(strName),
            UPCOL(dwUpdateTime),
            UPCOL(wPlayerFighterID),
            UPCOL(byQuality),
            UPCOL(byVIPLevel),
            UPCOL(Max)
        };

    public:
        CDBRankLevelTable();
        virtual ~CDBRankLevelTable();


        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64          GetRoleID() const;
        UINT16          GetLevel() const;
        UINT64          GetExp() const;
        const string&   GetName() const;
        UINT32          GetUpdataTime() const;
        UINT16          GetPlayerFighterID() const;
        UINT8           GetQuality() const;
        UINT8           GetVIPLevel() const;

    private:
        bool InitDataByRankLevel(const SRRLevelInfo& rLog);

    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwRoleID;
        UINT16 _wLevel;
        UINT64 _qwExp;
        string _strName;
        UINT32 _dwUpdateTime;
        UINT8  _wPlayerFighterID;
        UINT8  _byQuality;
        UINT8  _byVIPLevel;
};

class CDBRankLevelTableManager : public CTableManagerBaseForRoleRank, public CPoolObj<CDBRankLevelTableManager>
{ 
    public:
        CDBRankLevelTableManager(UINT64 qwRoleID);
        virtual ~CDBRankLevelTableManager();

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

        map<UINT64, CDBRankLevelTable> _mapRankData;
        TVecUINT64  _vecDelRoleID;
};

#endif //#ifndef DB_RANK_LEVEL_TABLE_H
