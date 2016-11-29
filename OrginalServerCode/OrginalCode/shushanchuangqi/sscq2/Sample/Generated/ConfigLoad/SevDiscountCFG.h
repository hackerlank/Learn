// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSevDiscountCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSEVDISCOUNTLOADER_H
#define _CSEVDISCOUNTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SSevDiscountCFG
{
	/**
	天数
	**/
	UINT16	_Day;

	/**
	原价
	**/
	UINT16	_Price;

	/**
	折扣价
	**/
	UINT16	_Discount;

	/**
	折扣
	**/
	UINT16	_Agio;

	/**
	奖励
	**/
	string	_Reward;
}; // SSevDiscountCFG define end

//data loader for the excel table
class CSevDiscountLoader
{
public:
	std::vector<SSevDiscountCFG*> _vecData;

	~CSevDiscountLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

