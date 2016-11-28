// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SAreaCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CAREALOADER_H
#define _CAREALOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SAreaCFG
{
	/**
	触发区域ID
	**/
	UINT16	_areaId;

	/**
	触发区域名称
	**/
	string	_areaName;

	/**
	资源类型
	**/
	UINT8	_AssetType;

	/**
	资源参数1
	**/
	UINT16	_AssetParam1;

	/**
	模型大小缩放
	**/
	float	_AssetAdjust;

	/**
	模型影子缩放
	**/
	float	_AssetShadow;

	/**
	安全区域
	**/
	UINT8	_IsSafe;

	/**
	踩上去是否删除
	**/
	UINT8	_IsDel;

	/**
	特效动画
	**/
	string	_Asset;

	/**
	消失效果
	**/
	string	_Disappear;
}; // SAreaCFG define end

//data loader for the excel table
class CAreaLoader
{
public:
	std::vector<SAreaCFG*> _vecData;

	~CAreaLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

