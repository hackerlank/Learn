// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSkillBaseCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSKILLBASELOADER_H
#define _CSKILLBASELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SSkillBaseCFG
{
	/**
	技能 ID
	**/
	UINT32	_ID;

	/**
	技能 名
	**/
	string	_Name;

	/**
	能否被反击
	**/
	UINT8	_canBeCounter;

	/**
	技能类型
	**/
	UINT16	_type;

	/**
	连携点数
	**/
	UINT8	_skillLink;

	/**
	多个选择发生的效果ID
	**/
	string	_probEffect;

	/**
	必然发生效果ID
	**/
	string	_effectid;

	/**
	符文名
	**/
	string	_symbolName;

	/**
	符文ID
	**/
	UINT32	_symbol;

	/**
	进阶ID
	**/
	UINT32	_advance;

	/**
	职业类型
	**/
	UINT16	_career;

	/**
	品质
	**/
	UINT8	_Color;

	/**
	解锁提示
	**/
	string	_LockTIPS;
}; // SSkillBaseCFG define end

//data loader for the excel table
class CSkillBaseLoader
{
public:
	std::vector<SSkillBaseCFG*> _vecData;

	~CSkillBaseLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

