// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SAttachSpiritCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CATTACHSPIRITLOADER_H
#define _CATTACHSPIRITLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SAttachSpiritCFG
{
	/**
	注灵等级
	**/
	UINT8	_SoulLevel;

	/**
	每次点击消耗魂魄值
	**/
	UINT32	_SoulCost;

	/**
	获取注灵点数最小值
	**/
	UINT32	_AttachMin;

	/**
	获取注灵点数最大值
	**/
	UINT32	_AttachMax;
}; // SAttachSpiritCFG define end

//data loader for the excel table
class CAttachSpiritLoader
{
public:
	std::vector<SAttachSpiritCFG*> _vecData;

	~CAttachSpiritLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

