#ifndef  DBROLE_PENDRES_TABLE_H__
#define  DBROLE_PENDRES_TABLE_H__
#include "DBTableBase.h"

class DBRolePendResTable : public TableRowBase, public SPendRes, public CPoolObj<DBRolePendResTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(dwValue),
            UPCOL(bySource),
            UPCOL(byResType),
            UPCOL(dwParam),
            UPCOL(Max)
        };

    public:
        DBRolePendResTable(UINT64 setqwRoleID):_qwRoleID(setqwRoleID){}
        DBRolePendResTable():_qwRoleID(0){}

        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);
        bool OnRecv_SaveOffLinePendResInfo(UINT8 byIsFail);

    private:
        bitset<UPCOL(Max)> _setChanged;
        UINT64 _qwRoleID;
};
#define MAMK_KEY(Data,Key) \
        Key = Data.byResType + (((UINT16)Data.bySource) << 8);
#define DisPatchKey(byResType,bySource,Key) \
        byResType = (UINT8)Key; \
        bySource  =  (Key >> 8);
class DBRolePendResTableManager : public TableManagerBaseForRole, public CPoolObj<DBRolePendResTableManager>
{ 
    public:
        DBRolePendResTableManager(UINT64 setqwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypePendRes, setqwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();
        //bool OnRecv_SaveOffLinePendResInfo(UINT32 dwPendResType,UINT8 byIsFail);
    private:
        map<UINT32,DBRolePendResTable> _mapRolePendResData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT16> _vecDelPendRes;
};
#endif

