#ifndef  DBROLE_TASK_TABLE_H__
#define  DBROLE_TASK_TABLE_H__
#include "DBTableBase.h"

class DBRoleTaskTable : public TableRowBase, public RoleTaskInfo, public CPoolObj<DBRoleTaskTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(eTaskState),
            UPCOL(dwAcceptTimes),
            UPCOL(dwLastAcceptTimer),
            UPCOL(dwFinishTimes),
            UPCOL(dwLastFinishTimer),
            UPCOL(byProcessType1),
            UPCOL(dwProcessParam11),
            UPCOL(dwProcessParam12),
            UPCOL(byProcessType2),
            UPCOL(dwProcessParam21),
            UPCOL(dwProcessParam22),
            UPCOL(byProcessType3),
            UPCOL(dwProcessParam31),
            UPCOL(dwProcessParam32),
            UPCOL(dwRepeatAcceptTimes),
            UPCOL(Max)
        };

    public:
        DBRoleTaskTable(UINT64 setqwRoleID):_qwRoleID(setqwRoleID){}
        DBRoleTaskTable():_qwRoleID(0){}

        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);
        bool OnRecv_SaveOffLineTaskInfo(UINT8 byIsFail);

    private:
        bitset<UPCOL(Max)> _setChanged;
        UINT64 _qwRoleID;
};

class DBRoleTaskTableManager : public TableManagerBaseForRole, public CPoolObj<DBRoleTaskTableManager>
{ 
    public:
        DBRoleTaskTableManager(UINT64 setqwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeTaskInfo, setqwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();
        //bool OnRecv_SaveOffLineTaskInfo(UINT32 dwTaskType,UINT8 byIsFail);
    private:
        map<UINT32,DBRoleTaskTable> _mapRoleTaskData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT32> _vecDelTask;
};
#endif

