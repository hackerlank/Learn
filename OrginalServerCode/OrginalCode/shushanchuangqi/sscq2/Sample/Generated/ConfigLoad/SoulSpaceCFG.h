// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSoulSpaceCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSOULSPACELOADER_H
#define _CSOULSPACELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SSoulSpaceCFG
{
	/**
	编号
	**/
	UINT32	_ID;

	/**
	类型
	**/
	UINT32	_TypeID;

	/**
	等级
	**/
	UINT32	_Level;

	/**
	名称
	**/
	string	_Name;

	/**
	需求主角等级
	**/
	UINT32	_NeedLevel;

	/**
	升级货币类型
	**/
	UINT32	_NeedMoneyType;

	/**
	升级货币数量
	**/
	UINT32	_NeedMoneyValue;

	/**
	附加属性
	**/
	string	_Attrib;
}; // SSoulSpaceCFG define end

//data loader for the excel table
class CSoulSpaceLoader
{
public:
	std::vector<SSoulSpaceCFG*> _vecData;

	~CSoulSpaceLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

