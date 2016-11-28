// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STreasureToolsSuitCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CTREASURETOOLSSUITLOADER_H
#define _CTREASURETOOLSSUITLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct STreasureToolsSuitCFG
{
	/**
	套装Id
	**/
	UINT16	_ID;

	/**
	套装名称
	**/
	string	_Name;

	/**
	宝具品质
	**/
	UINT16	_Color;

	/**
	宝具等级
	**/
	UINT16	_Level;

	/**
	件数
	**/
	UINT8	_Num;

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
	附加技能
	**/
	UINT16	_AdditionalSkills;
}; // STreasureToolsSuitCFG define end

//data loader for the excel table
class CTreasureToolsSuitLoader
{
public:
	std::vector<STreasureToolsSuitCFG*> _vecData;

	~CTreasureToolsSuitLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

