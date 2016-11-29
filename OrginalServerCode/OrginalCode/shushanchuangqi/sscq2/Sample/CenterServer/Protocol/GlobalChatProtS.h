#pragma once

#include "GlobalChatProtSvr.h"

using namespace NGlobalChatProt;

class CGlobalChatProtS : public CGlobalChatProtSvr
{
public:
	//接收：聊天
	virtual void OnRecv_Chat(
		EChannelType eChannelType, //通道类型
		const std::string& strInfo, //聊天信息
		const TVecShowInfo& vecShowInfo //炫耀物品信息
		);
	
	//接收：私聊
	virtual bool OnRecv_Whisper(
		UINT64 qwUsrID, //帐号ID
		const std::string& strInfo, //聊天信息
		const TVecShowInfo& vecShowInfo, //炫耀物品信息
		shared_func<SWhisperAck>& fnAck //返回回调函数
		);

    /*
	//接收：请求展示信息
	virtual bool OnRecv_ShowItemReq(
		UINT32 dwShowID, //展示ID
		EChatShowType eShowType, //类型
		shared_func<SShowItemReqAck>& fnAck //返回回调函数
		);
        */

	//接收：获取炫耀信息
	virtual bool OnRecv_GetShowInfo(
		UINT64 qwInstID, //唯一ID
		shared_func<SGetShowInfoAck>& fnAck //返回回调函数
	);

    //接收：请求私聊信
    virtual bool OnRecv_ReqWhisperInfo(
		const std::string& strReceiveName, //玩家名字
		shared_func<SReqWhisperInfoAck>& fnAck //返回回调函数
	);
};
