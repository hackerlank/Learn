// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDaily_yamentaskCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDAILY_YAMENTASKLOADER_H
#define _CDAILY_YAMENTASKLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDaily_yamentaskCFG
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
	免费任务刷新概率和对应银币奖励
	**/
	string	_Chance_Award;

	/**
	付费任务刷新概率和对应银币奖励
	**/
	string	_Chance_Award_Gold;
}; // SDaily_yamentaskCFG define end

//data loader for the excel table
class CDaily_yamentaskLoader
{
public:
	std::vector<SDaily_yamentaskCFG*> _vecData;

	~CDaily_yamentaskLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

