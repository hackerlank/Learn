// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCittaSignetSuitCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCITTASIGNETSUITLOADER_H
#define _CCITTASIGNETSUITLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SCittaSignetSuitCFG
{
	/**
	套装编号
	**/
	UINT32	_ID;

	/**
	印记ID
	**/
	string	_SignetID;

	/**
	套装等级
	**/
	UINT8	_Level;

	/**
	激活数量1
	**/
	UINT8	_Number1;

	/**
	套装1属性编号
	**/
	UINT32	_AttrID1;

	/**
	激活数量2
	**/
	UINT8	_Number2;

	/**
	套装2属性编号
	**/
	UINT32	_AttrID2;

	/**
	激活数量3
	**/
	UINT8	_Number3;

	/**
	套装3属性编号
	**/
	UINT32	_AttrID3;

	/**
	激活数量4
	**/
	UINT8	_Number4;

	/**
	套装4属性编号
	**/
	UINT32	_AttrID4;
}; // SCittaSignetSuitCFG define end

//data loader for the excel table
class CCittaSignetSuitLoader
{
public:
	std::vector<SCittaSignetSuitCFG*> _vecData;

	~CCittaSignetSuitLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

