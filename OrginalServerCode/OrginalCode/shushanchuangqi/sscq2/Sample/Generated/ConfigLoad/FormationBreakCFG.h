// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFormationBreakCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFORMATIONBREAKLOADER_H
#define _CFORMATIONBREAKLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFormationBreakCFG
{
	/**
	阵图Id
	**/
	UINT16	_ID;

	/**
	阵图名称
	**/
	string	_Name;

	/**
	需要等级
	**/
	UINT8	_RequiredLevel;

	/**
	怪物序列
	**/
	string	_MonsterTeam;

	/**
	通关奖励
	**/
	string	_Reward;
}; // SFormationBreakCFG define end

//data loader for the excel table
class CFormationBreakLoader
{
public:
	std::vector<SFormationBreakCFG*> _vecData;

	~CFormationBreakLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

