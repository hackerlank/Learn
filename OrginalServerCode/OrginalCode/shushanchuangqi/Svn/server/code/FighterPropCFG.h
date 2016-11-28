// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SFighterPropCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CFIGHTERPROPLOADER_H
#define _CFIGHTERPROPLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SFighterPropCFG
{
	/**
	类型ID
	**/
	UINT16	_ID;

	/**
	名字
	**/
	string	_Name;

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
	资源存在
	**/
	bool	_AssetExist;

	/**
	入场动作
	**/
	bool	_FirstExist;

	/**
	怪物特性
	**/
	string	_MonsterType;

	/**
	血条层数
	**/
	UINT8	_HealthNum;

	/**
	等级
	**/
	UINT8	_Level;

	/**
	职业
	**/
	UINT8	_Job;

	/**
	散仙倾向
	**/
	UINT8	_Inclination;

	/**
	颜色
	**/
	UINT8	_Color;

	/**
	入场怒气
	**/
	UINT8	_EnterRage;

	/**
	怒气上限
	**/
	UINT8	_MaxRage;

	/**
	物理攻击
	**/
	float	_EFIGHTATTR_PHYATK;

	/**
	法术攻击
	**/
	float	_EFIGHTATTR_MGCATK;

	/**
	物理防御
	**/
	float	_EFIGHTATTR_PHYDEF;

	/**
	法术防御
	**/
	float	_EFIGHTATTR_MGCDEF;

	/**
	物理免伤
	**/
	float	_EFIGHTATTR_PHYRDC;

	/**
	魔法免伤
	**/
	float	_EFIGHTATTR_MGCRDC;

	/**
	最大生命
	**/
	UINT32	_EFIGHTATTR_MAXHP;

	/**
	身法
	**/
	float	_EFIGHTATTR_SPEED;

	/**
	命中值
	**/
	float	_EFIGHTATTR_HIT;

	/**
	命中率
	**/
	float	_EFIGHTATTR_HITRATE;

	/**
	闪避值
	**/
	float	_EFIGHTATTR_DODGE;

	/**
	闪避率
	**/
	float	_EFIGHTATTR_DODGERATE;

	/**
	暴击值
	**/
	float	_EFIGHTATTR_CRITICAL;

	/**
	暴击率
	**/
	float	_EFIGHTATTR_CRTRATE;

	/**
	稳固值
	**/
	float	_EFIGHTATTR_ANTICRITCAL;

	/**
	稳固率
	**/
	float	_EFIGHTATTR_ANTICRTRATE;

	/**
	格挡值
	**/
	float	_EFIGHTATTR_BLOCK;

	/**
	格挡率
	**/
	float	_EFIGHTATTR_BLOCKRATE;

	/**
	穿透值
	**/
	float	_EFIGHTATTR_PIERCE;

	/**
	穿透率
	**/
	float	_EFIGHTATTR_PIERCERATE;

	/**
	反击值
	**/
	float	_EFIGHTATTR_COUNTER;

	/**
	反击率
	**/
	float	_EFIGHTATTR_COUNTERRATE;

	/**
	压制值
	**/
	float	_EFIGHTATTR_RESIST;

	/**
	压制率
	**/
	float	_EFIGHTATTR_RESISTRATE;

	/**
	入场灵气
	**/
	UINT32	_EFIGHTATTR_INITAURA;

	/**
	最大灵气
	**/
	UINT32	_EFIGHTATTR_MAXAURA;

	/**
	暴击伤害增加
	**/
	float	_EFIGHTATTR_CRIEXTRAADD;

	/**
	暴击伤害减免
	**/
	float	_EFIGHTATTR_CRIEXTRARDC;

	/**
	金攻
	**/
	float	_EFIGHTATTR_METALATK;

	/**
	木攻
	**/
	float	_EFIGHTATTR_WOODATK;

	/**
	水攻
	**/
	float	_EFIGHTATTR_WATERATK;

	/**
	火攻
	**/
	float	_EFIGHTATTR_FIREATK;

	/**
	土攻
	**/
	float	_EFIGHTATTR_EARTHATK;

	/**
	金防
	**/
	float	_EFIGHTATTR_METALDEF;

	/**
	木防
	**/
	float	_EFIGHTATTR_WOODDEF;

	/**
	水防
	**/
	float	_EFIGHTATTR_WATERDEF;

	/**
	火防
	**/
	float	_EFIGHTATTR_FIREDEF;

	/**
	土防
	**/
	float	_EFIGHTATTR_EARTHDEF;

	/**
	物理攻击%
	**/
	float	_EFIGHTATTR_PHYATK_PER;

	/**
	法术攻击%
	**/
	float	_EFIGHTATTR_MGCATK_PER;

	/**
	物理防御%
	**/
	float	_EFIGHTATTR_PHYDEF_PER;

	/**
	法术防御%
	**/
	float	_EFIGHTATTR_MGCDEF_PER;

	/**
	最大生命%
	**/
	float	_EFIGHTATTR_MAXHP_PER;

	/**
	身法%
	**/
	float	_EFIGHTATTR_SPEED_PER;

	/**
	命中值%
	**/
	float	_EFIGHTATTR_HIT_PER;

	/**
	闪避值%
	**/
	float	_EFIGHTATTR_DODGE_PER;

	/**
	暴击值%
	**/
	float	_EFIGHTATTR_CRITICAL_PER;

	/**
	稳固值%
	**/
	float	_EFIGHTATTR_ANTICRITCAL_PER;

	/**
	格挡值%
	**/
	float	_EFIGHTATTR_BLOCK_PER;

	/**
	穿透值%
	**/
	float	_EFIGHTATTR_PIERCE_PER;

	/**
	反击值%
	**/
	float	_EFIGHTATTR_COUNTER_PER;

	/**
	压制值%
	**/
	float	_EFIGHTATTR_RESIST_PER;

	/**
	法术抵抗
	**/
	float	_EFIGHTATTR_ANTIEFFECT;

	/**
	阵灵灵力
	**/
	float	_SOUL;

	/**
	死亡动画（技能）
	**/
	UINT32	_NormalDead;

	/**
	平砍
	**/
	UINT32	_NormalAttack;

	/**
	变身平砍
	**/
	string	_NormalAttackEx;

	/**
	所属组合
	**/
	string	_Combination;

	/**
	技能
	**/
	string	_Skills;

	/**
	变身技能
	**/
	string	_SkillsEx;

	/**
	无双技能
	**/
	string	_Peerless;

	/**
	被动技能
	**/
	string	_Talent;

	/**
	心法
	**/
	string	_Xinfa;

	/**
	出生时装
	**/
	UINT16	_Closes;

	/**
	出生武器
	**/
	UINT16	_Weapon;

	/**
	初始星级
	**/
	UINT8	_Star;

	/**
	渡劫模板
	**/
	UINT16	_DujieTemplateId;

	/**
	散仙特性
	**/
	UINT8	_HeroFeature;

	/**
	散仙特性
	**/
	string	_HeroFeatureDes;

	/**
	散仙特性
	**/
	string	_HeroFeatureDesText;

	/**
	攻击资质
	**/
	UINT8	_AttackTalent;

	/**
	物防资质
	**/
	UINT8	_PhysicalDefenseTalent;

	/**
	法防资质
	**/
	UINT8	_MagicDefenseTalent;

	/**
	生命资质
	**/
	UINT8	_HealthTalent;

	/**
	招募散仙对应道具
	**/
	UINT16	_RecruitItem;

	/**
	散仙谱排序
	**/
	UINT16	_Sort;
}; // SFighterPropCFG define end

//data loader for the excel table
class CFighterPropLoader
{
public:
	std::vector<SFighterPropCFG*> _vecData;

	~CFighterPropLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

