// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SConsumeTypeCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCONSUMETYPELOADER_H
#define _CCONSUMETYPELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SConsumeTypeCFG
{
	/**
	参数ID
	**/
	UINT16	_ID;
}; // SConsumeTypeCFG define end

//data loader for the excel table
class CConsumeTypeLoader
{
public:
	std::vector<SConsumeTypeCFG*> _vecData;

	~CConsumeTypeLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

