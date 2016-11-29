/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    PHPProt.h
//  Purpose:      PHP相关协议
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

namespace NPHPProt
{

/////////////////////以下为类型定义/////////////////////
//后台操作结果
enum EOptResult
{
	eOptResultSucc, //成功
	eOptResultFailed //失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EOptResult);
bool EnumStrToVal(const char*, EOptResult&);
#endif //PROT_USE_XML

//后台操作类型
enum EOptType
{
	eOptNone, //无
	eOptLockUser, //封号
	eOptUnlockUser, //解封
	eOptLockSpeak, //禁言
	eOptUnlockSpeak, //解禁
	eOptSetPlayerVIPLevel, //设置玩家VIP等级
	eOptAddGrowthValue, //增加玩家成长值
	eOptEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EOptType);
bool EnumStrToVal(const char*, EOptType&);
#endif //PROT_USE_XML

//日常任务类型
enum EPHPTaskType
{
	ePHPTaskNone, //无
	ePHPYaMenTask, //衙门任务
	ePHPShiMenTask, //师门任务
	ePHPTaskEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EPHPTaskType);
bool EnumStrToVal(const char*, EPHPTaskType&);
#endif //PROT_USE_XML

//发放对象
enum ESendTarget
{
	eSendTargetNone, //无
	eIsOnline, //在线玩家
	eAll, //所有玩家
	eClanMember, //帮派成员
	eClanBag, //帮派仓库
	eSendTargetEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ESendTarget);
bool EnumStrToVal(const char*, ESendTarget&);
#endif //PROT_USE_XML

//任务集市中任务操作
enum ETaskOpt
{
	eTaskOptNone, //无
	eTaskOptComplete, //任务是否完成
	eTaskOptCompAndReward, //任务是否完成，若完成发放奖励
	eTaskOptReward, //发放奖励
	eTaskOptEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETaskOpt);
bool EnumStrToVal(const char*, ETaskOpt&);
#endif //PROT_USE_XML

//任务集市状态返回
enum ETaskState
{
	eTaskStateNone, //无
	eTaskStateSuc, //奖励发放成功或任务步骤完成
	eTaskStateNoRole, //玩家没有创建角色
	eTaskStateNoComp, //任务步骤没有完成
	eTaskStateSended, //奖励已经发放过
	eTaskStateSendErr, //发放奖励错误
	eTaskStateParamErr, //请求参数错误
	eTaskStateOtherErr, //其他错误
	eTaskStateEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETaskState);
bool EnumStrToVal(const char*, ETaskState&);
#endif //PROT_USE_XML

//平台类型
enum EPlatformType
{
	ePlatformNone, //无
	ePlatformTypeQQYellow, //QQ黄钻平台/Qzone
	ePlatformTypeQQPengyou, //QQ朋友/校友/黄钻
	ePlatformTypeQQWeibo, //QQ微博平台
	ePlatformTypeQQPlus, //QQ/Q+平台
	ePlatformTypeQQGame, //QQ蓝钻/游戏平台
	ePlatformTypeQQ3366, //QQ蓝钻/3366平台/包子
	ePlatformTypeQQKingxin, //QQ官网平台/QQ会员
	ePlatformTypeKingxin, //恺英官网平台
	ePlatformTypeEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EPlatformType);
bool EnumStrToVal(const char*, EPlatformType&);
#endif //PROT_USE_XML

//QQ平台类型
enum EQQPlatformType
{
	eQQPlatformTypeNone, //无
	eQQPlatformTypeYellow, //黄钻平台
	eQQPlatformTypeBlue, //蓝钻平台
	eQQPlatformTypeRed, //红钻/VIP平台
	eQQPlatformTypeEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EQQPlatformType);
bool EnumStrToVal(const char*, EQQPlatformType&);
#endif //PROT_USE_XML
const char* GetDescription(EQQPlatformType);

//平台类型定义
enum EPHPPtType
{
	ePHPPtTypeNone, //无
	ePHPPtTypeQQYellow, //QQ黄钻平台/Qzone
	ePHPPtTypeQQPengyou, //QQ朋友/校友/黄钻
	ePHPPtTypeQQWeibo, //QQ微博平台
	ePHPPtTypeQQPlus, //QQ/Q+平台
	ePHPPtTypeQQGame, //QQ蓝钻/游戏平台
	ePHPPtTypeQQ3366, //QQ蓝钻/3366平台/包子
	ePHPPtTypeQQKingxin, //QQ官网平台/QQ会员
	ePHPPtTypeKingxin, //恺英官网平台
	ePHPPtTypeMax //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EPHPPtType);
bool EnumStrToVal(const char*, EPHPPtType&);
#endif //PROT_USE_XML
const char* GetDescription(EPHPPtType);

//公告显示区域类型
enum EShowType
{
	eShowNone, //无
	eChatWindowNotice, //聊天窗口显示公告
	eAllNotice, //全部显示
	eShowEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EShowType);
bool EnumStrToVal(const char*, EShowType&);
#endif //PROT_USE_XML

//是否滚动
enum ERollType
{
	eRollNone, //无
	eIsRoll, //滚动
	eNoRoll, //不滚动
	eRollEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ERollType);
bool EnumStrToVal(const char*, ERollType&);
#endif //PROT_USE_XML

//是否立即发送
enum ESendType
{
	eSendNone, //无
	eIsImmediateSend, //立即发送
	eNoImmediateSend, //不立即发送
	eSendEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ESendType);
bool EnumStrToVal(const char*, ESendType&);
#endif //PROT_USE_XML

//弹窗类型
enum EDialogType
{
	eDialogNone, //无
	eUpdateNoticeDialog, //更新公告弹窗
	eSysDialog, //系统弹窗
	eDialogEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDialogType);
bool EnumStrToVal(const char*, EDialogType&);
#endif //PROT_USE_XML

//类型
enum EActivityType
{
	eActivity_None, //无
	eActivity_WorldBoss = 1, //世界boss活动
	eActivity_LangHuanBless = 2, //琅环活动
	eActivity_DragonBall = 3, //七星龙珠活动
	eActivity_SevenConsume = 4, //七日消费活动
	eActivity_QQCoin = 5, //Q币养成活动
	eActivity_Max //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EActivityType);
bool EnumStrToVal(const char*, EActivityType&);
#endif //PROT_USE_XML

//UserID和Name
struct SUserIDAndName
{
	UINT64 qwUserID; //用户ID
	std::string strName; //角色名称

	SUserIDAndName();
	SUserIDAndName(UINT64 qwUserID_, const std::string& strName_);
#ifdef __GNUG__
	SUserIDAndName(const SUserIDAndName& src) = default; //默认拷贝构造函数
	SUserIDAndName& operator=(const SUserIDAndName& rhs) = default; //默认赋值操作符
#endif
	SUserIDAndName(SUserIDAndName&& src); //转移构造函数
	SUserIDAndName& operator=(SUserIDAndName&& rhs); //转移赋值操作符
};

typedef std::vector<SUserIDAndName> TVecUserIDAndName;

//公告
struct SNotice
{
	UINT32 dwNoticeID; //公告ID
	UINT8 byNoticeType; //公告类型
	std::string strContent; //公告内容
	UINT32 dwBeginTime; //公告开始时间
	UINT32 dwEndTime; //公告结束

	SNotice();
	SNotice(UINT32 dwNoticeID_, UINT8 byNoticeType_, const std::string& strContent_, UINT32 dwBeginTime_, UINT32 dwEndTime_);
#ifdef __GNUG__
	SNotice(const SNotice& src) = default; //默认拷贝构造函数
	SNotice& operator=(const SNotice& rhs) = default; //默认赋值操作符
#endif
	SNotice(SNotice&& src); //转移构造函数
	SNotice& operator=(SNotice&& rhs); //转移赋值操作符
};

typedef std::vector<SNotice> TVecNotice;

//玩家信息
struct SPlayerInfo
{
	UINT64 qwUserID; //用户ID
	std::string strName; //角色名称
	UINT16 wLevel; //等级
	std::string strGuildName; //帮派名
	UINT64 qwGuildID; //帮派ID
	UINT8 byJob; //职业(1、儒；2、释；3、道；4、墨)
	UINT8 bySex; //性别(1、男；2、女)
	UINT32 dwSilver; //银币
	UINT32 dwGold; //仙石
	UINT32 dwCoupon; //礼券
	UINT8 byForbExpire; //是否禁言(0、否；1、是)
	UINT8 byLockExpire; //是否封号(0、否；1、是)
	UINT8 byVIPLevel; //VIP等级
	UINT32 dwPrestige; //声望
	UINT32 dwHonor; //荣誉
	UINT32 dwDJ; //斗剑排名
	UINT32 dwHistoryDJ; //历史最高斗剑
	UINT32 dwCreateTime; //创角时间
	UINT16 wShiMenTask; //师门任务
	UINT16 wYaMenTaTask; //衙门任务

	SPlayerInfo();
#ifdef __GNUG__
	SPlayerInfo(const SPlayerInfo& src) = default; //默认拷贝构造函数
	SPlayerInfo& operator=(const SPlayerInfo& rhs) = default; //默认赋值操作符
#endif
	SPlayerInfo(SPlayerInfo&& src); //转移构造函数
	SPlayerInfo& operator=(SPlayerInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SPlayerInfo> TVecPlayerInfo;

//玩家背包信息
struct SPlayerBagInfo
{
	UINT64 qwInstID; //物品唯一ID
	UINT16 wItemID; //物品模板
	UINT8 byType; //1；背包，2：仓库
	UINT16 wCount; //堆叠数
	UINT8 byBind; //0：非绑定，1：绑定

	SPlayerBagInfo();
	SPlayerBagInfo(UINT64 qwInstID_, UINT16 wItemID_, UINT8 byType_, UINT16 wCount_, UINT8 byBind_);
};

typedef std::vector<SPlayerBagInfo> TVecPlayerBagInfo;

//天赐宝箱活动参数修改
struct SChestInfo
{
	UINT32 dwTime; //开启时间
	UINT8 byBig; //大宝箱个数
	UINT8 byMid; //中宝箱个数
	UINT8 bySmall; //小宝箱个数
	UINT8 byPeroid; //活动持续时间
	UINT16 wMapID; //宝箱刷新地图

	SChestInfo();
	SChestInfo(UINT32 dwTime_, UINT8 byBig_, UINT8 byMid_, UINT8 bySmall_, UINT8 byPeroid_, 
		UINT16 wMapID_);
};

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SUserIDAndName&);
COutArchive& operator<<(COutArchive&, const SUserIDAndName&);

CInArchive& operator>>(CInArchive&, SNotice&);
COutArchive& operator<<(COutArchive&, const SNotice&);

CInArchive& operator>>(CInArchive&, SPlayerInfo&);
COutArchive& operator<<(COutArchive&, const SPlayerInfo&);

CInArchive& operator>>(CInArchive&, SPlayerBagInfo&);
COutArchive& operator<<(COutArchive&, const SPlayerBagInfo&);

CInArchive& operator>>(CInArchive&, SChestInfo&);
COutArchive& operator<<(COutArchive&, const SChestInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SUserIDAndName&);
bool ToXML(const SUserIDAndName&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecUserIDAndName&);
bool VectorToXML(const TVecUserIDAndName&, TiXmlElement&);

bool FromXML(TiXmlElement&, SNotice&);
bool ToXML(const SNotice&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecNotice&);
bool VectorToXML(const TVecNotice&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPlayerInfo&);
bool ToXML(const SPlayerInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerInfo&);
bool VectorToXML(const TVecPlayerInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPlayerBagInfo&);
bool ToXML(const SPlayerBagInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerBagInfo&);
bool VectorToXML(const TVecPlayerBagInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SChestInfo&);
bool ToXML(const SChestInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NPHPProt
