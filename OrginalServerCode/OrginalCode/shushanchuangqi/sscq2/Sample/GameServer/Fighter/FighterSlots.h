
#ifndef FIGHTERSLOTS_H_
#define FIGHTERSLOTS_H_

#include "stdafx.h"
#include "VecSlots.h"
#include "Fighter.h"
#include "Battle.h"

// =====================================================================================
//        Class:  CFighterSlots
//  Description:  
// =====================================================================================
class CFighterSlots : public CVecSlots<int, CFighterPtr>
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CFighterSlots ();                             // constructor //
        virtual ~CFighterSlots();

        CFighterPtr GetMainFighter() const;

        CFighterPtr GetFighterByInstID(UINT64 qwFighterID, int* pIdx = NULL);
        CFighterPtr GetFighterByID(UINT16 wFighterID, int* pIdx = NULL);

        bool HasFighter(UINT16 wFighterID, int* pIdx = NULL);
        bool HasRecruitFighter(UINT16 wFighterID, int* pIdx = NULL);
        bool GetBattleFighters(TVecBattleFighterPtr& vecBattleFighter, EBattleType eBattleType);

        // ====================  ACCESSORS     ======================================= //

        // ====================  MUTATORS      ======================================= //

        // ====================  OPERATORS     ======================================= //

    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //

}; // -----  end of class CFighterSlots  ----- //

#endif // FIGHTERSLOTS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

