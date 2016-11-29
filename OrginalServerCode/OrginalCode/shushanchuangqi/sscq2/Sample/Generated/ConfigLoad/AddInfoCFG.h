// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SAddInfoCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CADDINFOLOADER_H
#define _CADDINFOLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SAddInfoCFG
{
	/**
	ID
	**/
	UINT8	_ID;

	/**
	说明
	**/
	string	_Tips;

	/**
	类型
	**/
	UINT8	_Type;

	/**
	默认值数据
	**/
	string	_DefaultData;
}; // SAddInfoCFG define end

//data loader for the excel table
class CAddInfoLoader
{
public:
	std::vector<SAddInfoCFG*> _vecData;

	~CAddInfoLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

