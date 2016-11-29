// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLootsCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CLOOTSLOADER_H
#define _CLOOTSLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SLootsCFG
{
	/**
	ID
	**/
	UINT32	_ID;

	/**
	掉落分组名称
	**/
	string	_Name;

	/**
	掉落计算方式
	**/
	UINT8	_LootType;

	/**
	掉落产物
	**/
	string	_products;
}; // SLootsCFG define end

//data loader for the excel table
class CLootsLoader
{
public:
	std::vector<SLootsCFG*> _vecData;

	~CLootsLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

