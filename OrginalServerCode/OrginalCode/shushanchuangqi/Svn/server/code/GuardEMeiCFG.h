// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuardEMeiCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGUARDEMEILOADER_H
#define _CGUARDEMEILOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGuardEMeiCFG
{
	/**
	关卡Id
	**/
	UINT16	_LevelId;

	/**
	名称
	**/
	string	_Name;

	/**
	美术字Id
	**/
	UINT16	_NamePic;

	/**
	开放等级
	**/
	UINT16	_RequiredLevel;

	/**
	前置关卡
	**/
	UINT16	_PreLevel;

	/**
	奖励预览
	**/
	string	_RewardReview;

	/**
	通关奖励
	**/
	string	_FinishReward;

	/**
	最大波数
	**/
	UINT8	_MaxNum;
}; // SGuardEMeiCFG define end

//data loader for the excel table
class CGuardEMeiLoader
{
public:
	std::vector<SGuardEMeiCFG*> _vecData;

	~CGuardEMeiLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

