// =====================================================================================
//
//       Filename:  DBRoleAdoreTable.h
//
//    Description:  崇拜数据
//
//        Version:  1.0
//        Created:  09/29/2014 10:39:05 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef DB_ROLE_ADORE_TABLE_H
#define DB_ROLE_ADORE_TABLE_H

#include "DBRankTableBase.h"

class CDBRoleAdoreTable : public TableRowBase, public CPoolObj<CDBRoleAdoreTable>
{
    friend class CDBRoleAdoreTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(dwCount),
            UPCOL(dwUpdateTime),
            UPCOL(Max)
        };

    public:
        CDBRoleAdoreTable();
        virtual ~CDBRoleAdoreTable();


        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64          GetRoleID() const;
        UINT32          GetCount() const;
        UINT32          GetUpdataTime() const;

    private:
        bool InitDataByRoleAdore(const SDBAdoreInfo& rLog);

    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwRoleID;
        UINT32 _dwCount;
        UINT32 _dwUpdateTime;
};

class CDBRoleAdoreTableManager : public CPoolObj<CDBRoleAdoreTableManager>
{ 
    public:
        CDBRoleAdoreTableManager(UINT64 qwRoleID);
        virtual ~CDBRoleAdoreTableManager();

        virtual void QueryDataByRoleID(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(UINT64 qwRoleID);
        virtual void Update(string& strData, EDataChange eUpdateType);
        virtual void GetAllInfo(TVecDBAdoreInfo& vecAdoreInfo);
        virtual void DumpToDBRank(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:

        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;

        map<UINT64, CDBRoleAdoreTable> _mapAdoreData;
        TVecUINT64  _vecDelRoleID;
};
#endif // #ifndef DB_ROLE_ADORE_TABLE_H


