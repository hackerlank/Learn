
#ifndef  DBROLEFIGHTFORMATIONABLE_H__
#define  DBROLEFIGHTFORMATIONABLE_H__
#include "DBTableBase.h"
#include "RoleInfoDefine.h"
using namespace NRoleInfoDefine;
struct SFightFormationKey
{
    SFightFormationKey(UINT64 qwRoleID,UINT16 wBattleType)
        : qwRoleID(qwRoleID),wBattleType(wBattleType) {}

    UINT64  qwRoleID;
    UINT16  wBattleType;

    bool operator < (const SFightFormationKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        return wBattleType < sk.wBattleType;
    }
};


class CDBRoleFightFormationTable : public TableRowBase, public SFightFormationDBInfo, public CPoolObj<CDBRoleFightFormationTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID      ),
            UPCOL(wBattleType       ),
            UPCOL(wFormationID      ),
            UPCOL(strBattlePosInfo     ),
            UPCOL(Max           )
        };

    public:
        CDBRoleFightFormationTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleFightFormationTable():_qwRoleID(0){}
        void InitDataByBase(const SFightFormationDBInfo &rInfo);
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

class CDBRoleFightFormationTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleFightFormationTableManager>
{ 
    public:
        CDBRoleFightFormationTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeFightFormation, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SFightFormationKey,CDBRoleFightFormationTable> _mapRoleFightFormationData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SFightFormationKey> _vecDelFightFormation;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

