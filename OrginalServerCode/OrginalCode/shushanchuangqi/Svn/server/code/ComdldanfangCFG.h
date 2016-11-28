// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SComdldanfangCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCOMDLDANFANGLOADER_H
#define _CCOMDLDANFANGLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SComdldanfangCFG
{
	/**
	丹方id
	**/
	UINT32	_ID;

	/**
	丹方类型
	**/
	UINT8	_Type;

	/**
	丹方名
	**/
	string	_Name;

	/**
	基础元气值
	**/
	UINT16	_Yuanqi;

	/**
	基础产量
	**/
	string	_Output;

	/**
	所需材料
	**/
	string	_Ingredient;
}; // SComdldanfangCFG define end

//data loader for the excel table
class CComdldanfangLoader
{
public:
	std::vector<SComdldanfangCFG*> _vecData;

	~CComdldanfangLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

