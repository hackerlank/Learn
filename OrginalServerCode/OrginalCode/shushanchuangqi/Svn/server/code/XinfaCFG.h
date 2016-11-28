// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SXinfaCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CXINFALOADER_H
#define _CXINFALOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SXinfaCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	心法名
	**/
	string	_Name;

	/**
	类型
	**/
	UINT8	_Type;

	/**
	颜色
	**/
	UINT8	_Color;

	/**
	元神力
	**/
	UINT8	_Limit;

	/**
	效果
	**/
	UINT16	_Effect;

	/**
	需要物品
	**/
	string	_NeedItem;

	/**
	描述
	**/
	string	_Description;

	/**
	备注
	**/
	string	_Remark;
}; // SXinfaCFG define end

//data loader for the excel table
class CXinfaLoader
{
public:
	std::vector<SXinfaCFG*> _vecData;

	~CXinfaLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

