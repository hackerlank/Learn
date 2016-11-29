#include "stdafx.h"
#include "Protocols.h"
#include "VIPMgr.h"
#include "UserMgr.h"
#include "Player.h"
#include "Tokenizer.h"
#include "ItemProt.h"
#include "RegisterSevenDays.h"
#include "RegisterSevenDaysProtS.h"
#include "SysMsgDefine.h"
#include "CommonMgr.h"

UINT32 CRegisterSevenDays::GetRegisterCurDay()
{
    UINT32 dwTime = Time::TheDay(0, Time::Now()) - Time::TheDay(0, _rPlayer.GetCreateTime());
    UINT32 dwDay = dwTime / DAY_TIME + 1;
   
    if (dwDay >= THE_FIRST_DAY && dwDay <= THE_SEVENTH_DAY)
        return dwDay;

    return 0;
}

UINT32 CRegisterSevenDays::GetOpenCurDay()
{
    UINT32 dwTime = Time::TheDay(0, Time::Now()) - Time::TheDay(0, Config._dwOpenServerTime);
    UINT32 dwDay = dwTime / DAY_TIME + 1;
   
    if (dwDay >= THE_FIRST_DAY && dwDay <= THE_SEVENTH_DAY)
        return dwDay;

    return 0;
}

void CRegisterSevenDays::GetCurTargetInfo(UINT32& dwDay, UINT64& qwTargetInfo)
{
    UINT32 dwValue = GetRegisterCurDay();
    if (dwValue > 0)
    {
        dwDay = dwValue;
        qwTargetInfo = GetTargetInfoByDayID(dwDay);
    }
}

UINT64 CRegisterSevenDays::GetTargetInfoByDayID(UINT32 dwDay)
{
    UINT64 qwTargetInfo = 0;

    if (dwDay<THE_FIFTH_DAY || dwDay>THE_SEVENTH_DAY)
        return qwTargetInfo;

    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    switch (dwDay)
    {
    case THE_FIRST_DAY:
        qwTargetInfo = rCGameVar.GetVar(NVarDefine::ePlayerRegisterSevenDaysA);
        break;
    case THE_SECOND_DAY:
        qwTargetInfo = rCGameVar.GetVar(NVarDefine::ePlayerRegisterSevenDaysB);
        break;
    case THE_THIRD_DAY:
        qwTargetInfo = rCGameVar.GetVar(NVarDefine::ePlayerRegisterSevenDaysC);
        break;
    case THE_FOURTH_DAY:
        qwTargetInfo = rCGameVar.GetVar(NVarDefine::ePlayerRegisterSevenDaysD);
        break;
    case THE_FIFTH_DAY:
        qwTargetInfo = rCGameVar.GetVar(NVarDefine::ePlayerRegisterSevenDaysE);
        break;
    case THE_SIXTH_DAY:
        qwTargetInfo = rCGameVar.GetVar(NVarDefine::ePlayerRegisterSevenDaysF);
        break;
    case THE_SEVENTH_DAY:
        qwTargetInfo = rCGameVar.GetVar(NVarDefine::ePlayerRegisterSevenDaysG);
        break;
    default:
        break;
    }

    return qwTargetInfo;
}

bool CRegisterSevenDays::SetTargetInfoByDayID(UINT32 dwDay, UINT64 qwTargetInfo)
{
    if (dwDay<THE_FIFTH_DAY || dwDay>THE_SEVENTH_DAY)
        return false;

    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    switch (dwDay)
    {
    case THE_FIRST_DAY:
        rCGameVar.SetVar(NVarDefine::ePlayerRegisterSevenDaysA, qwTargetInfo);
        break;
    case THE_SECOND_DAY:
        rCGameVar.SetVar(NVarDefine::ePlayerRegisterSevenDaysB, qwTargetInfo);
        break;
    case THE_THIRD_DAY:
        rCGameVar.SetVar(NVarDefine::ePlayerRegisterSevenDaysC, qwTargetInfo);
        break;
    case THE_FOURTH_DAY:
        rCGameVar.SetVar(NVarDefine::ePlayerRegisterSevenDaysD, qwTargetInfo);
        break;
    case THE_FIFTH_DAY:
        rCGameVar.SetVar(NVarDefine::ePlayerRegisterSevenDaysE, qwTargetInfo);
        break;
    case THE_SIXTH_DAY:
        rCGameVar.SetVar(NVarDefine::ePlayerRegisterSevenDaysF, qwTargetInfo);
        break;
    case THE_SEVENTH_DAY:
        rCGameVar.SetVar(NVarDefine::ePlayerRegisterSevenDaysG, qwTargetInfo);
        break;
    default:
        break;
    }

    return true;
}

bool CRegisterSevenDays::GetAward(UINT32 dwDay, UINT8 byTargetID)
{
    if (dwDay<THE_FIFTH_DAY || dwDay>THE_SEVENTH_DAY)
        return false;

    if (0 == byTargetID)
        return false;
   
    UINT8 byPos = byTargetID - 1;
    UINT64 qwTargetInfo = GetTargetInfoByDayID(dwDay);
    UINT8 byMark = GET_BIT_2(qwTargetInfo, byPos);
    if (CAN_GETAWARD != byMark)
        return false;

    //TODO
    {

    }

    qwTargetInfo = SET_BIT_2(qwTargetInfo, byPos, ALREADY_GETAWARD);
    bool bRet = SetTargetInfoByDayID(dwDay, qwTargetInfo);

    return bRet;
}

EBuyStatus CRegisterSevenDays::GetCurBuyStatus()
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    EBuyStatus eBuyStatus = EBuyStatus(rCGameVar.GetVar(NVarDefine::ePlayerCurDayBuyMark));

    return eBuyStatus;
}

void CRegisterSevenDays::SetCurBuyStatus(EBuyStatus eBuyStatus)
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    rCGameVar.SetVar(NVarDefine::ePlayerCurDayBuyMark, eBuyStatus);
}

void CRegisterSevenDays::GetCurBuyInfo(UINT32& dwDay, EBuyStatus& eBuyStatus)
{
    dwDay = GetOpenCurDay();
    if ((dwDay>0) && (eNoBuy==GetCurBuyStatus()))
        SetCurBuyStatus(eCanBuy);

    eBuyStatus = GetCurBuyStatus();
}

bool CRegisterSevenDays::ReqBuy()
{
    UINT32 dwCurDay = GetOpenCurDay();
    if (0 == dwCurDay)
        return false;
    
    EBuyStatus eBuyStatus = GetCurBuyStatus();
    if (eCanBuy != eBuyStatus)
        return false;
   
    SSevDiscountCFG* pSevDiscountCFG = CCommonMgr::Instance().GetSevDiscountCFG(dwCurDay);
    if (!pSevDiscountCFG)
        return false;

    CUser& rUser = _rPlayer.GetUser();
    if (!rUser.CanSubMoney(EMONEY_GOLD, pSevDiscountCFG->_Discount))
        return false;

    TVecItemGenInfo vecItems;
    Tokenizer tk(pSevDiscountCFG->_Reward, "|");
    for (size_t i=0; i<tk.size(); i++)
    {
        string strAward = tk[i].c_str();
        
        Tokenizer tk(strAward, ',');
        if (2 != tk.size())
            continue;

        SItemGenInfo sItemGenInfo;
        sItemGenInfo.wItemID = atoi(tk[0].c_str());
        sItemGenInfo.dwCount = atoi(tk[1].c_str());
        sItemGenInfo.eBindType = eBindGet;
        vecItems.push_back(sItemGenInfo);
    }
    
    CPack& oPack = _rPlayer.GetUser().GetPack();
    if(!oPack.CanAddItem(vecItems))
    {
        _rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgMonsterDropPackFull));
        return false;
    }

    rUser.SubMoney(EMONEY_GOLD, pSevDiscountCFG->_Discount, NLogDataDefine::ItemTo_RegisterSevenDaysDis);

    oPack.AddItem(vecItems, NLogDataDefine::ItemFrom_RegisterSevenDaysDis);

    SetCurBuyStatus(eAlreadyBuy);

    {
        TVecString vecstring;
        vecstring.push_back(NumberToString(_rPlayer.GetColor()));
        vecstring.push_back(_rPlayer.GetName());
        g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgDiscount, vecstring);
    }
    return true;
}

