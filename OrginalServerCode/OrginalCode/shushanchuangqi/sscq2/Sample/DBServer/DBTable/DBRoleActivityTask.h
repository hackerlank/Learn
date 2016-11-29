#ifndef  DBROLE_ACTIVITYTASK_TABLE_H__
#define  DBROLE_ACTIVITYTASK_TABLE_H__
#include "DBTableBase.h"

class DBRoleActivityTaskTable : public TableRowBase, public SActivityTaskInfo, public CPoolObj<DBRoleActivityTaskTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(byTimes),
            UPCOL(byIsSpecial),
            UPCOL(Max)
        };

    public:
        DBRoleActivityTaskTable(UINT64 setqwRoleID):_qwRoleID(setqwRoleID){}
        DBRoleActivityTaskTable():_qwRoleID(0){}

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

class DBRoleActivityTaskTableManager : public TableManagerBaseForRole, public CPoolObj<DBRoleActivityTaskTableManager>
{ 
    public:
        DBRoleActivityTaskTableManager(UINT64 setqwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeActivityTask, setqwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();
    private:
        map<UINT32,DBRoleActivityTaskTable> _mapRoleActivityTaskData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT32> _vecDelActivityTask;
};
#endif

