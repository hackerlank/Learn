
#ifndef  DBROLEDAYTARGETTABLE_H__
#define  DBROLEDAYTARGETTABLE_H__
#include "DBTableBase.h"
#include "RoleInfoDefine.h"
using namespace NRoleInfoDefine;
struct SDayTargetKey
{
    SDayTargetKey(UINT64 qwRoleID,UINT16 wTaskID)
        : qwRoleID(qwRoleID),wTaskID(wTaskID) {}

    UINT64  qwRoleID;
    UINT16  wTaskID;

    bool operator < (const SDayTargetKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        return wTaskID < sk.wTaskID;
    }
};


class CDBRoleDayTargetTable : public TableRowBase, public SDayTargetDBInfo, public CPoolObj<CDBRoleDayTargetTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID      ),
            UPCOL(wTaskID       ),
            UPCOL(byStatus      ),
            UPCOL(dwProcess     ),
            UPCOL(Max           )
        };

    public:
        CDBRoleDayTargetTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleDayTargetTable():_qwRoleID(0){}
        void InitDataByBase(const SDayTargetDBInfo &rInfo);
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

class CDBRoleDayTargetTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleDayTargetTableManager>
{ 
    public:
        CDBRoleDayTargetTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeDayTarget, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SDayTargetKey,CDBRoleDayTargetTable> _mapRoleDayTargetData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SDayTargetKey> _vecDelDayTarget;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

