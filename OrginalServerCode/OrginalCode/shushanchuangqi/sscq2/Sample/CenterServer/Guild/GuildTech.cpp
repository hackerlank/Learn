#include "GuildTech.h"
#include "GuildMgr.h"
#include "Protocols.h"
#include "GuildUser.h"
#include "Guild.h"
#include "GuildBuilding.h"
#include "User.h"

static const UINT8 TECH_COUNT = 4;

CGuildTech::CGuildTech(ETechType eType) : 
    _eType(eType)
{
    _eLevelType = eLevelUpByLevelResetExp;
    SetLevel(0);
}

CGuildTech::~CGuildTech()
{
}

bool CGuildTech::InitFromDB(ETechType eType, UINT16 wLevel)
{
    _eType = eType;
    CLevelObject::InitFromDB(0, wLevel, 0);
    return true;
}

UINT32 CGuildTech::GetTableLevelExp(UINT16 wLevel) const
{
    TVecPGuildTechCFG vecPGuildTechCFG;
    if (!CGuildMgr::Instance().GetTechConfig(_eType, vecPGuildTechCFG))
        return 0;
    if (vecPGuildTechCFG.size() < static_cast<size_t>(wLevel + 1))
        return 0;
    return vecPGuildTechCFG[wLevel]->_Cost;
}

ETechType CGuildTech::GetType() const
{
    return _eType;
}

UINT32 CGuildTech::GetAttrValue() const
{
    TVecPGuildTechCFG vecPGuildTechCFG;
    if (!CGuildMgr::Instance().GetTechConfig(_eType, vecPGuildTechCFG))
        return 0;
    if (vecPGuildTechCFG.size() < static_cast<size_t>(GetLevel() + 1))
        return 0;
    return vecPGuildTechCFG[GetLevel()]->_Value;
}

// 返回等级
UINT16 CGuildTech::GetTableLevel(UINT32 exp) const
{
    TVecPGuildTechCFG vecPGuildTechCFG;
    if (!CGuildMgr::Instance().GetTechConfig(_eType, vecPGuildTechCFG))
        return 0;
    if (vecPGuildTechCFG.size() < 2)
        return 0;
    UINT16 wLevel = 0;
    for (auto it = vecPGuildTechCFG.begin() + 1; it != vecPGuildTechCFG.end(); ++it)
    {
        if (((*it)->_Cost) <= exp)
            ++wLevel;
    }
    return wLevel;
}

//  返回最高等级
UINT16 CGuildTech::GetMaxLevel() const
{
    TVecPGuildTechCFG vecPGuildTechCFG;
    if (!CGuildMgr::Instance().GetTechConfig(_eType, vecPGuildTechCFG))
        return 0;
    if (vecPGuildTechCFG.empty())
        return 0;
    return vecPGuildTechCFG.size() - 1;
}

void CGuildTech::GetAllInfo(SGuildTechInfo& rInfo) const
{
    rInfo.eType     = _eType;
    rInfo.wLevel    = GetLevel();
}

bool CGuildTech::GetFtAttr(TVecFtAttrMod& vecFtAttr) const
{
    TVecPGuildTechCFG vecPGuildTechCFG;
    if (!CGuildMgr::Instance().GetTechConfig(_eType, vecPGuildTechCFG))
        return false;
    if (vecPGuildTechCFG.size() < static_cast<size_t>(GetLevel() + 1))
        return false;
    for (size_t i = 0; i < vecPGuildTechCFG[GetLevel()]->_vecFtAttrMod.size(); ++ i)
    {
        vecFtAttr.push_back(vecPGuildTechCFG[GetLevel()]->_vecFtAttrMod[i]);
    }
    return true;
    /*
       switch(_eType)
       {
       case eTechAttack: //攻击之魂
       {
       SFtAttrMod sAttr;
       sAttr._eAttr = EFIGHTATTR_PHYATK;
       sAttr._fValue = GetAttrValue();
       vecFtAttr.push_back(sAttr);
       sAttr._eAttr = EFIGHTATTR_MGCATK;
       sAttr._fValue = GetAttrValue();
       vecFtAttr.push_back(sAttr);
       }
       break;
       case eTechPhyDef: //物防之魂
       {
       SFtAttrMod sAttr;
       sAttr._eAttr = EFIGHTATTR_PHYDEF;
       sAttr._fValue = GetAttrValue();
       vecFtAttr.push_back(sAttr);
       }
       break;
       case eTechMgcDef: //魔防之魂
       {
       SFtAttrMod sAttr;
       sAttr._eAttr = EFIGHTATTR_MGCDEF;
       sAttr._fValue = GetAttrValue();
       vecFtAttr.push_back(sAttr);
       }
       break;
       case eTechSpeed: //身法之魂
       {
       SFtAttrMod sAttr;
       sAttr._eAttr = EFIGHTATTR_SPEED;
       sAttr._fValue = GetAttrValue();
       vecFtAttr.push_back(sAttr);
       }
       break;
       case eTechHP: //生命之魂
       {
       SFtAttrMod sAttr;
       sAttr._eAttr = EFIGHTATTR_MAXHP;
       sAttr._fValue = GetAttrValue();
       vecFtAttr.push_back(sAttr);
       }
       break;
       case eTechHit: //命中之魂
       {
       SFtAttrMod sAttr;
       sAttr._eAttr = EFIGHTATTR_HIT;
       sAttr._fValue = GetAttrValue();
       vecFtAttr.push_back(sAttr);
       }
       break;
       }
       return true;
       */
}

UINT16 CGuildTech::GetUserLevel() const
{
    TVecPGuildTechCFG vecPGuildTechCFG;
    if (!CGuildMgr::Instance().GetTechConfig(_eType, vecPGuildTechCFG))
        return 0;
    if (vecPGuildTechCFG.size() < GetLevel())
        return 0;
    return vecPGuildTechCFG[GetLevel()]->_RoleLevel;
}

////////////////////////////////////////////////////////////////////////////////////////////////

CGuildTechOwner::CGuildTechOwner(CGuildUserPtr pGuildUser) : 
    _pGuildUser(pGuildUser)
{
    for (UINT8 byIndex = static_cast<UINT8>(eTechNone) + 1; byIndex < eTechMax; ++byIndex)
    {
        TVecPGuildTechCFG vecPGuildTechCFG;
        if (!CGuildMgr::Instance().GetTechConfig(static_cast<ETechType>(byIndex), vecPGuildTechCFG))
            continue;
        CGuildTechPtr pTech (new CGuildTech(static_cast<ETechType>(byIndex)));
        _mapGuildTechPtr.insert(make_pair(static_cast<ETechType>(byIndex), pTech));
    }
}

CGuildTechOwner::~CGuildTechOwner()
{
}

// 从数据库加载
bool CGuildTechOwner::InitFromDB(const TVecGuildTechInfo& rvecTechs)
{
    for (auto it = rvecTechs.begin(); it != rvecTechs.end(); ++it)
    {
        TVecPGuildTechCFG vecPGuildTechCFG;
        if (!CGuildMgr::Instance().GetTechConfig((*it)->eType, vecPGuildTechCFG))
            continue;
        CGuildTechPtr pTech(new CGuildTech((*it)->eType));
        pTech->InitFromDB((*it)->eType, (*it)->wLevel);
        _mapGuildTechPtr[(*it)->eType] = pTech;
    }
    return true;
}

UINT64 CGuildTechOwner::GetGuildID() const
{
    if (!_pGuildUser)
        return 0;
    return _pGuildUser->GetGuildID();
}

UINT16 CGuildTechOwner::GetLevel(ETechType eType) const
{
    auto it = _mapGuildTechPtr.find(eType);
    if (it == _mapGuildTechPtr.end())
        return 0;
    return (it->second)->GetLevel();
}

UINT16 CGuildTechOwner::GetMaxLevel(ETechType eType) const
{
    auto it = _mapGuildTechPtr.find(eType);
    if (it == _mapGuildTechPtr.end())
        return 0;
    return it->second->GetMaxLevel();
}

// 帮派科技升级
bool CGuildTechOwner::UpgradeTech(ETechType eType, ETechResult& eResult)
{
    if (!_pGuildUser)
    {
        eResult = eGTResultFailed;
        return false;
    }

    auto it = _mapGuildTechPtr.find(eType);
    if (it == _mapGuildTechPtr.end())
    {
        eResult = eGTResultFailed;
        return false;
    }
    CGuildTechPtr pTech = it->second;

    if (pTech->GetLevel() >= GetMaxLevel(eType)) // 已经最高等级
    {
        eResult = eGTResultLevelMax;
        return false;
    }

    if (pTech->GetUserLevel() > _pGuildUser->GetLevel()) // 玩家等级不足
    {
        eResult = eGTResultUserLevelTooLow;
        return false;
    }

    CGuildPtr pGuild = _pGuildUser->GetGuild();
    CGuildBuildingOwnerPtr pBuildingOwner;
    if (pGuild)
        pBuildingOwner = pGuild->GetBuildingOwner();

    if (!pBuildingOwner || (pTech->GetLevel() >= pBuildingOwner->GetAttrValue(eBuildingSword)))  // 剑阁等级过低
    {
        eResult = eGTResultBuildingLevelTooLow;
        return false;
    }
    UINT32 dwContribution = _pGuildUser->GetContribution();
    UINT32 dwTmpContrib = dwContribution;
    ELevelObjectErr eErr = pTech->TryLevelUp(dwContribution);
    if (eErr == eErrNoEnoughExp)
    {
        eResult = eGTResultLackofSilver;
        return false;
    }
    else if (eErr != eErrSuccess)
    {
        eResult = eGTResultFailed;
        return false;
    }
    if (dwTmpContrib > dwContribution) // 帮贡没有用光
        _pGuildUser->SubContribution(dwTmpContrib - dwContribution);
    else
        _pGuildUser->SetContribution(0);

    CUserPtr pUser = _pGuildUser->GetOnlineUser();
    TVecINT32 vecParam2;
    ostringstream strInfo2;
    vecParam2.push_back(eType);
    vecParam2.push_back(pTech->GetLevel());  //占位
    for (auto it = _mapGuildTechPtr.begin(); it != _mapGuildTechPtr.end(); ++it)
    {
        if (it->second)
            vecParam2.push_back(it->second->GetLevel());
    }
    if (pUser && pUser->IsOnLine())
    {
        // 帮派技能id，所有帮派技能等级

        pUser->OnEvent(eEventType_GuildSkillUpgrade,vecParam2, strInfo2.str());
    }
    else
    {
        CUser::AddOffLineEvent(_pGuildUser->GetID(), eEventType_GuildSkillUpgrade,vecParam2, strInfo2.str());
    }
    eResult = eGTResultSuccess;
    return true;
}

void CGuildTechOwner::GetAllInfo(TVecSGuildInfoBase& rvecInfo) const
{
    for (auto it = _mapGuildTechPtr.begin(); it != _mapGuildTechPtr.end(); ++it)
    {
        if (it->second)
        {
            SGuildTechInfoPtr pTechInfo(new SGuildTechInfo);
            pTechInfo->qwGuildID = GetGuildID();
            it->second->GetAllInfo(*pTechInfo);
            rvecInfo.push_back(pTechInfo);
        }
    }
}

void CGuildTechOwner::GetAllInfo(TVecGuildTechInfo& rvecInfo) const
{
    for (auto it = _mapGuildTechPtr.begin(); it != _mapGuildTechPtr.end(); ++it)
    {
        if (it->second)
        {
            SGuildTechInfoPtr pTechInfo(new SGuildTechInfo);
            pTechInfo->qwGuildID = GetGuildID();
            it->second->GetAllInfo(*pTechInfo);
            rvecInfo.push_back(pTechInfo);
        }
    }
}

bool CGuildTechOwner::GetFtAttr(TVecFtAttrMod& vecFtAttr) const
{
    for (auto it = _mapGuildTechPtr.begin(); it != _mapGuildTechPtr.end(); ++it)
    {
        it->second->GetFtAttr(vecFtAttr);
    }
    return true;
}

void CGuildTechOwner::Update2DB(CGuildTechOwnerPtr pTechOwner, EDataChange eChangeType, UINT64 qwOwnerID /* = 0 */)
{
    if (pTechOwner && !qwOwnerID)
        return;

    if (!qwOwnerID)
        qwOwnerID = pTechOwner->GetGuildID();

    TVecGuildTechInfo vecTechInfo;
    if (pTechOwner)
        pTechOwner->GetAllInfo(vecTechInfo);
    string strData;
    COutArchive iar(strData);
    iar << vecTechInfo;
    //g_Center2DBCommC.Send_GuildDataUpdate(qwOwnerID, eGDTTech, eChangeType, strData);
}
