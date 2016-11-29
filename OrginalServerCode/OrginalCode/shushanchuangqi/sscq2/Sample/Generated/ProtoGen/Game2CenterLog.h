/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Game2CenterLog.h
//  Purpose:      GameServer到CenterServer的数据中心log协议
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

namespace NGame2CenterLog
{

/////////////////////以下为类型定义/////////////////////
//操作类型
enum EOpType
{
	eOpTypeGM, //GM操作
	eOpTypeItemChange, //道具获得与使用操作
	eOpTypeMoneyChange, //货币获得与使用操作
	eOpTypeEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EOpType);
bool EnumStrToVal(const char*, EOpType&);
#endif //PROT_USE_XML

//帐号金钱变化信息
struct SUserMoneyChange
{
	NProtoCommon::EMoneyType eMoneyType; //货币类型
	INT32 dwValue; //值
	UINT16 wFromTo; //货币来源or消耗类型(dwValue>0来源 dwValue<0消耗)

	SUserMoneyChange();
	SUserMoneyChange(NProtoCommon::EMoneyType eMoneyType_, INT32 dwValue_, UINT16 wFromTo_);
};

typedef std::vector<SUserMoneyChange> TVecUserMoneyChange;

//帐号道具变化信息
struct SUserItemChange
{
	UINT16 wItemID; //道具ID
	INT32 dwCount; //数量
	float dwPrice; //价格
	UINT16 wFromTo; //道具来源or消耗类型(dwCount>0来源 dwCount<0消耗)

	SUserItemChange();
	SUserItemChange(UINT16 wItemID_, INT32 dwCount_, float dwPrice_, UINT16 wFromTo_);
};

typedef std::vector<SUserItemChange> TVecUserItemChange;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SUserMoneyChange&);
COutArchive& operator<<(COutArchive&, const SUserMoneyChange&);

CInArchive& operator>>(CInArchive&, SUserItemChange&);
COutArchive& operator<<(COutArchive&, const SUserItemChange&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SUserMoneyChange&);
bool ToXML(const SUserMoneyChange&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecUserMoneyChange&);
bool VectorToXML(const TVecUserMoneyChange&, TiXmlElement&);

bool FromXML(TiXmlElement&, SUserItemChange&);
bool ToXML(const SUserItemChange&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecUserItemChange&);
bool VectorToXML(const TVecUserItemChange&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NGame2CenterLog
