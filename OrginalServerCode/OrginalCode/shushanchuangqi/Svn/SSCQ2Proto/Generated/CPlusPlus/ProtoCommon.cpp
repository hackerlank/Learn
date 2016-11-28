/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ProtoCommon.cpp
//  Purpose:      各个协议、服务器之间通用结构存放文件
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ProtoCommon.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NProtoCommon
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ECareerType e)
{
	switch(e)
	{
	case ECAREER_ALL:
		return "ECAREER_ALL";
	case ECAREER_RU:
		return "ECAREER_RU";
	case ECAREER_SHI:
		return "ECAREER_SHI";
	case ECAREER_DAO:
		return "ECAREER_DAO";
	case ECAREER_MO:
		return "ECAREER_MO";
	case ECAREER_MAX:
		return "ECAREER_MAX";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECareerType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECareerType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ECAREER_ALL", ECAREER_ALL));
		mapStr2Val.insert(make_pair("ECAREER_RU", ECAREER_RU));
		mapStr2Val.insert(make_pair("ECAREER_SHI", ECAREER_SHI));
		mapStr2Val.insert(make_pair("ECAREER_DAO", ECAREER_DAO));
		mapStr2Val.insert(make_pair("ECAREER_MO", ECAREER_MO));
		mapStr2Val.insert(make_pair("ECAREER_MAX", ECAREER_MAX));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

#ifdef PROT_USE_XML

const char* EnumValToStr(ESexType e)
{
	switch(e)
	{
	case ESEX_ALL:
		return "ESEX_ALL";
	case ESEX_MALE:
		return "ESEX_MALE";
	case ESEX_FEMALE:
		return "ESEX_FEMALE";
	case ESEX_MAX:
		return "ESEX_MAX";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ESexType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ESexType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ESEX_ALL", ESEX_ALL));
		mapStr2Val.insert(make_pair("ESEX_MALE", ESEX_MALE));
		mapStr2Val.insert(make_pair("ESEX_FEMALE", ESEX_FEMALE));
		mapStr2Val.insert(make_pair("ESEX_MAX", ESEX_MAX));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

#ifdef PROT_USE_XML

const char* EnumValToStr(EColor e)
{
	switch(e)
	{
	case ECOLOR_BLACK:
		return "ECOLOR_BLACK";
	case ECOLOR_WHITE:
		return "ECOLOR_WHITE";
	case ECOLOR_GREEN:
		return "ECOLOR_GREEN";
	case ECOLOR_BLUE:
		return "ECOLOR_BLUE";
	case ECOLOR_PURPLE:
		return "ECOLOR_PURPLE";
	case ECOLOR_ORANGE:
		return "ECOLOR_ORANGE";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EColor& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EColor> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ECOLOR_BLACK", ECOLOR_BLACK));
		mapStr2Val.insert(make_pair("ECOLOR_WHITE", ECOLOR_WHITE));
		mapStr2Val.insert(make_pair("ECOLOR_GREEN", ECOLOR_GREEN));
		mapStr2Val.insert(make_pair("ECOLOR_BLUE", ECOLOR_BLUE));
		mapStr2Val.insert(make_pair("ECOLOR_PURPLE", ECOLOR_PURPLE));
		mapStr2Val.insert(make_pair("ECOLOR_ORANGE", ECOLOR_ORANGE));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

#ifdef PROT_USE_XML

const char* EnumValToStr(ECoinType e)
{
	switch(e)
	{
	case eCoinNone:
		return "eCoinNone";
	case eGoldCoin:
		return "eGoldCoin";
	case eSilverCoin:
		return "eSilverCoin";
	case eCouponCoin:
		return "eCouponCoin";
	case eHonourCoin:
		return "eHonourCoin";
	case eCoinEnd:
		return "eCoinEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECoinType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECoinType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eCoinNone", eCoinNone));
		mapStr2Val.insert(make_pair("eGoldCoin", eGoldCoin));
		mapStr2Val.insert(make_pair("eSilverCoin", eSilverCoin));
		mapStr2Val.insert(make_pair("eCouponCoin", eCouponCoin));
		mapStr2Val.insert(make_pair("eHonourCoin", eHonourCoin));
		mapStr2Val.insert(make_pair("eCoinEnd", eCoinEnd));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

#ifdef PROT_USE_XML

const char* EnumValToStr(EDataChange e)
{
	switch(e)
	{
	case eOpNone:
		return "eOpNone";
	case eOpAdd:
		return "eOpAdd";
	case eOpDel:
		return "eOpDel";
	case eOpUpdate:
		return "eOpUpdate";
	case eOpReplace:
		return "eOpReplace";
	case eOpAddIgnore:
		return "eOpAddIgnore";
	case eOpMax:
		return "eOpMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDataChange& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDataChange> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eOpNone", eOpNone));
		mapStr2Val.insert(make_pair("eOpAdd", eOpAdd));
		mapStr2Val.insert(make_pair("eOpDel", eOpDel));
		mapStr2Val.insert(make_pair("eOpUpdate", eOpUpdate));
		mapStr2Val.insert(make_pair("eOpReplace", eOpReplace));
		mapStr2Val.insert(make_pair("eOpAddIgnore", eOpAddIgnore));
		mapStr2Val.insert(make_pair("eOpMax", eOpMax));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

const char* GetDescription(EDataChange e)
{
	switch(e)
	{
	case eOpNone:
		return "无变化";
	case eOpAdd:
		return "数据增加";
	case eOpDel:
		return "数据删除";
	case eOpUpdate:
		return "数据更新";
	case eOpReplace:
		return "数据替换";
	case eOpAddIgnore:
		return "数据仅新增";
	case eOpMax:
		return "最大值";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EMoneyType e)
{
	switch(e)
	{
	case EMONEY_NONE:
		return "EMONEY_NONE";
	case EMONEY_GOLD:
		return "EMONEY_GOLD";
	case EMONEY_SILVER:
		return "EMONEY_SILVER";
	case EMONEY_COUPON:
		return "EMONEY_COUPON";
	case EMONEY_GIFTCOIN:
		return "EMONEY_GIFTCOIN";
	case EMONEY_EXP:
		return "EMONEY_EXP";
	case EMONEY_PRESTIGE:
		return "EMONEY_PRESTIGE";
	case EMONEY_SOUL:
		return "EMONEY_SOUL";
	case EMONEY_HONOR:
		return "EMONEY_HONOR";
	case EMONEY_PEXP:
		return "EMONEY_PEXP";
	case EMONEY_SIGIL:
		return "EMONEY_SIGIL";
	case EMONEY_CENTSY:
		return "EMONEY_CENTSY";
	case EMONEY_ACTION:
		return "EMONEY_ACTION";
	case EMONEY_SOP:
		return "EMONEY_SOP";
	case EMONEY_TAOISM:
		return "EMONEY_TAOISM";
	case EMONEY_POTEN:
		return "EMONEY_POTEN";
	case EMONEY_REIKI:
		return "EMONEY_REIKI";
	case EMONEY_HFP:
		return "EMONEY_HFP";
	case EMONEY_DEMONSOUL:
		return "EMONEY_DEMONSOUL";
	case EMONEY_SOULATTACK:
		return "EMONEY_SOULATTACK";
	case EMONEY_SOULHP:
		return "EMONEY_SOULHP";
	case EMONEY_SOULCRITICAL:
		return "EMONEY_SOULCRITICAL";
	case EMONEY_SOULCOUNTER:
		return "EMONEY_SOULCOUNTER";
	case EMONEY_SOULSPEED:
		return "EMONEY_SOULSPEED";
	case EMONEY_SOULDEFENCE:
		return "EMONEY_SOULDEFENCE";
	case EMONEY_SOULHIT:
		return "EMONEY_SOULHIT";
	case EMONEY_SOULDODGE:
		return "EMONEY_SOULDODGE";
	case EMONEY_ACHIEVEMENTAP:
		return "EMONEY_ACHIEVEMENTAP";
	case EMONEY_COLLECTAP:
		return "EMONEY_COLLECTAP";
	case EMONEY_GUILDCONTRIB:
		return "EMONEY_GUILDCONTRIB";
	case EMONEY_STAMPHUANG:
		return "EMONEY_STAMPHUANG";
	case EMONEY_STAMPXUAN:
		return "EMONEY_STAMPXUAN";
	case EMONEY_STAMPDI:
		return "EMONEY_STAMPDI";
	case EMONEY_STAMPTIAN:
		return "EMONEY_STAMPTIAN";
	case EMONEY_STAMPXING:
		return "EMONEY_STAMPXING";
	case EMONEY_STAMPYUE:
		return "EMONEY_STAMPYUE";
	case EMONEY_STAMPDI2:
		return "EMONEY_STAMPDI2";
	case EMONEY_STAMPXIAN:
		return "EMONEY_STAMPXIAN";
	case EMONEY_STAMPSHENG:
		return "EMONEY_STAMPSHENG";
	case EMONEY_STAMPFO:
		return "EMONEY_STAMPFO";
	case EMONEY_LOVEHEART:
		return "EMONEY_LOVEHEART";
	case EMONEY_BLUEFAIRYFATE:
		return "EMONEY_BLUEFAIRYFATE";
	case EMONEY_PURPLEFAIRYFATE:
		return "EMONEY_PURPLEFAIRYFATE";
	case EMONEY_ORANGEFAIRYFATE:
		return "EMONEY_ORANGEFAIRYFATE";
	case EMONEY_DUJIEFU:
		return "EMONEY_DUJIEFU";
	case EMONEY_LUCKYCOUPON:
		return "EMONEY_LUCKYCOUPON";
	case EMONEY_END:
		return "EMONEY_END";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMoneyType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMoneyType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EMONEY_NONE", EMONEY_NONE));
		mapStr2Val.insert(make_pair("EMONEY_GOLD", EMONEY_GOLD));
		mapStr2Val.insert(make_pair("EMONEY_SILVER", EMONEY_SILVER));
		mapStr2Val.insert(make_pair("EMONEY_COUPON", EMONEY_COUPON));
		mapStr2Val.insert(make_pair("EMONEY_GIFTCOIN", EMONEY_GIFTCOIN));
		mapStr2Val.insert(make_pair("EMONEY_EXP", EMONEY_EXP));
		mapStr2Val.insert(make_pair("EMONEY_PRESTIGE", EMONEY_PRESTIGE));
		mapStr2Val.insert(make_pair("EMONEY_SOUL", EMONEY_SOUL));
		mapStr2Val.insert(make_pair("EMONEY_HONOR", EMONEY_HONOR));
		mapStr2Val.insert(make_pair("EMONEY_PEXP", EMONEY_PEXP));
		mapStr2Val.insert(make_pair("EMONEY_SIGIL", EMONEY_SIGIL));
		mapStr2Val.insert(make_pair("EMONEY_CENTSY", EMONEY_CENTSY));
		mapStr2Val.insert(make_pair("EMONEY_ACTION", EMONEY_ACTION));
		mapStr2Val.insert(make_pair("EMONEY_SOP", EMONEY_SOP));
		mapStr2Val.insert(make_pair("EMONEY_TAOISM", EMONEY_TAOISM));
		mapStr2Val.insert(make_pair("EMONEY_POTEN", EMONEY_POTEN));
		mapStr2Val.insert(make_pair("EMONEY_REIKI", EMONEY_REIKI));
		mapStr2Val.insert(make_pair("EMONEY_HFP", EMONEY_HFP));
		mapStr2Val.insert(make_pair("EMONEY_DEMONSOUL", EMONEY_DEMONSOUL));
		mapStr2Val.insert(make_pair("EMONEY_SOULATTACK", EMONEY_SOULATTACK));
		mapStr2Val.insert(make_pair("EMONEY_SOULHP", EMONEY_SOULHP));
		mapStr2Val.insert(make_pair("EMONEY_SOULCRITICAL", EMONEY_SOULCRITICAL));
		mapStr2Val.insert(make_pair("EMONEY_SOULCOUNTER", EMONEY_SOULCOUNTER));
		mapStr2Val.insert(make_pair("EMONEY_SOULSPEED", EMONEY_SOULSPEED));
		mapStr2Val.insert(make_pair("EMONEY_SOULDEFENCE", EMONEY_SOULDEFENCE));
		mapStr2Val.insert(make_pair("EMONEY_SOULHIT", EMONEY_SOULHIT));
		mapStr2Val.insert(make_pair("EMONEY_SOULDODGE", EMONEY_SOULDODGE));
		mapStr2Val.insert(make_pair("EMONEY_ACHIEVEMENTAP", EMONEY_ACHIEVEMENTAP));
		mapStr2Val.insert(make_pair("EMONEY_COLLECTAP", EMONEY_COLLECTAP));
		mapStr2Val.insert(make_pair("EMONEY_GUILDCONTRIB", EMONEY_GUILDCONTRIB));
		mapStr2Val.insert(make_pair("EMONEY_STAMPHUANG", EMONEY_STAMPHUANG));
		mapStr2Val.insert(make_pair("EMONEY_STAMPXUAN", EMONEY_STAMPXUAN));
		mapStr2Val.insert(make_pair("EMONEY_STAMPDI", EMONEY_STAMPDI));
		mapStr2Val.insert(make_pair("EMONEY_STAMPTIAN", EMONEY_STAMPTIAN));
		mapStr2Val.insert(make_pair("EMONEY_STAMPXING", EMONEY_STAMPXING));
		mapStr2Val.insert(make_pair("EMONEY_STAMPYUE", EMONEY_STAMPYUE));
		mapStr2Val.insert(make_pair("EMONEY_STAMPDI2", EMONEY_STAMPDI2));
		mapStr2Val.insert(make_pair("EMONEY_STAMPXIAN", EMONEY_STAMPXIAN));
		mapStr2Val.insert(make_pair("EMONEY_STAMPSHENG", EMONEY_STAMPSHENG));
		mapStr2Val.insert(make_pair("EMONEY_STAMPFO", EMONEY_STAMPFO));
		mapStr2Val.insert(make_pair("EMONEY_LOVEHEART", EMONEY_LOVEHEART));
		mapStr2Val.insert(make_pair("EMONEY_BLUEFAIRYFATE", EMONEY_BLUEFAIRYFATE));
		mapStr2Val.insert(make_pair("EMONEY_PURPLEFAIRYFATE", EMONEY_PURPLEFAIRYFATE));
		mapStr2Val.insert(make_pair("EMONEY_ORANGEFAIRYFATE", EMONEY_ORANGEFAIRYFATE));
		mapStr2Val.insert(make_pair("EMONEY_DUJIEFU", EMONEY_DUJIEFU));
		mapStr2Val.insert(make_pair("EMONEY_LUCKYCOUPON", EMONEY_LUCKYCOUPON));
		mapStr2Val.insert(make_pair("EMONEY_END", EMONEY_END));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

const char* GetDescription(EMoneyType e)
{
	switch(e)
	{
	case EMONEY_NONE:
		return "无类型表示不消耗";
	case EMONEY_GOLD:
		return "仙石";
	case EMONEY_SILVER:
		return "银币";
	case EMONEY_COUPON:
		return "礼券";
	case EMONEY_GIFTCOIN:
		return "金券";
	case EMONEY_EXP:
		return "经验";
	case EMONEY_PRESTIGE:
		return "声望";
	case EMONEY_SOUL:
		return "魂魄";
	case EMONEY_HONOR:
		return "荣誉";
	case EMONEY_PEXP:
		return "修为";
	case EMONEY_SIGIL:
		return "符印";
	case EMONEY_CENTSY:
		return "仙元";
	case EMONEY_ACTION:
		return "体力";
	case EMONEY_SOP:
		return "阅历";
	case EMONEY_TAOISM:
		return "道术";
	case EMONEY_POTEN:
		return "渡劫点数";
	case EMONEY_REIKI:
		return "副本星级";
	case EMONEY_HFP:
		return "寻仙积分";
	case EMONEY_DEMONSOUL:
		return "封印点";
	case EMONEY_SOULATTACK:
		return "攻击之魂";
	case EMONEY_SOULHP:
		return "生命之魂";
	case EMONEY_SOULCRITICAL:
		return "暴击之魂";
	case EMONEY_SOULCOUNTER:
		return "反击之魂";
	case EMONEY_SOULSPEED:
		return "身法之魂";
	case EMONEY_SOULDEFENCE:
		return "防御之魂";
	case EMONEY_SOULHIT:
		return "命中之魂";
	case EMONEY_SOULDODGE:
		return "闪避之魂";
	case EMONEY_ACHIEVEMENTAP:
		return "成就点";
	case EMONEY_COLLECTAP:
		return "收藏点";
	case EMONEY_GUILDCONTRIB:
		return "帮派贡献";
	case EMONEY_STAMPHUANG:
		return "橙阶除魔印";
	case EMONEY_STAMPXUAN:
		return "蓝阶除魔印";
	case EMONEY_STAMPDI:
		return "绿阶除魔印";
	case EMONEY_STAMPTIAN:
		return "紫阶除魔印";
	case EMONEY_STAMPXING:
		return "星阶除魔印";
	case EMONEY_STAMPYUE:
		return "月阶除魔印";
	case EMONEY_STAMPDI2:
		return "帝阶除魔印";
	case EMONEY_STAMPXIAN:
		return "仙阶除魔印";
	case EMONEY_STAMPSHENG:
		return "圣阶除魔印";
	case EMONEY_STAMPFO:
		return "佛阶除魔印";
	case EMONEY_LOVEHEART:
		return "爱心";
	case EMONEY_BLUEFAIRYFATE:
		return "蓝色仙缘";
	case EMONEY_PURPLEFAIRYFATE:
		return "紫色仙缘";
	case EMONEY_ORANGEFAIRYFATE:
		return "橙色仙缘";
	case EMONEY_DUJIEFU:
		return "渡劫符";
	case EMONEY_LUCKYCOUPON:
		return "抽奖券";
	case EMONEY_END:
		return "货币类型上限标志";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EFighterAttr e)
{
	switch(e)
	{
	case EFIGHTATTR_MIN:
		return "EFIGHTATTR_MIN";
	case EFIGHTATTR_PHYATK:
		return "EFIGHTATTR_PHYATK";
	case EFIGHTATTR_MGCATK:
		return "EFIGHTATTR_MGCATK";
	case EFIGHTATTR_PHYDEF:
		return "EFIGHTATTR_PHYDEF";
	case EFIGHTATTR_MGCDEF:
		return "EFIGHTATTR_MGCDEF";
	case EFIGHTATTR_PHYRDC:
		return "EFIGHTATTR_PHYRDC";
	case EFIGHTATTR_MGCRDC:
		return "EFIGHTATTR_MGCRDC";
	case EFIGHTATTR_MAXHP:
		return "EFIGHTATTR_MAXHP";
	case EFIGHTATTR_SPEED:
		return "EFIGHTATTR_SPEED";
	case EFIGHTATTR_HIT:
		return "EFIGHTATTR_HIT";
	case EFIGHTATTR_HITRATE:
		return "EFIGHTATTR_HITRATE";
	case EFIGHTATTR_DODGE:
		return "EFIGHTATTR_DODGE";
	case EFIGHTATTR_DODGERATE:
		return "EFIGHTATTR_DODGERATE";
	case EFIGHTATTR_CRITICAL:
		return "EFIGHTATTR_CRITICAL";
	case EFIGHTATTR_CRTRATE:
		return "EFIGHTATTR_CRTRATE";
	case EFIGHTATTR_ANTICRITCAL:
		return "EFIGHTATTR_ANTICRITCAL";
	case EFIGHTATTR_ANTICRTRATE:
		return "EFIGHTATTR_ANTICRTRATE";
	case EFIGHTATTR_BLOCK:
		return "EFIGHTATTR_BLOCK";
	case EFIGHTATTR_BLOCKRATE:
		return "EFIGHTATTR_BLOCKRATE";
	case EFIGHTATTR_PIERCE:
		return "EFIGHTATTR_PIERCE";
	case EFIGHTATTR_PIERCERATE:
		return "EFIGHTATTR_PIERCERATE";
	case EFIGHTATTR_COUNTER:
		return "EFIGHTATTR_COUNTER";
	case EFIGHTATTR_COUNTERRATE:
		return "EFIGHTATTR_COUNTERRATE";
	case EFIGHTATTR_RESIST:
		return "EFIGHTATTR_RESIST";
	case EFIGHTATTR_RESISTRATE:
		return "EFIGHTATTR_RESISTRATE";
	case EFIGHTATTR_INITAURA:
		return "EFIGHTATTR_INITAURA";
	case EFIGHTATTR_MAXAURA:
		return "EFIGHTATTR_MAXAURA";
	case EFIGHTATTR_CRIEXTRAADD:
		return "EFIGHTATTR_CRIEXTRAADD";
	case EFIGHTATTR_CRIEXTRARDC:
		return "EFIGHTATTR_CRIEXTRARDC";
	case EFIGHTATTR_METALATK:
		return "EFIGHTATTR_METALATK";
	case EFIGHTATTR_WOODATK:
		return "EFIGHTATTR_WOODATK";
	case EFIGHTATTR_WATERATK:
		return "EFIGHTATTR_WATERATK";
	case EFIGHTATTR_FIREATK:
		return "EFIGHTATTR_FIREATK";
	case EFIGHTATTR_EARTHATK:
		return "EFIGHTATTR_EARTHATK";
	case EFIGHTATTR_METALDEF:
		return "EFIGHTATTR_METALDEF";
	case EFIGHTATTR_WOODDEF:
		return "EFIGHTATTR_WOODDEF";
	case EFIGHTATTR_WATERDEF:
		return "EFIGHTATTR_WATERDEF";
	case EFIGHTATTR_FIREDEF:
		return "EFIGHTATTR_FIREDEF";
	case EFIGHTATTR_EARTHDEF:
		return "EFIGHTATTR_EARTHDEF";
	case EFIGHTATTR_PHYATK_PER:
		return "EFIGHTATTR_PHYATK_PER";
	case EFIGHTATTR_MGCATK_PER:
		return "EFIGHTATTR_MGCATK_PER";
	case EFIGHTATTR_PHYDEF_PER:
		return "EFIGHTATTR_PHYDEF_PER";
	case EFIGHTATTR_MGCDEF_PER:
		return "EFIGHTATTR_MGCDEF_PER";
	case EFIGHTATTR_MAXHP_PER:
		return "EFIGHTATTR_MAXHP_PER";
	case EFIGHTATTR_SPEED_PER:
		return "EFIGHTATTR_SPEED_PER";
	case EFIGHTATTR_HIT_PER:
		return "EFIGHTATTR_HIT_PER";
	case EFIGHTATTR_DODGE_PER:
		return "EFIGHTATTR_DODGE_PER";
	case EFIGHTATTR_CRITICAL_PER:
		return "EFIGHTATTR_CRITICAL_PER";
	case EFIGHTATTR_ANTICRITCAL_PER:
		return "EFIGHTATTR_ANTICRITCAL_PER";
	case EFIGHTATTR_BLOCK_PER:
		return "EFIGHTATTR_BLOCK_PER";
	case EFIGHTATTR_PIERCE_PER:
		return "EFIGHTATTR_PIERCE_PER";
	case EFIGHTATTR_COUNTER_PER:
		return "EFIGHTATTR_COUNTER_PER";
	case EFIGHTATTR_RESIST_PER:
		return "EFIGHTATTR_RESIST_PER";
	case EFIGHTATTR_ANTIEFFECT:
		return "EFIGHTATTR_ANTIEFFECT";
	case EFIGHTATTR_COUTEREXTRAADD:
		return "EFIGHTATTR_COUTEREXTRAADD";
	case EFIGHTATTR_COUTEREXTRARDC:
		return "EFIGHTATTR_COUTEREXTRARDC";
	case EFIGHTATTR_MAX:
		return "EFIGHTATTR_MAX";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EFighterAttr& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EFighterAttr> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EFIGHTATTR_MIN", EFIGHTATTR_MIN));
		mapStr2Val.insert(make_pair("EFIGHTATTR_PHYATK", EFIGHTATTR_PHYATK));
		mapStr2Val.insert(make_pair("EFIGHTATTR_MGCATK", EFIGHTATTR_MGCATK));
		mapStr2Val.insert(make_pair("EFIGHTATTR_PHYDEF", EFIGHTATTR_PHYDEF));
		mapStr2Val.insert(make_pair("EFIGHTATTR_MGCDEF", EFIGHTATTR_MGCDEF));
		mapStr2Val.insert(make_pair("EFIGHTATTR_PHYRDC", EFIGHTATTR_PHYRDC));
		mapStr2Val.insert(make_pair("EFIGHTATTR_MGCRDC", EFIGHTATTR_MGCRDC));
		mapStr2Val.insert(make_pair("EFIGHTATTR_MAXHP", EFIGHTATTR_MAXHP));
		mapStr2Val.insert(make_pair("EFIGHTATTR_SPEED", EFIGHTATTR_SPEED));
		mapStr2Val.insert(make_pair("EFIGHTATTR_HIT", EFIGHTATTR_HIT));
		mapStr2Val.insert(make_pair("EFIGHTATTR_HITRATE", EFIGHTATTR_HITRATE));
		mapStr2Val.insert(make_pair("EFIGHTATTR_DODGE", EFIGHTATTR_DODGE));
		mapStr2Val.insert(make_pair("EFIGHTATTR_DODGERATE", EFIGHTATTR_DODGERATE));
		mapStr2Val.insert(make_pair("EFIGHTATTR_CRITICAL", EFIGHTATTR_CRITICAL));
		mapStr2Val.insert(make_pair("EFIGHTATTR_CRTRATE", EFIGHTATTR_CRTRATE));
		mapStr2Val.insert(make_pair("EFIGHTATTR_ANTICRITCAL", EFIGHTATTR_ANTICRITCAL));
		mapStr2Val.insert(make_pair("EFIGHTATTR_ANTICRTRATE", EFIGHTATTR_ANTICRTRATE));
		mapStr2Val.insert(make_pair("EFIGHTATTR_BLOCK", EFIGHTATTR_BLOCK));
		mapStr2Val.insert(make_pair("EFIGHTATTR_BLOCKRATE", EFIGHTATTR_BLOCKRATE));
		mapStr2Val.insert(make_pair("EFIGHTATTR_PIERCE", EFIGHTATTR_PIERCE));
		mapStr2Val.insert(make_pair("EFIGHTATTR_PIERCERATE", EFIGHTATTR_PIERCERATE));
		mapStr2Val.insert(make_pair("EFIGHTATTR_COUNTER", EFIGHTATTR_COUNTER));
		mapStr2Val.insert(make_pair("EFIGHTATTR_COUNTERRATE", EFIGHTATTR_COUNTERRATE));
		mapStr2Val.insert(make_pair("EFIGHTATTR_RESIST", EFIGHTATTR_RESIST));
		mapStr2Val.insert(make_pair("EFIGHTATTR_RESISTRATE", EFIGHTATTR_RESISTRATE));
		mapStr2Val.insert(make_pair("EFIGHTATTR_INITAURA", EFIGHTATTR_INITAURA));
		mapStr2Val.insert(make_pair("EFIGHTATTR_MAXAURA", EFIGHTATTR_MAXAURA));
		mapStr2Val.insert(make_pair("EFIGHTATTR_CRIEXTRAADD", EFIGHTATTR_CRIEXTRAADD));
		mapStr2Val.insert(make_pair("EFIGHTATTR_CRIEXTRARDC", EFIGHTATTR_CRIEXTRARDC));
		mapStr2Val.insert(make_pair("EFIGHTATTR_METALATK", EFIGHTATTR_METALATK));
		mapStr2Val.insert(make_pair("EFIGHTATTR_WOODATK", EFIGHTATTR_WOODATK));
		mapStr2Val.insert(make_pair("EFIGHTATTR_WATERATK", EFIGHTATTR_WATERATK));
		mapStr2Val.insert(make_pair("EFIGHTATTR_FIREATK", EFIGHTATTR_FIREATK));
		mapStr2Val.insert(make_pair("EFIGHTATTR_EARTHATK", EFIGHTATTR_EARTHATK));
		mapStr2Val.insert(make_pair("EFIGHTATTR_METALDEF", EFIGHTATTR_METALDEF));
		mapStr2Val.insert(make_pair("EFIGHTATTR_WOODDEF", EFIGHTATTR_WOODDEF));
		mapStr2Val.insert(make_pair("EFIGHTATTR_WATERDEF", EFIGHTATTR_WATERDEF));
		mapStr2Val.insert(make_pair("EFIGHTATTR_FIREDEF", EFIGHTATTR_FIREDEF));
		mapStr2Val.insert(make_pair("EFIGHTATTR_EARTHDEF", EFIGHTATTR_EARTHDEF));
		mapStr2Val.insert(make_pair("EFIGHTATTR_PHYATK_PER", EFIGHTATTR_PHYATK_PER));
		mapStr2Val.insert(make_pair("EFIGHTATTR_MGCATK_PER", EFIGHTATTR_MGCATK_PER));
		mapStr2Val.insert(make_pair("EFIGHTATTR_PHYDEF_PER", EFIGHTATTR_PHYDEF_PER));
		mapStr2Val.insert(make_pair("EFIGHTATTR_MGCDEF_PER", EFIGHTATTR_MGCDEF_PER));
		mapStr2Val.insert(make_pair("EFIGHTATTR_MAXHP_PER", EFIGHTATTR_MAXHP_PER));
		mapStr2Val.insert(make_pair("EFIGHTATTR_SPEED_PER", EFIGHTATTR_SPEED_PER));
		mapStr2Val.insert(make_pair("EFIGHTATTR_HIT_PER", EFIGHTATTR_HIT_PER));
		mapStr2Val.insert(make_pair("EFIGHTATTR_DODGE_PER", EFIGHTATTR_DODGE_PER));
		mapStr2Val.insert(make_pair("EFIGHTATTR_CRITICAL_PER", EFIGHTATTR_CRITICAL_PER));
		mapStr2Val.insert(make_pair("EFIGHTATTR_ANTICRITCAL_PER", EFIGHTATTR_ANTICRITCAL_PER));
		mapStr2Val.insert(make_pair("EFIGHTATTR_BLOCK_PER", EFIGHTATTR_BLOCK_PER));
		mapStr2Val.insert(make_pair("EFIGHTATTR_PIERCE_PER", EFIGHTATTR_PIERCE_PER));
		mapStr2Val.insert(make_pair("EFIGHTATTR_COUNTER_PER", EFIGHTATTR_COUNTER_PER));
		mapStr2Val.insert(make_pair("EFIGHTATTR_RESIST_PER", EFIGHTATTR_RESIST_PER));
		mapStr2Val.insert(make_pair("EFIGHTATTR_ANTIEFFECT", EFIGHTATTR_ANTIEFFECT));
		mapStr2Val.insert(make_pair("EFIGHTATTR_COUTEREXTRAADD", EFIGHTATTR_COUTEREXTRAADD));
		mapStr2Val.insert(make_pair("EFIGHTATTR_COUTEREXTRARDC", EFIGHTATTR_COUTEREXTRARDC));
		mapStr2Val.insert(make_pair("EFIGHTATTR_MAX", EFIGHTATTR_MAX));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

#ifdef PROT_USE_XML

const char* EnumValToStr(EAttrGroupType e)
{
	switch(e)
	{
	case eAttrGpMin:
		return "eAttrGpMin";
	case eAttrGpPlayerBegin:
		return "eAttrGpPlayerBegin";
	case eAttrGpFashion:
		return "eAttrGpFashion";
	case eAttrGpTitle:
		return "eAttrGpTitle";
	case eAttrGpCitta:
		return "eAttrGpCitta";
	case eAttrGpPlayerEnd:
		return "eAttrGpPlayerEnd";
	case eAttrGpHeroBegin:
		return "eAttrGpHeroBegin";
	case eAttrGpEquipTrump:
		return "eAttrGpEquipTrump";
	case eAttrGpGemstone:
		return "eAttrGpGemstone";
	case eAttrGpHeroEnd:
		return "eAttrGpHeroEnd";
	case eAttrGpHeroAndPlayerBegin:
		return "eAttrGpHeroAndPlayerBegin";
	case eAttrGpTrumpActive:
		return "eAttrGpTrumpActive";
	case eAttrGpTrumpExtra:
		return "eAttrGpTrumpExtra";
	case eAttrGpTrumpHalo:
		return "eAttrGpTrumpHalo";
	case eAttrGpHorse:
		return "eAttrGpHorse";
	case eAttrGpShushanBattle:
		return "eAttrGpShushanBattle";
	case eAttrGpBag:
		return "eAttrGpBag";
	case eAttrGpAchievement:
		return "eAttrGpAchievement";
	case eAttrGpCollection:
		return "eAttrGpCollection";
	case eAttrGpFormation:
		return "eAttrGpFormation";
	case eAttrGpPet:
		return "eAttrGpPet";
	case eAttrGpBeastSoul:
		return "eAttrGpBeastSoul";
	case eAttrGpGuildTech:
		return "eAttrGpGuildTech";
	case eAttrGpBuffer:
		return "eAttrGpBuffer";
	case eAttrGpTripod:
		return "eAttrGpTripod";
	case eAttrGpFighterCombination:
		return "eAttrGpFighterCombination";
	case eAttrBeauty:
		return "eAttrBeauty";
	case eAttrGpHeroAndPlayerEnd:
		return "eAttrGpHeroAndPlayerEnd";
	case eAttrGpMax:
		return "eAttrGpMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EAttrGroupType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EAttrGroupType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eAttrGpMin", eAttrGpMin));
		mapStr2Val.insert(make_pair("eAttrGpPlayerBegin", eAttrGpPlayerBegin));
		mapStr2Val.insert(make_pair("eAttrGpFashion", eAttrGpFashion));
		mapStr2Val.insert(make_pair("eAttrGpTitle", eAttrGpTitle));
		mapStr2Val.insert(make_pair("eAttrGpCitta", eAttrGpCitta));
		mapStr2Val.insert(make_pair("eAttrGpPlayerEnd", eAttrGpPlayerEnd));
		mapStr2Val.insert(make_pair("eAttrGpHeroBegin", eAttrGpHeroBegin));
		mapStr2Val.insert(make_pair("eAttrGpEquipTrump", eAttrGpEquipTrump));
		mapStr2Val.insert(make_pair("eAttrGpGemstone", eAttrGpGemstone));
		mapStr2Val.insert(make_pair("eAttrGpHeroEnd", eAttrGpHeroEnd));
		mapStr2Val.insert(make_pair("eAttrGpHeroAndPlayerBegin", eAttrGpHeroAndPlayerBegin));
		mapStr2Val.insert(make_pair("eAttrGpTrumpActive", eAttrGpTrumpActive));
		mapStr2Val.insert(make_pair("eAttrGpTrumpExtra", eAttrGpTrumpExtra));
		mapStr2Val.insert(make_pair("eAttrGpTrumpHalo", eAttrGpTrumpHalo));
		mapStr2Val.insert(make_pair("eAttrGpHorse", eAttrGpHorse));
		mapStr2Val.insert(make_pair("eAttrGpShushanBattle", eAttrGpShushanBattle));
		mapStr2Val.insert(make_pair("eAttrGpBag", eAttrGpBag));
		mapStr2Val.insert(make_pair("eAttrGpAchievement", eAttrGpAchievement));
		mapStr2Val.insert(make_pair("eAttrGpCollection", eAttrGpCollection));
		mapStr2Val.insert(make_pair("eAttrGpFormation", eAttrGpFormation));
		mapStr2Val.insert(make_pair("eAttrGpPet", eAttrGpPet));
		mapStr2Val.insert(make_pair("eAttrGpBeastSoul", eAttrGpBeastSoul));
		mapStr2Val.insert(make_pair("eAttrGpGuildTech", eAttrGpGuildTech));
		mapStr2Val.insert(make_pair("eAttrGpBuffer", eAttrGpBuffer));
		mapStr2Val.insert(make_pair("eAttrGpTripod", eAttrGpTripod));
		mapStr2Val.insert(make_pair("eAttrGpFighterCombination", eAttrGpFighterCombination));
		mapStr2Val.insert(make_pair("eAttrBeauty", eAttrBeauty));
		mapStr2Val.insert(make_pair("eAttrGpHeroAndPlayerEnd", eAttrGpHeroAndPlayerEnd));
		mapStr2Val.insert(make_pair("eAttrGpMax", eAttrGpMax));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

#ifdef PROT_USE_XML

const char* EnumValToStr(AWARDTYPE e)
{
	switch(e)
	{
	case AWARDTYPE_TITLE:
		return "AWARDTYPE_TITLE";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, AWARDTYPE& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, AWARDTYPE> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("AWARDTYPE_TITLE", AWARDTYPE_TITLE));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

const char* GetDescription(AWARDTYPE e)
{
	switch(e)
	{
	case AWARDTYPE_TITLE:
		return "称号";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EBuffType e)
{
	switch(e)
	{
	case eBTNone:
		return "eBTNone";
	case eBTUser:
		return "eBTUser";
	case eBTPlayer:
		return "eBTPlayer";
	case eBTMainFighter:
		return "eBTMainFighter";
	case eBTFighter:
		return "eBTFighter";
	case eBTMonster:
		return "eBTMonster";
	case eBTNPC:
		return "eBTNPC";
	case eBTMax:
		return "eBTMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBuffType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBuffType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBTNone", eBTNone));
		mapStr2Val.insert(make_pair("eBTUser", eBTUser));
		mapStr2Val.insert(make_pair("eBTPlayer", eBTPlayer));
		mapStr2Val.insert(make_pair("eBTMainFighter", eBTMainFighter));
		mapStr2Val.insert(make_pair("eBTFighter", eBTFighter));
		mapStr2Val.insert(make_pair("eBTMonster", eBTMonster));
		mapStr2Val.insert(make_pair("eBTNPC", eBTNPC));
		mapStr2Val.insert(make_pair("eBTMax", eBTMax));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

const char* GetDescription(EBuffType e)
{
	switch(e)
	{
	case eBTNone:
		return "无效Buff大类";
	case eBTUser:
		return "帐号相关Buff类型";
	case eBTPlayer:
		return "玩家自带Buff类型";
	case eBTMainFighter:
		return "主将相关Buff类型";
	case eBTFighter:
		return "散仙相关Buff类型";
	case eBTMonster:
		return "怪物相关Buff类型";
	case eBTNPC:
		return "NPC相关Buff类型";
	case eBTMax:
		return "Buff大类最大值";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EBuffEffectType e)
{
	switch(e)
	{
	case eBETNone:
		return "eBETNone";
	case eBETAttr:
		return "eBETAttr";
	case eBETTimeCount:
		return "eBETTimeCount";
	case eBETCount:
		return "eBETCount";
	case eBETMax:
		return "eBETMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBuffEffectType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBuffEffectType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBETNone", eBETNone));
		mapStr2Val.insert(make_pair("eBETAttr", eBETAttr));
		mapStr2Val.insert(make_pair("eBETTimeCount", eBETTimeCount));
		mapStr2Val.insert(make_pair("eBETCount", eBETCount));
		mapStr2Val.insert(make_pair("eBETMax", eBETMax));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

const char* GetDescription(EBuffEffectType e)
{
	switch(e)
	{
	case eBETNone:
		return "无效Buff效果类型";
	case eBETAttr:
		return "Buff属性加成";
	case eBETTimeCount:
		return "Buff持续时间同时持续次数";
	case eBETCount:
		return "Buff仅持续时间";
	case eBETMax:
		return "Buff效果最大值";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EBuffState e)
{
	switch(e)
	{
	case eBSNone:
		return "eBSNone";
	case eBSActived:
		return "eBSActived";
	case eBSPaused:
		return "eBSPaused";
	case eBSOverdue:
		return "eBSOverdue";
	case eBSMax:
		return "eBSMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBuffState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBuffState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBSNone", eBSNone));
		mapStr2Val.insert(make_pair("eBSActived", eBSActived));
		mapStr2Val.insert(make_pair("eBSPaused", eBSPaused));
		mapStr2Val.insert(make_pair("eBSOverdue", eBSOverdue));
		mapStr2Val.insert(make_pair("eBSMax", eBSMax));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

const char* GetDescription(EBuffState e)
{
	switch(e)
	{
	case eBSNone:
		return "无效Buff状态";
	case eBSActived:
		return "Buff生效";
	case eBSPaused:
		return "Buff暂停";
	case eBSOverdue:
		return "Buff过期";
	case eBSMax:
		return "Buff状态最大值";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EBuffOpResult e)
{
	switch(e)
	{
	case eBORSuccess:
		return "eBORSuccess";
	case eBORFailed:
		return "eBORFailed";
	case eBORExisted:
		return "eBORExisted";
	case eBORNotExisted:
		return "eBORNotExisted";
	case eBOROverdue:
		return "eBOROverdue";
	case eBORPaused:
		return "eBORPaused";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBuffOpResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBuffOpResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBORSuccess", eBORSuccess));
		mapStr2Val.insert(make_pair("eBORFailed", eBORFailed));
		mapStr2Val.insert(make_pair("eBORExisted", eBORExisted));
		mapStr2Val.insert(make_pair("eBORNotExisted", eBORNotExisted));
		mapStr2Val.insert(make_pair("eBOROverdue", eBOROverdue));
		mapStr2Val.insert(make_pair("eBORPaused", eBORPaused));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

const char* GetDescription(EBuffOpResult e)
{
	switch(e)
	{
	case eBORSuccess:
		return "操作成功";
	case eBORFailed:
		return "操作失败";
	case eBORExisted:
		return "存在相同Buff";
	case eBORNotExisted:
		return "不存在该Buff";
	case eBOROverdue:
		return "已经过期的Buff";
	case eBORPaused:
		return "已经暂停的Buff";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EAttacked e)
{
	switch(e)
	{
	case eAttacked_None:
		return "eAttacked_None";
	case eAttacked_Demontower:
		return "eAttacked_Demontower";
	case eAttacked_Max:
		return "eAttacked_Max";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EAttacked& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EAttacked> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eAttacked_None", eAttacked_None));
		mapStr2Val.insert(make_pair("eAttacked_Demontower", eAttacked_Demontower));
		mapStr2Val.insert(make_pair("eAttacked_Max", eAttacked_Max));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

const char* GetDescription(EAttacked e)
{
	switch(e)
	{
	case eAttacked_None:
		return "无";
	case eAttacked_Demontower:
		return "锁妖塔";
	case eAttacked_Max:
		return "类型上限";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EQQPtType e)
{
	switch(e)
	{
	case eQQPtTypeNone:
		return "eQQPtTypeNone";
	case eQQPtTypeYellow:
		return "eQQPtTypeYellow";
	case eQQPtTypeBlue:
		return "eQQPtTypeBlue";
	case eQQPtTypeRed:
		return "eQQPtTypeRed";
	case eQQPtTypeMax:
		return "eQQPtTypeMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EQQPtType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EQQPtType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eQQPtTypeNone", eQQPtTypeNone));
		mapStr2Val.insert(make_pair("eQQPtTypeYellow", eQQPtTypeYellow));
		mapStr2Val.insert(make_pair("eQQPtTypeBlue", eQQPtTypeBlue));
		mapStr2Val.insert(make_pair("eQQPtTypeRed", eQQPtTypeRed));
		mapStr2Val.insert(make_pair("eQQPtTypeMax", eQQPtTypeMax));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

const char* GetDescription(EQQPtType e)
{
	switch(e)
	{
	case eQQPtTypeNone:
		return "无";
	case eQQPtTypeYellow:
		return "黄钻平台";
	case eQQPtTypeBlue:
		return "蓝钻平台";
	case eQQPtTypeRed:
		return "红钻/VIP平台";
	case eQQPtTypeMax:
		return "最大值";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EPtType e)
{
	switch(e)
	{
	case ePtTypeNone:
		return "ePtTypeNone";
	case ePtTypeQQYellow:
		return "ePtTypeQQYellow";
	case ePtTypeQQPengyou:
		return "ePtTypeQQPengyou";
	case ePtTypeQQWeibo:
		return "ePtTypeQQWeibo";
	case ePtTypeQQPlus:
		return "ePtTypeQQPlus";
	case ePtTypeQQGame:
		return "ePtTypeQQGame";
	case ePtTypeQQ3366:
		return "ePtTypeQQ3366";
	case ePtTypeQQKingxin:
		return "ePtTypeQQKingxin";
	case ePtTypeKingxin:
		return "ePtTypeKingxin";
	case ePtTypeMax:
		return "ePtTypeMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EPtType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EPtType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ePtTypeNone", ePtTypeNone));
		mapStr2Val.insert(make_pair("ePtTypeQQYellow", ePtTypeQQYellow));
		mapStr2Val.insert(make_pair("ePtTypeQQPengyou", ePtTypeQQPengyou));
		mapStr2Val.insert(make_pair("ePtTypeQQWeibo", ePtTypeQQWeibo));
		mapStr2Val.insert(make_pair("ePtTypeQQPlus", ePtTypeQQPlus));
		mapStr2Val.insert(make_pair("ePtTypeQQGame", ePtTypeQQGame));
		mapStr2Val.insert(make_pair("ePtTypeQQ3366", ePtTypeQQ3366));
		mapStr2Val.insert(make_pair("ePtTypeQQKingxin", ePtTypeQQKingxin));
		mapStr2Val.insert(make_pair("ePtTypeKingxin", ePtTypeKingxin));
		mapStr2Val.insert(make_pair("ePtTypeMax", ePtTypeMax));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

const char* GetDescription(EPtType e)
{
	switch(e)
	{
	case ePtTypeNone:
		return "无";
	case ePtTypeQQYellow:
		return "QQ黄钻平台/Qzone";
	case ePtTypeQQPengyou:
		return "QQ朋友/校友/黄钻";
	case ePtTypeQQWeibo:
		return "QQ微博平台";
	case ePtTypeQQPlus:
		return "QQ/Q+平台";
	case ePtTypeQQGame:
		return "QQ蓝钻/游戏平台";
	case ePtTypeQQ3366:
		return "QQ蓝钻/3366平台/包子";
	case ePtTypeQQKingxin:
		return "QQ官网平台/QQ会员";
	case ePtTypeKingxin:
		return "恺英官网平台";
	case ePtTypeMax:
		return "最大值";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EPlatformBitType e)
{
	switch(e)
	{
	case ePBBitSuper:
		return "ePBBitSuper";
	case ePBBitYearly:
		return "ePBBitYearly";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EPlatformBitType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EPlatformBitType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ePBBitSuper", ePBBitSuper));
		mapStr2Val.insert(make_pair("ePBBitYearly", ePBBitYearly));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

const char* GetDescription(EPlatformBitType e)
{
	switch(e)
	{
	case ePBBitSuper:
		return "豪华/超级";
	case ePBBitYearly:
		return "年费";
	default:
		return "未知错误";
	}
}

SCoinValue::SCoinValue() : eCoinType((ECoinType)0), dwValue(0) { }

SCoinValue::SCoinValue(ECoinType eCoinType_, UINT32 dwValue_) : eCoinType(eCoinType_), dwValue(dwValue_) { }

CInArchive& operator>>(CInArchive& src, SCoinValue& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eCoinType;
	src >> s.dwValue;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SCoinValue& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eCoinType;
	src << s.dwValue;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SCoinValue& s)
{
	if(strcmp(rElement.Value(), "SCoinValue") != 0)
	{
		LOG_CRI << "rElement is not SCoinValue!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eCoinType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ECoinType") != 0)
	{
		LOG_CRI << "pElemChild is not ECoinType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eCoinType") != 0)
	{
		LOG_CRI << "Attribute: name is not eCoinType!";
		return false;
	}
	const char* pszVal_eCoinType = pElemChild->Attribute("value");
	if(pszVal_eCoinType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eCoinType, s.eCoinType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwValue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwValue!";
		return false;
	}
	const char* pszVal_dwValue = pElemChild->Attribute("value");
	if(pszVal_dwValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwValue, s.dwValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SCoinValue& s, TiXmlElement& rElement)
{
	rElement.SetValue("SCoinValue");
	rElement.SetAttribute("type", ToUTF8Ptr("货币信息"));
	unique_ptr<TiXmlElement> pElem_eCoinType(new TiXmlElement("ECoinType"));
	if(pElem_eCoinType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eCoinType->SetAttribute("name", "eCoinType");
	const char* pszEnum_eCoinType = EnumValToStr(s.eCoinType);
	if(pszEnum_eCoinType == NULL)
	{
		LOG_CRI << "EnumValToStr for ECoinType fails!";
		return false;
	}
	pElem_eCoinType->SetAttribute("value", pszEnum_eCoinType);
	pElem_eCoinType->SetAttribute("comment", ToUTF8Ptr("货币类型"));
	if(rElement.LinkEndChild(pElem_eCoinType.get()) != NULL)
		pElem_eCoinType.release();
	unique_ptr<TiXmlElement> pElem_dwValue(new TiXmlElement("UINT32"));
	if(pElem_dwValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwValue->SetAttribute("name", "dwValue");
	pElem_dwValue->SetAttribute("value", NumberToString(s.dwValue).c_str());
	pElem_dwValue->SetAttribute("comment", ToUTF8Ptr("值"));
	if(rElement.LinkEndChild(pElem_dwValue.get()) != NULL)
		pElem_dwValue.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecCoinValue& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SCoinValue s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecCoinValue& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SCoinValue"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SFtAttrMod::SFtAttrMod() : _eAttr((EFighterAttr)0), _fValue(0) { }

SFtAttrMod::SFtAttrMod(EFighterAttr _eAttr_, float _fValue_) : _eAttr(_eAttr_), _fValue(_fValue_) { }

CInArchive& operator>>(CInArchive& src, SFtAttrMod& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s._eAttr;
	src >> s._fValue;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFtAttrMod& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s._eAttr;
	src << s._fValue;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFtAttrMod& s)
{
	if(strcmp(rElement.Value(), "SFtAttrMod") != 0)
	{
		LOG_CRI << "rElement is not SFtAttrMod!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for _eAttr is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EFighterAttr") != 0)
	{
		LOG_CRI << "pElemChild is not EFighterAttr!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "_eAttr") != 0)
	{
		LOG_CRI << "Attribute: name is not _eAttr!";
		return false;
	}
	const char* pszVal__eAttr = pElemChild->Attribute("value");
	if(pszVal__eAttr == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal__eAttr, s._eAttr))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for _fValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "_fValue") != 0)
	{
		LOG_CRI << "Attribute: name is not _fValue!";
		return false;
	}
	const char* pszVal__fValue = pElemChild->Attribute("value");
	if(pszVal__fValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal__fValue, s._fValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFtAttrMod& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFtAttrMod");
	rElement.SetAttribute("type", ToUTF8Ptr("属性变化结构"));
	unique_ptr<TiXmlElement> pElem__eAttr(new TiXmlElement("EFighterAttr"));
	if(pElem__eAttr == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem__eAttr->SetAttribute("name", "_eAttr");
	const char* pszEnum__eAttr = EnumValToStr(s._eAttr);
	if(pszEnum__eAttr == NULL)
	{
		LOG_CRI << "EnumValToStr for EFighterAttr fails!";
		return false;
	}
	pElem__eAttr->SetAttribute("value", pszEnum__eAttr);
	pElem__eAttr->SetAttribute("comment", ToUTF8Ptr("属性类型"));
	if(rElement.LinkEndChild(pElem__eAttr.get()) != NULL)
		pElem__eAttr.release();
	unique_ptr<TiXmlElement> pElem__fValue(new TiXmlElement("float"));
	if(pElem__fValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem__fValue->SetAttribute("name", "_fValue");
	pElem__fValue->SetAttribute("value", NumberToString(s._fValue).c_str());
	pElem__fValue->SetAttribute("comment", ToUTF8Ptr("改变的值"));
	if(rElement.LinkEndChild(pElem__fValue.get()) != NULL)
		pElem__fValue.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFtAttrMod& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFtAttrMod s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecFtAttrMod& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFtAttrMod"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SAttrGroup::SAttrGroup() : eType((EAttrGroupType)0) { }

SAttrGroup::SAttrGroup(EAttrGroupType eType_, const TVecFtAttrMod& vecFtAttrMod_) : eType(eType_), vecFtAttrMod(vecFtAttrMod_) { }

SAttrGroup::SAttrGroup(SAttrGroup&& src) : eType(src.eType), vecFtAttrMod(move(src.vecFtAttrMod)) { }

SAttrGroup& SAttrGroup::operator=(SAttrGroup&& rhs)
{
	if(this != &rhs)
	{
		this->~SAttrGroup();
		new (this) SAttrGroup(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SAttrGroup& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eType;
	src >> s.vecFtAttrMod;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SAttrGroup& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eType;
	src << s.vecFtAttrMod;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SAttrGroup& s)
{
	if(strcmp(rElement.Value(), "SAttrGroup") != 0)
	{
		LOG_CRI << "rElement is not SAttrGroup!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EAttrGroupType") != 0)
	{
		LOG_CRI << "pElemChild is not EAttrGroupType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eType") != 0)
	{
		LOG_CRI << "Attribute: name is not eType!";
		return false;
	}
	const char* pszVal_eType = pElemChild->Attribute("value");
	if(pszVal_eType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eType, s.eType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFtAttrMod is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecFtAttrMod") != 0)
	{
		LOG_CRI << "pElemChild is not TVecFtAttrMod!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFtAttrMod") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFtAttrMod!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecFtAttrMod))
	{
		LOG_CRI << "VectorFromXML for vecFtAttrMod fails!";
		return false;
	}
	return true;
}

bool ToXML(const SAttrGroup& s, TiXmlElement& rElement)
{
	rElement.SetValue("SAttrGroup");
	rElement.SetAttribute("type", ToUTF8Ptr("属性加成"));
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("EAttrGroupType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for EAttrGroupType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("属性加成类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_vecFtAttrMod(new TiXmlElement("TVecFtAttrMod"));
	if(pElem_vecFtAttrMod == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFtAttrMod->SetAttribute("name", "vecFtAttrMod");
	if(!VectorToXML(s.vecFtAttrMod, *pElem_vecFtAttrMod))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFtAttrMod->SetAttribute("comment", ToUTF8Ptr("属性变化结构"));
	if(rElement.LinkEndChild(pElem_vecFtAttrMod.get()) != NULL)
		pElem_vecFtAttrMod.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecAttrGroup& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SAttrGroup s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecAttrGroup& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SAttrGroup"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SDBBuffInfo::SDBBuffInfo() : qwRoleID(0), qwOwnerID(0), eBuffType((EBuffType)0), wBuffID(0), eBuffEffectType((EBuffEffectType)0), 
			eBuffState((EBuffState)0), dwBuffCount(0), dwBuffTime(0), byBattleType(0) { }

CInArchive& operator>>(CInArchive& src, SDBBuffInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.qwOwnerID;
	src >> (UINT8&)s.eBuffType;
	src >> s.wBuffID;
	src >> (UINT8&)s.eBuffEffectType;
	src >> (UINT8&)s.eBuffState;
	src >> s.vecBuffParam;
	src >> s.dwBuffCount;
	src >> s.dwBuffTime;
	src >> s.vecEffectMapID;
	src >> s.byBattleType;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDBBuffInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.qwOwnerID;
	src << (UINT8&)s.eBuffType;
	src << s.wBuffID;
	src << (UINT8&)s.eBuffEffectType;
	src << (UINT8&)s.eBuffState;
	src << s.vecBuffParam;
	src << s.dwBuffCount;
	src << s.dwBuffTime;
	src << s.vecEffectMapID;
	src << s.byBattleType;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDBBuffInfo& s)
{
	if(strcmp(rElement.Value(), "SDBBuffInfo") != 0)
	{
		LOG_CRI << "rElement is not SDBBuffInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwOwnerID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwOwnerID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwOwnerID!";
		return false;
	}
	const char* pszVal_qwOwnerID = pElemChild->Attribute("value");
	if(pszVal_qwOwnerID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwOwnerID, s.qwOwnerID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eBuffType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBuffType") != 0)
	{
		LOG_CRI << "pElemChild is not EBuffType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eBuffType") != 0)
	{
		LOG_CRI << "Attribute: name is not eBuffType!";
		return false;
	}
	const char* pszVal_eBuffType = pElemChild->Attribute("value");
	if(pszVal_eBuffType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eBuffType, s.eBuffType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wBuffID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBuffID") != 0)
	{
		LOG_CRI << "Attribute: name is not wBuffID!";
		return false;
	}
	const char* pszVal_wBuffID = pElemChild->Attribute("value");
	if(pszVal_wBuffID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBuffID, s.wBuffID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eBuffEffectType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBuffEffectType") != 0)
	{
		LOG_CRI << "pElemChild is not EBuffEffectType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eBuffEffectType") != 0)
	{
		LOG_CRI << "Attribute: name is not eBuffEffectType!";
		return false;
	}
	const char* pszVal_eBuffEffectType = pElemChild->Attribute("value");
	if(pszVal_eBuffEffectType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eBuffEffectType, s.eBuffEffectType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eBuffState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBuffState") != 0)
	{
		LOG_CRI << "pElemChild is not EBuffState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eBuffState") != 0)
	{
		LOG_CRI << "Attribute: name is not eBuffState!";
		return false;
	}
	const char* pszVal_eBuffState = pElemChild->Attribute("value");
	if(pszVal_eBuffState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eBuffState, s.eBuffState))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBuffParam is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT32") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBuffParam") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBuffParam!";
		return false;
	}
	const char* pszText_vecBuffParam = pElemChild->GetText();
	if(pszText_vecBuffParam != NULL)
		SplitToNumber(pszText_vecBuffParam, ",", s.vecBuffParam);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuffCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuffCount") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuffCount!";
		return false;
	}
	const char* pszVal_dwBuffCount = pElemChild->Attribute("value");
	if(pszVal_dwBuffCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuffCount, s.dwBuffCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuffTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuffTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuffTime!";
		return false;
	}
	const char* pszVal_dwBuffTime = pElemChild->Attribute("value");
	if(pszVal_dwBuffTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuffTime, s.dwBuffTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecEffectMapID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT32") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecEffectMapID") != 0)
	{
		LOG_CRI << "Attribute: name is not vecEffectMapID!";
		return false;
	}
	const char* pszText_vecEffectMapID = pElemChild->GetText();
	if(pszText_vecEffectMapID != NULL)
		SplitToNumber(pszText_vecEffectMapID, ",", s.vecEffectMapID);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBattleType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBattleType") != 0)
	{
		LOG_CRI << "Attribute: name is not byBattleType!";
		return false;
	}
	const char* pszVal_byBattleType = pElemChild->Attribute("value");
	if(pszVal_byBattleType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBattleType, s.byBattleType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDBBuffInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDBBuffInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("Buff数据信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("对应玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_qwOwnerID(new TiXmlElement("UINT64"));
	if(pElem_qwOwnerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOwnerID->SetAttribute("name", "qwOwnerID");
	pElem_qwOwnerID->SetAttribute("value", NumberToString(s.qwOwnerID).c_str());
	pElem_qwOwnerID->SetAttribute("comment", ToUTF8Ptr("所属实例ID(Role/Fighter/..."));
	if(rElement.LinkEndChild(pElem_qwOwnerID.get()) != NULL)
		pElem_qwOwnerID.release();
	unique_ptr<TiXmlElement> pElem_eBuffType(new TiXmlElement("EBuffType"));
	if(pElem_eBuffType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eBuffType->SetAttribute("name", "eBuffType");
	const char* pszEnum_eBuffType = EnumValToStr(s.eBuffType);
	if(pszEnum_eBuffType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBuffType fails!";
		return false;
	}
	pElem_eBuffType->SetAttribute("value", pszEnum_eBuffType);
	pElem_eBuffType->SetAttribute("comment", ToUTF8Ptr("Buff大类"));
	if(rElement.LinkEndChild(pElem_eBuffType.get()) != NULL)
		pElem_eBuffType.release();
	unique_ptr<TiXmlElement> pElem_wBuffID(new TiXmlElement("UINT16"));
	if(pElem_wBuffID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBuffID->SetAttribute("name", "wBuffID");
	pElem_wBuffID->SetAttribute("value", NumberToString(s.wBuffID).c_str());
	pElem_wBuffID->SetAttribute("comment", ToUTF8Ptr("Buff种类"));
	if(rElement.LinkEndChild(pElem_wBuffID.get()) != NULL)
		pElem_wBuffID.release();
	unique_ptr<TiXmlElement> pElem_eBuffEffectType(new TiXmlElement("EBuffEffectType"));
	if(pElem_eBuffEffectType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eBuffEffectType->SetAttribute("name", "eBuffEffectType");
	const char* pszEnum_eBuffEffectType = EnumValToStr(s.eBuffEffectType);
	if(pszEnum_eBuffEffectType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBuffEffectType fails!";
		return false;
	}
	pElem_eBuffEffectType->SetAttribute("value", pszEnum_eBuffEffectType);
	pElem_eBuffEffectType->SetAttribute("comment", ToUTF8Ptr("Buff效果类型"));
	if(rElement.LinkEndChild(pElem_eBuffEffectType.get()) != NULL)
		pElem_eBuffEffectType.release();
	unique_ptr<TiXmlElement> pElem_eBuffState(new TiXmlElement("EBuffState"));
	if(pElem_eBuffState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eBuffState->SetAttribute("name", "eBuffState");
	const char* pszEnum_eBuffState = EnumValToStr(s.eBuffState);
	if(pszEnum_eBuffState == NULL)
	{
		LOG_CRI << "EnumValToStr for EBuffState fails!";
		return false;
	}
	pElem_eBuffState->SetAttribute("value", pszEnum_eBuffState);
	pElem_eBuffState->SetAttribute("comment", ToUTF8Ptr("Buff当前状态"));
	if(rElement.LinkEndChild(pElem_eBuffState.get()) != NULL)
		pElem_eBuffState.release();
	unique_ptr<TiXmlElement> pElem_vecBuffParam(new TiXmlElement("TVecUINT32"));
	if(pElem_vecBuffParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBuffParam->SetAttribute("name", "vecBuffParam");
	string strText_vecBuffParam;
	for(size_t i = 0; i < s.vecBuffParam.size(); ++i)
	{
		if(i > 0)
			strText_vecBuffParam += ", ";
		strText_vecBuffParam += NumberToString(s.vecBuffParam[i]);
	}
	unique_ptr<TiXmlText> pText_vecBuffParam(new TiXmlText(strText_vecBuffParam.c_str()));
	if(pText_vecBuffParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecBuffParam->LinkEndChild(pText_vecBuffParam.get()) != NULL)
		pText_vecBuffParam.release();
	pElem_vecBuffParam->SetAttribute("comment", ToUTF8Ptr("Buff效果参数"));
	if(rElement.LinkEndChild(pElem_vecBuffParam.get()) != NULL)
		pElem_vecBuffParam.release();
	unique_ptr<TiXmlElement> pElem_dwBuffCount(new TiXmlElement("UINT32"));
	if(pElem_dwBuffCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuffCount->SetAttribute("name", "dwBuffCount");
	pElem_dwBuffCount->SetAttribute("value", NumberToString(s.dwBuffCount).c_str());
	pElem_dwBuffCount->SetAttribute("comment", ToUTF8Ptr("Buff失效次数"));
	if(rElement.LinkEndChild(pElem_dwBuffCount.get()) != NULL)
		pElem_dwBuffCount.release();
	unique_ptr<TiXmlElement> pElem_dwBuffTime(new TiXmlElement("UINT32"));
	if(pElem_dwBuffTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuffTime->SetAttribute("name", "dwBuffTime");
	pElem_dwBuffTime->SetAttribute("value", NumberToString(s.dwBuffTime).c_str());
	pElem_dwBuffTime->SetAttribute("comment", ToUTF8Ptr("Buff失效时间"));
	if(rElement.LinkEndChild(pElem_dwBuffTime.get()) != NULL)
		pElem_dwBuffTime.release();
	unique_ptr<TiXmlElement> pElem_vecEffectMapID(new TiXmlElement("TVecUINT32"));
	if(pElem_vecEffectMapID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecEffectMapID->SetAttribute("name", "vecEffectMapID");
	string strText_vecEffectMapID;
	for(size_t i = 0; i < s.vecEffectMapID.size(); ++i)
	{
		if(i > 0)
			strText_vecEffectMapID += ", ";
		strText_vecEffectMapID += NumberToString(s.vecEffectMapID[i]);
	}
	unique_ptr<TiXmlText> pText_vecEffectMapID(new TiXmlText(strText_vecEffectMapID.c_str()));
	if(pText_vecEffectMapID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecEffectMapID->LinkEndChild(pText_vecEffectMapID.get()) != NULL)
		pText_vecEffectMapID.release();
	pElem_vecEffectMapID->SetAttribute("comment", ToUTF8Ptr("地图ID限制，空表示任意地图"));
	if(rElement.LinkEndChild(pElem_vecEffectMapID.get()) != NULL)
		pElem_vecEffectMapID.release();
	unique_ptr<TiXmlElement> pElem_byBattleType(new TiXmlElement("UINT8"));
	if(pElem_byBattleType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBattleType->SetAttribute("name", "byBattleType");
	pElem_byBattleType->SetAttribute("value", NumberToString(s.byBattleType).c_str());
	pElem_byBattleType->SetAttribute("comment", ToUTF8Ptr("有效的战斗类型(不存数据库)"));
	if(rElement.LinkEndChild(pElem_byBattleType.get()) != NULL)
		pElem_byBattleType.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDBBuffInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDBBuffInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecDBBuffInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDBBuffInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SBuffInfo::SBuffInfo() : qwRoleID(0), qwOwnerID(0), wBuffID(0), eBuffState((EBuffState)0), dwBuffCount(0), 
			dwBuffTime(0) { }

SBuffInfo::SBuffInfo(UINT64 qwRoleID_, UINT64 qwOwnerID_, UINT16 wBuffID_, EBuffState eBuffState_, const TVecUINT32& vecBuffData_, 
			UINT32 dwBuffCount_, UINT32 dwBuffTime_)
			: qwRoleID(qwRoleID_), qwOwnerID(qwOwnerID_), wBuffID(wBuffID_), eBuffState(eBuffState_), vecBuffData(vecBuffData_), 
			dwBuffCount(dwBuffCount_), dwBuffTime(dwBuffTime_) { }

CInArchive& operator>>(CInArchive& src, SBuffInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.qwOwnerID;
	src >> s.wBuffID;
	src >> (UINT8&)s.eBuffState;
	src >> s.vecBuffData;
	src >> s.dwBuffCount;
	src >> s.dwBuffTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBuffInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.qwOwnerID;
	src << s.wBuffID;
	src << (UINT8&)s.eBuffState;
	src << s.vecBuffData;
	src << s.dwBuffCount;
	src << s.dwBuffTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBuffInfo& s)
{
	if(strcmp(rElement.Value(), "SBuffInfo") != 0)
	{
		LOG_CRI << "rElement is not SBuffInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwOwnerID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwOwnerID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwOwnerID!";
		return false;
	}
	const char* pszVal_qwOwnerID = pElemChild->Attribute("value");
	if(pszVal_qwOwnerID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwOwnerID, s.qwOwnerID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wBuffID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBuffID") != 0)
	{
		LOG_CRI << "Attribute: name is not wBuffID!";
		return false;
	}
	const char* pszVal_wBuffID = pElemChild->Attribute("value");
	if(pszVal_wBuffID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBuffID, s.wBuffID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eBuffState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBuffState") != 0)
	{
		LOG_CRI << "pElemChild is not EBuffState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eBuffState") != 0)
	{
		LOG_CRI << "Attribute: name is not eBuffState!";
		return false;
	}
	const char* pszVal_eBuffState = pElemChild->Attribute("value");
	if(pszVal_eBuffState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eBuffState, s.eBuffState))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBuffData is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT32") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBuffData") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBuffData!";
		return false;
	}
	const char* pszText_vecBuffData = pElemChild->GetText();
	if(pszText_vecBuffData != NULL)
		SplitToNumber(pszText_vecBuffData, ",", s.vecBuffData);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuffCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuffCount") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuffCount!";
		return false;
	}
	const char* pszVal_dwBuffCount = pElemChild->Attribute("value");
	if(pszVal_dwBuffCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuffCount, s.dwBuffCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuffTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuffTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuffTime!";
		return false;
	}
	const char* pszVal_dwBuffTime = pElemChild->Attribute("value");
	if(pszVal_dwBuffTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuffTime, s.dwBuffTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBuffInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBuffInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("Buff详细信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("对应玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_qwOwnerID(new TiXmlElement("UINT64"));
	if(pElem_qwOwnerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOwnerID->SetAttribute("name", "qwOwnerID");
	pElem_qwOwnerID->SetAttribute("value", NumberToString(s.qwOwnerID).c_str());
	pElem_qwOwnerID->SetAttribute("comment", ToUTF8Ptr("所属实例ID(Role/Fighter/..."));
	if(rElement.LinkEndChild(pElem_qwOwnerID.get()) != NULL)
		pElem_qwOwnerID.release();
	unique_ptr<TiXmlElement> pElem_wBuffID(new TiXmlElement("UINT16"));
	if(pElem_wBuffID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBuffID->SetAttribute("name", "wBuffID");
	pElem_wBuffID->SetAttribute("value", NumberToString(s.wBuffID).c_str());
	pElem_wBuffID->SetAttribute("comment", ToUTF8Ptr("Buff种类"));
	if(rElement.LinkEndChild(pElem_wBuffID.get()) != NULL)
		pElem_wBuffID.release();
	unique_ptr<TiXmlElement> pElem_eBuffState(new TiXmlElement("EBuffState"));
	if(pElem_eBuffState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eBuffState->SetAttribute("name", "eBuffState");
	const char* pszEnum_eBuffState = EnumValToStr(s.eBuffState);
	if(pszEnum_eBuffState == NULL)
	{
		LOG_CRI << "EnumValToStr for EBuffState fails!";
		return false;
	}
	pElem_eBuffState->SetAttribute("value", pszEnum_eBuffState);
	pElem_eBuffState->SetAttribute("comment", ToUTF8Ptr("Buff当前状态"));
	if(rElement.LinkEndChild(pElem_eBuffState.get()) != NULL)
		pElem_eBuffState.release();
	unique_ptr<TiXmlElement> pElem_vecBuffData(new TiXmlElement("TVecUINT32"));
	if(pElem_vecBuffData == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBuffData->SetAttribute("name", "vecBuffData");
	string strText_vecBuffData;
	for(size_t i = 0; i < s.vecBuffData.size(); ++i)
	{
		if(i > 0)
			strText_vecBuffData += ", ";
		strText_vecBuffData += NumberToString(s.vecBuffData[i]);
	}
	unique_ptr<TiXmlText> pText_vecBuffData(new TiXmlText(strText_vecBuffData.c_str()));
	if(pText_vecBuffData == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecBuffData->LinkEndChild(pText_vecBuffData.get()) != NULL)
		pText_vecBuffData.release();
	pElem_vecBuffData->SetAttribute("comment", ToUTF8Ptr("Buff数值"));
	if(rElement.LinkEndChild(pElem_vecBuffData.get()) != NULL)
		pElem_vecBuffData.release();
	unique_ptr<TiXmlElement> pElem_dwBuffCount(new TiXmlElement("UINT32"));
	if(pElem_dwBuffCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuffCount->SetAttribute("name", "dwBuffCount");
	pElem_dwBuffCount->SetAttribute("value", NumberToString(s.dwBuffCount).c_str());
	pElem_dwBuffCount->SetAttribute("comment", ToUTF8Ptr("Buff叠加层数"));
	if(rElement.LinkEndChild(pElem_dwBuffCount.get()) != NULL)
		pElem_dwBuffCount.release();
	unique_ptr<TiXmlElement> pElem_dwBuffTime(new TiXmlElement("UINT32"));
	if(pElem_dwBuffTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuffTime->SetAttribute("name", "dwBuffTime");
	pElem_dwBuffTime->SetAttribute("value", NumberToString(s.dwBuffTime).c_str());
	pElem_dwBuffTime->SetAttribute("comment", ToUTF8Ptr("Buff失效时间"));
	if(rElement.LinkEndChild(pElem_dwBuffTime.get()) != NULL)
		pElem_dwBuffTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBuffInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBuffInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecBuffInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBuffInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SMoneyCount::SMoneyCount() : eMoneyType((EMoneyType)0), dwCount(0) { }

SMoneyCount::SMoneyCount(EMoneyType eMoneyType_, UINT32 dwCount_) : eMoneyType(eMoneyType_), dwCount(dwCount_) { }

CInArchive& operator>>(CInArchive& src, SMoneyCount& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eMoneyType;
	src >> s.dwCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMoneyCount& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eMoneyType;
	src << s.dwCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SMoneyCount& s)
{
	if(strcmp(rElement.Value(), "SMoneyCount") != 0)
	{
		LOG_CRI << "rElement is not SMoneyCount!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eMoneyType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EMoneyType") != 0)
	{
		LOG_CRI << "pElemChild is not EMoneyType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eMoneyType") != 0)
	{
		LOG_CRI << "Attribute: name is not eMoneyType!";
		return false;
	}
	const char* pszVal_eMoneyType = pElemChild->Attribute("value");
	if(pszVal_eMoneyType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eMoneyType, s.eMoneyType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCount") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCount!";
		return false;
	}
	const char* pszVal_dwCount = pElemChild->Attribute("value");
	if(pszVal_dwCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCount, s.dwCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SMoneyCount& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMoneyCount");
	rElement.SetAttribute("type", ToUTF8Ptr("货币列表"));
	unique_ptr<TiXmlElement> pElem_eMoneyType(new TiXmlElement("EMoneyType"));
	if(pElem_eMoneyType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eMoneyType->SetAttribute("name", "eMoneyType");
	const char* pszEnum_eMoneyType = EnumValToStr(s.eMoneyType);
	if(pszEnum_eMoneyType == NULL)
	{
		LOG_CRI << "EnumValToStr for EMoneyType fails!";
		return false;
	}
	pElem_eMoneyType->SetAttribute("value", pszEnum_eMoneyType);
	pElem_eMoneyType->SetAttribute("comment", ToUTF8Ptr("货币类型"));
	if(rElement.LinkEndChild(pElem_eMoneyType.get()) != NULL)
		pElem_eMoneyType.release();
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("货币量"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMoneyCount& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMoneyCount s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecMoneyCount& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMoneyCount"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SPlatformParam::SPlatformParam() : byPtType((EPtType)0), byQQPtType((EQQPtType)0), byQQPtLv(0), bySPType(0) { }

SPlatformParam::SPlatformParam(EPtType byPtType_, EQQPtType byQQPtType_, UINT8 byQQPtLv_, UINT8 bySPType_) : byPtType(byPtType_), byQQPtType(byQQPtType_), byQQPtLv(byQQPtLv_), bySPType(bySPType_) { }

CInArchive& operator>>(CInArchive& src, SPlatformParam& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.byPtType;
	src >> (UINT8&)s.byQQPtType;
	src >> s.byQQPtLv;
	src >> s.bySPType;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlatformParam& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.byPtType;
	src << (UINT8&)s.byQQPtType;
	src << s.byQQPtLv;
	src << s.bySPType;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPlatformParam& s)
{
	if(strcmp(rElement.Value(), "SPlatformParam") != 0)
	{
		LOG_CRI << "rElement is not SPlatformParam!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byPtType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EPtType") != 0)
	{
		LOG_CRI << "pElemChild is not EPtType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byPtType") != 0)
	{
		LOG_CRI << "Attribute: name is not byPtType!";
		return false;
	}
	const char* pszVal_byPtType = pElemChild->Attribute("value");
	if(pszVal_byPtType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_byPtType, s.byPtType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQQPtType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EQQPtType") != 0)
	{
		LOG_CRI << "pElemChild is not EQQPtType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQQPtType") != 0)
	{
		LOG_CRI << "Attribute: name is not byQQPtType!";
		return false;
	}
	const char* pszVal_byQQPtType = pElemChild->Attribute("value");
	if(pszVal_byQQPtType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_byQQPtType, s.byQQPtType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQQPtLv is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQQPtLv") != 0)
	{
		LOG_CRI << "Attribute: name is not byQQPtLv!";
		return false;
	}
	const char* pszVal_byQQPtLv = pElemChild->Attribute("value");
	if(pszVal_byQQPtLv == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQQPtLv, s.byQQPtLv))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySPType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySPType") != 0)
	{
		LOG_CRI << "Attribute: name is not bySPType!";
		return false;
	}
	const char* pszVal_bySPType = pElemChild->Attribute("value");
	if(pszVal_bySPType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySPType, s.bySPType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPlatformParam& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlatformParam");
	rElement.SetAttribute("type", ToUTF8Ptr("平台相关参数"));
	unique_ptr<TiXmlElement> pElem_byPtType(new TiXmlElement("EPtType"));
	if(pElem_byPtType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPtType->SetAttribute("name", "byPtType");
	const char* pszEnum_byPtType = EnumValToStr(s.byPtType);
	if(pszEnum_byPtType == NULL)
	{
		LOG_CRI << "EnumValToStr for EPtType fails!";
		return false;
	}
	pElem_byPtType->SetAttribute("value", pszEnum_byPtType);
	pElem_byPtType->SetAttribute("comment", ToUTF8Ptr("平台类型"));
	if(rElement.LinkEndChild(pElem_byPtType.get()) != NULL)
		pElem_byPtType.release();
	unique_ptr<TiXmlElement> pElem_byQQPtType(new TiXmlElement("EQQPtType"));
	if(pElem_byQQPtType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQQPtType->SetAttribute("name", "byQQPtType");
	const char* pszEnum_byQQPtType = EnumValToStr(s.byQQPtType);
	if(pszEnum_byQQPtType == NULL)
	{
		LOG_CRI << "EnumValToStr for EQQPtType fails!";
		return false;
	}
	pElem_byQQPtType->SetAttribute("value", pszEnum_byQQPtType);
	pElem_byQQPtType->SetAttribute("comment", ToUTF8Ptr("QQ平台类型"));
	if(rElement.LinkEndChild(pElem_byQQPtType.get()) != NULL)
		pElem_byQQPtType.release();
	unique_ptr<TiXmlElement> pElem_byQQPtLv(new TiXmlElement("UINT8"));
	if(pElem_byQQPtLv == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQQPtLv->SetAttribute("name", "byQQPtLv");
	pElem_byQQPtLv->SetAttribute("value", NumberToString(s.byQQPtLv).c_str());
	pElem_byQQPtLv->SetAttribute("comment", ToUTF8Ptr("QQ平台类型等级"));
	if(rElement.LinkEndChild(pElem_byQQPtLv.get()) != NULL)
		pElem_byQQPtLv.release();
	unique_ptr<TiXmlElement> pElem_bySPType(new TiXmlElement("UINT8"));
	if(pElem_bySPType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySPType->SetAttribute("name", "bySPType");
	pElem_bySPType->SetAttribute("value", NumberToString(s.bySPType).c_str());
	pElem_bySPType->SetAttribute("comment", ToUTF8Ptr("Bit位定义见EPlatformBitType"));
	if(rElement.LinkEndChild(pElem_bySPType.get()) != NULL)
		pElem_bySPType.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlatformParam& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPlatformParam s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecPlatformParam& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPlatformParam"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SActivityTime::SActivityTime() : dwActID(0), dwAlarm(0), dwReady(0), dwBegin(0), dwEnd(0) { }

SActivityTime::SActivityTime(UINT32 dwActID_, UINT32 dwAlarm_, UINT32 dwReady_, UINT32 dwBegin_, UINT32 dwEnd_)
			: dwActID(dwActID_), dwAlarm(dwAlarm_), dwReady(dwReady_), dwBegin(dwBegin_), dwEnd(dwEnd_) { }

CInArchive& operator>>(CInArchive& src, SActivityTime& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwActID;
	src >> s.dwAlarm;
	src >> s.dwReady;
	src >> s.dwBegin;
	src >> s.dwEnd;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SActivityTime& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwActID;
	src << s.dwAlarm;
	src << s.dwReady;
	src << s.dwBegin;
	src << s.dwEnd;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SActivityTime& s)
{
	if(strcmp(rElement.Value(), "SActivityTime") != 0)
	{
		LOG_CRI << "rElement is not SActivityTime!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwActID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwActID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwActID!";
		return false;
	}
	const char* pszVal_dwActID = pElemChild->Attribute("value");
	if(pszVal_dwActID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwActID, s.dwActID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAlarm is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAlarm") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAlarm!";
		return false;
	}
	const char* pszVal_dwAlarm = pElemChild->Attribute("value");
	if(pszVal_dwAlarm == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAlarm, s.dwAlarm))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwReady is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwReady") != 0)
	{
		LOG_CRI << "Attribute: name is not dwReady!";
		return false;
	}
	const char* pszVal_dwReady = pElemChild->Attribute("value");
	if(pszVal_dwReady == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwReady, s.dwReady))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBegin is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBegin") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBegin!";
		return false;
	}
	const char* pszVal_dwBegin = pElemChild->Attribute("value");
	if(pszVal_dwBegin == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBegin, s.dwBegin))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwEnd is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEnd") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEnd!";
		return false;
	}
	const char* pszVal_dwEnd = pElemChild->Attribute("value");
	if(pszVal_dwEnd == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEnd, s.dwEnd))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SActivityTime& s, TiXmlElement& rElement)
{
	rElement.SetValue("SActivityTime");
	rElement.SetAttribute("type", ToUTF8Ptr("Center2Game 活动时间同步"));
	unique_ptr<TiXmlElement> pElem_dwActID(new TiXmlElement("UINT32"));
	if(pElem_dwActID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwActID->SetAttribute("name", "dwActID");
	pElem_dwActID->SetAttribute("value", NumberToString(s.dwActID).c_str());
	pElem_dwActID->SetAttribute("comment", ToUTF8Ptr("活动ID"));
	if(rElement.LinkEndChild(pElem_dwActID.get()) != NULL)
		pElem_dwActID.release();
	unique_ptr<TiXmlElement> pElem_dwAlarm(new TiXmlElement("UINT32"));
	if(pElem_dwAlarm == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAlarm->SetAttribute("name", "dwAlarm");
	pElem_dwAlarm->SetAttribute("value", NumberToString(s.dwAlarm).c_str());
	pElem_dwAlarm->SetAttribute("comment", ToUTF8Ptr("公告"));
	if(rElement.LinkEndChild(pElem_dwAlarm.get()) != NULL)
		pElem_dwAlarm.release();
	unique_ptr<TiXmlElement> pElem_dwReady(new TiXmlElement("UINT32"));
	if(pElem_dwReady == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwReady->SetAttribute("name", "dwReady");
	pElem_dwReady->SetAttribute("value", NumberToString(s.dwReady).c_str());
	pElem_dwReady->SetAttribute("comment", ToUTF8Ptr("准备"));
	if(rElement.LinkEndChild(pElem_dwReady.get()) != NULL)
		pElem_dwReady.release();
	unique_ptr<TiXmlElement> pElem_dwBegin(new TiXmlElement("UINT32"));
	if(pElem_dwBegin == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBegin->SetAttribute("name", "dwBegin");
	pElem_dwBegin->SetAttribute("value", NumberToString(s.dwBegin).c_str());
	pElem_dwBegin->SetAttribute("comment", ToUTF8Ptr("开始"));
	if(rElement.LinkEndChild(pElem_dwBegin.get()) != NULL)
		pElem_dwBegin.release();
	unique_ptr<TiXmlElement> pElem_dwEnd(new TiXmlElement("UINT32"));
	if(pElem_dwEnd == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEnd->SetAttribute("name", "dwEnd");
	pElem_dwEnd->SetAttribute("value", NumberToString(s.dwEnd).c_str());
	pElem_dwEnd->SetAttribute("comment", ToUTF8Ptr("结束"));
	if(rElement.LinkEndChild(pElem_dwEnd.get()) != NULL)
		pElem_dwEnd.release();
	return true;
}

#endif

SActivityOpt::SActivityOpt() : dwActID(0), byIndex(0), dwSync(0), dwAlarm(0), dwReady(0), 
			dwBegin(0), dwEnd(0), bSync(false), dwOptTime(0) { }

SActivityOpt::SActivityOpt(UINT32 dwActID_, UINT8 byIndex_, const std::string& strName_, UINT32 dwSync_, UINT32 dwAlarm_, 
			UINT32 dwReady_, UINT32 dwBegin_, UINT32 dwEnd_, bool bSync_, UINT32 dwOptTime_)
			: dwActID(dwActID_), byIndex(byIndex_), strName(strName_), dwSync(dwSync_), dwAlarm(dwAlarm_), 
			dwReady(dwReady_), dwBegin(dwBegin_), dwEnd(dwEnd_), bSync(bSync_), dwOptTime(dwOptTime_) { }

SActivityOpt::SActivityOpt(SActivityOpt&& src) : dwActID(src.dwActID), byIndex(src.byIndex), strName(move(src.strName)), dwSync(src.dwSync), dwAlarm(src.dwAlarm), 
			dwReady(src.dwReady), dwBegin(src.dwBegin), dwEnd(src.dwEnd), bSync(src.bSync), dwOptTime(src.dwOptTime) { }

SActivityOpt& SActivityOpt::operator=(SActivityOpt&& rhs)
{
	if(this != &rhs)
	{
		this->~SActivityOpt();
		new (this) SActivityOpt(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SActivityOpt& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwActID;
	src >> s.byIndex;
	src >> s.strName;
	src >> s.dwSync;
	src >> s.dwAlarm;
	src >> s.dwReady;
	src >> s.dwBegin;
	src >> s.dwEnd;
	src >> s.bSync;
	src >> s.dwOptTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SActivityOpt& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwActID;
	src << s.byIndex;
	src << s.strName;
	src << s.dwSync;
	src << s.dwAlarm;
	src << s.dwReady;
	src << s.dwBegin;
	src << s.dwEnd;
	src << s.bSync;
	src << s.dwOptTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SActivityOpt& s)
{
	if(strcmp(rElement.Value(), "SActivityOpt") != 0)
	{
		LOG_CRI << "rElement is not SActivityOpt!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwActID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwActID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwActID!";
		return false;
	}
	const char* pszVal_dwActID = pElemChild->Attribute("value");
	if(pszVal_dwActID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwActID, s.dwActID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byIndex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byIndex") != 0)
	{
		LOG_CRI << "Attribute: name is not byIndex!";
		return false;
	}
	const char* pszVal_byIndex = pElemChild->Attribute("value");
	if(pszVal_byIndex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byIndex, s.byIndex))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strName") != 0)
	{
		LOG_CRI << "Attribute: name is not strName!";
		return false;
	}
	const char* pszVal_strName = pElemChild->Attribute("value");
	if(pszVal_strName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strName = pszVal_strName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSync is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSync") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSync!";
		return false;
	}
	const char* pszVal_dwSync = pElemChild->Attribute("value");
	if(pszVal_dwSync == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSync, s.dwSync))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAlarm is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAlarm") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAlarm!";
		return false;
	}
	const char* pszVal_dwAlarm = pElemChild->Attribute("value");
	if(pszVal_dwAlarm == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAlarm, s.dwAlarm))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwReady is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwReady") != 0)
	{
		LOG_CRI << "Attribute: name is not dwReady!";
		return false;
	}
	const char* pszVal_dwReady = pElemChild->Attribute("value");
	if(pszVal_dwReady == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwReady, s.dwReady))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBegin is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBegin") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBegin!";
		return false;
	}
	const char* pszVal_dwBegin = pElemChild->Attribute("value");
	if(pszVal_dwBegin == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBegin, s.dwBegin))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwEnd is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEnd") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEnd!";
		return false;
	}
	const char* pszVal_dwEnd = pElemChild->Attribute("value");
	if(pszVal_dwEnd == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEnd, s.dwEnd))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bSync is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bSync") != 0)
	{
		LOG_CRI << "Attribute: name is not bSync!";
		return false;
	}
	const char* pszVal_bSync = pElemChild->Attribute("value");
	if(pszVal_bSync == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bSync, s.bSync))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOptTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOptTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOptTime!";
		return false;
	}
	const char* pszVal_dwOptTime = pElemChild->Attribute("value");
	if(pszVal_dwOptTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOptTime, s.dwOptTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SActivityOpt& s, TiXmlElement& rElement)
{
	rElement.SetValue("SActivityOpt");
	rElement.SetAttribute("type", ToUTF8Ptr("活动中心数据库记录"));
	unique_ptr<TiXmlElement> pElem_dwActID(new TiXmlElement("UINT32"));
	if(pElem_dwActID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwActID->SetAttribute("name", "dwActID");
	pElem_dwActID->SetAttribute("value", NumberToString(s.dwActID).c_str());
	pElem_dwActID->SetAttribute("comment", ToUTF8Ptr("活动ID"));
	if(rElement.LinkEndChild(pElem_dwActID.get()) != NULL)
		pElem_dwActID.release();
	unique_ptr<TiXmlElement> pElem_byIndex(new TiXmlElement("UINT8"));
	if(pElem_byIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIndex->SetAttribute("name", "byIndex");
	pElem_byIndex->SetAttribute("value", NumberToString(s.byIndex).c_str());
	pElem_byIndex->SetAttribute("comment", ToUTF8Ptr("场次"));
	if(rElement.LinkEndChild(pElem_byIndex.get()) != NULL)
		pElem_byIndex.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("活动名字"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_dwSync(new TiXmlElement("UINT32"));
	if(pElem_dwSync == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSync->SetAttribute("name", "dwSync");
	pElem_dwSync->SetAttribute("value", NumberToString(s.dwSync).c_str());
	pElem_dwSync->SetAttribute("comment", ToUTF8Ptr("活动时间 同步"));
	if(rElement.LinkEndChild(pElem_dwSync.get()) != NULL)
		pElem_dwSync.release();
	unique_ptr<TiXmlElement> pElem_dwAlarm(new TiXmlElement("UINT32"));
	if(pElem_dwAlarm == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAlarm->SetAttribute("name", "dwAlarm");
	pElem_dwAlarm->SetAttribute("value", NumberToString(s.dwAlarm).c_str());
	pElem_dwAlarm->SetAttribute("comment", ToUTF8Ptr("活动公告时间"));
	if(rElement.LinkEndChild(pElem_dwAlarm.get()) != NULL)
		pElem_dwAlarm.release();
	unique_ptr<TiXmlElement> pElem_dwReady(new TiXmlElement("UINT32"));
	if(pElem_dwReady == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwReady->SetAttribute("name", "dwReady");
	pElem_dwReady->SetAttribute("value", NumberToString(s.dwReady).c_str());
	pElem_dwReady->SetAttribute("comment", ToUTF8Ptr("活动准备时间"));
	if(rElement.LinkEndChild(pElem_dwReady.get()) != NULL)
		pElem_dwReady.release();
	unique_ptr<TiXmlElement> pElem_dwBegin(new TiXmlElement("UINT32"));
	if(pElem_dwBegin == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBegin->SetAttribute("name", "dwBegin");
	pElem_dwBegin->SetAttribute("value", NumberToString(s.dwBegin).c_str());
	pElem_dwBegin->SetAttribute("comment", ToUTF8Ptr("活动开始时间"));
	if(rElement.LinkEndChild(pElem_dwBegin.get()) != NULL)
		pElem_dwBegin.release();
	unique_ptr<TiXmlElement> pElem_dwEnd(new TiXmlElement("UINT32"));
	if(pElem_dwEnd == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEnd->SetAttribute("name", "dwEnd");
	pElem_dwEnd->SetAttribute("value", NumberToString(s.dwEnd).c_str());
	pElem_dwEnd->SetAttribute("comment", ToUTF8Ptr("活动结束时间"));
	if(rElement.LinkEndChild(pElem_dwEnd.get()) != NULL)
		pElem_dwEnd.release();
	unique_ptr<TiXmlElement> pElem_bSync(new TiXmlElement("bool"));
	if(pElem_bSync == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bSync->SetAttribute("name", "bSync");
	pElem_bSync->SetAttribute("value", NumberToString(s.bSync).c_str());
	pElem_bSync->SetAttribute("comment", ToUTF8Ptr("是否同步Game"));
	if(rElement.LinkEndChild(pElem_bSync.get()) != NULL)
		pElem_bSync.release();
	unique_ptr<TiXmlElement> pElem_dwOptTime(new TiXmlElement("UINT32"));
	if(pElem_dwOptTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOptTime->SetAttribute("name", "dwOptTime");
	pElem_dwOptTime->SetAttribute("value", NumberToString(s.dwOptTime).c_str());
	pElem_dwOptTime->SetAttribute("comment", ToUTF8Ptr("操作时间"));
	if(rElement.LinkEndChild(pElem_dwOptTime.get()) != NULL)
		pElem_dwOptTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecActivityOpt& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SActivityOpt s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecActivityOpt& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SActivityOpt"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

} //namespace NProtoCommon
