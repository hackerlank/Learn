/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    GuildProt.h
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "GuildProt.h"

namespace NGuildProt
{

//协议类：帮派相关协议
class CGuildProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：帮派创建结果通知
	bool Send_GuildCreateNotify( //发送给当前协议处理的客户端
		ECreateResult eResult, //创建结果
		const TVecGuildAllInfo& vecGuildInfo //帮派信息(大小为0或者1)
	);
	bool SendClt_GuildCreateNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		ECreateResult eResult, //创建结果
		const TVecGuildAllInfo& vecGuildInfo //帮派信息(大小为0或者1)
	);
	std::string& BuildPkg_GuildCreateNotify( //只组包不发送
		ECreateResult eResult, //创建结果
		const TVecGuildAllInfo& vecGuildInfo //帮派信息(大小为0或者1)
	);

	//发送：帮派信息更新
	bool Send_GuildInfoNotify( //发送给当前协议处理的客户端
		EGuildDataType eDataType, //帮派信息类型
		const TVecSGuildInfoBase& vecGuildInfoBase //帮派信息
	);
	bool SendClt_GuildInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EGuildDataType eDataType, //帮派信息类型
		const TVecSGuildInfoBase& vecGuildInfoBase //帮派信息
	);
	std::string& BuildPkg_GuildInfoNotify( //只组包不发送
		EGuildDataType eDataType, //帮派信息类型
		const TVecSGuildInfoBase& vecGuildInfoBase //帮派信息
	);

	//发送：帮派列表信息
	bool Send_GuildListInfoNotify( //发送给当前协议处理的客户端
		UINT32 dwMaxGuildCount, //最大帮派
		UINT32 dwCurGuildCount, //当前帮派索引
		const TVecGuildListInfo& vecGuildListInfo //帮派列表信息
	);
	bool SendClt_GuildListInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwMaxGuildCount, //最大帮派
		UINT32 dwCurGuildCount, //当前帮派索引
		const TVecGuildListInfo& vecGuildListInfo //帮派列表信息
	);
	std::string& BuildPkg_GuildListInfoNotify( //只组包不发送
		UINT32 dwMaxGuildCount, //最大帮派
		UINT32 dwCurGuildCount, //当前帮派索引
		const TVecGuildListInfo& vecGuildListInfo //帮派列表信息
	);

	//发送：帮派申请通过通知
	bool Send_GuildApplyPassedNotify( //发送给当前协议处理的客户端
		const SGuildAllInfo& sGuildAllInfo //帮派信息
	);
	bool SendClt_GuildApplyPassedNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SGuildAllInfo& sGuildAllInfo //帮派信息
	);
	std::string& BuildPkg_GuildApplyPassedNotify( //只组包不发送
		const SGuildAllInfo& sGuildAllInfo //帮派信息
	);

	//发送：帮派申请拒绝通知
	bool Send_GuildApplyRejectNotify( //发送给当前协议处理的客户端
		UINT64 qwGuildID //帮派ID
	);
	bool SendClt_GuildApplyRejectNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwGuildID //帮派ID
	);
	std::string& BuildPkg_GuildApplyRejectNotify( //只组包不发送
		UINT64 qwGuildID //帮派ID
	);

	//发送：帮派被踢出通知
	bool Send_GuildKickNotify( //发送给当前协议处理的客户端
		UINT64 qwGuildID, //帮派ID
		const std::string& strName, //帮派名称
		const std::string& strKickName //踢人者姓名
	);
	bool SendClt_GuildKickNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwGuildID, //帮派ID
		const std::string& strName, //帮派名称
		const std::string& strKickName //踢人者姓名
	);
	std::string& BuildPkg_GuildKickNotify( //只组包不发送
		UINT64 qwGuildID, //帮派ID
		const std::string& strName, //帮派名称
		const std::string& strKickName //踢人者姓名
	);

	//发送：玩家被邀请进入帮派通知
	bool Send_GuildInviteNotify( //发送给当前协议处理的客户端
		UINT64 qwGuildID, //帮派ID
		const std::string& strGuildName, //帮派名称
		const std::string& strInviterName //邀请者名称
	);
	bool SendClt_GuildInviteNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwGuildID, //帮派ID
		const std::string& strGuildName, //帮派名称
		const std::string& strInviterName //邀请者名称
	);
	std::string& BuildPkg_GuildInviteNotify( //只组包不发送
		UINT64 qwGuildID, //帮派ID
		const std::string& strGuildName, //帮派名称
		const std::string& strInviterName //邀请者名称
	);

	//发送：帮派弹劾通知
	bool Send_GuildImpeachNotify( //发送给当前协议处理的客户端
		UINT64 qwGuildID, //帮派ID
		const std::string& strLauncherName, //发起者姓名
		const std::string& strOwnerName //帮主姓名
	);
	bool SendClt_GuildImpeachNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwGuildID, //帮派ID
		const std::string& strLauncherName, //发起者姓名
		const std::string& strOwnerName //帮主姓名
	);
	std::string& BuildPkg_GuildImpeachNotify( //只组包不发送
		UINT64 qwGuildID, //帮派ID
		const std::string& strLauncherName, //发起者姓名
		const std::string& strOwnerName //帮主姓名
	);

	//发送：帮派弹劾取消通知
	bool Send_GuildImpeachSucceedNotify( //发送给当前协议处理的客户端
	);
	bool SendClt_GuildImpeachSucceedNotify(const UINT64* pUsrID, UINT16 wCnt //发送给多个客户端
	);
	std::string& BuildPkg_GuildImpeachSucceedNotify( //只组包不发送
	);

	//发送：帮派弹劾取消通知
	bool Send_GuildImpeachFailedNotify( //发送给当前协议处理的客户端
	);
	bool SendClt_GuildImpeachFailedNotify(const UINT64* pUsrID, UINT16 wCnt //发送给多个客户端
	);
	std::string& BuildPkg_GuildImpeachFailedNotify( //只组包不发送
	);

	//发送：帮派弹劾取消通知
	bool Send_GuildImpeachCancelNotify( //发送给当前协议处理的客户端
	);
	bool SendClt_GuildImpeachCancelNotify(const UINT64* pUsrID, UINT16 wCnt //发送给多个客户端
	);
	std::string& BuildPkg_GuildImpeachCancelNotify( //只组包不发送
	);

	//发送：更新玩家羲和神车信息
	bool Send_UpdateGuildXiheInfo( //发送给当前协议处理的客户端
		const SGuildXihe& sGuildXihe //玩家羲和神车信息
	);
	bool SendClt_UpdateGuildXiheInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SGuildXihe& sGuildXihe //玩家羲和神车信息
	);
	std::string& BuildPkg_UpdateGuildXiheInfo( //只组包不发送
		const SGuildXihe& sGuildXihe //玩家羲和神车信息
	);

	//发送：更新玩家羲和神车帮助信息
	bool Send_GuildXiheHelpNotify( //发送给当前协议处理的客户端
		UINT8 byType, //0增加请求帮助信息 1删除帮助列表的信息 2删除请求帮助信息添加XX帮助信息
		const SXiheRequest& sXiheRequest //玩家羲和神车请求帮助的信息
	);
	bool SendClt_GuildXiheHelpNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byType, //0增加请求帮助信息 1删除帮助列表的信息 2删除请求帮助信息添加XX帮助信息
		const SXiheRequest& sXiheRequest //玩家羲和神车请求帮助的信息
	);
	std::string& BuildPkg_GuildXiheHelpNotify( //只组包不发送
		UINT8 byType, //0增加请求帮助信息 1删除帮助列表的信息 2删除请求帮助信息添加XX帮助信息
		const SXiheRequest& sXiheRequest //玩家羲和神车请求帮助的信息
	);

	//发送：帮派兑换物品更新
	bool Send_GuildExchangedItemNotify( //发送给当前协议处理的客户端
		const TVecGuildExchangedItem& vecGuildExchangedItem, //兑换物品信息
		UINT32 dwGUildAllMemberExchangedItemNum, //帮派所有成员兑换物品总数量
		UINT32 dwPlayerExchangedItemNum //玩家兑换物品总数量
	);
	bool SendClt_GuildExchangedItemNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecGuildExchangedItem& vecGuildExchangedItem, //兑换物品信息
		UINT32 dwGUildAllMemberExchangedItemNum, //帮派所有成员兑换物品总数量
		UINT32 dwPlayerExchangedItemNum //玩家兑换物品总数量
	);
	std::string& BuildPkg_GuildExchangedItemNotify( //只组包不发送
		const TVecGuildExchangedItem& vecGuildExchangedItem, //兑换物品信息
		UINT32 dwGUildAllMemberExchangedItemNum, //帮派所有成员兑换物品总数量
		UINT32 dwPlayerExchangedItemNum //玩家兑换物品总数量
	);

	//发送：帮派战兑换物品开始
	bool Send_GuildExchangedItemBeginNotify( //发送给当前协议处理的客户端
		const TVecUINT8& vecLingShanType //灵山类型
	);
	bool SendClt_GuildExchangedItemBeginNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecUINT8& vecLingShanType //灵山类型
	);
	std::string& BuildPkg_GuildExchangedItemBeginNotify( //只组包不发送
		const TVecUINT8& vecLingShanType //灵山类型
	);

	//发送：帮派兑换物品日志更新
	bool Send_GuildExchangeItemLogNotify( //发送给当前协议处理的客户端
		const SGuildLogInfo& sGuildLogInfo //兑换物品日志信息
	);
	bool SendClt_GuildExchangeItemLogNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SGuildLogInfo& sGuildLogInfo //兑换物品日志信息
	);
	std::string& BuildPkg_GuildExchangeItemLogNotify( //只组包不发送
		const SGuildLogInfo& sGuildLogInfo //兑换物品日志信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetGuildInfoAck : public CClientFuncAck
	{
		SGetGuildInfoBasePtr sGuildInfoBase; //返回结果

		SGetGuildInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取帮派面板信息
	virtual bool OnRecv_GetGuildInfo(
		shared_func<SGetGuildInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetGuildListAck : public CClientFuncAck
	{
		EGuildResult eResult; //返回结果
		SOtherGuildListInfo sListInfo; //帮派列表信息

		SGetGuildListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获得帮派列表
	virtual bool OnRecv_GetGuildList(
		UINT32 dwIndex, //帮派索引
		UINT32 dwCount, //帮派个数
		shared_func<SGetGuildListAck>& fnAck //返回回调函数
	) = 0;

	struct SGetGuildApplyInfoAck : public CClientFuncAck
	{
		EGuildResult eResult; //返回结果
		TVecGuildApplyInfo vecApplyInfo; //申请列表

		SGetGuildApplyInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取帮派申请列表信息
	virtual bool OnRecv_GetGuildApplyInfo(
		shared_func<SGetGuildApplyInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SCreateGuildAck : public CClientFuncAck
	{
		ECreateResult eResult; //创建结果
		TVecGuildAllInfo vecGuildInfo; //帮派信息(大小为0或者1)

		SCreateGuildAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：创建帮派
	virtual bool OnRecv_CreateGuild(
		const std::string& strName, //帮派名称
		shared_func<SCreateGuildAck>& fnAck //返回回调函数
	) = 0;

	struct SApplyGuildAck : public CClientFuncAck
	{
		EApplyResult eResult; //申请列表信息

		SApplyGuildAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：申请加入帮派
	virtual bool OnRecv_ApplyGuild(
		UINT64 qwGuildID, //帮派ID
		shared_func<SApplyGuildAck>& fnAck //返回回调函数
	) = 0;

	struct SAgreeApplyAck : public CClientFuncAck
	{
		EApplyResult eResult; //返回结果

		SAgreeApplyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：通过加入申请
	virtual bool OnRecv_AgreeApply(
		UINT64 qwRoleID, //申请者ID
		shared_func<SAgreeApplyAck>& fnAck //返回回调函数
	) = 0;

	struct SAgreeApplyAllAck : public CClientFuncAck
	{
		EApplyResult eResult; //返回结果

		SAgreeApplyAllAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：全部同意
	virtual bool OnRecv_AgreeApplyAll(
		shared_func<SAgreeApplyAllAck>& fnAck //返回回调函数
	) = 0;

	struct SRejectApplyAck : public CClientFuncAck
	{
		EApplyResult eResult; //返回结果

		SRejectApplyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：拒绝加入申请
	virtual bool OnRecv_RejectApply(
		UINT64 qwRoleID, //申请者ID
		shared_func<SRejectApplyAck>& fnAck //返回回调函数
	) = 0;

	struct SRejectApplyAllAck : public CClientFuncAck
	{
		EApplyResult eResult; //返回结果

		SRejectApplyAllAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：全部拒绝
	virtual bool OnRecv_RejectApplyAll(
		shared_func<SRejectApplyAllAck>& fnAck //返回回调函数
	) = 0;

	struct SInviteApplyAck : public CClientFuncAck
	{
		EApplyResult eResult; //返回结果

		SInviteApplyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：邀请加入
	virtual bool OnRecv_InviteApply(
		const std::string& strName, //被邀请者名字
		shared_func<SInviteApplyAck>& fnAck //返回回调函数
	) = 0;

	struct SGetGuildApplyListAck : public CClientFuncAck
	{
		EApplyResult eResult; //返回结果
		TVecGuildListInfo vecGuildListInfo; //帮派列表信息

		SGetGuildApplyListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获得已申请帮派列表
	virtual bool OnRecv_GetGuildApplyList(
		shared_func<SGetGuildApplyListAck>& fnAck //返回回调函数
	) = 0;

	struct SCancelApplyAck : public CClientFuncAck
	{
		EApplyResult eResult; //返回结果

		SCancelApplyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：撤销帮派申请
	virtual bool OnRecv_CancelApply(
		UINT64 qwGuildID, //帮派ID
		shared_func<SCancelApplyAck>& fnAck //返回回调函数
	) = 0;

	struct SInviteReplyAck : public CClientFuncAck
	{
		EApplyResult eResult; //返回结果

		SInviteReplyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：邀请回应
	virtual bool OnRecv_InviteReply(
		UINT64 qwGuildID, //帮派ID
		bool bAgree, //同意/拒绝
		shared_func<SInviteReplyAck>& fnAck //返回回调函数
	) = 0;

	struct SQuitGuildAck : public CClientFuncAck
	{
		EQuitResult eResult; //返回结果

		SQuitGuildAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：退出帮派
	virtual bool OnRecv_QuitGuild(
		shared_func<SQuitGuildAck>& fnAck //返回回调函数
	) = 0;

	struct SSetAuthorityAck : public CClientFuncAck
	{
		ESetAuthorityResult eResult; //返回结果

		SSetAuthorityAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：设置权限
	virtual bool OnRecv_SetAuthority(
		EMemberRank eRank, //职位
		UINT32 dwAuthority, //可选权限
		shared_func<SSetAuthorityAck>& fnAck //返回回调函数
	) = 0;

	struct SEditInfoAck : public CClientFuncAck
	{
		EEditInfoResult eResult; //返回结果

		SEditInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：编辑公告
	virtual bool OnRecv_EditInfo(
		const std::string& strInfo, //公告信息
		shared_func<SEditInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SMemberOperateAck : public CClientFuncAck
	{
		EMemberOperateResult eResult; //返回结果

		SMemberOperateAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：帮派成员操作
	virtual bool OnRecv_MemberOperate(
		UINT64 qwRoleID, //被设置者ID
		EMemberOperateType eOpType, //操作类型
		shared_func<SMemberOperateAck>& fnAck //返回回调函数
	) = 0;

	struct SImpeachReplyAck : public CClientFuncAck
	{
		EImpeachResult eResult; //返回结果

		SImpeachReplyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：弹劾回应
	virtual bool OnRecv_ImpeachReply(
		UINT64 qwGuildID, //帮派ID
		bool bAgree, //同意/拒绝
		shared_func<SImpeachReplyAck>& fnAck //返回回调函数
	) = 0;

	struct SLaunchImpeachAck : public CClientFuncAck
	{
		EImpeachResult eResult; //弹劾结果

		SLaunchImpeachAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：发起弹劾
	virtual bool OnRecv_LaunchImpeach(
		shared_func<SLaunchImpeachAck>& fnAck //返回回调函数
	) = 0;

	struct SSearchGuildByNameAck : public CClientFuncAck
	{
		EGuildResult eResult; //返回结果
		TVecGuildListInfo vecGuildListInfo; //帮派列表信息

		SSearchGuildByNameAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：搜索帮派
	virtual bool OnRecv_SearchGuildByName(
		const std::string& strName, //帮派名称
		shared_func<SSearchGuildByNameAck>& fnAck //返回回调函数
	) = 0;

	struct SSearchGuildByOwnerNameAck : public CClientFuncAck
	{
		EGuildResult eResult; //返回结果
		TVecGuildListInfo vecGuildListInfo; //帮派列表信息

		SSearchGuildByOwnerNameAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：根据帮主搜索帮派
	virtual bool OnRecv_SearchGuildByOwnerName(
		const std::string& strOwnerName, //帮主名称
		shared_func<SSearchGuildByOwnerNameAck>& fnAck //返回回调函数
	) = 0;

	struct SSearchGuildByBothNameAck : public CClientFuncAck
	{
		EGuildResult eResult; //返回结果
		TVecGuildListInfo vecGuildListInfo; //帮派列表信息

		SSearchGuildByBothNameAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：根据帮主搜索帮派
	virtual bool OnRecv_SearchGuildByBothName(
		const std::string& strName, //帮派名称
		const std::string& strOwnerName, //帮主名称
		shared_func<SSearchGuildByBothNameAck>& fnAck //返回回调函数
	) = 0;

	struct SUpgradeBuildingAck : public CClientFuncAck
	{
		EBuildingResult eResult; //返回结果

		SUpgradeBuildingAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：提升帮派建筑等级
	virtual bool OnRecv_UpgradeBuilding(
		EBuildingType eBuildingType, //帮派建筑类型
		shared_func<SUpgradeBuildingAck>& fnAck //返回回调函数
	) = 0;

	struct SUpgradeTechAck : public CClientFuncAck
	{
		ETechResult eResult; //返回结果

		SUpgradeTechAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：提升帮派科技等级
	virtual bool OnRecv_UpgradeTech(
		ETechType eType, //帮派科技类型
		shared_func<SUpgradeTechAck>& fnAck //返回回调函数
	) = 0;

	struct SDonateAck : public CClientFuncAck
	{
		EDonateResult eResult; //返回结果

		SDonateAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：帮派捐献
	virtual bool OnRecv_Donate(
		UINT32 dwMoney, //捐献数量
		shared_func<SDonateAck>& fnAck //返回回调函数
	) = 0;

	struct SWorshipAck : public CClientFuncAck
	{
		EStatueResult eResult; //返回结果

		SWorshipAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：帮派供奉
	virtual bool OnRecv_Worship(
		EWorshipType eType, //供奉类型
		shared_func<SWorshipAck>& fnAck //返回回调函数
	) = 0;

	struct SMusterAck : public CClientFuncAck
	{
		EGuildResult eResult; //返回结果

		SMusterAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：募集帮众
	virtual bool OnRecv_Muster(
		shared_func<SMusterAck>& fnAck //返回回调函数
	) = 0;

	//接收：获取玩家的羲和神车信息
	virtual void OnRecv_GetXiheInfo(
		UINT64 qwUserID //玩家ID(可为自己ID也可为帮派成员ID)
	) = 0;

	//接收：玩家接受羲和神车任务
	virtual void OnRecv_AcceptXiheTask(
	) = 0;

	struct SGetXiheRequestInfoAck : public CClientFuncAck
	{
		TVecXiheRequest vecXiheRequest; //玩家羲和神车请求帮助的信息

		SGetXiheRequestInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取自己帮派成员的羲和神车请求帮助列表
	virtual bool OnRecv_GetXiheRequestInfo(
		shared_func<SGetXiheRequestInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SShipGoodsAck : public CClientFuncAck
	{
		EGuildXiheResult eResult; //返回结果

		SShipGoodsAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：羲和神车装货
	virtual bool OnRecv_ShipGoods(
		UINT8 byType, //0:用道具装货 1:用仙石装货
		UINT8 byPos, //货物顺序索引(0~7)
		shared_func<SShipGoodsAck>& fnAck //返回回调函数
	) = 0;

	struct SDeliveryGoodsAck : public CClientFuncAck
	{
		EGuildXiheResult eResult; //返回结果

		SDeliveryGoodsAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：羲和神车发货
	virtual bool OnRecv_DeliveryGoods(
		shared_func<SDeliveryGoodsAck>& fnAck //返回回调函数
	) = 0;

	struct SRequestForHelpAck : public CClientFuncAck
	{
		EGuildXiheResult eResult; //返回结果

		SRequestForHelpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：羲和神车请求帮助装货
	virtual bool OnRecv_RequestForHelp(
		UINT8 byPos, //货物顺序索引(0~7)
		shared_func<SRequestForHelpAck>& fnAck //返回回调函数
	) = 0;

	struct SHelpShipGoodsAck : public CClientFuncAck
	{
		EGuildXiheResult eResult; //返回结果

		SHelpShipGoodsAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：羲和神车帮众成员帮助装货
	virtual bool OnRecv_HelpShipGoods(
		UINT8 byType, //0:用道具装货 1:用仙石装货
		UINT64 qwOtherID, //玩家ID
		UINT8 byPos, //货物顺序索引(0~7)
		shared_func<SHelpShipGoodsAck>& fnAck //返回回调函数
	) = 0;

	struct SReqGuildExchangedItemInfoAck : public CClientFuncAck
	{
		TVecUINT8 vecLingShanType; //灵山类型
		TVecGuildExchangedItem vecGuildExchangedItem; //兑换物品信息
		UINT32 dwGUildAllMemberExchangedItemNum; //帮派所有成员兑换物品总数量
		UINT32 dwPlayerExchangedItemNum; //玩家兑换物品总数量
		EMemberRank eMemberLastRank; //玩家上一次帮派职位

		SReqGuildExchangedItemInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求帮派兑换物品信息
	virtual bool OnRecv_ReqGuildExchangedItemInfo(
		shared_func<SReqGuildExchangedItemInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SReqGuildExchangeItemAck : public CClientFuncAck
	{
		EGuildExchangeRet eResult; //返回结果

		SReqGuildExchangeItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求帮派兑换物品
	virtual bool OnRecv_ReqGuildExchangeItem(
		UINT32 dwExchangeID, //兑换id
		UINT32 dwCount, //兑换数量
		shared_func<SReqGuildExchangeItemAck>& fnAck //返回回调函数
	) = 0;

	struct SReqGuildExchangeItemLogInfoAck : public CClientFuncAck
	{
		TVecGuildLogInfo vecGuildLogInfo; //兑换物品日志信息

		SReqGuildExchangeItemLogInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求帮派兑换物品日志信息
	virtual bool OnRecv_ReqGuildExchangeItemLogInfo(
		shared_func<SReqGuildExchangeItemLogInfoAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 16; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetGuildInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetGuildList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetGuildApplyInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CreateGuild(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ApplyGuild(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AgreeApply(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AgreeApplyAll(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_RejectApply(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_RejectApplyAll(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_InviteApply(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetGuildApplyList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CancelApply(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_InviteReply(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_QuitGuild(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetAuthority(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_EditInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_MemberOperate(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ImpeachReply(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LaunchImpeach(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SearchGuildByName(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SearchGuildByOwnerName(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SearchGuildByBothName(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpgradeBuilding(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpgradeTech(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Donate(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Worship(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Muster(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetXiheInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AcceptXiheTask(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetXiheRequestInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ShipGoods(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DeliveryGoods(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_RequestForHelp(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_HelpShipGoods(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqGuildExchangedItemInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqGuildExchangeItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqGuildExchangeItemLogInfo(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGuildProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGuildProt
