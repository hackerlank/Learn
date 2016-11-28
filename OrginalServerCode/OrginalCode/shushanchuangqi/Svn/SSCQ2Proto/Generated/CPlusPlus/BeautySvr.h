/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Beauty.h
//  Purpose:      美女系统
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Beauty.h"

namespace NBeauty
{

//协议类：美女系统
class CBeautySvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：美女信息更新
	bool Send_BeautyNotify( //发送给当前协议处理的客户端
		const SBeauty& oBeauty //美女信息
	);
	bool SendClt_BeautyNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SBeauty& oBeauty //美女信息
	);
	std::string& BuildPkg_BeautyNotify( //只组包不发送
		const SBeauty& oBeauty //美女信息
	);

	//发送：爱心数目更新
	bool Send_LoveHeartCntNotify( //发送给当前协议处理的客户端
		UINT32 dwLoveCnt //爱心个数
	);
	bool SendClt_LoveHeartCntNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwLoveCnt //爱心个数
	);
	std::string& BuildPkg_LoveHeartCntNotify( //只组包不发送
		UINT32 dwLoveCnt //爱心个数
	);

	//发送：聊天cd
	bool Send_ChatCdNotify( //发送给当前协议处理的客户端
		UINT32 dwNextChatTime //下次聊天冷却时间
	);
	bool SendClt_ChatCdNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwNextChatTime //下次聊天冷却时间
	);
	std::string& BuildPkg_ChatCdNotify( //只组包不发送
		UINT32 dwNextChatTime //下次聊天冷却时间
	);

	//发送：免费抽奖cd
	bool Send_FreeMoneyCdNotify( //发送给当前协议处理的客户端
		ELotteryBeautyType eLotteryBeautyType, //抽奖类型,只有单次金币，银币两种类型
		UINT32 dwNextChatTime //下次聊天冷却时间
	);
	bool SendClt_FreeMoneyCdNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		ELotteryBeautyType eLotteryBeautyType, //抽奖类型,只有单次金币，银币两种类型
		UINT32 dwNextChatTime //下次聊天冷却时间
	);
	std::string& BuildPkg_FreeMoneyCdNotify( //只组包不发送
		ELotteryBeautyType eLotteryBeautyType, //抽奖类型,只有单次金币，银币两种类型
		UINT32 dwNextChatTime //下次聊天冷却时间
	);

	//发送：当前已免费抽奖次数
	bool Send_LotteryFreeCntNotify( //发送给当前协议处理的客户端
		UINT8 byFreeCnt //已免费抽奖次数
	);
	bool SendClt_LotteryFreeCntNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byFreeCnt //已免费抽奖次数
	);
	std::string& BuildPkg_LotteryFreeCntNotify( //只组包不发送
		UINT8 byFreeCnt //已免费抽奖次数
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetBeatyInfoAck : public CClientFuncAck
	{
		TVecBeauty vecBeauty; //美女信息列表
		UINT32 dwLoveCnt; //爱心个数
		UINT32 dwNextChatTime; //下次聊天冷却时间
		UINT32 dwNextGoldLotteryTime; //下次免费金币抽奖冷却时间
		UINT32 dwNextSilverLotterTime; //下次免费银币冷却时间
		UINT16 wBeautyID; //出战美女ID

		SGetBeatyInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取美女信息
	virtual bool OnRecv_GetBeatyInfo(
		shared_func<SGetBeatyInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SMeetBeautyAck : public CClientFuncAck
	{
		EBeautyRet eRet; //操作结果

		SMeetBeautyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：结识美女
	virtual bool OnRecv_MeetBeauty(
		UINT16 wBeautyID, //美女id
		shared_func<SMeetBeautyAck>& fnAck //返回回调函数
	) = 0;

	struct SChatBeautyAck : public CClientFuncAck
	{
		EBeautyRet eRet; //操作结果

		SChatBeautyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：和美女聊天
	virtual bool OnRecv_ChatBeauty(
		UINT16 wBeautyID, //美女id
		shared_func<SChatBeautyAck>& fnAck //返回回调函数
	) = 0;

	struct SSendPrizeBeautyAck : public CClientFuncAck
	{
		EBeautyRet eRet; //操作结果

		SSendPrizeBeautyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：送美女礼品
	virtual bool OnRecv_SendPrizeBeauty(
		UINT16 wBeautyID, //美女id
		const NItemProt::TVecItemCount& vecItemCount, //物品列表
		shared_func<SSendPrizeBeautyAck>& fnAck //返回回调函数
	) = 0;

	struct SLotteryBeautyAck : public CClientFuncAck
	{
		EBeautyRet eRet; //操作结果
		NItemProt::TVecItemGenInfo vecItemGenInfo; //物品列表

		SLotteryBeautyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：抽奖
	virtual bool OnRecv_LotteryBeauty(
		ELotteryBeautyType eLotteryBeautyType, //抽奖类型
		shared_func<SLotteryBeautyAck>& fnAck //返回回调函数
	) = 0;

	struct SBeautyFightAck : public CClientFuncAck
	{
		EBeautyRet eRet; //操作结果

		SBeautyFightAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：美女出战
	virtual bool OnRecv_BeautyFight(
		UINT16 wBeautyID, //美女id
		shared_func<SBeautyFightAck>& fnAck //返回回调函数
	) = 0;

	struct SGetRareItemListAck : public CClientFuncAck
	{
		TVecUINT16 vecItemID; //稀有物品列表

		SGetRareItemListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取稀有物品列表
	virtual bool OnRecv_GetRareItemList(
		shared_func<SGetRareItemListAck>& fnAck //返回回调函数
	) = 0;

	//接收：获取当前已免费抽奖次数
	virtual void OnRecv_GetLotteryFreeCnt(
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 131; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetBeatyInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_MeetBeauty(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ChatBeauty(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendPrizeBeauty(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LotteryBeauty(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BeautyFight(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetRareItemList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetLotteryFreeCnt(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CBeautySvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NBeauty
