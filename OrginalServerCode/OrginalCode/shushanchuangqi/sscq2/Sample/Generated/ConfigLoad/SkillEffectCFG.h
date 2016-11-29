// ******************************************************************************************************/
// 这个是工具自动生成的表代码，这个里面的任何更改在下次生成之后会变得无效，请注意！<UTF-8 With BOM>
// 文件名：     SSkillEffectCFG.h
// Copyright(c) 2012-2100 上海恺英网络科技有限公司，All rights reserved.
// ******************************************************************************************************/


#ifndef _CSKILLEFFECTLOADER_H
#define _CSKILLEFFECTLOADER_H

#include <string>
#include <vector>
#include "Platform.h"

using namespace std;

//struct definition for the excel table
struct SSkillEffectCFG
{
	/**
	效果ID
	**/
	UINT32	_id;

	/**
	效果名
	**/
	string	_name;

	/**
	效果名
	**/
	string	_buffName;

	/**
	消耗类型1
	**/
	UINT16	_skillCostType;

	/**
	升级消耗1
	**/
	UINT32	_skillCost;

	/**
	需求等级
	**/
	UINT8	_needLvl;

	/**
	CD
	**/
	INT32	_cd;

	/**
	概率
	**/
	UINT16	_rate;

	/**
	触发条件概率
	**/
	UINT16	_condRate;

	/**
	触发条件
	**/
	UINT16	_cond;

	/**
	触发参数
	**/
	string	_condstr;

	/**
	触发计数
	**/
	UINT8	_condCD;

	/**
	消失条件
	**/
	UINT16	_outCond;

	/**
	消失参数
	**/
	string	_outCondcondstr;

	/**
	消失计数
	**/
	UINT8	_outCD;

	/**
	回合次数
	**/
	UINT8	_turnNumber;

	/**
	持续回合
	**/
	UINT8	_last;

	/**
	覆盖规则ID
	**/
	UINT16	_gpId;

	/**
	范围
	**/
	UINT16	_area;

	/**
	效果类型
	**/
	UINT16	_type;

	/**
	可否免疫
	**/
	UINT8	_resist;

	/**
	效果值
	**/
	UINT32	_value1;

	/**
	效果值
	**/
	UINT32	_value2;

	/**
	效果值
	**/
	UINT32	_value3;

	/**
	带出效果
	**/
	string	_buffID;

	/**
	战斗力数值
	**/
	UINT32	_battlePoint;
}; // SSkillEffectCFG define end

//data loader for the excel table
class CSkillEffectLoader
{
public:
	std::vector<SSkillEffectCFG*> _vecData;

	~CSkillEffectLoader();
	bool LoadData(const std::string& strPath);
	void ClearData();
};
#endif

