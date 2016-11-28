// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SWorldBossPrizeCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CWORLDBOSSPRIZELOADER_H
#define _CWORLDBOSSPRIZELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SWorldBossPrizeCFG
{
	/**
	排名区间上
	**/
	UINT16	_RankTop;

	/**
	排名区间下
	**/
	UINT16	_RankBottom;

	/**
	奖励类型
	**/
	UINT16	_PrizeType;

	/**
	BossID
	**/
	UINT16	_BossID;

	/**
	奖励名称
	**/
	string	_BossName;

	/**
	奖励资源类型1
	**/
	UINT16	_Resource1Type;

	/**
	值
	**/
	UINT32	_ResourceValue1;

	/**
	奖励资源类型2
	**/
	UINT16	_Resource2Type;

	/**
	值
	**/
	UINT16	_ResourceValue2;

	/**
	奖励经验值
	**/
	UINT32	_GivenExp;

	/**
	奖励道具1
	**/
	string	_GivenItem;
}; // SWorldBossPrizeCFG define end

//data loader for the excel table
class CWorldBossPrizeLoader
{
public:
	std::vector<SWorldBossPrizeCFG*> _vecData;

	~CWorldBossPrizeLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

