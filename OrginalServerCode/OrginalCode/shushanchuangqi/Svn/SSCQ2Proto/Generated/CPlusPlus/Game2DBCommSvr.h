/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Game2DBComm.h
//  Purpose:      GameServer到DBServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Game2DBComm.h"

namespace NGame2DBComm
{

//协议类：GameServer到DBServer的通信协议
class CGame2DBCommSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：帐号协议代理发送请求
	bool Send_UserPackageProxy( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT32 dwGateID, //所在网关服务器ID
		const TVecString& vecPackage //协议包列表
	);
	bool SendSvr_UserPackageProxy(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT32 dwGateID, //所在网关服务器ID
		const TVecString& vecPackage //协议包列表
	);
	std::string& BuildPkg_UserPackageProxy( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		UINT32 dwGateID, //所在网关服务器ID
		const TVecString& vecPackage //协议包列表
	);

	//发送：DB向GameSever推送角色信息/
	bool Send_UserLoginNtf( //发送给当前协议处理的服务器
		EEnterType eEnterType, //进入的类型
		const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
		const TVecString& vecEnterString, //平台相关参数
		UINT32 dwGateId, //网关Id
		UINT64 qwUserId, //用户Id
		const NRoleInfoDefine::RoleDataInfo& RoleData //玩家数据
	);
	bool SendSvr_UserLoginNtf(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		EEnterType eEnterType, //进入的类型
		const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
		const TVecString& vecEnterString, //平台相关参数
		UINT32 dwGateId, //网关Id
		UINT64 qwUserId, //用户Id
		const NRoleInfoDefine::RoleDataInfo& RoleData //玩家数据
	);
	std::string& BuildPkg_UserLoginNtf( //只组包不发送
		EEnterType eEnterType, //进入的类型
		const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
		const TVecString& vecEnterString, //平台相关参数
		UINT32 dwGateId, //网关Id
		UINT64 qwUserId, //用户Id
		const NRoleInfoDefine::RoleDataInfo& RoleData //玩家数据
	);

	//发送：账号重新进入通知
	bool Send_UserReEnterNotify( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //账号ID
		UINT32 dwGateID, //所在网关服务器ID
		const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
		const TVecString& vecEnterString //平台相关参数
	);
	bool SendSvr_UserReEnterNotify(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //账号ID
		UINT32 dwGateID, //所在网关服务器ID
		const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
		const TVecString& vecEnterString //平台相关参数
	);
	std::string& BuildPkg_UserReEnterNotify( //只组包不发送
		UINT64 qwUsrID, //账号ID
		UINT32 dwGateID, //所在网关服务器ID
		const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
		const TVecString& vecEnterString //平台相关参数
	);

	//发送：账号退出DBServer通知
	bool Send_UserLogoutNtf( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //账号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
	);
	bool SendSvr_UserLogoutNtf(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //账号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
	);
	std::string& BuildPkg_UserLogoutNtf( //只组包不发送
		UINT64 qwUsrID, //账号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
	);

	//发送：离线事件通知
	bool Send_NewOffEventNotice( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //账号ID
		const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
	);
	bool SendSvr_NewOffEventNotice(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //账号ID
		const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
	);
	std::string& BuildPkg_NewOffEventNotice( //只组包不发送
		UINT64 qwUsrID, //账号ID
		const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
	);

	//发送：新帮派战历史记录获取返回
	bool Send_NewGuildBattleHistoryNotify( //发送给当前协议处理的服务器
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
	);
	bool SendSvr_NewGuildBattleHistoryNotify(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
	);
	std::string& BuildPkg_NewGuildBattleHistoryNotify( //只组包不发送
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：心跳
	virtual void OnRecv_KeepAlive(
	) = 0;

	struct SGetStatusAck : public CServerFuncAck
	{
		SGetStatusAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：DBServer状态请求
	virtual bool OnRecv_GetStatus(
		shared_func<SGetStatusAck>& fnAck //返回回调函数
	) = 0;

	//接收：更新玩家充值仙石信息
	virtual void OnRecv_UpdateRecharge(
		const NRoleInfoDefine::SRecharge& oRecharge //充值仙石的数据
	) = 0;

	//接收：一行数据更新
	virtual void OnRecv_RoleDataUpdate(
		UINT64 qwRoleId, //角色Id
		NRoleInfoDefine::EDataType eDataType, //更新数据块
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const std::string& strData //更新数据
	) = 0;

	struct SSaveUserDataReqAck : public CServerFuncAck
	{
		SSaveUserDataReqAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求保存账号数据
	virtual bool OnRecv_SaveUserDataReq(
		UINT64 qwUsrID, //账号ID
		ESaveType eSaveType, //保存类型
		const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
		shared_func<SSaveUserDataReqAck>& fnAck //返回回调函数
	) = 0;

	struct SSaveOffLineDgnInfoAck : public CServerFuncAck
	{
		SSaveOffLineDgnInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：副本结束时候，玩家不在gameserver的数据保存
	virtual bool OnRecv_SaveOffLineDgnInfo(
		UINT64 qwUsrID, //账号ID
		UINT32 dwDgnType, //副本类型
		UINT8 byIsFail, //0:表示成功保存，1：表示失败保存
		shared_func<SSaveOffLineDgnInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SLoadOffLineUserDataAck : public CServerFuncAck
	{
		UINT8 byRet; //0表示成功
		NRoleInfoDefine::RoleDataInfo RoleData; //玩家数据

		SLoadOffLineUserDataAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：加载离线玩家数据
	virtual bool OnRecv_LoadOffLineUserData(
		UINT64 qwUsrID, //账号ID
		shared_func<SLoadOffLineUserDataAck>& fnAck //返回回调函数
	) = 0;

	struct SLoadWorldBossInfoAck : public CServerFuncAck
	{
		TVecWBossDBInfo vecWorldBossInfo; //世界BOSS信息

		SLoadWorldBossInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：加载世界BOSS信息请求
	virtual bool OnRecv_LoadWorldBossInfo(
		shared_func<SLoadWorldBossInfoAck>& fnAck //返回回调函数
	) = 0;

	//接收：存储世界BOSS信息
	virtual void OnRecv_SaveWorldBossInfo(
		const SWBossDBInfo& sWorldBossInfo //世界BOSS信息
	) = 0;

	struct SGetUserIDFromNameAck : public CServerFuncAck
	{
		UINT64 qwUsrID; //用户ID

		SGetUserIDFromNameAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：根据名字获取ID请求
	virtual bool OnRecv_GetUserIDFromName(
		const std::string& strName, //主角色名称
		shared_func<SGetUserIDFromNameAck>& fnAck //返回回调函数
	) = 0;

	struct SGetBattleReportAck : public CServerFuncAck
	{
		NRoleInfoDefine::TVecBattleRePort vecReport; //返回的数据

		SGetBattleReportAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获得玩家战报信息
	virtual bool OnRecv_GetBattleReport(
		UINT64 qwRoleID, //玩家的ID
		NRoleInfoDefine::EBattleReportType eBattleType, //战斗类型
		NRoleInfoDefine::EBattleActionType eAction, //战斗的发起
		shared_func<SGetBattleReportAck>& fnAck //返回回调函数
	) = 0;

	struct SAddBattleReportAck : public CServerFuncAck
	{
		TVecUINT64 vecBattleID; //删除的战报

		SAddBattleReportAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：增加玩家战报信息
	virtual bool OnRecv_AddBattleReport(
		UINT64 qwRoleID, //
		const NRoleInfoDefine::SBattleRePort& sReport, //战斗数据
		UINT8 byNum, //超过byNum，返回删除的旧的战报,0表示不删除
		shared_func<SAddBattleReportAck>& fnAck //返回回调函数
	) = 0;

	//接收：增加离线事件
	virtual void OnRecv_AddOffLineEvent(
		const TVecUINT64& vecRoleID, //
		const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
	) = 0;

	//接收：删除离线事件
	virtual void OnRecv_DelOffLineEvent(
		UINT64 qwRoleID, //
		const NRoleInfoDefine::TVecEventOffLine& vecEventType //事件类型
	) = 0;

	struct SLoadMallDiscountAck : public CServerFuncAck
	{
		NMallProt::TVecDiscount vecDisItems; //限购道具信息

		SLoadMallDiscountAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：加载商城限购信息
	virtual bool OnRecv_LoadMallDiscount(
		shared_func<SLoadMallDiscountAck>& fnAck //返回回调函数
	) = 0;

	//接收：更新商城限购
	virtual void OnRecv_UpdateMallDiscount(
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NMallProt::TVecDiscount& vecDisItems //限购道具
	) = 0;

	//接收：获取新帮派战历史
	virtual void OnRecv_GetNewGuildBattleHistory(
	) = 0;

	//接收：新增新帮派战历史
	virtual void OnRecv_AddNewGuildBattleHistory(
		const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 4; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_KeepAlive(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetStatus(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateRecharge(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_RoleDataUpdate(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SaveUserDataReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SaveOffLineDgnInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LoadOffLineUserData(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LoadWorldBossInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SaveWorldBossInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetUserIDFromName(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetBattleReport(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddBattleReport(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddOffLineEvent(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DelOffLineEvent(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LoadMallDiscount(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateMallDiscount(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetNewGuildBattleHistory(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddNewGuildBattleHistory(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGame2DBCommSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGame2DBComm
