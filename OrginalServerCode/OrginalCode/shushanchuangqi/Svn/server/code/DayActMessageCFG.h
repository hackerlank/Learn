// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDayActMessageCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDAYACTMESSAGELOADER_H
#define _CDAYACTMESSAGELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDayActMessageCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	活动类型
	**/
	UINT8	_ActType;

	/**
	活动Id
	**/
	string	_DayActId;

	/**
	周
	**/
	UINT8	_WeekDay;

	/**
	月
	**/
	UINT8	_Moth;

	/**
	天
	**/
	UINT8	_MothDay;

	/**
	预告时间
	**/
	string	_AppearTime;

	/**
	正式开始时间
	**/
	string	_BeginTime;

	/**
	结束时间
	**/
	string	_EndTime;

	/**
	活动图标
	**/
	UINT32	_Icon;
}; // SDayActMessageCFG define end

//data loader for the excel table
class CDayActMessageLoader
{
public:
	std::vector<SDayActMessageCFG*> _vecData;

	~CDayActMessageLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

