
#ifndef  DBROLEAUTOSTORETABLE_H__
#define  DBROLEAUTOSTORETABLE_H__
#include "DBTableBase.h"
#include "RoleInfoDefine.h"
using namespace NRoleInfoDefine;
struct SAutoStoreKey
{
    SAutoStoreKey(UINT64 qwRoleID,UINT16 wType,UINT32 dwClassID)
        : qwRoleID(qwRoleID),wType(wType),dwClassID(dwClassID) {}

    UINT64  qwRoleID;
    UINT16  wType;
    UINT32  dwClassID;

    bool operator < (const SAutoStoreKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        
        if (wType !=  sk.wType)
            return wType < sk.wType;

        return dwClassID < sk.dwClassID;
    }
};


class CDBRoleAutoStoreTable : public TableRowBase, public SAutoStoreDBInfo, public CPoolObj<CDBRoleAutoStoreTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID      ),
            UPCOL(wType       ),
            UPCOL(dwClassID      ),
            UPCOL(dwValue     ),
            UPCOL(Max           )
        };

    public:
        CDBRoleAutoStoreTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleAutoStoreTable():_qwRoleID(0){}
        void InitDataByBase(const SAutoStoreDBInfo &rInfo);
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

class CDBRoleAutoStoreTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleAutoStoreTableManager>
{ 
    public:
        CDBRoleAutoStoreTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeAutoStore, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SAutoStoreKey,CDBRoleAutoStoreTable> _mapRoleAutoStoreData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SAutoStoreKey> _vecDelAutoStore;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

