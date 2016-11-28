// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     STavernCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CTAVERNLOADER_H
#define _CTAVERNLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct STavernCFG
{
	/**
	酒馆Id
	**/
	UINT16	_TemplateId;

	/**
	酒馆名称
	**/
	string	_Name;

	/**
	解锁等级
	**/
	UINT16	_Condition;

	/**
	酒馆品质
	**/
	UINT16	_TavernLevel;

	/**
	酒馆底图
	**/
	UINT16	_TavernPIC;

	/**
	散仙1
	**/
	UINT16	_Hero1;

	/**
	缩放比例
	**/
	float	_Hero1Zoom;

	/**
	散仙1招募条件
	**/
	UINT16	_Hero1GetConId;

	/**
	散仙2
	**/
	UINT16	_Hero2;

	/**
	缩放比例
	**/
	float	_Hero2Zoom;

	/**
	散仙2招募条件
	**/
	UINT16	_Hero2GetConId;

	/**
	散仙3
	**/
	UINT16	_Hero3;

	/**
	缩放比例
	**/
	float	_Hero3Zoom;

	/**
	散仙3招募条件
	**/
	UINT16	_Hero3GetConId;

	/**
	散仙4
	**/
	UINT16	_Hero4;

	/**
	缩放比例
	**/
	float	_Hero4Zoom;

	/**
	散仙4招募条件
	**/
	UINT16	_Hero4GetConId;
}; // STavernCFG define end

//data loader for the excel table
class CTavernLoader
{
public:
	std::vector<STavernCFG*> _vecData;

	~CTavernLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

