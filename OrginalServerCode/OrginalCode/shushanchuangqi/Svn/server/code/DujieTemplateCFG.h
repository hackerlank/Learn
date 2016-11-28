// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDujieTemplateCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDUJIETEMPLATELOADER_H
#define _CDUJIETEMPLATELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDujieTemplateCFG
{
	/**
	模板Id
	**/
	UINT16	_TemplateId;

	/**
	渡劫等级
	**/
	UINT8	_Level;

	/**
	渡劫期
	**/
	string	_PeriodName;

	/**
	限制等级
	**/
	UINT16	_RequiredLevel;

	/**
	经验值
	**/
	UINT32	_Exp;

	/**
	主动技能解锁
	**/
	string	_NormalSkillUnlock;

	/**
	无双技能解锁
	**/
	UINT8	_MasterSkillUnlock;

	/**
	天赋技能解锁
	**/
	string	_BuffSkillUnlock;

	/**
	散仙颜色
	**/
	UINT8	_Color;

	/**
	模型特效
	**/
	UINT16	_Effect;

	/**
	底图Id
	**/
	UINT16	_Background;

	/**
	名字边框Id
	**/
	UINT16	_NameSquare;

	/**
	升阶所需道具ID
	**/
	UINT16	_EvolveItemID;

	/**
	单次消耗数量
	**/
	UINT16	_UsingNum;

	/**
	物理攻击
	**/
	float	_EFIGHTATTR_PHYATK;

	/**
	法术攻击
	**/
	float	_EFIGHTATTR_MGCATK;

	/**
	物理防御
	**/
	float	_EFIGHTATTR_PHYDEF;

	/**
	法术防御
	**/
	float	_EFIGHTATTR_MGCDEF;

	/**
	物理免伤
	**/
	float	_EFIGHTATTR_PHYRDC;

	/**
	魔法免伤
	**/
	float	_EFIGHTATTR_MGCRDC;

	/**
	最大生命
	**/
	UINT32	_EFIGHTATTR_MAXHP;

	/**
	身法
	**/
	float	_EFIGHTATTR_SPEED;

	/**
	命中值
	**/
	float	_EFIGHTATTR_HIT;

	/**
	命中率
	**/
	float	_EFIGHTATTR_HITRATE;

	/**
	闪避值
	**/
	float	_EFIGHTATTR_DODGE;

	/**
	闪避率
	**/
	float	_EFIGHTATTR_DODGERATE;

	/**
	暴击值
	**/
	float	_EFIGHTATTR_CRITICAL;

	/**
	暴击率
	**/
	float	_EFIGHTATTR_CRTRATE;

	/**
	稳固值
	**/
	float	_EFIGHTATTR_ANTICRITCAL;

	/**
	稳固率
	**/
	float	_EFIGHTATTR_ANTICRTRATE;

	/**
	格挡值
	**/
	float	_EFIGHTATTR_BLOCK;

	/**
	格挡率
	**/
	float	_EFIGHTATTR_BLOCKRATE;

	/**
	穿透值
	**/
	float	_EFIGHTATTR_PIERCE;

	/**
	穿透率
	**/
	float	_EFIGHTATTR_PIERCERATE;

	/**
	反击值
	**/
	float	_EFIGHTATTR_COUNTER;

	/**
	反击率
	**/
	float	_EFIGHTATTR_COUNTERRATE;

	/**
	压制值
	**/
	float	_EFIGHTATTR_RESIST;

	/**
	压制率
	**/
	float	_EFIGHTATTR_RESISTRATE;

	/**
	入场灵气
	**/
	UINT32	_EFIGHTATTR_INITAURA;

	/**
	最大灵气
	**/
	UINT32	_EFIGHTATTR_MAXAURA;

	/**
	暴击伤害增加
	**/
	float	_EFIGHTATTR_CRIEXTRAADD;

	/**
	暴击伤害减免
	**/
	float	_EFIGHTATTR_CRIEXTRARDC;

	/**
	金攻
	**/
	float	_EFIGHTATTR_METALATK;

	/**
	木攻
	**/
	float	_EFIGHTATTR_WOODATK;

	/**
	水攻
	**/
	float	_EFIGHTATTR_WATERATK;

	/**
	火攻
	**/
	float	_EFIGHTATTR_FIREATK;

	/**
	土攻
	**/
	float	_EFIGHTATTR_EARTHATK;

	/**
	金防
	**/
	float	_EFIGHTATTR_METALDEF;

	/**
	木防
	**/
	float	_EFIGHTATTR_WOODDEF;

	/**
	水防
	**/
	float	_EFIGHTATTR_WATERDEF;

	/**
	火防
	**/
	float	_EFIGHTATTR_FIREDEF;

	/**
	土防
	**/
	float	_EFIGHTATTR_EARTHDEF;

	/**
	物理攻击%
	**/
	float	_EFIGHTATTR_PHYATK_PER;

	/**
	法术攻击%
	**/
	float	_EFIGHTATTR_MGCATK_PER;

	/**
	物理防御%
	**/
	float	_EFIGHTATTR_PHYDEF_PER;

	/**
	法术防御%
	**/
	float	_EFIGHTATTR_MGCDEF_PER;

	/**
	最大生命%
	**/
	float	_EFIGHTATTR_MAXHP_PER;

	/**
	身法%
	**/
	float	_EFIGHTATTR_SPEED_PER;

	/**
	命中值%
	**/
	float	_EFIGHTATTR_HIT_PER;

	/**
	闪避值%
	**/
	float	_EFIGHTATTR_DODGE_PER;

	/**
	暴击值%
	**/
	float	_EFIGHTATTR_CRITICAL_PER;

	/**
	稳固值%
	**/
	float	_EFIGHTATTR_ANTICRITCAL_PER;

	/**
	格挡值%
	**/
	float	_EFIGHTATTR_BLOCK_PER;

	/**
	穿透值%
	**/
	float	_EFIGHTATTR_PIERCE_PER;

	/**
	反击值%
	**/
	float	_EFIGHTATTR_COUNTER_PER;

	/**
	压制值%
	**/
	float	_EFIGHTATTR_RESIST_PER;
}; // SDujieTemplateCFG define end

//data loader for the excel table
class CDujieTemplateLoader
{
public:
	std::vector<SDujieTemplateCFG*> _vecData;

	~CDujieTemplateLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

