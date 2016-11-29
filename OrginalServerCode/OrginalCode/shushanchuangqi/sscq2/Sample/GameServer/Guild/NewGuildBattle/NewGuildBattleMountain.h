// =====================================================================================
//
//       Filename:  NewGuildBattleMountain.h
//
//    Description:  新帮派战灵山类
//
//        Version:  1.0
//        Created:  03/19/2015 01:58:23 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef NEW_GUILD_BATTLE_MOUTAIN_H
#define NEW_GUILD_BATTLE_MOUTAIN_H

#include "stdafx.h"

#include "NewGuildBattleTypeDef.h"

#include "NewGuildBattleProt.h"
#include "Game2DBComm.h"

namespace NNewGuildBattle
{

using namespace NNewGuildBattleProt;

// =====================================================================================
//        Class:  CMountain
//  Description:  新帮派战灵山
// =====================================================================================
class CMountain : public enable_shared_from_this<CMountain>
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CMountain (ENGBMountain eType);                             // constructor //
        virtual ~CMountain();

        // ====================  ACCESSORS     ======================================= //
        ENGBMountain GetType() const;
        string  GetName() const;

        ENGBMountainState GetState() const;

        UINT64 GetGuildID() const;

        bool GetPanelInfo(SMountainPanelInfo& rInfo) const;
        bool GetHistoryInfo(TVecOwnerHistoryInfo& rvecInfo) const;

        void PlayerNotify(UINT64 qwRoleID) const;

        CGatePtr GetGate() const;
        CCavePtr GetCave() const;

        UINT32  GetGateHP() const;
        UINT32  GetGateMaxHP() const;

        // ====================  MUTATORS      ======================================= //
        bool    StartBattle();
        void    EndBattle(bool bTimeOver);

        void    Reset();

        void    SetGateHP(UINT32 dwHP);
        void    SetGateMaxHP(UINT32 dwMaxHP);

        bool    PushHistory(CMountainHistoryPtr pHistory);

        void    ChangeGuildLevel(UINT64 qwGuildID, UINT16 wLevel);
        void    ChangeGuildOwnerName(UINT64 qwGuildID, const string& strName);
        void    ClearGuild(UINT64 qwGuildID);

        // ====================  OPERATORS     ======================================= //
        void BattleProcess(time_t tNow);

        ENGBEnterResult PlayerEnter (CPlayerPtr pPlayer);
        ENGBQuitResult  PlayerQuit (CPlayerPtr pPlayer);

        void Reward(UINT64 qwRoleID) const;

        bool GMCapture(UINT64 qwGuildID, const string& strGuildName, UINT16 wLevel);

    private:
        // ====================  METHODS       ======================================= //
        bool    StartGate();
        bool    StartCave();

        // ====================  DATA MEMBERS  ======================================= //
        const ENGBMountain      _eType;                    // 灵山类型

        ENGBMountainState       _eState;                   // 灵山状态

        UINT64                  _qwGuildID;                // 当前占领帮派ID
        string                  _strGuildName;             // 当前占领帮派名称
        UINT16                  _wGuildLevel;              // 当前占领帮派等级
        string                  _strGuildOwnerName;        // 当前占领帮派帮主名称
        UINT32                  _dwGuildOwnCount;          // 当前占领帮派占领次数
        UINT32                  _dwCaptureTime;            // 占领时间

        TListMountainHistoryPtr _listHistoryPtr;           // 占领历史
        
        CGatePtr                _pGate;                    // 城门战的城门
        CCavePtr                _pCave;                    // 洞府战的洞府

        map<UINT64, UINT32>     _mapGuildCaptureCount;     // 帮派占领次数

        UINT64                  _qwGuildLostID;            // 失败者帮派ID

        TVecUINT64              _vecCaveAttackGuildID;     // 洞府战攻击帮派

}; // -----  end of class CMountain  ----- //

// =====================================================================================
//        Class:  CMountainHistory
//  Description:  新帮派战灵山占领历史
// =====================================================================================
class CMountainHistory
{
    friend class CMountain;
    public:
        // ====================  LIFECYCLE     ======================================= //
        CMountainHistory (ENGBMountain eMountainType, 
                UINT64 qwGuildID, const string& strName, const string& strOwnerName, 
                UINT32 dwTime);                             // constructor //
        virtual ~CMountainHistory();

        // ====================  ACCESSORS     ======================================= //
        bool GetAllInfo(SOwnerHistoryInfo& rInfo) const;
        bool GetAllInfo (NGame2DBComm::SDBGuildNewBattleHistoryInfo& rInfo) const;

        // ====================  MUTATORS      ======================================= //

        // ====================  OPERATORS     ======================================= //

    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //
        ENGBMountain        _eMountainType;      // 灵山类型
        UINT64              _qwGuildID;          // 当前占领帮派ID
        string              _strGuildName;       // 当前占领帮派名称
        string              _strGuildOwnerName;  // 当前占领帮派帮主名称
        UINT32              _dwTime;             // 占领时间

}; // -----  end of class CMountainHistory  ----- //

} // namespace NNewGuildBattle

#endif // #ifndef NEW_GUILD_BATTLE_MOUTAIN_H
