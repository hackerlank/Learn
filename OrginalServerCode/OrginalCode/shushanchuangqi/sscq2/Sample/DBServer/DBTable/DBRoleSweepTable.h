
#ifndef DBROLESWEEPTABLE_H_
#define DBROLESWEEPTABLE_H_

#include "DBTableBase.h"
#include "DungeonProt.h"
#include "RoleInfoDefine.h"
using namespace NRoleInfoDefine;
using namespace NDungeonProt;
class CDBRoleSweepTable : public TableRowBase, public SSweepInfo, public CPoolObj<CDBRoleSweepTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(wCurDgnID),
            UPCOL(wCurCount),
            UPCOL(dwReserverTime),
            UPCOL(dwSaveTime),
            UPCOL(wOptions),
            UPCOL(wCount),
            UPCOL(strVecDgn),
            UPCOL(Max)
        };

    public:
        CDBRoleSweepTable(UINT64 qwRoleID) : _qwRoleID(qwRoleID) {}
        CDBRoleSweepTable() : _qwRoleID(0){}

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
class CDBRoleSweepTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleSweepTableManager>
{ 
    public:
        CDBRoleSweepTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeSweep, qwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
       
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT64,CDBRoleSweepTable>  _mapData; // OwnerID to PetDataTable
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT64> _vecDelData;
};

#endif 

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

