// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSearchBuffCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSEARCHBUFFLOADER_H
#define _CSEARCHBUFFLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SSearchBuffCFG
{
	/**
	流水号
	**/
	UINT8	_ID;

	/**
	Buff表ID
	**/
	UINT16	_BuffID;

	/**
	Buff名字
	**/
	string	_Name;

	/**
	Buff效果
	**/
	UINT16	_Effect;

	/**
	每日使用次数
	**/
	UINT8	_DailyTimes;

	/**
	Buff使用间隔S
	**/
	UINT16	_BuffCD;

	/**
	描述
	**/
	string	_Description;
}; // SSearchBuffCFG define end

//data loader for the excel table
class CSearchBuffLoader
{
public:
	std::vector<SSearchBuffCFG*> _vecData;

	~CSearchBuffLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

