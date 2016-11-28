/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Game2DBComm.h
//  Purpose:      GameServer到DBServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Game2DBComm.h"

namespace NGame2DBComm
{

//协议类：GameServer到DBServer的通信协议
class CGame2DBCommClt : public IProtocol
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

	//发送：DBServer状态请求
	bool Send_GetStatus( //发送给当前协议处理的服务器
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetStatus(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：更新玩家充值仙石信息
	bool Send_UpdateRecharge( //发送给当前协议处理的服务器
		const NRoleInfoDefine::SRecharge& oRecharge //充值仙石的数据
	);
	bool SendSvr_UpdateRecharge(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NRoleInfoDefine::SRecharge& oRecharge //充值仙石的数据
	);
	std::string& BuildPkg_UpdateRecharge( //只组包不发送
		const NRoleInfoDefine::SRecharge& oRecharge //充值仙石的数据
	);

	//发送：一行数据更新
	bool Send_RoleDataUpdate( //发送给当前协议处理的服务器
		UINT64 qwRoleId, //角色Id
		NRoleInfoDefine::EDataType eDataType, //更新数据块
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const std::string& strData //更新数据
	);
	bool SendSvr_RoleDataUpdate(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleId, //角色Id
		NRoleInfoDefine::EDataType eDataType, //更新数据块
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const std::string& strData //更新数据
	);
	std::string& BuildPkg_RoleDataUpdate( //只组包不发送
		UINT64 qwRoleId, //角色Id
		NRoleInfoDefine::EDataType eDataType, //更新数据块
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const std::string& strData //更新数据
	);

	//发送：请求保存账号数据
	bool Send_SaveUserDataReq( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //账号ID
		ESaveType eSaveType, //保存类型
		const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID, //(本地保存的函数参数)账号ID
			ESaveType eSaveType //(本地保存的函数参数)保存类型
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_SaveUserDataReq(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //账号ID
		ESaveType eSaveType, //保存类型
		const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID, //(本地保存的函数参数)账号ID
			ESaveType eSaveType //(本地保存的函数参数)保存类型
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：副本结束时候，玩家不在gameserver的数据保存
	bool Send_SaveOffLineDgnInfo( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //账号ID
		UINT32 dwDgnType, //副本类型
		UINT8 byIsFail, //0:表示成功保存，1：表示失败保存
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID, //(本地保存的函数参数)账号ID
			UINT32 dwDgnType //(本地保存的函数参数)副本类型
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_SaveOffLineDgnInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //账号ID
		UINT32 dwDgnType, //副本类型
		UINT8 byIsFail, //0:表示成功保存，1：表示失败保存
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID, //(本地保存的函数参数)账号ID
			UINT32 dwDgnType //(本地保存的函数参数)副本类型
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：加载离线玩家数据
	bool Send_LoadOffLineUserData( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //账号ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet, //(返回值)0表示成功
			const NRoleInfoDefine::RoleDataInfo& RoleData //(返回值)玩家数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_LoadOffLineUserData(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //账号ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byRet, //(返回值)0表示成功
			const NRoleInfoDefine::RoleDataInfo& RoleData //(返回值)玩家数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：加载世界BOSS信息请求
	bool Send_LoadWorldBossInfo( //发送给当前协议处理的服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const TVecWBossDBInfo& vecWorldBossInfo //(返回值)世界BOSS信息
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_LoadWorldBossInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const TVecWBossDBInfo& vecWorldBossInfo //(返回值)世界BOSS信息
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：存储世界BOSS信息
	bool Send_SaveWorldBossInfo( //发送给当前协议处理的服务器
		const SWBossDBInfo& sWorldBossInfo //世界BOSS信息
	);
	bool SendSvr_SaveWorldBossInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const SWBossDBInfo& sWorldBossInfo //世界BOSS信息
	);
	std::string& BuildPkg_SaveWorldBossInfo( //只组包不发送
		const SWBossDBInfo& sWorldBossInfo //世界BOSS信息
	);

	//发送：根据名字获取ID请求
	bool Send_GetUserIDFromName( //发送给当前协议处理的服务器
		const std::string& strName, //主角色名称
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID //(返回值)用户ID
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetUserIDFromName(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const std::string& strName, //主角色名称
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID //(返回值)用户ID
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：获得玩家战报信息
	bool Send_GetBattleReport( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家的ID
		NRoleInfoDefine::EBattleReportType eBattleType, //战斗类型
		NRoleInfoDefine::EBattleActionType eAction, //战斗的发起
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NRoleInfoDefine::TVecBattleRePort& vecReport //(返回值)返回的数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetBattleReport(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家的ID
		NRoleInfoDefine::EBattleReportType eBattleType, //战斗类型
		NRoleInfoDefine::EBattleActionType eAction, //战斗的发起
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NRoleInfoDefine::TVecBattleRePort& vecReport //(返回值)返回的数据
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：增加玩家战报信息
	bool Send_AddBattleReport( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //
		const NRoleInfoDefine::SBattleRePort& sReport, //战斗数据
		UINT8 byNum, //超过byNum，返回删除的旧的战报,0表示不删除
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const TVecUINT64& vecBattleID //(返回值)删除的战报
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_AddBattleReport(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //
		const NRoleInfoDefine::SBattleRePort& sReport, //战斗数据
		UINT8 byNum, //超过byNum，返回删除的旧的战报,0表示不删除
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const TVecUINT64& vecBattleID //(返回值)删除的战报
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：增加离线事件
	bool Send_AddOffLineEvent( //发送给当前协议处理的服务器
		const TVecUINT64& vecRoleID, //
		const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
	);
	bool SendSvr_AddOffLineEvent(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const TVecUINT64& vecRoleID, //
		const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
	);
	std::string& BuildPkg_AddOffLineEvent( //只组包不发送
		const TVecUINT64& vecRoleID, //
		const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
	);

	//发送：删除离线事件
	bool Send_DelOffLineEvent( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //
		const NRoleInfoDefine::TVecEventOffLine& vecEventType //事件类型
	);
	bool SendSvr_DelOffLineEvent(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //
		const NRoleInfoDefine::TVecEventOffLine& vecEventType //事件类型
	);
	std::string& BuildPkg_DelOffLineEvent( //只组包不发送
		UINT64 qwRoleID, //
		const NRoleInfoDefine::TVecEventOffLine& vecEventType //事件类型
	);

	//发送：加载商城限购信息
	bool Send_LoadMallDiscount( //发送给当前协议处理的服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NMallProt::TVecDiscount& vecDisItems //(返回值)限购道具信息
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_LoadMallDiscount(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NMallProt::TVecDiscount& vecDisItems //(返回值)限购道具信息
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：更新商城限购
	bool Send_UpdateMallDiscount( //发送给当前协议处理的服务器
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NMallProt::TVecDiscount& vecDisItems //限购道具
	);
	bool SendSvr_UpdateMallDiscount(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NMallProt::TVecDiscount& vecDisItems //限购道具
	);
	std::string& BuildPkg_UpdateMallDiscount( //只组包不发送
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NMallProt::TVecDiscount& vecDisItems //限购道具
	);

	//发送：获取新帮派战历史
	bool Send_GetNewGuildBattleHistory( //发送给当前协议处理的服务器
	);
	bool SendSvr_GetNewGuildBattleHistory(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_GetNewGuildBattleHistory( //只组包不发送
	);

	//发送：新增新帮派战历史
	bool Send_AddNewGuildBattleHistory( //发送给当前协议处理的服务器
		const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
	);
	bool SendSvr_AddNewGuildBattleHistory(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
	);
	std::string& BuildPkg_AddNewGuildBattleHistory( //只组包不发送
		const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：帐号协议代理发送请求
	virtual void OnRecv_UserPackageProxy(
		UINT64 qwUsrID, //帐号ID
		UINT32 dwGateID, //所在网关服务器ID
		const TVecString& vecPackage //协议包列表
	) = 0;

	//接收：DB向GameSever推送角色信息/
	virtual void OnRecv_UserLoginNtf(
		EEnterType eEnterType, //进入的类型
		const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
		const TVecString& vecEnterString, //平台相关参数
		UINT32 dwGateId, //网关Id
		UINT64 qwUserId, //用户Id
		const NRoleInfoDefine::RoleDataInfo& RoleData //玩家数据
	) = 0;

	//接收：账号重新进入通知
	virtual void OnRecv_UserReEnterNotify(
		UINT64 qwUsrID, //账号ID
		UINT32 dwGateID, //所在网关服务器ID
		const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
		const TVecString& vecEnterString //平台相关参数
	) = 0;

	//接收：账号退出DBServer通知
	virtual void OnRecv_UserLogoutNtf(
		UINT64 qwUsrID, //账号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
	) = 0;

	//接收：离线事件通知
	virtual void OnRecv_NewOffEventNotice(
		UINT64 qwUsrID, //账号ID
		const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
	) = 0;

	//接收：新帮派战历史记录获取返回
	virtual void OnRecv_NewGuildBattleHistoryNotify(
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID) override;

	virtual UINT8 GetProtID() const override { return 4; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_UserPackageProxy(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserLoginNtf(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserReEnterNotify(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserLogoutNtf(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_NewOffEventNotice(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_NewGuildBattleHistoryNotify(const char* pBuf, UINT32 dwLen);

	/////////////////////协议返回函数/////////////////////
	bool _DoReturn_GetStatus(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetStatus(UINT32 dwSessionID);
	bool _DoReturn_SaveUserDataReq(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_SaveUserDataReq(UINT32 dwSessionID);
	bool _DoReturn_SaveOffLineDgnInfo(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_SaveOffLineDgnInfo(UINT32 dwSessionID);
	bool _DoReturn_LoadOffLineUserData(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_LoadOffLineUserData(UINT32 dwSessionID);
	bool _DoReturn_LoadWorldBossInfo(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_LoadWorldBossInfo(UINT32 dwSessionID);
	bool _DoReturn_GetUserIDFromName(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetUserIDFromName(UINT32 dwSessionID);
	bool _DoReturn_GetBattleReport(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetBattleReport(UINT32 dwSessionID);
	bool _DoReturn_AddBattleReport(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_AddBattleReport(UINT32 dwSessionID);
	bool _DoReturn_LoadMallDiscount(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_LoadMallDiscount(UINT32 dwSessionID);

private:
	typedef bool (CGame2DBCommClt::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _ReturnFuncs[];
	static THandleFunc _HandleFuncs[];

	typedef void (CGame2DBCommClt::*TTimeOutFunc)(UINT32 dwSessionID);
	static TTimeOutFunc _TimeoutFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGame2DBComm
