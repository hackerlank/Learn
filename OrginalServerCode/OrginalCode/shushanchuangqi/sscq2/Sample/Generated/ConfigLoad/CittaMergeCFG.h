// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCittaMergeCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCITTAMERGELOADER_H
#define _CCITTAMERGELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SCittaMergeCFG
{
	/**
	配方ID
	**/
	UINT32	_FormulaID;

	/**
	配方名称
	**/
	string	_Name;

	/**
	目标道具ID
	**/
	string	_CittaID;

	/**
	印记效果
	**/
	string	_SignetID;

	/**
	职业需求
	**/
	UINT8	_Job;

	/**
	配方等级
	**/
	UINT16	_RoleLevel;

	/**
	材料1ID
	**/
	UINT32	_Material1ID;

	/**
	材料1数量
	**/
	UINT32	_Material1Count;

	/**
	材料2ID
	**/
	UINT32	_Material2ID;

	/**
	材料2数量
	**/
	UINT32	_Material2Count;

	/**
	材料3ID
	**/
	UINT32	_Material3ID;

	/**
	材料3数量
	**/
	UINT32	_Material3Count;

	/**
	材料4ID
	**/
	UINT32	_Material4ID;

	/**
	材料4数量
	**/
	UINT32	_Material4Count;

	/**
	银币消耗
	**/
	UINT32	_SilverCost;

	/**
	悬浮Tips
	**/
	string	_Tips;
}; // SCittaMergeCFG define end

//data loader for the excel table
class CCittaMergeLoader
{
public:
	std::vector<SCittaMergeCFG*> _vecData;

	~CCittaMergeLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

