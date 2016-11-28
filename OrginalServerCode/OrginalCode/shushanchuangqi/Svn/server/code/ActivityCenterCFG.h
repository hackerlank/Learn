// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SActivityCenterCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CACTIVITYCENTERLOADER_H
#define _CACTIVITYCENTERLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SActivityCenterCFG
{
	/**
	活动ID
	**/
	UINT32	_ID;

	/**
	场次
	**/
	UINT8	_Index;

	/**
	名字
	**/
	string	_Name;

	/**
	公告时间
	**/
	string	_Alarm;

	/**
	准备时间
	**/
	UINT32	_Ready;

	/**
	开始时间
	**/
	UINT32	_Begin;

	/**
	结束时间
	**/
	UINT32	_End;

	/**
	是否同步GameServer
	**/
	UINT8	_bSync;

	/**
	活动公告前什么时候同步
	**/
	UINT32	_Sync;
}; // SActivityCenterCFG define end

//data loader for the excel table
class CActivityCenterLoader
{
public:
	std::vector<SActivityCenterCFG*> _vecData;

	~CActivityCenterLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

