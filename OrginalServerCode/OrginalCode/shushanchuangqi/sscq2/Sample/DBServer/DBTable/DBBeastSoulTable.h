// =====================================================================================
//
//       Filename:  DBBeastSoulTable.h
//
//    Description:  兽魂数据表
//
//        Version:  1.0
//        Created:  10/10/2014 12:07:15 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================


#ifndef DB_BEAST_SOUL_TABLE_H
#define DB_BEAST_SOUL_TABLE_H

#include "DBTableBase.h"

class CDBBeastSoulTable : public TableRowBase, public SBeastSoulInfo, public CPoolObj<CDBBeastSoulTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(byType),
            UPCOL(byRank),
            UPCOL(byLevel),
            UPCOL(Max)
        };

    public:
        CDBBeastSoulTable(UINT64 qwRoleID) : _qwRoleID(qwRoleID) {}
        CDBBeastSoulTable() : _qwRoleID(0){}

        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

    private:
        bitset<UPCOL(Max)> _setChanged;
        UINT64 _qwRoleID;
};

// XXX: 需要到这个函数TableManagerBaseForRole::CreateManager里去注册
class CDBBeastSoulTableManager : public TableManagerBaseForRole, public CPoolObj<CDBBeastSoulTableManager>
{ 
    public:
        CDBBeastSoulTableManager(UINT64 qwRoleID,UINT8 byLine):
            TableManagerBaseForRole(eTypeBeastSoulInfo, qwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<EBeastSoulType, CDBBeastSoulTable> _mapBeastSoulData; // OwnerID to BeastDataTable
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<EBeastSoulType> _vecDelBeastData;
};

#endif // #ifndef DB_BEAST_SOUL_TABLE_H

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

