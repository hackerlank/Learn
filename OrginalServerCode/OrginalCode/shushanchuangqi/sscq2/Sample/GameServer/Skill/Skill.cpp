#include "stdafx.h"
#include "Skill.h"
#include "SkillBaseCFG.h"
#include "SkillEffectCFG.h"
#include "Tokenizer.h"

bool CSkillMgr::ReloadCfg(const string& strPath)
{

    _mapSkill.clear();
    _mapSkillEf.clear();
    return LoadSkill(strPath);
}

bool CSkillMgr::Init(const string& strPath)
{
    return LoadSkill(strPath);
}

bool CSkillMgr::LoadSkill(const string& strPath)
{
    if (!LoadSkillCfg(strPath))
        return false;
    if (!LoadSkillEffectCfg(strPath))
        return false;
    return true;
}

bool CSkillMgr::ReLoadConfig(const string &strFile)
{
    string strPath; 
    if("SkillBase.xml" == strFile)
    {
        strPath = Config._strConfigDir;
        if (!LoadSkillCfg(strPath))
        return false;
    }else if("SkillEffect.xml" == strFile)
    {
        strPath = Config._strConfigDir;
        if (!LoadSkillEffectCfg(strPath))
        return false;
    }
    return true;
}

bool CSkillMgr::LoadSkillCfg(const string& strPath)
{
    CSkillBaseLoader cfg;
    string strConfig = strPath + "Conf/Table/SkillBase.xml";

    if(!cfg.LoadData(strConfig))
        return false;

    LOG_INF << "Loading SkillBase.xml Config...";
    vector<SSkillBaseCFG*>::iterator iter;
    for (iter = cfg._vecData.begin(); iter != cfg._vecData.end(); iter++)
    {
        SSkillPtr pSkill(new SSkill);
        if (pSkill == NULL)
            return false;
        pSkill->_dwID = (*iter)->_ID;
        pSkill->_strName = (*iter)->_Name;
        pSkill->_eType = static_cast<ESkillType>((*iter)->_type);
        pSkill->_bCanBeCounter = (*iter)->_canBeCounter? true:false;
        AnalysisString2VectorUINT32((*iter)->_probEffect, ";", pSkill->_vecProbEffectID);
        AnalysisString2VectorUINT32((*iter)->_effectid, ";", pSkill->_vecEffectID);
        pSkill->_dwSymbol = (*iter)->_symbol;
        pSkill->_dwAdv = (*iter)->_advance;
        pSkill->_byColor = (*iter)->_Color;
        if(!_mapSkill.insert(make_pair(pSkill->_dwID, pSkill)).second)
        {
            LOG_CRI<<"Skill ID duplicated in Skill : "<< pSkill->_dwID;
            return false;
        }
    }
    return true;
}


bool CSkillMgr::LoadSkillEffectCfg(const string& strPath)
{
    CSkillEffectLoader cfg;
    string strConfig = strPath + "Conf/Table/SkillEffect.xml";

    if(!cfg.LoadData(strConfig))
        return false;

    LOG_INF << "Loading SkillEffect.xml Config...";
    vector<SSkillEffectCFG*>::iterator iter;
    for (iter = cfg._vecData.begin(); iter != cfg._vecData.end(); iter++)
    {
        SSkillEfPtr pSkillEf(new SSkillEf);
        if (pSkillEf == NULL)
            return false;

        pSkillEf->_dwID = (*iter)->_id;
        pSkillEf->_strName = (*iter)->_name;

        pSkillEf->_wCostType = (*iter)->_skillCostType;
        pSkillEf->_dwCost = (*iter)->_skillCost;
        pSkillEf->_byNeedLevel = (*iter)->_needLvl;

        pSkillEf->_dwCD = (*iter)->_cd;
        pSkillEf->_wRate = (*iter)->_rate;

        pSkillEf->_wCond = (*iter)->_cond;
        AnalysisString2VectorUINT32((*iter)->_condstr, ";", pSkillEf->_vecCondValue);
        pSkillEf->_byCondCD = (*iter)->_condCD;
        pSkillEf->_wOutCond = (*iter)->_outCond;
        AnalysisString2VectorUINT32((*iter)->_outCondcondstr, ";", pSkillEf->_vecOutCondValue);
        pSkillEf->_byOutCD = (*iter)->_outCD;

        pSkillEf->_byLast = (*iter)->_last;
        pSkillEf->_wGroupID = (*iter)->_gpId;
        pSkillEf->_wArea = (*iter)->_area;
        pSkillEf->_wType = (*iter)->_type;

        pSkillEf->_fValue1 = (*iter)->_value1;
        pSkillEf->_fValue2 = (*iter)->_value2;
        pSkillEf->_fValue3 = (*iter)->_value3;

        pSkillEf->_dwBattlePoint = (*iter)->_battlePoint;
        AnalysisString2VectorUINT32((*iter)->_buffID, ";", pSkillEf->_vecBuffID);

        if(!_mapSkillEf.insert(make_pair(pSkillEf->_dwID, pSkillEf)).second)
        {
            LOG_CRI<<"Skill Effect ID duplicated in Skill Effect : "<< pSkillEf->_dwID;
            return false;
        }
    }
    return true;
}

bool CSkillMgr::AnalysisString2VectorUINT16(string strValue, string strSep, TVecUINT16& vOut)
{
    vOut.clear();
    Tokenizer tk(strValue, strSep);
    for (size_t i = 0; i < tk.size(); ++i)
    {               
        vOut.push_back(::atoi(tk[i].c_str()));
    }               
    return true;
}

bool CSkillMgr::AnalysisString2VectorUINT32(string strValue, string strSep, TVecUINT32& vOut)
{
    vOut.clear();
    Tokenizer tk(strValue, strSep);
    for (size_t i = 0; i < tk.size(); ++i)
    {               
        vOut.push_back(::atoi(tk[i].c_str()));
    }               
    return true;
}

bool CSkillMgr::AnalysisString2VectorFloat(string strValue, string strSep, TVecFloat& vOut)
{
    vOut.clear();
    Tokenizer tk(strValue, strSep);
    for (size_t i = 0; i < tk.size(); ++i)
    {               
        vOut.push_back(::atof(tk[i].c_str()));
    }               
    return true;
}

SSkillPtr CSkillMgr::GetSkill(UINT32 dwSkillID)
{
    auto it =  _mapSkill.find(dwSkillID);
    if(it != _mapSkill.end())
        return it->second;

    return NULL;
}

SSkillEfPtr CSkillMgr::GetSkillEf(UINT32 dwEffectID)
{
    auto it =  _mapSkillEf.find(dwEffectID);
    if(it != _mapSkillEf.end())
        return it->second;

    return NULL;
}

UINT32 CSkillMgr::GetSkillIDQualityLevel(UINT32 dwSkillID, UINT8 byLevel/* = 1*/, UINT8 byColor/* = 0*/)
{
    if (byColor == 0)
    {
        SSkillPtr pSkillCfg = GetSkill(dwSkillID);
        if (!pSkillCfg)
            return 0;
        byColor = pSkillCfg->_byColor;
    }
    return SKILLID_QUALITY_LEVEL(dwSkillID, byColor, byLevel);
}

