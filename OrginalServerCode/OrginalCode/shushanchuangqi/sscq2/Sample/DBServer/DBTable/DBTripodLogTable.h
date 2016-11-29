// =====================================================================================
//
//       Filename:  DBTripodLogTable.h
//
//    Description:  九疑鼎动态历史表
//
//        Version:  1.0
//        Created:  11/21/2014 01:49:38 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef DB_TRIPOD_LOG_TABLE_H
#define DB_TRIPOD_LOG_TABLE_H

#include "DBTableBase.h"
#include "TripodProt.h"

using namespace NTripodProt;

struct SLogKey
{
    SLogKey(UINT64 qwRoleID,UINT16 wMsgID)
        : qwRoleID(qwRoleID), wMsgID(wMsgID) {}

    UINT64  qwRoleID;
    UINT16  wMsgID;

    bool operator < (const SLogKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        return wMsgID < sk.wMsgID;
    }
};


class CDBTripodLogTable : public TableRowBase, public STripodLog, public CPoolObj<CDBTripodLogTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID),
            UPCOL(wMsgID),
            UPCOL(vecString),
            UPCOL(vecParam),
            UPCOL(dwTime),
            UPCOL(Max)
        };

    public:
        CDBTripodLogTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBTripodLogTable():_qwRoleID(0){}
        void InitDataByBase(const STripodLog &rInfo);
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);
        string _strParam;
        string _strString;
    private:
        bitset<UPCOL(Max)> _setChanged;
        UINT64 _qwRoleID;
};

typedef vector<CDBTripodLogTable> TVecDBTripodLogTable;

class CDBTripodLogTableManager : public CPoolObj<CDBTripodLogTableManager>
{ 
    public:
        CDBTripodLogTableManager() : _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(const STripodLog& oTripodLog);
        virtual void GetAllInfo(UINT64 qwRoleID, TVecTripodLog& rvecLog);
        virtual void DumpToDB();
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

        void GetAllTripodLog(UINT32 dwPageSize);
        void QueryData(UINT32 dwPageSize, QueryFun queryfun);
        void SendDataToCenter(UINT32 dwTotalPage,UINT32 dwPageSize);

    private:
        UINT64 _qwRoleID;
        map<UINT64,TVecDBTripodLogTable> _mapTripodLog;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        TVecUINT64 _vecDelTripodLog;
};

extern CDBTripodLogTableManager g_CDBTripodLogTableManager;
#endif

