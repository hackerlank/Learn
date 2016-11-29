// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STalentSkillCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CTALENTSKILLLOADER_H
#define _CTALENTSKILLLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct STalentSkillCFG
{
	/**
	ID
	**/
	UINT32	_ID;

	/**
	技能ID
	**/
	UINT32	_SkillID;

	/**
	名字
	**/
	string	_Name;

	/**
	品质
	**/
	UINT8	_Quality;

	/**
	等级
	**/
	UINT8	_Level;

	/**
	消耗类型1
	**/
	UINT16	_skillCostType;

	/**
	升级消耗1
	**/
	UINT32	_skillCost;

	/**
	需求等级
	**/
	UINT8	_needLvl;

	/**
	附加属性ID
	**/
	UINT32	_SkillAttr;
}; // STalentSkillCFG define end

//data loader for the excel table
class CTalentSkillLoader
{
public:
	std::vector<STalentSkillCFG*> _vecData;

	~CTalentSkillLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

