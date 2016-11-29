
#ifndef FORMATIONMGR_H_
#define FORMATIONMGR_H_

#include "ProtoCommon.h" // for TVecFtAttrMod
#include "CommonDef.h" // fox INVALID_POS
#include "FightFormation.h"
#include "RoleInfoDefine.h"

#include "Battle.h"

#ifndef MAX_POS // XXX: 这里原来从"BattleTypeDef.h"里面获得的
#define MAX_POS 9
#endif

using namespace NProtoCommon;
using namespace NFightFormation;
using namespace NRoleInfoDefine;
typedef std::map<UINT16,FightFormationInfo> TMapFightFormationInfo;
class CFightFormationMgr
{
public:
    CFightFormationMgr(CPlayer& rPlayer):_rPlayer(rPlayer){}
    ~CFightFormationMgr() {}
    EFightFormationResult OnGetFormation(UINT16 wBattleType,FightFormationInfo& rFightFormationInfo);
    EFightFormationResult OnSetFormation(UINT16 wBattleType,const FightFormationInfo& rFightFormationInfo);
    bool IsCanSet(const FightFormationInfo& rFightFormation);
    
    bool LoadFromDB(const RoleDataInfo& rRoleDataInfo);
    void Update2DB(UINT16 wBattleType,FightFormationInfo& rFightFormationInfo, EDataChange eDataChanige = eOpUpdate);
    UINT64 GetBattleFighters(EBattleType eBattleType,TVecBattleFighterPtr& vecBattleFighter);

    //获取战斗力
    UINT32 GetBattlePoint(EBattleType eBattleType);

    FightFormationInfo GetFormationByType(EBattleType eBattleType);

    //清除阵型数据
    void ClearFormation(EBattleType eBattleType);

private:
    CPlayer& _rPlayer;
    TMapFightFormationInfo _mapFightFormationInfo;
};

#endif // FORMATIONMGR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

