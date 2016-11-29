// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SPageCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CPAGELOADER_H
#define _CPAGELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SPageCFG
{
	/**
	切页ID
	**/
	UINT16	_ID;

	/**
	切页名称
	**/
	string	_Name;

	/**
	切页说明
	**/
	string	_TIPS;

	/**
	切页图片
	**/
	string	_Icon;
}; // SPageCFG define end

//data loader for the excel table
class CPageLoader
{
public:
	std::vector<SPageCFG*> _vecData;

	~CPageLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

