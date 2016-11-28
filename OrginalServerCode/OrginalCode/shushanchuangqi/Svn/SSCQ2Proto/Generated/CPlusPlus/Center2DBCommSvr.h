/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Center2DBComm.h
//  Purpose:      CenterServer到DBServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Center2DBComm.h"

namespace NCenter2DBComm
{

//协议类：CenterServer到DBServer的通信协议
class CCenter2DBCommSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：返回查询结果
	bool Send_SendResult2Cent( //发送给当前协议处理的服务器
		const SBaseCond& sCond, //查询条件
		const SBaseResult& sResult //查询结果
	);
	bool SendSvr_SendResult2Cent(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const SBaseCond& sCond, //查询条件
		const SBaseResult& sResult //查询结果
	);
	std::string& BuildPkg_SendResult2Cent( //只组包不发送
		const SBaseCond& sCond, //查询条件
		const SBaseResult& sResult //查询结果
	);

	//发送：返回所有玩家ID和名字
	bool Send_SendAllUserIDAndName( //发送给当前协议处理的服务器
		UINT32 dwTotalSize, //总条数
		const NPHPProt::TVecUserIDAndName& vecUserIDAndName //玩家ID和名字
	);
	bool SendSvr_SendAllUserIDAndName(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwTotalSize, //总条数
		const NPHPProt::TVecUserIDAndName& vecUserIDAndName //玩家ID和名字
	);
	std::string& BuildPkg_SendAllUserIDAndName( //只组包不发送
		UINT32 dwTotalSize, //总条数
		const NPHPProt::TVecUserIDAndName& vecUserIDAndName //玩家ID和名字
	);

	//发送：返回所有公告
	bool Send_SendAllNotice( //发送给当前协议处理的服务器
		const NPHPProt::TVecNotice& vecNotice //公告内容
	);
	bool SendSvr_SendAllNotice(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NPHPProt::TVecNotice& vecNotice //公告内容
	);
	std::string& BuildPkg_SendAllNotice( //只组包不发送
		const NPHPProt::TVecNotice& vecNotice //公告内容
	);

	//发送：返回请求斗剑信息
	bool Send_SendAllArena( //发送给当前协议处理的服务器
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NArenaGS::TVecArenaPlayerData& vecSendDate //更新信息
	);
	bool SendSvr_SendAllArena(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NArenaGS::TVecArenaPlayerData& vecSendDate //更新信息
	);
	std::string& BuildPkg_SendAllArena( //只组包不发送
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NArenaGS::TVecArenaPlayerData& vecSendDate //更新信息
	);

	//发送：返回机器人天梯排行信息
	bool Send_SendAllRobot( //发送给当前协议处理的服务器
		const NArenaGS::TVecLadderRobot& vecRobot //机器人排行信息
	);
	bool SendSvr_SendAllRobot(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NArenaGS::TVecLadderRobot& vecRobot //机器人排行信息
	);
	std::string& BuildPkg_SendAllRobot( //只组包不发送
		const NArenaGS::TVecLadderRobot& vecRobot //机器人排行信息
	);

	//发送：返回请求排行榜数据
	bool Send_RankInitNotify( //发送给当前协议处理的服务器
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NRankProt::TVecRankInfo& vecRankInfo //更新信息
	);
	bool SendSvr_RankInitNotify(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NRankProt::TVecRankInfo& vecRankInfo //更新信息
	);
	std::string& BuildPkg_RankInitNotify( //只组包不发送
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NRankProt::TVecRankInfo& vecRankInfo //更新信息
	);

	//发送：返回请求崇拜数据
	bool Send_AdoreInitNotify( //发送给当前协议处理的服务器
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NRankProt::TVecDBAdoreInfo& vecAdoreInfo //更新信息
	);
	bool SendSvr_AdoreInitNotify(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NRankProt::TVecDBAdoreInfo& vecAdoreInfo //更新信息
	);
	std::string& BuildPkg_AdoreInitNotify( //只组包不发送
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NRankProt::TVecDBAdoreInfo& vecAdoreInfo //更新信息
	);

	//发送：返回所有九疑鼎信息
	bool Send_SendAllTripod( //发送给当前协议处理的服务器
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NTripodProt::TVecTripodData& vecSendData //更新信息
	);
	bool SendSvr_SendAllTripod(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NTripodProt::TVecTripodData& vecSendData //更新信息
	);
	std::string& BuildPkg_SendAllTripod( //只组包不发送
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NTripodProt::TVecTripodData& vecSendData //更新信息
	);

	//发送：返回所有九疑鼎的协助信息
	bool Send_SendAllTripodHelper( //发送给当前协议处理的服务器
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NTripodProt::TVecTripodHelp& vecSendData //更新信息
	);
	bool SendSvr_SendAllTripodHelper(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NTripodProt::TVecTripodHelp& vecSendData //更新信息
	);
	std::string& BuildPkg_SendAllTripodHelper( //只组包不发送
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NTripodProt::TVecTripodHelp& vecSendData //更新信息
	);

	//发送：返回所有九疑鼎的动态信息
	bool Send_SendAllTripodLog( //发送给当前协议处理的服务器
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NTripodProt::TVecTripodLog& vecSendData //更新信息
	);
	bool SendSvr_SendAllTripodLog(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NTripodProt::TVecTripodLog& vecSendData //更新信息
	);
	std::string& BuildPkg_SendAllTripodLog( //只组包不发送
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NTripodProt::TVecTripodLog& vecSendData //更新信息
	);

	//发送：平台参数加载返回
	bool Send_PlatformParamInfoNotify( //发送给当前协议处理的服务器
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const TVecUINT64& vecRoleID, //玩家ID
		const NProtoCommon::TVecPlatformParam& vecPlatformParam //更新信息
	);
	bool SendSvr_PlatformParamInfoNotify(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const TVecUINT64& vecRoleID, //玩家ID
		const NProtoCommon::TVecPlatformParam& vecPlatformParam //更新信息
	);
	std::string& BuildPkg_PlatformParamInfoNotify( //只组包不发送
		UINT32 dwCurSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const TVecUINT64& vecRoleID, //玩家ID
		const NProtoCommon::TVecPlatformParam& vecPlatformParam //更新信息
	);

	//发送：返回请求金船信息
	bool Send_SendAllShip( //发送给当前协议处理的服务器
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NShipProt::TVecPlayerShip& vecSendDate //更新信息
	);
	bool SendSvr_SendAllShip(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NShipProt::TVecPlayerShip& vecSendDate //更新信息
	);
	std::string& BuildPkg_SendAllShip( //只组包不发送
		UINT32 dwPageSize, //已发送条数
		UINT32 dwTotalSize, //总条数
		const NShipProt::TVecPlayerShip& vecSendDate //更新信息
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

	//接收：插入玩家充值仙石信息(未创角预先充值)
	virtual void OnRecv_InsertRecharge(
		const NRoleInfoDefine::SRecharge& oRecharge //充值仙石的数据
	) = 0;

	struct SLoadPrepaidAck : public CServerFuncAck
	{
		NRoleInfoDefine::TVecPrepaid vecPrepaid; //玩家未创角预先值信息

		SLoadPrepaidAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：加载玩家未创角预先充值的仙石信息
	virtual bool OnRecv_LoadPrepaid(
		shared_func<SLoadPrepaidAck>& fnAck //返回回调函数
	) = 0;

	//接收：更新玩家未创角预先充值信息
	virtual void OnRecv_UpdatePrepaid(
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		UINT64 qwRoleID, //玩家ID
		UINT32 dwGold //仙石数量
	) = 0;

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

	//接收：一行数据更新
	virtual void OnRecv_RoleDataUpdate(
		UINT64 qwRoleId, //角色Id
		NRoleInfoDefine::EDataType eDataType, //更新数据块
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const std::string& strData //更新数据
	) = 0;

	//接收：获取排名信息
	virtual void OnRecv_GetRankInfo(
	) = 0;

	//接收：排行榜数据更新
	virtual void OnRecv_RankDataUpdate(
		UINT64 qwInstID, //唯一ID
		NRankProt::ERankType eDataType, //更新数据类型
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	) = 0;

	//接收：获取崇拜信息
	virtual void OnRecv_GetAdoreInfo(
	) = 0;

	//接收：崇拜数据更新
	virtual void OnRecv_AdoreDataUpdate(
		UINT64 qwInstID, //唯一ID
		NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
		const std::string& strData //更新数据
	) = 0;

	//接收：获取账号ID或主角色名请求
	virtual void OnRecv_UserIDNameReq(
		NServerCommon::EUserReqType eType, //类型
		UINT64 qwUsrID, //帐号ID
		const std::string& strName, //主角色名称
		UINT64 qwUsrData //用户数据
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

	struct SGetAllMailListAck : public CServerFuncAck
	{
		NMailProt::TVecMailDetail vecMails; //邮件列表

		SGetAllMailListAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获得邮件列表
	virtual bool OnRecv_GetAllMailList(
		UINT64 qwRoleID, //玩家ID
		UINT32 dwOverTime, //过期时间
		shared_func<SGetAllMailListAck>& fnAck //返回回调函数
	) = 0;

	struct SSaveMailAck : public CServerFuncAck
	{
		INT8 byRet; //非0表示失败

		SSaveMailAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：保存邮件
	virtual bool OnRecv_SaveMail(
		UINT64 qwMailID, //邮件ID
		UINT64 qwReceiveID, //接受者ID
		UINT64 qwSenderID, //发送者ID
		const std::string& strSenderName, //发送者名字
		NMailProt::EMailType eMailType, //邮件类型
		NMailProt::EMailState eMailState, //邮件状态
		UINT32 dwSendTime, //发送时间
		const std::string& strTitle, //标题
		const std::string& strMsg, //邮件内容
		shared_func<SSaveMailAck>& fnAck //返回回调函数
	) = 0;

	struct SDeleteMailAck : public CServerFuncAck
	{
		INT8 byRet; //非0表示失败

		SDeleteMailAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：删除邮件
	virtual bool OnRecv_DeleteMail(
		UINT64 qwRoleID, //玩家ID
		const TVecMailDelData& vecMailIDs, //邮件ID列表
		shared_func<SDeleteMailAck>& fnAck //返回回调函数
	) = 0;

	struct SSaveSystemMailAck : public CServerFuncAck
	{
		INT8 byRet; //非0表示失败

		SSaveSystemMailAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：保存系统邮件
	virtual bool OnRecv_SaveSystemMail(
		const TVecSystemMailTargetInfo& vecSystemMailTargetInfo, //邮件目标
		const SSystemMailInfo& rSystemMailInfo, //系统邮件信息
		shared_func<SSaveSystemMailAck>& fnAck //返回回调函数
	) = 0;

	struct SUpdateMailStatusAck : public CServerFuncAck
	{
		INT8 byRet; //非0表示失败

		SUpdateMailStatusAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：更新邮件状态
	virtual bool OnRecv_UpdateMailStatus(
		UINT64 qwMailID, //邮件ID
		NMailProt::EMailState eMailState, //邮件状态
		shared_func<SUpdateMailStatusAck>& fnAck //返回回调函数
	) = 0;

	struct SDelMailAttachAck : public CServerFuncAck
	{
		INT8 byRet; //非0表示失败

		SDelMailAttachAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：删除邮件附件
	virtual bool OnRecv_DelMailAttach(
		const MailDelData& stDelData, //删除提示
		shared_func<SDelMailAttachAck>& fnAck //返回回调函数
	) = 0;

	struct SGetPrizeStatusAck : public CServerFuncAck
	{
		NWonderActivityProt::TVecWonderPrize2DB vecRet; //查询结果

		SGetPrizeStatusAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：查询玩家奖励状态
	virtual bool OnRecv_GetPrizeStatus(
		shared_func<SGetPrizeStatusAck>& fnAck //返回回调函数
	) = 0;

	//接收：删除玩家数据
	virtual void OnRecv_DelActPrizeData(
		UINT16 wActID //活动ID
	) = 0;

	struct SGetAllRoleLevelAck : public CServerFuncAck
	{
		UINT8 byTypeRet; //类型
		TVecRoleLevel vecRoleLevel; //返回玩家等级

		SGetAllRoleLevelAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：查询所有玩家信息
	virtual bool OnRecv_GetAllRoleLevel(
		UINT8 byType, //类型
		shared_func<SGetAllRoleLevelAck>& fnAck //返回回调函数
	) = 0;

	//接收：更新玩家奖励状态
	virtual void OnRecv_UpdatePrizeStatus(
		const NWonderActivityProt::SWonderPrize2DB& sPrize2DB, //玩家信息
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	) = 0;

	struct SGetRetainAck : public CServerFuncAck
	{
		NWonderActivityProt::TVecRetain vecRet; //查询结果

		SGetRetainAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：查询玩家保留信息
	virtual bool OnRecv_GetRetain(
		shared_func<SGetRetainAck>& fnAck //返回回调函数
	) = 0;

	//接收：更新玩家保留信息
	virtual void OnRecv_UpdateRetain(
		const NWonderActivityProt::SRetain& sRetain, //玩家保留信息
		NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
	) = 0;

	//接收：删除玩家保留数据
	virtual void OnRecv_DelActRetainData(
		UINT16 wActID //活动ID
	) = 0;

	//接收：请求所有UserID和name
	virtual void OnRecv_GetAllUserIDAndName(
	) = 0;

	//接收：请求所有公告
	virtual void OnRecv_GetAllNotice(
	) = 0;

	//接收：增加公告
	virtual void OnRecv_AddNotice(
		const NPHPProt::SNotice& sNotice //公告内容
	) = 0;

	//接收：删除公告
	virtual void OnRecv_DelNotice(
		UINT32 dwNoticeID //公告ID
	) = 0;

	//接收：请求斗剑信息
	virtual void OnRecv_GetAllArena(
		UINT32 dwPageSize //发送条数
	) = 0;

	//接收：更新斗剑数据
	virtual void OnRecv_UpdateAllArena(
		const NArenaGS::TVecArenaPlayerBaseDataUpdate& vecUpdate //更新信息
	) = 0;

	//接收：删除玩家斗剑数据
	virtual void OnRecv_DelPlayerArena(
		const TVecUINT64& vecDel //删除玩家斗剑信息
	) = 0;

	struct SGetGameVarAck : public CServerFuncAck
	{
		NRoleInfoDefine::TVecGameVarsDBInfo vecVar; //返回的Var

		SGetGameVarAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求系统Var数据
	virtual bool OnRecv_GetGameVar(
		shared_func<SGetGameVarAck>& fnAck //返回回调函数
	) = 0;

	//接收：更新系统Var数据
	virtual void OnRecv_UpdateGameVar(
		const NRoleInfoDefine::SGameVarsDBInfo& Var //更新的Var
	) = 0;

	//接收：增加系统Var数据
	virtual void OnRecv_AddGameVar(
		const NRoleInfoDefine::SGameVarsDBInfo& Var //增加的Var
	) = 0;

	//接收：删除Var数据
	virtual void OnRecv_DelGameVar(
		UINT16 wVarID //删除的VarID
	) = 0;

	struct SGetArenaFighterByIDAck : public CServerFuncAck
	{
		NArenaGS::SArenaFighter stFighter; //返回的数据

		SGetArenaFighterByIDAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：根据玩家ID获得竞技基本数据
	virtual bool OnRecv_GetArenaFighterByID(
		UINT64 qwRoleID, //玩家的ID
		shared_func<SGetArenaFighterByIDAck>& fnAck //返回回调函数
	) = 0;

	struct SGetDemonTowerInfoAck : public CServerFuncAck
	{
		NDemonTowerGS::TVecDemonTowerPlayer vecDemonTowerPlayer; //镇妖塔玩家信息

		SGetDemonTowerInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取镇妖塔信息（启动预加载调用）
	virtual bool OnRecv_GetDemonTowerInfo(
		shared_func<SGetDemonTowerInfoAck>& fnAck //返回回调函数
	) = 0;

	//接收：更新镇妖塔玩家信息
	virtual void OnRecv_UpateDemonTowerInfo(
		NDemonTowerGS::EDemonTowerDB eDbType, //更新类型
		const NDemonTowerGS::SDemonTowerPlayer& oDemonTowerPlayer //镇妖塔玩家信息
	) = 0;

	struct SGetCenterDataAck : public CServerFuncAck
	{
		TVecCenterData vecCenterData; //中心服数据

		SGetCenterDataAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取中心服数据
	virtual bool OnRecv_GetCenterData(
		shared_func<SGetCenterDataAck>& fnAck //返回回调函数
	) = 0;

	//接收：更新中心服数据
	virtual void OnRecv_UpateCenterData(
		const SCenterData& oCenterData, //中心服数据
		bool bDelete //删除/更新
	) = 0;

	struct SGetWhisperInfoAck : public CServerFuncAck
	{
		NGlobalChatProt::SWhisperInfo whisperInfo; //返回的数据

		SGetWhisperInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：查看玩家私聊信息
	virtual bool OnRecv_GetWhisperInfo(
		UINT64 qwRoleID, //玩家的ID
		shared_func<SGetWhisperInfoAck>& fnAck //返回回调函数
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
		UINT64 qwRoleID, //玩家的ID
		const NRoleInfoDefine::SBattleRePort& sReport, //战斗数据
		UINT8 byNum, //超过byNum，返回删除的旧的战报,0表示不删除
		shared_func<SAddBattleReportAck>& fnAck //返回回调函数
	) = 0;

	//接收：重新加载表格
	virtual void OnRecv_ReloadTable(
		const TVecString& vecTableName //表格名字
	) = 0;

	//接收：请求所有九疑鼎信息
	virtual void OnRecv_GetAllTripod(
		UINT32 dwPageSize //发送条数
	) = 0;

	//接收：请求所有九疑鼎的协助信息
	virtual void OnRecv_GetAllTripodHelper(
		UINT32 dwPageSize //发送条数
	) = 0;

	//接收：请求所有九疑鼎的动态信息
	virtual void OnRecv_GetAllTripodLog(
		UINT32 dwPageSize //发送条数
	) = 0;

	//接收：更新玩家九疑鼎信息
	virtual void OnRecv_UpdateTripod(
		UINT64 qwRoleID, //玩家的ID
		const NTripodProt::STripodInfo& oTripodInfo //九疑鼎的数据
	) = 0;

	//接收：更新玩家九疑鼎协助信息
	virtual void OnRecv_UpateTripodHelp(
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NTripodProt::STripodHelp& oTripodHelp //九疑鼎协助的信息
	) = 0;

	//接收：更新玩家九疑鼎动态信息
	virtual void OnRecv_UpdateTripodLog(
		UINT64 qwRoleID, //玩家的ID
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NTripodProt::STripodLog& oTripodLog //九疑鼎动态的信息
	) = 0;

	//接收：增加离线事件
	virtual void OnRecv_AddOffLineEvent(
		const TVecUINT64& vecRoleID, //玩家的ID
		const NRoleInfoDefine::SEventOffLine& sEventData //事件
	) = 0;

	//接收：对玩家封号
	virtual void OnRecv_FreezePlayer(
		UINT64 qwRoleID, //玩家的ID
		UINT32 dwFreezeTimer //封号
	) = 0;

	//接收：对玩家禁言
	virtual void OnRecv_ForbitChat(
		UINT64 qwRoleID, //玩家的ID
		UINT32 dwForbitTimer //禁言时间
	) = 0;

	//接收：将玩家登录时IP写入数据库
	virtual void OnRecv_UpdateLoginIP(
		UINT64 qwUserID, //玩家的ID
		const std::string& strLoginIP //登录时IP
	) = 0;

	//接收：请求拉取进入参数
	virtual void OnRecv_GetPlatformParam(
	) = 0;

	//接收：数据库查询
	virtual void OnRecv_GetResult2DB(
		const SBaseCond& sBaseCond //查询条件
	) = 0;

	//接收：请求金船信息
	virtual void OnRecv_GetAllShip(
		UINT32 dwPageSize //发送条数
	) = 0;

	//接收：更新金船数据
	virtual void OnRecv_UpdateShip(
		const NShipProt::PlayerShip& UpdateInfo //更新信息
	) = 0;

	//接收：删除金船数据
	virtual void OnRecv_DelShip(
		UINT64 qwInsID //删除金船信息
	) = 0;

	//接收：增加金船报告
	virtual void OnRecv_AddShipReport(
		UINT64 qwRoleID, //报告拥有者
		const NShipProt::ShipReport& sReport //报告内容
	) = 0;

	//接收：删除金船报告
	virtual void OnRecv_DelShipReport(
		UINT64 qwRoleID, //报告拥有者
		UINT64 qwInsID //金船唯一ID
	) = 0;

	//接收：天元神兽同步玩家信息
	virtual void OnRecv_SyncMonsterUserInfo(
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NGodMonsterProt::SGuildUser2DB& sUser //数据
	) = 0;

	struct SGetGodMonsterInfoAck : public CServerFuncAck
	{
		NGodMonsterProt::TVecGuildUser2DB vecUser; //天元神兽玩家信息

		SGetGodMonsterInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取天元神兽信息（启动预加载调用）
	virtual bool OnRecv_GetGodMonsterInfo(
		shared_func<SGetGodMonsterInfoAck>& fnAck //返回回调函数
	) = 0;

	//接收：天元神兽同步玩家限购礼包信息
	virtual void OnRecv_SyncLimitPrizeInfo(
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NGodMonsterProt::SLimitPrize2DB& oLimitPrize //数据
	) = 0;

	struct SGetLimitPrizeInfoAck : public CServerFuncAck
	{
		NGodMonsterProt::TVecLimitPrize2DB vecLimitPrize; //数据

		SGetLimitPrizeInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取天元神兽玩家限购礼包信息（启动预加载调用）
	virtual bool OnRecv_GetLimitPrizeInfo(
		shared_func<SGetLimitPrizeInfoAck>& fnAck //返回回调函数
	) = 0;

	//接收：运营活动中心同步信息
	virtual void OnRecv_SyncActivityCenterInfo(
		NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
		const NProtoCommon::SActivityOpt& oActOpt //数据
	) = 0;

	struct SGetActivityCenterInfoAck : public CServerFuncAck
	{
		NProtoCommon::TVecActivityOpt vecActOpt; //数据

		SGetActivityCenterInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：运营活动中心操作（启动预加载调用）
	virtual bool OnRecv_GetActivityCenterInfo(
		shared_func<SGetActivityCenterInfoAck>& fnAck //返回回调函数
	) = 0;

	//接收：增加机器人新信息
	virtual void OnRecv_AddLadderRobot(
		const NArenaGS::TVecLadderRobot& vecData //数据
	) = 0;

	//接收：增加机器人新信息
	virtual void OnRecv_UpdateLadderRobot(
		const NArenaGS::SLadderRobot& SData //数据
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 31; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_KeepAlive(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetStatus(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_InsertRecharge(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LoadPrepaid(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdatePrepaid(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReplaceUser(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LoadOffLineUserData(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_RoleDataUpdate(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetRankInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_RankDataUpdate(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAdoreInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AdoreDataUpdate(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserIDNameReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetUserIDFromName(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllMailList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SaveMail(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DeleteMail(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SaveSystemMail(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateMailStatus(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DelMailAttach(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPrizeStatus(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DelActPrizeData(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllRoleLevel(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdatePrizeStatus(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetRetain(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateRetain(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DelActRetainData(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllUserIDAndName(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllNotice(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddNotice(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DelNotice(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllArena(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateAllArena(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DelPlayerArena(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetGameVar(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateGameVar(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddGameVar(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DelGameVar(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetArenaFighterByID(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetDemonTowerInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpateDemonTowerInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetCenterData(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpateCenterData(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetWhisperInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetBattleReport(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddBattleReport(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReloadTable(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllTripod(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllTripodHelper(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllTripodLog(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateTripod(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpateTripodHelp(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateTripodLog(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddOffLineEvent(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FreezePlayer(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ForbitChat(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateLoginIP(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPlatformParam(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetResult2DB(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllShip(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateShip(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DelShip(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddShipReport(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DelShipReport(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SyncMonsterUserInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetGodMonsterInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SyncLimitPrizeInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetLimitPrizeInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SyncActivityCenterInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetActivityCenterInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddLadderRobot(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateLadderRobot(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CCenter2DBCommSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NCenter2DBComm
