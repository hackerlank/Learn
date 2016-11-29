// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SArenaCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CARENALOADER_H
#define _CARENALOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SArenaCFG
{
	/**
	段位
	**/
	UINT8	_id;

	/**
	段位名称
	**/
	string	_Name;

	/**
	保级条件
	**/
	UINT8	_byKeepLevelDays;

	/**
	保级奖励ID
	**/
	UINT32	_dwKeepLevelLoot;

	/**
	段位宝箱ID
	**/
	UINT32	_dwLevelLoot;

	/**
	奖励名次
	**/
	UINT8	_byAwardNum;

	/**
	名次奖励ID
	**/
	string	_strAwardLoot;

	/**
	挑战胜利声望
	**/
	UINT16	_wVictorFame;

	/**
	挑战失败声望
	**/
	UINT16	_wFailFame;

	/**
	挑战胜利分
	**/
	UINT16	_wVictorScore;

	/**
	挑战失败分
	**/
	UINT16	_wFailScore;

	/**
	额外积分
	**/
	string	_strExtraScore;

	/**
	晋级比例
	**/
	UINT8	_byLevelUpRate;

	/**
	降级比例
	**/
	UINT8	_byLevelDwonRate;
}; // SArenaCFG define end

//data loader for the excel table
class CArenaLoader
{
public:
	std::vector<SArenaCFG*> _vecData;

	~CArenaLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

