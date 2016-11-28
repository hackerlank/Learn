// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFighterInstinctCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFIGHTERINSTINCTLOADER_H
#define _CFIGHTERINSTINCTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFighterInstinctCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	类型
	**/
	UINT8	_Type;

	/**
	血脉能力
	**/
	string	_Name;

	/**
	加成比例
	**/
	string	_Growth;

	/**
	品质
	**/
	UINT8	_Level;

	/**
	刷出的几率
	**/
	UINT16	_Probability;

	/**
	描述
	**/
	string	_Description;
}; // SFighterInstinctCFG define end

//data loader for the excel table
class CFighterInstinctLoader
{
public:
	std::vector<SFighterInstinctCFG*> _vecData;

	~CFighterInstinctLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

