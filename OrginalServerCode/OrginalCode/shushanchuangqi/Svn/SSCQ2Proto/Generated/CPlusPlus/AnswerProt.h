/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    AnswerProt.h
//  Purpose:      答题协议
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

namespace NAnswerProt
{

/////////////////////以下为类型定义/////////////////////
//答题操作结果
enum EAnswerResult
{
	EAnswerResult_Suc, //操作成功
	EAnswerResult_Lack, //技能使用完
	EAnswerResult_No, //技能无法使用
	EAnswerResult_Err //操作失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EAnswerResult);
bool EnumStrToVal(const char*, EAnswerResult&);
#endif //PROT_USE_XML

//答题技能
enum EAnswerSkill
{
	EAnswerSkill_NONE, //无技能
	EAnswerSkill_1, //仙人之路
	EAnswerSkill_2, //天官赐福
	EAnswerSkill_3, //驱散迷雾
	EAnswerSkill_END //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EAnswerSkill);
bool EnumStrToVal(const char*, EAnswerSkill&);
#endif //PROT_USE_XML

//答题时间控制
struct SAnswerTime
{
	UINT32 dwReadTime; //玩家阅读时间
	UINT32 dwAnswerTime; //玩家答题时间
	UINT32 dwResultTime; //玩家显示结果时间
	UINT32 dwEndTime; //玩家答题结束时间

	SAnswerTime();
	SAnswerTime(UINT32 dwReadTime_, UINT32 dwAnswerTime_, UINT32 dwResultTime_, UINT32 dwEndTime_);
};

//答题技能信息
struct SAnswerSkill
{
	EAnswerSkill eSkillType; //技能ID
	UINT8 byRemain; //剩余次数

	SAnswerSkill();
	SAnswerSkill(EAnswerSkill eSkillType_, UINT8 byRemain_);
};

typedef std::vector<SAnswerSkill> TVecAnswerSkill;

//答题题目信息
struct SAnswerTopic
{
	UINT8 byIndex; //编号
	UINT32 dwTopicID; //题目ID
	UINT8 byAnswer1; //答案1
	UINT8 byAnswer2; //答案2
	UINT8 byAnswer3; //答案3
	UINT8 byAnswer4; //答案4
	SAnswerTime sTimeInfo; //题目时间
	UINT32 dwRemain; //剩余题目数

	SAnswerTopic();
	SAnswerTopic(UINT8 byIndex_, UINT32 dwTopicID_, UINT8 byAnswer1_, UINT8 byAnswer2_, UINT8 byAnswer3_, 
		UINT8 byAnswer4_, const SAnswerTime& sTimeInfo_, UINT32 dwRemain_);
};

//玩家信息
struct SAnswerPlayer
{
	UINT64 qwRoleID; //玩家ID
	bool bRight; //本次答题是否正确
	UINT32 dwThisScore; //本题玩家获得积分
	UINT32 dwScore; //玩家积分
	UINT32 dwRank; //玩家排名
	UINT32 dwRight; //玩家答对题目数
	UINT32 dwUntilFail; //连续答对题目数
	TVecAnswerSkill vecSkillInfo; //技能信息

	SAnswerPlayer();
	SAnswerPlayer(UINT64 qwRoleID_, bool bRight_, UINT32 dwThisScore_, UINT32 dwScore_, UINT32 dwRank_, 
		UINT32 dwRight_, UINT32 dwUntilFail_, const TVecAnswerSkill& vecSkillInfo_);
#ifdef __GNUG__
	SAnswerPlayer(const SAnswerPlayer& src) = default; //默认拷贝构造函数
	SAnswerPlayer& operator=(const SAnswerPlayer& rhs) = default; //默认赋值操作符
#endif
	SAnswerPlayer(SAnswerPlayer&& src); //转移构造函数
	SAnswerPlayer& operator=(SAnswerPlayer&& rhs); //转移赋值操作符
};

//排名信息
struct SAnswerRank
{
	UINT32 dwRank; //玩家排名
	std::string strName; //玩家名字
	UINT32 dwScore; //玩家积分

	SAnswerRank();
	SAnswerRank(UINT32 dwRank_, const std::string& strName_, UINT32 dwScore_);
#ifdef __GNUG__
	SAnswerRank(const SAnswerRank& src) = default; //默认拷贝构造函数
	SAnswerRank& operator=(const SAnswerRank& rhs) = default; //默认赋值操作符
#endif
	SAnswerRank(SAnswerRank&& src); //转移构造函数
	SAnswerRank& operator=(SAnswerRank&& rhs); //转移赋值操作符
};

typedef std::vector<SAnswerRank> TVecAnswerRank;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SAnswerTime&);
COutArchive& operator<<(COutArchive&, const SAnswerTime&);

CInArchive& operator>>(CInArchive&, SAnswerSkill&);
COutArchive& operator<<(COutArchive&, const SAnswerSkill&);

CInArchive& operator>>(CInArchive&, SAnswerTopic&);
COutArchive& operator<<(COutArchive&, const SAnswerTopic&);

CInArchive& operator>>(CInArchive&, SAnswerPlayer&);
COutArchive& operator<<(COutArchive&, const SAnswerPlayer&);

CInArchive& operator>>(CInArchive&, SAnswerRank&);
COutArchive& operator<<(COutArchive&, const SAnswerRank&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SAnswerTime&);
bool ToXML(const SAnswerTime&, TiXmlElement&);

bool FromXML(TiXmlElement&, SAnswerSkill&);
bool ToXML(const SAnswerSkill&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecAnswerSkill&);
bool VectorToXML(const TVecAnswerSkill&, TiXmlElement&);

bool FromXML(TiXmlElement&, SAnswerTopic&);
bool ToXML(const SAnswerTopic&, TiXmlElement&);

bool FromXML(TiXmlElement&, SAnswerPlayer&);
bool ToXML(const SAnswerPlayer&, TiXmlElement&);

bool FromXML(TiXmlElement&, SAnswerRank&);
bool ToXML(const SAnswerRank&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecAnswerRank&);
bool VectorToXML(const TVecAnswerRank&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NAnswerProt
