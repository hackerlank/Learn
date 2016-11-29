#pragma once

#define DEF_UINT32(name, id) e##name = id,
#define DEF_UINT16(name, id) e##name = id,
#define DEF_UINT8(name, id) e##name = id,
#define DEF_DOUBLE(name, id) e##name = id,
#define DEF_FLOAT(name, id) e##name = id,

enum ESystemMsgID
{
#include "Message.inc"


#if 0
	eMsg_Common,                    //通用0 - 500
	eMsg_Success = 1,               //操作成功
	eMsg_OtherErr,                  //其他错误
	eMsg_NameLengthErr,             //名字长度不符
	eMsg_NameInvalidErr,            //非法命名
	eMsg_NameDuplicateErr,          //名字已存在
	eMsg_OperateSelfErr,            //不能操作自己的
	eMsg_OperateOtherErr,           //不能操作别人的
	eMsg_CooldownErr,               //正在冷却中
	eMsg_RefreshCountErr,           //刷新次数已满
	eMsg_LevelLimitErr,             //已达到最高等级
	eMsg_MemberCountLimitErr,       //已达到最大人数上限
	eMsg_DistanceErr,               //距离太远
	eMsg_TargetNotExistErr,         //目标不存在
	eMsg_TargetOfflineErr,          //目标不在线
	eMsg_StuffNotEnoughErr,         //材料不足
	eMsg_PasswdInvalidErr,          //密码无效
	eMsg_FamilyNotExistErr,         //家族不存在
	eMsg_GuildNotExistErr,          //公会不存在
	eMsg_CampErr,                   //阵营不符
	eMsg_ClearCDSuccess,            //清除冷却成功
	eMsg_NoNationErr,				//未加入任何国家
	eMsg_AlreadyInMineErr,			//已在矿场中
	eMsg_NotInMineErr,				//不在矿场中
	eMsg_BuyMineErr,				//已购买采矿次数，无法再次购买
	eMsg_SysNotOpenLvErr,			//等级不足，功能未开放
	eMsg_SysNotOpenTaskErr,			//任务未完成，功能未开放
	eMsg_SysNotOpenErr,				//功能暂未开放
	eMsg_SysChatTooFask,			//聊天消息发送过快，等稍后发送！
	eMsg_SysChatForbid,             //被禁言了
	eMsg_SysLoginForbid,            //被禁止登陆
	eMsg_SysSvrException,			//服务器异常
	eMsg_SysChatWorldLvErr,			//世界频道发言等级不足
	eMsg_SysHonourMaxPerDay,		//超过每日最大荣誉值

	/*货币经验相关*/
	eMsg_GoldCoin = 50,				//您获得了{0}金币
	eMsg_MagicCrystal,				//您获得了{0}魔法水晶
	eMsg_GiftCoin,					//您获得了{0}礼金
	eMsg_Diamond,					//您获得了{0}钻石
	eMsg_HonorCoin,				    //您获得了{0}荣誉币
	eMsg_PVPPt,                     //您获得了{0}PVP点
	eMsg_GuildExp,                  //您的公会获得了{0}经验
	eMsg_ContributePt,              //您获得了{0}公会贡献点
	eMsg_Prestige,                  //家族增加了{0}威望
	eMsg_Wealth,                    //家族增加了{0}财富
	eMsg_OfferValue,                //您获得了{0}祭献值
	eMsg_AlchemyPt,                 //您获得了{0}圣物点
	eMsg_Exp,						//您获得了{0}点经验
	eMsg_Action,                    //您获得了{0}点行动力
	eMsg_ScoreCoin,					//您获得了{0}积分
	eMsg_GoldCoinErr = 65,			//金币不足
	eMsg_MagicCrystalErr,           //魔法水晶不足
	eMsg_GiftCoinErr,               //礼金不足
	eMsg_DiamondErr,                //钻石不足
	eMsg_HonorCoinErr,              //荣誉币不足
	eMsg_PVPPtErr,                  //PVP点不足
	eMsg_ContributePtErr,           //公会贡献点不足
	eMsg_TotalContributePtErr,      //公会总贡献点不足
	eMsg_PrestigeErr,               //家族威望不足
	eMsg_WealthErr,                 //家族财富不足
	eMsg_OfferValueErr,             //祭献值不足
	eMsg_AlchemyPtErr,              //圣物点不足
	eMsg_ExpErr,					//经验不足
	eMsg_ActionErr,                 //行动力不足
	eMsg_CoinLimitErr,              //货币已达上限
	eMsg_GoldCoinLimitErr,			//金币已达上限
	eMsg_MagicCrystalLimitErr,      //魔法水晶已达上限
	eMsg_GiftCoinLimitErr,          //礼金已达上限
	eMsg_DiamondLimitErr,           //钻石已达上限
	eMsg_HonorCoinLimitErr,         //荣誉币已达上限
	eMsg_PVPPtLimitErr,             //PVP点已达上限
	eMsg_ContributePtLimitErr,      //公会贡献点已达上限
	eMsg_TotalContributePtLimitErr, //公会总贡献点已达上限
	eMsg_PrestigeLimitErr,          //家族威望已达上限
	eMsg_WealthLimitErr,            //家族财富已达上限
	eMsg_OfferValueLimitErr,        //祭献值已达上限
	eMsg_AlchemyPtLimitErr,         //圣物点已达上限
	eMsg_ExpLimitErr,				//经验已达上限
	eMsg_ActionLimitErr,            //行动力已达上限
	eMsg_BuyActionErr,              //购买行动力次数不足
	eMsg_GainStrStone,              //您获得了{0}力量符石
	eMsg_GainAdvStone,              //您获得了{0}冒险符石
	eMsg_GainMagStone,              //您获得了{0}魔法符石
	eMsg_GainSkillExp,              //您获得了{0}点战技点

	/*道具相关*/
	eMsg_ItemUseSuccess = 100,	    //道具使用成功
	eMsg_ItemCantUseErr,            //道具：{0}无法使用
	eMsg_ItemNotExistErr,		    //道具不存在
	eMsg_ItemNotEnoughErr,		    //道具：{0}不足
	eMsg_ItemTypeErr,               //道具：{0}类型不符
	eMsg_ItemTypeStackErr,          //不可堆叠的道具类型
	eMsg_ItemTypeSellErr,           //不可出售的道具类型
	eMsg_ItemTypeAuctionErr,        //不可拍卖的道具类型
	eMsg_ItemTypeDropErr,           //不可丢弃的道具类型
	eMsg_ItemTypeOfferErr,          //不可祭献的道具类型
	eMsg_ItemBoundErr,              //道具已绑定
	eMsg_ItemExpiredErr,            //道具已过期
	eMsg_ItemLevelErr,              //使用等级不足
	eMsg_ItemJobErr,                //使用职业不符
	eMsg_ItemRaceErr,               //使用种族不符
	eMsg_ItemSupportNotEnoughErr,   //承载力不足
	eMsg_ItemMapErr,                //不能在此地图使用
	eMsg_ItemGainSelf,              //您获得了{0}
	eMsg_ItemGainOther,             //天降神运，恭喜{0}获得了{1}
	eMsg_ItemTimeOutDel,            //您的限时道具{0}到期，系统回收
	eMsg_ItemTimeOut,               //您的限时道具{0}到期，无法使用
	eMsg_ItemSpiritNotEnough,       //魔魂不足
	eMsg_ItemLearnSynthesize,       //学习{0}成功

	/*角色相关*/
	eMsg_RoleFullErr = 130,         //角色数目已满
	eMsg_MainRoleLevelNotEnoughErr, //主角等级不足
	eMsg_MainRoleLevelTooHighErr,   //主角等级太高
	eMsg_MainRoleLevelErr,          //主角等级不符
	eMsg_RoleLevelNotEnoughErr,     //角色等级不足
	eMsg_RoleLevelTooHighErr,       //角色等级太高
	eMsg_RoleLevelErr,              //角色等级不符
	eMsg_RoleNotExistErr,           //角色不存在
	eMsg_RoleJobErr,                //角色职业不符
	eMsg_RoleSexErr,                //角色性别不符
	eMsg_RoleNotDeadErr,            //角色没有死亡
	eMsg_RoleDeadErr,               //角色已经死亡
	eMsg_RoleNotGhostErr,           //角色不在灵魂状态
	eMsg_RoleGhostErr,              //角色处于灵魂状态

	/*背包相关*/
	eMsg_PackFullErr = 160,         //背包已满
	eMsg_StoreFullErr,              //仓库已满

	/*申请相关*/
	eMsg_ApplyDuplicateErr = 190,   //重复申请
	eMsg_ApplyNotExistErr,          //申请不存在
	eMsg_ApplyCountErr,             //申请数已达上限
	eMsg_ApplyQueueErr,             //申请队列已满

	/*头衔与能力相关*/
	eMsg_TitleErr = 220,            //头衔不比目标高
	eMsg_Title2Err,                 //不能超过你的头衔
	eMsg_TitleCountErr,             //超过头衔上限
	eMsg_CapacityErr,               //能力不够

	//////////////////////////////////////////////////////////////////////////

	eMsg_Mail = 500,                //邮件500 - 600
	eMsg_MailSendSuccess,           //邮件发送成功
	eMsg_MailSaveFailErr,           //邮件保存失败
	eMsg_MailAnnexErr,              //附件未领取，无法删除！

	eMsg_MailContent = 600,			//邮件内容600 - 700
	eMsg_MMallBuyT,					//商城购买
	eMsg_MMallBuy,					//亲爱的玩家，由于您的背包已满，所以此次购买的物品将以邮件形式发送，请查收!
	eMsg_MMallPresentT,				//商城赠送物品
	eMsg_MMallPresent,				//玩家{0}赠送给您的物品，请查收!
	eMsg_MAuctionBidErrT,			//拍卖行竞拍失败
	eMsg_MAuctionBidErr,			//您的竞拍出价被超过，金钱已返还，请查收!
	eMsg_MAuctionCancelT,			//拍卖品撤消
	eMsg_MAuctionCancel,			//您撤消了此次拍卖，物品已返还，请查收!
	eMsg_MAuctionBidForT,			//拍卖品竞拍获胜
	eMsg_MAuctionBidFor,			//您的竞拍成功，物品已返还，请查收!
	eMsg_MAuctionSellT,				//拍卖品售出
	eMsg_MAuctionSell,				//您的竞拍品出售成功，金钱已寄送到达，请查收!
	eMsg_MAuctionTimeOutT,			//拍卖品到期
	eMsg_MAuctionTimeOut,			//您的竞拍品无人竞拍，物品已返还，请查收!
	eMsg_MWorldBossRankAwardT,		//世界Boss排名奖励
	eMsg_MWorldBossRankAward,		//世界Boss伤害排名前几奖励
	eMsg_MVIPPresentT,				//VIP赠送
	eMsg_MVIPPresent,				//玩家{0}赠送给您VIP卡!
	eMsg_MDropT,					//掉落物品
	eMsg_MDrop,						//由于您包裹已满,获得的物品已由邮件发送!
	eMsg_MFamilyAllocT,				//家族战宝箱奖励
	eMsg_MFamilyAlloc,				//亲爱的{0}家族成员，由于您在家族战中的卓越表现，族长{1}赏赐您{2}!

	eMsg_ShopMall = 700,			//商城700 - 800
	eMsg_SMBuySucceed,				//购买成功
	eMsg_SMPresentSucceed,			//赠送成功
	eMsg_SMNotExist,				//物品不存在
	eMsg_SMNoEnough,				//库存不足
	eMsg_SMNoGive,					//不可赠送
	eMsg_SMNoUser,					//目标玩家不存在
	eMsg_SMNoCountErr,				//数量不对

	eMsg_Auction = 800,				//拍卖行800 - 900
	eMsg_AuctionAdd,				//寄售成功
	eMsg_AuctionBidFor,				//竞拍成功
	eMsg_AuctionNotExist,			//物品不存在
	eMsg_AuctionMax,				//拍卖个数已满
	eMsg_AuctionPriceErr,			//拍卖价格错误
	eMsg_AuctionTimeErr,			//时间错误
	eMsg_AuctionBidForErr,			//竞拍失败
	eMsg_AuctionBidMaxPrice,		//已是最高出价者
	eMsg_AuctionCancelErr,			//已有人竞拍，无法取消拍卖
	eMsg_AuctionSellSuccess,		//您寄售的{0}*{1}已经成功出售!
	eMsg_AuctionBuySuccess,			//您的竞拍成功，物品已通过邮件寄送，请查收!
	eMsg_AuctionTimeOut,			//您寄售的{0}*{1}已经到期，物品已返还，请查收!

	eMsg_Achieve = 900,				//成就900 - 1000
	eMsg_AchieveAward,				//领取成就奖励成功
	eMsg_AchieveNotExist,			//成就不存在
	eMsg_AchieveErrFinish,			//成就未达成

	eMsg_Alchemy = 1000,			//圣物1000 - 1100
	eMsg_AlchemySeek,				//炼金成功
	eMsg_AlchemyGain,				//拾取成功
	eMsg_AlchemySell,				//出售圣物成功
	eMsg_AlchemyMix,				//合成圣物成功
	eMsg_AlchemyWear,				//镶嵌圣物成功
	eMsg_AlchemyTakeOff,			//取下圣物成功
	eMsg_AlchemyBuy,				//购买圣物成功
	eMsg_AlchemyLock,				//锁定圣物成功
	eMsg_AlchemyErrorOpr,			//错误操作
	eMsg_AlchemyNotExit,			//圣物不存在
	eMsg_AlchemyHoleLock,			//圣物孔未开启
	eMsg_AlchemyHoleMax,			//圣物孔已达上限
	eMsg_AlchemyFull,				//圣物包裹已满
	eMsg_AlchemyOnly,				//同类型圣物只能镶嵌一个
	eMsg_AlchemyUnLock,				//解锁圣物成功

	eMsg_Cortege = 1100,			//扈从1100 - 1200
	eMsg_CortegeFresh,				//刷新成功
	eMsg_CortegeBuyVIP,				//购买VIP状态成功
	eMsg_CortegeAward,				//领取奖励成功
	eMsg_CortegeRecruit,			//招募扈从成功
	eMsg_CortegeDel,				//解散扈从成功
	eMsg_CortegeBelt,				//带上扈从成功
	eMsg_CortegeUnBelt,				//取下扈从成功
	eMsg_CortegeRandom,				//扈从培养成功
	eMsg_CortegeApply,				//运用新属性成功
	eMsg_CortegeNotExist,			//不存在
	eMsg_CortegeErrStore,			//扈从容器错误
	eMsg_CortegeErrOper,			//错误操作
	eMsg_CortegeStoreFull,			//扈从包裹已满
	eMsg_CortegeBest,				//已是最佳属性

	eMsg_Horse = 1200,				//坐骑1200 - 1300
	eMsg_HorseNotExist,				//坐骑不存在
	eMsg_HorseErrOper,				//操作错误
	eMsg_HorseErrUse,				//坐骑已被使用
	eMsg_HorseEquipMax,				//坐骑盔甲已强化最大等级
	eMsg_HorseStrenItemNotEnough,	//坐骑盔甲强化所需材料不足
	eMsg_HorseEquipStrenSuccess,	//坐骑盔甲强化成功
	eMsg_HorseAvartarSuccess,		//坐骑幻化成功
	eMsg_HorseEquipStrenFail,		//坐骑盔甲强化失败

	eMsg_Item = 1300,				//道具1300 - 1400
	eMsg_ItemTransf,				//传送成功
	eMsg_ItemTransfRecord,			//记录传送点成功
	eMsg_ItemSell,					//出售成功
	eMsg_ItemMix,					//堆叠成功
	eMsg_ItemSplit,					//拆分成功
	eMsg_ItemTidy,					//整理成功
	eMsg_ItemTakeOff,				//脱下装备成功
	eMsg_ItemWear,					//穿上装备成功
	eMsg_ItemExpandPack,			//开启{0}格包裹
	eMsg_ItemExpandDepot,			//开启{0}格仓库
	eMsg_ItemExpandAlchemy,			//开启{0}格圣物栏
	eMsg_ItemErrOper,				//操作非法
	eMsg_ItemErrSlot,				//装备位错误
	eMsg_ItemNotNeed,				//无需此操作
	eMsg_ItemMountExist,			//马棚中已存在该坐骑
	eMsg_ItemMutualEquip,			//已装备有相同属性构装
	eMsg_ItemMutual,				//已装备有相同属性宝物
	eMsg_ItemNoTakeOff,				//无法脱下
	eMsg_ItemUseDustPlane,			//位面之尘充能成功
	eMsg_ItemLeadNotEnough,			//领导力不够，无法脱下
	eMsg_ItemFashionExist,			//该时装已存在

	eMsg_PowerUp = 1400,			//铁匠铺1400 - 1500
	eMsg_PowerUpEmbed,				//镶嵌宝石成功
	eMsg_PowerUpDisEmbed,			//拆除宝石成功
	eMsg_PowerUpMakeHole,			//装备打孔成功
	eMsg_PowerUpTransfStone,		//宝石转化成功
	eMsg_PowerUpDecompose,			//装备分解成功
	eMsg_PowerUpSynthesize,			//装备合成成功
	eMsg_PowerUpApplyRandom,		//替换属性成功
	eMsg_PowerUpRandom,				//洗练成功
	eMsg_PowerUpStrengthen,			//装备强化成功
	eMsg_PowerUpStrengthenFail,		//装备强化失败
	eMsg_PowerUpNotExit,			//道具不存在
	eMsg_PowerUpHoleLock,			//宝石孔未开启
	eMsg_PowerUpHoleMax,			//道具孔已达上限
	eMsg_PowerUpTimeOut,			//装备强化时间冷却中
	eMsg_PowerUpExistStone,			//装备有宝石无法分解
	eMsg_PowerUpSameStone,			//已镶嵌相同属性宝石
	eMsg_PowerUpFormula,			//需要更高级配方
	eMsg_PowerUpNoStoneStuff,		//打孔石不足
	eMsg_PowerUpEquipLevel,			//宝物升级成功
	eMsg_PowerUpEquipMaxLevel,		//宝物已达最大等级
	eMsg_PowerUpNoDecompose,		//道具无法分解
	eMsg_PowerUpUpGradeEmbedStone,	//一键提升宝石成功

	eMsg_Task = 1500,				//任务1500 - 1600
	eMsg_TaskFinish,				//任务领取奖励成功
	eMsg_TaskGiveUp,				//任务放弃成功
	eMsg_TaskAccept,				//任务接取成功
	eMsg_TaskNotExist,				//任务不存在
	eMsg_TaskAlreadyAccept,			//任务已经接取
	eMsg_TaskErrFinish,				//任务不能完成
	eMsg_TaskErrGiveUp,				//任务不能取消
	eMsg_TaskErrAccept,				//接取任务失败
	eMsg_TaskErrRepeat,				//不能接取重复任务
	eMsg_TaskErrFull,				//已接任务数已满
	eMsg_TaskErrPrepTask,			//前置任务
	eMsg_TaskErrNoSelOptAward,		//未选取奖励
	eMsg_TaskErrMap,				//所在地图不符
	eMsg_TaskNoRepution,			//声望不够
	eMsg_TaskNoJob,					//职业限制
	eMsg_TaskNoRace,				//种族限制
	eMsg_TaskErrOther,				//其它错误

	eMsg_Title = 1600,				//称号 1600 - 1700
	eMsg_TitleUse,					//使用称号成功
	eMsg_TitleNotExist,				//称号不存在
	eMsg_TitleErrOper,				//操作错误
	eMsg_TitleErrOther,				//其他错误

	eMsg_Skill = 1700,              //技能相关1700 - 1800
	eMsg_LearnSkillSucceed,         //学习技能成功
	eMsg_ForgetSkillSucceed,        //技能遗忘成功
	eMsg_UpgradeSkillSucceed,       //升级技能成功
	eMsg_PreManaSkillInvalid,		//上一级符石技能尚未开启
	eMsg_PreManaSkillTotalLevErr,	//前置符石技能之和不到5级 
	eMsg_StrStoneNotEnough,			//力量符石数量不足
	eMsg_AdvStoneNotEnough,			//冒险符石数量不足
	eMsg_MagStoneNotEnough,			//魔法符石数量不足
	eMsg_SkillNotExistErr,          //技能不存在
	eMsg_SkillSafeAreaErr,          //安全区不能攻击
	eMsg_SkillGatherStaleErr,       //已被别人采了
	eMsg_SkillExistErr,				//技能已存在

	eMsg_Room = 1800,               //房间相关 1800 - 1900
	eMsg_KickedFromRoom,            //被踢出房间
	eMsg_LessThanDgnLevel,          //玩家等级小于已设置的副本等级
	eMsg_WaitOtherRoomPlayer,		//在副本中等待其他玩家
	eMsg_RoomIsNotWaiting,			//游戏已经开始，无法加入
	eMsg_InvalidRoomPassword,		//密码不对，无法加入
	eMsg_FullRoom,					//房间人数已满，无法加入
	eMsg_InvalidPlayerLevel,		//您的等级不足，无法加入
	eMsg_PleasePassPrevDgn,			//请先通过普通难度，才能进入噩梦难度
	eMsg_FYZJJoinErr1 = 1810,		//今日已挑战过此房间
	eMsg_FYZJJoinErr2 = 1811,		//战斗已开启，无法加入
	eMsg_RoomLevelLimit = 1812,		//等级不符合房间设置要求
	eMsg_RoomSwordLimit = 1813,		//战力不符合房间设置要求

	eMsg_Building = 1900,              //建筑系统 1900 - 2000
	eMsg_BuildingCollectCountErr,      //征收次数已达上限
	eMsg_BuildingRelivingErr,          //还在复活中
	eMsg_BuildingExchangeErr,          //道具无法兑换或购买
	eMsg_BuildingItemNumErr,           //道具数量错误
	eMsg_BuildingLevelErr,             //等级不足
	eMsg_BuildingTrainingErr,          //试炼中
	eMsg_BuildingSweepingErr,          //扫荡中
	eMsg_BuildingNotTrainingErr,       //不在试炼
	eMsg_BuildingNotSweepingErr,       //不在扫荡
	eMsg_BuildingUnsealErr,            //未开封
	eMsg_BuildingTrainingCountErr,     //试炼次数已满
	eMsg_BuildingSpeedExistErr,        //已经扫荡加速了
	eMsg_BuildingMercenRecruitDupErr,  //此佣兵已被招募
	eMsg_BuildingTrainingTimeErr,      //试炼时间错误
	eMsg_BuildingHeroTraining,		   //此英雄已在试炼中
	eMsg_BuildingTechSuccess,			//成功
	eMsg_BuildingTechFailed,			//失败
	eMsg_BuildingTechCfgErr,			//配置错误
	eMsg_BuildingTechAlreadyOpen,		//已开启
	eMsg_BuildingTechItemMaxLv,			//项最大等级
	eMsg_BuildingTechSmallMaxLv,		//小最大等级
	eMsg_BuildingTechBigMaxLv,			//大最大等级
	eMsg_BuildingTechPreItemErr,		//未达成前置条件
	eMsg_BuildingTechSmallOpenErr,		//无法进阶
	eMsg_BuildingTechBigOpenErr,		//无法进行大进阶
	eMsg_BuildingTechCoinErr,			//钱不足
	eMsg_BuildingTechNoAvilItem,		//没有能开启的项
	eMsg_BuildingTech_RoleMaxLv,		//超过自身等级

	eMsg_Family = 2000,             //家族系统 2000 - 2100
	eMsg_FamilyLevel,               //您的家族升到{0}级
	eMsg_FamilyExistErr,            //已经存在家族
	eMsg_FamilyTargetNotInErr,      //目标不在家族中
	eMsg_FamilyExceedFamilyLevelErr,//超过家族的最大等级
	eMsg_FamilyNotPatriarchErr,     //不是族长
	eMsg_FamilyPatriarchErr,        //你是族长
	eMsg_FamilyInDismissingErr,     //正在解散中
	eMsg_FamilyNotInDismissingErr,  //不在解散中
	eMsg_FamilyFeastErr,            //没有宴会可以参加
	eMsg_FamilyFeastDuplicateErr,   //宴会已经开启了
	eMsg_FamilyFeastSignErr,        //已经参加过宴会了
	eMsg_FamilyNoFeastSignErr,      //没有一个人签到
	eMsg_FamilyFightStateErr,       //家族战状态错误
	eMsg_FamilyNotInFightErr,       //不在家族战
	eMsg_FamilyFightUnitDuplicateErr,//战斗单位已经存在
	eMsg_FamilyFightUnitNotExistErr,//战斗单位不存在
	eMsg_FamilyFightUnitFullErr,    //战斗单位已数目达上限
	eMsg_FamilyNoticeLengthErr,     //家族公告长度不符
	eMsg_FamilyMessageLengthErr,    //家族留言长度不符
	eMsg_FamilyApplyRefused,		//家族申请被拒绝
	eMsg_FamilyHasPatriarchErr,		//家族族长仍然有效
	eMsg_FamilyFeastSucceed,		//参加宴会成功
	eMsg_FamilyDiamiss,				//家族财富长期欠费,自动解散!
	eMsg_FamilyMaxInspire,			//家族战激励次数已达上限!
	eMsg_FamilyFightAward,			//家族战奖励已经领取!
	eMsg_FamilyFightAwardErr,		//家族战奖励宝箱数量不足!
	eMsg_FamilyFightWinNone,		//{0}家族在{1}组的战斗中取得了胜利
	eMsg_FamilyFightWin,		    //{0}家族在{1}组的战斗中战胜了{2}家族
	eMsg_FamilyFightWinRoundNone,	//{0}家族在第{1}轮竞技中取得了胜利
	eMsg_FamilyFightWinRound,		//{0}家族在第{1}轮竞技中击败了{2}家族

	eMsg_Guild = 2100,              //公会系统 2100 -2200
	eMsg_GuildLevel,                //您的公会升到{0}级
	eMsg_GuildExistErr,             //已经存在公会
	eMsg_GuildTargetNotInErr,       //目标不在公会中
	eMsg_GuildExceedGuildLevelErr,  //超过公会的最大等级
	eMsg_GuildNotChairmanErr,       //不是会长
	eMsg_GuildChairmanErr,          //你是会长
	eMsg_GuildInDismissingErr,      //正在解散中
	eMsg_GuildNotInDismissingErr,   //不在解散中
	eMsg_GuildGoodsNotExistErr,     //商品不存在
	eMsg_GuildSkillNotExistErr,     //技能不存在
	eMsg_GuildLevelErr,             //公会等级不足
	eMsg_GuildNoticeLengthErr,      //公会公告长度不符
	eMsg_GuildApplyRefused,			//公会申请被拒绝
	eMsg_GuildHasChairmanErr,		//公会会长仍然有效
	eMsg_GuildContrib,				//成功公会捐献,获得{0}贡献点

	eMsg_Friend = 2200,             //好友 2200 - 2300
	eMsg_FriendExistErr,            //目标已在你的好友列表
	eMsg_FriendExist2Err,           //你已在目标的好友列表
	eMsg_FriendNumLimitErr,         //好友数目已达上限
	eMsg_FriendNumLimit2Err,        //目标好友数目已达上限
	eMsg_FriendRefuseErr,           //对方拒绝了好友请求
	eMsg_FriendGroupIDErr,          //分组ID错误
	eMsg_FriendAddFriend,           //成功添加{0}成为您的好友
	eMsg_FriendAddBlack,            //成功将{0}列入黑名单
	eMsg_FriendExistBlack,          //已在黑名单中
	eMsg_FriendRemoveFriend,        //成功将{0}从好友列表中移除
	eMsg_FriendRemoveBlack,         //成功将{0}移出黑名单
	eMsg_FriendInvited,				//好友邀请已发出，请耐心等待！
	eMsg_FriendExistTarBlack,		//你已被对方加入黑名单

	eMsg_Misc = 2300,               //杂项 2300 - 2400
	eMsg_MiscSweepingErr,           //扫荡中
	eMsg_MiscNotSweepingErr,        //不在扫荡中
	eMsg_MiscSweepingSeepUpErr,     //扫荡加速中
	eMsg_MiscWorldBossHurtAward,	//获得对Boss造成{0}伤害奖励
	eMsg_MiscWorldBossHurtRankAward,//世界Boss伤害前几名奖励
	eMsg_MiscDungeonNoIncome,		//副本无收益
	eMsg_MiscMultiPVPNoIncome,		//多人竞技场无收益
	eMsg_MiscRoleLevelNotEnoughTips,//英雄等级不足，需要等级达到{0}级

	eMsg_NPC = 2400,                //NPC 2400 - 2500
	eMsg_NPCTalkScriptFailErr,      //NPC对话脚本执行失败

	eMsg_Mercen = 2500,             //佣兵 2500 - 2600
	eMsg_MercenNotExistErr,         //佣兵不存在
	eMsg_MercenLevelErr,            //佣兵等级不足
	eMsg_MercenCampFullErr,         //兵营已满
	eMsg_MercenCantMoveErr,         //不能移动佣兵
	eMsg_MercenUpdateErr,           //佣兵升级错误
	eMsg_MercenTechNotExistErr,     //兵营科技不存在
	eMsg_MercenTechExistErr,        //兵营科技已存在
	eMsg_MercenNeedTechErr,         //需要的兵营科技不存在
	eMsg_MercenNeedTypeErr,         //需要的兵种不存在
	eMsg_MercenPreTechErr,          //前置科技未开启
	eMsg_MercenLeadPointErr,        //领导力不足
	eMsg_MercenRaceErr,             //种族错误
	eMsg_MercenRecruitSucceed,		//招募佣兵成功
	eMsg_MercenFireSucceed,			//解雇佣兵成功
	eMsg_MercenUpdateSucceed,		//佣兵升阶成功
	eMsg_MercenTechSucceed,			//开启佣兵科技成功
	eMsg_MercenAddToForm,			//{0}加入队伍
	eMsg_MercenNoFire,				//先脱下佣兵装备才能解雇佣兵

	eMsg_VIP = 2600,				//VIP 2600 - 2700
	eMsg_BuyVIPSuccess,				//VIP购买成功
	eMsg_AwardVIPSuccess,			//领取VIP礼包成功
	eMsg_VIPNotActive,		        //VIP未激活
	eMsg_VIPLevelErr,               //VIP等级不够
	eMsg_VIPPresent,                //玩家{0}赠送给您VIP卡
	eMsg_VIPNoBag,					//VIP礼包已领取
	eMsg_VIPNoNewBag = 2608,		//黄钻新手礼包已领取
	eMsg_NoYellowDiamondBag,		//黄钻每日礼包已领取
	eMsg_VIPNewBag,					//领取黄钻新手礼包成功
	eMsg_YellowDiamondBag,			//领取黄钻每日礼包成功
	eMsg_UseVIPItem,				//玩家使用VIP体验卡提示

	eMsg_BuyPlat = 2800,			//聚宝盆 2700 - 2800
	eMsg_BuyPlatSuccess,			//聚宝盆成功
	eMsg_BuyPlatNoCount,	        //聚宝盆次数已用完

	eMsg_OtherHeroMapHook = 2901,	//已有英雄正在挂机，无法再次挂机
	eMsg_MapHookFightErr,			//此英雄正在挂机中，无法进入战斗
	eMsg_MapHookFuncLimit,			//英雄正在挂机中，无法进行此操作
	eMsg_CannotUseHoldFunc,			//已有英雄正在使用挂机功能，无法再次挂机

	eMsg_Activity = 3000,          //活动相关 3000-3100
	eMsg_AwardGotted,              //已领取
	eMsg_AwardGotLimit,            //已领取到上限
	eMsg_AwardNotGot,              //有奖励未领取
	eMsg_AwardNotExist,            //奖品不存在
	eMsg_AwardTimeLack,            //未达到领奖时间

	eMsg_EscapeWorldWarCD = 3026,	//城战逃跑者一定时间后才能再次进入

	/*宝藏图相关*/
	eMsg_Treasure_Success = 3101,	//挖宝成功
	eMsg_Treasure_Fail,				//挖宝失败
	eMsg_Treasure_RangeErr,			//挖掘区域不对
	eMsg_Treasure_BuyInfoSuccess,	//购买信息成功

	eMsg_Fashion = 3200,			//时装3200 - 3300
	eMsg_FashionSave,				//时装形象保存成功
	eMsg_FashionCharge,				//魔龙之心充能成功
	eMsg_FashionUseSkill,			//魔龙之心技能装备成功
	eMsg_FashionActiveSkill,		//魔龙之心技能激活成功
	eMsg_FashionNotExist,			//时装未获得
	eMsg_FashionErrOper,			//操作错误
	eMsg_FashionErrUse,				//时装已被使用
	eMsg_FashionDragonMaxLevel,		//魔龙之心已达最大等级
	eMsg_FashionClothNotEnough,		//时装数量不足
	eMsg_FashionWingNotEnough,		//翅膀数量不足
	eMsg_FashionChargeNotExist,		//圣者遗物不足
	eMsg_FashionSkillNotExist,		//魔龙之心技能不存在
	eMsg_FashionSkillLearnErr,		//魔龙之心技能激活失败
	eMsg_FashionDragonLevelErr,		//魔龙之心等级不足

    /*礼包相关*/
    eMsg_GiftGetedSuccess = 3301,   // 礼包领取成功
    eMsg_GiftJobErr,                // 礼包职业不符
    eMsg_GiftPackErr,               // 包裹空间不足
    eMsg_GiftGeted,                 // 该礼包已领取

	eMsg_End
#endif
};

#undef DEF_UINT32
#undef DEF_UINT16
#undef DEF_UINT8
#undef DEF_DOUBLE
#undef DEF_FLOAT

