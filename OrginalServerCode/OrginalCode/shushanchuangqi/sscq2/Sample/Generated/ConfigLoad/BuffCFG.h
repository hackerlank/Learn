// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBuffCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CBUFFLOADER_H
#define _CBUFFLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SBuffCFG
{
	/**
	BUFF ID
	**/
	UINT16	_ID;

	/**
	BUFF名字
	**/
	string	_Name;

	/**
	BUFF描述
	**/
	string	_Desc;

	/**
	BUFF效果时间描述
	**/
	string	_DescTime;

	/**
	生效的战斗类型
	**/
	UINT8	_BattleType;

	/**
	效果类型
	**/
	UINT8	_EffectType;

	/**
	效果参数
	**/
	string	_Param1;

	/**
	使用次数
	**/
	UINT32	_UseTime;

	/**
	效果时间
	**/
	UINT32	_Time;

	/**
	最大叠加时间
	**/
	UINT32	_TotalTime;

	/**
	buff图标
	**/
	string	_Icon;

	/**
	地图限制
	**/
	string	_MapID;

	/**
	是否显示
	**/
	UINT8	_Show;

	/**
	覆盖buff
	**/
	string	_IsSame;
}; // SBuffCFG define end

//data loader for the excel table
class CBuffLoader
{
public:
	std::vector<SBuffCFG*> _vecData;

	~CBuffLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

