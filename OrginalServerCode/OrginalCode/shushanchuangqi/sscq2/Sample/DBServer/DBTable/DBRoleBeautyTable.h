
#ifndef  DBROLEBEAUTYTABLE_H__
#define  DBROLEBEAUTYTABLE_H__
#include "DBTableBase.h"
#include "BeautySvr.h"
#include "RoleInfoDefine.h"
using namespace NBeauty;
using namespace NRoleInfoDefine;
struct SBeautyKey
{
    SBeautyKey(UINT64 qwRoleID,UINT32 wBeautyID)
        : qwRoleID(qwRoleID),wBeautyID(wBeautyID) {}

    UINT64  qwRoleID;
    UINT16  wBeautyID;

    bool operator < (const SBeautyKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        return wBeautyID < sk.wBeautyID;
    }
};


class CDBRoleBeautyTable : public TableRowBase, public SBeauty, public CPoolObj<CDBRoleBeautyTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwUserID      ),
            UPCOL(wBeautyID     ),
            UPCOL(wBeautyLevel  ),
            UPCOL(dwBeautyExp   ),
            UPCOL(wDayLoveType  ),
            UPCOL(dwChatTime    ),
            UPCOL(dwPrizeExp    ),
            UPCOL(Max           )
        };

    public:
        CDBRoleBeautyTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleBeautyTable():_qwRoleID(0){}
        void InitDataByBase(const SBeauty &rInfo);
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

class CDBRoleBeautyTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleBeautyTableManager>
{ 
    public:
        CDBRoleBeautyTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeBeauty, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SBeautyKey,CDBRoleBeautyTable> _mapRoleBeautyData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SBeautyKey> _vecDelBeauty;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

