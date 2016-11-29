#pragma once

#include "ChatProtSvr.h"

#include "stdafx.h"

using namespace NGlobalChatProt;
using namespace NChatProt;

class CChatProtS : public CChatProtSvr
{
public:
	//接收：聊天
	virtual void OnRecv_Chat(
		NGlobalChatProt::EChannelType eChannelType, //通道类型
		const std::string& strInfo, //聊天信息
		const NGlobalChatProt::TVecShowInfo& vecShowInfo //炫耀物品信息
		);

    /*
	//接收：聊天展示
	virtual bool OnRecv_ChatShowItem(
		//NItemProt::EStoreType eStoreType, //容器类型
		UINT64 qwRoleID, //角色ID(0:自己)
		UINT64 qwInstID, //道具ID
        shared_func<SChatShowItemAck>& fnAck //返回回调函数
		);
        */

	//接收：气泡信息获取
	virtual bool OnRecv_BubbleGet(
		shared_func<SBubbleGetAck>& fnAck //返回回调函数
	);

	//接收：气泡回应
	virtual bool OnRecv_BubbleRespond(
		UINT16 wIndex, //气泡对应位置
		const TVecINT64& vecParam, //整型变量
		const TVecString& vecString, //字符串型变量
		shared_func<SBubbleRespondAck>& fnAck //返回回调函数
	);
    //接收：邀请平台好友成功
	virtual void OnRecv_InviteSuc(
		UINT64 qwRoleID //被邀请人
	); 

};
