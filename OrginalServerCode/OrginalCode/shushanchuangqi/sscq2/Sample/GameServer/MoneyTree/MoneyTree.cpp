#include "stdafx.h"
#include "Protocols.h"
#include "VIPMgr.h"
#include "UserMgr.h"
#include "Player.h"
#include "Tokenizer.h"
#include "ItemProt.h"
#include "SysMsgDefine.h"
#include "MoneyTree.h"
#include "MoneyTreeProtS.h"
#include "DungeonMgr.h"
#include "Random.h"

void CMoneyTree::GetMoneyTreeInfo(UINT16& wTodayUseCount)
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    wTodayUseCount = rCGameVar.GetVar(NVarDefine::ePlayerMoneyTreeCount);
}

bool CMoneyTree::GetMoney(UINT16& wTodayUseCount)
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    wTodayUseCount = rCGameVar.GetVar(NVarDefine::ePlayerMoneyTreeCount);

    SVIPLevelCFGEx* pCfgVip = VIPMgr.GetVIPLevelCfg(rUser.GetVIPLevel());
    if(NULL == pCfgVip)
        return false;

    if ((rUser.GetVIPLevel()>=VIPMgr.GetVIPMaxLevel()) 
            && (wTodayUseCount >= (pCfgVip->_MoneyTree + SParamConfig::byMoneyTreeFree)))
    {
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgMoneyTreeVMax);
        return false;
    }

    if (wTodayUseCount >= (pCfgVip->_MoneyTree + SParamConfig::byMoneyTreeFree))
        return false;

    UINT16 wUseMoneyCount = 0;
    if (wTodayUseCount >= SParamConfig::byMoneyTreeFree)
        wUseMoneyCount = wTodayUseCount - SParamConfig::byMoneyTreeFree + 1;

    if (wUseMoneyCount > 0)
    {
        UINT32 dwCost = CDungeonMgr::GetMoneyTreePrice(wUseMoneyCount); 
        if (!rUser.CanSubGoldOrCoupon(dwCost, eCouponCoin))
            return false;

        if (!rUser.SubGoldOrCoupon(dwCost, eCouponCoin, NLogDataDefine::ItemTo_MoneyTree))
            return false;
    }

    bool bmark = false;
    UINT8 byNum = 1;
    UINT16 wRand = CRandom::RandInt(0, MAX_RANDNUM);
    if (wRand < SParamConfig::wMoneyTreeChance2)
    {
        bmark = true;
        byNum = SParamConfig::byMoneyTreeTimes2;
        rUser.SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(eMoneyTreeCrit, eFiveMultipleCrit));
    }
    else if (wRand < SParamConfig::wMoneyTreeChance2 + SParamConfig::wMoneyTreeChance1)
    {
        bmark = true;
        byNum = SParamConfig::byMoneyTreeTimes1;
        rUser.SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(eMoneyTreeCrit, eTwoMultipleCrit));
    }
   
    if (bmark)
    {
        TVecString vecstring;
        vecstring.push_back(NumberToString(_rPlayer.GetColor()));
        vecstring.push_back(_rPlayer.GetName());
        vecstring.push_back(NumberToString(byNum));
        g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgMoneyTreeCrit, vecstring);
    }

    UINT32 dwAddMoney = (SParamConfig::wMoneyTreeSilver1 * _rPlayer.GetLevel() + SParamConfig::wMoneyTreeSilver2) * byNum;
    rUser.AddMoney(EMONEY_SILVER, dwAddMoney, NLogDataDefine::ItemFrom_MoneyTree);

    wTodayUseCount += 1;
    rCGameVar.SetVar(NVarDefine::ePlayerMoneyTreeCount, wTodayUseCount);
    
    rUser.GetTaskPkg().OnAction(_rPlayer, eProcessAction_MoneyTree, 1);

    //事件
    {
        TVecINT32 vecParam;
        vecParam.push_back(1);

        CEventMgrPtr pEventMgr = _rPlayer.GetEventMgr();
        if(pEventMgr)
            pEventMgr->OnEvent(eEventType_MoneyTree, vecParam);
    }

    return true;
}

