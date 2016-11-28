// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SItemTimeCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CITEMTIMELOADER_H
#define _CITEMTIMELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SItemTimeCFG
{
	/**
	限时ID
	**/
	UINT16	_ID;

	/**
	开始类型
	**/
	UINT8	_StartType;

	/**
	提示类型
	**/
	UINT8	_TipType;

	/**
	到期处理方式
	**/
	UINT8	_Disposal;

	/**
	时间限制类型
	**/
	UINT8	_DueType;

	/**
	剩余分钟
	**/
	UINT32	_RemTime;

	/**
	到期时间
	**/
	string	_ExpireTime;
}; // SItemTimeCFG define end

//data loader for the excel table
class CItemTimeLoader
{
public:
	std::vector<SItemTimeCFG*> _vecData;

	~CItemTimeLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

