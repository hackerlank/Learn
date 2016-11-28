// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGetCondCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGETCONDLOADER_H
#define _CGETCONDLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGetCondCFG
{
	/**
	条件ID
	**/
	UINT16	_ID;

	/**
	货币
	**/
	string	_Money;

	/**
	等级
	**/
	UINT32	_Level;

	/**
	物品
	**/
	string	_ItemID;

	/**
	通关副本
	**/
	string	_DungeonID;

	/**
	完成任务
	**/
	string	_TaskID;

	/**
	好友数量
	**/
	UINT32	_FriendCount;

	/**
	VIP等级
	**/
	UINT32	_VipLevel;

	/**
	当天充值
	**/
	UINT32	_Recharge;

	/**
	当天消费
	**/
	UINT32	_Consume;

	/**
	阵灵等级
	**/
	UINT32	_PetLevel;

	/**
	前置散仙
	**/
	string	_PreHero;

	/**
	需要职业
	**/
	UINT8	_NeedCareer;

	/**
	需要渡劫境界
	**/
	UINT8	_Dujie;

	/**
	帮派等级
	**/
	UINT8	_GuildLevel;

	/**
	需要渡劫境界
	**/
	UINT8	_DujieLevel;
}; // SGetCondCFG define end

//data loader for the excel table
class CGetCondLoader
{
public:
	std::vector<SGetCondCFG*> _vecData;

	~CGetCondLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

