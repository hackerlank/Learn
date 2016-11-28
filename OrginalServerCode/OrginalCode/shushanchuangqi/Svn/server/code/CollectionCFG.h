// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCollectionCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCOLLECTIONLOADER_H
#define _CCOLLECTIONLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SCollectionCFG
{
	/**
	收藏ID
	**/
	UINT16	_ID;

	/**
	收藏大类
	**/
	UINT16	_Type;

	/**
	收藏子类1
	**/
	UINT16	_Type1;

	/**
	收藏子类2
	**/
	UINT16	_Type2;

	/**
	职业显示
	**/
	UINT8	_Carreer;

	/**
	收藏名
	**/
	string	_Name;

	/**
	收藏描述
	**/
	string	_Desc;

	/**
	事件id
	**/
	UINT16	_EventID;

	/**
	收藏点
	**/
	UINT16	_CP;
}; // SCollectionCFG define end

//data loader for the excel table
class CCollectionLoader
{
public:
	std::vector<SCollectionCFG*> _vecData;

	~CCollectionLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

