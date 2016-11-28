/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterComm.h
//  Purpose:      GameServer到CenterServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Game2CenterComm.h"

namespace NGame2CenterComm
{

//协议类：GameServer到CenterServer的通信协议
class CGame2CenterCommClt : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：心跳
	bool Send_KeepAlive( //发送给当前协议处理的服务器
	);
	bool SendSvr_KeepAlive(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_KeepAlive( //只组包不发送
	);

	//发送：GameServer初始化完成通知
	bool Send_GameSvrInitNft( //发送给当前协议处理的服务器
	);
	bool SendSvr_GameSvrInitNft(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_GameSvrInitNft( //只组包不发送
	);

	//发送：CenterServer状态请求
	bool Send_GetCenterState( //发送给当前协议处理的服务器
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetCenterState(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：GameServer数据同步请求
	bool Send_GameSvrDataSyncReq( //发送给当前协议处理的服务器
		ESyncKey eSyncKey, //同步Key
		UINT16 wDestGroup, //目的服务器组号
		UINT8 byDestIndex, //目的GameServer(0为全部)
		const TVecINT32& vecParam, //同步参数
		const std::string& strSyncData //同步数据
	);
	bool SendSvr_GameSvrDataSyncReq(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		ESyncKey eSyncKey, //同步Key
		UINT16 wDestGroup, //目的服务器组号
		UINT8 byDestIndex, //目的GameServer(0为全部)
		const TVecINT32& vecParam, //同步参数
		const std::string& strSyncData //同步数据
	);
	std::string& BuildPkg_GameSvrDataSyncReq( //只组包不发送
		ESyncKey eSyncKey, //同步Key
		UINT16 wDestGroup, //目的服务器组号
		UINT8 byDestIndex, //目的GameServer(0为全部)
		const TVecINT32& vecParam, //同步参数
		const std::string& strSyncData //同步数据
	);

	//发送：账号进入游戏通知
	bool Send_UserLoginNtf( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //账号ID
		const SUserEnterInfo& rUserInfo //帐号进入信息
	);
	bool SendSvr_UserLoginNtf(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //账号ID
		const SUserEnterInfo& rUserInfo //帐号进入信息
	);
	std::string& BuildPkg_UserLoginNtf( //只组包不发送
		UINT64 qwUsrID, //账号ID
		const SUserEnterInfo& rUserInfo //帐号进入信息
	);

	//发送：账号退出游戏通知
	bool Send_UserLogoutNtf( //发送给当前协议处理的服务器
		UINT64 qwUsrID //账号ID
	);
	bool SendSvr_UserLogoutNtf(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID //账号ID
	);
	std::string& BuildPkg_UserLogoutNtf( //只组包不发送
		UINT64 qwUsrID //账号ID
	);

	//发送：账号替换通知
	bool Send_UserReplaceNtf( //发送给当前协议处理的服务器
		UINT64 qwUsrID //账号ID
	);
	bool SendSvr_UserReplaceNtf(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID //账号ID
	);
	std::string& BuildPkg_UserReplaceNtf( //只组包不发送
		UINT64 qwUsrID //账号ID
	);

	//发送：帐号跳GameServer通知
	bool Send_UserJumpSvrNtf( //发送给当前协议处理的服务器
		UINT64 qwUsrID //账号ID
	);
	bool SendSvr_UserJumpSvrNtf(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID //账号ID
	);
	std::string& BuildPkg_UserJumpSvrNtf( //只组包不发送
		UINT64 qwUsrID //账号ID
	);

	//发送：玩家同步属性通知
	bool Send_UserSyncPropNtf( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //账号ID
		EUserSyncPropField eField, //同步属性类型
		const std::string& strVal //值序列化字符串
	);
	bool SendSvr_UserSyncPropNtf(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //账号ID
		EUserSyncPropField eField, //同步属性类型
		const std::string& strVal //值序列化字符串
	);
	std::string& BuildPkg_UserSyncPropNtf( //只组包不发送
		UINT64 qwUsrID, //账号ID
		EUserSyncPropField eField, //同步属性类型
		const std::string& strVal //值序列化字符串
	);

	//发送：是否为好友
	bool Send_IsFriend( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //账号ID
		UINT64 qwFriID, //好友账号ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet //(返回值)0是好友 1非好友
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_IsFriend(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //账号ID
		UINT64 qwFriID, //好友账号ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet //(返回值)0是好友 1非好友
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：是否在同一个帮派
	bool Send_IsSameGuild( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //账号ID
		UINT64 qwOtherID, //帮派成员ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet //(返回值)0在同一个帮派 1不在同一个帮派
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_IsSameGuild(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //账号ID
		UINT64 qwOtherID, //帮派成员ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet //(返回值)0在同一个帮派 1不在同一个帮派
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：发送系统邮件,自定义字符串
	bool Send_SendMail( //发送给当前协议处理的服务器
		const std::string& strSender, //发送者
		const std::string& strTitle, //标题
		const NMailProt::SysMailSendTxt& strMsgInfo, //内容
		const NMailProt::TVecMailAttachment& vecItemInfo, //物品信息
		const TVecUINT64& vecTargetIDs //接受者IDs
	);
	bool SendSvr_SendMail(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const std::string& strSender, //发送者
		const std::string& strTitle, //标题
		const NMailProt::SysMailSendTxt& strMsgInfo, //内容
		const NMailProt::TVecMailAttachment& vecItemInfo, //物品信息
		const TVecUINT64& vecTargetIDs //接受者IDs
	);
	std::string& BuildPkg_SendMail( //只组包不发送
		const std::string& strSender, //发送者
		const std::string& strTitle, //标题
		const NMailProt::SysMailSendTxt& strMsgInfo, //内容
		const NMailProt::TVecMailAttachment& vecItemInfo, //物品信息
		const TVecUINT64& vecTargetIDs //接受者IDs
	);

	//发送：获取帮派ID
	bool Send_GetGuildID( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwGuildID, //(返回值)帮派ID
			const std::string& strGuildName, //(返回值)帮派名称
			UINT8 byGuildLvl, //(返回值)帮派等级
			const std::string& strGuildOwnerName //(返回值)帮主名称
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetGuildID(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwGuildID, //(返回值)帮派ID
			const std::string& strGuildName, //(返回值)帮派名称
			UINT8 byGuildLvl, //(返回值)帮派等级
			const std::string& strGuildOwnerName //(返回值)帮主名称
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：获取帮派ID
	bool Send_GetGuildName( //发送给当前协议处理的服务器
		UINT64 qwGuildID, //帮派ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			bool bValid, //(返回值)是否已经找到
			UINT64 qwGuildID, //(返回值)帮派ID
			const std::string& strGuildName, //(返回值)帮派名称
			UINT8 byGuildLvl, //(返回值)帮派等级
			const std::string& strGuildOwnerName //(返回值)帮主名称
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetGuildName(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwGuildID, //帮派ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			bool bValid, //(返回值)是否已经找到
			UINT64 qwGuildID, //(返回值)帮派ID
			const std::string& strGuildName, //(返回值)帮派名称
			UINT8 byGuildLvl, //(返回值)帮派等级
			const std::string& strGuildOwnerName //(返回值)帮主名称
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：帮派广播
	bool Send_NotifyGuildInfo( //发送给当前协议处理的服务器
		UINT64 qwGuildID, //帮派ID
		const TVecUINT64& vecExcpRoleID, //不需要通知的人ID
		const std::string& strData //具体信息
	);
	bool SendSvr_NotifyGuildInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwGuildID, //帮派ID
		const TVecUINT64& vecExcpRoleID, //不需要通知的人ID
		const std::string& strData //具体信息
	);
	std::string& BuildPkg_NotifyGuildInfo( //只组包不发送
		UINT64 qwGuildID, //帮派ID
		const TVecUINT64& vecExcpRoleID, //不需要通知的人ID
		const std::string& strData //具体信息
	);

	//发送：同步增加icon
	bool Send_SynIconAppear( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //角色ID
		const std::string& szIcon //功能
	);
	bool SendSvr_SynIconAppear(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //角色ID
		const std::string& szIcon //功能
	);
	std::string& BuildPkg_SynIconAppear( //只组包不发送
		UINT64 qwRoleID, //角色ID
		const std::string& szIcon //功能
	);

	//发送：增加帮派贡献
	bool Send_AddGuildContribution( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		UINT32 dwContribution //帮派贡献
	);
	bool SendSvr_AddGuildContribution(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		UINT32 dwContribution //帮派贡献
	);
	std::string& BuildPkg_AddGuildContribution( //只组包不发送
		UINT64 qwRoleID, //玩家ID
		UINT32 dwContribution //帮派贡献
	);

	//发送：增加玩家九疑鼎火种
	bool Send_ActiveTripodFire( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		UINT16 wFireID //火种ID
	);
	bool SendSvr_ActiveTripodFire(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		UINT16 wFireID //火种ID
	);
	std::string& BuildPkg_ActiveTripodFire( //只组包不发送
		UINT64 qwRoleID, //玩家ID
		UINT16 wFireID //火种ID
	);

	//发送：更新登录参数
	bool Send_UpdatePlatformParam( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		const NProtoCommon::TVecPlatformParam& vecPlatform, //平台参数列表
		UINT32 dwIndex //当前平台索引
	);
	bool SendSvr_UpdatePlatformParam(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		const NProtoCommon::TVecPlatformParam& vecPlatform, //平台参数列表
		UINT32 dwIndex //当前平台索引
	);
	std::string& BuildPkg_UpdatePlatformParam( //只组包不发送
		UINT64 qwRoleID, //玩家ID
		const NProtoCommon::TVecPlatformParam& vecPlatform, //平台参数列表
		UINT32 dwIndex //当前平台索引
	);

	//发送：更新登录其他参数
	bool Send_UpdateEnterString( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		const TVecString& vecEnterString //平台参数列表
	);
	bool SendSvr_UpdateEnterString(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		const TVecString& vecEnterString //平台参数列表
	);
	std::string& BuildPkg_UpdateEnterString( //只组包不发送
		UINT64 qwRoleID, //玩家ID
		const TVecString& vecEnterString //平台参数列表
	);

	//发送：发送全服活动信息
	bool Send_SendWonderType( //发送给当前协议处理的服务器
		EWonderActType eActType, //活动类型
		UINT64 qwRoleID, //玩家ID
		UINT32 dwCond //条件ID
	);
	bool SendSvr_SendWonderType(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		EWonderActType eActType, //活动类型
		UINT64 qwRoleID, //玩家ID
		UINT32 dwCond //条件ID
	);
	std::string& BuildPkg_SendWonderType( //只组包不发送
		EWonderActType eActType, //活动类型
		UINT64 qwRoleID, //玩家ID
		UINT32 dwCond //条件ID
	);

	//发送：扣除帮贡
	bool Send_SubGuildContribution( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		UINT32 dwContribution, //帮贡数量
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			NGuildProt::EGuildResult eResult //(返回值)检测结果
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_SubGuildContribution(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		UINT32 dwContribution, //帮贡数量
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			NGuildProt::EGuildResult eResult //(返回值)检测结果
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：美女抽奖log
	bool Send_BeautyLotteryLog( //发送给当前协议处理的服务器
		const NBeautyLogGS::SBeautyLog& oBeautyLog //抽奖log
	);
	bool SendSvr_BeautyLotteryLog(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NBeautyLogGS::SBeautyLog& oBeautyLog //抽奖log
	);
	std::string& BuildPkg_BeautyLotteryLog( //只组包不发送
		const NBeautyLogGS::SBeautyLog& oBeautyLog //抽奖log
	);

	//发送：邀请好友成功
	bool Send_InviteFriend( //发送给当前协议处理的服务器
		UINT64 qwUserID, //邀请人
		UINT64 qwInvitedUserID //被邀请人
	);
	bool SendSvr_InviteFriend(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID, //邀请人
		UINT64 qwInvitedUserID //被邀请人
	);
	std::string& BuildPkg_InviteFriend( //只组包不发送
		UINT64 qwUserID, //邀请人
		UINT64 qwInvitedUserID //被邀请人
	);

	//发送：通知帮派兑换物品开始
	bool Send_NotifyGuildExchangedItemBegin( //发送给当前协议处理的服务器
		const TVecLingShanShopData& vecLingShanShopData //灵山商店数据
	);
	bool SendSvr_NotifyGuildExchangedItemBegin(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const TVecLingShanShopData& vecLingShanShopData //灵山商店数据
	);
	std::string& BuildPkg_NotifyGuildExchangedItemBegin( //只组包不发送
		const TVecLingShanShopData& vecLingShanShopData //灵山商店数据
	);

	//发送：同步在Center使用的buff结束时间(待修改完善)
	bool Send_SyncGameBuffUseInCenter( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		UINT16 wBuffID, //buffID
		UINT32 dwEndTime //结束时间
	);
	bool SendSvr_SyncGameBuffUseInCenter(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		UINT16 wBuffID, //buffID
		UINT32 dwEndTime //结束时间
	);
	std::string& BuildPkg_SyncGameBuffUseInCenter( //只组包不发送
		UINT64 qwRoleID, //玩家ID
		UINT16 wBuffID, //buffID
		UINT32 dwEndTime //结束时间
	);

	//发送：同步活动参数
	bool Send_SyncGameActiveParam( //发送给当前协议处理的服务器
		ActiveParam eParam, //参数类型
		const TVecUINT32& vecParam //参数
	);
	bool SendSvr_SyncGameActiveParam(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		ActiveParam eParam, //参数类型
		const TVecUINT32& vecParam //参数
	);
	std::string& BuildPkg_SyncGameActiveParam( //只组包不发送
		ActiveParam eParam, //参数类型
		const TVecUINT32& vecParam //参数
	);

	//发送：获取全局Var值
	bool Send_GetSystemVar( //发送给当前协议处理的服务器
		const TVecUINT16& vecVarID, //varID列表
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const TVecUINT16& vecVars, //(返回值)varID列表
			const TVecUINT64& vecValues //(返回值)var数值列表(必须与vecVars对应)
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetSystemVar(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const TVecUINT16& vecVarID, //varID列表
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const TVecUINT16& vecVars, //(返回值)varID列表
			const TVecUINT64& vecValues //(返回值)var数值列表(必须与vecVars对应)
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：设置全局Var值
	bool Send_SetSystemVar( //发送给当前协议处理的服务器
		const TVecUINT16& vecVars, //varID列表
		const TVecUINT64& vecValues, //var数值列表(必须与vecVars对应)
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const TVecUINT16& vecVarID //(返回值)设置成功的varID列表(只是校验用)
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_SetSystemVar(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const TVecUINT16& vecVars, //varID列表
		const TVecUINT64& vecValues, //var数值列表(必须与vecVars对应)
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const TVecUINT16& vecVarID //(返回值)设置成功的varID列表(只是校验用)
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SReplaceUserAck : public CServerFuncAck
	{
		SReplaceUserAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：替换帐号
	virtual bool OnRecv_ReplaceUser(
		UINT64 qwUsrID, //帐号ID
		shared_func<SReplaceUserAck>& fnAck //返回回调函数
	) = 0;

	struct SGMCmdAck : public CServerFuncAck
	{
		SGMCmdAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：GM指令
	virtual bool OnRecv_GMCmd(
		UINT64 qwUsrID, //帐号ID
		const std::string& strInfo, //GM指令信息
		shared_func<SGMCmdAck>& fnAck //返回回调函数
	) = 0;

	struct SAddTotalRechargeAck : public CServerFuncAck
	{
		SAddTotalRechargeAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：充值接口
	virtual bool OnRecv_AddTotalRecharge(
		const NRoleInfoDefine::SRecharge& oRecharge, //充值仙石的数据
		const std::string& strUdp1, //udpLog参数1(平台传来的)
		const std::string& strUdp2, //udpLog参数2(平台传来的)
		shared_func<SAddTotalRechargeAck>& fnAck //返回回调函数
	) = 0;

	struct SAddRechargeMailItemAck : public CServerFuncAck
	{
		SAddRechargeMailItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：充值接口(改版:加仙石礼包到邮件)
	virtual bool OnRecv_AddRechargeMailItem(
		const NRoleInfoDefine::SRecharge& oRecharge, //充值仙石的数据
		const std::string& strUdp1, //udpLog参数1(平台传来的)
		const std::string& strUdp2, //udpLog参数2(平台传来的)
		shared_func<SAddRechargeMailItemAck>& fnAck //返回回调函数
	) = 0;

	struct SAddTotalPrepaidAck : public CServerFuncAck
	{
		SAddTotalPrepaidAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：补偿玩家未创建预先充值的仙石
	virtual bool OnRecv_AddTotalPrepaid(
		UINT64 qwUsrID, //帐号ID
		UINT32 dwGold, //仙石数量
		shared_func<SAddTotalPrepaidAck>& fnAck //返回回调函数
	) = 0;

	struct SAddQQCoinBuyItemAck : public CServerFuncAck
	{
		SAddQQCoinBuyItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：Q点直购道具
	virtual bool OnRecv_AddQQCoinBuyItem(
		UINT64 qwUsrID, //帐号ID
		const TVecUserItem& vecUserItem, //物品列表
		shared_func<SAddQQCoinBuyItemAck>& fnAck //返回回调函数
	) = 0;

	struct SCheckMailAttchAck : public CServerFuncAck
	{
		UINT8 byCan; //0表示可以提取

		SCheckMailAttchAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：询问可否提取附件
	virtual bool OnRecv_CheckMailAttch(
		UINT64 qwUsrID, //帐号ID
		UINT64 qwMailID, //邮件ID
		const NMailProt::TVecMailAttachment& vecItemInfo, //附件
		shared_func<SCheckMailAttchAck>& fnAck //返回回调函数
	) = 0;

	//接收：发送附件
	virtual void OnRecv_SendMailAttch(
		UINT64 qwUsrID, //帐号ID
		UINT64 qwMailID, //邮件ID
		const NMailProt::TVecMailAttachment& vecItemInfo //附件
	) = 0;

	//接收：修改签名
	virtual void OnRecv_SetSign(
		UINT64 qwUsrID, //帐号ID
		const std::string& strSign //签名
	) = 0;

	//接收：修改表情
	virtual void OnRecv_SetMood(
		UINT64 qwUsrID, //帐号ID
		UINT16 wMood //表情
	) = 0;

	struct SFigtherToOtherAck : public CServerFuncAck
	{
		UINT8 byRet; //请求结果
		UINT8 bySuc; //是否胜利
		UINT64 qwBattleID; //战报ID
		UINT32 dwSelfFighterPower; //自己的战斗力
		UINT8 bySelfQuality; //自己的主将品质
		UINT32 dwOtherFighterPower; //他人的战斗力
		UINT8 byOtherQuality; //他人的主将品质
		UINT32 dwTurns; //战斗回合数

		SFigtherToOtherAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求和他人发起战斗
	virtual bool OnRecv_FigtherToOther(
		UINT64 qwUsrID, //帐号ID
		UINT64 qwOtherID, //他人的ID
		UINT32 dwCost, //花费的游戏币
		NBattleGS::EBattleType eBattleType, //战斗类型
		UINT32 dwBufferID, //临时增加的buffer
		UINT32 dwSkillAttrID, //增加的属性
		UINT32 dwCount, //buffer叠加层数
		shared_func<SFigtherToOtherAck>& fnAck //返回回调函数
	) = 0;

	struct SCanPushLootAck : public CServerFuncAck
	{
		UINT8 byRet; //0,可以，1，没有这个掉落，2，其他错误

		SCanPushLootAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：询问可否放下掉落
	virtual bool OnRecv_CanPushLoot(
		UINT64 qwUsrID, //帐号ID
		UINT32 dwLootId, //掉落的ID
		shared_func<SCanPushLootAck>& fnAck //返回回调函数
	) = 0;

	//接收：掉落到玩家包裹
	virtual void OnRecv_PushLoot(
		UINT64 qwUsrID, //帐号ID
		EOpSource eSource, //原因
		NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
		UINT32 dwLootId //掉落的ID
	) = 0;

	struct SReduceItemAck : public CServerFuncAck
	{
		UINT8 byRet; //0,可以,1，不足，2，其他错误

		SReduceItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：扣钱或物品
	virtual bool OnRecv_ReduceItem(
		UINT64 qwUsrID, //帐号ID
		NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
		UINT32 dwID, //钱或物品ID
		UINT32 dwCount, //数量
		shared_func<SReduceItemAck>& fnAck //返回回调函数
	) = 0;

	struct SCanReduceItemAck : public CServerFuncAck
	{
		UINT8 byRet; //0,可以,1，不足，2，其他错误

		SCanReduceItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：物品/资源数量是否够
	virtual bool OnRecv_CanReduceItem(
		UINT64 qwUsrID, //帐号ID
		UINT32 dwItemID, //物品ID
		UINT32 dwCount, //数量
		shared_func<SCanReduceItemAck>& fnAck //返回回调函数
	) = 0;

	struct SGetUserUINTPropAck : public CServerFuncAck
	{
		UINT32 dwValue; //属性值
		UINT8 byError; //0 成功, 其他错误

		SGetUserUINTPropAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：查询玩家属性
	virtual bool OnRecv_GetUserUINTProp(
		UINT64 qwUsrID, //帐号ID
		EPlayerUINTProp eUINTPropType, //属性类型
		shared_func<SGetUserUINTPropAck>& fnAck //返回回调函数
	) = 0;

	struct SSetUserUINTPropAck : public CServerFuncAck
	{
		UINT8 byError; //0 成功, 其他错误

		SSetUserUINTPropAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：设置玩家属性
	virtual bool OnRecv_SetUserUINTProp(
		UINT64 qwUsrID, //帐号ID
		EPlayerUINTProp eUINTPropType, //属性类型
		UINT32 dwValue, //属性值
		shared_func<SSetUserUINTPropAck>& fnAck //返回回调函数
	) = 0;

	struct SUserSubItemAck : public CServerFuncAck
	{
		UINT8 byError; //0 成功, 其他错误

		SUserSubItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：扣除物品/钱币
	virtual bool OnRecv_UserSubItem(
		UINT64 qwUsrID, //帐号ID
		NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
		const TVecUserItem& vecUserItem, //物品列表
		shared_func<SUserSubItemAck>& fnAck //返回回调函数
	) = 0;

	struct SUserAddItemAck : public CServerFuncAck
	{
		UINT8 byError; //0 成功, 其他错误

		SUserAddItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：添加物品/钱币
	virtual bool OnRecv_UserAddItem(
		UINT64 qwUsrID, //帐号ID
		NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
		const TVecUserItem& vecUserItem, //物品列表
		shared_func<SUserAddItemAck>& fnAck //返回回调函数
	) = 0;

	//接收：转发系统消息
	virtual void OnRecv_SendSysMsg(
		UINT64 qwUsrID, //帐号ID
		UINT16 wMsgID //消息ID
	) = 0;

	//接收：任务事件通知
	virtual void OnRecv_ActionNotify(
		UINT64 qwUsrID, //帐号ID
		UINT16 wAction //通知类型
	) = 0;

	//接收：气泡事件通知
	virtual void OnRecv_BubbleNotify(
		UINT64 qwUsrID, //帐号ID
		NProtoCommon::EDataChange eType, //修改类型
		UINT16 wMsgID, //通知类型
		const TVecINT64& vecParam, //整型变量
		const TVecString& vecString //字符串型变量
	) = 0;

	//接收：玩家帮派等级更新
	virtual void OnRecv_GuildLevelUpdated(
		UINT64 qwRoleID, //玩家ID
		UINT16 wLevel //帮派等级
	) = 0;

	//接收：玩家帮派名有更新
	virtual void OnRecv_GuildNameUpdated(
		UINT64 qwRoleID, //玩家ID
		const std::string& strGuildName //帮派名称
	) = 0;

	//接收：帮派技能属性更新
	virtual void OnRecv_GuildTechUpdate(
		UINT64 qwRoleID, //玩家唯一ID
		const NProtoCommon::TVecFtAttrMod& vecFtAttr, //玩家的帮派技能属性
		const NGuildProt::TVecGuildTechInfo& vecGuildTech //玩家的帮派技能信息
	) = 0;

	//接收：重新加载表格
	virtual void OnRecv_ReloadTable(
		const TVecString& vecTableName //表格名字
	) = 0;

	//接收：玩家九疑鼎属性更新
	virtual void OnRecv_TripodAttrUpdate(
		UINT64 qwRoleID, //玩家唯一ID
		const TVecUINT32& vecValue //九疑鼎ID、等级
	) = 0;

	struct SProcessCondAck : public CServerFuncAck
	{
		UINT8 byError; //0 成功, 1 其他错误

		SProcessCondAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：完成GetCond条件
	virtual bool OnRecv_ProcessCond(
		UINT64 qwUsrID, //玩家ID
		UINT16 wCondID, //条件ID
		NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
		shared_func<SProcessCondAck>& fnAck //返回回调函数
	) = 0;

	struct SUpgradeTripodAck : public CServerFuncAck
	{
		UINT8 byError; //0 成功, 1 其他错误
		UINT8 byLevel; //九疑鼎当前等级
		UINT32 dwExp; //九疑鼎当前经验值

		SUpgradeTripodAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家升级九疑鼎
	virtual bool OnRecv_UpgradeTripod(
		UINT64 qwUsrID, //玩家ID
		UINT8 byTripodID, //九疑鼎ID
		UINT8 byLevel, //九疑鼎当前等级
		UINT32 dwExp, //九疑鼎当前经验值
		UINT8 byOneKey, //是否一键
		shared_func<SUpgradeTripodAck>& fnAck //返回回调函数
	) = 0;

	struct SSpeedTripodAck : public CServerFuncAck
	{
		UINT8 byError; //0 成功, 1 其他错误
		UINT32 dwSoul; //九疑鼎增加的元气值

		SSpeedTripodAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：加速九疑鼎炼丹(道具入鼎)
	virtual bool OnRecv_SpeedTripod(
		UINT64 qwUsrID, //玩家ID
		UINT32 dwCurSoul, //当前九疑鼎的火种元气值
		UINT32 dwMaxSoul, //当前九疑鼎的火种最大元气值(配置)
		const NItemProt::TVecItemCount& vecItems, //入鼎道具列表
		shared_func<SSpeedTripodAck>& fnAck //返回回调函数
	) = 0;

	struct SCheckHasFighterAck : public CServerFuncAck
	{
		UINT8 byError; //0 拥有, 1 其他错误
		UINT8 byColor; //散仙品质

		SCheckHasFighterAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：判断玩家是否拥有散仙
	virtual bool OnRecv_CheckHasFighter(
		UINT64 qwUsrID, //玩家ID
		UINT16 wFighterID, //散仙ID
		shared_func<SCheckHasFighterAck>& fnAck //返回回调函数
	) = 0;

	struct SGetBattlePointAck : public CServerFuncAck
	{
		UINT8 byError; //0 成功, 1 其他错误
		UINT32 dwBattlePoint; //玩家战斗力

		SGetBattlePointAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取战斗力
	virtual bool OnRecv_GetBattlePoint(
		UINT64 qwUsrID, //玩家ID
		shared_func<SGetBattlePointAck>& fnAck //返回回调函数
	) = 0;

	//接收：玩家发事件中心消息
	virtual void OnRecv_OnPlayerEvent(
		UINT64 qwUsrID, //玩家ID
		NEventCenter::EventType eEventType, //事件类型
		const TVecINT32& vecParam, //事件参数
		const std::string& strParam, //事件参数
		bool bLog //事件参数
	) = 0;

	//接收：增加或者设置玩家GameVar数值
	virtual void OnRecv_AddORSetGameVar(
		UINT64 qwUsrID, //玩家ID
		UINT8 byType, //0增加 >0设置
		const TVecUINT16& vecVars, //varID列表
		const TVecUINT64& vecValues //var数值列表(必须与vecVars对应)
	) = 0;

	//接收：清除玩家GameVar
	virtual void OnRecv_DeleteGameVar(
		UINT64 qwUsrID, //玩家ID
		const TVecUINT16& vecVars //varID列表
	) = 0;

	//接收：增加商城限购活动
	virtual void OnRecv_AddMallDiscount(
		const NMallProt::SDiscount& oDiscount //限购道具列表
	) = 0;

	//接收：清除商城限购活动
	virtual void OnRecv_ClearMallDiscount(
		UINT8 byPos //限购道具栏位
	) = 0;

	struct SSubPlayerMoneyAck : public CServerFuncAck
	{
		SSubPlayerMoneyAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：扣除多个玩家钱币/物品
	virtual bool OnRecv_SubPlayerMoney(
		const TVecUINT64& vecUserID, //玩家ID
		const TVecUserItem& vecUserItem, //物品列表
		shared_func<SSubPlayerMoneyAck>& fnAck //返回回调函数
	) = 0;

	struct SSetPlayerLevelAck : public CServerFuncAck
	{
		SSetPlayerLevelAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：设置玩家等级
	virtual bool OnRecv_SetPlayerLevel(
		UINT64 qwUsrID, //玩家ID
		UINT16 wLevel, //玩家等级
		shared_func<SSetPlayerLevelAck>& fnAck //返回回调函数
	) = 0;

	struct SSetPlayerVIPLevelAck : public CServerFuncAck
	{
		SSetPlayerVIPLevelAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：设置玩家VIP等级
	virtual bool OnRecv_SetPlayerVIPLevel(
		UINT64 qwUsrID, //玩家ID
		NPHPProt::EOptType eOptType, //台台操作类型(eOptSetPlayerVIPLevel/eOptAddGrowthValue)
		UINT32 dwLevelOrGrowthValue, //等级or成长值
		shared_func<SSetPlayerVIPLevelAck>& fnAck //返回回调函数
	) = 0;

	struct SSetDayTaskAck : public CServerFuncAck
	{
		SSetDayTaskAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：设置日常任务
	virtual bool OnRecv_SetDayTask(
		const TVecUINT64& vecUserID, //玩家ID
		NPHPProt::EPHPTaskType eTaskType, //日常任务类型
		shared_func<SSetDayTaskAck>& fnAck //返回回调函数
	) = 0;

	struct SGetPlayerInfoAck : public CServerFuncAck
	{
		NPHPProt::SPlayerInfo sPlayerInfo; //返回的数据

		SGetPlayerInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取玩家信息
	virtual bool OnRecv_GetPlayerInfo(
		UINT64 qwUserID, //玩家ID
		shared_func<SGetPlayerInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetPlayerBagInfoAck : public CServerFuncAck
	{
		NPHPProt::TVecPlayerBagInfo vecPlayerBagInfo; //返回的数据

		SGetPlayerBagInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取玩家背包信息
	virtual bool OnRecv_GetPlayerBagInfo(
		UINT64 qwUserID, //玩家ID
		shared_func<SGetPlayerBagInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SDelPlayerItemAck : public CServerFuncAck
	{
		SDelPlayerItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：删除玩家物品
	virtual bool OnRecv_DelPlayerItem(
		UINT64 qwUserID, //用户ID
		UINT8 byType, //1；背包，2：仓库
		UINT64 qwInstID, //物品唯一ID
		UINT16 wCount, //堆叠数
		shared_func<SDelPlayerItemAck>& fnAck //返回回调函数
	) = 0;

	//接收：给玩家用掉落包发系统邮件
	virtual void OnRecv_SendSysMailByLootId(
		UINT64 qwUserID, //用户ID
		UINT16 wTitle, //邮件标题
		UINT16 wText, //邮件正文
		const TVecString& vecParam, //邮件参数
		UINT32 dwLootId, //掉落包
		UINT32 dwRate //倍率
	) = 0;

	struct SGetTaskStateForPlatfromAck : public CServerFuncAck
	{
		NPHPProt::ETaskState eRet; //返回的数据

		SGetTaskStateForPlatfromAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：任务集市
	virtual bool OnRecv_GetTaskStateForPlatfrom(
		UINT64 qwUserID, //用户ID
		UINT32 dwTaskID, //邮件标题
		UINT8 byStep, //邮件正文
		UINT8 byOpt, //邮件正文
		shared_func<SGetTaskStateForPlatfromAck>& fnAck //返回回调函数
	) = 0;

	//接收：同步微信微博人数
	virtual void OnRecv_SynWeiweiPersonNum(
		UINT64 qwUserID, //玩家ID
		UINT8 byType, //类型
		UINT32 dwCount //人数
	) = 0;

	//接收：检测CDK
	virtual void OnRecv_CheckCDK(
		UINT64 qwUserID, //玩家ID
		const std::string& strCDK //CDK码
	) = 0;

	//接收：QQAlarm安装
	virtual void OnRecv_SynQQAlarm(
		UINT64 qwUserID //玩家ID
	) = 0;

	//接收：运营修改宝箱信息
	virtual void OnRecv_ModifyChest(
		const NPHPProt::SChestInfo& sChestInfo //信息
	) = 0;

	//接收：Center2Game活动时间同步
	virtual void OnRecv_SyncActivityTime(
		const NProtoCommon::SActivityTime& sActTime //信息
	) = 0;

	struct SGetLoginDaysAck : public CServerFuncAck
	{
		UINT32 dwDays; //天数

		SGetLoginDaysAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求累计登入天数
	virtual bool OnRecv_GetLoginDays(
		UINT64 qwUserID, //玩家ID
		shared_func<SGetLoginDaysAck>& fnAck //返回回调函数
	) = 0;

	//接收：同步活动状态
	virtual void OnRecv_SyncActState(
		const SActivityState& oInfo, //数据
		bool bNotify //是否通知全服
	) = 0;

	//接收：添加Title
	virtual void OnRecv_SyncTitle(
		UINT64 qwUserID, //玩家ID
		UINT16 wTitleID //添加Title
	) = 0;

	struct SSubGoldOrCouponAck : public CServerFuncAck
	{
		UINT8 byError; //0 成功, 其他错误

		SSubGoldOrCouponAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：扣除礼卷钻石
	virtual bool OnRecv_SubGoldOrCoupon(
		UINT64 qwUsrID, //帐号ID
		NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
		UINT32 dwCount, //扣款数量
		shared_func<SSubGoldOrCouponAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID) override;

	virtual UINT8 GetProtID() const override { return 12; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_ReplaceUser(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GMCmd(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddTotalRecharge(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddRechargeMailItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddTotalPrepaid(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddQQCoinBuyItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CheckMailAttch(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendMailAttch(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetSign(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetMood(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FigtherToOther(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CanPushLoot(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_PushLoot(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReduceItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CanReduceItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetUserUINTProp(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetUserUINTProp(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserSubItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserAddItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendSysMsg(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ActionNotify(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BubbleNotify(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GuildLevelUpdated(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GuildNameUpdated(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GuildTechUpdate(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReloadTable(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TripodAttrUpdate(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ProcessCond(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpgradeTripod(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SpeedTripod(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CheckHasFighter(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetBattlePoint(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OnPlayerEvent(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddORSetGameVar(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DeleteGameVar(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddMallDiscount(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ClearMallDiscount(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SubPlayerMoney(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetPlayerLevel(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetPlayerVIPLevel(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetDayTask(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPlayerInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPlayerBagInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DelPlayerItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendSysMailByLootId(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetTaskStateForPlatfrom(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SynWeiweiPersonNum(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CheckCDK(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SynQQAlarm(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ModifyChest(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SyncActivityTime(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetLoginDays(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SyncActState(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SyncTitle(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SubGoldOrCoupon(const char* pBuf, UINT32 dwLen);

	/////////////////////协议返回函数/////////////////////
	bool _DoReturn_GetCenterState(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetCenterState(UINT32 dwSessionID);
	bool _DoReturn_IsFriend(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_IsFriend(UINT32 dwSessionID);
	bool _DoReturn_IsSameGuild(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_IsSameGuild(UINT32 dwSessionID);
	bool _DoReturn_GetGuildID(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetGuildID(UINT32 dwSessionID);
	bool _DoReturn_GetGuildName(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetGuildName(UINT32 dwSessionID);
	bool _DoReturn_SubGuildContribution(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_SubGuildContribution(UINT32 dwSessionID);
	bool _DoReturn_GetSystemVar(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetSystemVar(UINT32 dwSessionID);
	bool _DoReturn_SetSystemVar(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_SetSystemVar(UINT32 dwSessionID);

private:
	typedef bool (CGame2CenterCommClt::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _ReturnFuncs[];
	static THandleFunc _HandleFuncs[];

	typedef void (CGame2CenterCommClt::*TTimeOutFunc)(UINT32 dwSessionID);
	static TTimeOutFunc _TimeoutFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGame2CenterComm
