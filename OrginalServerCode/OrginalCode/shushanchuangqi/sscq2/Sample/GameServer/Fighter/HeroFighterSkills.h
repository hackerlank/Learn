#ifndef HEROFIGHTERSKILLS_H_
#define HEROFIGHTERSKILLS_H_

#include "SkillSlots.h"
#include "GameServerLog.h"

class CHeroFighterSkills
{
    public:
        CHeroFighterSkills();
        ~CHeroFighterSkills();

        void SetUser(const CUserPtr& pUser);
        CUserPtr GetUser() const;
        void SetFighter(const CFighterPtr& pFighter);
        CFighterPtr GetFighter() const;

        ESkillResult UpgradeActiveSkill(UINT32 dwSkillID);      // 主动技能升级
        ESkillResult UpgradePassiveSkill(UINT32 dwSkillID);     // 被动技能升级
        ESkillResult UpSkill(UINT32 dwSkillID, int iSlot);

        void GetAllUpSkills(TVecUINT32& vecSkills) const;       //所有技能(3主动 1无双 2被动)
        void GetActiveSkills(TVecUINT32& vecSkills) const;   //所有主动技能
        void GetPassiveSkills(TVecUINT32& vecSkills) const;   //所有主动技能
        void GetAllCombineSkills(TVecUINT32& vecSkills) const;
        UINT32 GetPeerLessID() const;

        void UpSkillFromDB(UINT32 dwSkillID, int iSlot);
        void UpPassiveSkillFromDB(UINT32 dwSkillID, UINT32 dwSkillQuality, UINT32 dwSkillLevel);

        void Update2DB(EDataChange eDataChange);

        void UpdatePassiveSkill2DB(EDataChange eDataChange);

        //LogServer日志
        void WriteFighterLog(EFighterOptType eType,UINT32 dwDetail, UINT64 qwResult,UINT16 wID);

        //散仙组合技能
        void AddCombinationSkill(UINT32 dwSkillID);
        void ClearCombinationSkill();

        bool UnlockAllSkillByDujie(bool bInit);
        void FighterSkillDismiss(TVecItemGenInfo& vecItems);

        void GetPassiveSkillAttr(TVecFloat& vecAttr) const;

    private:
        CUserWtr        _pUser;
        CFighterWtr     _pFighter;

        CSkillSlots<HERO_UPSKILL_SLOTS> _oUpSkills; // 所有装备的技能  XXX 0/1/2主动技能 3无双技能
        TVecUINT32          _vecPassiveSkill;       // 被动技能（只是加属性用的）
        TVecUINT32          _vecCombinationSkillID;

};

#endif // HEROFIGHTERSKILLS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

