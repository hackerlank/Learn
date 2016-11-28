// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuardEMeiLevelCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGUARDEMEILEVELLOADER_H
#define _CGUARDEMEILEVELLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGuardEMeiLevelCFG
{
	/**
	波数
	**/
	UINT16	_GroupId;

	/**
	关卡Id
	**/
	UINT16	_LevelId;

	/**
	怪物组
	**/
	string	_MonsterGroup;

	/**
	奖励掉落包
	**/
	UINT16	_LootId;

	/**
	奖励预览
	**/
	string	_RewardReview;

	/**
	掉落增益
	**/
	string	_LootBuff;
}; // SGuardEMeiLevelCFG define end

//data loader for the excel table
class CGuardEMeiLevelLoader
{
public:
	std::vector<SGuardEMeiLevelCFG*> _vecData;

	~CGuardEMeiLevelLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

