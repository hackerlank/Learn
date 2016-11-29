// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SComdldanlucostCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCOMDLDANLUCOSTLOADER_H
#define _CCOMDLDANLUCOSTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SComdldanlucostCFG
{
	/**
	位置顺序
	**/
	UINT8	_Sequence;

	/**
	等级限制
	**/
	UINT8	_playerLevel;

	/**
	vip等级限制
	**/
	UINT8	_Vip;

	/**
	九疑鼎等级限制
	**/
	UINT8	_Jiuyidinglevel;

	/**
	花费银币
	**/
	UINT32	_Silver;

	/**
	花费礼券
	**/
	UINT16	_Coupon;

	/**
	花费仙石
	**/
	UINT16	_Gold;
}; // SComdldanlucostCFG define end

//data loader for the excel table
class CComdldanlucostLoader
{
public:
	std::vector<SComdldanlucostCFG*> _vecData;

	~CComdldanlucostLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

