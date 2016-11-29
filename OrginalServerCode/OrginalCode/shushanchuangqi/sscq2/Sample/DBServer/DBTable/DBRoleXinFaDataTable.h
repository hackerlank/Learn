#ifndef DBROLEXINFADATATABLE_H_
#define DBROLEXINFADATATABLE_H_

#include "DBTableBase.h"

struct SXinFaKey
{
    SXinFaKey(UINT64 qwRoleID, UINT64 qwOwnerID, UINT32 dwXinFaID)
        :_qwRoleID(qwRoleID), _qwOwnerID(qwOwnerID), _dwXinFaID(dwXinFaID) {}

    UINT64  _qwRoleID;
    UINT64  _qwOwnerID;
    UINT32  _dwXinFaID;
    

    bool operator < (const SXinFaKey& sk) const
    {
        if (_qwRoleID < sk._qwRoleID)
        {
           return true;
        }
        else if (_qwRoleID > sk._qwRoleID)
        {
            return false;
        }

        if(_qwOwnerID < sk._qwOwnerID)
        {
             return true;
        }
        else if(_qwOwnerID > sk._qwOwnerID)
        {
          return false;
        }
        return _dwXinFaID < sk._dwXinFaID;
    }
};

class CDBRoleXinFaDataTable : public TableRowBase, public SXinFaDBInfo, public CPoolObj<CDBRoleXinFaDataTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(qwOwnerID),
            UPCOL(dwXinFaID),
            UPCOL(byXinFaLvl),
            UPCOL(iSlot),
            UPCOL(Max)
        };

    public:
        CDBRoleXinFaDataTable(UINT64 qwRoleID) : _qwRoleID(qwRoleID) {}
        CDBRoleXinFaDataTable() : _qwRoleID(0){}

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

// XXX: 需要到这个函数TableManagerBaseForRole::CreateManager里去注册
class CDBRoleXinFaDataTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleXinFaDataTableManager>
{ 
    public:
        CDBRoleXinFaDataTableManager(UINT64 qwRoleID, UINT8 byLine) : TableManagerBaseForRole(eTypeXinFaInfo, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
       
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SXinFaKey, CDBRoleXinFaDataTable> _mapData; // OwnerID to PetDataTable
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SXinFaKey> _vecDelData;
};

#endif //DBROLEXINFADATATABLE_H_

