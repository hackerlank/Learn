// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFightWordCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFIGHTWORDLOADER_H
#define _CFIGHTWORDLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFightWordCFG
{
	/**
	战斗结果
	**/
	UINT32	_ResultID;

	/**
	流水号
	**/
	UINT32	_Num;
}; // SFightWordCFG define end

//data loader for the excel table
class CFightWordLoader
{
public:
	std::vector<SFightWordCFG*> _vecData;

	~CFightWordLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

