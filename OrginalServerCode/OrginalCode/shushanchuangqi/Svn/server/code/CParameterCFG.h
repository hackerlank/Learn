﻿// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCParameterCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCPARAMETERLOADER_H
#define _CCPARAMETERLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SCParameterCFG
{
	/**
	参数ID
	**/
	UINT32	_ID;
}; // SCParameterCFG define end

//data loader for the excel table
class CCParameterLoader
{
public:
	std::vector<SCParameterCFG*> _vecData;

	~CCParameterLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

