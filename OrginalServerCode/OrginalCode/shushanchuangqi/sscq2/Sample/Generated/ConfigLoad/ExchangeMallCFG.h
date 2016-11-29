// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SExchangeMallCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CEXCHANGEMALLLOADER_H
#define _CEXCHANGEMALLLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SExchangeMallCFG
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
	数量
	**/
	UINT16	_ItemCount;

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
	出现条件
	**/
	UINT16	_AppearCon;

	/**
	可购买条件
	**/
	UINT16	_AvailableCon;

	/**
	可购买次数
	**/
	UINT16	_StoreNum;
}; // SExchangeMallCFG define end

//data loader for the excel table
class CExchangeMallLoader
{
public:
	std::vector<SExchangeMallCFG*> _vecData;

	~CExchangeMallLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

