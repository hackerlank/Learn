// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SWeakGuideCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CWEAKGUIDELOADER_H
#define _CWEAKGUIDELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SWeakGuideCFG
{
	/**
	ICONID
	**/
	UINT8	_ID;

	/**
	触发类型
	**/
	UINT8	_Type;

	/**
	触发参数
	**/
	UINT32	_Parameter;

	/**
	触发参数2
	**/
	UINT32	_value;
}; // SWeakGuideCFG define end

//data loader for the excel table
class CWeakGuideLoader
{
public:
	std::vector<SWeakGuideCFG*> _vecData;

	~CWeakGuideLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

