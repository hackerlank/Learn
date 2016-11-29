// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SStarPageCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSTARPAGELOADER_H
#define _CSTARPAGELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SStarPageCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	名称
	**/
	string	_Name;

	/**
	兽魂种类
	**/
	UINT8	_PageType;

	/**
	篇章编号
	**/
	UINT8	_PageLevel;

	/**
	篇章奖励
	**/
	string	_Award;
}; // SStarPageCFG define end

//data loader for the excel table
class CStarPageLoader
{
public:
	std::vector<SStarPageCFG*> _vecData;

	~CStarPageLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

