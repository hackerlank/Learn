
#ifndef _GUARDEMEI_H_
#define _GUARDEMEI_H_
#include "GuardEMeiProt.h"
#include "Battle.h"

using namespace NGuardEMeiProt;

#define BIT_MARKA 0
#define BIT_MARKB 1
#define GEM_MAX_RANDNUM 9999
#define SWEEP_TIMER 5
#define GEM_GUARD 1
#define GEM_SWEEP 2

class CGuardEMei : public CPoolObj<CGuardEMei>
{

public:

   CGuardEMei(CPlayer& rPlayer): _rPlayer(rPlayer), _byGEMType(0), _byGuardMark(0), _wMissionID(0), _wCurProgress(0), _wGuardProgress(0), _dwGuardMonsterGroupID(0), _dwSweepLastTime(0), _dwSweepEndTime(0) {}

   ~CGuardEMei() {}

public:

   //加载DB
   void LoadFromDB(const SGEMDBInfo& sGEMDBInfo);

   //请求守卫峨眉信息
   bool ReqGEMInfo(TVecGEMMissionInfo& vecGEMMissionInfo);

   //请求购买守卫峨眉进入次数
   bool BuyGEMEntryNum();

   //请求使用守卫峨眉守卫Buff
   bool ReqUseGEMGuardBuff(UINT32 dwBuffID, TVecGEMBattleFighterInfo& vecGEMBattleFighterInfo, TVecGEMBuffInfo& vecGEMBuffInfo);
    
   //请求重置守卫峨眉守卫关卡
   bool ReqResetGEMGuardMission(UINT16 wMissionID);
   
   //请求守卫峨眉守卫准备战斗信息
   bool ReqGEMGuardPrepareBattleInfo(UINT16 wMissionID, SGEMPrepareBattleInfo& sGEMPrepareBattleInfo);
   
   //请求守卫峨眉守卫战斗
   bool ReqGEMGuardBattle(UINT16 wMissionID, UINT32 dwBuffID, EGEMBattleType eGEMBattleType, EGEMBattleRet& eGEMBattleRet, SGEMPrepareBattleInfo& sGEMPrepareBattleInfo);

   //请求守卫峨眉扫荡开始
   bool ReqGEMSweepBegin(UINT16 wMissionID);
    
   //守卫峨眉扫荡定时器
   bool GEMSweepTimerCheck(UINT32 dwNow);
   
   //守卫峨眉特殊扫荡
   bool GEMSpecialSweep();

   //请求获取守卫峨眉扫荡结束(放弃扫荡)
   UINT16 ReqGEMSweepEnd(UINT16 wMissionID);

   //更新DB
   bool Update2DB(EDataChange eDataChange);

private:
    
   //守卫峨眉守卫结束战斗信息
   bool GEMGuardEndBattleInfo(SGEMPrepareBattleInfo& sGEMPrepareBattleInfo);
   
   //查找守卫峨眉守卫Buff
   bool FindGEMGuardBuff(UINT32 dwBuffID);
   
   //添加守卫峨眉守卫Buff
   bool AddGEMGuardBuff(SGEMBuffInfo& sGEMBuffInfo);
    
   //扣除守卫峨眉守卫Buff
   bool SubGEMGuardBuff(UINT32 dwBuffID);

   //获取守卫峨眉通关奖励
   bool GetGEMGuardSuccAward(TVecItemGenInfo& vecAwards);

   //获取奖励
   bool GetAward(TVecItemGenInfo& vecAwards);

   //守卫峨眉扫荡定结果
   bool GEMSweepResult();

   //清除守卫峨眉信息
    bool CleanGEMData();
    
   //清除守卫峨眉守卫信息
   bool CleanGEMGuardData();

   //清除守卫峨眉扫荡信息
   bool CleanGEMSweepData();

   UINT8 GetGEMType() { return _byGEMType; }
   void SetGEMType(UINT8 byGEMType) { _byGEMType = byGEMType; }
   
   UINT8 GetGuardMark() { return _byGuardMark; }
   void SetGuardMark(UINT8 byGuardMark) { _byGuardMark = byGuardMark; }
   
   UINT16 GetMissionID() { return _wMissionID; }
   void SetMissionID(UINT16 wMissionID) { _wMissionID = wMissionID; }

   UINT16 GetCurProgress() { return _wCurProgress; }
   void SetCurProgress(UINT16 wCurProgress) { _wCurProgress = wCurProgress; }
   
   UINT16 GetGuardProgress() { return _wGuardProgress; }
   void SetGuardProgress(UINT16 wGuardProgress) { _wGuardProgress = wGuardProgress; }

   UINT32 GetGuardMonsterGroupID() { return _dwGuardMonsterGroupID; }
   void SetGuardMonsterGroupID(UINT32 dwGuardMonsterGroupID) { _dwGuardMonsterGroupID = dwGuardMonsterGroupID; }
   
   UINT32 GetSweepLastTime() { return _dwSweepLastTime; }
   void SetSweepLastTime(UINT32 dwSweepLastTime) { _dwSweepLastTime = dwSweepLastTime; }

   UINT32 GetSweepEndTime() { return _dwSweepEndTime; }
   void SetSweepEndTime(UINT32 dwSweepEndTime) { _dwSweepEndTime = dwSweepEndTime; }

 private:

   CPlayer& _rPlayer;
 
   //守卫峨眉类型(1：守卫；2：扫荡)
   UINT8 _byGEMType;

   //扣除进入次数标志
   UINT8 _byGuardMark;

   //关卡ID
   UINT16 _wMissionID;

   //当前进度（两种情况 1：守卫进度；2：守卫进度+扫荡进度；）
   UINT16 _wCurProgress;

   //守卫进度 
   UINT16 _wGuardProgress;

   //守卫怪物组
   UINT32 _dwGuardMonsterGroupID;

   //上一波扫荡时间 
   UINT32 _dwSweepLastTime;

   //扫荡结束时间 
   UINT32 _dwSweepEndTime;

   typedef map<UINT32, SGEMBuffInfo> MapGEMBuff;

   MapGEMBuff _mapGEMBuff;
};
#endif // _GUARDEMEI_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */
