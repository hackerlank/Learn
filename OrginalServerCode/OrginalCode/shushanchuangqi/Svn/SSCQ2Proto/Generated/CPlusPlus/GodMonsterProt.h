/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GodMonsterProt.h
//  Purpose:      天元神兽协议
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

namespace NGodMonsterProt
{

/////////////////////以下为类型定义/////////////////////
//操作结果
enum EMonsterResult
{
	EMonsterResult_suc, //操作成功
	EMonsterResult_ful, //背包满
	EMonsterResult_get, //奖励已经领取
	EMonsterResult_not, //无此奖励
	EMonsterResult_lack, //仙石不足
	EMonsterResult_Level, //等级不够
	EMonsterResult_Devote, //贡献度不够
	EMonsterResult_guild, //不在帮派
	EMonsterResult_Num, //数量不足
	EMonsterResult_Err //操作失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMonsterResult);
bool EnumStrToVal(const char*, EMonsterResult&);
#endif //PROT_USE_XML

//神兽阶段
enum EMonsterPeroid
{
	EMonsterPeroid_none, //无
	EMonsterPeroid_1, //神兽元胎
	EMonsterPeroid_2, //神兽幼年期
	EMonsterPeroid_3, //神兽成年期
	EMonsterPeroid_4, //神兽青年期
	EMonsterPeroid_5, //亚圣兽期
	EMonsterPeroid_6, //天元神兽
	EMonsterPeroid_end //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMonsterPeroid);
bool EnumStrToVal(const char*, EMonsterPeroid&);
#endif //PROT_USE_XML

//奖励类型
enum EMonsterPrizeType
{
	EMonsterPrize_Begin, //礼包Begin
	EMonsterPrize_1, //每日成长礼包
	EMonsterPrize_2, //每日初级礼包
	EMonsterPrize_3, //每日中级礼包
	EMonsterPrize_4, //每日高级礼包
	EMonsterPrize_5, //每日终极礼包
	EMonsterPrize_End //End
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMonsterPrizeType);
bool EnumStrToVal(const char*, EMonsterPrizeType&);
#endif //PROT_USE_XML

//排行榜
enum EMonsterRank
{
	EMonsterRank_none, //无
	EMonsterRank_1, //个人榜
	EMonsterRank_2, //帮派榜
	EMonsterRank_end //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMonsterRank);
bool EnumStrToVal(const char*, EMonsterRank&);
#endif //PROT_USE_XML

//排行榜数据
struct SMonsterRankInfo
{
	UINT32 dwRank; //排名
	std::string strName; //名字
	UINT32 dwScore; //积分

	SMonsterRankInfo();
	SMonsterRankInfo(UINT32 dwRank_, const std::string& strName_, UINT32 dwScore_);
#ifdef __GNUG__
	SMonsterRankInfo(const SMonsterRankInfo& src) = default; //默认拷贝构造函数
	SMonsterRankInfo& operator=(const SMonsterRankInfo& rhs) = default; //默认赋值操作符
#endif
	SMonsterRankInfo(SMonsterRankInfo&& src); //转移构造函数
	SMonsterRankInfo& operator=(SMonsterRankInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SMonsterRankInfo> TVecMonsterRankInfo;

//排行榜
struct SMonsterRank
{
	EMonsterRank eRank; //排名
	TVecMonsterRankInfo vecRankInfo; //数据

	SMonsterRank();
	SMonsterRank(EMonsterRank eRank_, const TVecMonsterRankInfo& vecRankInfo_);
#ifdef __GNUG__
	SMonsterRank(const SMonsterRank& src) = default; //默认拷贝构造函数
	SMonsterRank& operator=(const SMonsterRank& rhs) = default; //默认赋值操作符
#endif
	SMonsterRank(SMonsterRank&& src); //转移构造函数
	SMonsterRank& operator=(SMonsterRank&& rhs); //转移赋值操作符
};

typedef std::vector<SMonsterRank> TVecMonsterRank;

//排行榜
struct SMonsterPrize
{
	EMonsterPrizeType eType; //奖励类型
	UINT8 byType; //0表示条件未达到，1表示可以领取，2表示已经领取

	SMonsterPrize();
	SMonsterPrize(EMonsterPrizeType eType_, UINT8 byType_);
};

typedef std::vector<SMonsterPrize> TVecMonsterPrize;

//帮派成员贡献
struct SGuildUserDevote
{
	UINT64 qwRoleID; //ID
	std::string strName; //名字
	std::string strLevel; //职务
	UINT32 dwScore; //积分

	SGuildUserDevote();
	SGuildUserDevote(UINT64 qwRoleID_, const std::string& strName_, const std::string& strLevel_, UINT32 dwScore_);
#ifdef __GNUG__
	SGuildUserDevote(const SGuildUserDevote& src) = default; //默认拷贝构造函数
	SGuildUserDevote& operator=(const SGuildUserDevote& rhs) = default; //默认赋值操作符
#endif
	SGuildUserDevote(SGuildUserDevote&& src); //转移构造函数
	SGuildUserDevote& operator=(SGuildUserDevote&& rhs); //转移赋值操作符
};

typedef std::vector<SGuildUserDevote> TVecGuildUserDevote;

//限购礼包
struct SLimitPrize
{
	UINT16 wPrizeID; //礼品ID
	UINT16 wCurNum; //已经购买数量
	UINT16 wMaxNum; //最大值

	SLimitPrize();
	SLimitPrize(UINT16 wPrizeID_, UINT16 wCurNum_, UINT16 wMaxNum_);
};

typedef std::vector<SLimitPrize> TVecLimitPrize;

//发送给客户端的数据
struct SyncInfoToClient
{
	EMonsterPeroid ePeroid; //神兽阶段
	UINT32 dwPersonScore; //个人总积分
	UINT32 dwGuildScore; //帮派总积分
	UINT32 dwPersonDevote; //个人贡献值
	UINT32 dwPersonRank; //个人总排名
	UINT32 dwGuildRank; //帮派总排名
	UINT32 dwFruit; //朱果数量
	TVecMonsterPrize vecPrize; //奖励数据
	TVecMonsterRank vecRank; //排行榜数据
	TVecGuildUserDevote vecUser; //成员贡献数据
	TVecLimitPrize vecLimitPrize; //玩家限购礼包数据

	SyncInfoToClient();
#ifdef __GNUG__
	SyncInfoToClient(const SyncInfoToClient& src) = default; //默认拷贝构造函数
	SyncInfoToClient& operator=(const SyncInfoToClient& rhs) = default; //默认赋值操作符
#endif
	SyncInfoToClient(SyncInfoToClient&& src); //转移构造函数
	SyncInfoToClient& operator=(SyncInfoToClient&& rhs); //转移赋值操作符
};

//DB Operator
struct SGuildUser2DB
{
	UINT64 qwRoleID; //名字
	UINT64 qwGuildID; //职务
	UINT32 dwFruit; //朱果数量
	UINT32 dwScore; //积分
	UINT32 dwTotalScore; //总积分

	SGuildUser2DB();
	SGuildUser2DB(UINT64 qwRoleID_, UINT64 qwGuildID_, UINT32 dwFruit_, UINT32 dwScore_, UINT32 dwTotalScore_);
};

typedef std::vector<SGuildUser2DB> TVecGuildUser2DB;

//DB Operator
struct SLimitPrize2DB
{
	UINT64 qwRoleID; //玩家ID
	UINT16 wPrizeID; //礼品ID
	UINT16 wNum; //购买数量

	SLimitPrize2DB();
	SLimitPrize2DB(UINT64 qwRoleID_, UINT16 wPrizeID_, UINT16 wNum_);
};

typedef std::vector<SLimitPrize2DB> TVecLimitPrize2DB;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SMonsterRankInfo&);
COutArchive& operator<<(COutArchive&, const SMonsterRankInfo&);

CInArchive& operator>>(CInArchive&, SMonsterRank&);
COutArchive& operator<<(COutArchive&, const SMonsterRank&);

CInArchive& operator>>(CInArchive&, SMonsterPrize&);
COutArchive& operator<<(COutArchive&, const SMonsterPrize&);

CInArchive& operator>>(CInArchive&, SGuildUserDevote&);
COutArchive& operator<<(COutArchive&, const SGuildUserDevote&);

CInArchive& operator>>(CInArchive&, SLimitPrize&);
COutArchive& operator<<(COutArchive&, const SLimitPrize&);

CInArchive& operator>>(CInArchive&, SyncInfoToClient&);
COutArchive& operator<<(COutArchive&, const SyncInfoToClient&);

CInArchive& operator>>(CInArchive&, SGuildUser2DB&);
COutArchive& operator<<(COutArchive&, const SGuildUser2DB&);

CInArchive& operator>>(CInArchive&, SLimitPrize2DB&);
COutArchive& operator<<(COutArchive&, const SLimitPrize2DB&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SMonsterRankInfo&);
bool ToXML(const SMonsterRankInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMonsterRankInfo&);
bool VectorToXML(const TVecMonsterRankInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SMonsterRank&);
bool ToXML(const SMonsterRank&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMonsterRank&);
bool VectorToXML(const TVecMonsterRank&, TiXmlElement&);

bool FromXML(TiXmlElement&, SMonsterPrize&);
bool ToXML(const SMonsterPrize&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMonsterPrize&);
bool VectorToXML(const TVecMonsterPrize&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildUserDevote&);
bool ToXML(const SGuildUserDevote&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildUserDevote&);
bool VectorToXML(const TVecGuildUserDevote&, TiXmlElement&);

bool FromXML(TiXmlElement&, SLimitPrize&);
bool ToXML(const SLimitPrize&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecLimitPrize&);
bool VectorToXML(const TVecLimitPrize&, TiXmlElement&);

bool FromXML(TiXmlElement&, SyncInfoToClient&);
bool ToXML(const SyncInfoToClient&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildUser2DB&);
bool ToXML(const SGuildUser2DB&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildUser2DB&);
bool VectorToXML(const TVecGuildUser2DB&, TiXmlElement&);

bool FromXML(TiXmlElement&, SLimitPrize2DB&);
bool ToXML(const SLimitPrize2DB&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecLimitPrize2DB&);
bool VectorToXML(const TVecLimitPrize2DB&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NGodMonsterProt
