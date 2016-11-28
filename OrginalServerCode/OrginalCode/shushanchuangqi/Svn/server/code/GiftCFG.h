// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SGiftCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CGIFTLOADER_H
#define _CGIFTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SGiftCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	类型
	**/
	UINT8	_Type;

	/**
	类型2
	**/
	UINT8	_Type2;

	/**
	
	**/
	string	_Type3;

	/**
	名称
	**/
	string	_GiftItem;

	/**
	标题
	**/
	string	_Title;
}; // SGiftCFG define end

//data loader for the excel table
class CGiftLoader
{
public:
	std::vector<SGiftCFG*> _vecData;

	~CGiftLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

