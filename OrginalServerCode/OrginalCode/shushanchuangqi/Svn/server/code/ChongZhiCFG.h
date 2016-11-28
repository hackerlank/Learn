// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SChongZhiCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCHONGZHILOADER_H
#define _CCHONGZHILOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SChongZhiCFG
{
	/**
	商品编号
	**/
	UINT32	_Id;

	/**
	仙石包名称
	**/
	string	_Name;

	/**
	仙石数
	**/
	UINT32	_Amount;

	/**
	商品图标
	**/
	string	_Icon1;

	/**
	首冲礼券返利
	**/
	string	_Gift;

	/**
	标签
	**/
	string	_Icon2;

	/**
	说明文字
	**/
	string	_Tips;

	/**
	对应Item表
	**/
	UINT32	_ItemID;
}; // SChongZhiCFG define end

//data loader for the excel table
class CChongZhiLoader
{
public:
	std::vector<SChongZhiCFG*> _vecData;

	~CChongZhiLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

