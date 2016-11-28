/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    LingShanProt.h
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "LingShanProt.h"

namespace NLingShanProt
{

//协议类：灵山（改名秘境）寻宝
class CLingShanProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：玩家个人血量通知
	bool Send_SelHPRateNotify( //发送给当前协议处理的客户端
		float fHPRate //血量百分比
	);
	bool SendClt_SelHPRateNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		float fHPRate //血量百分比
	);
	std::string& BuildPkg_SelHPRateNotify( //只组包不发送
		float fHPRate //血量百分比
	);

	//发送：玩家自己当前状态通知
	bool Send_StatusNotify( //发送给当前协议处理的客户端
		ELingShanStatus eRet, //当前状态
		UINT32 dwParam, //排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
		UINT32 dwTime, //服务器时间戳
		UINT16 wRoomID //房间id
	);
	bool SendClt_StatusNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		ELingShanStatus eRet, //当前状态
		UINT32 dwParam, //排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
		UINT32 dwTime, //服务器时间戳
		UINT16 wRoomID //房间id
	);
	std::string& BuildPkg_StatusNotify( //只组包不发送
		ELingShanStatus eRet, //当前状态
		UINT32 dwParam, //排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
		UINT32 dwTime, //服务器时间戳
		UINT16 wRoomID //房间id
	);

	//发送：观看房间当前状态通知
	bool Send_VisitRoomStatusNotify( //发送给当前协议处理的客户端
		ELingShanStatus eRet, //当前状态
		UINT32 dwParam, //排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
		UINT32 dwTime //服务器时间戳
	);
	bool SendClt_VisitRoomStatusNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		ELingShanStatus eRet, //当前状态
		UINT32 dwParam, //排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
		UINT32 dwTime //服务器时间戳
	);
	std::string& BuildPkg_VisitRoomStatusNotify( //只组包不发送
		ELingShanStatus eRet, //当前状态
		UINT32 dwParam, //排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
		UINT32 dwTime //服务器时间戳
	);

	//发送：玩家移动结果通知
	bool Send_PlayerMoveNotify( //发送给当前协议处理的客户端
		const TVecPlayerMoveInfo& vecPlayerMoveInfo, //玩家移动路径
		UINT16 wRoomID //房间id
	);
	bool SendClt_PlayerMoveNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecPlayerMoveInfo& vecPlayerMoveInfo, //玩家移动路径
		UINT16 wRoomID //房间id
	);
	std::string& BuildPkg_PlayerMoveNotify( //只组包不发送
		const TVecPlayerMoveInfo& vecPlayerMoveInfo, //玩家移动路径
		UINT16 wRoomID //房间id
	);

	//发送：玩家路径碰撞结果通知
	bool Send_PathCollideNotify( //发送给当前协议处理的客户端
		const TVecPathCollideInfo& vecPathCollideInfo, //路径碰撞
		UINT16 wRoomID //房间id
	);
	bool SendClt_PathCollideNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecPathCollideInfo& vecPathCollideInfo, //路径碰撞
		UINT16 wRoomID //房间id
	);
	std::string& BuildPkg_PathCollideNotify( //只组包不发送
		const TVecPathCollideInfo& vecPathCollideInfo, //路径碰撞
		UINT16 wRoomID //房间id
	);

	//发送：玩家格子碰撞结果通知
	bool Send_GridCollideNotify( //发送给当前协议处理的客户端
		const TVecGridCollideInfo& vecGridCollideInfo, //格子碰撞
		UINT16 wRoomID //房间id
	);
	bool SendClt_GridCollideNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecGridCollideInfo& vecGridCollideInfo, //格子碰撞
		UINT16 wRoomID //房间id
	);
	std::string& BuildPkg_GridCollideNotify( //只组包不发送
		const TVecGridCollideInfo& vecGridCollideInfo, //格子碰撞
		UINT16 wRoomID //房间id
	);

	//发送：新玩家进入
	bool Send_NewPlayerEnterNotify( //发送给当前协议处理的客户端
		const TVecRoomPlayInfo& vecRoomPlayInfo, //玩家列表
		UINT16 wRoomID //房间id
	);
	bool SendClt_NewPlayerEnterNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecRoomPlayInfo& vecRoomPlayInfo, //玩家列表
		UINT16 wRoomID //房间id
	);
	std::string& BuildPkg_NewPlayerEnterNotify( //只组包不发送
		const TVecRoomPlayInfo& vecRoomPlayInfo, //玩家列表
		UINT16 wRoomID //房间id
	);

	//发送：新一轮开始
	bool Send_NewTurnBeginNotify( //发送给当前协议处理的客户端
		bool bFreshBox, //是否刷新宝箱
		UINT16 wRoomID, //房间id
		UINT32 dwFreshTurn //至宝刷新剩余轮数
	);
	bool SendClt_NewTurnBeginNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		bool bFreshBox, //是否刷新宝箱
		UINT16 wRoomID, //房间id
		UINT32 dwFreshTurn //至宝刷新剩余轮数
	);
	std::string& BuildPkg_NewTurnBeginNotify( //只组包不发送
		bool bFreshBox, //是否刷新宝箱
		UINT16 wRoomID, //房间id
		UINT32 dwFreshTurn //至宝刷新剩余轮数
	);

	//发送：模型修改
	bool Send_PlayerChangeModelNotify( //发送给当前协议处理的客户端
		UINT64 qwRoleID, //玩家id
		UINT32 dwModelID, //模型id
		UINT16 wRoomID //房间id
	);
	bool SendClt_PlayerChangeModelNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwRoleID, //玩家id
		UINT32 dwModelID, //模型id
		UINT16 wRoomID //房间id
	);
	std::string& BuildPkg_PlayerChangeModelNotify( //只组包不发送
		UINT64 qwRoleID, //玩家id
		UINT32 dwModelID, //模型id
		UINT16 wRoomID //房间id
	);

	//发送：玩家奖励log
	bool Send_PlayerPrizeLogNotify( //发送给当前协议处理的客户端
		const TVecTakePrizeLog& vecTakePrizeLog //玩家奖励log列表
	);
	bool SendClt_PlayerPrizeLogNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecTakePrizeLog& vecTakePrizeLog //玩家奖励log列表
	);
	std::string& BuildPkg_PlayerPrizeLogNotify( //只组包不发送
		const TVecTakePrizeLog& vecTakePrizeLog //玩家奖励log列表
	);

	//发送：聊天
	bool Send_ChatNotify( //发送给当前协议处理的客户端
		UINT64 qwRoleID, //结果
		const std::string& strChatMsg, //聊天内容
		UINT16 wRoomID //房间id
	);
	bool SendClt_ChatNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwRoleID, //结果
		const std::string& strChatMsg, //聊天内容
		UINT16 wRoomID //房间id
	);
	std::string& BuildPkg_ChatNotify( //只组包不发送
		UINT64 qwRoleID, //结果
		const std::string& strChatMsg, //聊天内容
		UINT16 wRoomID //房间id
	);

	//发送：玩家数据更新
	bool Send_PlayerUpdateNotify( //发送给当前协议处理的客户端
		const TVecRoomPlayInfo& vecRoomPlayInfo, //玩家列表
		UINT16 wRoomID //房间id
	);
	bool SendClt_PlayerUpdateNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecRoomPlayInfo& vecRoomPlayInfo, //玩家列表
		UINT16 wRoomID //房间id
	);
	std::string& BuildPkg_PlayerUpdateNotify( //只组包不发送
		const TVecRoomPlayInfo& vecRoomPlayInfo, //玩家列表
		UINT16 wRoomID //房间id
	);

	//发送：从观察者房间踢掉
	bool Send_KickViewNotify( //发送给当前协议处理的客户端
		UINT16 wRoomID //进入的房间id
	);
	bool SendClt_KickViewNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wRoomID //进入的房间id
	);
	std::string& BuildPkg_KickViewNotify( //只组包不发送
		UINT16 wRoomID //进入的房间id
	);

	//发送：从房间离开
	bool Send_KickPlayerNotify( //发送给当前协议处理的客户端
		UINT64 qwRoleID, //进入的房间id
		UINT16 wRoomID //进入的房间id
	);
	bool SendClt_KickPlayerNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwRoleID, //进入的房间id
		UINT16 wRoomID //进入的房间id
	);
	std::string& BuildPkg_KickPlayerNotify( //只组包不发送
		UINT64 qwRoleID, //进入的房间id
		UINT16 wRoomID //进入的房间id
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：获取状态（回StatusNotify通知）
	virtual void OnRecv_GetStatus(
	) = 0;

	struct SRegAck : public CClientFuncAck
	{
		ELingShanOP eRet; //报名结果

		SRegAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：活动报名
	virtual bool OnRecv_Reg(
		shared_func<SRegAck>& fnAck //返回回调函数
	) = 0;

	struct SGetMatchInfoAck : public CClientFuncAck
	{
		ELingShanOP eRet; //结果
		TVecBoxInfo vecBoxInfo; //地图箱子信息
		TVecRoomPlayInfo vecRoomPlayInfo; //地图玩家信息
		TVecRoomMonsterInfo vecRoomMonsterInfo; //地图怪物信息
		UINT16 wRoomID; //房间id
		UINT32 dwFreshTurn; //至宝刷新剩余轮数
		ELingShanStatus eStatus; //当前状态
		UINT32 dwParam; //排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
		UINT32 dwTime; //服务器时间戳
		SPlayMovieInfo oPlayMovieInfo; //动画播放信息
		TVecTakePrizeLog vecTakePrizeLog; //玩家奖励log列表
		UINT32 dwTurn; //当前轮数

		SGetMatchInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：当前棋盘状态
	virtual bool OnRecv_GetMatchInfo(
		shared_func<SGetMatchInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetMathSelInfoAck : public CClientFuncAck
	{
		ELingShanOP eRet; //结果
		ELingShanStatus eStatus; //当前状态
		SRoomPlayInfo oRoomPlayInfo; //玩家地图信息
		float fHPRate; //血量百分比
		UINT16 dwBoxCnt; //宝箱数量
		UINT32 dwSuiYuan; //随缘值
		UINT32 dwRoomID; //房间号
		UINT32 dwFreshTurn; //至宝刷新剩余轮数
		UINT32 dwModelID; //模型id

		SGetMathSelInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取自己的比赛信息
	virtual bool OnRecv_GetMathSelInfo(
		shared_func<SGetMathSelInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SChangeModelAck : public CClientFuncAck
	{
		ELingShanOP eRet; //
		UINT32 dwModelID; //模型id

		SChangeModelAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：更换模型信息
	virtual bool OnRecv_ChangeModel(
		UINT32 dwModelID, //模型id
		shared_func<SChangeModelAck>& fnAck //返回回调函数
	) = 0;

	struct SMoveSelectAck : public CClientFuncAck
	{
		ELingShanOP eRet; //结果
		UINT32 dwCdTime; //cd

		SMoveSelectAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：移动选择
	virtual bool OnRecv_MoveSelect(
		UINT16 wPos, //位置
		shared_func<SMoveSelectAck>& fnAck //返回回调函数
	) = 0;

	struct SGetActInfoAck : public CClientFuncAck
	{
		ELingShanOP eRet; //结果
		UINT32 dwBeginTime; //比赛开启时间
		UINT32 dwEndTime; //比赛结束时间

		SGetActInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取活动信息
	virtual bool OnRecv_GetActInfo(
		shared_func<SGetActInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SChatAck : public CClientFuncAck
	{
		ELingShanOP eRet; //结果

		SChatAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：聊天
	virtual bool OnRecv_Chat(
		const std::string& strChatMsg, //聊天内容
		shared_func<SChatAck>& fnAck //返回回调函数
	) = 0;

	struct SGetRoomListAck : public CClientFuncAck
	{
		ELingShanOP eRet; //结果
		TVecRoomInfo vecRoomInfo; //房间信息

		SGetRoomListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取房间信息
	virtual bool OnRecv_GetRoomList(
		shared_func<SGetRoomListAck>& fnAck //返回回调函数
	) = 0;

	struct SEnterVisitRoomAck : public CClientFuncAck
	{
		ELingShanOP eRet; //结果

		SEnterVisitRoomAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：进入参观房间
	virtual bool OnRecv_EnterVisitRoom(
		UINT16 wRoomID, //房间id
		shared_func<SEnterVisitRoomAck>& fnAck //返回回调函数
	) = 0;

	struct SLeaveVisitRoomAck : public CClientFuncAck
	{
		ELingShanOP eRet; //结果

		SLeaveVisitRoomAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：离开参观房间
	virtual bool OnRecv_LeaveVisitRoom(
		shared_func<SLeaveVisitRoomAck>& fnAck //返回回调函数
	) = 0;

	struct SGetPlayMovieInfoAck : public CClientFuncAck
	{
		ELingShanOP eRet; //结果
		SPlayMovieInfo oPlayMovieInfo; //动画播放信息
		TVecTakePrizeLog vecTakePrizeLog; //玩家奖励log列表
		UINT16 wRoomID; //房间id
		UINT32 dwTurn; //当前轮数

		SGetPlayMovieInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取动画播放信息
	virtual bool OnRecv_GetPlayMovieInfo(
		shared_func<SGetPlayMovieInfoAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 135; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetStatus(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Reg(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetMatchInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetMathSelInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ChangeModel(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_MoveSelect(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetActInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Chat(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetRoomList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_EnterVisitRoom(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LeaveVisitRoom(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPlayMovieInfo(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CLingShanProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NLingShanProt
