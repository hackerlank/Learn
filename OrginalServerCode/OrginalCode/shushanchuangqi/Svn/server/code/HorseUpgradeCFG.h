// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SHorseUpgradeCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CHORSEUPGRADELOADER_H
#define _CHORSEUPGRADELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SHorseUpgradeCFG
{
	/**
	坐骑等阶
	**/
	UINT32	_HorseLevel;

	/**
	技能等级
	**/
	UINT32	_SkillLevel;

	/**
	速度加成
	**/
	UINT32	_Speed;

	/**
	消耗道具ID
	**/
	UINT32	_NeedItemID;

	/**
	每次消耗
	**/
	UINT32	_NeedItemCnt;

	/**
	进阶值下限
	**/
	UINT32	_ExpLow;

	/**
	进阶值上限
	**/
	UINT32	_ExpHigh;

	/**
	升级需求值
	**/
	UINT32	_NeedExp;

	/**
	附加属性
	**/
	UINT32	_SkillAttrID;

	/**
	模型id
	**/
	UINT32	_ModelID;

	/**
	名字
	**/
	string	_ModelName;

	/**
	坐骑特效
	**/
	string	_EffectName;
}; // SHorseUpgradeCFG define end

//data loader for the excel table
class CHorseUpgradeLoader
{
public:
	std::vector<SHorseUpgradeCFG*> _vecData;

	~CHorseUpgradeLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

