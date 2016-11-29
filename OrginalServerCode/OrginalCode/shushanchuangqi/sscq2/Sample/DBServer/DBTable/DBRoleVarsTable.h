
#ifndef DBROLEVARS_H_
#define DBROLEVARS_H_

#include "DBTableBase.h"

class CDBRoleVarsTable : public TableRowBase, public SVarsDBInfo, public CPoolObj<CDBRoleVarsTable>
{
    public:
        enum EUpdateColumn
        {
            //UPCOL(qwOwnerID),
            UPCOL(qwValue),
            UPCOL(dwExpired),
            UPCOL(Max)
        };

    public:
        CDBRoleVarsTable(UINT64 qwRoleID) : _qwRoleID(qwRoleID){}
        CDBRoleVarsTable() : _qwRoleID(0){}

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
class CDBRoleVarsTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleVarsTableManager>
{ 
    public:
        CDBRoleVarsTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeVarInfo, qwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT16, CDBRoleVarsTable> _mapVarsData; // OwnerID to VarsTable
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT16> _vecDelVars;
};

#endif // DBROLEVARS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

