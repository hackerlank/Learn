/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    PropInfo.h
//  Purpose:      属性相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "PropInfo.h"

namespace NPropInfo
{

//协议类：属性相关协议
class CPropInfoSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：属性列表通知(改变后通知)
	bool Send_PropListNotify( //发送给当前协议处理的客户端
		UINT64 qwInstID, //变更对象ID
		EPropClass eClass, //变更对象类型
		const TVecPropValue& vecPropValue //属性列表
	);
	bool SendClt_PropListNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwInstID, //变更对象ID
		EPropClass eClass, //变更对象类型
		const TVecPropValue& vecPropValue //属性列表
	);
	std::string& BuildPkg_PropListNotify( //只组包不发送
		UINT64 qwInstID, //变更对象ID
		EPropClass eClass, //变更对象类型
		const TVecPropValue& vecPropValue //属性列表
	);

	//发送：属性列表通知(改变后通知)
	bool Send_PropNotify( //发送给当前协议处理的客户端
		UINT64 qwInstID, //变更对象ID
		EPropClass eClass, //变更对象类型
		const TVecPropValue& vecPropValue, //属性列表
		bool bType //是否飘字
	);
	bool SendClt_PropNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwInstID, //变更对象ID
		EPropClass eClass, //变更对象类型
		const TVecPropValue& vecPropValue, //属性列表
		bool bType //是否飘字
	);
	std::string& BuildPkg_PropNotify( //只组包不发送
		UINT64 qwInstID, //变更对象ID
		EPropClass eClass, //变更对象类型
		const TVecPropValue& vecPropValue, //属性列表
		bool bType //是否飘字
	);

	//发送：扩展属性列表通知(改变后通知)
	bool Send_PropExtListNotify( //发送给当前协议处理的客户端
		UINT64 qwInstID, //变更对象ID
		EPropClass eClass, //变更对象类型
		const TVecPropValExt& vecPropValExt //扩展属性列表
	);
	bool SendClt_PropExtListNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwInstID, //变更对象ID
		EPropClass eClass, //变更对象类型
		const TVecPropValExt& vecPropValExt //扩展属性列表
	);
	std::string& BuildPkg_PropExtListNotify( //只组包不发送
		UINT64 qwInstID, //变更对象ID
		EPropClass eClass, //变更对象类型
		const TVecPropValExt& vecPropValExt //扩展属性列表
	);

	//发送：属性列表通知(改变后通知)
	bool Send_PropQWListNotify( //发送给当前协议处理的客户端
		UINT64 qwInstID, //变更对象ID
		EPropClass eClass, //变更对象类型
		const TVecPropQWValue& vecPropValue //属性列表
	);
	bool SendClt_PropQWListNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwInstID, //变更对象ID
		EPropClass eClass, //变更对象类型
		const TVecPropQWValue& vecPropValue //属性列表
	);
	std::string& BuildPkg_PropQWListNotify( //只组包不发送
		UINT64 qwInstID, //变更对象ID
		EPropClass eClass, //变更对象类型
		const TVecPropQWValue& vecPropValue //属性列表
	);

	//发送：扩展属性列表通知(改变后通知)
	bool Send_PropQWExtListNotify( //发送给当前协议处理的客户端
		UINT64 qwInstID, //变更对象ID
		EPropClass eClass, //变更对象类型
		const TVecPropQWValExt& vecPropValExt //扩展属性列表
	);
	bool SendClt_PropQWExtListNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwInstID, //变更对象ID
		EPropClass eClass, //变更对象类型
		const TVecPropQWValExt& vecPropValExt //扩展属性列表
	);
	std::string& BuildPkg_PropQWExtListNotify( //只组包不发送
		UINT64 qwInstID, //变更对象ID
		EPropClass eClass, //变更对象类型
		const TVecPropQWValExt& vecPropValExt //扩展属性列表
	);

	//发送：Creature的名字改变通知
	bool Send_NameChangeNotify( //发送给当前协议处理的客户端
		UINT64 qwCreatureID, //生物ID
		const std::string& strName //新名字
	);
	bool SendClt_NameChangeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwCreatureID, //生物ID
		const std::string& strName //新名字
	);
	std::string& BuildPkg_NameChangeNotify( //只组包不发送
		UINT64 qwCreatureID, //生物ID
		const std::string& strName //新名字
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SMoneyExchangeAck : public CClientFuncAck
	{
		EExchangeResult eResult; //兑换结果

		SMoneyExchangeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：货币兑换
	virtual bool OnRecv_MoneyExchange(
		EPropType eSrcProp, //源货币
		EPropType eDestProp, //目标货币
		UINT32 dwCount, //数量
		shared_func<SMoneyExchangeAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 17; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_MoneyExchange(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CPropInfoSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NPropInfo
