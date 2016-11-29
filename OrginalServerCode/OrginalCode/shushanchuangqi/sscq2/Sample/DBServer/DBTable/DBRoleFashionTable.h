
#ifndef  DBROLEFASHIONTABLE_H__
#define  DBROLEFASHIONTABLE_H__
#include "DBTableBase.h"

class CDBRoleFashionTable : public TableRowBase, public CPoolObj<CDBRoleFashionTable>
{
    public:
        enum EUpdateColumn
        {
            //UPCOL(qwInstID),
            //UPCOL(qwRoleID),
            //UPCOL(byEnable),
            UPCOL(byLevel),
            UPCOL(dwExp),
            UPCOL(bySelected),
            UPCOL(byHide),
            UPCOL(Max)
        };

    public:
        CDBRoleFashionTable(UINT64 setqwRoleID):_qwRoleID(setqwRoleID){}
        CDBRoleFashionTable():_qwRoleID(0){}
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);
    public:
         bool InitDataByFashion(SFashionPtr pFashion);
    public:
        UINT64 qwInstID;
        UINT8 byLevel;
        UINT32 dwExp;
        UINT8 bySelected;
        UINT8 byHide;

    private:
        bitset<UPCOL(Max)> _setChanged;
        UINT64 _qwRoleID;
};

class CDBRoleFashionTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleFashionTableManager>
{ 
    public:
        CDBRoleFashionTableManager(UINT64 setqwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeFashionInfo,setqwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<UINT64,CDBRoleFashionTable> _mapRoleFashionData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT64> _vecDelFashion;
};
#endif

