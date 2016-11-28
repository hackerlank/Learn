// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFighterFindCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFIGHTERFINDLOADER_H
#define _CFIGHTERFINDLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFighterFindCFG
{
	/**
	编号
	**/
	UINT16	_ID;

	/**
	寻仙分类
	**/
	UINT8	_Scene;

	/**
	仙石出现概率
	**/
	float	_GoldRandom;

	/**
	礼券出现概率
	**/
	float	_CouponRandom;

	/**
	银币出现概率
	**/
	float	_SilverRandom;

	/**
	奖励散仙机缘
	**/
	string	_FighterProp;

	/**
	奖励物品
	**/
	string	_PriceItem;
}; // SFighterFindCFG define end

//data loader for the excel table
class CFighterFindLoader
{
public:
	std::vector<SFighterFindCFG*> _vecData;

	~CFighterFindLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

