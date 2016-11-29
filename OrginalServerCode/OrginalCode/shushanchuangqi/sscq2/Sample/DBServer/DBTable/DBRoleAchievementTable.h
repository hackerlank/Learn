
#ifndef  DBROLEACHIEVEMENTTABLE_H__
#define  DBROLEACHIEVEMENTTABLE_H__
#include "DBTableBase.h"
#include "AchievementProt.h"
#include "RoleInfoDefine.h"
using namespace NAchievementProt;
using namespace NRoleInfoDefine;
struct SAchieveKey
{
    SAchieveKey(UINT64 qwRoleID,UINT16 wAchievementID)
        : qwRoleID(qwRoleID),wAchievementID(wAchievementID) {}

    UINT64  qwRoleID;
    UINT16  wAchievementID;

    bool operator < (const SAchieveKey& sk) const
    {
        if (qwRoleID !=  sk.qwRoleID)
            return qwRoleID < sk.qwRoleID;
        return wAchievementID < sk.wAchievementID;
    }
};


class CDBRoleAchievementTable : public TableRowBase, public SAchievementInfo, public CPoolObj<CDBRoleAchievementTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(qwRoleID      ),
            UPCOL(wAchievementID),
            UPCOL(dwCount       ),
            UPCOL(dwProcess     ),
            UPCOL(dwFinishTime  ),
            UPCOL(Max           )
        };

    public:
        CDBRoleAchievementTable(UINT64 qwRoleID):_qwRoleID(qwRoleID){}
        CDBRoleAchievementTable():_qwRoleID(0){}
        void InitDataByBase(const SAchievementInfo &rInfo);
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

class CDBRoleAchievementTableManager : public TableManagerBaseForRole, public CPoolObj<CDBRoleAchievementTableManager>
{ 
    public:
        CDBRoleAchievementTableManager(UINT64 qwRoleID,UINT8 byLine) : TableManagerBaseForRole(eTypeAchievementInfo, qwRoleID, byLine), _nNowQuery(0), _nMaxQuery(0), _nErrQuery(0) {}
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData);
        virtual void Update(string& strData, bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();

    private:
        map<SAchieveKey,CDBRoleAchievementTable> _mapRoleAchievementData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
        vector<SAchieveKey> _vecDelAchievement;
};

#endif // DBROLEITEMTABLE_H__

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

