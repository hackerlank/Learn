// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGatherCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGATHERLOADER_H
#define _CGATHERLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGatherCFG
{
	/**
	采集物ID
	**/
	UINT16	_wGatherId;

	/**
	采集物名称
	**/
	string	_strName;

	/**
	资源类型
	**/
	UINT8	_AssetType;

	/**
	资源参数1
	**/
	UINT16	_AssetParam1;

	/**
	待机特效参数
	**/
	string	_AssetParam3;

	/**
	模型大小缩放
	**/
	float	_AssetAdjust;

	/**
	模型影子缩放
	**/
	float	_AssetShadow;

	/**
	出现特效
	**/
	UINT16	_ApearEffect;

	/**
	采集物扣除
	**/
	string	_strCost;

	/**
	采集时间
	**/
	UINT16	_wGatherTimer;

	/**
	采集物数量
	**/
	UINT16	_wGatherNum;

	/**
	采集之前的格子判定
	**/
	UINT8	_byEmptyPack;

	/**
	掉落Id
	**/
	UINT32	_dwDropId;

	/**
	需要对应任务才可以采集
	**/
	UINT8	_byIsTask;

	/**
	特效动画
	**/
	string	_Asset;

	/**
	消失效果
	**/
	string	_Disappear;

	/**
	是否可多人采集
	**/
	UINT8	_IsPublic;

	/**
	是否显示名字
	**/
	UINT8	_IsShowName;

	/**
	是否播放采集动作
	**/
	UINT8	_IsMotion;
}; // SGatherCFG define end

//data loader for the excel table
class CGatherLoader
{
public:
	std::vector<SGatherCFG*> _vecData;

	~CGatherLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

