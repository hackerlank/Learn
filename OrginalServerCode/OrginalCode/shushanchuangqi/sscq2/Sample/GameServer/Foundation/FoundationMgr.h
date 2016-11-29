// =====================================================================================
//
//       Filename:  FoundationMgr.h
//
//    Description:  基金管理类
//
//        Version:  1.0
//        Created:  04/17/2015 10:52:19 AM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef FOUNDATION_MGR_H
#define FOUNDATION_MGR_H

#include "stdafx.h"

#include "Singleton.h"
#include "FoundationCFG.h"
#include "ItemProt.h"

using namespace NItemProt;

//蜀山基金
struct SFoundationCFGEx : public SFoundationCFG
{
    void SetConfig(const SFoundationCFG& rFoundationCFG)
    {
        *(SFoundationCFG*)this = rFoundationCFG;
    }

    map<UINT8, SItemGenInfo> _mapItemGen;
    map<UINT8, UINT8> _mapID2Level;     //成长基金用
};

// =====================================================================================
//        Class:  CFoundationMgr
//  Description:  基金管理类
// =====================================================================================
class CFoundationMgr : public Singleton<CFoundationMgr>
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        virtual ~CFoundationMgr ();

        // ====================  ACCESSORS     ======================================= //
        SFoundationCFGEx* GetFoundationCFG(UINT8 byType);

        // ====================  MUTATORS      ======================================= //

        // ====================  OPERATORS     ======================================= //
        bool Init();

    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //

        map<UINT8,SFoundationCFGEx> _mapID2FoundationCFG;

}; // -----  end of class CFoundationMgr  ----- //

#endif // #ifndef FOUNDATION_MGR_H

