#pragma once
#include "stdafx.h"
#include <map>
#include "DemonTowerGS.h"
#include "DemonTowerGSSvr.h"
#include "DemonTowerCFG.h"
#include "Protocols.h"
#include "Game2CenterDemonTower.h"
#include "CenterDataMgr.h"
using namespace NGame2CenterDemonTower;
using namespace NDemonTowerGS;
namespace NGame2CenterDemonTower
{
    struct SDemonTowerEnterPlayer;
};
using namespace NGame2CenterDemonTower;
enum
{
    MAX_POSITON = 10,  //最大装备位
    MAX_FLOORID = 100+1,  //最高楼层 100层
    ATTCK_CD    = 60*5,//攻击cd间隔 5分钟
    PRIZE_CD    = 60*10, //奖励时间 10分钟
    MIN_PRIZE_TIMESPAN = 3600, // 1小时
    MIN_TOP_SIZE = 3,   //通关排序
};

const double MAX_RATE = 10000.0;

struct SDemonTowerCFGEx:public SDemonTowerCFG
{
    TVecMoneyInfo vecDayPrize;
    TVecMoneyInfo vecPassPrize;
    //额外奖励
    //item
    TVecMoneyInfo vecPrize;
    SDemonTowerCFGEx(const SDemonTowerCFG* pDemonTowerCFG)
    {
        *(SDemonTowerCFG*)this = *pDemonTowerCFG;
    }
};

typedef std::shared_ptr<SDemonTowerCFGEx> SDemonTowerCFGExPtr;
typedef std::vector<SDemonTowerCFGExPtr> TVecSDemonTowerCFGExPtr;

struct SDemonTowerFloorInfo
{
    UINT32 dwFloorID;
    UINT32 dwMaxPos;
    bool   bCanAtk;
    GuardInfo arGuardInfo[MAX_POSITON];
    SDemonTowerFloorInfo()
    {
        dwFloorID = 0;
        dwMaxPos = 1;
        bCanAtk = true;
        for(UINT32 i=0; i< MAX_POSITON; i++)
        {
            arGuardInfo[i].dwGuardPos = i;
        }
    }
};


typedef std::shared_ptr<SDemonTowerPlayer> DemonTowerUserPtr;

typedef std::map<UINT64,DemonTowerUserPtr> TMapDemonTowerUserPtr;

//锁妖塔
class CDemonTowerMgr 
{
public:
    enum EGainPrize
    {
        eGainPrize_Error,
        eGainPrize_SUCESS,
        eGainPrize_RESET,
    };
    CDemonTowerMgr();
    virtual ~CDemonTowerMgr();
    
    //加载基础数据
    bool Init();

    bool ReloadTable();//重新加载表格
    void TimerCheck(UINT64 qwTick);
   
    void LoadFromDB();

    void OnLoad(const TVecDemonTowerPlayer& vecDemonTowerPlayer);

    void OnLoad_MinTurns(const SCenterData& oCenterData);

    void OnLoad_MinBattlePoint(const SCenterData& oCenterData);

    void Update2DB(ECenterData eCenterData,UINT32 dwFloorID,UINT32 dwNo,SDemonTowerKillMonster& rSDemonTowerKillMonster,bool bDelete = false);

    bool GetDemonTowerInfo(UINT64 qwUserID,SDemonTowerPlayer& rSDemonTowerPlayer);

    //进入锁妖塔
    UINT32  PlayerEnter(UINT64 qwUserID, UINT32 dwFloorID);
  
    UINT32  OnPlayerEnter(const SDemonTowerEnterPlayer& oDemonTowerEnterPlayer);

    UINT32 onPlayerEnterNextFloor(UINT32 qwUserID);
    
    //离开锁妖塔
    UINT32  PlayerLeave(UINT64 qwUserID);
    void  OnPlayerLeave(UINT64 qwUserID);
   
    //过关
    void OnPlayerPass(UINT64 qwUserID,UINT16 wFloorID,UINT16 wMonsterColor, const std::string& strMonsterName);    

    //void RemoveSameUser(TVecDemonTowerKillMonster& vecKillMonster,UINT64 qwUserID,ECenterData eCenterData);
    //
    bool IsNeedUpdate(TVecDemonTowerKillMonster& vecKillMonster,SDemonTowerKillMonster& rKillMonster,UINT16 wFloorID,ECenterData eCenterData);

    //击败锁妖塔怪物
    void OnKillMonster(const SDemonTowerPassPlayer& oDemonTowerPassPlayer);

    //获取过关信息
    void OnGetPassInfo(UINT16 wFloorID,TVecDemonTowerKillMonster& vecMinRound,TVecDemonTowerKillMonster& vecMinBattlePoint);
    
    //每天重置
    void OnReset();
    void OnResetPlayer(DemonTowerUserPtr& pGuardPlayer); 
    
    //镇守
    UINT32  Guard(UINT64 qwUserID,UINT32 dwFloorID,UINT32 dwPos);
   
    UINT32  OnGuard(UINT64 qwUserID,UINT32 dwFloorID,UINT32 dwPos);

    //抢夺镇守位置
    UINT32  AtkPlayer(UINT64 qwUserID,UINT32 dwFloorID,UINT32 dwPos);

    UINT32  OnAtkPlayer(UINT64 qwUserID,UINT32 dwFloorID,UINT32 dwPos);

    UINT32  AbandonGuard(UINT64 qwUserID,bool bReset= false);
    
    //镇守位改变
    UINT32  OnChangePos(UINT64 qwUserID,UINT32 dwFloorID,UINT32 dwPos);

    //领取每日过关奖励
    UINT32 TakeSealPrize(UINT64 qwUserID);
    
    //领取过每日镇守奖励
    UINT32  TakePassDayPrize(UINT64 qwUserID);
    
    //领取镇守失败奖励
    UINT32  TakeGuardFailPrize(UINT64 qwUserID);

    //获取镇守榜
    void GetTopList(UINT16 wPage,UINT16 wPageItemCount,SDemonFloorPage& oDemonFloorPage);

    UINT16 GetTopGuardFloorID();

    //恢复
    void Restore(UINT64 qwUserID,UINT32 dwItemCount);
    void OnRestore(UINT64 qwUserID,UINT32 dwItemCount);

    //增加聚魂速度
    void AddSpeed(UINT64 qwUserID,UINT32 dwItemCount);
    void OnAddSpeed(UINT64 qwUserID,UINT32 dwItemCount,UINT32 dwAddTime);    

    //减弱属性
    void OnReduceAttr(DemonTowerUserPtr pDemonTowerUser,GuardInfo& rGuardInfo);

    //产生奖励
    UINT32 OnGainPrize(DemonTowerUserPtr pDemonTowerUser,GuardInfo& rGuardInfo);

    //gm set
    void  GMSet();     

    void  GuardInfoChangeNotify(UINT32 dwFloorID,UINT32 dwPos,UINT64 qwUserID,GuardInfo& oGuardInfo);

    void  GuardInfoNotify(const SDemonTowerFloorInfo* pDemonTowerFloorInfo);
   
    //群发层消息
    void  SendPkgToFloor(UINT32 dwFloorID,const string& strPkg);

    //群发消息
    void  SendPkg(const string& strPkg);


    //bToSelfOnly 是否仅给自己发更新信息
    void  PlayerInfoNotify(DemonTowerUserPtr pDemonTowerUser,bool bToSelfOnly,bool bSaveToDB = true);

    void  GetGuardInfo(UINT32 dwFloorID,TVecGuardInfo& vecGuardInfo);
//private:

    // @VecMoneyInfo的数据会被覆盖
    void CalGuildPrize(DemonTowerUserPtr& pDemonTowerUser, TVecMoneyInfo& VecMoneyInfo,float fRate=1.0);
    
    SDemonTowerCFGExPtr GetDemonTowerCFG(UINT32 dwFloorID);

    SDemonTowerFloorInfo* GetFloorInfo(UINT32 dwFloorID);

    DemonTowerUserPtr GetTowerUserInfoByUserId(UINT64 qwUserID);

    void RemoveUser(UINT64 qwUserID);

    void FullPlayerInfo(DemonTowerUserPtr pDemonTowerUser,SDemonFloorPlayer& oDemonFloorPlayer);

    //获取玩家镇守的层
    UINT32 GetPlayerGuardLayerID(UINT64 qwUserID);

    UINT8 GetPlayerInfo(UINT64 qwUserID,SDemonFloorPlayer& oDemonFloorPlayer);

    //
    void OnResetBuyTime(UINT64 qwUserID);

    UINT8 OnClearFightCd(UINT64 qwUserID,shared_func<CDemonTowerGSSvr::SClearFightCdAck>& fnAck);
    

    //初始化
    void OnGuardInit(DemonTowerUserPtr pDemonTowerUser);

    void OnGuardEnd(DemonTowerUserPtr pDemonTowerUser);
    
    bool _bOpenLog;

    //上线
    void OnLogin(CUser& rUser);

    //下线
    void OnOffLine(UINT64 qwUserID);

protected:
    UINT32 _dwAttackCD;
    UINT32 _dwPrizeCD;
    UINT32 _dwMinPrizeTimeSpan;

    UINT32 _dwResetTime;

    // 更新时钟
    UINT32 _dwReduceAttrTime;

    //
    UINT32 _dwLastSubSpeedTime;

    TMapDemonTowerUserPtr _mapDemonTowerUserPtr;

    //从1层开始0不用
    SDemonTowerFloorInfo _arFloorInfo[MAX_FLOORID];

    TVecSDemonTowerCFGExPtr _vecSDemonTowerCFGExPtr;

    //最小回合通关
    TVecDemonTowerKillMonster _arMinRound[MAX_FLOORID];
    //TMapFloorID2KillMonster _mapMinRound;

    //最小战斗力
    //TMapFloorID2KillMonster _mapMinBattlePoint;
    TVecDemonTowerKillMonster _arMinBattlePoint[MAX_FLOORID];

};

extern CDemonTowerMgr g_DemonTowerMgr;


