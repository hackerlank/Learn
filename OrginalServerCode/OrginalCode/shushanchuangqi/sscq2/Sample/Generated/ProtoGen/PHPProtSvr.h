/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    PHPProt.h
//  Purpose:      PHP相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "PHPProt.h"

namespace NPHPProt
{

//协议类：PHP相关协议
class CPHPProtSvr : public IProtocol
{
public:
	/////////////////////以下的接收函数需要重载/////////////////////
	struct SOnUserRechargeAck : public CServerFuncAck
	{
		UINT8 byRet; //充值返回值(值为0:成功 非0其他错误)
		std::string strError; //错误码字符串(若成功为空)

		SOnUserRechargeAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家充值仙石
	virtual bool OnRecv_OnUserRecharge(
		UINT16 wServerNo, //区服ID
		const std::string& strToken, //memcach校验
		const std::string& strNo, //充值流水号
		UINT64 qwUserID, //用户ID
		UINT16 wID, //仙石包ID(41[10仙石],42[100仙石],43[300仙石],44[500仙石],45[1000仙石],46[3000仙石])或者Q点直购道具ID
		UINT32 dwValue, //充值的仙石包数量或者Q点直购道具数量
		const std::string& strUINT, //单位,默认发QQCOIN(Q点)
		const std::string& strMoney, //仙石对应的QQCOIN值
		const std::string& strParam, //用来url请求
		shared_func<SOnUserRechargeAck>& fnAck //返回回调函数
	) = 0;

	struct SModifyActivityIntegralAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SModifyActivityIntegralAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：修改玩家各种活动积分信息
	virtual bool OnRecv_ModifyActivityIntegral(
		UINT16 wServerNo, //区服ID
		UINT64 qwUserID, //用户ID
		EActivityType eType, //活动ID
		INT32 dwActCount, //活动积分(负数表明减少)
		shared_func<SModifyActivityIntegralAck>& fnAck //返回回调函数
	) = 0;

	struct SGetPlayerInfoAck : public CServerFuncAck
	{
		TVecPlayerInfo vecPlayerInfo; //玩家信息

		SGetPlayerInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取玩家信息
	virtual bool OnRecv_GetPlayerInfo(
		UINT16 wServerNo, //区服ID
		const std::string& strName, //角色名称
		UINT64 qwUserID, //用户ID
		shared_func<SGetPlayerInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetPlayerBagInfoAck : public CServerFuncAck
	{
		TVecPlayerBagInfo vecPlayerBagInfo; //玩家背包信息

		SGetPlayerBagInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取玩家背包信息
	virtual bool OnRecv_GetPlayerBagInfo(
		UINT16 wServerNo, //区服ID
		const std::string& strName, //角色名称
		UINT64 qwUserID, //用户ID
		shared_func<SGetPlayerBagInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SDelItemAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SDelItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：删除物品
	virtual bool OnRecv_DelItem(
		UINT16 wServerNo, //区服ID
		const std::string& strName, //角色名称
		UINT64 qwUserID, //用户ID
		UINT8 byType, //1；背包，2：仓库
		UINT64 qwInstID, //物品唯一ID
		UINT16 wCount, //堆叠数
		shared_func<SDelItemAck>& fnAck //返回回调函数
	) = 0;

	struct SGetActListAck : public CServerFuncAck
	{
		TVecUINT16 vecIDs; //活动列表

		SGetActListAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取活动列表信息
	virtual bool OnRecv_GetActList(
		shared_func<SGetActListAck>& fnAck //返回回调函数
	) = 0;

	struct SOpenActAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SOpenActAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：开启指定活动
	virtual bool OnRecv_OpenAct(
		EActivityType eType, //活动ID
		UINT32 dwBegin, //活动开启时间
		UINT32 dwEnd, //活动结束时间
		shared_func<SOpenActAck>& fnAck //返回回调函数
	) = 0;

	struct SLockOrUnlockUserAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SLockOrUnlockUserAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：封号/解封
	virtual bool OnRecv_LockOrUnlockUser(
		UINT16 wServerNo, //区服ID
		const std::string& strName, //角色名称
		UINT64 qwUserID, //用户ID
		EOptType eOptType, //后台操作类型(eOptLockUser/eOptUnlockUser)
		UINT32 dwEndTime, //时间
		const std::string& strArgument, //理由
		shared_func<SLockOrUnlockUserAck>& fnAck //返回回调函数
	) = 0;

	struct SLockOrUnlockSpeakAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SLockOrUnlockSpeakAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：禁言/解禁
	virtual bool OnRecv_LockOrUnlockSpeak(
		UINT16 wServerNo, //区服ID
		const std::string& strName, //角色名称
		UINT64 qwUserID, //用户ID
		EOptType eOptType, //后台操作类型(eOptLockSpeak/eOptUnlockSpeak)
		UINT32 dwEndTime, //时间
		const std::string& strArgument, //理由
		shared_func<SLockOrUnlockSpeakAck>& fnAck //返回回调函数
	) = 0;

	struct SGetOnlineNumAck : public CServerFuncAck
	{
		UINT32 dwOnlineNum; //在线人数

		SGetOnlineNumAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取在线人数
	virtual bool OnRecv_GetOnlineNum(
		UINT16 wServerNo, //区服ID
		shared_func<SGetOnlineNumAck>& fnAck //返回回调函数
	) = 0;

	struct SSendItemAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SSendItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：发放物品/货币
	virtual bool OnRecv_SendItem(
		UINT16 wServerNo, //区服ID
		const std::string& strUserID, //格式：用户AID|户BID|..
		const std::string& strName, //角色名称(注：考虑到解析字符异常，名字不支持多个)
		const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		const std::string& strTitle, //邮件标题
		const std::string& strContent, //邮件内容
		const std::string& strArgument, //理由
		shared_func<SSendItemAck>& fnAck //返回回调函数
	) = 0;

	struct SSubMoneyAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SSubMoneyAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：减少货币数量
	virtual bool OnRecv_SubMoney(
		UINT16 wServerNo, //区服ID
		const std::string& strUserID, //格式：用户AID|户BID|..
		const std::string& strName, //角色名称(注：考虑到解析字符异常，名字不支持多个)
		const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		shared_func<SSubMoneyAck>& fnAck //返回回调函数
	) = 0;

	struct SSendVIPItemAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SSendVIPItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：发放VIP物品
	virtual bool OnRecv_SendVIPItem(
		UINT16 wServerNo, //区服ID
		UINT8 byVIPMinLevel, //VIP最小等级
		UINT8 byVIPMaxLevel, //VIP最大等级
		const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		const std::string& strTitle, //邮件标题
		const std::string& strContent, //邮件内容
		const std::string& strArgument, //理由
		shared_func<SSendVIPItemAck>& fnAck //返回回调函数
	) = 0;

	struct SSendClanItemAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SSendClanItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：发放帮派物品
	virtual bool OnRecv_SendClanItem(
		UINT16 wServerNo, //区服ID
		UINT64 qwClanID, //帮派ID
		ESendTarget eTarget, //对象
		const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		const std::string& strTitle, //邮件标题
		const std::string& strContent, //邮件内容
		const std::string& strArgument, //理由
		shared_func<SSendClanItemAck>& fnAck //返回回调函数
	) = 0;

	struct SGlobalSendItemAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SGlobalSendItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：全区发放物品
	virtual bool OnRecv_GlobalSendItem(
		UINT16 wServerNo, //区服ID
		ESendTarget eTarget, //对象
		const std::string& strItem, //格式：ItemAID,ItemANum|ItemBID,ItemBNum|..,..
		const std::string& strTitle, //邮件标题
		const std::string& strContent, //邮件内容
		const std::string& strArgument, //理由
		shared_func<SGlobalSendItemAck>& fnAck //返回回调函数
	) = 0;

	struct SSendMailAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SSendMailAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：发送邮件
	virtual bool OnRecv_SendMail(
		UINT16 wServerNo, //区服ID
		const std::string& strUserID, //格式：用户AID|户BID|..
		const std::string& strName, //角色名称(注：考虑到解析字符异常，名字不支持多个)
		const std::string& strTitle, //邮件标题
		const std::string& strContent, //邮件内容
		shared_func<SSendMailAck>& fnAck //返回回调函数
	) = 0;

	struct SGlobalSendMailAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SGlobalSendMailAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：全区发送邮件
	virtual bool OnRecv_GlobalSendMail(
		UINT16 wServerNo, //区服ID
		ESendTarget eTarget, //对象
		const std::string& strTitle, //邮件标题
		const std::string& strContent, //邮件内容
		shared_func<SGlobalSendMailAck>& fnAck //返回回调函数
	) = 0;

	struct SGlobalSendNoticeAck : public CServerFuncAck
	{
		UINT32 dwNoticeID; //返回公告ID
		EOptResult eOptResult; //后台操作结果

		SGlobalSendNoticeAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：发送公告
	virtual bool OnRecv_GlobalSendNotice(
		UINT16 wServerNo, //区服ID
		const std::string& strContent, //系统弹窗内容
		EPlatformType ePlatformType, //平台类型
		EShowType eShowType, //显示区域
		ERollType eRollType, //是否滚动
		ESendType eSendType, //是否立即发送
		UINT32 dwBeginTime, //公告开始时间(注：如果选择立即发送，dwBeginTime为0)
		UINT32 dwEndTime, //公告结束时间(注：如果选择立即发送，dwEndTime为0)
		shared_func<SGlobalSendNoticeAck>& fnAck //返回回调函数
	) = 0;

	struct SGlobalDelNoticeAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SGlobalDelNoticeAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：删除公告
	virtual bool OnRecv_GlobalDelNotice(
		UINT16 wServerNo, //区服ID
		UINT32 dwNoticeID, //公告ID
		shared_func<SGlobalDelNoticeAck>& fnAck //返回回调函数
	) = 0;

	struct SGlobalSendSysDialogAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SGlobalSendSysDialogAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：发送系统弹窗
	virtual bool OnRecv_GlobalSendSysDialog(
		UINT16 wServerNo, //区服ID
		EPlatformType ePlatformType, //平台类型
		EDialogType eDialogType, //弹窗类型
		shared_func<SGlobalSendSysDialogAck>& fnAck //返回回调函数
	) = 0;

	struct SOpenDiscountActivityAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SOpenDiscountActivityAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：开启商城限购活动
	virtual bool OnRecv_OpenDiscountActivity(
		UINT16 wServerNo, //区服ID
		UINT8 byPos, //限购位置(0,1,2表示)
		UINT8 byOptType, //操作类型(0：增加；1：删除)
		const std::string& strDisItems, //限购道具信息(itemID,原价,折扣价|...)
		UINT8 byLimitType, //类型限制(0无条件、1充值限购、2消费限购)
		UINT32 dwLimitValue, //达到的仙石数量限制(0无条件、1充值限购、2消费限购)
		UINT16 wLimitCount, //购买道具个数限制
		UINT32 dwBeginTime, //限购开始时间
		UINT32 dwEndTime, //限购结束时间
		shared_func<SOpenDiscountActivityAck>& fnAck //返回回调函数
	) = 0;

	struct SSetPlayerLevelAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SSetPlayerLevelAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：设置玩家等级
	virtual bool OnRecv_SetPlayerLevel(
		UINT16 wServerNo, //区服ID
		const std::string& strName, //角色名称
		UINT64 qwUserID, //用户ID
		UINT16 wLevel, //等级
		shared_func<SSetPlayerLevelAck>& fnAck //返回回调函数
	) = 0;

	struct SSetPlayerVIPLevelAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SSetPlayerVIPLevelAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：设置玩家VIP等级
	virtual bool OnRecv_SetPlayerVIPLevel(
		UINT16 wServerNo, //区服ID
		const std::string& strName, //角色名称
		UINT64 qwUserID, //用户ID
		EOptType eOptType, //后台台操作类型(eOptSetPlayerVIPLevel/eOptAddGrowthValue)
		UINT32 wLevelOrGrowthValue, //等级or成长值
		shared_func<SSetPlayerVIPLevelAck>& fnAck //返回回调函数
	) = 0;

	struct STaskManagerAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		STaskManagerAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：日常任务管理
	virtual bool OnRecv_TaskManager(
		UINT16 wServerNo, //区服ID
		const std::string& strUserID, //格式：用户AID|户BID|..
		const std::string& strName, //角色名称(注：考虑到解析字符异常，名字不支持多个)
		EPHPTaskType ePHPTaskType, //任务类型
		shared_func<STaskManagerAck>& fnAck //返回回调函数
	) = 0;

	//接收：平台信息
	virtual void OnRecv_PlatformInfo(
		EPlatformType byPtType, //平台类型
		EQQPlatformType byQQPtType, //QQ平台类型
		UINT8 byQQPtLv, //QQ平台类型等级
		UINT8 byQQPtYearType, //是否年费
		UINT8 byQQPtLuxuryType, //是否豪华
		const std::string& customPar1, //广告主来源
		const std::string& customPar2, //广告次来源
		const std::string& strOpenId, //openID
		const std::string& strOpenKey //openKey
	) = 0;

	struct SGetTaskStateAck : public CServerFuncAck
	{
		UINT16 wServerNo; //区服ID
		ETaskState eTaskState; //状态返回

		SGetTaskStateAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：任务集市中任务状态查询
	virtual bool OnRecv_GetTaskState(
		UINT16 wServerNo, //区服ID
		UINT64 qwUserID, //玩家ID
		UINT32 dwTaskID, //任务ID
		UINT8 byStep, //步骤ID
		ETaskOpt eTaskOpt, //任务操作
		shared_func<SGetTaskStateAck>& fnAck //返回回调函数
	) = 0;

	struct SSynWeiweiPersonNumAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SSynWeiweiPersonNumAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：同步微信微博人数
	virtual bool OnRecv_SynWeiweiPersonNum(
		UINT16 wServerNo, //区服ID
		UINT64 qwUserID, //玩家ID
		UINT8 byType, //任务ID
		UINT32 dwCount, //步骤ID
		shared_func<SSynWeiweiPersonNumAck>& fnAck //返回回调函数
	) = 0;

	struct SCheckCDKAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SCheckCDKAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：检测CDK
	virtual bool OnRecv_CheckCDK(
		UINT16 wServerNo, //区服ID
		UINT64 qwUserID, //玩家ID
		const std::string& strCDK, //CDK码
		shared_func<SCheckCDKAck>& fnAck //返回回调函数
	) = 0;

	struct SSynQQAlarmAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SSynQQAlarmAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：QQAlarm安装
	virtual bool OnRecv_SynQQAlarm(
		UINT16 wServerNo, //区服ID
		UINT64 qwUserID, //玩家ID
		shared_func<SSynQQAlarmAck>& fnAck //返回回调函数
	) = 0;

	struct SModifyChestAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SModifyChestAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：天赐宝箱活动参数修改
	virtual bool OnRecv_ModifyChest(
		const SChestInfo& sInfo, //数据
		shared_func<SModifyChestAck>& fnAck //返回回调函数
	) = 0;

	struct SSetPoolAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SSetPoolAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：设置汇灵盏奖励池
	virtual bool OnRecv_SetPool(
		UINT8 byType, //类型，0表示设置奖励池最大值，1表示设置奖励池现有值
		UINT32 dwValue, //数据
		shared_func<SSetPoolAck>& fnAck //返回回调函数
	) = 0;

	struct SGetLoginDaysAck : public CServerFuncAck
	{
		UINT32 dwDays; //累计登入天数
		EOptResult eOptResult; //后台操作结果

		SGetLoginDaysAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求玩家累计登入天数
	virtual bool OnRecv_GetLoginDays(
		UINT16 wServerNo, //区服ID
		UINT64 qwUserID, //玩家ID
		shared_func<SGetLoginDaysAck>& fnAck //返回回调函数
	) = 0;

	struct SSendQQGroupMsgAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SSendQQGroupMsgAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：发送工会聊天信息
	virtual bool OnRecv_SendQQGroupMsg(
		UINT64 qwGroupUserID, //绑定qq的玩家ID
		UINT16 wServerNo, //聊天玩家区号ID
		UINT64 qwUserID, //聊天玩家账号ID
		const std::string& strChatMsg, //聊天
		shared_func<SSendQQGroupMsgAck>& fnAck //返回回调函数
	) = 0;

	struct SSendTitleAck : public CServerFuncAck
	{
		EOptResult eOptResult; //后台操作结果

		SSendTitleAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：添加称号
	virtual bool OnRecv_SendTitle(
		UINT16 wServerNo, //区服ID
		UINT64 qwUserID, //玩家ID
		UINT16 wTitleID, //TitleID
		shared_func<SSendTitleAck>& fnAck //返回回调函数
	) = 0;

	//接收：Test
	virtual void OnRecv_TestPHP(
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 90; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_OnUserRecharge(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ModifyActivityIntegral(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPlayerInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPlayerBagInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DelItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetActList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OpenAct(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LockOrUnlockUser(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LockOrUnlockSpeak(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetOnlineNum(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SubMoney(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendVIPItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendClanItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GlobalSendItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendMail(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GlobalSendMail(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GlobalSendNotice(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GlobalDelNotice(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GlobalSendSysDialog(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OpenDiscountActivity(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetPlayerLevel(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetPlayerVIPLevel(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TaskManager(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_PlatformInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetTaskState(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SynWeiweiPersonNum(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CheckCDK(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SynQQAlarm(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ModifyChest(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetPool(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetLoginDays(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendQQGroupMsg(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendTitle(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TestPHP(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CPHPProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NPHPProt
