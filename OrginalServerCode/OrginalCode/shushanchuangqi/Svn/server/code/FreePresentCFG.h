// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFreePresentCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFREEPRESENTLOADER_H
#define _CFREEPRESENTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFreePresentCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	奖励
	**/
	string	_Content;

	/**
	达成解封等级
	**/
	UINT16	_Condition;

	/**
	礼物的名称
	**/
	string	_Title;

	/**
	默认赠言
	**/
	string	_Msg;

	/**
	图片
	**/
	UINT8	_img;
}; // SFreePresentCFG define end

//data loader for the excel table
class CFreePresentLoader
{
public:
	std::vector<SFreePresentCFG*> _vecData;

	~CFreePresentLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

