// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SStoveFireCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSTOVEFIRELOADER_H
#define _CSTOVEFIRELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SStoveFireCFG
{
	/**
	配方ID
	**/
	UINT16	_ID;

	/**
	配方名字
	**/
	string	_Name;

	/**
	序列
	**/
	UINT16	_Position;

	/**
	使用次数
	**/
	UINT8	_LimitTimes;

	/**
	品质
	**/
	UINT8	_Color;

	/**
	元气值上限
	**/
	UINT32	_VigorMax;

	/**
	鼎经验
	**/
	UINT32	_StoveExp;

	/**
	是否乘等级系数
	**/
	UINT8	_LevelC;

	/**
	消耗物
	**/
	string	_RequiredItem;

	/**
	产出物
	**/
	string	_RewardItem;
}; // SStoveFireCFG define end

//data loader for the excel table
class CStoveFireLoader
{
public:
	std::vector<SStoveFireCFG*> _vecData;

	~CStoveFireLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

