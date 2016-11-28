// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SIntensifyCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CINTENSIFYLOADER_H
#define _CINTENSIFYLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SIntensifyCFG
{
	/**
	职业
	**/
	UINT8	_Job;

	/**
	装备类型
	**/
	UINT8	_ArmorType;

	/**
	强化等级
	**/
	UINT8	_IntensifyLevel;

	/**
	银币消耗量
	**/
	UINT32	_SilverNeed;

	/**
	特殊效果几率
	**/
	UINT32	_SpecialEffect;

	/**
	成功几率
	**/
	UINT32	_Chance;

	/**
	物理攻击
	**/
	UINT32	_EFIGHTATTR_PHYATK;

	/**
	法术攻击
	**/
	UINT32	_EFIGHTATTR_MGCATK;

	/**
	物理防御
	**/
	UINT32	_EFIGHTATTR_PHYDEF;

	/**
	法术防御
	**/
	UINT32	_EFIGHTATTR_MGCDEF;

	/**
	物理免伤
	**/
	UINT32	_EFIGHTATTR_PHYRDC;

	/**
	法术免伤
	**/
	UINT32	_EFIGHTATTR_MGCRDC;

	/**
	最大生命
	**/
	UINT32	_EFIGHTATTR_MAXHP;

	/**
	身法
	**/
	UINT32	_EFIGHTATTR_SPEED;

	/**
	命中值
	**/
	UINT32	_EFIGHTATTR_HIT;

	/**
	命中率
	**/
	UINT32	_EFIGHTATTR_HITRATE;

	/**
	闪避值
	**/
	UINT32	_EFIGHTATTR_DODGE;

	/**
	闪避率
	**/
	UINT32	_EFIGHTATTR_DODGERATE;

	/**
	暴击值
	**/
	UINT32	_EFIGHTATTR_CRITICAL;

	/**
	暴击率
	**/
	UINT32	_EFIGHTATTR_CRTRATE;

	/**
	稳固值
	**/
	UINT32	_EFIGHTATTR_ANTICRITCAL;

	/**
	稳固率
	**/
	UINT32	_EFIGHTATTR_ANTICRTRATE;

	/**
	格挡值
	**/
	UINT32	_EFIGHTATTR_BLOCK;

	/**
	格挡率
	**/
	UINT32	_EFIGHTATTR_BLOCKRATE;

	/**
	穿透值
	**/
	UINT32	_EFIGHTATTR_PIERCE;

	/**
	穿透率
	**/
	UINT32	_EFIGHTATTR_PIERCERATE;

	/**
	反击值
	**/
	UINT32	_EFIGHTATTR_COUNTER;

	/**
	反击率
	**/
	UINT32	_EFIGHTATTR_COUNTERRATE;

	/**
	压制值
	**/
	UINT32	_EFIGHTATTR_RESIST;

	/**
	压制率
	**/
	UINT32	_EFIGHTATTR_RESISTRATE;

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
	UINT32	_EFIGHTATTR_CRIEXTRAADD;

	/**
	暴击伤害减免
	**/
	UINT32	_EFIGHTATTR_CRIEXTRARDC;

	/**
	金攻击
	**/
	UINT32	_EFIGHTATTR_METALATK;

	/**
	木攻击
	**/
	UINT32	_EFIGHTATTR_WOODATK;

	/**
	水攻击
	**/
	UINT32	_EFIGHTATTR_WATERATK;

	/**
	火攻击
	**/
	UINT32	_EFIGHTATTR_FIREATK;

	/**
	土攻击
	**/
	UINT32	_EFIGHTATTR_EARTHATK;

	/**
	金防
	**/
	UINT32	_EFIGHTATTR_METALDEF;

	/**
	木防
	**/
	UINT32	_EFIGHTATTR_WOODDEF;

	/**
	水防
	**/
	UINT32	_EFIGHTATTR_WATERDEF;

	/**
	火防
	**/
	UINT32	_EFIGHTATTR_FIREDEF;

	/**
	土防
	**/
	UINT32	_EFIGHTATTR_EARTHDEF;
}; // SIntensifyCFG define end

//data loader for the excel table
class CIntensifyLoader
{
public:
	std::vector<SIntensifyCFG*> _vecData;

	~CIntensifyLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

