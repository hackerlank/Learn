// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCittaSignetCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCITTASIGNETLOADER_H
#define _CCITTASIGNETLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SCittaSignetCFG
{
	/**
	印记ID
	**/
	UINT32	_ID;

	/**
	套装ID
	**/
	UINT32	_TypeID;

	/**
	编号
	**/
	string	_Name;

	/**
	印记名称
	**/
	string	_IdName;

	/**
	印记品质
	**/
	UINT8	_Quality;
}; // SCittaSignetCFG define end

//data loader for the excel table
class CCittaSignetLoader
{
public:
	std::vector<SCittaSignetCFG*> _vecData;

	~CCittaSignetLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

