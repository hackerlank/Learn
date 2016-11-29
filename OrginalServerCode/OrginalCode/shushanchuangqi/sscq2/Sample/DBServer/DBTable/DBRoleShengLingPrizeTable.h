
#ifndef  DBROLESHENGLINGPRIZETABLE_H__
#define  DBROLESHENGLINGPRIZETABLE_H__
#include "DBTableBase.h"
#include "RoleInfoDefine.h"
#include "ShengLingProt.h"
#include "ItemProt.h"
using namespace NRoleInfoDefine;
using namespace NShengLingProt;
using namespace NItemProt;
struct SShengLingPrizeKey
{
    SShengLingPrizeKey(UINT64 qwRoleID,UINT16 wItem)
        : qwRoleID(qwRoleID),wItem(wItem) {}

    UINT64  qwRoleID;
    UINT16  wItem;

    bool operator < (const SShengLingPrizeKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        return wItem < sk.wItem;
    }
};

class CDBRoleShengLingPrizeDBTable: public TableRowBase, public SShengLingPrize2DB, public CPoolObj<CDBRoleShengLingPrizeDBTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID       ),
            UPCOL(wItemID        ),
            UPCOL(wNum           ),
            UPCOL(Max            )
        };

    public:
        CDBRoleShengLingPrizeDBTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleShengLingPrizeDBTable():_qwRoleID(0){}
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);
        UINT64 GetRoleID(){ return _qwRoleID; }
    private:
        bitset<UPCOL(Max)> _setChanged;
        UINT64 _qwRoleID;
};

class CDBRoleShengLingPrizeTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleShengLingPrizeTableManager>
{ 
    public:
        CDBRoleShengLingPrizeTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeShengLingPrize, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SShengLingPrizeKey,CDBRoleShengLingPrizeDBTable> _mapRoleShengLingPrizeDBData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT64> _vecDel;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

