// =====================================================================================
//
//       Filename:  BeastSoul.cpp
//
//    Description:  兽魂属性
//
//        Version:  1.0
//        Created:  10/08/2014 04:54:54 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "BeastSoul.h"

#include "FighterMgr.h"
#include "User.h"
#include "Player.h"
#include "FighterManager.h"
#include "GameServerSysMail.h"
#include "Random.h"

#include "Protocols.h"
#include "EventCenter.h"

CBeastSoul::CBeastSoul(CUser& rUser):
     _rUser(rUser)
{
    for (UINT8 byIndex = eBeastSoulNone + 1; byIndex < eBeastSoulMax; ++byIndex)
    {
        EBeastSoulType eType = static_cast<EBeastSoulType>(byIndex);
        SBSInfo sInfo;
        _mapInfo.insert(make_pair(eType, sInfo));
    }
}

CBeastSoul::~CBeastSoul()
{
}

// ===  FUNCTION  ======================================================================
//         Name:  LoadFromDB
//  Description:  从数据库加载
// =====================================================================================
bool CBeastSoul::LoadFromDB (EBeastSoulType eType, UINT8 byRank, UINT8 byLevel)
{
    if (eType <= eBeastSoulNone || eType >= eBeastSoulMax)
    {
        LOG_CRI << "Invalid Type: " << static_cast<UINT32>(eType) << ".";
        return false;
    }
    _mapInfo[eType]._byRank = byRank;
    _mapInfo[eType]._byLevel = byLevel;
    return true;
}		// -----  end of function LoadFromDB  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllInfo
//  Description:  获取所有的兽魂信息
// =====================================================================================
EBeastSoulResult CBeastSoul::GetAllInfo(TVecBeastSoulInfo& vecBeastSoulInfo) const
{
    for (auto& kvInfo: _mapInfo)
    {
        SBeastSoulInfo sInfo;
        sInfo.eType = kvInfo.first;
        sInfo.byRank = kvInfo.second._byRank;
        sInfo.byLevel = kvInfo.second._byLevel;
        vecBeastSoulInfo.push_back(sInfo);
    }
    return eBeastSoulSucces;
}		// -----  end of function GetAllInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AppendAttr
//  Description:  获得加成属性值
// =====================================================================================
bool CBeastSoul::AppendAttr (TVecFloat& vecAttr) const
{
    for (auto& kvInfo: _mapInfo)
    {
        const SBeastSoulLevelConfig* pBeastSoulLevelCFG = CFighterMgr::GetBeastSoulLevelCFG(kvInfo.first, kvInfo.second._byRank, kvInfo.second._byLevel);
        if (!pBeastSoulLevelCFG)
        {
            if (kvInfo.second._byRank || kvInfo.second._byLevel)
                LOG_CRI << "No CFG When GSoulLevelCFGetBeastSoulCFG: " 
                    << "Type: " << static_cast<UINT32>(kvInfo.first) << ", "
                    << "Rank: " << static_cast<UINT32>(kvInfo.second._byRank) << ", "
                    << "Level: " << static_cast<UINT32>(kvInfo.second._byLevel) << ".";
            continue;
        }

        // XXX: 配置上就这么点
        PHYATK_ADD(vecAttr, pBeastSoulLevelCFG);
        MGCATK_ADD(vecAttr, pBeastSoulLevelCFG);
        PHYDEF_ADD(vecAttr, pBeastSoulLevelCFG);
        MGCDEF_ADD(vecAttr, pBeastSoulLevelCFG);
        MAXHP_ADD(vecAttr, pBeastSoulLevelCFG);
        SPEED_ADD(vecAttr, pBeastSoulLevelCFG);
        HIT_ADD(vecAttr, pBeastSoulLevelCFG);
        DODGE_ADD(vecAttr, pBeastSoulLevelCFG);
        CRITICAL_ADD(vecAttr, pBeastSoulLevelCFG);
        COUNTER_ADD(vecAttr, pBeastSoulLevelCFG);
    }
    return true;
}		// -----  end of function AppendAttr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAttrVec
//  Description:  获取加成属性值
// =====================================================================================
TVecFloat CBeastSoul::GetAttrVec () const
{
    TVecFloat vecAttr;
    VECATTR_RESET(vecAttr);
    AppendAttr(vecAttr);
    return vecAttr;
}		// -----  end of function GetAttrVec  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  UpgradeBeastSoul
//  Description:  升级兽魂
// =====================================================================================
EBeastSoulResult CBeastSoul::UpgradeBeastSoul(EBeastSoulType eType, TVecBeastSoulItem& rvecItems)
{
    EBeastSoulResult eResult = eBeastSoulFailed;

    if (eType <= eBeastSoulNone || eType >= eBeastSoulMax)
    {
        LOG_CRI << "Invalid Type: " << static_cast<UINT32>(eType) << ".";
        return eResult;
    }

    bool bRank = false;
    UINT8 byRank = _mapInfo[eType]._byRank;
    UINT8 byLevel = _mapInfo[eType]._byLevel;
    const SBeastSoulLevelConfig* pBeastSoulLevelCFG2 = CFighterMgr::GetBeastSoulLevelCFG(eType, byRank, ++ byLevel);
    if (pBeastSoulLevelCFG2)
    {
        pBeastSoulLevelCFG2 = CFighterMgr::GetBeastSoulLevelCFG(eType, byRank, byLevel + 1);
        if (!pBeastSoulLevelCFG2)
            bRank = true;
    }
    else
    {
        byLevel = 1;
        pBeastSoulLevelCFG2 = CFighterMgr::GetBeastSoulLevelCFG(eType, ++ byRank, byLevel);
        if (!pBeastSoulLevelCFG2)
        {
            eResult = eBeastSoulRankMax;
            return eResult;
        }
    }

    const SBeastSoulLevelConfig* pBeastSoulLevelCFG = CFighterMgr::GetBeastSoulLevelCFG(eType, byRank, byLevel);
    if (!pBeastSoulLevelCFG)
    {
        LOG_CRI << "No CFG When GSoulLevelCFGetBeastSoulCFG: " 
            << "Type: " << static_cast<UINT32>(eType) << ", "
            << "Rank: " << static_cast<UINT32>(_mapInfo[eType]._byRank) << ", "
            << "Level: " << static_cast<UINT32>(_mapInfo[eType]._byLevel) << ".";
        return eResult;
    }
    else if (pBeastSoulLevelCFG->_RoleLevel > _rUser.GetLevel())
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgRoleLevelErr);
        _rUser.SendPkg(strPkg);
        return eResult;
    }
    string strMoneyType;
    switch(eType)
    {
        case eBeastSoulAtttack: //攻击之魂
            if (_rUser.CanSubMoney(EMONEY_SOULATTACK,pBeastSoulLevelCFG->_Cost))
            {
                _rUser.SubMoney(EMONEY_SOULATTACK,pBeastSoulLevelCFG->_Cost,NLogDataDefine::ItemTo_UpgradeBeastSoul);
                eResult = eBeastSoulSucces;
            }
            else
            {
                strMoneyType = NProtoCommon::GetDescription(EMONEY_SOULATTACK);
                eResult = eBeastSoulLackOfMoney;
            }
            break;
        case eBeastSoulHP: //生命之魂
            if (_rUser.CanSubMoney(EMONEY_SOULHP,pBeastSoulLevelCFG->_Cost))
            {
                _rUser.SubMoney(EMONEY_SOULHP,pBeastSoulLevelCFG->_Cost,NLogDataDefine::ItemTo_UpgradeBeastSoul);
                eResult = eBeastSoulSucces;
            }
            else
            {
                strMoneyType = NProtoCommon::GetDescription(EMONEY_SOULHP);
                eResult = eBeastSoulLackOfMoney;
            }
            break;
        case eBeastSoulCritical: //暴击之魂
            if (_rUser.CanSubMoney(EMONEY_SOULCRITICAL,pBeastSoulLevelCFG->_Cost))
            {
                _rUser.SubMoney(EMONEY_SOULCRITICAL,pBeastSoulLevelCFG->_Cost,NLogDataDefine::ItemTo_UpgradeBeastSoul);
                eResult = eBeastSoulSucces;
            }
            else
            {
                strMoneyType = NProtoCommon::GetDescription(EMONEY_SOULCRITICAL);
                eResult = eBeastSoulLackOfMoney;
            }
            break;
        case eBeastSoulCounter: //反击之魂
            if (_rUser.CanSubMoney(EMONEY_SOULCOUNTER,pBeastSoulLevelCFG->_Cost))
            {
                _rUser.SubMoney(EMONEY_SOULCOUNTER,pBeastSoulLevelCFG->_Cost,NLogDataDefine::ItemTo_UpgradeBeastSoul);
                eResult = eBeastSoulSucces;
            }
            else
            {
                strMoneyType = NProtoCommon::GetDescription(EMONEY_SOULCOUNTER);
                eResult = eBeastSoulLackOfMoney;
            }
            break;
        case eBeastSoulSpeed: //身法之魂
            if (_rUser.CanSubMoney(EMONEY_SOULSPEED,pBeastSoulLevelCFG->_Cost))
            {
                _rUser.SubMoney(EMONEY_SOULSPEED,pBeastSoulLevelCFG->_Cost,NLogDataDefine::ItemTo_UpgradeBeastSoul);
                eResult = eBeastSoulSucces;
            }
            else
            {
                strMoneyType = NProtoCommon::GetDescription(EMONEY_SOULSPEED);
                eResult = eBeastSoulLackOfMoney;
            }
            break;
        case eBeastSoulDefence: //防御之魂
            if (_rUser.CanSubMoney(EMONEY_SOULDEFENCE,pBeastSoulLevelCFG->_Cost))
            {
                _rUser.SubMoney(EMONEY_SOULDEFENCE,pBeastSoulLevelCFG->_Cost,NLogDataDefine::ItemTo_UpgradeBeastSoul);
                eResult = eBeastSoulSucces;
            }
            else
            {
                strMoneyType = NProtoCommon::GetDescription(EMONEY_SOULDEFENCE);
                eResult = eBeastSoulLackOfMoney;
            }
            break;
        case eBeastSoulHit: //命中之魂
            if (_rUser.CanSubMoney(EMONEY_SOULHIT,pBeastSoulLevelCFG->_Cost))
            {
                _rUser.SubMoney(EMONEY_SOULHIT,pBeastSoulLevelCFG->_Cost,NLogDataDefine::ItemTo_UpgradeBeastSoul);
                eResult = eBeastSoulSucces;
            }
            else
            {
                strMoneyType = NProtoCommon::GetDescription(EMONEY_SOULHIT);
                eResult = eBeastSoulLackOfMoney;
            }
            break;
        case eBeastSoulDodge: //闪避之魂
            if (_rUser.CanSubMoney(EMONEY_SOULDODGE,pBeastSoulLevelCFG->_Cost))
            {
                _rUser.SubMoney(EMONEY_SOULDODGE,pBeastSoulLevelCFG->_Cost,NLogDataDefine::ItemTo_UpgradeBeastSoul);
                eResult = eBeastSoulSucces;
            }
            else
            {
                strMoneyType = NProtoCommon::GetDescription(EMONEY_SOULDODGE);
                eResult = eBeastSoulLackOfMoney;
            }
            break;
        default:
            break;
    }
    if (eResult == eBeastSoulLackOfMoney)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgShouHunNotEnough, BuildStrVec(strMoneyType));
        _rUser.SendPkg(strPkg);
        return eResult;
    }
    else if (eResult != eBeastSoulSucces)
        return eResult;
    UINT16 wRand = CRandom::RandInt(0, 9999);
    if (wRand >= pBeastSoulLevelCFG->_Chance)
    {
        eResult = eBeastSoulFailed;
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgShouHunFailed);
        _rUser.SendPkg(strPkg);
        return eResult;
    }

    if (bRank)
    {
        //LOG_WRN << "byRank = " << static_cast<UINT32>(byRank) << ".";
        const SBeastSoulRankConfig* pRankConfig = CFighterMgr::GetBeastSoulRankCFG(eType, byRank);
        if (!pRankConfig)
            LOG_CRI << "No Rank Info: " << static_cast<UINT32>(eType) << ", " << static_cast<UINT32>(byRank) << ".";
        else
        {
            TVecItemGenInfo vecGenItem;
            for (auto& rItem : pRankConfig->_vecAward)
            {
                SItemGenInfo sInfo;
                sInfo.wItemID = rItem.wItemID;
                sInfo.dwCount = rItem.dwCount;
                vecGenItem.push_back(sInfo);
                //LOG_WRN << "AddItem: " << rItem.wItemID << "(" << rItem.dwCount << ").";
                SBeastSoulItem sBSItem;
                sBSItem.wItemID = sInfo.wItemID;
                sBSItem.dwCount = sInfo.dwCount;
                rvecItems.push_back(sBSItem);
            }
            if(!vecGenItem.empty())
            {
                CPack& oPack = _rUser.GetPack();
                if(!oPack.CanAddItem(vecGenItem))//包裹放不进
                {
                    //发送邮件
                    NMailProt::SysMailSendTxt stBody;
                    stBody.dwstrMsgID = BODY_BEASTSOUL_AWARD;
                    TVecUINT64 vecTargets;
                    vecTargets.push_back(_rUser.GetUserID());
                    GameServerSysMail::SendSysMail(TITLE_BEASTSOUL_AWARD,TITLE_BEASTSOUL_AWARD,stBody,vecTargets,&vecGenItem);
                }
                else
                    oPack.AddItem(vecGenItem,NLogDataDefine::ItemFrom_BeastSoul);
            }
        }
    }
    _mapInfo[eType]._byRank = byRank;
    _mapInfo[eType]._byLevel = byLevel;
    Update2DB(eType);
    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(pPlayer)
    {
        CFighterManagerPtr& pFighterManager = pPlayer->GetFighterManager();
        if(pFighterManager)
            pFighterManager->SetDirty(eAttrGpBeastSoul);


        //onEvent
        TVecINT32 vecParam;
        vecParam.push_back(eType);
        vecParam.push_back(byLevel);
        vecParam.push_back(byRank);
        for(auto itr = _mapInfo.begin(); itr != _mapInfo.end(); itr++)
        {
            vecParam.push_back(itr->second._byLevel);
            vecParam.push_back(itr->second._byRank);
        }
        pPlayer->OnEvent(NEventCenter::eEventType_BeastUpgrade,vecParam);

        {
            TVecINT32 vecParam;
            vecParam.push_back(pBeastSoulLevelCFG->_ID);
            pPlayer->OnEvent(NEventCenter::eEventType_BeastSoulActive,vecParam);
        }
    }
    if(eBeastSoulSucces == eResult)
    {
        _rUser.GetTaskPkg().OnAction(*pPlayer, eProcessAction_GetBeast);
        _rUser.GetTaskPkg().OnAction(*pPlayer,eProcessAction_BeastUpLevel);
    }

    return eResult;
}		// -----  end of function UpgradeBeastSoul  ----- //

void CBeastSoul::Update2DB(EBeastSoulType eType)
{
    auto it = _mapInfo.find(eType);
    if (it == _mapInfo.end())
        return;

    string strData;
    COutArchive iar(strData);
    SBeastSoulInfo sInfo;
    sInfo.eType = it->first;
    sInfo.byRank = it->second._byRank;
    sInfo.byLevel = it->second._byLevel;
    iar << sInfo;

    g_Game2DBCommC.Send_RoleDataUpdate(_rUser.GetUserID(), eTypeBeastSoulInfo, eOpUpdate, strData);
}

bool CBeastSoul::FindBeastSoul(EBeastSoulType eType, UINT8 byRank, UINT8 byLevel)
{
    auto it = _mapInfo.find(eType);
    if (it == _mapInfo.end())
        return false;

    if (eType != it->first)
        return false;
    if (0 == it->second._byRank)
        return false;

    if (0 == it->second._byLevel)
        return false;

    return true;
}
