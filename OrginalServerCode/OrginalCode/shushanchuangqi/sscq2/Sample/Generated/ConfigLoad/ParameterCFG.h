// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SParameterCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CPARAMETERLOADER_H
#define _CPARAMETERLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SParameterCFG
{
	/**
	参数ID
	**/
	UINT32	_ID;

	/**
	名称
	**/
	string	_Name;

	/**
	参数值
	**/
	float	_Fvalue;

	/**
	参数字符串
	**/
	string	_Svalue;
}; // SParameterCFG define end

//data loader for the excel table
class CParameterLoader
{
public:
	std::vector<SParameterCFG*> _vecData;

	~CParameterLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

