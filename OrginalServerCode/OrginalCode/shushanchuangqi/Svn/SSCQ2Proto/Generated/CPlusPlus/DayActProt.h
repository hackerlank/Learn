/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    DayActProt.h
//  Purpose:      活动
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

namespace NDayActProt
{

/////////////////////以下为类型定义/////////////////////
//活动ID（保留暂时不用）
enum EActID
{
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EActID);
bool EnumStrToVal(const char*, EActID&);
#endif //PROT_USE_XML

//活动类型
enum EActType
{
	eActTypeInvalid = 0,
	eActTypeWorldBoss = 1, //boss活动
	eActTypeLangHuanBless = 2, //LangHuanBless活动
	eActTypeGuildBattle = 3, //帮派战活动
	eActTypeShushanBattle = 4, //蜀山论剑活动
	eActTypeEnergy = 5, //剑气充盈活动
	eActTypeTeamReward = 6, //组队副本奖励活动
	eActTypeAnswer = 7, //答题活动
	eActTypeLingShan = 8, //秘境寻宝
	eActTypeNewGuildBattle = 9, //新帮派战
	eActTypeChest = 10, //刷宝箱
	eActTypeShipReward = 11, //元江金船活动
	eActTypeEnd
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EActType);
bool EnumStrToVal(const char*, EActType&);
#endif //PROT_USE_XML

//活动状态
enum EDayActivityStatus
{
	eDayActivityStatusInit = 0, //活动初始化状态
	eDayActivityStatusAlarm, //活动警戒状态
	eDayActivityStatusReady, //活动准备状态
	eDayActivityStatusProcess, //活动进行状态
	eDayActivityStatusEnd //活动结束状态
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDayActivityStatus);
bool EnumStrToVal(const char*, EDayActivityStatus&);
#endif //PROT_USE_XML

//活动信息表
struct SActInfo
{
	UINT32 dwActType; //活动id
	UINT32 dwActStatus; //活动状态

	SActInfo();
	SActInfo(UINT32 dwActType_, UINT32 dwActStatus_);
};

typedef std::vector<SActInfo> TVecActInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SActInfo&);
COutArchive& operator<<(COutArchive&, const SActInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SActInfo&);
bool ToXML(const SActInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecActInfo&);
bool VectorToXML(const TVecActInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NDayActProt
