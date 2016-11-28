// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSearchMapCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSEARCHMAPLOADER_H
#define _CSEARCHMAPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SSearchMapCFG
{
	/**
	场景id
	**/
	UINT8	_ID;

	/**
	名字
	**/
	string	_Name;

	/**
	场景等级
	**/
	UINT8	_Level;

	/**
	场景底图
	**/
	string	_Map;

	/**
	boss头像
	**/
	UINT32	_Boss;

	/**
	怪物组
	**/
	string	_MonsterGroup;

	/**
	预计银币
	**/
	UINT32	_Money;

	/**
	预计修为
	**/
	UINT32	_Pexp;

	/**
	标准通关时间S
	**/
	UINT16	_ClearTime;

	/**
	标准通关奖励
	**/
	UINT16	_TimeAward;

	/**
	立即完成花费仙石
	**/
	UINT16	_FinishCost;

	/**
	立即完成奖励
	**/
	UINT16	_FinishAward;
}; // SSearchMapCFG define end

//data loader for the excel table
class CSearchMapLoader
{
public:
	std::vector<SSearchMapCFG*> _vecData;

	~CSearchMapLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

