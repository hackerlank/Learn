
#ifndef PET_H_
#define PET_H_

#include "stdafx.h"
#include "ProtoCommon.h" // fox TVecFtAttrMod
#include "SkillSlots.h"
#include "RoleInfoDefine.h"
#include "BoostObject.h"

#include "Battle.h"

using namespace NProtoCommon;
class CPet : public CPoolObj<CPet>, public CBoostObject
{
public:
    CPet():_wPetID(0), _bySelected(0), _byLevel(0), _dwExp(0), _bDirty(true) {}
    virtual ~CPet() {}

    bool Init(UINT16 wPetID);
    bool Load(const SPetDataInfo& sPetDataInfo);

    UINT16 GetID() const { return _wPetID; }
    bool IsHide() const { return _bySelected == 2 || _bySelected == 0; }

    void SetSelected(UINT8 bySelected) { _bySelected = bySelected; }
    UINT8 GetSelected() const { return _bySelected; }

    void SetPetLevel(UINT8 byLevel) { _byLevel = byLevel; }
    UINT8 GetPetLevel() const { return _byLevel; }

    void SetPetExp(UINT32 dwExp) { _dwExp = dwExp; }
    UINT32 GetPetExp() const { return _dwExp; }

    void SetPetSkill();

    void InitItemAttr();

    IBattleFighterPtr ToBattleFighter(const TVecFloat& allPetAttr) const;
    
    void InitPetAttr();
    void RebuildAttr();
    void AppendAttr(TVecFloat& vecAttr);

    void GetAllSkillID(TVecUINT32& rvecSkillID) const;

    // 其他
    bool IsDirty() const { return _bDirty; }
    void SetDirty(bool bDirty) { _bDirty = bDirty; }
    void GetShowInfo(NGlobalChatProt::SShowInfo& sInfo);

    virtual EBoostObjectType GetType() const { return eBOTPet;}
    virtual void Super();

private:

    UINT16 _wPetID;
    UINT8 _bySelected;                  // XXX: 0-未选中 1-出战且显示 2-出战隐藏
    UINT8 _byLevel;                     // 宠物等级
    UINT32 _dwExp;                      // 宠物经验
    TVecFloat _vecAttr;                 // 基础属性加成

    //TVecFtAttrMod vecAttr; // 解锁属性加成：获得此宠物后对全队所加的属性
    CSkillSlots<PET_UPSKILL_SLOTS> _oUpSkills; // 所带出的主动技能
    bool _bDirty;
};

#endif // PET_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

