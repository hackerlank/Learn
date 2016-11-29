// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFighterLevelUPCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFIGHTERLEVELUPLOADER_H
#define _CFIGHTERLEVELUPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFighterLevelUPCFG
{
	/**
	ID
	**/
	UINT8	_ID;

	/**
	消耗类型
	**/
	UINT16	_CostType;

	/**
	消耗数额
	**/
	UINT32	_Cost;
}; // SFighterLevelUPCFG define end

//data loader for the excel table
class CFighterLevelUPLoader
{
public:
	std::vector<SFighterLevelUPCFG*> _vecData;

	~CFighterLevelUPLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

