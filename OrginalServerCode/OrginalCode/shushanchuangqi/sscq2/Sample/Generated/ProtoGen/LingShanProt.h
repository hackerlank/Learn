/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    LingShanProt.h
//  Purpose:      灵山（改名秘境）寻宝
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

namespace NLingShanProt
{

/////////////////////以下为类型定义/////////////////////
//灵山操作结果
enum ELingShanOP
{
	eLingShanOP_Sucess = 0, //成功
	eLingShanOP_Fail = 1, //失败
	eLingShanOP_Cd = 2, //cd
	eLingShanOP_ErrorPath = 3, //目标点错误,没有路径
	eLingShanOP_NoMove = 4, //目前状态无法移动
	eLingShanOP_NoOpen = 5, //活动未开始
	eLingShanOP_NoReg, //未报名
	eLingShanOP_ErrorRoomId, //错误的房间
	eLingShanOP_MoveCd, //移动cd限制
	eLingShanOP_MapCFG, //获取地图配置错误
	eLingShanOP_NotInRoom, //不在比赛地图
	eLingShanOP_ErrorModelID, //错误的模型ｉｄ
	eLingShanOP_ErrorCondID, //开启条件不满足
	eLingShanOP_ActEnded, //活动已结束
	eLingShanOP_ChatCD, //聊天ｃｄ
	eLingShanOP_End
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ELingShanOP);
bool EnumStrToVal(const char*, ELingShanOP&);
#endif //PROT_USE_XML

//玩家状态
enum ELingShanStatus
{
	eLingShanStatus_Init = 0, //未报名状态
	eLingShanStatus_Wait, //排队状态
	eLingShanStatus_Move, //可移动状态
	eLingShanStatus_PlayMovie, //播放动画状态
	eLingShanStatus_End //活动结束状态
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ELingShanStatus);
bool EnumStrToVal(const char*, ELingShanStatus&);
#endif //PROT_USE_XML

//地图格子上单元类型（暂时不用）
enum ELingShanObjType
{
	eLingShanObjType_Invalid = 0, //无效类型
	eLingShanObjType_Player, //玩家
	eLingShanObjType_Box, //物品(宝箱)
	eLingShanObjType_Monster, //怪物
	eObjType_End //活动结束状态
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ELingShanObjType);
bool EnumStrToVal(const char*, ELingShanObjType&);
#endif //PROT_USE_XML

//玩家获取奖励类型
enum ELingShanPrizeType
{
	eLingShanPrizeType_Invalid = 0, //无效类型
	eLingShanPrizeType_PickNormalBox, //拣普通宝箱
	eLingShanPrizeType_PickGodBox, //拣大宝箱
	eLingShanPrizeType_MoveByGodBox, //带有大宝箱
	eLingShanPrizeType_Win, //击败玩家
	eLingShanPrizeType_Fail, //被击败
	eLingShanPrizeType_End
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ELingShanPrizeType);
bool EnumStrToVal(const char*, ELingShanPrizeType&);
#endif //PROT_USE_XML

//碰撞类型
enum ECollideType
{
	eCollideType_Invalid = 0, //无效数据
	eCollideType_Path = 1, //路径碰撞
	eCollideType_Grid //格子碰撞
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECollideType);
bool EnumStrToVal(const char*, ECollideType&);
#endif //PROT_USE_XML

//玩家获取奖励记录
struct STakePrizeLog
{
	ELingShanPrizeType eType; //奖励类型
	UINT16 wTakeBoxCount; //获得宝箱数量
	std::string strFailName; //敌对玩家
	UINT64 qwReportID; //战报id
	float fHPRate; //最终血量
	UINT32 dwSuiYuan; //增加的随缘值
	ECollideType eCollideType; //碰撞类型

	STakePrizeLog();
	STakePrizeLog(ELingShanPrizeType eType_, UINT16 wTakeBoxCount_, const std::string& strFailName_, UINT64 qwReportID_, float fHPRate_, 
		UINT32 dwSuiYuan_, ECollideType eCollideType_);
#ifdef __GNUG__
	STakePrizeLog(const STakePrizeLog& src) = default; //默认拷贝构造函数
	STakePrizeLog& operator=(const STakePrizeLog& rhs) = default; //默认赋值操作符
#endif
	STakePrizeLog(STakePrizeLog&& src); //转移构造函数
	STakePrizeLog& operator=(STakePrizeLog&& rhs); //转移赋值操作符
};

typedef std::vector<STakePrizeLog> TVecTakePrizeLog;

//地图箱子信息
struct SBoxInfo
{
	UINT16 wPos; //当前所在地图位置
	UINT16 dwModelID; //物品id

	SBoxInfo();
	SBoxInfo(UINT16 wPos_, UINT16 dwModelID_);
};

typedef std::vector<SBoxInfo> TVecBoxInfo;

//比赛的玩家信息
struct SRoomPlayInfo
{
	UINT64 qwRoleID; //玩家id
	UINT32 dwModelID; //模型id
	UINT16 dwKillCnt; //击杀人数
	bool bGodBox; //是否带有大宝箱
	UINT16 wPos; //当前所在地图位置

	SRoomPlayInfo();
	SRoomPlayInfo(UINT64 qwRoleID_, UINT32 dwModelID_, UINT16 dwKillCnt_, bool bGodBox_, UINT16 wPos_);
};

typedef std::vector<SRoomPlayInfo> TVecRoomPlayInfo;

//地图的怪物信息
struct SRoomMonsterInfo
{
	UINT32 dwMonsterID; //怪物组id
	UINT16 dwKillCnt; //击杀人数
	UINT16 wPos; //当前所在地图位置

	SRoomMonsterInfo();
	SRoomMonsterInfo(UINT32 dwMonsterID_, UINT16 dwKillCnt_, UINT16 wPos_);
};

typedef std::vector<SRoomMonsterInfo> TVecRoomMonsterInfo;

//玩家移动信息
struct SPlayerMoveInfo
{
	UINT64 qwRoleID; //玩家id
	UINT16 wSrcPos; //当前位置
	UINT16 wDstPos; //目标位置

	SPlayerMoveInfo();
	SPlayerMoveInfo(UINT64 qwRoleID_, UINT16 wSrcPos_, UINT16 wDstPos_);
};

typedef std::vector<SPlayerMoveInfo> TVecPlayerMoveInfo;

//玩家路径碰撞信息
struct SPathCollideInfo
{
	UINT16 wMinPos; //小编号位置
	UINT16 wMaxtPos; //大编号位置
	UINT64 qwWinPlayer; //胜利玩家
	UINT32 dwWinKillCnt; //胜利击杀数目
	UINT64 qwFailPlayer; //失败玩家

	SPathCollideInfo();
	SPathCollideInfo(UINT16 wMinPos_, UINT16 wMaxtPos_, UINT64 qwWinPlayer_, UINT32 dwWinKillCnt_, UINT64 qwFailPlayer_);
};

typedef std::vector<SPathCollideInfo> TVecPathCollideInfo;

//玩家格子碰撞信息
struct SGridCollideInfo
{
	UINT16 wPos; //碰撞位置
	UINT64 qwWinPlayer; //胜利玩家
	UINT32 dwWinKillCnt; //击杀数目
	TVecUINT64 vecFailPlayer; //失败玩家列表

	SGridCollideInfo();
	SGridCollideInfo(UINT16 wPos_, UINT64 qwWinPlayer_, UINT32 dwWinKillCnt_, const TVecUINT64& vecFailPlayer_);
};

typedef std::vector<SGridCollideInfo> TVecGridCollideInfo;

//玩家战斗信息（目前不需要战斗日志)
struct SPlayerFighterLog
{
	UINT64 qwEnemy; //战斗玩家
	UINT64 qwReportID; //战斗日志
	bool bWin; //是否胜利

	SPlayerFighterLog();
	SPlayerFighterLog(UINT64 qwEnemy_, UINT64 qwReportID_, bool bWin_);
};

typedef std::vector<SPlayerFighterLog> TVecPlayerFighterLog;

//房间信息
struct SRoomInfo
{
	UINT16 wRoomID; //房间编号
	UINT16 wPlayerCnt; //房间人数

	SRoomInfo();
	SRoomInfo(UINT16 wRoomID_, UINT16 wPlayerCnt_);
};

typedef std::vector<SRoomInfo> TVecRoomInfo;

//动画播放信息
struct SPlayMovieInfo
{
	TVecPlayerMoveInfo vecPlayerMoveInfo; //玩家移动路径
	TVecPathCollideInfo vecPathCollideInfo; //路径碰撞
	TVecGridCollideInfo vecGridCollideInfo; //格子碰撞
	TVecRoomPlayInfo vecRoomPlayInfo; //玩家信息

	SPlayMovieInfo();
	SPlayMovieInfo(const TVecPlayerMoveInfo& vecPlayerMoveInfo_, const TVecPathCollideInfo& vecPathCollideInfo_, const TVecGridCollideInfo& vecGridCollideInfo_, const TVecRoomPlayInfo& vecRoomPlayInfo_);
#ifdef __GNUG__
	SPlayMovieInfo(const SPlayMovieInfo& src) = default; //默认拷贝构造函数
	SPlayMovieInfo& operator=(const SPlayMovieInfo& rhs) = default; //默认赋值操作符
#endif
	SPlayMovieInfo(SPlayMovieInfo&& src); //转移构造函数
	SPlayMovieInfo& operator=(SPlayMovieInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SPlayMovieInfo> TVecPlayMovieInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, STakePrizeLog&);
COutArchive& operator<<(COutArchive&, const STakePrizeLog&);

CInArchive& operator>>(CInArchive&, SBoxInfo&);
COutArchive& operator<<(COutArchive&, const SBoxInfo&);

CInArchive& operator>>(CInArchive&, SRoomPlayInfo&);
COutArchive& operator<<(COutArchive&, const SRoomPlayInfo&);

CInArchive& operator>>(CInArchive&, SRoomMonsterInfo&);
COutArchive& operator<<(COutArchive&, const SRoomMonsterInfo&);

CInArchive& operator>>(CInArchive&, SPlayerMoveInfo&);
COutArchive& operator<<(COutArchive&, const SPlayerMoveInfo&);

CInArchive& operator>>(CInArchive&, SPathCollideInfo&);
COutArchive& operator<<(COutArchive&, const SPathCollideInfo&);

CInArchive& operator>>(CInArchive&, SGridCollideInfo&);
COutArchive& operator<<(COutArchive&, const SGridCollideInfo&);

CInArchive& operator>>(CInArchive&, SPlayerFighterLog&);
COutArchive& operator<<(COutArchive&, const SPlayerFighterLog&);

CInArchive& operator>>(CInArchive&, SRoomInfo&);
COutArchive& operator<<(COutArchive&, const SRoomInfo&);

CInArchive& operator>>(CInArchive&, SPlayMovieInfo&);
COutArchive& operator<<(COutArchive&, const SPlayMovieInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, STakePrizeLog&);
bool ToXML(const STakePrizeLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTakePrizeLog&);
bool VectorToXML(const TVecTakePrizeLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBoxInfo&);
bool ToXML(const SBoxInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBoxInfo&);
bool VectorToXML(const TVecBoxInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRoomPlayInfo&);
bool ToXML(const SRoomPlayInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoomPlayInfo&);
bool VectorToXML(const TVecRoomPlayInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRoomMonsterInfo&);
bool ToXML(const SRoomMonsterInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoomMonsterInfo&);
bool VectorToXML(const TVecRoomMonsterInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPlayerMoveInfo&);
bool ToXML(const SPlayerMoveInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerMoveInfo&);
bool VectorToXML(const TVecPlayerMoveInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPathCollideInfo&);
bool ToXML(const SPathCollideInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPathCollideInfo&);
bool VectorToXML(const TVecPathCollideInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGridCollideInfo&);
bool ToXML(const SGridCollideInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGridCollideInfo&);
bool VectorToXML(const TVecGridCollideInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPlayerFighterLog&);
bool ToXML(const SPlayerFighterLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerFighterLog&);
bool VectorToXML(const TVecPlayerFighterLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRoomInfo&);
bool ToXML(const SRoomInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoomInfo&);
bool VectorToXML(const TVecRoomInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPlayMovieInfo&);
bool ToXML(const SPlayMovieInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayMovieInfo&);
bool VectorToXML(const TVecPlayMovieInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NLingShanProt
