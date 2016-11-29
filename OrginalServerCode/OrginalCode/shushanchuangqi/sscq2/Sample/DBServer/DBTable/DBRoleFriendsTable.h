
#ifndef DBROLEFRIENDSTABLE_H_
#define DBROLEFRIENDSTABLE_H_

#include "DBTableBase.h"

class CDBRoleFriendsTable : public TableRowBase, public SFriendDBInfo, public CPoolObj<CDBRoleFriendsTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(byGroup),
            UPCOL(byVIPLevel),
            UPCOL(byColor),
            UPCOL(Max)
        };

    public:
        CDBRoleFriendsTable(UINT64 qwRoleID) : _qwRoleID(qwRoleID) {}
        CDBRoleFriendsTable() : _qwRoleID(0){}

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
class CDBRoleFriendsTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleFriendsTableManager>
{ 
    public:
        CDBRoleFriendsTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeFriendInfo, qwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT64, CDBRoleFriendsTable> _mapFriendsData; // OwnerID to FriendsTable
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT64> _vecDelFriends;
};

#endif // DBROLEFRIENDSTABLE_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

