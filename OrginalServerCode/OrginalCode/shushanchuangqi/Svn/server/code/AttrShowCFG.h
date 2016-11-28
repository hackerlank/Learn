// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SAttrShowCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CATTRSHOWLOADER_H
#define _CATTRSHOWLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SAttrShowCFG
{
	/**
	清单ID
	**/
	UINT8	_List_ID;

	/**
	属性ID
	**/
	UINT8	_Attr_ID;

	/**
	属性名称（长）
	**/
	string	_Attr_Name;

	/**
	属性名称（短）
	**/
	string	_Attr_Name1;

	/**
	显示模式
	**/
	UINT8	_Show_Mod;

	/**
	显示切页
	**/
	UINT8	_Show_Page;

	/**
	切内分区
	**/
	UINT8	_Page_Part;

	/**
	区内位序
	**/
	UINT8	_Part_Num;

	/**
	显示格式
	**/
	string	_Show_Form;

	/**
	显示文字1
	**/
	string	_Show_Tip_1;

	/**
	显示文字2
	**/
	string	_Show_Tip_2;

	/**
	显示文字2所需属性
	**/
	string	_Tip_Need_Attr;

	/**
	战斗力
	**/
	UINT32	_Battle_Points;
}; // SAttrShowCFG define end

//data loader for the excel table
class CAttrShowLoader
{
public:
	std::vector<SAttrShowCFG*> _vecData;

	~CAttrShowLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

