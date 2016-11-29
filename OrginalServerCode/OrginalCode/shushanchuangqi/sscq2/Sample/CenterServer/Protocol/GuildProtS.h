#ifndef GUILD_PROT_S_H
#define GUILD_PROT_S_H

#pragma once
#include "GuildProtSvr.h"

using namespace NGuildProt;

class CGuildProtS : public CGuildProtSvr
{
    public:
	//接收：获取帮派面板信息
	virtual bool OnRecv_GetGuildInfo(
		shared_func<SGetGuildInfoAck>& fnAck //返回回调函数
	);

	//接收：获得帮派列表
	virtual bool OnRecv_GetGuildList(
		UINT32 dwIndex, //帮派索引
		UINT32 dwCount, //帮派个数
		shared_func<SGetGuildListAck>& fnAck //返回回调函数
	);

	//接收：获取帮派申请列表信息
	virtual bool OnRecv_GetGuildApplyInfo(
		shared_func<SGetGuildApplyInfoAck>& fnAck //返回回调函数
	);

	//接收：创建帮派
	virtual bool OnRecv_CreateGuild(
		const std::string& strName, //帮派名称
		shared_func<SCreateGuildAck>& fnAck //返回回调函数
	);

	//接收：申请加入帮派
	virtual bool OnRecv_ApplyGuild(
		UINT64 qwGuildID, //帮派ID
		shared_func<SApplyGuildAck>& fnAck //返回回调函数
	);

	//接收：通过加入申请
	virtual bool OnRecv_AgreeApply(
		UINT64 qwRoleID, //申请者ID
		shared_func<SAgreeApplyAck>& fnAck //返回回调函数
	);

    //接收：全部同意
	virtual bool OnRecv_AgreeApplyAll(
		shared_func<SAgreeApplyAllAck>& fnAck //返回回调函数
	);

	//接收：拒绝加入申请
	virtual bool OnRecv_RejectApply(
		UINT64 qwRoleID, //申请者ID
		shared_func<SRejectApplyAck>& fnAck //返回回调函数
	);

	//接收：全部拒绝
	virtual bool OnRecv_RejectApplyAll(
		shared_func<SRejectApplyAllAck>& fnAck //返回回调函数
	);

	//接收：邀请加入
	virtual bool OnRecv_InviteApply(
		const std::string& strName, //被邀请者名字
		shared_func<SInviteApplyAck>& fnAck //返回回调函数
	);

	//接收：获得已申请帮派列表
	virtual bool OnRecv_GetGuildApplyList(
		shared_func<SGetGuildApplyListAck>& fnAck //返回回调函数
	);

	//接收：撤销帮派申请
	virtual bool OnRecv_CancelApply(
		UINT64 qwGuildID, //帮派ID
		shared_func<SCancelApplyAck>& fnAck //返回回调函数
	);

	//接收：邀请回应
	virtual bool OnRecv_InviteReply(
		UINT64 qwGuildID, //帮派ID
		bool bAgree, //同意/拒绝
		shared_func<SInviteReplyAck>& fnAck //返回回调函数
	);

	//接收：退出帮派
	virtual bool OnRecv_QuitGuild(
		shared_func<SQuitGuildAck>& fnAck //返回回调函数
	);

	//接收：设置权限
	virtual bool OnRecv_SetAuthority(
		EMemberRank eRank, //新职位
		UINT32 dwAuthority, //可选权限
		shared_func<SSetAuthorityAck>& fnAck //返回回调函数
	);

	//接收：编辑公告
	virtual bool OnRecv_EditInfo(
		const std::string& strInfo, //公告信息
		shared_func<SEditInfoAck>& fnAck //返回回调函数
	);

	//接收：帮派成员操作
	virtual bool OnRecv_MemberOperate(
		UINT64 qwRoleID, //被设置者ID
		EMemberOperateType eOpType, //操作类型
		shared_func<SMemberOperateAck>& fnAck //返回回调函数
	);

	//接收：弹劾回应
	virtual bool OnRecv_ImpeachReply(
		UINT64 qwGuildID, //帮派ID
		bool bAgree, //同意/拒绝
		shared_func<SImpeachReplyAck>& fnAck //返回回调函数
	);

	//接收：发起弹劾
	virtual bool OnRecv_LaunchImpeach(
		shared_func<SLaunchImpeachAck>& fnAck //返回回调函数
	);

	//接收：搜索帮派
	virtual bool OnRecv_SearchGuildByName(
		const std::string& strName, //帮派名称
		shared_func<SSearchGuildByNameAck>& fnAck //返回回调函数
	);

	//接收：搜索帮派
	virtual bool OnRecv_SearchGuildByOwnerName(
		const std::string& strOwnerName, //帮主名称
		shared_func<SSearchGuildByOwnerNameAck>& fnAck //返回回调函数
	);

	//接收：根据帮主搜索帮派
	virtual bool OnRecv_SearchGuildByBothName(
		const std::string& strName, //帮派名称
		const std::string& strOwnerName, //帮主名称
		shared_func<SSearchGuildByBothNameAck>& fnAck //返回回调函数
	);

	//接收：提升帮派建筑等级
	virtual bool OnRecv_UpgradeBuilding(
		EBuildingType eBuildingType, //帮派建筑类型
		shared_func<SUpgradeBuildingAck>& fnAck //返回回调函数
	);

	//接收：提升帮派科技等级
	virtual bool OnRecv_UpgradeTech(
		ETechType eType, //帮派科技类型
		shared_func<SUpgradeTechAck>& fnAck //返回回调函数
	);

	//接收：帮派捐献
	virtual bool OnRecv_Donate(
		UINT32 dwMoney, //捐献数量
		shared_func<SDonateAck>& fnAck //返回回调函数
	);

	//接收：帮派供奉
	virtual bool OnRecv_Worship(
		EWorshipType eType, //供奉类型
		shared_func<SWorshipAck>& fnAck //返回回调函数
	);

	//接收：募集帮众
	virtual bool OnRecv_Muster(
		shared_func<SMusterAck>& fnAck //返回回调函数
	);

	//接收：获取羲和神车信息
	virtual void OnRecv_GetXiheInfo(
		UINT64 qwUserID //玩家ID(可为自己ID也可为帮派成员ID)
	);

	//接收：玩家接受羲和神车任务
	virtual void OnRecv_AcceptXiheTask(
	);

	//接收：获取自己帮派成员的羲和神车请求帮助列表
	virtual bool OnRecv_GetXiheRequestInfo(
		shared_func<SGetXiheRequestInfoAck>& fnAck //返回回调函数
	);

	//接收：羲和神车装货
	virtual bool OnRecv_ShipGoods(
		UINT8 byType, //0:用道具装货 1:用仙石装货
		UINT8 byPos, //货物顺序索引(0~7)
		shared_func<SShipGoodsAck>& fnAck //返回回调函数
	);

	//接收：羲和神车发货
	virtual bool OnRecv_DeliveryGoods(
		shared_func<SDeliveryGoodsAck>& fnAck //返回回调函数
	);

	//接收：羲和神车请求帮助装货
	virtual bool OnRecv_RequestForHelp(
	    UINT8 byPos, //货物顺序索引(0~7)
		shared_func<SRequestForHelpAck>& fnAck //返回回调函数
	);

	//接收：羲和神车帮众成员帮助装货
	virtual bool OnRecv_HelpShipGoods(
		UINT8 byType, //0:用道具装货 1:用仙石装货
		UINT64 qwOtherID, //玩家ID
		UINT8 byPos, //货物顺序索引(0~7)
		shared_func<SHelpShipGoodsAck>& fnAck //返回回调函数
	);

    //接收：请求帮派兑换物品信息
	virtual bool OnRecv_ReqGuildExchangedItemInfo(
		shared_func<SReqGuildExchangedItemInfoAck>& fnAck //返回回调函数
	);
	
    //接收：请求帮派兑换物品
	virtual bool OnRecv_ReqGuildExchangeItem(
		UINT32 dwExchangeID, //兑换id
		UINT32 dwCount, //兑换数量
		shared_func<SReqGuildExchangeItemAck>& fnAck //返回回调函数
	);
    
    //接收：请求帮派兑换物品日志信息
	virtual bool OnRecv_ReqGuildExchangeItemLogInfo(
		shared_func<SReqGuildExchangeItemLogInfoAck>& fnAck //返回回调函数
	);

};

#endif // #ifndef GUILD_PROT_S_H
