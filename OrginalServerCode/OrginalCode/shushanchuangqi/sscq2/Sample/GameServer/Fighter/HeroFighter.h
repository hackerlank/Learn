
#ifndef HEROFIGHTER_H_
#define HEROFIGHTER_H_

#include "Fighter.h"
#include "HeroFighterSkills.h"
#include "HeroFighterXinFa.h"
#include "GemstoneSlots.h"
#include "EquipTrumpSlot.h"

class CHeroFighter : public CFighter
{
    public:
        CHeroFighter(UINT16 wFighterID);
        virtual ~CHeroFighter();

        virtual UINT8 GetLevel() const;
        virtual UINT64 GetExp() const;
        virtual const string GetName() const;

        void SetUser(const CUserPtr& pUser) override;
        virtual void GetAllSkillsID(TVecUINT32& vecSkillsID) const;

        bool ToProt(SFighterSpecInfo& sFighterInfo) const override;

        void InitSkills(const TVecUINT32& vecSkillID) override;
        //初始化函数InitSkills后调用
        void Init() override;
        CHeroFighterSkills& GetSkills() { return _oSkills; }
        const CHeroFighterSkills& GetSkills() const { return _oSkills; }
        CHeroFighterXinFa& GetXinFas() { return _oXinFas; }
        const CHeroFighterXinFa& GetXinFas() const { return _oXinFas; }

        void InitDujieAttr();
        const TVecFloat& GetDujieAttr() const { return _vecDujieAttr; }
        const TVecFloat& GetCuiTiAttr() const;
        ECuiTiResult CuiTiUpgrade(ECuiTiType eCuiTiType, UINT8& byLevel, bool bForce = false);

        virtual bool RebuildAttr() const override;
        virtual void OnAttrRebuilded() const;

        EShiftResult Shift(CFighterPtr& pFighter);
        EDismissResult FighterDismiss();

        // 渡劫相关
        EDujieResult DujieUpgrade(bool bOneKey);
        void SetDujieLevelByGM(UINT8 byLevel);
        void WriteDujieLog(string &sPeriodName);

        //购买散仙时渡劫
        bool BuyFighterDujie(UINT8 byDujieLvl);

        //LogServer日志
        void WriteFighterLog(EFighterOptType eType,UINT32 dwDetail, UINT64 qwResult,UINT16 wID);
        void UpdateRankInfo() const;
        CGemstoneSlots& GetGemstoneSlots() { return _oGemStone; }

        CEquipTrumpSlot& GetEquipTrumpSlot() { return _oEquipTrumpSlot; }

        void Super();

        void BuildBattleInfo() const;

    private:
        void OnDujieLevelChanged(UINT8 byNewLevel);
        void DujieUpgradeEvent();

        virtual bool GetAllSkills(TVecUINT32& rvecAllSklls, UINT32& dwNormalAttack) const;

        virtual SFeatureBasePtr GetAppear() const;
        virtual SFeatureBasePtr GetBattleAppear(EBattleType eBattleType) const;

    private:
        CHeroFighterSkills _oSkills;        // 散仙技能
        CHeroFighterXinFa _oXinFas;         // 散仙心法

        mutable CGemstoneSlots _oGemStone;  // 散仙宝石

        CEquipTrumpSlot _oEquipTrumpSlot;   // 装备法宝栏

        mutable TVecFloat _vecCuiTi;        // 淬体加成属性列表
        mutable TVecFloat _vecDujieAttr;    // 渡劫列表
};

#endif // HEROFIGHTER_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

