// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuildLevelCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGUILDLEVELLOADER_H
#define _CGUILDLEVELLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGuildLevelCFG
{
	/**
	等级
	**/
	UINT8	_Level;

	/**
	升级所需总经验
	**/
	UINT32	_Exp;

	/**
	本级经验
	**/
	UINT32	_OriginExp;

	/**
	供奉奖励
	**/
	string	_Award;

	/**
	建筑等级上限
	**/
	UINT8	_Tower;

	/**
	灵山购买数量
	**/
	UINT16	_LingBuyLimit;
}; // SGuildLevelCFG define end

//data loader for the excel table
class CGuildLevelLoader
{
public:
	std::vector<SGuildLevelCFG*> _vecData;

	~CGuildLevelLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

