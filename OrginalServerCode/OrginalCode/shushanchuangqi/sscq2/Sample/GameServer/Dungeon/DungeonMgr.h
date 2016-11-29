#pragma once
#include "DungeonCFG.h"
#include "Dungeon.h"
#include "TimesPriceCFG.h"
class CPlayerDgn;
class CPlayer;
struct SPoint;
class CDemonTowerDgn;

#define DGN_WAIT_DEL 1000* 30 * 1
#define DGN_WAIT_AWARD 1000 * 20
#define DGN_WAIT_CARD_TIME 1000 * 10
#define DGN_WAIT_SEND_AWARD 1000 * 5
#define DGN_DEFAULT_EXIST_TIMER 5*60//2*3600
struct StarAward
{
    UINT32 dwStar;//需要星级
    map<UINT16,UINT32> mapAward;
    StarAward()
    {
        dwStar = 0;
    }
};
enum DungeonCfg
{
    CleanIcon = 80,
};

class CDungeonMgr
{
    public:
        static bool Init();
        static void Destroy();
        static const SDgnInfo* GetDgnInfo(UINT16 wDgnID);
       // static CDungeonPtr CreateDungeon(UINT16 wDgnID);
        static CPlayerDgnPtr CreatePlayerDungeon(UINT16 wDgnID, CPlayer& rPlayer,EDungeonResult &eResult,bool bGM = false);
        static  EDungeonResult PlayerCanCreatePlayerDGN(UINT16 wDgnID, CPlayer& rPlayer,bool bGM = false);
        //创建镇妖塔副本
        static CDemonTowerDgnPtr CreateDemonTowerDgn(UINT16 wDgnID, CPlayer& rPlayer,EDungeonResult &eResult);
        static void DestroyDungeon(const CDungeonPtr& pDungeon);
        static void DestroyDungeon(UINT64 qwInstID);
        static CDungeonPtr GetDungeon(UINT64 qwInstID);
        static CGameMapPtr GetDungeonMap(UINT64 qwInstID);
        static void GetDungeon(UINT16 wDgnID, vector<CDungeonPtr>& rVecDungeon);
        static bool PlayerEnterDungeon(CPlayer& rPlayer, UINT64 qwInstID, SPoint* pPoint = NULL);
        static bool PlayerReEnterDungeon(CPlayer& rPlayer, UINT64 qwInstID, SPoint& rPoint);
        static EDungeonResult  PlayerEnterNewDungeon(CPlayer& rPlayer, UINT16 wDgnID, const SPoint* pPoint = NULL,bool bGM = false);
        static EDungeonResult PlayerLeaveDungeon(CPlayer& rPlayer);        static EDungeonResult PlayerFinishDungeon(CPlayer& rPlayer);

        static void TimerCheck(time_t tNow);
        //static bool CanSelectDgn(const CPlayerPtr& pPlayer, UINT16 wDgnID, UINT16* pMsgID = NULL);
        static void NotifyPlayerWait(CPlayer& rPlayer);
        //static const SRaidsCFG* GetRaidsConfig(UINT16 wRaidID);
        static bool Sweeping(CPlayer& rPlayer, UINT16 wDgnID, UINT8 byOptions);
        static bool IsBornDungeon(UINT16 wDgnID);
        static EDungeonResult CleanDGN(UINT16 wDgnID,CPlayer& rPlayer,std::vector<SItemGenInfo>* pvecItems ,TVecResource * pvecRes);
        static EDungeonResult  TestCanSweeping(UINT16 wDgnID,CPlayer& rPlayer,UINT16 wCount=1);
        static map<UINT16, SDgnInfo>& GetAllDgnInfo() { return _mapID2DgnInfo; }
        static void ClearLua();
        static void PlayerDungeonKillAll(CPlayer& rPlayer);
        static UINT32 GetAwardLootId(const SDgnInfo& rDgnInfo,bool bCost);
        static void AwardToPlayer(const SDgnInfo& rDgnInfo,UINT8 byStar,CPlayer& rPlayer,bool bIsAppend,std::vector<SItemGenInfo> *pvecItems =NULL ,TVecResource* pvecRes= NULL, UINT32 dwRewardRate = 10000);
        static bool CanCreateByDgnType(EDgnType eType);
        static UINT32 GetHeroDgnPrice(UINT32 dwTimes);
        static UINT32 GetLiXianDgnPrice(UINT32 dwTimes);
        static UINT32 GetMoneyTreePrice(UINT32 dwTimes);
        static const StarAward * GetAwardByID(UINT16 wStarID);
    private:
        static UINT64 GetNewDgnInstID();

        static map<UINT64, CDungeonPtr> _mapInst2Dgn;
        static map<UINT16, SDgnInfo> _mapID2DgnInfo;
        UINT32 _dwLastCheckSizeTimer;
        static map<UINT32,STimesPriceCFG> _mapTimesPriceCFG;
        static map<UINT16,StarAward> _mapStarAward;
        
        //static map<UINT16, SRaidsCFG> _mapID2RaidsCfg;
        //static map<UINT32, UINT32> _mapDgnID2RoomID;
};

