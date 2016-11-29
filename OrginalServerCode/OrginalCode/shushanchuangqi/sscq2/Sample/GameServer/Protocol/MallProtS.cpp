
#include "stdafx.h"
#include "Protocols.h"
#include "MallProtS.h"
#include "ItemMgr.h"
#include "Mall.h"
#include "ShopItemMgr.h"
#include "Player.h"
#include "Tokenizer.h"
#include "GameNetMgr.h"

//接收：预览商城信息
bool CMallProtS::OnRecv_MalGet(
        EMallType eType, //商城类型
        shared_func<SMalGetAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if (!pPlayer)
        return false;

    const std::vector<SMallCFG>* pCfg = CItemMgr::GetMallCfg((UINT8)eType);
    if (!pCfg)
        return false;

    const std::vector<SMallCFG>& rCfg = *pCfg;
    for (size_t i = 0; i < pCfg->size(); ++i)
    {
        const SMallCFG& rMallCfg = rCfg[i];
       
        UINT32 dwLimit = 0;
        UINT8 byVIPLevel = pUser->GetVIPLevel();
        Tokenizer tk(rMallCfg._DayCntLimit, "|");
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

        fnAck->vecMallInfo.push_back(SMallInfo(rMallCfg._Id,rMallCfg._Name,rMallCfg._ItemId,rMallCfg._ItemNum,
                    (EMoneyType)rMallCfg._MoneyType, rMallCfg._Price, rMallCfg._VIP,rMallCfg._Icon,dwLimit));
    }

    return true;
}

//接收：商场购买
bool CMallProtS::OnRecv_MalBuy(
		EUseMoneyMark eMark, //使用钱币标志
        EMallType eType, //商城类型
        UINT32 wInstID, //实例ID
		UINT16 wCount, //物品个数
        shared_func<SMalBuyAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eMallResultFailed;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if (!pPlayer)
    {
        fnAck->eResult = eMallResultFailed;
        return false;
    }

    fnAck->eResult = CMall::Instance().BuyItem(*pUser, eMark, eType, wInstID, wCount);
    return true;
}

//接收：商场赠送
bool CMallProtS::OnRecv_MallPresent(
		EUseMoneyMark eMark, //使用钱币标志
		EMallType eType, //商城类型
        UINT32 wInstID, //实例ID
		UINT16 wCount, //物品个数
		const std::string& strReceiveName, //接受者姓名
		const std::string& strTitle, //邮件标题
		const std::string& strMsg, //邮件内容
		shared_func<SMallPresentAck>& fnAck //返回回调函数
        ) 
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eMallResultFailed;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if (!pPlayer)
    {
        fnAck->eResult = eMallResultFailed;
        return false;
    }

    CMall::Instance().PresentItem(*pUser, eMark, eType, wInstID, wCount, strReceiveName, strTitle, strMsg, fnAck);

    return true;
}

//接收：获取物品购买数量列表
bool CMallProtS::OnRecv_GetBuyItemList(
		shared_func<SGetBuyItemListAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        //fnAck->eResult = eMallResultFailed;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if (!pPlayer)
    {
        //fnAck->eResult = eMallResultFailed;
        return false;
    }

    CShopItemMgrPtr pShopItemMgr = pPlayer->GetShopItemMgr();
    if(NULL == pShopItemMgr)
    {
        return false;
    }

    pShopItemMgr->GetShopItemList(fnAck->vecBuyItemInfo);

    return true;

}

//接收：预览商城限购信息
void CMallProtS::OnRecv_GetMallDiscountInfo(
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return;

    CMall::Instance().SendMallDiscountInfo(pUser);
}

//接收：购买商场限购道具
bool CMallProtS::OnRecv_BuyDiscountItem(
    UINT8 byPos, //限购位置(0,1,2)
    UINT16 wCount, //购买个数
    shared_func<SBuyDiscountItemAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eMallResultFailed;
        return false;
    }
    fnAck->eResult = CMall::Instance().BuyDiscountItem(pUser, byPos, wCount);
    fnAck->byPos  = byPos;
    fnAck->wCount = wCount;

    return true;
}

//接收：获取玩家首次充值活动完成信息(在商城界面的奖励)
void CMallProtS::OnRecv_GetChongZhiActInfo()
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return;

    UINT8 byChongZhi = pUser->GetVars().GetVar(NVarDefine::ePlayerVarChongZhi);
    string strData = g_MallProtS.BuildPkg_UpdateChongZhiActInfo(0, 0, byChongZhi);
    pUser->SendPkg(strData);
    return;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

