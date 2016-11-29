// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFighterTalentCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFIGHTERTALENTLOADER_H
#define _CFIGHTERTALENTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFighterTalentCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	天赋类型
	**/
	UINT8	_TalentType;

	/**
	分组
	**/
	UINT32	_GroupID;

	/**
	需求等级
	**/
	UINT16	_Level;

	/**
	激活条件
	**/
	UINT32	_CondID;

	/**
	技能id
	**/
	UINT32	_SkillID;

	/**
	天赋名字
	**/
	string	_Name;

	/**
	描述
	**/
	string	_Description;

	/**
	美术素材
	**/
	string	_Icon;
}; // SFighterTalentCFG define end

//data loader for the excel table
class CFighterTalentLoader
{
public:
	std::vector<SFighterTalentCFG*> _vecData;

	~CFighterTalentLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

