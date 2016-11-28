/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterComm.h
//  Purpose:      GameServer到CenterServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Game2CenterComm.h"

namespace NGame2CenterComm
{

//协议类：GameServer到CenterServer的通信协议
class CGame2CenterCommSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：替换帐号
	bool Send_ReplaceUser( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID //(本地保存的函数参数)帐号ID
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_ReplaceUser(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID //(本地保存的函数参数)帐号ID
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：GM指令
	bool Send_GMCmd( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		const std::string& strInfo, //GM指令信息
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID //(本地保存的函数参数)帐号ID
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GMCmd(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		const std::string& strInfo, //GM指令信息
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID //(本地保存的函数参数)帐号ID
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：充值接口
	bool Send_AddTotalRecharge( //发送给当前协议处理的服务器
		const NRoleInfoDefine::SRecharge& oRecharge, //充值仙石的数据
		const std::string& strUdp1, //udpLog参数1(平台传来的)
		const std::string& strUdp2, //udpLog参数2(平台传来的)
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_AddTotalRecharge(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NRoleInfoDefine::SRecharge& oRecharge, //充值仙石的数据
		const std::string& strUdp1, //udpLog参数1(平台传来的)
		const std::string& strUdp2, //udpLog参数2(平台传来的)
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：充值接口(改版:加仙石礼包到邮件)
	bool Send_AddRechargeMailItem( //发送给当前协议处理的服务器
		const NRoleInfoDefine::SRecharge& oRecharge, //充值仙石的数据
		const std::string& strUdp1, //udpLog参数1(平台传来的)
		const std::string& strUdp2, //udpLog参数2(平台传来的)
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_AddRechargeMailItem(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NRoleInfoDefine::SRecharge& oRecharge, //充值仙石的数据
		const std::string& strUdp1, //udpLog参数1(平台传来的)
		const std::string& strUdp2, //udpLog参数2(平台传来的)
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：补偿玩家未创建预先充值的仙石
	bool Send_AddTotalPrepaid( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT32 dwGold, //仙石数量
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_AddTotalPrepaid(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT32 dwGold, //仙石数量
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：Q点直购道具
	bool Send_AddQQCoinBuyItem( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		const TVecUserItem& vecUserItem, //物品列表
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_AddQQCoinBuyItem(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		const TVecUserItem& vecUserItem, //物品列表
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：询问可否提取附件
	bool Send_CheckMailAttch( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT64 qwMailID, //邮件ID
		const NMailProt::TVecMailAttachment& vecItemInfo, //附件
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byCan //(返回值)0表示可以提取
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_CheckMailAttch(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT64 qwMailID, //邮件ID
		const NMailProt::TVecMailAttachment& vecItemInfo, //附件
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byCan //(返回值)0表示可以提取
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：发送附件
	bool Send_SendMailAttch( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT64 qwMailID, //邮件ID
		const NMailProt::TVecMailAttachment& vecItemInfo //附件
	);
	bool SendSvr_SendMailAttch(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT64 qwMailID, //邮件ID
		const NMailProt::TVecMailAttachment& vecItemInfo //附件
	);
	std::string& BuildPkg_SendMailAttch( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		UINT64 qwMailID, //邮件ID
		const NMailProt::TVecMailAttachment& vecItemInfo //附件
	);

	//发送：修改签名
	bool Send_SetSign( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		const std::string& strSign //签名
	);
	bool SendSvr_SetSign(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		const std::string& strSign //签名
	);
	std::string& BuildPkg_SetSign( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		const std::string& strSign //签名
	);

	//发送：修改表情
	bool Send_SetMood( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT16 wMood //表情
	);
	bool SendSvr_SetMood(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT16 wMood //表情
	);
	std::string& BuildPkg_SetMood( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		UINT16 wMood //表情
	);

	//发送：请求和他人发起战斗
	bool Send_FigtherToOther( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT64 qwOtherID, //他人的ID
		UINT32 dwCost, //花费的游戏币
		NBattleGS::EBattleType eBattleType, //战斗类型
		UINT32 dwBufferID, //临时增加的buffer
		UINT32 dwSkillAttrID, //增加的属性
		UINT32 dwCount, //buffer叠加层数
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet, //(返回值)请求结果
			UINT8 bySuc, //(返回值)是否胜利
			UINT64 qwBattleID, //(返回值)战报ID
			UINT32 dwSelfFighterPower, //(返回值)自己的战斗力
			UINT8 bySelfQuality, //(返回值)自己的主将品质
			UINT32 dwOtherFighterPower, //(返回值)他人的战斗力
			UINT8 byOtherQuality, //(返回值)他人的主将品质
			UINT32 dwTurns //(返回值)战斗回合数
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_FigtherToOther(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT64 qwOtherID, //他人的ID
		UINT32 dwCost, //花费的游戏币
		NBattleGS::EBattleType eBattleType, //战斗类型
		UINT32 dwBufferID, //临时增加的buffer
		UINT32 dwSkillAttrID, //增加的属性
		UINT32 dwCount, //buffer叠加层数
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet, //(返回值)请求结果
			UINT8 bySuc, //(返回值)是否胜利
			UINT64 qwBattleID, //(返回值)战报ID
			UINT32 dwSelfFighterPower, //(返回值)自己的战斗力
			UINT8 bySelfQuality, //(返回值)自己的主将品质
			UINT32 dwOtherFighterPower, //(返回值)他人的战斗力
			UINT8 byOtherQuality, //(返回值)他人的主将品质
			UINT32 dwTurns //(返回值)战斗回合数
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：询问可否放下掉落
	bool Send_CanPushLoot( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT32 dwLootId, //掉落的ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet //(返回值)0,可以，1，没有这个掉落，2，其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_CanPushLoot(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT32 dwLootId, //掉落的ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet //(返回值)0,可以，1，没有这个掉落，2，其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：掉落到玩家包裹
	bool Send_PushLoot( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		EOpSource eSource, //原因
		NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
		UINT32 dwLootId //掉落的ID
	);
	bool SendSvr_PushLoot(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		EOpSource eSource, //原因
		NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
		UINT32 dwLootId //掉落的ID
	);
	std::string& BuildPkg_PushLoot( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		EOpSource eSource, //原因
		NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
		UINT32 dwLootId //掉落的ID
	);

	//发送：扣钱或物品
	bool Send_ReduceItem( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
		UINT32 dwID, //钱或物品ID
		UINT32 dwCount, //数量
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet //(返回值)0,可以,1，不足，2，其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_ReduceItem(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
		UINT32 dwID, //钱或物品ID
		UINT32 dwCount, //数量
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet //(返回值)0,可以,1，不足，2，其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：物品/资源数量是否够
	bool Send_CanReduceItem( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT32 dwItemID, //物品ID
		UINT32 dwCount, //数量
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet //(返回值)0,可以,1，不足，2，其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_CanReduceItem(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT32 dwItemID, //物品ID
		UINT32 dwCount, //数量
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet //(返回值)0,可以,1，不足，2，其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：查询玩家属性
	bool Send_GetUserUINTProp( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		EPlayerUINTProp eUINTPropType, //属性类型
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT32 dwValue, //(返回值)属性值
			UINT8 byError //(返回值)0 成功, 其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetUserUINTProp(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		EPlayerUINTProp eUINTPropType, //属性类型
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT32 dwValue, //(返回值)属性值
			UINT8 byError //(返回值)0 成功, 其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：设置玩家属性
	bool Send_SetUserUINTProp( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		EPlayerUINTProp eUINTPropType, //属性类型
		UINT32 dwValue, //属性值
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError //(返回值)0 成功, 其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_SetUserUINTProp(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		EPlayerUINTProp eUINTPropType, //属性类型
		UINT32 dwValue, //属性值
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError //(返回值)0 成功, 其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：扣除物品/钱币
	bool Send_UserSubItem( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
		const TVecUserItem& vecUserItem, //物品列表
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError //(返回值)0 成功, 其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_UserSubItem(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
		const TVecUserItem& vecUserItem, //物品列表
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError //(返回值)0 成功, 其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：添加物品/钱币
	bool Send_UserAddItem( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
		const TVecUserItem& vecUserItem, //物品列表
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError //(返回值)0 成功, 其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_UserAddItem(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
		const TVecUserItem& vecUserItem, //物品列表
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError //(返回值)0 成功, 其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：转发系统消息
	bool Send_SendSysMsg( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT16 wMsgID //消息ID
	);
	bool SendSvr_SendSysMsg(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT16 wMsgID //消息ID
	);
	std::string& BuildPkg_SendSysMsg( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		UINT16 wMsgID //消息ID
	);

	//发送：任务事件通知
	bool Send_ActionNotify( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT16 wAction //通知类型
	);
	bool SendSvr_ActionNotify(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT16 wAction //通知类型
	);
	std::string& BuildPkg_ActionNotify( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		UINT16 wAction //通知类型
	);

	//发送：气泡事件通知
	bool Send_BubbleNotify( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		NProtoCommon::EDataChange eType, //修改类型
		UINT16 wMsgID, //通知类型
		const TVecINT64& vecParam, //整型变量
		const TVecString& vecString //字符串型变量
	);
	bool SendSvr_BubbleNotify(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		NProtoCommon::EDataChange eType, //修改类型
		UINT16 wMsgID, //通知类型
		const TVecINT64& vecParam, //整型变量
		const TVecString& vecString //字符串型变量
	);
	std::string& BuildPkg_BubbleNotify( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		NProtoCommon::EDataChange eType, //修改类型
		UINT16 wMsgID, //通知类型
		const TVecINT64& vecParam, //整型变量
		const TVecString& vecString //字符串型变量
	);

	//发送：玩家帮派等级更新
	bool Send_GuildLevelUpdated( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		UINT16 wLevel //帮派等级
	);
	bool SendSvr_GuildLevelUpdated(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		UINT16 wLevel //帮派等级
	);
	std::string& BuildPkg_GuildLevelUpdated( //只组包不发送
		UINT64 qwRoleID, //玩家ID
		UINT16 wLevel //帮派等级
	);

	//发送：玩家帮派名有更新
	bool Send_GuildNameUpdated( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		const std::string& strGuildName //帮派名称
	);
	bool SendSvr_GuildNameUpdated(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		const std::string& strGuildName //帮派名称
	);
	std::string& BuildPkg_GuildNameUpdated( //只组包不发送
		UINT64 qwRoleID, //玩家ID
		const std::string& strGuildName //帮派名称
	);

	//发送：帮派技能属性更新
	bool Send_GuildTechUpdate( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家唯一ID
		const NProtoCommon::TVecFtAttrMod& vecFtAttr, //玩家的帮派技能属性
		const NGuildProt::TVecGuildTechInfo& vecGuildTech //玩家的帮派技能信息
	);
	bool SendSvr_GuildTechUpdate(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家唯一ID
		const NProtoCommon::TVecFtAttrMod& vecFtAttr, //玩家的帮派技能属性
		const NGuildProt::TVecGuildTechInfo& vecGuildTech //玩家的帮派技能信息
	);
	std::string& BuildPkg_GuildTechUpdate( //只组包不发送
		UINT64 qwRoleID, //玩家唯一ID
		const NProtoCommon::TVecFtAttrMod& vecFtAttr, //玩家的帮派技能属性
		const NGuildProt::TVecGuildTechInfo& vecGuildTech //玩家的帮派技能信息
	);

	//发送：重新加载表格
	bool Send_ReloadTable( //发送给当前协议处理的服务器
		const TVecString& vecTableName //表格名字
	);
	bool SendSvr_ReloadTable(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const TVecString& vecTableName //表格名字
	);
	std::string& BuildPkg_ReloadTable( //只组包不发送
		const TVecString& vecTableName //表格名字
	);

	//发送：玩家九疑鼎属性更新
	bool Send_TripodAttrUpdate( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家唯一ID
		const TVecUINT32& vecValue //九疑鼎ID、等级
	);
	bool SendSvr_TripodAttrUpdate(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家唯一ID
		const TVecUINT32& vecValue //九疑鼎ID、等级
	);
	std::string& BuildPkg_TripodAttrUpdate( //只组包不发送
		UINT64 qwRoleID, //玩家唯一ID
		const TVecUINT32& vecValue //九疑鼎ID、等级
	);

	//发送：完成GetCond条件
	bool Send_ProcessCond( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //玩家ID
		UINT16 wCondID, //条件ID
		NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError //(返回值)0 成功, 1 其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_ProcessCond(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //玩家ID
		UINT16 wCondID, //条件ID
		NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError //(返回值)0 成功, 1 其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：玩家升级九疑鼎
	bool Send_UpgradeTripod( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //玩家ID
		UINT8 byTripodID, //九疑鼎ID
		UINT8 byLevel, //九疑鼎当前等级
		UINT32 dwExp, //九疑鼎当前经验值
		UINT8 byOneKey, //是否一键
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError, //(返回值)0 成功, 1 其他错误
			UINT8 byLevel, //(返回值)九疑鼎当前等级
			UINT32 dwExp //(返回值)九疑鼎当前经验值
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_UpgradeTripod(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //玩家ID
		UINT8 byTripodID, //九疑鼎ID
		UINT8 byLevel, //九疑鼎当前等级
		UINT32 dwExp, //九疑鼎当前经验值
		UINT8 byOneKey, //是否一键
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError, //(返回值)0 成功, 1 其他错误
			UINT8 byLevel, //(返回值)九疑鼎当前等级
			UINT32 dwExp //(返回值)九疑鼎当前经验值
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：加速九疑鼎炼丹(道具入鼎)
	bool Send_SpeedTripod( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //玩家ID
		UINT32 dwCurSoul, //当前九疑鼎的火种元气值
		UINT32 dwMaxSoul, //当前九疑鼎的火种最大元气值(配置)
		const NItemProt::TVecItemCount& vecItems, //入鼎道具列表
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError, //(返回值)0 成功, 1 其他错误
			UINT32 dwSoul //(返回值)九疑鼎增加的元气值
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_SpeedTripod(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //玩家ID
		UINT32 dwCurSoul, //当前九疑鼎的火种元气值
		UINT32 dwMaxSoul, //当前九疑鼎的火种最大元气值(配置)
		const NItemProt::TVecItemCount& vecItems, //入鼎道具列表
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError, //(返回值)0 成功, 1 其他错误
			UINT32 dwSoul //(返回值)九疑鼎增加的元气值
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：判断玩家是否拥有散仙
	bool Send_CheckHasFighter( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //玩家ID
		UINT16 wFighterID, //散仙ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError, //(返回值)0 拥有, 1 其他错误
			UINT8 byColor //(返回值)散仙品质
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_CheckHasFighter(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //玩家ID
		UINT16 wFighterID, //散仙ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError, //(返回值)0 拥有, 1 其他错误
			UINT8 byColor //(返回值)散仙品质
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：获取战斗力
	bool Send_GetBattlePoint( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError, //(返回值)0 成功, 1 其他错误
			UINT32 dwBattlePoint //(返回值)玩家战斗力
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetBattlePoint(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError, //(返回值)0 成功, 1 其他错误
			UINT32 dwBattlePoint //(返回值)玩家战斗力
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：玩家发事件中心消息
	bool Send_OnPlayerEvent( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //玩家ID
		NEventCenter::EventType eEventType, //事件类型
		const TVecINT32& vecParam, //事件参数
		const std::string& strParam, //事件参数
		bool bLog //事件参数
	);
	bool SendSvr_OnPlayerEvent(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //玩家ID
		NEventCenter::EventType eEventType, //事件类型
		const TVecINT32& vecParam, //事件参数
		const std::string& strParam, //事件参数
		bool bLog //事件参数
	);
	std::string& BuildPkg_OnPlayerEvent( //只组包不发送
		UINT64 qwUsrID, //玩家ID
		NEventCenter::EventType eEventType, //事件类型
		const TVecINT32& vecParam, //事件参数
		const std::string& strParam, //事件参数
		bool bLog //事件参数
	);

	//发送：增加或者设置玩家GameVar数值
	bool Send_AddORSetGameVar( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //玩家ID
		UINT8 byType, //0增加 >0设置
		const TVecUINT16& vecVars, //varID列表
		const TVecUINT64& vecValues //var数值列表(必须与vecVars对应)
	);
	bool SendSvr_AddORSetGameVar(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //玩家ID
		UINT8 byType, //0增加 >0设置
		const TVecUINT16& vecVars, //varID列表
		const TVecUINT64& vecValues //var数值列表(必须与vecVars对应)
	);
	std::string& BuildPkg_AddORSetGameVar( //只组包不发送
		UINT64 qwUsrID, //玩家ID
		UINT8 byType, //0增加 >0设置
		const TVecUINT16& vecVars, //varID列表
		const TVecUINT64& vecValues //var数值列表(必须与vecVars对应)
	);

	//发送：清除玩家GameVar
	bool Send_DeleteGameVar( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //玩家ID
		const TVecUINT16& vecVars //varID列表
	);
	bool SendSvr_DeleteGameVar(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //玩家ID
		const TVecUINT16& vecVars //varID列表
	);
	std::string& BuildPkg_DeleteGameVar( //只组包不发送
		UINT64 qwUsrID, //玩家ID
		const TVecUINT16& vecVars //varID列表
	);

	//发送：增加商城限购活动
	bool Send_AddMallDiscount( //发送给当前协议处理的服务器
		const NMallProt::SDiscount& oDiscount //限购道具列表
	);
	bool SendSvr_AddMallDiscount(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NMallProt::SDiscount& oDiscount //限购道具列表
	);
	std::string& BuildPkg_AddMallDiscount( //只组包不发送
		const NMallProt::SDiscount& oDiscount //限购道具列表
	);

	//发送：清除商城限购活动
	bool Send_ClearMallDiscount( //发送给当前协议处理的服务器
		UINT8 byPos //限购道具栏位
	);
	bool SendSvr_ClearMallDiscount(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT8 byPos //限购道具栏位
	);
	std::string& BuildPkg_ClearMallDiscount( //只组包不发送
		UINT8 byPos //限购道具栏位
	);

	//发送：扣除多个玩家钱币/物品
	bool Send_SubPlayerMoney( //发送给当前协议处理的服务器
		const TVecUINT64& vecUserID, //玩家ID
		const TVecUserItem& vecUserItem, //物品列表
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_SubPlayerMoney(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const TVecUINT64& vecUserID, //玩家ID
		const TVecUserItem& vecUserItem, //物品列表
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：设置玩家等级
	bool Send_SetPlayerLevel( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //玩家ID
		UINT16 wLevel, //玩家等级
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_SetPlayerLevel(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //玩家ID
		UINT16 wLevel, //玩家等级
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：设置玩家VIP等级
	bool Send_SetPlayerVIPLevel( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //玩家ID
		NPHPProt::EOptType eOptType, //台台操作类型(eOptSetPlayerVIPLevel/eOptAddGrowthValue)
		UINT32 dwLevelOrGrowthValue, //等级or成长值
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_SetPlayerVIPLevel(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //玩家ID
		NPHPProt::EOptType eOptType, //台台操作类型(eOptSetPlayerVIPLevel/eOptAddGrowthValue)
		UINT32 dwLevelOrGrowthValue, //等级or成长值
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：设置日常任务
	bool Send_SetDayTask( //发送给当前协议处理的服务器
		const TVecUINT64& vecUserID, //玩家ID
		NPHPProt::EPHPTaskType eTaskType, //日常任务类型
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_SetDayTask(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const TVecUINT64& vecUserID, //玩家ID
		NPHPProt::EPHPTaskType eTaskType, //日常任务类型
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：获取玩家信息
	bool Send_GetPlayerInfo( //发送给当前协议处理的服务器
		UINT64 qwUserID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NPHPProt::SPlayerInfo& sPlayerInfo //(返回值)返回的数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetPlayerInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NPHPProt::SPlayerInfo& sPlayerInfo //(返回值)返回的数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：获取玩家背包信息
	bool Send_GetPlayerBagInfo( //发送给当前协议处理的服务器
		UINT64 qwUserID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NPHPProt::TVecPlayerBagInfo& vecPlayerBagInfo //(返回值)返回的数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetPlayerBagInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NPHPProt::TVecPlayerBagInfo& vecPlayerBagInfo //(返回值)返回的数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：删除玩家物品
	bool Send_DelPlayerItem( //发送给当前协议处理的服务器
		UINT64 qwUserID, //用户ID
		UINT8 byType, //1；背包，2：仓库
		UINT64 qwInstID, //物品唯一ID
		UINT16 wCount, //堆叠数
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_DelPlayerItem(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID, //用户ID
		UINT8 byType, //1；背包，2：仓库
		UINT64 qwInstID, //物品唯一ID
		UINT16 wCount, //堆叠数
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：给玩家用掉落包发系统邮件
	bool Send_SendSysMailByLootId( //发送给当前协议处理的服务器
		UINT64 qwUserID, //用户ID
		UINT16 wTitle, //邮件标题
		UINT16 wText, //邮件正文
		const TVecString& vecParam, //邮件参数
		UINT32 dwLootId, //掉落包
		UINT32 dwRate //倍率
	);
	bool SendSvr_SendSysMailByLootId(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID, //用户ID
		UINT16 wTitle, //邮件标题
		UINT16 wText, //邮件正文
		const TVecString& vecParam, //邮件参数
		UINT32 dwLootId, //掉落包
		UINT32 dwRate //倍率
	);
	std::string& BuildPkg_SendSysMailByLootId( //只组包不发送
		UINT64 qwUserID, //用户ID
		UINT16 wTitle, //邮件标题
		UINT16 wText, //邮件正文
		const TVecString& vecParam, //邮件参数
		UINT32 dwLootId, //掉落包
		UINT32 dwRate //倍率
	);

	//发送：任务集市
	bool Send_GetTaskStateForPlatfrom( //发送给当前协议处理的服务器
		UINT64 qwUserID, //用户ID
		UINT32 dwTaskID, //邮件标题
		UINT8 byStep, //邮件正文
		UINT8 byOpt, //邮件正文
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			NPHPProt::ETaskState eRet //(返回值)返回的数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetTaskStateForPlatfrom(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID, //用户ID
		UINT32 dwTaskID, //邮件标题
		UINT8 byStep, //邮件正文
		UINT8 byOpt, //邮件正文
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			NPHPProt::ETaskState eRet //(返回值)返回的数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：同步微信微博人数
	bool Send_SynWeiweiPersonNum( //发送给当前协议处理的服务器
		UINT64 qwUserID, //玩家ID
		UINT8 byType, //类型
		UINT32 dwCount //人数
	);
	bool SendSvr_SynWeiweiPersonNum(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID, //玩家ID
		UINT8 byType, //类型
		UINT32 dwCount //人数
	);
	std::string& BuildPkg_SynWeiweiPersonNum( //只组包不发送
		UINT64 qwUserID, //玩家ID
		UINT8 byType, //类型
		UINT32 dwCount //人数
	);

	//发送：检测CDK
	bool Send_CheckCDK( //发送给当前协议处理的服务器
		UINT64 qwUserID, //玩家ID
		const std::string& strCDK //CDK码
	);
	bool SendSvr_CheckCDK(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID, //玩家ID
		const std::string& strCDK //CDK码
	);
	std::string& BuildPkg_CheckCDK( //只组包不发送
		UINT64 qwUserID, //玩家ID
		const std::string& strCDK //CDK码
	);

	//发送：QQAlarm安装
	bool Send_SynQQAlarm( //发送给当前协议处理的服务器
		UINT64 qwUserID //玩家ID
	);
	bool SendSvr_SynQQAlarm(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID //玩家ID
	);
	std::string& BuildPkg_SynQQAlarm( //只组包不发送
		UINT64 qwUserID //玩家ID
	);

	//发送：运营修改宝箱信息
	bool Send_ModifyChest( //发送给当前协议处理的服务器
		const NPHPProt::SChestInfo& sChestInfo //信息
	);
	bool SendSvr_ModifyChest(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NPHPProt::SChestInfo& sChestInfo //信息
	);
	std::string& BuildPkg_ModifyChest( //只组包不发送
		const NPHPProt::SChestInfo& sChestInfo //信息
	);

	//发送：Center2Game活动时间同步
	bool Send_SyncActivityTime( //发送给当前协议处理的服务器
		const NProtoCommon::SActivityTime& sActTime //信息
	);
	bool SendSvr_SyncActivityTime(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NProtoCommon::SActivityTime& sActTime //信息
	);
	std::string& BuildPkg_SyncActivityTime( //只组包不发送
		const NProtoCommon::SActivityTime& sActTime //信息
	);

	//发送：请求累计登入天数
	bool Send_GetLoginDays( //发送给当前协议处理的服务器
		UINT64 qwUserID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT32 dwDays //(返回值)天数
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetLoginDays(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT32 dwDays //(返回值)天数
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：同步活动状态
	bool Send_SyncActState( //发送给当前协议处理的服务器
		const SActivityState& oInfo, //数据
		bool bNotify //是否通知全服
	);
	bool SendSvr_SyncActState(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const SActivityState& oInfo, //数据
		bool bNotify //是否通知全服
	);
	std::string& BuildPkg_SyncActState( //只组包不发送
		const SActivityState& oInfo, //数据
		bool bNotify //是否通知全服
	);

	//发送：添加Title
	bool Send_SyncTitle( //发送给当前协议处理的服务器
		UINT64 qwUserID, //玩家ID
		UINT16 wTitleID //添加Title
	);
	bool SendSvr_SyncTitle(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID, //玩家ID
		UINT16 wTitleID //添加Title
	);
	std::string& BuildPkg_SyncTitle( //只组包不发送
		UINT64 qwUserID, //玩家ID
		UINT16 wTitleID //添加Title
	);

	//发送：扣除礼卷钻石
	bool Send_SubGoldOrCoupon( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
		UINT32 dwCount, //扣款数量
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError //(返回值)0 成功, 其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_SubGoldOrCoupon(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
		UINT32 dwCount, //扣款数量
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError //(返回值)0 成功, 其他错误
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：心跳
	virtual void OnRecv_KeepAlive(
	) = 0;

	//接收：GameServer初始化完成通知
	virtual void OnRecv_GameSvrInitNft(
	) = 0;

	struct SGetCenterStateAck : public CServerFuncAck
	{
		SGetCenterStateAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：CenterServer状态请求
	virtual bool OnRecv_GetCenterState(
		shared_func<SGetCenterStateAck>& fnAck //返回回调函数
	) = 0;

	//接收：GameServer数据同步请求
	virtual void OnRecv_GameSvrDataSyncReq(
		ESyncKey eSyncKey, //同步Key
		UINT16 wDestGroup, //目的服务器组号
		UINT8 byDestIndex, //目的GameServer(0为全部)
		const TVecINT32& vecParam, //同步参数
		const std::string& strSyncData //同步数据
	) = 0;

	//接收：账号进入游戏通知
	virtual void OnRecv_UserLoginNtf(
		UINT64 qwUsrID, //账号ID
		const SUserEnterInfo& rUserInfo //帐号进入信息
	) = 0;

	//接收：账号退出游戏通知
	virtual void OnRecv_UserLogoutNtf(
		UINT64 qwUsrID //账号ID
	) = 0;

	//接收：账号替换通知
	virtual void OnRecv_UserReplaceNtf(
		UINT64 qwUsrID //账号ID
	) = 0;

	//接收：帐号跳GameServer通知
	virtual void OnRecv_UserJumpSvrNtf(
		UINT64 qwUsrID //账号ID
	) = 0;

	//接收：玩家同步属性通知
	virtual void OnRecv_UserSyncPropNtf(
		UINT64 qwUsrID, //账号ID
		EUserSyncPropField eField, //同步属性类型
		const std::string& strVal //值序列化字符串
	) = 0;

	struct SIsFriendAck : public CServerFuncAck
	{
		UINT8 byRet; //0是好友 1非好友

		SIsFriendAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：是否为好友
	virtual bool OnRecv_IsFriend(
		UINT64 qwUsrID, //账号ID
		UINT64 qwFriID, //好友账号ID
		shared_func<SIsFriendAck>& fnAck //返回回调函数
	) = 0;

	struct SIsSameGuildAck : public CServerFuncAck
	{
		UINT8 byRet; //0在同一个帮派 1不在同一个帮派

		SIsSameGuildAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：是否在同一个帮派
	virtual bool OnRecv_IsSameGuild(
		UINT64 qwUsrID, //账号ID
		UINT64 qwOtherID, //帮派成员ID
		shared_func<SIsSameGuildAck>& fnAck //返回回调函数
	) = 0;

	//接收：发送系统邮件,自定义字符串
	virtual void OnRecv_SendMail(
		const std::string& strSender, //发送者
		const std::string& strTitle, //标题
		const NMailProt::SysMailSendTxt& strMsgInfo, //内容
		const NMailProt::TVecMailAttachment& vecItemInfo, //物品信息
		const TVecUINT64& vecTargetIDs //接受者IDs
	) = 0;

	struct SGetGuildIDAck : public CServerFuncAck
	{
		UINT64 qwGuildID; //帮派ID
		std::string strGuildName; //帮派名称
		UINT8 byGuildLvl; //帮派等级
		std::string strGuildOwnerName; //帮主名称

		SGetGuildIDAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取帮派ID
	virtual bool OnRecv_GetGuildID(
		UINT64 qwRoleID, //玩家ID
		shared_func<SGetGuildIDAck>& fnAck //返回回调函数
	) = 0;

	struct SGetGuildNameAck : public CServerFuncAck
	{
		bool bValid; //是否已经找到
		UINT64 qwGuildID; //帮派ID
		std::string strGuildName; //帮派名称
		UINT8 byGuildLvl; //帮派等级
		std::string strGuildOwnerName; //帮主名称

		SGetGuildNameAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取帮派ID
	virtual bool OnRecv_GetGuildName(
		UINT64 qwGuildID, //帮派ID
		shared_func<SGetGuildNameAck>& fnAck //返回回调函数
	) = 0;

	//接收：帮派广播
	virtual void OnRecv_NotifyGuildInfo(
		UINT64 qwGuildID, //帮派ID
		const TVecUINT64& vecExcpRoleID, //不需要通知的人ID
		const std::string& strData //具体信息
	) = 0;

	//接收：同步增加icon
	virtual void OnRecv_SynIconAppear(
		UINT64 qwRoleID, //角色ID
		const std::string& szIcon //功能
	) = 0;

	//接收：增加帮派贡献
	virtual void OnRecv_AddGuildContribution(
		UINT64 qwRoleID, //玩家ID
		UINT32 dwContribution //帮派贡献
	) = 0;

	//接收：增加玩家九疑鼎火种
	virtual void OnRecv_ActiveTripodFire(
		UINT64 qwRoleID, //玩家ID
		UINT16 wFireID //火种ID
	) = 0;

	//接收：更新登录参数
	virtual void OnRecv_UpdatePlatformParam(
		UINT64 qwRoleID, //玩家ID
		const NProtoCommon::TVecPlatformParam& vecPlatform, //平台参数列表
		UINT32 dwIndex //当前平台索引
	) = 0;

	//接收：更新登录其他参数
	virtual void OnRecv_UpdateEnterString(
		UINT64 qwRoleID, //玩家ID
		const TVecString& vecEnterString //平台参数列表
	) = 0;

	//接收：发送全服活动信息
	virtual void OnRecv_SendWonderType(
		EWonderActType eActType, //活动类型
		UINT64 qwRoleID, //玩家ID
		UINT32 dwCond //条件ID
	) = 0;

	struct SSubGuildContributionAck : public CServerFuncAck
	{
		NGuildProt::EGuildResult eResult; //检测结果

		SSubGuildContributionAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：扣除帮贡
	virtual bool OnRecv_SubGuildContribution(
		UINT64 qwRoleID, //玩家ID
		UINT32 dwContribution, //帮贡数量
		shared_func<SSubGuildContributionAck>& fnAck //返回回调函数
	) = 0;

	//接收：美女抽奖log
	virtual void OnRecv_BeautyLotteryLog(
		const NBeautyLogGS::SBeautyLog& oBeautyLog //抽奖log
	) = 0;

	//接收：邀请好友成功
	virtual void OnRecv_InviteFriend(
		UINT64 qwUserID, //邀请人
		UINT64 qwInvitedUserID //被邀请人
	) = 0;

	//接收：通知帮派兑换物品开始
	virtual void OnRecv_NotifyGuildExchangedItemBegin(
		const TVecLingShanShopData& vecLingShanShopData //灵山商店数据
	) = 0;

	//接收：同步在Center使用的buff结束时间(待修改完善)
	virtual void OnRecv_SyncGameBuffUseInCenter(
		UINT64 qwRoleID, //玩家ID
		UINT16 wBuffID, //buffID
		UINT32 dwEndTime //结束时间
	) = 0;

	//接收：同步活动参数
	virtual void OnRecv_SyncGameActiveParam(
		ActiveParam eParam, //参数类型
		const TVecUINT32& vecParam //参数
	) = 0;

	struct SGetSystemVarAck : public CServerFuncAck
	{
		TVecUINT16 vecVars; //varID列表
		TVecUINT64 vecValues; //var数值列表(必须与vecVars对应)

		SGetSystemVarAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取全局Var值
	virtual bool OnRecv_GetSystemVar(
		const TVecUINT16& vecVarID, //varID列表
		shared_func<SGetSystemVarAck>& fnAck //返回回调函数
	) = 0;

	struct SSetSystemVarAck : public CServerFuncAck
	{
		TVecUINT16 vecVarID; //设置成功的varID列表(只是校验用)

		SSetSystemVarAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：设置全局Var值
	virtual bool OnRecv_SetSystemVar(
		const TVecUINT16& vecVars, //varID列表
		const TVecUINT64& vecValues, //var数值列表(必须与vecVars对应)
		shared_func<SSetSystemVarAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID) override;

	virtual UINT8 GetProtID() const override { return 12; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_KeepAlive(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GameSvrInitNft(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetCenterState(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GameSvrDataSyncReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserLoginNtf(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserLogoutNtf(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserReplaceNtf(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserJumpSvrNtf(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserSyncPropNtf(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_IsFriend(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_IsSameGuild(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendMail(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetGuildID(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetGuildName(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_NotifyGuildInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SynIconAppear(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddGuildContribution(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ActiveTripodFire(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdatePlatformParam(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateEnterString(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendWonderType(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SubGuildContribution(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BeautyLotteryLog(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_InviteFriend(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_NotifyGuildExchangedItemBegin(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SyncGameBuffUseInCenter(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SyncGameActiveParam(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetSystemVar(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetSystemVar(const char* pBuf, UINT32 dwLen);

	/////////////////////协议返回函数/////////////////////
	bool _DoReturn_ReplaceUser(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_ReplaceUser(UINT32 dwSessionID);
	bool _DoReturn_GMCmd(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GMCmd(UINT32 dwSessionID);
	bool _DoReturn_AddTotalRecharge(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_AddTotalRecharge(UINT32 dwSessionID);
	bool _DoReturn_AddRechargeMailItem(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_AddRechargeMailItem(UINT32 dwSessionID);
	bool _DoReturn_AddTotalPrepaid(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_AddTotalPrepaid(UINT32 dwSessionID);
	bool _DoReturn_AddQQCoinBuyItem(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_AddQQCoinBuyItem(UINT32 dwSessionID);
	bool _DoReturn_CheckMailAttch(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_CheckMailAttch(UINT32 dwSessionID);
	bool _DoReturn_FigtherToOther(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_FigtherToOther(UINT32 dwSessionID);
	bool _DoReturn_CanPushLoot(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_CanPushLoot(UINT32 dwSessionID);
	bool _DoReturn_ReduceItem(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_ReduceItem(UINT32 dwSessionID);
	bool _DoReturn_CanReduceItem(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_CanReduceItem(UINT32 dwSessionID);
	bool _DoReturn_GetUserUINTProp(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetUserUINTProp(UINT32 dwSessionID);
	bool _DoReturn_SetUserUINTProp(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_SetUserUINTProp(UINT32 dwSessionID);
	bool _DoReturn_UserSubItem(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_UserSubItem(UINT32 dwSessionID);
	bool _DoReturn_UserAddItem(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_UserAddItem(UINT32 dwSessionID);
	bool _DoReturn_ProcessCond(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_ProcessCond(UINT32 dwSessionID);
	bool _DoReturn_UpgradeTripod(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_UpgradeTripod(UINT32 dwSessionID);
	bool _DoReturn_SpeedTripod(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_SpeedTripod(UINT32 dwSessionID);
	bool _DoReturn_CheckHasFighter(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_CheckHasFighter(UINT32 dwSessionID);
	bool _DoReturn_GetBattlePoint(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetBattlePoint(UINT32 dwSessionID);
	bool _DoReturn_SubPlayerMoney(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_SubPlayerMoney(UINT32 dwSessionID);
	bool _DoReturn_SetPlayerLevel(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_SetPlayerLevel(UINT32 dwSessionID);
	bool _DoReturn_SetPlayerVIPLevel(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_SetPlayerVIPLevel(UINT32 dwSessionID);
	bool _DoReturn_SetDayTask(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_SetDayTask(UINT32 dwSessionID);
	bool _DoReturn_GetPlayerInfo(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetPlayerInfo(UINT32 dwSessionID);
	bool _DoReturn_GetPlayerBagInfo(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetPlayerBagInfo(UINT32 dwSessionID);
	bool _DoReturn_DelPlayerItem(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_DelPlayerItem(UINT32 dwSessionID);
	bool _DoReturn_GetTaskStateForPlatfrom(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetTaskStateForPlatfrom(UINT32 dwSessionID);
	bool _DoReturn_GetLoginDays(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetLoginDays(UINT32 dwSessionID);
	bool _DoReturn_SubGoldOrCoupon(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_SubGoldOrCoupon(UINT32 dwSessionID);

private:
	typedef bool (CGame2CenterCommSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _ReturnFuncs[];
	static THandleFunc _HandleFuncs[];

	typedef void (CGame2CenterCommSvr::*TTimeOutFunc)(UINT32 dwSessionID);
	static TTimeOutFunc _TimeoutFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGame2CenterComm
