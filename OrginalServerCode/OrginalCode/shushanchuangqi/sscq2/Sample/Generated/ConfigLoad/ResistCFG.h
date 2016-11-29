// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SResistCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CRESISTLOADER_H
#define _CRESISTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SResistCFG
{
	/**
	阻挡物ID
	**/
	UINT16	_wResistId;

	/**
	阻挡物名称
	**/
	string	_strName;

	/**
	资源类型
	**/
	UINT8	_AssetType;

	/**
	资源参数1
	**/
	UINT16	_AssetParam1;

	/**
	出现动画
	**/
	string	_Asset;

	/**
	消失效果
	**/
	string	_Disappear;
}; // SResistCFG define end

//data loader for the excel table
class CResistLoader
{
public:
	std::vector<SResistCFG*> _vecData;

	~CResistLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

