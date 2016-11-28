// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDataUploadCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDATAUPLOADLOADER_H
#define _CDATAUPLOADLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDataUploadCFG
{
	/**
	数据统计ID
	**/
	UINT32	_ID;

	/**
	类型
	**/
	UINT16	_Type;

	/**
	事件id
	**/
	UINT16	_EventID;

	/**
	category值
	**/
	string	_category;

	/**
	action值
	**/
	string	_action;

	/**
	参数
	**/
	UINT16	_Para;
}; // SDataUploadCFG define end

//data loader for the excel table
class CDataUploadLoader
{
public:
	std::vector<SDataUploadCFG*> _vecData;

	~CDataUploadLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

