#pragma once

#include "BaseRes.h"
#include <map>
//徽章系统

class BadgeRes : public BaseRes
{
public:
	BadgeRes(ACE_UINT32 unType);
	virtual ~BadgeRes();

	virtual int parse_xml_node(xmlNodePtr node);
	ACE_UINT32 m_equip_id;//对应的装备ID
	ACE_UINT32 m_gaint_to[3];//"加成目标（16进制）1.全体2.队长characterID.指定角色（最多3人，逗号分割）"
	ACE_UINT32 m_gaint_ype[2];//"增益类型：加成类型(1.攻击加成/2.生命加成/3.暴击加成/4.韧性加成/5.贝壳收益/6.合金收益)，数值类型(1.固定值/2.百分比)"
	float m_gain_value[2];//"增益值初始值,成长"
	ACE_UINT32 m_need_role;


	//ACE_UINT32 m_unQuality;品质
	//ACE_UINT32 m_unSubType;
	/*
		"徽章类型
			1.锤子武器
			2.弓箭武器
			3.兔子武器
			4.漫画武器
			5.法杖武器
			6.刀武器
			7.狗玩具武器
			8.花武器
			101.戒指防具
			102.腰带防具
			103.项链防具"
		*/

	//virtual void process_res_id_by_name();
public:
	int Parse_info(ACE_UINT32 * des, char *str);
	int Parse_infoEx(float * des, char *str);
	int Parse_res_info(ACE_UINT32 * des, char *str);

	static std::map<ACE_UINT32,ACE_UINT32> m_equipmentMap;//对应的装备ID<equipmentid,badgeid>
	static ACE_UINT32 GetBadgeID(ACE_UINT32 equipmentid);
};