// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SUpgradeCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CUPGRADELOADER_H
#define _CUPGRADELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SUpgradeCFG
{
	/**
	合成道具Id
	**/
	UINT16	_TargetItemId;

	/**
	需要材料
	**/
	string	_MaterialItemId;
}; // SUpgradeCFG define end

//data loader for the excel table
class CUpgradeLoader
{
public:
	std::vector<SUpgradeCFG*> _vecData;

	~CUpgradeLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

