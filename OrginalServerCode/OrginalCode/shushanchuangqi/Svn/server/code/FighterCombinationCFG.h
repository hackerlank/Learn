// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFighterCombinationCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFIGHTERCOMBINATIONLOADER_H
#define _CFIGHTERCOMBINATIONLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFighterCombinationCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	组合名
	**/
	string	_Name;

	/**
	图标
	**/
	UINT8	_Icon;

	/**
	包含散仙
	**/
	string	_Hero;

	/**
	光环效果ID
	**/
	UINT8	_Effect;

	/**
	连携技ID
	**/
	UINT32	_Skill;

	/**
	激活条件
	**/
	UINT16	_GetCond;

	/**
	品质
	**/
	UINT8	_Color;

	/**
	等级限制
	**/
	UINT16	_Limit;
}; // SFighterCombinationCFG define end

//data loader for the excel table
class CFighterCombinationLoader
{
public:
	std::vector<SFighterCombinationCFG*> _vecData;

	~CFighterCombinationLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

