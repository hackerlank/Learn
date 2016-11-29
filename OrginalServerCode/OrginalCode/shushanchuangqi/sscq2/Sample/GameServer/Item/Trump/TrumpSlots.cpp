#include "TrumpSlots.h"
#include "User.h"
#include "Player.h"
#include "Trump.h"
#include "TrumpMgr.h"
#include "ItemMgr.h"
#include "FighterManager.h"
#include "GetCondMgr.h"
#include "Map.h"
#include "EventMgr.h"
#include "BoostMgr.h"

#include "Random.h"
#include "RankProt.h"
#include "Protocols.h"
#include "HeroFighter.h"


using namespace NRankProt;

CTrumpSlots::CTrumpSlots(CUserPtr pUser) : 
    CStore(0), _pUser(pUser), _wActiveIndex(-1)
{
    for (UINT8 byIndex = 0; byIndex < MAX_PASSIVE_COUNT; ++byIndex)
    {
        _wPassiveIndex[byIndex] = -1;
    }
}

CTrumpSlots::~CTrumpSlots()
{
}

EStoreType CTrumpSlots::GetStoreType() const 
{ 
    return eStorePlayerTrump; 
}

CUser& CTrumpSlots::GetUser()
{
    return *(_pUser.lock());
}

CUser& CTrumpSlots::GetUser() const
{
    return *(_pUser.lock());
}

CUserPtr CTrumpSlots::GetUserPtr()
{
    return _pUser.lock();
}


void CTrumpSlots::SetDirty(EAttrGroupType eType) const
{
    CPlayerPtr pPlayer = GetUser().GetPlayer();
    if (!pPlayer)
        return;
    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
        return;
    pFighterManager->SetDirty(eType);
}

bool CTrumpSlots::AddItem(CItem& rItem, INT16 wIndex/* = -1*/, bool bNotify /*= true*/, bool bNew/* = false*/, bool bUpdate/* = true*/, UINT16 fromwhere/* = 0*/)
{
    CStore::AddItem(rItem, wIndex, bNotify, bNew, bUpdate, fromwhere);
    CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(ToThisPtr(rItem));
    if (!pTrump || !pTrump->GetUsed())
        return true;
    switch (pTrump->GetItemSubType())
    {
        case eItemSubActiveTrump:
            _wActiveIndex = wIndex;
            break;
        case eItemSubPassiveTrump:
            {
                UINT8 byUsed = pTrump->GetUsed();
                for (UINT8 byIndex = 0; byIndex < MAX_PASSIVE_COUNT; ++byIndex)
                {
                    if (byUsed == byIndex+1)
                    {
                        _wPassiveIndex[byIndex] = wIndex;
                        break;
                    }
                }
            }
            break;
        default:
            break;
    }
    return true;
}

// 激活法宝
ETrumpResult CTrumpSlots::ActiveTrump(UINT16 wItemID, bool bForce /* = false */)
{
    TVecTrump vecTrump;
    return ActiveTrump(wItemID, vecTrump, bForce);
}

// 激活法宝
ETrumpResult CTrumpSlots::ActiveTrump(UINT16 wItemID, TVecTrump& vecTrump, bool bForce /* = false */)
{
    if (GetItemCount(wItemID))
        return eTrumpExist;

    // 条件解锁
    if (!bForce)
    {
        SItemInfo* pItemInfo = CItemMgr::GetItemConfig(wItemID);
        if (!pItemInfo)
            return eTrumpActiveFailed;
        UINT16 wCondID = pItemInfo->oItemCfg._Cond;
        if (wCondID > 0)
        {
            if (!CGetCondMgr::Instance().TestCond(GetUser(), wCondID))
                return eTrumpActiveFailed;
            if (!CGetCondMgr::Instance().ProcessCond(GetUser(), wCondID, NLogDataDefine::ItemTo_TrumpActive))
                return eTrumpActiveFailed;
        }
    }

    CTrumpPtr pTrump = CItemMgr::CreateTrump(wItemID);
    if (!pTrump)
        return eTrumpFailed;
    pTrump->SetRoleID(GetUser().GetUserID());

    if (!GetEmptyCount()) // 如果背包格子不够，开一个给新法宝
        Expand(TRUMP_SLOTS_COUNT);
    if (!AddItem(*pTrump, -1, true, false, true, NLogDataDefine::ItemFrom_ActiveTrump))
        return eTrumpFailed;

    SetDirty(eAttrGpTrumpHalo);
    SetDirty(eAttrGpTrumpActive);
    UpdateRankInfo();

    STrumpPtr pTrumpStream = STrumpPtr(new STrump);
    if (!pTrumpStream || !pTrump->ToStream(*pTrumpStream))
        return eTrumpNotifyFailed;
    vecTrump.push_back(pTrumpStream);

    //获得法宝
    CPlayerPtr pPlayer = GetUser().GetPlayer();
    if(pPlayer)
    {
        //Event事件
        TVecINT32 vecParam;
        vecParam.push_back(wItemID);
        pPlayer->OnEvent(eEventType_TrumpActive, vecParam);
        g_Game2CenterCommC.Send_SendWonderType(NGame2CenterComm::eActTrump,pPlayer->GetRoleID(),wItemID);
        if(pTrump->GetQuality() >= NProtoCommon::ECOLOR_PURPLE)
        {
            SItem_Wrapper wrapper; 
            wrapper.ptr = pTrumpStream;
            NGlobalChatProt::SShowInfo stShow;
            stShow.qwInstID = pPlayer->GetUserID();
            COutArchive iar(stShow.strShowInfo);
            iar << UINT8(NGlobalChatProt::eShowItem);
            iar << wrapper;
            NGlobalChatProt::TVecShowInfo vecShow;
            TVecString vecstring; 
            vecstring.push_back(NumberToString(pPlayer->GetColor()));
            vecstring.push_back(pPlayer->GetName());
            vecShow.push_back(stShow);
            g_ChatProtS.SendClt_SystemFormatMsgIDNotifyWithShow(NULL,0,eMsgPurpleMagicGet,vecstring,vecShow);

        }
    }
    return eTrumpSuccess;
}

// 出战法宝
ETrumpResult CTrumpSlots::EquipTrump(UINT64 qwInstID, TVecTrump& vecTrump)
{
    INT16 wIndex = GetIndexByInst(qwInstID);
    if (wIndex < 0)
        return eTrumpNotExist;
    CItemPtr pItem = GetItem(qwInstID);
    if (!pItem || !pItem->IsTrumpItem())
        return eTrumpNotExist;
    CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(pItem);
    if (!pTrump)
        return eTrumpNotExist;
    switch (pTrump->GetItemSubType())
    {
        case eItemSubActiveTrump:
            if (_wActiveIndex == wIndex)
                return eTrumpIsEquiped;
            if (_wActiveIndex >= 0)
            {
                CItemPtr pItem = GetItem(_wActiveIndex);
                if (!pItem)
                {
                    LOG_WRN << "Err when EquipTrump : wIndex = " << _wActiveIndex << ".";
                    return eTrumpFull;
                }
                else
                {
                    CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(pItem);
                    TVecTrump vecTrump2;
                    UINT64 qwInstID2 = pTrump->GetInstID();
                    ETrumpResult eResult = UnEquipTrump(qwInstID2, vecTrump2);
                    if (eResult != eTrumpSuccess)
                        return eTrumpFull;
                }
            }
            _wActiveIndex = wIndex;
            pTrump->SetUsed(1);
            break;
        case eItemSubPassiveTrump:
            {
                bool bCanEquip = false;
                for (UINT8 byIndex = 0; byIndex < MAX_PASSIVE_COUNT; ++byIndex)
                {
                    if (_wPassiveIndex[byIndex] == wIndex)
                        return eTrumpIsEquiped;
                }
                for (UINT8 byIndex = 0; byIndex < MAX_PASSIVE_COUNT; ++byIndex)
                {
                    if (_wPassiveIndex[byIndex] < 0)
                    {
                        _wPassiveIndex[byIndex] = wIndex;
                        pTrump->SetUsed(byIndex+1);
                        bCanEquip = true;
                        break;
                    }
                }
                if (!bCanEquip) // 没有空位，直接换第一个法宝
                {
                    CItemPtr pItem = GetItem(_wPassiveIndex[0]);
                    if (!pItem)
                    {
                        LOG_WRN << "Err when EquipTrump : wIndex = " << _wPassiveIndex[0] << ".";
                        return eTrumpFull;
                    }
                    else
                    {
                        CTrumpPtr pTrump2 = dynamic_pointer_cast<CTrump>(pItem);
                        TVecTrump vecTrump2;
                        UINT64 qwInstID2 = pTrump2->GetInstID();
                        ETrumpResult eResult = UnEquipTrump(qwInstID2, vecTrump2);
                        if (eResult != eTrumpSuccess)
                            return eTrumpFull;
                        _wPassiveIndex[0] = wIndex;
                        pTrump->SetUsed(0+1);
                    }
                }
            }
            break;
        default:
            return eTrumpNotExist;
    }
    CItem::Update2DB(*pTrump, GetUser().GetUserID(), GetUser().GetUserID(), GetStoreType(), wIndex, eOpUpdate);
    CItem::ItemChangeNotify(GetUser(), *pTrump, GetStoreType(), wIndex, GetUser().GetUserID());
    SetDirty(eAttrGpTrumpHalo);
    SetDirty(eAttrGpTrumpExtra);
    UpdateRankInfo();

    STrumpPtr pTrumpStream = STrumpPtr(new STrump);
    if (!pTrumpStream || !pTrump->ToStream(*pTrumpStream))
        return eTrumpNotifyFailed;
    vecTrump.push_back(pTrumpStream);

    GetUser().GetTaskPkg().OnAction(*(GetUser().GetPlayer()), eProcessAction_GetTrump, 1);

    CGameMapPtr pMap = GetUser().GetPlayer()->GetMap();
    if (pMap)
        pMap->AppearToSurround(*GetUser().GetPlayer());
    CPlayerPtr pPlayer = GetUser().GetPlayer();
    if (pPlayer)
    {
        TVecINT32 vecParam;
        CTrumpPtr pTrump2 = GetActiveTrump();
        if (pTrump2)
            vecParam.push_back(pTrump2->GetID());
        vector<CTrumpPtr> vecTrumpPtr = GetPassiveTrump();
        for (auto& p : vecTrumpPtr)
        {
            if (p)
                vecParam.push_back(p->GetID());
        }
        pPlayer->OnEvent(eEventType_TrumpEquiping, vecParam);
    }
    return eTrumpSuccess;
}

// 卸下法宝
ETrumpResult CTrumpSlots::UnEquipTrump(UINT64 qwInstID, TVecTrump& vecTrump)
{
    INT16 wIndex = GetIndexByInst(qwInstID);
    if (wIndex < 0)
        return eTrumpNotExist;
    CItemPtr pItem = GetItem(qwInstID);
    if (!pItem || !pItem->IsTrumpItem())
        return eTrumpNotExist;
    CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(pItem);
    if (!pTrump)
        return eTrumpNotExist;

    bool bIsEquiped = false;
    if (wIndex == _wActiveIndex)
    {
        bIsEquiped = true;
        _wActiveIndex = -1;
        pTrump->SetUsed(0);
    }
    for (UINT8 byIndex = 0; byIndex < MAX_PASSIVE_COUNT; ++byIndex)
    {
        if (wIndex == _wPassiveIndex[byIndex])
        {
            bIsEquiped = true;
            _wPassiveIndex[byIndex] = -1;
            pTrump->SetUsed(0);
            break;
        }
    }

    CItem::Update2DB(*pTrump, GetUser().GetUserID(), GetUser().GetUserID(), GetStoreType(), wIndex, eOpUpdate);
    CItem::ItemChangeNotify(GetUser(), *pTrump, GetStoreType(), wIndex, GetUser().GetUserID());
    //SetDirty(eAttrGpTrumpHalo);
    SetDirty(eAttrGpTrumpExtra);
    UpdateRankInfo();

    STrumpPtr pTrumpStream = STrumpPtr(new STrump);
    if (!pTrumpStream || !pTrump->ToStream(*pTrumpStream))
        return eTrumpNotifyFailed;
    vecTrump.push_back(pTrumpStream);

    CGameMapPtr pMap = GetUser().GetPlayer()->GetMap();
    if (pMap)
        pMap->AppearToSurround(*GetUser().GetPlayer());
    if (bIsEquiped)
        return eTrumpSuccess;
    else
        return eTrumpNotEquiped;

}

// 祭炼法宝
ETrumpResult CTrumpSlots::UpgradeTrump(UINT64 qwInstID, UINT8 byOneKey, TVecTrump& vecTrump)
{
    INT16 wIndex = GetIndexByInst(qwInstID);
    if (wIndex < 0)
        return eTrumpNotExist;
    CItemPtr pItem = GetItem(qwInstID);
    if (!pItem || !pItem->IsTrumpItem())
        return eTrumpNotExist;
    CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(pItem);
    if (!pTrump)
        return eTrumpNotExist;

    UINT32 dwAddExp = 0;
    UINT32 dwCount = 0;
    ETrumpResult eResult = pTrump->Upgrade(byOneKey?true:false, GetUserPtr(), dwAddExp, dwCount);

    if (eResult == eTrumpSuccess)
    {
        CItem::Update2DB(*pTrump, GetUser().GetUserID(), GetUser().GetUserID(), GetStoreType(), wIndex, eOpUpdate);
        CItem::ItemChangeNotify(GetUser(), *pTrump, GetStoreType(), wIndex, GetUser().GetUserID());

        STrumpPtr pTrumpStream = STrumpPtr(new STrump);
        if (!pTrumpStream || !pTrump->ToStream(*pTrumpStream))
            return eTrumpNotifyFailed;
        vecTrump.push_back(pTrumpStream);

        SetDirty(eAttrGpTrumpHalo);
        UpdateRankInfo();


        //LogServer
        string sTrumpName = pItem->GetItemName(); 
        UINT16 wTrumpLevel= pTrump->GetRank();
        UINT32 dwSkillID = pTrump->GetSkill();
        UINT32 dwExp = pTrump->GetExp();
        WriteTrumpLog(wIndex,sTrumpName,wTrumpLevel,dwSkillID,dwExp);
        CPlayerPtr pPlayer = GetUser().GetPlayer();
        if(pPlayer)
        {
            //Event事件
            TVecINT32 vecParam;
            vecParam.push_back(pTrump->GetItemID());
            vecParam.push_back(dwCount);
            vecParam.push_back(wTrumpLevel);

            vector<CItemPtr> vecTrump;
            GetAllActiveTrump(vecTrump);
            for (size_t i = 0; i < vecTrump.size(); ++i)
            {
                if (vecTrump[i] && vecTrump[i]->IsTrumpItem()&& (vecTrump[i]!= pTrump))
                {
                    CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(vecTrump[i]);
                    if (pTrump)
                        vecParam.push_back(pTrump->GetLevel());
                }
            }
            pPlayer->OnEvent(eEventType_TrumpForging, vecParam);
            if(pTrump->GetLevel() >= 9)
            {
                SItem_Wrapper wrapper; 
                wrapper.ptr = pTrumpStream;
                NGlobalChatProt::SShowInfo stShow;
                stShow.qwInstID = pPlayer->GetUserID();
                COutArchive iar(stShow.strShowInfo);
                iar << UINT8(NGlobalChatProt::eShowItem);
                iar << wrapper;
                NGlobalChatProt::TVecShowInfo vecShow;
                TVecString vecstring; 
                vecstring.push_back(NumberToString(pPlayer->GetColor()));
                vecstring.push_back(pPlayer->GetName());
                vecShow.push_back(stShow);
                g_ChatProtS.SendClt_SystemFormatMsgIDNotifyWithShow(NULL,0,eMsgMagicTop,vecstring,vecShow);

            }

        }
    }
    return eResult;
}

void CTrumpSlots::WriteTrumpLog(UINT32 dwID,string &sName,UINT16 wLevel,UINT32 dwSkillID,UINT32 dwExp)
{
    NLogDataDefine::STrumpLogPtr ptrLog(new NLogDataDefine::STrumpLog());
    if(NULL == ptrLog)
        return;
    NLogDataDefine::STrumpLog& rLog = *ptrLog;
    rLog.dwServerId  = Config._wGroup;
    rLog.qwUserId    = GetUserPtr()->GetRoleID();
    rLog.sName       = sName;
    rLog.wID         = dwID;
    rLog.dwSkillId   = dwSkillID;
    rLog.dwLevel     = wLevel;
    rLog.dwExp       = dwExp;
    rLog.happenedTime = time(NULL);
    CGameServerLog::LogToDB(ptrLog);
}

// 提升法宝品级
ETrumpResult CTrumpSlots::EvolveTrump(UINT64 qwInstID, TVecTrump& vecTrump)
{
    INT16 wIndex = GetIndexByInst(qwInstID);
    if (wIndex < 0)
        return eTrumpNotExist;
    CItemPtr pItem = GetItem(qwInstID);
    if (!pItem || !pItem->IsTrumpItem())
        return eTrumpNotExist;
    CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(pItem);
    if (!pTrump)
        return eTrumpNotExist;

    ETrumpResult eResult = pTrump->Evolve(GetUserPtr());

    if (eResult == eTrumpSuccess)
    {
        CItem::Update2DB(*pTrump, GetUser().GetUserID(), GetUser().GetUserID(), GetStoreType(), wIndex, eOpUpdate);
        CItem::ItemChangeNotify(GetUser(), *pTrump, GetStoreType(), wIndex, GetUser().GetUserID());

        STrumpPtr pTrumpStream = STrumpPtr(new STrump);
        if (!pTrumpStream || !pTrump->ToStream(*pTrumpStream))
            return eTrumpNotifyFailed;
        vecTrump.push_back(pTrumpStream);
        SetDirty(eAttrGpTrumpHalo);
        UpdateRankInfo();
    }
    return eResult;
}

// 光环属性
bool CTrumpSlots::GetHaloAttr(TVecFloat& rvecAttr) const
{
#if 0 // 所有出战/不出战法宝光环属性都有效
    if (_wActiveIndex >=0)
    {
        CItemPtr pItem = GetItem(_wActiveIndex);
        if (!pItem)
            LOG_WRN << "Err when GetHaloAttr: wIndex = " << _wActiveIndex << ".";
        else
        {
            CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(pItem);
            pTrump->GetHaloAttr(rvecAttr);
        }
    }

    for (UINT8 byIndex = 0; byIndex < MAX_PASSIVE_COUNT; ++byIndex)
    {
        if (_wPassiveIndex[byIndex] < 0)
            continue;
        CItemPtr pItem = GetItem(_wPassiveIndex[byIndex]);
        if (!pItem)
        {
            LOG_WRN << "Err when GetHaloAttr: wIndex = " << _wPassiveIndex[byIndex] << ".";
            continue;
        }
        CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(pItem);
        pTrump->GetHaloAttr(rvecAttr);
    }
#else
    vector<CItemPtr> vecItem;
    GetAllItemList(vecItem);
    for (auto it = vecItem.begin(); it != vecItem.end(); ++it)
    {
        if (!(*it)->IsTrumpItem())
        {
            LOG_WRN << "Err when GetHaloAttr.";
            continue;
        }
        CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(*it);
        pTrump->GetHaloAttr(rvecAttr);
    }
#endif
    return true;
}

// 附加属性
bool CTrumpSlots::GetExtraAttr(TVecFloat& rvecAttr) const
{
    if (_wActiveIndex >=0)
    {
        CItemPtr pItem = GetItem(_wActiveIndex);
        if (!pItem)
            LOG_WRN << "Err when GetExtraAttr: wIndex = " << _wActiveIndex << ".";
        else
        {
            CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(pItem);
            pTrump->GetExtraAttr(rvecAttr);
        }
    }


    for (UINT8 byIndex = 0; byIndex < MAX_PASSIVE_COUNT; ++byIndex)
    {
        if (_wPassiveIndex[byIndex] < 0)
            continue;
        CItemPtr pItem = GetItem(_wPassiveIndex[byIndex]);
        if (!pItem)
        {
            LOG_WRN << "Err when GetExtraAttr: wIndex = " << _wPassiveIndex[byIndex] << ".";
            continue;
        }
        CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(pItem);
        pTrump->GetExtraAttr(rvecAttr);
    }
    return true;
}

// 激活属性
bool CTrumpSlots::GetActiveAttr(TVecFloat& rvecAttr) const
{
    vector<CItemPtr> vecItem;
    GetAllItemList(vecItem);
    for (auto it = vecItem.begin(); it != vecItem.end(); ++it)
    {
        if (!(*it)->IsTrumpItem())
        {
            LOG_WRN << "Err when GetActiveAttr.";
            continue;
        }
        CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(*it);
        pTrump->GetActiveAttr(rvecAttr);
    }
    return true;
}

// 获得当前使用的主动法宝
CTrumpPtr CTrumpSlots::GetActiveTrump()
{
    CItemPtr pItem = GetItem(_wActiveIndex);
    if (pItem)
        return dynamic_pointer_cast<CTrump>(pItem);
    else
        return NULL;
}
// 获得当前使用的主动法宝
CTrumpPtr CTrumpSlots::GetActiveTrump() const
{
    CItemPtr pItem = GetItem(_wActiveIndex);
    if (pItem)
        return dynamic_pointer_cast<CTrump>(pItem);
    else
        return NULL;
}

// 获得当前使用的被动法宝
vector<CTrumpPtr> CTrumpSlots::GetPassiveTrump()
{
    vector<CTrumpPtr> vecTrump;
    for (UINT8 byIndex = 0; byIndex < MAX_PASSIVE_COUNT; ++byIndex)
    {
        CItemPtr pItem = GetItem(_wPassiveIndex[byIndex]);
        if (pItem)
            vecTrump.push_back(dynamic_pointer_cast<CTrump>(pItem));
    }
    return vecTrump;
}

// 获得当前使用的被动法宝
vector<CTrumpPtr> CTrumpSlots::GetPassiveTrump() const
{
    vector<CTrumpPtr> vecTrump;
    for (UINT8 byIndex = 0; byIndex < MAX_PASSIVE_COUNT; ++byIndex)
    {
        CItemPtr pItem = GetItem(_wPassiveIndex[byIndex]);
        if (pItem)
            vecTrump.push_back(dynamic_pointer_cast<CTrump>(pItem));
    }
    return vecTrump;
}

UINT32 CTrumpSlots::GetPeerlessSkill() const
{
    CTrumpPtr pTrump = GetActiveTrump();
    if (pTrump)
        return pTrump->GetSkill();
    return 0;
}

void CTrumpSlots::GetPassiveSkills(TVecUINT32& rvecPassiveSkill) const
{
    vector<CTrumpPtr> vecTrumpPtr = GetPassiveTrump();
    for (auto it = vecTrumpPtr.begin(); it != vecTrumpPtr.end(); ++it)
    {
        rvecPassiveSkill.push_back((*it)->GetSkill());
    }
}

bool CTrumpSlots::IsTrumpActived(UINT16 wItemID) const
{
    return GetItemCount(wItemID) > 0 ? true:false;
}

// 获取已激活无双法宝
bool CTrumpSlots::GetAllActiveTrump(vector<CItemPtr>& rvecItem) const
{
    GetAllItemList(rvecItem);
    return true;
}

// GM祭炼法宝
void CTrumpSlots::Boost(ECareerType eType)
{
    TVecUINT16 vecTrumpID;
    switch(eType)
    {
        case ECAREER_RU: //儒
            {
                UINT16 wTrumpID[] = {5000};
                vecTrumpID.insert(vecTrumpID.begin(), wTrumpID, wTrumpID + sizeof(wTrumpID)/sizeof(UINT16));
            }
            break;
        case ECAREER_SHI: //释
            {
                UINT16 wTrumpID[] = {5001};
                vecTrumpID.insert(vecTrumpID.begin(), wTrumpID, wTrumpID + sizeof(wTrumpID)/sizeof(UINT16));
            }
            break;
        case ECAREER_DAO: //道
            {
                UINT16 wTrumpID[] = {5002};
                vecTrumpID.insert(vecTrumpID.begin(), wTrumpID, wTrumpID + sizeof(wTrumpID)/sizeof(UINT16));
            }
            break;
        case ECAREER_MO: //墨
            {
                UINT16 wTrumpID[] = {5003};
                vecTrumpID.insert(vecTrumpID.begin(), wTrumpID, wTrumpID + sizeof(wTrumpID)/sizeof(UINT16));
            }
            break;
        default:
            break;
    }
    for (auto& wTrumpID : vecTrumpID)
    {
        TVecTrump vecTrump;
        ETrumpResult eResult = ActiveTrump(wTrumpID, vecTrump, true);
        if (eResult == eTrumpSuccess)
        {
            if (!vecTrump.empty())
            {
                TVecTrump vecTrump2;
                EquipTrump(vecTrump[0]->sItemInfo.qwInstID, vecTrump2);
            }
        }
    }

}

void CTrumpSlots::SuperBoostObjects()
{
    ECareerType eType = GetUser().GetPlayer()->GetMainFighter()->GetJob();
    TVecUINT16 vecTrumpID;
    const TVecUINT16& rvecTrumpID = CBoostMgr::Instance().GetTrumpID(eType);
    const TVecUINT16& rvecTrumpID2 = CBoostMgr::Instance().GetTrumpID(ECAREER_ALL);
    vecTrumpID.insert(vecTrumpID.end(), rvecTrumpID.begin(), rvecTrumpID.end());
    vecTrumpID.insert(vecTrumpID.end(), rvecTrumpID2.begin(), rvecTrumpID2.end());
    for (auto& wTrumpID : vecTrumpID)
    {
        TVecTrump vecTrump;
        ETrumpResult eResult = ActiveTrump(wTrumpID, vecTrump, true);
        if (eResult == eTrumpSuccess && !vecTrump.empty())
        {
            UINT64 qwInstID = vecTrump[0]->sItemInfo.qwInstID;
            vecTrump.clear();
            EquipTrump(qwInstID, vecTrump);

            INT16 wIndex = GetIndexByInst(qwInstID);
            if (wIndex < 0)
                return;
            CItemPtr pItem = GetItem(qwInstID);
            if (!pItem || !pItem->IsTrumpItem())
                return;
            CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(pItem);
            if (!pTrump)
                return;

            pTrump->Super();

            CItem::Update2DB(*pTrump, GetUser().GetUserID(), GetUser().GetUserID(), GetStoreType(), wIndex, eOpUpdate);
            CItem::ItemChangeNotify(GetUser(), *pTrump, GetStoreType(), wIndex, GetUser().GetUserID());
            SetDirty(eAttrGpTrumpHalo);
            UpdateRankInfo();
        }
    }

}

void CTrumpSlots::RobotBoost(ECareerType eType)
{
    TVecUINT16 vecTrumpID;
    switch(eType)
    {
        case ECAREER_RU: //儒
            {
                UINT16 wTrumpID[] = {5000, 5004, 5008, 5012, 5080};
                vecTrumpID.insert(vecTrumpID.begin(), wTrumpID, wTrumpID + sizeof(wTrumpID)/sizeof(UINT16));
            }
            break;
        case ECAREER_SHI: //释
            {
                UINT16 wTrumpID[] = {5001, 5005, 5009, 5013, 5080};
                vecTrumpID.insert(vecTrumpID.begin(), wTrumpID, wTrumpID + sizeof(wTrumpID)/sizeof(UINT16));
            }
            break;
        case ECAREER_DAO: //道
            {
                UINT16 wTrumpID[] = {5002, 5006, 5010, 5014, 5080};
                vecTrumpID.insert(vecTrumpID.begin(), wTrumpID, wTrumpID + sizeof(wTrumpID)/sizeof(UINT16));
            }
            break;
        case ECAREER_MO: //墨
            {
                UINT16 wTrumpID[] = {5003, 5007, 5011, 5015, 5080};
                vecTrumpID.insert(vecTrumpID.begin(), wTrumpID, wTrumpID + sizeof(wTrumpID)/sizeof(UINT16));
            }
            break;
        default:
            break;
    }
    /*
    bool bSuc = false;
    do
    {
        TVecTrump vecTrump;
        UINT16 wActiveID = CRandom::RandVecElem(vecTrumpID);
        ETrumpResult eResult = ActiveTrump(wActiveID, vecTrump, true);
        if (eResult == eTrumpSuccess)
        {
            if (!vecTrump.empty())
            {
                TVecTrump vecTrump2;
                EquipTrump(vecTrump[0]->sItemInfo.qwInstID, vecTrump2);
                bSuc = true;
            }
        }
    }while(!bSuc);
    */
        TVecTrump vecTrump;
        UINT16 wActiveID = CRandom::RandVecElem(vecTrumpID);
        ETrumpResult eResult = ActiveTrump(wActiveID, vecTrump, true);
        if (eResult == eTrumpSuccess)
        {
            if (!vecTrump.empty())
            {
                TVecTrump vecTrump2;
                EquipTrump(vecTrump[0]->sItemInfo.qwInstID, vecTrump2);
            }
        }
}

void CTrumpSlots::UpdateRankInfo() const
{
    CPlayerPtr pPlayer = GetUser().GetPlayer();
    if (!pPlayer || pPlayer->GetLevel() < SParamConfig::wRankLevelLimit5)
        return;
    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
        return;

    UINT32 dwBattlePoint = pFighterManager->GetTrumpBattlePoint();
    if (!dwBattlePoint)
        return;

    TVecRankInfo vecRankInfo;

    SRRTrumpInfoPtr pInfo (new SRRTrumpInfo);

    pInfo->dwValue = dwBattlePoint;
    pInfo->dwUpdateTime = Time::Now();
    pInfo->qwRoleID = pPlayer->GetRoleID();
    pInfo->strName = pPlayer->GetName();
    pInfo->strGuildName = pPlayer->GetGuildName();
    pInfo->dwBattlePoint = dwBattlePoint;
    pInfo->wPlayerFighterID = GetUser().GetPlayer()->GetMainFighter()->GetID();
    pInfo->byQuality = GetUser().GetPlayer()->GetMainFighter()->GetColor();
    pInfo->vecPlatforms = GetUser().GetPlatformParam();
    pInfo->byVIPLevel = GetUser().GetVIPLevel();
    CTrumpPtr pTrump = GetActiveTrump();
    if (pTrump)
        pInfo->wID = pTrump->GetID();
    else
    {
        vector<CTrumpPtr> vecTrumpPtr = GetPassiveTrump();
        for (auto& pTrump : vecTrumpPtr)
        {
            if (pTrump)
            {
                pInfo->wID = pTrump->GetID();
                break;
            }
        }
    }
    vecRankInfo.push_back(dynamic_pointer_cast<SRankInfo>(pInfo));
    g_Game2CenterRankC.Send_UpdateRankInfo(eRTTrump, pPlayer->GetRoleID(), vecRankInfo);
}

