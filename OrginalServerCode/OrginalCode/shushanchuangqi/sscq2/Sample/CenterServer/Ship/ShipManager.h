#ifndef SHIPMANAGER_H__
#define SHIPMANAGER_H__
#include "ShipProt.h"
#include "ShipCFG.h"
const UINT8 TotalChannel = 10;//航道数量
const UINT16 wShowShip = 500 ;//最多发500条船给客户端 
const UINT8 LockTime =3;//操作锁定时间
class CUser;
using namespace NShipProt;
struct SShipRate
{
    UINT16 wShip;
    UINT16 wRate;
    SShipRate()
    {
        wShip = 0;
        wRate = 0;
    }

};
typedef vector<SShipRate> TVecShipRate;
struct SShipFlush
{
    TVecShipRate vecFree;
    TVecShipRate vecCost;

};
struct RunShip
{
    PlayerShip sRunShip;
    RunShip():_dwLockTimer(0){}
    bool Lock();
    void UnLock();
    bool HasLock();
    private:
    UINT32 _dwLockTimer;
};
class CShipManager
{
    public:
        CShipManager();
        bool Init();//加载配置，向数据库发消息请求加载数据
        bool Load();
        void LoadFromDB();
        void ReciveDBShip(UINT32 dwPageSize,UINT32 dwTotalSize, const TVecPlayerShip &vecShip);//数据库加载来的运船信息
        void TimerCheck();//计时器，监控船到岸消息
        RunShip * GetShipByID(UINT64 qwShipID);//获得一条船信息
        UINT16 ReFlushShip(CUser& rUser,UINT8 byColor);
        UINT16 ReFlushShipByVip(CUser& rUser,UINT8 byColor);
        const SShipCFG * GetConfigById(UINT16 wShip);
        UINT64 GetShipByOwer(UINT64 qwRoleID);
        UINT64 GetShipByDefense(UINT64 qwRoleID);
        bool  OpenShip(CUser& rUser);//请求开船
        void ArriveShip(const PlayerShip& rShip);//船到站
        void CreateClientShipReport(ShipReportForClient & rClient,const ShipReport& rPort,NBattleGS::EBattleResult eResult = NBattleGS::EBResultNone);
        void RobShip(UINT64 qwShip,CUser& rUser,NBattleGS::EBattleResult eResult,UINT64 qwBattleID);
        void GrabShip(UINT64 qwShip,CUser& rUser,UINT64 qwROBID,NBattleGS::EBattleResult eResult,UINT64 qwBattleID);
        void GetRobID(const PlayerShip& rShip,TSetUINT64& setRoB) const; 
        void GetAllShipForList(UINT64 qwRoleID,TVecPlayerShipForList &rVec);
        void CloseNoticeShip(UINT64 qwRoleID);
        void GetListItem(const PlayerShip& rShip,PlayerShipForList & rItem); 
        bool FinishShip(UINT64 qwShipID);
        void GetPlayerShipForClient(const PlayerShip& rShip,PlayerShipForClient &rClient);
        void SetAwardRate(UINT32 dwRate);
    private:
        void AddShipToList(const PlayerShip& sRunShip);
        void CreateReport(const PlayerShip& rShip,EShipBattleSource eSource,UINT64 qwOtherID = 0,NBattleGS::EBattleResult eResult = NBattleGS::EBResultNone,UINT64 qwBattleID = 0,UINT8 byOtherColor = 0); 
    private:
        map<UINT64,RunShip> _mapAllShip;
        multimap<UINT32,UINT64> _mapTimerShip;//关联，时间，船
        map<UINT64,UINT64> _mapPlayerShip;//关联，船主，船
        map<UINT64,UINT64> _mapDefenseShip;//关联，护卫，船
        map<UINT16,SShipCFG> _mapConfig;
        map<UINT8,SShipFlush> _mapFlush;
        UINT32 ArryChannel[TotalChannel];
        TSetUINT64 _setNoticeShipPlayer; 
        UINT32 _dwAwardRate;
};
extern  CShipManager g_ShipManager;
#endif

