/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    VIPProt.h
//  Purpose:      VIP特权相关协议
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

namespace NVIPProt
{

/////////////////////以下为类型定义/////////////////////
//VIP特权操作结果
enum EVIPResult
{
	eVIP_Succeed, //成功
	eVIP_LackMoney, //金钱不够
	eVIP_HasGetAward, //已领取过礼包
	eVIP_Expired, //VIP特权已过期
	eVIP_UnFriend, //对方不是你的好友并且不是你的帮派成员
	eVIP_LevelErr, //VIP特权等级不足
	eVIP_OtherErr //其他错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EVIPResult);
bool EnumStrToVal(const char*, EVIPResult&);
#endif //PROT_USE_XML

//开启VIP特权数据结构
struct SVIPData
{
	UINT32 dwMonthCardEndTime; //月卡结束时间
	UINT32 dwDayPack; //VIP特权每日礼包领取状态
	UINT32 dwLvlAward; //VIP特权等级奖励领取状态

	SVIPData();
	SVIPData(UINT32 dwMonthCardEndTime_, UINT32 dwDayPack_, UINT32 dwLvlAward_);
};

typedef std::vector<SVIPData> TVecVIPData;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SVIPData&);
COutArchive& operator<<(COutArchive&, const SVIPData&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SVIPData&);
bool ToXML(const SVIPData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecVIPData&);
bool VectorToXML(const TVecVIPData&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NVIPProt
