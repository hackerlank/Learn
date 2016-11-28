// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSkinCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSKINLOADER_H
#define _CSKINLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SSkinCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	职业
	**/
	UINT8	_Job;

	/**
	性别
	**/
	UINT8	_Sex;

	/**
	时装id
	**/
	UINT8	_SkinId;

	/**
	名字
	**/
	string	_Name;

	/**
	附件id
	**/
	UINT16	_Appendix;
}; // SSkinCFG define end

//data loader for the excel table
class CSkinLoader
{
public:
	std::vector<SSkinCFG*> _vecData;

	~CSkinLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

