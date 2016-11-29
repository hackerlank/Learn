
#ifndef DBROLEPETTABLE_H_
#define DBROLEPETTABLE_H_

#include "DBTableBase.h"

class CDBRolePetTable : public TableRowBase, public SRolePetInfo, public CPoolObj<CDBRolePetTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(dwExp),
            UPCOL(byLevel),
            UPCOL(dwSpirit),
            UPCOL(Max)
        };

    public:
        CDBRolePetTable(UINT64 qwRoleID) : _qwRoleID(qwRoleID) {}
        CDBRolePetTable() : _qwRoleID(0){}

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
class CDBRolePetTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRolePetTableManager>
{ 
    public:
        CDBRolePetTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeRolePetInfo, qwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT64, CDBRolePetTable> _mapRolePetData; // OwnerID to RolePetTable
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT64> _vecDelRolePet;
};

#endif // DBROLEPETTABLE_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

