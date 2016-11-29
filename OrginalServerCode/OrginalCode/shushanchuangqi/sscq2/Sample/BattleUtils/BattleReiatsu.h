// =====================================================================================
//
//       Filename:  BattleReiatsu.h
//
//    Description:  战斗美女灵压
//
//        Version:  1.0
//        Created:  01/03/2015 04:05:24 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef BATTLE_REIATSU_H
#define BATTLE_REIATSU_H

#include "BattleTypeDef.h"

namespace NBattle
{

// =====================================================================================
//        Class:  CBattleReiatsu
//  Description:  战斗灵压（内部包含美女）
// =====================================================================================
class CBattleReiatsu
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CBattleReiatsu ();                             // constructor //
        virtual ~CBattleReiatsu();

        // ====================  ACCESSORS     ======================================= //
        CBattleFighter* GetBeauty(UINT8 bySide);

        UINT8  GetReiatsu(UINT8 bySide) const;
        // ====================  MUTATORS      ======================================= //
        bool SetBeautyObject(CBattleFighterPtr pBF);
        void ClearFormatin(UINT8 bySide);

        void   ClearReiatsu(UINT8 bySide);
        void   ChangeReiatsu(UINT8 bySide, INT8 byReiatsu);
        void   SetReiatsu(UINT8 bySide, UINT8 byReiatsu);
        void   AddReiatsu(UINT8 bySide, UINT8 byReiatsu);
               
    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //
        CBattleFighterPtr     _pBeauty[2];         // 美女

        UINT8                 _byReiatsu[2];          // 灵压（当美女不为空就有效）

}; // -----  end of class CBattleReiatsu  ----- //

} // namespace NBattle
#endif //#ifndef BATTLE_REIATSU_H
