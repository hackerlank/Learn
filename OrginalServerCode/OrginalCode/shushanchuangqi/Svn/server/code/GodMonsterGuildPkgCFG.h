// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGodMonsterGuildPkgCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGODMONSTERGUILDPKGLOADER_H
#define _CGODMONSTERGUILDPKGLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGodMonsterGuildPkgCFG
{
	/**
	帮派排行ID
	**/
	UINT8	_ID;

	/**
	下成长区间
	**/
	UINT16	_FieldDown;

	/**
	上成长区间
	**/
	UINT16	_FieldUp;

	/**
	帮派排行描述
	**/
	string	_Desc;

	/**
	奖励内容
	**/
	string	_Content;
}; // SGodMonsterGuildPkgCFG define end

//data loader for the excel table
class CGodMonsterGuildPkgLoader
{
public:
	std::vector<SGodMonsterGuildPkgCFG*> _vecData;

	~CGodMonsterGuildPkgLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

