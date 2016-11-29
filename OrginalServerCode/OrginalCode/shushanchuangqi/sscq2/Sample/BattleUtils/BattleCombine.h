// =====================================================================================
//
//       Filename:  BattleCombine.h
//
//    Description:  战斗的连携点数
//
//        Version:  1.0
//        Created:  12/29/2014 08:57:32 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef BATTLE_COMBINE_H
#define BATTLE_COMBINE_H

#include "BattleTypeDef.h"

#include "BattleGS.h"


namespace NBattle
{

using namespace NBattleGS;

struct SCombinePosition
{
    UINT8                       byIndex;        // 唯一ID
    UINT8                       byTeamID;       // 所属队伍ID
    TSetUINT16                  setFighterID;   // 涉及到的散仙ID
    UINT32                      dwSkillID;      // 连携技能ID
    UINT8                       byCombineCount; // 当前连携点数
    mutable bool                bLock;          // 是否已经发动，锁住需要新回合解锁
    mutable set<ECombineType>   setType;        // 以及触发的增加连携点数的方式
    SCombinePosition():
        byIndex(0), byTeamID(0), dwSkillID(0), byCombineCount(0), bLock(false)
    {
    }
};
typedef std::vector<SCombinePosition> TVecCombinePosition;

// =====================================================================================
//        Class:  CBattleCombine
//  Description:  战斗中的连携槽，管理连携点数
// =====================================================================================
class CBattleCombine
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CBattleCombine ();                             // constructor //
        virtual ~CBattleCombine();

        // ====================  ACCESSORS     ======================================= //

        // 根据对应散仙获取连携点数
        UINT8  GetCombine(CBattleFighter* pFighter) const;

        // 返回需要释放的组合技能
        UINT32 GetCombineSkill(UINT8 bySide, UINT8& byIndex, UINT8& byTeamID) const;

        // 获取需要更新连携点数组合技能
        bool   GetNewCombineCount (UINT8 bySide, UINT8& byIndex, UINT8& byCount, TVecUINT8& rvecType) const;

        // 获取连携技能的散仙ID
        bool   GetCombineSkillFighterID (UINT8 bySide, UINT8 byIndex, TSetUINT16& rsetFighterID) const;

        // ====================  MUTATORS      ======================================= //
        
        // 增加新的连携技能
        bool   PushCombineSkill(UINT8 bySide, UINT8 byTeamID, UINT8 byIndex, UINT32 dwSkillID);

        // 增加连携点数
        bool   AddCombine(CBattleFighter* pFighter, ECombineType eType, UINT8 byCount = 1);

        // 让组合技能重新解锁
        void   UnlockCombineSkill();

        // ====================  OPERATORS     ======================================= //
       
        // 重置连携点数
        void   ResetCombine(UINT8 bySide, UINT32 dwSkillID);

        // 清除连携点数
        void   ClearCombine(UINT8 bySide);

        // 移除和某一个战斗对象有关的所有连携技能
        void   RemoveCombineFighter(CBattleFighter* pFighter, TVecUINT8& rvecCombineIndex);

    private:
        // ====================  DATA MEMBERS  ======================================= //

        TVecCombinePosition   _vecCombinePosition[2]; // 连携点数(和玩家以及对应的散仙组合绑定)

}; // -----  end of class CBattleCombine  ----- //

} // namespace NBattle

#endif // #ifndef BATTLE_COMBINE_H
