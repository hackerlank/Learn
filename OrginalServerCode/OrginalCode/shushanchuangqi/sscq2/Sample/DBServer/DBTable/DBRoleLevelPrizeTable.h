
#ifndef  DBROLELEVELPRIZETABLE_H__
#define  DBROLELEVELPRIZETABLE_H__
#include "DBTableBase.h"
#include "LevelPrizeSvr.h"
#include "RoleInfoDefine.h"
using namespace NLevelPrize;
using namespace NRoleInfoDefine;
struct SLevelPrizeKey
{
    SLevelPrizeKey(UINT64 qwRoleID,UINT16 wActID,UINT16 wLevel)
        : qwRoleID(qwRoleID),wActID(wActID),wLevel(wLevel) {}

    UINT64  qwRoleID;
    UINT16  wActID;
    UINT16  wLevel;

    bool operator < (const SLevelPrizeKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        if(wLevel != sk.wLevel)
            return wLevel < sk.wLevel;
        return wActID < sk.wActID;
    }
};


class CDBRoleLevelPrizeDBTable: public TableRowBase, public SPrize2DB, public CPoolObj<CDBRoleLevelPrizeDBTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID      ),
            UPCOL(wActID        ),
            UPCOL(wLevel        ),
            UPCOL(wStatus       ),
            UPCOL(Max           )
        };

    public:
        CDBRoleLevelPrizeDBTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleLevelPrizeDBTable():_qwRoleID(0){}
        void InitDataByBase(const SPrize2DB &rInfo);
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

class CDBRoleLevelPrizeTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleLevelPrizeTableManager>
{ 
    public:
        CDBRoleLevelPrizeTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeLevelPrize, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SLevelPrizeKey,CDBRoleLevelPrizeDBTable> _mapRoleLevelPrizeDBData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SLevelPrizeKey> _vecDel;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

