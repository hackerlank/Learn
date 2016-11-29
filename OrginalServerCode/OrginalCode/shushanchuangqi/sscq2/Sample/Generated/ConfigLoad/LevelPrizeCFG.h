// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLevelPrizeCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CLEVELPRIZELOADER_H
#define _CLEVELPRIZELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SLevelPrizeCFG
{
	/**
	序号
	**/
	UINT16	_ID;

	/**
	活动id
	**/
	UINT16	_Type;

	/**
	等级
	**/
	UINT16	_Level;

	/**
	奖励
	**/
	string	_ItemPrize;
}; // SLevelPrizeCFG define end

//data loader for the excel table
class CLevelPrizeLoader
{
public:
	std::vector<SLevelPrizeCFG*> _vecData;

	~CLevelPrizeLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

