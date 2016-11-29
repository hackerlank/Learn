
#ifndef  DBROLESHENGLINGTABLE_H__
#define  DBROLESHENGLINGTABLE_H__
#include "DBTableBase.h"
#include "ShengLingProt.h"
#include "RoleInfoDefine.h"
#include "ItemProt.h"
using namespace NShengLingProt;
using namespace NRoleInfoDefine;
using namespace NItemProt;
struct SShengLingKey
{
    SShengLingKey(UINT64 qwRoleID,UINT8 byLevel,UINT8 byIndex)
        : qwRoleID(qwRoleID),byLevel(byLevel),byIndex(byIndex) {}

    UINT64  qwRoleID;
    UINT8  byLevel;
    UINT8  byIndex;

    bool operator < (const SShengLingKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        if(byLevel != sk.byLevel)
            return byLevel < sk.byLevel;
        return byIndex < sk.byIndex;
    }
};

class CDBRoleShengLingDBTable: public TableRowBase, public SShengLingInfo2DB, public CPoolObj<CDBRoleShengLingDBTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID       ),
            UPCOL(byLevel        ),
            UPCOL(byIndex        ),
            UPCOL(byType         ),
            UPCOL(wNoteID        ),
            UPCOL(byRandom       ),
            UPCOL(byFinish       ),
            UPCOL(Max            )
        };

    public:
        CDBRoleShengLingDBTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleShengLingDBTable():_qwRoleID(0){}
        void InitDataByBase(const SShengLingInfo2DB &rInfo);
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

class CDBRoleShengLingTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleShengLingTableManager>
{ 
    public:
        CDBRoleShengLingTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeShengLing, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SShengLingKey,CDBRoleShengLingDBTable> _mapRoleShengLingDBData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SShengLingKey> _vecDel;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

