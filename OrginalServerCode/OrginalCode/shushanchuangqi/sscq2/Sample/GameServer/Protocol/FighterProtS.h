#pragma once
#include "FighterProtSvr.h"

using namespace NFighterProt;

class CFighterProtS : public CFighterProtSvr
{
public:
	//接收：散仙装备技能
	virtual bool OnRecv_FighterSkillEquipTo(
		UINT64 qwInstID, //散仙唯一ID
		UINT32 dwSkillID, //技能ID
		INT32 iSlot, //技能槽 -1表示卸下技能
		shared_func<SFighterSkillEquipToAck>& fnAck //返回回调函数
	);
	//接收：散仙技能升级
	virtual bool OnRecv_FighterSkillLevelUp(
		UINT64 qwInstID, //散仙唯一ID
		UINT32 dwSkillID, //技能ID
		shared_func<SFighterSkillLevelUpAck>& fnAck //返回回调函数
	);

	//接收：散仙被动技能升级
	virtual bool OnRecv_FighterPassiveSkillLevelUp(
		UINT64 qwInstID, //散仙唯一ID
		UINT32 dwSkillID, //技能ID
		shared_func<SFighterPassiveSkillLevelUpAck>& fnAck //返回回调函数
	);

	//接收：获取客栈信息
	virtual bool OnRecv_GetTavernInfo(
		shared_func<SGetTavernInfoAck>& fnAck //返回回调函数
	);

	//接收：求签
	virtual bool OnRecv_Draw(
		EDrawType eType, //求签类型
		shared_func<SDrawAck>& fnAck //返回回调函数
	);

	//接收：招募
	virtual bool OnRecv_FighterRecruit(
		UINT16 wFighterID, //将ID
		shared_func<SFighterRecruitAck>& fnAck //返回回调函数
	);

	//接收：淬体升级
	virtual bool OnRecv_CuiTiUpgrade(
		UINT64 qwInstID, //将唯一ID
		ECuiTiType eCuiTiType, //淬体类型
        UINT8 byTimes, //次数
		shared_func<SCuiTiUpgradeAck>& fnAck //返回回调函数
	);
	//接收：散仙淬体全体(六种)升级一次
	virtual bool OnRecv_CuiTiAllUpgrade(
		UINT64 qwInstID, //将唯一ID
		shared_func<SCuiTiAllUpgradeAck>& fnAck //返回回调函数
	);
	//接收：转移
	virtual bool OnRecv_FighterShift(
		UINT64 qwInstIDSrc, //将唯一ID
		UINT64 qwInstIDDst, //将唯一ID
		shared_func<SFighterShiftAck>& fnAck //返回回调函数
	);
	//接收：同步等级
	virtual bool OnRecv_FighterSyncLevel(
		UINT64 qwInstID, //将唯一ID
		UINT8 byGoalLvl, //同步的目标等级
		shared_func<SFighterSyncLevelAck>& fnAck //返回回调函数
	);

	//接收：渡劫升级
	virtual bool OnRecv_UpgradeDujie(
		UINT64 qwInstID, //将唯一ID
		UINT8 byOneKey, //是否一键(是>0 否=0)
		shared_func<SUpgradeDujieAck>& fnAck //返回回调函数
	);

    //接收：请求散仙心法
	virtual bool OnRecv_ReqFighterXinFaInfo(
		UINT64 qwInstID, //散仙唯一ID
		shared_func<SReqFighterXinFaInfoAck>& fnAck //返回回调函数
	);
    //接收：散仙学习心法
	virtual bool OnRecv_FighterActiveXinFa(
		UINT64 qwInstID, //散仙唯一ID
		UINT32 dwXinFaID, //心法ID
		shared_func<SFighterActiveXinFaAck>& fnAck //返回回调函数
	);
	//接收：散仙心法升级
	virtual bool OnRecv_FighterXinFaLevelUp(
		UINT64 qwInstID, //散仙唯一ID
		UINT32 dwXinFaID, //心法ID
		shared_func<SFighterXinFaLevelUpAck>& fnAck //返回回调函数
	);
    //接收：散仙心法散功
	virtual bool OnRecv_FighterXinFaDisperse(
		UINT64 qwInstID, //散仙唯一ID
		UINT32 dwXinFaID, //心法ID
		shared_func<SFighterXinFaDisperseAck>& fnAck //返回回调函数
	);
	//接收：获取玩家的所有散仙组合
	virtual bool OnRecv_GetAllFighterCombination(
		shared_func<SGetAllFighterCombinationAck>& fnAck //返回回调函数
	);
	//接收：激活散仙组合
	virtual bool OnRecv_ActiveCombination(
		UINT8 byGroupID, //散仙组合ID
		shared_func<SActiveCombinationAck>& fnAck //返回回调函数
	);
	//接收：升级散仙组合
	virtual bool OnRecv_UpgradeCombination(
		UINT8 byGroupID, //散仙组合ID
		UINT8 byOneKey, //是否一键(是>0 否=0)
		shared_func<SUpgradeCombinationAck>& fnAck //返回回调函数
	);
	//接收：装备散仙组合技能(连携技)
	virtual bool OnRecv_EquipToCombinationSkill(
        UINT8 byGroupID, //散仙组合ID
		UINT8 byType, //1出战在阵型 2出战在守卫峨眉
		shared_func<SEquipToCombinationSkillAck>& fnAck //返回回调函数
	);

	//接收：散仙散功
	virtual bool OnRecv_FighterDismiss(
		UINT64 qwInstID, //散仙唯一ID
		shared_func<SFighterDismissAck>& fnAck //返回回调函数
	);

    //接收：获取购买散仙信息
	virtual bool OnRecv_GetFighterBuyInfo(
		shared_func<SGetFighterBuyInfoAck>& fnAck //返回回调函数
	);

	//接收：散仙购买
	virtual bool OnRecv_FighterBuy(
		UINT16 wFighterID, //将ID
		shared_func<SFighterBuyAck>& fnAck //返回回调函数
	);

private:
};
