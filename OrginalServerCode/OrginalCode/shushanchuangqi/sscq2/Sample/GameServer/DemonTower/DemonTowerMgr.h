#pragma once
#include "stdafx.h"
#include <memory>
#include <map>
#include "DemonTowerSvr.h"
#include "DemonTowerCFG.h"
#include "SoulSpaceCFG.h"
#include "DemonTowerGS.h"
#include "ItemProt.h"
class CGameMap;
class CPlayer;
struct SPoint;
using namespace NDemonTower;
using namespace NDemonTowerGS;
using namespace NItemProt;
enum
{
    MAX_POSITON = 10,  //最大装备位
    MAX_FLOORID = 20,  //最高楼层
    ATTCK_CD    = 60*5,//攻击cd间隔 5分钟
    PRIZE_CD    = 60*10, //奖励时间 10分钟
    MIN_PRIZE_TIMESPAN = 3600, // 1小时
};

struct SDemonTowerCFGEx:public SDemonTowerCFG
{
    
    TVecMoneyInfo vecDayPrize;
    TVecMoneyInfo vecPassPrize;
 
    //额外奖励
    TVecItemGenInfo vecExtraPrize;

    //item
    TVecMoneyInfo vecPrize;
    SDemonTowerCFGEx(const SDemonTowerCFG* pDemonTowerCFG)
    {
        *(SDemonTowerCFG*)this = *pDemonTowerCFG;
    }
};

typedef std::shared_ptr<SDemonTowerCFGEx> SDemonTowerCFGExPtr;   
typedef std::vector<SDemonTowerCFGExPtr> TVecDemonTowerCFGExPtr;

struct SSoulSpaceCFGEx:public SSoulSpaceCFG
{
    TVecFloat _vecAttr;
    SSoulSpaceCFGEx(const SSoulSpaceCFG* pSoulSpaceCFG)
    {
        *(SSoulSpaceCFG*)this = *pSoulSpaceCFG;
    }
};

typedef std::shared_ptr<SSoulSpaceCFGEx> SSoulSpaceCFGExPtr;   
typedef std::map<UINT32,SSoulSpaceCFGExPtr> TMapSoulSpaceCFGEx;



//锁妖塔
class CDemonTowerMgr 
{
public:
    CDemonTowerMgr();
    virtual ~CDemonTowerMgr();
    
    //加载基础数据
    bool Init();
    bool ReLoadConfig(const string &);

    void TimerCheck(UINT64 qwTick);
   

    //进入锁妖塔
    UINT32  PlayerEnter(CPlayer& rPlayer, UINT32 dwFloorID);
  
    //离开锁妖塔
    UINT32  PlayerLeave(CPlayer& rPlayer);

    //封印怪物
    UINT32  AttackMonster(CPlayer& rPlayer, UINT32 dwFloorID);
    
    //镇守
    UINT32  Guard(CPlayer& rPlayer,UINT32 dwFloorID,UINT32 dwPos);
   
    //抢夺镇守位置
    UINT32  AtkPlayer(CPlayer& rPlayer,UINT32 dwFloorID,UINT32 dwPos);

    //上一层
    void   PlayerEnterNextFloor(CPlayer& rPlayer);

    //下一层
    void   PlayerEnterLowFloor(CPlayer& rPlayer);

    //每日重置更新
    void   OnDayResetNotify(CPlayer& rPlayer);

    //领取每日过关奖励
    UINT32 TakeSealPrize(CPlayer& rPlayer);
    
    //领取过每日镇守奖励
    UINT32  TakePassDayPrize(CPlayer& rPlayer);

    //过关奖励
    UINT32  TakePassPrize(CPlayer& rPlayer,UINT32 dwFloorID);

    //每层奖励
    UINT32  TakeLayerPrize(CPlayer& rPlayer,UINT32 dwFloorID,UINT32& dwCurPrizeFloorID);

    //已经领奖层数`
    void OnGetLayerPrized(CPlayer& rPlayer,TVecUINT32& vecFloorID);

    
    //领取镇守失败奖励
    UINT32  TakeGuardFailPrize(CPlayer& rPlayer);
    SDemonTowerCFGExPtr GetDemonTowerCFG(UINT32 dwFloorID);
    
    //魄空间配置
    SSoulSpaceCFGExPtr   GetSoulSpaceCFG(UINT32 dwSpaceID);

protected:
    UINT32 _dwAttackCD;
    UINT32 _dwPrizeCD;
    UINT32 _dwMinPrizeTimeSpan;

    TVecDemonTowerCFGExPtr _vecSDemonTowerCFGExPtr;
    TMapSoulSpaceCFGEx _mapSoulSpaceCFGEx;
};

extern CDemonTowerMgr g_DemonTowerMgr;


