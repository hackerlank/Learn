// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuildBattleSkillCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGUILDBATTLESKILLLOADER_H
#define _CGUILDBATTLESKILLLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGuildBattleSkillCFG
{
	/**
	技能ID
	**/
	UINT16	_ID;

	/**
	技能名称
	**/
	string	_Name;

	/**
	技能描述
	**/
	string	_Desc;

	/**
	对应BUFFID
	**/
	UINT16	_BuffID;

	/**
	货币类型
	**/
	string	_PriceType;

	/**
	价格
	**/
	UINT16	_Price;
}; // SGuildBattleSkillCFG define end

//data loader for the excel table
class CGuildBattleSkillLoader
{
public:
	std::vector<SGuildBattleSkillCFG*> _vecData;

	~CGuildBattleSkillLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

