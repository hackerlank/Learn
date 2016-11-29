// =====================================================================================
//
//       Filename:  NewGuildBattleCave.h
//
//    Description:  新帮派战洞府
//
//        Version:  1.0
//        Created:  03/20/2015 10:11:42 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef NEW_GUILD_BATTLE_CAVE_H
#define NEW_GUILD_BATTLE_CAVE_H

#include "stdafx.h"

#include "NewGuildBattleTypeDef.h"

#include "NewGuildBattleProt.h"

using namespace NNewGuildBattleProt;

namespace NNewGuildBattle
{

// =====================================================================================
//        Class:  CCave
//  Description:  新帮派战洞府
// =====================================================================================
class CCave
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CCave (CMountainPtr pMountain);                             // constructor //
        virtual ~CCave();

        // ====================  ACCESSORS     ======================================= //
        CMountainPtr GetMountain() const;

        UINT32 GetRemainTime() const;

        UINT64 GetDefenderID() const;
        void GetAllAttackGuildID(TVecUINT64& rvecGuildID) const;

        UINT64 GetWinnerID() const;

        CPlayerPtr GetPlayer(UINT64 qwRoleID) const;
        void GetAllPlayerID(TVecUINT64& rvecRoleID) const;

        void PlayerNotify(UINT64 qwRoleID) const;

        bool GetAllInfo(SCaveInfo& rInfo, UINT64 qwRoleID = 0) const;

        // ====================  MUTATORS      ======================================= //

        // ====================  OPERATORS     ======================================= //
        bool StartBattle(UINT64 qwGuildID, 
                const TVecUINT64& rvecAttackGuildID, const TVecString& rvecAttackGuildName,
                const TVecUINT64& rvecRoleID);
        void EndBattle(bool bTimeOver, UINT64 qwWinnerID);

        void BattleProcess(time_t tNow);

        ENGBEnterResult PlayerEnter (CPlayerPtr pPlayer);
        ENGBQuitResult  PlayerQuit (CPlayerPtr pPlayer);
        ENGBCaveAttackResult PlayerAttack (CPlayerPtr pPlayer, UINT64 qwRoleID);
        ENGBCaveAttackResult PlayerCapture (CPlayerPtr pPlayer, ENGBCaveCore eCaveType);
        ENGBCaveAttackResult PlayerRest (CPlayerPtr pPlayer);

        void CalcFinalWinner(bool bTimeOver, UINT64 qwWinnerID);

        void NotifyCaveInfo() const;
        void NotifyCaveCoreInfo() const;

        void NotifyRankInfo() const;
        void NotifyWinner() const;
    private:
        // ====================  METHODS       ======================================= //
        void GetPlayerInfo (SCaveInfo& rInfo, CPlayerPtr pPlayer) const;
        void GetOthersInfo (TVecPlayerPanelInfo& rvecInfo, UINT64 qwGuildID) const;

        void AddPlayerScore(CPlayerPtr pPlayer, UINT32 dwScore);

        void KickAllPlayer();
        // ====================  DATA MEMBERS  ======================================= //
        CMountainWtr                        _pMountain;

        UINT32                              _dwStartRemainTime;     // 开始前倒计时

        UINT64                              _qwDefenderID;          // 防守帮派ID
        TVecUINT64                          _vecAttackGuildID;      // 攻击帮派ID
        TVecString                          _vecAttackGuildName;    // 攻击帮派名称

        map<UINT64, UINT32>                 _mapGuildRes;           // 攻击帮派资源数

        map<UINT64, CPlayerPtr>             _mapAllPlayer;          // 所有参加洞府战的玩家

        map<ENGBCaveCore, CCaveCorePtr>     _mapCorePtr;            // 阵眼

        UINT32                              _dwNextResCalcTime;     // 下次资源结算时间

        UINT64                              _qwWinnerID;            // 获胜者帮派ID
}; // -----  end of class CCave  ----- //

} // namespace NNewGuildBattle

#endif // #ifndef NEW_GUILD_BATTLE_CAVE_H

