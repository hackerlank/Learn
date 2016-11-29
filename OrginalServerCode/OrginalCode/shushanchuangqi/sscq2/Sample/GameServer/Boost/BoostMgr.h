// =====================================================================================
//
//       Filename:  BoostMgr.h
//
//    Description:  玩家加速功能管理
//
//        Version:  1.0
//        Created:  01/20/2015 08:27:48 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef BOOST_MGR_H
#define BOOST_MGR_H

#include "stdafx.h"

#include "Singleton.h"

#include "ProtoCommon.h"

using namespace NProtoCommon;


typedef map     <ECareerType, UINT8>        TMapJobUINT8;
typedef map     <ECareerType, UINT16>       TMapJobUINT16;
typedef map     <ECareerType, UINT32>       TMapJobUINT32;

typedef map     <ECareerType, TVecUINT8>    TMapJobVec8;
typedef map     <ECareerType, TVecUINT16>   TMapJobVec16;
typedef map     <ECareerType, TVecUINT32>   TMapJobVec32;

// =====================================================================================
//        Class:  CBoostMgr
//  Description:  玩家加速管理类
// =====================================================================================
class CBoostMgr : public Singleton<CBoostMgr>
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        bool Init(); // 初始化

        // ====================  ACCESSORS     ======================================= //
        UINT8 GetVIPLevel() const;
        UINT16 GetPlayerLevel() const;
        const TVecUINT32& GetSkillID(ECareerType eCareerType) const;
        UINT16 GetFighterLevel(UINT16 wID) const;

        UINT32 GetMoney(EMoneyType eType) const;

        const TVecUINT16& GetFormationID() const;
        const TVecUINT16& GetPetID() const;
        const TVecUINT16& GetTrumpID(ECareerType eCareerType) const;

        const TVecUINT16& GetFighterID(ECareerType eCareerType) const;

        const TVecUINT16& GetIconAppearID() const;

        // ====================  MUTATORS      ======================================= //

        // ====================  OPERATORS     ======================================= //
        bool Reload(); // 重新加载
        bool ReLoadConfig(const string&);

    private:
        // ====================  METHODS       ======================================= //
        bool LoadConfig(const string& strFile);

        bool LoadSuperConfig (TiXmlElement* pElemSuper);

        bool LoadSuperUserConfig (TiXmlElement* pElemUser);
        bool LoadSuperPlayerConfig (TiXmlElement* pElemPlayer);
        bool LoadSuperJobPlayerConfig (TiXmlElement* pElemJobPlayer);

        bool LoadSuperFighterConfig (TiXmlElement* pElemFighter);

        bool LoadBoostConfig (TiXmlElement* pElemBoost);

        bool LoadBoostUserConfig (TiXmlElement* pElemUser);
        bool LoadBoostPlayerConfig (TiXmlElement* pElemPlayer);
        bool LoadBoostJobPlayerConfig (TiXmlElement* pElemJobPlayer);

        bool LoadBoostFighterConfig (TiXmlElement* pElemFighter);

        // ====================  DATA MEMBERS  ======================================= //
        
        UINT8 _byVIPLevel;
        UINT16 _wPlayerLevel;
        UINT16 _wPlayerEquip;

        map<EMoneyType, UINT32> _mapMoneyCount;
        map<UINT16,     UINT32> _mapItemCount;

        TMapJobUINT16 _mapLevel;

        TMapJobVec16  _mapTrumpIDVec;
        TMapJobUINT16 _mapTrumpLevel;

        TMapJobVec32  _mapSkillIDVec;
        TMapJobUINT16 _mapSkillLevel;

        TVecUINT16 _vecFormationID;
        TVecUINT16 _vecPetID;
        TVecUINT16 _vecIconAppearID;

        TMapJobVec16  _mapFighterIDVec;
        UINT16        _wFighterCuiTiLevel;
        UINT16        _wFighterSkillLevel;
        UINT16        _wFighterXinFaLevel;

}; // -----  end of class CBoostMgr  ----- //
#endif //#ifndef BOOST_MGR_H
