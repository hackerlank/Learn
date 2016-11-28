// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SShipCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSHIPLOADER_H
#define _CSHIPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SShipCFG
{
	/**
	ID
	**/
	UINT8	_ID;

	/**
	船的类型ID
	**/
	UINT8	_TypeID;

	/**
	各等级ID
	**/
	UINT16	_Number;

	/**
	船的名字
	**/
	string	_Name;

	/**
	船的品质
	**/
	UINT8	_Color;

	/**
	免费刷新概率
	**/
	UINT16	_FreeChance;

	/**
	仙石刷新概率
	**/
	UINT16	_MoneyChance;

	/**
	运送时间
	**/
	UINT16	_Time;

	/**
	满船的奖励
	**/
	UINT16	_Award;

	/**
	被劫1次奖励
	**/
	UINT16	_Award1;

	/**
	被劫2次奖励
	**/
	UINT16	_Award2;

	/**
	被劫3次奖励
	**/
	UINT16	_Award3;

	/**
	好友护送奖励
	**/
	UINT16	_ProtectAward;

	/**
	劫船奖励
	**/
	UINT16	_RobAward;

	/**
	运船Buff
	**/
	UINT16	_Buff;
}; // SShipCFG define end

//data loader for the excel table
class CShipLoader
{
public:
	std::vector<SShipCFG*> _vecData;

	~CShipLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

