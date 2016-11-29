// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBagCostCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CBAGCOSTLOADER_H
#define _CBAGCOSTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SBagCostCFG
{
	/**
	待开启格子顺序
	**/
	UINT8	_Idx;

	/**
	开启花费金额
	**/
	UINT8	_Cost;

	/**
	自动开启所需时间
	**/
	UINT16	_Time;

	/**
	开启格子提供的属性
	**/
	UINT16	_BagAttr;
}; // SBagCostCFG define end

//data loader for the excel table
class CBagCostLoader
{
public:
	std::vector<SBagCostCFG*> _vecData;

	~CBagCostLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

