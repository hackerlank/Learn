// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SLanghuanfudiSkillCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CLANGHUANFUDISKILLLOADER_H
#define _CLANGHUANFUDISKILLLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SLanghuanfudiSkillCFG
{
	/**
	技能 ID
	**/
	UINT32	_ID;

	/**
	技能 名
	**/
	string	_Name;

	/**
	技能使用次数
	**/
	UINT32	_UseTimes;

	/**
	使用距离
	**/
	UINT16	_Distance;

	/**
	冷却时间
	**/
	UINT16	_CoolDown;

	/**
	地图ID
	**/
	UINT32	_MapId;

	/**
	自己说话
	**/
	string	_MeTalk;

	/**
	对方说话
	**/
	string	_OtherTalk;
}; // SLanghuanfudiSkillCFG define end

//data loader for the excel table
class CLanghuanfudiSkillLoader
{
public:
	std::vector<SLanghuanfudiSkillCFG*> _vecData;

	~CLanghuanfudiSkillLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

