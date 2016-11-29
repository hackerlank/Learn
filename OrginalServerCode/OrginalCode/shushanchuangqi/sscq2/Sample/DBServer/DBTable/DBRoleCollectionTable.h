
#ifndef  DBROLECOLLECTIONTABLE_H__
#define  DBROLECOLLECTIONTABLE_H__
#include "DBTableBase.h"
#include "CollectionProt.h"
#include "RoleInfoDefine.h"
using namespace NCollectionProt;
using namespace NRoleInfoDefine;
struct SCollectKey
{
    SCollectKey(UINT64 qwRoleID,UINT16 wCollectionID)
        : qwRoleID(qwRoleID),wCollectionID(wCollectionID) {}

    UINT64  qwRoleID;
    UINT16  wCollectionID;

    bool operator < (const SCollectKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        return wCollectionID < sk.wCollectionID;
    }
};


class CDBRoleCollectionTable : public TableRowBase, public SCollectionInfo, public CPoolObj<CDBRoleCollectionTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID      ),
            UPCOL(wCollectionID),
            UPCOL(dwCount       ),
            UPCOL(dwProcess     ),
            UPCOL(dwFinishTime  ),
            UPCOL(Max           )
        };

    public:
        CDBRoleCollectionTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleCollectionTable():_qwRoleID(0){}
        void InitDataByBase(const SCollectionInfo &rInfo);
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

class CDBRoleCollectionTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleCollectionTableManager>
{ 
    public:
        CDBRoleCollectionTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeCollectionInfo, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SCollectKey,CDBRoleCollectionTable> _mapRoleCollectionData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SCollectKey> _vecDelCollection;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

