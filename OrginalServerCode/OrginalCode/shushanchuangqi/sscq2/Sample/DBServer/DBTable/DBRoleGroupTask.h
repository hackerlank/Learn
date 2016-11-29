#ifndef  DBROLE_GROUP_TASK_TABLE_H__
#define  DBROLE_GROUP_TASK_TABLE_H__
#include "DBTableBase.h"

class CDBRoleGroupTaskTable : public TableRowBase, public SGroupTaskInfo, public CPoolObj<CDBRoleGroupTaskTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(dwRepute),
            UPCOL(byReputeLevel),
            UPCOL(byBuyTimes),
            UPCOL(dwFlushTask1),
            UPCOL(eState1),
            UPCOL(dwFlushTask2),
            UPCOL(eState2),
            UPCOL(dwFlushTask3),
            UPCOL(eState3),
            UPCOL(dwFlushTask4),
            UPCOL(eState4),
            UPCOL(dwFlushTask5),
            UPCOL(eState5),
            UPCOL(Max)
        };

    public:
        CDBRoleGroupTaskTable(UINT64 setqwRoleID):_qwRoleID(setqwRoleID){}
        CDBRoleGroupTaskTable():_qwRoleID(0){}

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

class CDBRoleGroupTaskTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleGroupTaskTableManager>
{ 
    public:
        CDBRoleGroupTaskTableManager(UINT64 setqwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeGroupTask, setqwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0),_RoleGroupTaskData(setqwRoleID) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();
    private:
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        CDBRoleGroupTaskTable _RoleGroupTaskData;
};
#endif

