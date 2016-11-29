#pragma once
#include "PropInfoSvr.h"

using namespace NPropInfo;

class CPropInfoS : public CPropInfoSvr
{
public:
	//接收：货币兑换
	virtual bool OnRecv_MoneyExchange(
		EPropType eSrcProp, //源货币
		EPropType eDestProp, //目标货币
		UINT32 dwCount, //数量
		shared_func<SMoneyExchangeAck>& fnAck //返回回调函数
	);

	static void UniquePropList(TVecPropValue& vecPropValue, bool bAdd);

	void PropNotify(CCreature& rCreature, EPropClass eClass, EPropType ePropType, UINT32 dwValue, bool bBroadCast = false);
	void PropQWNotify(CCreature& rCreature, EPropClass eClass, EPropType ePropType, UINT64 qwValue, bool bBroadCast = false);

	void PropExtNotify(CCreature& rCreature, EPropClass eClass, EPropType ePropType, UINT32 dwValue, INT32 dwDelta, bool bBroadCast = false);
	void PropQWExtNotify(CCreature& rCreature, EPropClass eClass, EPropType ePropType, UINT64 qwValue, INT32 dwDelta, bool bBroadCast = false);

	void PropListNotify(CCreature& rCreature, EPropClass eClass, TVecPropValue& vecPropValue);
	void PropExtListNotify(CCreature& rCreature, EPropClass eClass, TVecPropValExt& vecPropValExt);

	void PropNotify(CCreature& rCreature, UINT64 qwInstID, EPropClass eClass, EPropType ePropType, UINT32 dwValue, bool bBroadCast = false);
	void CouponNotify(CCreature& rCreature, UINT64 qwInstID, EPropClass eClass, EPropType ePropType, UINT32 dwValue, bool bBroadCast = false,bool bType = false);
	void PropQWNotify(CCreature& rCreature, UINT64 qwInstID, EPropClass eClass, EPropType ePropType, UINT64 qwValue, bool bBroadCast = false);

	void PropExtNotify(CCreature& rCreature, UINT64 qwInstID, EPropClass eClass, EPropType ePropType, UINT32 dwValue, INT32 dwDelta, bool bBroadCast = false);
	void PropQWExtNotify(CCreature& rCreature, UINT64 qwInstID, EPropClass eClass, EPropType ePropType, UINT64 qwValue, INT32 dwDelta, bool bBroadCast = false);

	void PropListNotify(CCreature& rCreature, UINT64 qwInstID, EPropClass eClass, TVecPropValue& vecPropValue);
	void PropExtListNotify(CCreature& rCreature, UINT64 qwInstID, EPropClass eClass, TVecPropValExt& vecPropValExt);
    
	void FighterPropNotify(CFighterPtr& pFighter, EPropType ePropType, UINT32 dwValue, bool bBroadCast = false);

    void ChangeGold(CCreature& rCreature, UINT32 dwGold);
    void ChangeSilver(CCreature& rCreature, UINT32 dwSilver);
    void ChangeCoupon(CCreature& rCreature, UINT32 dwCoupon);
    void ChangePrestige(CCreature& rCreature, UINT32 dwPrestige);
    void ChangeSoul(CCreature& rCreature, UINT32 dwSoul);
    void ChangeHonor(CCreature& rCreature, UINT32 dwHonor);
    void ChangeExp(CCreature& rCreature, UINT32 dwExp);
    void ChangePExp(CCreature& rCreature, UINT32 dwPExp);
    void ChangeSigil(CCreature& rCreature, UINT32 dwSigil);
    void ChangeCentsY(CCreature& rCreature, UINT32 dwCentsY);
    void ChangeAction(CCreature& rCreature, UINT32 dwAction);
    void ChangeSop(CCreature& rCreature, UINT32 dwSop);
    void ChangeTaoism(CCreature& rCreature, UINT32 dwTaoism);
    void ChangePoten(CCreature& rCreature, UINT32 dwPoten);
    void ChangeReiki(CCreature& rCreature, UINT32 dwReiki);
    void ChangeHFP(CCreature& rCreature, UINT32 dwHFP);
    void ChangeDemonSoul(CCreature& rCreature, UINT32 dwDemonSoul);
    void ChangeSoulAttack(CCreature& rCreature, UINT32 dwSoulAttack);
    void ChangeSoulHp(CCreature& rCreature, UINT32 dwSoulHp);
    void ChangeSoulCritical(CCreature& rCreature, UINT32 dwSoulCritical);
    void ChangeSoulCounter(CCreature& rCreature, UINT32 dwSoulCounter);
    void ChangeSoulSpeed(CCreature& rCreature, UINT32 dwSoulSpeed);
    void ChangeSoulDefence(CCreature& rCreature, UINT32 dwDefence);
    void ChangeSoulHit(CCreature& rCreature, UINT32 dwSoulHit);
    void ChangeSoulDodge(CCreature& rCreature, UINT32 dwSoulDodge);

    void ChangeStampHuang(CCreature& rCreature, UINT32 dwStampHuang);
    void ChangeStampXuan(CCreature& rCreature, UINT32 dwStampXuan);
    void ChangeStampDi(CCreature& rCreature, UINT32 dwStampDi);
    void ChangeStampTian(CCreature& rCreature, UINT32 dwStampTian);
    void ChangeStampXing(CCreature& rCreature, UINT32 dwStampXing);
    void ChangeStampYue(CCreature& rCreature, UINT32 dwStampYue);
    void ChangeStampDi2(CCreature& rCreature, UINT32 dwStampDi2);
    void ChangeStampXian(CCreature& rCreature, UINT32 dwStampXian);
    void ChangeStampSheng(CCreature& rCreature, UINT32 dwStampSheng);
    void ChangeStampFo(CCreature& rCreature, UINT32 dwStampFo);

    void ChangeAchievementAP(CCreature& rCreature, UINT32 dwAchievementAP);
    void ChangeCollectAP(CCreature& rCreature, UINT32 dwCollectAP);
    void ChangeTotalRecharge(CCreature& rCreature,UINT32 dwValue);

    void ChangeMoney(CCreature& rCreature,UINT32 dwType,UINT32 dwValue);
    void ChangeCoupon(CCreature& rCreature,UINT32 dwType,UINT32 dwValue);
    void ChangeBTPoint(CCreature& rCreature, UINT32 dwBTPoint);
	void AppearPropNotify(CCreature& rCreature, bool bBroadCast = true);
};

template<typename T>
void AppendProp(TVecPropValue& vecPropValue, EPropType ePropType, T&& rT)
{
	if(forward<T>(rT) != 0)
		vecPropValue.emplace_back(ePropType, rT);
}
