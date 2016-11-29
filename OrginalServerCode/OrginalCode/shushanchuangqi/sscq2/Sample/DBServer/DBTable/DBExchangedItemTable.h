
#ifndef  DBROLEECHANGEDITEMTABLE_H__
#define  DBROLEECHANGEDITEMTABLE_H__
#include "DBTableBase.h"
#include "ExchangeShopProtSvr.h"
#include "RoleInfoDefine.h"
using namespace NExchangeShopProt;
using namespace NRoleInfoDefine;
struct SExchangedItemedKey
{
    SExchangedItemedKey(UINT64 qwRoleID,UINT32 dwExchangeID)
        : qwRoleID(qwRoleID),dwExchangeID(dwExchangeID) {}

    UINT64  qwRoleID;
    UINT32  dwExchangeID;

    bool operator < (const SExchangedItemedKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        return dwExchangeID < sk.dwExchangeID;
    }
};


class CDBRoleExchangedItemTable: public TableRowBase, public ExchangeInfo, public CPoolObj<CDBRoleExchangedItemTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID      ),
            UPCOL(dwExchangeID  ),
            UPCOL(dwCount),
            UPCOL(dwFinishTime ),
            UPCOL(Max           )
        };

    public:
        CDBRoleExchangedItemTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleExchangedItemTable():_qwRoleID(0){}
        void InitDataByBase(const ExchangeInfo &rInfo);
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

class CDBRoleExchangedItemTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleExchangedItemTableManager>
{ 
    public:
        CDBRoleExchangedItemTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeExchangedItem, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SExchangedItemedKey,CDBRoleExchangedItemTable> _mapRoleExchangedItemData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SExchangedItemedKey> _vecDel;
};

#endif 

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

