
#ifndef  DBROLEITEMTABLE_H__
#define  DBROLEITEMTABLE_H__
#include "DBTableBase.h"

class CDBRoleItemTable : public TableRowBase, public RoleItemInfo, public CPoolObj<CDBRoleItemTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(byStoreType),
            UPCOL(wIndex),
            UPCOL(wItemID),
            UPCOL(wItemCount),
            UPCOL(byBind),
            UPCOL(wCount),
            UPCOL(byExpired),
            UPCOL(dwExpireTime),
            UPCOL(dwMark),
            UPCOL(Max)
        };

    public:
        CDBRoleItemTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleItemTable():_qwRoleID(0){}
        void InitDataByBase(const RoleItemInfo &rInfo);
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

class CDBRoleItemTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleItemTableManager>
{ 
    public:
        CDBRoleItemTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeItemInfo, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT64,CDBRoleItemTable> _mapRoleItemData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT64> _vecDelItem;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

