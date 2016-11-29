
#include "stdafx.h"
#include "Protocols.h"
#include "FashionSlots.h"
#include "FighterManager.h"
#include "ItemMgr.h"
#include "Player.h"
#include "Map.h"
#include "EventMgr.h"
#include "GetCondMgr.h"
#include "GameServerLog.h"
#include "Random.h"

EFashionResult CFashionSlots::ActiveFashion(UINT64 qwInstID)
{
    int iSlot = INVALID_SLOT;
    CItemPtr pItem = GetSlotByInstID(qwInstID, &iSlot);
    if (!pItem || iSlot == INVALID_SLOT)
        return eFashionFailed;
    return ActiveFashion(iSlot, pItem);
}

CFashionSlots::~CFashionSlots()
{
 //LOG_CRI << "delete CFashionSlots";

}
EFashionResult CFashionSlots::ActiveFashion(int iSlot, CItemPtr& pItem)
{
    if (!pItem || !GetUser())
        return eFashionFailed;

    CFashionPtr pFashion = dynamic_pointer_cast<CFashion>(pItem);
    if (!pFashion)
        return eFashionFailed;

    if (pFashion->GetSelected())
        return eFashionSucc;

    if (pFashion->GetItemSubType() == eItemSubFashion) // 神器
    {
        if (_pCurrW)
        {
            _pCurrW->SetSelected(0);
            Update2DB(_pCurrW->GetIndex(), *_pCurrW, eOpUpdate);
            CItem::ItemChangeNotify(*GetUser(), *_pCurrW, eStoreFashion, _pCurrW->GetIndex(), GetFighter()->GetInstID());
        }
        _pCurrW = pFashion;
    }
    if (pFashion->GetItemSubType() == eItemSubFashion2) // 神衣
    {
        if (_pCurrD)
        {
            _pCurrD->SetSelected(0);
            Update2DB(_pCurrD->GetIndex(), *_pCurrD, eOpUpdate);
            CItem::ItemChangeNotify(*GetUser(), *_pCurrD, eStoreFashion, _pCurrD->GetIndex(), GetFighter()->GetInstID());
        }
        _pCurrD = pFashion;
    }

    pFashion->SetSelected(1);

    Update2DB(iSlot, *pItem, eOpUpdate);
    CItem::ItemChangeNotify(*GetUser(), *pItem, eStoreFashion, iSlot, GetFighter()->GetInstID());
    if (GetUser()->GetPlayer() && GetUser()->GetPlayer()->GetMap())
        GetUser()->GetPlayer()->GetMap()->AppearToSurround(*GetUser()->GetPlayer());

    if (GetUser()->GetPlayer())
    {   //Event事件
        TVecINT32 vecParam;
        vecParam.push_back(pFashion->GetItemID());
        GetUser()->GetPlayer()->OnEvent(eEventType_FaionGetUsed, vecParam);
    }

    return eFashionSucc;
}

void CFashionSlots::WriteFashionLog(UINT16 wID, string rName, UINT32 dwLevel)
{
    NLogDataDefine::SFashionLogPtr ptrLog(new NLogDataDefine::SFashionLog());
    if(NULL == ptrLog)
        return;
    NLogDataDefine::SFashionLog& rLog = *ptrLog;
    rLog.dwServerId    = Config._wGroup;
    rLog.qwUserId      = GetUser()->GetRoleID();
    rLog.wId           = wID;
    rLog.sName         = rName;
    rLog.dwLevel       = dwLevel;
    rLog.happenedTime  = time(NULL);
    CGameServerLog::LogToDB(ptrLog);
}

bool CFashionSlots::AdoptFashion(UINT16 wItemID, bool bUpdate/* = true*/)
{
    if (!CItemType::IsFashion(wItemID))
        return false;
    CItemPtr pItem = CItemMgr::CreateFashion(wItemID);
    if (!pItem)
        return false;
    UINT16 wCondID = pItem->GetItemCfg()._Cond;
    if (wCondID)
    {
        if (!CGetCondMgr::Instance().TestCond(*GetUser(), wCondID))
            return false;
        if (!CGetCondMgr::Instance().ProcessCond(*GetUser(), wCondID, NLogDataDefine::ItemTo_FashionActive))
            return false;
    }
    return AdoptFashion(pItem, bUpdate); 
}

bool CFashionSlots::AdoptFashion(CItemPtr& pItem, bool bUpdate/* = true*/)
{
    if (!pItem || !GetUser() || !GetFighter())
        return false;

    CItemPtr pTmp = GetSlotByID(pItem->GetID());
    if (pTmp)
        return false;

    int iSlot = pItem->GetIndex();
    if (iSlot == INVALID_SLOT)
        iSlot = GetEmptySlot();
    if (iSlot == INVALID_SLOT)
        return false;

    CFashionPtr pFashion = dynamic_pointer_cast<CFashion>(pItem);
    if (!pFashion)
        return false;

    if (bUpdate)
    {
        if (!_pCurrW && pFashion->GetItemSubType() == eItemSubFashion) // 神器
            pFashion->SetSelected(1);
        if (!_pCurrD && pFashion->GetItemSubType() == eItemSubFashion2) // 神衣
            pFashion->SetSelected(1);
    }

    if (pFashion->GetSelected())
    {
        if (pFashion->GetItemSubType() == eItemSubFashion && !_pCurrW) // 神器
            _pCurrW = pFashion;
        if (pFashion->GetItemSubType() == eItemSubFashion2 && !_pCurrD) // 神衣
            _pCurrD = pFashion;
    }

    if (!Set(iSlot, pFashion))
        return false;

    if (bUpdate)
        Update2DB(iSlot, *pItem, eOpAdd);
    pFashion->SetDirty(true);
    if (GetUser() && GetUser()->GetPlayer() && GetUser()->GetPlayer()->GetFighterManager())
        GetUser()->GetPlayer()->GetFighterManager()->SetDirty(eAttrGpFashion);

    CItem::ItemChangeNotify(*GetUser(), *pItem, eStoreFashion, iSlot, GetFighter()->GetInstID());

    //获得时装事件
    CPlayerPtr pPlayer = GetUser()->GetPlayer();
    if(GetUser() && bUpdate)
    {
        TVecINT32 vecParam;
        vecParam.push_back(pItem->GetItemID());
        vecParam.push_back(GetSlots());
        GetUser()->GetPlayer()->OnEvent(eEventType_FaionActive, vecParam);
        if(pFashion->GetQuality() >= NProtoCommon::ECOLOR_PURPLE)
        {
            NGlobalChatProt::SShowInfo stShow;
            stShow.qwInstID = pPlayer->GetUserID();
            CItem::GetShowMsg(*pFashion,stShow);
            NGlobalChatProt::TVecShowInfo vecShow;
            TVecString vecstring; 
            vecstring.push_back(NumberToString(pPlayer->GetColor()));
            vecstring.push_back(pPlayer->GetName());
            vecShow.push_back(stShow);
            g_ChatProtS.SendClt_SystemFormatMsgIDNotifyWithShow(NULL,0,eMsgPurpleFashionGet,vecstring,vecShow);

        }

    }

    return true;
}

EFashionResult CFashionSlots::FashionUpgrade(UINT64 qwInstID, bool bOneKey)
{
    CItemPtr pItem = GetSlotByInstID(qwInstID);
    if (!pItem || !GetUser() || !GetFighter())
        return eFashionFailed;

    if (!pItem->IsFashionItem())
        return eFashionFailed;
    if (pItem->GetTrumpExp() > 0)     //策划配置 不能炼化
        return eFashionFailed;
    CFashionPtr pFashion = dynamic_pointer_cast<CFashion>(pItem);
    if (!pFashion)
        return eFashionFailed;

    UINT8 byLevel = pFashion->GetLevel();
    if (byLevel >= CItemMgr::GetFashionLevelMax())
        return eFashionFailed;
    SFashionCFG* pFashionCfg = CItemMgr::GetFashionConfig(byLevel);
    if (!pFashionCfg)
        return eFashionFailed;
    if (!pFashionCfg->_Number || !pFashionCfg->_Material)
        return eFashionFailed;

    CPack& rPack = GetUser()->GetPack();
    if (rPack.GetItemCount(pFashionCfg->_Material) < pFashionCfg->_Number)
        return eFashionItemErr;

    UINT32 dwUsedNum = 0;
    while(true)
    {
        dwUsedNum += pFashionCfg->_Number;
        if (rPack.GetItemCount(pFashionCfg->_Material) < dwUsedNum)
        {
            dwUsedNum -= pFashionCfg->_Number;
            break;
        }

        UINT8 byNum = 1;
#if ON_OFF
        UINT16 wRand = CRandom::RandInt(0, MAX_RANDNUM);
        if (wRand < RANDVALUE_A)
            byNum = 10;
        else if (wRand < RANDVALUE_B)
            byNum = 5;
        else if (wRand < RANDVALUE_C)
            byNum = 2;

        CPlayerPtr pPlayer = GetUser()->GetPlayer();
        if (pPlayer)
        {
            if (TWO_NOTIFY==byNum)
                pPlayer->SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(eFashionCrit, eTwoMultipleCrit));
            else if (FIVE_NOTIFY==byNum)
                pPlayer->SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(eFashionCrit, eFiveMultipleCrit));
            else if(TEN_NOTIFY==byNum)
            {
                TVecString vecstring;
                vecstring.push_back(NumberToString(pPlayer->GetColor()));
                vecstring.push_back(pPlayer->GetName());
                vecstring.push_back(NumberToString(byNum));
                g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgFashionAttr, vecstring);
                pPlayer->SendPkg(g_RoleEventProtS.BuildPkg_CritNotify(eFashionCrit, eTenMultipleCrit));
            }
        }
#endif

        UINT32 dwExp = pFashion->GetExp();
        dwExp += (pFashionCfg->_Each_exp * byNum);

        pFashion->SetExp(dwExp);
        UINT32 dwNewLvl = CItemMgr::FashionExpToLevel(dwExp);
        if (dwNewLvl > byLevel)
        {
            pFashion->SetLevel(dwNewLvl);
            break;
        }
        if (!bOneKey)
            break;
    }

    rPack.DelItemByItemID(pFashionCfg->_Material, dwUsedNum, true, NLogDataDefine::ItemTo_FashionUpgrade);
    Update2DB(*pItem);
    CItem::ItemChangeNotify(*GetUser(), *pItem, eStoreFashion, pItem->GetIndex(), GetFighter()->GetInstID());

    if (byLevel != pFashion->GetLevel())
    {
        pFashion->SetDirty(true);
        if (GetUser() && GetUser()->GetPlayer() && GetUser()->GetPlayer()->GetFighterManager())
        {
            GetUser()->GetPlayer()->GetFighterManager()->SetDirty(eAttrGpFashion);
            if(pFashion->GetSelected())
                GetUser()->GetPlayer()->GetMap()->AppearToSurround(*GetUser()->GetPlayer());
        }
    }

    if (GetUser()->GetPlayer())
    {   //Event事件
        TVecINT32 vecParam;
        vecParam.push_back(pFashion->GetItemID());
        for (size_t iSlot = 0; iSlot < static_cast<size_t>(GetSlots()); ++ iSlot)
        {
            CItemPtr pItem = Get(iSlot);
            CFashionPtr pFashion = dynamic_pointer_cast<CFashion>(pItem);
            if (!pItem || !pFashion)
                continue;
            vecParam.push_back(pFashion->GetLevel());
        }
        GetUser()->GetPlayer()->OnEvent(eEventType_FaionUpgrade, vecParam);
        if(pFashion->GetLevel() >= 9)
        {
            CPlayerPtr pPlayer = GetUser()->GetPlayer();
            NGlobalChatProt::SShowInfo stShow;
            stShow.qwInstID = pPlayer->GetUserID();
            CItem::GetShowMsg(*pFashion,stShow);
            NGlobalChatProt::TVecShowInfo vecShow;
            TVecString vecstring; 
            vecstring.push_back(NumberToString(pPlayer->GetColor()));
            vecstring.push_back(pPlayer->GetName());
            vecShow.push_back(stShow);
            g_ChatProtS.SendClt_SystemFormatMsgIDNotifyWithShow(NULL,0,eMsgFashionTop,vecstring,vecShow);

        }


    }

    //时装炼化Log记录
    UINT32 dwLevel = static_cast<UINT32>(pFashion->GetLevel());
    WriteFashionLog(pFashion->GetItemID(),pFashion->GetItemName(),dwLevel);

    return eFashionSucc;
}

class FashionEnumerate4Attr : public Enumerator<typename CFashionSlots::value_type>
{
    public:
        typedef CFashionSlots::value_type value_type;

    public:
        FashionEnumerate4Attr(TVecFloat& vecAddAttr) : _vecAddAttr(vecAddAttr) {}

        bool operator()(const value_type* obj) const
        {
            if (obj && std::get<1>(*obj))
                std::get<2>(*obj)->AppendAttr(_vecAddAttr);
            return true;
        }

    public:
        TVecFloat& _vecAddAttr;
};

bool CFashionSlots::GetAddAttr(TVecFloat& vecAddAttr) const
{
    FashionEnumerate4Attr en(vecAddAttr);
    enumerate(en);
    SetDirty(false);
    return true;
}

class FashionEnumerateToStream : public Enumerator<typename CFashionSlots::value_type>
{
    public:
        typedef CFashionSlots::value_type value_type;

    public:
        FashionEnumerateToStream(TVecItem& vecItem) : _vecItem(vecItem) {}

        bool operator()(const value_type* obj) const
        {
            if (obj && std::get<1>(*obj))
                _vecItem.push_back(std::get<2>(*obj)->ToProt());
            return true;
        }

    public:
        TVecItem& _vecItem;
};

void CFashionSlots::ToProt(TVecItem& vecItem) const
{
    FashionEnumerateToStream en(vecItem);
    enumerate(en);
}

void CFashionSlots::Update2DB(int iSlot, CItem& rItem, EDataChange eDataChange/* = eOpUpdate*/)
{
    UINT64 qwUserID = 0;
    UINT64 qwFighterID = 0;

    if (GetUser())
        qwUserID = GetUser()->GetUserID();

    if (GetFighter())
        qwFighterID = GetFighter()->GetInstID();

    if (qwUserID)
        CItem::Update2DB(rItem, qwUserID, qwFighterID?qwFighterID:qwUserID, eStoreFashion, iSlot/*UINT16*/, eDataChange);

    //SetDirty(true);
}

void CFashionSlots::Update2DB(CItem& rItem)
{
    Update2DB(rItem.GetIndex(), rItem, eOpUpdate);
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

