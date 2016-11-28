// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SMonsterGroupCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CMONSTERGROUPLOADER_H
#define _CMONSTERGROUPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SMonsterGroupCFG
{
	/**
	怪物组ID
	**/
	UINT16	_ID;

	/**
	主怪ID(地图显示)
	**/
	UINT16	_MainMonster;

	/**
	怪物组名
	**/
	string	_Name;

	/**
	怪物组品质
	**/
	UINT8	_uQuality;

	/**
	类型
	**/
	UINT8	_uType;

	/**
	战斗类型
	**/
	UINT8	_FightType;

	/**
	等级
	**/
	UINT16	_wLevel;

	/**
	经验
	**/
	UINT32	_uExp;

	/**
	掉落包
	**/
	string	_strDropID;

	/**
	怪物阵形
	**/
	string	_strFighters;

	/**
	多波怪物组
	**/
	string	_MonsterClass;

	/**
	参战阵灵
	**/
	UINT32	_addPet;

	/**
	参战NPC
	**/
	string	_addNPC;

	/**
	强插技能
	**/
	string	_AddSkill;

	/**
	怪物AI
	**/
	UINT16	_AI;

	/**
	是否可见
	**/
	UINT8	_Visual;

	/**
	待机对白
	**/
	string	_dialog;

	/**
	发现对白
	**/
	string	_findDialog;

	/**
	战斗地图
	**/
	UINT16	_FightMap;
}; // SMonsterGroupCFG define end

//data loader for the excel table
class CMonsterGroupLoader
{
public:
	std::vector<SMonsterGroupCFG*> _vecData;

	~CMonsterGroupLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

