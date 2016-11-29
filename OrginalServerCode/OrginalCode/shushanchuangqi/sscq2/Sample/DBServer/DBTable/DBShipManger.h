#ifndef  DBTOTAL_SHIP_TABLE_H__
#define  DBTOTAL_SHIP_TABLE_H__
#include "DBTableBase.h"
#include "ShipProt.h"
using namespace NShipProt;
class CDBTotalShip : public PlayerShip, public CPoolObj<CDBTotalShip>
{
    public:
        enum EUpdateColumn
        {	
            UPCOL(dwOwerPoint), //金船拥有者战斗力
            UPCOL(byOwerLevel), //拥有者等级
            UPCOL(byOwerColor), //拥有者颜色
            UPCOL(byChannel), //航道
            UPCOL(wShipId), //金船模板
            UPCOL(qwDefense), //护送者ID
            UPCOL(dwDefensePoint), //护送者战斗力
            UPCOL(byDefenseLevel), //护送者等级
            UPCOL(byDefenseColor), //护送者颜色
            UPCOL(qwRoBId1), //打劫者1
            UPCOL(byRoB1Color), //打劫者1颜色
            UPCOL(dwRoB1Point),//打劫者1战斗力
            UPCOL(byRoB1Level),//打劫者1等级
            UPCOL(qwRoBId2), //打劫者2
            UPCOL(byRoB2Color), //打劫者2颜色
            UPCOL(dwRoB2Point),//打劫者2战斗力
            UPCOL(byRoB2Level),//打劫者2等级
            UPCOL(qwRoBId3), //打劫者3
            UPCOL(byRoB3Color), //打劫者3颜色
            UPCOL(dwRoB3Point),//打劫者3战斗力
            UPCOL(byRoB3Level),//打劫者3等级
            UPCOL(dwBeginTimer), //开船时间
            UPCOL(dwEndTimer), //结束时间
            UPCOL(dwAwardRate),//倍率

            UPCOL(Max)
        };

    public:
        CDBTotalShip():_bIsNew(false){}
        void InitDataByData(const PlayerShip & rData);
        bool UpdateDataByData(const PlayerShip & rData);
        bool GetInsertSqlStr(string& sqlstr);
        bool GetUpdateSqlStr(string& sqlstr);
        void ResetChange(void);
        void InitDataByDBRow(const mysqlpp::Row &row);
        void SetNew(bool bNew) {_bIsNew = bNew;}
        bool IsNew(){return _bIsNew;}
        bool IsChange(){ return !_setChanged.none();}
    private:
        bitset<UPCOL(Max)> _setChanged;
        bool _bIsNew;

};


class CDBTotalShipManager : public CPoolObj<CDBTotalShipManager>
{ 
    public:
        CDBTotalShipManager():_dwQueryFighterMax(0){}
        void GetAllShip(UINT32 dwPageSize);
        void QueryData(UINT32 dwPageSize,QueryFun fun);
        void SendDataToCenter(UINT32 dwTotalPage,UINT32 dwPageSize);
        void DelData(UINT64 qwInsID);
        void UpdateData(const PlayerShip &stData);
        void DumpToDB(bool bForBit =false);
        UINT32 GetUpdataNum();
    private:
        map<UINT64,CDBTotalShip> _mapRoleShipData;
        vector<UINT64> _vecDelShip;
        UINT32 _dwQueryFighterMax;
};
extern CDBTotalShipManager g_CDBTotalShipManager;
#endif

