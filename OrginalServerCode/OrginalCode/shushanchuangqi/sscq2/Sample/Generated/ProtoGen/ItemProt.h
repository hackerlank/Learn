/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ItemProt.h
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
#include "ProtoCommon.h"

namespace NItemProt
{

/////////////////////以下为类型定义/////////////////////
//使用道具结果
enum EItemResult
{
	eItemSucceed, //成功
	eItemFailed, //失败
	eItemNotEnougth, //道具使用个数不足
	eItemNotExist, //道具不存在
	eItemErrBind, //道具为绑定
	eItemErrUse, //道具无法使用
	eItemStoreFull, //包裹或仓库满
	eItemStoreErr, //包裹或仓库错误
	eItemRangeErr, //道具距离过远
	eItemNoStack, //道具为非堆叠的
	eItemNoCoin, //游戏币不足
	eItemCoinFull, //游戏币超出上限
	eItemNoMoney, //仙石不足
	eItemMoneyFull, //充值货币超出上限
	eItemErrOper, //操作非法
	eItemErrCD, //CD时间未到
	eItemErrSlot, //装备位错误
	eItemNotNeed, //无需此操作
	eItemErrName, //名字太长
	eItemExpired, //道具使用时间过期
	eItemErrSell, //道具无法出售
	eItemErrDrop, //道具无法丢弃
	eItemErrLevel, //使用等级不够
	eItemErrJob, //使用职业限制
	eItemNoStuff, //材料不足
	eItemErrDungeon, //副本中无法使用传送卷轴
	eItemErrTransfMap, //该地图中无法使用传送卷轴
	eItemMountExist, //已存在该坐骑
	eItemMutualEquip, //属性类型
	eItemMutual, //属性类型
	eItemNoTakeOff, //无法脱下
	eItemSkillExist, //该技能已存在
	eItemFashionExist, //该时装已存在
	eItemStoreMax, //背包已达上限
	eItemDepotMax, //仓库已达上限
	eItemErrOther //其它错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EItemResult);
bool EnumStrToVal(const char*, EItemResult&);
#endif //PROT_USE_XML

//心法操作结果
enum ECittaResult
{
	eCittaSuccess, //心法操作成功
	eCittaFailed, //心法操作失败
	eCittaPackFull, //心法操作时背包已满
	eCittaMaterialLack, //材料不足
	eCittaSlotNotEmpty, //心法槽已满
	eCittaSlotEmpty, //心法槽为空
	eCittaSilverLack //银币不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECittaResult);
bool EnumStrToVal(const char*, ECittaResult&);
#endif //PROT_USE_XML

//装备养成结果
enum ETrumpResult
{
	eTrumpSuccess, //法宝养成成功
	eTrumpFailed, //法宝养成失败
	eTrumpExist, //法宝已经存在
	eTrumpNotifyFailed, //法宝通知失败
	eTrumpNotActived, //法宝未激活
	eTrumpNotExist, //法宝不存在
	eTrumpUpgradeMaterialLack, //法宝强化材料不足
	eTrumpEvolveMaterialLack, //法宝升阶材料不足
	eTrumpFull, //法宝位已满
	eTrumpIsEquiped, //法宝已装备
	eTrumpNotEquiped, //法宝未装备
	eTrumpActiveFailed //法宝解锁失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETrumpResult);
bool EnumStrToVal(const char*, ETrumpResult&);
#endif //PROT_USE_XML

//时装养成结果
enum EFashionResult
{
	eFashionSucc, //时装养成成功
	eFashionFailed, //时装养成失败
	eFashionItemErr //时装养成时所需物品不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EFashionResult);
bool EnumStrToVal(const char*, EFashionResult&);
#endif //PROT_USE_XML

//宝石操作
enum EGemstoneResult
{
	eGemstoneSuccess, //宝石操作成功
	eGemstoneFailed, //宝石操作失败
	eGemstoneSlotNotEmpty, //宝石位置非空
	eGemstoneSlotEmpty, //宝石位置空
	eGemstonePackFull, //包裹满
	eGemstoneHeroErr, //将错误
	eGemstoneNoStone, //没有找到宝石
	eGemstoneErrStone, //宝石合成目标不存在
	eGemstoneMaterialLack, //宝石材料不足
	eGemstoneHasSameType //已经装备相同类型宝石
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGemstoneResult);
bool EnumStrToVal(const char*, EGemstoneResult&);
#endif //PROT_USE_XML

//道具品质
enum EItemQuality
{
	eColorNone, //无
	eColorGreen, //绿
	eColorBlue, //蓝
	eColorPurple, //紫
	eColorOrange, //橙
	eColorBlackGold, //暗金
	eColorEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EItemQuality);
bool EnumStrToVal(const char*, EItemQuality&);
#endif //PROT_USE_XML

//存储类型
enum EStoreType
{
	eStoreNone, //无
	eStorePack, //道具包裹
	eStoreDepot, //角色仓库
	eStorePlayerTrump, //法宝栏
	eStorePlayerCitta, //心法栏
	eStoreFashion, //时装栏
	eStoreGemstone, //宝石栏
	eStoreEquipTrump //装备法宝栏
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EStoreType);
bool EnumStrToVal(const char*, EStoreType&);
#endif //PROT_USE_XML

//道具日志类型
enum EItemLoggerType
{
	eItemLogger1 //试炼塔道具日志
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EItemLoggerType);
bool EnumStrToVal(const char*, EItemLoggerType&);
#endif //PROT_USE_XML

//绑定类型
enum EBindType
{
	eBindNone, //未绑定
	eBindGet, //获取绑定
	eBindStren //强化后绑定
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBindType);
bool EnumStrToVal(const char*, EBindType&);
#endif //PROT_USE_XML

//绑定优先使用类型
enum EBindUseType
{
	eBindUseNone, //只使用非绑定
	eBindUseBind, //只使用绑定
	eBindUseNoneFirst, //优先使用非绑定
	eBindUseBindFirst //优先使用绑定
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBindUseType);
bool EnumStrToVal(const char*, EBindUseType&);
#endif //PROT_USE_XML

//类型大类型
enum EItemType
{
	eItemNone, //无类型
	eItemResource, //资源道具
	eItemNormal, //普通道具
	eItemTrump, //法宝
	eItemEquipTrump, //装备法宝
	eItemFashion, //时装
	eItemFormation, //阵法
	eItemCitta, //心法
	eItemIntensify, //强化
	eItemSkillBook, //技能书
	eItemStone, //宝石
	eItemStuff, //材料
	eItemTask, //任务
	eItemSpirit, //注灵
	eItemSoul, //元神
	eItemNeidan, //灵宠内丹
	eItemVigour, //灵宠精魄
	eItemOther, //其他
	eItemEnd
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EItemType);
bool EnumStrToVal(const char*, EItemType&);
#endif //PROT_USE_XML

//物品子类型
enum EItemSubType
{
	eItemSubNone, //无类型
	eItemSubResource = 1, //资源
	eItemSubNormal = 2, //普通
	eItemSubFasionMaterial = 10, //时装激活材料
	eItemSubZTMaterial = 20, //本命法宝温养材料
	eItemSubWepaon = 21, //武器
	eItemSubRing = 22, //戒指
	eItemSubNeck = 23, //项链
	eItemSubHead = 24, //头盔
	eItemSubChest = 25, //胸甲
	eItemSubLegging = 26, //护腿
	eItemSubMounts = 30, //坐骑
	eItemSubActiveTrump = 32, //主动法宝
	eItemSubPassiveTrump = 33, //被动法宝
	eItemSubFashion = 51, //时装-神器
	eItemSubFashion2 = 52, //时装-神衣
	eItemSubSpirit = 141, //注灵
	eItemSubPetSoul = 151, //兽魂
	eItemSubEquipTrumpInnate = 205, //先天
	eItemSubEquipTrumpPassive = 206, //被动
	eItemSubEquipTrumpTransform = 207, //光环
	eItemSubEquipTrumpHalo = 208 //变身
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EItemSubType);
bool EnumStrToVal(const char*, EItemSubType&);
#endif //PROT_USE_XML

//法宝位类型
enum ETrumpSlotType
{
	eSlotTrump1, //法宝1
	eSlotTrump2, //法宝2
	eSlotTrump3, //法宝3
	eSlotTrump4, //法宝4
	eSlotTrump5, //法宝5
	eSlotTrump6, //法宝6
	eSlotTrump7, //法宝7
	eSlotTrump8, //法宝8
	eSlotTrump9, //法宝9
	eSlotTrump10 //法宝10
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETrumpSlotType);
bool EnumStrToVal(const char*, ETrumpSlotType&);
#endif //PROT_USE_XML

//心法位类型
enum ECittaSlotType
{
	eSlotCitta1, //心法1
	eSlotCitta2, //心法2
	eSlotCitta3, //心法3
	eSlotCitta4, //心法4
	eSlotCitta5, //心法5
	eSlotCitta6, //心法6
	eSlotCitta7, //心法7
	eSlotCitta8 //心法8
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECittaSlotType);
bool EnumStrToVal(const char*, ECittaSlotType&);
#endif //PROT_USE_XML

//心法姓名前缀类型
enum ECittaNameType
{
	eNameNone = 0, //破烂之
	eNameAttack, //力量之
	eNameDefence, //坚固的
	eNameMgcDefence, //道心之
	eNameHP, //长生的
	eNameHit, //神佑的
	eNameDodge, //灵猴的
	eNameCritical, //刺客的
	eNameAntiCri, //平衡的
	eNamePiece, //破击之
	eNameCounter, //反击之
	eNameResist //压制的
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECittaNameType);
bool EnumStrToVal(const char*, ECittaNameType&);
#endif //PROT_USE_XML

//结构体：SItem的继承体系类型
enum EType_SItem
{
	eType_SItem, //类型：SItem
	eType_SStack, //类型：SStack
	eType_SEquipTrump, //类型：SEquipTrump
	eType_SCitta, //类型：SCitta
	eType_STrump, //类型：STrump
	eType_SFashion, //类型：SFashion
	eType_SGemstone //类型：SGemstone
};

//显示用的模板数据
struct SItemGenInfo
{
	UINT16 wItemID; //模板ID
	UINT32 dwCount; //数量
	UINT8 byQuality; //品质
	EBindType eBindType; //绑定类型
	UINT32 dwTimeID; //时钟ID

	SItemGenInfo();
	SItemGenInfo(UINT16 wItemID_, UINT32 dwCount_, UINT8 byQuality_, EBindType eBindType_, UINT32 dwTimeID_);
};

typedef std::vector<SItemGenInfo> TVecItemGenInfo;

//物品列表
struct SInstCount
{
	UINT64 qwInstID; //道具唯一ID
	UINT32 wCount; //道具个数

	SInstCount();
	SInstCount(UINT64 qwInstID_, UINT32 wCount_);
};

typedef std::vector<SInstCount> TVecInstCount;

//物品列表
struct SItemCount
{
	UINT16 wItemID; //道具ID
	UINT32 wCount; //道具个数

	SItemCount();
	SItemCount(UINT16 wItemID_, UINT32 wCount_);
};

typedef std::vector<SItemCount> TVecItemCount;

//资源列表
struct SResource
{
	NProtoCommon::EMoneyType _eRes; //资源(货币)类型
	UINT32 _dwValue; //资源(货币)数量

	SResource();
	SResource(NProtoCommon::EMoneyType _eRes_, UINT32 _dwValue_);
};

typedef std::vector<SResource> TVecResource;

//EDataType:eRoleItemInfo
struct RoleItemInfo
{
	UINT64 qwInstID; //物品唯一ID
	UINT16 wItemID; //物品模板
	UINT8 byStoreType; //背包类型-数据来源：EStoreType
	INT16 wIndex; //所属背包的位置
	UINT16 wCount; //具的堆叠数
	UINT8 byBind; //绑定类型0非绑定，1绑定
	UINT8 byExpired; //是否时效，>0 时效物品
	UINT32 dwExpireTime; //时效过期时间
	UINT32 dwMark; //标记为错误物品,存下标记时间

	RoleItemInfo();
	RoleItemInfo(UINT64 qwInstID_, UINT16 wItemID_, UINT8 byStoreType_, INT16 wIndex_, UINT16 wCount_, 
		UINT8 byBind_, UINT8 byExpired_, UINT32 dwExpireTime_, UINT32 dwMark_);
};

typedef std::vector<RoleItemInfo> TVecRoleItemInfo;

//洗炼信息
struct SShuffleInfo
{
	UINT32 dwType; //洗炼类型
	UINT32 dwValue; //洗炼数值

	SShuffleInfo();
	SShuffleInfo(UINT32 dwType_, UINT32 dwValue_);
};

typedef std::vector<SShuffleInfo> TVecShuffleInfo;

//道具的信息
struct SItem
{
	RoleItemInfo sItemInfo; //道具信息

	SItem();
	virtual ~SItem() { }
	DEF_NEW_DELETE(SItem); //使用对象池
	virtual EType_SItem GetClassType() const { return eType_SItem; }
};

typedef std::shared_ptr<SItem> SItemPtr;
typedef std::weak_ptr<SItem> SItemWtr;
typedef std::vector<SItemPtr> TVecItem;

//父类：SItem的辅助结构体
struct SItem_Wrapper
{
	SItemPtr ptr;
	SItem_Wrapper(const SItemPtr& ptr_ = NULL) : ptr(ptr_) { }
};

//堆叠道具的信息，只用于识别
struct SStack : public SItem
{
	SStack();
	DEF_NEW_DELETE(SStack); //使用对象池
	virtual EType_SItem GetClassType() const { return eType_SStack; }
};

typedef std::shared_ptr<SStack> SStackPtr;
typedef std::weak_ptr<SStack> SStackWtr;
typedef std::vector<SStackPtr> TVecStack;

//装备的信息
struct SEquipTrump : public SItem
{
	UINT64 qwOwnerID; //散仙唯一ID，属于散仙的物品时有效
	UINT8 byIntensifyLvl; //当前强化等级
	UINT8 byIntensifyLvlMax; //可强的最高等级
	UINT32 dwBlessing; //强化祝福值
	TVecShuffleInfo vecShuffleInfo; //洗炼信息
	TVecShuffleInfo vecNowReplace; //可替换的洗炼信息
	UINT32 dwXiLianBlessing; //洗练祝福值

	SEquipTrump();
#ifdef __GNUG__
	SEquipTrump(const SEquipTrump& src) = default; //默认拷贝构造函数
	SEquipTrump& operator=(const SEquipTrump& rhs) = default; //默认赋值操作符
#endif
	SEquipTrump(SEquipTrump&& src); //转移构造函数
	SEquipTrump& operator=(SEquipTrump&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SEquipTrump); //使用对象池
	virtual EType_SItem GetClassType() const { return eType_SEquipTrump; }
};

typedef std::shared_ptr<SEquipTrump> SEquipTrumpPtr;
typedef std::weak_ptr<SEquipTrump> SEquipTrumpWtr;
typedef std::vector<SEquipTrumpPtr> TVecEquipTrump;

//心法的信息
struct SCitta : public SItem
{
	UINT64 qwOwnerID; //散仙唯一ID，属于散仙的物品时有效
	ECittaNameType eCittaNameType; //心法姓名前缀
	NProtoCommon::TVecFtAttrMod oAttrVec; //增加属性
	UINT32 dwSkillID; //附加技能ID
	UINT32 dwSignetID; //印记ID

	SCitta();
#ifdef __GNUG__
	SCitta(const SCitta& src) = default; //默认拷贝构造函数
	SCitta& operator=(const SCitta& rhs) = default; //默认赋值操作符
#endif
	SCitta(SCitta&& src); //转移构造函数
	SCitta& operator=(SCitta&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SCitta); //使用对象池
	virtual EType_SItem GetClassType() const { return eType_SCitta; }
};

typedef std::shared_ptr<SCitta> SCittaPtr;
typedef std::weak_ptr<SCitta> SCittaWtr;
typedef std::vector<SCittaPtr> TVecCitta;

//法宝信息
struct STrump : public SItem
{
	UINT64 qwRoleID; //拥有者RoleID
	UINT8 byActived; //
	UINT8 byUsed; //法宝是否出战
	UINT32 dwExp; //法宝祭炼值
	UINT16 wLevel; //法宝祭炼等级
	UINT16 wRank; //法宝祭炼阶数

	STrump();
	DEF_NEW_DELETE(STrump); //使用对象池
	virtual EType_SItem GetClassType() const { return eType_STrump; }
};

typedef std::shared_ptr<STrump> STrumpPtr;
typedef std::weak_ptr<STrump> STrumpWtr;
typedef std::vector<STrumpPtr> TVecTrump;

//时装信息
struct SFashion : public SItem
{
	UINT8 byLevel; //时装等级
	UINT32 dwExp; //时装经验
	UINT8 bySelected; //是否选中
	UINT8 byHide; //是否隐藏

	SFashion();
	DEF_NEW_DELETE(SFashion); //使用对象池
	virtual EType_SItem GetClassType() const { return eType_SFashion; }
};

typedef std::shared_ptr<SFashion> SFashionPtr;
typedef std::weak_ptr<SFashion> SFashionWtr;
typedef std::vector<SFashionPtr> TVecFashion;

//宝石信息
struct SGemstone : public SItem
{
	UINT64 qwOwnerID; //散仙唯一ID

	SGemstone();
	DEF_NEW_DELETE(SGemstone); //使用对象池
	virtual EType_SItem GetClassType() const { return eType_SGemstone; }
};

typedef std::shared_ptr<SGemstone> SGemstonePtr;
typedef std::weak_ptr<SGemstone> SGemstoneWtr;
typedef std::vector<SGemstonePtr> TVecGemstone;

//背包信息
struct SStoreStream
{
	UINT16 wCapacity; //背包大小(不发最大值，最大值由两端的配置决定)
	TVecItem vecItem; //物品信息

	SStoreStream();
#ifdef __GNUG__
	SStoreStream(const SStoreStream& src) = default; //默认拷贝构造函数
	SStoreStream& operator=(const SStoreStream& rhs) = default; //默认赋值操作符
#endif
	SStoreStream(SStoreStream&& src); //转移构造函数
	SStoreStream& operator=(SStoreStream&& rhs); //转移赋值操作符
};

//玩家道具冷却时间
struct SItemColdTime
{
	UINT16 wID; //冷却ID
	UINT32 dwTime; //冷却到期时间

	SItemColdTime();
	SItemColdTime(UINT16 wID_, UINT32 dwTime_);
};

typedef std::vector<SItemColdTime> TVecItemColdTime;

//玩家获得道具
struct SAddItemMsg
{
	UINT16 wItemID; //道具的ID
	UINT16 wCount; //道具个数
	UINT8 byQuality; //道具品质

	SAddItemMsg();
	SAddItemMsg(UINT16 wItemID_, UINT16 wCount_, UINT8 byQuality_);
};

typedef std::vector<SAddItemMsg> TVecAddItemMsg;

//记录的道具
struct SLoggedItem
{
	UINT16 wItemID; //道具ID
	UINT8 byQuality; //品质
	UINT32 dwCount; //道具个数
	bool bBind; //是否绑定

	SLoggedItem();
	SLoggedItem(UINT16 wItemID_, UINT8 byQuality_, UINT32 dwCount_, bool bBind_);
};

typedef std::vector<SLoggedItem> TVecLoggedItem;

//收件人信息
struct SGMMailTarget
{
	UINT64 qwTargetID; //收件人ID
	std::string strTarget; //收件人名

	SGMMailTarget();
	SGMMailTarget(UINT64 qwTargetID_, const std::string& strTarget_);
#ifdef __GNUG__
	SGMMailTarget(const SGMMailTarget& src) = default; //默认拷贝构造函数
	SGMMailTarget& operator=(const SGMMailTarget& rhs) = default; //默认赋值操作符
#endif
	SGMMailTarget(SGMMailTarget&& src); //转移构造函数
	SGMMailTarget& operator=(SGMMailTarget&& rhs); //转移赋值操作符
};

typedef std::vector<SGMMailTarget> TVecGMMailTarget;

//道具信息
struct SGMMailItem
{
	UINT16 wItemID; //道具配置ID
	UINT32 wItemCount; //道具数量

	SGMMailItem();
	SGMMailItem(UINT16 wItemID_, UINT32 wItemCount_);
};

typedef std::vector<SGMMailItem> TVecGMMailItem;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SItemGenInfo&);
COutArchive& operator<<(COutArchive&, const SItemGenInfo&);

CInArchive& operator>>(CInArchive&, SInstCount&);
COutArchive& operator<<(COutArchive&, const SInstCount&);

CInArchive& operator>>(CInArchive&, SItemCount&);
COutArchive& operator<<(COutArchive&, const SItemCount&);

CInArchive& operator>>(CInArchive&, SResource&);
COutArchive& operator<<(COutArchive&, const SResource&);

CInArchive& operator>>(CInArchive&, RoleItemInfo&);
COutArchive& operator<<(COutArchive&, const RoleItemInfo&);

CInArchive& operator>>(CInArchive&, SShuffleInfo&);
COutArchive& operator<<(COutArchive&, const SShuffleInfo&);

CInArchive& operator>>(CInArchive&, SItem&);
COutArchive& operator<<(COutArchive&, const SItem&);
CInArchive& operator>>(CInArchive&, SItem_Wrapper&);
COutArchive& operator<<(COutArchive&, const SItem_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecItem&);
COutArchive& operator<<(COutArchive&, const TVecItem&);

CInArchive& operator>>(CInArchive&, SStack&);
COutArchive& operator<<(COutArchive&, const SStack&);
CInArchive& operator>>(CInArchive&, TVecStack&);
COutArchive& operator<<(COutArchive&, const TVecStack&);

CInArchive& operator>>(CInArchive&, SEquipTrump&);
COutArchive& operator<<(COutArchive&, const SEquipTrump&);
CInArchive& operator>>(CInArchive&, TVecEquipTrump&);
COutArchive& operator<<(COutArchive&, const TVecEquipTrump&);

CInArchive& operator>>(CInArchive&, SCitta&);
COutArchive& operator<<(COutArchive&, const SCitta&);
CInArchive& operator>>(CInArchive&, TVecCitta&);
COutArchive& operator<<(COutArchive&, const TVecCitta&);

CInArchive& operator>>(CInArchive&, STrump&);
COutArchive& operator<<(COutArchive&, const STrump&);
CInArchive& operator>>(CInArchive&, TVecTrump&);
COutArchive& operator<<(COutArchive&, const TVecTrump&);

CInArchive& operator>>(CInArchive&, SFashion&);
COutArchive& operator<<(COutArchive&, const SFashion&);
CInArchive& operator>>(CInArchive&, TVecFashion&);
COutArchive& operator<<(COutArchive&, const TVecFashion&);

CInArchive& operator>>(CInArchive&, SGemstone&);
COutArchive& operator<<(COutArchive&, const SGemstone&);
CInArchive& operator>>(CInArchive&, TVecGemstone&);
COutArchive& operator<<(COutArchive&, const TVecGemstone&);

CInArchive& operator>>(CInArchive&, SStoreStream&);
COutArchive& operator<<(COutArchive&, const SStoreStream&);

CInArchive& operator>>(CInArchive&, SItemColdTime&);
COutArchive& operator<<(COutArchive&, const SItemColdTime&);

CInArchive& operator>>(CInArchive&, SAddItemMsg&);
COutArchive& operator<<(COutArchive&, const SAddItemMsg&);

CInArchive& operator>>(CInArchive&, SLoggedItem&);
COutArchive& operator<<(COutArchive&, const SLoggedItem&);

CInArchive& operator>>(CInArchive&, SGMMailTarget&);
COutArchive& operator<<(COutArchive&, const SGMMailTarget&);

CInArchive& operator>>(CInArchive&, SGMMailItem&);
COutArchive& operator<<(COutArchive&, const SGMMailItem&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SItemGenInfo&);
bool ToXML(const SItemGenInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecItemGenInfo&);
bool VectorToXML(const TVecItemGenInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SInstCount&);
bool ToXML(const SInstCount&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecInstCount&);
bool VectorToXML(const TVecInstCount&, TiXmlElement&);

bool FromXML(TiXmlElement&, SItemCount&);
bool ToXML(const SItemCount&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecItemCount&);
bool VectorToXML(const TVecItemCount&, TiXmlElement&);

bool FromXML(TiXmlElement&, SResource&);
bool ToXML(const SResource&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecResource&);
bool VectorToXML(const TVecResource&, TiXmlElement&);

bool FromXML(TiXmlElement&, RoleItemInfo&);
bool ToXML(const RoleItemInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoleItemInfo&);
bool VectorToXML(const TVecRoleItemInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SShuffleInfo&);
bool ToXML(const SShuffleInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecShuffleInfo&);
bool VectorToXML(const TVecShuffleInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SItem&);
bool ToXML(const SItem&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, SItemPtr&);
bool SuperToXML(const SItem&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecItem&);
bool VectorToXML(const TVecItem&, TiXmlElement&);

bool FromXML(TiXmlElement&, SStack&);
bool ToXML(const SStack&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecStack&);
bool VectorToXML(const TVecStack&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEquipTrump&);
bool ToXML(const SEquipTrump&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecEquipTrump&);
bool VectorToXML(const TVecEquipTrump&, TiXmlElement&);

bool FromXML(TiXmlElement&, SCitta&);
bool ToXML(const SCitta&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecCitta&);
bool VectorToXML(const TVecCitta&, TiXmlElement&);

bool FromXML(TiXmlElement&, STrump&);
bool ToXML(const STrump&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTrump&);
bool VectorToXML(const TVecTrump&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFashion&);
bool ToXML(const SFashion&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFashion&);
bool VectorToXML(const TVecFashion&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGemstone&);
bool ToXML(const SGemstone&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGemstone&);
bool VectorToXML(const TVecGemstone&, TiXmlElement&);

bool FromXML(TiXmlElement&, SStoreStream&);
bool ToXML(const SStoreStream&, TiXmlElement&);

bool FromXML(TiXmlElement&, SItemColdTime&);
bool ToXML(const SItemColdTime&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecItemColdTime&);
bool VectorToXML(const TVecItemColdTime&, TiXmlElement&);

bool FromXML(TiXmlElement&, SAddItemMsg&);
bool ToXML(const SAddItemMsg&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecAddItemMsg&);
bool VectorToXML(const TVecAddItemMsg&, TiXmlElement&);

bool FromXML(TiXmlElement&, SLoggedItem&);
bool ToXML(const SLoggedItem&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecLoggedItem&);
bool VectorToXML(const TVecLoggedItem&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGMMailTarget&);
bool ToXML(const SGMMailTarget&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGMMailTarget&);
bool VectorToXML(const TVecGMMailTarget&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGMMailItem&);
bool ToXML(const SGMMailItem&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGMMailItem&);
bool VectorToXML(const TVecGMMailItem&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NItemProt
