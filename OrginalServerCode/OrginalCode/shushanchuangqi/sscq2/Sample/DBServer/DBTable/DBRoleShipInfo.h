#ifndef  DBROLE_SHIP_TABLE_H__
#define  DBROLE_SHIP_TABLE_H__
#include "DBTableBase.h"
#include "ShipProt.h"
using namespace NShipProt;

class DBRoleShipTable : public TableRowBase, public PlayerSelfShipData, public CPoolObj<DBRoleShipTable>
{
    public:
        enum EUpdateColumn
        {
            UPCOL(dwBuyOpenShipTimes), //购买的运船次数
            UPCOL(dwBuyRoBShipTimes), //购买的抢劫次数
            UPCOL(dwBuyReflushShipTimes),//购买刷新次数
            UPCOL(wReflushShip), //刷出来的船
            UPCOL(qwInviteDefense), //邀请的护送者
            UPCOL(dwInviteDefenseAgreeTime), //别人同意护送的时间
            UPCOL(dwInviteDefensePoint),//被邀请人战斗力
            UPCOL(byInviteDefenseLevel),//被邀请人等级
            UPCOL(byInviteDefenseColor),//被邀请人颜色
            UPCOL(qwAgreeDefenseShipOwer), //我同意护送的船主
            UPCOL(dwAgreeDefenseShipOwerTime), //我同意护送的时间
            UPCOL(dwReflushShipTimer), //刷船时间
            UPCOL(Max)
        };

    public:
        DBRoleShipTable(UINT64 setqwRoleID):_qwRoleID(setqwRoleID){}
        DBRoleShipTable():_qwRoleID(0){}

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

class DBRoleShipTableManager : public TableManagerBaseForRole, public CPoolObj<DBRoleShipTableManager>
{ 
    public:
        DBRoleShipTableManager(UINT64 setqwRoleID,UINT8 byLine); 
        virtual void QueryDataByRoleId(UINT64 qwRoleID, QueryFun fun);
        virtual void DelData(string& strData){}
        virtual void Update(string& strData,bool bIsAdd);
        virtual void GetALLInfo(RoleDataInfo& rData);
        virtual void DumpToDB(ManagerUpdateFun fun);
        virtual UINT32 GetUpdataNum();
        //bool OnRecv_SaveOffLineShipInfo(UINT32 dwReflushShipType,UINT8 byIsFail);
    private:
        DBRoleShipTable _rShipData;
        UINT32 _nNowQuery;
        UINT32 _nMaxQuery;
        UINT32 _nErrQuery;
};
#endif

