#ifndef DB_ROLE_TRUMP_H
#define DB_ROLE_TRUMP_H
#include "DBTableBase.h"

class DBRoleTrumpTable : public TableRowBase, public CPoolObj<DBRoleTrumpTable>
{
    friend class DBRoleTrumpTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwInstID),
            UPCOL(qwRoleID),
            UPCOL(byUsed),
            UPCOL(dwExp),
            UPCOL(wLevel),
            UPCOL(wRank),
            UPCOL(Max)
        };

    public:
        DBRoleTrumpTable();
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64  GetInstID() const;
        UINT64  GetRoleID() const;

    private:
        bool InitDataByTrump(STrumpPtr pTrump);
    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwInstID;
        UINT64 _qwRoleID;
        UINT8  _byUsed;
        UINT32 _dwExp;
        UINT16 _wLevel;
        UINT16 _wRank;
};

// XXX: 需要到这个函数TableManagerBaseForRole::CreateManager里去注册
class DBRoleTrumpTableManager : public TableManagerBaseForRole, public CPoolObj<DBRoleTrumpTableManager>
{ 
    public:
        DBRoleTrumpTableManager(UINT64 setqwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeTrumpInfo,setqwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT64,DBRoleTrumpTable> _mapRoleTrumpData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT64> _vecDelTrump;
};


#endif // #ifndef DB_ROLE_TRUMP_H
