// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SXiHeTruckCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CXIHETRUCKLOADER_H
#define _CXIHETRUCKLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SXiHeTruckCFG
{
	/**
	货物编号
	**/
	UINT8	_ID;

	/**
	需求道具
	**/
	string	_Goods;

	/**
	货物奖励
	**/
	string	_Award;

	/**
	帮派资金奖励
	**/
	UINT32	_GuildMoney;

	/**
	货物价值
	**/
	UINT16	_Value;

	/**
	货物等级
	**/
	string	_Level;
}; // SXiHeTruckCFG define end

//data loader for the excel table
class CXiHeTruckLoader
{
public:
	std::vector<SXiHeTruckCFG*> _vecData;

	~CXiHeTruckLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

