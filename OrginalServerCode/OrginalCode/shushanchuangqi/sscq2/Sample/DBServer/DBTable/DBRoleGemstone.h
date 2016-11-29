
#ifndef  DBROLEGEMSTONEABLE_H__
#define  DBROLEGEMSTONEABLE_H__
#include "DBTableBase.h"

class CDBRoleGemstoneTable : public TableRowBase, public CPoolObj<CDBRoleGemstoneTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwOwnerID),
            UPCOL(Max)
        };

    public:
        CDBRoleGemstoneTable(UINT64 setqwRoleID):_qwRoleID(setqwRoleID){}
        CDBRoleGemstoneTable():_qwRoleID(0){}
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);
    public:
         bool InitDataByGemstone(SGemstonePtr pGemstone);
    public:
        UINT64 qwInstID;
        UINT64 qwOwnerID;
    private:
        bitset<UPCOL(Max)> _setChanged;
        UINT64 _qwRoleID;
};

class CDBRoleGemstoneTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleGemstoneTableManager>
{ 
    public:
        CDBRoleGemstoneTableManager(UINT64 setqwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeGemstone,setqwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT64,CDBRoleGemstoneTable> _mapRoleGemstoneData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT64> _vecDelGemstone;
};
#endif

