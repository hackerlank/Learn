// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SEnergyPriceCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CENERGYPRICELOADER_H
#define _CENERGYPRICELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SEnergyPriceCFG
{
	/**
	购买次数
	**/
	UINT32	_BoughtTimes;

	/**
	体力定价
	**/
	UINT32	_Price;
}; // SEnergyPriceCFG define end

//data loader for the excel table
class CEnergyPriceLoader
{
public:
	std::vector<SEnergyPriceCFG*> _vecData;

	~CEnergyPriceLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

