#ifndef DB_ROLE_BUBBLE_H
#define DB_ROLE_BUBBLE_H
#include "DBTableBase.h"
#include "RoleInfoDefine.h"

using namespace NRoleInfoDefine;

class CDBRoleBubbleTable : public TableRowBase, public CPoolObj<CDBRoleBubbleTable>
{
    friend class CDBRoleBubbleTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(qwTransID),
            UPCOL(wMsgID),
            UPCOL(vecString),
            UPCOL(vecParam),
            UPCOL(dwTime),
            UPCOL(Max)
        };

    public:
        CDBRoleBubbleTable();
        virtual ~CDBRoleBubbleTable();
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64  GetRoleID() const;
        UINT64  GetTransID() const;
        UINT16  GetMsgID() const;
        const string& GetParam() const;
        const string& GetString() const;
        UINT32  GetTime() const;

    private:
        bool InitDataByBubble(const SDBBubbleInfo&sBubble);
    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwRoleID;
        UINT64 _qwTransID;
        UINT16 _wMsgID;
        string _strString;
        string _strParam;
        UINT32 _dwTime;
};

// XXX: 需要到这个函数TableManagerBaseForRole::CreateManager里去注册
class CDBRoleBubbleTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleBubbleTableManager>
{ 
    public:
        CDBRoleBubbleTableManager(UINT64 qwRoleID, UINT8 byLine);
        virtual ~CDBRoleBubbleTableManager();

        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT64,CDBRoleBubbleTable> _mapBubbleData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT64> _vecDelTransID;
};


#endif // #ifndef DB_ROLE_BUBBLE_H
