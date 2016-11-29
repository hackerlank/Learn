
#ifndef FIGHTHEROINFOMGR_H_
#define FIGHTHEROINFOMGR_H_
#include "RoleInfoDefine.h"
#include "CommonDef.h"
#include "Battle.h"
#include "FightFormation.h"
using namespace NProtoCommon;
using namespace NFightFormation;


using namespace NRoleInfoDefine;

typedef std::map<UINT64,SFightHeroDBInfo> TMapFightHeroDBInfo;
typedef std::map<UINT16,TMapFightHeroDBInfo> TMapBattleType2MapFightHeroDBInfo;
class CFightHeroInfoMgr 
{

public:
    CFightHeroInfoMgr(CPlayer& rPlayer);
    ~CFightHeroInfoMgr() {}
    static bool FightHeroInfoInit();
    bool LoadFromDB(const RoleDataInfo& rRoleDataInfo);
    void Update2DB(const SFightHeroDBInfo& rInfo, EDataChange eDataChanige = eOpUpdate);

    //更新仙信息
    void UpdateFightHeroDBInfo(SFightHeroDBInfo& rFightHeroDBInfo,bool bSaveToDB=true);

    //获取散仙信息false表示未存储
    bool GetFightHeroDBInfo(UINT16 wBattleType,UINT64 qwInstID,SFightHeroDBInfo& rFightHeroDBInfo);

    //清理指定战斗类型的散仙数据
    void ClearByBattleType(UINT16 wBattleType);

    //获取散仙信息
    void OnGetFightHeroInfo(UINT16 wBattleType,TVecFightHeroInfo& vecTVecFightHeroInfo);

    //获取当前战斗散仙数据
    bool GetBattleFighterInfo(EBattleType eBattleType,TVecBattleFighterPtr& vecBattleFighter);

    //保存当前战斗散仙数据
    void SaveBattleFighterInfo(EBattleType eBattleType,TVecBattleFighterPtr& vecBattleFighter);

    //检测所有散仙血量是否为0
    bool CheckAllFighterHPByBattleType(UINT16 wBattleType);

private:
    TMapFightHeroDBInfo& GetMapFightHeroDBInfoByBattleType(UINT16 wBattleType); 
private:

    CPlayer& _rPlayer;
    TMapBattleType2MapFightHeroDBInfo _mapBattleType2MapFightHeroDBInfo;
};

#endif // 

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

