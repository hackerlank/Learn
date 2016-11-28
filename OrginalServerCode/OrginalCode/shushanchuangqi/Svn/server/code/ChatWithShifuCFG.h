// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SChatWithShifuCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCHATWITHSHIFULOADER_H
#define _CCHATWITHSHIFULOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SChatWithShifuCFG
{
	/**
	编号
	**/
	UINT16	_Num;

	/**
	师门1衙门2
	**/
	UINT8	_Type;

	/**
	tip内容
	**/
	string	_Tip;

	/**
	注释
	**/
	string	_Descripition;
}; // SChatWithShifuCFG define end

//data loader for the excel table
class CChatWithShifuLoader
{
public:
	std::vector<SChatWithShifuCFG*> _vecData;

	~CChatWithShifuLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

