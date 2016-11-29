
#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "GetCondMgr.h"
#include "ItemMgr.h"
#include "FighterManager.h"
#include "GameScript.h"
#include "Tokenizer.h"
#include "VarDefine.h"
#include "HeroFighter.h"

using namespace NVarDefine;

bool CGetCondMgr::Init()
{
    return LoadConfig();
}

bool CGetCondMgr::LoadConfig(bool bReload)
{
    string strPath = Config._strConfigDir + "Conf/Table/GetCond.xml";
    {
        CGetCondLoader oGetCondLoader;
        if(!oGetCondLoader.LoadData(strPath))
        {
            LOG_CRI << "oGetCondLoader.LoadData fails! Path: " << strPath;
            return false;
        }

        for(size_t i = 0; i < oGetCondLoader._vecData.size(); ++i)
        {
            SGetCondCFG* pGetCondCfg = oGetCondLoader._vecData[i];
            SGetCondCFGEx& rGetCondCfg = _mapID2GetCondInfo[pGetCondCfg->_ID];
            rGetCondCfg = static_cast<SGetCondCFGEx>(*pGetCondCfg);
            {
                Tokenizer tk(rGetCondCfg._Money, "|");
                for (size_t i = 0; i < tk.size(); ++i)
                {
                    Tokenizer yatk(tk[i], ",");
                    if (yatk.size())
                    {
                        UINT8 byType = atoi(yatk[0].c_str());
                        UINT32 dwCount = 1;
                        if (yatk.size() > 1)
                            dwCount = atoi(yatk[1].c_str());

                        if (byType && (EMoneyType)byType < EMONEY_END)
                            rGetCondCfg.vecMoney.push_back(SMoneyCount((EMoneyType)byType, dwCount));
                    }
                }
            }
            {
                Tokenizer tk(rGetCondCfg._ItemID, "|");
                for (size_t i = 0; i < tk.size(); ++i)
                {
                    Tokenizer yatk(tk[i], ",");
                    if (yatk.size())
                    {
                        UINT16 wItemID = atoi(yatk[0].c_str());
                        UINT32 dwCount = 1;
                        if (yatk.size() > 1)
                            dwCount = atoi(yatk[1].c_str());

                        if (wItemID && CItemMgr::GetItemConfig(wItemID))
                            rGetCondCfg.vecItem.push_back(SItemCount(wItemID, dwCount));
                    }
                }
            }
            {
                Tokenizer tk(rGetCondCfg._DungeonID, ",");
                for (size_t i = 0; i < tk.size(); ++i)
                {
                    UINT32 dwDgnID = atoi(tk[i].c_str());
                    if (dwDgnID)
                        rGetCondCfg.vecDgnID.push_back(dwDgnID);
                }
            }
            {
                Tokenizer tk(rGetCondCfg._TaskID, ",");
                for (size_t i = 0; i < tk.size(); ++i)
                {
                    UINT32 dwTaskID = atoi(tk[i].c_str());
                    if (dwTaskID)
                        rGetCondCfg.vecTaskID.push_back(dwTaskID);
                }
            }
            {
                Tokenizer tk(rGetCondCfg._PreHero, ",");
                for (size_t i = 0; i < tk.size(); ++i)
                {
                    UINT16 wFighterID = atoi(tk[i].c_str());
                    if (wFighterID)
                        rGetCondCfg.vecPreHero.push_back(wFighterID);
                }
            }
        }
    }

    return true;
}

bool CGetCondMgr::TestCond(CUser& rUser, UINT16 wCondID,UINT16 fromwhere, bool bNodify /* = false */)
{
    CPlayerPtr pPlayer = rUser.GetPlayer();
    if (!pPlayer)
        return false;

    auto i = _mapID2GetCondInfo.find(wCondID);
    if (i == _mapID2GetCondInfo.end())
        return false;

    SGetCondCFGEx& rGetCondCfg = i->second;

    for (size_t i = 0; i < rGetCondCfg.vecMoney.size(); ++i)
    {
        if(0 == rGetCondCfg.vecMoney[i].eMoneyType)
        {
        }
        else if(rGetCondCfg.vecMoney[i].eMoneyType == EMONEY_ACTION)
        {
            if (!rUser.CanSubAction(rGetCondCfg.vecMoney[i].dwCount))
                return false;
        }
        else
        {
            if(!rUser.CanSubMoney((EMoneyType)rGetCondCfg.vecMoney[i].eMoneyType,rGetCondCfg.vecMoney[i].dwCount))
            {
                if (bNodify)
                {
                    switch((EMoneyType)rGetCondCfg.vecMoney[i].eMoneyType)
                    {
                        case EMONEY_GOLD: //仙石
                            {
                                string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDrawGoldLack);
                                rUser.SendPkg(strPkg);
                            }
                            break;
                        case EMONEY_SILVER: //银币
                            {
                                string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgDrawSilverLack);
                                rUser.SendPkg(strPkg);
                            }
                            break;
                        case EMONEY_COUPON: //礼券
                            /*
                            {
                                string strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgGetEXP, 
                                        BuildStrVec(pMainFighter->GetColor(), pMainFighter->GetName(), qwExp));
                                rUser.SendPkg(strPkg);
                            }
                            */
                            break;
                        case EMONEY_BLUEFAIRYFATE:
                        case EMONEY_PURPLEFAIRYFATE:
                        case EMONEY_ORANGEFAIRYFATE:
                            {
                                string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgInviteFateLack);
                                rUser.SendPkg(strPkg);
                            }
                            break;
                        default:
                            break;

                    }

                }
                return false;
            }
        }
    }

    if (rUser.GetLevel() < rGetCondCfg._Level)
    {
        // TODO: Notify
        return false;
    }

    CPack& rPack = rUser.GetPack();
    for (size_t i = 0; i < rGetCondCfg.vecItem.size(); ++i)
    {
        if (rPack.GetItemCount(rGetCondCfg.vecItem[i].wItemID) < rGetCondCfg.vecItem[i].wCount)
        {
            // TODO: Notify
            return false;
        }
    }

    for(auto iter = rGetCondCfg.vecDgnID.begin();iter != rGetCondCfg.vecDgnID.end();iter++)
    {

        if (!pPlayer->GetDgnPkg().IsDgnPassed(*iter))
            return false;
    }

    for (size_t i = 0; i < rGetCondCfg.vecTaskID.size(); ++i)
    {
        if (!rUser.GetTaskPkg().IsTaskFinished(rGetCondCfg.vecTaskID[i]))
            return false;
    }

    // TODO: FriendCount

    if (rGetCondCfg._VipLevel && rUser.GetVIPLevel() < rGetCondCfg._VipLevel)
    {
        // TODO: Notify
        return false;
    }

    if (rUser.GetVars().GetVar(NVarDefine::ePlayerVarRecharge) < rGetCondCfg._Recharge)
    {
        // TODO: Notify
        return false;
    }

    if (rUser.GetVars().GetVar(NVarDefine::ePlayerVarConsume) < rGetCondCfg._Consume)
    {
        // TODO: Notify
        return false;
    }

    CFighterManagerPtr& pFighterManager = pPlayer->GetFighterManager();
    for (size_t i = 0; i < rGetCondCfg.vecPreHero.size(); ++i)
    {
        CFighterPtr pFighter = pFighterManager->GetFighterByID(rGetCondCfg.vecPreHero[i]);
        if (!pFighter || !pFighter->GetRecruited())
            return false;
    }

    if (pPlayer->GetGuildLevel() < rGetCondCfg._GuildLevel)
        return false;
    
    CHeroFighterPtr pMainFighter = pPlayer->GetMainFighter();
    if (!pMainFighter)
        return false;

    if (pMainFighter->GetDujieLevel() < rGetCondCfg._DujieLevel)
        return false;

    return true;
}

bool CGetCondMgr::ProcessCond(CUser& rUser, UINT16 wCondID, UINT16 towhere)
{

    auto i = _mapID2GetCondInfo.find(wCondID);
    if (i == _mapID2GetCondInfo.end())
        return false;

    SGetCondCFGEx& rGetCondCfg = i->second;

    for (size_t i = 0; i < rGetCondCfg.vecMoney.size(); ++i)
    {
        if(rGetCondCfg.vecMoney[i].eMoneyType)
        {
            if(rGetCondCfg.vecMoney[i].eMoneyType == EMONEY_ACTION)
            {
                if(!rUser.SubAction(rGetCondCfg.vecMoney[i].dwCount,towhere))
                    return false;
            }

            if (!rUser.SubMoney((EMoneyType)(rGetCondCfg.vecMoney[i].eMoneyType),rGetCondCfg.vecMoney[i].dwCount,(NLogDataDefine::ItemTo)towhere))
            {
                return false;
            }
        }
    }
    CPack& rPack = rUser.GetPack();
    for (size_t i = 0; i < rGetCondCfg.vecItem.size(); ++i)
    {
        if (!rPack.DelItemByItemID(rGetCondCfg.vecItem[i].wItemID, rGetCondCfg.vecItem[i].wCount, true, towhere))
            return false;
    }
    for (size_t i = 0; i < rGetCondCfg.vecTaskID.size(); ++i)
    {
        if (!rGetCondCfg.vecTaskID[i])
            continue;
        if (!rUser.GetTaskPkg().FinishTask(rGetCondCfg.vecTaskID[i], 0, 0))
            return false;
    }

    return true;
}

SGetCondCFGEx* CGetCondMgr::GetGetCondMgrCFG(UINT16 wCondID)
{
    auto iter = _mapID2GetCondInfo.find(wCondID);
    if (iter == _mapID2GetCondInfo.end())
        return NULL;

    return &iter->second;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

