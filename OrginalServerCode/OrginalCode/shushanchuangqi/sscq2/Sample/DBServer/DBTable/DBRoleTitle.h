#ifndef  DBROLE_TITLE_TABLE_H__
#define  DBROLE_TITLE_TABLE_H__
#include "DBTableBase.h"

class DBRoleTitleTable : public TableRowBase, public STitle, public CPoolObj<DBRoleTitleTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(byEquipPos),
            UPCOL(dwValidTime),
            UPCOL(Max)
        };

    public:
        DBRoleTitleTable(UINT64 setqwRoleID):_qwRoleID(setqwRoleID){}
        DBRoleTitleTable():_qwRoleID(0){}

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

class DBRoleTitleTableManager : public TableManagerBaseForRole, public CPoolObj<DBRoleTitleTableManager>
{ 
    public:
        DBRoleTitleTableManager(UINT64 setqwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeTitle, setqwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();
    private:
        map<UINT32,DBRoleTitleTable> _mapRoleTitleData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT32> _vecDelTitle;
};
#endif

