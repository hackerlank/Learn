
#ifndef  DBROLEFIGHTHEROTABLE_H__
#define  DBROLEFIGHTHEROTABLE_H__
#include "DBTableBase.h"
#include "RoleInfoDefine.h"
using namespace NRoleInfoDefine;
struct SFightHeroKey
{
    SFightHeroKey(UINT64 qwRoleID,UINT16 wBattleType,UINT64 qwInstID)
        : qwRoleID(qwRoleID),wBattleType(wBattleType),qwInstID(qwInstID) {}

    UINT64  qwRoleID;
    UINT16  wBattleType;
    UINT64  qwInstID;

    bool operator < (const SFightHeroKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        
        if (wBattleType !=  sk.wBattleType)
            return wBattleType < sk.wBattleType;

        return qwInstID < sk.qwInstID;
    }
};


class CDBRoleFightHeroTable : public TableRowBase, public SFightHeroDBInfo, public CPoolObj<CDBRoleFightHeroTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID      ),
            UPCOL(wBattleType   ),
            UPCOL(qwInstID      ),
            UPCOL(dwHP          ),
            UPCOL(dwMaxHP       ),
            UPCOL(dwAura        ),
            UPCOL(Max           )
        };

    public:
        CDBRoleFightHeroTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleFightHeroTable():_qwRoleID(0){}
        void InitDataByBase(const SFightHeroDBInfo &rInfo);
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

class CDBRoleFightHeroTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleFightHeroTableManager>
{ 
    public:
        CDBRoleFightHeroTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeFightHero, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SFightHeroKey,CDBRoleFightHeroTable> _mapRoleFightHeroData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SFightHeroKey> _vecDelFightHero;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

