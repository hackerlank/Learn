// =====================================================================================
//
//       Filename:  HeroFighterTavern.h
//
//    Description:  散仙招募客栈
//
//        Version:  1.0
//        Created:  03/09/2015 08:47:08 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef HERO_FIGHTER_TAVERN_H
#define HERO_FIGHTER_TAVERN_H

#include "stdafx.h"

#include "Singleton.h"

typedef map<UINT16, CTavernPtr> MapTavernPtr;

// =====================================================================================
//        Class:  CTavernMgr
//  Description:  客栈总管理类
// =====================================================================================
class CTavernMgr : public Singleton<CTavernMgr>
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        virtual ~CTavernMgr();

        // ====================  ACCESSORS     ======================================= //
        CTavernPtr GetTavernByFighterID(UINT16 wID) const;

        // ====================  MUTATORS      ======================================= //

        // ====================  OPERATORS     ======================================= //
        bool Init();

    private:
        // ====================  METHODS       ======================================= //
        bool LoadTavernConfig(const string& strPath);

        // ====================  DATA MEMBERS  ======================================= //
        MapTavernPtr    _mapTavernPtr;

}; // -----  end of class CTavernMgr  ----- //

// =====================================================================================
//        Class:  CTavern
//  Description:  客栈
// =====================================================================================
class CTavern
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CTavern (UINT16 wID, UINT16 wMinLevel);                             // constructor //
        virtual ~CTavern();

        // ====================  ACCESSORS     ======================================= //
        UINT16 GetID() const;
        UINT16 GetMinLevel() const;
        CHeroFighterInTavernPtr GetHeroFighter(UINT16 wFighterID) const;

        // ====================  MUTATORS      ======================================= //
        void SetName(const string& strName);
        bool PushHeroFighter(CHeroFighterInTavernPtr pHeroFighter);

        // ====================  OPERATORS     ======================================= //
        
    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //
        typedef map<UINT16, CHeroFighterInTavernPtr> MapHeroFighterInTavernPtr;
        UINT16      _wID;                               // 客栈ID
        string      _strName;                           // 客栈名称

        UINT16      _wMinLevel;                         // 所需等级
        MapHeroFighterInTavernPtr _mapHeroFighterPtr;   // 客栈内散仙

}; // -----  end of class CTavern  ----- //

// =====================================================================================
//        Class:  CHeroFighterInTavern
//  Description:  客栈中的散仙
// =====================================================================================
class CHeroFighterInTavern
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CHeroFighterInTavern (UINT16 wID, UINT16 wGetCondID);   // constructor //
        virtual ~CHeroFighterInTavern();

        // ====================  ACCESSORS     ======================================= //
        UINT16 GetID() const;
        UINT16 GetGetCondID() const;

        // ====================  MUTATORS      ======================================= //
        
        // ====================  OPERATORS     ======================================= //

    private:
        // ====================  METHODS       ======================================= //

        // ====================  DATA MEMBERS  ======================================= //


        UINT16          _wID;               // 散仙ID
        UINT16          _wGetCondID;        // 解锁ID

}; // -----  end of class CHeroFighterInTavern  ----- //


#endif // #ifndef HERO_FIGHTER_TAVERN_H

