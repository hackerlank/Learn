// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCittaCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCITTALOADER_H
#define _CCITTALOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SCittaCFG
{
	/**
	物品ID
	**/
	UINT32	_ID;

	/**
	属性条目数
	**/
	UINT8	_AttrCount;

	/**
	技能条目数
	**/
	UINT8	_SkillCount;

	/**
	最小值域
	**/
	UINT32	_RangeMin;

	/**
	最大值域
	**/
	UINT32	_RangeMax;

	/**
	特殊技能
	**/
	string	_Skill;

	/**
	印记
	**/
	string	_Signet;

	/**
	分解消耗银币
	**/
	UINT32	_SilverCost;

	/**
	分解获得材料ID
	**/
	UINT32	_ResolveMaterial;

	/**
	材料最小数量
	**/
	UINT32	_ResolveMin;

	/**
	材料最大数量
	**/
	UINT32	_ResolveMax;

	/**
	分解掉落ID
	**/
	UINT32	_ResolveLoots;
}; // SCittaCFG define end

//data loader for the excel table
class CCittaLoader
{
public:
	std::vector<SCittaCFG*> _vecData;

	~CCittaLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

