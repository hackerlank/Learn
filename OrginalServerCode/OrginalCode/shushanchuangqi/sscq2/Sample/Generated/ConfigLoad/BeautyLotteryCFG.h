// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBeautyLotteryCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CBEAUTYLOTTERYLOADER_H
#define _CBEAUTYLOTTERYLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SBeautyLotteryCFG
{
	/**
	抽奖类型
	**/
	UINT16	_PrizeType;

	/**
	名字
	**/
	string	_Name;

	/**
	消耗数量
	**/
	UINT32	_Cost;

	/**
	必出掉落Id
	**/
	UINT16	_DropID;

	/**
	随机掉落Id
	**/
	UINT16	_RandomDropID;

	/**
	随机掉落次数
	**/
	UINT32	_Count;
}; // SBeautyLotteryCFG define end

//data loader for the excel table
class CBeautyLotteryLoader
{
public:
	std::vector<SBeautyLotteryCFG*> _vecData;

	~CBeautyLotteryLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

