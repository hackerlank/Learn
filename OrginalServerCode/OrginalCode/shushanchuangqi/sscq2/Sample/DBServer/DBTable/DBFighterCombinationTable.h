
#ifndef DBFIGHTERCOMBINATIONTABLE_H_
#define DBFIGHTERCOMBINATIONTABLE_H_

#include "DBTableBase.h"
#include "FighterProt.h"

using namespace NFighterProt;

struct SCombinationKey
{
    SCombinationKey(UINT64 qwRoleID, UINT8 byGroupID)
        : qwRoleID(qwRoleID), byGroupID(byGroupID) {}

    UINT64 qwRoleID;
    UINT8  byGroupID;

    bool operator < (const SCombinationKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        return byGroupID < sk.byGroupID;
    }
};

class CDBFighterCombinationTable : public TableRowBase, public SFighterCombination, public CPoolObj<CDBFighterCombinationTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(byGroupID),
            UPCOL(byGroupLvl),
            UPCOL(dwGroupExp),
            UPCOL(byInLineUp),
            UPCOL(byInEMei),
            UPCOL(Max)
        };

    public:
        CDBFighterCombinationTable(UINT64 qwRoleID) : _qwRoleID(qwRoleID) {}
        CDBFighterCombinationTable() : _qwRoleID(0) {}

        void InitDataByData(const SFighterCombination& rInData);
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);
        bool IsChange() { return !_setChanged.none(); }
    private:
        bitset<UPCOL(Max)> _setChanged;
        UINT64 _qwRoleID;
};

class CDBFighterCombinationTableManager : public TableManagerBaseForRole, public CPoolObj<CDBFighterCombinationTableManager>
{
    public:
        CDBFighterCombinationTableManager(UINT64 qwRoleID, UINT8 byLine) : TableManagerBaseForRole(eTypeTripodFireInfo, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SCombinationKey,CDBFighterCombinationTable> _mapFighterCombinationData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SCombinationKey> _vecDelCombination;
};
extern CDBFighterCombinationTableManager g_CDBFighterCombinationTableManager;

#endif // DBFIGHTERCOMBINATIONTABLE_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

