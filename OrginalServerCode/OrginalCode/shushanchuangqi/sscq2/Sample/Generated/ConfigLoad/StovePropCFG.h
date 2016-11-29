// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SStovePropCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSTOVEPROPLOADER_H
#define _CSTOVEPROPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SStovePropCFG
{
	/**
	鼎ID
	**/
	UINT8	_ID;

	/**
	鼎名字
	**/
	string	_Name;

	/**
	图标
	**/
	UINT16	_Icon;

	/**
	模型
	**/
	UINT16	_Model;

	/**
	初始配方
	**/
	string	_BornFires;

	/**
	解锁条件
	**/
	UINT16	_GetCondId;
}; // SStovePropCFG define end

//data loader for the excel table
class CStovePropLoader
{
public:
	std::vector<SStovePropCFG*> _vecData;

	~CStovePropLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

