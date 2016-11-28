// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLingShanCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CLINGSHANLOADER_H
#define _CLINGSHANLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SLingShanCFG
{
	/**
	活动id
	**/
	UINT16	_ActID;

	/**
	棋盘id
	**/
	UINT16	_MapID;

	/**
	初始化格子
	**/
	string	_BornID;

	/**
	初始化人数
	**/
	UINT16	_InitPlayerCnt;

	/**
	标准人数
	**/
	UINT16	_TotalPlayerCnt;

	/**
	填充玩家轮数
	**/
	UINT16	_SpawPlayerTurns;

	/**
	填充玩家人数
	**/
	UINT16	_SpawPlayerCnt;

	/**
	刷新宝箱轮数
	**/
	UINT16	_SpawBoxTurns;

	/**
	初始化大宝箱格子
	**/
	UINT16	_BornBigID;

	/**
	大宝箱id
	**/
	UINT32	_GodBoxID;

	/**
	大宝箱采集物id
	**/
	UINT16	_GodBoxModelID;

	/**
	普通宝箱id
	**/
	UINT32	_NormalBoxID;

	/**
	普通宝箱采集物id
	**/
	UINT16	_NormalBoxModelID;

	/**
	参与奖
	**/
	string	_PlayAward;
}; // SLingShanCFG define end

//data loader for the excel table
class CLingShanLoader
{
public:
	std::vector<SLingShanCFG*> _vecData;

	~CLingShanLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

