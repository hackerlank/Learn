// =====================================================================================
//
//       Filename:  NewGuildBattleGate.h
//
//    Description:  新帮派战城门
//
//        Version:  1.0
//        Created:  03/20/2015 10:10:38 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef NEW_GUILD_BATTLE_GATE_H
#define NEW_GUILD_BATTLE_GATE_H

#include "stdafx.h"

#include "NewGuildBattleTypeDef.h"

#include "NewGuildBattleProt.h"

using namespace NNewGuildBattleProt;

namespace NNewGuildBattle
{
// =====================================================================================
//        Class:  CGate
//  Description:  新帮派战城门
// =====================================================================================
class CGate
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CGate (CMountainPtr pMountain);                             // constructor //
        virtual ~CGate();

        // ====================  ACCESSORS     ======================================= //
        CMountainPtr GetMountain() const;

        UINT32 GetStartRemainTime()     const;

        UINT64 GetDefenderID()  const;

        UINT32 GetGateMaxHP()   const;
        UINT32 GetGateHP()      const;

        bool   IsBroken()       const;

        void GetGuildAndPlayer(TVecUINT64& rvecGuildID, TVecString& rvecGuildName,
                TVecUINT64& rvecRoleID) const;

        CPlayerPtr GetPlayer(UINT64 qwRoleID, ENGBSide& eSide) const;

        void PlayerNotify(UINT64 qwRoleID) const;

        bool GetAllInfo(SMountainGateInfo& rInfo, UINT64 qwRoleID = 0) const;

        // ====================  MUTATORS      ======================================= //
        void SetGateHP(UINT32 dwHP);
        void SetGateMaxHP(UINT32 dwHP);

        // ====================  OPERATORS     ======================================= //
        bool StartBattle(UINT64 qwGuildID);
        void EndBattle(bool bTimeOver);

        UINT8 CalcFinalWinner();
        void ClearInvalidPlayers();
        void StopAllPuppets();

        void BattleProcess(time_t tNow);

        ENGBEnterResult         PlayerEnter (CPlayerPtr pPlayer);
        ENGBQuitResult          PlayerQuit (CPlayerPtr pPlayer);
        ENGBGateAttackResult    PlayerAttack (CPlayerPtr pPlayer, UINT64 qwRoleID);
        ENGBBuyPuppetResult     PlayerBuyPuppet(CPlayerPtr pPlayer);

        void NotifyGateInfo() const;
        void NotifyBroken() const;
        void NotifyRankInfo() const;

    private:
        // ====================  METHODS       ======================================= //
        bool CheckGate();
        bool TryPuppetAttack(time_t tNow);

        void GetPuppetInfo (TVecPuppetInfo& rvecInfo) const;
        void GetPlayerInfo (SMountainGateInfo& rInfo, UINT64 qwRoleID) const;

        void AddPlayerScore(CPlayerPtr pPlayer, UINT32 dwScore);

        void ReliveAllPlayers();

        void RejustGateAttr();

        // ====================  DATA MEMBERS  ======================================= //

        CMountainWtr    _pMountain;

        UINT32          _dwStartRemainTime; // 还没开始的倒计时

        UINT64          _qwDefenderID;      // 防守帮派ID

        UINT32          _dwGateMaxHP;       // 城门血量最大值
        UINT32          _dwGateHP;          // 城门血量
        UINT32          _dwGateAttack;      // 城门攻击力

        CPuppetPtr      _pPuppet;           // 系统自带的攻城傀儡

        map<UINT64, CPlayerPtr>     _mapAllAttackPlayer;      // 所有攻击城门的玩家
        map<UINT64, CPlayerPtr>     _mapAllDefendPlayer;      // 所有防守城门的玩家

        map<UINT64, UINT32>         _mapGuildScore;         // 所有参加帮派的战功
        map<UINT64, UINT32>         _mapGuildScoreTime;     // 所有参加帮派的战功更新时间

        TVecUINT64                  _vecWinnerGuildID;      // 获胜帮派ID
        TVecString                  _vecWinnerGuildName;    // 获胜帮派姓名
}; // -----  end of class CGate  ----- //

} // namespace NNewGuildBattle

#endif // #ifndef NEW_GUILD_BATTLE_GATE_H

