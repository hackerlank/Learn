/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ViewInfoProt.h
//  Purpose:      查看信息协议
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
#include "ProtoCommon.h"
#include "RoleInfoDefine.h"

namespace NViewInfoProt
{

/////////////////////以下为类型定义/////////////////////
//出战散仙信息
struct SBattleFighterData
{
	UINT64 qwInstID; //散仙唯一ID
	UINT16 wFighterID; //散仙模版
	UINT8 byFighterLevel; //散仙等级
	UINT8 byTemplateID; //渡劫模版Id
	UINT8 byLevel; //渡劫等级

	SBattleFighterData();
	SBattleFighterData(UINT64 qwInstID_, UINT16 wFighterID_, UINT8 byFighterLevel_, UINT8 byTemplateID_, UINT8 byLevel_);
};

typedef std::vector<SBattleFighterData> TVecBattleFighterData;

//渡劫信息
struct SDujieData
{
	UINT8 byTemplateID; //渡劫模版Id
	UINT8 byLevel; //渡劫等级

	SDujieData();
	SDujieData(UINT8 byTemplateID_, UINT8 byLevel_);
};

typedef std::vector<SDujieData> TVecDujieData;

//淬体（装备）信息
struct SCTData
{
	UINT8 byLianPi; //炼皮
	UINT8 byTongJin; //通筋
	UINT8 byQiangJi; //强肌
	UINT8 byDuanGu; //锻骨
	UINT8 byHuoLuo; //活络
	UINT8 byXiSui; //洗髓

	SCTData();
	SCTData(UINT8 byLianPi_, UINT8 byTongJin_, UINT8 byQiangJi_, UINT8 byDuanGu_, UINT8 byHuoLuo_, 
		UINT8 byXiSui_);
};

//心法数据
struct SCittaData
{
	UINT32 dwCittaID; //心法ID
	UINT8 byLevel; //等级

	SCittaData();
	SCittaData(UINT32 dwCittaID_, UINT8 byLevel_);
};

typedef std::vector<SCittaData> TVecCittaData;

//稀有的法宝信息
struct SRareTrumpData
{
	UINT16 wItemID; //法宝模板
	UINT8 byTrumpLvl; //法宝等级
	UINT8 bySelected; //是否出战

	SRareTrumpData();
	SRareTrumpData(UINT16 wItemID_, UINT8 byTrumpLvl_, UINT8 bySelected_);
};

typedef std::vector<SRareTrumpData> TVecRareTrumpData;

//坐骑信息
struct SHorseData
{
	UINT32 dwHorseID; //坐骑id
	UINT8 byHorseLvl; //坐骑等级
	UINT8 bySelected; //0-不跟随 1-跟随

	SHorseData();
	SHorseData(UINT32 dwHorseID_, UINT8 byHorseLvl_, UINT8 bySelected_);
};

typedef std::vector<SHorseData> TVecHorseData;

//出战美女信息
struct SBeautyData
{
	UINT16 wBeautyID; //美女ID
	UINT8 byLevel; //美女等级
	NProtoCommon::TVecFtAttrMod vecAttr; //美女属性

	SBeautyData();
	SBeautyData(UINT16 wBeautyID_, UINT8 byLevel_, const NProtoCommon::TVecFtAttrMod& vecAttr_);
#ifdef __GNUG__
	SBeautyData(const SBeautyData& src) = default; //默认拷贝构造函数
	SBeautyData& operator=(const SBeautyData& rhs) = default; //默认赋值操作符
#endif
	SBeautyData(SBeautyData&& src); //转移构造函数
	SBeautyData& operator=(SBeautyData&& rhs); //转移赋值操作符
};

//时装信息
struct SFashionData
{
	UINT16 wItemID; //时装模板
	UINT8 byFashionLvl; //时装等级
	UINT8 bySelected; //是否选中

	SFashionData();
	SFashionData(UINT16 wItemID_, UINT8 byFashionLvl_, UINT8 bySelected_);
};

typedef std::vector<SFashionData> TVecFashionData;

//收集信息
struct SCollectionData
{
	UINT8 byCollectionLevel; //收藏等级
	UINT32 dwAP; //收藏点

	SCollectionData();
	SCollectionData(UINT8 byCollectionLevel_, UINT32 dwAP_);
};

typedef std::vector<SCollectionData> TVecCollectionData;

//称号信息
struct STitleData
{
	UINT16 wTitleID; //称号ID
	UINT8 bySelected; //是否选中

	STitleData();
	STitleData(UINT16 wTitleID_, UINT8 bySelected_);
};

typedef std::vector<STitleData> TVecTitleData;

//帮派技能信息
struct SGuildSkillData
{
	UINT32 dwGuildSkillID; //技能id
	UINT8 byGuildSkillLvl; //技能等级

	SGuildSkillData();
	SGuildSkillData(UINT32 dwGuildSkillID_, UINT8 byGuildSkillLvl_);
};

typedef std::vector<SGuildSkillData> TVecGuildSkillData;

//帮派信息
struct SGuildData
{
	std::string strName; //帮派名称
	UINT8 byGuildLvl; //帮派等级
	TVecGuildSkillData vecGuildSkill; //帮派技能

	SGuildData();
	SGuildData(const std::string& strName_, UINT8 byGuildLvl_, const TVecGuildSkillData& vecGuildSkill_);
#ifdef __GNUG__
	SGuildData(const SGuildData& src) = default; //默认拷贝构造函数
	SGuildData& operator=(const SGuildData& rhs) = default; //默认赋值操作符
#endif
	SGuildData(SGuildData&& src); //转移构造函数
	SGuildData& operator=(SGuildData&& rhs); //转移赋值操作符
};

typedef std::vector<SGuildData> TVecGuildData;

//参与战斗的技能信息
struct SSkillData
{
	UINT32 dwSkillID; //技能id
	UINT8 bySkillLvl; //技能等级
	UINT8 bySkillQuality; //技能品质

	SSkillData();
	SSkillData(UINT32 dwSkillID_, UINT8 bySkillLvl_, UINT8 bySkillQuality_);
};

typedef std::vector<SSkillData> TVecSkillData;

//兽魂
struct SBeastSoulData
{
	NRoleInfoDefine::TVecBeastSoulInfo vecBeasSoulInfo; //兽魂
	NProtoCommon::TVecFtAttrMod vecAttr; //兽魂属性

	SBeastSoulData();
	SBeastSoulData(const NRoleInfoDefine::TVecBeastSoulInfo& vecBeasSoulInfo_, const NProtoCommon::TVecFtAttrMod& vecAttr_);
#ifdef __GNUG__
	SBeastSoulData(const SBeastSoulData& src) = default; //默认拷贝构造函数
	SBeastSoulData& operator=(const SBeastSoulData& rhs) = default; //默认赋值操作符
#endif
	SBeastSoulData(SBeastSoulData&& src); //转移构造函数
	SBeastSoulData& operator=(SBeastSoulData&& rhs); //转移赋值操作符
};

//组合
struct SCombData
{
	UINT8 byGroupID; //组合ID
	UINT8 byLevel; //组合等级
	UINT8 bySelected; //是否出战

	SCombData();
	SCombData(UINT8 byGroupID_, UINT8 byLevel_, UINT8 bySelected_);
};

typedef std::vector<SCombData> TVecCombData;

//主角信息
struct SRoleData
{
	std::string strName; //玩家名字
	NProtoCommon::ECareerType eCareer; //职业
	UINT8 byLevel; //玩家等级
	UINT32 dwBTPoint; //战斗力
	NProtoCommon::TVecFtAttrMod vecAttr; //总属性
	TVecBattleFighterData vecBattleFighter; //出战的散仙
	SDujieData sDujie; //渡劫
	SCTData sCuiTi; //淬体(装备)
	TVecUINT32 vecBaoshi; //宝石
	TVecCittaData vecCitta; //心法
	NItemProt::TVecEquipTrump vecTrump; //法宝
	TVecRareTrumpData vecRareTrump; //稀有(被动）法宝
	SBeautyData sBeauty; //美女
	SBeastSoulData sBeastSoul; //魂魄
	TVecCombData vecComb; //组合
	TVecSkillData vecSkill; //技能
	TVecHorseData vecHorse; //坐骑
	TVecFashionData vecFashion; //已激活的时装
	TVecTitleData vecTitle; //已激活的称号
	TVecGuildData vecGuild; //帮派
	NProtoCommon::TVecFtAttrMod vecTianBookAttr; //天书属性

	SRoleData();
#ifdef __GNUG__
	SRoleData(const SRoleData& src) = default; //默认拷贝构造函数
	SRoleData& operator=(const SRoleData& rhs) = default; //默认赋值操作符
#endif
	SRoleData(SRoleData&& src); //转移构造函数
	SRoleData& operator=(SRoleData&& rhs); //转移赋值操作符
};

//散仙信息
struct SFighterData
{
	UINT16 wFighterID; //散仙模版
	UINT8 byLevel; //散仙等级
	UINT32 dwBTPoint; //战斗力
	NProtoCommon::TVecFtAttrMod vecAttr; //将属性
	SDujieData sDujie; //渡劫
	TVecSkillData vecSkill; //技能
	SCTData sCuiTi; //淬体
	TVecUINT32 vecBaoshi; //宝石
	TVecCittaData vecCitta; //心法
	NItemProt::TVecEquipTrump vecTrump; //法宝

	SFighterData();
	SFighterData(UINT16 wFighterID_, UINT8 byLevel_, UINT32 dwBTPoint_, const NProtoCommon::TVecFtAttrMod& vecAttr_, const SDujieData& sDujie_, 
		const TVecSkillData& vecSkill_, const SCTData& sCuiTi_, const TVecUINT32& vecBaoshi_, const TVecCittaData& vecCitta_, const NItemProt::TVecEquipTrump& vecTrump_);
#ifdef __GNUG__
	SFighterData(const SFighterData& src) = default; //默认拷贝构造函数
	SFighterData& operator=(const SFighterData& rhs) = default; //默认赋值操作符
#endif
	SFighterData(SFighterData&& src); //转移构造函数
	SFighterData& operator=(SFighterData&& rhs); //转移赋值操作符
};

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SBattleFighterData&);
COutArchive& operator<<(COutArchive&, const SBattleFighterData&);

CInArchive& operator>>(CInArchive&, SDujieData&);
COutArchive& operator<<(COutArchive&, const SDujieData&);

CInArchive& operator>>(CInArchive&, SCTData&);
COutArchive& operator<<(COutArchive&, const SCTData&);

CInArchive& operator>>(CInArchive&, SCittaData&);
COutArchive& operator<<(COutArchive&, const SCittaData&);

CInArchive& operator>>(CInArchive&, SRareTrumpData&);
COutArchive& operator<<(COutArchive&, const SRareTrumpData&);

CInArchive& operator>>(CInArchive&, SHorseData&);
COutArchive& operator<<(COutArchive&, const SHorseData&);

CInArchive& operator>>(CInArchive&, SBeautyData&);
COutArchive& operator<<(COutArchive&, const SBeautyData&);

CInArchive& operator>>(CInArchive&, SFashionData&);
COutArchive& operator<<(COutArchive&, const SFashionData&);

CInArchive& operator>>(CInArchive&, SCollectionData&);
COutArchive& operator<<(COutArchive&, const SCollectionData&);

CInArchive& operator>>(CInArchive&, STitleData&);
COutArchive& operator<<(COutArchive&, const STitleData&);

CInArchive& operator>>(CInArchive&, SGuildSkillData&);
COutArchive& operator<<(COutArchive&, const SGuildSkillData&);

CInArchive& operator>>(CInArchive&, SGuildData&);
COutArchive& operator<<(COutArchive&, const SGuildData&);

CInArchive& operator>>(CInArchive&, SSkillData&);
COutArchive& operator<<(COutArchive&, const SSkillData&);

CInArchive& operator>>(CInArchive&, SBeastSoulData&);
COutArchive& operator<<(COutArchive&, const SBeastSoulData&);

CInArchive& operator>>(CInArchive&, SCombData&);
COutArchive& operator<<(COutArchive&, const SCombData&);

CInArchive& operator>>(CInArchive&, SRoleData&);
COutArchive& operator<<(COutArchive&, const SRoleData&);

CInArchive& operator>>(CInArchive&, SFighterData&);
COutArchive& operator<<(COutArchive&, const SFighterData&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SBattleFighterData&);
bool ToXML(const SBattleFighterData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleFighterData&);
bool VectorToXML(const TVecBattleFighterData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDujieData&);
bool ToXML(const SDujieData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDujieData&);
bool VectorToXML(const TVecDujieData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SCTData&);
bool ToXML(const SCTData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SCittaData&);
bool ToXML(const SCittaData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecCittaData&);
bool VectorToXML(const TVecCittaData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRareTrumpData&);
bool ToXML(const SRareTrumpData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRareTrumpData&);
bool VectorToXML(const TVecRareTrumpData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SHorseData&);
bool ToXML(const SHorseData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecHorseData&);
bool VectorToXML(const TVecHorseData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBeautyData&);
bool ToXML(const SBeautyData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFashionData&);
bool ToXML(const SFashionData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFashionData&);
bool VectorToXML(const TVecFashionData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SCollectionData&);
bool ToXML(const SCollectionData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecCollectionData&);
bool VectorToXML(const TVecCollectionData&, TiXmlElement&);

bool FromXML(TiXmlElement&, STitleData&);
bool ToXML(const STitleData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTitleData&);
bool VectorToXML(const TVecTitleData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildSkillData&);
bool ToXML(const SGuildSkillData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildSkillData&);
bool VectorToXML(const TVecGuildSkillData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildData&);
bool ToXML(const SGuildData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildData&);
bool VectorToXML(const TVecGuildData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSkillData&);
bool ToXML(const SSkillData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSkillData&);
bool VectorToXML(const TVecSkillData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBeastSoulData&);
bool ToXML(const SBeastSoulData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SCombData&);
bool ToXML(const SCombData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecCombData&);
bool VectorToXML(const TVecCombData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRoleData&);
bool ToXML(const SRoleData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFighterData&);
bool ToXML(const SFighterData&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NViewInfoProt
