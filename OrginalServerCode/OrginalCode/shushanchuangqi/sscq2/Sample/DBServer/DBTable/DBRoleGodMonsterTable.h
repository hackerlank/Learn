
#ifndef  DBROLEGODMONSTERTABLE_H__
#define  DBROLEGODMONSTERTABLE_H__
#include "DBTableBase.h"
#include "GodMonsterProt.h"
#include "RoleInfoDefine.h"
#include "Singleton.h"

using namespace NGodMonsterProt;
using namespace NRoleInfoDefine;
class CDBRoleGodMonsterDBTable: public TableRowBase,public SGuildUser2DB,public CPoolObj<CDBRoleGodMonsterDBTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID      ),
            UPCOL(qwGuildID     ),
            UPCOL(dwFruit       ),
            UPCOL(dwScore       ),
            UPCOL(dwTotalScore  ),
            UPCOL(Max           )
        };

    public:
        CDBRoleGodMonsterDBTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleGodMonsterDBTable():_qwRoleID(0){}
        void InitDataByBase(const SGuildUser2DB &rInfo);
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

class CDBRoleGodMonsterTableManager : public Singleton<CDBRoleGodMonsterTableManager>
{ 
    public:
        CDBRoleGodMonsterTableManager(UINT8 byLine = 0) : _byLine(byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        //void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        void QueryData();
        void DelData(const SGuildUser2DB& oGuildUser);
        void Update(const SGuildUser2DB& oGuildUser, bool bIsAdd);
        void GetALLInfo(TVecGuildUser2DB& rData);
        void DumpToDB();
        UINT32 GetUpdataNum();

    private:
        map<UINT64,CDBRoleGodMonsterDBTable> _mapRoleGodMonsterDBData;
        UINT8 _byLine;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<UINT64> _vecDel;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

