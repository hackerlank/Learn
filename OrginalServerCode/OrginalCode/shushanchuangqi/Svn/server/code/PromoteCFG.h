// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SPromoteCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CPROMOTELOADER_H
#define _CPROMOTELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SPromoteCFG
{
	/**
	功能点
	**/
	UINT8	_ID;

	/**
	1~10级
	**/
	UINT32	_Level1;

	/**
	11~20级
	**/
	UINT32	_Level2;

	/**
	21~30级
	**/
	UINT32	_Level3;

	/**
	31~40级
	**/
	UINT32	_Level4;

	/**
	41~50级
	**/
	UINT32	_Level5;

	/**
	51~60级
	**/
	UINT32	_Level6;

	/**
	61~70级
	**/
	UINT32	_Level7;

	/**
	71~80级
	**/
	UINT32	_Level8;

	/**
	81~90级
	**/
	UINT32	_Level9;

	/**
	91~100级
	**/
	UINT32	_Level10;

	/**
	101~110级
	**/
	UINT32	_Level11;

	/**
	111~120级
	**/
	UINT32	_Level12;

	/**
	121~130级
	**/
	UINT32	_Level13;

	/**
	131~140级
	**/
	UINT32	_Level14;

	/**
	141~150级
	**/
	UINT32	_Level15;
}; // SPromoteCFG define end

//data loader for the excel table
class CPromoteLoader
{
public:
	std::vector<SPromoteCFG*> _vecData;

	~CPromoteLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

