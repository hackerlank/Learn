// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STaskDropCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CTASKDROPLOADER_H
#define _CTASKDROPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct STaskDropCFG
{
	/**
	怪物ID
	**/
	UINT16	_ID;

	/**
	怪物名称
	**/
	string	_Name;

	/**
	任务ID
	**/
	UINT16	_TaskID;

	/**
	道具ID
	**/
	UINT16	_ItemID;

	/**
	道具名称
	**/
	string	_ItemName;

	/**
	掉落概率(万分位)
	**/
	UINT16	_DropRate;
}; // STaskDropCFG define end

//data loader for the excel table
class CTaskDropLoader
{
public:
	std::vector<STaskDropCFG*> _vecData;

	~CTaskDropLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

