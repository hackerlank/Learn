// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SDujieCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CDUJIELOADER_H
#define _CDUJIELOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SDujieCFG
{
	/**
	伙伴Id
	**/
	UINT16	_FighterId;

	/**
	渡劫等级
	**/
	UINT8	_Level;

	/**
	渡劫期
	**/
	string	_PeriodName;

	/**
	伙伴名字
	**/
	string	_Name;

	/**
	渡劫条件
	**/
	string	_Condition;

	/**
	奖励掉落包
	**/
	UINT32	_LootId;

	/**
	渡劫副本
	**/
	UINT16	_Dgn;

	/**
	散仙品质
	**/
	UINT8	_Color;

	/**
	主动技能品质
	**/
	string	_SkillColor;

	/**
	法宝无双技能品质
	**/
	UINT8	_MasterSkillColor;

	/**
	解锁被动技能
	**/
	string	_UnlockSkill;

	/**
	解锁天赋技能
	**/
	string	_UnlockTalent;

	/**
	成长率
	**/
	float	_GrowthRate;

	/**
	奖励元神力
	**/
	UINT8	_AwardYuanshen;

	/**
	心法位
	**/
	string	_XinfaPos;

	/**
	模型特效
	**/
	string	_EffectName;
}; // SDujieCFG define end

//data loader for the excel table
class CDujieLoader
{
public:
	std::vector<SDujieCFG*> _vecData;

	~CDujieLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

