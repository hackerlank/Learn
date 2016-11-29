// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SCampCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CCAMPLOADER_H
#define _CCAMPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SCampCFG
{
	/**
	阵营ID
	**/
	UINT8	_ID;

	/**
	阵营名称
	**/
	string	_Name;

	/**
	复活地图ID
	**/
	UINT16	_ReliveMap;

	/**
	复活X坐标
	**/
	float	_ReliveX;

	/**
	复活Y坐标
	**/
	float	_ReliveY;

	/**
	势力主城ID
	**/
	UINT16	_CityID_1;

	/**
	战场ID
	**/
	UINT16	_WarID_1;

	/**
	势力主城ID
	**/
	UINT16	_CityID_2;

	/**
	战场ID
	**/
	UINT16	_WarID_2;

	/**
	矿场地图
	**/
	UINT16	_MapID;

	/**
	进入X坐标
	**/
	float	_EnterX;

	/**
	进入Y坐标
	**/
	float	_EnterY;
}; // SCampCFG define end

//data loader for the excel table
class CCampLoader
{
public:
	std::vector<SCampCFG*> _vecData;

	~CCampLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

