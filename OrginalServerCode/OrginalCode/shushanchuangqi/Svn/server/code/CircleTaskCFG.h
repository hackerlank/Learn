// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCircleTaskCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCIRCLETASKLOADER_H
#define _CCIRCLETASKLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SCircleTaskCFG
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
	任务
	**/
	string	_Task_ID;

	/**
	星级刷出概率
	**/
	string	_Chance_Award;

	/**
	1星完成奖励
	**/
	string	_Award;

	/**
	完成所有环奖励
	**/
	string	_FinishAward;
}; // SCircleTaskCFG define end

//data loader for the excel table
class CCircleTaskLoader
{
public:
	std::vector<SCircleTaskCFG*> _vecData;

	~CCircleTaskLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

