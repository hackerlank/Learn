// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SMapCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CMAPLOADER_H
#define _CMAPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SMapCFG
{
	/**
	地图ID
	**/
	UINT16	_ID;

	/**
	名称
	**/
	string	_Name;

	/**
	类型
	**/
	UINT8	_Type;

	/**
	客户端类型
	**/
	UINT8	_Type2;

	/**
	配置文件
	**/
	string	_ConfigFile;

	/**
	客户端配置文件
	**/
	string	_ClientFile;

	/**
	是否多层
	**/
	bool	_IsFar;

	/**
	势力
	**/
	UINT8	_Force;

	/**
	最低进入等级
	**/
	UINT16	_Leastlevel;

	/**
	是否为安全区
	**/
	bool	_IsSafe;

	/**
	战斗地图
	**/
	UINT16	_FightMap;

	/**
	掉落ID
	**/
	UINT16	_DropID;

	/**
	场景技能
	**/
	string	_SkillID;

	/**
	区域最高人数
	**/
	UINT16	_MaxPlayer;

	/**
	区域健康人数
	**/
	UINT16	_SMaxPlayer;

	/**
	副本名字动画
	**/
	UINT16	_MapNameAppear;

	/**
	背景图
	**/
	string	_LoadingBGMap;
}; // SMapCFG define end

//data loader for the excel table
class CMapLoader
{
public:
	std::vector<SMapCFG*> _vecData;

	~CMapLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

