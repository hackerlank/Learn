// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STaskActionTypeCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CTASKACTIONTYPELOADER_H
#define _CTASKACTIONTYPELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct STaskActionTypeCFG
{
	/**
	类型
	**/
	UINT16	_type;

	/**
	类型参数
	**/
	UINT16	_typepara;

	/**
	打开界面名
	**/
	string	_moduleName;

	/**
	格式化文字
	**/
	string	_format;
}; // STaskActionTypeCFG define end

//data loader for the excel table
class CTaskActionTypeLoader
{
public:
	std::vector<STaskActionTypeCFG*> _vecData;

	~CTaskActionTypeLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

