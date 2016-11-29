// =====================================================================================
//
//       Filename:  GuildBattleInfo.h
//
//    Description:  帮派战战斗信息
//
//        Version:  1.0
//        Created:  07/24/2014 09:10:02 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  上海恺英网络科技有限公司
//
// =====================================================================================

#ifndef GUILD_BATTLE_INFO_H
#define GUILD_BATTLE_INFO_H

#include "stdafx.h"

#include "GuildBattleProt.h"

#include "GuildBattleSpot.h"

using namespace NGuildBattleProt;

// =====================================================================================
//        Class:  CGuildBattleInfo
//  Description: 帮派战战斗信息（战报胜负。双方情况）
// =====================================================================================
class CGuildBattleInfo
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        //CGuildBattleInfo ();                             // constructor //
        CGuildBattleInfo (UINT64 qwBattleID, UINT8 byIndex,
                const SBattleUserAllInfo& sUserAllInfoA, const SBattleUserAllInfo& sUserAllInfoB,
                UINT64 qwRoleIDA, UINT64 qwRoleIDB,
                const string& strName1, const string& strName2, EGBSide eSide,
                const string& strReport);// constructor //
        virtual ~CGuildBattleInfo();

        // ====================  ACCESSORS     ======================================= //
        const string& GetName ( EGBSide eSide ) const;
        UINT64 GetBattleID () const;
        UINT8 GetIndex() const;

        bool GetAllInfo(SBattleInfo& rInfo) const;
        bool GetAllInfo(SBattleSlotInfo& rInfo) const;
        bool GetAllInfo(SBattleData& rInfo) const;

        UINT64 GetRoleIDA() const;
        UINT64 GetRoleIDB() const;

        // ====================  MUTATORS      ======================================= //
        void SetState (UINT64 qwRoleID, EGBUserState eState);

        // ====================  OPERATORS     ======================================= //

    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //
        UINT64 _qwBattleID;     // 战报ID
        UINT8  _byIndex;        // 战斗场编号(1-3)
        string _strName[2];     // 战斗双方姓名
        UINT64 _qwRoleID[2];    // 战斗双方ID 
        EGBSide  _eWinnerSide;  // 胜利方
        UINT64 _qwGuiildID[2];  // 帮派ID
        string _strReport;
        SBattleUserAllInfo _sUserAllInfo[2];

}; // -----  end of class CGuildBattleInfo  ----- //

#endif // #ifndef GUILD_BATTLE_INFO_H

