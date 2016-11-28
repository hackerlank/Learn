// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SHelpCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CHELPLOADER_H
#define _CHELPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SHelpCFG
{
	/**
	帮助Id
	**/
	UINT16	_ID;

	/**
	帮助名称
	**/
	string	_Name;

	/**
	帮助名称图片
	**/
	UINT16	_NamePicId;

	/**
	功能名称
	**/
	string	_FunctionName;

	/**
	内容
	**/
	string	_StoveExp;
}; // SHelpCFG define end

//data loader for the excel table
class CHelpLoader
{
public:
	std::vector<SHelpCFG*> _vecData;

	~CHelpLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

