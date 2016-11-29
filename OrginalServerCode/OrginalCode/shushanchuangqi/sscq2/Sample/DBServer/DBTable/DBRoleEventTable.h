
#ifndef  DBROLEEVENTTABLE_H__
#define  DBROLEEVENTTABLE_H__
#include "DBTableBase.h"
#include "RoleInfoDefine.h"
using namespace NRoleInfoDefine;
struct SEventKey
{
    SEventKey(UINT64 qwRoleID,UINT8 byActClassID,UINT32 dwEventInstID,UINT32  dwApplyID)
        : qwRoleID(qwRoleID),byActClassID(byActClassID),dwEventInstID(dwEventInstID),dwApplyID(dwApplyID) {}

    UINT64  qwRoleID;
    UINT16   byActClassID; //不用UINT8 <<操作符不允许
    UINT32  dwEventInstID;
    UINT32  dwApplyID;

    bool operator < (const SEventKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        
        if (byActClassID !=  sk.byActClassID)
            return byActClassID < sk.byActClassID;

        if(dwEventInstID != sk.dwEventInstID)
            return dwEventInstID < sk.dwEventInstID;

        return dwApplyID < sk.dwApplyID;
    }
};


class CDBRoleEventDBTable: public TableRowBase, public SEventInfo, public CPoolObj<CDBRoleEventDBTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID            ),
            UPCOL(byActClassID        ),
            UPCOL(dwEventInstID       ),
            UPCOL(dwApplyID           ),
            UPCOL(wEventStatus        ),
            UPCOL(bySave              ),
            UPCOL(dwParam1            ),
            UPCOL(dwParam2            ),
            UPCOL(Max                 )
        };

    public:
        CDBRoleEventDBTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleEventDBTable():_qwRoleID(0){}
        void InitDataByBase(const SEventInfo &rInfo);
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

class CDBRoleEventTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleEventTableManager>
{ 
    public:
        CDBRoleEventTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeEventInfo, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SEventKey,CDBRoleEventDBTable> _mapRoleDBData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SEventKey> _vecDel;
};

#endif // 

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

