/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    EquipTrumpProt.h
//  Purpose:      道具相关协议
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
#include "ItemProt.h"

namespace NEquipTrumpProt
{

/////////////////////以下为类型定义/////////////////////
//装备法宝操作结果
enum EEquipTrumpResult
{
	eETRSuccess, //成功
	eETRFailed, //失败
	eETRNotExist, //不存在
	eETRInOthers, //在其他人身上
	eETRSlotFull, //槽位已满
	eETRSlotLock, //槽位未开启
	eETRSlotConflict, //法宝冲突
	eETRMax //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EEquipTrumpResult);
bool EnumStrToVal(const char*, EEquipTrumpResult&);
#endif //PROT_USE_XML

//装备法宝强化结果
enum EEquipTrumpIntensifyResult
{
	eETIRSuccess = 0, //装备法宝强化成功
	eETIRFailed, //未知错误
	eETIRCrit, //装备法宝强化成功并暴击
	eETIRMaxErr, //已达最大强化等级
	eETIRSilverErr, //强化时银币不足
	eETIRItemErr, //强化时物品不足
	eETIRCFGErr, //强化配置错误
	eETIRTypeErr, //强化参数错误
	eETIRRandomFailErr //强化失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EEquipTrumpIntensifyResult);
bool EnumStrToVal(const char*, EEquipTrumpIntensifyResult&);
#endif //PROT_USE_XML

//装备法宝合成结果
enum EEquipTrumpMergeResult
{
	eETMRSuccess, //成功
	eETMRFailed, //失败
	eETMRLackOfMaterial, //材料不足
	eETMRLackOfSilver, //银币不足
	eETMRPackFull, //背包已满
	eETMRMax //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EEquipTrumpMergeResult);
bool EnumStrToVal(const char*, EEquipTrumpMergeResult&);
#endif //PROT_USE_XML

//装备法宝分解结果
enum EEquipTrumpBreakResult
{
	eETBRSuccess, //成功
	eETBRFailed, //失败
	eETBRPackFull, //背包已满
	eETBREquiped, //仍在装备中
	eETBRMax //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EEquipTrumpBreakResult);
bool EnumStrToVal(const char*, EEquipTrumpBreakResult&);
#endif //PROT_USE_XML

//装备法宝洗炼结果
enum EEquipTrumpShuffleResult
{
	eETSRSuccess = 0, //装备法宝洗炼成功
	eETSRFailed, //装备法宝洗炼失败
	eETSRLevelErr, //装备法宝洗炼时玩家等级不足
	eETSRSilverErr, //洗炼时银币不足
	eETSRMaterialErr //洗炼时材料不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EEquipTrumpShuffleResult);
bool EnumStrToVal(const char*, EEquipTrumpShuffleResult&);
#endif //PROT_USE_XML

//能装备法宝的道具类型
enum EEquipTrumpType
{
	eETTNone = 0, //无
	eETTInnate, //先天法宝
	eETTPassive, //被动法宝
	eETTHalo, //光环法宝
	eETTTransform, //变身法宝
	eETTEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EEquipTrumpType);
bool EnumStrToVal(const char*, EEquipTrumpType&);
#endif //PROT_USE_XML

//装备法宝位类型
enum EEquipTrumpSlotType
{
	eETSTNone = 0, //无
	eETSTInnate, //先天法宝
	eETSTPassive, //被动
	eETSTHalo, //光环
	eETSTTransform, //变身
	eETSTMax //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EEquipTrumpSlotType);
bool EnumStrToVal(const char*, EEquipTrumpSlotType&);
#endif //PROT_USE_XML

//装备法宝强化类型
enum ETIntensifyType
{
	eETIntensify_None = 0, //无
	eETIntensify_NormalGold, //太乙真金
	eETIntensify_GodGold, //太乙精金
	eETIntensify_MAX //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETIntensifyType);
bool EnumStrToVal(const char*, ETIntensifyType&);
#endif //PROT_USE_XML

//最大洗练属性
struct SMaxShuffleInfo
{
	UINT32 dwType; //洗炼类型
	UINT32 dwValue; //洗炼数值

	SMaxShuffleInfo();
	SMaxShuffleInfo(UINT32 dwType_, UINT32 dwValue_);
};

typedef std::vector<SMaxShuffleInfo> TVecMaxShuffleInfo;

//洗练区间属性
struct SXiLianProb
{
	UINT32 dwMinRate; //洗炼最小概率
	UINT32 dwMaxRate; //洗炼最大概率
	UINT32 dwRateValue; //洗炼权值空间

	SXiLianProb();
	SXiLianProb(UINT32 dwMinRate_, UINT32 dwMaxRate_, UINT32 dwRateValue_);
};

typedef std::vector<SXiLianProb> TVecXiLianProb;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SMaxShuffleInfo&);
COutArchive& operator<<(COutArchive&, const SMaxShuffleInfo&);

CInArchive& operator>>(CInArchive&, SXiLianProb&);
COutArchive& operator<<(COutArchive&, const SXiLianProb&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SMaxShuffleInfo&);
bool ToXML(const SMaxShuffleInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMaxShuffleInfo&);
bool VectorToXML(const TVecMaxShuffleInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SXiLianProb&);
bool ToXML(const SXiLianProb&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecXiLianProb&);
bool VectorToXML(const TVecXiLianProb&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NEquipTrumpProt
