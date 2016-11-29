// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SYelloDiamondCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CYELLODIAMONDLOADER_H
#define _CYELLODIAMONDLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SYelloDiamondCFG
{
	/**
	ID
	**/
	UINT8	_ID;

	/**
	UINT8
	**/
	UINT8	_BagType;

	/**
	等级
	**/
	UINT8	_Level;

	/**
	礼包内容
	**/
	string	_Pack;

	/**
	礼包内容
	**/
	string	_PackEx;
}; // SYelloDiamondCFG define end

//data loader for the excel table
class CYelloDiamondLoader
{
public:
	std::vector<SYelloDiamondCFG*> _vecData;

	~CYelloDiamondLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

