
#ifndef  DBCENTERDATATABLE_H__
#define  DBCENTERDATATABLE_H__
#include "DBTableBase.h"
#include "HorseSvr.h"
#include "Center2DBComm.h"
using namespace NCenter2DBComm;
struct SCenterDataKey
{
    SCenterDataKey(UINT64 qwInstID,UINT64  qwInstID2,UINT16 wType)
        : qwInstID(qwInstID),qwInstID2(qwInstID2),wType(wType) {}

    UINT64  qwInstID;
    UINT64  qwInstID2;
    UINT16  wType;

    bool operator < (const SCenterDataKey& sk) const
    {
        if (qwInstID !=  sk.qwInstID)
            return qwInstID < sk.qwInstID;

        if (qwInstID2 !=  sk.qwInstID2)
            return qwInstID2 < sk.qwInstID2;
 
        return wType < sk.wType;
    }
};


class CDBCenterDataDBTable : public TableRowBase, public SCenterData, public CPoolObj<CDBCenterDataDBTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwInstID      ),
            UPCOL(qwInstID2     ),
            UPCOL(wType         ),
            UPCOL(qwParam       ),
            UPCOL(strParam      ),
            UPCOL(dwParam1      ),
            UPCOL(dwParam2      ),
            UPCOL(dwParam3      ),
            UPCOL(qwParam4      ),
            UPCOL(Max           )
        };

    public:
        CDBCenterDataDBTable(){}
        void InitDataByBase(const SCenterData &rInfo);
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);
    private:
        bitset<UPCOL(Max)> _setChanged;
};

class CDBCenterDataDBTableManager: public Singleton<CDBCenterDataDBTableManager>
{ 
    public:
        CDBCenterDataDBTableManager(UINT8 byLine=0) :_nNowQuery(0), _nMaxQuery(0), _nErrQuery(0),_byLine(byLine) {}
        void QueryData();
        void DelData(const SCenterData& oCenterData);
        void Update(const SCenterData& oCenterData);
        void GetALLInfo(TVecCenterData& vecCenterData);
        void DumpToDB();
        UINT32 GetUpdataNum();

    private:
        map<SCenterDataKey,CDBCenterDataDBTable> _mapCenterDataDBData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        UINT8  _byLine;
        vector<SCenterDataKey> _vecDelCenterData;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

