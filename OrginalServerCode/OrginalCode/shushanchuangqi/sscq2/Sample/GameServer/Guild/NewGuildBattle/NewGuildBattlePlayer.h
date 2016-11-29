// =====================================================================================
//
//       Filename:  NewGuildBattlePlayer.h
//
//    Description:  新帮派战玩家数据
//
//        Version:  1.0
//        Created:  03/21/2015 05:25:44 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef NEW_GUILD_BATTLE_PLAYER_H
#define NEW_GUILD_BATTLE_PLAYER_H

#include "stdafx.h"

#include "NewGuildBattleTypeDef.h"

#include "NewGuildBattleProt.h"

using namespace NNewGuildBattleProt;

namespace NNewGuildBattle
{

// =====================================================================================
//        Class:  CPlayer
//  Description:  新帮派战玩家
// =====================================================================================
class CPlayer
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CPlayer (::CPlayerPtr pPlayer, 
                UINT64 qwGuildID, 
                const string& strGuildName, UINT16 wGuildLevel, const string& strGuildOwnerName);     // constructor //
        virtual ~CPlayer();

        // ====================  ACCESSORS     ======================================= //
        
        ::CPlayerPtr GetPlayer() const;

        UINT64 GetRoleID() const;
        const string& GetName() const;

        UINT64 GetGuildID() const;
        const string& GetGuildName() const;
        UINT16 GetGuildLevel() const;
        const string& GetGuildOwnerName() const;

        UINT32 GetScore(ENGBMountain eMountainType) const;
        UINT32 GetScore() const;

        UINT32 GetDeadTime() const;

        ENGBMountain GetMountain() const;
        ENGBSide    GetSide() const;

        TVecPuppetPtr& GetAllPuppet(ENGBMountain eMountainType);

        bool GetAllInfo(NNewGuildBattleProt::SPlayerInfo& rInfo) const;
        bool GetAllPanelInfo(NNewGuildBattleProt::SPlayerPanelInfo& rInfo) const;
        bool GetPuppetInfo(TVecPuppetInfo& rvecInfo, ENGBMountain eMountainType = eNGBMNone) const;

        // ====================  MUTATORS      ======================================= //
        void SetScore(ENGBMountain eMountainType, UINT32 dwScore);
        void AddScore(ENGBMountain eMountainType, UINT32 dwScore);

        void SetScore(UINT32 dwScore);
        void AddScore(UINT32 dwScore);

        void SetDeadTime(UINT32 dwTime);

        void SetMountain(ENGBMountain eMountainType, ENGBSide eSide);

        void SetPlayer(::CPlayerPtr pPlayer);

        // ====================  OPERATORS     ======================================= //
        ENGBBuyPuppetResult BuyPuppet(ENGBMountain eMountainType, UINT32 dwStartTime);
        void StopPuppet(ENGBMountain eMountainType);

    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //
        ::CPlayerWtr    _pPlayer;                       // 玩家对象

        UINT64          _qwRoleID;                      // 玩家ID
        string          _strName;                       // 玩家姓名

        UINT64          _qwGuildID;                     // 帮派ID
        string          _strGuildName;                  // 帮派名称
        UINT16          _wGuildLevel;                   // 帮派等级
        string          _strGuildOwnerName;             // 帮主名称

        map <ENGBMountain, UINT32>   _mapScore;         // 不同灵山的积分
        UINT32          _dwScore;                       // 战功数量

        UINT32          _dwDeadTime;                    // 死亡需要复活的时间

        ENGBMountain    _eMountainType;                 // 自己所参加战斗的灵山类型
        ENGBSide        _eSide;                         // 自己所参加灵山的战斗方向

        map <ENGBMountain, TVecPuppetPtr>   _mapPuppet; // 不同灵山购买的傀儡


}; // -----  end of class CPlayer  ----- //

} // namespace NNewGuildBattle
#endif // #ifndef NEW_GUILD_BATTLE_PLAYER_H

