// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGodMonsterDayPkgCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGODMONSTERDAYPKGLOADER_H
#define _CGODMONSTERDAYPKGLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGodMonsterDayPkgCFG
{
	/**
	每日礼包ID
	**/
	UINT8	_ID;

	/**
	神兽贡献需求
	**/
	UINT32	_DayScore;

	/**
	礼包描述
	**/
	string	_Desc;

	/**
	礼包内容
	**/
	string	_Content;
}; // SGodMonsterDayPkgCFG define end

//data loader for the excel table
class CGodMonsterDayPkgLoader
{
public:
	std::vector<SGodMonsterDayPkgCFG*> _vecData;

	~CGodMonsterDayPkgLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

