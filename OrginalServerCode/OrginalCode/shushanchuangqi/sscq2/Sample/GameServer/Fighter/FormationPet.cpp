
#include "stdafx.h"
#include "Protocols.h"
#include "FormationPet.h"
#include "UtilFunc.h" // XXX: for ValueInVec
#include "FighterMgr.h"

CFormationPet::CFormationPet(CUser& rUser)
    : _rUser(rUser), _oPets(rUser), 
    _oBeastSoul(rUser)
{}

/*
bool CFormationPet::LoadFormationFromDB(const SFormationInfo& sFormationInfo)
{
    CFormationPtr pFormation = _oFormations.AdoptFormation(sFormationInfo.wFormationID, false);
    if (!pFormation)
        return false;
    if (sFormationInfo.bySelected)
        return _oFormations.SetCurrFormation(pFormation, false);
    return true;
}
*/

bool CFormationPet::LoadPetDataFromDB(const SPetDataInfo& sPetDataInfo)
{
    if(!_oPets.LoadPet(sPetDataInfo))
        return false;

    return true;

    /*CPetPtr pPet = _oPets.AdoptPet(sPetDataInfo.wPetID, false);
    if (!pPet)
        return false;
    if (sPetDataInfo.bySelected)
        return _oPets.ActivePet(pPet, 1, false);
    return true;*/
}

bool CFormationPet::LoadRolePetFromDB(const SRolePetInfo& sRolePetInfo)
{
    /*_oPets.SetLevel(sRolePetInfo.byLevel);
    _oPets.SetExp(sRolePetInfo.dwExp);
    _oPets.SetSpirit(sRolePetInfo.dwSpirit);*/
    return true;
}

bool CFormationPet::LoadBeastSoulFromDB(const TVecBeastSoulInfo& vecBeastSoulInfo)
{
    for (auto& rInfo : vecBeastSoulInfo)
    {
        _oBeastSoul.LoadFromDB(rInfo.eType, rInfo.byRank, rInfo.byLevel);
    }
    return true;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

