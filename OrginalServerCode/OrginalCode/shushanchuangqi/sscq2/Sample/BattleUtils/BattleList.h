// =====================================================================================
//
//       Filename:  BattleList.h
//
//    Description:  战斗队列，用于战斗场地的行动队列
//
//        Version:  1.0
//        Created:  12/27/2014 04:42:16 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef BATTLE_LIST_H
#define BATTLE_LIST_H

#include "BattleTypeDef.h"

namespace NBattle
{

// =====================================================================================
//        Class:  CBattleList
//  Description:  战斗行动队列
// =====================================================================================
class CBattleList
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CBattleList ();                             // constructor //
        virtual ~CBattleList();

        // ====================  ACCESSORS     ======================================= //
        void DumpListInfo() const;

        bool IsEmpty() const;

        UINT32 GetRounds() const;
        UINT32 GetTurns() const;

        void GetAllAliveBattleFighter(TVecBattleFighterPtr& vecBF);
        void GetAllAliveBattleFighter(TVecBattleFighterPtr& vecBF, UINT8 bySide);

        void GetAllAliveBattleFighterWithMS(TVecBattleFighterPtr& vecBF, EMachineState eMachineState);
        void GetAllAliveBattleFighterWithMS(TVecBattleFighterPtr& vecBF, UINT8 bySide, EMachineState eMachineState);

        CBattleFighter* PopCurrentFighter(bool& bNewRound);      // 从当前等待队列获取Fighter

        // ====================  MUTATORS      ======================================= //
        void PushFighterToNext(CBattleFighter* pFighter);         // 将战斗对象加入下一回合等待队列
        void InsertFighterToCurrent(CBattleFighter* pFighter);    // 将战斗对象加入当前回合等待队列

        void RemoveFighter(CBattleFighter* pFighter);             // 移除战斗对象

        // ====================  OPERATORS     ======================================= //

    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //
        UINT32                _dwRounds;              // 总回合数
        UINT32                _dwTurns;               // 总出手数

        TVecBattleFighterPtr  _vecCurFigher;          // 当前回合的行动队列
        TVecBattleFighterPtr  _vecNextFighter;        // 下一回合的行动队列


}; // -----  end of class CBattleList  ----- //

} // namespace NBattle

#endif // #ifndef BATTLE_LIST_H

