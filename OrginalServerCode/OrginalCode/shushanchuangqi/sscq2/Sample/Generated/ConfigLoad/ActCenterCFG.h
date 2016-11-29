// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SActCenterCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CACTCENTERLOADER_H
#define _CACTCENTERLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SActCenterCFG
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

	/**
	IconAppearID
	**/
	UINT16	_IconAppearID;
}; // SActCenterCFG define end

//data loader for the excel table
class CActCenterLoader
{
public:
	std::vector<SActCenterCFG*> _vecData;

	~CActCenterLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

