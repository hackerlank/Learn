// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSignInCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSIGNINLOADER_H
#define _CSIGNINLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SSignInCFG
{
	/**
	编号
	**/
	UINT16	_ID;

	/**
	累计签到次数
	**/
	UINT8	_SignIn;

	/**
	可获得奖励
	**/
	string	_Award;
}; // SSignInCFG define end

//data loader for the excel table
class CSignInLoader
{
public:
	std::vector<SSignInCFG*> _vecData;

	~CSignInLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

