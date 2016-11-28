// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDrawCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDRAWLOADER_H
#define _CDRAWLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDrawCFG
{
	/**
	主角等级
	**/
	UINT16	_PlayerLevel;

	/**
	求签类型
	**/
	UINT16	_Type;

	/**
	基础类型
	**/
	UINT16	_BasicType;

	/**
	基础概率
	**/
	UINT16	_BasicPercent;

	/**
	基础值下
	**/
	UINT16	_BasicValue1;

	/**
	基础值上
	**/
	UINT16	_BasicValue2;

	/**
	惊喜类型
	**/
	UINT16	_UnexpectedType;

	/**
	惊喜值下
	**/
	UINT16	_UnexpectedValue1;

	/**
	惊喜值上
	**/
	UINT16	_UnexpectedValue2;

	/**
	消耗银币数
	**/
	UINT32	_DrawSilverPrice;

	/**
	消耗仙石数
	**/
	UINT16	_DrawGoldPrice;
}; // SDrawCFG define end

//data loader for the excel table
class CDrawLoader
{
public:
	std::vector<SDrawCFG*> _vecData;

	~CDrawLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

