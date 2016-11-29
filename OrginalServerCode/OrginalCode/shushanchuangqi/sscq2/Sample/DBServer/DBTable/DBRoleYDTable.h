
#ifndef  DBROLEYDTABLE_H__
#define  DBROLEYDTABLE_H__
#include "DBTableBase.h"
#include "RoleInfoDefine.h"
#include "RoleEnterGameProt.h"
#include "ProtoCommon.h"

using namespace NProtoCommon;

using namespace NRoleEnterGameProt;
using namespace NRoleInfoDefine;
struct SYDKey
{
    SYDKey(UINT64 qwRoleID,UINT8 byPtType,UINT8 byQQPtType)
        : qwRoleID(qwRoleID),byPtType(byPtType),byQQPtType(byQQPtType) {}

    UINT64 qwRoleID;
    UINT8  byPtType;
    UINT8  byQQPtType;

    bool operator < (const SYDKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        if(byQQPtType != sk.byQQPtType)
            return byQQPtType < sk.byQQPtType;
        return byPtType < sk.byPtType;
    }
};


class CDBRoleYDDBTable: public TableRowBase, public SPlatformParam, public CPoolObj<CDBRoleYDDBTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(byPtType),
            UPCOL(byQQPtType),
            UPCOL(byQQPtLv),
            UPCOL(bySPType),
            UPCOL(Max)
        };

    public:
        CDBRoleYDDBTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleYDDBTable():_qwRoleID(0){}
        void InitDataByBase(const SPlatformParam &rInfo);
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

class CDBRoleYDTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleYDTableManager>
{ 
    public:
        static map<UINT64, CDBRoleYDTableManager*> s_mapRoleYDTable;
    public:
        CDBRoleYDTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeYelloDiamond, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void GetAllInfo(TVecPlatformParam& rvecPlatform);
        virtual void GetAllInfo(TVecUINT64& rvecRoleID, TVecPlatformParam& rvecPlatform);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

        UINT64 GetRoleID() const { return _qwRoleID; }

    private:
        map<SYDKey,CDBRoleYDDBTable> _mapRoleYDDBData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SYDKey> _vecDel;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

