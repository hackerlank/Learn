/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Horse.h
//  Purpose:      坐骑
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Horse.h"

namespace NHorse
{

//协议类：坐骑
class CHorseSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：坐骑信息
	bool Send_HorseNotifyList( //发送给当前协议处理的客户端
		const TVecHorseInfo& vecHorseInfo //坐骑信息
	);
	bool SendClt_HorseNotifyList(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecHorseInfo& vecHorseInfo //坐骑信息
	);
	std::string& BuildPkg_HorseNotifyList( //只组包不发送
		const TVecHorseInfo& vecHorseInfo //坐骑信息
	);

	//发送：坐骑信息更新
	bool Send_HorseInfoChangeNotifyList( //发送给当前协议处理的客户端
		UINT32 dwHorseOpType, //更新类型
		const SHorseInfo& oHorseInfo //坐骑信息更新
	);
	bool SendClt_HorseInfoChangeNotifyList(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwHorseOpType, //更新类型
		const SHorseInfo& oHorseInfo //坐骑信息更新
	);
	std::string& BuildPkg_HorseInfoChangeNotifyList( //只组包不发送
		UINT32 dwHorseOpType, //更新类型
		const SHorseInfo& oHorseInfo //坐骑信息更新
	);

	//发送：坐骑属性信息
	bool Send_HorseAttrNotify( //发送给当前协议处理的客户端
		UINT32 dwHorseID, //坐骑ID
		const NProtoCommon::TVecFtAttrMod& vecAttrInfo //坐骑属性信息表
	);
	bool SendClt_HorseAttrNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwHorseID, //坐骑ID
		const NProtoCommon::TVecFtAttrMod& vecAttrInfo //坐骑属性信息表
	);
	std::string& BuildPkg_HorseAttrNotify( //只组包不发送
		UINT32 dwHorseID, //坐骑ID
		const NProtoCommon::TVecFtAttrMod& vecAttrInfo //坐骑属性信息表
	);

	//发送：玩家速度通知
	bool Send_SpeedChangeNotify( //发送给当前协议处理的客户端
		UINT32 dwSpeed //玩家速度
	);
	bool SendClt_SpeedChangeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwSpeed //玩家速度
	);
	std::string& BuildPkg_SpeedChangeNotify( //只组包不发送
		UINT32 dwSpeed //玩家速度
	);

	//发送：坐骑外观改变
	bool Send_HorseLookChangeNotify( //发送给当前协议处理的客户端
		UINT64 qwRoleID, //角色Id
		UINT32 dwHorseID, //坐骑模型
		UINT32 dwHorseLevel //坐骑等级
	);
	bool SendClt_HorseLookChangeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwRoleID, //角色Id
		UINT32 dwHorseID, //坐骑模型
		UINT32 dwHorseLevel //坐骑等级
	);
	std::string& BuildPkg_HorseLookChangeNotify( //只组包不发送
		UINT64 qwRoleID, //角色Id
		UINT32 dwHorseID, //坐骑模型
		UINT32 dwHorseLevel //坐骑等级
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：获取坐骑信息
	virtual void OnRecv_GetHorseList(
	) = 0;

	struct SActiveHorseAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果 0成功其他错误码

		SActiveHorseAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：激活坐骑
	virtual bool OnRecv_ActiveHorse(
		UINT32 dwHorseID, //坐骑ID
		shared_func<SActiveHorseAck>& fnAck //返回回调函数
	) = 0;

	struct SUpgradeHorseAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果 0成功其他错误码

		SUpgradeHorseAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：坐骑进阶
	virtual bool OnRecv_UpgradeHorse(
		UINT32 dwHorseID, //坐骑ID
		bool bAll, //是否一键进阶
		shared_func<SUpgradeHorseAck>& fnAck //返回回调函数
	) = 0;

	struct SSetHorseStatusAck : public CClientFuncAck
	{
		bool bRet; //结果

		SSetHorseStatusAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：骑乘状态修改
	virtual bool OnRecv_SetHorseStatus(
		UINT32 dwHorseID, //坐骑ID
		UINT32 eHorseStatus, //骑乘状态
		shared_func<SSetHorseStatusAck>& fnAck //返回回调函数
	) = 0;

	struct SGetHorseAttrAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果 0成功其他错误码

		SGetHorseAttrAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取坐骑属性
	virtual bool OnRecv_GetHorseAttr(
		UINT32 dwHorseID, //坐骑ID id=0为所有坐骑属性
		shared_func<SGetHorseAttrAck>& fnAck //返回回调函数
	) = 0;

	struct SUnLockHorseSkillAttrAck : public CClientFuncAck
	{
		bool bRet; //结果

		SUnLockHorseSkillAttrAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：解锁技能属性（暂时不用）
	virtual bool OnRecv_UnLockHorseSkillAttr(
		UINT32 dwHorseID, //坐骑ID
		UINT32 dwPos, //第几个技能属性 1开始
		shared_func<SUnLockHorseSkillAttrAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 74; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetHorseList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ActiveHorse(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpgradeHorse(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetHorseStatus(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetHorseAttr(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UnLockHorseSkillAttr(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CHorseSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NHorse
