// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBattleArrayCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CBATTLEARRAYLOADER_H
#define _CBATTLEARRAYLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SBattleArrayCFG
{
	/**
	阵id
	**/
	UINT16	_ID;

	/**
	阵图名
	**/
	string	_Name;

	/**
	阵图资源
	**/
	UINT16	_Image;

	/**
	阵图名称美术字
	**/
	UINT16	_NamePic;

	/**
	地图Id
	**/
	UINT16	_MapId;

	/**
	需要等级
	**/
	UINT16	_RequiredLevel;

	/**
	前置阵ID
	**/
	UINT16	_PreID;

	/**
	通关奖励
	**/
	string	_PassPrize;

	/**
	阵图特性描述
	**/
	string	_Des;
}; // SBattleArrayCFG define end

//data loader for the excel table
class CBattleArrayLoader
{
public:
	std::vector<SBattleArrayCFG*> _vecData;

	~CBattleArrayLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

