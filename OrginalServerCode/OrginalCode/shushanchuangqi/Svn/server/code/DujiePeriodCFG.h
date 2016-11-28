// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDujiePeriodCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDUJIEPERIODLOADER_H
#define _CDUJIEPERIODLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDujiePeriodCFG
{
	/**
	Id
	**/
	UINT8	_PeriodId;

	/**
	渡劫等级
	**/
	UINT16	_DujieLevel;

	/**
	时期名称
	**/
	string	_PeriodName;

	/**
	名称颜色
	**/
	UINT8	_NameColor;

	/**
	具体信息
	**/
	string	_Info;
}; // SDujiePeriodCFG define end

//data loader for the excel table
class CDujiePeriodLoader
{
public:
	std::vector<SDujiePeriodCFG*> _vecData;

	~CDujiePeriodLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

