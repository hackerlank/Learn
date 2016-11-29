// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGiftCenterCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGIFTCENTERLOADER_H
#define _CGIFTCENTERLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGiftCenterCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	图标
	**/
	UINT32	_Icon;

	/**
	模块名字
	**/
	string	_moduleName;

	/**
	类型
	**/
	UINT8	_Type;
}; // SGiftCenterCFG define end

//data loader for the excel table
class CGiftCenterLoader
{
public:
	std::vector<SGiftCenterCFG*> _vecData;

	~CGiftCenterLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

