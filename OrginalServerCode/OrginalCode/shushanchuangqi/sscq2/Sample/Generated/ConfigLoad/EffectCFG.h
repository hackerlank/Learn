// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SEffectCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CEFFECTLOADER_H
#define _CEFFECTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SEffectCFG
{
	/**
	流水号
	**/
	UINT8	_ID;

	/**
	效果类型
	**/
	UINT8	_EffectType;

	/**
	Buff表ID
	**/
	UINT16	_BuffID;

	/**
	UINT16
	**/
	UINT16	_EffectIcon;

	/**
	Buff名字
	**/
	string	_Name;

	/**
	Buff效果
	**/
	UINT32	_Effect;

	/**
	描述
	**/
	string	_Description;
}; // SEffectCFG define end

//data loader for the excel table
class CEffectLoader
{
public:
	std::vector<SEffectCFG*> _vecData;

	~CEffectLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

