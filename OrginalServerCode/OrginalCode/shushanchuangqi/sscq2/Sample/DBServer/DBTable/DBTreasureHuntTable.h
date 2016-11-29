#ifndef DBTREASUREHUNTTABLE_H_
#define DBTREASUREHUNTTABLE_H_

#include "DBTableBase.h"
#include "TreasureHuntProt.h"

using namespace NTreasureHuntProt;

struct STHKey
{
    STHKey(UINT64 qwRoleID, UINT8 byCopyID)
        :_qwRoleID(qwRoleID), _byCopyID(byCopyID) {}

    UINT64 _qwRoleID;
    UINT8 _byCopyID;
    

    bool operator < (const STHKey& sk) const
    {
        if (_qwRoleID < sk._qwRoleID)
        {
           return true;
        }
        else if (_qwRoleID > sk._qwRoleID)
        {
            return false;
        }

        return _byCopyID < sk._byCopyID;
    }
};

class CDBTreasureHuntTable : public TableRowBase, public STHDBInfo, public CPoolObj<CDBTreasureHuntTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(byCopyID),
            UPCOL(byStatus),
            UPCOL(dwBossCurHP),
            UPCOL(dwLastTime),
            UPCOL(dwTime),
            UPCOL(dwNum),
            UPCOL(strAward),
            UPCOL(Max)
        };

    public:
        CDBTreasureHuntTable(UINT64 qwRoleID) : _qwRoleID(qwRoleID) {}
        CDBTreasureHuntTable() : _qwRoleID(0){}

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
class CDBTreasureHuntTableManager : public TableManagerBaseForRole, public CPoolObj<CDBTreasureHuntTableManager>
{ 
    public:
        CDBTreasureHuntTableManager(UINT64 qwRoleID, UINT8 byLine) : TableManagerBaseForRole(eTypeTH, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
       
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<STHKey, CDBTreasureHuntTable> _mapData; // OwnerID to PetDataTable
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<STHKey> _vecDelData;
};

#endif //DBTREASUREHUNTTABLE_H_



