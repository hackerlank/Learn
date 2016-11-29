
#ifndef  DBROLESHOPITEMTABLE_H__
#define  DBROLESHOPITEMTABLE_H__
#include "DBTableBase.h"
#include "RoleInfoDefine.h"
using namespace NRoleInfoDefine;
struct SShopItemKey
{
    SShopItemKey(UINT64 qwRoleID,UINT32 dwInstID)
        : qwRoleID(qwRoleID),dwInstID(dwInstID) {}

    UINT64  qwRoleID;
    UINT32  dwInstID;

    bool operator < (const SShopItemKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        return dwInstID < sk.dwInstID;
    }
};


class CDBRoleShopItemTable: public TableRowBase, public SBuyItemDBInfo, public CPoolObj<CDBRoleShopItemTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID      ),
            UPCOL(dwInstID  ),
            UPCOL(dwCount),
            UPCOL(Max           )
        };

    public:
        CDBRoleShopItemTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleShopItemTable():_qwRoleID(0){}
        void InitDataByBase(const SBuyItemDBInfo &rInfo);
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

class CDBRoleShopItemTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleShopItemTableManager>
{ 
    public:
        CDBRoleShopItemTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeBuyItemLimit, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SShopItemKey,CDBRoleShopItemTable> _mapRoleShopItemData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SShopItemKey> _vecDel;
};

#endif 

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

