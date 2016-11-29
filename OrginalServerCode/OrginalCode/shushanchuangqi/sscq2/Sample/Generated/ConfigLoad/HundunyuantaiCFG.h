// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SHundunyuantaiCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CHUNDUNYUANTAILOADER_H
#define _CHUNDUNYUANTAILOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SHundunyuantaiCFG
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
}; // SHundunyuantaiCFG define end

//data loader for the excel table
class CHundunyuantaiLoader
{
public:
	std::vector<SHundunyuantaiCFG*> _vecData;

	~CHundunyuantaiLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

