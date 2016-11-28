/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    FighterProt.h
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "FighterProt.h"

namespace NFighterProt
{

//协议类：道具相关协议
class CFighterProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：装备技能返回
	bool Send_SkillUpNotify( //发送给当前协议处理的客户端
		UINT32 dwSkillID, //技能ID
		INT32 iSlot //技能槽 -1表示卸下技能
	);
	bool SendClt_SkillUpNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwSkillID, //技能ID
		INT32 iSlot //技能槽 -1表示卸下技能
	);
	std::string& BuildPkg_SkillUpNotify( //只组包不发送
		UINT32 dwSkillID, //技能ID
		INT32 iSlot //技能槽 -1表示卸下技能
	);

	//发送：增加新技能
	bool Send_SkillAddNotify( //发送给当前协议处理的客户端
		UINT32 dwSkillID //技能ID
	);
	bool SendClt_SkillAddNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwSkillID //技能ID
	);
	std::string& BuildPkg_SkillAddNotify( //只组包不发送
		UINT32 dwSkillID //技能ID
	);

	//发送：散仙血脉激活
	bool Send_InstinctActiveNotify( //发送给当前协议处理的客户端
		UINT64 qwInstID, //散仙唯一ID
		const TVecUINT16& vecInstinctIDRandom, //血脉随机结果
		const TVecUINT16& vecInstinctIDRet //血脉最终结果
	);
	bool SendClt_InstinctActiveNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwInstID, //散仙唯一ID
		const TVecUINT16& vecInstinctIDRandom, //血脉随机结果
		const TVecUINT16& vecInstinctIDRet //血脉最终结果
	);
	std::string& BuildPkg_InstinctActiveNotify( //只组包不发送
		UINT64 qwInstID, //散仙唯一ID
		const TVecUINT16& vecInstinctIDRandom, //血脉随机结果
		const TVecUINT16& vecInstinctIDRet //血脉最终结果
	);

	//发送：招募散仙成功的弹框通知
	bool Send_RecruitSuccNotify( //发送给当前协议处理的客户端
		UINT16 wFighterID //散仙ID
	);
	bool SendClt_RecruitSuccNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wFighterID //散仙ID
	);
	std::string& BuildPkg_RecruitSuccNotify( //只组包不发送
		UINT16 wFighterID //散仙ID
	);

	//发送：阵型位置变更
	bool Send_FighterPosNotify( //发送给当前协议处理的客户端
		const TVecFighterPos& vecPos //阵型位置
	);
	bool SendClt_FighterPosNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecFighterPos& vecPos //阵型位置
	);
	std::string& BuildPkg_FighterPosNotify( //只组包不发送
		const TVecFighterPos& vecPos //阵型位置
	);

	//发送：更新散仙的渡劫数据
	bool Send_UpdateDujieValue( //发送给当前协议处理的客户端
		UINT64 qwInstID, //将唯一ID
		UINT8 byDujieLevel, //当前渡劫等级
		UINT32 dwDujieExp, //当前渡劫经验
		UINT32 dwSpiritPower //元神力
	);
	bool SendClt_UpdateDujieValue(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwInstID, //将唯一ID
		UINT8 byDujieLevel, //当前渡劫等级
		UINT32 dwDujieExp, //当前渡劫经验
		UINT32 dwSpiritPower //元神力
	);
	std::string& BuildPkg_UpdateDujieValue( //只组包不发送
		UINT64 qwInstID, //将唯一ID
		UINT8 byDujieLevel, //当前渡劫等级
		UINT32 dwDujieExp, //当前渡劫经验
		UINT32 dwSpiritPower //元神力
	);

	//发送：心法数据更新通知
	bool Send_XinFaNotify( //发送给当前协议处理的客户端
		UINT64 qwInstID, //将唯一ID
		UINT32 dwXinFaID, //心法ID
		UINT8 byXinFaLvl, //心法等级
		INT32 iSlot //心法槽 -1表示心法没装备
	);
	bool SendClt_XinFaNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwInstID, //将唯一ID
		UINT32 dwXinFaID, //心法ID
		UINT8 byXinFaLvl, //心法等级
		INT32 iSlot //心法槽 -1表示心法没装备
	);
	std::string& BuildPkg_XinFaNotify( //只组包不发送
		UINT64 qwInstID, //将唯一ID
		UINT32 dwXinFaID, //心法ID
		UINT8 byXinFaLvl, //心法等级
		INT32 iSlot //心法槽 -1表示心法没装备
	);

	//发送：散仙心法主卷等级满了添加一个天赋技能更新通知
	bool Send_AddTalentSkillNotify( //发送给当前协议处理的客户端
		UINT64 qwInstID, //将唯一ID
		UINT8 byIdx, //技能槽idx
		UINT32 dwSkillID //技能ID
	);
	bool SendClt_AddTalentSkillNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwInstID, //将唯一ID
		UINT8 byIdx, //技能槽idx
		UINT32 dwSkillID //技能ID
	);
	std::string& BuildPkg_AddTalentSkillNotify( //只组包不发送
		UINT64 qwInstID, //将唯一ID
		UINT8 byIdx, //技能槽idx
		UINT32 dwSkillID //技能ID
	);

	//发送：散仙技能列表返回
	bool Send_SkillListNotify( //发送给当前协议处理的客户端
		UINT64 qwInstID, //将唯一ID
		const TVecFighterSkill& VecFighterSkill //技能ID
	);
	bool SendClt_SkillListNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwInstID, //将唯一ID
		const TVecFighterSkill& VecFighterSkill //技能ID
	);
	std::string& BuildPkg_SkillListNotify( //只组包不发送
		UINT64 qwInstID, //将唯一ID
		const TVecFighterSkill& VecFighterSkill //技能ID
	);

	//发送：玩家的散仙组合列表返回
	bool Send_FighterCombinationNotify( //发送给当前协议处理的客户端
		const TVecFighterCombination& VecCombination //散仙组合列表
	);
	bool SendClt_FighterCombinationNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecFighterCombination& VecCombination //散仙组合列表
	);
	std::string& BuildPkg_FighterCombinationNotify( //只组包不发送
		const TVecFighterCombination& VecCombination //散仙组合列表
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SFighterSkillEquipToAck : public CClientFuncAck
	{
		ESkillResult eResult; //结果
		TVecFightSkillInfo vActiveSkill; //装备的主动技能

		SFighterSkillEquipToAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：散仙装备主动技能
	virtual bool OnRecv_FighterSkillEquipTo(
		UINT64 qwInstID, //散仙唯一ID
		UINT32 dwSkillID, //技能ID
		INT32 iSlot, //技能槽 -1表示卸下技能
		shared_func<SFighterSkillEquipToAck>& fnAck //返回回调函数
	) = 0;

	struct SFighterSkillLevelUpAck : public CClientFuncAck
	{
		ESkillResult eResult; //结果

		SFighterSkillLevelUpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：散仙技能升级
	virtual bool OnRecv_FighterSkillLevelUp(
		UINT64 qwInstID, //散仙唯一ID
		UINT32 dwSkillID, //技能ID
		shared_func<SFighterSkillLevelUpAck>& fnAck //返回回调函数
	) = 0;

	struct SFighterPassiveSkillLevelUpAck : public CClientFuncAck
	{
		ESkillResult eResult; //结果

		SFighterPassiveSkillLevelUpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：散仙被动技能升级
	virtual bool OnRecv_FighterPassiveSkillLevelUp(
		UINT64 qwInstID, //散仙唯一ID
		UINT32 dwSkillID, //技能ID
		shared_func<SFighterPassiveSkillLevelUpAck>& fnAck //返回回调函数
	) = 0;

	struct SGetTavernInfoAck : public CClientFuncAck
	{
		UINT32 dwDrawCount; //免费求签次数
		TVecTavernInfo vecTavernInfo; //具体客栈信息

		SGetTavernInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取客栈信息
	virtual bool OnRecv_GetTavernInfo(
		shared_func<SGetTavernInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SDrawAck : public CClientFuncAck
	{
		EDrawResult eResult; //返回结果
		NItemProt::TVecItemCount vecItemGet; //求签获得物品

		SDrawAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：求签
	virtual bool OnRecv_Draw(
		EDrawType eType, //求签类型
		shared_func<SDrawAck>& fnAck //返回回调函数
	) = 0;

	struct SFighterRecruitAck : public CClientFuncAck
	{
		ERecruitResult eResult; //结果

		SFighterRecruitAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：招募
	virtual bool OnRecv_FighterRecruit(
		UINT16 wFighterID, //将ID
		shared_func<SFighterRecruitAck>& fnAck //返回回调函数
	) = 0;

	struct SCuiTiUpgradeAck : public CClientFuncAck
	{
		ECuiTiResult eResult; //结果
		UINT8 byLevel; //当前淬体等级

		SCuiTiUpgradeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：淬体升级
	virtual bool OnRecv_CuiTiUpgrade(
		UINT64 qwInstID, //将唯一ID
		ECuiTiType eCuiTiType, //淬体类型
		UINT8 byTimes, //次数
		shared_func<SCuiTiUpgradeAck>& fnAck //返回回调函数
	) = 0;

	struct SCuiTiAllUpgradeAck : public CClientFuncAck
	{
		ECuiTiResult eResult; //结果
		TVecUINT8 vecLevel; //当前全体淬体等级(按炼皮/通筋/强肌/锻骨/活络/洗髓顺序)

		SCuiTiAllUpgradeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：散仙淬体全体(六种)升级一次
	virtual bool OnRecv_CuiTiAllUpgrade(
		UINT64 qwInstID, //将唯一ID
		shared_func<SCuiTiAllUpgradeAck>& fnAck //返回回调函数
	) = 0;

	struct SFighterShiftAck : public CClientFuncAck
	{
		EShiftResult eResult; //结果

		SFighterShiftAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：转移
	virtual bool OnRecv_FighterShift(
		UINT64 qwInstIDSrc, //将唯一ID
		UINT64 qwInstIDDst, //将唯一ID
		shared_func<SFighterShiftAck>& fnAck //返回回调函数
	) = 0;

	struct SFighterSyncLevelAck : public CClientFuncAck
	{
		ESyncLevelResult eResult; //结果

		SFighterSyncLevelAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：同步等级
	virtual bool OnRecv_FighterSyncLevel(
		UINT64 qwInstID, //将唯一ID
		UINT8 byGoalLvl, //同步的目标等级
		shared_func<SFighterSyncLevelAck>& fnAck //返回回调函数
	) = 0;

	struct SUpgradeDujieAck : public CClientFuncAck
	{
		EDujieResult eResult; //结果
		UINT64 qwInstID; //将唯一ID

		SUpgradeDujieAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：渡劫升级
	virtual bool OnRecv_UpgradeDujie(
		UINT64 qwInstID, //将唯一ID
		UINT8 byOneKey, //是否一键(是>0 否=0)
		shared_func<SUpgradeDujieAck>& fnAck //返回回调函数
	) = 0;

	struct SReqFighterXinFaInfoAck : public CClientFuncAck
	{
		TVecXinFaInfo vecFighterXinFa; //散仙已经学会的心法信息

		SReqFighterXinFaInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求散仙心法
	virtual bool OnRecv_ReqFighterXinFaInfo(
		UINT64 qwInstID, //散仙唯一ID
		shared_func<SReqFighterXinFaInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SFighterActiveXinFaAck : public CClientFuncAck
	{
		EXinFaResult eResult; //结果

		SFighterActiveXinFaAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：散仙学习心法
	virtual bool OnRecv_FighterActiveXinFa(
		UINT64 qwInstID, //散仙唯一ID
		UINT32 dwXinFaID, //心法ID
		shared_func<SFighterActiveXinFaAck>& fnAck //返回回调函数
	) = 0;

	struct SFighterXinFaLevelUpAck : public CClientFuncAck
	{
		EXinFaResult eResult; //结果

		SFighterXinFaLevelUpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：散仙心法升级
	virtual bool OnRecv_FighterXinFaLevelUp(
		UINT64 qwInstID, //散仙唯一ID
		UINT32 dwXinFaID, //心法ID
		shared_func<SFighterXinFaLevelUpAck>& fnAck //返回回调函数
	) = 0;

	struct SFighterXinFaDisperseAck : public CClientFuncAck
	{
		EXinFaResult eResult; //结果

		SFighterXinFaDisperseAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：散仙心法散功
	virtual bool OnRecv_FighterXinFaDisperse(
		UINT64 qwInstID, //散仙唯一ID
		UINT32 dwXinFaID, //心法ID
		shared_func<SFighterXinFaDisperseAck>& fnAck //返回回调函数
	) = 0;

	struct SGetAllFighterCombinationAck : public CClientFuncAck
	{
		TVecFighterCombination vecCombinationInfo; //玩家的散仙组合信息

		SGetAllFighterCombinationAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取玩家的所有散仙组合
	virtual bool OnRecv_GetAllFighterCombination(
		shared_func<SGetAllFighterCombinationAck>& fnAck //返回回调函数
	) = 0;

	struct SActiveCombinationAck : public CClientFuncAck
	{
		ECombinationResult eResult; //结果

		SActiveCombinationAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：激活散仙组合
	virtual bool OnRecv_ActiveCombination(
		UINT8 byGroupID, //散仙组合ID
		shared_func<SActiveCombinationAck>& fnAck //返回回调函数
	) = 0;

	struct SUpgradeCombinationAck : public CClientFuncAck
	{
		SFighterCombination oCombinationInfo; //当前升级的散仙组合信息
		ECombinationResult eResult; //结果

		SUpgradeCombinationAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：升级散仙组合
	virtual bool OnRecv_UpgradeCombination(
		UINT8 byGroupID, //散仙组合ID
		UINT8 byOneKey, //是否一键(是>0 否=0)
		shared_func<SUpgradeCombinationAck>& fnAck //返回回调函数
	) = 0;

	struct SEquipToCombinationSkillAck : public CClientFuncAck
	{
		ECombinationResult eResult; //结果

		SEquipToCombinationSkillAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：装备散仙组合技能(连携技)
	virtual bool OnRecv_EquipToCombinationSkill(
		UINT8 byGroupID, //散仙组合ID
		UINT8 byType, //1出战在阵型 2出战在守卫峨眉
		shared_func<SEquipToCombinationSkillAck>& fnAck //返回回调函数
	) = 0;

	struct SFighterDismissAck : public CClientFuncAck
	{
		EDismissResult eResult; //结果

		SFighterDismissAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：散仙散功
	virtual bool OnRecv_FighterDismiss(
		UINT64 qwInstID, //散仙唯一ID
		shared_func<SFighterDismissAck>& fnAck //返回回调函数
	) = 0;

	struct SGetFighterBuyInfoAck : public CClientFuncAck
	{
		TVecFighterBuyInfo vecFighterBuyInfo; //购买散仙信息

		SGetFighterBuyInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取购买散仙信息
	virtual bool OnRecv_GetFighterBuyInfo(
		shared_func<SGetFighterBuyInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SFighterBuyAck : public CClientFuncAck
	{
		EFighterBuyResult eResult; //结果

		SFighterBuyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：散仙购买
	virtual bool OnRecv_FighterBuy(
		UINT16 wFighterID, //将ID
		shared_func<SFighterBuyAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 20; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_FighterSkillEquipTo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FighterSkillLevelUp(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FighterPassiveSkillLevelUp(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetTavernInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Draw(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FighterRecruit(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CuiTiUpgrade(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CuiTiAllUpgrade(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FighterShift(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FighterSyncLevel(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpgradeDujie(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqFighterXinFaInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FighterActiveXinFa(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FighterXinFaLevelUp(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FighterXinFaDisperse(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllFighterCombination(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ActiveCombination(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpgradeCombination(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_EquipToCombinationSkill(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FighterDismiss(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetFighterBuyInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FighterBuy(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CFighterProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NFighterProt
