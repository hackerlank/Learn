#include "BattleDebugger.h"

#include "BattleTypeDef.h"
#include "BattleFighter.h"
#include "BattleSkill.h"

namespace NBattle
{

    CLog g_BattleLog;
    UINT64 g_qwDebuggerID = 0;
    string g_strDeuggerFile;

    string& operator << (string& s, const CBattleFighter& rBattleFighter)
    {
        ostringstream strInfo;
        strInfo << rBattleFighter.GetName().c_str() 
            << "(" << (UINT32)(rBattleFighter.GetSide()) << ":" << (UINT32) (rBattleFighter.GetPos() % ROW_LEN)  << "," << (UINT32) (rBattleFighter.GetPos() / ROW_LEN) <<  ")";
        s += strInfo.str();
        return s;
    }

    const char* AttrTypeToStr(EFighterAttr e)
    {
        switch(e)
        {
            case  1:
                return "物理攻击";
            case  2:
                return "法术攻击";
            case  3:
                return "物理防御";
            case  4:
                return "法术防御";
            case  5:
                return "物理免伤";
            case  6:
                return "魔法免伤";
            case  7:
                return "最大生命";
            case  8:
                return "身法";
            case  9:
                return "命中值";
            case 10:
                return "命中率";
            case 11:
                return "闪避值";
            case 12:
                return "闪避率";
            case 13:
                return "暴击值";
            case 14:
                return "暴击率";
            case 15:
                return "稳固值";
            case 16:
                return "稳固率";
            case 17:
                return "格挡值";
            case 18:
                return "格挡率";
            case 19:
                return "穿透值";
            case 20:
                return "穿透率";
            case 21:
                return "反击值";
            case 22:
                return "反击率";
            case 23:
                return "压制值";
            case 24:
                return "压制率";
            case 25:
                return "入场灵气";
            case 26:
                return "最大灵气";
            case 27:
                return "暴击伤害增加";
            case 28:
                return "暴击伤害减免";
            case 29:
                return "金攻";
            case 30:
                return "木攻";
            case 31:
                return "水攻";
            case 32:
                return "火攻";
            case 33:
                return "土攻";
            case 34:
                return "金防";
            case 35:
                return "木防";
            case 36:
                return "水防";
            case 37:
                return "火防";
            case 38:
                return "土防";
            case 39:
                return "物理攻击%";
            case 40:
                return "法术攻击%";
            case 41:
                return "物理防御%";
            case 42:
                return "法术防御%";
            case 43:
                return "最大生命%";
            case 44:
                return "身法%";
            case 45:
                return "命中值%";
            case 46:
                return "闪避值%";
            case 47:
                return "暴击值%";
            case 48:
                return "稳固值%";
            case 49:
                return "格挡值%";
            case 50:
                return "穿透值%";
            case 51:
                return "反击值%";
            case 52:
                return "压制值%";
            case 53:   
                return "法术抵抗";
            case 54:  
                return "反击伤害增加";
            case 55:  
                return "反击伤害减免";
            default:
                return "未知属性";
        }
        return "未知属性";
    }

#ifndef MS_VAL_STR
#define MS_VAL_STR(s) \
    case s:\
        return #s;
#endif
    const char* MSValToStr(EMachineState e)
    {
        switch(e)
        {
            MS_VAL_STR(eMSNone);
            MS_VAL_STR(eMSBeforeAct);
            MS_VAL_STR(eMSAfterAct);
            MS_VAL_STR(eMSOnAct);
            MS_VAL_STR(eMSAftCounter);
            MS_VAL_STR(eMSAftEvade);
            MS_VAL_STR(eMSAftHit);
            MS_VAL_STR(eMSAftCri);
            MS_VAL_STR(eMSAftBlocked);
            MS_VAL_STR(eMSOnHPAdd);
            MS_VAL_STR(eMSOnHPSub);
            MS_VAL_STR(eMSAftNormaleAtk);
            MS_VAL_STR(eMSAftActSkill);
            MS_VAL_STR(eMSAftPeerless);
            MS_VAL_STR(eMSAftPassiveSkill);
            MS_VAL_STR(eMSAftSomeSkillAtk);
            MS_VAL_STR(eMSAftSomeSkillAct);
            MS_VAL_STR(eMSBeforeDead);
            MS_VAL_STR(eMSOnHPLow);
            MS_VAL_STR(eMSOnEnter);
            MS_VAL_STR(eMSOnAuraAdd);
            MS_VAL_STR(eMSOnAuraSub);
            MS_VAL_STR(eMSOnRoundStart);
            MS_VAL_STR(eMSAftRound);
            MS_VAL_STR(eMSOnBuffGet);
            MS_VAL_STR(eMSOnBuffSet);
            MS_VAL_STR(eMSOnBuffAct);
            MS_VAL_STR(eMSAftBeAtked);
            MS_VAL_STR(eMSBeforeCri);
            MS_VAL_STR(eMSBeAtk);
            MS_VAL_STR(eMSOnAtkDmg);
            MS_VAL_STR(eMSOnCounter);
            MS_VAL_STR(eMSForget);
            MS_VAL_STR(eMSAfterAtk);
            MS_VAL_STR(eMSBeforeAtk);
            MS_VAL_STR(eMSBleed);
            MS_VAL_STR(eMSHit);
            MS_VAL_STR(eMSNormalAtk);
            MS_VAL_STR(eMSStart);
            MS_VAL_STR(eMSEnter);
            MS_VAL_STR(eMSEvade);
            MS_VAL_STR(eMSOnLostBuff);
            MS_VAL_STR(eMSRelease);
            MS_VAL_STR(eMSBeDmged);
            MS_VAL_STR(eMSAftDmg);
            MS_VAL_STR(eMSBeforeDmg);
            MS_VAL_STR(eMSOnDead);
            MS_VAL_STR(eMSState);
            MS_VAL_STR(eMSStun);
            MS_VAL_STR(eMSSkillAtk);
            MS_VAL_STR(eMSOnHPChanged);
            MS_VAL_STR(eMSOnHPHigh);
            MS_VAL_STR(eMSOnAllBuffGet);
            MS_VAL_STR(eMSOnAllLostBuff);
            MS_VAL_STR(eMSOnReiatsuAdd);
            MS_VAL_STR(eMSBeforeRound);
            MS_VAL_STR(eMSOnTherapyLaunch);
            MS_VAL_STR(eMSOnClearBuff);
            MS_VAL_STR(eMSAftDead);
            MS_VAL_STR(eMSOnOtherSideBuffAct);
            MS_VAL_STR(eMSOnKilled);
            MS_VAL_STR(eMSSummonTimeOut);
            MS_VAL_STR(eMSSelfSideDead);
            MS_VAL_STR(eMSSelfSideDamaged);
            MS_VAL_STR(eMSSelfSideTherapy);
            MS_VAL_STR(eMSOnCombineAdd);
            MS_VAL_STR(eMSAfterCombineAdd);
            MS_VAL_STR(eMSBeforeCombineSkill);
            MS_VAL_STR(eMSOnCombineSkill);
            MS_VAL_STR(eMSAfterCombineSkill);
            MS_VAL_STR(eMSSelfSideDeadAll);
            MS_VAL_STR(eMSOnSelfSideBuffGet);
            MS_VAL_STR(eMSOnOtherBounceDmg);
            MS_VAL_STR(eMSOnSelfPeerless);
            MS_VAL_STR(eMSOnOtherBeDmged);
            MS_VAL_STR(eMSOnSelfCrit);
            MS_VAL_STR(eMSOnSelfCounter);
            default:
            {
                string strTmp;
                strTmp += static_cast<UINT32>(e);
                return strTmp.c_str();
            }
        }
    }

    const char* SETValToStr(ESkillEffectType e)
    {
        switch(e)
        {
            case ENone:
                return "ENone";
            case EPhyDmg:
                return "EPhyDmg";
            case EMgcDmg:
                return "EMgcDmg";
            case ETrueDmg:
                return "ETrueDmg";
            case EHPDmg:
                return "EHPDmg";
            case EAbsorbHP:
                return "EAbsorbHP";
            case EAuraAdd:
                return "EAuraAdd";
            case EAuraSub:
                return "EAuraSub";
            case EBuffLast:
                return "EBuffLast";
            case EStun:
                return "EStun";
            case EConfuse:
                return "EConfuse";
            case EForget:
                return "EForget";
            case EBleed:
                return "EBleed";
            case EAttrAdd:
                return "EAttrAdd";
            case EAttrSub:
                return "EAttrSub";
            case EShield:
                return "EShield";
            case EAtkMulti:
                return "EAtkMulti";
            case EAssist:
                return "EAssist";
            case EProtect:
                return "EProtect";
            case EPierce:
                return "EPierce";
            case EBounceDmg:
                return "EBounceDmg";
            case EHide:
                return "EHide";
            case EInvincible:
                return "EInvincible";
            case EFreeze:
                return "EFreeze";
            case EExtendLast:
                return "EExtendLast";
            case ETherapyAdd:
                return "ETherapyAdd";
            case ESummon:
                return "ESummon";
            case ECongest:
                return "ECongest";
            case EBronze:
                return "EBronze";
            case EKingkong:
                return "EKingkong";
            case EBlock:
                return "EBlock";
            case EShoke:
                return "EShoke";
            case ENeverDead   :
                return  "ENeverDead";
            case EReflect     :
                return  "EReflect";
            case EResist      :
                return  "EResist";
            case EClone       :
                return  "EClone";
            case ESealed      :
                return  "ESealed";
            case EDamgeAbsorb :
                return  "EDamgeAbsorb";
            case EDamageReduce:
                return  "EDamageReduce";
            case EAttackAddP  :
                return  "EAttackAddP";
            case EAttackSubP  :
                return  "EAttackSubP";
            case EDefendAddP  :
                return  "EDefendAddP";
            case EDefendSubP  :
                return  "EDefendSubP";
            case EDialog      :
                return  "EDialog";
            case EBlunt       :
                return  "EBlunt";
            case EClearDebuff :
                return  "EClearDebuff";
            case EResistDeBuff:
                return  "EResistDeBuff";
            case ETransForm   :
                return  "ETransForm";
            case EToggleSkills:
                return  "EToggleSkills";
            case EPartBroken  :
                return  "EPartBroken";
            case ENoGainAura  :
                return  "ENoGainAura";
            case EEffectAdd   :
                return  "EEffectAdd";
            case EEffectSub   :
                return  "EEffectSub";
            case EDmgTherapy  :
                return  "EDmgTherapy";
            case EBuffAction  :
                return  "EBuffAction";
            case ESkillTrigger  :
                return  "ESkillTrigger";
            case EAttr2AttrAdd  :
                return  "EAttr2AttrAdd";
            case EStoned  :
                return  "EStoned";
            case EDeadAction  :
                return  "EDeadAction";
            case EBlind  :
                return  "EBlind";
            case EResistAdd  :
                return  "EResistAdd";
            case EResistSub  :
                return  "EResistSub";
            case EDamageShare   :
                return "EDamageShare";
            case ERevival   :
                return "ERevival";
            case ESkillEffectTypeMax:
                return "ESkillEffectTypeMax";
            case EBuffAction2  :
                return  "EBuffAction2";
            default:
                return NULL;
        }
    }

    const char* BFTValToStr(EBStateBuffType e)
    {
        switch(e)
        {
            case EBFBuffTypeNone:
                return "EBFBuffTypeNone";
            case EBFBuffTypeStun:
                return "EBFBuffTypeStun";
            case EBFBuffTypeConfuse:
                return "EBFBuffTypeConfuse";
            case EBFBuffTypeCover:
                return "EBFBuffTypeCover";
            case EBFBuffTypeEShock:
                return "EBFBuffTypeEShock";
            case EBFBuffTypeBlock:
                return "EBFBuffTypeBlock";
            case EBFBuffTypeInvincible:
                return "EBFBuffTypeInvincible";
            case EBFBuffTypeShield:
                return "EBFBuffTypeShield";
            case EBFBuffTypePierce:
                return "EBFBuffTypePierce";
            case EBFBuffTypeBleed:
                return "EBFBuffTypeBleed";
            case EBFBuffTypeForget:
                return "EBFBuffTypeForget";
            case EBFBuffTypeFreeze:
                return "EBFBuffTypeFreeze";
            case EBFBuffTypeBurned:
                return "EBFBuffTypeBurned";
            case EBFBuffTypeAtkAdd:
                return "EBFBuffTypeAtkAdd";
            case EBFBuffTypeAtkSub:
                return "EBFBuffTypeAtkSub";
            case EBFBuffTypeRedAdd:
                return "EBFBuffTypeRedAdd";
            case EBFBuffTypeRedSub:
                return "EBFBuffTypeRedSub";
            case EBFBuffTypeStoned:
                return "EBFBuffTypeStoned";
            case EBFBuffTypePoison:
                return "EBFBuffTypePoison";
            case EBFBuffTypeHide:
                return "EBFBuffTypeHide";
            case EBFBuffTypeBronze:
                return "EBFBuffTypeBronze";
            case EBFBuffTypeKingkong:
                return "EBFBuffTypeKingkong";
            case EBFBuffTypeDmgReduce:
                return "EBFBuffTypeDmgReduce";
            case EBFBuffTypeDmgAdd:
                return "EBFBuffTypeDmgAdd";
            case EBFBuffTypeCongest:
                return "EBFBuffTypeCongest";
            case EBFBuffTypeReflect:
                return "EBFBuffTypeReflect";
            case EBFBuffTypeHitDown:
                return "EBFBuffTypeHitDown";
            case EBFBuffTypeClone:
                return "EBFBuffTypeClone";
            case EBFBuffTypeSealed:
                return "EBFBuffTypeSealed";
            case EBFBuffTypeBeDmgReudce:
                return "EBFBuffTypeBeDmgReudce";
            case EBFBuffTypeBlind:
                return "EBFBuffTypeBlind";
            case EBFBuffTypeSmoke:
                return "EBFBuffTypeSmoke";
            case EBFBuffTypeGuard:
                return "EBFBuffTypeGuard";
            case EBFBuffTypeKindKing:
                return "EBFBuffTypeKindKing";
            case EBFBuffTypeBlunt:
                return "EBFBuffTypeBlunt";
            case EBFBuffTypeIceBlade:
                return "EBFBuffTypeIceBlade";
            case EBFBuffTypeThunderBlade:
                return "EBFBuffTypeThunderBlade";
            case EBFBuffTypeFireBlade:
                return "EBFBuffTypeFireBlade";
            case EBFBuffTypeSnowSoul:
                return "EBFBuffTypeSnowSoul";
            case EBFBuffTypeHaloRed:
                return "EBFBuffTypeHaloRed";
            case EBFBuffTypeHaloBlue:
                return "EBFBuffTypeHaloBlue";
            case EBFBuffTypeMax:
                return "EBFBuffTypeMax";
            case EBFBuffTypeDrogenSting:
                return "EBFBuffTypeDrogenSting";
            case EBFBuffTypeDmgShare:
                return "EBFBuffTypeDmgShare";
            case EBFBuffTypeAttrAdd:
                return "EBFBuffTypeAttrAdd";
            case EBFBuffTypeAttrSub:
                return "EBFBuffTypeAttrSub";
            case EBFBuffTypeActAtkAdd:
                return "EBFBuffTypeActAtkAdd";
            case EBFBuffTypeActDefAdd:
                return "EBFBuffTypeActDefAdd";
            default:
                return "What a fuck.";
        }
    }

    string& operator << (string& s, const CBattleSkillEffect& rBattleSkillEf)
    {
        ostringstream strInfo;
        if (rBattleSkillEf.GetSkillEffect())
        {
            strInfo << rBattleSkillEf.GetName().c_str();
#ifdef BATTLE_SKILL_ID
            strInfo << "(" << rBattleSkillEf.GetID() << ") ";
#endif
#ifdef BATTLE_SKILL_RATE
            strInfo << " Rate = " << rBattleSkillEf.GetRate() << ".";
#endif
#ifdef BATTLE_SKILL_TYPE
            strInfo << "Type: " << SETValToStr(rBattleSkillEf.GetType()) << ".";
#endif
        }
        s += strInfo.str();
        return s;
    }

    string& operator << (string& s, const CBattleBuff& rBattleBuff)
    {
        ostringstream strInfo;
        if (rBattleBuff.GetSkillEffect())
        {
            strInfo << rBattleBuff.GetName().c_str() << " Buff";
#ifdef BATTLE_SKILL_ID
            strInfo << "(" << rBattleBuff.GetID() << ") ";
#endif
#ifdef BATTLE_SKILL_INST_ID
            strInfo << "(" << rBattleBuff.GetInstID() << ") ";
#endif
#ifdef BATTLE_SKILL_BUFF_LAST
            strInfo << " Last = " << (UINT32)rBattleBuff.GetLast() << ".";
#endif
#ifdef BATTLE_SKILL_TYPE
            strInfo << "Type: " << SETValToStr(rBattleBuff.GetType()) << ".";
#endif
#ifdef BATTLE_SKILL_BUFF_CD
            strInfo << "CD: " << rBattleBuff.GetCD() << ".";
#endif
        }
        s += strInfo.str();
        return s;
    }

    const char* IndexToAttrStr(UINT8 byIndex)
    {
        switch(byIndex)
        {
            case  1:
                return "物理攻击";
            case  2:
                return "法术攻击";
            case  3:
                return "物理防御";
            case  4:
                return "法术防御";
            case  5:
                return "物理免伤";
            case  6:
                return "魔法免伤";
            case  7:
                return "最大生命";
            case  8:
                return "身法";
            case  9:
                return "命中值";
            case 10:
                return "命中率";
            case 11:
                return "闪避值";
            case 12:
                return "闪避率";
            case 13:
                return "暴击值";
            case 14:
                return "暴击率";
            case 15:
                return "稳固值";
            case 16:
                return "稳固率";
            case 17:
                return "格挡值";
            case 18:
                return "格挡率";
            case 19:
                return "穿透值";
            case 20:
                return "穿透率";
            case 21:
                return "反击值";
            case 22:
                return "反击率";
            case 23:
                return "压制值";
            case 24:
                return "压制率";
            case 25:
                return "入场灵气";
            case 26:
                return "最大灵气";
            case 27:
                return "暴击伤害增加";
            case 28:
                return "暴击伤害减免";
            case 29:
                return "金攻";
            case 30:
                return "木攻";
            case 31:
                return "水攻";
            case 32:
                return "火攻";
            case 33:
                return "土攻";
            case 34:
                return "金防";
            case 35:
                return "木防";
            case 36:
                return "水防";
            case 37:
                return "火防";
            case 38:
                return "土防";
            case 39:
                return "物理攻击%";
            case 40:
                return "法术攻击%";
            case 41:
                return "物理防御%";
            case 42:
                return "法术防御%";
            case 43:
                return "最大生命%";
            case 44:
                return "身法%";
            case 45:
                return "命中值%";
            case 46:
                return "闪避值%";
            case 47:
                return "暴击值%";
            case 48:
                return "稳固值%";
            case 49:
                return "格挡值%";
            case 50:
                return "穿透值%";
            case 51:
                return "反击值%";
            case 52:
                return "压制值%";
            case 53:   
                return "法术抵抗";
            case 54:  
                return "反击伤害增加";
            case 55:  
                return "反击伤害减免";
        }
        return "未知属性";
    };

    string GetAllAttrStr(const TVecFloat& rvecAttr)
    {
        ostringstream strInfo;
        for (auto it = rvecAttr.begin(); it != rvecAttr.end(); ++it)
        {
            UINT8 byIndex = static_cast<UINT8>(it-rvecAttr.begin());
            if (byIndex > EFIGHTATTR_MIN && byIndex < EFIGHTATTR_MAX)
            {
                strInfo << "Index:" << UINT32(byIndex);
                strInfo << IndexToAttrStr(byIndex) << ":" << *it;
                if (byIndex % 2)
                    strInfo << "\t";
                else
                    strInfo << "\n";
            }
        }
        return strInfo.str().c_str();
    }

    string GetAddAttrStr(const TVecFloat& rvecAttr)
    {
        ostringstream strInfo;
        UINT8 byCount = 0;
        for (auto it = rvecAttr.begin(); it != rvecAttr.end(); ++it)
        {
            UINT8 byIndex = static_cast<UINT8>(it-rvecAttr.begin());
            if (byIndex > EFIGHTATTR_MIN && byIndex < EFIGHTATTR_MAX)
            {
                if (*it > 0.0001f || *it < -0.0001f)
                {
                    strInfo << IndexToAttrStr(byIndex) << ":" << *it;
                    if (++byCount % 2)
                        strInfo << "\t";
                    else
                        strInfo << "\n";
                }
            }
        }
        return strInfo.str().c_str();
    }

    UINT32 g_dwCheatBit = 0;

    bool IsRate100()
    {
        return (g_dwCheatBit & CHEAT_RATE)?true:false;
    }

    bool IsPassiveDisable()
    {
        return (g_dwCheatBit & NO_PASSIVE)?true:false;
    }

    bool IsCrital100()
    {
        return (g_dwCheatBit & CHEAT_CRITICAL)?true:false;

    }

    bool IsNoMain()
    {
        return (g_dwCheatBit & CHEAT_NO_MIAN)?true:false;

    }

    bool IsActiveDisable()
    {
        return (g_dwCheatBit & NO_ACTIVE)?true:false;
    }

    bool IsCounter100()
    {
        return (g_dwCheatBit & CHEAT_COUNTER)?true:false;
    }

    bool IsDodge50()
    {
        return (g_dwCheatBit & CHEAT_DODGE_50)?true:false;
    }

} // namespace NBattle
