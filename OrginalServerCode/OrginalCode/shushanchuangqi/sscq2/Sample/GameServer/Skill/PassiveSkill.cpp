// =====================================================================================
//
//       Filename:  PassiveSkill.cpp
//
//    Description:  被动技能（其实就只是加属性的）
//
//        Version:  1.0
//        Created:  05/12/2015 05:12:46 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "PassiveSkill.h"

#include "Skill.h"

// ===  FUNCTION  ======================================================================
//         Name:  GetCFG
//  Description:  获取对应配置
// =====================================================================================
const STalentSkillCFG* CPassiveSkillMgr::GetCFG (UINT32 dwPassiveSkill) const
{
    auto it = _mapCFG.find(dwPassiveSkill);
    if (it == _mapCFG.end())
        return NULL;
    else
        return &it->second;
}		// -----  end of function GetCFG  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  LoadConfig
//  Description:  读取配置
// =====================================================================================
bool CPassiveSkillMgr::LoadConfig (const string& strPath)
{
    string strFile = strPath + "Conf/Table/TalentSkill.xml";
    CTalentSkillLoader oLoader;
    if(!oLoader.LoadData(strFile))
        return false;
    _mapCFG.clear();
    for (auto& pCFG : oLoader._vecData)
    {
        if (!pCFG)
        {
            LOG_CRI << "pCFG = NULL";
            continue;
        }
        if (pCFG->_ID != SKILLID_QUALITY_LEVEL(pCFG->_SkillID, pCFG->_Quality, pCFG->_Level))
        {
            LOG_CRI << "CPassiveSkillMgr(" << pCFG->_ID << ") error.";
            return false;
        }
        _mapCFG[pCFG->_ID] = *pCFG;
    }
    return true;
}		// -----  end of function LoadConfig  ----- //

