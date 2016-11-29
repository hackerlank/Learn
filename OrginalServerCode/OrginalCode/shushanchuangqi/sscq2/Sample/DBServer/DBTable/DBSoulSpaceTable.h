#ifndef DB_SOULSPACE_TABLE_H
#define DB_SOULSPACE_TABLE_H
#include "DBTableBase.h"

#include "ProtoCommon.h"

using namespace NProtoCommon;

struct SSoulSpaceKey
{
    SSoulSpaceKey(UINT64 qwRoleID,UINT32 dwSoulSpaceID)
        : _qwRoleID(qwRoleID),_dwSoulSpaceID(dwSoulSpaceID) {}

    UINT64  _qwRoleID;
    UINT32  _dwSoulSpaceID;

    bool operator < (const SSoulSpaceKey& sk) const
    {
        if (_qwRoleID !=  sk._qwRoleID)
            return _qwRoleID < sk._qwRoleID;
        return _dwSoulSpaceID< sk._dwSoulSpaceID;
    }
};

class CDBSoulSpaceTable : public TableRowBase, public SSoulSpaceInfo, public CPoolObj<CDBSoulSpaceTable>
{
    friend class CDBSoulSpaceTableManager;
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(dwSoulSpaceID),
            UPCOL(dwSoulSpaceLevel),
            UPCOL(Max)
        };

    public:
        CDBSoulSpaceTable();
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);

        UINT64  GetRoleID() const;

    private:
        bool InitDataBySoulSpace(const SSoulSpaceInfo& rSoulSpaceInfo);
    private:
        bitset<UPCOL(Max)> _setChanged;

};

// XXX: 需要到这个函数TableManagerBaseForRole::CreateManager里去注册
class CDBSoulSpaceTableManager : public TableManagerBaseForRole, public CPoolObj<CDBSoulSpaceTableManager>
{ 
    public:
        CDBSoulSpaceTableManager(UINT64 setqwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeSoulSpaceInfo,setqwRoleID,byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SSoulSpaceKey,CDBSoulSpaceTable> _mapSoulSpaceData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SSoulSpaceKey> _vecDelSoulSpace;
};


#endif // #ifndef DB_BUFF_TABLE_H
