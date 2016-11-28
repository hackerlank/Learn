// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDayActCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDAYACTLOADER_H
#define _CDAYACTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDayActCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	显示名称
	**/
	string	_Name;

	/**
	活动类型
	**/
	UINT8	_ActType;

	/**
	是否互斥
	**/
	UINT8	_SpecialType;

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
	开服强行开启天数
	**/
	UINT8	_OpenDay;

	/**
	程序准备时间
	**/
	string	_AlarmTime;

	/**
	预告时间
	**/
	string	_ReadyTime;

	/**
	正式开始时间
	**/
	string	_BeginTime;

	/**
	结束时间
	**/
	string	_EndTime;

	/**
	附加参数1
	**/
	UINT32	_dwParam;

	/**
	附加参数2
	**/
	string	_strParam;

	/**
	脚本
	**/
	string	_Script;

	/**
	是否跨服
	**/
	bool	_CrossServer;

	/**
	重启检测
	**/
	bool	_IsRestartCheck;

	/**
	活动图标
	**/
	UINT32	_Icon;

	/**
	参与条件
	**/
	string	_Limit;

	/**
	活动奖励
	**/
	string	_Reward;

	/**
	活动说明
	**/
	string	_QqRemind;

	/**
	活动说明
	**/
	string	_Description;
}; // SDayActCFG define end

//data loader for the excel table
class CDayActLoader
{
public:
	std::vector<SDayActCFG*> _vecData;

	~CDayActLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

