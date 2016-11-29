// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SWorldBossCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CWORLDBOSSLOADER_H
#define _CWORLDBOSSLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SWorldBossCFG
{
	/**
	BossId
	**/
	UINT16	_BossId;

	/**
	Boss名
	**/
	string	_BossName;

	/**
	地图ID
	**/
	UINT16	_MapId;

	/**
	地图名
	**/
	string	_MapName;

	/**
	Boss位置
	**/
	string	_BossPosition;

	/**
	玩家出生区域
	**/
	string	_BirthPlace;
}; // SWorldBossCFG define end

//data loader for the excel table
class CWorldBossLoader
{
public:
	std::vector<SWorldBossCFG*> _vecData;

	~CWorldBossLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

