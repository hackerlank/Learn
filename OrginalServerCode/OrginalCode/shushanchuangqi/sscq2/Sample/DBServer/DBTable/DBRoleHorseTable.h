
#ifndef  DBROLEHORSETABLE_H__
#define  DBROLEHORSETABLE_H__
#include "DBTableBase.h"
#include "HorseSvr.h"
#include "RoleInfoDefine.h"
using namespace NHorse;
using namespace NRoleInfoDefine;
struct SHorseKey
{
    SHorseKey(UINT64 qwRoleID,UINT32 dwHorseID)
        : qwRoleID(qwRoleID),dwHorseID(dwHorseID) {}

    UINT64  qwRoleID;
    UINT32  dwHorseID;

    bool operator < (const SHorseKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        return dwHorseID < sk.dwHorseID;
    }
};


class CDBRoleHorseDBTable : public TableRowBase, public SHorseDB, public CPoolObj<CDBRoleHorseDBTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwUserID      ),
            UPCOL(dwHorseID     ),
            UPCOL(dwHorseLevel  ),
            UPCOL(dwPos         ),
            UPCOL(dwModelID     ),
            UPCOL(dwExp         ),
            UPCOL(dwLock        ),
            UPCOL(strModel      ),
            UPCOL(Max           )
        };

    public:
        CDBRoleHorseDBTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleHorseDBTable():_qwRoleID(0){}
        void InitDataByBase(const SHorseDB &rInfo);
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

class CDBRoleHorseDBTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleHorseDBTableManager>
{ 
    public:
        CDBRoleHorseDBTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeHorseDBInfo, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SHorseKey,CDBRoleHorseDBTable> _mapRoleHorseDBData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SHorseKey> _vecDelHorseDB;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

