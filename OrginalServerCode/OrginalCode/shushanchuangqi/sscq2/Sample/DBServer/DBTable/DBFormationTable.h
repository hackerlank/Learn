
#ifndef DBFORMATIONTABLE_H_
#define DBFORMATIONTABLE_H_

#include "DBTableBase.h"

class CDBFormationTable : public TableRowBase, public SFormationInfo, public CPoolObj<CDBFormationTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(wFormationID),
            UPCOL(bySelected),
            UPCOL(Max)
        };

    public:
        CDBFormationTable(UINT64 qwRoleID) : _qwRoleID(qwRoleID) {}
        CDBFormationTable() : _qwRoleID(0){}

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
class CDBFormationTableManager : public TableManagerBaseForRole, public CPoolObj<CDBFormationTableManager>
{ 
    public:
        CDBFormationTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeFormationInfo, qwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT16, CDBFormationTable> _mapFormationData; // OwnerID to FormationTable
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT16> _vecDelFormation;
};

#endif // DBFORMATIONTABLE_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

