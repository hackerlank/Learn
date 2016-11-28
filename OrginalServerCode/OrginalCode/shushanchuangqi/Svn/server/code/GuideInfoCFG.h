// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGuideInfoCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGUIDEINFOLOADER_H
#define _CGUIDEINFOLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGuideInfoCFG
{
	/**
	ICONID
	**/
	UINT8	_ID;

	/**
	任务ID
	**/
	UINT32	_TaskId;

	/**
	步骤ID
	**/
	UINT8	_GuideStep;

	/**
	文字
	**/
	string	_GuideInfo;

	/**
	NPC头像
	**/
	string	_NpcIcon;
}; // SGuideInfoCFG define end

//data loader for the excel table
class CGuideInfoLoader
{
public:
	std::vector<SGuideInfoCFG*> _vecData;

	~CGuideInfoLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

