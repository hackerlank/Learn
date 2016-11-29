
#ifndef DBTRIPODFIRETABLE_H__ 
#define DBTRIPODFIRETABLE_H__

#include "DBTableBase.h"
#include "TripodProt.h"

using namespace NTripodProt;

struct SFireKey
{
    SFireKey(UINT64 qwRoleID,UINT16 wFireID)
        : qwRoleID(qwRoleID), wFireID(wFireID) {}

    UINT64  qwRoleID;
    UINT16  wFireID;

    bool operator < (const SFireKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        return wFireID < sk.wFireID;
    }
};


class CDBTripodFireTable : public TableRowBase, public SFireInfo, public CPoolObj<CDBTripodFireTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(wFireID   ),
            UPCOL(dwSucceed ),
            UPCOL(dwRemain  ),
            UPCOL(Max       )
        };

    public:
        CDBTripodFireTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBTripodFireTable():_qwRoleID(0){}
        void InitDataByBase(const SFireInfo &rInfo);
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

class CDBTripodFireTableManager : public TableManagerBaseForRole, public CPoolObj<CDBTripodFireTableManager>
{ 
    public:
        CDBTripodFireTableManager(UINT64 qwRoleID, UINT8 byLine) : TableManagerBaseForRole(eTypeTripodFireInfo, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SFireKey,CDBTripodFireTable> _mapTripodFireData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SFireKey> _vecDelTripodFire;
};

#endif // DBTRIPODFIRETABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

