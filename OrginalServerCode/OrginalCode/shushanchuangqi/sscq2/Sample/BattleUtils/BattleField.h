#ifndef _BATTLE_FIELD_H_
#define _BATTLE_FIELD_H_

#include "BattleTypeDef.h"

#include "BattleGS.h"

#include "BattleList.h"
#include "BattleCombine.h"
#include "BattleReiatsu.h"

namespace NBattle
{

using namespace NBattleGS;

bool IsTargetAlive(CBattleFighter* pBF);          // 目标是否存活
bool IsTargetCanBeAttacked(CBattleFighter* pBF);  // 目标是否能被攻击到
bool IsTargetControled(CBattleFighter* pBF);      // 目标是否被控制技能控制
bool IsTargetHPLost(CBattleFighter* pBF);         // 目标血量是否有损失

struct SAttacker
{
    CBattleFighter*   _pBO;
    FLOAT               _fFactor;
    UINT8               _byMainTarget;

    SAttacker() : 
        _pBO(NULL), _fFactor(0), _byMainTarget(0)
    {
    }
};
typedef std::vector<SAttacker> TVecAttacker;

struct SFieldPos
{
    bool  bMainTarget;
    UINT8 byGroupID;
    UINT8 byPos;
    FLOAT fFactor;
    SFieldPos():
        bMainTarget(false), byGroupID(0), byPos(0), fFactor(0)
    {
    }
};
typedef std::vector<SFieldPos> TVecFieldPos;

// =====================================================================================
//        Class:  CBattleField
//  Description:  战斗场地
// =====================================================================================
class CBattleField : public CBattleList, public CBattleCombine, public CBattleReiatsu
{

    public:
        // ====================  LIFECYCLE     ======================================= //
        CBattleField ();                             // constructor //
        virtual ~CBattleField();

        // ====================  ACCESSORS     ======================================= //
        CBattleFighterPtr GetSummonFighter(UINT16 wFighterID);
        CBattleFighter* GetFighterByID(UINT8 bySide, UINT8 byTeamID, UINT16 wFighterID);

        CBattleFighter* GetScene();
        CBattleFighter* GetPet(UINT8 bySide);

        void              GetTargetList(CBattleFighter* pBF, CBattleFighter* pBO, UINT16 wAreaID, 
                            TVecAttacker& vFgtOut, TVecFieldPos& rvecPos, UINT16& rAreaID);
        CBattleFighter* GetPossibleTarget(CBattleFighter* pBF, function<bool (CBattleFighter* pBO)>);
        CBattleFighter* GetRandomTarget(UINT8 bySide, const TVecBattleFighterPtr& vecExcpFgtOut);
        bool              GetIDTargets(UINT8 bySide, TVecBattleFighterPtr& vecFighters, const TSetUINT16& rsetFighterID);

        bool            GetSideAliveTargets(UINT8 bySide, TVecBattleFighterPtr& vecFighters);

        EBattleResult GetResult() const;

        bool IsPet(CBattleFighter* pBF) const;

        // ====================  MUTATORS      ======================================= //
        bool SetObject(CBattleFighterPtr pBF, EBattleFieldDest eDest);

        // ====================  OPERATORS     ======================================= //
        bool TrySummonAppear(UINT8 bySide, UINT8 byPos, CBattleFighterPtr pFighter, UINT8 bySumonLast);
        bool TryRelive( CBattleFighter* pFighter, FLOAT fHPFactor);

        bool OnDead(CBattleFighter* pFighter, TVecUINT8& rvecCombineIndex);

        void ResetBattleFighterBuff();

    private:
        // ====================  METHODS       ======================================= //

        bool SetFieldObject(CBattleFighterPtr pBF);
        bool SetSummon(CBattleFighterPtr pBF);
        bool SetScene(CBattleFighterPtr pBF);
        bool SetPet(CBattleFighterPtr pBF);

        void ClearSide(UINT8 bySide);

        void GetAllFighter (UINT8 bySide, TVecBattleFighterPtr& vFgtOut, const TVecBattleFighterPtr& vecExcpFgtOut);

        CBattleFighter*   GetSelfPossibleTarget(CBattleFighter* pBF, function<bool (CBattleFighter* pBO)>);
        bool                GetSelfPossibleTargets(UINT8 bySide, TVecBattleFighterPtr& vecFighters, function<bool (CBattleFighter* pBO)> func);
        CBattleFighter*   GetHPPMinTarget(UINT8 bySide);
        CBattleFighter*   GetHPPMinTarget2 (UINT8 bySide, const TVecBattleFighterPtr& vecExcpFgtOut);

        bool GetEmptyPos(UINT8 bySide, TVecUINT8& rvecPos);
        bool GetRandomEmptyPos(UINT8 bySide, UINT8& byX, UINT8& byY, const TVecUINT8& rvecEmptyPos);

        UINT8 GetTargetSide (EAreaSide eSideType, UINT8 bySide);

        CBattleFighter* GetObject(UINT8 bySide, UINT8 byPos);

        bool GetSpecialTargetList(CBattleFighter* pBF, CBattleFighter* pBO, UINT16 wAreaID, 
                TVecAttacker& rvecAttacker, TVecFieldPos& rvecPos, UINT16& rAreaID);

        bool GetAreaFirstTarget (CBattleAreaPtr pArea, UINT8 bySelfSide, UINT8 byTargetSide,
                CBattleFighter* pBF, CBattleFighter* pBO,
                UINT8& rX, UINT8& rY, bool& rNeedPos, TVecBattleFighterPtr& rvecFighters, TVecUINT8& rvecEmptyPos);

        // ====================  DATA MEMBERS  ======================================= //

        mutable EBattleResult _eResult;               // 胜利方

        CBattleFighterPtr     _pObjects[2][MAX_POS];  // 战斗对象
        CBattleFighterPtr     _pScene;                // 场景技能对象
        CBattleFighterPtr     _pPet[2];            // 阵灵技能对象

        UINT8                 _byAliveCount[2];       // 存活数量

        TSetBattleFighterPtr  _setDeadFighter[2];     // 死人

        TMapBattleFighterPtr  _mapSummons;            // 召唤物
}; // -----  end of class CBattleField  ----- //

} // namespace NBattle


#endif // _BATTLE_FIELD_H_
