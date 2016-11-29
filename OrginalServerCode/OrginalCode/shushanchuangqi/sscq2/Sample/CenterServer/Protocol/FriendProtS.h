#pragma once
#include "FriendProtSvr.h"

using namespace NFriendProt;

class CFriendProtS : public CFriendProtSvr
{
public:
	//接收：增加好友/黑名单请求
	virtual void OnRecv_AddFriendReq1(
		EFriendGroupType eGroupType, //组别
		const TVecUINT64& vecUserID, //玩家ID
		UINT8 byNeedRet //0-不需要返回消息 1-需要返回消息
		);

	//接收：增加好友/黑名单请求
	virtual void OnRecv_AddFriendReq2(
		EFriendGroupType eGroupType, //组别
		const std::string& strName, //用户名
		UINT8 byNeedRet //0-不需要返回消息 1-需要返回消息
		);

	//接收：回答增加好友
	virtual void OnRecv_AnswerAddFriend(
		bool bAgree, //是否同意
		UINT64 qwUsrID //帐号ID
		);

	//接收：删除好友
	virtual void OnRecv_RemoveFriendReq(
		const TVecUINT64& vecUserID //玩家ID
		);

	//接收：移动好友
	virtual bool OnRecv_MoveFriend(
		UINT64 qwUsrID, //帐号ID
		EFriendGroupType eGroupType, //分组ID
		shared_func<SMoveFriendAck>& fnAck //返回回调函数
		);

	//接收：私聊
	virtual void OnRecv_Whisper(
		UINT64 qwUsrID //帐号ID
		);

	//接收：查询玩家
	virtual void OnRecv_FindUserIDNameReq(
		UINT64 qwUsrID, //帐号ID
		const std::string& strRoleName //主角色名
		);

	//接收：获取推荐好友
	virtual bool OnRecv_FindReferFriendReq(
		shared_func<SFindReferFriendReqAck>& fnAck //返回回调函数
		);

	//接收：取得所有好友信息
	virtual void OnRecv_GetFriendInfo(
	);

	//接收：修改签名
	virtual bool OnRecv_SetSign(
		const std::string& strSign, //签名文字：最多不超过255个字符
		shared_func<SSetSignAck>& fnAck //返回回调函数
	);

	//接收：设置心情表情
	virtual bool OnRecv_SetMood(
		UINT16 wMood, //心情表情
		shared_func<SSetMoodAck>& fnAck //返回回调函数
	);
};
