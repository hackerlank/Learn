// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SIconConfigCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CICONCONFIGLOADER_H
#define _CICONCONFIGLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SIconConfigCFG
{
	/**
	功能开启id
	**/
	UINT16	_ID;

	/**
	目标达成等级
	**/
	UINT16	_level;
}; // SIconConfigCFG define end

//data loader for the excel table
class CIconConfigLoader
{
public:
	std::vector<SIconConfigCFG*> _vecData;

	~CIconConfigLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

