// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SExclusionCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CEXCLUSIONLOADER_H
#define _CEXCLUSIONLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SExclusionCFG
{
	/**
	功能Id
	**/
	UINT8	_Level;

	/**
	扫荡
	**/
	UINT8	_One;

	/**
	打坐
	**/
	UINT8	_Two;

	/**
	副本
	**/
	UINT8	_Three;

	/**
	世界Boss
	**/
	UINT8	_Four;

	/**
	锁妖塔
	**/
	UINT8	_Five;

	/**
	公会战
	**/
	UINT8	_Six;

	/**
	阵营战
	**/
	UINT8	_Seven;

	/**
	采集
	**/
	UINT8	_Eight;

	/**
	历练
	**/
	UINT8	_Nine;

	/**
	斗剑
	**/
	UINT8	_Ten;

	/**
	破阵
	**/
	UINT8	_Eleven;

	/**
	组队副本
	**/
	UINT8	_Twelve;

	/**
	论剑
	**/
	UINT8	_Thirteen;

	/**
	琅环福地
	**/
	UINT8	_Forteen;

	/**
	九疑鼎
	**/
	UINT8	_Fifteen;
}; // SExclusionCFG define end

//data loader for the excel table
class CExclusionLoader
{
public:
	std::vector<SExclusionCFG*> _vecData;

	~CExclusionLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

