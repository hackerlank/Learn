// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuildShopCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGUILDSHOPLOADER_H
#define _CGUILDSHOPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGuildShopCFG
{
	/**
	商品编号
	**/
	UINT32	_ID;

	/**
	物品
	**/
	string	_Item;

	/**
	价格
	**/
	UINT32	_Price;

	/**
	帮会等级
	**/
	UINT8	_GuildLevel;

	/**
	每日购买次数限制
	**/
	UINT16	_DayCntLimit;

	/**
	可购买条件
	**/
	UINT16	_AvailableCon;

	/**
	可购买次数
	**/
	UINT16	_StoreNum;
}; // SGuildShopCFG define end

//data loader for the excel table
class CGuildShopLoader
{
public:
	std::vector<SGuildShopCFG*> _vecData;

	~CGuildShopLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

