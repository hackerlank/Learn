// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SStoveFireLevelCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSTOVEFIRELEVELLOADER_H
#define _CSTOVEFIRELEVELLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SStoveFireLevelCFG
{
	/**
	品数
	**/
	UINT8	_Level;

	/**
	品名
	**/
	string	_Name;

	/**
	颜色
	**/
	UINT8	_Color;

	/**
	出现概率
	**/
	UINT16	_Appear;

	/**
	增加下区间
	**/
	UINT8	_LowLine;

	/**
	增加上区间
	**/
	UINT32	_MaxLine;
}; // SStoveFireLevelCFG define end

//data loader for the excel table
class CStoveFireLevelLoader
{
public:
	std::vector<SStoveFireLevelCFG*> _vecData;

	~CStoveFireLevelLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

