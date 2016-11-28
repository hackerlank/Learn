// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SMainIconCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CMAINICONLOADER_H
#define _CMAINICONLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SMainIconCFG
{
	/**
	id
	**/
	UINT16	_id;

	/**
	ICON模块名
	**/
	string	_data;

	/**
	ICON描述
	**/
	string	_descript;

	/**
	开放类型
	**/
	UINT16	_type;

	/**
	出现位置
	**/
	UINT16	_index;

	/**
	层级
	**/
	UINT16	_display;

	/**
	IconAppearId
	**/
	UINT16	_iconid;

	/**
	显示位置
	**/
	UINT16	_layoutid;
}; // SMainIconCFG define end

//data loader for the excel table
class CMainIconLoader
{
public:
	std::vector<SMainIconCFG*> _vecData;

	~CMainIconLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

