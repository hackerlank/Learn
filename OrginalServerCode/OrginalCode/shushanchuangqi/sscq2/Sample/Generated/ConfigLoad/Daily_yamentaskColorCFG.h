// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDaily_yamentaskColorCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDAILY_YAMENTASKCOLORLOADER_H
#define _CDAILY_YAMENTASKCOLORLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDaily_yamentaskColorCFG
{
	/**
	任务ID
	**/
	UINT16	_TaskId;

	/**
	任务等级
	**/
	UINT16	_level;

	/**
	颜色
	**/
	UINT8	_Color;

	/**
	掉落包
	**/
	UINT32	_LootId;

	/**
	银币奖励
	**/
	UINT32	_Exp;
}; // SDaily_yamentaskColorCFG define end

//data loader for the excel table
class CDaily_yamentaskColorLoader
{
public:
	std::vector<SDaily_yamentaskColorCFG*> _vecData;

	~CDaily_yamentaskColorLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

