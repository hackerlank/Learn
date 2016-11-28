// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STreasureToolsCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CTREASURETOOLSLOADER_H
#define _CTREASURETOOLSLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct STreasureToolsCFG
{
	/**
	id
	**/
	UINT16	_ID;

	/**
	宝具等级
	**/
	UINT16	_Level;

	/**
	颜色
	**/
	UINT16	_Color;

	/**
	部位
	**/
	UINT16	_Location;

	/**
	名称
	**/
	string	_Name;

	/**
	图标
	**/
	string	_Icon;

	/**
	条目数
	**/
	UINT8	_EntryNum;

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
	物理攻击出现概率
	**/
	float	_EFIGHTATTR_PHYATKChance;

	/**
	法术攻击出现概率
	**/
	float	_EFIGHTATTR_MGCATKChance;

	/**
	物理防御出现概率
	**/
	float	_EFIGHTATTR_PHYDEFChance;

	/**
	法术防御出现概率
	**/
	float	_EFIGHTATTR_MGCDEFChance;

	/**
	最大生命出现概率
	**/
	UINT32	_EFIGHTATTR_MAXHPChance;

	/**
	身法出现概率
	**/
	float	_EFIGHTATTR_SPEEDChance;

	/**
	命中值出现概率
	**/
	float	_EFIGHTATTR_HITChance;

	/**
	闪避值出现概率
	**/
	float	_EFIGHTATTR_DODGEChance;

	/**
	暴击值出现概率
	**/
	float	_EFIGHTATTR_CRITICALChance;

	/**
	反击值出现概率
	**/
	float	_EFIGHTATTR_COUNTERChance;

	/**
	攻击中缀
	**/
	string	_AttackName;

	/**
	物防中缀
	**/
	string	_PhyDefName;

	/**
	法防中缀
	**/
	string	_MagicDefName;

	/**
	身法中缀
	**/
	string	_SpeedName;

	/**
	生命中缀
	**/
	string	_HealthName;

	/**
	命中中缀
	**/
	string	_HitName;

	/**
	闪避中缀
	**/
	string	_DodgeName;

	/**
	暴击中缀
	**/
	string	_CriticalName;

	/**
	反击中缀
	**/
	string	_CounterName;

	/**
	绿色区间
	**/
	string	_GreenRange;

	/**
	出现概率
	**/
	UINT16	_GreenChance;

	/**
	蓝色区间
	**/
	string	_BlueRange;

	/**
	出现概率
	**/
	UINT16	_BlueChance;

	/**
	紫色区间
	**/
	string	_PurpleRange;

	/**
	出现概率
	**/
	UINT16	_PurpleChance;

	/**
	技能概率
	**/
	UINT16	_SkillChancePurple;

	/**
	技能Id
	**/
	UINT16	_SkillIdPurple;

	/**
	技能前缀
	**/
	string	_SkillPreName;

	/**
	橙色区间
	**/
	string	_OrangeRange;

	/**
	橙色概率
	**/
	UINT16	_OrangeChance;

	/**
	技能概率
	**/
	UINT16	_SkillChanceOrange;

	/**
	技能Id
	**/
	UINT16	_SkillIdOrange;

	/**
	技能前缀
	**/
	string	_SkillName;
}; // STreasureToolsCFG define end

//data loader for the excel table
class CTreasureToolsLoader
{
public:
	std::vector<STreasureToolsCFG*> _vecData;

	~CTreasureToolsLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

