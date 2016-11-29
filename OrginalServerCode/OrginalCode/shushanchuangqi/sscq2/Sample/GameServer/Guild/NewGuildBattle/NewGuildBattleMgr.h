// =====================================================================================
//
//       Filename:  NewGuildBattleMgr.h
//
//    Description:  新帮派战管理类
//
//        Version:  1.0
//        Created:  03/19/2015 10:48:44 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef NEW_GUILD_BATTLE_MGR_H
#define NEW_GUILD_BATTLE_MGR_H

#include "stdafx.h"

#include "NewGuildBattleTypeDef.h"

#include "Singleton.h"
#include "DayActivity.h"
#include "NewGuildBattleProt.h"

using namespace NNewGuildBattleProt;

namespace NNewGuildBattle
{

typedef map<ENGBMountain, CMountainPtr> MapMountainPtr;

// =====================================================================================
//        Class:  CBattleMgr
//  Description:  新帮派战管理类
// =====================================================================================
class CBattleMgr : public Singleton<CBattleMgr>, public CDayActivity
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CBattleMgr();
        virtual ~CBattleMgr();

        // ====================  ACCESSORS     ======================================= //
        bool            IsLoaded() const;

        ENGBState       GetState() const;

        bool            GetAllMountainsPanelInfo(TVecMountainPanelInfo& rvecInfo) const;
        UINT32          GetRemainTime() const;
        ENGBMountain    GetPlayerMountain(UINT64 qwRoleID) const;
        bool            IsPlayerInBattle(UINT64 qwRoleID) const;

        const string&   GetGuildName(UINT64 qwGuildID) const;
        UINT16          GetGuildLevel(UINT64 qwGuildID) const;
        const string&   GetGuildOwnerName(UINT64 qwGuildID) const;
        UINT32          GetGuildScore(UINT64 qwGuildID, ENGBMountain eMountainType) const;
        UINT32          GetPlayerScore(UINT64 qwRoleID) const;

        CPlayerPtr      GetPlayer(UINT64 qwRoleID) const;

        void PlayerNotify (UINT64 qwRoleID) const;

        CGuildRankMgrPtr  GetGuildRankMgr() const;
        CGuildMemberRankMgrPtr  GetGuildMemberRankMgr() const;
        CPlayerRankMgrPtr GetPlayerRankMgr() const;

        CMountainPtr    GetMountain(ENGBMountain eMountainType) const;

        UINT32          GetGateHP(ENGBMountain eMountainType) const;
        UINT32          GetGateMaxHP(ENGBMountain eMountainType) const;

        void            GetAllGuildPlayer(UINT64 qwGuildID, TVecUINT64& rvecRoleID) const;

        UINT32          GetGateInitHP() const;
        UINT32          GetGateInitAttack() const;

        // ====================  MUTATORS      ======================================= //
        void            SetLoaded(bool bLoaded);

        ENGBEnterResult     PlayerEnter(CPlayerPtr pPlayer, 
                ENGBMountain eMountainType, ENGBMountainState& eState);
        ENGBQuitResult      PlayerQuit(CPlayerPtr pPlayer);

        void SetState(ENGBState eState, bool bNotify = true);

        bool GMCapture(ENGBMountain eMountainType, 
                UINT64 qwGuildID, const string& strName, UINT16 wLevel);

        void  SetGateHP(ENGBMountain eMountainType, UINT32 dwHP);
        void  SetGateMaxHP(ENGBMountain eMountainType, UINT32 dwMaxHP);

        void AddPlayerBattleCount(UINT64 qwRoleID, bool bWin);

        void PushGuildName(UINT64 qwGuildID, const string& strGuildName, 
                UINT16 wGuildLevel, const string& strGuildOwnerName);

        void ChangeGuildLevel(UINT64 qwGuildID, UINT16 wLevel);
        void ChangeGuildOwnerName(UINT64 qwGuildID, const string& strName);
        void ClearGuild(UINT64 qwGuildID);

        void SetGateInitHP(UINT32 dwHP);
        void SetGateInitAttack(UINT32 dwAttack);

        // ====================  OPERATORS     ======================================= //

        void StartLoadData();
        bool LoadFromDB(const string& strData);

        void TimerCheck(time_t tNow);               // 定时器检查

        void ExpProcess(UINT32 dwTime);             // 经验值结算

        virtual bool GMOpen();                      // GM指令直接开启活动

        virtual bool OnAlarm();                     // 程序开始准备
        virtual void OnReady();                     // 开始通知
        virtual void OnBegin();                     // 正式开始
        virtual void OnEnd();                       // 活动结束
        
        virtual void OnReBegin();                   // 服务器重启,处于活动期间的处理

        virtual void UpdateState(time_t tNow);      // 更新状态
        
        virtual void ResetState();                  // 重置原始状态

        virtual void OnEvent(SActEventData& oSActEventData);    // 注册事件触发

    private:
        // ====================  METHODS       ======================================= //

        bool StartBattle();
        void EndBattle();

        void ForceEndBattle();

        void Reset();

        // ====================  DATA MEMBERS  ======================================= //
        bool                        _bLoaded;                // 相关加载已经完成

        ENGBState                   _eState;                 // 当前帮派战活动状态
        MapMountainPtr              _mapMountainPtr;         // 新帮派战灵山

        map<UINT64, string>         _mapGuildName;           // 帮派姓名索引
        map<UINT64, UINT16>         _mapGuildLevel;          // 帮派等级索引
        map<UINT64, string>         _mapGuildOwnerName;      // 帮派帮主姓名索引

        map<UINT64, UINT32>         _mapGuildScore;          // 所有参加帮派的战功

        map<UINT64, CPlayerPtr>     _mapAllPlayer;           // 所有参加帮派战的玩家

        map<UINT64, UINT8>          _mapPlayerWinCombo;      // 玩家帮派战连胜

        CGuildRankMgrPtr            _pGuildRankMgr;          // 帮派排行榜
        CGuildMemberRankMgrPtr      _pGuildMemberRankMgr;    // 帮派成员排行榜
        CPlayerRankMgrPtr           _pPlayerRankMgr;         // 玩家排行榜

        UINT32                      _dwLastExpCheckTime;     // 经验值上次结算时间

        UINT32                      _dwGateHP;               // 山门战城门血量
        UINT32                      _dwGateAttack;           // 山门战城门攻击力
}; // -----  end of class CBattleMgr  ----- //

} // namespace NNewGuildBattle

#endif

