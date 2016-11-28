// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBattleArrayPriceCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CBATTLEARRAYPRICELOADER_H
#define _CBATTLEARRAYPRICELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SBattleArrayPriceCFG
{
	/**
	购买次数
	**/
	UINT16	_BoughtTimes;

	/**
	破阵次数定价
	**/
	UINT32	_BattleArrayPrice;
}; // SBattleArrayPriceCFG define end

//data loader for the excel table
class CBattleArrayPriceLoader
{
public:
	std::vector<SBattleArrayPriceCFG*> _vecData;

	~CBattleArrayPriceLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

