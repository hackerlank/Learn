// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLotteryCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CLOTTERYLOADER_H
#define _CLOTTERYLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SLotteryCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	个数
	**/
	UINT8	_Count;

	/**
	奖励
	**/
	string	_Content;

	/**
	排序
	**/
	UINT8	_Sort;
}; // SLotteryCFG define end

//data loader for the excel table
class CLotteryLoader
{
public:
	std::vector<SLotteryCFG*> _vecData;

	~CLotteryLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

