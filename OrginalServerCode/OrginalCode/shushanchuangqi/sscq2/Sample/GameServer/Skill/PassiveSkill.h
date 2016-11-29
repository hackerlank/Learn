// =====================================================================================
//
//       Filename:  PassiveSkill.h
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

#ifndef PASSIVE_SKILL_H
#define PASSIVE_SKILL_H

#include "stdafx.h"

#include "Singleton.h"

#include "TalentSkillCFG.h"

// =====================================================================================
//        Class:  CPassiveSkillMgr
//  Description:  被动技能管理类（主要还是配置）
// =====================================================================================
class CPassiveSkillMgr : public Singleton<CPassiveSkillMgr>
{
    public:
        // ====================  LIFECYCLE     ======================================= //

        // ====================  ACCESSORS     ======================================= //
        const STalentSkillCFG* GetCFG(UINT32 dwPassiveSkill) const;

        // ====================  MUTATORS      ======================================= //
        bool LoadConfig(const string& strPath);

        // ====================  OPERATORS     ======================================= //


    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //
        std::map<UINT32, STalentSkillCFG> _mapCFG;
}; // -----  end of class CPassiveSkillMgr  ----- //

#endif // #ifndef PASSIVE_SKILL_H

