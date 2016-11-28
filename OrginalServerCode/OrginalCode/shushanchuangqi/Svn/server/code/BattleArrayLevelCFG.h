// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBattleArrayLevelCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CBATTLEARRAYLEVELLOADER_H
#define _CBATTLEARRAYLEVELLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SBattleArrayLevelCFG
{
	/**
	阵位id
	**/
	UINT32	_ID;

	/**
	大阵Id
	**/
	UINT16	_BattleId;

	/**
	名称
	**/
	string	_Name;

	/**
	阵位类型
	**/
	UINT8	_SpotType;

	/**
	怪物组
	**/
	UINT16	_MonsterGroupID;

	/**
	通关奖励
	**/
	UINT16	_PassLootId;

	/**
	首次通关奖励
	**/
	UINT16	_FirstPassLootId;

	/**
	消耗体力
	**/
	UINT8	_CostEnergy;

	/**
	破阵标志
	**/
	UINT8	_PassTag;

	/**
	需要背包空格
	**/
	UINT8	_RequiredPackage;

	/**
	评价条件
	**/
	string	_Access;
}; // SBattleArrayLevelCFG define end

//data loader for the excel table
class CBattleArrayLevelLoader
{
public:
	std::vector<SBattleArrayLevelCFG*> _vecData;

	~CBattleArrayLevelLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

