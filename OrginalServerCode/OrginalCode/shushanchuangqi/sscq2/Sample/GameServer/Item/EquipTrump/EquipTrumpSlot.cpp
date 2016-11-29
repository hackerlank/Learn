// =====================================================================================
//
//       Filename:  EquipTrumpTrumpSlot.cpp
//
//    Description:  法宝槽
//
//        Version:  1.0
//        Created:  05/14/2015 02:46:14 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "EquipTrumpSlot.h"

#include "EquipTrump.h"

#include "EquipTrumpMgr.h"
#include "Pack.h"
#include "EquipTrumpProtS.h"
#include "User.h"
#include "Fighter.h"
#include "FighterManager.h"
#include "HeroFighter.h"
#include "SysMsgDefine.h"
#include "Player.h"
#include "EventCenter.h"
using namespace NEventCenter;

// ===  FUNCTION  ======================================================================
//         Name:  CEquipTrumpSlot
//  Description:  构造函数
// =====================================================================================
CEquipTrumpSlot::CEquipTrumpSlot ():
    CItemSlots(),
    _bDirty(true)
{
}		// -----  end of function CEquipTrumpSlot  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CEquipTrumpSlot
//  Description:  析构函数
// =====================================================================================
CEquipTrumpSlot::~CEquipTrumpSlot ()
{
}		// -----  end of function ~CEquipTrumpSlot  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllInfo
//  Description:  获取所有的协议化数据
// =====================================================================================
bool CEquipTrumpSlot::GetAllInfo (NItemProt::TVecEquipTrump& rvecEquipTrump) const
{
    for (auto& rPair : _mapSlotType)
    {
        UINT8 byIndex = rPair.first;
        if (!HasObj(byIndex))
        {
            LOG_DBG << "Index(" << static_cast<UINT32>(rPair.first) << ") has no Obj.";
            continue;
        }

        CItemPtr pItem = Get(byIndex);
        if (!pItem)
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") has no Obj.";
            continue;
        }

        if (!pItem->IsEquipTrumpItem())
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") is not EquipTrump.";
            continue;
        }

        CEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<CEquipTrump>(pItem);
        if (!pEquipTrump)
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") is not EquipTrump.";
            continue;
        }

        SItemPtr pProtItem = pEquipTrump->ToProt();
        if (!pProtItem)
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") is wrong.";
            continue;
        }
        if (pProtItem->GetClassType() != eType_SEquipTrump)
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") is wrong.";
            continue;
        }

        SEquipTrumpPtr pProtEquipTrump = dynamic_pointer_cast<SEquipTrump>(pProtItem);
        if (!pProtEquipTrump)
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") is wrong.";
            continue;
        }
        rvecEquipTrump.push_back(pProtEquipTrump);

    }
    return true;
}		// -----  end of function GetAllInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAddAttr
//  Description:  获取增加的属性值
// =====================================================================================
bool CEquipTrumpSlot::GetAddAttr (TVecFloat& rvecAddAttr) const
{
    for (auto & rPair : _mapSlotType)
    {
        UINT8 byIndex = rPair.first;
        if (!HasObj(byIndex))
            continue;

        CItemPtr pItem = Get(byIndex);
        if (!pItem)
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") has no Obj.";
            continue;
        }

        if (!pItem->IsEquipTrumpItem())
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") is not EquipTrump.";
            continue;
        }

        CEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<CEquipTrump>(pItem);
        if (!pEquipTrump)
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") is not EquipTrump.";
            continue;
        }
        pEquipTrump->GetAttr(rvecAddAttr);
    }
    return true;
}		// -----  end of function GetAddAttr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllSkills
//  Description:  获取所有法宝带有的技能
// =====================================================================================
void CEquipTrumpSlot::GetAllSkills (TVecUINT32& rvecAllSkills) const
{
    TSetUINT32 setSkillID;
    for (auto & rPair : _mapSlotType)
    {
        UINT8 byIndex = rPair.first;
        if (!HasObj(byIndex))
            continue;

        CItemPtr pItem = Get(byIndex);
        if (!pItem)
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") has no Obj.";
            continue;
        }

        if (!pItem->IsEquipTrumpItem())
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") is not EquipTrump.";
            continue;
        }

        CEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<CEquipTrump>(pItem);
        if (!pEquipTrump)
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") is not EquipTrump.";
            continue;
        }
        UINT32 dwSkillID = pEquipTrump->GetSkillID();
        if (dwSkillID)
            setSkillID.insert(dwSkillID);
    }
    for (auto & rID : setSkillID)
    {
        rvecAllSkills.push_back(rID);
    }
}		// -----  end of function GetAllSkills  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllEquipTrump
//  Description:  获取所有的装备法宝
// =====================================================================================
bool CEquipTrumpSlot::GetAllEquipTrump(TVecEquipTrumpPtr& rvecEquipTrump) const
{
    for (auto& rPair : _mapSlotType)
    {
        UINT8 byIndex = rPair.first;
        if (!HasObj(byIndex))
        {
            LOG_DBG << "Index(" << static_cast<UINT32>(rPair.first) << ") has no Obj.";
            continue;
        }

        CItemPtr pItem = Get(byIndex);
        if (!pItem)
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") has no Obj.";
            continue;
        }

        if (!pItem->IsEquipTrumpItem())
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") is not EquipTrump.";
            continue;
        }

        CEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<CEquipTrump>(pItem);
        if (!pEquipTrump)
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") is not EquipTrump.";
            continue;
        }

        rvecEquipTrump.push_back(pEquipTrump);
    }
    return true;
}		// -----  end of function GetAllEquipTrump  ----- //


// ===  FUNCTION  ======================================================================
//         Name:  InitSlot
//  Description:  初始化槽数量
// =====================================================================================
bool  CEquipTrumpSlot::InitSlot(UINT16 wMaxSlot, UINT16 wMaxAvaliableSlot)
{
    SetMaxSlot(wMaxSlot, true);
    SetMaxAvaliable(wMaxAvaliableSlot, true);
    return true;
}		// -----  end of function InitSlot  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AddItemFromDB
//  Description:  从数据库加载道具
// =====================================================================================
bool CEquipTrumpSlot::AddItemFromDB (CEquipTrumpPtr pEquipTrump)
{
    if (!pEquipTrump)
        return false;
    INT16 wIndex = pEquipTrump->GetIndex();
    if (wIndex < 0)
    {
        LOG_CRI << "wIndex = " << wIndex << ".";
        return false;
    }
    auto it = _mapSlotType.find(wIndex);
    if (it == _mapSlotType.end())
    {
        LOG_CRI << "_mapSlotType error.";
        return false;
    }
    EEquipTrumpSlotType eSlotType = pEquipTrump->GetSlotType();
    if (eSlotType != it->second)
    {
        LOG_CRI << "SlotType conflict:" << eSlotType << "/ " << it->second << ".";
        return false;
    }

    Set(wIndex, pEquipTrump);
    return true;
}		// -----  end of function AddItemFromDB  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  TryLockSlot
//  Description:  解锁法宝栏
// =====================================================================================
bool CEquipTrumpSlot::TryUnlockSlot (UINT16 wLevel)
{
    auto rMapConfig = CEquipTrumpMgr::Instance().GetSlotConfig();
    TSetUINT8 setUnlockedIndex;
    for (auto & rPair : rMapConfig)
    {
        if (!rPair.first)
        {
            LOG_CRI << "EquipTrumpSlot Config = 0.";
            continue;
        }

        auto it = _mapSlotType.find(rPair.first);
        if (wLevel < rPair.second.wMinDujieLevel)
            continue;

        // 没有开启，开启一个新的格子
        if (it == _mapSlotType.end())
        {
            _mapSlotType.insert(make_pair(rPair.first, rPair.second.eSlotType));
            LOG_DBG << "Open EquipTrumpSlot: " << static_cast<UINT32>(rPair.first) << ".";
        }
        // 已经开启，但类型变了
        else if(it->second != rPair.second.eSlotType)
        {
            LOG_CRI << "Wrong type: " << static_cast<UINT32>(it->second) << " -> " 
                << static_cast<UINT32>(rPair.second.eSlotType) << ".";
            CUserPtr pUser = GetUser();
            if (pUser)
                continue;
        }
        setUnlockedIndex.insert(rPair.first);
    }

    // 寻找是否有已经开启的法宝位需要关闭
    for (auto it0 = _mapSlotType.begin(); it0 != _mapSlotType.end();)
    {
        auto it = setUnlockedIndex.find(it0->first);
        if (it != setUnlockedIndex.end())
            ++it0;
        else
        {
            UINT8 byIndex = it0->first;
            // 将已经存在的法宝塞回背包
            if (HasObj(byIndex))
            {
                CItemPtr pItem = Get(byIndex);
                if (pItem)
                {
                    CUserPtr pUser = GetUser();
                    if (pUser)
                    {
                        CPack& rPack =  pUser->GetPack();
                        rPack.AddItemOrMail(*pItem);
                    }
                    else
                        LOG_CRI << "pEquipTrump Missing: " << pItem->GetInstID() << ".";
                }
            }
            LOG_DBG << "Close EquipTrumpSlot Lock: " << static_cast<UINT32>(it0->first) << ".";
            _mapSlotType.erase(it0++);
        }
    }
    return true;
}		// -----  end of function TryLockSlot  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Wear
//  Description:  穿戴装备法宝
// =====================================================================================
EEquipTrumpResult CEquipTrumpSlot::Wear (CEquipTrumpPtr pEquipTrump,UINT32 dwFighterID)
{
    EEquipTrumpResult eResult = eETRFailed;
    if (!pEquipTrump)
        return eResult;

    EEquipTrumpSlotType eSlotType = pEquipTrump->GetSlotType();
    if (eSlotType == eETSTNone)
        return eResult;

    TSetUINT16& rsetConflictID = CItemMgr::GetConflictID(pEquipTrump->GetID());
    TSetUINT16& rsetTeamConflictID = CItemMgr::GetTeamConflictID(pEquipTrump->GetID());

    INT16 wIndex = -1;
    INT16 wUsedIndex = -1;
    for (auto & rPair : _mapSlotType)
    {
        if (rPair.second != eSlotType)
            continue;
        if (HasObj(rPair.first))
        {
            CItemPtr pItem = Get(rPair.first);
            if (pItem)
            {
                auto it = rsetConflictID.find(pItem->GetID());
                // 个人装备有冲突，无法更换
                if (it != rsetConflictID.end())
                    return eETRSlotConflict;
                else if (pEquipTrump->GetID() == pItem->GetID()) // 同样的装备直接替换
                {
                    wUsedIndex = rPair.first;
                    wIndex = -1;
                    break;
                    /*
                    CUserPtr pUser = GetUser();
                    if (pUser)
                    {
                        string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eEquipTrump12);
                        pUser->SendPkg(strPkg);
                    }
                    return eETRSlotConflict;
                    */

                }
            }
            if (wUsedIndex < 0)
                wUsedIndex = rPair.first;
        }
        else if (wIndex < 0)
            wIndex = rPair.first;
    }

    //  检查是否队伍中有冲突的装备
    CFighterPtr pFighter = GetFighter();
    if (!pFighter)
        return eETRFailed;
    CFighterManagerPtr pFighterManager = pFighter->GetFighterManager();
    if (pFighterManager)
    {
        TVecFighterPtr rvecFighters;
        pFighterManager->GetAllFighters(rvecFighters);

        for(auto& pFighter0 : rvecFighters)
        {
            if (!pFighter0 || !pFighter0->IsHeroFighter() || pFighter0 == pFighter)
                continue;
            CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter0);
            if(pHeroFighter)
            {
                CEquipTrumpSlot& rEquipTrumpSlot = pHeroFighter->GetEquipTrumpSlot(); 

                for (auto & rID : rsetTeamConflictID)
                {
                    CItemPtr pItem = rEquipTrumpSlot.GetSlotByID(rID);
                    if(pItem)
                        return eETRSlotConflict;
                }
            }
        }
    }

    CPack& rPack =  GetUser()->GetPack();
    if (wIndex < 0 && wUsedIndex >= 0)
    {
        CItemPtr pItem = Get(wUsedIndex);
        if (pItem)
        {
            if (pItem->IsEquipTrumpItem())
            {
                CEquipTrumpPtr pEquipTrump2 = dynamic_pointer_cast<CEquipTrump>(pItem);
                if (pEquipTrump2)
                {
                    Reset(wUsedIndex);
                    pEquipTrump2->SetOwnerID(0);
                    pEquipTrump2->SetIndex(-1);
                    rPack.AddItemOrMail(*pItem);
                }
            }
        }
        wIndex = wUsedIndex;
    }

    if (wIndex >= 0)
    {
        rPack.DelItem(*pEquipTrump, true, false, NLogDataDefine::ItemTo_GM);
        Set(wIndex, pEquipTrump);
        CFighterPtr pFighter = GetFighter();
        if (pFighter)
            pEquipTrump->SetOwnerID(pFighter->GetInstID());
        pEquipTrump->SetIndex(wIndex);
        pEquipTrump->SetStoreType(eStoreEquipTrump);
        eResult = eETRSuccess;
        CItem::Update2DB(*pEquipTrump, GetUser()->GetUserID(), GetUser()->GetUserID(), GetStoreType(), wIndex, eOpUpdate);
        SetDirty(true);
    }
    else
        eResult = eETRSlotLock;
    NotifyInfo();

    CUserPtr pUser = GetUser(); 
    if(pUser && pUser->GetPlayer())
    {
        TVecINT32 vecParam;
        vecParam.push_back(pEquipTrump->GetID());
        vecParam.push_back(dwFighterID);

        for (auto& rPair : _mapSlotType)
        {
            UINT8 byIndex = rPair.first;
            if (!HasObj(byIndex))
            {
                continue;
            }

            CItemPtr pItem = Get(byIndex);
            if (!pItem)
            {
                continue;
            }

            vecParam.push_back(pItem->GetID());
        }

        pUser->GetPlayer()->OnEvent(eEventType_TrumpEquip,vecParam);
    }
    return eResult;
}		// -----  end of function Wear  ----- //

struct SEquipTrumpBP
{
    UINT16 wItemID;         // 物品ID
    UINT64 qwInstID;        // 物品唯一ID 
    UINT32 dwBattlePoint;
    bool bPack;
    TSetUINT16 setConflictItemID;
    CEquipTrumpPtr pEquipTrump;
    SEquipTrumpBP():
        wItemID(0), qwInstID(0), dwBattlePoint(0), bPack(false)
    {
    }
    bool operator < (const SEquipTrumpBP& rOther) const
    {
        if (qwInstID == rOther.qwInstID)
            return false;
        if (dwBattlePoint != rOther.dwBattlePoint)
            return dwBattlePoint > rOther.dwBattlePoint;
        return qwInstID < rOther.qwInstID;
    }
};

// ===  FUNCTION  ======================================================================
//         Name:  WearOneKey
//  Description:  一键穿戴装备法宝
//        FIXME:  队伍互斥没有考虑
// =====================================================================================
EEquipTrumpResult CEquipTrumpSlot::WearOneKey (UINT32 dwFighterID)
{
    EEquipTrumpResult eResult = eETRFailed;
    CPack& rPack =  GetUser()->GetPack();
    TVecEquipTrumpPtr vecEquipTrumpPtr;
    set<SEquipTrumpBP> setPackItemInfo;
    rPack.GetAllEquipTrump(vecEquipTrumpPtr);
    for (auto & pEquipTrump : vecEquipTrumpPtr)
    {
        SEquipTrumpBP sInfo;
        sInfo.wItemID = pEquipTrump->GetID();
        sInfo.qwInstID = pEquipTrump->GetInstID();
        sInfo.dwBattlePoint = pEquipTrump->GetBattlePoint();
        sInfo.bPack = true;
        sInfo.setConflictItemID = CItemMgr::GetConflictID(sInfo.wItemID);
        sInfo.pEquipTrump = pEquipTrump;
        bool bReplace = true;
        for (auto & rInfo : setPackItemInfo)
        {
            if ( rInfo.wItemID == sInfo.wItemID) 
            {
                if ( rInfo.dwBattlePoint > sInfo.dwBattlePoint)
                    setPackItemInfo.erase(rInfo);
                else
                    bReplace = false;
                break;
            }
        }
        if (bReplace)
            setPackItemInfo.insert(sInfo);
    }


    TSetUINT16 setEmptyIndex;
    TSetUINT16 setConflictID;
    set<SEquipTrumpBP> setEquipItemInfo;
    for (auto & rPair : _mapSlotType)
    {
        if (HasObj(rPair.first))
        {
            if(rPair.first >= EQUIP_TRUMP_SLOTS)
                continue;

            CItemPtr pItem = Get(rPair.first);
            if (pItem)
            {
                if (pItem->IsEquipTrumpItem())
                {
                    CEquipTrumpPtr pEquipTrump2 = dynamic_pointer_cast<CEquipTrump>(pItem);
                    if (pEquipTrump2)
                    {
                        SEquipTrumpBP sInfo;
                        sInfo.wItemID = pEquipTrump2->GetID();
                        sInfo.qwInstID = pEquipTrump2->GetInstID();
                        sInfo.dwBattlePoint = pEquipTrump2->GetBattlePoint();
                        sInfo.bPack = false;
                        sInfo.setConflictItemID = CItemMgr::GetConflictID(sInfo.wItemID);
                        sInfo.pEquipTrump = pEquipTrump2;
                        setEquipItemInfo.insert(sInfo);
                        setConflictID.insert(sInfo.wItemID);
                        setConflictID.insert(sInfo.setConflictItemID.begin(), sInfo.setConflictItemID.end());

                    }
                }
            }
        }
        else
            setEmptyIndex.insert(rPair.first);
    }

    // 先把空位填上最好的法宝
    for (auto & rIndex : setEmptyIndex)
    {
        for (auto & rInfo : setPackItemInfo)
        {
            auto it = setConflictID.find(rInfo.wItemID);
            if (it != setConflictID.end() || (rInfo.pEquipTrump)->GetSlotType() != _mapSlotType[rIndex])
                continue;
            rPack.DelItem(*rInfo.pEquipTrump, true, false, NLogDataDefine::ItemTo_GM);
            Set(rIndex, rInfo.pEquipTrump);
            CFighterPtr pFighter = GetFighter();
            if (pFighter)
                rInfo.pEquipTrump->SetOwnerID(pFighter->GetInstID());
            rInfo.pEquipTrump->SetIndex(rIndex);
            rInfo.pEquipTrump->SetStoreType(eStoreEquipTrump);
            CItem::Update2DB(*rInfo.pEquipTrump, GetUser()->GetUserID(), GetUser()->GetUserID(), GetStoreType(), rIndex, eOpUpdate);
            SetDirty(true);
            setPackItemInfo.erase(rInfo);

            CUserPtr pUser = GetUser(); 
            if(pUser && pUser->GetPlayer())
            {
                TVecINT32 vecParam;
                vecParam.push_back(rInfo.pEquipTrump->GetID());
                vecParam.push_back(dwFighterID);
            
                for (auto& rPair : _mapSlotType)
                {
                    UINT8 byIndex = rPair.first;
                    if (!HasObj(byIndex))
                    {
                        continue;
                    }

                    CItemPtr pItem = Get(byIndex);
                    if (!pItem)
                    {
                        continue;
                    }
                    vecParam.push_back(pItem->GetID());
                }

                pUser->GetPlayer()->OnEvent(eEventType_TrumpEquip,vecParam);
            }

            break;
        }
    }

    // 然后把同类的换战力更高的
    for (auto & rInfo : setEquipItemInfo)
    {
        for (auto & rInfo2 : setPackItemInfo)
        {
            if (rInfo.wItemID != rInfo2.wItemID)
                continue;
            if (rInfo.dwBattlePoint >= rInfo2.dwBattlePoint)
                break;

            INT16 wIndex = rInfo.pEquipTrump->GetIndex();
            Reset(wIndex);
            rInfo.pEquipTrump->SetOwnerID(0);
            rInfo.pEquipTrump->SetIndex(-1);
            rPack.AddItemOrMail(*rInfo.pEquipTrump);

            rPack.DelItem(*rInfo2.pEquipTrump, true, false, NLogDataDefine::ItemTo_GM);
            Set(wIndex, rInfo2.pEquipTrump);
            CFighterPtr pFighter = GetFighter();
            if (pFighter)
                rInfo2.pEquipTrump->SetOwnerID(pFighter->GetInstID());
            rInfo2.pEquipTrump->SetIndex(wIndex);
            rInfo2.pEquipTrump->SetStoreType(eStoreEquipTrump);
            CItem::Update2DB(*rInfo2.pEquipTrump, GetUser()->GetUserID(), GetUser()->GetUserID(), GetStoreType(), wIndex, eOpUpdate);
            SetDirty(true);
            setPackItemInfo.erase(rInfo2);
            break;
        }
    }
    eResult = eETRSuccess;
    NotifyInfo();
    SetDirty(true);
    return eResult;
}		// -----  end of function WearOneKey  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  TakeOff
//  Description:  卸下装备法宝
// =====================================================================================
EEquipTrumpResult CEquipTrumpSlot::TakeOff (UINT64 qwInstID, INT16 wIndex)
{
    EEquipTrumpResult eResult = eETRFailed;
    CItemPtr pItem = GetSlotByInstID(qwInstID);
    if (!pItem)
        return eResult;
    if (!pItem->IsEquipTrumpItem())
        return eResult;
    CEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<CEquipTrump>(pItem);
    if (!pEquipTrump)
        return eResult;

    EEquipTrumpSlotType eSlotType = pEquipTrump->GetSlotType();
    if (eSlotType == eETSTNone)
        return eResult;

    Reset(pEquipTrump->GetIndex());
    pEquipTrump->SetOwnerID(0);
    pEquipTrump->SetIndex(-1);

    CPack& rPack =  GetUser()->GetPack();
    rPack.AddItemOrMail(*pItem);

    eResult = eETRSuccess;

    NotifyInfo();
    SetDirty(true);
    return eResult;
}		// -----  end of function TakeOff  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  Swap
//  Description:  交换装备法宝
// =====================================================================================
EEquipTrumpResult CEquipTrumpSlot::Swap (CEquipTrumpPtr pEquipTrump, INT16 wIndex, UINT32 dwFighterID)
{
    CPack& rPack =  GetUser()->GetPack();
    EEquipTrumpResult eResult = eETRFailed;
    if (!pEquipTrump)
        return eResult;

    auto it = _mapSlotType.find(wIndex);
    if (it == _mapSlotType.end())
        return eETRSlotLock;
    EEquipTrumpSlotType eSlotType = pEquipTrump->GetSlotType();
    if (eSlotType == eETSTNone || eSlotType != it->second)
        return eETRSlotConflict;

    TSetUINT16& rsetConflictID = CItemMgr::GetConflictID(pEquipTrump->GetID());
    TSetUINT16& rsetTeamConflictID = CItemMgr::GetTeamConflictID(pEquipTrump->GetID());

    for (auto & rPair : _mapSlotType)
    {
        if (rPair.second != eSlotType)
            continue;
        if (HasObj(rPair.first) && wIndex != rPair.first)
        {
            CItemPtr pItem = Get(rPair.first);
            if (pItem)
            {
                auto it = rsetConflictID.find(pItem->GetID());
                // 个人装备有冲突，无法更换
                if (it != rsetConflictID.end() || pEquipTrump->GetID() == pItem->GetID()) 
                {
                    CUserPtr pUser = GetUser();
                    if (pUser)
                    {
                        string strPkg;
                        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eEquipTrump12);
                        pUser->SendPkg(strPkg);
                    }
                    return eETRSlotConflict;
                }
            }
        }
    }

    //  检查是否队伍中有冲突的装备
    CFighterPtr pFighter = GetFighter();
    if (!pFighter)
        return eETRFailed;
    CFighterManagerPtr pFighterManager = pFighter->GetFighterManager();
    if (pFighterManager)
    {
        TVecFighterPtr rvecFighters;
        pFighterManager->GetAllFighters(rvecFighters);

        for(auto& pFighter0 : rvecFighters)
        {
            if (!pFighter0 || !pFighter0->IsHeroFighter() || pFighter0 == pFighter)
                continue;
            CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter0);
            if(pHeroFighter)
            {
                CEquipTrumpSlot& rEquipTrumpSlot = pHeroFighter->GetEquipTrumpSlot(); 

                for (auto & rID : rsetTeamConflictID)
                {
                    CItemPtr pItem = rEquipTrumpSlot.GetSlotByID(rID);
                    if(pItem)
                        return eETRSlotConflict;
                }
            }
        }
    }

    if (HasObj(wIndex))
    {
        CItemPtr pItem = Get(wIndex);
        if (pItem)
        {
            if (pItem->IsEquipTrumpItem())
            {
                CEquipTrumpPtr pEquipTrump2 = dynamic_pointer_cast<CEquipTrump>(pItem);
                if (pEquipTrump2)
                {
                    Reset(wIndex);
                    pEquipTrump2->SetOwnerID(0);
                    pEquipTrump2->SetIndex(-1);
                    rPack.AddItemOrMail(*pItem);
                }
            }
        }
    }

    rPack.DelItem(*pEquipTrump, true, false, NLogDataDefine::ItemTo_GM);
    Set(wIndex, pEquipTrump);
    pEquipTrump->SetOwnerID(pFighter->GetInstID());
    pEquipTrump->SetIndex(wIndex);
    pEquipTrump->SetStoreType(eStoreEquipTrump);
    eResult = eETRSuccess;
    CItem::Update2DB(*pEquipTrump, GetUser()->GetUserID(), GetUser()->GetUserID(), GetStoreType(), wIndex, eOpUpdate);
    SetDirty(true);

    NotifyInfo();
    CUserPtr pUser = GetUser(); 
    if(pUser && pUser->GetPlayer())
    {
        TVecINT32 vecParam;
        vecParam.push_back(pEquipTrump->GetID());
        vecParam.push_back(dwFighterID);

        for (auto& rPair : _mapSlotType)
        {
            UINT8 byIndex = rPair.first;
            if (!HasObj(byIndex))
            {
                continue;
            }

            CItemPtr pItem = Get(byIndex);
            if (!pItem)
            {
                continue;
            }

            vecParam.push_back(pItem->GetID());
        }

        pUser->GetPlayer()->OnEvent(eEventType_TrumpEquip,vecParam);
    }
    return eResult;
}		// -----  end of function Swap  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  NotifyInfo
//  Description:  广播通知
// =====================================================================================
void CEquipTrumpSlot::NotifyInfo () const
{
    CUserPtr pUser = GetUser();
    CFighterPtr pFighter = GetFighter();
    if (!pUser || !pFighter)
        return;
    NItemProt::TVecEquipTrump vecEquipTrump;
    if (!GetAllInfo(vecEquipTrump))
        return;
    string strPkg = g_EquipTrumpProtS.BuildPkg_EquipTrumpNotify(pFighter->GetInstID(), eETSTNone, vecEquipTrump);
    pUser->SendPkg(strPkg);
}		// -----  end of function NotifyInfo  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetDirty
//  Description:  设置更新标志
// =====================================================================================
void CEquipTrumpSlot::SetDirty(bool bDirty) const 
{ 
    CArrSlots::SetDirty(bDirty);
    CFighterPtr pFighter = GetFighter();
    if (pFighter)
        pFighter->SetDirty(true);
    CFighterManagerPtr pFighterManager = pFighter->GetFighterManager();
    if (!pFighterManager)
        return;
    pFighterManager->SetDirty(eAttrGpEquipTrump);
}		// -----  end of function SetDirty  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetEquipTrumpCount
//  Description:  获取一定条件的法宝数量
// =====================================================================================

UINT32 CEquipTrumpSlot::GetEquipTrumpCount(UINT8 byMinQuality,UINT8 byMinInsifyLevel)
{
    UINT32 dwCount = 0;

    for (auto& rPair : _mapSlotType)
    {
        UINT8 byIndex = rPair.first;
        if (!HasObj(byIndex))
        {
            LOG_DBG << "Index(" << static_cast<UINT32>(rPair.first) << ") has no Obj.";
            continue;
        }

        CItemPtr pItem = Get(byIndex);
        if (!pItem)
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") has no Obj.";
            continue;
        }

        if (!pItem->IsEquipTrumpItem())
        {
            LOG_CRI << "Index(" << static_cast<UINT32>(rPair.first) << ") is not EquipTrump.";
            continue;
        }

        if(pItem->GetQuality()==byMinQuality && pItem->GetEquipTrumpLevel()>= byMinInsifyLevel)
        {
            dwCount++;
        }
    }

    return dwCount;
}
