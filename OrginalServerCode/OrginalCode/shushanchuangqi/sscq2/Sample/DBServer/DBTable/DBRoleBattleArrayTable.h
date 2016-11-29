
#ifndef  DBROLEBATTLEARRAYTABLE_H__
#define  DBROLEBATTLEARRAYTABLE_H__
#include "DBTableBase.h"
#include "RoleInfoDefine.h"
using namespace NRoleInfoDefine;
struct SBattleArrayKey
{
    SBattleArrayKey(UINT64 qwRoleID,UINT16 wBattleArrayID)
        : qwRoleID(qwRoleID),wBattleArrayID(wBattleArrayID) {}

    UINT64  qwRoleID;
    UINT16  wBattleArrayID;

    bool operator < (const SBattleArrayKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        return wBattleArrayID < sk.wBattleArrayID;
    }
};


class CDBRoleBattleArrayTable : public TableRowBase, public SBattleArrayDBInfo, public CPoolObj<CDBRoleBattleArrayTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID      ),
            UPCOL(wBattleArrayID       ),
            UPCOL(dwBattleArrayLevelID      ),
            UPCOL(byBattleArrayStatus     ),
            UPCOL(Max           )
        };

    public:
        CDBRoleBattleArrayTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleBattleArrayTable():_qwRoleID(0){}
        void InitDataByBase(const SBattleArrayDBInfo &rInfo);
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

class CDBRoleBattleArrayTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleBattleArrayTableManager>
{ 
    public:
        CDBRoleBattleArrayTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeBattleArray, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SBattleArrayKey,CDBRoleBattleArrayTable> _mapRoleBattleArrayData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SBattleArrayKey> _vecDelBattleArray;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

