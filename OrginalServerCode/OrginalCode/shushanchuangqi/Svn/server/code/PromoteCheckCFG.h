// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SPromoteCheckCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CPROMOTECHECKLOADER_H
#define _CPROMOTECHECKLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SPromoteCheckCFG
{
	/**
	序列号
	**/
	UINT8	_ID;

	/**
	类型
	**/
	UINT8	_Type;

	/**
	标题名
	**/
	string	_Name;

	/**
	检测点
	**/
	UINT8	_CheckPoint;

	/**
	否/未满足
	**/
	string	_NotSatisfied;

	/**
	是/满足提示
	**/
	string	_Meet;

	/**
	提升跳转界面
	**/
	string	_Guide;

	/**
	按钮名字
	**/
	string	_ButtonName;

	/**
	标题图标
	**/
	UINT8	_Icon;

	/**
	变强途径显示文字
	**/
	string	_unMeet;
}; // SPromoteCheckCFG define end

//data loader for the excel table
class CPromoteCheckLoader
{
public:
	std::vector<SPromoteCheckCFG*> _vecData;

	~CPromoteCheckLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

