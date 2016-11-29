#ifndef  DBROLE_DGN_TABLE_H__
#define  DBROLE_DGN_TABLE_H__
#include "DBTableBase.h"

class DBRoleDgnTable : public TableRowBase, public RoleDgnInfo, public CPoolObj<DBRoleDgnTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(dwLastEnterTimer),
            UPCOL(byCost),
            UPCOL(dwEnterTimesAppend),
            UPCOL(dwAppendEndTimer),
            UPCOL(dwEnterTimes),
            UPCOL(dwLastCompleteTimer),
            UPCOL(dwCompleteTimes),
            UPCOL(wMinTurns),
            UPCOL(dwBuyTimer),
            UPCOL(dwBuyTimesToday),
            UPCOL(dwFinishTimesToday),
            UPCOL(Max)
        };

    public:
        DBRoleDgnTable(UINT64 setqwRoleID):_qwRoleID(setqwRoleID){}
        DBRoleDgnTable():_qwRoleID(0){}

        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);
        bool OnRecv_SaveOffLineDgnInfo(UINT8 byIsFail);

    private:
        bitset<UPCOL(Max)> _setChanged;
        UINT64 _qwRoleID;
};

class DBRoleDgnTableManager : public TableManagerBaseForRole, public CPoolObj<DBRoleDgnTableManager>
{ 
    public:
        DBRoleDgnTableManager(UINT64 setqwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypePlayerDgn, setqwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();
        bool OnRecv_SaveOffLineDgnInfo(UINT32 dwDgnType,UINT8 byIsFail);
    private:
        map<UINT32,DBRoleDgnTable> _mapRoleDgnData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT32> _vecDelDgn;
};
#endif

