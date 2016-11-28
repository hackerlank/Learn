// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SPromoteNewCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CPROMOTENEWLOADER_H
#define _CPROMOTENEWLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SPromoteNewCFG
{
	/**
	序列号
	**/
	UINT8	_ID;

	/**
	类型
	**/
	UINT8	_Type;

	/**
	分页位置
	**/
	UINT8	_Page;

	/**
	名字
	**/
	string	_PageName;

	/**
	包含功能点
	**/
	string	_Include;

	/**
	起始等级
	**/
	UINT8	_startLevel;

	/**
	结束等级
	**/
	UINT8	_EndLevel;
}; // SPromoteNewCFG define end

//data loader for the excel table
class CPromoteNewLoader
{
public:
	std::vector<SPromoteNewCFG*> _vecData;

	~CPromoteNewLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

