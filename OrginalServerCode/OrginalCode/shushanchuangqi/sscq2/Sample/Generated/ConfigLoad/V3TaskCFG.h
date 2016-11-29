// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SV3TaskCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CV3TASKLOADER_H
#define _CV3TASKLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SV3TaskCFG
{
	/**
	任务id
	**/
	UINT32	_ID;

	/**
	任务集市id
	**/
	UINT32	_TaskID;

	/**
	任务名称
	**/
	string	_TaskName;

	/**
	步骤
	**/
	UINT8	_StepID;

	/**
	奖励id
	**/
	UINT32	_PrizeID;

	/**
	奖励名称
	**/
	string	_PrizeName;

	/**
	任务条件id
	**/
	UINT32	_CondID;

	/**
	任务描述
	**/
	string	_CondName;
}; // SV3TaskCFG define end

//data loader for the excel table
class CV3TaskLoader
{
public:
	std::vector<SV3TaskCFG*> _vecData;

	~CV3TaskLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

