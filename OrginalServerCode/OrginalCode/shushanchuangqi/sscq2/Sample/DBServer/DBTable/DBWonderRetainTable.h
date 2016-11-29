
#ifndef  DBWONDERRETAINTABLE_H__
#define  DBWONDERRETAINTABLE_H__
#include "DBTableBase.h"
#include "RoleInfoDefine.h"
#include "WonderActivityProt.h"

using namespace NRoleInfoDefine;
using namespace NWonderActivityProt;
struct SWonderRetainKey
{
    SWonderRetainKey(UINT64 qwRoleID,UINT16 wActID,UINT16 wType)
        : qwRoleID(qwRoleID),wActID(wActID),wType(wType) {}

    UINT64  qwRoleID;
    UINT16  wActID;
    UINT16  wType;

    bool operator < (const SWonderRetainKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        if(wType != sk.wType)
            return wType < sk.wType;
        return wActID < sk.wActID;
    }
};

class CDBWonderRetainTable: public TableRowBase, public SRetain, public CPoolObj<CDBWonderRetainTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID      ),
            UPCOL(strName       ),
            UPCOL(strGuildName  ),
            UPCOL(wID           ),
            UPCOL(byCareer      ),
            UPCOL(bySex         ),
            UPCOL(wActID        ),
            UPCOL(wType         ),
            UPCOL(dwValue       ),
            UPCOL(dwTime        ),
            UPCOL(Max           )
        };

    public:
        CDBWonderRetainTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBWonderRetainTable():_qwRoleID(0){}
        void InitDataByBase(const SRetain &rInfo);
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

class CDBWonderRetainTableManager : public Singleton<CDBWonderRetainTableManager>
{ 
    public:
        CDBWonderRetainTableManager(UINT8 byLine = 0) : _byLine(byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        UINT32 GetUpdataNum();
        void   GetALLInfo(TVecRetain& vecRetain);
        void   DumpToDB();
        void   DelData(const SRetain& oData);
        void   Update(const SRetain&  oData,bool bIsAdd);
        void   QueryData();
        void   DelData(const UINT16& wActID);
    private:
        map<SWonderRetainKey,CDBWonderRetainTable> _mapRetainDBData;
        vector<SWonderRetainKey> _vecDel;
        UINT8 _byLine;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

