// =====================================================================================
//
//       Filename:  EquipTrump.cpp
//
//    Description:  装备用的法宝
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

#include "EquipTrump.h"
#include "EquipTrumpMgr.h"
#include "User.h"
#include "Player.h"
#include "Random.h"
#include "SysMsgDefine.h"
#include "TrumpMgr.h"
#include "ItemMgr.h"
#include "FighterManager.h"
#include "HeroFighter.h"
#include "EquipTrumpSlot.h"
#include "FeedBackMgr.h"

CEquipTrump::CEquipTrump(UINT16 wItemID) : 
    CItem(wItemID),
    _qwOwnerID(0), _bDirty(true),
    _byIntensifyLvl(1), 
    _byIntensifyLvlMax(9),
    _dwBlessing(0),
    _dwXiLianBlessing(0)
{
}

CEquipTrump::~CEquipTrump() 
{
}

void CEquipTrump::InitAttr()
{
    _byIntensifyLvl = 1;
    _byIntensifyLvlMax = 9;

    if(!_vecMaxShuffleInfo.empty())
    {
        return;
    }

    SXiLianCFGExPtr  pXiLianCFGEx = CEquipTrumpMgr::Instance().GetXiLianCFGEx(GetID());
    if(NULL == pXiLianCFGEx)
    {
        return;
    }
    
    if(_vecMaxShuffleInfo.size() < pXiLianCFGEx->_Attrnum)
    {
        _vecMaxShuffleInfo.resize(pXiLianCFGEx->_Attrnum);
    }

    //筛选随机库
    TVecShuffleInfo vecRandom = pXiLianCFGEx->_vecMaxShuffleInfo;
  
    //随机属性
    for(UINT16 i = 0; i< pXiLianCFGEx->_Attrnum; i++)
    {
        {
            SShuffleInfo oMaxShuffleInfo;
            if(!GetRandomVec(oMaxShuffleInfo,vecRandom))
            {
                LOG_CRI<<" Fatal Error";
                continue;
            }
            _vecMaxShuffleInfo[i].dwType = oMaxShuffleInfo.dwType;
            UINT8 bySelect = 0;
            _vecMaxShuffleInfo[i].dwValue = oMaxShuffleInfo.dwValue*GetRandomRate(pXiLianCFGEx->_vecXiLianProb,0,bySelect);
        }
    }

}

// ===  FUNCTION  ======================================================================
//         Name:  GetOwnerID
//  Description:  获取拥有者ID
// =====================================================================================
UINT64 CEquipTrump::GetOwnerID () const
{
    return _qwOwnerID;
}		// -----  end of function GetOwnerID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetIntensify
//  Description:  获取强化等级
// =====================================================================================
UINT8 CEquipTrump::GetIntensify () const
{
    return _byIntensifyLvl;
}		// -----  end of function GetIntensify  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ToProt
//  Description: 生成协议结构体
// =====================================================================================
SItemPtr CEquipTrump::ToProt() const
{
    SEquipTrump* pEquipTrump = new SEquipTrump;
    if(pEquipTrump == NULL)
        return NULL;
    if(!ToStream(*pEquipTrump))
    {
        delete pEquipTrump;
        return NULL;
    }
    return SItemPtr(pEquipTrump);
}		// -----  end of function ToProt  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  FromStream
//  Description:  从协议反序列化
// =====================================================================================
bool CEquipTrump::FromStream(const SEquipTrump& rStream)
{
    CItem::FromStream(rStream);

    _qwOwnerID = rStream.qwOwnerID;
    _byIntensifyLvl = rStream.byIntensifyLvl;
    _dwBlessing     = rStream.dwBlessing;
    _vecMaxShuffleInfo = rStream.vecShuffleInfo;
    _byIntensifyLvlMax = rStream.byIntensifyLvlMax;
    _dwXiLianBlessing  = rStream.dwXiLianBlessing;

    return true;
}		// -----  end of function FromStream  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetDirty
//  Description:  设置更新标志
// =====================================================================================
void CEquipTrump::SetDirty (bool bDirty, CPlayerPtr pPlayer)
{
    if (bDirty)
        CBattlePointOwner::SetDirty();
    _bDirty = bDirty;

    if (bDirty)
    {
        if(!pPlayer)
            return;
        CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
        if(!pFighterManager)
            return;
        pFighterManager->SetDirty(eAttrGpEquipTrump);
        CFighterPtr pFighter = pFighterManager->GetFighterByInstID(_qwOwnerID);
        if (pFighter && pFighter->IsHeroFighter())
        {
            CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
            if (pHeroFighter)
                pHeroFighter->GetEquipTrumpSlot().SetDirty(true);
        }
    }

}		// -----  end of function SetDirty  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSlotType
//  Description:  获取法宝可以入槽类型
// =====================================================================================
EEquipTrumpSlotType CEquipTrump::GetSlotType () const
{
    EEquipTrumpSlotType eSlotType = eETSTNone;
    auto rCFG = GetItemConfig();
    switch(rCFG._Type)
    {
        case 205: // 先天  
        case 206: // 被动  
        case 207: // 光环  
        case 208: // 变身
            eSlotType = static_cast<EEquipTrumpSlotType>(rCFG._Type - 204);
            break;
        default:
            break;
    }
    return eSlotType;
}		// -----  end of function GetSlotType  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAttr
//  Description:  获取对应增加的属性
// =====================================================================================
void CEquipTrump::GetAttr (TVecFloat& rvecAttr) const
{
    CTrumpMgr::Instance().GetHaloAttr(rvecAttr, GetID(), GetIntensify(), 1);
    CItemMgr::AppendAttr2(GetID(), rvecAttr);

    for(size_t i= 0; i <_vecMaxShuffleInfo.size(); ++ i)
    {
        const SShuffleInfo& rShuffleInfo = _vecMaxShuffleInfo[i];
        if(rShuffleInfo.dwType >= rvecAttr.size())
            rvecAttr.resize(rShuffleInfo.dwType);
        rvecAttr[rShuffleInfo.dwType] += rShuffleInfo.dwValue;
    }

}		// -----  end of function GetAttr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetSkillID
//  Description:  获取对应的技能ID
// =====================================================================================
UINT32 CEquipTrump::GetSkillID () const
{
    return CTrumpMgr::Instance().GetSkill(GetID(), GetIntensify(), 1);
}		// -----  end of function GetSkillID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllSkillsID
//  Description:  获取所有的技能ID
// =====================================================================================
void CEquipTrump::GetAllSkillsID(TVecUINT32& vecSkillsID) const
{
    UINT32 dwSkillID = CTrumpMgr::Instance().GetSkill(GetID(), GetIntensify(), 1);
    if (dwSkillID)
        vecSkillsID.push_back(dwSkillID);
}		// -----  end of function GetAllSkillsID  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  AppendAttr
//  Description:  获取属性
// =====================================================================================
void CEquipTrump::AppendBPAttr(TVecFloat& rvecAttr) const
{
    GetAttr(rvecAttr);
}		// -----  end of function AppendAttr  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  SetOwnerID
//  Description:  设置所有者ID
// =====================================================================================
void CEquipTrump::SetOwnerID (UINT64 qwOwnerID) 
{
    _qwOwnerID = qwOwnerID;
}		// -----  end of function SetOwnerID  ----- //
// ===  FUNCTION  ======================================================================
//         Name:  ToStream
//  Description:  协议序列化
// =====================================================================================
bool CEquipTrump::ToStream(SEquipTrump& rStream) const
{
    CItem::ToStream(rStream);

    rStream.qwOwnerID = _qwOwnerID;
    rStream.byIntensifyLvl = _byIntensifyLvl;
    rStream.byIntensifyLvlMax = _byIntensifyLvlMax;
    rStream.dwBlessing        = _dwBlessing;
    rStream.vecShuffleInfo    = _vecMaxShuffleInfo;
    rStream.dwXiLianBlessing  = _dwXiLianBlessing;
    return true;
}		// -----  end of function ToStream  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  IsDirty
//  Description:  是否需要更新
// =====================================================================================
bool CEquipTrump::IsDirty () const
{
    return _bDirty;
}		// -----  end of function IsDirty  ----- //

// 强化
EEquipTrumpIntensifyResult CEquipTrump::OnIntensify(CUser& rUser,ETIntensifyType eType,
        shared_func<CEquipTrumpProtSvr::SIntensifyAck>& fnAck)
{
    CPlayerPtr pPlayer = rUser.GetPlayer();
    if(NULL == pPlayer)
    {
        return eETIRFailed;
    }

    if(eType >= eETIntensify_MAX || eType <= 0)
    {
        return eETIRTypeErr;
    }

    bool bSucess = false;

    EEquipTrumpIntensifyResult eRet = IntensifyOnce(rUser,eType,bSucess);

    fnAck->bSucess = bSucess;

    CItem::ItemChangeNotify(rUser,*this,(NItemProt::EStoreType)GetStoreType(),this->GetIndex(),rUser.GetUserID());
    CItem::Update2DB(*this,rUser.GetUserID(),rUser.GetUserID(),(NItemProt::EStoreType)this->GetStoreType(),this->GetIndex());

    SetDirty(true, rUser.GetPlayer());

    return eRet;
}

EEquipTrumpIntensifyResult CEquipTrump::IntensifyOnce(CUser& rUser,ETIntensifyType eType,bool& bSucess)
{
    CPlayerPtr pPlayer = rUser.GetPlayer();
    if(NULL == pPlayer)
    {
        return eETIRFailed;
    }

    STrumpIntensifyCFGExPtr pTrumpIntensifyEx = CEquipTrumpMgr::Instance().GetTrumpIntensify(GetItemAttrID(),GetIntensifyLevel());
    if(NULL == pTrumpIntensifyEx)
    {
        return eETIRCFGErr;
    }
    
    STrumpIntensifyCFGExPtr pNextLevel = CEquipTrumpMgr::Instance().GetTrumpIntensify(GetItemAttrID(),GetIntensifyLevel()+1);
    if(NULL == pNextLevel)
    {
        return eETIRMaxErr;
    }

    SStrengthProbabilityCFGExPtr pStrengthProbabilityCFGEx = 
        CEquipTrumpMgr::Instance().GetStrengthProbabilityCFGEx(pTrumpIntensifyEx->_ProbNeed);
    if(NULL == pStrengthProbabilityCFGEx)
    {
        return eETIRCFGErr;
    }

    UINT32 dwProtect = pStrengthProbabilityCFGEx->_Protect2;

    UINT32 dwProb = 0;
    UINT16 wItemID  = 0;
    UINT32 dwItemCnt = 1;
    switch(eType)
    {
        case eETIntensify_NormalGold:
            {
                dwProb = pStrengthProbabilityCFGEx->_Probability1;
                wItemID = 290;
            }
            break;
        case eETIntensify_GodGold:
            {
                dwProb = pStrengthProbabilityCFGEx->_Probability2;
                wItemID = 291;
            }
            break;
        default:
            {
                return eETIRFailed;
            }
    }

    if(!wItemID)
    {
        return eETIRFailed;
    }
    
    CPack& rPack = rUser.GetPack();


    if(!rPack.CanSubItemWithID(wItemID,dwItemCnt,eBindUseBindFirst))
    {
        //pPlayer->SendSysMsg(eMsgBeautyLackItem);
        return eETIRItemErr;
    }


    rPack.SubItemWithID(wItemID,dwItemCnt,NLogDataDefine::ItemTo_ETrumpStrength,eBindUseBindFirst);


    if(eType == eETIntensify_GodGold)
    {
        dwProb += _dwBlessing;
    }

   
    UINT32 dwRandValue = CRandom::RandInt(1,10000);
    
    bool bFail = dwProb < dwRandValue;

    if(bFail)
    {
        if(_byIntensifyLvl&& (eType == eETIntensify_NormalGold))
        {
            _byIntensifyLvl--;
            //g_FeedBackMgr.OnEquipTrumpChange(*rUser.GetPlayer(),GetQuality(),_byIntensifyLvl);
        }

        if(eType == eETIntensify_GodGold)
        {
            _dwBlessing += dwProtect; 
            if(_dwBlessing > 5000)
            {
                _dwBlessing = 5000;
            }
        }

        bSucess = false;
        TVecINT32 vecParam;
        vecParam.push_back(_byIntensifyLvl);
        vecParam.push_back(wItemID);
        vecParam.push_back(GetID());
        pPlayer->OnEvent(eEventType_TrumpToStrongSucess,vecParam);
    }
    else
    {
        _byIntensifyLvl++;
        bSucess = true;
        _dwBlessing = 0;

        TVecINT32 vecParam;
        vecParam.push_back(_byIntensifyLvl);
        vecParam.push_back(wItemID);
        vecParam.push_back(GetID());
        pPlayer->OnEvent(eEventType_TrumpToStrongFaild,vecParam);

        if(_byIntensifyLvl == 8)
        {
            g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eEquipTrump8,
                        BuildStrVec(pPlayer->GetColor(),pPlayer->GetName(),this->GetQuality(),this->GetItemName()));
        }
        
        if(_byIntensifyLvl == 9)
        {
            g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eEquipTrump9,
                        BuildStrVec(pPlayer->GetColor(),pPlayer->GetName(),this->GetQuality(),this->GetItemName()));
        }

        g_FeedBackMgr.OnEquipTrumpChange(*rUser.GetPlayer(),GetQuality(),_byIntensifyLvl);
    }
    SetDirty(true, pPlayer);

    return eETIRSuccess;

}

// 一键强化
EEquipTrumpIntensifyResult CEquipTrump::OnIntensifyOneKey(CUser& rUser,ETIntensifyType eType,
        shared_func<CEquipTrumpProtSvr::SIntensifyOneKeyAck>& fnAck)
{
    CPlayerPtr pPlayer = rUser.GetPlayer();
    if(NULL == pPlayer)
    {
        return eETIRFailed;
    }

    if(eType >= eETIntensify_MAX || eType <= 0)
    {
        return eETIRTypeErr;
    }

    UINT32 dwIntensifyCount = 0;
    bool bSucess = false;
    do
    {

        EEquipTrumpIntensifyResult eRet = IntensifyOnce(rUser,eType,bSucess);

        fnAck->bSucess = bSucess;

        dwIntensifyCount++;

        if(bSucess || (eRet != eETIRSuccess))
        {
            break;
        }

        if(dwIntensifyCount > 100000)
        {
            break;
        }

    }while(1);


    fnAck->bSucess = bSucess;
    fnAck->dwIntensifyCount = dwIntensifyCount;

    CItem::ItemChangeNotify(rUser,*this,(NItemProt::EStoreType)GetStoreType(),this->GetIndex(),rUser.GetUserID());
    CItem::Update2DB(*this,rUser.GetUserID(),rUser.GetUserID(),(NItemProt::EStoreType)this->GetStoreType(),this->GetIndex());

    SetDirty(true, rUser.GetPlayer());

    return eETIRSuccess;
}

bool IsLockBitCount(UINT32 dwLock,UINT8 dwIndex)
{
    UINT32 dwBit = 0;
    dwBit = 1<<dwIndex;
    return ((dwBit&dwLock) != 0);
}

bool CEquipTrump::GetRandomVec(SShuffleInfo&rMaxShuffleInfo,TVecShuffleInfo& vecRandom)
{
    if(vecRandom.empty())
    {
        return false;
    }

    if(vecRandom.size() == 1)
    {
        rMaxShuffleInfo = vecRandom[0];
        return true;
    }

    UINT32 dwMaxID = vecRandom.size();
    UINT32 dwSelectID = CRandom::RandInt(0,dwMaxID-1);
    if(dwSelectID>= vecRandom.size())
    {
        LOG_CRI<<"Error!!!";
        return false;
    }
    rMaxShuffleInfo =  vecRandom[dwSelectID];
    vecRandom.erase(vecRandom.begin()+dwSelectID);
    return true;
}

FLOAT CEquipTrump::GetRandomRate(TVecXiLianProb& vecXiLianProb,UINT32 dwBlessValue,UINT8& bySelect)
{
    if(vecXiLianProb.empty())
    {
        LOG_CRI<<"vecXiLianProb.empty()";
        return 0;
    }

    UINT32 dwMaxRandom = vecXiLianProb[vecXiLianProb.size()-1].dwRateValue;
    if(dwMaxRandom<1)
    {
        LOG_CRI<<"dwMaxRandom<1";
        return 0;
    }

    UINT32 dwRandomValue = CRandom::RandInt(1,dwMaxRandom);

    UINT32 dwSelect = vecXiLianProb.size()-1;

    for(size_t i = 0; i < vecXiLianProb.size(); i++)
    {
        if(vecXiLianProb[i].dwRateValue >= dwRandomValue)
        {
            dwSelect = i;
            break;
        }
    }

    if(dwSelect >= vecXiLianProb.size())
    {
        LOG_CRI<<"dwSelect >= vecXiLianProb.size";
        return 0;
    }

    bySelect = dwSelect;

    UINT32 dwEndValue = CRandom::RandInt(vecXiLianProb[dwSelect].dwMinRate,vecXiLianProb[dwSelect].dwMaxRate);

    return dwEndValue/100.0;
}

// 洗炼
EEquipTrumpShuffleResult CEquipTrump::OnShuffleResult(CUser& rUser,UINT32 dwLock)
{
    CPlayerPtr pPlayer = rUser.GetPlayer();
    if(NULL == pPlayer)
    {
        return eETSRFailed;
    }

    SXiLianCFGExPtr  pXiLianCFGEx = CEquipTrumpMgr::Instance().GetXiLianCFGEx(GetID());
    if(NULL == pXiLianCFGEx)
    {
        return eETSRFailed;
    }
    
    if(_vecMaxShuffleInfo.size() < pXiLianCFGEx->_Attrnum)
    {
        _vecMaxShuffleInfo.resize(pXiLianCFGEx->_Attrnum);
    }

   
    std::set<UINT32> setLock;
    
    for(UINT16 i = 0; i< pXiLianCFGEx->_Attrnum; i++)
    {
        if(IsLockBitCount(dwLock,i))
        {
           if(_vecMaxShuffleInfo[i].dwType)
            setLock.insert(_vecMaxShuffleInfo[i].dwType);
        }
    }

    UINT8 byLockCount = setLock.size();

    if( byLockCount  >= pXiLianCFGEx->_Attrnum)
    {
        return eETSRFailed;
    }

   
     CPack& rPack = rUser.GetPack();

     UINT32 dwXiLianItemID = 292;
     UINT32 dwXiLianCnt = 1;

     UINT32 dwXiLianProctedItemID = 293;
     UINT32 dwXiLianProctedCnt = byLockCount;

    if(!rPack.CanSubItemWithID(dwXiLianItemID,dwXiLianCnt,eBindUseBindFirst))
    {
        //pPlayer->SendSysMsg(eMsgBeautyLackItem);
        return eETSRFailed;
    }

    if(!rPack.CanSubItemWithID(dwXiLianProctedItemID,dwXiLianProctedCnt,eBindUseBindFirst))
    {
        //pPlayer->SendSysMsg(eMsgBeautyLackItem);
        return eETSRFailed;
    }

    rPack.SubItemWithID(dwXiLianItemID,dwXiLianCnt,NLogDataDefine::ItemTo_ETrumpStrength,eBindUseBindFirst);

    rPack.SubItemWithID(dwXiLianProctedItemID,dwXiLianProctedCnt,NLogDataDefine::ItemTo_ETrumpStrength,eBindUseBindFirst);

   
    //筛选随机库
    TVecShuffleInfo vecRandom = pXiLianCFGEx->_vecMaxShuffleInfo;

    for(size_t i =0;i < vecRandom.size();)
    {
        if(setLock.find(vecRandom[i].dwType) != setLock.end())
        {
            vecRandom.erase(vecRandom.begin()+i);
        }
        else
        {
            i++;
        }
    }
  
    bool bNotify = false;

    //随机属性
    for(UINT16 i = 0; i< pXiLianCFGEx->_Attrnum; i++)
    {
        if(IsLockBitCount(dwLock,i) == false)
        {
            SShuffleInfo oMaxShuffleInfo;
            if(!GetRandomVec(oMaxShuffleInfo,vecRandom))
            {
                LOG_CRI<<" Fatal Error";
                continue;
            }

            UINT8 bySelect = 0;
            _vecMaxShuffleInfo[i].dwType = oMaxShuffleInfo.dwType;

            float fRate = 0.0;
            if(_dwXiLianBlessing <SParamConfig::wShuffer1)
            {
                fRate = GetRandomRate(pXiLianCFGEx->_vecXiLianProb,0,bySelect); 
            }
            else if(_dwXiLianBlessing < SParamConfig::wShuffer2)
            {
                fRate = GetRandomRate(pXiLianCFGEx->_vecXiLianProb2,0,bySelect);
            }
            else
            {
                fRate = GetRandomRate(pXiLianCFGEx->_vecXiLianProb3,0,bySelect);
            }
            _vecMaxShuffleInfo[i].dwValue = oMaxShuffleInfo.dwValue*fRate;

            if(bySelect == pXiLianCFGEx->_vecXiLianProb.size()-1)
            {
                bNotify = true;
                _dwXiLianBlessing = 0;
            }
        }
    }

    //洗练数目
    _dwXiLianBlessing++;


    if(bNotify&& rUser.GetPlayer())
    {
        g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eEquipTrump10,
                BuildStrVec(rUser.GetPlayer()->GetColor(),rUser.GetPlayer()->GetName(),this->GetQuality(),this->GetItemName()));
    }

    //洗练数目
    _dwXiLianBlessing++;
    CItem::ItemChangeNotify(rUser,*this,(NItemProt::EStoreType)GetStoreType(),this->GetIndex(),rUser.GetUserID());
    CItem::Update2DB(*this,rUser.GetUserID(),rUser.GetUserID(),(NItemProt::EStoreType)this->GetStoreType(),this->GetIndex());

    SetDirty(true, rUser.GetPlayer());
    
    TVecINT32 vecParam;
    vecParam.push_back(byLockCount);
    vecParam.push_back(GetID());
    pPlayer->OnEvent(eEventType_TrumpPu,vecParam);

    return eETSRSuccess;
}

//获取强化等级
UINT8 CEquipTrump::GetIntensifyLevel()
{
    return _byIntensifyLvl;
}


//获取关联物品属性id
UINT32 CEquipTrump::GetItemAttrID()
{
    return GetItemConfig()._AttrIdx_1;
}



