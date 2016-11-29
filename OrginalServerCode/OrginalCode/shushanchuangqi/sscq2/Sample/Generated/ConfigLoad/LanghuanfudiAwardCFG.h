// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLanghuanfudiAwardCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CLANGHUANFUDIAWARDLOADER_H
#define _CLANGHUANFUDIAWARDLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SLanghuanfudiAwardCFG
{
	/**
	等级
	**/
	UINT8	_Level;

	/**
	打坐基础修为
	**/
	UINT16	_SitBasicXiuwei;

	/**
	使用技能修为
	**/
	UINT16	_SkillXiuwei;

	/**
	打坐基础经验
	**/
	UINT16	_SitBasicExp;
}; // SLanghuanfudiAwardCFG define end

//data loader for the excel table
class CLanghuanfudiAwardLoader
{
public:
	std::vector<SLanghuanfudiAwardCFG*> _vecData;

	~CLanghuanfudiAwardLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

