/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    MiscProt.h
//  Purpose:      不好归类的小协议
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
#include "ProtoCommon.h"

namespace NMiscProt
{

/////////////////////以下为类型定义/////////////////////
//购买体力错误码
enum EBuyActionRet
{
	eBuyActionRet_Sucess = 0, //成功
	eBuyActionRet_MaxAction, //体力已满
	eBuyActionRet_MoneyLimit, //仙元不足
	eBuyActionRet_CountLimit, //购买次数限制
	eBuyActionRet_VIPCFGError //vip配置出错
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBuyActionRet);
bool EnumStrToVal(const char*, EBuyActionRet&);
#endif //PROT_USE_XML

//操作结果
enum EMiscOptRes
{
	eMiscOptRes_Sucess = 0, //成功
	eMiscOptRes_Error //失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMiscOptRes);
bool EnumStrToVal(const char*, EMiscOptRes&);
#endif //PROT_USE_XML

//抽奖操作结果
enum ELotteryRes
{
	eLotteryRes_Sucess = 0, //成功
	eLotteryRes_PackFul, //背包满
	eLotteryRes_LackMoney, //缺钱
	eLotteryRes_Error //失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ELotteryRes);
bool EnumStrToVal(const char*, ELotteryRes&);
#endif //PROT_USE_XML

//每日冲值领奖奖励
enum EEveryDayReChargeAward
{
	eEveryDayReChargeAward_Sucess, //成功
	eEveryDayReChargeAward_LowMoney, //今日冲值不足
	eEveryDayReChargeAward_HasDone, //今日已经领奖
	eEveryDayReChargeAward_NoAward //今日无奖
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EEveryDayReChargeAward);
bool EnumStrToVal(const char*, EEveryDayReChargeAward&);
#endif //PROT_USE_XML

//刷宝箱信息
struct SGodChestInfo
{
	UINT8 byState; //状态
	UINT8 byRount; //回合数
	UINT32 dwTime; //倒计时数
	UINT32 dwEnd; //活动结束时间

	SGodChestInfo();
	SGodChestInfo(UINT8 byState_, UINT8 byRount_, UINT32 dwTime_, UINT32 dwEnd_);
};

//抽奖信息
struct SLotteryInfo
{
	std::string strName; //玩家
	UINT32 dwLotteryID; //奖励ID(对应配置表)

	SLotteryInfo();
	SLotteryInfo(const std::string& strName_, UINT32 dwLotteryID_);
#ifdef __GNUG__
	SLotteryInfo(const SLotteryInfo& src) = default; //默认拷贝构造函数
	SLotteryInfo& operator=(const SLotteryInfo& rhs) = default; //默认赋值操作符
#endif
	SLotteryInfo(SLotteryInfo&& src); //转移构造函数
	SLotteryInfo& operator=(SLotteryInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SLotteryInfo> TVecLotteryInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SGodChestInfo&);
COutArchive& operator<<(COutArchive&, const SGodChestInfo&);

CInArchive& operator>>(CInArchive&, SLotteryInfo&);
COutArchive& operator<<(COutArchive&, const SLotteryInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SGodChestInfo&);
bool ToXML(const SGodChestInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SLotteryInfo&);
bool ToXML(const SLotteryInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecLotteryInfo&);
bool VectorToXML(const TVecLotteryInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NMiscProt
