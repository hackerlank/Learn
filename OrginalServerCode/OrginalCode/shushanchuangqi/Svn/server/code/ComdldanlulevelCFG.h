// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SComdldanlulevelCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCOMDLDANLULEVELLOADER_H
#define _CCOMDLDANLULEVELLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SComdldanlulevelCFG
{
	/**
	丹炉等级
	**/
	UINT8	_Level;

	/**
	丹炉名称
	**/
	string	_Name;

	/**
	产量值增加
	**/
	UINT8	_Outputincrease;

	/**
	基础元气值降低
	**/
	UINT8	_Yuanqireduce;

	/**
	升级花费银币
	**/
	UINT16	_Silvercost;

	/**
	升级花费礼券
	**/
	UINT16	_Couponcost;

	/**
	升级花费仙石
	**/
	UINT16	_Goldcost;
}; // SComdldanlulevelCFG define end

//data loader for the excel table
class CComdldanlulevelLoader
{
public:
	std::vector<SComdldanlulevelCFG*> _vecData;

	~CComdldanlulevelLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

