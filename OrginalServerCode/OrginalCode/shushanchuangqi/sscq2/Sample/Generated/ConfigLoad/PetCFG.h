// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SPetCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CPETLOADER_H
#define _CPETLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SPetCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	名字
	**/
	string	_Name;

	/**
	解锁条件
	**/
	UINT32	_Unlock;

	/**
	FighterPropID
	**/
	UINT32	_FighterProp;

	/**
	跟随距离
	**/
	UINT16	_Distance;
}; // SPetCFG define end

//data loader for the excel table
class CPetLoader
{
public:
	std::vector<SPetCFG*> _vecData;

	~CPetLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

