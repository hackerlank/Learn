// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SItemGuideCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CITEMGUIDELOADER_H
#define _CITEMGUIDELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SItemGuideCFG
{
	/**
	引导ID
	**/
	UINT16	_ID;

	/**
	文字说明
	**/
	string	_Tips;

	/**
	引导类型
	**/
	UINT8	_Type;

	/**
	引导标签
	**/
	UINT32	_Tag;

	/**
	标签名
	**/
	string	_TagName;

	/**
	跳转限制
	**/
	UINT16	_SkipLimit;

	/**
	小图标
	**/
	UINT8	_Icon;
}; // SItemGuideCFG define end

//data loader for the excel table
class CItemGuideLoader
{
public:
	std::vector<SItemGuideCFG*> _vecData;

	~CItemGuideLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

