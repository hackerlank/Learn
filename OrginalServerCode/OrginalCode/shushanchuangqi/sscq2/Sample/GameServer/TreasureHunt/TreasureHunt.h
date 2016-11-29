
#ifndef _TREASUREHUNT_H_
#define _TREASUREHUNT_H_
#include "TreasureHuntProt.h"
#include "Battle.h"

using namespace NTreasureHuntProt;

#define BUFF_TGSL 1
#define BUFF_BJGX 2
#define BUFF_TLHZ 3

#define BIT_MARKA 0
#define BIT_MARKB 1

#define TH_TIMER 5

#define MAX_KILLNUM 10


#define XFCY_A 108
#define XFCY_B 109
#define XFCY_C 110
#define XFCY_D 111

class CTreasureHunt : public CPoolObj<CTreasureHunt>
{

public:

   CTreasureHunt(CPlayer& rPlayer): _rPlayer(rPlayer), _byCopyID(0), _byStatus(0), _byTotalNum(0), _dwTotalTime(0), _dwLastTime(0), _dwBossMaxHP(0), _bOffLineHandleMark(false) {}
   ~CTreasureHunt() {}

public:

   //加载DB
   void LoadFromDB(
           UINT8 byCopyID,
           UINT8 byStatus,
           UINT32 dwBossCurHP,
           UINT32 dwLastTime, 
           UINT32 dwTime, 
           UINT32 dwNum, 
           string strAward
           );
   
   //请求寻宝信息
   bool ReqTHInfo(UINT8& byCopyID, ETHStatus& eTHStatus, UINT8& byKillNum, UINT8& byCurrentID);

   //获取战斗准备信息
   bool GetTHBattlePrepareInfo(
           UINT8& byKillNum, 
           UINT32& dwCurBossHP,
           UINT32& dwTotalTimes, 
           TVecTHAwardInfo& vecTHAwardInfo, 
           TVecTHBuffInfo& vecTHBuffInfo
           );
   
   //请求寻宝开始
   ETHOptResult ReqTHStart(UINT8 byCopyID);

   //请求寻宝立即完成
   bool ReqTHQuickFinish();

   //寻宝定时器
   bool THTimerCheck(UINT32 dwNow);

   //寻宝战斗准备
   bool THBattlePrepare();

   //寻宝战斗
   bool THBattle(UINT32 dwMonsterGroupID, 
           UINT64 qwMainMonsterID, UINT64 qwDefenseID, 
           TVecBattleFighterPtr& vecBattleFighter2, 
           UINT8 byCurIndex
           );

   //放弃寻宝
   bool ReqGiveUpTH();

   //使用Buff(天罡神力/驹过隙/偷梁换柱)
   bool UseBuff(UINT8 byBuffID);

   //添加寻宝奖励
   bool AddTHAward(STHAwardInfo sTHAwardInfo);
   
   //请求寻宝奖励信息
   bool ReqTHAwardInfo(UINT8& byCopyID, TVecTHAwardInfo& vecTHAwardInfo);

   //获取寻宝奖励
   bool GetTHAward();
  
   //寻宝开始/结束通知
   bool THNotify(ETHNotify eTHNotify);

   //离线寻宝处理
   bool OffLineTH(UINT32 dwBossCurHP);

   //离线寻宝战斗准备
   bool OffLineTHBattlePrepare();
   
   //离线寻宝战斗
   bool OffLineTHBattle(
           UINT32 dwMonsterGroupID,
           UINT64 qwMainMonsterID,
           UINT64 qwDefenseID, 
           TVecBattleFighterPtr& vecBattleFighter2, 
           UINT8 byCurIndex
           );
   
   //玩家离开清除寻宝信息
   bool PlayerLeaveCleanTHInfo();
   
   //玩家离开设置寻宝状态
   bool PlayerLeaveSetTHStatus();

   //清除寻宝基本信息
   bool CleanTHBaseInfo();

   //清除寻宝奖励信息
   bool CleanTHAwardInfo();

   //更新DB
   bool Update2DB(EDataChange eDataChange);

private:

   UINT8 GetTHCopyID() { return _byCopyID; }
   void SetTHCopyID(UINT8 byCopyID) { _byCopyID = byCopyID; }

   UINT8 GetTHStatus() { return _byStatus; }
   void SetTHStatus(UINT8 byStatus) { _byStatus = byStatus; }

   UINT32 GetTHTotalNum() { return _byTotalNum; }
   void SetTHTotalNum(UINT32 byTotalNum) { _byTotalNum = byTotalNum; }
   void AddTHTotalNum(UINT32 byTotalNum) { _byTotalNum += byTotalNum; }
   
   UINT32 GetTHTotalTime() { return _dwTotalTime; }
   void SetTHTotalTime(UINT32 dwTotalTime) { _dwTotalTime = dwTotalTime; }
   void AddTHTotalTime(UINT32 dwTotalTime) { _dwTotalTime += dwTotalTime; }

   UINT32 GetTHLastTime() { return _dwLastTime; }
   void SetTHLastTime(UINT32 dwLastTime) { _dwLastTime = dwLastTime; }
   
   UINT32 GetTHBossMaxHP() { return _dwBossMaxHP; }
   void SetTHBossMaxHP(UINT32 dwBossMaxHP) { _dwBossMaxHP = dwBossMaxHP; }
private:

   CPlayer& _rPlayer;
   UINT8 _byCopyID;
   UINT8 _byStatus;
   UINT32 _byTotalNum;
   UINT32 _dwTotalTime;
   UINT32 _dwLastTime;
   UINT32 _dwBossMaxHP;
   bool _bOffLineHandleMark; //处理离线寻宝标志
   
   TVecUINT32 _vecMonsterGroupID;
   TVecUINT64 _vecMonsterID;
   TVecUINT64 _vecDefenseID;
   typedef vector<TVecBattleFighterPtr> TVecBattleFighterVec;
   typedef map<UINT16, STHAwardInfo> MapTHAward;
   TVecBattleFighterVec _TVecBattleFighterVec;
   MapTHAward _MapTHAward;
};
#endif // _TREASUREHUNT_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

