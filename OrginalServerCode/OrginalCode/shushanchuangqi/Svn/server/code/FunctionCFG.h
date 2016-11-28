// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFunctionCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFUNCTIONLOADER_H
#define _CFUNCTIONLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFunctionCFG
{
	/**
	索引Id
	**/
	UINT16	_ID;
}; // SFunctionCFG define end

//data loader for the excel table
class CFunctionLoader
{
public:
	std::vector<SFunctionCFG*> _vecData;

	~CFunctionLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

