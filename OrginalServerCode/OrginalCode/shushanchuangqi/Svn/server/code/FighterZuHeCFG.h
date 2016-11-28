// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFighterZuHeCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFIGHTERZUHELOADER_H
#define _CFIGHTERZUHELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFighterZuHeCFG
{
	/**
	组合ID
	**/
	UINT16	_ID;

	/**
	组合名称
	**/
	string	_Name;

	/**
	基础道术效果
	**/
	UINT16	_BaseEffect;

	/**
	完整道术效果
	**/
	UINT16	_FullEffect;
}; // SFighterZuHeCFG define end

//data loader for the excel table
class CFighterZuHeLoader
{
public:
	std::vector<SFighterZuHeCFG*> _vecData;

	~CFighterZuHeLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

