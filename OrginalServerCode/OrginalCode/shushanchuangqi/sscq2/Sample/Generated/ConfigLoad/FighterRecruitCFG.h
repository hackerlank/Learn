// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFighterRecruitCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFIGHTERRECRUITLOADER_H
#define _CFIGHTERRECRUITLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFighterRecruitCFG
{
	/**
	散仙ID
	**/
	UINT16	_ID;

	/**
	招募条件
	**/
	UINT16	_CondID;

	/**
	所属组合
	**/
	string	_Combination;

	/**
	需要机缘点
	**/
	UINT8	_NeedPoint;

	/**
	声望兑换机缘比例
	**/
	UINT32	_Exchange;

	/**
	机缘任务
	**/
	UINT16	_ChanceTask;

	/**
	出现等级
	**/
	UINT8	_AppearLevel;

	/**
	散仙介绍
	**/
	string	_Introduce;
}; // SFighterRecruitCFG define end

//data loader for the excel table
class CFighterRecruitLoader
{
public:
	std::vector<SFighterRecruitCFG*> _vecData;

	~CFighterRecruitLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

