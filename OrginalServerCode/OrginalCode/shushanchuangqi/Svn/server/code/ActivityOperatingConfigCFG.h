// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SActivityOperatingConfigCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CACTIVITYOPERATINGCONFIGLOADER_H
#define _CACTIVITYOPERATINGCONFIGLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SActivityOperatingConfigCFG
{
	/**
	活动配置ID
	**/
	UINT16	_ID;

	/**
	索引表
	**/
	string	_TableID;

	/**
	活动名
	**/
	string	_Name;

	/**
	活动类型
	**/
	UINT16	_Type;

	/**
	活动类型参数1
	**/
	string	_TypePara1;

	/**
	活动类型参数2
	**/
	string	_TypePara2;

	/**
	活动类型参数4
	**/
	string	_TypePara4;

	/**
	活动类型参数5
	**/
	string	_TypePara5;

	/**
	活动类型参数3
	**/
	string	_TypePara3;

	/**
	邮件标题id
	**/
	UINT16	_MailTitle;

	/**
	邮件内容id
	**/
	UINT16	_MailContent;
}; // SActivityOperatingConfigCFG define end

//data loader for the excel table
class CActivityOperatingConfigLoader
{
public:
	std::vector<SActivityOperatingConfigCFG*> _vecData;

	~CActivityOperatingConfigLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

