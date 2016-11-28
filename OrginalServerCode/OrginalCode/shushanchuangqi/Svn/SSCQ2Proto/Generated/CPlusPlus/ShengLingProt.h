/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ShengLingProt.h
//  Purpose:      圣陵协议
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

namespace NShengLingProt
{

/////////////////////以下为类型定义/////////////////////
//操作结果
enum EShengLingResult
{
	EShengLingResultSuc, //操作成功
	EShengLingResultPackFul, //背包空间不足
	EShengLingResultPrizeTaked, //奖励被领取
	EShengLingResultFailed, //战斗失败
	EShengLingResultGoldLack, //仙石不足
	EShengLingResultEnterLack, //次数不足
	EShengLingResultLifeLack, //生命不足
	EShengLingResultControlDiceLack, //遥控骰子不足
	EShengLingResultTurnDiceLack, //转向骰子不足
	EShengLingResultScoreLack, //积分不够
	EShengLingResultStepLack, //积分不够
	EShengLingResultNotFinish, //格子未完成
	EShengLingResultTypeError, //格子类型不对
	EShengLingResultError //操作失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EShengLingResult);
bool EnumStrToVal(const char*, EShengLingResult&);
#endif //PROT_USE_XML

//卡片类型
enum ECardType
{
	ECardType_ControlDice, //遥控骰子
	ECardType_TurnDice //转向卡片
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECardType);
bool EnumStrToVal(const char*, ECardType&);
#endif //PROT_USE_XML

//圣陵格子类型
enum EGridType
{
	EGridType_None, //无
	EGridType_Empty, //空格子
	EGridType_Normal, //普通怪物格子
	EGridType_Elite, //精英怪物格子
	EGridType_Boss, //Boss怪物格子
	EGridType_Big, //小宝箱格子
	EGridType_Mid, //中宝箱格子
	EGridType_Small, //大宝箱格子
	EGridType_Born, //出生格子
	EGridType_Random, //随机格子
	EGridType_Motu, //三消陷阱格子
	EGridType_Pintu, //拼图陷阱格子
	EGridType_Zadan, //砸蛋陷阱格子
	EGridType_Go, //传送格子
	EGridType_End //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGridType);
bool EnumStrToVal(const char*, EGridType&);
#endif //PROT_USE_XML

//购买类型
enum EBuyType
{
	EBuyType_ControlDice, //购买遥控骰子
	EBuyType_TurnCard, //购买转向卡片
	EBuyType_Life, //购买生命
	EBuyType_Enter, //购买进入次数
	EBuyType_Step //购买三消步数
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBuyType);
bool EnumStrToVal(const char*, EBuyType&);
#endif //PROT_USE_XML

//格子数据
struct SGrid
{
	UINT8 byIndex; //格子ID
	UINT8 byLevel; //格子所在层
	EGridType eGridType; //格子类型
	UINT16 wNoteID; //格子记录数据
	bool bFinished; //是否完成
	bool bRandom; //是否随机格子

	SGrid();
	SGrid(UINT8 byIndex_, UINT8 byLevel_, EGridType eGridType_, UINT16 wNoteID_, bool bFinished_, 
		bool bRandom_);
};

typedef std::vector<SGrid> TVecGrid;

//卡片信息
struct SCard
{
	ECardType eCardType; //卡片类型
	UINT8 byBuy; //玩家购买次数
	UINT8 byUse; //当日使用次数
	UINT8 byBuyForToday; //当日购买次数

	SCard();
	SCard(ECardType eCardType_, UINT8 byBuy_, UINT8 byUse_, UINT8 byBuyForToday_);
};

typedef std::vector<SCard> TVecCard;

//玩家信息
struct SPlayerInfo
{
	UINT64 qwRoleID; //玩家ID
	UINT8 byCurLevel; //玩家当前所在层
	UINT8 byCurIndex; //玩家当前所在层格子ID
	UINT8 byPreLevel; //玩家上一次所在层
	UINT8 byPreIndex; //玩家上一次所在层格子ID
	UINT8 byBuy; //玩家购买生命数
	UINT8 byUse; //玩家当前使用生命数
	UINT8 byNext; //是否进入下一层
	TVecGrid vecGrid; //格子数据

	SPlayerInfo();
	SPlayerInfo(UINT64 qwRoleID_, UINT8 byCurLevel_, UINT8 byCurIndex_, UINT8 byPreLevel_, UINT8 byPreIndex_, 
		UINT8 byBuy_, UINT8 byUse_, UINT8 byNext_, const TVecGrid& vecGrid_);
#ifdef __GNUG__
	SPlayerInfo(const SPlayerInfo& src) = default; //默认拷贝构造函数
	SPlayerInfo& operator=(const SPlayerInfo& rhs) = default; //默认赋值操作符
#endif
	SPlayerInfo(SPlayerInfo&& src); //转移构造函数
	SPlayerInfo& operator=(SPlayerInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SPlayerInfo> TVecPlayerInfo;

//玩家进入信息
struct SShengLingInfo
{
	UINT64 qwRoleID; //玩家ID
	UINT16 wPassword; //初始密码
	UINT8 byDir; //玩家在棋盘中的方向（0表示反向，1表示正向）
	UINT8 byLevel; //玩家当前所在层
	UINT8 byIndex; //玩家当前所在层格子ID
	UINT8 byBuyLife; //玩家购买生命数
	UINT8 byUseLife; //玩家今日使用生命数
	UINT8 byStep; //玩家在“三消”中剩余步数
	UINT16 byScore; //玩家在“三消”中累计积分
	UINT8 byBit; //玩家在“三消”中奖励领取状态，bit位表示从低到高
	UINT8 byBuyLifeToday; //玩家今天购买生命数
	UINT8 byFirst; //玩家是否第一次进入圣陵
	TVecGrid vecGrid; //格子数据
	TVecCard vecCard; //卡片数据
	NItemProt::TVecItemGenInfo vecItem; //获得的奖励数据

	SShengLingInfo();
#ifdef __GNUG__
	SShengLingInfo(const SShengLingInfo& src) = default; //默认拷贝构造函数
	SShengLingInfo& operator=(const SShengLingInfo& rhs) = default; //默认赋值操作符
#endif
	SShengLingInfo(SShengLingInfo&& src); //转移构造函数
	SShengLingInfo& operator=(SShengLingInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SShengLingInfo> TVecShengLingInfo;

//数据库信息
struct SShengLingInfo2DB
{
	UINT64 qwRoleID; //玩家ID
	UINT8 byLevel; //玩家所在层
	UINT8 byIndex; //格子ID
	UINT8 byType; //格子类型
	UINT16 wNoteID; //格子中记录ID
	UINT8 byRandom; //是否随机格子
	UINT8 byFinish; //是否完成

	SShengLingInfo2DB();
	SShengLingInfo2DB(UINT64 qwRoleID_, UINT8 byLevel_, UINT8 byIndex_, UINT8 byType_, UINT16 wNoteID_, 
		UINT8 byRandom_, UINT8 byFinish_);
};

typedef std::vector<SShengLingInfo2DB> TVecShengLingInfo2DB;

//数据库奖励信息
struct SShengLingPrize2DB
{
	UINT64 qwRoleID; //玩家ID
	UINT16 wItemID; //物品
	UINT16 wNum; //数量

	SShengLingPrize2DB();
	SShengLingPrize2DB(UINT64 qwRoleID_, UINT16 wItemID_, UINT16 wNum_);
};

typedef std::vector<SShengLingPrize2DB> TVecShengLingPrize2DB;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SGrid&);
COutArchive& operator<<(COutArchive&, const SGrid&);

CInArchive& operator>>(CInArchive&, SCard&);
COutArchive& operator<<(COutArchive&, const SCard&);

CInArchive& operator>>(CInArchive&, SPlayerInfo&);
COutArchive& operator<<(COutArchive&, const SPlayerInfo&);

CInArchive& operator>>(CInArchive&, SShengLingInfo&);
COutArchive& operator<<(COutArchive&, const SShengLingInfo&);

CInArchive& operator>>(CInArchive&, SShengLingInfo2DB&);
COutArchive& operator<<(COutArchive&, const SShengLingInfo2DB&);

CInArchive& operator>>(CInArchive&, SShengLingPrize2DB&);
COutArchive& operator<<(COutArchive&, const SShengLingPrize2DB&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SGrid&);
bool ToXML(const SGrid&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGrid&);
bool VectorToXML(const TVecGrid&, TiXmlElement&);

bool FromXML(TiXmlElement&, SCard&);
bool ToXML(const SCard&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecCard&);
bool VectorToXML(const TVecCard&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPlayerInfo&);
bool ToXML(const SPlayerInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerInfo&);
bool VectorToXML(const TVecPlayerInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SShengLingInfo&);
bool ToXML(const SShengLingInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecShengLingInfo&);
bool VectorToXML(const TVecShengLingInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SShengLingInfo2DB&);
bool ToXML(const SShengLingInfo2DB&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecShengLingInfo2DB&);
bool VectorToXML(const TVecShengLingInfo2DB&, TiXmlElement&);

bool FromXML(TiXmlElement&, SShengLingPrize2DB&);
bool ToXML(const SShengLingPrize2DB&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecShengLingPrize2DB&);
bool VectorToXML(const TVecShengLingPrize2DB&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NShengLingProt
