
#ifndef  DBROLEATTACKEDTABLE_H__
#define  DBROLEATTACKEDTABLE_H__
#include "DBTableBase.h"
#include "DemonTowerSvr.h"
#include "RoleInfoDefine.h"
using namespace NDemonTower;
using namespace NRoleInfoDefine;
struct SAttackedKey
{
    SAttackedKey(UINT64 qwRoleID,UINT32 dwPos)
        : qwRoleID(qwRoleID),dwPos(dwPos) {}

    UINT64  qwRoleID;
    UINT32  dwPos;

    bool operator < (const SAttackedKey& sk) const
    {
        if (qwRoleID != sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        return dwPos < sk.dwPos;
    }
};


class CDBRoleAttackedDBTable: public TableRowBase, public SRoleAttaked, public CPoolObj<CDBRoleAttackedDBTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID      ),
            UPCOL(dwPos         ),
            UPCOL(qwAtkRoleID   ),
            UPCOL(strRoleName   ),
            UPCOL(byLevel       ),
            UPCOL(dwAttackedTime),
            UPCOL(dwFighterType ),
            UPCOL(Max           )
        };

    public:
        CDBRoleAttackedDBTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleAttackedDBTable():_qwRoleID(0){}
        void InitDataByBase(const SRoleAttaked &rInfo);
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

class CDBRoleAttackedTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleAttackedTableManager>
{ 
    public:
        CDBRoleAttackedTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeAttacked, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SAttackedKey,CDBRoleAttackedDBTable> _mapRoleAttackedDBData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SAttackedKey> _vecDel;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

