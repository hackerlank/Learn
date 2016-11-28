/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    EquipTrumpProt.h
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "EquipTrumpProt.h"

namespace NEquipTrumpProt
{

//协议类：道具相关协议
class CEquipTrumpProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：当前玩家角色的装备法宝通知
	bool Send_EquipTrumpNotify( //发送给当前协议处理的客户端
		UINT64 qwOwnerID, //散仙唯一ID
		EEquipTrumpSlotType eSlotType, //装备法宝位类型
		const NItemProt::TVecEquipTrump& vecEquipTrump //当前装备法宝的列表
	);
	bool SendClt_EquipTrumpNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwOwnerID, //散仙唯一ID
		EEquipTrumpSlotType eSlotType, //装备法宝位类型
		const NItemProt::TVecEquipTrump& vecEquipTrump //当前装备法宝的列表
	);
	std::string& BuildPkg_EquipTrumpNotify( //只组包不发送
		UINT64 qwOwnerID, //散仙唯一ID
		EEquipTrumpSlotType eSlotType, //装备法宝位类型
		const NItemProt::TVecEquipTrump& vecEquipTrump //当前装备法宝的列表
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetAllEquipTrumpAck : public CClientFuncAck
	{
		NItemProt::TVecEquipTrump vecEquipTrump; //当前装备法宝的列表

		SGetAllEquipTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获得所有装备法宝
	virtual bool OnRecv_GetAllEquipTrump(
		UINT64 qwOwnerID, //散仙唯一ID（0表示获取所有散仙法宝）
		shared_func<SGetAllEquipTrumpAck>& fnAck //返回回调函数
	) = 0;

	struct SWearAck : public CClientFuncAck
	{
		EEquipTrumpResult eResult; //穿上装备法宝的结果

		SWearAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求穿上装备法宝
	virtual bool OnRecv_Wear(
		UINT64 qwOwnerID, //散仙唯一ID
		UINT64 qwInstID, //装备法宝唯一ID
		shared_func<SWearAck>& fnAck //返回回调函数
	) = 0;

	struct SWearOneKeyAck : public CClientFuncAck
	{
		EEquipTrumpResult eResult; //穿上装备法宝的结果

		SWearOneKeyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求一键穿上装备法宝
	virtual bool OnRecv_WearOneKey(
		UINT64 qwOwnerID, //散仙唯一ID
		shared_func<SWearOneKeyAck>& fnAck //返回回调函数
	) = 0;

	struct STakeOffAck : public CClientFuncAck
	{
		EEquipTrumpResult eResult; //脱下装备法宝的结果

		STakeOffAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求脱下装备法宝
	virtual bool OnRecv_TakeOff(
		UINT64 qwInstID, //装备法宝唯一ID
		INT16 wIndex, //-1：右击脱下；其他：包裹的位置
		shared_func<STakeOffAck>& fnAck //返回回调函数
	) = 0;

	struct SSwapAck : public CClientFuncAck
	{
		EEquipTrumpResult eResult; //换位置的结果

		SSwapAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：交换法宝
	virtual bool OnRecv_Swap(
		UINT64 qwOwnerID, //散仙唯一ID
		UINT64 qwInstID, //装备法宝唯一ID
		INT16 wIndex, //-1：右击脱下；其他：包裹的位置
		shared_func<SSwapAck>& fnAck //返回回调函数
	) = 0;

	struct SMergeEquipTrumpAck : public CClientFuncAck
	{
		EEquipTrumpMergeResult eResult; //结果
		NItemProt::TVecItem vecItem; //新增的道具

		SMergeEquipTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求合成装备法宝
	virtual bool OnRecv_MergeEquipTrump(
		UINT16 wItemID, //制作装备法宝模版ID
		UINT16 wCount, //数量
		shared_func<SMergeEquipTrumpAck>& fnAck //返回回调函数
	) = 0;

	struct SBreakEquipTrumpAck : public CClientFuncAck
	{
		EEquipTrumpBreakResult eResult; //结果
		NItemProt::TVecItemGenInfo vecItem; //分解产生的道具

		SBreakEquipTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求分解装备法宝
	virtual bool OnRecv_BreakEquipTrump(
		const TVecUINT64& vecInstID, //物品唯一ID
		shared_func<SBreakEquipTrumpAck>& fnAck //返回回调函数
	) = 0;

	struct SIntensifyAck : public CClientFuncAck
	{
		bool bSucess; //成功/失败
		EEquipTrumpIntensifyResult eResult; //结果

		SIntensifyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：装备法宝强化
	virtual bool OnRecv_Intensify(
		UINT64 qwInstID, //装备法宝唯一ID
		ETIntensifyType eType, //强化类型
		shared_func<SIntensifyAck>& fnAck //返回回调函数
	) = 0;

	struct SIntensifyOneKeyAck : public CClientFuncAck
	{
		bool bSucess; //成功/失败
		UINT32 dwIntensifyCount; //强化次数（包括成功
		EEquipTrumpIntensifyResult eResult; //结果

		SIntensifyOneKeyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：装备法宝一键强化
	virtual bool OnRecv_IntensifyOneKey(
		UINT64 qwInstID, //装备法宝唯一ID
		ETIntensifyType eType, //强化类型
		shared_func<SIntensifyOneKeyAck>& fnAck //返回回调函数
	) = 0;

	struct SShuffleResultAck : public CClientFuncAck
	{
		EEquipTrumpShuffleResult eResult; //结果

		SShuffleResultAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：装备法宝洗炼
	virtual bool OnRecv_ShuffleResult(
		UINT64 qwInstID, //装备法宝唯一ID
		UINT32 dwLock, //锁定属性（按位锁定 0x110 锁定2，3位）
		shared_func<SShuffleResultAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 30; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetAllEquipTrump(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Wear(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_WearOneKey(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakeOff(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Swap(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_MergeEquipTrump(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BreakEquipTrump(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Intensify(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_IntensifyOneKey(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ShuffleResult(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CEquipTrumpProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NEquipTrumpProt
