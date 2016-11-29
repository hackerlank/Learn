
#ifndef PETSLOTS_H_
#define PETSLOTS_H_

#include "VecSlots.h"
#include "Pet.h"
#include "RoleInfoDefine.h"
#include "Battle.h"
#include "FormationProt.h"
#include "BoostOwner.h"

using namespace NProtoCommon;
using namespace NFormationProt;

class CUser;

class CPetSlots : public CVecSlots<int, CPetPtr>, public CBoostOwner
{

public:
    CPetSlots(CUser& rUser) : 
        CVecSlots(100), _rUser(rUser)/*, _byLevel(1), _dwExp(0), _dwSpirit(0)*/ {}
    virtual ~CPetSlots() {}

    CPetPtr GetPet(UINT16 wPetID, int* pIdx = NULL) const
    {
        VecSlotsEnumerateByID<UINT16, int, CPetPtr> en(wPetID);
        enumerate(en);
        if (en._sSlot == INVALID_SLOT)
            return NULL;
        if (pIdx)
            *pIdx = en._sSlot;
        return en._pObj;
    }

    void GetAllPets(TVecPetDataInfo& vecPets);
    bool GetAllPetAttr(TVecFloat& vecAddAttr) const;

    /*void SetLevel(UINT8 byLevel) { _byLevel = byLevel; }
    UINT8 GetLevel() const { return _byLevel; }

    void SetExp(UINT32 dwExp) { _dwExp = dwExp; }
    UINT32 GetExp() const { return _dwExp; }

    void SetSpirit(UINT32 dwSpirit) { _dwSpirit = dwSpirit; }
    UINT32 GetSpirit() const { return _dwSpirit; }*/

    CPetPtr GetCurrPet() const { return _pCurrPet; }
    const TVecFloat& GetAttrVec() const;
    
    //记录日志
    void WritePetLog(UINT16 wID,UINT8 byOpType);

    // 获得阵灵
    CPetPtr AdoptPet(UINT16 wPetID, bool bUpdate = true, bool bForce = false);
    bool LoadPet(const SPetDataInfo& sPetDataInfo);

    // 阵灵跟随
    bool PetFollow(CPetPtr& pPet, bool bFollow);
    bool PetFollow(UINT16 wPetID, bool bFollow);

    // 选择出战
    bool ActivePet(UINT16 wPetID, UINT8 byType, bool bUpdate = true);
    bool ActivePet(CPetPtr& pPet, UINT8 byType, bool bUpdate = true);

    // 幻化
    bool PetUpgrade(CPetPtr& pPet);
    bool PetUpgrade(UINT16 wPetID);

    void UpdateGroupAttr();

    // 升级
    EFormPetType PetLevelUp(CPetPtr& pPet, UINT8 byType = 0);
    EFormPetType PetLevelUp(UINT16 wPetID, UINT8 byType = 0);

    EFormPetType QuickPetLevelUp(UINT16 wPetID);
    
    bool GetBattleFighters(std::vector<IBattleFighterPtr>& vecBattleFighter);

    void Update2DB(CPetPtr& pPet, EDataChange eDataChange = eOpUpdate);
    void Update2DB(SRolePetInfo& sRolePetInfo, EDataChange eDataChange = eOpUpdate);

    UINT32 GetPetBattlePoint() const;

    void   UpdateRankInfo() const;

    virtual void SuperBoostObjects();

private:
    CUser& _rUser;
    CPetPtr _pCurrPet;          // 当前所出战的阵灵
    mutable TVecFloat _vecAttr; // 所有阵灵属性

    /*以下几个变量已经不用
    UINT8 _byLevel;     // 等级
    UINT32 _dwExp;      // 升级经验
    UINT32 _dwSpirit;   // 灵力值 XXX: 影响阵灵技能输出*/
};

#endif // PETSLOTS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

