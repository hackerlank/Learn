// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSkillTipsCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSKILLTIPSLOADER_H
#define _CSKILLTIPSLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SSkillTipsCFG
{
	/**
	AI ID
	**/
	UINT16	_ID;

	/**
	标题
	**/
	string	_Title;

	/**
	说明
	**/
	string	_Desc;
}; // SSkillTipsCFG define end

//data loader for the excel table
class CSkillTipsLoader
{
public:
	std::vector<SSkillTipsCFG*> _vecData;

	~CSkillTipsLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

