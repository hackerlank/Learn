#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "ViewInfoProtS.h"
#include "FighterManager.h"
#include "HeroFighter.h"
#include "HorseMgr.h"
#include "Trump.h"
#include "GameNetMgr.h"
#include "EquipTrump.h"
#include "EquipTrumpSlot.h"
#include "BeautyMgr.h"
#include "SoulSpaceMgr.h"
#include "CittaSlots.h"
CViewInfoProtS g_ViewInfoProtS;

//接收：获取对方主角信息
bool CViewInfoProtS::OnRecv_GetRoleInfo(
    const std::string& strReceiveName, //对方玩家名字
    shared_func<SGetRoleInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck(true);
        return false;
    }

    UINT64 qwRoleID = pUser->GetUserID();
    g_Game2DBCommC.Send_GetUserIDFromName(strReceiveName, [this,  qwRoleID, fnAck](UINT8 byRet, UINT64 qwReceiveID)
    {
        if(byRet != 0 || qwReceiveID == 0)
        {
            fnAck(true);
            return ;
        }

        CUserPtr pCurUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (NULL == pCurUser)
        {
            fnAck(true);
            return;
        }

        if (qwReceiveID == qwRoleID)
        {
            fnAck(true);
            return;
        }

        CUserPtr pReceive = CUserMgr::GetUserByUserID(qwReceiveID);
        if (NULL != pReceive)
        {
            g_Game2CenterCommC.Send_GetGuildID(qwReceiveID, [this, qwReceiveID, fnAck](UINT8 byRet, UINT64 qwGuildID, const string& strGuildName, UINT8 byGuildLvl, const string& strGuildOwnerName)
            {
                SRoleData roleData;
                if (byRet == 0)
                    this->SetGuildInfo(qwReceiveID, qwGuildID, strGuildName, byGuildLvl, roleData);

                this->GetRoleInfo(qwReceiveID, roleData);

                fnAck->RoleData = roleData;

                fnAck(true);
                return;
            });
        }
        else
        {
            CUserMgr::LoadUser(qwReceiveID,[this, qwReceiveID, fnAck](CUserPtr pReceive)
            {
                if (NULL != pReceive)
                {
                    g_Game2CenterCommC.Send_GetGuildID(qwReceiveID, [this, qwReceiveID, fnAck](UINT8 byRet, UINT64 qwGuildID, const string& strGuildName, UINT8 byGuildLvl, const string& strGuildOwnerName)
                    {
                        SRoleData roleData;
                        if (byRet == 0)
                            this->SetGuildInfo(qwReceiveID, qwGuildID, strGuildName, byGuildLvl, roleData);

                        this->GetRoleInfo(qwReceiveID, roleData);

                        fnAck->RoleData = roleData;

                        fnAck(true);
                        return;
                    });
                }
            });
        }
    });

    return true;
}

bool CViewInfoProtS::SetGuildInfo(UINT64 qwReceiveID, UINT64 qwGuildID, const string& strGuildName, UINT8 byGuildLvl, NViewInfoProt::SRoleData& roleData)
{
    CUserPtr pReceive = CUserMgr::GetUserByUserID(qwReceiveID);
    if (NULL == pReceive)
        return false;

    CPlayerPtr pReceivePlayer = pReceive->GetPlayer();
    if (NULL == pReceivePlayer)
        return false;
    SGuildData guildData;
    guildData.strName = strGuildName;
    guildData.byGuildLvl = byGuildLvl;
    TVecGuildTechInfo vecGuildTech = pReceivePlayer->GetGuildTechInfo();
    for (size_t i = 0; i < vecGuildTech.size(); ++i)
    {
        if (vecGuildTech[i])
        {
            SGuildSkillData guildSkillData;
            guildSkillData.dwGuildSkillID = vecGuildTech[i]->eType;
            guildSkillData.byGuildSkillLvl = vecGuildTech[i]->wLevel;
            guildData.vecGuildSkill.push_back(guildSkillData);
        }
    }
    roleData.vecGuild.push_back(guildData);
    return true;
}

bool CViewInfoProtS::GetRoleInfo(
    UINT64 qwReceiveID,
    NViewInfoProt::SRoleData& roleData //玩家信息 
)
{
    CUserPtr pReceive = CUserMgr::GetUserByUserID(qwReceiveID);
    if (NULL == pReceive)
        return false;

    CPlayerPtr pReceivePlayer = pReceive->GetPlayer();
    if (NULL == pReceivePlayer)
        return false;

    CHeroFighterPtr pMainFighter = pReceivePlayer->GetMainFighter();
    CFighterManagerPtr pFighterManager = pReceivePlayer->GetFighterManager();
    if (NULL == pMainFighter || NULL == pFighterManager)
        return false;

    //基本信息
    roleData.strName = pReceive->GetUserName();
    roleData.byLevel = pReceivePlayer->GetLevel();
    roleData.eCareer = (ECareerType)pMainFighter->GetJob();
    roleData.dwBTPoint = pMainFighter->GetBattlePoint();

    //主将属性
    const TVecFloat& vecAttr = pMainFighter->GetBPAttrVec();
    for(UINT32 i = 0; i< vecAttr.size(); ++i)
    {
        if(vecAttr[i]>0)
        {
            SFtAttrMod oInfo;
            oInfo._eAttr = (EFighterAttr)i;
            oInfo._fValue = vecAttr[i];
            roleData.vecAttr.push_back(oInfo);
        }
    }
    //主将渡劫
    roleData.sDujie.byTemplateID = pMainFighter->GetDujieTemplateID();
    roleData.sDujie.byLevel = pMainFighter->GetDujieLevel();

    //出战散仙
    CFormation& rFormation = pFighterManager->GetFormation();
    {
        TVecLineup vecLineup;
        rFormation.GetLineup(vecLineup);
        for (size_t i = 0; i < vecLineup.size(); ++i)
        {
            if (vecLineup[i].pFighter)
            {
                SBattleFighterData fighterData;
                fighterData.qwInstID = vecLineup[i].pFighter->GetInstID();
                fighterData.wFighterID = vecLineup[i].pFighter->GetFighterID();
                fighterData.byFighterLevel = vecLineup[i].pFighter->GetLevel();
                fighterData.byLevel = vecLineup[i].pFighter->GetDujieLevel();
                fighterData.byTemplateID = vecLineup[i].pFighter->GetDujieTemplateID();
                roleData.vecBattleFighter.push_back(fighterData);
            }
        }
    }

    //技能
    TVecUINT32 vecSkills;
    pMainFighter->GetSkills().GetAllUpSkills(vecSkills);
    pMainFighter->GetSkills().GetPassiveSkills(vecSkills);
    for (auto it = vecSkills.begin(); it != vecSkills.end(); ++it)
    {
        SSkillData skillData;
        skillData.dwSkillID = SKILL_ID(*it);
        skillData.bySkillLvl = SKILL_LEVEL(*it);
        skillData.bySkillQuality = SKILL_QUALITY(*it);
        roleData.vecSkill.push_back(skillData);
    }
    //宝石
    TVecGemstonePtr  vecStone;
    pMainFighter->GetGemstoneSlots().GetGemstoneAll(vecStone);
    for(auto it : vecStone)
        if(it)
            roleData.vecBaoshi.push_back(it->GetItemID());
    
    //心法
    CHeroFighterXinFa &rFighterXinFa = pMainFighter->GetXinFas();
    TVecXinFaInfo vecXinFa;
    rFighterXinFa.HeroFighterXFInfo(vecXinFa);
    for(auto it : vecXinFa)
    {
        SCittaData oCittaData;
        oCittaData.dwCittaID = it.dwXinFaID;
        oCittaData.byLevel = it.byXinFaLvl;
        roleData.vecCitta.push_back(oCittaData);
    }
    //天书
    {
        TVecFloat vecTianbook;
        pFighterManager->GetCittaSlots().GetAddAttr(vecTianbook); 
        for(UINT8 i=0; i<vecTianbook.size(); ++i)
        {
            if(vecTianbook[i] > 0)
            {
                SFtAttrMod oAttr;
                oAttr._eAttr = (EFighterAttr)(i);
                oAttr._fValue = vecTianbook[i];
                roleData.vecTianBookAttr.push_back(oAttr);
            }
        }
    }
    //法宝
    pMainFighter->GetEquipTrumpSlot().GetAllInfo(roleData.vecTrump);
    //稀有法宝
    vector<CItemPtr> vecTrump;
    pFighterManager->GetTrumpSlots().GetAllActiveTrump(vecTrump);
    for (size_t i = 0; i < vecTrump.size(); ++i)
    {
        CTrumpPtr pTrump = dynamic_pointer_cast<CTrump>(vecTrump.at(i));
        if (pTrump && pTrump->IsTrumpItem())
        {
            SRareTrumpData trumpData;
            trumpData.wItemID = pTrump->GetItemID();
            trumpData.byTrumpLvl = pTrump->GetLevel();
            trumpData.bySelected = pTrump->GetUsed();
            roleData.vecRareTrump.push_back(trumpData);
        }
    }
    //美女
    CBeautyMgrPtr pBeauty = pReceivePlayer->GetBeautyMgr();
    if(pBeauty)
    {
        SBeautyData& oData = roleData.sBeauty;
        pBeauty->GetAppear(oData.wBeautyID,oData.byLevel);
        const TVecFloat &vecFloatAttr = pBeauty->GetAttrVec();
        for(UINT8 i=0; i<vecFloatAttr.size(); ++i)
        {
            if(vecFloatAttr[i] > 0)
            {
                SFtAttrMod oAttr;
                oAttr._eAttr = (EFighterAttr)(i);
                oAttr._fValue = vecFloatAttr[i];
                oData.vecAttr.push_back(oAttr);
            }
        }
    }

    //兽魂
    CBeastSoul &rSoul = pFighterManager->GetFormationPet().GetBeastSoul();
    TVecBeastSoulInfo vecBeastSoulInfo;
    rSoul.GetAllInfo(vecBeastSoulInfo);
    roleData.sBeastSoul.vecBeasSoulInfo.insert(roleData.sBeastSoul.vecBeasSoulInfo.end(),vecBeastSoulInfo.begin(),vecBeastSoulInfo.end());
    TVecFloat vecSoulAttr;
    rSoul.AppendAttr(vecSoulAttr);
    for(UINT8 i=0; i<vecSoulAttr.size(); ++i)
    {
        if(vecSoulAttr[i] > 0)
        {
            SFtAttrMod oAttr;
            oAttr._eAttr = (EFighterAttr)(i);
            oAttr._fValue = vecSoulAttr[i];
            roleData.sBeastSoul.vecAttr.push_back(oAttr);
        }
    }
    
    //组合
    TVecFighterCombination vecComb;
    pFighterManager->GetHeroFighterCombinationSlots().GetAllFighterCombination(vecComb); 
    for(auto it : vecComb)
    {
        SCombData oData;
        oData.byGroupID = it.byGroupID;
        oData.byLevel  = it.byGroupLvl;
        oData.bySelected = it.byInLineUp;
        roleData.vecComb.push_back(oData);
    }
    //坐骑
    CHorseMgrPtr pHorse = pReceivePlayer->GetHorseMgr();
    if (pHorse)
    {
        TVecHorseInfo vecHorseInfo;
        pHorse->HorseList(vecHorseInfo);
        for (auto it = vecHorseInfo.begin(); it != vecHorseInfo.end(); ++it)
        {
            SHorseData horseData;
            horseData.dwHorseID = it->dwHorseID;
            horseData.byHorseLvl = it->dwHorseLevel;
            horseData.bySelected = it->dwPos;
            roleData.vecHorse.push_back(horseData);
        }
    }

    //时装
    TVecItem vecFashion;
    pFighterManager->GetFashionSlots().ToProt(vecFashion);
    for (size_t i = 0; i < vecFashion.size(); ++i)
    {
        if (vecFashion[i])
        {
            SFashionPtr pFashion = dynamic_pointer_cast<SFashion>(vecFashion[i]);
            if (pFashion)
            {
                SFashionData fashionData;
                fashionData.wItemID = pFashion->sItemInfo.wItemID;
                fashionData.byFashionLvl = pFashion->byLevel;
                fashionData.bySelected = pFashion->bySelected;
                roleData.vecFashion.push_back(fashionData);
            }
        }
    }

    //称号
    TVecTitle vecTitle;
    CTitlePkg& rTitlePkg = pReceivePlayer->GetTitlePkg();
    rTitlePkg.GetAllTitle(vecTitle);
    for (size_t i = 0; i < vecTitle.size(); ++i)
    {
        STitleData titleData;
        titleData.wTitleID = vecTitle[i].wId;
        titleData.bySelected = vecTitle[i].byEquipPos;
        roleData.vecTitle.push_back(titleData);
    }
    
    //装备
    roleData.sCuiTi.byLianPi = pMainFighter->GetLianPi();
    roleData.sCuiTi.byTongJin = pMainFighter->GetTongJin();
    roleData.sCuiTi.byQiangJi = pMainFighter->GetQiangJi();
    roleData.sCuiTi.byDuanGu = pMainFighter->GetDuanGu();
    roleData.sCuiTi.byHuoLuo = pMainFighter->GetHuoLuo();
    roleData.sCuiTi.byXiSui = pMainFighter->GetXiSui();
        
    return true;
}

//接收：获取散仙信息
bool CViewInfoProtS::OnRecv_GetFighterInfo(
    const std::string& strReceiveName, //对方玩家名字
    UINT64 qwInstID, //散仙唯一ID
    shared_func<SGetFighterInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck(true);
        return false;
    }

    UINT64 qwRoleID = pUser->GetUserID();
    g_Game2DBCommC.Send_GetUserIDFromName(strReceiveName, [this, qwRoleID, qwInstID, fnAck](UINT8 byRet, UINT64 qwReceiveID)
    {
        if(byRet != 0 || qwReceiveID == 0)
        {
            fnAck(true);
            return ;
        }

        CUserPtr pCurUser = CUserMgr::GetUserByUserID(qwRoleID);
        if (NULL == pCurUser)
        {
            fnAck(true);
            return;
        }

        if (qwReceiveID == qwRoleID)
        {
            fnAck(true);
            return;
        }

        CUserPtr pReceive = CUserMgr::GetUserByUserID(qwReceiveID);
        if (NULL != pReceive)
        {
            SFighterData fighterData;
            if (this->GetFighterInfo(qwReceiveID, qwInstID, fighterData))
                fnAck->FighterData = fighterData;
           
            fnAck(true);
            return;
        }
        else
        {
            CUserMgr::LoadUser(qwReceiveID,[this, qwReceiveID, qwInstID, fnAck](CUserPtr pReceive)
            {
                if (NULL != pReceive)
                {
                    SFighterData fighterData;
                    if (this->GetFighterInfo(qwReceiveID, qwInstID, fighterData))
                        fnAck->FighterData = fighterData;
                   
                    fnAck(true);
                    return;
                }
            });
        }
    });

    return true;
}

bool CViewInfoProtS::GetFighterInfo(
    UINT64 qwReceiveID, //对方玩家ID
    UINT64 qwInstID, //散仙唯一ID
    NViewInfoProt::SFighterData& fighterData //散仙信息 
)
{
    CUserPtr pReceive = CUserMgr::GetUserByUserID(qwReceiveID);
    if (NULL == pReceive)
        return false;

    CPlayerPtr pReceivePlayer = pReceive->GetPlayer();
    if (NULL == pReceivePlayer)
        return false;

    CHeroFighterPtr pFighter = dynamic_pointer_cast<CHeroFighter>(pReceivePlayer->GetFighterByInstID(qwInstID));
    if (NULL == pFighter)
        return false;

    //基本信息
    fighterData.wFighterID = pFighter->GetID();
    fighterData.byLevel = pFighter->GetLevel();
    fighterData.dwBTPoint = pFighter->GetBattlePoint();
    const TVecFloat& vecAttr = pFighter->GetBPAttrVec();
    TVecFtAttrMod vecAttrInfo;
    for(UINT32 i = 0; i< vecAttr.size(); ++i)
    {
        if(vecAttr[i] > 0)
        {
            SFtAttrMod oInfo;
            oInfo._eAttr = (EFighterAttr)i;
            oInfo._fValue = vecAttr[i];
            fighterData.vecAttr.push_back(oInfo);
        }
    }

    //技能
    TVecUINT32 vecSkills;
    pFighter->GetSkills().GetAllUpSkills(vecSkills);
    pFighter->GetSkills().GetPassiveSkills(vecSkills);
    for (auto it = vecSkills.begin(); it != vecSkills.end(); ++it)
    {
        SSkillData skillData;
        skillData.dwSkillID = SKILL_ID(*it);
        skillData.bySkillLvl = SKILL_LEVEL(*it);
        skillData.bySkillQuality = SKILL_QUALITY(*it);
        fighterData.vecSkill.push_back(skillData);
    }

    //淬体
    fighterData.sCuiTi.byLianPi = pFighter->GetLianPi();
    fighterData.sCuiTi.byTongJin = pFighter->GetTongJin();
    fighterData.sCuiTi.byQiangJi = pFighter->GetQiangJi();
    fighterData.sCuiTi.byDuanGu = pFighter->GetDuanGu();
    fighterData.sCuiTi.byHuoLuo = pFighter->GetHuoLuo();
    fighterData.sCuiTi.byXiSui = pFighter->GetXiSui();

    //宝石
    TVecGemstonePtr  vecStone;
    pFighter->GetGemstoneSlots().GetGemstoneAll(vecStone);
    for(auto it : vecStone)
        if(it)
            fighterData.vecBaoshi.push_back(it->GetItemID());
    
    //天书心法
    CHeroFighterXinFa &rFighterXinFa = pFighter->GetXinFas();
    TVecXinFaInfo vecXinFa;
    rFighterXinFa.HeroFighterXFInfo(vecXinFa);
    for(auto it : vecXinFa)
    {
        SCittaData oCittaData;
        oCittaData.dwCittaID = it.dwXinFaID;
        oCittaData.byLevel = it.byXinFaLvl;
        fighterData.vecCitta.push_back(oCittaData);
    }
    
    fighterData.sDujie.byTemplateID = pFighter->GetDujieTemplateID();
    fighterData.sDujie.byLevel = pFighter->GetDujieLevel();
    //法宝
    pFighter->GetEquipTrumpSlot().GetAllInfo(fighterData.vecTrump);
    
    return true;
}
