// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SMallCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CMALLLOADER_H
#define _CMALLLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SMallCFG
{
	/**
	商品编号
	**/
	UINT32	_Id;

	/**
	物品ID
	**/
	UINT16	_ItemId;

	/**
	商品名称
	**/
	string	_Name;

	/**
	物品数量
	**/
	UINT16	_ItemNum;

	/**
	所属商城
	**/
	UINT8	_Type;

	/**
	货币类型
	**/
	UINT8	_MoneyType;

	/**
	价格
	**/
	UINT32	_Price;

	/**
	VIP等级限制
	**/
	UINT8	_VIP;

	/**
	商品图标
	**/
	UINT16	_Icon;

	/**
	每日购买次数限制
	**/
	string	_DayCntLimit;

	/**
	可购买条件
	**/
	UINT16	_AvailableCon;
}; // SMallCFG define end

//data loader for the excel table
class CMallLoader
{
public:
	std::vector<SMallCFG*> _vecData;

	~CMallLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

