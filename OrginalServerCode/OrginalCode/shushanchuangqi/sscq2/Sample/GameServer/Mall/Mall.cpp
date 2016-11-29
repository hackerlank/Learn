
#include "stdafx.h"
#include "Protocols.h"
#include "Mall.h"
#include "ItemMgr.h" // XXX: for SMallCFG
#include "Player.h"
#include "UserMgr.h"
#include "FighterManager.h"
#include "FashionSlots.h"
#include "GameServerSysMail.h"
#include "ShopItemMgr.h"
#include "Tokenizer.h"
#include "GetCondMgr.h"

EMallResult CMall::BuyItem(CUser& rUser, EUseMoneyMark eMark, EMallType eType, UINT32 dwInstID, INT16 wCount)
{

    const SMallCFG* pMallCfg = CItemMgr::GetMallCFG((UINT8)eType,dwInstID);
    if (!pMallCfg)
        return eMallResultNoItem;

    UINT16 wItemID = pMallCfg->_ItemId;

    SItemInfo* pItemCfg = CItemMgr::GetItemConfig(wItemID);
    if (!pItemCfg)
        return eMallResultNoItem;

    if (eType == eMallVIP && rUser.GetVIPLevel() < pMallCfg->_VIP)
        return eMallResultFailed;
   
    if (pMallCfg->_AvailableCon && !CGetCondMgr::Instance().TestCond(rUser, pMallCfg->_AvailableCon))
        return eMallResultFailed;

    UINT32 bindNum = 0;   // 绑定数量
    UINT32 noBindNum = 0; // 非绑定数量
#if 0
    if ((EMoneyType)pMallCfg->_MoneyType == EMONEY_COUPON)
    {
        if(eUseBindMoney == eMark)
        {
            //选择优先使用绑定钱币（先扣礼券再扣仙石）
            if (!rUser.CanSubGoldOrCoupon(pMallCfg->_Price*wCount, eCouponCoin))
                return eMallResultMoney;
            
            if (rUser.GetMoney(EMONEY_COUPON) > 0)
            {
                if (rUser.GetMoney(EMONEY_COUPON) < pMallCfg->_Price*wCount)
                {
                    if (0 == rUser.GetMoney(EMONEY_COUPON) % pMallCfg->_Price)
                        bindNum = rUser.GetMoney(EMONEY_COUPON) / pMallCfg->_Price;
                    else
                        bindNum = rUser.GetMoney(EMONEY_COUPON) / pMallCfg->_Price + 1;
                    noBindNum = wCount - bindNum;
                }
                else
                    bindNum = wCount;
            }
            else
                noBindNum = wCount;
        }
        else
        {
            //不选择优先使用绑定钱币（只扣仙石）
            if (!rUser.CanSubMoney(EMONEY_GOLD, pMallCfg->_Price*wCount))
                return eMallResultMoney;

            noBindNum = wCount;

            /*if (!rUser.CanSubGoldOrCoupon(pMallCfg->_Price*wCount, eGoldCoin))
                return eMallResultMoney;

            if (rUser.GetMoney(EMONEY_GOLD) < pMallCfg->_Price*wCount)
            {
                noBindNum = rUser.GetMoney(EMONEY_GOLD) / pMallCfg->_Price;
                bindNum = wCount - noBindNum;
            }
            else
                noBindNum = wCount;*/
        }
    }
    else
#endif
    {
        if (!rUser.CanSubMoney((EMoneyType)pMallCfg->_MoneyType, pMallCfg->_Price*wCount))
            return eMallResultMoney;

        if ((EMoneyType)pMallCfg->_MoneyType == EMONEY_GOLD)
            noBindNum = wCount;
        else
            bindNum = wCount;
    }
   
    //限购条件
    UINT32 dwLimit = 0;
    UINT8 byVIPLevel = rUser.GetVIPLevel();
    Tokenizer tk(pMallCfg->_DayCntLimit, "|");
    for (size_t i=0; i<tk.size(); i++)
    {
        string strLimit = tk[i].c_str();
        
        Tokenizer tkA(strLimit, ',');
        if (2 != tkA.size())
            break;

        if(byVIPLevel == atoi(tkA[0].c_str()))
        {
            dwLimit = atoi(tkA[1].c_str());
            break;
        }
    }

    //限购检测
    if(dwLimit)
    {
        CPlayerPtr pPlayer = rUser.GetPlayer();
        if(NULL == pPlayer)
        {
            return eMallResultFailed;
        }
        CShopItemMgrPtr pShopItem = pPlayer->GetShopItemMgr();
        if(NULL == pShopItem)
        {
            return eMallResultFailed;

        }

        UINT32 dwBuycount = pShopItem->GetBuyItemCountByInstID(dwInstID);
        if(dwBuycount+wCount > dwLimit)
        {
            return eMallResultFailed;
        }
    }

    CPack& rPack = rUser.GetPack();
    TVecItemGenInfo vecItems;
    if(bindNum > 0)
    {
        SItemGenInfo sItemGen;
        sItemGen.wItemID = wItemID;
        sItemGen.dwCount = bindNum * pMallCfg->_ItemNum;
        sItemGen.eBindType = eBindGet;
        sItemGen.byQuality = pItemCfg->oItemCfg._Quality;
        sItemGen.dwTimeID = pItemCfg->oItemCfg._ItemTimeID;
        vecItems.push_back(sItemGen);
    }
    if(noBindNum > 0)
    {
        SItemGenInfo sItemGen;
        sItemGen.wItemID = wItemID;
        sItemGen.dwCount = noBindNum * pMallCfg->_ItemNum;
        sItemGen.eBindType = eBindNone;
        sItemGen.byQuality = pItemCfg->oItemCfg._Quality;
        sItemGen.dwTimeID = pItemCfg->oItemCfg._ItemTimeID;
        vecItems.push_back(sItemGen);
    }

    /*
    if (eType == eMallFashion)
    {
        CPlayerFighterPtr pFighter = dynamic_pointer_cast<CPlayerFighter>(rUser.GetPlayer()->GetFighterManager()->GetPlayerFighter());
        if (!pFighter)
            return eMallResultStoreAdd;
        if (pFighter->GetFashions().GetSlotByID(wItemID))
            return eMallResultFashionAlready;
        if (!pFighter->GetFashions().AdoptFashion(wItemID))
            return eMallResultStoreAdd;
    }
    else
    */
    {
        if (CItemType::IsFashion(wItemID))
            return eMallResultFashionErr;
        if (!rPack.CanAddItem(vecItems))
            return eMallResultStore;

        NLogDataDefine::ItemFrom dwLogType = NLogDataDefine::ItemFrom_Mall;
        if ((EMoneyType)pMallCfg->_MoneyType == EMONEY_GOLD)
        {
            dwLogType = NLogDataDefine::ItemFrom_Mall;
        }
        else
        {
            dwLogType = NLogDataDefine::ItemFrom_Mall_NoGold;
        }

        if (!rPack.AddItem(vecItems,dwLogType))
            return eMallResultStoreAdd;
    }

#if 0
    if ((EMoneyType)pMallCfg->_MoneyType == EMONEY_COUPON)
    {
        if(eUseBindMoney == eMark)
            rUser.SubGoldOrCoupon(pMallCfg->_Price*wCount, eCouponCoin,NLogDataDefine::ItemTo_MallBuy);
        else
            rUser.SubMoney(EMONEY_GOLD, pMallCfg->_Price*wCount,NLogDataDefine::ItemTo_MallBuy);
    }
    else
    {
        rUser.SubMoney((EMoneyType)pMallCfg->_MoneyType, pMallCfg->_Price*wCount,NLogDataDefine::ItemTo_MallBuy);
    }
#endif

        NLogDataDefine::ItemTo dwSubLogType = NLogDataDefine::ItemTo_MallBuy;
        if ((EMoneyType)pMallCfg->_MoneyType == EMONEY_GOLD)
        {
            dwSubLogType = NLogDataDefine::ItemTo_MallBuy;
        }
        else
        {
            dwSubLogType = NLogDataDefine::ItemTo_MallBuy_NoGold;
        }

    rUser.SubMoney((EMoneyType)pMallCfg->_MoneyType, pMallCfg->_Price*wCount,dwSubLogType);
    
    //限购增加次数
    if(dwLimit)
    {
        CPlayerPtr pPlayer = rUser.GetPlayer();
        if(NULL == pPlayer)
        {
            return eMallResultFailed;
        }
        CShopItemMgrPtr pShopItem = pPlayer->GetShopItemMgr();
        if(NULL == pShopItem)
        {
            return eMallResultFailed;

        }

        pShopItem->AddBuyItemCountByInstID(dwInstID,wCount);
     }


    //商城购买事件
    CPlayerPtr pPlayer = rUser.GetPlayer();
    if(pPlayer)
    {
        {
            TVecINT32 vecParam;
            vecParam.push_back(eType);
            vecParam.push_back(wItemID);
            vecParam.push_back(wCount);
            vecParam.push_back(pMallCfg->_MoneyType);
            pPlayer->OnEvent(eEventType_MallBought, vecParam);
        }
        {
            TVecINT32 vecParam;
            vecParam.push_back(wItemID);
            vecParam.push_back(pMallCfg->_MoneyType);
            vecParam.push_back(pMallCfg->_Price * wCount);
            pPlayer->OnEvent(eEventType_MallBoughtMomey, vecParam);

        }
    }

    return eMallResultSucc;
}

void CMall::PresentItem(CUser& rUser, EUseMoneyMark eMark, EMallType eType,UINT32 dwInstID,  INT16 wCount,
        const std::string& strReceiveName, const std::string& strTitle, const std::string& strMsg, shared_func<CMallProtSvr::SMallPresentAck>& fnAck)
{
#if 0
    // check wCount
    if (0 == wCount)
    {
        fnAck->eResult = eMallResultFailed;
        fnAck(true);
        return ;
    }

    // check self
    if (rUser.GetUserName() == strReceiveName)
    {
        fnAck->eResult = eMallResultFailed;
        fnAck(true);
        return ;
    }

    // check mail msg length
    if (strMsg.size() > 80 * 3)
    {
        fnAck->eResult = eMallResultFailed;
        fnAck(true);
        return ;
    }


    const SMallCFG* pMallCfg = CItemMgr::GetMallCFG((UINT8)eType,dwInstID);
    if (!pMallCfg)
    {
        fnAck->eResult = eMallResultFailed;
        fnAck(true);
        return ;
    }

    if(pMallCfg->_DayCntLimit)
    {
        fnAck->eResult = eMallResultFailed;
        fnAck(true);
        return;
    }

    UINT16 wItemID = pMallCfg->_ItemId; 
    
    if ((EMoneyType)pMallCfg->_MoneyType == EMONEY_GOLD)
    {
        if (!rUser.CanSubMoney((EMoneyType)pMallCfg->_MoneyType, pMallCfg->_Price*wCount))
        {
            fnAck->eResult = eMallResultMoney;
            fnAck(true);
            return ;
        }
    }
    else
    {
        fnAck->eResult = eMallResultFailed;
        fnAck(true);
        return ;
    }
       
    if (eType == eMallFashion || eType == eMallGold)
    {
        UINT64 qwRoleID = rUser.GetUserID();
        g_Game2DBCommC.Send_GetUserIDFromName(strReceiveName, [eMark, wItemID, wCount, strTitle, strMsg, eType,dwInstID,qwRoleID, fnAck](UINT8 byRet, UINT64 qwReceiveID){
        if(byRet != 0 || qwReceiveID == 0)
        {
            fnAck->eResult = eMallPresentNoTarget;
            fnAck(true);
            return ;
        }

        CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (pUser == NULL)
        {
            fnAck->eResult = eMallResultFailed;
            fnAck(true);
            return ;
        }

        const SMallCFG* pMallCfg = CItemMgr::GetMallCFG((UINT8)eType,dwInstID);
        if (!pMallCfg)
        {
            fnAck->eResult = eMallResultFailed;
            fnAck(true);
            return ;
        }

        SItemInfo* pItemCfg = CItemMgr::GetItemConfig(wItemID);
        if (!pItemCfg)
        {
            fnAck->eResult = eMallResultNoItem;
            fnAck(true);
            return ;
        }

        if ((EMoneyType)pMallCfg->_MoneyType == EMONEY_GOLD)
        {
            if (!pUser->CanSubMoney((EMoneyType)pMallCfg->_MoneyType, pMallCfg->_Price*wCount))
            {
            fnAck->eResult = eMallResultMoney;
            fnAck(true);
            return ;
            }
        }
        else
        {
            fnAck->eResult = eMallResultFailed;
            fnAck(true);
            return ;
        }

        //发送邮件
        TVecItemGenInfo vecItems;
        SItemGenInfo stItemGen;
        stItemGen.wItemID = wItemID;
        stItemGen.dwCount = wCount;
        stItemGen.byQuality = pItemCfg->oItemCfg._Quality;
        stItemGen.eBindType = eBindNone;
        stItemGen.dwTimeID = pItemCfg->oItemCfg._ItemTimeID;
        vecItems.push_back(stItemGen);

        NMailProt::SysMailSendTxt stBody;
        stBody.dwstrMsgID = BODY_PRESENTITEM;
        stBody.vecParam.push_back(strMsg);
        TVecUINT64 vecTargets;
        vecTargets.push_back(qwReceiveID);
        GameServerSysMail::SendSysMail(pUser->GetUserName(), strTitle, stBody, vecTargets, &vecItems);

        //扣钱
        if ((EMoneyType)pMallCfg->_MoneyType == EMONEY_GOLD)
        {
            pUser->SubMoney((EMoneyType)pMallCfg->_MoneyType, pMallCfg->_Price*wCount,NLogDataDefine::ItemTo_MallBuy);
        }

        fnAck->eResult = eMallPresentSucc;
        fnAck(true);
        });
    }
    else
    {
        fnAck->eResult = eMallResultFailed;
        fnAck(true);
        return ;
    }
#endif

    fnAck->eResult = eMallResultFailed;
    fnAck(true);
    return ;
}

/********商城限购 begin*******/

//XXX 是否开启充值仙石限购
void CMall::IsInRechargeDiscount(UINT32& dwPos1EndTime, UINT32& dwPos2EndTime, UINT32& dwPos3EndTime)
{
    UINT32 dwNow = time(NULL);
    for (size_t i=0; i<_vecDiscountItem.size(); ++i)
    {
        SDiscount& oDiscount = _vecDiscountItem[i];
        if (oDiscount.byLimitType == eDiscountLimitTypeRecharge)
        {
            if (oDiscount.dwBeginTime > dwNow || oDiscount.dwEndTime < dwNow)
                continue;

            if (0 == oDiscount.byPos)
                dwPos1EndTime = oDiscount.dwEndTime;
            else if (1 == oDiscount.byPos)
                dwPos2EndTime = oDiscount.dwEndTime;
            else if (2 == oDiscount.byPos)
                dwPos3EndTime = oDiscount.dwEndTime;
        }
    }

    return;
}

//XXX 是否开启消费仙石限购
void CMall::IsInConsumeDiscount(UINT32& dwPos1EndTime, UINT32& dwPos2EndTime, UINT32& dwPos3EndTime)
{
    UINT32 dwNow = time(NULL);
    for (size_t i=0; i<_vecDiscountItem.size(); ++i)
    {
        SDiscount& oDiscount = _vecDiscountItem[i];
        if (oDiscount.byLimitType == eDiscountLimitTypeConsume)
        {
            if (oDiscount.dwBeginTime > dwNow || oDiscount.dwEndTime < dwNow)
                continue;

            if (0 == oDiscount.byPos)
                dwPos1EndTime = oDiscount.dwEndTime;
            else if (1 == oDiscount.byPos)
                dwPos2EndTime = oDiscount.dwEndTime;
            else if (2 == oDiscount.byPos)
                dwPos3EndTime = oDiscount.dwEndTime;
        }
    }

    return;
}

void CMall::CheckMarkID(CUserPtr pUser)
{
    if (!pUser)
        return;

    for (size_t i=0; i<_vecDiscountItem.size(); ++i)
    {
        UINT64 qwMarkID = pUser->GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos1Mark+i);
        if (_vecDiscountItem[i].qwMarkID > qwMarkID)
        {
            pUser->GetVars().DelVar((NVarDefine::ePlayerMallDiscountPos1+i));
            pUser->GetVars().DelVar((NVarDefine::ePlayerMallDiscountPos1Recharge+i));
            pUser->GetVars().DelVar((NVarDefine::ePlayerMallDiscountPos1Consume+i));
            pUser->GetVars().SetVar((NVarDefine::ePlayerMallDiscountPos1Mark+i), _vecDiscountItem[i].qwMarkID);
        }
    }
}

void CMall::AddDiscountFromBS(const SDiscount& oDiscount)
{
    if (oDiscount.byPos > 2)
        return;

    SDiscount oTempDiscount = oDiscount;
    for (size_t i = 0; i < _vecDiscountItem.size(); ++ i)
    {
        if (oTempDiscount.byPos == _vecDiscountItem[i].byPos)
        {
            oTempDiscount.qwMarkID = _vecDiscountItem[i].qwMarkID + 1;
            _vecDiscountItem[i] = oTempDiscount;

            return;
        }
    }
   
    //第一次设置限购栏位
    {
        oTempDiscount.qwMarkID = 100;
        _vecDiscountItem.push_back(oTempDiscount);
    }
}

void CMall::ClearMallDiscount(UINT8 byPos)
{
    for (auto iter=_vecDiscountItem.begin(); iter!=_vecDiscountItem.end(); ++iter)
    {
        if ((*iter).byPos == byPos)
        {
            (*iter).vecDisItems.clear();
            (*iter).byLimitType = 0;
            (*iter).dwLimitValue = 0;
            (*iter).wLimitCount = 0;
            (*iter).dwBeginTime = 0;
            (*iter).dwEndTime = 0;

            return;
        }
    }
}

void CMall::LoadMallDiscount()
{
    g_Game2DBCommC.Send_LoadMallDiscount([this](UINT8 byRet_ /*0为成功，1为失败，2为超时*/, const NMallProt::TVecDiscount& vecDisItems)
        {
            if(0 != byRet_)
            {
                LOG_CRI<<"LoadMallDiscount fail!!";
                return;
            }
            _vecDiscountItem = vecDisItems;
        });
}

void CMall::UpdateDiscountToDB()
{
    g_Game2DBCommC.Send_UpdateMallDiscount(eOpUpdate, _vecDiscountItem);
}

void CMall::SendMallDiscountInfo(CUserPtr pUser)
{
    if (!pUser)
        return;

    CheckMarkID(pUser);

    UINT32 dwNow = time(NULL);
    TVecDiscount vecDiscount;
    for (size_t i = 0; i < _vecDiscountItem.size(); ++ i)
    {
        SDiscount& oDiscount = _vecDiscountItem[i];
        if (oDiscount.dwBeginTime > dwNow || oDiscount.dwEndTime < dwNow)
            continue;

        vecDiscount.push_back(oDiscount);
    }
    UINT32 dwCountPos1 = 0;
    UINT32 dwCountPos2 = 0;
    UINT32 dwCountPos3 = 0;
    UINT32 dwRechargePos1 = 0;
    UINT32 dwRechargePos2 = 0;
    UINT32 dwRechargePos3 = 0;
    UINT32 dwConsumePos1 = 0;
    UINT32 dwConsumePos2 = 0;
    UINT32 dwConsumePos3 = 0;
    if (!vecDiscount.empty())
    {
        dwCountPos1 = pUser->GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos1);
        dwCountPos2 = pUser->GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos2);
        dwCountPos3 = pUser->GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos3);
        dwRechargePos1 = pUser->GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos1Recharge);
        dwRechargePos2 = pUser->GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos2Recharge);
        dwRechargePos3 = pUser->GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos3Recharge);
        dwConsumePos1 = pUser->GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos1Consume);
        dwConsumePos2 = pUser->GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos2Consume);
        dwConsumePos3 = pUser->GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos3Consume);
    }
    string strData = g_MallProtS.BuildPkg_UpdateMallDiscountInfo(
            vecDiscount, 
            dwCountPos1, dwCountPos2, dwCountPos3,
            dwRechargePos1, dwRechargePos2, dwRechargePos3,
            dwConsumePos1, dwConsumePos2, dwConsumePos3);

    pUser->SendPkg(strData);
}

void CMall::SendMallDiscountInfo(const SDiscount& oDiscount)
{
    UINT32 dwNow = time(NULL);
    if (oDiscount.dwBeginTime > dwNow || oDiscount.dwEndTime < dwNow)
        return;

    g_MallProtS.SendClt_UpdateMallDiscountInfoByPos(NULL, 0, oDiscount);
}

EMallResult CMall::BuyDiscountItem(CUserPtr pUser, UINT8 byPos, UINT16 wCount)
{
    if (!pUser || byPos > 2 || !wCount)
        return eMallResultFailed;

    CheckMarkID(pUser);

    UINT32 dwNow = time(NULL);
    UINT32 dwNeedGold = 0;
    TVecItemGenInfo vecItems;
    UINT32 dwExpired = 0;
    for (size_t i = 0; i < _vecDiscountItem.size(); ++ i)
    {
        SDiscount& oDiscount = _vecDiscountItem[i];
        if (oDiscount.byPos == byPos)
        {
            if (oDiscount.dwBeginTime > dwNow || oDiscount.dwEndTime < dwNow)
                return eMallResultDiscountOverTime;

            if (pUser->GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos1+byPos) + wCount > oDiscount.wLimitCount)
                return eMallResultDiscountFull;

            if (oDiscount.byLimitType == eDiscountLimitTypeRecharge)
            {
                if (pUser->GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos1Recharge+byPos) < oDiscount.dwLimitValue)
                    return eMallResultDiscountRechargeErr;
            }
            else if (oDiscount.byLimitType == eDiscountLimitTypeConsume)
            {
                if (pUser->GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos1Consume+byPos) < oDiscount.dwLimitValue)
                    return eMallResultDiscountConsumeErr;
            }

            for (size_t j=0; j<oDiscount.vecDisItems.size(); ++j)
            {
                UINT16 wItemID = oDiscount.vecDisItems[j].wItemID;
                SItemInfo* pItemCfg = CItemMgr::GetItemConfig(wItemID);
                if (!pItemCfg)
                    return eMallResultNoItem;

                dwNeedGold += oDiscount.vecDisItems[j].wDiscountPrice * wCount;
                SItemGenInfo sItemGen;
                sItemGen.wItemID = wItemID;
                sItemGen.dwCount = wCount;
                sItemGen.eBindType = eBindGet;
                sItemGen.byQuality = pItemCfg->oItemCfg._Quality;
                sItemGen.dwTimeID  = pItemCfg->oItemCfg._ItemTimeID;
                vecItems.push_back(sItemGen);
            }
            dwExpired = oDiscount.dwEndTime;
            break;
        }
    }
    if (vecItems.empty())
        return eMallResultFailed;

    if (!pUser->CanSubMoney(EMONEY_GOLD, dwNeedGold))
        return eMallResultMoney;

    CPack& rPack = pUser->GetPack();
    if (!rPack.CanAddItem(vecItems))
        return eMallResultStore;

    UINT16 wBuyCount = pUser->GetVars().GetVar(NVarDefine::ePlayerMallDiscountPos1+byPos) + wCount;
    pUser->GetVars().SetVar(NVarDefine::ePlayerMallDiscountPos1+byPos, wBuyCount, 0, dwExpired);
    
    pUser->SubMoney(EMONEY_GOLD, dwNeedGold,NLogDataDefine::ItemTo_MallBuy);
    
    if (!rPack.AddItem(vecItems, NLogDataDefine::ItemFrom_Mall))
        return eMallResultStoreAdd;

    return eMallResultSucc;
}
/********商城限购 end*******/

void CMall::OnChongZhiAward(UINT16 wGoldID, UINT32 dwCount, CUserPtr pUser)
{
    if ((wGoldID < 41 || wGoldID > 46) && (wGoldID < 180 || wGoldID > 185))
        return;
    if(!pUser || !dwCount)
        return;
    SChongZhiCFGEx* pChongZhiCfg = CItemMgr::GetChongZhiCfg(wGoldID);
    if (!pChongZhiCfg)
        return;
    UINT8 byChongZhi = pUser->GetVars().GetVar(NVarDefine::ePlayerVarChongZhi);
    if (GET_BIT(byChongZhi, (pChongZhiCfg->_Id-1)) > 0)
        return;
    CStore* pStore = pUser->GetStoreByType(eStorePack);
    if (!pStore || !pStore->CanAddItem(pChongZhiCfg->_vecItemAward, true))
        return;
    byChongZhi = SET_BIT(byChongZhi, (pChongZhiCfg->_Id-1));
    pUser->GetVars().SetVar(NVarDefine::ePlayerVarChongZhi, byChongZhi);
    pStore->AddItem(pChongZhiCfg->_vecItemAward, NLogDataDefine::ItemFrom_MallChongZhi);

    string strData = g_MallProtS.BuildPkg_UpdateChongZhiActInfo(pChongZhiCfg->_Id, dwCount, byChongZhi);
    pUser->SendPkg(strData);
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

