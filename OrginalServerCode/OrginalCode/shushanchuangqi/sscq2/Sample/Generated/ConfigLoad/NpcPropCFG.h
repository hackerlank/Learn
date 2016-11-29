// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SNpcPropCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CNPCPROPLOADER_H
#define _CNPCPROPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SNpcPropCFG
{
	/**
	NPC ID
	**/
	UINT16	_ID;

	/**
	NPC等级
	**/
	UINT8	_Level;

	/**
	NPC名称
	**/
	string	_Name;

	/**
	NPC称号
	**/
	string	_Title;

	/**
	NPC类型
	**/
	UINT8	_Type;

	/**
	障碍物条件ID
	**/
	UINT8	_BarrierID;

	/**
	NPC功能脚本
	**/
	string	_Script;

	/**
	自由巡逻范围
	**/
	UINT8	_FreePatrolDistance;

	/**
	移动速度
	**/
	UINT32	_Speed;

	/**
	头像id
	**/
	UINT32	_Icon;

	/**
	模型大小比例
	**/
	float	_ModelScale;

	/**
	资源ID
	**/
	string	_MapResID;

	/**
	资源类型
	**/
	UINT8	_AssetType;

	/**
	资源参数1
	**/
	UINT16	_AssetParam1;

	/**
	资源参数2
	**/
	UINT8	_AssetParam2;

	/**
	待机特效参数
	**/
	string	_AssetParam3;

	/**
	是否默认隐藏
	**/
	UINT8	_IfHide;

	/**
	引导副本
	**/
	UINT16	_GuiDgn;
}; // SNpcPropCFG define end

//data loader for the excel table
class CNpcPropLoader
{
public:
	std::vector<SNpcPropCFG*> _vecData;

	~CNpcPropLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

