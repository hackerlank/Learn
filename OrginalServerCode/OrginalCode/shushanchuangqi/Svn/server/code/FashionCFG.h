// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFashionCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFASHIONLOADER_H
#define _CFASHIONLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFashionCFG
{
	/**
	炼化等级
	**/
	UINT16	_Level;

	/**
	炼化材料ID
	**/
	UINT16	_Material;

	/**
	材料数量
	**/
	UINT16	_Number;

	/**
	升级经验
	**/
	UINT32	_Exp;

	/**
	单次炼化经验
	**/
	UINT32	_Each_exp;
}; // SFashionCFG define end

//data loader for the excel table
class CFashionLoader
{
public:
	std::vector<SFashionCFG*> _vecData;

	~CFashionLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

