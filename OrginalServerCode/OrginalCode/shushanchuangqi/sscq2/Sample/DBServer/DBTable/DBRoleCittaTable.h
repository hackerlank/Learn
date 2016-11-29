#ifndef DB_ROLE_CITTA_TABLE_H
#define DB_ROLE_CITTA_TABLE_H

#include "DBTableBase.h"

class DBRoleCittaTable : public TableRowBase, public CPoolObj<DBRoleCittaTable>
{
    friend class DBRoleCittaTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwInstID),
            UPCOL(qwRoleID),
            UPCOL(qwOwnerID),
            UPCOL(byAttrType1),
            UPCOL(dwAttrValue1),
            UPCOL(byAttrType2),
            UPCOL(dwAttrValue2),
            UPCOL(byAttrType3),
            UPCOL(dwAttrValue3),
            UPCOL(byAttrType4),
            UPCOL(dwAttrValue4),
            UPCOL(dwSkillID),
            UPCOL(dwSignetID),
            UPCOL(Max)
        };

    public:
        DBRoleCittaTable();
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64  GetInstID() const;
        UINT64  GetRoleID() const;
         
    public:
        bool InitDataByCitta(SCittaPtr pCitta);
    private:
        bitset<UPCOL(Max)> _setChanged;

        UINT64 _qwInstID;
        UINT64 _qwRoleID;
        UINT64 _qwOwnerID;

        UINT8  _byAttrType1;
        UINT32 _dwAttrValue1;
        UINT8  _byAttrType2;
        UINT32 _dwAttrValue2;
        UINT8  _byAttrType3;
        UINT32 _dwAttrValue3;
        UINT8  _byAttrType4;
        UINT32 _dwAttrValue4;

        UINT32 _dwSkillID;
        UINT32 _dwSignetID;
};

// XXX: 需要到这个函数TableManagerBaseForRole::CreateManager里去注册
class DBRoleCittaTableManager : public TableManagerBaseForRole, public CPoolObj<DBRoleCittaTableManager>
{ 
    public:
        DBRoleCittaTableManager(UINT64 setqwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeCittaInfo,setqwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT64,DBRoleCittaTable> _mapRoleCittaData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT64> _vecDelCitta;
};


#endif // #define DB_ROLE_CITTA_TABLE_H

