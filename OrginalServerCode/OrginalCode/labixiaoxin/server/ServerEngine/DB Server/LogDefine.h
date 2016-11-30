/********************************************************************
    创建时间：    2015/04/26  16:33:54 
    文件名：      LogDefine.h
    
    功能:		1.日志文件相关信息定义
				2.
                
    说明:		1. 主要用于日志文件数据结构及枚举定义
                2. 
*********************************************************************/
#ifndef __LOGDEFINE_H_
#define __LOGDEFINE_H_
#include "..\GameBase\Common\GameDefine.h"

#define ZeroVar(p) ZeroMemory( &p, sizeof( p ) )

//日志类型
enum enum_LOG_TYPE
{
	LOG_TYPE_DEFALT = 0,//默认值
	LOG_TYPE_money_add,//金卡增加
	LOG_TYPE_exp_add,//经验值增加
	LOG_TYPE_coin_add,//贝壳增加
	LOG_TYPE_energy_add,//体力增加
	LOG_TYPE_pvpenergy_add,//体力增加
	LOG_TYPE_PowerPoint_add,//合金增加
	LOG_TYPE_Friendship_add,//友情点增加
	LOG_TYPE_honour_add,//荣誉值增加
	LOG_TYPE_handBook_add,//图鉴增加
	LOG_TYPE_player_add,//真人增加
	LOG_TYPE_player_chip_add, //角色碎片增加
	LOG_TYPE_equipment_add, //设备，装备增加
	LOG_TYPE_function_add,	//功能解锁
	LOG_TYPE_gift_add,		//礼包获得
	LOG_TYPE_extra_skill_add, //技能获得
	LOG_TYPE_material_add,	 //材料，碎片获得
	LOG_TYPE_map_start_add,		//关卡进度 (星星更新)
	LOG_TYPE_equipment_up, //设备，装备升级
	LOG_TYPE_player_up,		//伙伴升级
	LOG_TYPE_skill_up,		//技能升级
	LOG_TYPE_step,			//进阶
	LOG_TYPE_money_lower,//金币减少
	LOG_TYPE_coin_lower,//贝壳下降
	LOG_TYPE_energy_lower,//体力下降
	LOG_TYPE_handBook_lower,//图鉴下降
	LOG_TYPE_PowerPoint_lower,//合金下降
	LOG_TYPE_honour_lower,//荣誉值下降
	LOG_TYPE_pvp_lower,//pvp下降
	LOG_TYPE_Friendship_lower,	//友情点下降
	LOG_TYPE_material_lower,	//材料，碎片消耗
	LOG_TYPE_equipment_lower,	//分解
	LOG_TYPE_props_add,		//增加道具
	LOG_TYPE_props_lower,	//减少道具
	LOG_TYPE_Dynamic_Energy_lower,	//动感能量
	LOG_TYPE_Dynamic_Energy_add,	//动感能量
	LOG_TYPE_RECHARGE,	//充值
	LOG_TYPE_Statistics,	//统计
	LOG_TYPE_props,		//道具
	LOG_TYPE_POWER,		//战力

	
	LOG_TYPE_FAIL,
};

//动作发生原因
enum enum_LOG_ACTION
{
	LOG_ACTION_DEFALT = 0,//默认值

	LOG_ACTION_use_gift = 1,//使用道具，领礼包
	LOG_ACTION_map_gift,	//关卡闯关 累积星星奖励
	LOG_ACTION_pvp_rank,	//pvp奖励
	LOG_ACTION_level_up,	//升级
	LOG_ACTION_vip_up,		//vip 升级
	LOG_ACTION_sign_up,		//每日签到
	LOG_ACTION_convert_gift, //礼包码兑换
	LOG_ACTION_mail_get,	//邮件提取
	LOG_ACTION_mail_all,	//一键领取所有附件
	LOG_ACTION_map_get,		//结算奖励,管卡
	LOG_ACTION_purchase_gold, //充值
	LOG_ACTION_do_behavior,	 //操作，如：领元宝，买pve，pvp体力//m_goodsID,0x16100019:浇水,0x16100020:摇钱,0x16000022:偷吃,每日登录
	LOG_ACTION_get_luck,	//抽奖
	LOG_ACTION_daily_Single_task,	//每日任务 
	LOG_ACTION_daily_task,	//每日任务 
	LOG_ACTION_task,		//任务
	LOG_ACTION_secret_buy,	//神秘商店
	LOG_ACTION_do_compose,	//合成
	LOG_ACTION_secret_refresh,//刷新神秘商店,0是自动刷新，1是普通元宝刷新，2是普通道具刷新，3是高级元宝刷新，4是高级道具刷新//
	LOG_ACTION_secret_expand,//扩充神秘商店的格子
	LOG_ACTION_melt,		//分解
	LOG_ACTION_step,		//升阶
	LOG_ACTION_map_start,	//关卡进度
	LOG_ACTION_Limited_Activity,	//限时活动任务
	LOG_ACTION_MAP_RESET,			//地图重置
	LOG_ACTION_golden_touch,        //点金手消费
	LOG_ACTION_buy_energy,        //买体力
	LOG_ACTION_map_cost,		//结算奖励,管卡
	LOG_ACTION_piece_role,		//碎片转角色
	LOG_ACTION_Unlock,		//解锁
	LOG_ACTION_user_level_up,//账户升级
	LOG_ACTION_user_exp_up,//账户经验值增加
	LOG_ACTION_Login,//登录
	LOG_ACTION_REGISTER,//注册
	LOG_ACTION_quit,//离开
	LOG_ACTION_shared,//分享得奖励
	LOG_ACTION_level_count,//等级统计
	LOG_ACTION_level_Gift,//等级礼包
	LOG_ACTION_badge_up,//徽章升级
	LOG_ACTION_CREATE_CHARACT,//创角
	LOG_ACTION_PVP_TIMES_up,//买PVP战斗次数
	LOG_ACTION_RECHARGE,//充值
	LOG_ACTION_use_props,//使用道具
	LOG_ACTION_FIRST_RECHARGE,//首充
	LOG_ACTION_Online_user_count,//时时在线人数统计
	LOG_ACTION_POWER,		//战力 (m_op_after 表示当前战力值)


	LOG_ACTION_TEST = 400,//测试
};
/*
	每日任务/任务中m_goodsID
	enum E_ACTIVE_BASE_EVENT
	{
	Event_Base_Type_Duplication = 1, //副本
	Event_Base_Type_TreasureMountain = 2, //金山
	Event_Base_Type_Trial = 3,             //
	Event_Base_Type_Lottery = 4,           //奖劵
	Event_Base_Type_LevelUp = 5,		//升级
	Event_Base_Type_EquipmentUpgrade = 6, //装备升级
	Event_Base_Type_EnhanceSkill = 7,   //技能增加
	Event_Base_Type_SecretBuy = 8,              //神秘商店
	Event_Base_Type_SupermanPowerStone = 9,     //动感能量石
	Event_Base_Type_SpecificDuplication = 10,	//特殊副本
	Event_Base_Type_ReachSpecificLevel = 11,	//等级
	Event_Base_Type_ReachSpecificStar = 12,		//星星
	Event_Base_Type_EquipmentSpecificLevel = 13,//装备特殊等级
	Event_Base_Type_EquipmentSpecificStar = 14,	//装备特殊星星
	};
*/

typedef struct tagLogItemInfo
{
	//log_id ://主键
	ACE_UINT32 m_unUserID;//帐号id user_id
	ACE_UINT32 m_unLevel;//角色等级 level
	ACE_UINT32 m_unChannel;//渠道 channel_id
	enum_LOG_TYPE m_unType;//log类别 log_type ---------------------------
	ACE_UINT32 m_goodsID;//装备ID char m_goods_name[MAX_ITEM_NAME + 1];//装备名称 goods_id
	ACE_UINT32 m_op_before;//操作前 operate_before
	ACE_UINT32 m_op_after;//操作后 operate_after
	ACE_UINT32 m_op_involve;//操作涉及 operate_involve (跟php没关系，用于消息关系)
	enum_LOG_ACTION m_op_action;//动作发生原因 operate_action---------------------
	ACE_UINT32 m_op_time;//操作时间 operate_time
	char m_name[MAX_CHARACTER_LENGTH + 1];//角色名 name
	char m_op_way[MAX_CHARACTER_LENGTH + 1];//途径(附加信息) operate_way   ---------------------------
	ACE_UINT32 m_charactID;//角色id
	void SetOp_Way(const char * str)
	{
		ZeroVar(m_op_way);
		int len = strlen(str);
		if (len > MAX_CHARACTER_LENGTH)
			len = MAX_CHARACTER_LENGTH;
		memcpy(m_op_way,str,len);
	}

	void SetOp_Way(const wchar_t * str)
	{
		ZeroVar(m_op_way);
		char rstrUtf8[MAX_CHARACTER_LENGTH + 1];
		ZeroVar(rstrUtf8);
		int dwLen = -1;
		WideCharToMultiByte(CP_UTF8, 0, str, dwLen, &rstrUtf8[0], MAX_CHARACTER_LENGTH, NULL, NULL);
		memcpy(m_op_way,rstrUtf8,MAX_CHARACTER_LENGTH + 1);
	}

	tagLogItemInfo()
	{
		ZeroVar((*this));
	}
}LogItemInfo;

// void tagLogItemInfo::ToJson( Json::Value &root )
// {
// 	root["m_unUserID"] = m_unUserID;
// 	root["m_name"] = m_name;
// 	root["m_unLevel"] = m_unLevel;
// 	root["m_unChannel"] = m_unChannel;
// 	root["m_goodsID"] = m_goodsID;
// 	root["m_op_action"] = (int)m_op_action;
// 	root["m_op_way"] = m_op_way;
// 	root["m_unType"] = (int)m_unType;
// 	root["m_op_before"] = m_op_before;
// 	root["m_op_after"] = m_op_after;
// 	root["m_op_involve"] = m_op_involve;
// 	root["m_op_time"] = m_op_time;
// }

#define _LOG_OP_WAY_use_gift			L"领礼包"
#define _LOG_OP_WAY_map_gift			L"累积星星奖励"
#define _LOG_OP_WAY_pvp_rank			L"pvp奖励"
#define _LOG_OP_WAY_level_up			L"level up"
#define _LOG_OP_WAY_vip_up				L"vip up"
#define _LOG_OP_WAY_sign_up				L"每日签到"
#define _LOG_OP_WAY_convert_gift		L"礼包码兑换"
#define _LOG_OP_WAY_mail_get			L"邮箱领取"
#define _LOG_OP_WAY_mail_all			L"一键领取所有附件"
#define _LOG_OP_WAY_map_get				L"结算奖励"
#define _LOG_OP_WAY_map_cost			L"地图消耗"
#define _LOG_OP_WAY_purchase_gold		L"充值"
#define _LOG_OP_WAY_do_behavior			L"操作"
#define _LOG_OP_WAY_get_luck			L"抽奖"
#define _LOG_OP_WAY_daily_task			L"每日任务"
#define _LOG_OP_WAY_daily_Single_task	L"每日单个任务"
#define _LOG_OP_WAY_task				L"任务奖励"
#define _LOG_OP_WAY_secret_buy			L"神秘商店"
#define _LOG_OP_WAY_do_compose			L"合成"
#define _LOG_OP_WAY_secret_refresh		L"刷新神秘商店"
#define _LOG_OP_WAY_secret_expand		L"扩充神秘商店"
#define _LOG_OP_WAY_melt				L"分解"
#define _LOG_OP_WAY_step				L"升阶"
#define _LOG_OP_WAY_map_start			L"关卡进度"
#define _LOG_OP_WAY_Limited_Activity	L"限时活动"
#define _LOG_OP_WAY_MAP_RESET			L"地图重置"
#define _LOG_OP_WAY_SYSTEM				L"系统邮件"
#define _LOG_OP_WAY_golden_touch		L"点金手"
#define _LOG_OP_WAY_buy_energy			L"买体力"
#define _LOG_OP_WAY_piece_role			L"碎片转角色"
#define _LOG_OP_WAY_Unlock				L"解锁"
#define _LOG_OP_WAY_user_level_up		L"帐号升级"
#define _LOG_OP_WAY_user_exp_up			L"经验值增加"
#define _LOG_OP_WAY_login				L"登录"
#define _LOG_OP_WAY_REGISTER			L"注册"
#define _LOG_OP_WAY_quit				L"离开"
#define _LOG_OP_WAY_shared				L"分享奖励"
#define _LOG_OP_WAY_level_count			L"等级统计"
#define _LOG_OP_WAY_level_Gift			L"等级礼包"
#define _LOG_OP_WAY_badge_up			L"徽章升级"
#define _LOG_OP_WAY_CREATE_CHARACT		L"创角"
#define _LOG_OP_WAY_TEST				L"测试登陆"
#define _LOG_OP_WAY_PVP_TIMES_up		L"竞技场买次数"
#define _LOG_OP_WAY_RECHARGE			L"充值"
#define _LOG_OP_WAY_use_props			L"使用道具"
#define _LOG_OP_WAY_FIRST_RECHARGE		L"首充"
#define _LOG_OP_WAY_Online_user_count	L"在线人数统计"
#define _LOG_OP_WAY_POWER				L"战力"


#endif