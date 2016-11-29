// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SActivityOperatingCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CACTIVITYOPERATINGLOADER_H
#define _CACTIVITYOPERATINGLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SActivityOperatingCFG
{
	/**
	活动ID
	**/
	UINT16	_ID;

	/**
	活动类型
	**/
	UINT16	_Stye;

	/**
	活动性质
	**/
	UINT16	_TotalType;

	/**
	活动名
	**/
	string	_Name;

	/**
	活动排序
	**/
	UINT16	_SortOn;

	/**
	客户端用类型
	**/
	UINT16	_Client_Type;

	/**
	活动类型
	**/
	UINT16	_Type;

	/**
	活动配置id
	**/
	UINT16	_ConfigID;

	/**
	活动预告时间
	**/
	string	_Time1;

	/**
	活动开始时间
	**/
	string	_Time2;

	/**
	活动结束时间
	**/
	string	_Time3;

	/**
	活动保留时间
	**/
	string	_Time4;

	/**
	活动描述
	**/
	string	_Desc;

	/**
	活动ICON
	**/
	UINT16	_IconUrl;
}; // SActivityOperatingCFG define end

//data loader for the excel table
class CActivityOperatingLoader
{
public:
	std::vector<SActivityOperatingCFG*> _vecData;

	~CActivityOperatingLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

