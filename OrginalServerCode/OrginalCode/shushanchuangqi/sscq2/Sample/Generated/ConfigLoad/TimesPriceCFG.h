// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STimesPriceCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CTIMESPRICELOADER_H
#define _CTIMESPRICELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct STimesPriceCFG
{
	/**
	购买次数
	**/
	UINT32	_BoughtTimes;

	/**
	英雄副本购买价格
	**/
	UINT32	_HeroDungeon;

	/**
	历险副本购买价格
	**/
	UINT32	_AdventureDungeon;

	/**
	斗剑购买次数价格
	**/
	UINT32	_Arena;

	/**
	摇钱树礼券购买
	**/
	UINT32	_MoneyTree;

	/**
	遥控色子价格
	**/
	UINT16	_CtrlDice;

	/**
	转向卡价格
	**/
	UINT16	_ComeBack;

	/**
	圣陵买命
	**/
	UINT16	_RichLife;

	/**
	圣陵进入价格
	**/
	UINT16	_RichTimes;

	/**
	历练购买次数价格
	**/
	UINT16	_LilianTimes;
}; // STimesPriceCFG define end

//data loader for the excel table
class CTimesPriceLoader
{
public:
	std::vector<STimesPriceCFG*> _vecData;

	~CTimesPriceLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

