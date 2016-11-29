// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFighterStarCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFIGHTERSTARLOADER_H
#define _CFIGHTERSTARLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFighterStarCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	综合星级
	**/
	UINT8	_Star;

	/**
	数值备注
	**/
	string	_Name;

	/**
	物理攻击
	**/
	UINT8	_EFIGHTATTR_PHYATK;

	/**
	法术攻击
	**/
	UINT8	_EFIGHTATTR_MGCATK;

	/**
	物理防御
	**/
	UINT8	_EFIGHTATTR_PHYDEF;

	/**
	法术防御
	**/
	UINT8	_EFIGHTATTR_MGCDEF;

	/**
	生命
	**/
	UINT8	_EFIGHTATTR_MAXHP;

	/**
	身法
	**/
	UINT8	_EFIGHTATTR_SPEED;

	/**
	命中值
	**/
	UINT8	_EFIGHTATTR_HIT;

	/**
	闪避值
	**/
	UINT8	_EFIGHTATTR_DODGE;

	/**
	暴击值
	**/
	UINT8	_EFIGHTATTR_CRITICAL;

	/**
	稳固值
	**/
	UINT8	_EFIGHTATTR_ANTICRITCAL;

	/**
	穿透值
	**/
	UINT8	_EFIGHTATTR_PIERCE;

	/**
	反击值
	**/
	UINT8	_EFIGHTATTR_COUNTER;

	/**
	压制值
	**/
	UINT8	_EFIGHTATTR_RESIST;

	/**
	格挡值
	**/
	UINT8	_EFIGHTATTR_BLOCK;

	/**
	物理免伤
	**/
	UINT8	_EFIGHTATTR_PHYRDC;

	/**
	魔法免伤
	**/
	UINT8	_EFIGHTATTR_MGCRDC;

	/**
	命中率
	**/
	UINT8	_EFIGHTATTR_HITRATE;

	/**
	闪避率
	**/
	UINT8	_EFIGHTATTR_DODGERATE;

	/**
	暴击率
	**/
	UINT8	_EFIGHTATTR_CRTRATE;

	/**
	稳固率
	**/
	UINT8	_EFIGHTATTR_ANTICRTRATE;

	/**
	格挡率
	**/
	UINT8	_EFIGHTATTR_BLOCKRATE;

	/**
	穿透率
	**/
	UINT8	_EFIGHTATTR_PIERCERATE;

	/**
	反击率
	**/
	UINT8	_EFIGHTATTR_COUNTERRATE;

	/**
	压制率
	**/
	UINT8	_EFIGHTATTR_RESISTRATE;

	/**
	入场灵气
	**/
	UINT8	_EFIGHTATTR_INITAURA;

	/**
	最大灵气
	**/
	UINT8	_EFIGHTATTR_MAXAURA;

	/**
	暴击伤害增加
	**/
	UINT8	_EFIGHTATTR_CRIEXTRAADD;

	/**
	暴击伤害减免
	**/
	UINT8	_EFIGHTATTR_CRIEXTRARDC;

	/**
	金攻
	**/
	UINT8	_EFIGHTATTR_METALATK;

	/**
	木攻
	**/
	UINT8	_EFIGHTATTR_WOODATK;

	/**
	水攻
	**/
	UINT8	_EFIGHTATTR_WATERATK;

	/**
	火攻
	**/
	UINT8	_EFIGHTATTR_FIREATK;

	/**
	土攻
	**/
	UINT8	_EFIGHTATTR_EARTHATK;

	/**
	金防
	**/
	UINT8	_EFIGHTATTR_METALDEF;

	/**
	木防
	**/
	UINT8	_EFIGHTATTR_WOODDEF;

	/**
	水防
	**/
	UINT8	_EFIGHTATTR_WATERDEF;

	/**
	火防
	**/
	UINT8	_EFIGHTATTR_FIREDEF;

	/**
	土防
	**/
	UINT8	_EFIGHTATTR_EARTHDEF;

	/**
	物理攻击%
	**/
	UINT8	_EFIGHTATTR_PHYATK_PER;

	/**
	法术攻击%
	**/
	UINT8	_EFIGHTATTR_MGCATK_PER;

	/**
	物理防御%
	**/
	UINT8	_EFIGHTATTR_PHYDEF_PER;

	/**
	法术防御%
	**/
	UINT8	_EFIGHTATTR_MGCDEF_PER;

	/**
	最大生命%
	**/
	UINT8	_EFIGHTATTR_MAXHP_PER;

	/**
	身法%
	**/
	UINT8	_EFIGHTATTR_SPEED_PER;

	/**
	命中值%
	**/
	UINT8	_EFIGHTATTR_HIT_PER;

	/**
	闪避值%
	**/
	UINT8	_EFIGHTATTR_DODGE_PER;

	/**
	暴击值%
	**/
	UINT8	_EFIGHTATTR_CRITICAL_PER;

	/**
	稳固值%
	**/
	UINT8	_EFIGHTATTR_ANTICRITCAL_PER;

	/**
	格挡值%
	**/
	UINT8	_EFIGHTATTR_BLOCK_PER;

	/**
	穿透值%
	**/
	UINT8	_EFIGHTATTR_PIERCE_PER;

	/**
	反击值%
	**/
	UINT8	_EFIGHTATTR_COUNTER_PER;

	/**
	压制值%
	**/
	UINT8	_EFIGHTATTR_RESIST_PER;

	/**
	法术抵抗
	**/
	UINT8	_EFIGHTATTR_ANTIEFFECT;
}; // SFighterStarCFG define end

//data loader for the excel table
class CFighterStarLoader
{
public:
	std::vector<SFighterStarCFG*> _vecData;

	~CFighterStarLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

