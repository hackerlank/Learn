
#ifndef  DBROLELIMITPRIZETABLE_H__
#define  DBROLELIMITPRIZETABLE_H__
#include "DBTableBase.h"
#include "GodMonsterProt.h"
#include "RoleInfoDefine.h"
#include "Singleton.h"

using namespace NGodMonsterProt;
using namespace NRoleInfoDefine;
class CDBRoleLimitPrizeDBTable: public TableRowBase,public SLimitPrize2DB,public CPoolObj<CDBRoleLimitPrizeDBTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID      ),
            UPCOL(wPrizeID      ),
            UPCOL(wNum          ),
            UPCOL(Max           )
        };

    public:
        CDBRoleLimitPrizeDBTable() { }
        void InitDataByBase(const SLimitPrize2DB &rInfo);
        virtual void InitDataByStr(string& strData);
        virtual bool UpdateDataByStr(string& strData);
        virtual bool GetInsertSqlStr(string& sqlstr);
        virtual bool GetUpdateSqlStr(string& sqlstr);
        virtual void ResetChange(void);
        virtual void InitDataByDBRow(const mysqlpp::Row &row);
    private:
        bitset<UPCOL(Max)> _setChanged;
};

class CDBRoleLimitPrizeTableManager : public Singleton<CDBRoleLimitPrizeTableManager>
{ 
    public:
        CDBRoleLimitPrizeTableManager(UINT8 byLine = 0) : _byLine(byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        //void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        void QueryData();
        void DelData(const SLimitPrize2DB& oLimitPrize);
        void Update(const SLimitPrize2DB& oLimitPrize);
        void GetALLInfo(TVecLimitPrize2DB& rData);
        void DumpToDB();
        UINT32 GetUpdataNum();

    private:
        vector<CDBRoleLimitPrizeDBTable> _vecData;
        UINT8 _byLine;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

