
#include "stdafx.h"
#include "Protocols.h"
#include "PropInfoS.h"
#include "UserMgr.h"
#include "Player.h"
#include "FighterMgr.h"
#include "GameNetMgr.h"

//接收：货币兑换
bool CPropInfoS::OnRecv_MoneyExchange(
        EPropType eSrcProp, //源货币
        EPropType eDestProp, //目标货币
        UINT32 dwCount, //数量
        shared_func<SMoneyExchangeAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
         return false;                       
    fnAck->eResult = pUser->ExchangeMoney(eSrcProp, eDestProp, dwCount);
    return true;
}


void CPropInfoS::UniquePropList(TVecPropValue& vecPropValue, bool bAdd)
{
	auto fnEqual = [](const SPropValue& left, const SPropValue& right)->bool{ return left.ePropType == right.ePropType; };
	if(bAdd)
	{
		sort(vecPropValue.begin(), vecPropValue.end(), [](const SPropValue& left, const SPropValue& right)->bool{
			if(left.ePropType < right.ePropType)
				return true;
			if(left.ePropType > right.ePropType)
				return false;
			return left.value > right.value;
		});
		vecPropValue.erase(unique(vecPropValue.begin(), vecPropValue.end(), fnEqual), vecPropValue.end());
	}
	else
	{
		sort(vecPropValue.begin(), vecPropValue.end(), [](const SPropValue& left, const SPropValue& right)->bool{
			if(left.ePropType < right.ePropType)
				return true;
			if(left.ePropType > right.ePropType)
				return false;
			return left.value < right.value;
		});
		vecPropValue.erase(unique(vecPropValue.begin(), vecPropValue.end(), fnEqual), vecPropValue.end());
	}
}

void CPropInfoS::PropNotify(CCreature& rCreature, UINT64 qwInstID, EPropClass eClass, EPropType ePropType, UINT32 dwValue, bool bBroadCast /*= false*/)
{
    TVecPropValue vecPropValue;
    SPropValue oPropValue(ePropType, dwValue);
    vecPropValue.push_back(oPropValue);
    string& strPkg = BuildPkg_PropListNotify(qwInstID, eClass, vecPropValue);
    if(bBroadCast)
        rCreature.NotifyMeAndSurround(strPkg);
    else
        rCreature.SendPkg(strPkg);
}

void CPropInfoS::CouponNotify(CCreature& rCreature, UINT64 qwInstID, EPropClass eClass, EPropType ePropType, UINT32 dwValue, bool bBroadCast /*= false*/,bool bType)
{
    TVecPropValue vecPropValue;
    SPropValue oPropValue(ePropType, dwValue);
    vecPropValue.push_back(oPropValue);
    string& strPkg = BuildPkg_PropNotify(qwInstID, eClass, vecPropValue,bType);
    if(bBroadCast)
        rCreature.NotifyMeAndSurround(strPkg);
    else
        rCreature.SendPkg(strPkg);
}
void CPropInfoS::FighterPropNotify(CFighterPtr& pFighter, EPropType ePropType, UINT32 dwValue, bool bBroadCast/* = false*/)
{
    if (!pFighter)
        return;
    if (!pFighter->GetUser() || !pFighter->GetUser()->GetPlayer())
        return;
    PropNotify(*pFighter->GetUser()->GetPlayer(), pFighter->GetInstID(), eClassFighter, ePropType, dwValue, bBroadCast);
}

void CPropInfoS::PropQWNotify(CCreature& rCreature, UINT64 qwInstID, EPropClass eClass, EPropType ePropType, UINT64 qwValue, bool bBroadCast /*= false*/)
{
    TVecPropQWValue vecPropValue;
    SPropQWValue oPropValue(ePropType, qwValue);
    vecPropValue.push_back(oPropValue);
    string& strPkg = BuildPkg_PropQWListNotify(qwInstID, eClass, vecPropValue);
    if(bBroadCast)
        rCreature.NotifyMeAndSurround(strPkg);
    else
        rCreature.SendPkg(strPkg);
}

void CPropInfoS::PropExtNotify(CCreature& rCreature, UINT64 qwInstID, EPropClass eClass, EPropType ePropType, UINT32 dwValue, INT32 dwDelta, bool bBroadCast /*= false*/)
{
    TVecPropValExt vecPropValExt;
    SPropValExt oPropValExt(ePropType, dwValue, dwDelta);
    vecPropValExt.push_back(oPropValExt);
    string& strPkg = BuildPkg_PropExtListNotify(qwInstID, eClass, vecPropValExt);
    if(bBroadCast)
        rCreature.NotifyMeAndSurround(strPkg);
    else
        rCreature.SendPkg(strPkg);
}

void CPropInfoS::PropQWExtNotify(CCreature& rCreature, UINT64 qwInstID, EPropClass eClass, EPropType ePropType, UINT64 qwValue, INT32 dwDelta, bool bBroadCast /*= false*/)
{
    TVecPropQWValExt vecPropValExt;
    SPropQWValExt oPropValExt(ePropType, qwValue, dwDelta);
    vecPropValExt.push_back(oPropValExt);
    string& strPkg = BuildPkg_PropQWExtListNotify(qwInstID, eClass, vecPropValExt);
    if(bBroadCast)
        rCreature.NotifyMeAndSurround(strPkg);
    else
        rCreature.SendPkg(strPkg);
}


void CPropInfoS::PropListNotify(CCreature& rCreature, UINT64 qwInstID, EPropClass eClass, TVecPropValue& vecPropValue)
{
	if(vecPropValue.empty())
		return;

	TVecPropValue vecPropValueBroad;
    /*
	for(size_t i = 0; i < vecPropValue.size(); ++i)
	{
		SPropValue& rPropValue = vecPropValue[i];
		switch(rPropValue.ePropType)
		{
            // TODO: 有些属性需要额外数据
		}
	}
    */
	if(!vecPropValueBroad.empty())
		rCreature.NotifySurround(BuildPkg_PropListNotify(qwInstID, eClass, vecPropValueBroad));
	if(!vecPropValue.empty())
		rCreature.SendPkg(BuildPkg_PropListNotify(qwInstID, eClass, vecPropValue));
}

void CPropInfoS::PropExtListNotify(CCreature& rCreature, UINT64 qwInstID, EPropClass eClass, TVecPropValExt& vecPropValExt)
{
	TVecPropValExt vecPropValExtBroad;
	TVecPropValExt vecPropValExtSelf;
	for(size_t i = 0; i < vecPropValExt.size(); ++i)
	{
		SPropValExt& rPropValExt = vecPropValExt[i];
		switch(rPropValExt.ePropType)
		{
            // TODO:
		default:
			vecPropValExtSelf.push_back(rPropValExt);
		}
	}
	if(!vecPropValExtBroad.empty())
	    rCreature.NotifyMeAndSurround(BuildPkg_PropExtListNotify(qwInstID, eClass, vecPropValExtBroad));
	if(!vecPropValExtSelf.empty())
		rCreature.SendPkg(BuildPkg_PropExtListNotify(qwInstID, eClass, vecPropValExtSelf));
}

void CPropInfoS::AppearPropNotify(CCreature& rCreature, bool bBroadCast /*= true*/)
{
	TVecPropValue vecPropValue;
	SPropValue oPropValue;

	oPropValue.ePropType = ePropLevel;
	oPropValue.value = rCreature.GetLevel();
	vecPropValue.push_back(oPropValue);

    // TODO:
#if 0
	oPropValue.ePropType = ePropSpeed;
	oPropValue.value = rCreature.Speed();
	vecPropValue.push_back(oPropValue);

	oPropValue.ePropType = ePropCurHP;
	oPropValue.value = rCreature.CurHP();
	vecPropValue.push_back(oPropValue);

	oPropValue.ePropType = ePropMaxHP;
	oPropValue.value = rCreature.MaxHP();
	vecPropValue.push_back(oPropValue);
#endif

	string& strPkg = BuildPkg_PropListNotify(rCreature.GetCreatureID(), eClassORole, vecPropValue);
	if(bBroadCast)
		rCreature.NotifyMeAndSurround(strPkg);
	else
		rCreature.SendPkg(strPkg);
}

void CPropInfoS::PropNotify(CCreature& rCreature, EPropClass eClass, EPropType ePropType, UINT32 dwValue, bool bBroadCast)
{
    PropNotify(rCreature, rCreature.GetCreatureID(), eClass, ePropType, dwValue, bBroadCast);
}

void CPropInfoS::PropQWNotify(CCreature& rCreature, EPropClass eClass, EPropType ePropType, UINT64 qwValue, bool bBroadCast)
{
    PropQWNotify(rCreature, rCreature.GetCreatureID(), eClass, ePropType, qwValue, bBroadCast);
}

void CPropInfoS::PropExtNotify(CCreature& rCreature, EPropClass eClass, EPropType ePropType, UINT32 dwValue, INT32 dwDelta, bool bBroadCast)
{
    PropExtNotify(rCreature, rCreature.GetCreatureID(), eClass, ePropType, dwValue, bBroadCast);
}

void CPropInfoS::PropQWExtNotify(CCreature& rCreature, EPropClass eClass, EPropType ePropType, UINT64 qwValue, INT32 dwDelta, bool bBroadCast)
{
    PropQWExtNotify(rCreature, rCreature.GetCreatureID(), eClass, ePropType, qwValue, dwDelta, bBroadCast);
}

void CPropInfoS::PropListNotify(CCreature& rCreature, EPropClass eClass, TVecPropValue& vecPropValue)
{
    PropListNotify(rCreature, rCreature.GetCreatureID(), eClass, vecPropValue);
}

void CPropInfoS::PropExtListNotify(CCreature& rCreature, EPropClass eClass, TVecPropValExt& vecPropValExt)
{
    PropExtListNotify(rCreature, rCreature.GetCreatureID(), eClass, vecPropValExt);
}

void CPropInfoS::ChangeGold(CCreature& rCreature, UINT32 dwGold)
{
    PropNotify(rCreature, eClassRole, ePropGold, dwGold);
}

void CPropInfoS::ChangeSilver(CCreature& rCreature, UINT32 dwSilver)
{
    PropNotify(rCreature, eClassRole, ePropSilver, dwSilver);
}

void CPropInfoS::ChangeCoupon(CCreature& rCreature, UINT32 dwCoupon)
{
    PropNotify(rCreature, eClassRole, ePropCoupon, dwCoupon);
}

void CPropInfoS::ChangePrestige(CCreature& rCreature, UINT32 dwPrestige)
{
    PropNotify(rCreature, eClassRole, ePropPrestige, dwPrestige);
}

void CPropInfoS::ChangeSoul(CCreature& rCreature, UINT32 dwSoul)
{
    PropNotify(rCreature, eClassRole, ePropSoul, dwSoul);
}

void CPropInfoS::ChangeHonor(CCreature& rCreature, UINT32 dwHonor)
{
    PropNotify(rCreature, eClassRole, ePropHonor, dwHonor);
}

void CPropInfoS::ChangeExp(CCreature& rCreature, UINT32 dwExp)
{
    PropNotify(rCreature, eClassRole, ePropExp, dwExp);
}

void CPropInfoS::ChangePExp(CCreature& rCreature, UINT32 dwPExp)
{
    PropNotify(rCreature, eClassRole, ePropPExp, dwPExp);
}

void CPropInfoS::ChangeSigil(CCreature& rCreature, UINT32 dwSigil)
{
    PropNotify(rCreature, eClassRole, ePropSigil, dwSigil);
}

void CPropInfoS::ChangeCentsY(CCreature& rCreature, UINT32 dwCentsY)
{
    PropNotify(rCreature, eClassRole, ePropCentsY, dwCentsY);
}

void CPropInfoS::ChangeAction(CCreature& rCreature, UINT32 dwAction)
{
    PropNotify(rCreature, eClassRole, ePropAction, dwAction);
}

void CPropInfoS::ChangeSop(CCreature& rCreature, UINT32 dwSop)
{
    PropNotify(rCreature, eClassRole, ePropSop, dwSop);
}

void CPropInfoS::ChangeTaoism(CCreature& rCreature, UINT32 dwTaoism)
{
    PropNotify(rCreature, eClassRole, ePropTaoism, dwTaoism);
}

void CPropInfoS::ChangePoten(CCreature& rCreature, UINT32 dwPoten)
{
    PropNotify(rCreature, eClassRole, ePropPoten, dwPoten);
}

void CPropInfoS::ChangeReiki(CCreature& rCreature, UINT32 dwReiki)
{
    PropNotify(rCreature, eClassRole, ePropReiki, dwReiki);
}

void CPropInfoS::ChangeHFP(CCreature& rCreature, UINT32 dwHFP)
{
    PropNotify(rCreature, eClassRole, ePropHFP, dwHFP);
}

void CPropInfoS::ChangeDemonSoul(CCreature& rCreature, UINT32 dwDemonSoul)
{
    PropNotify(rCreature, eClassRole, ePropDemonSoul, dwDemonSoul);
}

void CPropInfoS::ChangeSoulAttack(CCreature& rCreature, UINT32 dwSoulAttack)
{
    PropNotify(rCreature, eClassRole, ePropSoulAttack, dwSoulAttack);
}

void CPropInfoS::ChangeSoulHp(CCreature& rCreature, UINT32 dwSoulHp)
{
    PropNotify(rCreature, eClassRole, ePropSoulHp, dwSoulHp);
}

void CPropInfoS::ChangeSoulCritical(CCreature& rCreature, UINT32 dwSoulCritical)
{
    PropNotify(rCreature, eClassRole, ePropSoulCritical, dwSoulCritical);
}

void CPropInfoS::ChangeSoulCounter(CCreature& rCreature, UINT32 dwSoulCounter)
{
    PropNotify(rCreature, eClassRole, ePropSoulCounter, dwSoulCounter);
}

void CPropInfoS::ChangeSoulSpeed(CCreature& rCreature, UINT32 dwSoulSpeed)
{
    PropNotify(rCreature, eClassRole, ePropSoulSpeed, dwSoulSpeed);
}

void CPropInfoS::ChangeSoulDefence(CCreature& rCreature, UINT32 dwSoulDefence)
{
    PropNotify(rCreature, eClassRole, ePropSoulDefence, dwSoulDefence);
}

void CPropInfoS::ChangeSoulHit(CCreature& rCreature, UINT32 dwSoulHit)
{
    PropNotify(rCreature, eClassRole, ePropSoulHit, dwSoulHit);
}

void CPropInfoS::ChangeSoulDodge(CCreature& rCreature, UINT32 dwSoulDodge)
{
    PropNotify(rCreature, eClassRole, ePropSoulDodge, dwSoulDodge);
}

void CPropInfoS::ChangeStampHuang(CCreature& rCreature, UINT32 dwStampHuang)
{
    PropNotify(rCreature, eClassRole, ePropStampHuang, dwStampHuang);
}

void CPropInfoS::ChangeStampXuan(CCreature& rCreature, UINT32 dwStampXuan)
{
    PropNotify(rCreature, eClassRole, ePropStampXuan, dwStampXuan);
}

void CPropInfoS::ChangeStampDi(CCreature& rCreature, UINT32 dwStampDi)
{
    PropNotify(rCreature, eClassRole, ePropStampDi, dwStampDi);
}

void CPropInfoS::ChangeStampTian(CCreature& rCreature, UINT32 dwStampTian)
{
    PropNotify(rCreature, eClassRole, ePropStampTian, dwStampTian);
}

void CPropInfoS::ChangeStampXing(CCreature& rCreature, UINT32 dwStampXing)
{
    PropNotify(rCreature, eClassRole, ePropStampXing, dwStampXing);
}

void CPropInfoS::ChangeStampYue(CCreature& rCreature, UINT32 dwStampYue)
{
    PropNotify(rCreature, eClassRole, ePropStampYue, dwStampYue);
}

void CPropInfoS::ChangeStampDi2(CCreature& rCreature, UINT32 dwStampDi2)
{
    PropNotify(rCreature, eClassRole, ePropStampDi2, dwStampDi2);
}

void CPropInfoS::ChangeStampXian(CCreature& rCreature, UINT32 dwStampXian)
{
    PropNotify(rCreature, eClassRole, ePropStampXian, dwStampXian);
}

void CPropInfoS::ChangeStampSheng(CCreature& rCreature, UINT32 dwStampSheng)
{
    PropNotify(rCreature, eClassRole, ePropStampSheng, dwStampSheng);
}

void CPropInfoS::ChangeStampFo(CCreature& rCreature, UINT32 dwStampFo)
{
    PropNotify(rCreature, eClassRole, ePropStampFo, dwStampFo);
}

void CPropInfoS::ChangeAchievementAP(CCreature& rCreature, UINT32 dwAchievementAP)
{
    PropNotify(rCreature, eClassRole, ePropAchievementAP, dwAchievementAP);
}

void CPropInfoS::ChangeCollectAP(CCreature& rCreature, UINT32 dwCollectAP)
{
    PropNotify(rCreature, eClassRole, ePropCollectAP, dwCollectAP);
}

void CPropInfoS::ChangeBTPoint(CCreature& rCreature, UINT32 dwBTPoint)
{
    PropNotify(rCreature, eClassRole, ePropBTPoint, dwBTPoint);
}

void CPropInfoS::ChangeTotalRecharge(CCreature& rCreature,UINT32 dwValue)
{
    PropNotify(rCreature, eClassRole, ePropTotalRecharge, dwValue);
}

void CPropInfoS::ChangeMoney(CCreature& rCreature,UINT32 dwType,UINT32 dwValue)
{
    if(dwType < ePropMoneyEnd && dwType > ePropNone)
    {
        PropNotify(rCreature, eClassRole, (EPropType)dwType, dwValue);
    }
}

//888礼券
void CPropInfoS::ChangeCoupon(CCreature& rCreature,UINT32 dwType,UINT32 dwValue)
{
    if(dwType < ePropMoneyEnd && dwType > ePropNone)
    {
        CouponNotify(rCreature, rCreature.GetCreatureID(),eClassRole, (EPropType)dwType, dwValue,false,false);
    }
}
