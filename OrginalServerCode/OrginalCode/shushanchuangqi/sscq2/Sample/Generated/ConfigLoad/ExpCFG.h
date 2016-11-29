// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SExpCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CEXPLOADER_H
#define _CEXPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SExpCFG
{
	/**
	等级
	**/
	UINT8	_Level;

	/**
	升级经验
	**/
	UINT64	_Exp;

	/**
	世界boss系数1
	**/
	UINT16	_WC1;

	/**
	世界boss系数2
	**/
	UINT16	_WC2;

	/**
	打坐基础经验
	**/
	UINT16	_SitBasicExp;

	/**
	打坐资源类型
	**/
	UINT8	_SitBasicResourceType;

	/**
	打坐基础资源值
	**/
	UINT16	_SitBasicResourceValue;

	/**
	九疑鼎等级加成
	**/
	UINT16	_StoveC;

	/**
	九疑鼎玩家协助加成
	**/
	UINT16	_StoveHelperAddition;

	/**
	升级提示
	**/
	string	_LevelUpInfo;
}; // SExpCFG define end

//data loader for the excel table
class CExpLoader
{
public:
	std::vector<SExpCFG*> _vecData;

	~CExpLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

