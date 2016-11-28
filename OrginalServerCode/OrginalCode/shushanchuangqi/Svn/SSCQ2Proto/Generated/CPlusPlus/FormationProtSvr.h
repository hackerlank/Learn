/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Formation.h
//  Purpose:      阵灵相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "FormationProt.h"

namespace NFormationProt
{

//协议类：阵灵相关协议
class CFormationProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：阵形信息
	bool Send_FormationNotify( //发送给当前协议处理的客户端
		UINT16 wFormationID, //阵形ID
		UINT8 bySelected //状态: 0-未启用 1-未启用
	);
	bool SendClt_FormationNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wFormationID, //阵形ID
		UINT8 bySelected //状态: 0-未启用 1-未启用
	);
	std::string& BuildPkg_FormationNotify( //只组包不发送
		UINT16 wFormationID, //阵形ID
		UINT8 bySelected //状态: 0-未启用 1-未启用
	);

	//发送：阵灵信息
	bool Send_PetDataNotify( //发送给当前协议处理的客户端
		UINT16 wPetID, //阵灵ID
		UINT8 bySelected, //状态: 0-未启用 1-出战且显示 2-出战隐藏
		UINT8 byLevel, //阵灵等级
		UINT32 dwExp //经验
	);
	bool SendClt_PetDataNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wPetID, //阵灵ID
		UINT8 bySelected, //状态: 0-未启用 1-出战且显示 2-出战隐藏
		UINT8 byLevel, //阵灵等级
		UINT32 dwExp //经验
	);
	std::string& BuildPkg_PetDataNotify( //只组包不发送
		UINT16 wPetID, //阵灵ID
		UINT8 bySelected, //状态: 0-未启用 1-出战且显示 2-出战隐藏
		UINT8 byLevel, //阵灵等级
		UINT32 dwExp //经验
	);

	//发送：全局阵灵信息
	bool Send_RolePetNotify( //发送给当前协议处理的客户端
		const NRoleInfoDefine::SRolePetInfo& sRolePetInfo //阵灵全局信息
	);
	bool SendClt_RolePetNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const NRoleInfoDefine::SRolePetInfo& sRolePetInfo //阵灵全局信息
	);
	std::string& BuildPkg_RolePetNotify( //只组包不发送
		const NRoleInfoDefine::SRolePetInfo& sRolePetInfo //阵灵全局信息
	);

	//发送：兽魂信息
	bool Send_BeastNotify( //发送给当前协议处理的客户端
		UINT16 wBeastID //兽魂ID
	);
	bool SendClt_BeastNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wBeastID //兽魂ID
	);
	std::string& BuildPkg_BeastNotify( //只组包不发送
		UINT16 wBeastID //兽魂ID
	);

	//发送：兽魂信息
	bool Send_BeastSoulNotify( //发送给当前协议处理的客户端
		const NRoleInfoDefine::TVecBeastSoulInfo& vecBeastSoul //兽魂信息
	);
	bool SendClt_BeastSoulNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const NRoleInfoDefine::TVecBeastSoulInfo& vecBeastSoul //兽魂信息
	);
	std::string& BuildPkg_BeastSoulNotify( //只组包不发送
		const NRoleInfoDefine::TVecBeastSoulInfo& vecBeastSoul //兽魂信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SFormationUpAck : public CClientFuncAck
	{
		EFormPetType eResult; //结果

		SFormationUpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：上阵/下阵
	virtual bool OnRecv_FormationUp(
		UINT64 qwInstID, //散仙唯一ID
		INT32 iPos, //目标位置: [0-8]为上阵 <-1时为下阵
		shared_func<SFormationUpAck>& fnAck //返回回调函数
	) = 0;

	struct SSetFormationAck : public CClientFuncAck
	{
		bool bRet; //结果

		SSetFormationAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：设置阵形
	virtual bool OnRecv_SetFormation(
		const TVecSLineup& vecSLineup, //阵形列表
		shared_func<SSetFormationAck>& fnAck //返回回调函数
	) = 0;

	struct SPetsGetAck : public CClientFuncAck
	{
		NRoleInfoDefine::TVecPetDataInfo vecPets; //阵灵信息列表

		SPetsGetAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：取得所有阵灵信息
	virtual bool OnRecv_PetsGet(
		shared_func<SPetsGetAck>& fnAck //返回回调函数
	) = 0;

	struct SPetsActiveAck : public CClientFuncAck
	{
		EFormPetType eResult; //结果

		SPetsActiveAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：激活阵灵
	virtual bool OnRecv_PetsActive(
		UINT16 wPetID, //阵灵ID
		shared_func<SPetsActiveAck>& fnAck //返回回调函数
	) = 0;

	struct SPetsStatusAck : public CClientFuncAck
	{
		EFormPetType eResult; //结果

		SPetsStatusAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：设置阵灵状态
	virtual bool OnRecv_PetsStatus(
		UINT16 wPetID, //阵灵ID
		UINT8 byType, //状态: 1-出战且显示 2-出战隐藏
		shared_func<SPetsStatusAck>& fnAck //返回回调函数
	) = 0;

	struct SPetsUpgradeAck : public CClientFuncAck
	{
		EFormPetType eResult; //结果

		SPetsUpgradeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：阵灵幻化
	virtual bool OnRecv_PetsUpgrade(
		UINT16 wPetID, //阵灵ID
		shared_func<SPetsUpgradeAck>& fnAck //返回回调函数
	) = 0;

	struct SPetsLevelUpAck : public CClientFuncAck
	{
		EFormPetType eResult; //结果

		SPetsLevelUpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：阵灵升级
	virtual bool OnRecv_PetsLevelUp(
		UINT16 wPetID, //阵灵ID
		UINT8 byType, //升级消耗类型 0-朱果 1-蟠桃
		shared_func<SPetsLevelUpAck>& fnAck //返回回调函数
	) = 0;

	struct SQuickPetsLevelUpAck : public CClientFuncAck
	{
		EFormPetType eResult; //结果

		SQuickPetsLevelUpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：阵灵一键升级
	virtual bool OnRecv_QuickPetsLevelUp(
		UINT16 wPetID, //阵灵ID
		shared_func<SQuickPetsLevelUpAck>& fnAck //返回回调函数
	) = 0;

	struct SGetBeastSoulAck : public CClientFuncAck
	{
		EBeastSoulResult eResult; //获取结果
		NRoleInfoDefine::TVecBeastSoulInfo vecBeastSoul; //兽魂信息

		SGetBeastSoulAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取兽魂信息
	virtual bool OnRecv_GetBeastSoul(
		shared_func<SGetBeastSoulAck>& fnAck //返回回调函数
	) = 0;

	struct SUpgradeBeastSoulAck : public CClientFuncAck
	{
		EBeastSoulResult eResult; //获取结果
		NRoleInfoDefine::TVecBeastSoulInfo vecBeastSoul; //兽魂信息
		TVecBeastSoulItem vecItem; //包裹或仓库中道具的列表

		SUpgradeBeastSoulAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：升级兽魂
	virtual bool OnRecv_UpgradeBeastSoul(
		NRoleInfoDefine::EBeastSoulType eType, //兽魂种类
		shared_func<SUpgradeBeastSoulAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 22; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_FormationUp(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetFormation(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_PetsGet(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_PetsActive(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_PetsStatus(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_PetsUpgrade(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_PetsLevelUp(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_QuickPetsLevelUp(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetBeastSoul(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpgradeBeastSoul(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CFormationProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NFormationProt
