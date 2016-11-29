// =====================================================================================
//
//       Filename:  BeastSoul.h
//
//    Description:  兽魂属性
//
//        Version:  1.0
//        Created:  10/08/2014 04:54:54 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef BEAST_SOUL_H
#define BEAST_SOUL_H

#include "stdafx.h"

#include "RoleInfoDefine.h"
#include "FormationProt.h"


using namespace NRoleInfoDefine;
using namespace NFormationProt;

struct SBSInfo 
{
    SBSInfo():
        _byRank(0), _byLevel(0)
    {
    }
    UINT8 _byRank;
    UINT8 _byLevel;
};				// ----------  end of struct SBSInfo  ---------- //

// =====================================================================================
//        Class:  CBeastSoul
//  Description:  兽魂
// =====================================================================================
class CBeastSoul
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CBeastSoul (CUser& rUser);                             // constructor //
        virtual ~CBeastSoul();

        // ====================  ACCESSORS     ======================================= //
        UINT8 GetLevel(EBeastSoulType eType) const;
        UINT8 GetRank(EBeastSoulType eType) const;

        EBeastSoulResult GetAllInfo(TVecBeastSoulInfo& vecBeastSoulInfo) const;
        void NotifyAllInfo() const;

        bool AppendAttr(TVecFloat& vecAttr) const;
        TVecFloat GetAttrVec() const;

        // ====================  MUTATORS      ======================================= //
        bool LoadFromDB(EBeastSoulType eType, UINT8 byRank, UINT8 byLevel);

        void SetDirty();

        // ====================  OPERATORS     ======================================= //
        EBeastSoulResult UpgradeBeastSoul(EBeastSoulType eType, TVecBeastSoulItem& rvecItems);
        void Update2DB(EBeastSoulType eType);
        
        bool FindBeastSoul(EBeastSoulType eType, UINT8 byRank, UINT8 byLevel);

    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //
        map<EBeastSoulType, SBSInfo> _mapInfo;
        CUser& _rUser;
}; // -----  end of class CBeastSoul  ----- //

#endif // #ifndef BEAST_SOUL_H

