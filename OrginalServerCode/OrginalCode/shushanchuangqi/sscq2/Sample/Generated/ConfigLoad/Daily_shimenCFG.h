// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDaily_shimenCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDAILY_SHIMENLOADER_H
#define _CDAILY_SHIMENLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDaily_shimenCFG
{
	/**
	清修等级
	**/
	UINT16	_Level;

	/**
	需要的清修点
	**/
	UINT16	_Cost;

	/**
	每日领取修为
	**/
	UINT16	_Retrun;

	/**
	称号
	**/
	UINT8	_Title;

	/**
	升级任务
	**/
	UINT16	_Task;

	/**
	注释
	**/
	string	_Descripition;

	/**
	经验加成
	**/
	UINT16	_Exp;
}; // SDaily_shimenCFG define end

//data loader for the excel table
class CDaily_shimenLoader
{
public:
	std::vector<SDaily_shimenCFG*> _vecData;

	~CDaily_shimenLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

