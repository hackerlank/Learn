// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuildTechCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGUILDTECHLOADER_H
#define _CGUILDTECHLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGuildTechCFG
{
	/**
	技能类别ID
	**/
	UINT32	_ID;

	/**
	属性ID
	**/
	string	_Attr_ID;

	/**
	技能等级
	**/
	UINT8	_Level;

	/**
	技能名
	**/
	string	_Name;

	/**
	所需贡献
	**/
	UINT32	_Cost;

	/**
	技能数值
	**/
	UINT32	_Value;

	/**
	角色等级限制
	**/
	UINT16	_RoleLevel;
}; // SGuildTechCFG define end

//data loader for the excel table
class CGuildTechLoader
{
public:
	std::vector<SGuildTechCFG*> _vecData;

	~CGuildTechLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

