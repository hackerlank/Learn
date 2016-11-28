// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuildBuildingCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGUILDBUILDINGLOADER_H
#define _CGUILDBUILDINGLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGuildBuildingCFG
{
	/**
	建筑类别ID
	**/
	UINT8	_ID;

	/**
	等级
	**/
	UINT8	_Level;

	/**
	升级所需资金
	**/
	UINT32	_Cost;

	/**
	效果对应的参数值
	**/
	UINT32	_Val;
}; // SGuildBuildingCFG define end

//data loader for the excel table
class CGuildBuildingLoader
{
public:
	std::vector<SGuildBuildingCFG*> _vecData;

	~CGuildBuildingLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

