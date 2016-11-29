// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLingShanMapCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CLINGSHANMAPLOADER_H
#define _CLINGSHANMAPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SLingShanMapCFG
{
	/**
	编号
	**/
	UINT16	_ID;

	/**
	棋盘类型
	**/
	UINT16	_Type;

	/**
	相邻编号
	**/
	string	_Adj;
}; // SLingShanMapCFG define end

//data loader for the excel table
class CLingShanMapLoader
{
public:
	std::vector<SLingShanMapCFG*> _vecData;

	~CLingShanMapLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

