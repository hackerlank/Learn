// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SComdljiuyidinglevelCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCOMDLJIUYIDINGLEVELLOADER_H
#define _CCOMDLJIUYIDINGLEVELLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SComdljiuyidinglevelCFG
{
	/**
	等级
	**/
	UINT8	_Level;

	/**
	经验值
	**/
	UINT32	_Experience;

	/**
	激活丹方
	**/
	string	_Activaterecipe;

	/**
	丹方基础产量增加
	**/
	UINT8	_Outputincrease;

	/**
	丹方基础元气值降低
	**/
	UINT8	_Yuanqireduce;

	/**
	主将生命值增加
	**/
	UINT16	_Lifeincrease;

	/**
	获得经验值增加
	**/
	UINT8	_Expincrease;

	/**
	主将攻击力增加
	**/
	UINT16	_Attackincrease;

	/**
	主将防御力增加
	**/
	UINT16	_Armorincrease;
}; // SComdljiuyidinglevelCFG define end

//data loader for the excel table
class CComdljiuyidinglevelLoader
{
public:
	std::vector<SComdljiuyidinglevelCFG*> _vecData;

	~CComdljiuyidinglevelLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

