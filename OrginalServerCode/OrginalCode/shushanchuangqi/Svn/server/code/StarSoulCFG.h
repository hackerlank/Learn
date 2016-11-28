// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SStarSoulCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSTARSOULLOADER_H
#define _CSTARSOULLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SStarSoulCFG
{
	/**
	ID
	**/
	UINT16	_ID;

	/**
	名称
	**/
	string	_Name;

	/**
	节点编号
	**/
	UINT16	_StarLevel;

	/**
	兽魂种类
	**/
	UINT8	_SoulType;

	/**
	所属星图
	**/
	UINT8	_StarPage;

	/**
	需要角色等级
	**/
	UINT16	_RoleLevel;

	/**
	魂魄值
	**/
	UINT32	_Cost;

	/**
	成功率
	**/
	UINT16	_Chance;

	/**
	物理攻击
	**/
	UINT32	_EFIGHTATTR_PHYATK;

	/**
	法术攻击
	**/
	UINT32	_EFIGHTATTR_MGCATK;

	/**
	物理防御
	**/
	UINT32	_EFIGHTATTR_PHYDEF;

	/**
	法术防御
	**/
	UINT32	_EFIGHTATTR_MGCDEF;

	/**
	最大生命
	**/
	UINT32	_EFIGHTATTR_MAXHP;

	/**
	身法
	**/
	UINT32	_EFIGHTATTR_SPEED;

	/**
	命中值
	**/
	UINT32	_EFIGHTATTR_HIT;

	/**
	闪避值
	**/
	UINT32	_EFIGHTATTR_DODGE;

	/**
	暴击值
	**/
	UINT32	_EFIGHTATTR_CRITICAL;

	/**
	反击值
	**/
	UINT32	_EFIGHTATTR_COUNTER;
}; // SStarSoulCFG define end

//data loader for the excel table
class CStarSoulLoader
{
public:
	std::vector<SStarSoulCFG*> _vecData;

	~CStarSoulLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

