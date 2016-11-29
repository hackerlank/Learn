/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    MapProt.h
//  Purpose:      地图相关功能的协议
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
#include "BattleGS.h"
#include "ProtoCommon.h"

namespace NMapProt
{

/////////////////////以下为类型定义/////////////////////
//地图结果
enum EMapResult
{
	eMapSuccess, //成功
	eMapNotGhostErr, //没处于灵魂状态
	eMapCoinErr, //仙石不足
	eMapNotInDungeonErr, //不在副本
	eMapOtherErr //其他错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMapResult);
bool EnumStrToVal(const char*, EMapResult&);
#endif //PROT_USE_XML
const char* GetDescription(EMapResult);

//地图附加数据
enum EMapParam
{
	eMapParamDemonFloorID = 0, //镇妖塔层数
	eMapParamEnd = 3 //数组最大长度，上面索引不同功能可以重复
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMapParam);
bool EnumStrToVal(const char*, EMapParam&);
#endif //PROT_USE_XML

//地图上生物的外观状态
enum EAppearState
{
	eAppearNone = 0, //无
	eAppearFight = 1, //战斗状态
	eAppearGhost = 2, //灵魂状态
	eAppearDie = 3 //死亡状态
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EAppearState);
bool EnumStrToVal(const char*, EAppearState&);
#endif //PROT_USE_XML

//传送阵开关类型
enum ESwitcherType
{
	eSwitcherNone, //无
	eSwitcherJump, //副本传送开关
	eSwitcherCamp, //阵营选择开关
	eSwitcherTower, //试练之塔传送开关
	eSwitcherUpTower, //锁妖塔塔上传开关
	eSwitcherDownTower //锁妖塔下传开关
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ESwitcherType);
bool EnumStrToVal(const char*, ESwitcherType&);
#endif //PROT_USE_XML

//宝藏图操作结果
enum ETreasureResult
{
	eTreasureSuccess, //成功
	eTreasureFail, //失败
	eTreasureNoItem, //没有藏宝图
	eTreasureLackCoin, //仙石不足
	eTreasureNoInArea, //没有在指定区域挖掘
	eTreasureDropErr, //掉落物品错误
	eTreasureDiamond, //钻石不足
	eTreasureBuyInfoSuccess //购买信息成功
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETreasureResult);
bool EnumStrToVal(const char*, ETreasureResult&);
#endif //PROT_USE_XML

//地图负载
enum EMapOverLoad
{
	eMapFree, //空闲
	eMapBusy, //地图忙
	eMapFull //地图满
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMapOverLoad);
bool EnumStrToVal(const char*, EMapOverLoad&);
#endif //PROT_USE_XML

//地图负载情况
struct MapOverLoad
{
	UINT8 byIndex; //地图序号
	EMapOverLoad eLoadState; //负载状况

	MapOverLoad();
	MapOverLoad(UINT8 byIndex_, EMapOverLoad eLoadState_);
};

typedef std::vector<MapOverLoad> TVecMapOverLoad;

//地图上物体的位置
struct SPosition
{
	float fX; //X坐标
	float fY; //Y坐标

	SPosition();
	SPosition(float fX_, float fY_);
};

typedef std::vector<SPosition> TVecPosition;

//角色的外观
struct SPlayerAppear
{
	std::string strName; //角色名
	NProtoCommon::ECareerType eCareer; //职业
	NProtoCommon::ESexType eSex; //性别
	UINT8 byLevel; //等级
	UINT32 dwSpeed; //速度
	NBattleGS::SFeatureBasePtr pFeature; //外观信息
	UINT32 dwHorseID; //坐骑
	UINT32 dwHorseLevel; //坐骑等级
	UINT16 wPetID; //阵灵ID
	UINT8 byPetLevel; //阵灵等级
	UINT16 wBeautyID; //美女ID
	UINT8 byBeautyLevel; //美女等级
	UINT8 bIsSitting; //是否打坐0,没有打坐，1单修，2双修
	UINT64 qwOtherSitID; //双修玩家
	NProtoCommon::TVecPlatformParam vecPlatforms; //平台信息

	SPlayerAppear();
#ifdef __GNUG__
	SPlayerAppear(const SPlayerAppear& src) = default; //默认拷贝构造函数
	SPlayerAppear& operator=(const SPlayerAppear& rhs) = default; //默认赋值操作符
#endif
	SPlayerAppear(SPlayerAppear&& src); //转移构造函数
	SPlayerAppear& operator=(SPlayerAppear&& rhs); //转移赋值操作符
};

typedef std::vector<SPlayerAppear> TVecPlayerAppear;

//怪物的外观
struct SMonsterAppear
{
	UINT16 wMonsterID; //怪物ID
	std::string strName; //怪物名称
	UINT8 byLevel; //等级
	UINT32 dwSpeed; //移动速度/200
	UINT32 dwCurHP; //当前HP
	UINT32 dwMaxHP; //最大HP
	UINT8 byCamp; //阵营
	UINT16 wGroup; //所属的组
	UINT8 bySight; //视野
	UINT8 bySightAngle; //视野角度
	UINT8 byFindEnemy; //0,无目标：1有目标
	NBattleGS::SFeatureBasePtr pFeature; //外观信息

	SMonsterAppear();
};

//NPC的外观
struct SNpcAppear
{
	UINT16 wNpcID; //NPC类型ID
	std::string strName; //NPC名称

	SNpcAppear();
	SNpcAppear(UINT16 wNpcID_, const std::string& strName_);
#ifdef __GNUG__
	SNpcAppear(const SNpcAppear& src) = default; //默认拷贝构造函数
	SNpcAppear& operator=(const SNpcAppear& rhs) = default; //默认赋值操作符
#endif
	SNpcAppear(SNpcAppear&& src); //转移构造函数
	SNpcAppear& operator=(SNpcAppear&& rhs); //转移赋值操作符
};

//采集物的外观
struct SGatherAppear
{
	UINT16 wGatherID; //采集物类型ID
	UINT16 wTotalNum; //采集总次数,特别的为-1表示，采集无数次,以下两个字段始终为0
	UINT16 wReserverNum; //采集剩余次数
	UINT16 wGatheringNum; //正在采集的人次

	SGatherAppear();
	SGatherAppear(UINT16 wGatherID_, UINT16 wTotalNum_, UINT16 wReserverNum_, UINT16 wGatheringNum_);
};

//传送阵开关的外观
struct SSwitcherAppear
{
	UINT32 dwSwitcherID; //开关配置ID
	ESwitcherType eType; //开关类型
	bool bOpen; //开关状态

	SSwitcherAppear();
	SSwitcherAppear(UINT32 dwSwitcherID_, ESwitcherType eType_, bool bOpen_);
};

//阻挡物外观
struct SBlockerAppear
{
	UINT32 dwBlockerID; //阻挡物类型ID,表格数据
	TVecPosition vecPos; //阻挡物阻挡坐标点

	SBlockerAppear();
	SBlockerAppear(UINT32 dwBlockerID_, const TVecPosition& vecPos_);
#ifdef __GNUG__
	SBlockerAppear(const SBlockerAppear& src) = default; //默认拷贝构造函数
	SBlockerAppear& operator=(const SBlockerAppear& rhs) = default; //默认赋值操作符
#endif
	SBlockerAppear(SBlockerAppear&& src); //转移构造函数
	SBlockerAppear& operator=(SBlockerAppear&& rhs); //转移赋值操作符
};

//区域外观
struct SAreaAppear
{
	UINT16 wAreaID; //区域类型ID，表格数据

	SAreaAppear();
	SAreaAppear(UINT16 wAreaID_);
};

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, MapOverLoad&);
COutArchive& operator<<(COutArchive&, const MapOverLoad&);

CInArchive& operator>>(CInArchive&, SPosition&);
COutArchive& operator<<(COutArchive&, const SPosition&);

CInArchive& operator>>(CInArchive&, SPlayerAppear&);
COutArchive& operator<<(COutArchive&, const SPlayerAppear&);

CInArchive& operator>>(CInArchive&, SMonsterAppear&);
COutArchive& operator<<(COutArchive&, const SMonsterAppear&);

CInArchive& operator>>(CInArchive&, SNpcAppear&);
COutArchive& operator<<(COutArchive&, const SNpcAppear&);

CInArchive& operator>>(CInArchive&, SGatherAppear&);
COutArchive& operator<<(COutArchive&, const SGatherAppear&);

CInArchive& operator>>(CInArchive&, SSwitcherAppear&);
COutArchive& operator<<(COutArchive&, const SSwitcherAppear&);

CInArchive& operator>>(CInArchive&, SBlockerAppear&);
COutArchive& operator<<(COutArchive&, const SBlockerAppear&);

CInArchive& operator>>(CInArchive&, SAreaAppear&);
COutArchive& operator<<(COutArchive&, const SAreaAppear&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, MapOverLoad&);
bool ToXML(const MapOverLoad&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMapOverLoad&);
bool VectorToXML(const TVecMapOverLoad&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPosition&);
bool ToXML(const SPosition&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPosition&);
bool VectorToXML(const TVecPosition&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPlayerAppear&);
bool ToXML(const SPlayerAppear&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerAppear&);
bool VectorToXML(const TVecPlayerAppear&, TiXmlElement&);

bool FromXML(TiXmlElement&, SMonsterAppear&);
bool ToXML(const SMonsterAppear&, TiXmlElement&);

bool FromXML(TiXmlElement&, SNpcAppear&);
bool ToXML(const SNpcAppear&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGatherAppear&);
bool ToXML(const SGatherAppear&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSwitcherAppear&);
bool ToXML(const SSwitcherAppear&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBlockerAppear&);
bool ToXML(const SBlockerAppear&, TiXmlElement&);

bool FromXML(TiXmlElement&, SAreaAppear&);
bool ToXML(const SAreaAppear&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NMapProt
