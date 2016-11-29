// =====================================================================================
//
//       Filename:  NewGuildBattlePuppet.h
//
//    Description:  新帮派战战争傀儡
//
//        Version:  1.0
//        Created:  03/20/2015 10:14:39 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef NEW_GUILD_BATTLE_PUPPET_H
#define NEW_GUILD_BATTLE_PUPPET_H

#include "stdafx.h"

#include "NewGuildBattleTypeDef.h"

namespace NNewGuildBattle
{

// =====================================================================================
//        Class:  CPuppet
//  Description:  新帮派战战争傀儡
// =====================================================================================
class CPuppet
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CPuppet ();                             // constructor //
        virtual ~CPuppet();

        // ====================  ACCESSORS     ======================================= //
        UINT32 GetNextAttackTime() const;
        UINT32 GetAttack() const;

        // ====================  MUTATORS      ======================================= //
        void SetNextAttackTime(UINT32 dwTime);
        void CalcNextAttackTime();

        // ====================  OPERATORS     ======================================= //
        void Stop();

    private:
        // ====================  METHODS       ======================================= //


        // ====================  DATA MEMBERS  ======================================= //
        UINT32 _dwNextAttackTime;   // 傀儡下次攻击城门时间
        UINT32 _dwAttack;           // 傀儡攻击力

}; // -----  end of class CPuppet  ----- //

} // namespace NNewGuildBattle

#endif // #ifndef NEW_GUILD_BATTLE_PUPPET_H

