// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SBeautyCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CBEAUTYLOADER_H
#define _CBEAUTYLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SBeautyCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	名字
	**/
	string	_Name;

	/**
	解锁条件
	**/
	UINT32	_CondID;

	/**
	品质
	**/
	UINT8	_Color;

	/**
	npc
	**/
	UINT32	_NPCID;

	/**
	2D资源
	**/
	UINT8	_Model2D;

	/**
	出现等级
	**/
	UINT8	_AppearLevel;

	/**
	Client
	**/
	string	_EffectAppear;

	/**
	Client
	**/
	string	_EffectDisappear;
}; // SBeautyCFG define end

//data loader for the excel table
class CBeautyLoader
{
public:
	std::vector<SBeautyCFG*> _vecData;

	~CBeautyLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

