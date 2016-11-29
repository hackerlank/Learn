
#ifndef FORMATION_H_
#define FORMATION_H_

#include "stdafx.h"
#include "ArrSlots.h"
#include "ProtoCommon.h" // for TVecFtAttrMod
#include "CommonDef.h" // fox INVALID_POS

#include "Battle.h"
#include "FightFormation.h"
using namespace NFightFormation;
#ifndef MAX_POS // XXX: 这里原来从"BattleTypeDef.h"里面获得的
#define MAX_POS 9
#endif

//最大上阵人数
#define MAX_FIGHTER_SIZE 5
using namespace NProtoCommon;

struct LineupGrid
{
    LineupGrid() {}
    LineupGrid(const CFighterPtr& pFighter) : pFighter(pFighter) {}

    CFighterPtr pFighter;
    TVecFtAttrMod vecAttr; // 属性加成 XXX: 第1版中可能不会对阵位加属性
};

struct Lineup
{
    Lineup() : iPos(INVALID_POS) {}
    Lineup(CFighterPtr& pFighter, INT32 iPos) : pFighter(pFighter), iPos(iPos) {}

    CFighterPtr pFighter;
    INT32 iPos;
};

typedef std::vector<Lineup> TVecLineup;

class CFormation : public CArrSlots<int, LineupGrid, MAX_POS> // XXX: [0,8]
{
public:
//    typedef CArrSlots<int, LineupGrid, MAX_POS> BASE;

public:
    CFormation()  {}
    ~CFormation() {}

    bool Init();

    CFighterPtr GetMainFighter();
    CFighterPtr GetMainFighter() const;

    UINT64 GetBattleFighters(TVecBattleFighterPtr& vecBattleFighter, EBattleType eBattleType);
    void GetDefaultFightFormation(FightFormationInfo& rFightFormationInfo);
    UINT32 GetFightersCurrHP();
    UINT32 GetFightersMaxHP();
    UINT32 GetFightersMaxHP2();
    void RegenAllHP();
    bool RecoverFighters(TVecBattleFighterPtr& vecBattleFighter);
    void AddFightersCurrHP(UINT32 dwHP);
    void AddFightersCurrHPPer(float fFactor);

    int GetEmptySlot();
    bool PutIntoFormation(CFighterPtr pFighter);
    bool CanPutInto(int iSlot, const CFighterPtr& pFighter);
    bool PutInto(int iSlot, const CFighterPtr& pFighter);
    bool Set(int iSlot, const CFighterPtr& pFighter);
    bool Reset(int iSlot, const CFighterPtr& pFighter);
    bool Reset(int iSlot);
    bool Swap(int iSlotSrc, int iSlotDst);
    bool Move(int iSlotSrc, int iSlotDst);
    void Clear();
    bool SetFomation(TVecLineup& vecLineup);
    bool ClearWithOrigin(TVecLineup& vecLineup);
    void GetLineup(TVecLineup& vecLineup);

    //void Notify();
    //void Update2DB();
    //void LoadFromDB();

    //获取上阵散仙信息
    std::string GetInfoLog();
private:
};

#endif // FORMATION_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

