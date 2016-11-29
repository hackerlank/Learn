// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SRichCellCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CRICHCELLLOADER_H
#define _CRICHCELLLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SRichCellCFG
{
	/**
	格子Id
	**/
	UINT8	_ID;

	/**
	空格权重
	**/
	UINT16	_EmptyCellWeight;

	/**
	小宝箱权重
	**/
	UINT16	_SmallBoxWeight;

	/**
	大宝箱权重
	**/
	UINT16	_BigBoxWeight;

	/**
	超级宝箱权重
	**/
	UINT16	_SuperBoxWeight;

	/**
	普通怪权重
	**/
	UINT16	_NormalWeight;

	/**
	精英怪权重
	**/
	UINT16	_EliteWeight;

	/**
	Boss怪权重
	**/
	UINT16	_BossWeight;

	/**
	三消权重
	**/
	UINT16	_ChrushWeight;

	/**
	拼图权重
	**/
	UINT16	_PicWeight;

	/**
	抽卡权重
	**/
	UINT16	_DrawWeight;

	/**
	随机权重
	**/
	UINT16	_RandomWeight;

	/**
	X轴坐标
	**/
	UINT16	_Xposition;

	/**
	Y轴坐标
	**/
	UINT16	_Ypisition;
}; // SRichCellCFG define end

//data loader for the excel table
class CRichCellLoader
{
public:
	std::vector<SRichCellCFG*> _vecData;

	~CRichCellLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

