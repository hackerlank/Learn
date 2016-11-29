// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SAttachSpiritLevelUpCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CATTACHSPIRITLEVELUPLOADER_H
#define _CATTACHSPIRITLEVELUPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SAttachSpiritLevelUpCFG
{
	/**
	职业
	**/
	UINT8	_Job;

	/**
	装备类别
	**/
	UINT8	_ArmorType;

	/**
	注灵等级
	**/
	UINT8	_SoulLevel;

	/**
	注灵1属性类别
	**/
	UINT8	_Soul1;

	/**
	注灵1属性值
	**/
	UINT32	_Value1;

	/**
	注灵2属性类别
	**/
	UINT8	_Soul2;

	/**
	注灵2属性值
	**/
	UINT32	_Value2;

	/**
	注灵3属性值
	**/
	UINT8	_Soul3;

	/**
	注灵3属性值
	**/
	UINT32	_Value3;
}; // SAttachSpiritLevelUpCFG define end

//data loader for the excel table
class CAttachSpiritLevelUpLoader
{
public:
	std::vector<SAttachSpiritLevelUpCFG*> _vecData;

	~CAttachSpiritLevelUpLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

