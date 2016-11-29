// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SAICFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CAILOADER_H
#define _CAILOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SAICFG
{
	/**
	AI ID
	**/
	UINT16	_ID;

	/**
	移动类型
	**/
	UINT8	_Move;

	/**
	攻击类型
	**/
	UINT8	_Attack;

	/**
	巡逻移动速度
	**/
	UINT32	_StandbySpeed;

	/**
	追击移动速度
	**/
	UINT32	_ChaseSpeed;

	/**
	怪物追击范围
	**/
	float	_FightRadius;

	/**
	攻击距离
	**/
	float	_AtkDistance;

	/**
	移动范围
	**/
	float	_MoveRadius;

	/**
	视野范围
	**/
	string	_SightRadius;
}; // SAICFG define end

//data loader for the excel table
class CAILoader
{
public:
	std::vector<SAICFG*> _vecData;

	~CAILoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

