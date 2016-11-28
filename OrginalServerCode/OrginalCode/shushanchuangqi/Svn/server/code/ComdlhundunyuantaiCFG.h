// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SComdlhundunyuantaiCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCOMDLHUNDUNYUANTAILOADER_H
#define _CCOMDLHUNDUNYUANTAILOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SComdlhundunyuantaiCFG
{
	/**
	混沌元胎等级
	**/
	UINT8	_level;

	/**
	元气值
	**/
	UINT16	_Yuanqi;

	/**
	绿色掉落
	**/
	string	_Greenloot;

	/**
	蓝色掉落
	**/
	string	_Blueloot;

	/**
	紫色掉落
	**/
	string	_Purpleloot;

	/**
	橙色掉落
	**/
	string	_Yellowloot;
}; // SComdlhundunyuantaiCFG define end

//data loader for the excel table
class CComdlhundunyuantaiLoader
{
public:
	std::vector<SComdlhundunyuantaiCFG*> _vecData;

	~CComdlhundunyuantaiLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

