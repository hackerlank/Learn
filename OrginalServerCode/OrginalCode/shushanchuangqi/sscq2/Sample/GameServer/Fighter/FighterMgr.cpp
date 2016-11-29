
#include "FighterMgr.h"
#include "Tokenizer.h"
#include "HeroFighter.h"
#include "UserMgr.h"
#include "FormationProt.h"
#include "Version.h"
#include "Battle.h"
#include "EquipTrumpSlot.h"
#include "Parameter.h"
#ifdef _DEBUG
#include "RTime.h" // XXX: for Check load time.
#endif

#include "GUIDMgr.h"

using namespace NFormationProt;

UINT64 CFighterMgr::_qwVersion = VERSION_INIT;
map<UINT16, SFighterPropCFGEx> CFighterMgr::_mapID2FighterPropCFG;
map<UINT32, SFighterCuiTiCFG> CFighterMgr::_mapTypeLevel2CuiTiCFG;
map<UINT16, SFormationCFGEx> CFighterMgr::_mapID2FormationCFG;
map<UINT16, SPetCFGEx> CFighterMgr::_mapID2PetCFG;
map<UINT16, std::map<UINT8, SPetLevelCFG>> CFighterMgr::_mapID2PetLevelCFG;
//vector<SPetLevelCFG> CFighterMgr::_vecPetLevel2Exp;
map<UINT16, SFighterLvAttrCFG> CFighterMgr::_mapID2FighterLvAttrCFG;
map<UINT32, SFighterStarCFG> CFighterMgr::_mapIDnStar2AttrStar;
map<UINT32, SFighterStarGrowthCFG> CFighterMgr::_mapStar2Growth;
map<UINT8, vector<SDujieTemplateCFGEx*>> CFighterMgr::_mapID2DujieCFG;
map<UINT16, SXinfaCFG> CFighterMgr::_mapID2XinFaCFG;
map<UINT16, std::map<UINT8, SXinfaEffectCFG>> CFighterMgr::_mapID2XinFaLevelCFG;
map<EBeastSoulType, SBeastSoulCFG> CFighterMgr::_mapType2BeastSoulCFG;
map<UINT8, SFighterCombinationCFGEx> CFighterMgr::_mapID2FighterCombinationCFG;
map<UINT32, SFighterCombinationEffectCFGEx> CFighterMgr::_mapID2FighterCombinationEffectCFG;
map<UINT32, UINT8> CFighterMgr::_mapCombSkillID2GroupID;


bool CFighterMgr::Init()
{
    bool bRet = LoadConfig();
    IBattleFighter::_funCreateFromID = &CreateFromID;
    return bRet;
}

bool CFighterMgr::LoadConfig(bool bReload /*= false*/)
{
#ifdef LOAD_TIME_CHECK
    timediff_t tBegin = RTime().usecs();
#endif
    string strPath = Config._strConfigDir + "Conf/Table/DujieTemplate.xml";
    if (!LoadDujieTemplate(bReload, strPath))
        return false;

#ifdef LOAD_TIME_CHECK
    timediff_t tEnd = RTime().usecs();

    UINT64 dwTime = tEnd - tBegin;
    LOG_INF << strPath << ":(" << dwTime << ".";
    tBegin = RTime().usecs();
#endif

    strPath = Config._strConfigDir + "Conf/Table/FighterProp.xml";
    CFighterPropLoader oFighterPropLoader;
    if(!oFighterPropLoader.LoadData(strPath))
    {
        LOG_CRI << "oFighterPropLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oFighterPropLoader._vecData.size(); ++i)
    {
        SFighterPropCFG* pFighterPropCFG = oFighterPropLoader._vecData[i];
        if(pFighterPropCFG->_ID == 0)
            continue;
        SFighterPropCFGEx& rFighterPropCFGEx = _mapID2FighterPropCFG[pFighterPropCFG->_ID];
        rFighterPropCFGEx.SetConfig(*pFighterPropCFG);
        rFighterPropCFGEx._vecSkillID.clear();
        Tokenizer tk(rFighterPropCFGEx._Skills, "|");
        for (size_t i = 0; i < tk.size(); ++i)
        {
            Tokenizer yatk(tk[i], ",");
            UINT32 dwSkillID = atoi(yatk[0].c_str());
            if (dwSkillID)
            {
                UINT32 dwLevel = 1;
                if (yatk.size() > 1)
                    dwLevel = atoi(yatk[1].c_str());
                rFighterPropCFGEx._vecSkillID.push_back(SkillMgr.GetSkillIDQualityLevel(dwSkillID, dwLevel));
            }
        }
        rFighterPropCFGEx._vecSkillIDEx.clear();
        Tokenizer tkEx(rFighterPropCFGEx._SkillsEx, ";");
        for (size_t i = 0; i < tkEx.size(); ++i)
        {
            Tokenizer tkEx2(tkEx[i], "|");
            TVecUINT32 vecSkillsID;
            for (size_t j = 0; j < tkEx2.size(); ++j)
            {
                Tokenizer yatk(tkEx2[j], ",");
                UINT32 dwSkillID = atoi(yatk[0].c_str());
                if (dwSkillID)
                {
                    UINT32 dwLevel = 1;
                    if (yatk.size() > 1)
                        dwLevel = atoi(yatk[1].c_str());
                    vecSkillsID.push_back(SkillMgr.GetSkillIDQualityLevel(dwSkillID, dwLevel));
                }
            }
            rFighterPropCFGEx._vecSkillIDEx.push_back(vecSkillsID);
        }

        rFighterPropCFGEx._vecNormalAttackEx.clear();
        Tokenizer tkAtk(rFighterPropCFGEx._NormalAttackEx, ";");
        for (size_t i = 0; i < tkAtk.size(); ++i)
        {
            UINT32 dwNormalAttackEx = atoi(tkAtk[i].c_str());
            rFighterPropCFGEx._vecNormalAttackEx.push_back(dwNormalAttackEx);
        }

        rFighterPropCFGEx._vecPeerless.clear();
        Tokenizer tk1(rFighterPropCFGEx._Peerless, "|");
        for (size_t i = 0; i < tk1.size(); ++i)
        {
            UINT32 dwSkillID = atoi(tk1[i].c_str());
            if (dwSkillID)
                rFighterPropCFGEx._vecPeerless.push_back(SkillMgr.GetSkillIDQualityLevel(dwSkillID, 1));
        }
        rFighterPropCFGEx._vecPassive.clear();
        Tokenizer tk2(rFighterPropCFGEx._Talent, "|");
        for (size_t i = 0; i < tk2.size(); ++i)
        {
            Tokenizer tk3(tk2[i], ",");
            if (tk3.size() < 2)
            {
                LOG_CRI << rFighterPropCFGEx._ID << " tk3.size() error(" << tk3.size() << "): " << tk2[i] << ".";
                continue;
            }
            UINT32 dwSkillID = atoi(tk3[0].c_str());
            if (dwSkillID)
                rFighterPropCFGEx._vecPassive.push_back(SKILLID_QUALITY_LEVEL(dwSkillID, atoi(tk3[1].c_str()), 1));
        }

        //每个散仙能够学习的心法ID
        rFighterPropCFGEx._vecXinFaID.clear();
        Tokenizer tk6(rFighterPropCFGEx._Xinfa, "|");
        for (size_t i = 0; i < tk6.size(); ++i)
        {
            UINT16 wXinFaID = atoi(tk6[i].c_str());
            if (wXinFaID)
                rFighterPropCFGEx._vecXinFaID.push_back(wXinFaID);
        }

    }

#ifdef LOAD_TIME_CHECK
    tEnd = RTime().usecs();

    dwTime = tEnd - tBegin;
    LOG_INF << strPath << ":(" << dwTime << ".";
    tBegin = RTime().usecs();
#endif

    strPath = Config._strConfigDir + "Conf/Table/FighterCuiTi.xml";
    CFighterCuiTiLoader oFighterCuiTiLoader;
    if(!oFighterCuiTiLoader.LoadData(strPath))
    {
        LOG_CRI << "oFighterCuiTiLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oFighterCuiTiLoader._vecData.size(); ++i)
    {
        SFighterCuiTiCFG* pFighterCuiTiCFG = oFighterCuiTiLoader._vecData[i];
        SFighterCuiTiCFG& rFighterCuiTiCfg = _mapTypeLevel2CuiTiCFG[HEROCUITI_KEY(pFighterCuiTiCFG->_ArmorType, pFighterCuiTiCFG->_IntensifyLevel)];
        rFighterCuiTiCfg = *pFighterCuiTiCFG;
    }
#ifdef LOAD_TIME_CHECK
    tEnd = RTime().usecs();

    dwTime = tEnd - tBegin;
    LOG_INF << strPath << ":(" << dwTime << ".";
    tBegin = RTime().usecs();
#endif

    strPath = Config._strConfigDir + "Conf/Table/Formation.xml";
    CFormationLoader oFormationLoader;
    if(!oFormationLoader.LoadData(strPath))
    {
        LOG_CRI << "oFormationLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oFormationLoader._vecData.size(); ++i)
    {
        SFormationCFG* pFormationCFG = oFormationLoader._vecData[i];
        SFormationCFGEx& rFormationCfg = _mapID2FormationCFG[pFormationCFG->_ID];
        rFormationCfg.SetConfig(*pFormationCFG);
        Tokenizer tk(rFormationCfg._Position, ",");
        for (size_t i = 0; i < tk.size(); ++i)
        {
            UINT8 byPos = atoi(tk[i].c_str()); // TODO: 检查
            rFormationCfg.vecPos.push_back(byPos);
        }

        {
        }
    }
#ifdef LOAD_TIME_CHECK
    tEnd = RTime().usecs();

    dwTime = tEnd - tBegin;
    LOG_INF << strPath << ":(" << dwTime << ".";
    tBegin = RTime().usecs();
#endif

    strPath = Config._strConfigDir + "Conf/Table/Pet.xml";
    CPetLoader oPetLoader;
    if(!oPetLoader.LoadData(strPath))
    {
        LOG_CRI << "oPetLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oPetLoader._vecData.size(); ++i)
    {
        SPetCFG* pPetCFG = oPetLoader._vecData[i];
        SPetCFGEx& rPetCfg = _mapID2PetCFG[pPetCFG->_ID];
        rPetCfg.SetConfig(*pPetCFG);
        {
        }
    }
#ifdef LOAD_TIME_CHECK
    tEnd = RTime().usecs();

    dwTime = tEnd - tBegin;
    LOG_INF << strPath << ":(" << dwTime << ".";
    tBegin = RTime().usecs();
#endif

    strPath = Config._strConfigDir + "Conf/Table/PetLevel.xml";
    CPetLevelLoader oPetLevelLoader;
    if(!oPetLevelLoader.LoadData(strPath))
    {
        LOG_CRI << "oPetLevelLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oPetLevelLoader._vecData.size(); ++i)
    {
        /*SPetLevelCFG* pPetLevelCFG = oPetLevelLoader._vecData[i];
          SPetLevelCFG& rPetLevelCfg = _mapID2PetLevelCFG[pPetLevelCFG->_Level];
          rPetLevelCfg = *pPetLevelCFG;
          _vecPetLevel2Exp.push_back(rPetLevelCfg);*/

        /*SPetLevelCFG* pPetLevelCFG = oPetLevelLoader._vecData[i];
          std::vector<SPetLevelCFG>& rVec = _mapID2PetLevelCFG[pPetLevelCFG->_ID];
          rVec.push_back(*pPetLevelCFG);*/

        SPetLevelCFG* pPetLevelCFG = oPetLevelLoader._vecData[i];
        std::map<UINT16, std::map<UINT8, SPetLevelCFG>>::iterator iter = _mapID2PetLevelCFG.find(pPetLevelCFG->_ID);
        if(iter == _mapID2PetLevelCFG.end())
        {
            std::map<UINT8, SPetLevelCFG> _mapLevel2SPetLevelCFG;
            _mapLevel2SPetLevelCFG.insert(std::make_pair(pPetLevelCFG->_Level, *pPetLevelCFG));
            _mapID2PetLevelCFG.insert(std::make_pair(pPetLevelCFG->_ID, _mapLevel2SPetLevelCFG));
        }
        else
            iter->second.insert(std::make_pair(pPetLevelCFG->_Level, *pPetLevelCFG));
    }
#ifdef LOAD_TIME_CHECK
    tEnd = RTime().usecs();

    dwTime = tEnd - tBegin;
    LOG_INF << strPath << ":(" << dwTime << ".";
    tBegin = RTime().usecs();
#endif

    //升级增加属性 --jlt-- add 2014/5/16
    strPath = Config._strConfigDir + "Conf/Table/FighterLvAttr.xml";
    static CFighterLvAttrLoader oFighterLvAttrLoader;
    oFighterLvAttrLoader.ClearData();
    if(!oFighterLvAttrLoader.LoadData(strPath))
    {
        LOG_CRI << "oFighterLvAttrLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oFighterLvAttrLoader._vecData.size(); ++i)
    {
        SFighterLvAttrCFG* pFighterLvAttrCFG = oFighterLvAttrLoader._vecData[i];
        SFighterLvAttrCFG& rFighterLvAttrCFG = _mapID2FighterLvAttrCFG[pFighterLvAttrCFG->_ID];
        rFighterLvAttrCFG = *pFighterLvAttrCFG;
    }
#ifdef LOAD_TIME_CHECK
    tEnd = RTime().usecs();

    dwTime = tEnd - tBegin;
    LOG_INF << strPath << ":(" << dwTime << ".";
    tBegin = RTime().usecs();
#endif

    strPath = Config._strConfigDir + "Conf/Table/FighterStar.xml";
    CFighterStarLoader oFighterStarLoader;                                    
    oFighterStarLoader.ClearData();                                             
    if(!oFighterStarLoader.LoadData(strPath))                                   
    {                                                                             
        LOG_CRI << "oFighterStarLoader.LoadData fails! Path: " << strPath;
        return false;                                                     
    }
    for(size_t i = 0; i < oFighterStarLoader._vecData.size(); ++i)
    {
        SFighterStarCFG* pFighterStarCFG = oFighterStarLoader._vecData[i];
        SFighterStarCFG& rFighterStarCfg = _mapIDnStar2AttrStar[FIGHTERSTAR_KEY(pFighterStarCFG->_ID, pFighterStarCFG->_Star)];
        rFighterStarCfg= *pFighterStarCFG;
    }
#ifdef LOAD_TIME_CHECK
    tEnd = RTime().usecs();

    dwTime = tEnd - tBegin;
    LOG_INF << strPath << ":(" << dwTime << ".";
    tBegin = RTime().usecs();
#endif

    strPath = Config._strConfigDir + "Conf/Table/FighterStarGrowth.xml";
    CFighterStarGrowthLoader oFighterStarGrowthLoader;
    oFighterStarGrowthLoader.ClearData();
    if(!oFighterStarGrowthLoader.LoadData(strPath))
    {                                                                             
        LOG_CRI << "oFighterStarGrowthLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oFighterStarGrowthLoader._vecData.size(); ++i)
    {
        SFighterStarGrowthCFG* pFighterStarGrowthCFG = oFighterStarGrowthLoader._vecData[i];
        SFighterStarGrowthCFG& rFighterStarGrowthCfg = _mapStar2Growth[pFighterStarGrowthCFG->_ID];
        rFighterStarGrowthCfg = *pFighterStarGrowthCFG;
    }
#ifdef LOAD_TIME_CHECK
    tEnd = RTime().usecs();

    dwTime = tEnd - tBegin;
    LOG_INF << strPath << ":(" << dwTime << ".";
    tBegin = RTime().usecs();
#endif

    strPath = Config._strConfigDir + "Conf/Table/Xinfa.xml";
    CXinfaLoader oXinFaLoader;
    if(!oXinFaLoader.LoadData(strPath))
    {
        LOG_CRI << "oXinFaLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oXinFaLoader._vecData.size(); ++i)
    {
        SXinfaCFG* pXinFaCFG = oXinFaLoader._vecData[i];
        _mapID2XinFaCFG.insert(std::make_pair(pXinFaCFG->_ID, *pXinFaCFG));
    }
#ifdef LOAD_TIME_CHECK
    tEnd = RTime().usecs();

    dwTime = tEnd - tBegin;
    LOG_INF << strPath << ":(" << dwTime << ".";
    tBegin = RTime().usecs();
#endif

    strPath = Config._strConfigDir + "Conf/Table/XinfaEffect.xml";
    CXinfaEffectLoader oXinfaEffectLoader;
    if(!oXinfaEffectLoader.LoadData(strPath))
    {
        LOG_CRI << "oXinfaEffectLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oXinfaEffectLoader._vecData.size(); ++i)
    {
        SXinfaEffectCFG* pXinFaLevelCFG = oXinfaEffectLoader._vecData[i];
        std::map<UINT16, std::map<UINT8, SXinfaEffectCFG>>::iterator iter = _mapID2XinFaLevelCFG.find(pXinFaLevelCFG->_ID);
        if(iter == _mapID2XinFaLevelCFG.end())
        {
            std::map<UINT8, SXinfaEffectCFG> _mapLevel2XinFaLevel;
            _mapLevel2XinFaLevel.insert(std::make_pair(pXinFaLevelCFG->_Level, *pXinFaLevelCFG));
            _mapID2XinFaLevelCFG.insert(std::make_pair(pXinFaLevelCFG->_ID, _mapLevel2XinFaLevel));
        }
        else
            iter->second.insert(std::make_pair(pXinFaLevelCFG->_Level, *pXinFaLevelCFG));
    }
    for (auto& kv : _mapType2BeastSoulCFG)
    {
        SBeastSoulCFG& rCFG = kv.second;
        for (auto& p : rCFG._vecRankConfig)
        {
            if (!p)
                continue;
            for (auto& p2 : p->_vecLevelConfig)
            {
                if (p2)
                    delete p2;
                p2 = NULL;
            }
            delete p;
            p = NULL;
        }
    }
#ifdef LOAD_TIME_CHECK
    tEnd = RTime().usecs();

    dwTime = tEnd - tBegin;
    LOG_INF << strPath << ":(" << dwTime << ".";
    tBegin = RTime().usecs();
#endif

    _mapType2BeastSoulCFG.clear();

    strPath = Config._strConfigDir + "Conf/Table/StarPage.xml";
    CStarPageLoader oStarPageLoader;
    if(!oStarPageLoader.LoadData(strPath))
    {
        LOG_CRI << "oStarPageLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oStarPageLoader._vecData.size(); ++i)
    {
        SStarPageCFG* pStarPageCFG = oStarPageLoader._vecData[i];
        if (pStarPageCFG->_PageType >= eBeastSoulMax || pStarPageCFG->_PageType <= eBeastSoulNone)
        {
            LOG_CRI << "oStarPageLoader.LoadData fails! Type: " << static_cast<UINT32>(pStarPageCFG->_PageType);
            return false;
        }
        EBeastSoulType eType = static_cast<EBeastSoulType>(pStarPageCFG->_PageType);
        SBeastSoulCFG& rCFG = _mapType2BeastSoulCFG[eType];
        if (rCFG._vecRankConfig.size() < static_cast<size_t>(pStarPageCFG->_PageLevel + 1))
        {
            rCFG._vecRankConfig.resize(pStarPageCFG->_PageLevel + 1);
            rCFG._byMaxRank = pStarPageCFG->_PageLevel;
        }
        if (!rCFG._vecRankConfig[pStarPageCFG->_PageLevel])
            rCFG._vecRankConfig[pStarPageCFG->_PageLevel] = new SBeastSoulRankConfig;
        (rCFG._vecRankConfig[pStarPageCFG->_PageLevel])->SetConfig(*pStarPageCFG);

        Tokenizer tk5(pStarPageCFG->_Award, "|");
        for (size_t i = 0; i < tk5.size(); ++i)
        {
            Tokenizer yatk(tk5[i], ",");
            UINT32 dwItemID = atoi(yatk[0].c_str());
            if (dwItemID)
            {     
                UINT32 dwItemCount = 0;
                if (yatk.size() > 1)
                    dwItemCount = atoi(yatk[1].c_str());
                rCFG._vecRankConfig[pStarPageCFG->_PageLevel]->_vecAward.push_back(SBeastSoulItemAward((UINT16)dwItemID, (UINT32)dwItemCount));
            }
        }
    }
#ifdef LOAD_TIME_CHECK
    tEnd = RTime().usecs();

    dwTime = tEnd - tBegin;
    LOG_INF << strPath << ":(" << dwTime << ".";
    tBegin = RTime().usecs();
#endif

    strPath = Config._strConfigDir + "Conf/Table/StarSoul.xml";
    CStarSoulLoader oStarSoulLoader;
    if(!oStarSoulLoader.LoadData(strPath))
    {
        LOG_CRI << "oStarSoulLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oStarSoulLoader._vecData.size(); ++i)
    {
        SStarSoulCFG* pStarSoulCFG = oStarSoulLoader._vecData[i];
        if (pStarSoulCFG->_SoulType >= eBeastSoulMax || pStarSoulCFG->_SoulType <= eBeastSoulNone)
        {
            LOG_CRI << "oStarSoulLoader.LoadData fails! Type: " << static_cast<UINT32>(pStarSoulCFG->_SoulType);
            return false;
        }
        EBeastSoulType eType = static_cast<EBeastSoulType>(pStarSoulCFG->_SoulType);
        SBeastSoulCFG& rCFG = _mapType2BeastSoulCFG[eType];
        if (rCFG._vecRankConfig.size() < static_cast<size_t>(pStarSoulCFG->_StarPage + 1))
        {
            LOG_CRI << "oStarSoulLoader.LoadData fails! StarPage: " << static_cast<UINT32>(pStarSoulCFG->_StarPage);
            return false;
        }
        SBeastSoulRankConfig* pCFG = rCFG._vecRankConfig[pStarSoulCFG->_StarPage];
        if (!pCFG)
        {
            LOG_CRI << "oStarSoulLoader.LoadData fails! Null, StarPage: " << static_cast<UINT32>(pStarSoulCFG->_StarPage);
            return false;
        }
        if (pCFG->_vecLevelConfig.size() < static_cast<size_t>(pStarSoulCFG->_StarLevel + 1))
        {
            pCFG->_vecLevelConfig.resize(pStarSoulCFG->_StarLevel + 1);
            pCFG->_byMaxLevel = pStarSoulCFG->_StarLevel;
        }
        if (!pCFG->_vecLevelConfig[pStarSoulCFG->_StarLevel])
            pCFG->_vecLevelConfig[pStarSoulCFG->_StarLevel] = new SBeastSoulLevelConfig;
        (pCFG->_vecLevelConfig[pStarSoulCFG->_StarLevel])->SetConfig(*pStarSoulCFG);
    }
#ifdef LOAD_TIME_CHECK
    tEnd = RTime().usecs();

    dwTime = tEnd - tBegin;
    LOG_INF << strPath << ":(" << dwTime << ".";
    tBegin = RTime().usecs();
#endif

    strPath = Config._strConfigDir + "Conf/Table/FighterCombination.xml";
    CFighterCombinationLoader oFighterCombinationLoader;
    if(!oFighterCombinationLoader.LoadData(strPath))
    {
        LOG_CRI << "oFighterCombinationLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oFighterCombinationLoader._vecData.size(); ++i)
    {
        SFighterCombinationCFG* pFighterCombinationCFG = oFighterCombinationLoader._vecData[i];
        if(pFighterCombinationCFG->_ID == 0)
            continue;
        SFighterCombinationCFGEx& rFighterCombinationCFGEx = _mapID2FighterCombinationCFG[pFighterCombinationCFG->_ID];
        rFighterCombinationCFGEx.SetConfig(*pFighterCombinationCFG);

        Tokenizer tk(rFighterCombinationCFGEx._Hero, ",");
        for (size_t j = 0; j < tk.size(); ++ j)
        {
            UINT16 wFighterID = atoi(tk[j].c_str());
            if (wFighterID > 0)
                rFighterCombinationCFGEx._vecFighterID.push_back(wFighterID);
        }
        _mapCombSkillID2GroupID.insert(make_pair(pFighterCombinationCFG->_Skill, pFighterCombinationCFG->_ID));
    }
#ifdef LOAD_TIME_CHECK
    tEnd = RTime().usecs();

    dwTime = tEnd - tBegin;
    LOG_INF << strPath << ":(" << dwTime << ".";
    tBegin = RTime().usecs();
#endif

    strPath = Config._strConfigDir + "Conf/Table/FighterCombinationEffect.xml";
    CFighterCombinationEffectLoader oFighterCombinationEffectLoader;
    if(!oFighterCombinationEffectLoader.LoadData(strPath))
    {
        LOG_CRI << "oFighterCombinationEffectLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    for(size_t i = 0; i < oFighterCombinationEffectLoader._vecData.size(); ++i)
    {
        SFighterCombinationEffectCFG* pFighterCombinationEffectCFG = oFighterCombinationEffectLoader._vecData[i];
        if(pFighterCombinationEffectCFG->_ID == 0)
            continue;
        UINT32 dwKey = HEROCOMBINATION_KEY(pFighterCombinationEffectCFG->_ID, pFighterCombinationEffectCFG->_Level);
        SFighterCombinationEffectCFGEx& rFighterCombinationEffectCFGEx = _mapID2FighterCombinationEffectCFG[dwKey];
        rFighterCombinationEffectCFGEx.SetConfig(*pFighterCombinationEffectCFG);
    }
#ifdef LOAD_TIME_CHECK
    tEnd = RTime().usecs();

    dwTime = tEnd - tBegin;
    LOG_INF << strPath << ":(" << dwTime << ".";
    tBegin = RTime().usecs();
#endif
    /////////////////////////////////////

    if (bReload)
        ++_qwVersion;

    return true;
}

bool CFighterMgr::ReLoadConfig(const string &strFile)
{

    bool bReload = true;
    string strPath;
    if("FighterProp.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/FighterProp.xml";
        CFighterPropLoader oFighterPropLoader;
        if(!oFighterPropLoader.LoadData(strPath))
        {
            LOG_CRI << "oFighterPropLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oFighterPropLoader._vecData.size(); ++i)
        {
            SFighterPropCFG* pFighterPropCFG = oFighterPropLoader._vecData[i];
            if(pFighterPropCFG->_ID == 0)
                continue;
            SFighterPropCFGEx& rFighterPropCFGEx = _mapID2FighterPropCFG[pFighterPropCFG->_ID];
            rFighterPropCFGEx.SetConfig(*pFighterPropCFG);
            rFighterPropCFGEx._vecSkillID.clear();
            Tokenizer tk(rFighterPropCFGEx._Skills, "|"); // XXX 主动技能: SKillID[[,SkillLevel]|SKillID[,SkillLevel]...]
            for (size_t i = 0; i < tk.size(); ++i)
            {
                Tokenizer yatk(tk[i], ",");
                UINT32 dwSkillID = atoi(yatk[0].c_str());
                if (dwSkillID)
                {
                    UINT32 dwLevel = 1;
                    if (yatk.size() > 1)
                        dwLevel = atoi(yatk[1].c_str());
                    //rFighterPropCFGEx._vecSkillID.push_back(SKILLANDLEVEL(dwSkillID, dwLevel));
                    rFighterPropCFGEx._vecSkillID.push_back(SkillMgr.GetSkillIDQualityLevel(dwSkillID, dwLevel));
                }
            }
            rFighterPropCFGEx._vecSkillIDEx.clear();
            Tokenizer tkEx(rFighterPropCFGEx._SkillsEx, ";"); // XXX: SKillID[[,SkillLevel]|SKillID[,SkillLevel]...]
            for (size_t i = 0; i < tkEx.size(); ++i)
            {
                Tokenizer tkEx2(tkEx[i], "|");
                TVecUINT32 vecSkillsID;
                for (size_t j = 0; j < tkEx2.size(); ++j)
                {
                    Tokenizer yatk(tkEx2[j], ",");
                    UINT32 dwSkillID = atoi(yatk[0].c_str());
                    if (dwSkillID)
                    {
                        UINT32 dwLevel = 1;
                        if (yatk.size() > 1)
                            dwLevel = atoi(yatk[1].c_str());
                        vecSkillsID.push_back(SkillMgr.GetSkillIDQualityLevel(dwSkillID, dwLevel));
                    }
                }
                rFighterPropCFGEx._vecSkillIDEx.push_back(vecSkillsID);
            }

            rFighterPropCFGEx._vecNormalAttackEx.clear();
            Tokenizer tkAtk(rFighterPropCFGEx._NormalAttackEx, ";");
            for (size_t i = 0; i < tkAtk.size(); ++i)
            {
                UINT32 dwNormalAttackEx = atoi(tkAtk[i].c_str());
                rFighterPropCFGEx._vecNormalAttackEx.push_back(dwNormalAttackEx);
            }

            rFighterPropCFGEx._vecPeerless.clear();
            Tokenizer tk1(rFighterPropCFGEx._Peerless, "|"); // XXX 无双技能: SKillID[[,SkillLevel]|SKillID[,SkillLevel]...]
            for (size_t i = 0; i < tk1.size(); ++i)
            {
                UINT32 dwItemID = atoi(tk1[i].c_str());
                if (dwItemID)
                    rFighterPropCFGEx._vecPeerless.push_back(dwItemID);
            }
            rFighterPropCFGEx._vecPassive.clear();
            Tokenizer tk2(rFighterPropCFGEx._Talent, "|"); // XXX 被动技能: SKillID[[,SkillLevel]|SKillID[,SkillLevel]...]
            for (size_t i = 0; i < tk1.size(); ++i)
            {
                Tokenizer tk3(tk2[i], ",");
                if (tk3.size() < 2)
                {
                    LOG_CRI << rFighterPropCFGEx._ID << " tk3.size() error(" << tk3.size() << "): " << tk2[i] << ".";
                    continue;
                }
                UINT32 dwSkillID = atoi(tk3[0].c_str());
                if (dwSkillID)
                    rFighterPropCFGEx._vecPassive.push_back(SKILLID_QUALITY_LEVEL(dwSkillID, atoi(tk3[1].c_str()), 1));

                    //rFighterPropCFGEx._vecPassive.push_back(SkillMgr.GetSkillIDQualityLevel(dwSkillID, 1));
            }

            //每个散仙能够学习的心法ID
            rFighterPropCFGEx._vecXinFaID.clear();
            Tokenizer tk6(rFighterPropCFGEx._Xinfa, "|");
            for (size_t i = 0; i < tk6.size(); ++i)
            {
                UINT16 wXinFaID = atoi(tk6[i].c_str());
                if (wXinFaID)
                    rFighterPropCFGEx._vecXinFaID.push_back(wXinFaID);
            }
        }
    }else if("FighterCuiTi.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/FighterCuiTi.xml";
        CFighterCuiTiLoader oFighterCuiTiLoader;
        if(!oFighterCuiTiLoader.LoadData(strPath))
        {
            LOG_CRI << "oFighterCuiTiLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oFighterCuiTiLoader._vecData.size(); ++i)
        {
            SFighterCuiTiCFG* pFighterCuiTiCFG = oFighterCuiTiLoader._vecData[i];
            SFighterCuiTiCFG& rFighterCuiTiCfg = _mapTypeLevel2CuiTiCFG[HEROCUITI_KEY(pFighterCuiTiCFG->_ArmorType, pFighterCuiTiCFG->_IntensifyLevel)];
            rFighterCuiTiCfg = *pFighterCuiTiCFG;
        }
    }else if("Formation.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/Formation.xml";
        CFormationLoader oFormationLoader;
        if(!oFormationLoader.LoadData(strPath))
        {
            LOG_CRI << "oFormationLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oFormationLoader._vecData.size(); ++i)
        {
            SFormationCFG* pFormationCFG = oFormationLoader._vecData[i];
            SFormationCFGEx& rFormationCfg = _mapID2FormationCFG[pFormationCFG->_ID];
            rFormationCfg.SetConfig(*pFormationCFG);
            Tokenizer tk(rFormationCfg._Position, ",");
            for (size_t i = 0; i < tk.size(); ++i)
            {
                UINT8 byPos = atoi(tk[i].c_str()); // TODO: 检查
                rFormationCfg.vecPos.push_back(byPos);
            }

            {
            }
        }
    }else if("Pet.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/Pet.xml";
        CPetLoader oPetLoader;
        if(!oPetLoader.LoadData(strPath))
        {
            LOG_CRI << "oPetLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oPetLoader._vecData.size(); ++i)
        {
            SPetCFG* pPetCFG = oPetLoader._vecData[i];
            SPetCFGEx& rPetCfg = _mapID2PetCFG[pPetCFG->_ID];
            rPetCfg.SetConfig(*pPetCFG);
            {
            }
        }
    }else if("PetLevel.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/PetLevel.xml";
        CPetLevelLoader oPetLevelLoader;
        if(!oPetLevelLoader.LoadData(strPath))
        {
            LOG_CRI << "oPetLevelLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oPetLevelLoader._vecData.size(); ++i)
        {
            /*SPetLevelCFG* pPetLevelCFG = oPetLevelLoader._vecData[i];
              SPetLevelCFG& rPetLevelCfg = _mapID2PetLevelCFG[pPetLevelCFG->_Level];
              rPetLevelCfg = *pPetLevelCFG;
              _vecPetLevel2Exp.push_back(rPetLevelCfg);*/

            /*SPetLevelCFG* pPetLevelCFG = oPetLevelLoader._vecData[i];
              std::vector<SPetLevelCFG>& rVec = _mapID2PetLevelCFG[pPetLevelCFG->_ID];
              rVec.push_back(*pPetLevelCFG);*/

            SPetLevelCFG* pPetLevelCFG = oPetLevelLoader._vecData[i];
            std::map<UINT16, std::map<UINT8, SPetLevelCFG>>::iterator iter = _mapID2PetLevelCFG.find(pPetLevelCFG->_ID);
            if(iter == _mapID2PetLevelCFG.end())
            {
                std::map<UINT8, SPetLevelCFG> _mapLevel2SPetLevelCFG;
                _mapLevel2SPetLevelCFG.insert(std::make_pair(pPetLevelCFG->_Level, *pPetLevelCFG));
                _mapID2PetLevelCFG.insert(std::make_pair(pPetLevelCFG->_ID, _mapLevel2SPetLevelCFG));
            }
            else
                iter->second.insert(std::make_pair(pPetLevelCFG->_Level, *pPetLevelCFG));
        }
    }else if("FighterLvAttr.xml" == strFile)
    {
        //升级增加属性 --jlt-- add 2014/5/16
        strPath = Config._strConfigDir + "Conf/Table/FighterLvAttr.xml";
        static CFighterLvAttrLoader oFighterLvAttrLoader;
        oFighterLvAttrLoader.ClearData();
        if(!oFighterLvAttrLoader.LoadData(strPath))
        {
            LOG_CRI << "oFighterLvAttrLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oFighterLvAttrLoader._vecData.size(); ++i)
        {
            SFighterLvAttrCFG* pFighterLvAttrCFG = oFighterLvAttrLoader._vecData[i];
            SFighterLvAttrCFG& rFighterLvAttrCFG = _mapID2FighterLvAttrCFG[pFighterLvAttrCFG->_ID];
            rFighterLvAttrCFG = *pFighterLvAttrCFG;
        }
    }else if("FighterStar.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/FighterStar.xml";
        CFighterStarLoader oFighterStarLoader;                                    
        oFighterStarLoader.ClearData();                                             
        if(!oFighterStarLoader.LoadData(strPath))                                   
        {                                                                             
            LOG_CRI << "oFighterStarLoader.LoadData fails! Path: " << strPath;
            return false;                                                     
        }
        for(size_t i = 0; i < oFighterStarLoader._vecData.size(); ++i)
        {
            SFighterStarCFG* pFighterStarCFG = oFighterStarLoader._vecData[i];
            SFighterStarCFG& rFighterStarCfg = _mapIDnStar2AttrStar[FIGHTERSTAR_KEY(pFighterStarCFG->_ID, pFighterStarCFG->_Star)];
            rFighterStarCfg= *pFighterStarCFG;
        }
    }else if("FighterStarGrowth.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/FighterStarGrowth.xml";
        CFighterStarGrowthLoader oFighterStarGrowthLoader;
        oFighterStarGrowthLoader.ClearData();
        if(!oFighterStarGrowthLoader.LoadData(strPath))
        {                                                                             
            LOG_CRI << "oFighterStarGrowthLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oFighterStarGrowthLoader._vecData.size(); ++i)
        {
            SFighterStarGrowthCFG* pFighterStarGrowthCFG = oFighterStarGrowthLoader._vecData[i];
            SFighterStarGrowthCFG& rFighterStarGrowthCfg = _mapStar2Growth[pFighterStarGrowthCFG->_ID];
            rFighterStarGrowthCfg = *pFighterStarGrowthCFG;
        }
    }else if("DujieTemplate.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/DujieTemplate.xml";
        if (!LoadDujieTemplate(bReload, strPath))
            return false;
    }
    else if("Xinfa.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/Xinfa.xml";
        CXinfaLoader oXinFaLoader;
        if(!oXinFaLoader.LoadData(strPath))
        {
            LOG_CRI << "oXinFaLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        _mapID2XinFaCFG.clear();
        for(size_t i = 0; i < oXinFaLoader._vecData.size(); ++i)
        {
            SXinfaCFG* pXinFaCFG = oXinFaLoader._vecData[i];
            std::map<UINT8, SXinfaCFG> _mapID2XinFaCFG;
            _mapID2XinFaCFG.insert(std::make_pair(pXinFaCFG->_ID, *pXinFaCFG));
        }
    }else if("XinfaEffect.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/XinfaEffect.xml";
        CXinfaEffectLoader oXinfaEffectLoader;
        if(!oXinfaEffectLoader.LoadData(strPath))
        {
            LOG_CRI << "oXinfaEffectLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        _mapID2XinFaLevelCFG.clear();
        for(size_t i = 0; i < oXinfaEffectLoader._vecData.size(); ++i)
        {
            SXinfaEffectCFG* pXinFaLevelCFG = oXinfaEffectLoader._vecData[i];
            std::map<UINT16, std::map<UINT8, SXinfaEffectCFG>>::iterator iter = _mapID2XinFaLevelCFG.find(pXinFaLevelCFG->_ID);
            if(iter == _mapID2XinFaLevelCFG.end())
            {
                std::map<UINT8, SXinfaEffectCFG> _mapLevel2XinFaLevel;
                _mapLevel2XinFaLevel.insert(std::make_pair(pXinFaLevelCFG->_Level, *pXinFaLevelCFG));
                _mapID2XinFaLevelCFG.insert(std::make_pair(pXinFaLevelCFG->_ID, _mapLevel2XinFaLevel));
            }
            else
                iter->second.insert(std::make_pair(pXinFaLevelCFG->_Level, *pXinFaLevelCFG));
        }
    }
    else if ("StarSoul.xml" == strFile || "StarPage.xml" == strFile)
    {
        for (auto& kv : _mapType2BeastSoulCFG)
        {
            SBeastSoulCFG& rCFG = kv.second;
            for (auto& p : rCFG._vecRankConfig)
            {
                for (auto& p2 : p->_vecLevelConfig)
                {
                    delete p2;
                    p2 = NULL;
                }
                delete p;
                p = NULL;
            }
        }
        _mapType2BeastSoulCFG.clear();

        strPath = Config._strConfigDir + "Conf/Table/StarPage.xml";
        CStarPageLoader oStarPageLoader;
        if(!oStarPageLoader.LoadData(strPath))
        {
            LOG_CRI << "oStarPageLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oStarPageLoader._vecData.size(); ++i)
        {
            SStarPageCFG* pStarPageCFG = oStarPageLoader._vecData[i];
            if (pStarPageCFG->_PageType >= eBeastSoulMax || pStarPageCFG->_PageType <= eBeastSoulNone)
            {
                LOG_CRI << "oStarPageLoader.LoadData fails! Type: " << static_cast<UINT32>(pStarPageCFG->_PageType);
                return false;
            }
            EBeastSoulType eType = static_cast<EBeastSoulType>(pStarPageCFG->_PageType);
            SBeastSoulCFG& rCFG = _mapType2BeastSoulCFG[eType];
            if (rCFG._vecRankConfig.size() < static_cast<size_t>(pStarPageCFG->_PageLevel + 1))
            {
                rCFG._vecRankConfig.resize(pStarPageCFG->_PageLevel + 1);
                rCFG._byMaxRank = pStarPageCFG->_PageLevel;
            }
            if (!rCFG._vecRankConfig[pStarPageCFG->_PageLevel])
                rCFG._vecRankConfig[pStarPageCFG->_PageLevel] = new SBeastSoulRankConfig;
            (rCFG._vecRankConfig[pStarPageCFG->_PageLevel])->SetConfig(*pStarPageCFG);

            Tokenizer tk5(pStarPageCFG->_Award, "|");
            for (size_t i = 0; i < tk5.size(); ++i)
            {
                Tokenizer yatk(tk5[i], ",");
                UINT32 dwItemID = atoi(yatk[0].c_str());
                if (dwItemID)
                {     
                    UINT32 dwItemCount = 0;
                    if (yatk.size() > 1)
                        dwItemCount = atoi(yatk[1].c_str());
                    rCFG._vecRankConfig[pStarPageCFG->_PageLevel]->_vecAward.push_back(SBeastSoulItemAward((UINT16)dwItemID, (UINT32)dwItemCount));
                }
            }
        }

        strPath = Config._strConfigDir + "Conf/Table/StarSoul.xml";
        CStarSoulLoader oStarSoulLoader;
        if(!oStarSoulLoader.LoadData(strPath))
        {
            LOG_CRI << "oStarSoulLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        for(size_t i = 0; i < oStarSoulLoader._vecData.size(); ++i)
        {
            SStarSoulCFG* pStarSoulCFG = oStarSoulLoader._vecData[i];
            if (pStarSoulCFG->_SoulType >= eBeastSoulMax || pStarSoulCFG->_SoulType <= eBeastSoulNone)
            {
                LOG_CRI << "oStarSoulLoader.LoadData fails! Type: " << static_cast<UINT32>(pStarSoulCFG->_SoulType);
                return false;
            }
            EBeastSoulType eType = static_cast<EBeastSoulType>(pStarSoulCFG->_SoulType);
            SBeastSoulCFG& rCFG = _mapType2BeastSoulCFG[eType];
            if (rCFG._vecRankConfig.size() < static_cast<size_t>(pStarSoulCFG->_StarPage + 1))
            {
                LOG_CRI << "oStarSoulLoader.LoadData fails! StarSoul: " << static_cast<UINT32>(pStarSoulCFG->_StarPage);
                return false;
            }
            SBeastSoulRankConfig* pCFG = rCFG._vecRankConfig[pStarSoulCFG->_StarPage];
            if (!pCFG)
            {
                LOG_CRI << "oStarSoulLoader.LoadData fails! Null, StarSoul: " << static_cast<UINT32>(pStarSoulCFG->_StarPage);
                return false;
            }
            if (pCFG->_vecLevelConfig.size() < static_cast<size_t>(pStarSoulCFG->_StarLevel + 1))
            {
                pCFG->_vecLevelConfig.resize(pStarSoulCFG->_StarLevel + 1);
                pCFG->_byMaxLevel = pStarSoulCFG->_StarLevel;
            }
            if (!pCFG->_vecLevelConfig[pStarSoulCFG->_StarLevel])
                pCFG->_vecLevelConfig[pStarSoulCFG->_StarLevel] = new SBeastSoulLevelConfig;
            (pCFG->_vecLevelConfig[pStarSoulCFG->_StarLevel])->SetConfig(*pStarSoulCFG);
        }
    }
    else if ("FighterCombination.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/FighterCombination.xml";
        CFighterCombinationLoader oFighterCombinationLoader;
        if(!oFighterCombinationLoader.LoadData(strPath))
        {
            LOG_CRI << "oFighterCombinationLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        _mapID2FighterCombinationCFG.clear();
        _mapCombSkillID2GroupID.clear();
        for(size_t i = 0; i < oFighterCombinationLoader._vecData.size(); ++i)
        {
            SFighterCombinationCFG* pFighterCombinationCFG = oFighterCombinationLoader._vecData[i];
            if(pFighterCombinationCFG->_ID == 0)
                continue;
            SFighterCombinationCFGEx& rFighterCombinationCFGEx = _mapID2FighterCombinationCFG[pFighterCombinationCFG->_ID];
            rFighterCombinationCFGEx.SetConfig(*pFighterCombinationCFG);

            Tokenizer tk(rFighterCombinationCFGEx._Hero, ",");
            for (size_t j = 0; j < tk.size(); ++ j)
            {
                UINT16 wFighterID = atoi(tk[j].c_str());
                if (wFighterID > 0)
                    rFighterCombinationCFGEx._vecFighterID.push_back(wFighterID);
            }
            _mapCombSkillID2GroupID.insert(make_pair(pFighterCombinationCFG->_Skill, pFighterCombinationCFG->_ID));
        }
    }
    else if ("FighterCombinationEffect.xml" == strFile)
    {
        strPath = Config._strConfigDir + "Conf/Table/FighterCombinationEffect.xml";
        CFighterCombinationEffectLoader oFighterCombinationEffectLoader;
        if(!oFighterCombinationEffectLoader.LoadData(strPath))
        {
            LOG_CRI << "oFighterCombinationEffectLoader.LoadData fails! Path: " << strPath;
            return false;
        }
        _mapID2FighterCombinationEffectCFG.clear();
        for(size_t i = 0; i < oFighterCombinationEffectLoader._vecData.size(); ++i)
        {
            SFighterCombinationEffectCFG* pFighterCombinationEffectCFG = oFighterCombinationEffectLoader._vecData[i];
            if(pFighterCombinationEffectCFG->_ID == 0)
                continue;
            UINT32 dwKey = HEROCOMBINATION_KEY(pFighterCombinationEffectCFG->_ID, pFighterCombinationEffectCFG->_Level);
            SFighterCombinationEffectCFGEx& rFighterCombinationEffectCFGEx = _mapID2FighterCombinationEffectCFG[dwKey];
            rFighterCombinationEffectCFGEx.SetConfig(*pFighterCombinationEffectCFG);
        }
    }

    if (bReload)
        ++_qwVersion;
    return true;
}

bool CFighterMgr::LoadDujieTemplate(bool bReload, string strPath)
{
    if (strPath.empty())
        return false;
    CDujieTemplateLoader oDujieLoader;
    oDujieLoader.ClearData();
    if(!oDujieLoader.LoadData(strPath))
    {
        LOG_CRI << "oDujieLoader.LoadData fails! Path: " << strPath;
        return false;
    }
    UINT16 wLastID = 0;
    for(size_t idx = 0; idx < oDujieLoader._vecData.size(); ++idx)
    {
        SDujieTemplateCFG* pDujieCFG = oDujieLoader._vecData[idx];
        if (!pDujieCFG || pDujieCFG->_Level == 0)
            continue;
        vector<SDujieTemplateCFGEx*>& rVec = _mapID2DujieCFG[pDujieCFG->_TemplateId];
        if (bReload && wLastID != pDujieCFG->_TemplateId)
        {
            for (size_t i = 0; i < rVec.size(); ++ i)
                delete rVec[i];
            rVec.clear();
        }
        if (rVec.size() < static_cast<size_t>(pDujieCFG->_Level + 1))
        {
            rVec.resize(pDujieCFG->_Level + 1);
        }

        SDujieTemplateCFGEx* pDujieCFGEx = rVec[pDujieCFG->_Level];
        if (!pDujieCFGEx)
            pDujieCFGEx = new SDujieTemplateCFGEx;
        else
        {
            LOG_CRI << "Error! Repeat TemplateID: " << pDujieCFG->_TemplateId<< " or DujieLevel: " << pDujieCFG->_Level;
            return false;
        }
        pDujieCFGEx->SetConfig(*pDujieCFG);

        Tokenizer tk1(pDujieCFGEx->_NormalSkillUnlock, "|");    //主动技能解锁
        for (size_t i = 0; i < tk1.size(); ++i)
        {
            pDujieCFGEx->_vecActiveUnlock.push_back(atoi(tk1[i].c_str()));
        }
        Tokenizer tk2(pDujieCFGEx->_BuffSkillUnlock, "|");      //被动技能解锁
        for (size_t i = 0; i < tk2.size(); ++i)
        {
            pDujieCFGEx->_vecPassiveUnlock.push_back(atoi(tk2[i].c_str()));
        }

        VECATTR_RESET(pDujieCFGEx->_vecAddAttr);
        PHYATK_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        MGCATK_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        PHYDEF_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        MGCDEF_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        PHYRDC_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        MGCRDC_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        MAXHP_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        SPEED_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        HIT_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        HITRATE_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        DODGE_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        DODGERATE_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        CRITICAL_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        CRTRATE_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        ANTICRITCAL_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        ANTICRTRATE_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        BLOCK_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        BLOCKRATE_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        PIERCE_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        PIERCERATE_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        COUNTER_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        COUNTERRATE_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        RESIST_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        RESISTRATE_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        INITAURA_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        MAXAURA_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        CRIEXTRAADD_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        CRIEXTRARDC_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        METALATK_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        WOODATK_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        WATERATK_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        FIREATK_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        EARTHATK_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        METALDEF_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        WOODDEF_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        WATERDEF_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        FIREDEF_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        EARTHDEF_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        PHYATK_PER_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        MGCATK_PER_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        PHYDEF_PER_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        MGCDEF_PER_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        MAXHP_PER_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        SPEED_PER_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        HIT_PER_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        DODGE_PER_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        CRITICAL_PER_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        ANTICRITCAL_PER_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        BLOCK_PER_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        PIERCE_PER_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        COUNTER_PER_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        RESIST_PER_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        //ANTIEFFECT_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        //COUTEREXTRAADD_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);
        //COUTEREXTRARDC_ADD(pDujieCFGEx->_vecAddAttr, pDujieCFGEx);

        wLastID = pDujieCFGEx->_TemplateId;
        rVec[pDujieCFG->_Level] = pDujieCFGEx;
    }
    return true;
}

SFighterPropCFGEx* CFighterMgr::GetFighterPropCfg(UINT16 wFighterID)
{
    auto it = _mapID2FighterPropCFG.find(wFighterID);
    if(it != _mapID2FighterPropCFG.end())
        return &it->second;
    return NULL;
}

SFighterLvAttrCFG* CFighterMgr::GetFighterLvAttrCfg(UINT16 wFighterID)
{
    auto it = _mapID2FighterLvAttrCFG.find(wFighterID);
    if(it != _mapID2FighterLvAttrCFG.end())
        return &it->second;
    return NULL;
}

UINT16 CFighterMgr::GetDefaultFighterID(UINT8 byJob, ESexType eSex)
{
    UINT16 wRet = 1;
    switch (byJob)
    {
        case 1:
            if (eSex == ESEX_MALE)
                wRet = 1;
            else if (eSex == ESEX_FEMALE)
                wRet = 2;
            break;
        case 2:
            if (eSex == ESEX_MALE)
                wRet = 3;
            else if (eSex == ESEX_FEMALE)
                wRet = 4;
            break;
        case 3:
            if (eSex == ESEX_MALE)
                wRet = 5;
            else if (eSex == ESEX_FEMALE)
                wRet = 6;
            break;
        case 4:
            if (eSex == ESEX_MALE)
                wRet = 7;
            else if (eSex == ESEX_FEMALE)
                wRet = 8;
            break;
    }
    return wRet;
}

const string CFighterMgr::GetFighterName(UINT16 wFighterID)
{
    string strName= "未知";
    SFighterPropCFG* pFighterPropCFG = CFighterMgr::GetFighterPropCfg(wFighterID);
    if (pFighterPropCFG)
        strName = pFighterPropCFG->_Name;
    return strName;

}

CFighterPtr CFighterMgr::Create(UINT16 wFighterID, bool bGenGUID, const CUserPtr& pUser)
{
    SFighterPropCFGEx* pFighterPropCFG = CFighterMgr::GetFighterPropCfg(wFighterID);
    if (!pFighterPropCFG)
        return NULL;

    CFighterPtr pFighter = NULL;
    if (IsHeroFighter(*pFighterPropCFG))
        pFighter.reset(new CHeroFighter(wFighterID));
    else if (IsMonsterOrWorldBossFighter(*pFighterPropCFG))
    {
        CFighterPtr pFighterTmp (new CFighter(wFighterID, eFighterMonster));
        pFighter = pFighterTmp;
    }
    else
        pFighter.reset(new CFighter(wFighterID));

    if (!pFighter)
        return NULL;

    if (pUser)
        pFighter->SetUser(pUser);

    if (bGenGUID)
        pFighter->SetInstID(GET_GUID(GUID_HERO));

    // XXX: 在这里调用的初始化函数不允许写数据库，这里只是初始化为默认值
    // 需要初始化为最终值请在相应的真实对象里去初始化
    pFighter->SetRecruited(false);
    pFighter->SetStar(pFighterPropCFG->_Star);
    pFighter->SetSlot(INVALID_SLOT);
    pFighter->SetPos(INVALID_POS);
    pFighter->SetLevel(pFighterPropCFG->_Level, false);
    pFighter->SetExp(0);
    //pFighter->SetColor(pFighterPropCFG->_Color, true);
    pFighter->InitSkills(pFighterPropCFG->_vecSkillID);
    pFighter->InitFighterAttr();
    //pFighter->RegenAllHP()     //XXX 改为主动调用回满血;
    //派生类调用初始化

    //非产生guid不加入fighter
    if(bGenGUID)
    {
        pFighter->Init();
        CGameBuffMgr::Instance().AddBuffManager(pFighter->GetInstID(), &(*pFighter));

        switch (pFighter->GetType())
        {

            case eFighterHero:
                {
                    CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
                    if (pHeroFighter)
                    {
                        pHeroFighter->InitDujieAttr();
                        pHeroFighter->GetEquipTrumpSlot().TryUnlockSlot(pHeroFighter->GetDujieLevel());
                    }
                }
                break;

            case eFighterMonster:
            default:
                break;
        }
    }
    return pFighter;
}

CFighterPtr CFighterMgr::Create(const SFighterDBInfo& rFighterDBInfo, const CUserPtr& pUser)
{
    CFighterPtr pFighter = Create(rFighterDBInfo.wFighterID, false, pUser);
    if (!pFighter)
        return NULL;

    // Assign from db
    pFighter->SetInstID(rFighterDBInfo.qwInstID);
    pFighter->SetRecruited(rFighterDBInfo.byRecruited?true:false);
    pFighter->SetStar(rFighterDBInfo.byStar);
    pFighter->SetSlot(rFighterDBInfo.iSlot);
    pFighter->SetPos(rFighterDBInfo.iPos);
    pFighter->SetLevel(rFighterDBInfo.byLevel, false);
    pFighter->SetExp(rFighterDBInfo.qwExp);
    pFighter->SetLianPi(rFighterDBInfo.byLianPi);
    pFighter->SetTongJin(rFighterDBInfo.byTongJin);
    pFighter->SetQiangJi(rFighterDBInfo.byQiangJi);
    pFighter->SetDuanGu(rFighterDBInfo.byDuanGu);
    pFighter->SetHuoLuo(rFighterDBInfo.byHuoLuo);
    pFighter->SetXiSui(rFighterDBInfo.byXiSui);
    pFighter->SetDujieLevel(GetDujieLvlByExp(pFighter->GetDujieTemplateID(), rFighterDBInfo.dwDujieExp));
    pFighter->SetDujieExp(rFighterDBInfo.dwDujieExp);
    pFighter->SetSpiritPower(rFighterDBInfo.dwSpiritPower);

    switch (pFighter->GetType())
    {
        case eFighterPlayer:
            {
                if (pFighter->GetPos() == INVALID_POS)
                    pFighter->SetPos(0);
            }
            break;

        case eFighterHero:
            {
                CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
                if (pHeroFighter)
                {
                    pHeroFighter->InitDujieAttr();
                    pHeroFighter->GetEquipTrumpSlot().TryUnlockSlot(pHeroFighter->GetDujieLevel());
                }
            }
            break;

        case eFighterMonster:
            break;

        default:
            return NULL;
            break;
    }

    pFighter->Init();
    pFighter->InitFighterAttr();
    CGameBuffMgr::Instance().AddBuffManager(pFighter->GetInstID(), &(*pFighter));

    return pFighter;
}

bool CFighterMgr::IsMainFighter(SFighterPropCFG& rFighterPropCFG)
{
    return rFighterPropCFG._ID <= SParamConfig::dwMainFigherIDMax;
}

bool CFighterMgr::IsHeroFighter(SFighterPropCFG& rFighterPropCFG)
{
    return rFighterPropCFG._ID <= SParamConfig::dwFighterIDMax;
}

bool CFighterMgr::IsMonsterFighter(SFighterPropCFG& rFighterPropCFG)
{
    return rFighterPropCFG._ID > SParamConfig::dwFighterIDMax && rFighterPropCFG._ID <= SParamConfig::dwMonsterIDMax;
}

bool CFighterMgr::IsWorldBossFighter(SFighterPropCFG& rFighterPropCFG)
{
    return rFighterPropCFG._ID > SParamConfig::dwMonsterIDMax && rFighterPropCFG._ID <= SParamConfig::dwWorldBossIDMax;
}

bool CFighterMgr::IsMonsterOrWorldBossFighter(SFighterPropCFG& rFighterPropCFG)
{
    return rFighterPropCFG._ID > SParamConfig::dwFighterIDMax && rFighterPropCFG._ID <= SParamConfig::dwWorldBossIDMax;
}

SFighterCuiTiCFG* CFighterMgr::GetFighterCuiTiCfg(UINT8 byType, UINT8 byLevel)
{
    UINT32 key = HEROCUITI_KEY(byType, byLevel);
    auto i = _mapTypeLevel2CuiTiCFG.find(key);
    if (i == _mapTypeLevel2CuiTiCFG.end())
        return NULL;
    return &i->second;
}

SFormationCFGEx* CFighterMgr::GetFormationCfg(UINT16 wFormationID)
{
    auto i = _mapID2FormationCFG.find(wFormationID);
    if (i == _mapID2FormationCFG.end())
        return NULL;
    return &i->second;
}

SPetCFGEx* CFighterMgr::GetPetCfg(UINT16 wPetID)
{
    auto i = _mapID2PetCFG.find(wPetID);
    if (i == _mapID2PetCFG.end())
        return NULL;
    return &i->second;
}

SPetLevelCFG* CFighterMgr::GetPetLevelCfg(UINT16 wPetID, UINT8 byPetLevel)
{
    std::map<UINT16, std::map<UINT8, SPetLevelCFG>>::iterator iter = _mapID2PetLevelCFG.find(wPetID);
    if(iter != _mapID2PetLevelCFG.end())
    {
        std::map<UINT8, SPetLevelCFG>::iterator iterA = iter->second.find(byPetLevel);
        if(iterA != iter->second.end())
            return &(iterA->second);
    }

    return NULL;
}

SFighterStarCFG* CFighterMgr::GetFighterStarCfg(UINT8 byInclination, UINT8 byStar)
{
    auto it = _mapIDnStar2AttrStar.find(FIGHTERSTAR_KEY(byInclination, byStar));
    if(it != _mapIDnStar2AttrStar.end())
        return &it->second;

    return NULL;
}

SFighterStarGrowthCFG* CFighterMgr::GetFighterStarGrowthCfg(UINT8 byStar)
{
    auto it = _mapStar2Growth.find(byStar);
    if(it != _mapStar2Growth.end())
        return &it->second;
    return NULL;
}

SDujieTemplateCFGEx* CFighterMgr::GetDujieCFG(UINT8 byTemplateID, UINT8 byLevel)
{
    auto it = _mapID2DujieCFG.find(byTemplateID);
    if(it == _mapID2DujieCFG.end())
        return NULL;
    for (size_t i = 0; i < it->second.size(); ++ i)
    {
        if (it->second[i] && it->second[i]->_Level == byLevel)
            return it->second[i];
    }
    return NULL;
}

bool CFighterMgr::IsDujieMaxLevel(UINT8 byTemplateID, UINT8 byLevel)
{
    auto it = _mapID2DujieCFG.find(byTemplateID);
    if(it == _mapID2DujieCFG.end())
        return true;
    return it->second.size() <= static_cast<size_t>(byLevel) + 1;    //XXX it->second[0]为空
}

UINT8 CFighterMgr::GetDujieMaxLevel(UINT8 byTemplateID)
{
    auto it = _mapID2DujieCFG.find(byTemplateID);
    if(it == _mapID2DujieCFG.end())
        return 0;
    UINT8 byMaxlvl = 0;
    for (size_t i = 1; i < it->second.size(); ++ i)
    {
        byMaxlvl = it->second[i]->_Level;
    }
    return byMaxlvl;
}

UINT8 CFighterMgr::GetDujieLvlByExp(UINT8 byTemplateID, UINT32 dwExp)
{
    auto it = _mapID2DujieCFG.find(byTemplateID);
    if(it == _mapID2DujieCFG.end())
        return 0;
    UINT8 byMaxlvl = 0;
    for (size_t i = 1; i < it->second.size(); ++ i)
    {
        if (it->second[i] && it->second[i]->_Exp > dwExp)
        {
            byMaxlvl = it->second[i]->_Level;
            break;
        }
        else if (it->second[i])
            byMaxlvl = it->second[i]->_Level;
    }
    return byMaxlvl;
}

IBattleFighterPtr CFighterMgr::CreateFromID(UINT16 wFighterID)
{
    CFighterPtr pFighter = CFighterMgr::Create(wFighterID, false);
    if (!pFighter)
        return NULL;
    IBattleFighterPtr pBattleFighter = pFighter->ToBattleFighter(0, EBTINVALID);
    return pBattleFighter;
}

const SXinfaCFG* CFighterMgr::GetXinFaCfg(UINT16 wXinFaID)
{
    std::map<UINT16, SXinfaCFG>::iterator iter = _mapID2XinFaCFG.find(wXinFaID);
    if (iter != _mapID2XinFaCFG.end())
        return &iter->second;

    return NULL;
}

const SXinfaEffectCFG* CFighterMgr::GetXinFaLevelCfg(UINT16 wXinFaID, UINT8 byXinFaLevel) 
{
    std::map<UINT16, std::map<UINT8, SXinfaEffectCFG>>::iterator iter = _mapID2XinFaLevelCFG.find(wXinFaID);
    if(iter != _mapID2XinFaLevelCFG.end())
    {
        std::map<UINT8, SXinfaEffectCFG>::iterator iterA = iter->second.find(byXinFaLevel);
        if(iterA != iter->second.end())
            return &(iterA->second);
    }

    return NULL;
}

const SBeastSoulLevelConfig* CFighterMgr::GetBeastSoulLevelCFG(EBeastSoulType eType, UINT8 byRank, UINT8 byLevel)
{
    auto it = _mapType2BeastSoulCFG.find(eType);
    if (it == _mapType2BeastSoulCFG.end())
        return NULL;
    SBeastSoulCFG& rCFG = it->second;
    if (rCFG._vecRankConfig.size() < static_cast<size_t>(byRank + 1))
        return NULL;
    SBeastSoulRankConfig* pRankCFG = rCFG._vecRankConfig[byRank];
    if (!pRankCFG)
        return NULL;
    if (pRankCFG->_vecLevelConfig.size() < static_cast<size_t>(byLevel + 1))
        return NULL;
    return pRankCFG->_vecLevelConfig[byLevel];
}

const SBeastSoulRankConfig* CFighterMgr::GetBeastSoulRankCFG(EBeastSoulType eType, UINT8 byRank)
{
    auto it = _mapType2BeastSoulCFG.find(eType);
    if (it == _mapType2BeastSoulCFG.end())
        return NULL;
    SBeastSoulCFG& rCFG = it->second;
    if (rCFG._vecRankConfig.size() < static_cast<size_t>(byRank + 1))
        return NULL;
    return rCFG._vecRankConfig[byRank];
}

SFighterCombinationCFGEx* CFighterMgr::GetFighterCombinationCFG(UINT8 byGroupID)
{
    auto it = _mapID2FighterCombinationCFG.find(byGroupID);
    if (it == _mapID2FighterCombinationCFG.end())
        return NULL;
    return &it->second;
}

SFighterCombinationEffectCFGEx* CFighterMgr::GetFighterCombinationEffectCFG(UINT8 byGroupID, UINT8 byGroupLvl)
{
    auto it = _mapID2FighterCombinationEffectCFG.find(HEROCOMBINATION_KEY(byGroupID, byGroupLvl));
    if (it == _mapID2FighterCombinationEffectCFG.end())
        return NULL;
    return &it->second;
}

// 判断当前散仙组合是否是最大等级
bool CFighterMgr::IsMaxCombinationLevel(UINT8 byGroupID, UINT8 byGroupLevel)
{
    SFighterCombinationEffectCFGEx* pCFG = GetFighterCombinationEffectCFG(byGroupID, byGroupLevel + 1);
    if (pCFG)
        return false;
    else
        return true;
}

