// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDaily_title_shimenCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDAILY_TITLE_SHIMENLOADER_H
#define _CDAILY_TITLE_SHIMENLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDaily_title_shimenCFG
{
	/**
	称号等级
	**/
	UINT16	_Level;

	/**
	儒的称号
	**/
	string	_RU;

	/**
	释的称号
	**/
	string	_SHI;

	/**
	道的称号
	**/
	string	_DAO;

	/**
	墨的称号
	**/
	string	_MO;
}; // SDaily_title_shimenCFG define end

//data loader for the excel table
class CDaily_title_shimenLoader
{
public:
	std::vector<SDaily_title_shimenCFG*> _vecData;

	~CDaily_title_shimenLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

