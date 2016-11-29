// =====================================================================================
//
//       Filename:  GuildBattleMgr.h
//
//    Description:  帮派战管理类
//
//        Version:  1.0
//        Created:  07/24/2014 03:08:50 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================
#ifndef GUILD_BATTLE_MGR_H
#define GUILD_BATTLE_MGR_H

#include "GuildBattleProt.h"
#include "DayActivity.h"

#include "stdafx.h"

using namespace NGuildBattleProt;

// =====================================================================================
//        Class:  CGuildBattleMgr
//  Description:  帮派战管理器（配置/时间段/汇总）
// =====================================================================================
class CGuildBattleMgr : public Singleton<CGuildBattleMgr>, public CDayActivity
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CGuildBattleMgr ();                             // constructor //
        virtual ~CGuildBattleMgr();

        // ====================  ACCESSORS     ======================================= //
        CGuildBattlePtr GetBattleViaRoleID(UINT64 qwRoleID);
        CGuildBattlePtr GetBattleViaGuildID(UINT64 qwGuildID);
        CGameMapPtr GetPrepareMap(UINT64 qwGuildID);
        UINT8   GetBattleCount() const;
        UINT32  GetRemainTime() const;
        EGBState GetState() const;

        bool GetFieldInfo(CPlayerPtr pPlayer, UINT64 qwGuildID, const string& strGuildName,
                EGBResult& eResult, TVecFieldInfo& vecFieldInfo);
        bool IsGuildJoined(UINT64 qwGuildID) const;

        bool IsPlayerInGuildBattleField(UINT64 qwGuildID) const;

        EGBSpot GetSpotType(CPlayerPtr pPlayer) const;
        EGBSide GetSpotSide(CPlayerPtr pPlayer) const;
        UINT64 GetGuildID(CPlayerPtr pPlayer) const;

        CGuildBattleFieldPtr GetSignUpField(UINT64 qwGuildID);
        CGuildBattleFieldPtr GetBattleField(UINT64 qwGuildID);

        SGuildBattleSpotPlayerPtr GetSpotPlayer(UINT64 qwRoleID);

        bool GetSpotInfo(CPlayerPtr pPlayer, EGBSpot eType, TVecSpotInfo& rvecSpotInfo, EGBResult& eResult);
        bool GetAllMapPlayers(UINT64 qwGuildID, TVecUINT64& vecRoleID) const;
        bool GetAllOB(UINT64 qwGuildID, TVecUINT64& vecRoleID) const;

        bool GetBattleInfo(CPlayerPtr pPlayer, EGBSpot eSpotType, EGBBattleResult& eResult, TVecBattleData& rvecBattleData);

        bool GetSkillInfo(CPlayerPtr pPlayer, UINT64 qwGuildID, EGBSkillResult& eResult, TVecSkillInfo& rvecSkillInfo);

        UINT32 GetGuildScore(UINT64 qwGuildID) const;
        UINT32 GetGuildRank(UINT64 qwGuildID) const;
        UINT32 GetPlayerScore(UINT64 qwRoleID) const;

        string GetDumpInfo(CPlayerPtr pPlayer) const;

        // ====================  METHODS       ======================================= //
        void TimerCheck(time_t tNow); // 定时器检查

        bool UserSignUp(CPlayerPtr pPlayer, UINT64 qwGuildID, UINT16 wLevel, const string& strGuildName, UINT32 dwScore, EGBSpot eType, EGBSignUpResult& eResult);
        bool UserEnter(CPlayerPtr pPlayer, EGBEnterResult& eResult);
        bool UserQuit(CPlayerPtr pPlayer, EGBQuitResult& eResult);

        bool UserOnline(CPlayerPtr pPlayer);
        void UserOffline(CPlayerPtr pPlayer);

        void UserAdjust(CPlayerPtr pPlayer, UINT64 qwRoleID, EGBSpot eSpotType, UINT8 byIndex, EGBAdjustResult& eResult);

        void ForceEndBattle();

        void SyncGuildName();

        bool BuySkill(CPlayerPtr pPlayer, UINT64 qwGuildID, EGBSkill eSkillType, EGBSkillResult& eResult);

        void NotifyPreparePlayerInfo(UINT64 qwGuildID, const string& strData) const;

        virtual bool GMOpen();
        virtual bool OnAlarm();
        virtual void OnReady();
        virtual void OnBegin();
        virtual void OnEnd();
        virtual void OnEvent(SActEventData& oSActEventData);
        
        //服务器重启,处于活动期间的处理
        virtual void OnReBegin();
        
        //更新状态
        virtual void UpdateState(time_t tNow);
        
        //重置原始状态
        virtual void ResetState();

        // ====================  MUTATORS      ======================================= //
        
        void AddPlayerMap(SGuildBattleSpotPlayerPtr pSpotPlayer);
        void RemovePlayerMap(UINT64 qwRoleID);
        void ResetPlayerMap(SGuildBattleSpotPlayerPtr pSpotPlayer);

        bool AddGuildScore(UINT64 qwGuildID, UINT32 dwScore);
        bool AddPlayerScore(UINT64 qwRoleID, UINT32 dwScore);
        void AddPlayerBattleCount (UINT64 qwRoleID, bool bWin);

    private:
        // ====================  METHODS       ======================================= //
        void SetStatus(EGBState eState);

        void UpdateNextTime();

        void StartSignUp();
        void EnterNotify ();
        void StartBattle(UINT32 dwTodayTime);
        void EndBattle(bool bFinal, bool bForce = false);
        void ResultSum();
        void Reset();

        void StartNewRound();
        void BattleProcess(time_t tNow);
        void ExpProcess(UINT32 dwTodayTime);

        void CleanupInvalidGuild();
        // ====================  DATA MEMBERS  ======================================= //

        EGBState _eState; //帮派战状态

        UINT32 _dwNextTime;     // 下一个阶段的时间戳

        map<UINT64, CGuildBattleFieldPtr>      _mapSignUpField;      // 帮派战报名情况
        map<UINT64, TSetUINT64>                _mapGuildScore;       // 帮派战历史积分

        map<UINT64, UINT64>                    _mapUserID2GuildID;   // 玩家ID检索帮派ID
        map<UINT64, SGuildBattleSpotPlayerPtr> _mapAllPlayer;        // 所有玩家的索引

        map<UINT64, CGameMapPtr>               _mapPrepareMap;       // 帮派战准备地图

        map<UINT64, UINT32>                    _mapUserJoinTime;     // 玩家帮派战参与时间

        TVecGuildBattlePtr                     _vecGuildBattle;      // 具体帮派战战斗
        map<UINT64, CGuildBattlePtr>           _mapGuildBattleIndex; // 帮派ID索引帮派战

        UINT64                                 _qwEmptyBattleGuildID;// 轮空的帮派ID
        CGuildBattlePtr                        _pEmptyBattle;        // 轮空的帮派

        map<UINT64, UINT64>                    _mapBattleScore;      // 帮派战帮派所获得积分
        map<UINT64, UINT64>                    _mapBattleScoreOnce;  // 一轮帮派战帮派所获得积分
        map<UINT64, UINT32>                    _mapPlayerScore;      // 玩家帮派战积分
        map<UINT64, UINT8>                     _mapPlayerWinCombo;   // 玩家帮派战连胜

        map<UINT64, UINT32>                    _mapGuildRank;        // 当前帮派战积分排名

        map<UINT64, UINT16>                    _mapGuildLevel;       // 帮派等级

        UINT32 _dwLastExpCheckTime;     // 经验值最后结算时间

        UINT8  _byBattleCount;      // 当前已经进行的战斗数量
        bool   _bNeedSignNotify;    // 帮派战报名是否需要通知
        UINT32 _dwReadyNotifyTime;  // 忘记报名提醒时间
}; // -----  end of class CGuildBattleMgr  ----- //

#endif // #ifndef GUILD_BATTLE_MGR_H

