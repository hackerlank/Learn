
#ifndef MONSTER_H_
#define MONSTER_H_

#include "FighterPropCFG.h"
#include "AICFG.h"
#include "Creature.h"
#include "ItemProt.h"
#include "MonsterAI.h"

#include "Battle.h"

using namespace NItemProt;

enum EMonsterType
{
    eNonMonster,		//怪基类
    eRealMonster,		//地图上的怪
    eSharedMonster,		//地图上的共享怪
    eWorldBossMonster,	//世界boss
};

struct SFighterPropCFGEx;
struct SPath;
class CMonster : public CCreature, public CPoolObj<CMonster>
{
    friend class CMonsterMgr;

public:
    DEF_NEW_DELETE(CMonster);

    CMonster() : _wMonsterID(0), _qwCreatureID(0), _wGroupID(0), _eBattleType(EBTMonster),_byMapIndex(0),_pFighterPropCFG(NULL),_dwSpeed(0),_pPath(NULL) {}
    virtual ~CMonster();

    virtual EObjType GetObjType() const { return eObjMonster; }
    virtual UINT64 GetCreatureID() const { return _qwCreatureID; }
    virtual EMonsterType GetMonsterType() const { return eNonMonster; }
    virtual void OnDie(CCreature& rKiller);
    virtual bool IsDead() const;
    virtual void OnKill(CCreature& rTarget);
    virtual void Disappear();
    virtual void OnAttacked(CCreature& rAttacker);
    virtual bool CanFight(CCreature& /*rCreature*/);
    virtual bool IsAttackable(); 
    virtual float GetSpeedForWalker() const ;
    virtual bool IsWorldBoss() const { return false; }
    virtual void SetDir(float fDir);
    virtual void ReadjustBattleFighterList(vector<TVecBattleFighterPtr>& vecvecBattleFighter) {}

    void SetCreatureID(UINT64 qwCreatureID) { _qwCreatureID = qwCreatureID; }

    static void OnDrop(CCreature& rKiller,UINT16 wGroup,string &strReport);

    bool SetMonsterID(UINT16 wMonsterID);
    UINT16 GetMonsterID() const { return _wMonsterID; }
    SFighterPropCFG& GetFighterPropCfg();

    UINT64 GetBattleFighterList(vector<TVecBattleFighterPtr>& vecvecBattleFighter, UINT64 qwDefenseID, 
            TVecBattleFighterPtr& vecBattleFighterOther);

    static UINT64 GetBattleFighterListByGroupID(vector<TVecBattleFighterPtr>& vecvecBattleFighter, UINT16 wGroupID, UINT64 qwDefenseID, 
            TVecBattleFighterPtr& vecBattleFighterOther, CCreature *pCreature = NULL);

    static IBattleFighterPtr ToBattleFighter(UINT16 wMonsterID, UINT8 byPos, UINT64 qwDefenseID, CCreature *pCreature = NULL);

    static IBattleFighterPtr GetSceneFighter(UINT16 wMonsterID);

    IBattleFighterPtr GetSceneFighter();

    static UINT8 GetMonsterLevelByGroupID(UINT16 wGroupID);

    void GetMonsterAppear(SMonsterAppear& rMonsterAppear);
    void SetGroupID(UINT16 wGroupID);

    //设置战斗类型
    void SetBattleType(EBattleType eBattleType) { _eBattleType = eBattleType; }
    EBattleType GetBattleType() const { return _eBattleType; }

    UINT16 GetGroupID() { return _wGroupID; }
    CGameMapPtr GetBornMap() const { return _pBornMap.lock(); }
    void SetBornMap(const CGameMapPtr& pMap) { _pBornMap = pMap; }
    void SetMonsterVal(UINT32 dwKey, const string& strVal);
    bool GetMonsterVal(UINT32 dwKey, string& strVal);
    void ClearMonsterVal();
    CDungeonPtr GetDgnPtr();
    bool AllowMultiPlayerAttack() const;
    bool AllowDiedDisappear() const;
    bool CanNotifyAppear() const;
    static void DropToPlayer(UINT16 wGroupId,CPlayer& rPlayer,bool bIsAppend,std::vector<SItemGenInfo>* pvecItems =NULL ,TVecResource * pvecRes =NULL);
    static void DropToPlayer(UINT16 wGroupId, std::vector<SItemGenInfo>& pvecItems, TVecResource& pvecRes);
    UINT8 GetMapIdx(){ return _byMapIndex;} 
    void  SetMapIdx(UINT8 byIndx){_byMapIndex = byIndx;}
    CWalker& GetWalk(){return _oWalker;}
    UINT32& Speed(){return _dwSpeed;}
    CMonsterPtr GetThisPtr();
    void CreateAI(); 
    void SetInPathFind(bool bFind);
    void OnPathFound(TVecPoint& rVecPath);
    //主动对他发动挑战
    bool FighterToOther(CCreature& rTarget);
    bool FighterToOther(CCreature& rTarget,bool &bPlayerWiner);
    CMonsterAIPtr GetAI();
    const SPath* GetPath(){ return _pPath;}
    void SetPath(const SPath* pPath){ _pPath = pPath;}

    //buffer相关
    virtual EBuffType GetBuffType() const { return eBTMonster; }
    virtual void UpdateBuff2DB(const SDBBuffInfo& rDBBuffInfo, EDataChange eDataChange) {};
    virtual UINT64 GetRoleID() const { return 0; };
    virtual UINT64 GetOwnerID() const { return 0; };
    virtual void OnBuffChanged(EDataChange eType, const SBuffInfo& rInfo);

protected:
    UINT16 _wMonsterID;
    UINT64 _qwCreatureID;
    UINT16 _wGroupID;

    EBattleType _eBattleType;

    UINT8 _byMapIndex;//小地图用
    CGameMapWtr _pBornMap;
    SFighterPropCFG* _pFighterPropCFG;
    map<UINT32, string> _mapKey2Val;
    UINT32 _dwSpeed;
    const SPath* _pPath;
    CMonsterAIWtr _pAI;
};

inline CLogObj& operator<<(CLogObj& src, const CMonster& rMonster)
{
    src << " [" << rMonster.GetDescription() << "]";
    return src;
}

#endif // MONSTER_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

