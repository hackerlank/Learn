// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SHorseBaseCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CHORSEBASELOADER_H
#define _CHORSEBASELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SHorseBaseCFG
{
	/**
	坐骑ID
	**/
	UINT32	_ID;

	/**
	名字
	**/
	string	_ModelName;

	/**
	坐骑品质
	**/
	UINT8	_Quality;

	/**
	解锁条件
	**/
	UINT32	_ItemID;

	/**
	显示等级
	**/
	UINT8	_Level;

	/**
	初始速度加成
	**/
	UINT32	_Speed;

	/**
	模型Id
	**/
	UINT32	_ModelID;

	/**
	技能1
	**/
	UINT32	_SkillAttrID1;

	/**
	解锁条件1
	**/
	UINT8	_UnLockCond1;

	/**
	技能2
	**/
	UINT32	_SkillAttrID2;

	/**
	解锁条件2
	**/
	UINT32	_UnLockCond2;

	/**
	技能3
	**/
	UINT32	_SkillAttrID3;

	/**
	解锁条件3
	**/
	UINT32	_UnLockCond3;

	/**
	技能4
	**/
	UINT32	_SkillAttrID4;

	/**
	解锁条件4
	**/
	UINT32	_UnLockCond4;

	/**
	技能5
	**/
	UINT32	_SkillAttrID5;

	/**
	解锁条件5
	**/
	UINT32	_UnLockCond5;

	/**
	描述
	**/
	string	_Desc;
}; // SHorseBaseCFG define end

//data loader for the excel table
class CHorseBaseLoader
{
public:
	std::vector<SHorseBaseCFG*> _vecData;

	~CHorseBaseLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

