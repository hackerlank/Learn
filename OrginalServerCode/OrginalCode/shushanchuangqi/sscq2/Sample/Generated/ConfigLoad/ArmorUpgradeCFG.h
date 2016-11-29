// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SArmorUpgradeCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CARMORUPGRADELOADER_H
#define _CARMORUPGRADELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SArmorUpgradeCFG
{
	/**
	铸造前装备
	**/
	UINT16	_Id1;

	/**
	铸造后装备
	**/
	UINT16	_Id2;

	/**
	铸造等级
	**/
	UINT16	_Level;

	/**
	材料1ID
	**/
	UINT16	_Material1;

	/**
	材料1数量
	**/
	UINT8	_Number1;

	/**
	材料2ID
	**/
	UINT16	_Material2;

	/**
	材料2数量
	**/
	UINT8	_Number2;

	/**
	材料3ID
	**/
	UINT16	_Material3;

	/**
	材料3数量
	**/
	UINT8	_Number3;

	/**
	材料4ID
	**/
	UINT16	_Material4;

	/**
	材料4数量
	**/
	UINT8	_Number4;

	/**
	银币消耗
	**/
	UINT32	_Cost;
}; // SArmorUpgradeCFG define end

//data loader for the excel table
class CArmorUpgradeLoader
{
public:
	std::vector<SArmorUpgradeCFG*> _vecData;

	~CArmorUpgradeLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

