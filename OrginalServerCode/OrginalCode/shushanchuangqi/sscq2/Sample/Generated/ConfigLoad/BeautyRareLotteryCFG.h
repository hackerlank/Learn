// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBeautyRareLotteryCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CBEAUTYRARELOTTERYLOADER_H
#define _CBEAUTYRARELOTTERYLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SBeautyRareLotteryCFG
{
	/**
	掉落id
	**/
	UINT16	_ID;

	/**
	掉落库
	**/
	UINT16	_Loots;

	/**
	是否稀有
	**/
	UINT8	_Rare;

	/**
	物品id
	**/
	UINT32	_ItemID;

	/**
	数量
	**/
	UINT32	_ItemCount;

	/**
	概率
	**/
	UINT32	_Probablity;
}; // SBeautyRareLotteryCFG define end

//data loader for the excel table
class CBeautyRareLotteryLoader
{
public:
	std::vector<SBeautyRareLotteryCFG*> _vecData;

	~CBeautyRareLotteryLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

