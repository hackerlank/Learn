// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SActivityCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CACTIVITYLOADER_H
#define _CACTIVITYLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SActivityCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	活跃度
	**/
	UINT16	_Activity;

	/**
	宝箱ID
	**/
	UINT32	_LootID;

	/**
	额外奖励VIP需求
	**/
	UINT8	_VIPLevel;

	/**
	额外VIP奖励
	**/
	UINT32	_VIPLootID;
}; // SActivityCFG define end

//data loader for the excel table
class CActivityLoader
{
public:
	std::vector<SActivityCFG*> _vecData;

	~CActivityLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

