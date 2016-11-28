// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STitleCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CTITLELOADER_H
#define _CTITLELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct STitleCFG
{
	/**
	称号ID
	**/
	UINT16	_ID;

	/**
	称号类型
	**/
	UINT16	_Type;

	/**
	称号名
	**/
	string	_Name;

	/**
	称号描述
	**/
	string	_Desc;

	/**
	激活成就ID
	**/
	UINT16	_RequireID;

	/**
	资源id
	**/
	UINT16	_Assets;

	/**
	属性id
	**/
	UINT16	_PropID;

	/**
	时限性
	**/
	UINT32	_Time;
}; // STitleCFG define end

//data loader for the excel table
class CTitleLoader
{
public:
	std::vector<STitleCFG*> _vecData;

	~CTitleLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

