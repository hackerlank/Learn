// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDaily_shimentaskCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDAILY_SHIMENTASKLOADER_H
#define _CDAILY_SHIMENTASKLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDaily_shimentaskCFG
{
	/**
	等级段
	**/
	UINT16	_Level;

	/**
	最低等级
	**/
	UINT16	_Level_min;

	/**
	最高等级
	**/
	UINT16	_Level_max;

	/**
	白色任务库
	**/
	string	_Task_1;

	/**
	绿色任务库
	**/
	string	_Task_2;

	/**
	蓝色任务库
	**/
	string	_Task_3;

	/**
	紫色任务库
	**/
	string	_Task_4;

	/**
	橙色任务库
	**/
	string	_Task_5;

	/**
	任务
	**/
	string	_Task_ID;

	/**
	对任务的注释
	**/
	string	_Descripition;

	/**
	免费颜色概率和经验奖励
	**/
	string	_Chance_Award;

	/**
	付费颜色概率和经验奖励
	**/
	string	_Chance_Award_Gold;
}; // SDaily_shimentaskCFG define end

//data loader for the excel table
class CDaily_shimentaskLoader
{
public:
	std::vector<SDaily_shimentaskCFG*> _vecData;

	~CDaily_shimentaskLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

