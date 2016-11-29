// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDemonTowerCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDEMONTOWERLOADER_H
#define _CDEMONTOWERLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDemonTowerCFG
{
	/**
	层数
	**/
	UINT32	_FloorID;

	/**
	地图
	**/
	UINT32	_MapID;

	/**
	每日奖励类型
	**/
	UINT32	_DayPrizeType;

	/**
	每日奖励
	**/
	UINT32	_DayPrize;

	/**
	过关奖励类型
	**/
	UINT32	_PassPrizeType;

	/**
	过关奖励
	**/
	UINT32	_PassPrize;

	/**
	刷新宝箱
	**/
	UINT32	_PrizeBox;

	/**
	额外奖励
	**/
	string	_ExtraPrize;

	/**
	镇守位个数
	**/
	UINT32	_PositoinCount;

	/**
	是否可以争夺位置
	**/
	UINT8	_IsCanFighter;

	/**
	镇守怪物组
	**/
	UINT32	_MonsterGroupID;

	/**
	生命之魄
	**/
	UINT32	_Hp;

	/**
	攻击之魄
	**/
	UINT32	_Atk;

	/**
	暴击之魄
	**/
	UINT32	_Craze;

	/**
	反击之魄
	**/
	UINT32	_Pierce;

	/**
	身法之魄
	**/
	UINT32	_Agilty;

	/**
	防御之魄
	**/
	UINT32	_Def;

	/**
	命中之魄
	**/
	UINT32	_Destory;

	/**
	闪避之魄
	**/
	UINT32	_Tenacity;

	/**
	弹出引导
	**/
	UINT16	_Guide;
}; // SDemonTowerCFG define end

//data loader for the excel table
class CDemonTowerLoader
{
public:
	std::vector<SDemonTowerCFG*> _vecData;

	~CDemonTowerLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

