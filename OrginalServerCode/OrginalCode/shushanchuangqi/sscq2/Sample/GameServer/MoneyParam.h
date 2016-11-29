#pragma once

//#include "GoldpieceCFG.h"

enum EMoneyParamID
{
	eMoneyParamNone,
	ePackExternCost = 3, //包裹扩充价格
	eDeportExternCost = 4, //仓库扩充价格
	eCortegeVipstateCost = 5, //提振声望
	eCortegePackfreshCost = 6, //钻石刷新
	eAlchemyPackExternCost = 7, //圣物包裹扩充价格
	eAuctionCharge = 8, //拍卖行交易手续费(万分比)
	eTaskChurchCost = 9, //刷新悬赏任务花费
	eGoldCoinBuyNeedDiamond = 10, //魔币购买需要钻石
	eSweepingSpeedUpNeedDiamond = 11, //扫荡加速需要钻石参数
	eAddEncourageBuff = 12, //世界boss钻石参数
	eColonyMailCost = 13, //群体邮件花费
	ePVPClearCDDiamond = 14, //清除单人竞技CD的钻石参数
	eClearEquipStrenthCD = 15, //清除强化冷却时间
	eClearLibraryCD = 16, //清除图书馆冷却时间
	eClearCongressCD = 17, //清除议会冷却时间
	eTrainingPerCost = 18, //试练塔钻石试炼花费
	eTrainingPerSpeedCost = 19, //试练塔钻石加速花费
	eWeekVIPCost = 20, //VIP周卡
	eMonthVIPCost = 21, //VIP月卡
	eHalfYearVIPCost = 22, //VIP半年卡
	eBuyDailyMineCount = 23, //购买日常挖矿次数
	eBuyTempleCount = 24, //刷新神殿次数
	eRandomPropcost = 25, //洗练花费
	eGuildLeaveCost = 26, //清除公会离开CD
	eReliveInWorldBossDgn = 27, //在世界boss副本中从灵魂状态复活
	eReliveInTowerDgn = 28, //在诅咒之塔中从灵魂状态复活
	eBuyAction = 29, //购买行动力价格
	eClearGuildUpgradeCD = 30, //清除公会升级冷却价格
	eClearFamilyUpgradeCD = 31, //清除家族升级冷却价格
	eResetManaStone = 32, //重置符石所需消耗
	eMoneyChangeGuildName = 33, //修改公会名
	eMoneyFamilyFightInspire = 34, //激励
	eTreasureDigQuick = 35, //直接挖取宝藏图
	eFinishChurchTask = 36, //立刻完成领主任务
	eClearMineBattleSuperCD = 37, //清除矿战中的超强效果CD
	eGoldParamEnd
};

//钻石参数
class CMoneyParamMgr
{
public:
	static bool Init();
	//static const SGoldpieceCFG* GetMoneyParam(EMoneyParamID eParamID);

private:
	//static SGoldpieceCFG _arID2GoldPiece[];
};
