/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ExchangeShopProt.h
//  Purpose:      兑换商店
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include <vector>
#include <string>
#include <memory>
#include "ServerDefine.h"
#include "Archive.h"
#ifdef PROT_USE_XML
#include "tinyxml.h"
#endif

namespace NExchangeShopProt
{

/////////////////////以下为类型定义/////////////////////
//兑换商店错误码
enum EExchangeShop
{
	eExchangeShop_Sucess, //成功
	eExchangeShop_CfgLimit, //没有该兑换商品
	eExchangeShop_MoneyLimit, //钱不够
	eExchangeShop_CondLimit, //购买条件不满足
	eExchangeShop_CountLimit, //购买数量限制
	eExchangeShop_ErrorItemID, //物品配置找不到
	eExchangeShop_ErrorPack //背包满无法添加物品
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EExchangeShop);
bool EnumStrToVal(const char*, EExchangeShop&);
#endif //PROT_USE_XML

//已兑换信息列表
struct ExchangeInfo
{
	UINT64 qwRoleID; //角色ID
	UINT32 dwExchangeID; //兑换ID
	UINT32 dwCount; //已兑换次数
	UINT32 dwFinishTime; //兑换时间

	ExchangeInfo();
	ExchangeInfo(UINT64 qwRoleID_, UINT32 dwExchangeID_, UINT32 dwCount_, UINT32 dwFinishTime_);
};

typedef std::vector<ExchangeInfo> TVecExchangeInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, ExchangeInfo&);
COutArchive& operator<<(COutArchive&, const ExchangeInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, ExchangeInfo&);
bool ToXML(const ExchangeInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecExchangeInfo&);
bool VectorToXML(const TVecExchangeInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NExchangeShopProt
