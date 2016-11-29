#ifndef DBGUARDTABLE_H_
#define DBGUARDTABLE_H_

#include "DBTableBase.h"
#include "GuardEMeiProt.h"

using namespace NGuardEMeiProt;

struct SGEMKey
{
    SGEMKey(UINT64 qwRoleID, UINT16 wMissionID)
        :_qwRoleID(qwRoleID), _wMissionID(wMissionID) {}

    UINT64 _qwRoleID;
    UINT16 _wMissionID;
    

    bool operator < (const SGEMKey& sk) const
    {
        if (_qwRoleID < sk._qwRoleID)
        {
           return true;
        }
        else if (_qwRoleID > sk._qwRoleID)
        {
            return false;
        }

        return _wMissionID < sk._wMissionID;
    }
};

class CDBGuardEMeiTable : public TableRowBase, public SGEMDBInfo, public CPoolObj<CDBGuardEMeiTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(wMissionID),
            UPCOL(byGEMType),
            UPCOL(wCurProgress),
            UPCOL(wGuardProgress),
            UPCOL(dwGuardMonsterGroupID),
            UPCOL(dwSweepEndTime),
            UPCOL(strBuff),
            UPCOL(Max)
        };

    public:
        CDBGuardEMeiTable(UINT64 qwRoleID) : _qwRoleID(qwRoleID) {}
        CDBGuardEMeiTable() : _qwRoleID(0){}

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
class CDBGuardEMeiTableManager : public TableManagerBaseForRole, public CPoolObj<CDBGuardEMeiTableManager>
{ 
    public:
        CDBGuardEMeiTableManager(UINT64 qwRoleID, UINT8 byLine) : TableManagerBaseForRole(eTypeGuardEMei, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
       
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SGEMKey, CDBGuardEMeiTable> _mapData; // OwnerID to PetDataTable
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SGEMKey> _vecDelData;
};

#endif //DBTREASUREHUNTTABLE_H_



