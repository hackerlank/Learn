/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    MapProt.h
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "MapProt.h"

namespace NMapProt
{

//协议类：地图相关功能的协议
class CMapProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：通知玩家进入地图
	bool Send_UserEnterMapNtf( //发送给当前协议处理的客户端
		UINT16 wMapID, //地图ID
		UINT64 qwRoleID, //当前的角色ID
		UINT8 byIndex, //地图序号,非主城返回255
		UINT8 byTotal, //同Id地图总数,非主城返回0
		const SPosition& rPosition, //进入位置
		float fDir //方向
	);
	bool SendClt_UserEnterMapNtf(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wMapID, //地图ID
		UINT64 qwRoleID, //当前的角色ID
		UINT8 byIndex, //地图序号,非主城返回255
		UINT8 byTotal, //同Id地图总数,非主城返回0
		const SPosition& rPosition, //进入位置
		float fDir //方向
	);
	std::string& BuildPkg_UserEnterMapNtf( //只组包不发送
		UINT16 wMapID, //地图ID
		UINT64 qwRoleID, //当前的角色ID
		UINT8 byIndex, //地图序号,非主城返回255
		UINT8 byTotal, //同Id地图总数,非主城返回0
		const SPosition& rPosition, //进入位置
		float fDir //方向
	);

	//发送：新地图产生，通知同地图玩家
	bool Send_NoticeNewMap( //发送给当前协议处理的客户端
		const TVecMapOverLoad& vecLoad //地图负载
	);
	bool SendClt_NoticeNewMap(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecMapOverLoad& vecLoad //地图负载
	);
	std::string& BuildPkg_NoticeNewMap( //只组包不发送
		const TVecMapOverLoad& vecLoad //地图负载
	);

	//发送：角色(非当前控制)地图信息通知
	bool Send_RoleMapInfoNtf( //发送给当前协议处理的客户端
		UINT64 qwRoleID, //角色的ID
		UINT16 wMapID //地图ID
	);
	bool SendClt_RoleMapInfoNtf(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwRoleID, //角色的ID
		UINT16 wMapID //地图ID
	);
	std::string& BuildPkg_RoleMapInfoNtf( //只组包不发送
		UINT64 qwRoleID, //角色的ID
		UINT16 wMapID //地图ID
	);

	//发送：通知角色移动失败
	bool Send_PlayerMoveFail( //发送给当前协议处理的客户端
		UINT64 qwRoleID, //角色ID
		const SPosition& rLastPosition, //上一个位置
		const TVecPosition& vecPosition //移动位置列表
	);
	bool SendClt_PlayerMoveFail(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwRoleID, //角色ID
		const SPosition& rLastPosition, //上一个位置
		const TVecPosition& vecPosition //移动位置列表
	);
	std::string& BuildPkg_PlayerMoveFail( //只组包不发送
		UINT64 qwRoleID, //角色ID
		const SPosition& rLastPosition, //上一个位置
		const TVecPosition& vecPosition //移动位置列表
	);

	//发送：通知自己的玩家角色出现
	bool Send_NotifyAppear( //发送给当前协议处理的客户端
		UINT64 qwRoleID, //角色ID
		const SPlayerAppear& rPlayerAppear, //玩家的外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		UINT32 dwAppearState //当前状态(EAppearState按位或的结果)
	);
	bool SendClt_NotifyAppear(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwRoleID, //角色ID
		const SPlayerAppear& rPlayerAppear, //玩家的外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		UINT32 dwAppearState //当前状态(EAppearState按位或的结果)
	);
	std::string& BuildPkg_NotifyAppear( //只组包不发送
		UINT64 qwRoleID, //角色ID
		const SPlayerAppear& rPlayerAppear, //玩家的外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		UINT32 dwAppearState //当前状态(EAppearState按位或的结果)
	);

	//发送：通知别的玩家角色出现
	bool Send_PlayerAppear( //发送给当前协议处理的客户端
		UINT64 qwRoleID, //角色ID
		const SPlayerAppear& rPlayerAppear, //玩家的外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		UINT32 dwAppearState, //当前状态(EAppearState按位或的结果)
		bool bBorn //true为出生，false为进入视野
	);
	bool SendClt_PlayerAppear(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwRoleID, //角色ID
		const SPlayerAppear& rPlayerAppear, //玩家的外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		UINT32 dwAppearState, //当前状态(EAppearState按位或的结果)
		bool bBorn //true为出生，false为进入视野
	);
	std::string& BuildPkg_PlayerAppear( //只组包不发送
		UINT64 qwRoleID, //角色ID
		const SPlayerAppear& rPlayerAppear, //玩家的外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		UINT32 dwAppearState, //当前状态(EAppearState按位或的结果)
		bool bBorn //true为出生，false为进入视野
	);

	//发送：通知Creature移动
	bool Send_NotifyCreatureMove( //发送给当前协议处理的客户端
		UINT64 qwCreatureID, //生物ID
		const TVecPosition& vecPosition //移动位置列表
	);
	bool SendClt_NotifyCreatureMove(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwCreatureID, //生物ID
		const TVecPosition& vecPosition //移动位置列表
	);
	std::string& BuildPkg_NotifyCreatureMove( //只组包不发送
		UINT64 qwCreatureID, //生物ID
		const TVecPosition& vecPosition //移动位置列表
	);

	//发送：通知Creature跳点
	bool Send_NotifyCreatureJump( //发送给当前协议处理的客户端
		UINT64 qwCreatureID, //Creature ID
		const SPosition& rPosition, //跳点目的位置
		UINT16 wJumpId //跳点ID
	);
	bool SendClt_NotifyCreatureJump(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwCreatureID, //Creature ID
		const SPosition& rPosition, //跳点目的位置
		UINT16 wJumpId //跳点ID
	);
	std::string& BuildPkg_NotifyCreatureJump( //只组包不发送
		UINT64 qwCreatureID, //Creature ID
		const SPosition& rPosition, //跳点目的位置
		UINT16 wJumpId //跳点ID
	);

	//发送：通知Creature当前状态
	bool Send_NotifyCreatureState( //发送给当前协议处理的客户端
		UINT64 qwCreatureID, //Creature ID
		UINT32 dwAppearState //当前状态(EAppearState按位或的结果)
	);
	bool SendClt_NotifyCreatureState(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwCreatureID, //Creature ID
		UINT32 dwAppearState //当前状态(EAppearState按位或的结果)
	);
	std::string& BuildPkg_NotifyCreatureState( //只组包不发送
		UINT64 qwCreatureID, //Creature ID
		UINT32 dwAppearState //当前状态(EAppearState按位或的结果)
	);

	//发送：通知Creature停止
	bool Send_NotifyCreatureStop( //发送给当前协议处理的客户端
		UINT64 qwCreatureID, //生物ID
		const SPosition& rDestPosition //最终位置
	);
	bool SendClt_NotifyCreatureStop(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwCreatureID, //生物ID
		const SPosition& rDestPosition //最终位置
	);
	std::string& BuildPkg_NotifyCreatureStop( //只组包不发送
		UINT64 qwCreatureID, //生物ID
		const SPosition& rDestPosition //最终位置
	);

	//发送：通知地图上生物消失
	bool Send_CreatureDisappear( //发送给当前协议处理的客户端
		UINT64 qwCreatureID, //生物ID
		bool bDieFade //true为死亡消失，false为移出视野
	);
	bool SendClt_CreatureDisappear(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwCreatureID, //生物ID
		bool bDieFade //true为死亡消失，false为移出视野
	);
	std::string& BuildPkg_CreatureDisappear( //只组包不发送
		UINT64 qwCreatureID, //生物ID
		bool bDieFade //true为死亡消失，false为移出视野
	);

	//发送：通知NPC出现
	bool Send_NpcAppear( //发送给当前协议处理的客户端
		UINT64 qwCreatureID, //生物ID
		const SNpcAppear& rNpcAppear, //NPC外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		bool bBorn //true为出生，false为进入视野
	);
	bool SendClt_NpcAppear(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwCreatureID, //生物ID
		const SNpcAppear& rNpcAppear, //NPC外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		bool bBorn //true为出生，false为进入视野
	);
	std::string& BuildPkg_NpcAppear( //只组包不发送
		UINT64 qwCreatureID, //生物ID
		const SNpcAppear& rNpcAppear, //NPC外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		bool bBorn //true为出生，false为进入视野
	);

	//发送：通知怪物出现
	bool Send_MonsterAppear( //发送给当前协议处理的客户端
		UINT64 qwCreatureID, //生物ID
		const SMonsterAppear& rMonsterAppear, //怪物外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		UINT32 dwAppearState, //当前状态(EAppearState按位或的结果)
		bool bBorn //true为出生，false为进入视野
	);
	bool SendClt_MonsterAppear(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwCreatureID, //生物ID
		const SMonsterAppear& rMonsterAppear, //怪物外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		UINT32 dwAppearState, //当前状态(EAppearState按位或的结果)
		bool bBorn //true为出生，false为进入视野
	);
	std::string& BuildPkg_MonsterAppear( //只组包不发送
		UINT64 qwCreatureID, //生物ID
		const SMonsterAppear& rMonsterAppear, //怪物外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		UINT32 dwAppearState, //当前状态(EAppearState按位或的结果)
		bool bBorn //true为出生，false为进入视野
	);

	//发送：通知开关出现
	bool Send_SwitcherAppear( //发送给当前协议处理的客户端
		UINT32 dwInstID, //唯一实例ID
		const SSwitcherAppear& rSwitcherAppear, //开关外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		bool bBorn //true为出生，false为进入视野
	);
	bool SendClt_SwitcherAppear(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwInstID, //唯一实例ID
		const SSwitcherAppear& rSwitcherAppear, //开关外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		bool bBorn //true为出生，false为进入视野
	);
	std::string& BuildPkg_SwitcherAppear( //只组包不发送
		UINT32 dwInstID, //唯一实例ID
		const SSwitcherAppear& rSwitcherAppear, //开关外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		bool bBorn //true为出生，false为进入视野
	);

	//发送：通知地图上开关消失
	bool Send_SwitcherDisappear( //发送给当前协议处理的客户端
		UINT32 dwInstID //开关唯一ID
	);
	bool SendClt_SwitcherDisappear(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwInstID //开关唯一ID
	);
	std::string& BuildPkg_SwitcherDisappear( //只组包不发送
		UINT32 dwInstID //开关唯一ID
	);

	//发送：通知开关当前状态
	bool Send_NotifySwitcherState( //发送给当前协议处理的客户端
		UINT32 dwInstID, //开关唯一实例ID
		bool bOpen //当前开关是否开启
	);
	bool SendClt_NotifySwitcherState(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwInstID, //开关唯一实例ID
		bool bOpen //当前开关是否开启
	);
	std::string& BuildPkg_NotifySwitcherState( //只组包不发送
		UINT32 dwInstID, //开关唯一实例ID
		bool bOpen //当前开关是否开启
	);

	//发送：通知采集物出现
	bool Send_GatherAppear( //发送给当前协议处理的客户端
		UINT32 dwGatherID, //生物ID
		const SGatherAppear& rGatherAppear, //采集物外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		bool bBorn //true为出生，false为进入视野
	);
	bool SendClt_GatherAppear(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwGatherID, //生物ID
		const SGatherAppear& rGatherAppear, //采集物外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		bool bBorn //true为出生，false为进入视野
	);
	std::string& BuildPkg_GatherAppear( //只组包不发送
		UINT32 dwGatherID, //生物ID
		const SGatherAppear& rGatherAppear, //采集物外观
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		bool bBorn //true为出生，false为进入视野
	);

	//发送：通知地图上采集物消失
	bool Send_GatherDisappear( //发送给当前协议处理的客户端
		UINT32 dwGatherID, //采集物ID
		bool bDieFade //true为采集后消失，false为移出视野
	);
	bool SendClt_GatherDisappear(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwGatherID, //采集物ID
		bool bDieFade //true为采集后消失，false为移出视野
	);
	std::string& BuildPkg_GatherDisappear( //只组包不发送
		UINT32 dwGatherID, //采集物ID
		bool bDieFade //true为采集后消失，false为移出视野
	);

	//发送：通知地图上采集物改变
	bool Send_GatherChange( //发送给当前协议处理的客户端
		UINT32 dwGatherID, //采集物ID
		const SGatherAppear& rGatherAppear //采集物外观
	);
	bool SendClt_GatherChange(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwGatherID, //采集物ID
		const SGatherAppear& rGatherAppear //采集物外观
	);
	std::string& BuildPkg_GatherChange( //只组包不发送
		UINT32 dwGatherID, //采集物ID
		const SGatherAppear& rGatherAppear //采集物外观
	);

	//发送：阻挡物出现
	bool Send_BlockerAppear( //发送给当前协议处理的客户端
		UINT32 dwInstID, //唯一ID
		const SBlockerAppear& rBlockerAppear, //阻挡物开关
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		bool bBorn //true为出生，false为进入视野
	);
	bool SendClt_BlockerAppear(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwInstID, //唯一ID
		const SBlockerAppear& rBlockerAppear, //阻挡物开关
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		bool bBorn //true为出生，false为进入视野
	);
	std::string& BuildPkg_BlockerAppear( //只组包不发送
		UINT32 dwInstID, //唯一ID
		const SBlockerAppear& rBlockerAppear, //阻挡物开关
		const SPosition& rPosition, //出现位置
		float fDir, //方向(弧度)
		bool bBorn //true为出生，false为进入视野
	);

	//发送：通知地图上阻挡物消失
	bool Send_BlockerDisappear( //发送给当前协议处理的客户端
		UINT32 dwInstID //阻挡物唯一ID
	);
	bool SendClt_BlockerDisappear(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwInstID //阻挡物唯一ID
	);
	std::string& BuildPkg_BlockerDisappear( //只组包不发送
		UINT32 dwInstID //阻挡物唯一ID
	);

	//发送：通知怪物改变
	bool Send_MonsterChange( //发送给当前协议处理的客户端
		UINT64 qwCreatureID, //生物ID
		const SMonsterAppear& rMonsterAppear //怪物外观
	);
	bool SendClt_MonsterChange(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwCreatureID, //生物ID
		const SMonsterAppear& rMonsterAppear //怪物外观
	);
	std::string& BuildPkg_MonsterChange( //只组包不发送
		UINT64 qwCreatureID, //生物ID
		const SMonsterAppear& rMonsterAppear //怪物外观
	);

	//发送：通知区域出现
	bool Send_AreaAppear( //发送给当前协议处理的客户端
		UINT32 dwAreaID, //区域实例ID
		const SAreaAppear& rAreaAppear, //区域外观
		const SPosition& rPosition //出现位置
	);
	bool SendClt_AreaAppear(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwAreaID, //区域实例ID
		const SAreaAppear& rAreaAppear, //区域外观
		const SPosition& rPosition //出现位置
	);
	std::string& BuildPkg_AreaAppear( //只组包不发送
		UINT32 dwAreaID, //区域实例ID
		const SAreaAppear& rAreaAppear, //区域外观
		const SPosition& rPosition //出现位置
	);

	//发送：通知地图上区域消失
	bool Send_AreaDisappear( //发送给当前协议处理的客户端
		UINT32 dwAreaID //区域实例ID
	);
	bool SendClt_AreaDisappear(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwAreaID //区域实例ID
	);
	std::string& BuildPkg_AreaDisappear( //只组包不发送
		UINT32 dwAreaID //区域实例ID
	);

	//发送：怪物发现敌人
	bool Send_MonsterTargetChange( //发送给当前协议处理的客户端
		UINT64 qwMonsterID, //怪物ID
		UINT64 qwTargetID //目标ID
	);
	bool SendClt_MonsterTargetChange(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwMonsterID, //怪物ID
		UINT64 qwTargetID //目标ID
	);
	std::string& BuildPkg_MonsterTargetChange( //只组包不发送
		UINT64 qwMonsterID, //怪物ID
		UINT64 qwTargetID //目标ID
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：角色移动请求
	virtual void OnRecv_PlayerMoveReq(
		UINT16 wMapID, //地图ID
		const TVecPosition& vecPosition //移动位置列表
	) = 0;

	//接收：角色停止移动
	virtual void OnRecv_PlayerStopReq(
		UINT16 wMapID, //地图ID
		const SPosition& StopPos //停止点
	) = 0;

	struct SGetPlayerAppearAck : public CClientFuncAck
	{
		UINT8 byRet; //0 成功 1失败
		SPlayerAppear rPlayerAppear; //玩家的外观

		SGetPlayerAppearAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取玩家的外观信息
	virtual bool OnRecv_GetPlayerAppear(
		UINT64 qwUserID, //目标玩家ID
		shared_func<SGetPlayerAppearAck>& fnAck //返回回调函数
	) = 0;

	struct SJumpMapAck : public CClientFuncAck
	{
		UINT8 byRet; //0成功
		UINT16 wMapID; //地图ID
		UINT8 byIndex; //地图序号,255表示任意地图

		SJumpMapAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求跳地图
	virtual bool OnRecv_JumpMap(
		UINT16 wMapID, //地图ID
		UINT8 byIndex, //地图序号,255表示任意地图
		shared_func<SJumpMapAck>& fnAck //返回回调函数
	) = 0;

	struct SGetMapOverLoadAck : public CClientFuncAck
	{
		UINT16 wMapID; //地图ID
		TVecMapOverLoad vecLoad; //地图ID

		SGetMapOverLoadAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求地图负载
	virtual bool OnRecv_GetMapOverLoad(
		UINT16 wMapID, //地图ID
		shared_func<SGetMapOverLoadAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 5; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_PlayerMoveReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_PlayerStopReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPlayerAppear(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_JumpMap(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetMapOverLoad(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CMapProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NMapProt
