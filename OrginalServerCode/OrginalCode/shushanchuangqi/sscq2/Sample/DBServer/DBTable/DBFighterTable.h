
#ifndef DBFIGHTERTABLE_H_
#define DBFIGHTERTABLE_H_

#include "DBTableBase.h"

class CDBFighterTable : public TableRowBase, public SFighterDBInfo, public CPoolObj<CDBFighterTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwInstID),
            UPCOL(wFighterID),
            UPCOL(byRecruited),
            UPCOL(byStar),
            UPCOL(iSlot),
            UPCOL(iPos),
            UPCOL(byLevel),
            UPCOL(qwExp),
            UPCOL(byLianPi),
            UPCOL(byTongJin),
            UPCOL(byQiangJi),
            UPCOL(byDuanGu),
            UPCOL(byHuoLuo),
            UPCOL(byXiSui),
            UPCOL(dwDujieExp),
            UPCOL(dwSpiritPower),
            UPCOL(Max)
        };

    public:
        CDBFighterTable(UINT64 qwRoleID) : _qwRoleID(qwRoleID) {}
        CDBFighterTable() : _qwRoleID(0){}

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

class CDBFighterTableManager : public TableManagerBaseForRole, public CPoolObj<CDBFighterTableManager>
{ 
    public:
        CDBFighterTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeFighterInfo, qwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT64,CDBFighterTable> _mapFighterData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT64> _vecDelFighter;
};

#endif // DBFIGHTERTABLE_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

