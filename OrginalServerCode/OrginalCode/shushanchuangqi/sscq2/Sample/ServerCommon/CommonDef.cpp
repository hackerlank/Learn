#include "CommonDef.h"

using namespace NProtoCommon;

const char* StrToResourceStr(string& str)
{
    if (str.compare("Gold") == 0)
        return "仙石";
    else if (str.compare("Silver") == 0)
        return "银币";
    else if (str.compare("Coupon") == 0)
        return "礼券";
    else if (str.compare("GiftCoin") == 0)
        return "金券";
    else if (str.compare("Exp") == 0)
        return "经验";
    else if (str.compare("Prestige") == 0)
        return "声望";
    else if (str.compare("Soul") == 0)
        return "魂魄";
    else if (str.compare("Honor") == 0)
        return "荣誉";
    else if (str.compare("PExp") == 0)
        return "修为";
    else if (str.compare("Sigil") == 0)
        return "符印";
    else if (str.compare("CentsY") == 0)
        return "仙元";
    else if (str.compare("Action") == 0)
        return "体力";
    else if (str.compare("Sop") == 0)
        return "阅历";
    else if (str.compare("Taoism") == 0)
        return "道术";
    else if (str.compare("Poten") == 0)
        return "渡劫点数";
    else if (str.compare("Reiki") == 0)
        return "灵力";
    else if (str.compare("HFP") == 0)
        return "寻仙积分";
    else if (str.compare("DemonSoul") == 0)
        return "锁妖塔魂值";
    else if (str.compare("SoulAttack") == 0)
        return "攻击之魂";
    else if (str.compare("SoulHp") == 0)
        return "生命之魂";
    else if (str.compare("SoulCritical") == 0)
        return "暴击之魂";
    else if (str.compare("SoulCounter") == 0)
        return "反击之魂";
    else if (str.compare("SoulSpeed") == 0)
        return "身法之魂";
    else if (str.compare("SoulDefence") == 0)
        return "防御之魂";
    else if (str.compare("SoulHit") == 0)
        return "命中之魂";
    else if (str.compare("SoulDodge") == 0)
        return "闪避之魂";
    else if (str.compare("AchievementAP") == 0)
        return "成就点";
    else if (str.compare("CollectAP") == 0)
        return "收藏点";
    else if (str.compare("GuildContrib") == 0)
        return "帮派贡献";
    string str1 = "未知货币：" + str;
    return str1.c_str();
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

string GetAddAttrStr(const TVecFloat& rvecAttr)
{
    ostringstream strInfo;
    for (auto it = rvecAttr.begin(); it != rvecAttr.end(); ++it)
    {
        UINT8 byIndex = static_cast<UINT8>(it-rvecAttr.begin());
        if (byIndex > EFIGHTATTR_MIN && byIndex < EFIGHTATTR_MAX)
        {
            if (*it > 0.0001f || *it < -0.0001f)
                strInfo << IndexToAttrStr(byIndex) << ":" << *it << "\n";
        }
    }
    return strInfo.str().c_str();
}

