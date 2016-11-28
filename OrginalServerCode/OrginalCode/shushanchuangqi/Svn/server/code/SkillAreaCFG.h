// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSkillAreaCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSKILLAREALOADER_H
#define _CSKILLAREALOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SSkillAreaCFG
{
	/**
	范围 ID
	**/
	UINT16	_wID;

	/**
	范围 名
	**/
	string	_strName;

	/**
	类型
	**/
	UINT8	_bySelectType;

	/**
	概率选择方式
	**/
	UINT8	_byRateType;

	/**
	指定目标ID
	**/
	string	_strFighterID;

	/**
	是否有主目标
	**/
	UINT8	_byHasMainTarget;

	/**
	方向
	**/
	UINT8	_bySide;

	/**
	范围
	**/
	string	_strArea;

	/**
	系数
	**/
	string	_strFactor;

	/**
	重复系数
	**/
	string	_strRepeatFactor;
}; // SSkillAreaCFG define end

//data loader for the excel table
class CSkillAreaLoader
{
public:
	std::vector<SSkillAreaCFG*> _vecData;

	~CSkillAreaLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

