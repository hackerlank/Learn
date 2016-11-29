#ifndef BATTLE_SIMULATOR_H
#define BATTLE_SIMULATOR_H

#include "Battle.h"

#include "BattleTypeDef.h"
#include "BattleGS.h"
#include "BattleField.h"

namespace NBattle
{

using namespace NBattleGS;
struct SBattleTeam
{
    UINT8   _byGroupID;                 // 组ID，标志了组所在的位置，0进攻方，1防守方
    UINT64  _qwInstID;                  // 玩家ID，地图上跑的时候用的那个ID，怪物为0
    UINT64  _qwLeaderID;                // 队伍主将ID
    UINT16  _wLevel;                    // 队伍等级
    TVecBattleFighterSPtr _vecFighter;  // 队伍里面的所有Fighter
    SFeatureBasePtr _pFeature;          // 主将外观信息（用于显示头像用）

    SBattleTeam():
        _byGroupID(0), _qwInstID(0), _qwLeaderID(0), _wLevel(0)
    {
    }
};

// =====================================================================================
//        Class:  CBattleSimulator
//  Description:  战斗模拟器
// =====================================================================================
class CBattleSimulator : public IBattleSimulator
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CBattleSimulator (UINT64 qwGuildID);                             // constructor //
        virtual ~CBattleSimulator();

        // ====================  ACCESSORS     ======================================= //
        virtual EBattleResult GetFinalWinner() const;
        virtual UINT32        GetTurns() const;
        virtual UINT32        GetRounds() const;
        virtual void          GetReport(std::string& strReport) const;

        virtual UINT64        GetBattleID() const;

        virtual bool    IsAttackDead() const;
        virtual bool    IsDefenseDead() const;

        virtual bool GetFighterList(UINT8 bySide, ::TVecBattleFighterPtr& rvecBattleFighter);

        // ====================  MUTATORS      ======================================= //
        virtual void PutFighters(UINT8 bySide, UINT64 qwLeaderID, UINT16 wLevel, 
                ::TVecBattleFighterPtr& rvecBattleFighter, UINT64 qwInstID = 0, bool bFullHP = true,
                SFeatureBasePtr pMainFeature = NULL);
        virtual void PutScene(IBattleFighterPtr pFighter);

        // ====================  OPERATORS     ======================================= //
        virtual void          Start(EBattleType eType);

    private:
        // ====================  METHODS       ======================================= //

        void          EnterRound();
        void          BeautyRound(UINT8 bySide, SBattleRound& rRound);
        void          CombineRound(UINT8 bySide, SBattleRound& rRound);

        UINT32        StartOneBattle();
        void          InitField();

        void InitFieldSideInfo(UINT8 bySide, TSetUINT16& rsetFighterID);
        void InitSummonInfo(TSetUINT16& rsetFighterID);

        void ResetBattleFighterBuff();

        void SaveReport();

        void DumpBattleProtocol();

        EBattleResult CalcWinner();

        // ====================  DATA MEMBERS  ======================================= //
        CBattleField        _oField;        // 战斗场地
        TVecBattleTeamPtr   _vecTeams;      // 双方战斗队伍
        CBattleFighterPtr   _pScene;        // 场景技能代表的战斗对象

        SBattleReport       _oReport;       // 发送给客户端的战报数据（本地也有保存）
}; // -----  end of class CBattleSimulator  ----- //

} // namespace NBattle

#endif // #ifndef BATTLE_SIMULATOR_H
